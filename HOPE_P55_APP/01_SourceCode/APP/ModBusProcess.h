/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __MODBUS_PROCESS_H__
#define __MODBUS_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __MODBUS_PROCESS_C__
#define MODBUS_PROCESS
#else
#define MODBUS_PROCESS  extern
#endif

#ifndef NULL
#define NULL	0x00
#endif

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
MODBUS_PROCESS	void	sModBusParsing(INT8U sciid);
MODBUS_PROCESS	void	sCommConnectChk(INT8U sciid, INT16U wFilter);
MODBUS_PROCESS	void	sEmsCommConnectChk(INT16U wFilter);


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
MODBUS_PROCESS	INT8U	sbGetCommConnected(INT8U sciid);
MODBUS_PROCESS	INT16U	swGetMpptBatCurr(void);
MODBUS_PROCESS	INT16U	swGetMpptPVCurr(void);
MODBUS_PROCESS	INT16U	sbGetBMSAddr(void);
MODBUS_PROCESS	INT8U	sbGetEMSBMSConnect(void);
MODBUS_PROCESS	void 	sBmsDataFramePolling(INT8U sciid, INT16U TimerBase);

MODBUS_PROCESS	INT16U	sbGetClearEventLog(void);
MODBUS_PROCESS	INT16U	sbGetEventLogFunc(void);
MODBUS_PROCESS	INT16U	sbGetFaultLogFunc(void);
MODBUS_PROCESS	INT16U	sbGetLogType(void);
MODBUS_PROCESS	INT16U	sbGetLogIndex(void);

MODBUS_PROCESS	INT16U	sbGetUpdateFW(void);
MODBUS_PROCESS	INT16U	sbGetExCommBps(void);
MODBUS_PROCESS	INT16U	sbGet485CommBps(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
MODBUS_PROCESS	void	sSetModBusAddress(INT8U address);
MODBUS_PROCESS	void	sSetCommConnected(INT8U sciid, INT8U bStatus);


#endif	// __MODBUS_PROCESS_H__

