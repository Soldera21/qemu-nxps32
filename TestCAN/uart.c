#include "uart.h"

void UART_init(void) {
    /* SET BAUD RATE */
    UART0_BAUDDIV = 16;

    /* ENABLE UART TRANSMITTER */
    UART0_CTRL |= (1 << 19);

    /* ENABLE UART RECEIVER */
    UART0_CTRL |= (1 << 18);

    /* EXAMPLE TO ENABLE PARITY */
    UART0_CTRL |= (1 << 1);
}


void UART_printf(const char *s) {
    while(*s != '\0') {
        UART0_DATA = (unsigned int)(*s);
        s++;
    }
}

// Simulate parity error (16th bit of status register) for FreeRTOS simulation
// Simulate also parity error in data register (14th bit)