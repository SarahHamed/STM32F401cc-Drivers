/*
 * LED.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Sarah
 */

#ifndef LED_H_
#define LED_H_

#include "STD_TYPES.h"

#define ACTIVE_HIGH		0
#define ACTIVE_LOW		1

#define STATE_ON	1
#define STATE_OFF	0

typedef enum
{
	LED_Ok,
	LED_Nok
}LedErrStatus_t;

typedef enum
{
	LED_Alarm,
	LED_Stop,
	LED_Warning,
	LED_Start,
	LED_Count
}LED_t;


void LED_enuInit();
LedErrStatus_t LED_enuSetState(LED_t copy_enuLed,u8 copy_u8State);



#endif /* LED_H_ */
