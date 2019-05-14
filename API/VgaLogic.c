#include <VgaLogic.h>
#include <VgaIO.h>
#include <math.h>

int API_draw_simple_line (int x_1, int y_1, int x_2, int y2, int color);

//--------------------------------------------------------------
// fill the DMA RAM buffer with one color
//--------------------------------------------------------------
void API_init(void)
{
	VgaIOInit();
}


int API_clearscreen (int color)
{
	VgaIOClearScreen(color);
	return 0;
}


int API_draw_rectangle (int x, int y, int width, int height, int color, int filled, int weight, int bordercolor)
{
	int x_line, y_line;

	if (filled)
	{
		if (width > 2*weight)
		{
			for (y_line = y+weight; y_line < y+height-weight; y_line++) {
				VgaIOSetLine(x+weight,y_line,width-(weight*2),color);
			}
		}
	}
	else
		bordercolor = color;

	for (y_line = y; y_line < y+weight; y_line++) //Bovenlijn + bovenhoeken
		VgaIOSetLine(x,y_line,width,bordercolor);

	for (y_line = y+height-weight; y_line < y+height; y_line++) //Onderlijn + onderhoeken
		VgaIOSetLine(x,y_line,width,bordercolor);

	for (x_line = x; x_line < x+weight; x_line++)
		API_draw_line(x_line,y+weight,x_line,y+height-weight-1,bordercolor,1,0); //linkerlijn

	for (x_line = x+width-weight; x_line < x+width; x_line++)
		API_draw_line(x_line,y+weight,x_line,y+height-weight-1,bordercolor,1,0); //rechterlijn

	return 0;
}



int API_draw_simple_line(int x_1, int y_1, int x_2, int y_2, int color)
{ /* plot an anti-aliased line of width weight */

	//TODO: Berbetering toevoegen voor horizontaal en verticaale lijnen

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


int API_draw_circle (int x, int y, int radius, int color, int reserved)
{
	int x_t = -radius, y_t = 0, err = 2-2*radius; /* II. Quadrant */
	do
	{
		if(reserved)
		{
			VgaIOSetLine(x+x_t, y-y_t, x_t*-2+1, color);
			VgaIOSetLine(x+x_t, y+y_t, x_t*-2+1, color);
		}
		else
		{
			VgaIOSetPixel(x-x_t, y+y_t, color); /*   I. Quadrant (SE)*/
			VgaIOSetPixel(x-y_t, y-x_t, color); /*  II. Quadrant (SW)*/
			VgaIOSetPixel(x+x_t, y-y_t, color); /* III. Quadrant (NW)*/
			VgaIOSetPixel(x+y_t, y+x_t, color); /*  IV. Quadrant (NE)*/
		}
		radius = err;
		if (radius <= y_t) err += ++y_t*2+1;           /* e_xy+e_y < 0 */
		if (radius > x_t || err > y_t) err += ++x_t*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
	}
	while (x_t < 0);
	return 0;
}

int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	if (weight==1)
	{
		API_draw_simple_line(x_1,y_1,x_2,y_2,color);
	}
	else
	{
		float radius = (float)weight/2.0;
		int x_t = -radius, y_t = 0, err = 2-2*radius; /* II. Quadrant */
		do
		{
			int teller;
			for (teller = (x_t*-2)+1; teller > 0; teller--)
			{
				API_draw_simple_line(x_1+x_t+teller-1,y_1-y_t,x_2+x_t+teller-1,y_2-y_t,color);
				API_draw_simple_line(x_1+x_t+teller-1,y_1+y_t,x_2+x_t+teller-1,y_2+y_t,color);
			}

			radius = err;
			if (radius <= y_t) err += ++y_t*2+1;           /* e_xy+e_y < 0 */
			if (radius > x_t || err > y_t) err += ++x_t*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
		}
		while (x_t < 0);
	}
	return 0;
}
