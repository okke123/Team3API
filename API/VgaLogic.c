#include <VgaLogic.h>
#include <VgaIO.h>

//--------------------------------------------------------------
// fill the DMA RAM buffer with one color
//--------------------------------------------------------------
void API_init(void)
{
	VgaIOInit();
}


int API_clearscreen (int color)
{

	//Optie 1 (for loop)
	uint16_t xp,yp;
/*	OLD LEGACY CODE
	for(yp=0;yp<VGA_DISPLAY_Y;yp++) {
		for(xp=0;xp<VGA_DISPLAY_X;xp++) {
			VgaIOSetPixel(xp,yp,color);
		}
	}
*/
	//Optie 2 Memset:
	memset(VGA_RAM1, color, sizeof(VGA_RAM1));
	return 0;
}


//Momenteel gewoon invullen, later dit als optie maken.
int API_draw_rectangle (int x_lup, int y_lup, int x_rdown, int y_rdown, int color, int style, int reserved)
{
	uint16_t xp,yp;

	// invul:
	for(yp=y_lup;yp<=y_rdown;yp++) {
		for(xp=x_lup;xp<=x_rdown;xp++) {
			if (!reserved){
				if(xp != x_lup)
				{
					if(xp != x_rdown)
					{
						if(yp != y_lup)
						{
							if(yp != y_rdown)
								continue;
						}
					}
				}
			}
			VgaIOSetPixel(xp,yp,color);
		}
	}
}


int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int dx = abs(x_2-x_1), sx = x_1<x_2 ? 1 : -1;
	int dy = abs(y_2-y_1), sy = y_1<y_2 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		VgaIOSetPixel(x_1,y_1,color);
		if (x_1==x_2 && y_1==y_2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x_1 += sx; }
		if (e2 < dy) { err += dx; y_1 += sy; }
	}
}


