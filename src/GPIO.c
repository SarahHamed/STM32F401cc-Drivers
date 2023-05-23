/*
 * GPIO.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Sarah
 */


#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/MCAL/GPIO/GPIO.h"

GPIO_t *const GPIO[3]={(GPIO_t*)0x40020000,(GPIO_t*)0x40020400,(GPIO_t*)0x40020800};

GpioErrStatus_t GPIO_enuSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8MODE, u8 copy_u8Speed)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;
	if(copy_u8Port>3)
	{
		Loc_errStatus=GPIO_InvalidPortNum;
	}
	if(copy_u8Pin>15)
	{
		Loc_errStatus=GPIO_InvalidPinNum;
	}
	if(Loc_errStatus==GPIO_Ok)
	{
		/* Set Mode Direction*/
		u32 GPIO_MODER=GPIO[copy_u8Port]->MODER;
		GPIO_MODER&=~(CLR_MASK<<(copy_u8Pin*2));
		GPIO_MODER|=((copy_u8MODE>>3)<<(copy_u8Pin*2));
		GPIO[copy_u8Port]->MODER=GPIO_MODER;

		switch((copy_u8MODE>>2) & OTYPER_MASK )
		{
		case PUSH_PULL:
			CLR_BIT(GPIO[copy_u8Port]->OTYPER,copy_u8Pin);
			break;
		case OPEN_DRAIN:
			SET_BIT(GPIO[copy_u8Port]->OTYPER,copy_u8Pin);
			break;
		}

		/* Set Pull-up, pull-down, */
		u32 GPIO_PUPDR=GPIO[copy_u8Port]->PUPDR;
		GPIO_PUPDR&=~(CLR_MASK<<(copy_u8Pin*2));
		GPIO_PUPDR|=((copy_u8MODE & PUPDR_MASK)<<(copy_u8Pin*2));
		GPIO[copy_u8Port]->PUPDR=GPIO_PUPDR;

		/* Set Speed	*/
		u32 GPIO_OSPEEDR=GPIO[copy_u8Port]->OSPEEDR;
		GPIO_OSPEEDR&=~(CLR_MASK<<(copy_u8Pin*2));
		GPIO_OSPEEDR|=(copy_u8Speed<<(copy_u8Pin*2));
		GPIO[copy_u8Port]->OSPEEDR=GPIO_OSPEEDR;
	}
	return	Loc_errStatus;
}


GpioErrStatus_t GPIO_enuSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;
	if(copy_u8Port>3)
	{
		Loc_errStatus=GPIO_InvalidPortNum;
	}
	if(copy_u8Pin>15)
	{
		Loc_errStatus=GPIO_InvalidPinNum;
	}
	if(Loc_errStatus==GPIO_Ok)
	{
		if(copy_u8Value==Value_HIGH)
		{
			SET_BIT( GPIO[copy_u8Port]->ODR, copy_u8Pin);
		}
		else if(copy_u8Value==Value_LOW)
		{
			CLR_BIT( GPIO[copy_u8Port]->ODR, copy_u8Pin);
		}
		else
		{
			Loc_errStatus=GPIO_InvalidVal;
		}
	}

	return	Loc_errStatus;
}

GpioErrStatus_t GPIO_enuGetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 *Add_pu8PinVal)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;
	if(copy_u8Port>3)
	{
		Loc_errStatus=GPIO_InvalidPortNum;
	}
	if(copy_u8Pin>15)
	{
		Loc_errStatus=GPIO_InvalidPinNum;
	}
	if(Loc_errStatus==GPIO_Ok)
	{
		*Add_pu8PinVal=GET_BIT( GPIO[copy_u8Port]->IDR, copy_u8Pin);
	}

	return	Loc_errStatus;
}

GpioErrStatus_t GPIO_enuInitPin(GPIO_Cfg *pinCfg)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;
	Loc_errStatus=GPIO_enuSetPinDirection(pinCfg->Port,pinCfg->Pin,pinCfg->Mode,pinCfg->Speed);
	return	Loc_errStatus;

}

GpioErrStatus_t GPIO_enuSelectAF(u8 copy_u8Port, u8 copy_u8Pin,u8 copy_u8AF)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;

	if(copy_u8Pin<(MAX_PINS_NUM/2))
	{
		u32 AFRL = GPIO[copy_u8Port]->AFRL;
		AFRL &= ~(AF_CLR_MASK<<(copy_u8Pin*4));
		AFRL |= (copy_u8AF<<(copy_u8Pin*4));

		GPIO[copy_u8Port]->AFRL=AFRL;
	}
	else if(copy_u8Pin<MAX_PINS_NUM)
	{
		u32 AFRH = GPIO[copy_u8Port]->AFRH;
		AFRH &= ~(AF_CLR_MASK<<((copy_u8Pin%8)*4));
		AFRH |= (copy_u8AF<<((copy_u8Pin%8)*4));

		GPIO[copy_u8Port]->AFRH=AFRH;
	}
	else
	{
		Loc_errStatus=GPIO_Nok;
	}

	return Loc_errStatus;
}

GpioErrStatus_t GPIO_enuSetPinValueAtomic(u8 copy_u8Port, u8 copy_u8Pin,u8 copy_u8AtomicStatus)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;

	if(copy_u8Port>3)
	{
		Loc_errStatus=GPIO_InvalidPortNum;
	}

	if(copy_u8Pin>15)
	{
		Loc_errStatus=GPIO_InvalidPinNum;
	}

	if(Loc_errStatus==GPIO_Ok)
	{
		switch(copy_u8AtomicStatus)
		{
		case ATOMIC_SET:
			SET_BIT(GPIO[copy_u8Port]->BSRR,copy_u8Pin);
			break;
		case ATOMIC_RESET:
			SET_BIT(GPIO[copy_u8Port]->BSRR,(copy_u8Pin+MAX_PINS_NUM));
			break;
		default:
			Loc_errStatus=GPIO_Nok;
			break;
		}
	}
	return Loc_errStatus;
}


GpioErrStatus_t GPIO_enuPinLock(u8 copy_u8Port, u8 copy_u8Pin, u32 copy_u32pinsLockedVal)
{
	GpioErrStatus_t Loc_errStatus=GPIO_Ok;

	if(copy_u8Port>3)
	{
		Loc_errStatus=GPIO_InvalidPortNum;
	}

	if(copy_u8Pin>15)
	{
		Loc_errStatus=GPIO_InvalidPinNum;
	}

	if(Loc_errStatus==GPIO_Ok)
	{
		u32 regVal=copy_u32pinsLockedVal;
		regVal|=(1<<LOCK_PIN);
		GPIO[copy_u8Port]->LCKR=regVal;

		regVal&=~(1<<LOCK_PIN);
		GPIO[copy_u8Port]->LCKR=regVal;

		regVal|=(1<<LOCK_PIN);
		GPIO[copy_u8Port]->LCKR=regVal;

		regVal=GPIO[copy_u8Port]->LCKR;

		if(GET_BIT(GPIO[copy_u8Port]->LCKR,LOCK_PIN)==1)
			Loc_errStatus=GPIO_Ok;
		else
			Loc_errStatus=GPIO_Nok;

	}

	return Loc_errStatus;
}
