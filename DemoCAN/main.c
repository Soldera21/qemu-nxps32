#include "uart.h"
#include <stdlib.h>
#include <stdio.h>

#define CAN0_ADDRESS                        ( 0x40304000UL )
#define CAN0_DATA                           ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x80 ) ) ) )
#define CAN_MCR_OFFSET                      ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x00 ) ) ) )
#define IFLAG1_OFFSET                       ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x30 ) ) ) )

typedef struct
{
	uint16_t ID;
    uint8_t can_dlc;
    uint8_t flags;
	uint8_t payload[64];
} frame_t;


void CAN_printf(frame_t *frame);
void CAN_read();

int main(void){

    UART_init();

	UART_printf("Yeooo\n");

	UART_printf("Other test\n");

	frame_t frame_to_send;
    frame_to_send.ID=1234;
    frame_to_send.payload[0]=10;
    frame_to_send.payload[1]=12;
    frame_to_send.payload[2]=14;
    frame_to_send.payload[3]=16;
    frame_to_send.can_dlc=4;

    CAN_printf(&frame_to_send);

    CAN_read();
    CAN_read();


    /*

    Generato da chatgpt per un possibile lancio di init

    FLEXCAN->mcr |= (1 << 30); // Disabilita il modulo (MDIS = 1)
    FLEXCAN->mcr |= (1 << 28); // Freeze Mode
    FLEXCAN->mcr |= (1 << 27); // Halt Mode

    FLEXCAN->ctrl1 = (5 << 24) | (3 << 19) | (2 << 16); // Configura baud rate 500kbps

    FLEXCAN->rxmgmask = 0x00000000; // Riceve tutti i messaggi
    
    FLEXCAN->mcr &= ~(1 << 30); // Abilita FlexCAN
    FLEXCAN->mcr &= ~(1 << 28); // Esce da Freeze Mode
    */
	return 0;
}

void CAN_read(){

    if (IFLAG1_OFFSET & (1 << 2)){
        int data=0;
        data=CAN0_DATA;

        IFLAG1_OFFSET &= ~(1 << 2);
    }

}

void CAN_printf(frame_t *frame) {

    int i=0;
    
    while(frame->payload[i] != 0x00) {
        CAN0_DATA = (unsigned int)(frame->payload[i]);
        
        i++;

    }

    //Compact way to send both id and dlc to be set inside the frame
    
    int combined_value = ((uint32_t)(frame->can_dlc) << 16) | (frame->ID);

    CAN_MCR_OFFSET=(unsigned int)combined_value;

}

