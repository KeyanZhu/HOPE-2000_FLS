/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __ADJ_PROCESS_H__
#define __ADJ_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __ADJ_PROCESS_C__
#define ADJ_PROCESS
#else
#define ADJ_PROCESS  extern
#endif




/********************************************************************************
* Routines' implementations														*
********************************************************************************/
ADJ_PROCESS	void	sBattVoltAdj0(void);
ADJ_PROCESS	INT8U	sbBattVoltAdj1(INT16S wVolt);
ADJ_PROCESS	INT8U	sbBattVoltAdj2(INT16S wVolt);
ADJ_PROCESS	INT8U	sbBattVoltAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbBattCurrAdj(INT16S wCurr);
ADJ_PROCESS INT8U	sbPvVoltAdj(INT16S wVolt);
ADJ_PROCESS INT8U	sbPvBatCurrAdj(INT16S wCurr);
ADJ_PROCESS	INT8U	sbInvVoltAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbInvCurrAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbLineVoltAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbOPCurrAdj(INT16S wVolt);
ADJ_PROCESS INT8U	sbOPVoltAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbBusVoltAdj(INT16S wVolt);
ADJ_PROCESS INT8U	sbBusCurrAdj(INT16S wCurr);
ADJ_PROCESS	INT8U	sbConvertVoltAdj(INT16S wVolt);
ADJ_PROCESS	INT8U	sbPDCDCCurrAdj(INT16S wVolt);
//ADJ_PROCESS	void	sAdcInitial(void);


/********************************************************************************
* Output interface Routines														*
********************************************************************************/


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


#endif	// __ADJ_PROCESS_H__

