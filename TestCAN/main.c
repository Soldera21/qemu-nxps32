#include "uart.h"
#include "can.h"
#include <stdio.h>

int main(void){
    char msg[30];
    UART_init();
    CAN_init();

	UART_printf("UART Test\n");

	frame_t frame;
    frame.can_id=1234;
    frame.data[0]=10;
    frame.data[1]=12;
    frame.data[2]=14;
    frame.data[3]=16;
    frame.can_dlc=4;

    UART_printf("Writing to CAN...\n");
    CAN_write(&frame);

    frame.can_id=1235;
    frame.data[0]=10;
    frame.data[1]=12;
    frame.data[2]=14;
    frame.data[3]=16;
    frame.can_dlc=4;

    CAN_write(&frame);

    frame_t frame2;
    CAN_read(&frame2);

    snprintf(msg, sizeof(msg), "Received ID from CAN: %u\n", frame2.can_id);
    UART_printf(msg);
    snprintf(msg, sizeof(msg), "Received DLC from CAN: %u\n", frame2.can_dlc);
    UART_printf(msg);
    for(int i = 0; i < frame2.can_dlc; i++){
        snprintf(msg, sizeof(msg), "Received from CAN: %u\n", frame2.data[i]);
        UART_printf(msg);
    }

    CAN_read(&frame2);

    snprintf(msg, sizeof(msg), "Received ID from CAN: %u\n", frame2.can_id);
    UART_printf(msg);
    snprintf(msg, sizeof(msg), "Received DLC from CAN: %u\n", frame2.can_dlc);
    UART_printf(msg);
    for(int i = 0; i < frame2.can_dlc; i++){
        snprintf(msg, sizeof(msg), "Received from CAN: %u\n", frame2.data[i]);
        UART_printf(msg);
    }

	return 0;
}