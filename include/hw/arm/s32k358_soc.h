/*
 * S32K358 SoC
 */

#ifndef HW_ARM_S32K358_SOC_H
#define HW_ARM_S32K358_SOC_H

#include "hw/misc/s32k358_syscfg.h"
#include "hw/char/s32k358_uart.h"
#include "hw/or-irq.h"
#include "hw/arm/armv7m.h"
#include "hw/clock.h"
#include "qom/object.h"

#define TYPE_S32K358_SOC "s32k358-soc"
OBJECT_DECLARE_SIMPLE_TYPE(S32K358State, S32K358_SOC)

#define STM_NUM_UARTS 16

#define FLASH_BASE_ADDRESS 0x00400000
#define FLASH_SIZE (8192 * 1024)
#define SRAM_BASE_ADDRESS 0x20400000
#define SRAM_SIZE (768 * 1024)

struct S32K358State {
    SysBusDevice parent_obj;

    ARMv7MState armv7m;

    S32K358SyscfgState syscfg;
    S32K358UartState uart[STM_NUM_UARTS];

    OrIRQState *adc_irqs;

    MemoryRegion sram;
    MemoryRegion flash;
    MemoryRegion flash_alias;

    Clock *sysclk;
    Clock *refclk;
};

#endif
