/*
 * S32K358 UART
 */

#ifndef HW_S32K358_UART_H
#define HW_S32K358_UART_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"

#define UART_SR   0x00
#define UART_DR   0x04
#define UART_BRR  0x08
#define UART_CR1  0x0C
#define UART_CR2  0x10
#define UART_CR3  0x14
#define UART_GTPR 0x18

/*
 * NB: The reset value mentioned in "24.6.1 Status register" seems bogus.
 * Looking at "Table 98 UART register map and reset values", it seems it
 * should be 0xc0, and that's how real hardware behaves.
 */
#define UART_SR_RESET (UART_SR_TXE | UART_SR_TC)

#define UART_SR_TXE  (1 << 7)
#define UART_SR_TC   (1 << 6)
#define UART_SR_RXNE (1 << 5)

#define UART_CR1_UE     (1 << 13)
#define UART_CR1_TXEIE  (1 << 7)
#define UART_CR1_TCEIE  (1 << 6)
#define UART_CR1_RXNEIE (1 << 5)
#define UART_CR1_TE     (1 << 3)
#define UART_CR1_RE     (1 << 2)

#define TYPE_S32K358_UART "s32k358-uart"
OBJECT_DECLARE_SIMPLE_TYPE(S32K358UartState, S32K358_UART)

struct S32K358UartState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    uint32_t uart_sr;
    uint32_t uart_dr;
    uint32_t uart_brr;
    uint32_t uart_cr1;
    uint32_t uart_cr2;
    uint32_t uart_cr3;
    uint32_t uart_gtpr;

    CharBackend chr;
    qemu_irq irq;
};
#endif /* HW_S32K358_UART_H */
