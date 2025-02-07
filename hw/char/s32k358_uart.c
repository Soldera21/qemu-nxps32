/*
 * S32K358 UART
 */

#include "qemu/osdep.h"
#include "hw/char/s32k358_uart.h"
#include "hw/char/s32k358_uart_mapping.h" // Map addresses of each register UART
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "qemu/log.h"
#include "qemu/module.h"

#ifndef STM_UART_ERR_DEBUG
#define STM_UART_ERR_DEBUG 0
#endif

#define CAN_ID    0x100 // ID del messaggio CAN

#define DB_PRINT_L(lvl, fmt, args...) do { \
    if (STM_UART_ERR_DEBUG >= lvl) { \
        qemu_log("%s: " fmt, __func__, ## args); \
    } \
} while (0)

#define DB_PRINT(fmt, args...) DB_PRINT_L(1, fmt, ## args)

static void s32k358_update_irq(S32K358UartState *s)
{
    uint32_t mask = s->uart_stat & s->uart_ctrl;

    if (mask & (UART_STAT_TDRE | UART_STAT_TC | UART_STAT_RDRF)) {
        qemu_set_irq(s->irq, 1);
    } else {
        qemu_set_irq(s->irq, 0);
    }
}


static int s32k358_uart_can_receive(void *opaque)
{
    S32K358UartState *s = opaque;

    if (!(s->uart_stat & UART_STAT_RDRF)) {
        return 1;
    }

    return 0;
}

static void s32k358_uart_receive(void *opaque, const uint8_t *buf, int size)
{
    S32K358UartState *s = opaque;

    fprintf(stderr, "Called uart receive\n");
    if (!(s->uart_ctrl & UART_CTRL_TE && s->uart_ctrl & UART_CTRL_RE)) {
        fprintf(stderr, "Drop\n");
        return;
    }

    s->uart_data = *buf;
    //s->uart_dr = *buf;
    s->uart_stat |= UART_STAT_RDRF;

    s32k358_update_irq(s);

    DB_PRINT("Receiving: %c\n", s->uart_data);
    //DB_PRINT("Receiving: %c\n", s->uart_dr);
}

/*
static void uart_receive_can_command(void *opaque, void *canPointer) {

    S32K358CanState *c= canPointer;
    S32K358UartState *s = opaque;

    if (s->uart_stat & UART_STAT_RDRF) {
        uint8_t cmd = s->uart_data;
        uint8_t data[2] = {cmd, cmd + 1};
        flexcan_send(c,CAN_ID, data, 2);
        fprintf(stderr, "Called CAN\n");
    }
}
*/

static void s32k358_uart_reset(DeviceState *dev)
{
    S32K358UartState *s = S32K358_UART(dev);

    s->uart_verid    = 0x04040007;
    s->uart_param    = 0x00000404;
    s->uart_global   = 0x00000000;
    s->uart_pincfg   = 0x00000000;

    s->uart_baud     = 0x0F000004;
    s->uart_stat     = 0x00C00000;
    s->uart_ctrl     = 0x00000000;
    s->uart_data     = 0x00001000;

    s->uart_match    = 0x00000000;
    s->uart_modir    = 0x00000000;
    s->uart_fifo     = 0x00C00033;
    s->uart_water    = 0x00000000;
    s->uart_dataro   = 0x00001000;
    s->uart_mcr      = 0x00000000;
    s->uart_msr      = 0x00000000;
    s->uart_reir     = 0x00000000;
    s->uart_teir     = 0x00000000;
    s->uart_hdcr     = 0x00000000;
    s->uart_tocr     = 0x00000000;
    s->uart_tosr     = 0x0000000F;

    s->uart_timeout0 = 0x00000000;
    s->uart_timeout1 = 0x00000000;
    s->uart_timeout2 = 0x00000000;
    s->uart_timeout3 = 0x00000000;

    for (int i = 0; i < 128; i++) {
        s->uart_tcbr[i] = 0x00000000;
    }

    for (int i = 0; i < 192; i++) {
        s->uart_tdbr[i] = 0x00000000;
    }

    s32k358_update_irq(s);
}

static uint64_t s32k358_uart_read(void *opaque, hwaddr addr,
                                       unsigned int size)
{
    S32K358UartState *s = opaque;
    uint64_t retvalue;

    DB_PRINT("Read 0x%"HWADDR_PRIx"\n", addr);

    switch (addr) {
    case UART_STAT:
        retvalue = s->uart_stat;
        qemu_chr_fe_accept_input(&s->chr);
        return retvalue;
    case UART_DATA:
        DB_PRINT("Value: 0x%" PRIx32 ", %c\n", s->uart_data, (char) s->uart_data);
        retvalue = s->uart_data & 0x3FF;
        s->uart_data &= ~UART_STAT_RDRF;
        qemu_chr_fe_accept_input(&s->chr);
        s32k358_update_irq(s);
        return retvalue;
    case UART_BAUD:
        return s->uart_baud;
    case UART_CTRL:
        return s->uart_ctrl;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);
        return 0;
    }

    return 0;
}

static void s32k358_uart_write(void *opaque, hwaddr addr,
                                  uint64_t val64, unsigned int size)
{
    S32K358UartState *s = opaque;
    uint32_t value = val64;
    unsigned char ch;

    switch (addr) {
    case UART_STAT:
        s->uart_stat = value;
        return;
    case UART_DATA:
        //parity= value & (1 << 14);
        ch = value & 0xFF; // We take the first 8bits of the data register
        qemu_chr_fe_write_all(&s->chr, &ch, 1);
        s->uart_stat |= UART_STAT_TC;
        return;
    case UART_BAUD:
        s->uart_baud = value;
        return;
    case UART_CTRL:
        s->uart_ctrl |= value;
        return;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);
    }
}

static const MemoryRegionOps s32k358_uart_ops = {
    .read = s32k358_uart_read,
    .write = s32k358_uart_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const Property s32k358_uart_properties[] = {
    DEFINE_PROP_CHR("chardev", S32K358UartState, chr),
    DEFINE_PROP_END_OF_LIST(),
};

static void s32k358_uart_init(Object *obj)
{
    S32K358UartState *s = S32K358_UART(obj);

    sysbus_init_irq(SYS_BUS_DEVICE(obj), &s->irq);
    memory_region_init_io(&s->mmio, obj, &s32k358_uart_ops, s,
                          TYPE_S32K358_UART, 0x400);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void s32k358_uart_realize(DeviceState *dev, Error **errp)
{
    S32K358UartState *s = S32K358_UART(dev);

    qemu_chr_fe_set_handlers(&s->chr, s32k358_uart_can_receive,
                             s32k358_uart_receive, NULL, NULL,
                             s, NULL, true);
}

static void s32k358_uart_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = s32k358_uart_reset;
    dc->realize = s32k358_uart_realize;
    device_class_set_props(dc, s32k358_uart_properties);
}

static const TypeInfo s32k358_uart_info = {
    .name          = TYPE_S32K358_UART,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K358UartState),
    .instance_init = s32k358_uart_init,
    .class_init    = s32k358_uart_class_init,
};

static void s32k358_uart_register_types(void)
{
    type_register_static(&s32k358_uart_info);
}

type_init(s32k358_uart_register_types)
