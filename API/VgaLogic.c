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
	VgaIOClearScreen(color);
	return 0;
}


//Momenteel gewoon invullen, later dit als optie maken.
int API_draw_rectangle (int x_lup, int y_lup, int x_rdown, int y_rdown, int color, int style, int reserved)
{
	int x_length = x_rdown-x_lup+1;

	if (reserved)
	{
		int y_line;
		for (y_line = y_lup; y_line <= y_rdown; y_line++) {
			VgaIOSetLine(x_lup,y_line,x_length,color);
		}
	}
	else
	{
		VgaIOSetLine(x_lup,y_lup,x_length,color);
		VgaIOSetLine(x_lup,y_rdown,x_length,color);
		API_draw_line(x_lup,y_lup,x_lup,y_rdown,color,1,0);
		API_draw_line(x_rdown,y_lup,x_rdown,y_rdown,color,1,0);
	}
	return 0;
}



int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{ /* plot an anti-aliased line of width weight */

	//TODO: CHECK OF LIJN HORIZONTAAL IS, ZOJA GEBRUIK VgaIOSetLine()


	if (weight == 1)
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
	else
	{
		float f_weight = weight;

		int dx = abs(x_2-x_1), sx = x_1 < x_2 ? 1 : -1;
		int dy = abs(y_2-y_1), sy = y_1 < y_2 ? 1 : -1;
		int err = dx-dy, e2, x2, y2; /* error value e_xy */

		float ed = dx+dy == 0 ? 1 : sqrt((float)dx*dx+(float)dy*dy);

		for (f_weight = (f_weight+1)/2; ; )
		{ /* pixel loop */
			if ( 255*(abs(err-dx+dy)/ed-f_weight+1) < LINE_WIDTH_CUTOFF )
				VgaIOSetPixel(x_1, y_1, color);
			e2 = err; x2 = x_1;
			if (2*e2 >= -dx)
			{ /* x step */
				for (e2 += dy, y2 = y_1; e2 < ed*f_weight && (y_2 != y2 || dx > dy); e2 += dx)
					if ( 255*(abs(e2)/ed-f_weight+1) < LINE_WIDTH_CUTOFF )
						VgaIOSetPixel(x_1, y2 += sy, color);
				if (x_1 == x_2) break;
				e2 = err; err -= dy; x_1 += sx;
			}
			if (2*e2 <= dy) { /* y step */
				for (e2 = dx-e2; e2 < ed*f_weight && (x_2 != x2 || dx < dy); e2 += dy)
					if ( 255*(abs(e2)/ed-f_weight+1) < LINE_WIDTH_CUTOFF )
					VgaIOSetPixel(x2 += sx, y_1, color);
				if (y_1 == y_2) break;
				err += dx; y_1 += sy;
			}
		}
	}
	return 0;
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
