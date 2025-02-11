#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define UART0_ADDRESS                         ( 0x40328000UL )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 14UL ) ) ) )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x1C ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 18UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 10UL ) ) ) )

void UART_init(void);
void UART_printf(const char *s);

#endif //__UART_H__
