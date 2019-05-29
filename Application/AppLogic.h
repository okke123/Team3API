/**
  ******************************************************************************
  * @file    AppLogic.h
  * @author  Team 3
  * @brief   The headerfile for the AppLogic.c and includes relevant files, global defines and functions.
*/

#ifndef __APP_LOGIC_H
#define __APP_LOGIC_H

#include "AppUart.h"
#include "VgaLogic.h"

#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"

//#define DEBUG 1

#define NUM_SET "0123456789"
#define DELIMITER ","

/** @defgroup color names.
 *  @{
 *  	color names:
 * 		|defines kleur				|	kleur			|
 * 		|:-------------------------:|:------------------|
 * 		|COLOR_TEXT_BLACK			|	zwart			|
 * 		|COLOR_TEXT_BLUE			|	blauw			|
 * 		|COLOR_TEXT_LIGHT_BLUE		|	lichtblauw		|
 * 		|COLOR_TEXT_GREEN			|	groen			|
 * 		|COLOR_TEXT_LIGHT_GREEN		|	lichtgroen		|
 * 		|COLOR_TEXT_CYAN			|	cyaan			|
 * 		|COLOR_TEXT_LIGHT_CYAN		|	lichtcyaan		|
 * 		|COLOR_TEXT_RED				|	rood			|
 * 		|COLOR_TEXT_LIGHT_RED		|	lichtrood		|
 * 		|COLOR_TEXT_MAGENTA			|	magenta			|
 * 		|COLOR_TEXT_LIGHT_MAGENTA	|	lichtmagenta	|
 * 		|COLOR_TEXT_BROWN			|	bruin			|
 * 		|COLOR_TEXT_YELLOW			|	geel			|
 * 		|COLOR_TEXT_GRAY			|	grijs			|
 * 		|COLOR_TEXT_WHITE			|	wit				|
 * 		|COLOR_TEXT_PINK			|	roze			|
  */


#define COLOR_TEXT_BLACK 		 "zwart"
#define COLOR_TEXT_BLUE 		 "blauw"
#define COLOR_TEXT_LIGHT_BLUE 	 "lichtblauw"
#define COLOR_TEXT_GREEN 		 "groen"
#define COLOR_TEXT_LIGHT_GREEN 	 "lichtgroen"
#define COLOR_TEXT_CYAN 		 "cyaan"
#define COLOR_TEXT_LIGHT_CYAN 	 "lichtcyaan"
#define COLOR_TEXT_RED 			 "rood"
#define COLOR_TEXT_LIGHT_RED 	 "lichtrood"
#define COLOR_TEXT_MAGENTA 		 "magenta"
#define COLOR_TEXT_LIGHT_MAGENTA "lichtmagenta"
#define COLOR_TEXT_BROWN 		 "bruin"
#define COLOR_TEXT_YELLOW 		 "geel"
#define COLOR_TEXT_GRAY 		 "grijs"
#define COLOR_TEXT_WHITE 		 "wit"
#define COLOR_TEXT_PINK 		 "roze"


#define PARAMETER_TYPE_NUMBER 		1
#define PARAMETER_TYPE_COLOR 		2
#define PARAMETER_TYPE_FONT_STYLE 	3

#define FONT_STYLE_TEXT_NORMAL 	"normaal"
#define FONT_STYLE_TEXT_BOLD 	"vet"
#define FONT_STYLE_TEXT_ITALIC 	"cursief"

#define FONT_STYLE_CODE_NORMAL 	1
#define FONT_STYLE_CODE_BOLD 	2
#define FONT_STYLE_CODE_ITALIC 	3


#define COMMAND_TEXT_LINE 		 "lijn"
#define COMMAND_TEXT_CLEARSCREEN "clearscherm"
#define COMMAND_TEXT_RECTANGLE 	 "rechthoek"
#define COMMAND_TEXT_TEXT 		 "tekst"
#define COMMAND_TEXT_BITMAP 	 "bitmap"
#define COMMAND_TEXT_FIGURE 	 "figuur"
#define COMMAND_TEXT_CIRCLE 	 "cirkel"


/** @defgroup color names.
 *  @{
 *  	codes:
 * 		|define command code		|	value	|
 * 		|:-------------------------:|:----------|
 * 		|COMMAND_CODE_LINE			|	1		|
 * 		|COMMAND_CODE_CLEARSCREEN	|	2		|
 * 		|COMMAND_CODE_RECTANGLE		|	3		|
 * 		|COMMAND_CODE_TEXT			|	4		|
 * 		|COMMAND_CODE_BITMAP		|	5		|
 * 		|COMMAND_CODE_FIGURE		|	6		|
 * 		|COMMAND_CODE_CIRCLE		|	7		|
*/
#define COMMAND_CODE_LINE 		 1
#define COMMAND_CODE_CLEARSCREEN 2
#define COMMAND_CODE_RECTANGLE 	 3
#define COMMAND_CODE_TEXT 		 4
#define COMMAND_CODE_BITMAP 	 5
#define COMMAND_CODE_FIGURE 	 6
#define COMMAND_CODE_CIRCLE 	 7

int CharToInt(char* src, int *value);

void CreateObject(char* src, int error);

void StringHandler(char *str_inkomend);

char *trim(char *str, const char *seps);

void StringHandler(char *str_inkomend);

int check_commando(char *functie_naam);


#endif
