/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __DEARTING_PROCESS_H__
#define __DEARTING_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __DEARTING_PROCESS_C__
#define DEARTING_PROCESS
#else
#define DEARTING_PROCESS  extern
#endif



/********************************************************************************
* Routines' implementations														*
********************************************************************************/
DEARTING_PROCESS 	void	sDeratingProcInit(void);
DEARTING_PROCESS	void	sDeratingProc(void);

DEARTING_PROCESS	void	sPvTempChk(INT16U wFilter1, INT16U wFilter2);			// PV过温检测
DEARTING_PROCESS 	void	sInvOverTempChk(INT16U wFilter1, INT16U wFilter2);		// 逆变过温
DEARTING_PROCESS	void	sTwTempChk(INT16U wFilter1, INT16U wFilter2);			// 推挽低压侧过温
DEARTING_PROCESS	void	sTwTraTempChk(INT16U wFilter1, INT16U wFilter2);		// 推挽变压器过温检测
DEARTING_PROCESS	void	sBatHTempChk(INT16U wFilter1, INT16U wFilter2);			// 电池正NTC过温检测
DEARTING_PROCESS	void	sBatLTempChk(INT16U wFilter1, INT16U wFilter2);			// 电池负NTC过温检测

DEARTING_PROCESS 	INT16S sOutputVoltDrtProc(INT16S wOutputVoltRated);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
DEARTING_PROCESS	INT16U	suwGetSysDeratingStatus(void);							// 系统降额状态标识
DEARTING_PROCESS 	INT16S	swGetInvTempDeratVoltLimit(void);						// 逆变温度降额值
DEARTING_PROCESS 	INT16S	swGetTwTempDeratVoltLimit(void);						// 推挽温度降额值
DEARTING_PROCESS 	INT16S	swGetTraTempDeratVoltLimit(void);						// 推挽变压器温度降额值


DEARTING_PROCESS	INT16S	swGetTempDeratVoltNew(void);							// 温度降额输出电压
DEARTING_PROCESS	INT16S	swGetTempDeratPvBatCurrNew(void);						// PV降额输出电流


DEARTING_PROCESS	INT16S	swGetTempDeratVoltFilter(void);							// 温度降额输出电压
DEARTING_PROCESS 	INT16S	swGetTempDeratPvBatCurrFilter(void);					// PV降额输出电流
DEARTING_PROCESS	INT16S	swGetBatVoltDeratVoltLimit(void);						// 电池欠压降额输出电压
DEARTING_PROCESS	INT16S	swGetBatCurrDeratVoltLimit(void);						// BAT限流降额负载电压

DEARTING_PROCESS	INT16U	suwGetSysDerateEn(void);								// 降额使能标识

DEARTING_PROCESS	INT16S	swGetInvTempDeratPowerLimit(void);						// 逆变温度降额功率
DEARTING_PROCESS	INT16S	swGetTwTempDeratPowerLimit(void);						// 推挽温度降额功率
DEARTING_PROCESS	INT16S	swGetTraTempDeratPowerLimit(void);						// 推挽变压器温度降额功率
DEARTING_PROCESS 	INT16S	swGetBatVoltDeratPowerLimit(void);						// 电池低压降并网功率
DEARTING_PROCESS 	INT16S	swGetLineVoltDeratPowerLimit(void);						// 市电电压降额		

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
DEARTING_PROCESS	void	sSetSysDerateEn(INT16U	DerateEn);						// 降额使能设置



#endif	// __FAN_PROCESS_H__

