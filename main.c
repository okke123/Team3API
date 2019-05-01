#include "Uart.h"
#include "AppFront.h"
#include "AppLogic.h"

int error;
char* object_name;

int main(void)
{
	UartInit(UART_BAUDRATE);
	UartPuts("Hallo\n\r");

	int i = CharToInt("100", error);
	StrSplit("Hallo,allemaal", object_name, error);

    while(1)
    {
    }
}
