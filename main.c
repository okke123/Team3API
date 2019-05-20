#include "main.h"

char error_msg[255];
char msg[100];
int error;

int main(void)
{
	int i;
    SystemInit();
<<<<<<< HEAD

    UartInit();

    while(1)
=======
    API_init();
    API_clearscreen(0xFF);

	while(1)
>>>>>>> 11e60f069cd316a58f123febbe623e44b16d7efa
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
