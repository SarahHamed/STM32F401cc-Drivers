/*
 * LCD.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Sarah
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "LCD.h"
#include "GPIO.h"
#include "SYSTICK.h"


InitState_t initState=notInit;
u8 initDoneFlag=0;
reqType_t reqType=idle;

static LcdState_t state=LcdState_NotInitialized;

userReq usrReqData={"abc",3,0,0,0};

LcdState_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	/*	Rs=0 (Command)/Data	*/
		GPIO_enuSetPinValue( LCD_Control_Port, LCD_RS,Value_LOW);
		/*	RW=0 (Write)/Read	*/
		GPIO_enuSetPinValue( LCD_Control_Port, LCD_RW,Value_LOW);
		/*	EN=0 (Write)/Read	*/
		//GPIO_enuSetPinValue( LCD_Control_Port, LCD_EN,Value_LOW);

		/*	Command(D0->D7)		*/
		for(u8 i=0;i<8;i++)
		{
			GPIO_enuSetPinValue(LCD_Data_Port,i,GET_BIT(Copy_u8Command,i));
		}

		/*	Enable Pulse	*/
		GPIO_enuSetPinValue(LCD_Control_Port,LCD_EN ,Value_HIGH);

		GPIO_enuSetPinValue(LCD_Control_Port,LCD_EN,Value_LOW);
		//setBusy(2);
		return LcdState_Ok;
}



LcdState_t LCD_enuSendData(u8 Copy_u8Data)
{
	/*	Rs=1 Command/(Data)	*/
		GPIO_enuSetPinValue(LCD_Control_Port,LCD_RS,Value_HIGH);

		/*	RW=0 (Write)/Read	*/
		GPIO_enuSetPinValue(LCD_Control_Port,LCD_RW,Value_LOW);
		/*	EN=0 (Write)/Read	*/
		//GPIO_enuSetPinValue(LCD_Control_Port,LCD_EN,Value_LOW);

		/*	Command(D0->D7)		*/
		for(u8 i=0;i<8;i++)
		{
			GPIO_enuSetPinValue(LCD_Data_Port,i,GET_BIT(Copy_u8Data,i));
		}

		/*	Enable Pulse	*/
		GPIO_enuSetPinValue(LCD_Control_Port,LCD_EN,Value_HIGH);


		GPIO_enuSetPinValue(LCD_Control_Port,LCD_EN,Value_LOW);
		//setBusy(2);
		return LcdState_Ok;
}

/*
void  LCD_vidInit()
{
	//setBusy(31);
	LCD_enuSendCommand(LCD_FunctionalSet_Mask);
	setBusy(2);
	LCD_enuSendCommand(LCD_DisplayOnOff_Mask);
	setBusy(2);
	LCD_enuSendCommand(LCD_DisplayClear_Mask);
	setBusy(2);
}
*/
LcdState_t LCD_enuGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Loc_u8location=0;
	LcdState_t Loc_enuErrStatus=LcdState_Ok;

	if(Copy_u8YPos==First_Line)
	Loc_u8location=Copy_u8XPos;
	else if(Copy_u8YPos==Second_Line)
	Loc_u8location=BaseAddrLine2+Copy_u8XPos;

	Loc_enuErrStatus=LCD_enuSendCommand(DDRAM_SetAddInstCode+Loc_u8location);

	return Loc_enuErrStatus;
}



LcdState_t LCD_enuWriteString(char* Add_pchString)
{
	u8 Loc_u8Iter=0;
	static u8 pos_col=0;
	LcdState_t Loc_enuErrStatus=LcdState_Ok;

	while (Add_pchString[Loc_u8Iter]!='\0')
	{
		 if(pos_col>=LCD_Width)
		{
			pos_col=0;
			Loc_enuErrStatus= LCD_enuGotoXY(pos_col, Second_Line);
			//Loc_enuErrStatus= LCD_enuSendData(Add_pchString[Loc_u8Iter]);
		}

		Loc_enuErrStatus = LCD_enuSendData(Add_pchString[Loc_u8Iter]);
		Loc_u8Iter++;
		pos_col++;

	}
	return Loc_enuErrStatus;
}

LcdState_t LCD_enuWriteStringWithPos(const char *Add_pchString,u8 cpy_u8Len ,u8 cpy_u8posX,u8 cpy_u8posY)
{
	u8 Loc_u8Iter=0;
	LcdState_t Loc_enuErrStatus=LcdState_Ok;

	Loc_enuErrStatus= LCD_enuGotoXY(cpy_u8posX, cpy_u8posY);

	while (Add_pchString[Loc_u8Iter]!='\0')
	{

		Loc_enuErrStatus= LCD_enuSendData(Add_pchString[Loc_u8Iter]);

		Loc_u8Iter++;
		//cpy_u8posX++;

	}
	return Loc_enuErrStatus;
}

LcdState_t LCD_enuWriteStringAsync(const char *str,u8 cpy_u8Len ,u8 cpy_u8posX,u8 cpy_u8posY)
{
	//LcdState_t Loc_enuErrStatus=LcdState_Ok;

	LcdState_t res=LcdState_Busy;

	if(state==LcdState_Ok)
	{
		usrReqData.len=cpy_u8Len;
		usrReqData.posx=cpy_u8posX;
		usrReqData.posy=cpy_u8posY;
		usrReqData.str=str;
		reqType=writeReq;
		state=LcdState_Busy;
		//add res=LcdState_Ok;
	}
	else if(state==LcdState_NotInitialized)
	{
		res=notInit;
		initState=notInit;
	}


	return res;
}

void initStm(void)
{
	switch(initState)
	{
	case notInit:
		LCD_enuSendCommand(LCD_FunctionalSet_Mask);
		initState=DisplayOnOff;
		break;
	case DisplayOnOff:
		LCD_enuSendCommand(LCD_DisplayOnOff_Mask);
		initState=DisplayClear;
		break;
	case DisplayClear:
		LCD_enuSendCommand(LCD_DisplayClear_Mask);
		initState=initDone;
		break;
	case initDone:
		initDoneFlag=1;
		state=LcdState_Ok;
		break;
	}

}

void lcdTask(void)
{
	static u8 line=First_Line;
	if(initDoneFlag==0)
	{
		initStm();
	}
	else
	{
		switch(reqType)
		{
			case writeReq:

				LCD_enuSendData(usrReqData.str[usrReqData.idx]);
				usrReqData.idx++;
				if(usrReqData.idx>=usrReqData.len)
				{
					reqType=idle;
					state=LcdState_Ok;
					usrReqData.idx=0;
				}

				/*
				LCD_enuWriteString(usrReqData.str);
				reqType=idle;
				state=LcdState_Ok;
				*/
/* all of the following is wrong because it has to be written char by char because the task comes every 2 sec, but write string doesn't wait for 2 sec between every char*/
			/*
				if((usrReqData.idx)>=LCD_Width)
				{
					usrReqData.idx=0;
					line=Second_Line;
				}
				LCD_enuWriteStringWithPos(usrReqData.str,usrReqData.len,usrReqData.idx,line);
				usrReqData.idx+=6;
				reqType=idle;
				state=LcdState_Ok;
				if((usrReqData.idx)>=LCD_Width && line== Second_Line)
					reqType=clrReq;
					*/
				break;
			case idle:
				/*if(usrReqData.idx>LCD_Width)
				{
					reqType=clrReq;
					usrReqData.idx=0;
				}
*/
				break;
			case clrReq:
				LCD_clearScreen();
				//line=First_Line;
				reqType=idle;
				break;

		}
	}
}



void LCD_clearScreen(void)
{
	LCD_enuSendCommand(LCD_DisplayClear_Mask); //clear display
}
