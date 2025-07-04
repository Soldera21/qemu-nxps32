/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

/*
 * S32K358 SYSCFG
 */

#include "qemu/osdep.h"
#include "hw/misc/s32k358_syscfg.h"
#include "qemu/log.h"
#include "qemu/module.h"

#ifndef STM_SYSCFG_ERR_DEBUG
#define STM_SYSCFG_ERR_DEBUG 0
#endif

#define DB_PRINT_L(lvl, fmt, args...) do { \
    if (STM_SYSCFG_ERR_DEBUG >= lvl) { \
        qemu_log("%s: " fmt, __func__, ## args); \
    } \
} while (0)

#define DB_PRINT(fmt, args...) DB_PRINT_L(1, fmt, ## args)

static void s32k358_syscfg_reset(DeviceState *dev)
{
    S32K358SyscfgState *s = S32K358_SYSCFG(dev);

    s->syscfg_memrmp = 0x00000000;
    s->syscfg_pmc = 0x00000000;
    s->syscfg_exticr1 = 0x00000000;
    s->syscfg_exticr2 = 0x00000000;
    s->syscfg_exticr3 = 0x00000000;
    s->syscfg_exticr4 = 0x00000000;
    s->syscfg_cmpcr = 0x00000000;
}

static uint64_t s32k358_syscfg_read(void *opaque, hwaddr addr,
                                     unsigned int size)
{
    S32K358SyscfgState *s = opaque;

    DB_PRINT("0x%"HWADDR_PRIx"\n", addr);

    switch (addr) {
    case SYSCFG_MEMRMP:
        return s->syscfg_memrmp;
    case SYSCFG_PMC:
        return s->syscfg_pmc;
    case SYSCFG_EXTICR1:
        return s->syscfg_exticr1;
    case SYSCFG_EXTICR2:
        return s->syscfg_exticr2;
    case SYSCFG_EXTICR3:
        return s->syscfg_exticr3;
    case SYSCFG_EXTICR4:
        return s->syscfg_exticr4;
    case SYSCFG_CMPCR:
        return s->syscfg_cmpcr;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);
        return 0;
    }

    return 0;
}

static void s32k358_syscfg_write(void *opaque, hwaddr addr,
                       uint64_t val64, unsigned int size)
{
    S32K358SyscfgState *s = opaque;
    uint32_t value = val64;

    DB_PRINT("0x%x, 0x%"HWADDR_PRIx"\n", value, addr);

    switch (addr) {
    case SYSCFG_MEMRMP:
        qemu_log_mask(LOG_UNIMP,
                      "%s: Changing the memory mapping isn't supported " \
                      "in QEMU\n", __func__);
        return;
    case SYSCFG_PMC:
        qemu_log_mask(LOG_UNIMP,
                      "%s: Changing the memory mapping isn't supported " \
                      "in QEMU\n", __func__);
        return;
    case SYSCFG_EXTICR1:
        s->syscfg_exticr1 = (value & 0xFFFF);
        return;
    case SYSCFG_EXTICR2:
        s->syscfg_exticr2 = (value & 0xFFFF);
        return;
    case SYSCFG_EXTICR3:
        s->syscfg_exticr3 = (value & 0xFFFF);
        return;
    case SYSCFG_EXTICR4:
        s->syscfg_exticr4 = (value & 0xFFFF);
        return;
    case SYSCFG_CMPCR:
        s->syscfg_cmpcr = value;
        return;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "%s: Bad offset 0x%"HWADDR_PRIx"\n", __func__, addr);
    }
}

static const MemoryRegionOps s32k358_syscfg_ops = {
    .read = s32k358_syscfg_read,
    .write = s32k358_syscfg_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void s32k358_syscfg_init(Object *obj)
{
    S32K358SyscfgState *s = S32K358_SYSCFG(obj);

    memory_region_init_io(&s->mmio, obj, &s32k358_syscfg_ops, s,
                          TYPE_S32K358_SYSCFG, 0x400);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void s32k358_syscfg_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = s32k358_syscfg_reset;
}

static const TypeInfo s32k358_syscfg_info = {
    .name          = TYPE_S32K358_SYSCFG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K358SyscfgState),
    .instance_init = s32k358_syscfg_init,
    .class_init    = s32k358_syscfg_class_init,
};

static void s32k358_syscfg_register_types(void)
{
    type_register_static(&s32k358_syscfg_info);
}

type_init(s32k358_syscfg_register_types)
