/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

/*
 * S32K358 SYSCFG
 */

#ifndef HW_S32K358_SYSCFG_H
#define HW_S32K358_SYSCFG_H

#include "hw/sysbus.h"
#include "qom/object.h"

#define SYSCFG_MEMRMP  0x00
#define SYSCFG_PMC     0x04
#define SYSCFG_EXTICR1 0x08
#define SYSCFG_EXTICR2 0x0C
#define SYSCFG_EXTICR3 0x10
#define SYSCFG_EXTICR4 0x14
#define SYSCFG_CMPCR   0x20

#define TYPE_S32K358_SYSCFG "s32k358-syscfg"
OBJECT_DECLARE_SIMPLE_TYPE(S32K358SyscfgState, S32K358_SYSCFG)

struct S32K358SyscfgState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    uint32_t syscfg_memrmp;
    uint32_t syscfg_pmc;
    uint32_t syscfg_exticr1;
    uint32_t syscfg_exticr2;
    uint32_t syscfg_exticr3;
    uint32_t syscfg_exticr4;
    uint32_t syscfg_cmpcr;
};

#endif /* HW_S32K358_SYSCFG_H */
