/**
  ******************************************************************************
  * @file    VgaLogic.h
  * @author  Team 3
  * @version V1.0.0
  * @date    15-May-2019
  * @brief   This file prototypes the functions of 'VgaLogic.c', defines global constants and includes the nesseciary files.
  */

/** @defgroup ErrorCode Error codes
 *  @{
 *  	Error codes values:
 * 		|	Error code	|	Error type									|
 * 		|:-------------:|:----------------------------------------------|
 * 		|		0x00	|	None error									|
 * 		|		0x0n	|	Hardware related							|
 * 		|		0x1n	|	Script commandos related					|
 * 		|		0x2n	|	Draw functions related						|
 * 		|		0x3n	|	Memory functions related					|
 *
 */

/** @}*/

#define		API_NONE_ERROR					0x00
/* Hardware related ------------------------------------------------------------------*/
#define		API_DISCONNECT_ERROR			0x01
#define		API_UNKNOWN_COMMAND_ERROR		0x02
#define		API_COMMAND_READ_ERROR			0x03
/* Script commandos related ----------------------------------------------------------*/
#define 	API_CLEARSCREEN_PARAM_ERROR		0x10
#define 	API_LINE_PARAM_ERROR			0x11
#define 	API_RECT_PARAM_ERROR			0x12
#define 	API_TEXT_PARAM_ERROR			0x13
#define 	API_BITMAP_PARAM_ERROR			0x14
#define 	API_WAIT_PARAM_ERROR			0x15
#define		API_REPEAT_PARAM_ERROR			0x16
#define		API_EXECUTE_PARAM_ERROR			0x17
#define		API_CIRCLE_PARAM_ERROR			0x18
#define		API_FIGURE_PARAM_ERROR			0x19
/* Draw functions related ------------------------------------------------------------*/
#define		API_OFF_SCREEN_ERROR			0x20
#define		API_COLOR_ERROR					0x21
/* Memory functions related ----------------------------------------------------------*/
#define		API_MEM_FAULT_ERROR				0x30

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "VgaIO.h"
#include "math.h"


//--------------------------------------------------------------
// Global Function call
//--------------------------------------------------------------
void API_init(void);

int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontsytle, int reserved);
int API_draw_line (int x_1, int y_1, int x_2, int y2, int color, int weight, int reserved);
int API_draw_rectangle (int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
int API_draw_bitmap (int x_lup, int y_lup, int bm_nr);
int API_clearscreen (int color);

int API_wait (int msecs);
int API_repeat_commands (int nr_previous_commands, int iterations, int reserved);
int API_execute (void);
int API_draw_circle (int x, int y, int radius, int color, int filled);
int API_draw_figure (int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int weight);


//--------------------------------------------------------------
// Color defines
//--------------------------------------------------------------
// 8bit color (R3G3B2)
// Red   (3bit) -> Bit7-Bit5
// Green (3bit) -> Bit4-Bit2
// Blue  (2bit) -> Bit1-Bit0
//--------------------------------------------------------------


<<<<<<< HEAD
#define LINE_WIDTH_CUTOFF 150 //lager is minder dik       en hoger is dikker

#define  VGA_COL_BLACK			0x00 //0b00000000
#define  VGA_COL_BLUE			0x03 //0b00000011
#define  VGA_COL_LIGHT_BLUE		0x53 //0b01010011
#define  VGA_COL_GREEN			0x1C //0b00011100
#define  VGA_COL_LIGHT_GREEN	0x7D //0b01111101
#define  VGA_COL_CYAN			0x1F //0b00011111
#define  VGA_COL_LIGHT_CYAN		0x7F //0b01111111
#define  VGA_COL_RED			0xE0 //0b11100000
#define  VGA_COL_LIGHT_RED		0xED //0b11101101
#define  VGA_COL_MAGENTA		0xE3 //0b11100011
#define  VGA_COL_LIGHT_MAGENTA	0xEF //0b11101111
#define  VGA_COL_BROWN			0xA5 //0b10100101
#define  VGA_COL_YELLOW			0xFC //0b11111100
#define  VGA_COL_GRAY			0x49 //0b01001001
#define  VGA_COL_WHITE			0xFF //0b11111111
#define	 VGA_COL_PINK			0xF2 //0b10010010
