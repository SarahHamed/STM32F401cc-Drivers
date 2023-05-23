/*
 * NVIC.c
 *
 *  Created on: Mar 16, 2023
 *      Author: Sarah
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/NVIC/NVIC.h"

NVIC_t *const NVIC=(NVIC_t*)0x40020000;

NVIC_tenuErrorStatus NVIC_enuEnableInterrupt(u8 Copy_u8IntID)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if(Copy_u8IntID > INT_MAX_ID)
	{
		Loc_errStatus=NVIC_Nok;
	}


	u8 RegNum = Copy_u8IntID/32;
	u8 BitNum = Copy_u8IntID%32;

	u32 ISER = NVIC->NVIC_ISER[RegNum];
	SET_BIT(ISER,BitNum);
	NVIC->NVIC_ISER[RegNum]=ISER;

	return Loc_errStatus;
}

NVIC_tenuErrorStatus NVIC_enuDisableInterrupt(u8 Copy_u8IntID)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if(Copy_u8IntID > INT_MAX_ID)
	{
		Loc_errStatus=NVIC_Nok;
	}

	u8 RegNum = Copy_u8IntID/32;
	u8 BitNum = Copy_u8IntID%32;

	u32 ICER = NVIC->NVIC_ICER[RegNum];
	SET_BIT(ICER,BitNum);
	NVIC->NVIC_ICER[RegNum]=ICER;


	return Loc_errStatus;
}

NVIC_tenuErrorStatus NVIC_enuSetPending(u8 Copy_u8IntID)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if(Copy_u8IntID > INT_MAX_ID)
	{
		Loc_errStatus=NVIC_Nok;
	}

	u8 RegNum = Copy_u8IntID/32;
	u8 BitNum = Copy_u8IntID%32;

	u32 ISPR = NVIC->NVIC_ISPR[RegNum];
	SET_BIT(ISPR,BitNum);
	NVIC->NVIC_ISPR[RegNum]=ISPR;

	return Loc_errStatus;
}

NVIC_tenuErrorStatus NVIC_enuClearPending(u8 Copy_u8IntID)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if(Copy_u8IntID > INT_MAX_ID)
	{
		Loc_errStatus=NVIC_Nok;
	}

	u8 RegNum = Copy_u8IntID/32;
	u8 BitNum = Copy_u8IntID%32;

	u32 ICPR=NVIC->NVIC_ICPR[RegNum];
	SET_BIT(ICPR,BitNum);
	NVIC->NVIC_ICPR[RegNum]=ICPR;

	return Loc_errStatus;
}

NVIC_tenuErrorStatus NVIC_enuGetActive(u8 Copy_u8IntID, u8 *Add_pu8ActiveState)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if(Copy_u8IntID > INT_MAX_ID)
	{
		Loc_errStatus=NVIC_Nok;
	}

	u8 RegNum = Copy_u8IntID/32;
	u8 BitNum = Copy_u8IntID%32;
	*Add_pu8ActiveState=GET_BIT(NVIC->NVIC_ICPR[RegNum],BitNum);

	return Loc_errStatus;
}


NVIC_tenuErrorStatus NVIC_enuSetSubGroupPriorityBits(u32 Copy_GROUP_Priority_SUB_Priority)
{
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;

	if((Copy_GROUP_Priority_SUB_Priority & VECTKEYSTAT) == VECTKEYSTAT)
	{
		Loc_errStatus=NVIC_Nok;
	}

	SCB_AIRCR = Copy_GROUP_Priority_SUB_Priority;

	return Loc_errStatus;
}


//most significant bit only, least significant is ignored
NVIC_tenuErrorStatus NVIC_enuSetPriority(u8 Copy_u8IntID, u8 Copy_u8Priority)
{
	//add the part that eliminates first 5 interrupts
	NVIC_tenuErrorStatus Loc_errStatus=NVIC_Ok;
	if(Copy_u8IntID > MAX_IPR_BYTE_ACCESS)
	{
		Loc_errStatus=NVIC_Nok;
	}

	if(Loc_errStatus ==NVIC_Ok)
	{

		NVIC->NVIC_IPR[Copy_u8IntID]= (Copy_u8Priority<<MST_SIG_SHIFT);
	}
	return Loc_errStatus;
}
