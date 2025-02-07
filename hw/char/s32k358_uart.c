/*
 * S32K358 UART
 */

#include "qemu/osdep.h"
#include "hw/char/s32k358_uart.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "qemu/log.h"
#include "qemu/module.h"

#ifndef STM_UART_ERR_DEBUG
#define STM_UART_ERR_DEBUG 0
#endif

#define DB_PRINT_L(lvl, fmt, args...) do { \
    if (STM_UART_ERR_DEBUG >= lvl) { \
        qemu_log("%s: " fmt, __func__, ## args); \
    } \
} while (0)

#define DB_PRINT(fmt, args...) DB_PRINT_L(1, fmt, ## args)

static int s32k358_uart_can_receive(void *opaque)
{
    S32K358UartState *s = opaque;

    if (!(s->uart_sr & UART_SR_RXNE)) {
        return 1;
    }

    return 0;
}

static void s32k358_update_irq(S32K358UartState *s)
{
    uint32_t mask = s->uart_sr & s->uart_cr1;

    if (mask & (UART_SR_TXE | UART_SR_TC | UART_SR_RXNE)) {
        qemu_set_irq(s->irq, 1);
    } else {
        qemu_set_irq(s->irq, 0);
    }
}

static void s32k358_uart_receive(void *opaque, const uint8_t *buf, int size)
{
    S32K358UartState *s = opaque;

    if (!(s->uart_cr1 & UART_CR1_UE && s->uart_cr1 & UART_CR1_RE)) {
        /* UART not enabled - drop the chars */
        DB_PRINT("Dropping the chars\n");
        return;
    }

    s->uart_dr = *buf;
    s->uart_sr |= UART_SR_RXNE;

    s32k358_update_irq(s);

    DB_PRINT("Receiving: %c\n", s->uart_dr);
}

static void s32k358_uart_reset(DeviceState *dev)
{
    S32K358UartState *s = S32K358_UART(dev);

    s->uart_sr = UART_SR_RESET;
    s->uart_dr = 0x00000000;
    s->uart_brr = 0x00000000;
    s->uart_cr1 = 0x00000000;
    s->uart_cr2 = 0x00000000;
    s->uart_cr3 = 0x00000000;
    s->uart_gtpr = 0x00000000;

    s32k358_update_irq(s);
}

static uint64_t s32k358_uart_read(void *opaque, hwaddr addr,
                                       unsigned int size)
{
    S32K358UartState *s = opaque;
    uint64_t retvalue;

    DB_PRINT("Read 0x%"HWADDR_PRIx"\n", addr);

    switch (addr) {
    case UART_SR:
        retvalue = s->uart_sr;
        qemu_chr_fe_accept_input(&s->chr);
        return retvalue;
    case UART_DR:
        DB_PRINT("Value: 0x%" PRIx32 ", %c\n", s->uart_dr, (char) s->uart_dr);
        retvalue = s->uart_dr & 0x3FF;
        s->uart_sr &= ~UART_SR_RXNE;
        qemu_chr_fe_accept_input(&s->chr);
        s32k358_update_irq(s);
        return retvalue;
    case UART_BRR:
        return s->uart_brr;
    case UART_CR1:
        return s->uart_cr1;
    case UART_CR2:
        return s->uart_cr2;
    case UART_CR3:
        return s->uart_cr3;
    case UART_GTPR:
        return s->uart_gtpr;
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

    DB_PRINT("Write 0x%" PRIx32 ", 0x%"HWADDR_PRIx"\n", value, addr);

    switch (addr) {
    case UART_SR:
        if (value <= 0x3FF) {
            /* I/O being synchronous, TXE is always set. In addition, it may
               only be set by hardware, so keep it set here. */
            s->uart_sr = value | UART_SR_TXE;
        } else {
            s->uart_sr &= value;
        }
        s32k358_update_irq(s);
        return;
    case UART_DR:
        if (value < 0xF000) {
            ch = value;
            /* XXX this blocks entire thread. Rewrite to use
             * qemu_chr_fe_write and background I/O callbacks */
            qemu_chr_fe_write_all(&s->chr, &ch, 1);
            /* XXX I/O are currently synchronous, making it impossible for
               software to observe transient states where TXE or TC aren't
               set. Unlike TXE however, which is read-only, software may
               clear TC by writing 0 to the SR register, so set it again
               on each write. */
            s->uart_sr |= UART_SR_TC;
            s32k358_update_irq(s);
        }
        return;
    case UART_BRR:
        s->uart_brr = value;
        return;
    case UART_CR1:
        s->uart_cr1 = value;
        s32k358_update_irq(s);
        return;
    case UART_CR2:
        s->uart_cr2 = value;
        return;
    case UART_CR3:
        s->uart_cr3 = value;
        return;
    case UART_GTPR:
        s->uart_gtpr = value;
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
    device_class_set_props(dc, s32k358_uart_properties);
    dc->realize = s32k358_uart_realize;
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
