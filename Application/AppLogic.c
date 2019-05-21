/*!
 *	/arthur Chileam Bohnen
 *	/version 0.1
 *	/date 2019-5-1
 *	/mainpage Logic Layer
 *		Command parser for VGA API
 */

#include "AppLogic.h"
#include <String.h>

//Vullen van structs
void fill_text_struct(struct struct_text  *pstr, char *pstring_array[])
{
	pstr->x_lup  		= atoi(pstring_array[1]);	//x
	pstr->y_lup  		= atoi(pstring_array[2]);	//y
	pstr->color 		= string_to_kleur(pstring_array[3]);
	pstr->text			= pstring_array[4];
	pstr->fontname   	= pstring_array[5];
}

void fill_rectangle_struct(struct struct_rectangle *pstr, char *pstring_array[])
{
  pstr->x_lup   = atoi(pstring_array[1]);
  pstr->y_lup   = atoi(pstring_array[2]);
  pstr->x_rdown = atoi(pstring_array[3]);
  pstr->y_rdown = atoi(pstring_array[4]);
  pstr->color   = string_to_kleur(pstring_array[5]);
  pstr->style   = atoi(pstring_array[6]);
}

void fill_bitmap_struct(struct struct_bitmap  *pstr, char *pstring_array[])
{
  pstr->x_lup   = atoi(pstring_array[1]);
  pstr->y_lup   = atoi(pstring_array[2]);
  pstr->bm_nr   = atoi(pstring_array[3]);
}

void fill_clearscherm_struct(struct struct_clearscherm  *pstr, char *pstring_array[])
{
  pstr->color   = atoi(pstring_array[1]);
}

int CharToInt(char* src, int error)
{
	int value = -1;

	if (strpbrk(src, NUM_SET))
	{
		error = 0x00;
		return atoi(src);
	}
	else
	{
		error = 0x10;
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
		string_array[i] = token;

	//check functie_namen, return waarde voor de switch case.
	int commando_value = check_commando(string_array[0]);

	if(commando_value>0)
	{
	//pointer naar de desbetreffende struct;
	switch (commando_value) {
		case 1: //LIJN
		// 	struct struct_lijn lijntje;
			call_line(string_array);
			break;
			/*
		case 2:	//CLEARSCHERM
			fill_clearscherm_struct(&clearscherm, string_array);
			if(clearscherm.color==0x02) Logic_Layer_foutmelding(1);	//kleur fout.
			break;
		case 3:	//RECHTHOEK
			fill_rectangle_struct(&rectangle, string_array);
			if(rectangle.color==0x02) Logic_Layer_foutmelding(1);	//kleur fout.
			break;
			*/
		case 4: //TEKST
			//fill_text_struct(&text, string_array);
			//if(text.color==0x02) Logic_Layer_foutmelding(1);		//kleur fout.
			call_text(string_array);
			break;
			/*
		case 5:	//BITMAP
			fill_bitmap_struct(&bitmap, string_array);
			break;
			*/
		default:
			foutmeldings_error_logic(3);	//Iets fout gegaan met het maken van struct.
			break;
	}
	}
	else
	{
		foutmeldings_error_logic(3);
		//TODO: Foutmelding terug naar de visual layer
	}
}


int check_commando(char *functie_naam)
{
	//check alle defines
	if(strstr(functie_naam,LIJN)!=NULL)			return 1;
	if(strstr(functie_naam,CLEARSCHERM)!=NULL)	return 2;
	if(strstr(functie_naam,RECHTHOEK)!=NULL)	return 3;
	if(strstr(functie_naam,TEKST)!=NULL)		return 4;
	if(strstr(functie_naam,BITMAP)!=NULL)		return 5;
	return 0;
}

int foutmeldings_error_logic(int fout)
{
	int foutmelding;
	switch (fout) {
		case 1:
			//Foute commando
			foutmelding = "Onbekende kleur ingevoerd";
			break;
		case 2:
			//Fout parameters
			foutmelding = "verkeerde parameters ingevoerd";
		case 3:
			//Struct is niet gemaakt
			foutmelding = "Struct is niet gemaakt";
		case 4:
			//Tekst buiten het figuur
			foutmelding = "De tekst moet binnen het scherm passen";
		case 5:
			//Ingevulde functie bestaat niet.
			foutmelding = "De ingevoerde functie bestaat niet";
		default:
			return 0;
	}
	//TODO: foutmelding doorsturen naar frontlayer.
	//frontlayer
}

void Logic_Layer_foutmelding(int fout)
{
	//foutmelding
}

int string_to_kleur(char *kleur)
{
	if(strcmp(kleur,"zwart")		==0)	return VGA_COL_BLACK;
	if(strcmp(kleur,"blauw")		==0) 	return VGA_COL_BLUE;
	if(strcmp(kleur,"lichtblauw")	==0) 	return VGA_COL_LIGHT_BLUE;
	if(strcmp(kleur,"groen")		==0) 	return VGA_COL_GREEN;
	if(strcmp(kleur,"lichtgroen") 	==0) 	return VGA_COL_LIGHT_GREEN;
	if(strcmp(kleur,"cyaan")		==0) 	return VGA_COL_CYAN;
	if(strcmp(kleur,"lichtcyaan")	==0) 	return VGA_COL_LIGHT_CYAN;
	if(strcmp(kleur,"rood") 		==0) 	return VGA_COL_RED;
	if(strcmp(kleur,"lichtrood") 	==0) 	return VGA_COL_LIGHT_RED;
	if(strcmp(kleur,"magenta")		==0)	return VGA_COL_MAGENTA;
	if(strcmp(kleur,"lichtmagenta")	==0)	return VGA_COL_LIGHT_MAGENTA;
	if(strcmp(kleur,"bruin")		==0) 	return VGA_COL_BROWN;
	if(strcmp(kleur,"geel")			==0)	return VGA_COL_YELLOW;
	if(strcmp(kleur,"wit")  		==0) 	return VGA_COL_WHITE;
	if(strcmp(kleur,"roze")			==0) 	return VGA_COL_PINK;

	//Als er wat fout is gegaan
	return 0x02;
}

void call_line(char *pstring_array)
{
	API_draw_line(	atoi(pstring_array[1]),
					atoi(pstring_array[2]),
					atoi(pstring_array[3]),
					atoi(pstring_array[4]),
					string_to_kleur(pstring_array[5]),
					atoi(pstring_array[6]),
					atoi(pstring_array[7]));
}

void call_text(char *pstring_array)
{
	API_draw_text(	atoi(pstring_array[1]),	//x1
					atoi(pstring_array[2]),	//y1
					string_to_kleur(pstring_array[3]), //kleur
					pstring_array[4],	//string
					pstring_array[5],	//fontnaam
					atoi(pstring_array[6]),	//fontsize
					atoi(pstring_array[7]),	//fontstyle
					0);						//reserved
}
