#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "LED.h"
#include "Sched.h"
#include "SYSTICK.h"
#include "LCD.h"


int main(void)
{
	RCC_enuSetPeriStatus(SysBus_AHB1,GPIOAEN_MASK,Peri_StateOn);
	RCC_enuSetPeriStatus(SysBus_AHB1,GPIOBEN_MASK,Peri_StateOn);

	for(u8 pin=0;pin<8;pin++)
	{
		GPIO_enuSetPinDirection(GPIOA, pin, OUTPUT_PUSH_PULL, SPEED_LOW);
	}

	GPIO_enuSetPinDirection(GPIOB, PIN0, OUTPUT_PUSH_PULL, SPEED_LOW);
	GPIO_enuSetPinDirection(GPIOB, PIN1, OUTPUT_PUSH_PULL, SPEED_LOW);
	GPIO_enuSetPinDirection(GPIOB, PIN2, OUTPUT_PUSH_PULL, SPEED_LOW);

	LED_enuInit();

	sched_vidInit();

	sched_vidStart();
	//while(1);
}
