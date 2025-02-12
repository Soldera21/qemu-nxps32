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
    int i;
    int dlen = frame->can_dlc;

    if (dlen > 8) {
        return -1;
    }

    buff[6] = (frame->can_id << 2) & 0xFC;
    buff[7] = (frame->can_id >> 6) & 0x1F;

    // Internal code to make two nodes enable internal communication
    if (frame->can_id & QEMU_CAN_RTR_FLAG) { 
        buff[2] |= (1 << 4);
    }

    buff[2] = frame->can_dlc & 0xF;

    for (i = 0; i < dlen; i++) {
        buff[8 + i] = frame->data[i];
    }

    return dlen + 8;
}

static void buff2frame_bas(const uint8_t *buff, qemu_can_frame *frame)
{
    uint8_t i;

    frame->flags = 0;
    frame->can_id = ((buff[6] & 0xFC) >> 2) + ((buff[7] & 0x1F) << 6);

    if (buff[2] & 0x10) { 
        frame->can_id = QEMU_CAN_RTR_FLAG;
    }

    frame->can_dlc = (buff[2] & 0xF);

    frame->can_dlc=4;
    if (frame->can_dlc > 8) {
        frame->can_dlc = 8;
    }

    for (i = 0; i < frame->can_dlc; i++) {
        frame->data[i] = buff[8 + i];
    }
    for (; i < 64; i++) {
        frame->data[i] = 0;
    }
}

/*
#define CAN_ID    0x100 // ID del messaggio CAN
#define CAN_RX_MB 1  // Mailbox 1 per RX
static void flexcan_init(Object *obj) {

    S32K358CanState *s = S32K358_CAN(obj);

    fprintf(stderr,"Entered init CAN\n");
    // PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK; // Abilita clock CAN
    s->mcr |= CAN_MCR_MDIS; // Disabilita CAN per configurazione
    s->ctrl1 = 1 << CAN_CTRL1_PRESDIV_SHIFT | 2 << CAN_CTRL1_PROPSEG_SHIFT | 
                      3 << CAN_CTRL1_PSEG1_SHIFT | 3 << CAN_CTRL1_PSEG2_SHIFT | 1 << CAN_CTRL1_RJW_SHIFT ;
    s->mcr &= ~CAN_MCR_MDIS; // Riabilita CAN
    
    // Configura mailbox RX
    s->rximr[CAN_RX_MB] = 0x00000000;
    s->rxfgmask = (CAN_ID << 18);
    s->imask1 |= (1 << CAN_RX_MB);
    //NVIC_EnableIRQ(CAN0_ORed_IRQn);
}
*/

static void flexcan_write(void *opaque, hwaddr addr, uint64_t val64, unsigned int size){

    S32K358CanState *s = opaque;
    qemu_can_frame frame;

    switch (addr){
        case CAN_MCR_OFFSET:
            // We launch the transmission
            
            // The first 16 bit of val64 are the id
            s->can_data[6] = (val64 & 0x3F) << 2; 
            s->can_data[7] = (val64 >> 6) & 0x1F;  
            // Other 4 bits shifted of 16 is the dlc
            s->can_data[2] = ((val64 >> 16) & 0x0F);
            

            buff2frame_bas(s->can_data, &frame); // Save it inside the frame

            s->esr1 &= ~(1 << 6);

            can_bus_client_send(&s->bus_client, &frame, 1);

            s->esr1 |= (1 << 6);

            s->iflag1 |= (1 << 2);

            s->imask1 |= (1 << 2);

            // We reset the value index, used to index at which point of array we arrived with storing the data
            s->index_can_data=0;

            s32k358_update_irq(s);
            return;

        case CAN_DATA:

            // We take the value and store in the buffer (such as ID, flags, dlc and data)
            
            uint8_t value = val64 & 0xFF; // We take the first 8bits of the data register
            //fprintf(stderr, "Value %d, Index:%d\n",value,s->index_can_data);

            s->can_data[s->index_can_data+8]=value;

            s->index_can_data=(s->index_can_data+1)%44;

            return;
        default:
            qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);

    }
}

static uint64_t flexcan_read(void *opaque, hwaddr addr, unsigned int size) {

    S32K358CanState *s = opaque;
    uint32_t temp = 0;

    switch (addr) {
    case CAN_DATA ... CAN_DATA+44:
        if(s->index_limit_rx_data==0){
            fprintf(stderr,"Error related to can_receive\n");
            return -1;
        }
        temp = s->rx_can_data[s->index_rx_can_data+8];
        s->index_rx_can_data=(s->index_rx_can_data+1)%s->index_limit_rx_data;
        break;
    case IFLAG1_OFFSET:
        temp = s->iflag1;
        break;
    default:
        temp = 0xff;
        break;
    }
    return temp;
}

// Funzione di gestione dell'interrupt CAN (ad esempio, ricezione dei messaggi)
bool s32k358_can_can_receive(CanBusClientState *client) {

    S32K358CanState *s = container_of(client, S32K358CanState, bus_client);

    if ((s->mcr & (1 << 31)) &&  // MDIS (bit 31)
        (s->mcr & (1 << 30)) &&  // FRZ (bit 30)
        (s->mcr & (1 << 25)))    // SOFTRST (bit 25)
        {
        return false;
    }

    return true;
}

// Funzione di ricezione dei messaggi CAN
ssize_t s32k358_can_receive(CanBusClientState *client, const qemu_can_frame *frames, size_t frames_cnt) {
    S32K358CanState *s = container_of(client, S32K358CanState, bus_client);
    static uint8_t rcv[BUFF_SIZE];
    int i;
    int ret = -1;
    const qemu_can_frame *frame = frames;
    s->index_limit_rx_data=0;
    s->index_rx_can_data=0;

    // We check the number of frames received
    if (frames_cnt <= 0) {
        return 0;
    }

    // We set register to reception of message
    s->esr1 |= (1 << 3);

    ret = frame2buff_bas(frame, rcv);
    s->index_limit_rx_data=ret-8; // I want the limit index of only data byte.

    if (ret < 0) {
        s->esr1 &= ~(1 << 3);
        return ret;
    }

    if (ret> BUFF_SIZE){

        //s->status_bas |= (1 << 1); /* Overrun status */
        s->esr1 &= ~(1 << 3);
        //s->interrupt_bas |= (1 << 3);

        s32k358_update_irq(s);

        return ret;

    }

    for (i = 0; i < ret; i++) {
        s->rx_can_data[i % BUFF_SIZE] = rcv[i];
    }
    //s->rx_ptr %= BUFF_SIZE; /* update the pointer. */

    //s->status_bas |= 0x01; /* Set the Receive Buffer Status. DS-p15 */
    //s->interrupt_bas |= (1 << 0);
    s->esr1 &= ~(1 << 3);
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

    s->index_can_data=0;
    s->index_rx_can_data=0;

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
