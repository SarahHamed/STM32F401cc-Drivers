/*
 * LED_Cfg.h
 *
 *  Created on: Mar 9, 2023
 *      Author: Sarah
 */

#ifndef LED_CFG_H_
#define LED_CFG_H_



typedef struct
{
	u8 Port;
	u8 Pin;
	u8 Mode; //Active High/Low
	u8 Speed;
	u8 Name[50];
	u8 Color;
}LedCfg_t;



extern const LedCfg_t ledCfg[LED_Count];

#endif /* LED_CFG_H_ */
