/**
  ******************************************************************************
  * @file    AppUart.h
  * @author  Team 3
  * @date    29-5-2019
  * @brief   The headerfile for the Uart.c and includes relevant files, global defines and functions.
*/

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

/* Functies ------------------------------------------------------------------*/
void AppUartInit();
void AppUartPut(char c);
void AppUartPuts(char* s);
char AppUartGet();
int  AppUartGets(char* s, int echo);

#endif
