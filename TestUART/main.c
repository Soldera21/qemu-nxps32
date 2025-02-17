#include "uart.h"
#include <stdio.h>

int main(void){
    UART_init();

	UART_printf("Printf test in UART0\n");

	/*UART_printf("Test write between UART 1 and 2\n");
	UART1_DATA = 'a';
	while(!(UART2_STATE & (1 << 21)));
    char c = UART2_DATA;
	char r[60];
	snprintf(r, sizeof(r), "Received from uart1 char: %c\n", c);
    UART_printf(r);*/

	UART_printf("Try to write something:\n");
	char s[30];
	UART_scanf(s);
	char msg[60];
	snprintf(msg, sizeof(msg), "Received char: %s\n", s);
    UART_printf(msg);

	return 0;
}
