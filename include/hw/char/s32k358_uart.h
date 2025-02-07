/*
 * S32K358 UART
 */

#ifndef HW_S32K358_UART_H
#define HW_S32K358_UART_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"


#define TYPE_S32K358_UART "s32k358-uart"

#define S32K358_UART(obj) \
    OBJECT_CHECK(S32K358UartState, (obj), TYPE_S32K358_UART)

typedef struct {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    /* NEW UART*/
    uint32_t uart_verid;
    uint32_t uart_param;
    uint32_t uart_global;
    uint32_t uart_pincfg;

    uint32_t uart_baud;
    uint32_t uart_stat;
    uint32_t uart_ctrl;
    uint32_t uart_data;

    uint32_t uart_match;
    uint32_t uart_modir;
    uint32_t uart_fifo;
    uint32_t uart_water;
    uint32_t uart_dataro;
    uint32_t uart_mcr;
    uint32_t uart_msr;
    uint32_t uart_reir;
    uint32_t uart_teir;
    uint32_t uart_hdcr;
    uint32_t uart_tocr;
    uint32_t uart_tosr;

    uint32_t uart_timeout0;
    uint32_t uart_timeout1;
    uint32_t uart_timeout2;
    uint32_t uart_timeout3;

    uint32_t uart_tcbr[128];
    uint32_t uart_tdbr[192];

    CharBackend chr;
    qemu_irq irq;
} S32K358UartState;
#endif /* HW_S32K358_UART_H */
