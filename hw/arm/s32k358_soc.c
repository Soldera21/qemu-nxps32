/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

/*
 * S32K358 SoC
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/module.h"
#include "hw/arm/boot.h"
#include "exec/address-spaces.h"
#include "hw/arm/s32k358_soc.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-clock.h"
#include "sysemu/sysemu.h"

static const uint32_t uart_addr[STM_NUM_UARTS] = { 0x40328000, 0x4032C000, 0x40330000, 0x40334000, 0x40338000, 0x4033C000, 0x40340000, 0x40344000, 0x4048C000, 0x40490000, 0x40494000, 0x40498000, 0x4049C000, 0x404A0000, 0x404A4000, 0x404A8000 };

static const int uart_irq[STM_NUM_UARTS] = { 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172 };

static const uint32_t can_addr=0x40304000;

static const int can_irq=109;

static void s32k358_soc_initfn(Object *obj)
{
    S32K358State *s = S32K358_SOC(obj);
    int i;

    object_initialize_child(obj, "armv7m", &s->armv7m, TYPE_ARMV7M);

    object_initialize_child(obj, "syscfg", &s->syscfg, TYPE_S32K358_SYSCFG);

    for (i = 0; i < STM_NUM_UARTS; i++) {
        object_initialize_child(obj, "uart[*]", &s->uart[i],
                                TYPE_S32K358_UART);
    }

    object_initialize_child(obj, "can",&s->can, TYPE_S32K358_CAN);

    s->sysclk = qdev_init_clock_in(DEVICE(s), "sysclk", NULL, NULL, 0);
    s->refclk = qdev_init_clock_in(DEVICE(s), "refclk", NULL, NULL, 0);
}

static void s32k358_soc_realize(DeviceState *dev_soc, Error **errp)
{
    S32K358State *s = S32K358_SOC(dev_soc);
    DeviceState *dev, *armv7m;
    SysBusDevice *busdev;
    int i;

    MemoryRegion *system_memory = get_system_memory();

    /*
     * We use s->refclk internally and only define it with qdev_init_clock_in()
     * so it is correctly parented and not leaked on an init/deinit; it is not
     * intended as an externally exposed clock.
     */
    if (clock_has_source(s->refclk)) {
        error_setg(errp, "refclk clock must not be wired up by the board code");
        return;
    }

    if (!clock_has_source(s->sysclk)) {
        error_setg(errp, "sysclk clock must be wired up by the board code");
        return;
    }

    /*
     * TODO: ideally we should model the SoC RCC and its ability to
     * change the sysclk frequency and define different sysclk sources.
     */

    /* The refclk always runs at frequency HCLK / 8 */
    clock_set_mul_div(s->refclk, 8, 1);
    clock_set_source(s->refclk, s->sysclk);

    memory_region_init_rom(&s->p_flash, OBJECT(dev_soc), "S32K358.p_flash", PFLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, PFLASH_BASE_ADDRESS, &s->p_flash);

    memory_region_init_rom(&s->d_flash, OBJECT(dev_soc), "S32K358.d_flash", DFLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, DFLASH_BASE_ADDRESS, &s->d_flash);

    memory_region_init_ram(&s->itcm, NULL, "S32K358.itcm", ITCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, ITCM_BASE_ADDRESS, &s->itcm);
    memory_region_init_ram(&s->dtcm, NULL, "S32K358.dtcm", DTCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, DTCM_BASE_ADDRESS, &s->dtcm);

    memory_region_init_ram(&s->sram0, NULL, "S32K358.sram0", SRAM0_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, SRAM0_BASE_ADDRESS, &s->sram0);
    memory_region_init_ram(&s->sram1, NULL, "S32K358.sram1", SRAM1_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, SRAM1_BASE_ADDRESS, &s->sram1);
    memory_region_init_ram(&s->sram2, NULL, "S32K358.sram2", SRAM2_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, SRAM2_BASE_ADDRESS, &s->sram2);

    armv7m = DEVICE(&s->armv7m);
    qdev_prop_set_uint32(armv7m, "num-irq", 240);
    //qdev_prop_set_uint8(armv7m, "num-prio-bits", 4);
    qdev_prop_set_string(armv7m, "cpu-type", ARM_CPU_TYPE_NAME("cortex-m7"));
    qdev_prop_set_bit(armv7m, "enable-bitband", true);
    qdev_connect_clock_in(armv7m, "cpuclk", s->sysclk);
    qdev_connect_clock_in(armv7m, "refclk", s->refclk);
    object_property_set_link(OBJECT(&s->armv7m), "memory",
                             OBJECT(get_system_memory()), &error_abort);
    
    // Set vtor address to specify the position of the IVT
    qdev_prop_set_uint32(armv7m, "init-svtor", 0x00400000);
    qdev_prop_set_uint32(armv7m, "init-nsvtor", 0x00400000);

    if (!sysbus_realize(SYS_BUS_DEVICE(&s->armv7m), errp)) {
        return;
    }

    /* System configuration controller */
    dev = DEVICE(&s->syscfg);
    if (!sysbus_realize(SYS_BUS_DEVICE(&s->syscfg), errp)) {
        return;
    }
    busdev = SYS_BUS_DEVICE(dev);
    sysbus_mmio_map(busdev, 0, 0x402AC000);

    /* Attach UART (uses UART registers) and UART controllers */
    for (i = 0; i < STM_NUM_UARTS; i++) {
        dev = DEVICE(&(s->uart[i]));
        qdev_prop_set_chr(dev, "chardev", serial_hd(i));
        if (!sysbus_realize(SYS_BUS_DEVICE(&s->uart[i]), errp)) {
            return;
        }
        busdev = SYS_BUS_DEVICE(dev);
        sysbus_mmio_map(busdev, 0, uart_addr[i]);
        sysbus_connect_irq(busdev, 0, qdev_get_gpio_in(armv7m, uart_irq[i]));
    }

    // Attach CAN
    dev = DEVICE(&(s->can));
    //qdev_prop_set_chr(dev, "chardev", serial_hd(i));
    if (!sysbus_realize(SYS_BUS_DEVICE(&s->can), errp)) {
        return;
    }
    busdev = SYS_BUS_DEVICE(dev);
    sysbus_mmio_map(busdev, 0, can_addr);
    sysbus_connect_irq(busdev, 0, qdev_get_gpio_in(armv7m, can_irq));
}

static void s32k358_soc_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k358_soc_realize;
    /* No vmstate or reset required: device has no internal state */
}

static const TypeInfo s32k358_soc_info = {
    .name          = TYPE_S32K358_SOC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K358State),
    .instance_init = s32k358_soc_initfn,
    .class_init    = s32k358_soc_class_init,
};

static void s32k358_soc_types(void)
{
    type_register_static(&s32k358_soc_info);
}

type_init(s32k358_soc_types)
