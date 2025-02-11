/* Including necessary configuration files. */
#include "uart.h"

/**
* @brief        Main function of the example
* @details      Initializes the used drivers
*/
int main(void) {
	UART_init();
    UART_printf("Hello from main\n");

    return 0;
}

