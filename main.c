#include <VgaLogic.h>
#include <stm32f4xx.h>

int main(void)
{
	SystemInit();
	API_init();

	API_clearscreen(0xFF);

	//X: 0-109 | 110-209 | 210-319
	//Y: 0-69  |  70-169 | 170-239
	API_draw_rectangle(110, 70, 209, 169, 0x00, 0, 0);
	API_draw_rectangle(113, 73, 206, 166, 0x00, 0, 1);


	//API_draw_line(319,0,0,239,0x00,1,0);
	//API_draw_line(30,0,319,209,0xE0,2,0);
	//API_draw_line(0,0,319,239,0x03,10,0);

	API_draw_line(159,0,161,239,0xFF,10,0);
	API_draw_line(0,119,319,121,0xFF,10,0);

	API_draw_circle(160,120,100,0x00,0);
	API_draw_circle(160,120,40,0xFF,1);


    while(1)
    {

    }
}
