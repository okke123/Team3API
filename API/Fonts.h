#include "stdint.h"

typedef struct FONT_INFO FONT_INFO;
typedef struct FONTS FONTS;

void get_font_info(FONTS *info_array);

/**
	@brief opbouw blauwdruk van de informatie van de fonts. Hierbij wordt de
	breedte en positie / adres opgeslagen. Hierbij wordt het format van
	thedoyfactory gebruikt.
*/
struct FONT_INFO//FONT_INFO
{
	int width;
	int font_adr;
} ;

/**
	@brief opbouw struct voor font. Hierin staat een pointer naar de bitmap en
	een pointer naar de blauwdruk informatie
	@param pointer naar bitmap & blauwdruk voor informatie over struct.
*/
struct FONTS//FONTS
{
 	const struct FONT_INFO *bitmap_info;
	const uint8_t *bitmap;
} ;



