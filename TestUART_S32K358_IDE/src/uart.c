#include "uart.h"

void UART_init( void ) {
    UART0_BAUDDIV = 16;
    UART0_CTRL |= (1 << 18);
    UART0_CTRL |= (1 << 19);
}

void UART_printf(const char *s) {
    while(*s != '\0') {
        UART0_DATA = (unsigned int)(*s);
        s++;
    }
}

void UART_scanf(char *s) {
    do {
        while(!(UART0_STATE & (1 << 21)));
        *s = (unsigned int)UART0_DATA;
        char msg[2];
        snprintf(msg, sizeof(msg), "%c", *s);
        UART_printf(msg);
        s++;
    } while(*(s-1) != '\0' && *(s-1) != '\n' && *(s-1) != '\r');
    *(s-1) = '\0';
}

