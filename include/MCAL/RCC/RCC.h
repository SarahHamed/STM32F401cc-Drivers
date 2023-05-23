#ifndef RCC_H
#define	RCC_H



#define Clock_HSI	0
#define Clock_HSE	1
#define Clock_PLL	2

#define PPLN_SHIFT_LEFT	6
#define PPLP_SHIFT_LEFT	16
#define PPLQ_SHIFT_LEFT	24

#define RCC_PLLCFGR_PLLM_CLR_MASK	0xFFFFFFC0
#define RCC_PLLCFGR_PLLN_CLR_MASK	0xFFFF803F
#define RCC_PLLCFGR_PLLP_CLR_MASK	0xFFFCFFFF
#define RCC_PLLCFGR_PLLQ_CLR_MASK	0xF0FFFFFF

#define SWS_HSI_MASK	0x00000000
#define SWS_HSE_MASK	0x00000001
#define SWS_PLL_MASK	0x00000002

#define RCC_CR_HSION 	    0x00000001
#define RCC_CR_HSIRDY 	  	0x00000002
#define RCC_CR_HSEON	    0x00010000
#define RCC_CR_HSERDY	    0x00020000
#define RCC_CR_HSEBYP	    0x00040000
#define RCC_CR_CSSON	    0x00080000
#define RCC_CR_PLLON	    0x01000000
#define RCC_CR_PLLRDY	    0x02000000
#define RCC_CR_PLLI2SON	  	0x04000000
#define RCC_CR_PLLI2SRDY	0x08000000

#define RCC_CFGR_SW			0x00000003
#define RCC_CFGR_SWS		0x0000000C	/* SYS clk status*/

/*AHB1 Peripherals*/
#define GPIOAEN	0
#define GPIOBEN	1
#define GPIOCEN	2
#define GPIODEN	3
#define	CRCEN	12
#define	DMA1EN	21
#define	DMA2EN	22

#define GPIOAEN_MASK	0x00000001
#define GPIOBEN_MASK	0x00000002
#define GPIOCEN_MASK	0x00000004
#define GPIODEN_MASK	0x00000008

/*AHB2 Peripherals*/
#define OTGFSEN	7

/*APB1 Peripherals*/
#define TIM2EN	0
#define TIM3EN	1
#define TIM4EN	2
#define TIM5EN	3
#define	WWDGEN	11
#define	SPI2EN	14
#define	SPI3EN	15
#define	USART2EN	17
#define	I2C1EN	21
#define	I2C2EN	22
#define	I2C3EN	23
#define	PWREN	28


/*
#define Bus_AHB1	0
#define Bus_AHB2	1
#define Bus_APB1	2
#define Bus_APB2	3
*/


#define RCC_CFGR_AHB_Prescaler_Mask		0x000000F0
#define RCC_CFGR_APB1_Prescaler_Mask	0x00001C00
#define RCC_CFGR_APB2_Prescaler_Mask	0x0000E000


#define	APB2_Presacaler_2	0x00008000
#define	APB2_Presacaler_4	0x0000A000
#define	APB2_Presacaler_8	0x0000C000
#define	APB2_Presacaler_16	0x0000E000


#define	APB1_Presacaler_2	0x00001000
#define	APB1_Presacaler_4	0x00001400
#define	APB1_Presacaler_8	0x00001800
#define	APB1_Presacaler_16	0x00001C00


#define AHB_Presacaler_2	0x00000080
#define AHB_Presacaler_4	0x00000090
#define AHB_Presacaler_8	0x000000A0
#define AHB_Presacaler_16	0x000000B0
#define AHB_Presacaler_64	0x000000C0
#define AHB_Presacaler_128	0x000000D0
#define AHB_Presacaler_256	0x000000E0
#define AHB_Presacaler_512	0x000000F0


typedef enum
{
	SysBus_AHB1,
	SysBus_AHB2,
	SysBus_APB1,
	SysBus_APB2
}SysBus_t;

/*
typedef enum
{
	clkState_On,
	clkState_Off,
}ClkState_t;
*/
typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 Reserved1[2];
	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;
	volatile u32 Reserved2[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 Reserved3[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 Reserved4[2];
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 Reserved5[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 Reserved6[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 Reserved7[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RCC_DCKCFGR;

}RCC_t;

typedef enum
{
	Clock_StateOff,
	Clock_StateOn
}ClockState_t;

typedef enum
{
	Peri_StateOff,
	Peri_StateOn

}PeriState_t;

typedef enum
{
	ret_Ok,
	ret_Nok,
	ret_ClockError,
	ret_ClockNotReady
}RccErrStatus_t;

typedef enum
{
	NotRdy = 0,
	Rdy = 1
}ClockRdy_t;




RccErrStatus_t RCC_enuSetClockStatus(u8 cpy_u8Clock, ClockState_t cpy_enuClockStatus);
RccErrStatus_t RCC_enuGetReadyClock(u8 cpy_u8Clock, ClockRdy_t *Add_penuIsClockRdy);

RccErrStatus_t RCC_enuSelectSysClock(u8 cpy_u8Clock);
void RCC_vidGetSysClock(u32 *Add_pu32Clock); // static?

RccErrStatus_t RCC_enuSetPeriStatus(SysBus_t cpy_enuSysBus, u32 cpy_periNumMask, PeriState_t cpy_enuPeriState);

/* Set AHB1 and APB1 and APB2 Prescalers */
RccErrStatus_t RCC_enuSetBusesPrescaler(u32 copy_u32AHB, u32 copy_u32APB1, u32 copy_u32APB2);
/* Set PLL Factors */
RccErrStatus_t RCC_enuSetPLLFactors(u8 copy_u8PLLM, u32 copy_u32PLLN, u8 copy_u8PLLP, u8 copy_u8PLLQ);


#endif


