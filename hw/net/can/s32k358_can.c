/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

/*
 * S32K358 CAN
 */

#include "qemu/osdep.h"
#include "hw/net/s32k358_can.h"
#include "hw/net/s32k358_can_mapping.h" // Map addresses of each register CAN
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "net/can_emu.h"
#include <stdio.h>

static void s32k358_update_irq(S32K358CanState *s)
{
    uint32_t mask = (s->iflag1 & s->imask1) | (s->iflag2 & s->imask2) | (s->iflag3 & s->imask3);

    if (mask) {
        qemu_set_irq(s->irq, 1);
    } else {
        qemu_set_irq(s->irq, 0);
    }
}

static int frame2buff_bas( const qemu_can_frame *frame, uint8_t *buff)
{
    uint8_t len = frame->can_dlc;
    buff[2] = (buff[2] & 0xF0) | (len & 0x0F);
    buff[6] = (frame->can_id & 0x3F) << 2;
    buff[7] = (frame->can_id >> 6) & 0x1F;

    uint8_t i;
    for (i = 0; i < frame->can_dlc; i++) {
        buff[8 + i] = frame->data[i];
    }
    for (; i < 64; i++) {
        buff[8 + i] = 0;
    }

    return len + 8;
}

static void buff2frame_bas(const uint8_t *buff, qemu_can_frame *frame)
{
    frame->can_id = ((buff[6] >> 2) & 0b111111) | ((buff[7] & 0b11111) << 6);
    frame->can_dlc = buff[2] & 0b1111;
    frame->flags = 0;

    uint8_t i = 0;
    for (i = 0; i < frame->can_dlc; i++) {
        frame->data[i] = buff[8 + i];
    }
    for (; i < 64; i++) {
        frame->data[i] = 0;
    }
}

static void flexcan_write(void *opaque, hwaddr addr, uint64_t val64, unsigned int size){

    S32K358CanState *s = opaque;
    qemu_can_frame frame;

    switch(addr) {
        case CAN_CTRL1_OFFSET:
            s->ctrl1 = val64;
            return;
        case IFLAG1_OFFSET:
            s->iflag1 = val64;
            return;
        case IMASK1_OFFSET:
            s->imask1 = val64;
            return;
        case ESR1_OFFSET:
            s->esr1 = val64;
            break;
        case CAN_MCR_OFFSET:
            s->mcr = val64;
            break;
        case CAN_DATA ... CAN_DATA+BUFF_SIZE:
            uint16_t base = addr - CAN_DATA;
            s->can_data[base] = (uint8_t)val64;

            // find base address of memory buffer cell and offset
            uint16_t offset = 0;
            if(base < 72*7) {
                offset = base % 72;
            }
            else if(base < 72*14+8) {
                offset = (base-8) % 72;
            }
            else {
                offset = (base-16) % 72;
            }
            base = base - offset;

            // If changing a code verify if it is for transmitting in channel
            if(offset == 3) {
                uint8_t code = s->can_data[base+offset] & 0b1111;
                if(code == 0b1100 && !(s->mcr & (1 << 31))) {
                    // Transmit procedure...
                    uint8_t data[72];
                    for(int i = base; i < base+72; i++) {
                        data[i-base] = s->can_data[i];
                    }

                    buff2frame_bas(data, &frame); // Save it inside the frame

                    // If channel is busy then abort transmission
                    if(s->esr1 & (1 << 6)){
                        return;
                    }

                    s->esr1 |= (1 << 6);
                    can_bus_client_send(&s->bus_client, &frame, 1);
                    s->esr1 &= ~(1 << 6);

                    s32k358_update_irq(s);
                }
            }
            return;
        default:
            qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);

    }
}

static uint64_t flexcan_read(void *opaque, hwaddr addr, unsigned int size) {

    S32K358CanState *s = opaque;
    uint64_t temp = 0;

    switch (addr) {
        case CAN_DATA ... CAN_DATA+BUFF_SIZE:
            // Return value in corresponding cell...
            uint16_t base = addr - CAN_DATA;
            temp = s->can_data[base];
            break;
        case IFLAG1_OFFSET:
            temp = s->iflag1;
            break;
        case IMASK1_OFFSET:
            temp = s->imask1;
            break;
        case CAN_CTRL1_OFFSET:
            temp = s->ctrl1;
            break;
        case ESR1_OFFSET:
            temp = s->esr1;
            break;
        case CAN_MCR_OFFSET:
            temp = s->mcr;
            break;
        default:
            temp = 0xff;
            break;
    }
    return temp;
}

// Check if there is an empty buffer
static bool can_has_empty_buffer(S32K358CanState *s) {
    bool ret = false;
    uint16_t cont = 0;
    uint8_t n = 0;
    while(!ret && n < 21) {
        if( ( ((s->iflag1 >> n) & 1) == 0 && (s->can_data[cont+3] & 0b1111) == 0b0100 ) ||
            ( ((s->iflag1 >> n) & 1) == 1 && (s->can_data[cont+3] & 0b1111) == 0b1000 ) ) {
            ret = true;
        }

        cont += 72;
        if(cont == 72*7) {
            cont += 8;
        }
        if(cont == 72*14+8) {
            cont += 8;
        }
        n++;
    }
    return ret;
}

// Find the empty buffer
static uint16_t can_find_empty_buffer(S32K358CanState *s) {
    bool free = false;
    uint16_t cont = 0;
    uint8_t n = 0;
    while(!free && n < 21) {
        if( ( ((s->iflag1 >> n) & 1) == 0 && (s->can_data[cont+3] & 0b1111) == 0b0100 ) ||
            ( ((s->iflag1 >> n) & 1) == 1 && (s->can_data[cont+3] & 0b1111) == 0b1000 ) ) {
            free = true;
        }
        if(!free){
            cont += 72;
            if(cont == 72*7) {
                cont += 8;
            }
            if(cont == 72*14+8) {
                cont += 8;
            }
            n++;
        }
    }
    return cont;
}

// Funzione di gestione dell'interrupt CAN (ad esempio, ricezione dei messaggi)
bool s32k358_can_can_receive(CanBusClientState *client) {
    S32K358CanState *s = container_of(client, S32K358CanState, bus_client);

    if ((s->mcr & (1 << 31)) &&  // MDIS (bit 31)
        (s->mcr & (1 << 30)) &&  // FRZ (bit 30)
        (s->mcr & (1 << 25)) &&  // SOFTRST (bit 25)
        !can_has_empty_buffer(s) &&
        (s->esr1 & (1 << 3)))
        {
        return false;
    }

    return true;
}

// Funzione di ricezione dei messaggi CAN
ssize_t s32k358_can_receive(CanBusClientState *client, const qemu_can_frame *frame, size_t frames_cnt) {
    S32K358CanState *s = container_of(client, S32K358CanState, bus_client);
    static uint8_t data[72];

    if(!can_has_empty_buffer(s)) {
        return -1;
    }
    uint16_t base = can_find_empty_buffer(s);

    s->esr1 |= (1 << 3);

    int ret = frame2buff_bas(frame, data);
    if (ret < 0) {
        s->esr1 &= ~(1 << 3);
        return ret;
    }
    if (ret > 72){
        s->esr1 &= ~(1 << 3);
        s32k358_update_irq(s);

        return ret;
    }

    for(int i = base; i < base+72; i++) {
        s->can_data[i] = data[i-base];
    }
    s->esr1 &= ~(1 << 3);

    s->can_data[base+3] = (s->can_data[base+3] & 0xF0) | (0b0010 & 0x0F);
    s->iflag1 |= (1 << (base/72));
    s->imask1 |= (1 << (base/72));

    s32k358_update_irq(s);

    return 1;
}

static const MemoryRegionOps s32k358_can_ops = {
    .read = flexcan_read,
    .write = flexcan_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static CanBusClientInfo can_bus_client_info = {
    .can_receive = s32k358_can_can_receive,
    .receive = s32k358_can_receive,
};

static int can_connect_to_bus(S32K358CanState *s, CanBusState *bus)
{
    s->bus_client.info = &can_bus_client_info; // We connect the client to the structure of "receive" and "can receive"

    if (!bus) {
        return -EINVAL;
    }

    if (can_bus_insert_client(bus, &s->bus_client) < 0) { // Effectively insert the client in the bus
        return -1;
    }

    return 0;
}

// Initialitation of CAN device
static void s32k358_can_init(Object *obj) {
    S32K358CanState *s = S32K358_CAN(obj);
    
    object_property_add_link(obj, "canbus", TYPE_CAN_BUS,
                             (Object **)&s->canbus,
                             qdev_prop_allow_set_link_before_realize,
                             0);
}

static void s32k358_can_reset(DeviceState *dev)
{
    S32K358CanState *s = S32K358_CAN(dev);

    s->mcr        = 0xD890000F;
    s->ctrl1      = 0x00000000;
    s->timer      = 0x00000000;
    s->ecr        = 0x00000000;
    s->esr1       = 0x00000000;
    s->imask2     = 0x00000000;
    s->imask1     = 0x00000000;
    s->iflag2     = 0x00000000;
    s->iflag1     = 0x00000000;
    s->ctrl2      = 0x00600000;
    s->esr2       = 0x00000000;
    s->crcr       = 0x00000000;
    s->cbt        = 0x00000000;
    s->imask3     = 0x00000000;
    s->iflag3     = 0x00000000;
    s->et         = 0x00000000;
    s->fltconf_ie = 0x00000000;
    s->mecr       = 0x800C0080;
    s->erriar     = 0x00000000;
    s->erridpr    = 0x00000000;
    s->errippr    = 0x00000000;
    s->rerrar     = 0x00000000;
    s->rerrdr     = 0x00000000;
    s->rerrsynr   = 0x00000000;
    s->errsr      = 0x00000000;
    s->eprs       = 0x00000000;
    s->encbt      = 0x00000000;
    s->edcbt      = 0x00000000;
    s->etdc       = 0x00000000;
    s->fdctrl     = 0x80000100;
    s->fdcbt      = 0x00000000;
    s->fdcrc      = 0x00000000;
    s->erfcr      = 0x00000000;
    s->erfier     = 0x00000000;
    s->erfsr      = 0x00000000;    

    uint16_t cont = 0;
    uint8_t n = 0;
    while(n < 21) {
        s->can_data[cont+3] = 0x04;

        cont += 72;
        if(cont == 72*7) {
            cont += 8;
        }
        if(cont == 72*14+8) {
            cont += 8;
        }
        n++;
    }

    s32k358_update_irq(s);
}

// Funzione di realizzazione del dispositivo CAN
static void s32k358_can_realize(DeviceState *dev, Error **errp) {

    S32K358CanState *s = S32K358_CAN(dev);

    s->canbus=can_bus_find_by_name(NULL, true);

    if (s->canbus == NULL) {
        fprintf(stderr,"Cannot create can find/allocate CAN bus");
        return;
    }

    sysbus_init_irq(SYS_BUS_DEVICE(OBJECT(s)), &s->irq);

    qemu_irq_lower(s->irq);

    s32k358_can_reset(dev);

    memory_region_init_io(&s->mmio, OBJECT(s), &s32k358_can_ops, s, TYPE_S32K358_CAN, 0x4000); // mapped CAN

    sysbus_init_mmio(SYS_BUS_DEVICE(s), &s->mmio);

    if (can_connect_to_bus(s, s->canbus) < 0) {
        fprintf(stderr, "can_connect_to_bus failed");
        return;
    }
}

// Funzione di inizializzazione della classe del dispositivo CAN
static void s32k358_can_class_init(ObjectClass *klass, void *data) {
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = s32k358_can_reset;
    dc->realize = s32k358_can_realize;
    //dc->exit = s32k358_can_exit;
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

// Definizione delle informazioni di tipo del dispositivo CAN
static const TypeInfo s32k358_can_info = {
    .name          = TYPE_S32K358_CAN,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K358CanState),
    .instance_init = s32k358_can_init,
    .class_init    = s32k358_can_class_init,
};

// Funzione di registrazione del tipo del dispositivo CAN
static void s32k358_can_register_types(void) {
    type_register_static(&s32k358_can_info);
}

type_init(s32k358_can_register_types)