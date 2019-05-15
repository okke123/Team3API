/**
  ******************************************************************************
  * @file    AppFront.c
  * @author  Chileam Bohnen
  * @version V0.0.1
  * @date    30-april-2019
  * @brief   This file provides the front layer for the application
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "AppFront.h"

/** @addtogroup App Demo application
  * @{
  */

/** @defgroup AppFront Front layer
  * @brief Terminal functions
  * @{
  */

/**
 * @brief	Error code handling routine according to the specified error value
 * 			an automated message is generated.
 * @param	error:		integer that contains an error code value.
 *
 * @param	error_msg:	char pointer that contains a feedback message for the therminal.
 * @retval	None
 */
void ErrorCodeHandler(char error, char* error_msg)
{
	switch(error)
	{
		case API_NONE_ERROR:
			strcpy(error_msg, "\0");
			break;

		case API_DISCONNECT_ERROR:
			strcpy(error_msg, "VGA kabel is niet verbonden.\n\r");
			break;

		case API_UNKNOWN_COMMAND_ERROR:
			strcpy(error_msg, "Script commando onbekend.\n\r"
						 "Mogelijke commando's zijn:\n\r"
						 "\trechthoek,x_lup,y_lup,x_rdowm,y_rdown,kleur,stijle,reserved\n\r"
						 "\ttekst,x_lup,y_lup,kleur,text,font,fontsize,fontstyle,reserved\n\r");
			break;

		case API_COMMAND_READ_ERROR:
			strcpy(error_msg, "No data read.\n\r");
			break;

		case API_CLEARSCREEN_PARAM_ERROR:
			strcpy(error_msg, "Parameters clearscreen zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tclearscreen,kleur\n\r");
			break;

		case API_LINE_PARAM_ERROR:
			strcpy(error_msg, "Paramaters lijn zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tlijn,x_1,y_1,x_2,y_2,kleur,dikte,reserverd\n\r");
			break;

		case API_RECT_PARAM_ERROR:
			strcpy(error_msg, "Parameters rechthoek zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\trechthoek,x_lup,y_lup,x_rdowm,y_rdown,kleur,stijle,reserved\n\r");
			break;

		case API_TEXT_PARAM_ERROR:
			strcpy(error_msg, "Parameters text zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\ttekst,x_lup,y_lup,kleur,text,font,fontsize,fontstyle,reserved\n\r");
			break;

		case API_BITMAP_PARAM_ERROR:
			strcpy(error_msg, "Parameters bitmap zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tbitmap,x_lup,y_lup,bitmap_nummer");
			break;

		case API_WAIT_PARAM_ERROR:
			strcpy(error_msg, "Parameters wacht zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\twacht,milliseconden");
			break;

		case API_OFF_SCREEN_ERROR:
			strcpy(error_msg, "Object is buiten het beeldscherm.\n\r");
			break;

		case API_COLOR_ERROR:
			strcpy(error_msg, "Deze kleur is niet mogelijk.\n\r");
			break;

		case API_MEM_FAULT_ERROR:
			strcpy(error_msg, "Systeem heeft een geheugen.\n\r");
			break;

		default:
			stpcpy(error_msg, "\0");
			break;
	}
}
/**
  * @}
  */

/**
  * @}
  */
