/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

//
// S32K358 CAN
//

#ifndef HW_S32K358_CAN_H
#define HW_S32K358_CAN_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"
#include "net/can_emu.h"

#define TYPE_S32K358_CAN "s32k358-can"
#define BUFF_SIZE 72*21+16-128

#define S32K358_CAN(obj) \
    OBJECT_CHECK(S32K358CanState, (obj), TYPE_S32K358_CAN)

typedef struct {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    uint8_t can_data[BUFF_SIZE];

    uint32_t mcr;         // MCR Register Offset  
    uint32_t ctrl1;       // CTRL1 Register Offset  
    uint32_t timer;       // TIMER Register Offset  
    uint32_t rxmgmask;    // RXMGMASK Register Offset  
    uint32_t rx14mask;    // RX14MASK Register Offset  
    uint32_t rx15mask;    // RX15MASK Register Offset  
    uint32_t ecr;         // ECR Register Offset  
    uint32_t esr1;              // ESR1 Register Offset
    uint32_t imask2;            // IMASK2 Register Offset
    uint32_t imask1;            // IMASK1 Register Offset
    uint32_t iflag2;            // IFLAG2 Register Offset
    uint32_t iflag1;            // IFLAG1 Register Address
    uint32_t ctrl2;             // CTRL2 Register Offset
    uint32_t esr2;              // ESR2 Register Offset
    uint32_t crcr;              // CRCR Register Offset
    uint32_t rxfgmask;          // RXFGMASK Register Offset
    uint32_t rxfir;             // RXFIR Register Offset
    uint32_t cbt;               // CBT Register Offset
    uint32_t imask3;            // IMASK3 Register Offset
    uint32_t reserved_3;        // Reserved (Padding)
    uint32_t iflag3;            // IFLAG3 Register Offset
    uint32_t et;                // ET Register Offset
    uint32_t fltconf_ie;        // FLTCONF_IE Register Offset

    uint32_t rximr[512];        // RXIMR Base Offset
    uint32_t mecr;              // MECR Base Offset
    uint32_t erriar;            // ERRIAR Base Offset
    uint32_t erridpr;           // ERRIDPR Base Offset
    uint32_t errippr;           // ERRIPPR Base Offset (Error Injection Parity Pattern)
    uint32_t rerrar;            // RERRAR Base Offset (Error Report Address)
    uint32_t rerrdr;            // RERRDR Base Offset (Error Report Data)
    uint32_t rerrsynr;          // RERRSYNR Base Offset (Error Report Syndrome)
    uint32_t errsr;             // ERRSR Base Offset (Error Status Register)

    uint32_t eprs;              // EPRS Base Offset (Enhanced CAN Bit Timing Prescalers)
    uint32_t encbt;             // ENCBT Base Offset (Enhanced Nominal CAN Bit Timing)
    uint32_t edcbt;             // EDCBT Base Offset (Enhanced Data Phase CAN Bit Timing)
    uint32_t etdc;              // ETDC Base Offset (Enhanced Transceiver Delay Compensation)

    uint32_t fdctrl;            // FDCTRL Base Offset (CAN FD Control)
    uint32_t fdcbt;             // FDCBT Base Address (CAN FD Bit Timing)
    uint32_t fdcrc;             // FDCRC Base Address (CAN FD CRC)
    uint32_t erfcr;             // ERFCR Base Address (Error Frame Control Register)
    uint32_t erfier;            // ERFIER Base Address (Error Frame Interrupt Enable Register)
    uint32_t erfsr;             // ERFSR Base Address (Error Frame Status Register)

    CharBackend chr;
    qemu_irq irq;
    CanBusClientState bus_client;
    CanBusState *canbus;
} S32K358CanState;

bool s32k358_can_can_receive(CanBusClientState *client);
ssize_t s32k358_can_receive(CanBusClientState *client, const qemu_can_frame *frame, size_t frames_cnt);

#endif /* HW_S32K358_CAN_H */
