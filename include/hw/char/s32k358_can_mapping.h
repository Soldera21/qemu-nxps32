// CAN Register Offsets
#define CAN_MCR_OFFSET        0x00   // MCR Register Offset
#define CAN_CTRL1_OFFSET      0x04   // CTRL1 Register Offset
#define CAN_TIMER_OFFSET      0x08   // TIMER Register Offset
#define CAN_RXMGMASK_OFFSET   0x10   // RXMGMASK Register Offset
#define CAN_RX14MASK_OFFSET   0x14   // RX14MASK Register Offset
#define CAN_RX15MASK_OFFSET   0x18   // RX15MASK Register Offset
#define CAN_ECR_OFFSET        0x1C   // ECR Register Offset
#define ESR1_OFFSET           0x20   // ESR1 Register Offset
#define IMASK2_OFFSET         0x24   // IMASK2 Register Offset
#define IMASK1_OFFSET         0x28   // IMASK1 Register Offset
#define IFLAG2_OFFSET         0x2C   // IFLAG2 Register Offset
#define IFLAG1_OFFSET         0x30   // IFLAG1 Register Address
#define CTRL2_OFFSET          0x34   // CTRL2 Register Offset
#define ESR2_OFFSET           0x38   // ESR2 Register Offset
#define CRCR_OFFSET           0x44   // CRCR Register Offset
#define RXFGMASK_OFFSET       0x48   // RXFGMASK Register Offset
#define RXFIR_OFFSET          0x4C   // RXFIR Register Offset
#define CBT_OFFSET            0x50   // CBT Register Offset
#define IMASK3_OFFSET         0x6C   // IMASK3 Register Offset
#define IFLAG3_OFFSET         0x74   // IFLAG3 Register Offset
#define ET_OFFSET             0x78   // ET Register Offset
#define FLTCONF_IE_OFFSET     0x7C   // FLTCONF_IE Register Offset

#define RXIMR_BASE_OFFSET     0x880  // RXIMR Base Offset
#define MECR_BASE_OFFSET      0xAE0  // MECR Base Offset
#define ERRIAR_BASE_OFFSET    0xAE4  // ERRIAR Base Offset
#define ERRIDPR_BASE_OFFSET   0xAE8  // ERRIDPR Base Offset
#define ERRIPPR_BASE_OFFSET   0xAEC  // ERRIPPR Base Offset (Error Injection Parity Pattern)
#define RERRAR_BASE_OFFSET    0xAF0  // RERRAR Base Offset (Error Report Address)
#define RERRDR_BASE_OFFSET    0xAF4  // RERRDR Base Offset (Error Report Data)
#define RERRSYNR_BASE_OFFSET  0xAF8  // RERRSYNR Base Offset (Error Report Syndrome)
#define ERRSR_BASE_OFFSET     0xAFC  // ERRSR Base Offset (Error Status Register)

#define EPRS_BASE_OFFSET      0xBF0  // EPRS Base Offset (Enhanced CAN Bit Timing Prescalers)
#define ENCBT_BASE_OFFSET     0xBF4  // ENCBT Base Offset (Enhanced Nominal CAN Bit Timing)
#define EDCBT_BASE_OFFSET     0xBF8  // EDCBT Base Offset (Enhanced Data Phase CAN Bit Timing)
#define ETDC_BASE_OFFSET      0xBFC  // ETDC Base Offset (Enhanced Transceiver Delay Compensation)

#define FDCTRL_BASE_OFFSET    0xC00  // FDCTRL Base Offset (CAN FD Control)
#define FDCBT_BASE_ADDR       0xC04  // FDCBT Base Address (CAN FD Bit Timing)
#define FDCRC_BASE_ADDR       0xC08  // FDCRC Base Address (CAN FD CRC)
#define ERFCR_BASE_ADDR       0xC0C  // ERFCR Base Address (Error Frame Control Register)
#define ERFIER_BASE_ADDR      0xC10  // ERFIER Base Address (Error Frame Interrupt Enable Register)
#define ERFSR_BASE_ADDR       0xC14  // ERFSR Base Address (Error Frame Status Register)

// Time Stamp Register
#define HR_TIME_STAMP_BASE_ADDR 0xC30  // High-Resolution Time Stamp Base Address

// Additional CAN Error Registers
#define ERFFEL_BASE_ADDR      0x3000 // ERFFEL Base Address (Enhanced Error Frame Extension Logic)



// MCR Register Bit Definitions
#define CAN_MCR_MDIS           (1 << 31)  // Module Disable
#define CAN_MCR_FRZ            (1 << 30)  // Freeze Mode
#define CAN_MCR_RFEN           (1 << 29)  // Receive FIFO Enable
#define CAN_MCR_HALT           (1 << 28)  // Halt Mode
#define CAN_MCR_NOTRDY         (1 << 27)  // Not Ready
#define CAN_MCR_SOFTRST        (1 << 25)  // Software Reset
#define CAN_MCR_FRZACK         (1 << 24)  // Freeze Acknowledge
#define CAN_MCR_SUPV           (1 << 23)  // Supervisor Mode
#define CAN_MCR_WRNEN          (1 << 21)  // Warning Interrupt Enable
#define CAN_MCR_LPMACK         (1 << 20)  // Low Power Mode Acknowledge
#define CAN_MCR_SRXDIS         (1 << 17)  // Self-Receive Disable
#define CAN_MCR_IRMQ           (1 << 16)  // Interrupt Request Mask
#define CAN_MCR_DMA            (1 << 15)  // DMA Enable
#define CAN_MCR_LPRIOEN        (1 << 13)  // Low Priority Enable
#define CAN_MCR_AEN            (1 << 12)  // Acceptance Enable
#define CAN_MCR_FDEN           (1 << 11)  // FD Enable
#define CAN_MCR_TPOV           (1 << 10)  // Transmit FIFO Overflow
#define CAN_MCR_IDAM_MASK      (0x3 << 8) // Identifier Acceptance Mask [9:8]
#define CAN_MCR_TPOE           (1 << 7)   // Transmit FIFO Overflow Enable
#define CAN_MCR_MAXMB_MASK     (0x7F << 0) // Max Message Buffers [6:0]

// CTRL1 Register Bit Definitions
#define CAN_CTRL1_PRESDIV_MASK  (0xFF << 24)  // Prescaler Division Factor
#define CAN_CTRL1_RJW_MASK      (0x3 << 22)   // Resync Jump Width
#define CAN_CTRL1_PSEG1_MASK    (0x7 << 19)   // Phase Segment 1
#define CAN_CTRL1_PSEG2_MASK    (0x7 << 16)   // Phase Segment 2
#define CAN_CTRL1_BOFFMSK       (1 << 15)     // Bus Off Interrupt Mask
#define CAN_CTRL1_ERRMSK        (1 << 14)     // Error Interrupt Mask
#define CAN_CTRL1_LPB           (1 << 12)     // Loopback Mode
#define CAN_CTRL1_TWRNMSK       (1 << 11)     // TX Warning Interrupt Mask
#define CAN_CTRL1_RWRNMSK       (1 << 10)     // RX Warning Interrupt Mask
#define CAN_CTRL1_ROM           (1 << 8)      // Restricted Operation Mode
#define CAN_CTRL1_SMP           (1 << 7)      // CAN Bit Sampling
#define CAN_CTRL1_BOFFREC       (1 << 6)      // Bus Off Recovery
#define CAN_CTRL1_TSYN          (1 << 5)      // Timer Sync
#define CAN_CTRL1_LBUF          (1 << 4)      // Lowest Buffer Transmitted First
#define CAN_CTRL1_LOM           (1 << 3)      // Listen-Only Mode
#define CAN_CTRL1_PROPSEG_MASK  (0x7 << 0)    // Propagation Segment [2:0]


// TIMER Register Bit Definitions
// Timer Value
#define CAN_TIMER_TIMER_MASK   (0xFFFF << 0) // [15:0] - Timer content

// RX Message Buffers Global Mask
#define CAN_RXMGMASK_MG_MASK   (0xFFFFFFFF << 0) // [31:0] - Global Mask for RX Message Buffers

// RX Buffer 14 Mask
#define CAN_RX14MASK_RX14M_MASK (0xFFFFFFFF << 0) // [31:0] - RX Buffer 14 Mask Bits

// RX Buffer 15 Mask
#define CAN_RX15MASK_RX15M_MASK (0xFFFFFFFF << 0) // [31:0] - RX Buffer 15 Mask Bits

// Error Counter Register (ECR) Bit Definitions
#define CAN_ECR_RXERRCNT_FAST_MASK  (0xFF << 24)  // RX Error Counter (Fast) [31:24]
#define CAN_ECR_TXERRCNT_FAST_MASK  (0xFF << 16)  // TX Error Counter (Fast) [23:16]
#define CAN_ECR_RXERRCNT_MASK       (0xFF << 8)   // RX Error Counter [15:8]
#define CAN_ECR_TXERRCNT_MASK       (0xFF << 0)   // TX Error Counter [7:0]


// ESR1 Register Field Masks
#define ESR1_FAST_BIT1_ERR_MASK   (1 << 31)   // Fast Bit1 Error Flag
#define ESR1_FAST_BIT0_ERR_MASK   (1 << 30)   // Fast Bit0 Error Flag
#define ESR1_FAST_CRC_ERR_MASK    (1 << 28)   // Fast CRC Error Flag
#define ESR1_FAST_FRM_ERR_MASK    (1 << 27)   // Fast Form Error Flag
#define ESR1_FAST_STF_ERR_MASK    (1 << 26)   // Fast Stuffing Error Flag
#define ESR1_PTA_MASK             (1 << 23)   // Passive to Active State Flag
#define ESR1_ATP_MASK             (1 << 22)   // Active to Passive State Flag
#define ESR1_ERR_OVR_MASK         (1 << 21)   // Error Overrun Flag
#define ESR1_FAST_ERR_INT_MASK    (1 << 20)   // Fast Error Interrupt Flag
#define ESR1_BOFF_DONE_INT_MASK   (1 << 19)   // Bus Off Done Interrupt Flag
#define ESR1_SYNC_MASK            (1 << 18)   // Synchronization Flag
#define ESR1_TX_WARN_INT_MASK     (1 << 17)   // TX Warning Interrupt Flag
#define ESR1_RX_WARN_INT_MASK     (1 << 16)   // RX Warning Interrupt Flag
#define ESR1_BIT1_ERR_MASK        (1 << 15)   // Bit1 Error Flag
#define ESR1_BIT0_ERR_MASK        (1 << 14)   // Bit0 Error Flag
#define ESR1_ACK_ERR_MASK         (1 << 13)   // Acknowledge Error Flag
#define ESR1_CRC_ERR_MASK         (1 << 12)   // CRC Error Flag
#define ESR1_FRM_ERR_MASK         (1 << 11)   // Form Error Flag
#define ESR1_STF_ERR_MASK         (1 << 10)   // Stuffing Error Flag
#define ESR1_TX_WARN_MASK         (1 << 9)    // TX Error Warning Flag
#define ESR1_RX_WARN_MASK         (1 << 8)    // RX Error Warning Flag
#define ESR1_IDLE_MASK            (1 << 7)    // Idle Flag
#define ESR1_TX_MASK              (1 << 6)    // Transmitting Flag
#define ESR1_FLT_CONF_MASK        (0x03 << 4) // Fault Confinement State (2 bits)
#define ESR1_RX_MASK              (1 << 3)    // Receiving Flag
#define ESR1_BOFF_INT_MASK        (1 << 2)    // Bus Off Interrupt Flag
#define ESR1_ERR_INT_MASK         (1 << 1)    // Error Interrupt Flag


// IMASK2 Register Field Masks (Buffer Interrupt Masks for MB63–MB32)
#define IMASK2_BUF63TO32_MASK     (0xFFFFFFFF << 0) // Mask for MB63–MB32 buffer interrupts

// IMASK1 Register Field Masks (Buffer Interrupt Masks for MB31–MB0)
#define IMASK1_BUF31TO0_MASK      (0xFFFFFFFF << 0) // Mask for MB31–MB0 buffer interrupts

// IFLAG2 Register Field Masks (Buffer Interrupt Flags for MB63–MB32)
#define IFLAG2_BUF63TO32_MASK     (0xFFFFFFFF << 0) // Interrupt Flag for MB63–MB32

// Message Buffer Interrupt Flags for CAN_IFLAG1
#define CAN_IFLAG1_BUF31TO8_MASK  (0xFFFFFF << 8)  // Flags for MB31 to MB8
#define CAN_IFLAG1_BUF7_MASK      (1 << 7)     // Interrupt for MB7 or Legacy RX FIFO overflow
#define CAN_IFLAG1_BUF6_MASK      (1 << 6)     // Interrupt for MB6 or Legacy RX FIFO warning
#define CAN_IFLAG1_BUF5_MASK      (1 << 5)     // Interrupt for MB5 or frames available in Legacy RX FIFO
#define CAN_IFLAG1_BUF4TO1I_MASK  (0xF << 1)     // Interrupt for MB4 (reserved when MCR[RFEN]=1)
#define CAN_IFLAG1_BUF0_MASK      (1 << 0)     // Interrupt for MB0 or clear Legacy FIFO

// CTRL2 Register Field Masks
#define CAN_CTRL2_ERRMSK_FAULT_ACTIVE_MASK (1 << 31) // Error Mask for Fault Active State
#define CAN_CTRL2_BOFFDONE_MASK           (1 << 30) // Bus-Off Done Mask for Error State
#define CAN_CTRL2_ECR_WRITE_PROTECT_MASK  (1 << 29) // Enable Error Counter Write Protection
#define CAN_CTRL2_MSG_BUF_WRITE_FREEZE    (1 << 28) // Write Freeze for Message Buffer
#define CAN_CTRL2_RX_FIFO_FILTER_MASK     (0xF << 24) // RX FIFO Filters Number (bits 27-24)
#define CAN_CTRL2_ARB_START_DELAY_MASK    (0x1F << 19) // Transmission Arbitration Start Delay (bits 23-19)
#define CAN_CTRL2_MSG_RAM_POINTER_MASK    (1 << 18) // Message RAM Pointer
#define CAN_CTRL2_RX_FIFO_RESET_MASK      (1 << 17) // Receive FIFO Reset
#define CAN_CTRL2_ADAPTIVE_CAN_ERR_NOTIFY (1 << 16) // Enable Adaptive CAN Error Notification
#define CAN_CTRL2_TIMER_SOURCE_MASK       (1 << 15) // Timer Source Select
#define CAN_CTRL2_PRE_TX_ERROR_CONTROL_EN (1 << 14) // Pre-Transmitting Error Control Enable
#define CAN_CTRL2_BUS_TIMEOUT_EN_MASK     (1 << 13) // Bus Timeout Enable
#define CAN_CTRL2_ISO_CAN_FD_MODE_EN_MASK (1 << 12) // ISO CAN FD Mode Enable
#define CAN_CTRL2_CANFD_ERR_DET_DISABLE_MASK (1 << 11) // Disable CAN FD Error Detection
#define CAN_CTRL2_RX_FIFO_NUM_FILTER_MASK (1 << 10) // Filter Receive FIFO Number
#define CAN_CTRL2_MSG_BUF_TS_START_BASE_MASK (0x03 << 8) // Message Buffer Timing Start Base (bits 9-8)
#define CAN_CTRL2_TSTAMPCAP_MASK          (0x3 << 6) // Timestamp capture point
#define CAN_CTRL2_RETRY_MASK              (0x7 << 2) // Number of retransmission requests

// ESR2 Register Field Masks
#define CAN_ESR2_LPTM_MASK                   (0x7F << 16)  // Lowest Priority TX Message Buffer (bits 22-16)
#define CAN_ESR2_VPS_MASK                    (1 << 14)     // Valid Priority Status (bit 14)
#define CAN_ESR2_IMB_MASK                    (1 << 13)     // Inactive Message Buffer (bit 13)
#define CAN_ESR2_RX_PIN_STATUS_MASK          (1 << 12)     // RX Pin Status (bit 12)

// CRCR Register Field Masks
#define CAN_CRCR_MSG_BUF_CRC_MASK           (0x7F << 16)  // CRC Message Buffer (bits 22-16)
#define CAN_CRCR_TX_CRC_MASK                (0x7FFF << 0)       // Transmitted CRC Value (bits 14-0)

// RX FIFO Global Mask Bits (FGM)
#define RXFGMASK_FGM_MASK                   (0xFFFFFFFF << 0) // Bits 31-0: Mask Bits for the ID Filter Table Elements


// Mask Definitions for Legacy RX FIFO Information
#define RXFIR_IDHIT_MASK      (0x01FF << 0)        // Mask for Identifier Acceptance Filter Hit Indicator (Bits 8-0)

// CAN Bit Timing Configuration
#define CBT_BTF_MASK          (1 << 31)          // Bit 31: Bit Timing Format Enable
#define CBT_EPRESDIV_MASK     (0x3FF << 21)    // Bits 30-21: Extended Prescaler Division Factor
#define CBT_ERJW_MASK         (0x1F << 16)     // Bits 20-16: Extended Resync Jump Width
#define CBT_EPROPSEG_MASK     (0x3F << 10)      // Bits 15-10: Extended Propagation Segment
#define CBT_EPSEG1_MASK       (0x1F << 5)        // Bits 9-5: Extended Phase Segment 1
#define CBT_EPSEG2_MASK       (0x1F << 0)          // Bits 4-0: Extended Phase Segment 2

// Interrupt Mask Definitions for IMASK3 (Buffer MBi Mask for MB95–MB64)
#define IMASK3_BUF95TO64M_MASK    (0xFFFFFFFF << 0)  // Bits 31-0: Buffer MBi Mask for MB95–MB64

// Interrupt Flag Definitions for IFLAG3 (Buffer MBi Interrupt Flags for MB95–MB64)
#define IFLAG3_BUF95TO64_MASK    (0xFFFFFFFF << 0)   // Bits 31-0: Buffer MBi Interrupt Flags for MB95–MB64

// External Timer Register Definitions
#define ET_TIMER_MASK           (0xFFFFFFFF << 0)  // Bits 31-0: External Timer Value

// Fault Confinement Interrupt Enable Register Definitions
#define FLTCONF_IE_PTA_IE_MASK  (1 << 1)     // Bit 1: Passive to Active Interrupt Enable
#define FLTCONF_IE_ATP_IE_MASK  (1 << 0)     // Bit 0: Active to Passive Interrupt Enable

// RXIMR (Individual Mask Bits) Definitions
#define RXIMR_MI_MASK            (0xFFFFFFFF << 0)  // 32-bit mask for Individual Mask Bits

// MECR (Memory Error Configuration Register) Fields Definitions
#define MECR_ECRWRDIS            (1 << 31)     // Error Configuration Register Write Disable
#define MECR_HANCEI_MSK          (1 << 19)     // Host Access with Noncorrectable Errors Interrupt Mask
#define MECR_FANCEI_MSK          (1 << 18)     // FlexCAN Access with Noncorrectable Errors Interrupt Mask
#define MECR_CEI_MSK             (1 << 16)     // Correctable Errors Interrupt Mask
#define MECR_HAERRIE             (1 << 15)     // Host Access Error Injection Enable
#define MECR_FAERRIE             (1 << 14)     // FlexCAN Access Error Injection Enable
#define MECR_EXTERRIE            (1 << 13)     // Extended Error Injection Enable
#define MECR_RERRDIS             (1 << 9)      // Error Report Disable
#define MECR_ECCDIS              (1 << 8)      // Error Correction Disable
#define MECR_NCEFAFRZ            (1 << 7)      // Noncorrectable Errors in FlexCAN Access Put Chip in Freeze Mode

// ERRIAR (Error Injection Address Register) Fields Definitions
#define ERRIAR_INJADDR_H         (0xFFF << 2)  // Error Injection Address High (12 MSBs)
#define ERRIAR_INJADDR_L         (0x3 << 0)         // Error Injection Address Low (2 LSBs)

// ERRIDPR (Error Data Pattern Register) Fields Definitions
#define ERRIDPR_DFLIP            (0xFFFFFFFF << 0)  // Data Flip Pattern (flip pattern for data word)

// Parity Flip Pattern Bit Masks for ERRIPPR
#define ERRIPPR_PFLIP3           (0x1F << 24)  // Parity Flip Pattern for Byte 3 (Most Significant)
#define ERRIPPR_PFLIP2           (0x1F << 16)  // Parity Flip Pattern for Byte 2
#define ERRIPPR_PFLIP1           (0x1F << 8)  // Parity Flip Pattern for Byte 1
#define ERRIPPR_PFLIP0           (0x1F << 0)  // Parity Flip Pattern for Byte 0 (Least Significant)

// Raw Error Register Fields Definitions (RERRAR)
#define RERRAR_NCE               (1 << 24)  // Noncorrectable Error
#define RERRAR_SAID              (0x7 << 16)  // Source of Access Identification (SAID)
#define RERRAR_ERRADDR           (0x3FFF << 0)  // Error Address

// Raw Data Read from Memory with Error (RERRDR)
#define RERRDR_RDATA             (0xFFFFFFFF << 0)  // Raw Data Word Read from Memory with Error

// Bit Masks and Field Definitions for Error Syndrome
#define RERRSYNR_BE3_MASK      (1 << 31)  // Byte Enable for Byte 3 (Most Significant)
#define RERRSYNR_SYND3_MASK    (0x1F << 24)  // Error Syndrome for Byte 3
#define RERRSYNR_BE2_MASK      (1 << 23)  // Byte Enable for Byte 2
#define RERRSYNR_SYND2_MASK    (0x1F << 16)  // Error Syndrome for Byte 2
#define RERRSYNR_BE1_MASK      (1 << 15)  // Byte Enable for Byte 1
#define RERRSYNR_SYND1_MASK    (0x1F << 8)  // Error Syndrome for Byte 1
#define RERRSYNR_BE0_MASK      (1 << 7)  // Byte Enable for Byte 0 (Least Significant)
#define RERRSYNR_SYND0_MASK    (0x1F << 0)  // Error Syndrome for Byte 0

// Bit Masks for Error Status Register (ERRSR)
#define ERRSR_HANCEIF_MASK     (1 << 19)  // Host Access with Non-correctable Error Interrupt Flag
#define ERRSR_FANCEIF_MASK     (1 << 18)  // FlexCAN Access with Non-correctable Error Interrupt Flag
#define ERRSR_CEIF_MASK        (1 << 16)  // Correctable Error Interrupt Flag
#define ERRSR_HANCEIOF_MASK    (1 << 3)  // Host Access with Non-correctable Error Interrupt Overrun Flag
#define ERRSR_FANCEIOF_MASK    (1 << 2)  // FlexCAN Access with Non-correctable Error Interrupt Overrun Flag
#define ERRSR_CEIOF_MASK       (1 << 0)  // Correctable Error Interrupt Overrun Flag

// Bit Masks for Extended Prescaler Registers (EPRS)
#define EPRS_EDPRESDIV_MASK    (0x3FF << 16)  // Extended Data Phase Prescaler Division Factor Mask
#define EPRS_ENPRESDIV_MASK    (0x3FF << 0)  // Extended Nominal Prescaler Division Factor Mask

// Bit Masks for Nominal Bit Timing Registers (ENCBT)
#define ENCBT_NRJW_MASK        (0x7F << 22)  // Nominal Resynchronization Jump Width Mask
#define ENCBT_NTSEG2_MASK      (0x7F << 12)  // Nominal Time Segment 2 Mask
#define ENCBT_NTSEG1_MASK      (0xFF << 0)  // Nominal Time Segment 1 Mask

// Bit Masks for Data Bit Timing Registers (EDCBT)
#define EDCBT_DRJW_MASK        (0xF << 22)  // Data Phase Resynchronization Jump Width Mask
#define EDCBT_DTSEG2_MASK      (0xF << 12)  // Data Phase Time Segment 2 Mask
#define EDCBT_DTSEG1_MASK      (0x1F << 0)  // Data Phase Time Segment 1 Mask

// Bit Masks for Transceiver Delay Compensation (ETDC)
#define ETDC_ETDCEN_MASK       (1 << 31)  // Transceiver Delay Compensation Enable Mask
#define ETDC_TDMDIS_MASK       (1 << 30)  // Transceiver Delay Measurement Disable Mask
#define ETDC_ETDCOFF_MASK      (0x7F << 16)  // Enhanced Transceiver Delay Compensation Offset Mask
#define ETDC_ETDCFAIL_MASK     (1 << 15)  // Transceiver Delay Compensation Fail Mask
#define ETDC_ETDCVAL_MASK      (0xFF << 0)  // Enhanced Transceiver Delay Compensation Value Mask

// Bit Masks for Flexible Data Control (FDCTRL)
#define FDCTRL_FDRATE_MASK     (1 << 31)  // Bit Rate Switch Enable Mask
#define FDCTRL_MBDSR2_MASK     (0x3 << 22)  // Message Buffer Data Size for Region 2 Mask
#define FDCTRL_MBDSR1_MASK     (0x3 << 19)  // Message Buffer Data Size for Region 1 Mask
#define FDCTRL_MBDSR0_MASK     (0x3 << 16)  // Message Buffer Data Size for Region 0 Mask
#define FDCTRL_TDCEN_MASK      (1 << 15)  // Transceiver Delay Compensation Enable Mask
#define FDCTRL_TDCFAIL_MASK    (1 << 14)  // Transceiver Delay Compensation Fail Mask
#define FDCTRL_TDCOFF_MASK     (0x1F << 8)  // Transceiver Delay Compensation Offset Mask
#define FDCTRL_TDCVAL_MASK     (0x3F << 0)  // Transceiver Delay Compensation Value Mask

// Bit Definitions for Fast Bit Timing Control (FDCBT)
#define FDCBT_FPRESDIV_MASK    (0x3FF << 20)   // Fast Prescaler Division Factor Mask
#define FDCBT_FRJW_MASK        (0x7 << 16)    // Fast Resync Jump Width Mask
#define FDCBT_FPROPSEG_MASK    (0x1F << 10)    // Fast Propagation Segment Mask
#define FDCBT_FPSEG1_MASK      (0x7 << 5)     // Fast Phase Segment 1 Mask
#define FDCBT_FPSEG2_MASK      (0x7 << 0)     // Fast Phase Segment 2 Mask

// Bit Definitions for CRC Registers (FDCRC)
#define FDCRC_FD_MBCRC_MASK    (0x7F << 24)   // CRC Message Buffer Number for FD_TXCRC Mask
#define FDCRC_FD_TXCRC_MASK    (0x1FFFFF << 0) // Extended Transmitted CRC Value Mask

// Enhanced RX FIFO Control Register (ERFCR) Masks
#define ERFCR_ERFEN_MASK       (1 << 31)     // Enhanced RX FIFO Enable Mask
#define ERFCR_DMALW_MASK       (0x1F << 26)    // DMA Last Word Mask
#define ERFCR_NEXIF_MASK       (0x7F << 16)    // Number of Extended ID Filter Elements Mask
#define ERFCR_NFE_MASK         (0x3F << 8)     // Number of Enhanced RX FIFO Filter Elements Mask
#define ERFCR_ERFWM_MASK       (0x1F << 0)     // Enhanced RX FIFO Watermark Mask

// Enhanced RX FIFO Interrupt Enable Register (ERFIER) Masks
#define ERFIER_ERFUFWIE_MASK   (1 << 31)     // Underflow Interrupt Enable Mask
#define ERFIER_ERFOVFIE_MASK   (1 << 30)     // Overflow Interrupt Enable Mask
#define ERFIER_ERFWMIIE_MASK   (1 << 29)     // Watermark Indication Interrupt Enable Mask
#define ERFIER_ERFDAIE_MASK    (1 << 28)     // Data Available Interrupt Enable Mask

// Enhanced RX FIFO Status Register (ERFSR) Masks
#define ERFSR_ERFUFW_MASK      (1 << 31)     // Underflow Flag Mask
#define ERFSR_ERFOVF_MASK      (1 << 30)     // Overflow Flag Mask
#define ERFSR_ERFWMI_MASK      (1 << 29)     // Watermark Indication Flag Mask
#define ERFSR_ERFDA_MASK       (1 << 28)     // Data Available Flag Mask
#define ERFSR_ERFCLR_MASK      (1 << 27)     // FIFO Clear Mask
#define ERFSR_ERFE_MASK        (1 << 17)     // FIFO Empty Flag Mask
#define ERFSR_ERFF_MASK        (1 << 16)     // FIFO Full Flag Mask
#define ERFSR_ERFEL_MASK       (0x3F << 0)          // FIFO Elements Mask (6 bits)