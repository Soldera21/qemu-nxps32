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

/**
 * 0x00000000    0x00007FFF  32768   ITCM
 * 0x20000000    0x2000FFFF  65536   DTCM
 * 0x00400000    0x00BFFFFF  8388608 Program Flash
 * 0x10000000    0x1001FFFF  131072  Data Flash
 * 0x20400000    0x2043FFFF  262144  SRAM_0
 * 0x20440000    0x2047FFFF  262144  SRAM_1
 * 0x20480000    0x204BFFFF  262144  SRAM_2
 */

#define ITCM_BASE_ADDRESS 0x00000000
#define ITCM_SIZE (32768)
#define DTCM_BASE_ADDRESS 0x20000000
#define DTCM_SIZE (65536)
#define PFLASH_BASE_ADDRESS 0x00400000
#define PFLASH_SIZE (8388608)
#define DFLASH_BASE_ADDRESS 0x10000000
#define DFLASH_SIZE (131072)
#define SRAM0_BASE_ADDRESS 0x20400000
#define SRAM0_SIZE (262144)
#define SRAM1_BASE_ADDRESS 0x20440000
#define SRAM1_SIZE (262144)
#define SRAM2_BASE_ADDRESS 0x20480000
#define SRAM2_SIZE (262144)

struct S32K358State {
    SysBusDevice parent_obj;

    ARMv7MState armv7m;

    S32K358SyscfgState syscfg;
    S32K358UartState uart[STM_NUM_UARTS];

    OrIRQState *adc_irqs;

    MemoryRegion itcm;
    MemoryRegion dtcm;
    MemoryRegion p_flash;
    MemoryRegion p_flash_alias;
    MemoryRegion d_flash;
    MemoryRegion d_flash_alias;
    MemoryRegion sram0;
    MemoryRegion sram1;
    MemoryRegion sram2;

    Clock *sysclk;
    Clock *refclk;
};

#endif
