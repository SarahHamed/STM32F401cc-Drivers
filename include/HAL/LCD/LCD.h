/*
 * LCD.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Sarah
 */

#ifndef LCD_H_
#define LCD_H_

#include "../include/LIB/STD_TYPES.h"
#include "GPIO.h"

#define LCD_RS	PIN0
#define LCD_RW	PIN1
#define LCD_EN	PIN2

#define LCD_Data_Port		GPIOA
#define LCD_Control_Port	GPIOB

#define Anode		PIN3
#define Kathode		PIN4


#define LCD_FunctionalSet_Mask	0b00111000
#define LCD_DisplayOnOff_Mask	0b00001100
#define LCD_DisplayClear_Mask	0b00000001

#define First_Line	0
#define Second_Line	1

#define BaseAddrLine2	0x40
#define DDRAM_SetAddInstCode	128
#define CGRAM_SetAddInstCode	64
#define CGRAM_BlockSize	8

#define LCD_Width	16
#define Line_Pos_0	0

typedef enum
{
	LcdState_Ok,		//idle
	LcdState_Nok,
	LcdState_Busy,
	LcdState_NotInitialized
}LcdState_t;

typedef struct
{
	const char * str;
	u8 len;
	u8 posx;
	u8 posy;
	u8 idx;
}userReq;

typedef enum
{
	notInit,
	DisplayOnOff,
	DisplayClear,
	initDone
}InitState_t;


typedef enum
{
	idle,
	writeReq,
	clrReq,
}reqType_t;

void initStm(void);
void lcdTask(void);
LcdState_t LCD_enuWriteStringAsync(const char *str,u8 cpy_u8Len ,u8 cpy_u8posX,u8 cpy_u8posY);
void LCD_clearScreen(void);
LcdState_t LCD_enuInit();



void  LCD_vidInit();
LcdState_t LCD_enuSendData(u8 Copy_u8Data);
LcdState_t LCD_enuSendCommand(u8 Copy_u8Command);

LcdState_t LCD_enuGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);
LcdState_t LCD_enuWriteSpecialPattern(u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

LcdState_t LCD_enuWriteString(char* Add_pchString);
LcdState_t LCD_enuWriteNumber(u16 Copy_u16Number);

LcdState_t LCD_enuWriteString(char* Add_pchString);
LcdState_t LCD_enuWriteStringWithPos(const char *Add_pchString,u8 cpy_u8Len ,u8 cpy_u8posX,u8 cpy_u8posY);

#endif /* LCD_H_ */
