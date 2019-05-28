/**
  ******************************************************************************
  * @file    VgaLogic.c
  * @author  Team 3
  * @version V1.0.0
  * @date    15-May-2019
  * @brief   This file provides the logical functions of the API that do the following:
  *           - Draw lines and shapes on the VGA screen
  *           - Load images on the VGA screen
  *           - Clear the screen / make the screen one color
  *           - Wait for a specified time (and store commands during this time to be executed later)
  *           - Execute saved commands
  *           - Repeat previous commands
  *
  * @note	The origin of the x and y coordinates on the screen are in the top left.
  */

/** @addtogroup VGA-API
 *  @brief	API for VGA
 * 	@{
 */

/** @defgroup VGA-API-Logic API Logic Layer
 *  @brief	All the logic functions for the VGA screen
 * 	@{
 */

#include "VgaLogic.h"
#include "Fonts.h"

/*Declare private function, not to be used outside file*/
///@cond INTERNAL
void API_draw_simple_line (int x_1, int y_1, int x_2, int y2, int color);
void swap_horizontal(char* src, char* dest, int columns, int rows);
void swap_vertical(char* src, char* dest, int columns, int rows);
void swap(char *a, char *b);

//FONTS zijn toegevoegd in de Fonts.c file

int API_check_outside_screen (int x, int y);
///@endcond

/**
  * @brief  Initializes all the necessary API functionality in the IO-Layer (GPIO, Timers, DMA, Interrupts & SRAM)
  * @param  None
  * @retval None
  */
void API_init(void)
{
	VgaIOInit();
}



/**
  * @brief  Makes the VGA screen one color by calling VgaIOClearScreen() with the given color
  * @param  Color: integer with color code
  * @retval Error: A integer error code if something went wrong, else it's zero
  */
int API_clearscreen (int color)
{
	VgaIOClearScreen(color);
	return 0;
}



/**
  * @brief  Draws a rectangle on the VGA screen with the specified values
  * @note	The top left of the rectangle is the origin for the coordinates
  *
  * @param  x:				X position on the VGA screen (top left is the origin)
  * @param  y:				Y position on the VGA screen (top left is the origin)
  * @param  width:			Width of the rectangle (borders included)
  * @param  height:			Height of the rectangle (borders included)
  * @param  color:			Color of the border (except if the rectangle is filled, then this color is used for the inside of the rectangle)
  * @param  filled:			Specifies if the rectangle needs to be filled in with the 'color' parameter (0: only border | 1: border and filled)
  * @param  weight:			Weight of the border
  * @param  bordercolor:	Color of the border if the parameter 'color' is used for the inside of the rectangle
  *
  * @retval Error:	A integer error code if something went wrong, else it's zero
  */
int API_draw_rectangle (int x, int y, int width, int height, int color, int filled, int weight, int bordercolor)
{
	int error = 0;
	int y_line;
	
 /* Check if rectangle should be filled in */
	if (filled)
	{
		if (width > 2*weight)
		{
		 /* Fills in the inside with horizontal lines */
			for (y_line = y+weight; y_line < y+height-weight; y_line++) {
				VgaIOSetLine(x+weight,y_line,width-(weight*2),color);
			}
		}
	}
	else
	 /* If the inside does not need to be filled in use the parameter 'color' for the border */
		bordercolor = color;

 /* Draw the horizontal lines of the border */
	for (y_line = y; y_line < y+weight; y_line++) //Top
		VgaIOSetLine(x,y_line,width,bordercolor);

	for (y_line = y+height-weight; y_line < y+height; y_line++) //Bottom
		VgaIOSetLine(x,y_line,width,bordercolor);
		
 /* Draw the vertical lines of the border */
	for (y_line = y+weight; y_line < y+height-weight; y_line++) //Left + Right
	{
		VgaIOSetLine(x,y_line,weight,bordercolor);
		VgaIOSetLine(x+width-weight,y_line,weight,bordercolor);
	}
		
	error |= API_check_outside_screen(x,y);
	error |= API_check_outside_screen(x+width-1,y+height-1);

	return error;
}



/**
  * @brief  Draws a circle on the VGA screen with the specified values
  * @note	The center of the circle is the origin for the coordinates
  *
  * @param  x:				X position of center of circle
  * @param  y:				Y position of center of circle
  * @param  radius:			Radius of the circle
  * @param  color:			Color of the circle
  * @param  filled:			Specifies if the circle needs to be filled in (0: only border | 1: filled)
  *
  * @retval Error:	A integer error code if something went wrong, else it's zero
  */
int API_draw_circle (int x, int y, int radius, int color, int filled)
{
 /* Initializes private variables */
	int error = 0;
	int x_t = -radius, y_t = 0, err = 2-2*radius;

	do
	{
		if(filled)
		{/* If circle needs to be filled in, use horizontal lines */
			VgaIOSetLine(x+x_t, y-y_t, x_t*-2+1, color);
			VgaIOSetLine(x+x_t, y+y_t, x_t*-2+1, color);
		}
		else
		{/* If not filled in, draw the border per quadrant */
			VgaIOSetPixel(x+y_t, y+x_t, color); /* Quadrant (NE)*/
			VgaIOSetPixel(x-x_t, y+y_t, color); /* Quadrant (SE)*/
			VgaIOSetPixel(x-y_t, y-x_t, color); /* Quadrant (SW)*/
			VgaIOSetPixel(x+x_t, y-y_t, color); /* Quadrant (NW)*/
		}
	 /* Change variables according to the Brensenham's Algorithm */
		radius = err;
		if (radius <= y_t)
			err += ++y_t*2+1;
		if (radius > x_t || err > y_t)
			err += ++x_t*2+1;
	}
	while (x_t < 0);

	error |= API_check_outside_screen(x-radius,y-radius);
	error |= API_check_outside_screen(x+radius,y+radius);

	return error;
}


/**
  * @brief  Draws a line with the weight and color specified on the VGA screen
  * @note 	This function is private and not able to be called outside VgaLogic.c
  *
  * @param  x_1:		X value of 1st point of the line on the VGA screen
  * @param  y_1:		Y value of 1st point of the line on the VGA screen
  * @param  x_2:		X value of 2st point of the line on the VGA screen
  * @param  y_2:		Y value of 2st point of the line on the VGA screen
  * @param  color:		Color of the line
  * @param  weight:		Weight of the line
  * @param  reserved:	Extra parameter for later

  * @retval Error:	A integer error code if something went wrong, else it's zero
  */
int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int error = 0;

	if (weight==1)
	{/* If the weight of the pixel is one, use the 'API_draw_simple_line' function */
		API_draw_simple_line(x_1,y_1,x_2,y_2,color);

		error |= API_check_outside_screen(x_1,y_1);
		error |= API_check_outside_screen(x_2,y_2);

	}
	else
	{/* If the weight is more than one, make two circles at the points and draw multiple lines between them */
		float radius = (float)weight/2.0; //Weight is the same as diameter and the function needs a radius so we half the weight.

	 /* Initializes private variables */
		int x_t = -radius, y_t = 0, err = 2-2*radius;
		do
		{
			int teller;
			for (teller = (x_t*-2)+1; teller > 0; teller--)
			{/* Draw the lines between the two circles for all the pixels of the circles */
				API_draw_simple_line(x_1+x_t+teller-1,y_1-y_t,x_2+x_t+teller-1,y_2-y_t,color);
				API_draw_simple_line(x_1+x_t+teller-1,y_1+y_t,x_2+x_t+teller-1,y_2+y_t,color);
			}
		 /* Change variables according to the Brensenham's Algorithm */
			radius = err;
			if (radius <= y_t) err += ++y_t*2+1;
			if (radius > x_t || err > y_t) err += ++x_t*2+1;
		}
		while (x_t < 0);

		error |= API_check_outside_screen(x_1-(weight/2),y_1-(weight/2));
		error |= API_check_outside_screen(x_1+(weight/2),y_1+(weight/2));

		error |= API_check_outside_screen(x_2-(weight/2),y_2-(weight/2));
		error |= API_check_outside_screen(x_2+(weight/2),y_2+(weight/2));
	}
	return error;
}



/**
  * @brief  Draws a polygon with the given points on the VGA screen
  *
  * @param  x_1:		X value of 1st point of the polygon on the VGA screen
  * @param  y_1:		Y value of 1st point of the polygon on the VGA screen
  * @param  x_2:		X value of 2st point of the polygon on the VGA screen
  * @param  y_2:		Y value of 2st point of the polygon on the VGA screen
  * @param  x_3:		X value of 3st point of the polygon on the VGA screen
  * @param  y_3:		Y value of 3st point of the polygon on the VGA screen
  * @param  x_4:		X value of 4st point of the polygon on the VGA screen
  * @param  y_4:		Y value of 4st point of the polygon on the VGA screen
  * @param  x_5:		X value of 5st point of the polygon on the VGA screen
  * @param  y_5:		Y value of 5st point of the polygon on the VGA screen
  * @param  color:		Color of the lines of the polygon
  * @param  weight:		Weight of the lines of the polygon

  * @retval Error:	A integer error code if something went wrong, else it's zero
  */
int API_draw_figure (int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int weight)
{
	int error = 0;

	error |= API_draw_line(x_1,y_1,x_2,y_2,color,weight,0);
	error |= API_draw_line(x_2,y_2,x_3,y_3,color,weight,0);
	error |= API_draw_line(x_3,y_3,x_4,y_4,color,weight,0);
	error |= API_draw_line(x_4,y_4,x_5,y_5,color,weight,0);
	error |= API_draw_line(x_5,y_5,x_1,y_1,color,weight,0);

	return error;
}

/**
 * @}
 */

/**
 * @}
 */

// This function is internal so we dont want this documentation to appear in doxygen
///@cond INTERNAL

/**
  * @brief  Draws a line with the weight of one pixel on the VGA screen
  * @note 	This function is private and not able to be called outside VgaLogic.c
  *
  * @param  x_1:	X value of 1st point of the line on the VGA screen
  * @param  y_1:	Y value of 1st point of the line on the VGA screen
  * @param  x_2:	X value of 2st point of the line on the VGA screen
  * @param  y_2:	Y value of 2st point of the line on the VGA screen
  * @param  color:	Color of the line

  * @retval Error:	A integer error code if something went wrong, else it's zero
  */
void API_draw_simple_line(int x_1, int y_1, int x_2, int y_2, int color)
{
	//TODO: Berbetering toevoegen voor horizontaal en verticaale lijnen

 /* Initializes private variables */
	int dx = (int)fabs(x_2-x_1), sx = x_1<x_2 ? 1 : -1;
	int dy = (int)fabs(y_2-y_1), sy = y_1<y_2 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

 /* Draw the line according to the Bresenham's line Algorithm */
	while(1){
		VgaIOSetPixel(x_1,y_1,color);
		if (x_1==x_2 && y_1==y_2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x_1 += sx; }
		if (e2 < dy) { err += dx; y_1 += sy; }
	}
}



/**
  * @brief	Checks if the given position is outside the screen
  * @note 	This function is private and not able to be called outside VgaLogic.c
  *
  * @param  x_1:	X value of the point
  * @param  y_1:	Y value of the point

  * @retval Error:	Gives back a '0x20' if outside screen, '0' if this is not the case
  */
int API_check_outside_screen (int x, int y)
{
	if (x < 0 || x >= VGA_DISPLAY_X || y < 0 || y >= VGA_DISPLAY_Y)
		return API_OFF_SCREEN_ERROR;
	return 0;
}

/**!
   @brief Functie voor het schrijven van een char waarde van A tot Z.
   @param x_lup: 		links boven start cordinaat op de x-as.
   @param y_lup: 		links boven start cordinaat op de y-as.
   @param ltr_val:		letter waarde als een integer (a = 0, z = 25)
   @param color:		kleur van de fonts.
   @param FONTS info:	juiste font van die gekozen moet worden.
   @param format:		of de tekst klein (0) of groot (1) is.
   @return void
*/
void Draw_Letter(int x_lup, int y_lup, int ltr_val, int color, FONTS info, int format)
{
	//tellers voor for loops.
	int y, x_cor, byte_tel=0;

	int x_tel = 0;
	int width_x, width_y;

	//uitzondering voor de Z.
	//revisie 25-5-2019
	if(ltr_val == 25)
	{
		//e heeft dus 1.
		width_x = (info.bitmap_info[ltr_val].width>8) ? 2 : 1;
		width_y = (format>5) ? 16 : 8;
	}
	//Rest van de letters.
	else
	{
		if(info.bitmap_info[ltr_val].width > 16)
			width_x = 3;
		else if(info.bitmap_info[ltr_val].width > 8 && info.bitmap_info[ltr_val].width <= 16)
			width_x = 2;
		else width_x = 1;
		width_y = ((info.bitmap_info[ltr_val+1].font_adr - info.bitmap_info[ltr_val].font_adr)) / width_x;
	}

	//maak de teller van de bitmap gelijk aan het juiste adres van de letter.
	int bitmap_tel = info.bitmap_info[ltr_val].font_adr;

	//laat de teller net zo lang lopen als dat de font een y positie heeft.
	for(y = y_lup; y < (y_lup + (width_y)); y++)
	{
		//laat de teller net zo lang lopen als dat de font een x positie heeft.
		for(x_cor = x_lup; x_cor < (x_lup+(width_x*8)); x_cor+=8, byte_tel++,bitmap_tel++)
		{
			//haal de byte op en sla deze lokaal op als een buffer.
			uint8_t buf = info.bitmap[bitmap_tel];
			uint8_t op = 128;	//de operator wordt gebruikt als bitwise operator.
			for(x_tel=0, op=128;x_tel!=8;op/=2,x_tel++)
			{
				//AND-maks met de operator. Als dit een 1 is moet er een pixel worden getekend.
				if(buf&op)
				{
					VgaIOSetPixel(x_cor+x_tel,y,color);
				}
			}
		}
	}
}

/**
   @brief functie die de totale pixelsize meet.
   @param text: inkomende char pointer string.
   @param FONTS *info: pointer naar de desbetreffende font.
   @return totale grote van de pixels van het woord.
*/
int woord_pixel_groot(char *text, FONTS *info)
{
	int x_tot = 0, i;
	//bekijk elke char in de string.
	for(i=0;*(text+i)  != '\0';i++)
	{
		int asci = *(text+i) - 'a';	//controleer welke waarde deze moet zijn in de font array.
		//controlleer de wijdte van het aantal pixels
		x_tot+=	info->bitmap_info[asci].width;
		x_tot+=2;	//twee pixels tussen de chars voor leesbaarheid.
	}
	return x_tot;
}

/**
   @brief zorgt dat de goede font wordt aangeroepen.
   @param fontname: 	naam van de font (arial of consolas)
   @param fontsize:	of de tekst klein (0) of groot (1) is.
   @param fontstype:	of de tekst normaal (0), vet (1) of cursief (2) is.
   @return waarde van 0 tot 6.
*/
int get_info(char *fontname, int fontsize, int fontstype)
{
	int tel=0;
	if(fontsize==1)
		tel+=6;
	if(!strcmp(fontname,"arial"))	//check of beide strings gelijk zijn.
		tel+=3;
	tel+=fontstype;
	return tel;
} //return de waarde voor de fonts struct.

/**
   @brief omzetten van een string naar letters op het vga scherm.
   @param x: 			start positie van de x-as bij de linkerbovenkant.
   @param y: 			start positie van de y-as bij de rechterbovenkant.
   @param color:		kleur van de letters.
   @param text:			string van de te printen tekst.
   @param fontname: 	naam van de font (arial of consolas)
   @param fontsize:		of de tekst klein (0) of groot (1) is.
   @param fontstype:	of de tekst normaal (0), vet (1) of cursief (2) is.
   @param reserved:		gereserveerde parameter voor extra functionaliteiten.

   @pre string tekst.
   @post tekst op vga scherm.
*/
int API_draw_text (int x, int y, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved)
{
	//maak de fontsize gelijk aan de bedachte formule in get_info()
	fontsize-=1;	//0 is klein, 1 is groot.
	fontstyle-=1;	//0 = normaal, 1 = vet, 2 = cursief.

	int x_jumps = 0;

	if(reserved)
		x_jumps = x;

	int font_ber = get_info(fontname, fontsize, fontstyle);

	FONTS info = fonts[font_ber];

	int grot_str;
	grot_str = strlen(text);

	//maak een char array aan en zet de pointer over naar dit array. Dit is zo nodig voor de strtok functie.
	char str_buf[grot_str];
	strcpy(str_buf,text);
	char *pstr;

	//splits de inkomende string in wooorden. En ga per woord kijken.
	for(pstr = strtok (str_buf," ");pstr!=NULL;pstr = strtok (NULL, " "))
  	{
		//controleer de lengte van het woord.
  		int str_len = strlen(pstr);
  		//groote van alle pixels van het woord.
  		int x_pixel_size = woord_pixel_groot(pstr,&info);

  		//enter als deze niet past.
		if(x+x_pixel_size>VGA_DISPLAY_X)
		{
  			x=x_jumps+2;	//2pixels afstand voor leesbaarheid!
  			//x=2;	//2pixels afstand voor leesbaarheid!
			//controleer welk font zodat hier een 'enter' komt.
  			y += (info.bitmap_info[0].width>8) ? 16 : 8;
  			y+=2;//2pixels afstand voor leesbaarheid!
  		}

		int i;
		//ga van woord naar letters.
		for(i=0;i<str_len;i++)
		{
			//maak er zeker van dat de char waardes lowercase zijn.
			int ltr_val = tolower(*(pstr+i)) - 'a';
			//maak er zeker van dat de ascii waarde > 'a' & < 'z'
			if(ltr_val >= 0 && ltr_val <= 25)
			{
				Draw_Letter(x,y,ltr_val,color,info, font_ber);
				x+=info.bitmap_info[ltr_val].width+2;	//voor leesbaarheid
			}
			else
				return API_TEXT_PARAM_ERROR;
		}
		//check aan de hand van de font hoe groot de spatie moet zijn.
		x += (info.bitmap_info[0].width > 8) ? 10 : 6; //spatie
	}
	return 0;
}


int API_draw_bitmap (int x_lup, int y_lup, int bm_nr)
{
	int start_x = x_lup;
	int start_y = (VGA_DISPLAY_X + 1) * y_lup;

	VgaIOSetBitmap(start_x, start_y, &bitmaps[bm_nr]);

	return API_NONE_ERROR;
}


// End exclusion of doxygen
///@endcond


