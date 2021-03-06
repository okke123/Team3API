#include "VgaLogic.h"

/**
	@brief opbouw blauwdruk van de informatie van de fonts. Hierbij wordt de
	breedte en positie / adres opgeslagen. Hierbij wordt het format van
	thedoyfactory gebruikt.
*/
typedef struct //FONT_INFO
{
	int width;
	int font_adr;
}	FONT_INFO;

/**
	@brief opbouw struct voor font. Hierin staat een pointer naar de bitmap en
	een pointer naar de blauwdrukinformatie.
*/
typedef struct	//FONTS
{
 	const FONT_INFO *bitmap_info;
	const uint8_t *bitmap;
} FONTS;

extern FONTS fonts[];
