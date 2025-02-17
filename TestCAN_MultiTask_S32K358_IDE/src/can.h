#ifndef __CAN_H__
#define __CAN_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAN0_ADDRESS                        ( 0x40304000UL )
#define CAN0_MCR							( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x00 ) ) ) )
#define CAN0_IMASK1							( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x28 ) ) ) )
#define CAN0_IFLAG1                       	( *( ( ( volatile uint32_t * ) ( CAN0_ADDRESS + 0x30 ) ) ) )
#define CAN0_DATA                           ( ( ( uint8_t * ) ( CAN0_ADDRESS + 0x80 ) ) )

typedef struct {
	uint16_t can_id;
    uint8_t can_dlc;
	uint8_t data[64];
} frame_t;

void CAN_init(void);
int CAN_write(frame_t *frame);
int CAN_read(frame_t *frame);
int frame2buff( const frame_t *frame, uint8_t *buff);
void buff2frame(const uint8_t *buff, frame_t *frame);
int can_find_full_buffer(uint8_t* can_addr);
int can_find_empty_buffer(uint8_t* can_addr);

#endif // __CAN_H__
