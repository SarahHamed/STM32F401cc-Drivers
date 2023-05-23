/*
 * LED_Cfg.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Sarah
 */


//#include <HAL/LED/LED_Cfg.h>
//#include "STD_TYPES.h"
#include "GPIO.h"
#include "LED.h"
#include "LED_Cfg.h"

const LedCfg_t ledCfg[LED_Count]={

		[LED_Alarm]={
				.Port=GPIOB,
				.Pin=PIN3,
				.Mode=ACTIVE_HIGH,
				.Speed=SPEED_LOW,
				.Name="Alarm Led"
		},
		[LED_Stop]={
				.Port=GPIOB,
				.Pin=PIN4,
				.Mode=ACTIVE_HIGH,
				.Speed=SPEED_LOW,
				.Name="Stop Led"},
		[LED_Warning]={
				.Port=GPIOB,
				.Pin=PIN5,
				.Mode=ACTIVE_HIGH,
				.Speed=SPEED_LOW,
				.Name="Warning Led"},

		[LED_Start]={
				.Port=GPIOB,
				.Pin=PIN6,
				.Mode=ACTIVE_HIGH,
				.Speed=SPEED_LOW,
				.Name="Start Led"},

};
