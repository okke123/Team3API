#include "Uart.h"

int main(void)
{
	UartInit(UART_BAUDRATE);
	UartPuts("Hallo\n\r");

    while(1)
    {
    }
}
