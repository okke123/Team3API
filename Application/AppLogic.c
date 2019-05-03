/*!
 *	/arthur Chileam Bohnen
 *	/version 0.1
 *	/date 2019-5-1
 *	/mainpage Logic Layer
 *		Command parser for VGA API
 */

#include "AppLogic.h"


int CharToInt(char* src, int error)
{
	int value = -1;

	if (strpbrk(src, NUM_SET))
	{
		error = 0x00;
		return atoi(src);
	} else {
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
