#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include <stdio.h>

#define UART0_ADDRESS                         ( 0x40328000UL )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x14 ) ) ) )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x1C ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x18 ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x10 ) ) ) )

/*
#define UART1_ADDRESS                         ( 0x4032C000UL )
#define UART1_STATE                           ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + 0x14 ) ) ) )
#define UART1_DATA                            ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + 0x1C ) ) ) )
#define UART1_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + 0x18 ) ) ) )
#define UART1_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART1_ADDRESS + 0x10 ) ) ) )

#define UART2_ADDRESS                         ( 0x40330000UL )
#define UART2_STATE                           ( *( ( ( volatile uint32_t * ) ( UART2_ADDRESS + 0x14 ) ) ) )
#define UART2_DATA                            ( *( ( ( volatile uint32_t * ) ( UART2_ADDRESS + 0x1C ) ) ) )
#define UART2_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART2_ADDRESS + 0x18 ) ) ) )
#define UART2_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART2_ADDRESS + 0x10 ) ) ) )
*/

void UART_init(void);
void UART_printf(const char *s);
void UART_scanf(char *s);

#endif //__UART_H__
