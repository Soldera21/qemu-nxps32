#include "can.h"

void CAN_init(void) {
    CAN0_MCR &= ~(1 << 30); // Disable freeze
    CAN0_MCR &= ~(1 << 31); // Enable interface
}

int CAN_read(frame_t *frame) {
    uint8_t buff[72];

    int base = can_find_full_buffer(CAN0_DATA);
    if(base < 0){
    	frame->can_id = 0;
    	frame->can_dlc = 0;
        return -1;
    }
    uint8_t dlc = *(CAN0_DATA + base + 2) & 0xF;

    for(uint8_t i = 0; i < dlc+8; i++) {
        buff[i] = *(CAN0_DATA + base + i);
    }

    buff2frame(buff, frame);

    CAN0_DATA[base+3] = (CAN0_DATA[base+3] & 0xF0) | (0x4 & 0x0F); // mark the buffer EMPTY because full read
    CAN0_IMASK1 &= ~(1 << (base/72));
    CAN0_IFLAG1 &= ~(1 << (base/72));

    return 1;
}

int CAN_write(frame_t *frame) {
    uint8_t buff[72];
    
    frame2buff(frame, buff);
    buff[3] = (buff[3] & 0xF0) | (0x8 & 0x0F);

    int base = can_find_empty_buffer(CAN0_DATA);
    if(base < 0){
        return -1;
    }
    CAN0_IFLAG1 &= ~(1 << (base/72));

    for(uint8_t i = 0; i < frame->can_dlc+8; i++) {
        *(CAN0_DATA + base + i) = buff[i];
    }
    CAN0_DATA[base+3] = (CAN0_DATA[base+3] & 0xF0) | (0xC & 0x0F);

    CAN0_IFLAG1 |= (1 << (base/72)); // --> for successful action in corresponding buffer
    CAN0_DATA[base+3] = (CAN0_DATA[base+3] & 0xF0) | (0x8 & 0x0F); // mark the buffer INACTIVE
<<<<<<< HEAD

    return 1;
}

int frame2buff( const frame_t *frame, uint8_t *buff) {
    uint8_t len = frame->can_dlc;
    buff[2] = (buff[2] & 0xF0) | (len & 0x0F);
    buff[6] = (frame->can_id & 0x3F) << 2;
    buff[7] = (frame->can_id >> 6) & 0x1F;

    uint8_t i;
    for (i = 0; i < frame->can_dlc; i++) {
        buff[8 + i] = frame->data[i];
    }
    for (; i < 64; i++) {
        buff[8 + i] = 0;
    }

    return len + 8;
}

void buff2frame(const uint8_t *buff, frame_t *frame) {
    frame->can_id = ((buff[6] >> 2) & 0x3F) | ((buff[7] & 0x1F) << 6);
    frame->can_dlc = buff[2] & 0xF;

    uint8_t i = 0;
    for (i = 0; i < frame->can_dlc; i++) {
        frame->data[i] = buff[8 + i];
    }
    for (; i < 64; i++) {
        frame->data[i] = 0;
    }
}

int can_find_full_buffer(uint8_t* can_addr) {
    bool full = false;
    int cont = 0;
    uint8_t n = 0;
    while(!full && n < 21) {
        if( ((CAN0_IMASK1 >> n) & 1) == 1 && (can_addr[cont+3] & 0xF) == 0x2 ) {
            full = true;
        }
        if(!full){
            cont += 72;
            if(cont == 72*7) {
                cont += 8;
            }
            if(cont == 72*14+8) {
                cont += 8;
            }
            n++;
        }
    }
    if(n == 21) {
        cont = -1;
    }
    return cont;
}

int can_find_empty_buffer(uint8_t* can_addr) {
    bool free = false;
    uint16_t cont = 0;
    uint8_t n = 0;
    while(!free && n < 21) {
        if( ( ((CAN0_IFLAG1 >> n) & 1) == 0 && (can_addr[cont+3] & 0xF) == 0x4 ) ||
            ( ((CAN0_IFLAG1 >> n) & 1) == 1 && (can_addr[cont+3] & 0xF) == 0x8 ) ) {
            free = true;
        }
        if(!free){
            cont += 72;
            if(cont == 72*7) {
                cont += 8;
            }
            if(cont == 72*14+8) {
                cont += 8;
            }
            n++;
        }
    }
    if(n == 21) {
        cont = -1;
    }
    return cont;
}

=======

    return 1;
}

int frame2buff( const frame_t *frame, uint8_t *buff) {
    uint8_t len = frame->can_dlc;
    buff[2] = (buff[2] & 0xF0) | (len & 0x0F);
    buff[6] = (frame->can_id & 0x3F) << 2;
    buff[7] = (frame->can_id >> 6) & 0x1F;

    uint8_t i;
    for (i = 0; i < frame->can_dlc; i++) {
        buff[8 + i] = frame->data[i];
    }
    for (; i < 64; i++) {
        buff[8 + i] = 0;
    }

    return len + 8;
}

void buff2frame(const uint8_t *buff, frame_t *frame) {
    frame->can_id = ((buff[6] >> 2) & 0x3F) | ((buff[7] & 0x1F) << 6);
    frame->can_dlc = buff[2] & 0xF;

    uint8_t i = 0;
    for (i = 0; i < frame->can_dlc; i++) {
        frame->data[i] = buff[8 + i];
    }
    for (; i < 64; i++) {
        frame->data[i] = 0;
    }
}

int can_find_full_buffer(uint8_t* can_addr) {
    bool full = false;
    int cont = 0;
    uint8_t n = 0;
    while(!full && n < 21) {
        if( ((CAN0_IMASK1 >> n) & 1) == 1 && (can_addr[cont+3] & 0xF) == 0x2 ) {
            full = true;
        }
        if(!full){
            cont += 72;
            if(cont == 72*7) {
                cont += 8;
            }
            if(cont == 72*14+8) {
                cont += 8;
            }
            n++;
        }
    }
    if(n == 21) {
        cont = -1;
    }
    return cont;
}

int can_find_empty_buffer(uint8_t* can_addr) {
    bool free = false;
    uint16_t cont = 0;
    uint8_t n = 0;
    while(!free && n < 21) {
        if( ( ((CAN0_IFLAG1 >> n) & 1) == 0 && (can_addr[cont+3] & 0xF) == 0x4 ) ||
            ( ((CAN0_IFLAG1 >> n) & 1) == 1 && (can_addr[cont+3] & 0xF) == 0x8 ) ) {
            free = true;
        }
        if(!free){
            cont += 72;
            if(cont == 72*7) {
                cont += 8;
            }
            if(cont == 72*14+8) {
                cont += 8;
            }
            n++;
        }
    }
    if(n == 21) {
        cont = -1;
    }
    return cont;
}
>>>>>>> gitlab/main
