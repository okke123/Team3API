#include "main.h"

char error_msg[255];
char msg[100];
int error;

int main(void)
{
	int i;
    SystemInit();

    UartInit();

    while(1)
    {
    	error = UartGets(msg, FALSE);
    	if (error)
    	{
    		ErrorCodeHandler(error, error_msg);
    		UartPuts(error_msg);
    	} else {
    		UartPuts(msg);
    	}
    }
}
