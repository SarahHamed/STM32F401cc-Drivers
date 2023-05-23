/*
 * LED.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Sarah
 */


//#include <HAL/LED/LED.h>
//#include <HAL/LED/LED_Cfg.h>
//#include "STD_TYPES.h"
#include "math.h"
#include "GPIO.h"
#include "../include/MCAL/RCC/RCC.h"
#include "LED.h"
#include "LED_Cfg.h"

void LED_enuInit()
{
	GPIO_Cfg Led_Cfg;
	//RCC_enuSetPeriStatus(SysBus_AHB1,GPIOAEN_MASK,Peri_StateOn);

	for(u8 i=0;i<LED_Count;i++)
	{
		Led_Cfg.Port  = ledCfg[i].Port;
		Led_Cfg.Pin   = ledCfg[i].Pin;
		Led_Cfg.Mode  = OUTPUT_PUSH_PULL;
		//Led_Cfg.Mode  = OUTPUT_PUSH_PULL_PULL_UP;
		Led_Cfg.Speed = ledCfg[i].Speed;
		GPIO_enuInitPin(&Led_Cfg);
	}
}



LedErrStatus_t LED_enuSetState(LED_t copy_enuLed,u8 copy_u8State)
{
	LedErrStatus_t errStatus;

	errStatus=GPIO_enuSetPinValue(ledCfg[copy_enuLed].Port, ledCfg[copy_enuLed].Pin,copy_u8State^ledCfg[copy_enuLed].Mode);

	return errStatus;
}
