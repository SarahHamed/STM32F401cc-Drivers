/*
 * UART.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Sarah
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART.h"


UART_t *const UART = (UART_t*) 0x40011000; //0x4001 1000

/*
void UART_vidSend(u8 data)
{
	while(GET_BIT(UART->USART_SR,TXE)==0);
	UART->USART_DR=data;
}


u8 UART_vdReceive()
{
	while(GET_BIT(UART->USART_SR,RXNE)==0);

	return UART->USART_DR;
}

void UART_vid_Initialize()
{


	//u8 my_ucsrc=0;
	//8 bit data
	CLR_BIT(UART->USART_CR1,USART_CR1_M);
	//NO PARITY
	CLR_BIT(UART->USART_CR1,USART_CR1_PCE);


	// one stop bit
	CLR_BIT(UART->USART_CR2,USART_CR2_STOP_BIT_12);
	CLR_BIT(UART->USART_CR2,USART_CR2_STOP_BIT_13);

	//baud rate 9600 in case of clk 16M and
	UART->USART_BRR=0x68<<4|3;
	//enable rec and trans
	//BIT_SET(UCSRB,UCSRB_RXEN);

	SET_BIT(UART->USART_CR1,USART_CR1_TE);
	SET_BIT(UART->USART_CR1,USART_CR1_UE);
}

*/


void UART_vidInit(void)
{
	//8 bit data
	CLR_BIT(UART->USART_CR1,USART_CR1_M);

	//NO PARITY
	CLR_BIT(UART->USART_CR1,USART_CR1_PCE);

	// one stop bit
	CLR_BIT(UART->USART_CR2,USART_CR2_STOP_BIT_12);
	CLR_BIT(UART->USART_CR2,USART_CR2_STOP_BIT_13);

	/* 9600   BRR=0x683 */
	/* 115200 BRR=0x8B  */
	UART->USART_BRR=0x683;

	/*
	1- Enable RX
	2- Enable TX
	3- Enable USART
	*/

	SET_BIT(UART->USART_CR1,USART_CR1_RE);
	SET_BIT(UART->USART_CR1,USART_CR1_TE);
	SET_BIT(UART->USART_CR1,USART_CR1_UE);

	/* Clear Status Registers */
	UART->USART_SR=0x00000000;
}


void UART_vidTransmit(u8 *data)
{
	u8 i=0;
	while(data[i]!='\0')
	{
		UART->USART_DR=data[i];
		while((UART->USART_SR&TC_MASK)==0);
		i++;
	}

}


u8 UART_u8Receive(void)
{
	u8 data;
	while((UART->USART_SR & (1<<RXNE))==0);
	data=UART->USART_DR & 0xff;
	return data;
}
