
#include "STD_TYPES.h"
#include "RCC.h"

RCC_t *const RCC=(RCC_t*)0x40023800;



RccErrStatus_t RCC_enuSetClockStatus(u8 cpy_u8Clock, ClockState_t cpy_enuClockStatus)
{
	RccErrStatus_t loc_enuErrStatus=ret_Ok;
	u32 CR = RCC->RCC_CR;

	if(cpy_enuClockStatus != Clock_StateOff && cpy_enuClockStatus !=Clock_StateOn)
	{
		loc_enuErrStatus=ret_Nok;
	}

	switch(cpy_u8Clock)
	{
	case Clock_HSI:
		CR &=~RCC_CR_HSION;
		if(cpy_enuClockStatus == Clock_StateOn)
		{
			CR |=RCC_CR_HSION;
		}
		break;
	case Clock_HSE:
		CR &=~RCC_CR_HSEON;
		if(cpy_enuClockStatus == Clock_StateOn)
		{
			CR |=RCC_CR_HSEON;
		}
		break;
	case Clock_PLL:
		CR &=~RCC_CR_PLLON;
		if(cpy_enuClockStatus == Clock_StateOn)
		{
			CR |=RCC_CR_HSEON;
		}
		break;
	default:
		loc_enuErrStatus=ret_Nok;
		break;
	}

	RCC->RCC_CR = CR;

	return loc_enuErrStatus;
}

/*
 cpy_u32ClkRdyMask ---> RCC_CR_HSIRDY - RCC_CR_HSERDY - RCC_CR_PLLRDY
*/

RccErrStatus_t RCC_enuGetReadyClock(u8 cpy_u8Clock, ClockRdy_t *Add_penuIsClockRdy)
{
	u16 local_u16Counter = 0;
	u32 Loc_u32ClkRdyMask;
	RccErrStatus_t loc_enuErrStatus=ret_Ok;

	switch(cpy_u8Clock)
	{
		case Clock_HSI:
			Loc_u32ClkRdyMask=RCC_CR_HSIRDY;
			break;
		case Clock_HSE:
			Loc_u32ClkRdyMask=RCC_CR_HSERDY;
			break;
		case Clock_PLL:
			Loc_u32ClkRdyMask=RCC_CR_PLLRDY;
			break;
		default:
			loc_enuErrStatus=ret_Nok;
			break;
	}

	if(loc_enuErrStatus==ret_Ok)
	{
		while ((RCC->RCC_CR & Loc_u32ClkRdyMask) != Loc_u32ClkRdyMask && local_u16Counter < 50000)
			{
				local_u16Counter++;
			}

			if((RCC->RCC_CR & Loc_u32ClkRdyMask) == Loc_u32ClkRdyMask)
			{
				*Add_penuIsClockRdy=Rdy;
			}
			else
			{
				*Add_penuIsClockRdy=NotRdy;
			}

	}
		return ret_Ok;
}

/********************************************/
/* RCC SELECT SYSTEM CLOCK					*/
/* Input:  	Clock_HSI						*/
/* 			Clock_HSE						*/
/* 			Clock_PLL 						*/
/* Output: RccErrStatus_t to report error	*/
/********************************************/

RccErrStatus_t RCC_enuSelectSysClock(u8 cpy_u8Clock)
{
	u32 Loc_u32SysClk;
	RccErrStatus_t loc_enuErrStatus=ret_Ok;

	if(cpy_u8Clock>3)
	{
		loc_enuErrStatus=ret_Nok;
	}
	switch(cpy_u8Clock)
	{
		case Clock_HSI:
			RCC->RCC_CFGR &=~ RCC_CFGR_SW;
			RCC->RCC_CFGR |= SWS_HSI_MASK;
			break;
		case Clock_HSE:
			RCC->RCC_CFGR &=~ RCC_CFGR_SW;
			RCC->RCC_CFGR |= SWS_HSE_MASK;
			break;
		case Clock_PLL:
			RCC->RCC_CFGR &=~ RCC_CFGR_SW;
			RCC->RCC_CFGR |= SWS_PLL_MASK;
			break;
		default:
			loc_enuErrStatus=ret_Nok;
			break;
	}


	RCC_vidGetSysClock(&Loc_u32SysClk);

	if(Loc_u32SysClk != cpy_u8Clock)
		loc_enuErrStatus=ret_Nok;

	return loc_enuErrStatus;
}


void RCC_vidGetSysClock(u32 *Add_pu32Clock)
{
	*Add_pu32Clock = RCC->RCC_CFGR & RCC_CFGR_SWS;
}


/*******************************************/
/* RCC Set Peripheral Clock ON or OFF*/
/* Input:  	xxxxxx	*/
/* 			xxxxxx	*/
/* 			xxxxxx 	*/
/* Output: RccErrStatus_t to report error*/
/*********************************************/

/*
 * cpy_periNumMask --> (GPIOAEN_MASK - GPIOBEN_MASK - GPIOCEN_MASK - GPIODEN_MASK)
 */
RccErrStatus_t RCC_enuSetPeriStatus(SysBus_t cpy_enuSysBus, u32 cpy_periNumMask, PeriState_t cpy_enuPeriState)
{
	RccErrStatus_t loc_enuErrStatus=ret_Ok;

	if( cpy_enuSysBus>3 )
	{
		loc_enuErrStatus=ret_Nok;
	}

	if(cpy_enuPeriState != Peri_StateOff || cpy_enuPeriState !=Peri_StateOn)
	{
		loc_enuErrStatus=ret_Nok;
	}

	/*e3ml fekret l reserved 3shan t3mly beha check 3la l bus (cpy_periNumMask)
	 * l klam da mesh hena da momkn ykon fe enableAHBPeri
	 */
	u32 Loc_u32Reg;
	switch(cpy_enuSysBus)
	{
	case SysBus_AHB1:
		Loc_u32Reg= RCC->RCC_AHB1ENR;
		Loc_u32Reg &= ~cpy_periNumMask;
		if(cpy_enuPeriState==Peri_StateOn)
		{
			Loc_u32Reg |= cpy_periNumMask;
		}
		RCC->RCC_AHB1ENR=Loc_u32Reg;
		break;
	case SysBus_AHB2:
		Loc_u32Reg= RCC->RCC_AHB2ENR;
		Loc_u32Reg &= ~cpy_periNumMask;
		if(cpy_enuPeriState==Peri_StateOn){
			Loc_u32Reg |= cpy_periNumMask;
		}
		RCC->RCC_AHB2ENR=Loc_u32Reg;
		break;
	case SysBus_APB1:
		Loc_u32Reg=RCC->RCC_APB1ENR;
		Loc_u32Reg &= ~cpy_periNumMask;
		if(cpy_enuPeriState==Peri_StateOn){
			Loc_u32Reg |= cpy_periNumMask;
		}
		RCC->RCC_APB1ENR=Loc_u32Reg;
		break;
	case SysBus_APB2:
		Loc_u32Reg=RCC->RCC_APB2ENR;
		Loc_u32Reg &= ~cpy_periNumMask;
		if(cpy_enuPeriState==Peri_StateOn){
		Loc_u32Reg |= cpy_periNumMask;
		}
		RCC->RCC_APB2ENR=Loc_u32Reg;
		break;

	}
	return loc_enuErrStatus;
}




/* INPUTS: AHB_Presacaler_x, APB1_Presacaler_x, APB2_Presacaler_x */
RccErrStatus_t RCC_enuSetBusesPrescaler(u32 copy_u32AHB, u32 copy_u32APB1, u32 copy_u32APB2)
{
	RccErrStatus_t	loc_enuErrStatus=ret_Ok;

	u32 CFGR=RCC->RCC_CFGR;

	CFGR&=~RCC_CFGR_AHB_Prescaler_Mask;
	CFGR|=copy_u32AHB;


	CFGR&=~RCC_CFGR_APB1_Prescaler_Mask;
	CFGR|=copy_u32APB1;


	CFGR&=~RCC_CFGR_APB2_Prescaler_Mask;
	CFGR|=copy_u32APB2;

	RCC->RCC_CFGR=CFGR;

	return loc_enuErrStatus;
}

/* PLLQ = 2 ---> PLLQ = 15 */
/* PLLP = 2,4,6,8		   */
/* PLLN = 2 ---> PLLN = 511 except 433 */
/* PLLM = 2 ---> PLLM = 63 */

RccErrStatus_t RCC_enuSetPLLFactors(u8 copy_u8PLLM, u32 copy_u32PLLN, u8 copy_u8PLLP, u8 copy_u8PLLQ)
{
	RccErrStatus_t	loc_enuErrStatus=ret_Ok;
	if(copy_u8PLLM < 2 || copy_u8PLLM>15)
		loc_enuErrStatus=ret_Nok;
	if(copy_u8PLLP != 2 || copy_u8PLLP != 4 ||copy_u8PLLP != 6|| copy_u8PLLP != 8)
		loc_enuErrStatus=ret_Nok;
	if(copy_u32PLLN < 2 || copy_u32PLLN>511 ||copy_u32PLLN==433)
		loc_enuErrStatus=ret_Nok;
	if(copy_u8PLLM < 2 || copy_u32PLLN>63)
		loc_enuErrStatus=ret_Nok;
	u32 PLLCFGR = RCC->RCC_PLLCFGR;

	PLLCFGR&=RCC_PLLCFGR_PLLM_CLR_MASK;
	PLLCFGR|=copy_u8PLLM;

	PLLCFGR&=RCC_PLLCFGR_PLLN_CLR_MASK;
	PLLCFGR|=(copy_u32PLLN<<PPLN_SHIFT_LEFT);

	PLLCFGR&=RCC_PLLCFGR_PLLP_CLR_MASK;
	PLLCFGR|=(copy_u8PLLP<<PPLP_SHIFT_LEFT);

	PLLCFGR&=RCC_PLLCFGR_PLLQ_CLR_MASK;
	PLLCFGR|=(copy_u8PLLQ<<PPLQ_SHIFT_LEFT);


	return loc_enuErrStatus;
}
