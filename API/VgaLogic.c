/**
  ******************************************************************************
  * @file    VgaLogic.c
  * @author  Team 3
  * @version V1.0.0
  * @date    29-May-2019
  * @brief   This file provides the logical functions of the API that do the following:
  *           - Draw lines and shapes on the VGA screen
  *           - Load images on the VGA screen
  *           - Clear the screen / make the screen one color
  *
  * @note	The origin of the x and y coordinates on the screen are in the top left.
  */

/** @addtogroup API
 *  @brief	API for VGA
 * 	@{
 */

/** @defgroup API-Logic API Logic Layer
 *  @brief	All the logic functions for the VGA screen
 * 	@{
 */

#include "VgaLogic.h"

/*Declare private function, not to be used outside file*/
void	API_draw_simple_line (int x_1, int y_1, int x_2, int y2, int color);
int 	API_check_outside_screen (int x, int y);
void	API_draw_character(int x_lup, int y_lup, int char_val, int color, FONTS font_style, int format);
int		API_word_pixel_size(char *text, FONTS *font_info);
int		API_get_font_value(char *fontname, int fontsize, int fontstype);

/**
  * @brief  Initializes all the necessary API functionality in the IO-Layer (GPIO, Timers, DMA, Interrupts & SRAM)
  * @return None
  */
void API_init(void)
{
	VgaIOInit();
}



/**
  * @brief  Makes the VGA screen one color by calling VgaIOClearScreen() with the given color
  * @param  color: integer with color code
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
  * @return Error:	A integer error code if something went wrong, else it's zero
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
  * @return Error:	A integer error code if something went wrong, else it's zero
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

  * @return Error:	A integer error code if something went wrong, else it's zero
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

  * @return Error:	A integer error code if something went wrong, else it's zero
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
   @brief	Draws text with the given font, style and size on the VGA screen
   @note	The top left of the character is the origin for the coordinates

   @param x: 			X value of the coordinate
   @param y: 			Y value of the coordinate
   @param color:		Color of the text
   @param *text:		String to be displayed
   @param *fontname: 	Name of the font ("arial" or "consolas")
   @param fontsize:		Font size (0=small, 1=big)
   @param fontstype:	Font style (0=normal, 1=bold, 2=italic)
   @param reserved:		Value to enable new lines jumping to x coordinate

   @return Error:		A integer error code if something went wrong, else it's zero
*/
int API_draw_text (int x, int y, int color, char *text, char *fontname, int fontsize, int fontstyle, int reserved)
{
	//Make parameters ready to be used in API_get_font_value()
	fontsize-=1;
	fontstyle-=1;

	int x_jumps = 0;

	if(reserved)
		x_jumps = x;

	int font_ber = API_get_font_value(fontname, fontsize, fontstyle);

	FONTS info = all_fonts[font_ber];

	int grot_str;
	grot_str = strlen(text);

	//Make a char array and make a pointer pointing to this new char array. This is needed for the strtok function
	char str_buf[grot_str];
	strcpy(str_buf,text);
	char *pstr;

	//Splits the incomming string to words and look per word.
	for(pstr = strtok (str_buf," ");pstr!=NULL;pstr = strtok (NULL, " "))
  	{
		//Check the size of the word
  		int str_len = strlen(pstr);
  		//Get the nessesairy pixelwidth of the word
  		int x_pixel_size = API_word_pixel_size(pstr,&info);

  		//Put text on next line if it doesn't fit on the screen
		if(x+x_pixel_size>VGA_DISPLAY_X)
		{
  			x=x_jumps+2;	//2 pixels inbetween characters

			//Check what space should be in between lines
  			y += (info.bitmap_info[0].width>8) ? 16 : 8;
  			y+=2;
  		}

		int i;
		//Look at every character of the word one by one
		for(i=0;i<str_len;i++)
		{
			//Make sure the character is lowercase
			int ltr_val = tolower(*(pstr+i)) - 'a';
			//Make sure the character is in the alphabet
			if(ltr_val >= 0 && ltr_val <= 25)
			{
				API_draw_character(x,y,ltr_val,color,info, font_ber);
				x+=info.bitmap_info[ltr_val].width+2;
			}
			else
				//If character is not in the alphabet then return a parameter error
				return API_TEXT_PARAM_ERROR;
		}
		//Check how big a space should be
		x += (info.bitmap_info[0].width > 8) ? 10 : 6;
	}
	return 0;
}



/**
   @brief	Draws bitmap on the VGA screen
   @note	The top left of the bitmap is the origin for the coordinates

   @param 	x: 				X value of the coordinate
   @param 	y: 				Y value of the coordinate
   @param 	bitmap_number:	Integer of bitmap number

   @return 	Error:			A integer error code if something went wrong, else it's zero
*/
int API_draw_bitmap (int x, int y, int bitmap_number)
{
	VgaIOSetBitmap(x, (VGA_DISPLAY_X + 1)*y, &bitmaps[bitmap_number]);
	return API_NONE_ERROR;
}


/* Internal functions ---------------------------------------------------------------------------------------------------------------------*/


/**
  * @brief  Draws a line with the weight of one pixel on the VGA screen
  * @note 	This function is private and not able to be called outside VgaLogic.c
  *
  * @param  x_1:	X value of 1st point of the line on the VGA screen
  * @param  y_1:	Y value of 1st point of the line on the VGA screen
  * @param  x_2:	X value of 2st point of the line on the VGA screen
  * @param  y_2:	Y value of 2st point of the line on the VGA screen
  * @param  color:	Color of the line

  * @return Error:	A integer error code if something went wrong, else it's zero
  */
void API_draw_simple_line(int x_1, int y_1, int x_2, int y_2, int color)
{
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
  * @param  x:		X value of the point
  * @param  y:		Y value of the point
  *
  * @return Error:	Gives back a API_OFF_SCREEN_WARNING if outside screen, zero if this is not the case
  */
int API_check_outside_screen (int x, int y)
{
	if (x < 0 || x >= VGA_DISPLAY_X || y < 0 || y >= VGA_DISPLAY_Y)
		return API_OFF_SCREEN_WARNING;
	return 0;
}

/**
   @brief 	Function for drawing a single character
   @note 	This function is private and not able to be called outside VgaLogic.c
   @note	The top left of the character is the origin for the coordinates

   @param x_lup: 		X value of the point 
   @param y_lup: 		Y value of the point
   @param char_val:		Interger value of character (In order of the alphabet)
   @param color:		Color of the character.
   @param font_style:	Information of the font style
   @param format:		Size of the text (0=small and 1=big)

   @return void
*/
void API_draw_character(int x_lup, int y_lup, int char_val, int color, FONTS font_style, int format)
{
	//counters for loops
	int y, x_cor, byte_tel=0;

	int x_tel = 0;
	int width_x, width_y;

	//See if character is 'Z'
	if(char_val == 25)
	{ //Set widths
		width_x = (font_style.bitmap_info[char_val].width>8) ? 2 : 1;
		width_y = (format>5) ? 16 : 8;
	}
	//Other characters
	else
	{ //Set widths
		if(font_style.bitmap_info[char_val].width > 16)
			width_x = 3;
		else if(font_style.bitmap_info[char_val].width > 8 && font_style.bitmap_info[char_val].width <= 16)
			width_x = 2;
		else width_x = 1;
		width_y = ((font_style.bitmap_info[char_val+1].font_adr - font_style.bitmap_info[char_val].font_adr)) / width_x;
	}

	//Make counter of bitmap the index value where the character begins in the font byte array
	int bitmap_tel = font_style.bitmap_info[char_val].font_adr;

	//Go through all horizontal lines of the character specified by the widths
	for(y = y_lup; y < (y_lup + (width_y)); y++)
	{
		//Go through all the pixels in the horizontal line of the character
		for(x_cor = x_lup; x_cor < (x_lup+(width_x*8)); x_cor+=8, byte_tel++,bitmap_tel++)
		{
			//Get byte and store it
			uint8_t buf = font_style.bitmap[bitmap_tel];
			uint8_t op;	//Is used for bitwise AND operator

			//Use bitwise operator to see if pixel should be changed
			for(x_tel=0, op=128;x_tel!=8;op/=2,x_tel++)
			{
				if(buf&op)
				{
					VgaIOSetPixel(x_cor+x_tel,y,color);
				}
			}
		}
	}
}



/**
   @brief This function measures the pixel width of the given word
   @note 	This function is private and not able to be called outside VgaLogic.c

   @param text: 		String which contains the word to measure
   @param *font_info:	Pointer to fontstyle

   @return x_tot:		Width of the word in pixels
*/
int API_word_pixel_size(char *text, FONTS *font_info)
{
	int x_tot = 0, i;
	//Look at every character in the string
	for(i=0;*(text+i)  != '\0';i++)
	{ //Look at ASCII value of character
		int asci = *(text+i) - 'a';	

	 //Look at width of character and add two pixels for readability
		x_tot+=	font_info->bitmap_info[asci].width + 2;
	}
	return x_tot;
}



/**
   @brief	Function that gets the correct integer value for the font used in API_draw_text()
   @note 	This function is private and not able to be called outside VgaLogic.c

   @param fontname: 	Char pointer (string) Name of the font ("arial" or "consolas")
   @param fontsize:		Int value of font size (0=small, 1=big)
   @param fontstype:	Int value of text style (0=normal, 1=bold, 2=italic)

   @return font_value:	Integer value for the font used in API_draw_text()
*/
int API_get_font_value(char *fontname, int fontsize, int fontstype)
{
	int font_value = 0;
	if(fontsize==1)
		font_value+=6;
	if(!strcmp(fontname,"arial"))
		font_value+=3;

	font_value += fontstype;
	return font_value;
}

/**
 * @}
 */

/**
 * @}
 */
