/**
  ******************************************************************************
  * @file    Fonts.h
  * @author  Team 3
  * @version V1.0.0
  * @date    29-May-2019
  * @brief   This file defines the structures used in 'Font.c'
  */

//Include standard interger types ('uint8_t' used by the font arrays)
#include "stdint.h"


/**
	@brief Deceleration of structure used for storing info about a character. Stores the width of each character and the address of the first byte of the character.
*/
typedef struct
{
	int width;
	int font_adr;
}	FONT_INFO;

/**
	@brief Deceleration of structure used for storing info about a font. Stores address of the information for each character of the font and stores the address of the byte array of the font.
*/
typedef struct
{
 	const FONT_INFO *bitmap_info;
	const uint8_t *bitmap;
} FONTS;

extern FONTS all_fonts[];
