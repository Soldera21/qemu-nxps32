#include <stdint.h>
#define UART0_ADDRESS                         ( 0x40328000UL )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x14 ) ) ) )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x1C ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x18 ) ) ) )
#define UART0_BAUD                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0x10 ) ) ) )

void UART_init(void);
void UART_printf(const char *s);

