/*!
 *	/arthur Chileam Bohnen
 *	/version 0.1
 *	/date 2019-5-1
 *	/mainpage Logic Layer
 *		Command parser for VGA API
 */

#include "AppLogic.h"

int check_commando(char *functie_naam);

int check_parameter(char *parameter, int parameter_type, int *error);

int CharToInt(char* src, int* value)
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
			return API_COMMAND_READ_ERROR;
		}
		else
		{
			fault_counter = 0;
		}
	}

	*value = atoi(src);
	return API_NONE_ERROR;
}

void StringHandler(char *str_inkomend)
{
	//Aantal tekens in de inkomende string
	int aantal_tek;
	for(aantal_tek=0;*(str_inkomend+aantal_tek)!='\0';aantal_tek++);

	//Als er geen tekens zijn gestuurd:
	if(!aantal_tek)
		return;

	//Buffer array aanmaken
	char str_buf[aantal_tek];
	strcpy(str_buf, str_inkomend);

	char *token;
	int aantal_komma = 0, i;
	//Check het aantal komma's in de string
	for(i=0; str_buf[i] != '\0';i++)
		aantal_komma += (str_buf[i] == ',') ? 1 : 0;

	char *string_array[aantal_komma];		//Maak een array aan met alle strings.

	//Zet de string alvast in de pointer.
	token = strtok(str_buf, ",");

	//	Zet alle stukken tekst in de string_array
	for(i=0; token != NULL; i++,token=strtok(NULL,","))
		string_array[i] = trim(token,NULL);

	//DISPLAY ARGUMENTEN
	#ifdef DEBUG
	for (i=0;i<=aantal_komma;i++)
		UartPuts(string_array[i]);
	#endif

	int error = 0;
	int x_1,x_2,x_3,x_4,x_5;
	int y_1,y_2,y_3,y_4,y_5;
	int color,bordercolor,radius,weight,width,height,fontsize,fontstyle,reserved,filled,bm_nr;

	switch (check_commando(string_array[0]))
	{
	case COMMAND_CODE_LINE:
		#ifdef DEBUG
			UartPuts("Lijn commando gevonden");
		#endif
		if (aantal_komma==6 || aantal_komma==7)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			x_2 = 		check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			y_2 = 		check_parameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			weight = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (aantal_komma==6)
				reserved = 0;
			else
				reserved = check_parameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_line(x_1,y_1,x_2,y_2,color,weight,reserved);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Lijn getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_LINE_PARAM_ERROR);
		break;

	case COMMAND_CODE_CLEARSCREEN:
		#ifdef DEBUG
			UartPuts("Clear commando gevonden");
		#endif
		if (aantal_komma==1)
		{
			color = check_parameter(string_array[1],PARAMETER_TYPE_COLOR, &error);

			if (!error)
			{
				error = API_clearscreen(color);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Scherm gevuld");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_CLEARSCREEN_PARAM_ERROR);
		break;

	case COMMAND_CODE_RECTANGLE:
		#ifdef DEBUG
			UartPuts("Rechthoek commando gevonden");
		#endif
		if (aantal_komma >= 6 && aantal_komma <= 8)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			width = 	check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			height = 	check_parameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			filled = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (aantal_komma == 6)
			{
				weight = 1;
				bordercolor = color;
			}
			else
			{
				weight = check_parameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);
				if (aantal_komma == 7)
					bordercolor = color;
				else
					bordercolor = check_parameter(string_array[8],PARAMETER_TYPE_COLOR,&error);
			}

			if (!error)
			{
				error = API_draw_rectangle(x_1,y_1,width,height,color,filled,weight,bordercolor);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Rechthoek getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_RECT_PARAM_ERROR);
		break;

	case COMMAND_CODE_TEXT:
		#ifdef DEBUG
			UartPuts("Tekst commando gevonden");
		#endif
		if (aantal_komma >= 7 && aantal_komma <= 8)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[3],PARAMETER_TYPE_COLOR, &error);
			fontsize = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);
			fontstyle = check_parameter(string_array[7],PARAMETER_TYPE_FONT_STYLE,&error);

			if (aantal_komma < 8)
				reserved = 0;
			else
				reserved = check_parameter(string_array[8],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_text(x_1,y_1,color,string_array[4],string_array[5],fontsize,fontstyle,reserved);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Tekst getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_TEXT_PARAM_ERROR);
		break;

	case COMMAND_CODE_BITMAP:
		#ifdef DEBUG
			UartPuts("Bitmap commando gevonden");
		#endif
		if (aantal_komma == 3)
		{
			x_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			bm_nr =  	check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				//TODO: comment out
				error = API_draw_bitmap(x_1,y_1,bm_nr);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Bitmap getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_BITMAP_PARAM_ERROR);
		break;

	case COMMAND_CODE_FIGURE:
		#ifdef DEBUG
			UartPuts("Figuur commando gevonden");
		#endif
		if (aantal_komma >= 11 && aantal_komma <= 12)
		{
			x_1 = 		check_parameter(string_array[1] ,PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2] ,PARAMETER_TYPE_NUMBER,&error);
			x_2 = 		check_parameter(string_array[3] ,PARAMETER_TYPE_NUMBER,&error);
			y_2 = 		check_parameter(string_array[4] ,PARAMETER_TYPE_NUMBER,&error);
			x_3 = 		check_parameter(string_array[5] ,PARAMETER_TYPE_NUMBER,&error);
			y_3 = 		check_parameter(string_array[6] ,PARAMETER_TYPE_NUMBER,&error);
			x_4 = 		check_parameter(string_array[7] ,PARAMETER_TYPE_NUMBER,&error);
			y_4 = 		check_parameter(string_array[8] ,PARAMETER_TYPE_NUMBER,&error);
			x_5 = 		check_parameter(string_array[9] ,PARAMETER_TYPE_NUMBER,&error);
			y_5 = 		check_parameter(string_array[10],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[11],PARAMETER_TYPE_COLOR, &error);

			if (aantal_komma < 12)
				weight = 1;
			else
				weight = check_parameter(string_array[12],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_figure(x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4,x_5,y_5,color,weight);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Figuur getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_FIGURE_PARAM_ERROR);
		break;

	case COMMAND_CODE_CIRCLE:
		#ifdef DEBUG
			UartPuts("Cirkel commando gevonden");
		#endif
		if (aantal_komma >= 4 && aantal_komma <= 5)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			radius = 	check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[4],PARAMETER_TYPE_COLOR, &error);

			if (aantal_komma < 5) filled = 0;
			else filled = check_parameter(string_array[5],PARAMETER_TYPE_NUMBER,&error);

			if (!error)
			{
				error = API_draw_circle(x_1,y_1,radius,color,filled);
				ErrorCodeHandler(error);
				#ifdef DEBUG
					UartPuts("Cirkel getekend");
				#endif
				break;
			}
		}
		ErrorCodeHandler(API_CIRCLE_PARAM_ERROR);
		break;

	default:
		ErrorCodeHandler(API_UNKNOWN_COMMAND_ERROR);
		break;
	}
}



char *ltrim(char *str, const char *seps)
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

char *rtrim(char *str, const char *seps)
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

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

int check_commando(char *functie_naam)
{
	//check alle defines
	if(strstr(functie_naam,COMMAND_TEXT_LINE)		!=NULL)	return COMMAND_CODE_LINE;
	if(strstr(functie_naam,COMMAND_TEXT_CLEARSCREEN)!=NULL)	return COMMAND_CODE_CLEARSCREEN;
	if(strstr(functie_naam,COMMAND_TEXT_RECTANGLE)	!=NULL)	return COMMAND_CODE_RECTANGLE;
	if(strstr(functie_naam,COMMAND_TEXT_TEXT)		!=NULL)	return COMMAND_CODE_TEXT;
	if(strstr(functie_naam,COMMAND_TEXT_BITMAP)		!=NULL)	return COMMAND_CODE_BITMAP;
	if(strstr(functie_naam,COMMAND_TEXT_FIGURE)		!=NULL)	return COMMAND_CODE_FIGURE;
	if(strstr(functie_naam,COMMAND_TEXT_CIRCLE)		!=NULL)	return COMMAND_CODE_CIRCLE;
	return 0;
}

int check_parameter(char *parameter, int parameter_type, int *error)
{
	int number;

	switch (parameter_type)
	{
		case PARAMETER_TYPE_NUMBER:
			if(!CharToInt(parameter,&number))
				return number;
			break;

		case PARAMETER_TYPE_COLOR:
			//Kleuren compare
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
			//Font style compare
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
