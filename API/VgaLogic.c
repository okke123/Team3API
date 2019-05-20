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


/*Declare private function, not to be used outside file*/
///@cond INTERNAL
int API_draw_simple_line (int x_1, int y_1, int x_2, int y2, int color);
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
	int x_line, y_line;
	
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
	for (x_line = x; x_line < x+weight; x_line++) //Left
		API_draw_line(x_line,y+weight,x_line,y+height-weight-1,bordercolor,1,0);

	for (x_line = x+width-weight; x_line < x+width; x_line++) //Right
		API_draw_line(x_line,y+weight,x_line,y+height-weight-1,bordercolor,1,0);
		
	return 0;
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
		if (radius <= y_t) err += ++y_t*2+1;
		if (radius > x_t || err > y_t) err += ++x_t*2+1;
	}
	while (x_t < 0);
	return 0;
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
	if (weight==1)
	{/* If the weight of the pixel is one, use the 'API_draw_simple_line' function */
		API_draw_simple_line(x_1,y_1,x_2,y_2,color);
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
	}
	return 0;
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
	API_draw_line(x_1,y_1,x_2,y_2,color,weight,0);
	API_draw_line(x_2,y_2,x_3,y_3,color,weight,0);
	API_draw_line(x_3,y_3,x_4,y_4,color,weight,0);
	API_draw_line(x_4,y_4,x_5,y_5,color,weight,0);
	API_draw_line(x_5,y_5,x_1,y_1,color,weight,0);

	return 0;
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
int API_draw_simple_line(int x_1, int y_1, int x_2, int y_2, int color)
{
	//TODO: Berbetering toevoegen voor horizontaal en verticaale lijnen

 /* Initializes private variables */
	int dx = (int)fabs(x_2-x_1), sx = x_1<x_2 ? 1 : -1;
	int dy = (int)fabs(y_2-y_1), sy = y_1<y_2 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

 /* Draw the line according to the Bresenham's line Algorithm */
	for(;;){
		VgaIOSetPixel(x_1,y_1,color);
		if (x_1==x_2 && y_1==y_2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x_1 += sx; }
		if (e2 < dy) { err += dx; y_1 += sy; }
	}

	return 0;
}
// End exclusion of doxygen
///@endcond
