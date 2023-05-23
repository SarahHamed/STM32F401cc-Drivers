/*
 * SYSTICK.h
 *
 *  Created on: Mar 23, 2023
 *      Author: Sarah
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


typedef void (*notification_t)(void);

#define STK_CTRL_ENABLE		0x00000001
#define STK_CTRL_TICKINT	0x00000002
#define STK_CTRL_CLKSOURCE	0x00000004

#define STK_CTRL_COUNTFLAG_BIT	16
#define STK_CTRL_ENABLE_BIT	0

#define STK_CTRL_COUNTFLAG_MASK	0x00010000


#define CLKSOURCE_SEL	CLKSOURCE_AHB_8
#define	CLKSOURCE_AHB_8	0
#define	CLKSOURCE_AHB	1


#define CLKSRC_SEL	CLKSRC_HSI_AHB_8
#define	CLKSRC_HSI_AHB_8	0
#define	CLKSRC_HSI_AHB		1
#define	CLKSRC_HSE_AHB_8	2
#define	CLKSRC_HSE_AHB		3

/* In Case of Internal Clock */
#if	CLKSRC_SEL==CLKSRC_HSI_AHB
	#define SYS_CLOCK 	16	//?????????
#elif CLKSRC_SEL==CLKSRC_HSI_AHB_8
	#define SYS_CLOCK 	2
#elif	CLKSRC_SEL==CLKSRC_HSE_AHB_8
	#define SYS_CLOCK	3.125
#elif	CLKSRC_SEL==CLKSRC_HSE_AHB
	#define SYS_CLOCK	25
#endif

#define INT_STATE	INT_ON
#define INT_ON	1
#define INT_OFF	0

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}SysTick_t;


typedef enum
{
	SysTick_enuOk,
	SysTick_enuNok,
	SysTick_enuNullPtr
}SysTickErrStatus_t;

void SYSTICK_vidInit();
SysTickErrStatus_t SysTick_enuStart(void);
SysTickErrStatus_t SysTick_enuStop(void);
SysTickErrStatus_t SysTick_enuSetCbf(notification_t notifyFunc);
SysTickErrStatus_t SysTick_enuSetPeriod_us(u32 copy_u32Perid_Ms);
SysTickErrStatus_t SysTick_enuSetPeriod_ms(u32 copy_u32Perid_ms);
void setBusy(u32 copy_u32Ticks);
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */

