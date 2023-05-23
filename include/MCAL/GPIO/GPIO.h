/*
 * GPIO.h
 *
 *  Created on: Feb 27, 2023
 *      Author: Sarah
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "STD_TYPES.h"

#define GPIOA	0
#define GPIOB	1
#define GPIOC	2


#define CLR_MASK	0x00000003

/*MODER*/
#define MODE_INPUT	0
#define MODE_OUTPUT	1
#define MODE_AF	2
#define MODE_ANALOG	3



/* GPIOx_OSPEEDR */
#define SPEED_LOW		0b00
#define SPEED_MEDIUM	0b01
#define	SPEED_HIGH		0b10
#define	SPEED_VERY_HIGH	0b11

#define Value_HIGH	1
#define Value_LOW	0

#define DIRECTION_MASK	0b11111


#define OUTPUT_MASK					0b00001
#define INPUT_MASK					0b00000
#define AF_MASK						0b00010

#define OTYPER_MASK		0b00001
#define	PUSH_PULL		0b00000
#define OPEN_DRAIN		0b00001

#define PUPDR_MASK	0b00011
#define	PULL_UP		0b01
#define PULL_DOWN	0b10
#define NO_PULL_UP_DOWN	0b00

#define OUTPUT_PUSH_PULL			0b01000
#define OUTPUT_PUSH_PULL_PULL_UP	0b01001
#define OUTPUT_PUSH_PULL_PULL_DOWN	0b01010
#define OUTPUT_OPEN_DRAIN			0b01100
#define OUTPUT_OPEN_DRAIN_PULL_UP	0b01101
#define OUTPUT_OPEN_DRAIN_PULL_DOWN	0b01110

#define AF_PUSH_PULL				0b10000
#define AF_PUSH_PULL_PULL_UP		0b10001
#define AF_PUSH_PULL_PULL_DOWN		0b10010
#define AF_OPEN_DRAIN				0b10100
#define AF_OPEN_DRAIN_PULL_UP		0b10101
#define AF_OPEN_DRAIN_PULL_DOWN		0b10110

#define INPUT_FLOATING				0b00000
#define INPUT_ANALOG				0b00000
#define INPUT_PULL_UP				0b00001
#define INPUT_PULL_DOWN				0b00010

#define AF_CLR_MASK			0x0000000F
#define MAX_PINS_NUM	16

#define ATOMIC_SET		1
#define ATOMIC_RESET	0

#define LOCK_PIN 16U

typedef struct
{
	u8 Port;
	u8 Pin;
	u8 Speed;
	u8 Mode;
}GPIO_Cfg;


typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PIN_t;

typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_t;


typedef enum
{
	GPIO_Ok,
	GPIO_Nok,
	GPIO_InvalidPortNum,
	GPIO_InvalidPinNum,
	GPIO_InvalidVal
}GpioErrStatus_t;



GpioErrStatus_t GPIO_enuSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Direction, u8 copy_u8Speed);
GpioErrStatus_t GPIO_enuSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);

GpioErrStatus_t GPIO_enuGetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 *Add_pu8PinVal);
GpioErrStatus_t GPIO_enuInitPin(GPIO_Cfg *pinCfg);
GpioErrStatus_t GPIO_enuSelectAF(u8 copy_u8Port, u8 copy_u8Pin,u8 copy_u8AF);
GpioErrStatus_t GPIO_enuSetPinValueAtomic(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8AtomicStatus);

GpioErrStatus_t GPIO_enuPinLock(u8 copy_u8Port, u8 copy_u8Pin, u32 copy_u32pinsLockedVal);


#endif /* GPIO_H_ */
