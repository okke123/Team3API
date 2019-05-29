/**
  ******************************************************************************
  * @file    AppLogic.c
  * @author  Team 3
  * @date    29-5-2019
  * @brief   This file provides the logical functions for the UART:
  *           - char to integer.
  *           - handler of the strings for error codes.
  *           - left trim a string.
  *           - right trim a string.
  *           - left/right trim a string.
  *           - check if the function name from the script is valid.
  *           - check if the parameters in the script are valid.
  */

/** @addtogroup Application
 *  @brief	Application used for demo.
 * 	@{
 */

/** @defgroup APP-LOGIC App Logic Layer
 *  @brief	All the logic functions for the app layer.
 * 	@{
 */

/* Includes ///////////////////////------------------------------------------*/

#include "AppLogic.h"

/* Local deceleration of functions ------------------------------------------*/
int 	AppLogicCharToInt(char* src, int *value);
char   *AppLogicTrimString(char *str, const char *seps);
char   *AppLogicTrimStringLeft(char *str, const char *seps);
char   *AppLogicTrimStringRight(char *str, const char *seps);
int 	AppLogicCheckCommand(char *func_name);
int 	AppLogicCheckParameter(char *parameter, int parameter_type, int *error);


/**
   @brief Function to convert a pointer of char values to a int value.
   @param src:		Pointer of chars that have to be converted.
   @param value:	Pointer of the int value where the value will be stored.
   @return error: 	Returns errorcode if the char pointer can't be converted to integer.
*/
int AppLogicCharToInt(char* src, int* value)
{
	int fault_counter = 0;
	int i = 0, j;

	if (src[i] == '-')
		i = 1;

	for (; i < strlen(src); i++)
	{
		for (j = 0; j < strlen(NUM_SET); j++)
		{
			if (src[i] != *(NUM_SET + j)) {
				fault_counter++;
			}
			else
			{
				break;
			}
		}
		if (fault_counter >= 10)
		{
			*value = 0;
			return API_INT_PARAM_ERROR;
		}
		else
		{
			fault_counter = 0;
		}
	}

	*value = atoi(src);
	return API_NONE_ERROR;
}


/**
   @brief Checks the function for parameters and calls the correct function.
   @param str:		String from the UART.
   @return void
*/
void AppLogicStringHandler(char *str)
{
	//Amount of characters in the string
	int amount_chars;
	for(amount_chars=0;*(str+amount_chars)!='\0';amount_chars++);

	//Exit function if there are no characters
	if(!amount_chars)
		return;

	//Make buffer array
	char str_buf[amount_chars];
	strcpy(str_buf, str);

	char *token;
	int amount_comma = 0, i;

	//Check the amount of commas in the string
	for(i=0; str_buf[i] != '\0';i++)
		amount_comma += (str_buf[i] == ',') ? 1 : 0;

	char *string_array[amount_comma];		//Make a array of multiple char pointers (multiple strings)

	token = strtok(str_buf, ",");

	//Put split strings into array (spaces are trimmed of the front and end of the string)
	for(i=0; token != NULL; i++,token=strtok(NULL,","))
		string_array[i] = AppLogicTrimString(token,NULL);

	//Display split strings if DEBUG is defined
	#ifdef DEBUG
	for (i=0;i<=amount_comma;i++)
		AppUartPuts(string_array[i]);
	#endif

	int error = 0;
	int x_1,x_2,x_3,x_4,x_5;
	int y_1,y_2,y_3,y_4,y_5;
	int color,bordercolor,radius,weight,width,height,fontsize,fontstyle,reserved,filled,bm_nr;

	switch (AppLogicCheckCommand(string_array[0]))
	{
	case COMMAND_CODE_LINE:
		#ifdef DEBUG
			AppUartPuts("Lijn commando gevonden");
		#endif
		if (amount_comma==6 || amount_comma==7) //Fill variables with checked parameters
		{
			x_1 = 		AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			x_2 = 		AppLogicCheckParameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			y_2 = 		AppLogicCheckParameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	AppLogicCheckParameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			weight = 	AppLogicCheckParameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (amount_comma==6)
				reserved = 0;
			else
				reserved = AppLogicCheckParameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_line(x_1,y_1,x_2,y_2,color,weight,reserved);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Lijn getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_LINE_PARAM_ERROR);
		break;

	case COMMAND_CODE_CLEARSCREEN:
		#ifdef DEBUG
			AppUartPuts("Clear commando gevonden");
		#endif
		if (amount_comma==1)
		{
			color = AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_COLOR, &error);

			if (!error)
			{
				error = API_clearscreen(color);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Scherm gevuld");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_CLEARSCREEN_PARAM_ERROR);
		break;

	case COMMAND_CODE_RECTANGLE:
		#ifdef DEBUG
			AppUartPuts("Rechthoek commando gevonden");
		#endif
		if (amount_comma >= 6 && amount_comma <= 8)
		{
			x_1 = 		AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			width = 	AppLogicCheckParameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			height = 	AppLogicCheckParameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	AppLogicCheckParameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			filled = 	AppLogicCheckParameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (amount_comma == 6)
			{
				weight = 1;
				bordercolor = color;
			}
			else
			{
				weight = AppLogicCheckParameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);
				if (amount_comma == 7)
					bordercolor = color;
				else
					bordercolor = AppLogicCheckParameter(string_array[8],PARAMETER_TYPE_COLOR,&error);
			}

			if (!error)
			{
				error = API_draw_rectangle(x_1,y_1,width,height,color,filled,weight,bordercolor);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Rechthoek getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_RECT_PARAM_ERROR);
		break;

	case COMMAND_CODE_TEXT:
		#ifdef DEBUG
			AppUartPuts("Tekst commando gevonden");
		#endif
		if (amount_comma >= 7 && amount_comma <= 8)
		{
			x_1 = 		AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			color =  	AppLogicCheckParameter(string_array[3],PARAMETER_TYPE_COLOR, &error);
			fontsize = 	AppLogicCheckParameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);
			fontstyle = AppLogicCheckParameter(string_array[7],PARAMETER_TYPE_FONT_STYLE,&error);

			if (amount_comma < 8)
				reserved = 0;
			else
				reserved = AppLogicCheckParameter(string_array[8],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_text(x_1,y_1,color,string_array[4],string_array[5],fontsize,fontstyle,reserved);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Tekst getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_TEXT_PARAM_ERROR);
		break;

	case COMMAND_CODE_BITMAP:
		#ifdef DEBUG
			AppUartPuts("Bitmap commando gevonden");
		#endif
		if (amount_comma == 3)
		{
			x_1 = 		AppLogicCheckParameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			bm_nr =  	AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				//TODO: comment out
				error = API_draw_bitmap(x_1,y_1,bm_nr);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Bitmap getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_BITMAP_PARAM_ERROR);
		break;

	case COMMAND_CODE_FIGURE:
		#ifdef DEBUG
			AppUartPuts("Figuur commando gevonden");
		#endif
		if (amount_comma >= 11 && amount_comma <= 12)
		{
			x_1 = 		AppLogicCheckParameter(string_array[1] ,PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[2] ,PARAMETER_TYPE_NUMBER,&error);
			x_2 = 		AppLogicCheckParameter(string_array[3] ,PARAMETER_TYPE_NUMBER,&error);
			y_2 = 		AppLogicCheckParameter(string_array[4] ,PARAMETER_TYPE_NUMBER,&error);
			x_3 = 		AppLogicCheckParameter(string_array[5] ,PARAMETER_TYPE_NUMBER,&error);
			y_3 = 		AppLogicCheckParameter(string_array[6] ,PARAMETER_TYPE_NUMBER,&error);
			x_4 = 		AppLogicCheckParameter(string_array[7] ,PARAMETER_TYPE_NUMBER,&error);
			y_4 = 		AppLogicCheckParameter(string_array[8] ,PARAMETER_TYPE_NUMBER,&error);
			x_5 = 		AppLogicCheckParameter(string_array[9] ,PARAMETER_TYPE_NUMBER,&error);
			y_5 = 		AppLogicCheckParameter(string_array[10],PARAMETER_TYPE_NUMBER,&error);
			color =  	AppLogicCheckParameter(string_array[11],PARAMETER_TYPE_COLOR, &error);

			if (amount_comma < 12)
				weight = 1;
			else
				weight = AppLogicCheckParameter(string_array[12],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_figure(x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4,x_5,y_5,color,weight);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Figuur getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_FIGURE_PARAM_ERROR);
		break;

	case COMMAND_CODE_CIRCLE:
		#ifdef DEBUG
			AppUartPuts("Cirkel commando gevonden");
		#endif
		if (amount_comma >= 4 && amount_comma <= 5)
		{
			x_1 = 		AppLogicCheckParameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		AppLogicCheckParameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			radius = 	AppLogicCheckParameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			color =  	AppLogicCheckParameter(string_array[4],PARAMETER_TYPE_COLOR, &error);

			if (amount_comma < 5) filled = 0;
			else filled = AppLogicCheckParameter(string_array[5],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_circle(x_1,y_1,radius,color,filled);
				AppFrontErrorHandler(error);
				#ifdef DEBUG
					AppUartPuts("Cirkel getekend");
				#endif
				break;
			}
		}
		AppFrontErrorHandler(API_CIRCLE_PARAM_ERROR);
		break;

	default:
		AppFrontErrorHandler(API_UNKNOWN_COMMAND_ERROR);
		break;
	}
}



/**
   @brief 	Function that left trims a string
   @param str:		Pointer to string what has to be left trimmed
   @param seps:		Specific seperator character (default: tab, carriage return, vertical tab, page break, new line and space)
   @return str: 	Returns trimmed string
*/
char *AppLogicTrimStringLeft(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}



/**
   @brief 	Function that right trims a string
   @param str:		Pointer to string what has to be left trimmed
   @param seps:		Specific seperator character (default: tab, carriage return, vertical tab, page break, new line and space)
   @return str: 	Returns trimmed string
*/
char *AppLogicTrimStringRight(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}



/**
   @brief 	Function that trims a string using (AppLogicTrimStringLeft() and AppLogicTrimStringRight() ).
   @param str:		Pointer to string what has to be left trimmed
   @param seps:		Specific seperator character (default: tab, carriage return, vertical tab, page break, new line and space)
   @return str: 	Returns trimmed string
*/
char *AppLogicTrimString(char *str, const char *seps)
{
    return AppLogicTrimStringLeft(AppLogicTrimStringRight(str, seps), seps);
}



/**
   @brief	Function that checks if the command name in the string is valid
   @param func_name:		Pointer to string what has to be checked
   @return command_code: 	Returns corresponding code of command if a function name has been found, else it returns zero
*/
int AppLogicCheckCommand(char *func_name)
{
	//check alle defines
	if(strstr(func_name,COMMAND_TEXT_LINE)			!=NULL)	return COMMAND_CODE_LINE;
	if(strstr(func_name,COMMAND_TEXT_CLEARSCREEN)	!=NULL)	return COMMAND_CODE_CLEARSCREEN;
	if(strstr(func_name,COMMAND_TEXT_RECTANGLE)		!=NULL)	return COMMAND_CODE_RECTANGLE;
	if(strstr(func_name,COMMAND_TEXT_TEXT)			!=NULL)	return COMMAND_CODE_TEXT;
	if(strstr(func_name,COMMAND_TEXT_BITMAP)		!=NULL)	return COMMAND_CODE_BITMAP;
	if(strstr(func_name,COMMAND_TEXT_FIGURE)		!=NULL)	return COMMAND_CODE_FIGURE;
	if(strstr(func_name,COMMAND_TEXT_CIRCLE)		!=NULL)	return COMMAND_CODE_CIRCLE;
	return 0;
}


/**
   @brief 	Function that checks if the parameter type in the string is valid
   @param parameter: 		Pointer to a string array which has stored the parameters.
   @param parameter_type: 	Code for the parameter type.
   @param error: 			Pointer to the error value. Change the value if a error occurures.
   @return integer: 		Returns corresponding code for parameter type, if parameter type is not valid it returns a zero
*/
int AppLogicCheckParameter(char *parameter, int parameter_type, int *error)
{
	int number;

	switch (parameter_type)
	{
		case PARAMETER_TYPE_NUMBER:
			if(!AppLogicCharToInt(parameter,&number))
				return number;
			break;

		case PARAMETER_TYPE_COLOR:
			if(strcmp(parameter, COLOR_TEXT_BLACK)			==0)	return VGA_COL_BLACK;
			if(strcmp(parameter, COLOR_TEXT_BLUE)			==0) 	return VGA_COL_BLUE;
			if(strcmp(parameter, COLOR_TEXT_LIGHT_BLUE)		==0) 	return VGA_COL_LIGHT_BLUE;
			if(strcmp(parameter, COLOR_TEXT_GREEN)			==0) 	return VGA_COL_GREEN;
			if(strcmp(parameter, COLOR_TEXT_LIGHT_GREEN) 	==0) 	return VGA_COL_LIGHT_GREEN;
			if(strcmp(parameter, COLOR_TEXT_CYAN)			==0) 	return VGA_COL_CYAN;
			if(strcmp(parameter, COLOR_TEXT_LIGHT_CYAN)		==0) 	return VGA_COL_LIGHT_CYAN;
			if(strcmp(parameter, COLOR_TEXT_RED) 			==0) 	return VGA_COL_RED;
			if(strcmp(parameter, COLOR_TEXT_LIGHT_RED) 		==0) 	return VGA_COL_LIGHT_RED;
			if(strcmp(parameter, COLOR_TEXT_MAGENTA)		==0)	return VGA_COL_MAGENTA;
			if(strcmp(parameter, COLOR_TEXT_LIGHT_MAGENTA)	==0)	return VGA_COL_LIGHT_MAGENTA;
			if(strcmp(parameter, COLOR_TEXT_BROWN)			==0) 	return VGA_COL_BROWN;
			if(strcmp(parameter, COLOR_TEXT_YELLOW)			==0)	return VGA_COL_YELLOW;
			if(strcmp(parameter, COLOR_TEXT_GRAY)			==0)	return VGA_COL_GRAY;
			if(strcmp(parameter, COLOR_TEXT_WHITE)  		==0) 	return VGA_COL_WHITE;
			if(strcmp(parameter, COLOR_TEXT_PINK)			==0) 	return VGA_COL_PINK;
			break;

		case PARAMETER_TYPE_FONT_STYLE:
			if(strcmp(parameter, FONT_STYLE_TEXT_NORMAL)	==0)	return FONT_STYLE_CODE_NORMAL;
			if(strcmp(parameter, FONT_STYLE_TEXT_BOLD)		==0) 	return FONT_STYLE_CODE_BOLD;
			if(strcmp(parameter, FONT_STYLE_TEXT_ITALIC)	==0) 	return FONT_STYLE_CODE_ITALIC;
			break;

		default:
			break;
	}
	*error += 1;
	return 0;
}
