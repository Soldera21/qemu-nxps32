//
// S32K358 UART
//

#ifndef HW_S32K358_UART_H
#define HW_S32K358_UART_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"

#define UART_BAUD 0x10
#define UART_STAT 0x14
#define UART_CTRL 0x18
#define UART_DATA 0x1C


#define UART_STAT_RAF       (1 << 24) // Receiver Active Flag
#define UART_STAT_TDRE      (1 << 23) // Indicate that the register of transmission is empty. (we can transmit again)
#define UART_STAT_TC        (1 << 22) // Transmission Complete Flag
#define UART_STAT_RDRF      (1 << 21) // Receive Data Register Full Flag

#define UART_CTRL_UE        (1 << 13) // UART enabled
#define UART_CTRL_RE        (1 << 18) // Receiver Enable


#define TYPE_S32K358_UART "s32k358-uart"
OBJECT_DECLARE_SIMPLE_TYPE(S32K358UartState, S32K358_UART)

struct S32K358UartState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    /* NEW UART*/
    uint32_t uart_stat;
    uint32_t uart_data;
    uint32_t uart_ctrl;
    uint32_t uart_baud;

    CharBackend chr;
    qemu_irq irq;
};
#endif /* HW_S32K358_UART_H */
