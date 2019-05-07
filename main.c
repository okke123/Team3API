#include <VgaLogic.h>
#include <stm32f4xx.h>

int main(void)
{
	SystemInit();
	API_init();

	API_clearscreen(0x03);

	//X: 0-109 | 110-209 | 210-319
	//Y: 0-69  |  70-169 | 170-239
	//API_draw_rectangle(110, 70, 209, 169, 0x00, 0, 1);
	//API_draw_line(0,0,319,239,0xFF,1,0);

	int teller = 0;
    while(1)
    {
    	API_clearscreen(0x00);
    	API_draw_line(160,0,teller,239,0xFF,0,0);
    	teller++;
    	if (teller >= 320)
    		teller = 0;
    }
}
