#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

/* Defines ------------------------------------------------------------------*/
#define CR		13				// carriage return char
#define LF		10				// linefeed char
#define TRUE	1				// boolean value true
#define FALSE	0				// boolean value false

void UartInit();
void UartPut(char c);
void UartPuts(char* s);
char UartGet();
int UartGets(char* s, int echo);

#endif
