/*!
 *	/arthur Chileam Bohnen
 *	/version 0.1
 *	/date 2019-5-1
 *	/mainpage Logic Layer
 *		Command parser for VGA API
 */

#include "AppLogic.h"


int CharToInt(char* src, int* value)
{
	int fault_counter = 0;
	int i = 0, j;

	if (src[i] == '-')
		i = 1;

	for (; i < strlen(src); i++)
		for (j = 0; j < strlen(NUM_SET); j++)
		{
			if (src[i] != *(NUM_SET + j)) {
				fault_counter++;
			} else {
				break;
			}

		}

	if (fault_counter >= 10)
	{
		*value = 0;
		return API_COMMAND_READ_ERROR;
	}

	*value = atoi(src);
	return API_NONE_ERROR;
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
