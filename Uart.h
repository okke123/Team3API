#ifndef __UART_H
#define __UART_H

#include "stm32f4xx_usart.h"

#define CR 13				// carriage return char
#define LF 10				// linefeed char
#define UART_BAUDRATE 9600	// baudrate value
#define TRUE 1
#define FALSE 0

void UartInit(int baudrate);
void UartPut(char c);
void UartPuts(char* s);
char UartGet();
void UartGets(char* s, int echo);

#endif
