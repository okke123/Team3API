/**
  ******************************************************************************
  * @file    AppFront.c
  * @author  Team 3
  * @brief   This file provides the logical functions for the UART
  *           - init the front layer.
  *			  - pass a string from the UART.
  *			  - check which error code has to be send.
  */

/** @addtogroup Application
 *  @brief	Application used for demo.
 * 	@{
 */

/** @defgroup APP-FRONT Front layer for the application
 *  @brief	All the graphical functions for the app layer.
 * 	@{
 */

/* Includes ------------------------------------------------------------------*/
#include "AppFront.h"

char msg[100];
int error;

void AppFrontLoop(void);


/**
 * @brief	inits the front.
 * @param	void: no parameters needed.
 * @return	none.
 */
void AppFrontInit(void)
{
	UartInit();
	API_init();

	API_clearscreen(VGA_COL_WHITE);

	AppFrontLoop();
}


/**
 * @brief	while loop that gets the the UART messages.
 * @param	void: no parameters needed.
 * @return	none.
 */
void AppFrontLoop(void)
{
	while(1)
	{
		UartGets(msg, 1); //Get String
		StringHandler(msg);
	}
}



/**
 * @brief	Error code handling routine according to the specified error value
 * @param	error:		char that contains an error code value.
 * @return	none.
 */
void ErrorCodeHandler(char error)
{
	char error_msg[255];
	switch(error)
	{
		case API_NONE_ERROR:
			return;
			break;

		case API_UNKNOWN_COMMAND_ERROR:
			strcpy(error_msg, 	"Script commando onbekend.\r"
						 	 	"Mogelijke commando's zijn:\r"
								"\t* lijn\r"
			 	 				"\t* clearscherm\r"
			 	 				"\t* rechthoek\r"
			 	 				"\t* tekst\r"
			 	 				"\t* bitmap\r"
								"\t* figuur\r"
								"\t* cirkel\r");
			break;

		case API_CLEARSCREEN_PARAM_ERROR:
			strcpy(error_msg, "Parameters clearscreen zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tclearscreen, kleur\n\r");
			break;

		case API_LINE_PARAM_ERROR:
			strcpy(error_msg, "Paramaters lijn zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tlijn, x1, y1, x2, y2, kleur, dikte, gereserveerd\n\r");
			break;

		case API_RECT_PARAM_ERROR:
			strcpy(error_msg, "Parameters rechthoek zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\trechthoek, x linksboven, y linksboven, dikte, hoogte, kleur, gevuld, randdikte, randkleur\n\r");
			break;

		case API_TEXT_PARAM_ERROR:
			strcpy(error_msg, "Parameters text zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\ttekst, x linksboven, y linksboven, kleur, tekst, font, grootte, stijl, inspringen\n\r");
			break;

		case API_BITMAP_PARAM_ERROR:
			strcpy(error_msg, "Parameters bitmap zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tbitmap, x linksboven, y linksboven, bitmapnummer");
			break;

		case API_OFF_SCREEN_WARNING:
			strcpy(error_msg, "Object is buiten het beeldscherm.\n\r");
			break;

		case API_CIRCLE_PARAM_ERROR:
			strcpy(error_msg, "Parameters cirkel zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tcirkel, x, y, radius, kleur, gevuld\n\r");
			break;

		case API_FIGURE_PARAM_ERROR:
			strcpy(error_msg, "Parameters figuur zijn niet compleet.\n\r"
						 "Commando template is:\n\r"
						 "\tfiguur, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, kleur, dikte\n\r");
			break;

		default:
			stpcpy(error_msg, "\0");
			break;
	}
	UartPuts(error_msg);
}
/**
  * @}
  */

/**
  * @}
  */
