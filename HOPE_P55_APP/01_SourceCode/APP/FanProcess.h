/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __FAN_PROCESS_H__
#define __FAN_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __FAN_PROCESS_C__
#define FAN_PROCESS
#else
#define FAN_PROCESS  extern
#endif

#define 	cFanPeriod				3750 	// 20K = 150MHz/2/(3750)

#define		mFanPWM					EPwm6Regs.CMPA.bit.CMPA
#define		mEnFANPWMOut()			EALLOW;\
									EPwm6Regs.TZCLR.bit.OST=1;\
									EDIS
#define		mDisFANPWMOut()			EALLOW;\
									EPwm6Regs.TZFRC.bit.OST=1;\
									EDIS

#define 	cFanWait				cFanPeriod
#define 	cFanOpenLoop			0

#define 	cFanDutyOff				0

#define 	cFanDutyMax				cFanPeriod

//风机运行模式
#define cFanPerWaitMode				0		// 关风扇
#define cFanPerFormanceMode			1		// 性能模式	// 用户开放
#define cFanPerSilentMode			2		// 静音模式	// 用户开放
#define cFanPerManualMode			3		// 手动模式
#define cFanModeMax					cFanPerManualMode	

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
FAN_PROCESS void	sFBFanSpeedProc(INT16U ubFilter1,INT16U ubFilter2);


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
FAN_PROCESS INT16U	swGetFanDuty(void);
FAN_PROCESS INT16U	swGetFanDutyPct(void);
FAN_PROCESS INT16U	swGetFanStatus(void);
FAN_PROCESS INT16U	swGetFanWorkMode(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
FAN_PROCESS void	sSetFanDuty(INT16U wDuty);
FAN_PROCESS void	sSetFanDutyPct(INT16U wDutyPct);


#endif	// __FAN_PROCESS_H__

