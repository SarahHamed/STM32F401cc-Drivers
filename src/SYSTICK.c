/*
 * SYSTICK.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Sarah
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "SYSTICK.h"


SysTick_t *const Systick = (SysTick_t *)0xE000E010;
static notification_t notifyApp;


void SYSTICK_vidInit()
{
	u32 CTRL=Systick->STK_CTRL;
	/* Set Interrupt*/
	#if INT_STATE==INT_ON
		CTRL&=~STK_CTRL_TICKINT;
		CTRL|=STK_CTRL_TICKINT;
	#elif
		CTRL&=~STK_CTRL_TICKINT;
	#endif

	/* Set Clock */
	#if CLKSOURCE_SEL == CLKSOURCE_AHB_8
		CTRL&=~STK_CTRL_CLKSOURCE;
	#elif CLKSOURCE_SEL == CLKSOURCE_AHB
		CTRL&=~STK_CTRL_CLKSOURCE;
		CTRL|=STK_CTRL_CLKSOURCE;
	#endif

		Systick->STK_CTRL=CTRL;
}

SysTickErrStatus_t SysTick_enuStart(void)
{
	SysTickErrStatus_t Loc_errStatus=SysTick_enuOk;

	/* Enable */
	Systick->STK_VAL=0;
	Systick->STK_CTRL|=STK_CTRL_ENABLE;
	return Loc_errStatus;  //??????????
}

SysTickErrStatus_t SysTick_enuStop(void)
{
	SysTickErrStatus_t Loc_errStatus=SysTick_enuOk;

	Systick->STK_LOAD=0;
	Systick->STK_VAL=0;
	/*Disable*/
	Systick->STK_CTRL&=~STK_CTRL_ENABLE;

	return Loc_errStatus;
}


SysTickErrStatus_t SysTick_enuSetPeriod_us(u32 copy_u32Perid_Ms)
{
	SysTickErrStatus_t Loc_errStatus=SysTick_enuOk;

	u32 Loc_u32Counts=copy_u32Perid_Ms*SYS_CLOCK;
	Systick->STK_LOAD=Loc_u32Counts;


	return Loc_errStatus;
}

SysTickErrStatus_t SysTick_enuSetPeriod_ms(u32 copy_u32Perid_ms)
{
	SysTickErrStatus_t Loc_errStatus=SysTick_enuOk;

	u32 Loc_u32Counts=(copy_u32Perid_ms*1000)*SYS_CLOCK;
	Systick->STK_LOAD=Loc_u32Counts;


	return Loc_errStatus;
}

SysTickErrStatus_t SysTick_enuSetCbf(notification_t notifyFunc)
{
	SysTickErrStatus_t Loc_errStatus=SysTick_enuOk;
	if(notifyFunc)
	{
		notifyApp=notifyFunc;
	}
	else
	{
		Loc_errStatus=SysTick_enuNullPtr;
	}

	return Loc_errStatus;
}

void SysTick_Handler (void)
{
	if(notifyApp)
	{
		notifyApp();
	}
}

void setBusy(u32 copy_u32Ticks)
{
	SysTick_enuSetPeriod_ms(copy_u32Ticks);

	/* Enable the Timer */
	SysTick_enuStart();

	/*Polling on the flag of the timer*/
	while((Systick->STK_CTRL&STK_CTRL_COUNTFLAG_MASK)==0 );

	/* Disable the counter */
	CLR_BIT(Systick->STK_CTRL, STK_CTRL_ENABLE_BIT);

	/* update the pre-load value with 0 */
	Systick->STK_LOAD=0;
	Systick->STK_VAL=0;
}

