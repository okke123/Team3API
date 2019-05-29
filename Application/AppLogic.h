/**
  ******************************************************************************
  * @file    AppLogic.h
  * @author  Team 3
  * @date    29-5-2019
  * @brief   The headerfile for the AppLogic.c and includes relevant files, global defines and functions.
*/

#ifndef __APP_LOGIC_H
#define __APP_LOGIC_H

/* Includes --------------------------------------------------------------------------------------------------*/
#include "AppUart.h"
#include "VgaLogic.h"

#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"

//#define DEBUG 1

#define NUM_SET "0123456789"
#define DELIMITER ","


/** @addtogroup Application
 *  @brief	Application used for demo
 * 	@{
 */
/** @defgroup APP-DEFINES App Defines
 *  @brief	In this module are all the defines that are declared in the demo application.
 * 	@{
 *	Parameter type codes
 * 	-------------------------------------------------
 * 		|	Define names				|	Value	|
 * 		|:------------------------------|:---------:|
 * 		|	PARAMETER_TYPE_NUMBER		|	1		|
 * 		|	PARAMETER_TYPE_COLOR		|	2		|
 * 		|	PARAMETER_TYPE_FONT_STYLE	|	3		|
  */
/** @}*/
/** @}*/
#define PARAMETER_TYPE_NUMBER 		1
#define PARAMETER_TYPE_COLOR 		2
#define PARAMETER_TYPE_FONT_STYLE 	3


/** @addtogroup Application
 *  @brief	Application used for demo
 * 	@{
 */
/** @addtogroup APP-DEFINES App Defines
 * 	@{
 *	Color names
 * 	-------------------------------------------------------------
 * 		|	Define names				|	Color text (name)	|
 * 		|:------------------------------|:----------------------|
 * 		|	COLOR_TEXT_BLACK			|	zwart				|
 * 		|	COLOR_TEXT_BLUE				|	blauw				|
 * 		|	COLOR_TEXT_LIGHT_BLUE		|	lichtblauw			|
 * 		|	COLOR_TEXT_GREEN			|	groen				|
 * 		|	COLOR_TEXT_LIGHT_GREEN		|	lichtgroen			|
 * 		|	COLOR_TEXT_CYAN				|	cyaan				|
 * 		|	COLOR_TEXT_LIGHT_CYAN		|	lichtcyaan			|
 * 		|	COLOR_TEXT_RED				|	rood				|
 * 		|	COLOR_TEXT_LIGHT_RED		|	lichtrood			|
 * 		|	COLOR_TEXT_MAGENTA			|	magenta				|
 * 		|	COLOR_TEXT_LIGHT_MAGENTA	|	lichtmagenta		|
 * 		|	COLOR_TEXT_BROWN			|	bruin				|
 * 		|	COLOR_TEXT_YELLOW			|	geel				|
 * 		|	COLOR_TEXT_GRAY				|	grijs				|
 * 		|	COLOR_TEXT_WHITE			|	wit					|
 * 		|	COLOR_TEXT_PINK				|	roze				|
  */
/** @}*/
/** @}*/
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


/** @addtogroup Application
 *  @brief	Application used for demo
 * 	@{
 */
/** @addtogroup APP-DEFINES App Defines
 * 	@{
 *	Font styles
 * 	-------------------------------------------------------------
 *	(Text and codes)
 * 		|	Define names (Text)		|	Define names (Code)		|	Text	|	Code 	|
 * 		|:--------------------------|:--------------------------|:----------|:---------:|
 * 		|	FONT_STYLE_TEXT_NORMAL	|	FONT_STYLE_CODE_NORMAL	|	normaal	|	1		|
 * 		|	FONT_STYLE_TEXT_BOLD	|	FONT_STYLE_CODE_BOLD	|	vet		|	2		|
 * 		|	FONT_STYLE_TEXT_ITALIC	|	FONT_STYLE_CODE_ITALIC	|	cursief	|	3		|
  */
/** @}*/
/** @}*/
#define FONT_STYLE_TEXT_NORMAL 	"normaal"
#define FONT_STYLE_TEXT_BOLD 	"vet"
#define FONT_STYLE_TEXT_ITALIC 	"cursief"

#define FONT_STYLE_CODE_NORMAL 	1
#define FONT_STYLE_CODE_BOLD 	2
#define FONT_STYLE_CODE_ITALIC 	3


/** @addtogroup Application
 *  @brief	Application used for demo
 * 	@{
 */
/** @addtogroup APP-DEFINES App Defines
 * 	@{
 *	Command defines
 * 	-------------------------------------------------------------
 *	(Text and corresponding codes)
 * 		|	Define names (Text)			|	Define names (Code)			|	Text		|	Code 	|
 * 		|:------------------------------|:------------------------------|:--------------|:---------:|
 * 		|	COMMAND_TEXT_LINE			|	COMMAND_CODE_LINE			|	lijn		|	1		|
 * 		|	COMMAND_TEXT_CLEARSCREEN	|	COMMAND_CODE_CLEARSCREEN	|	clearscherm	|	2		|
 * 		|	COMMAND_TEXT_RECTANGLE		|	COMMAND_CODE_RECTANGLE		|	rechthoek	|	3		|
 * 		|	COMMAND_TEXT_TEXT			|	COMMAND_CODE_TEXT			|	tekst		|	4		|
 * 		|	COMMAND_TEXT_BITMAP			|	COMMAND_CODE_BITMAP			|	bitmap		|	5		|
 * 		|	COMMAND_TEXT_FIGURE			|	COMMAND_CODE_FIGURE			|	figuur		|	6		|
 * 		|	COMMAND_TEXT_CIRCLE			|	COMMAND_CODE_CIRCLE			|	cirkel		|	7		|
  */
/** @}*/
/** @}*/
#define COMMAND_TEXT_LINE 		 "lijn"
#define COMMAND_TEXT_CLEARSCREEN "clearscherm"
#define COMMAND_TEXT_RECTANGLE 	 "rechthoek"
#define COMMAND_TEXT_TEXT 		 "tekst"
#define COMMAND_TEXT_BITMAP 	 "bitmap"
#define COMMAND_TEXT_FIGURE 	 "figuur"
#define COMMAND_TEXT_CIRCLE 	 "cirkel"

#define COMMAND_CODE_LINE 		 1
#define COMMAND_CODE_CLEARSCREEN 2
#define COMMAND_CODE_RECTANGLE 	 3
#define COMMAND_CODE_TEXT 		 4
#define COMMAND_CODE_BITMAP 	 5
#define COMMAND_CODE_FIGURE 	 6
#define COMMAND_CODE_CIRCLE 	 7

/* Global deceleration of functions ------------------------------------------*/
void AppLogicStringHandler(char *str_inkomend);
int  AppLogicCheckCommand(char *functie_naam);

#endif