/*
 * Sched.h
 *
 *  Created on: Mar 31, 2023
 *      Author: Sarah
 */

#ifndef SCHED_H_
#define SCHED_H_



#define TICK	1	//assume 1ms
#define TASKS_NUM	7

typedef void (*taskCbf_t)(void);

typedef struct
{
	char *name;
	taskCbf_t cbf;
	u32 period_ms;
	u32 startDelay;
	u32 priority;
}TaskInfo_t;


typedef struct
{
	TaskInfo_t *taskInfo;
	u32 remainTime_ms;
}Task_t;

void sched_vidInit(void);
void sched_vidStart(void);
void tickCbf(void);
static void scheduler(void);
//void sched_vidPauseRunnable(runnableHandle,u32 time_ms);

#endif /* SCHED_H_ */
