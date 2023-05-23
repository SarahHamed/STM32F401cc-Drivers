/*
 * Sched_Cfg.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Sarah
 */



#include "../include/LIB/STD_TYPES.h"
#include "../include/Sched/Sched.h"
#include "../include/MCAL/SYSTICK/SYSTICK.h"
#include "GPIO.h"
#include "LED.h"
#include "LCD.h"


extern void SwitchTask(void);
extern void App_Runnable1();

extern void App_Runnable2();
extern void App_Runnable3();
//extern u8 Switch_getState();
extern void App4(void);
extern void AppLcd();
extern void lcdTask();

const TaskInfo_t TasksInfo[]={
		[0]={
				.name="task0",
				.cbf=App_Runnable1,
				.period_ms=500,
				.startDelay=1000,
				.priority=1,
		},
		[1]={
				.name="task1",
				.cbf=App_Runnable2,
				.period_ms=500,
				.startDelay=2000,
				.priority=2,
				},
		[2]={
				.name="task2",
				.cbf=App_Runnable3,
				.period_ms=500,
				.startDelay=3000,
				.priority=3,
				},

		[3]={
				.name="task3",
				.cbf=SwitchTask,
				.period_ms=5,
				.startDelay=0,
				.priority=0,
				},

		[4]={
				.name="task4",
				.cbf=App4,
				.period_ms=10,
				.startDelay=0,
				.priority=0,
				},
		[5]={
				.name="task5",
				.cbf=AppLcd,
				.period_ms=1000,
				.startDelay=500,
				.priority=0,
		},
		[6]={
				.name="task6",
				.cbf=lcdTask,
				.period_ms=2,
				.startDelay=0,
				.priority=0,
				}
};


