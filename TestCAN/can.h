#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>
#include <stdlib.h>

#define CAN0_ADDRESS                        ( 0x40304000UL )
#define CAN0_DATA                           ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x80 ) ) ) )
#define CAN_MCR_OFFSET                      ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x00 ) ) ) )
#define IFLAG1_OFFSET                       ( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x30 ) ) ) )

typedef struct {
	uint16_t ID;
    uint8_t can_dlc;
    uint8_t flags;
	uint8_t payload[64];
} frame_t;

void CAN_printf(frame_t *frame);
int CAN_read(void);

#endif // __CAN_H__
