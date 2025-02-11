#include "uart.h"
#include "can.h"
#include <stdio.h>

int main(void){
    int data = 0;
    char msg[25];
    UART_init();

	UART_printf("UART Test\n");

	frame_t frame_to_send;
    frame_to_send.ID=1234;
    frame_to_send.payload[0]=10;
    frame_to_send.payload[1]=12;
    frame_to_send.payload[2]=14;
    frame_to_send.payload[3]=16;
    frame_to_send.can_dlc=4;

    CAN_printf(&frame_to_send);

    data = CAN_read();
    snprintf(msg, sizeof(msg), "Received from CAN: %d\n", data);
    UART_printf(msg);

    data = CAN_read();
    snprintf(msg, sizeof(msg), "Received from CAN: %d\n", data);
    UART_printf(msg);

    data = CAN_read();
    snprintf(msg, sizeof(msg), "Received from CAN: %d\n", data);
    UART_printf(msg);

    data = CAN_read();
    snprintf(msg, sizeof(msg), "Received from CAN: %d\n", data);
    UART_printf(msg);

	return 0;
}

