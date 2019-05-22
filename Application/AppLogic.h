#ifndef __APP_LOGIC_H
#define __APP_LOGIC_H

#include "AppUart.h"
#include "VgaLogic.h"

#define NUM_SET "0123456789"
#define DELIMITER ","


#define PARAMETER_TYPE_NUMBER 1
#define PARAMETER_TYPE_COLOR 2
#define PARAMETER_TYPE_FONT_STYLE 3


#define CMD_LIJN "lijn"               //er  01
#define CMD_CLEARSCHERM "clearscherm" //er  02
#define CMD_RECHTHOEK "rechthoek"     //er  03
#define CMD_TEKST "tekst"             //er  04
#define CMD_BITMAP "bitmap"           //er  05
#define CMD_FIGUUR "figuur"           //er  06
#define CMD_CIRKEL "cirkel"           //er  07

int CharToInt(char* src, int *error);

void StrSplit(char* src, char* dest, int error);

void CreateObject(char* src, int error);

void StringHandler(char *str_inkomend);

char *trim(char *str, const char *seps);

#endif
