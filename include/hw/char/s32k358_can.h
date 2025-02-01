//
// S32K358 CAN
//

#ifndef HW_S32K358_CAN_H
#define HW_S32K358_CAN_H

#include "hw/sysbus.h"
#include "chardev/char-fe.h"
#include "qom/object.h"


#define TYPE_S32K358_CAN "s32k358-can"

#define S32K358_CAN(obj) \
    OBJECT_CHECK(S32K358CanState, (obj), TYPE_S32K358_CAN)

typedef struct {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    /* NEW CAN*/
    uint32_t CAN_MCR;           // MCR Register Offset
    uint32_t CAN_CTRL1;         // CTRL1 Register Offset
    uint32_t CAN_TIMER;         // TIMER Register Offset
    uint32_t RESERVED_0;        // Reserved (Padding)
    uint32_t CAN_RXMGMASK;      // RXMGMASK Register Offset
    uint32_t CAN_RX14MASK;      // RX14MASK Register Offset
    uint32_t CAN_RX15MASK;      // RX15MASK Register Offset
    uint32_t CAN_ECR;           // ECR Register Offset
    uint32_t ESR1;              // ESR1 Register Offset
    uint32_t IMASK2;            // IMASK2 Register Offset
    uint32_t IMASK1;            // IMASK1 Register Offset
    uint32_t IFLAG2;            // IFLAG2 Register Offset
    uint32_t IFLAG1;            // IFLAG1 Register Address
    uint32_t CTRL2;             // CTRL2 Register Offset
    uint32_t ESR2;              // ESR2 Register Offset
    uint32_t RESERVED_1;        // Reserved (Padding)
    uint32_t CRCR;              // CRCR Register Offset
    uint32_t RXFGMASK;          // RXFGMASK Register Offset
    uint32_t RXFIR;             // RXFIR Register Offset
    uint32_t CBT;               // CBT Register Offset
    uint32_t IMASK3;            // IMASK3 Register Offset
    uint32_t RESERVED_3;        // Reserved (Padding)
    uint32_t IFLAG3;            // IFLAG3 Register Offset
    uint32_t ET;                // ET Register Offset
    uint32_t FLTCONF_IE;        // FLTCONF_IE Register Offset

    uint32_t RXIMR[512];        // RXIMR Base Offset
    uint32_t MECR;              // MECR Base Offset
    uint32_t ERRIAR;            // ERRIAR Base Offset
    uint32_t ERRIDPR;           // ERRIDPR Base Offset
    uint32_t ERRIPPR;           // ERRIPPR Base Offset (Error Injection Parity Pattern)
    uint32_t RERRAR;            // RERRAR Base Offset (Error Report Address)
    uint32_t RERRDR;            // RERRDR Base Offset (Error Report Data)
    uint32_t RERRSYNR;          // RERRSYNR Base Offset (Error Report Syndrome)
    uint32_t ERRSR;             // ERRSR Base Offset (Error Status Register)
    
    
    uint32_t EPRS;              // EPRS Base Offset (Enhanced CAN Bit Timing Prescalers)
    uint32_t ENCBT;             // ENCBT Base Offset (Enhanced Nominal CAN Bit Timing)
    uint32_t EDCBT;             // EDCBT Base Offset (Enhanced Data Phase CAN Bit Timing)
    uint32_t ETDC;              // ETDC Base Offset (Enhanced Transceiver Delay Compensation)
    
    uint32_t FDCTRL;            // FDCTRL Base Offset (CAN FD Control)
    uint32_t FDCBT;             // FDCBT Base Address (CAN FD Bit Timing)
    uint32_t FDCRC;             // FDCRC Base Address (CAN FD CRC)
    uint32_t ERFCR;             // ERFCR Base Address (Error Frame Control Register)
    uint32_t ERFIER;            // ERFIER Base Address (Error Frame Interrupt Enable Register)
    uint32_t ERFSR;             // ERFSR Base Address (Error Frame Status Register)


    CharBackend chr;
    qemu_irq irq;
} S32K358CanState;
#endif /* HW_S32K358_CAN_H */
