#include <VgaLogic.h>
#include <stm32f4xx.h>

int main(void)
{
    SystemInit();
    API_init();

	API_clearscreen(0b11111111);
	/*API_draw_rectangle(0,0,319,79,0b11100000,0,1);
	API_draw_rectangle(0,160,319,239,0b00000011,0,1);

	API_draw_rectangle(50,130,59,129,0x00,0,1);

	API_draw_line(40,0,279,239,0x00,10,0);
	API_draw_line(40,239,279,0,0x00,10,0);

	API_draw_line(160,0,160,239,0x00,10,0);
	API_draw_line(0,120,319,120,0x00,10,0);

	API_draw_line(100,0,100,239,0x00,9,0);
	API_draw_line(0,180,319,180,0x00,9,0);

	API_draw_line(215,-50,247,239,0x00,10,0);*/
/*
	API_draw_line(50,50,160,100,0x00,1,0);
	API_draw_line(50,70,160,120,0x00,3,0);
	API_draw_line(50,90,160,140,0x00,10,0);


	API_draw_line(250,50,250,200,0x00,1,0);
	API_draw_line(260,50,260,200,0x00,3,0);
	API_draw_line(270,50,270,200,0x00,6,0);
	//API_draw_linecircle(50,50,200,100,0x00,0,0);
	//API_draw_linecircle(50,50,200,100,0x00,3,0);*/

	API_draw_rectangle(50,50,100,50,0xE0,1,10,0x03);
	API_draw_rectangle(50,50,100,50,0x00,0,1,0x00);

	while(1)
    {

    }
}
