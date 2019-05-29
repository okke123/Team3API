/**
  ******************************************************************************
  * @file    AppUart.c
  * @author  Team 3
  * @date    29-5-2019
  * @brief   This file provides the logical functions for the UART:
  *           - init of the UART.
  *			  - print a char over the UART.
  *			  - print a string over the UART.
  *			  - get a char from the UART.
  *			  - get a string from the UART.
  */

/** @addtogroup Application
 *  @brief	Application used for demo.
 * 	@{
 */

/** @defgroup APP-UART App Uart (IO) Layer
 *  @brief	All the logic functions for the UART.
 * 	@{
 */

/* Includes ------------------------------------------------------------------*/
#include "AppUart.h"


/**
 * @brief	Initializes the USART2 peripheral.
 * @note	This is a wrapper for STM32 USART initialization.
 * @retval	None
 */
void AppUartInit()
{
	/* --------------------------- System Clocks Configuration -----------------*/
	/* USART2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/*-------------------------- GPIO Configuration ----------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);   // USART2_TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX

	USART_InitTypeDef USART_InitStructure;

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
	  - BaudRate = 115200 baud
	  - Word Length = 8 Bits
	  - One Stop Bit
	  - No parity
	  - Hardware flow control disabled (RTS and CTS signals)
	  - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART2, ENABLE);
}

/**
 * @brief	Transmits single data through the USART2 peripheral.
 * @note	This is a wrapper for STM32 USART SendData.
 * @param	c:		The data to transmit.
 * @retval	None
 */
void AppUartPut(char c)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
	USART_SendData(USART2, c);
}

/**
 * @brief	Transmits a string of data through the USART2 peripheral.
 * @note	This is a wrapper for STM32 USART SendData.
 * @param	c:		The string of data to transmit.
 * @retval	None
 */
void AppUartPuts(char* s)
{
	volatile unsigned int i;
	for (i=0; s[i]; i++)
	{
		AppUartPut(s[i]);
	}
	AppUartPut(CR);
	AppUartPut(LF);
}

/**
 * @brief	Return the most recent received data by the USART2 peripheral.
 * @note	This is a wrapper for STM32 USART ReceiveData.
 * @param	None.
 */
char AppUartGet(void)
{
	char c = -1;
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)== SET)  // check for data available
		c &= (char) USART_ReceiveData(USART2);
	return c;
}

/**
 * @brief	Return the most recent received string of data by the USART2 peripheral.
 * @note	This is a wrapper for STM32 USART ReceiveData.

 * @param	s: 		incomming string.
 * @param	echo: 	output-flag what prints the data.

 * @return	error:	gives if the function fails.
 */
int AppUartGets(char* s, int echo)
{
	while (TRUE)
	{
	 	*s = AppUartGet();

	 	if (*s==-1)             // check for data available
	 		continue;

	 	if (*s==0xff || *s==LF) // if no data or LF, continue
			continue;

		if (echo)              	// if output-flag set
			AppUartPut(*s);  	// to read what u entered

		if (*s==CR)            	// if enter pressed
		{
			*s = '\0';         	// ignore char and close string
		    return 0x00;            	// buf ready, exit loop
		}
		s++;
	}

	return 0x03;
}


/**
  * @}
  */

/**
  * @}
  */
