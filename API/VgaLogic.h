/**
  ******************************************************************************
  * @file    VgaLogic.h
  * @author  Team 3
  * @version V1.0.0
  * @date    15-May-2019
  * @brief   This file prototypes the functions of 'VgaLogic.c', defines global constants and includes the nesseciary files.
  */


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
int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
int API_draw_rectangle (int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
int API_draw_bitmap (int x_lup, int y_lup, int bm_nr);
int API_clearscreen (int color);

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
