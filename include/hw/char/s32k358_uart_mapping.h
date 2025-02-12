/*
 * This file is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#define UART_VERID    0x00
#define UART_PARAM    0x04
#define UART_GLOBAL   0x08
#define UART_PINCFG   0x0C
#define UART_BAUD     0x10
#define UART_STAT     0x14
#define UART_CTRL     0x18
#define UART_DATA     0x1C
#define UART_MATCH    0x20
#define UART_MODIR    0x24
#define UART_FIFO     0x28
#define UART_WATER    0x2C
#define UART_DATARO   0x30
#define UART_MCR      0x40
#define UART_MSR      0x44
#define UART_REIR     0x48
#define UART_TEIR     0x4C
#define UART_HDCR     0x50
#define UART_TOCR     0x58
#define UART_TOSR     0x5C
#define UART_TIMEOUT0 0x60
#define UART_TIMEOUT1 0x64
#define UART_TIMEOUT2 0x68
#define UART_TIMEOUT3 0x6C
#define UART_TCBR0    0x200
#define UART_TDBR0    0x400



/* VERID REGISTER MAP */
#define VERID_MAJOR        (0xFF000000) // Major version number mask
#define VERID_MINOR        (0x00FF0000) // Minor version number mask
#define VERID_FEATURE      (0x0000FFFF) // Feature Identification Number mask


/* PARAM REGISTER MAP */
#define PARAM_RXFIFO    (0xFF00)   // Receive FIFO Size (bits 15-8)
#define PARAM_TXFIFO    (0x00FF)   // Transmit FIFO Size (bits 7-0)


/* GLOBAL REGISTER MAP */
#define GLOBAL_RST      (1 << 1)  // Software Reset (bit 1)


/* PINCFG REGISTER MAP */
#define PINCFG_TRGSEL    (0x03)   // Trigger Select (bits 1-0)


/* BAUD REGISTER MAP*/
#define UART_BAUD_MAEN1      (1 << 31)  // Match Address Mode Enable 1 (bit 31)
#define UART_BAUD_MAEN2      (1 << 30)  // Match Address Mode Enable 2 (bit 30)
#define UART_BAUD_M10        (1 << 29)  // 10-Bit Mode Select (bit 29)
#define UART_BAUD_OSR        (0x1F << 24)  // Mask for Oversampling Ratio (bits 28-24)
#define UART_BAUD_TDMAE      (1 << 23)  // Transmitter DMA Enable (bit 23)
#define UART_BAUD_RDMAE      (1 << 21)  // Receiver Full DMA Enable (bit 21)
#define UART_BAUD_MATCFG     (0x3 << 18)  // Mask for Match Configuration (bits 19-18)
#define UART_BAUD_BOTHEDGE   (1 << 17)  // Both Edge Sampling (bit 17)
#define UART_BAUD_RESYNCDIS  (1 << 16)  // Resynchronization Disable (bit 16)
#define UART_BAUD_LBKDIE     (1 << 15)  // LIN Break Detect Interrupt Enable (bit 15)
#define UART_BAUD_RXEDGIE    (1 << 14)  // RX Input Active Edge Interrupt Enable (bit 14)
#define UART_BAUD_SBNS       (1 << 13)  // Stop Bit Number Select (bit 13)
#define UART_BAUD_SBR        (0x1FFF)  // Mask for SBR (bits 12-0)


/* STAT REGISTER MAP */
#define UART_STAT_LBKDIF     (1 << 31)  // LIN Break Detect Interrupt Flag (bit 31)
#define UART_STAT_RXEDGIF    (1 << 30)  // RXD Pin Active Edge Interrupt Flag (bit 30)
#define UART_STAT_MSBF       (1 << 29)  // MSB First (bit 29)
#define UART_STAT_RXINV      (1 << 28)  // Receive Data Inversion (bit 28)
#define UART_STAT_RWUID      (1 << 27)  // Receive Wake Up Idle Detect (bit 27)
#define UART_STAT_BRK13      (1 << 26)  // Break Character Generation Length (bit 26)
#define UART_STAT_LBKDE      (1 << 25)  // LIN Break Detection Enable (bit 25)
#define UART_STAT_RAF        (1 << 24)  // Receiver Active Flag (bit 24)
#define UART_STAT_TDRE       (1 << 23)  // Transmit Data Register Empty Flag (bit 23)
#define UART_STAT_TC         (1 << 22)  // Transmission Complete Flag (bit 22)
#define UART_STAT_RDRF       (1 << 21)  // Receive Data Register Full Flag (bit 21)
#define UART_STAT_IDLE       (1 << 20)  // Idle Line Flag (bit 20)
#define UART_STAT_OR         (1 << 19)  // Receiver Overrun Flag (bit 19)
#define UART_STAT_NF         (1 << 18)  // Noise Flag (bit 18)
#define UART_STAT_FE         (1 << 17)  // Framing Error Flag (bit 17)
#define UART_STAT_PF         (1 << 16)  // Parity Error Flag (bit 16)
#define UART_STAT_MA1F       (1 << 15)  // Match 1 Flag (bit 15)
#define UART_STAT_MA2F       (1 << 14)  // Match 2 Flag (bit 14)
#define UART_STAT_TSF        (1 << 9)   // Timeout Status Flag (bit 9)
#define UART_STAT_MSF        (1 << 8)   // Modem Status Flag (bit 8)
#define UART_STAT_AME        (1 << 1)   // Address Mark Enable (bit 1)
#define UART_STAT_LBKFE      (1 << 0)   // LIN Break Flag Enable (bit 0)

/* CTRL REGISTER MAP */
#define UART_CTRL_R8T9          (1 << 31) // Receive Bit 8 / Transmit Bit 9 (R8 is read-only, T9 is write-only)
#define UART_CTRL_R9T8          (1 << 30) // Receive Bit 9 / Transmit Bit 8 (R9 is read-only, T8 is write-only)
#define UART_CTRL_TXDIR         (1 << 29) // TXD Pin Direction in Single-Wire Mode
#define UART_CTRL_TXINV         (1 << 28) // Transmit Data Inversion
#define UART_CTRL_ORIE          (1 << 27) // Overrun Interrupt Enable
#define UART_CTRL_NEIE          (1 << 26) // Noise Error Interrupt Enable
#define UART_CTRL_FEIE          (1 << 25) // Framing Error Interrupt Enable
#define UART_CTRL_PEIE          (1 << 24) // Parity Error Interrupt Enable
#define UART_CTRL_TIE           (1 << 23) // Transmit Interrupt Enable
#define UART_CTRL_TCIE          (1 << 22) // Transmission Complete Interrupt Enable
#define UART_CTRL_RIE           (1 << 21) // Receiver Interrupt Enable
#define UART_CTRL_ILIE          (1 << 20) // Idle Line Interrupt Enable
#define UART_CTRL_TE            (1 << 19) // Transmitter Enable
#define UART_CTRL_RE            (1 << 18) // Receiver Enable
#define UART_CTRL_RWU           (1 << 17) // Receiver Wake-Up Control
#define UART_CTRL_SBK           (1 << 16) // Send Break
#define UART_CTRL_MA1IE         (1 << 15) // Match 1 Interrupt Enable
#define UART_CTRL_MA2IE         (1 << 14) // Match 2 Interrupt Enable
#define UART_CTRL_M7            (1 << 11) // 7-Bit Mode Select
#define UART_CTRL_IDLECFG       (0x7 << 8) // Idle Configuration (bits 10-8)
#define UART_CTRL_LOOPS         (1 << 7)  // Loop Mode Select
#define UART_CTRL_RSRC          (1 << 5)  // Receiver Source Select
#define UART_CTRL_M             (1 << 4)  // 9-Bit or 8-Bit Mode Select
#define UART_CTRL_WAKE          (1 << 3)  // Receiver Wake-Up Method Select
#define UART_CTRL_ILT           (1 << 2)  // Idle Line Type Select
#define UART_CTRL_PE            (1 << 1)  // Parity Enable
#define UART_CTRL_PT            (1 << 0)  // Parity Type



/* DATA REGISTER MAP */
#define UART_DATA_NOISY         (1 << 15) // Noisy Data Received
#define UART_DATA_PARITYE       (1 << 14) // Parity Error
#define UART_DATA_FRETSC        (1 << 13) // Frame Error / Transmit Special Character
#define UART_DATA_RXEMPT        (1 << 12) // Receive Buffer Empty
#define UART_DATA_IDLINE        (1 << 11) // Idle Line
#define UART_DATA_LINBRK        (1 << 10) // LIN Break
#define UART_DATA_R9T9          (1 << 9)  // Read receive FIFO bit 9 / Write transmit FIFO bit 9
#define UART_DATA_R8T8          (1 << 8)  // Read receive FIFO bit 8 / Write transmit FIFO bit 8
#define UART_DATA_R7T7          (1 << 7)  // Read receive FIFO bit 7 / Write transmit FIFO bit 7
#define UART_DATA_R6T6          (1 << 6)  // Read receive FIFO bit 6 / Write transmit FIFO bit 6
#define UART_DATA_R5T5          (1 << 5)  // Read receive FIFO bit 5 / Write transmit FIFO bit 5
#define UART_DATA_R4T4          (1 << 4)  // Read receive FIFO bit 4 / Write transmit FIFO bit 4
#define UART_DATA_R3T3          (1 << 3)  // Read receive FIFO bit 3 / Write transmit FIFO bit 3
#define UART_DATA_R2T2          (1 << 2)  // Read receive FIFO bit 2 / Write transmit FIFO bit 2
#define UART_DATA_R1T1          (1 << 1)  // Read receive FIFO bit 1 / Write transmit FIFO bit 1
#define UART_DATA_R0T0          (1 << 0)  // Read receive FIFO bit 0 / Write transmit FIFO bit 0


/* MATCH REGISTER MAP */
#define UART_MATCH_MA2         (0x03FF0000)   // Match Address 2 (bits 25-16)
#define UART_MATCH_MA1         (0x000003FF)   // Match Address 1 (bits 9-0)


/* MODIR REGISTER MAP */
#define UART_MODIR_IREN         (1 << 18)   // IR Enable (bit 18)
#define UART_MODIR_TNP          (0x3 << 16)   // Transmitter Narrow Pulse (bits 17-16)
#define UART_MODIR_RTSWATER     (0xF << 8)    // Receive RTS Configuration (bits 15-8)
#define UART_MODIR_TXCTSSRC     (1 << 5)   // Transmit CTS Source (bit 5)
#define UART_MODIR_TXCTSC       (1 << 4)   // Transmit CTS Configuration (bit 4)
#define UART_MODIR_RXRTSE       (1 << 3)   // Receiver RTS Enable (bit 3)
#define UART_MODIR_TXRTSPOL     (1 << 2)   // Transmitter RTS Polarity (bit 2)
#define UART_MODIR_TXRTSE       (1 << 1)   // Transmitter RTS Enable (bit 1)
#define UART_MODIR_TXCTSE       (1 << 0)   // Transmitter CTS Enable (bit 0)


/* FIFO REGISTER MAP */
#define UART_FIFO_TXEMPT        (1 << 23)   // Transmit FIFO Or Buffer Empty (bit 23)
#define UART_FIFO_RXEMPT        (1 << 22)   // Receive FIFO Or Buffer Empty (bit 22)
#define UART_FIFO_TXOF          (1 << 17)   // Transmitter FIFO Overflow Flag (bit 17)
#define UART_FIFO_RXUF          (1 << 16)   // Receiver FIFO Underflow Flag (bit 16)
#define UART_FIFO_TXFLUSH       (1 << 15)   // Transmit FIFO Flush (bit 15)
#define UART_FIFO_RXFLUSH       (1 << 14)   // Receive FIFO Flush (bit 14)
#define UART_FIFO_RXIDEN        (0x7 << 10) // Receiver Idle Empty Enable (bits 12-10)
#define UART_FIFO_TXOFE         (1 << 9)    // Transmit FIFO Overflow Interrupt Enable (bit 9)
#define UART_FIFO_RXUFE         (1 << 8)    // Receive FIFO Underflow Interrupt Enable (bit 8)
#define UART_FIFO_TXFE          (1 << 7)    // Transmit FIFO Enable (bit 7)
#define UART_FIFO_TXFIFOSIZE    (0x7 << 4)  // Transmit FIFO Buffer Depth (bits 6-4)
#define UART_FIFO_RXFE          (1 << 3)    // Receive FIFO Enable (bit 3)
#define UART_FIFO_RXFIFOSIZE    (0x7 << 0)       // Receive FIFO Buffer Depth (bits 2-0)


/* WATER REGISTER MAP */
#define UART_RXCOUNT_MASK      (0x1F << 24)  // RXCOUNT field (bits 24-28)
#define UART_RXWATER_MASK      (0xF << 16)  // RXWATER field (bits 16-19)
#define UART_TXCOUNT_MASK      (0x1F << 8)   // TXCOUNT field (bits 8-12)
#define UART_TXWATER_MASK      (0xF << 0)   // TXWATER field (bits 0-3)


/* DATARO REGISTER MAP */
#define UART_DATARO_DATA_MASK   0x0000FFFF


/* MODEM CONTROL REGISTER MAP */
#define UART_MCR_RTS           (1 << 9)   // Request To Send (bit 9)
#define UART_MCR_DTR           (1 << 8)   // Data Terminal Ready (bit 8)
#define UART_MCR_DCD           (1 << 3)   // Data Carrier Detect Interrupt Enable (bit 3)
#define UART_MCR_RIN           (1 << 2)   // Ring Indicator Interrupt Enable (bit 2)
#define UART_MCR_DSR           (1 << 1)   // Data Set Ready Interrupt Enable (bit 1)
#define UART_MCR_CTS           (1 << 0)   // Clear To Send Interrupt Enable (bit 0)


/* MODEM STATUS REGISTER MAP */
#define UART_MSR_DCD_MASK      (1 << 7)  // DCD (Data Carrier Detect) pin state
#define UART_MSR_RIN_MASK      (1 << 6)  // RIN (Ring Indicator) pin state
#define UART_MSR_DSR_MASK      (1 << 5)  // DSR (Data Set Ready) pin state
#define UART_MSR_CTS_MASK      (1 << 4)  // CTS (Clear To Send) pin state
#define UART_MSR_DDCD_MASK     (1 << 3)  // Delta Data Carrier Detect
#define UART_MSR_DRI_MASK      (1 << 2)  // Delta Ring Indicator
#define UART_MSR_DDSR_MASK     (1 << 1)  // Delta Data Set Ready
#define UART_MSR_DCTS_MASK     (1 << 0)  // Delta Clear To Send


/* REIR REGISTER MAP */
#define UART_REIR_IDTIME      (0x3FFF)  // Mask for Idle Time (bits 13-0)


/* TEIR REGISTER MAP */
#define UART_TEIR_IDTIME      (0x3FFF)  // Mask for Idle Time (bits 13-0)


/* HALF DUPLEX CONTROL REGISTER MAP */
#define UART_HDCR_RTSEXT       (0xFF << 8)   // RTS Extension (bits 15-8)
#define UART_HDCR_RXMSK        (1 << 3)   // Receive Mask (bit 3)
#define UART_HDCR_RXWRMSK      (1 << 2)   // Receive FIFO Write Mask (bit 2)
#define UART_HDCR_RXSEL        (1 << 1)   // Receive Select (bit 1)
#define UART_HDCR_TXSTALL      (1 << 0)   // Transmit Stall (bit 0)


/* TIMEOUT CONTROL REGISTER MAP */
#define UART_TOCR_TOIE         (0xF << 8)      // Timeout Interrupt Enable Mask (bits 11-8)
#define UART_TOCR_TOEN         (0xF << 0)      // Timeout Enable Mask (bits 3-0)


/* TIMEOUT STATUS REGISTER MAP */
#define UART_TOSR_TOF          (0xF << 8)    // Timeout Flag Mask (bits 11-8)
#define UART_TOSR_TOZ          (0xF << 0)     // Timeout Zero Mask (bits 3-0)


/* TIMEOUT REGISTER MAP */
#define UART_TIMEOUT_CFG       (0x3 << 30)  // Mask per configurazione idle (bits 31-30)
#define UART_TIMEOUT_VALUE     (0x3FFF << 0)  // Mask per il valore timeout (bits 0-13)


/* TRANSMIT COMMAND BURST REGISTER MAP */
#define UART_TCBR_DATA         (0xFFFF << 0)     // DATA field (bits 0-15)


/* TRANSMIT DATA BURST REGISTER MAP*/
#define UART_TDBR_DATA0         (0xFF << 0)       // DATA0 field (bits 0-7)
#define UART_TDBR_DATA1         (0xFF << 8)     // DATA1 field (bits 8-15)
#define UART_TDBR_DATA2         (0xFF << 16)   // DATA2 field (bits 16-23)
#define UART_TDBR_DATA3         (0xFF << 24) // DATA3 field (bits 24-31)