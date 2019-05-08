#ifndef __APP_FRONT_H
#define __APP_FRONT_H

#include <stdint.h>

typedef struct {
	uint8_t *command;
	uint8_t length;
} msg_typedef;

int MessageToCommand(uint8_t* msg, msg_typedef* MSG_command);
void ErrorCodeHandler(uint8_t error, uint8_t* error_msg);

#endif
