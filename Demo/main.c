#include "uart.h"
#include <stdlib.h>
#include <stdio.h>


int main(void){

    UART_init();

	UART_printf("Yeooo\n");

	UART_printf("Other test\n");

	return 0;
}
