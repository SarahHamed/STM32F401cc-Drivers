/*
 * Sched.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Sarah
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/Sched/Sched.h"
#include "SYSTICK.h"

extern const TaskInfo_t TasksInfo[];

u8 schedFlag=0;
Task_t tasks[TASKS_NUM];



void sched_vidInit(void)
{
	SYSTICK_vidInit();
	SysTick_enuSetCbf(tickCbf);
	SysTick_enuSetPeriod_ms(TICK);

	for(u8 idx=0;idx<TASKS_NUM;idx++)
	{
		tasks[idx].taskInfo=&TasksInfo[idx];
		tasks[idx].remainTime_ms=TasksInfo[idx].startDelay;
	}
}

void sched_vidStart(void)
{
	SysTick_enuStart();

	while(1)
	{
		if(schedFlag)
		{
			scheduler();
			schedFlag=0;
		}
	}
}

void tickCbf(void)
{
	if(schedFlag==0)
	{
		schedFlag=1;
	}
	else
	{
		/* CPU 100% */
	}
}


static void scheduler(void)
{
	for(u8 idx=0;idx<TASKS_NUM;idx++)
	{
		if(tasks[idx].taskInfo)
		{
			if(tasks[idx].remainTime_ms==0)
			{
				tasks[idx].taskInfo->cbf();
				tasks[idx].remainTime_ms=tasks[idx].taskInfo->period_ms;
			}
			tasks[idx].remainTime_ms -=TICK;
		}
	}
}
