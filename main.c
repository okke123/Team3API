#include "main.h"

char error_msg[255];
char msg[100];
int error;

int main(void)
{
	//int i;
    SystemInit();
    UartInit();
    API_init();
    API_clearscreen(0xFF);

    API_draw_text(0, 0, VGA_COL_RED, "the quick brown fox jumps over the lazy dog", 1);

	  while(1)
    {
    	error = UartGets(msg, 0);
    	if (error)
    	{
    		ErrorCodeHandler(error, error_msg);
    		UartPuts(error_msg);
    	}
      else
      {
    		UartPuts(msg);
    	}
    }
}
