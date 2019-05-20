#include <VgaLogic.h>
#include <stm32f4xx.h>

int main(void)
{
    SystemInit();
    API_init();
    API_clearscreen(0xFF);

	while(1)
    {

    }
}
