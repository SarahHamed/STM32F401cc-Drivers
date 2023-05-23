/*
 * UART.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Sarah
 */

#ifndef UART_H_
#define UART_H_

#include "STD_TYPES.h"

#define TC_MASK	0x00000040
#define USART_SR_TC	6

#define TXE		7
#define RXNE	5
#define USART_CR1_UE	13
#define USART_CR1_M		12	//data length
#define USART_CR1_PCE	10
#define USART_CR1_PS	9
#define USART_CR1_TE	3
#define USART_CR1_RE	2

#define USART_CR2_STOP_BIT_12	12	// 12 &13 ?????????????
#define USART_CR2_STOP_BIT_13	13
//0x4001 1000 - 0x4001 13FF USART1
//APB2
typedef struct{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;
}UART_t;


/*
void UART_vidSend(u8 data);
u8 UART_vdReceive();
void UART_vid_Initialize();
*/

void UART_vidInit(void);
void UART_vidTransmit(u8 *data);
u8 UART_u8Receive(void);

#endif /* UART_H_ */
