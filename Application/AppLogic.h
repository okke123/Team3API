#ifndef __APP_LOGIC_H
#define __APP_LOGIC_H

#include "AppUart.h"
#include "VgaLogic.h"

#define NUM_SET "0123456789"
#define DELIMITER ","

int CharToInt(char* src, int error);

void StrSplit(char* src, char* dest, int error);

void CreateObject(char* src, int error);

#endif
