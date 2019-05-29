/**
  ******************************************************************************
  * @file    VgaLogic.h
  * @author  Team 3
  * @version V1.0.0
  * @date    29-May-2019
  * @brief   This file prototypes the functions of 'VgaLogic.c', defines global constants and includes the necessary files.
  */


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "VgaIO.h"	//Include so hardware functions can be used
#include "ctype.h"	//Include so string (char array) can be converted to only lowercase characters
#include "math.h"	//Include for mathematical functions that are used for example by the Brensenham's Algorithm
#include "Fonts.h"	//Include seperate file where fonts are stored


//--------------------------------------------------------------
// Global Function call
//--------------------------------------------------------------
void API_init(void);

int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontsytle, int reserved);
int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
int API_draw_rectangle (int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
int API_draw_bitmap (int x, int y, int bitmap_number);
int API_clearscreen (int color);
int API_draw_circle (int x, int y, int radius, int color, int filled);
int API_draw_figure (int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int weight);


/** @addtogroup API
 *  @brief	API for VGA
 * 	@{
 */
/** @defgroup API-Defines API Defines
 *  @brief	In this module are all the defines that are declared in the API
 *  @{
 *  Error defines
 *	--------------------------------------------------------------
 *	These error codes can be used outside the API to have organised error handeling.
 * 		|	Define name						|	Error type								|  Error value	|
 * 		|:----------------------------------|:------------------------------------------|:-------------:|
 * 		|	API_NONE_ERROR					|	No error								| 0x00			|
 * 		|	API_UNKNOWN_COMMAND_ERROR		|	Unknown command							| 0x01			|
 * 		|	API_CLEARSCREEN_PARAM_ERROR		|	Command clearscreen parameter error		| 0x10			|
 * 		|	API_LINE_PARAM_ERROR			|	Command line parameter error			| 0x11			|
 * 		|	API_RECT_PARAM_ERROR			|	Command rectangle parameter error		| 0x12			|
 * 		|	API_TEXT_PARAM_ERROR			|	Command text parameter error			| 0x13			|
 * 		|	API_BITMAP_PARAM_ERROR			|	Command bitmap parameter error			| 0x14			|
 * 		|	API_CIRCLE_PARAM_ERROR			|	Command circle parameter error			| 0x15			|
 * 		|	API_FIGURE_PARAM_ERROR			|	Command figure parameter error			| 0x16			|
 * 		|	API_INT_PARAM_ERROR				|	Convert string to int parameter error	| 0x17			|
 * 		|	API_OFF_SCREEN_WARNING			|	Drawing outside of screen warning		| 0x20			|
 *
 */
/** @}*/
/** @}*/

/* No error --------------------------------------------------------------------------*/
#define		API_NONE_ERROR					0x00
/* Function command related errors ---------------------------------------------------*/
#define		API_UNKNOWN_COMMAND_ERROR		0x01
/* Function parameter related errors -------------------------------------------------*/
#define 	API_CLEARSCREEN_PARAM_ERROR		0x10
#define 	API_LINE_PARAM_ERROR			0x11
#define 	API_RECT_PARAM_ERROR			0x12
#define 	API_TEXT_PARAM_ERROR			0x13
#define 	API_BITMAP_PARAM_ERROR			0x14
#define		API_CIRCLE_PARAM_ERROR			0x15
#define		API_FIGURE_PARAM_ERROR			0x16
#define		API_INT_PARAM_ERROR				0x17
/* Drawing outside of screen ---------------------------------------------------------*/
#define 	API_OFF_SCREEN_WARNING			0x20


/** @addtogroup API
 * 	@{
 */
/** @addtogroup API-Defines API Defines
 *  @{
 * 	Color defines
 *	--------------------------------------------------------------
 * 	Red   (3bit) -> Bit 7-Bit 5 <br>
 *	Green (3bit) -> Bit 4-Bit 2 <br>
 *	Blue  (2bit) -> Bit 1-Bit 0 <br>
 * 		|	Define name				|	Color			|	HEX value	|	Binary code	|
 * 		|:--------------------------|:------------------|:-------------:|:-------------:|
 * 		|	VGA_COL_BLACK			|	Black			|	0x00		|	00000000	|
 * 		|	VGA_COL_BLUE			|	Blue			|	0x03 		|	00000011	|
 * 		|	VGA_COL_LIGHT_BLUE		|	Light Blue		|	0x53 		|	01010011	|
 * 		|	VGA_COL_GREEN			|	Green			|	0x1C 		|	00011100	|
 * 		|	VGA_COL_LIGHT_GREEN		|	Light Green		|	0x7D 		|	01111101	|
 * 		|	VGA_COL_CYAN			|	Cyan			|	0x1F 		|	00011111	|
 * 		|	VGA_COL_LIGHT_CYAN		|	Light Cyan		|	0x7F 		|	01111111	|
 * 		|	VGA_COL_RED				|	Red				|	0xE0 		|	11100000	|
 * 		|	VGA_COL_LIGHT_RED		|	Light Red		|	0xED 		|	11101101	|
 * 		|	VGA_COL_MAGENTA			|	Magenta			|	0xE3 		|	11100011	|
 * 		|	VGA_COL_LIGHT_MAGENTA	|	Light Magenta	|	0xEF 		|	11101111	|
 * 		|	VGA_COL_BROWN			|	Brown			|	0xA5 		|	10100101	|
 * 		|	VGA_COL_YELLOW			|	Yellow			|	0xFC 		|	11111100	|
 * 		|	VGA_COL_GRAY			|	Gray			|	0x49 		|	01001001	|
 * 		|	VGA_COL_WHITE			|	White			|	0xFF 		|	11111111	|
 * 		|	VGA_COL_PINK			|	Pink			|	0xF2 		|	10010010	|
 */
/** @}*/
/** @}*/

/* Set color defines -----------------------------------------------------------------*/
#define  VGA_COL_BLACK			0x00
#define  VGA_COL_BLUE			0x03
#define  VGA_COL_LIGHT_BLUE		0x53
#define  VGA_COL_GREEN			0x1C
#define  VGA_COL_LIGHT_GREEN	0x7D
#define  VGA_COL_CYAN			0x1F
#define  VGA_COL_LIGHT_CYAN		0x7F
#define  VGA_COL_RED			0xE0
#define  VGA_COL_LIGHT_RED		0xED
#define  VGA_COL_MAGENTA		0xE3
#define  VGA_COL_LIGHT_MAGENTA	0xEF
#define  VGA_COL_BROWN			0xA5
#define  VGA_COL_YELLOW			0xFC
#define  VGA_COL_GRAY			0x49
#define  VGA_COL_WHITE			0xFF
#define	 VGA_COL_PINK			0xF2
