#include "can.h"

int CAN_read(void) {
    int data = 0;
    if (IFLAG1_OFFSET & (1 << 2)){
        data = CAN0_DATA;
        IFLAG1_OFFSET &= ~(1 << 2);
    }
    return data;
}

void CAN_printf(frame_t *frame) {
    int i = 0;
    while(frame->payload[i] != 0x00) {
        CAN0_DATA = (unsigned int)(frame->payload[i]);
        i++;
    }

    //Compact way to send both id and dlc to be set inside the frame
    int combined_value = ((uint32_t)(frame->can_dlc) << 16) | (frame->ID);
    CAN_MCR_OFFSET = (unsigned int)combined_value;
}

/*
Generato per un possibile lancio di init

FLEXCAN->mcr |= (1 << 30); // Disabilita il modulo (MDIS = 1)
FLEXCAN->mcr |= (1 << 28); // Freeze Mode
FLEXCAN->mcr |= (1 << 27); // Halt Mode

FLEXCAN->ctrl1 = (5 << 24) | (3 << 19) | (2 << 16); // Configura baud rate 500kbps

FLEXCAN->rxmgmask = 0x00000000; // Riceve tutti i messaggi

FLEXCAN->mcr &= ~(1 << 30); // Abilita FlexCAN
FLEXCAN->mcr &= ~(1 << 28); // Esce da Freeze Mode
*/