/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __SUPERVISOR_JOB_H__
#define __SUPERVISOR_JOB_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef	__SUPERVISOR_JOB_C__
#define	SUPERVISOR_JOB
#else
#define	SUPERVISOR_JOB  extern
#endif

#define	cPowerOnMode			0	// 上电模式
#define	cStandbyMode			1	// 待机模式
#define	cBypassMode				2	// 旁路模式
#define	cBatteryMode			3	// 离网模式
#define	cFaultMode				4	// 故障模式
#define	cLineMode				5	// 市电模式
#define	cChgMode				6	// 充电模式
#define	cShutdownMode			7	// 关机模式		// for test 20240927

// below macro are used in Line mode
#define	cToBypassMode			12	// 切到旁路模式
#define	cToBatteryMode			13	// 切到电池模式
#define	cToLineMode				15	// 切到电网模式
#define	cToChgMode				16	// 切到充电模式
#define cLineLoss				10	// 

// 
#define UpDownLimit(x,high,low)   (x = x > (high) ? (high) : (x < (low) ? (low) : x))
#define Uplimit(x,high)           (x = x > (high) ? (high) : x)
#define Dnlimit(x,low)            (x = x < (low) ? (low) : x)


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
SUPERVISOR_JOB void		sSupervisorJob(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
SUPERVISOR_JOB INT16U	swGetWorkMode(void);
SUPERVISOR_JOB INT16U	swGetFaultCode(void);
SUPERVISOR_JOB INT16U	swGetLoadOnSts(void);
SUPERVISOR_JOB INT16U	swGetStayStandby(void);
SUPERVISOR_JOB INT16U	swGetAgingStatus(void);
SUPERVISOR_JOB INT16U	uwGetSuperStkChk(void);


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
SUPERVISOR_JOB void		sSetFaultCode(INT16U uwFaultCode);
SUPERVISOR_JOB void		sSetWorkMode(INT16U uwWorkMode);
SUPERVISOR_JOB void		sSetLoadOnSts(INT16U uwTemp);
SUPERVISOR_JOB void		sSetStayStandby(INT16U uwTemp);
SUPERVISOR_JOB void		sSetAgingStatus(INT16U uwTemp);


#endif	// __SUPERVISOR_JOB_H__

