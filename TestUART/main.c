#include "uart.h"

int main(void){

    UART_init();

	UART_printf("Printf test in UART0\n");

	return 0;
}
