/*!
 *	/arthur Chileam Bohnen
 *	/version 0.1
 *	/date 2019-5-1
 *	/mainpage Logic Layer
 *		Command parser for VGA API
 */

#include "AppLogic.h"

#include "stdlib.h"
#include "ctype.h"
#include "stdio.h"
#include "string.h"

int check_commando(char *functie_naam);

int check_parameter(char *parameter, int parameter_type, int *error);

int CharToInt(char* src, int *error)
{
	int value = -1;
//TODO: Maak werkend met min getallen en als de string begint met een letter (bijvb. "50f")
	if (strpbrk(src, NUM_SET))
	{
		*error = 0x00;
		return atoi(src);
	}
	else
	{
		*error = 0x10;
		return value;
	}
}

void StrSplit(char* src, char* dest, int error)
{
	if ((dest = strtok(src, DELIMITER)) == NULL)
	{
		error = 0x10;
		return;
	}
	error = 0x00;
}


void StringHandler(char *str_inkomend)
{
	//Aantal tekens in de inkomende string
	int aantal_tek;
	for(aantal_tek=0;*(str_inkomend+aantal_tek)!='\0';aantal_tek++);

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
	for (i=0;i<=aantal_komma;i++)
	{
		UartPuts(string_array[i]);
	}

	int error = 0;
	int x_1,x_2,x_3,x_4,x_5;
	int y_1,y_2,y_3,y_4,y_5;
	int color,bordercolor,radius,weight,width,height,fontsize,fontstyle,reserved,filled,bm_nr;

	switch (check_commando(string_array[0]))
	{
	case 1:	//LIJN Commando
		//UartPuts("lijn commando gevonden!");
		if (aantal_komma==6 || aantal_komma==7)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			x_2 = 		check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			y_2 = 		check_parameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			weight = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (aantal_komma==6) reserved = 0;
			else reserved = check_parameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);

			if (error==0)
			{
				API_draw_line(x_1,y_1,x_2,y_2,color,weight,reserved);
				UartPuts("Lijn getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 2: //Clearscherm
		if (aantal_komma==1)
		{
			color =  	check_parameter(string_array[1],PARAMETER_TYPE_COLOR, &error);

			if (error==0)
			{
				API_clearscreen(color);
				UartPuts("Scherm gevuld");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 3: //Rechthoek
		if (aantal_komma >= 6 && aantal_komma <= 8)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			width = 	check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			height = 	check_parameter(string_array[4],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[5],PARAMETER_TYPE_COLOR, &error);
			filled = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);

			if (aantal_komma < 8)
			{
				bordercolor = 0;
				if (aantal_komma < 7)
					weight = 1;
				else
					weight = check_parameter(string_array[7],PARAMETER_TYPE_NUMBER,&error);
			}
			else
				bordercolor = check_parameter(string_array[8],PARAMETER_TYPE_NUMBER,&error);


			if (error==0)
			{
				API_draw_rectangle(x_1,y_1,width,height,color,filled,weight,bordercolor);
				UartPuts("Rechthoek getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 4: //Tekst
		if (aantal_komma >= 7 && aantal_komma <= 8)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[3],PARAMETER_TYPE_COLOR, &error);
			//tekst
			//font
			fontsize = 	check_parameter(string_array[6],PARAMETER_TYPE_NUMBER,&error);
			fontstyle = check_parameter(string_array[7],PARAMETER_TYPE_FONT_STYLE,&error);

			if (aantal_komma < 8) reserved = 0;
			else reserved = check_parameter(string_array[8],PARAMETER_TYPE_NUMBER,&error);

			if (error==0)
			{
				API_draw_text(x_1,y_1,color,string_array[4],fontstyle);
				//API_draw_text(x_1,y_1,color,string_array[4],string_array[5],fontsize,fontstyle,reserved);
				UartPuts("Tekst getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 5: //Bitmap
		if (aantal_komma == 3)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			bm_nr =  	check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);

			if (error==0)
			{
				//TODO: comment out
				//API_draw_bitmap(x_1,y_1,bm_nr);
				UartPuts("Bitmap getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 6: //Figuur
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

			if (aantal_komma < 12) weight = 1;
			else weight = check_parameter(string_array[12],PARAMETER_TYPE_NUMBER,&error);

			if (error==0)
			{
				API_draw_figure(x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4,x_5,y_5,color,weight);
				UartPuts("Figuur getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;

	case 7: //Cirkel
		if (aantal_komma >= 4 && aantal_komma <= 5)
		{
			x_1 = 		check_parameter(string_array[1],PARAMETER_TYPE_NUMBER,&error);
			y_1 = 		check_parameter(string_array[2],PARAMETER_TYPE_NUMBER,&error);
			radius = 	check_parameter(string_array[3],PARAMETER_TYPE_NUMBER,&error);
			color =  	check_parameter(string_array[4],PARAMETER_TYPE_COLOR, &error);

			if (aantal_komma < 5) filled = 0;
			else filled = check_parameter(string_array[5],PARAMETER_TYPE_NUMBER,&error);

			if (error==0)
			{
				API_draw_circle(x_1,y_1,radius,color,filled);
				UartPuts("Cirkel getekend");
				break;
			}
		}
		UartPuts("ERROR IN PARAMETERS!");
		break;




	default:
		UartPuts("Geen commando gevonden");
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
	if(strstr(functie_naam,CMD_LIJN)!=NULL)			return 1;
	if(strstr(functie_naam,CMD_CLEARSCHERM)!=NULL)	return 2;
	if(strstr(functie_naam,CMD_RECHTHOEK)!=NULL)	return 3;
	if(strstr(functie_naam,CMD_TEKST)!=NULL)		return 4;
	if(strstr(functie_naam,CMD_BITMAP)!=NULL)		return 5;
	if(strstr(functie_naam,CMD_FIGUUR)!=NULL)		return 6;
	if(strstr(functie_naam,CMD_CIRKEL)!=NULL)		return 7;
	return 0;
}

int check_parameter(char *parameter, int parameter_type, int *error)
{
	int number;
	int internal_error = 0;

	switch (parameter_type)
	{
		case PARAMETER_TYPE_NUMBER:
			number = CharToInt(parameter,&internal_error);
			if (internal_error == 0)
				return number;
			break;
		case PARAMETER_TYPE_COLOR:
			//Kleuren compare
			if(strcmp(parameter,"zwart")		==0)	return VGA_COL_BLACK;
			if(strcmp(parameter,"blauw")		==0) 	return VGA_COL_BLUE;
			if(strcmp(parameter,"lichtblauw")	==0) 	return VGA_COL_LIGHT_BLUE;
			if(strcmp(parameter,"groen")		==0) 	return VGA_COL_GREEN;
			if(strcmp(parameter,"lichtgroen") 	==0) 	return VGA_COL_LIGHT_GREEN;
			if(strcmp(parameter,"cyaan")		==0) 	return VGA_COL_CYAN;
			if(strcmp(parameter,"lichtcyaan")	==0) 	return VGA_COL_LIGHT_CYAN;
			if(strcmp(parameter,"rood") 		==0) 	return VGA_COL_RED;
			if(strcmp(parameter,"lichtrood") 	==0) 	return VGA_COL_LIGHT_RED;
			if(strcmp(parameter,"magenta")		==0)	return VGA_COL_MAGENTA;
			if(strcmp(parameter,"lichtmagenta")	==0)	return VGA_COL_LIGHT_MAGENTA;
			if(strcmp(parameter,"bruin")		==0) 	return VGA_COL_BROWN;
			if(strcmp(parameter,"geel")			==0)	return VGA_COL_YELLOW;
			if(strcmp(parameter,"wit")  		==0) 	return VGA_COL_WHITE;
			if(strcmp(parameter,"roze")			==0) 	return VGA_COL_PINK;
			break;
		case PARAMETER_TYPE_FONT_STYLE:
			//Font style compare
			if(strcmp(parameter,"normaal")	==0)	return 2;
			if(strcmp(parameter,"vet")		==0) 	return 0;
			if(strcmp(parameter,"cursief")	==0) 	return 1;
			break;

		default:
			break;
	}
	*error |= 0x11;
	return 0;
}
