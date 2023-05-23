/*
 * NVIC.h
 *
 *  Created on: Mar 16, 2023
 *      Author: Sarah
 */

#ifndef NVIC_H_
#define NVIC_H_

#define REG_WIDTH	32
#define INT_MAX_ID 244

#define SCB_AIRCR *((volatile u32 *)0xE000ED0C)

#define	VECTKEYSTAT	0x05FA

#define NVIC_GROUP_SUB_DIV	NVIC_GROUP_0_SUB_4
#define NVIC_GROUP_4_SUB_0	 0x05FA0000
#define NVIC_GROUP_3_SUB_1	 0x05FA0400
#define NVIC_GROUP_2_SUB_2	 0x05FA0500
#define NVIC_GROUP_1_SUB_3	 0x05FA0600
#define NVIC_GROUP_0_SUB_4	 0x05FA0700


#define PRIORITY_0 0
#define PRIORITY_1 1
#define PRIORITY_2 2
#define PRIORITY_3 3
#define PRIORITY_4 4
#define PRIORITY_5 5
#define PRIORITY_6 6
#define PRIORITY_7 7
#define PRIORITY_8 8
#define PRIORITY_9 9
#define PRIORITY_10 10
#define PRIORITY_11 11
#define PRIORITY_12 12
#define PRIORITY_13 13
#define PRIORITY_14 14
#define PRIORITY_15 15

#define MAX_IPR_BYTE_ACCESS	240
#define MST_SIG_SHIFT	4

typedef struct
{
	volatile u32 NVIC_ISER[8];
	volatile u32 NVIC_RESERVED0[24];
	volatile u32 NVIC_ICER[8];
	volatile u32 NVIC_RESERVED1[24];
	volatile u32 NVIC_ISPR[8];
	volatile u32 NVIC_RESERVED2[24];
	volatile u32 NVIC_ICPR[8];
	volatile u32 NVIC_RESERVED3[24];
	volatile u32 NVIC_IABR[8];
	volatile u32 NVIC_RESERVED4[32];
	volatile u8 NVIC_IPR[240];	//Address offset: 0x400 + 0x04 * x, (x = 0 to 59)

	//volatile u32 NVIC_IABR[60];
}NVIC_t;


typedef enum
{
	NVIC_Ok,
	NVIC_Nok,
	NVIC_InvalidIntID,
	NVIC_InvalidVal
}NVIC_tenuErrorStatus;


NVIC_tenuErrorStatus NVIC_enuEnableInterrupt(u8 Copy_u8IntID);
NVIC_tenuErrorStatus NVIC_enuDisableInterrupt(u8 Copy_u8IntID);

NVIC_tenuErrorStatus NVIC_enuSetPending(u8 Copy_u8IntID);
NVIC_tenuErrorStatus NVIC_enuClearPending(u8 Copy_u8IntID);

NVIC_tenuErrorStatus NVIC_enuGetActive(u8 Copy_u8IntID, u8 *Add_pu8ActiveState);

NVIC_tenuErrorStatus NVIC_enuSetSubGroupPriorityBits(u32 Copy_GROUP_Priority_SUB_Priority);

NVIC_tenuErrorStatus NVIC_enuSetPriority(u8 Copy_u8IntID, u8 Copy_u8Priority);


#endif /* NVIC_H_ */
