/*
 * APP.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Sarah
 */

#include "LED.h"
#include "GPIO.h"
#include "LCD.h"

u8 currentState;
u8 switchState;

void SwitchTask(void)
{
	static u8 counter=0;
	static u8 prevState=0;

	GPIO_enuGetPinValue(GPIOB,PIN7,&currentState);
	if(currentState==prevState)
	{
		counter++;
	}
	else
	{
		counter=0;
	}

	if(counter==5)
	{
		switchState=currentState;
		counter=0;
	}

	prevState=currentState;
}

void App_Runnable1()
{
	static int i=0;
	if(i%2)
	{
		LED_enuSetState(LED_Stop,STATE_OFF);
	}
	else
	{
		LED_enuSetState(LED_Stop,STATE_ON);
	}
	i++;
}

void App_Runnable2()
{
	static int i=0;
	if(i%2)
	{
		LED_enuSetState(LED_Alarm,STATE_OFF);
	}
	else
	{
		LED_enuSetState(LED_Alarm,STATE_ON);
	}
	i++;
}

void App_Runnable3()
{
	static int i=0;
	if(i%2)
	{
		LED_enuSetState(LED_Warning,STATE_OFF);
	}
	else
	{
		LED_enuSetState(LED_Warning,STATE_ON);
	}
	i++;
}

static u8 Switch_getState()
{
	return switchState;
}

void App4(void)
{

	if(Switch_getState()==1)
	{
		LED_enuSetState(LED_Start,STATE_ON);
	}
	else
	{
		LED_enuSetState(LED_Start,STATE_OFF);
	}
}



void AppLcd()
{
	static int counter;
	static u8 x=0;
	if(counter%2==0)
	{
		LCD_enuWriteStringAsync("Salma ",6 ,0,0);
		/*x++;
		if(x==6)
		{
			x=0;
		}
		*/
	}
	else
	{
		//LCD_clearScreen();
	}

	counter++;
}
