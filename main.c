#include <VgaLogic.h>
#include <stm32f4xx.h>

int main(void)
{
    SystemInit();
    API_init();

    API_clearscreen(0xFF);

    API_draw_line(50,50,100,200,0x00,1,0);
    API_draw_line(50,50,250,200,0x00,10,0);


	while(1)
    {

    }
}
