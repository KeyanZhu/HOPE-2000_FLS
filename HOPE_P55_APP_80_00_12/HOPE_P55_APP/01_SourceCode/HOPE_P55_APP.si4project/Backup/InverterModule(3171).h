/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INVERTER_MODULE_H__
#define __INVERTER_MODULE_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INVERTER_MODULE_C__
#define INVERTER_MODULE
#else
#define INVERTER_MODULE extern
#endif

typedef	struct
{
	INT8U IntConflict;
	INT16U InvTd;
}INV_TD;

union INVERTER_STATUS_TABLE
{
	struct INVERTER_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U LineFGInvF:1;
		INT16U InvPhaseLead:1;
		INT16U PhaseLocked:1;
		INT16U rsvd1:1;
		
		// BIT4-7
		INT16U rsvd2:4;
		
		// BIT8-11
		INT16U rsvd3:4;
		
		// BIT12-15
		INT16U rsvd4:4;
	} bits;
	INT16U data;
} ;
extern union INVERTER_STATUS_TABLE fInverterStatus;

#define mGetInvLinePLStatus()		fInverterStatus.bits.PhaseLocked

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INVERTER_MODULE	void	sInverterInitial(void);
INVERTER_MODULE	void	sInverterParaUpdate(void);
INVERTER_MODULE	void	sRInvPowerCal(void);
INVERTER_MODULE	void	sFrePhaseLockProc(void);
INVERTER_MODULE	void	sRVoltRegu(INT16U wRTrackVolt, INT16U wRKVoltrack1, INT16U wRKVoltrack2);
INVERTER_MODULE	void	sRInvDCVoltCntl(INT16S wInvDCVoltRef, INT16U wVoltKp, INT16U wVoltKi);
INVERTER_MODULE	void	sClrInvDCVoltCntlPara(void);
INVERTER_MODULE	void	sClrInvDCCurrCntlPara(void);
INVERTER_MODULE	void	sInvVoltHighChk(INT8U ubFilter);
INVERTER_MODULE void	sInvShortChk(INT16U uwFilter);	// Äæ±äÊä³ö¶ÌÂ·¼ì²â
INVERTER_MODULE void	sInvCurrOverChk(INT8U ubFilter);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INVERTER_MODULE INT16S	swGetRInvVoltNew(void);
INVERTER_MODULE INT16S	swGetRInvCurrNew(void);
INVERTER_MODULE INT16S	swGetRInvFreqNew(void);
INVERTER_MODULE INT16S	swGetRInvWattNew(void);
INVERTER_MODULE INT16S	swGetRInvDcVoltNew(void);
INVERTER_MODULE INT16S	swGetRInvDCVNew(void);
INVERTER_MODULE INT16S	swGetRInvVarNew(void);
INVERTER_MODULE INT16S	swGetRInvVANew(void);
INVERTER_MODULE INT16S	swGetRInvPFNew(void);
INVERTER_MODULE INT16S	swGetRInvVoltFilter(void);
INVERTER_MODULE INT16S	swGetRInvCurrFilter(void);
INVERTER_MODULE INT16S	swGetRInvFreqFilter(void);
INVERTER_MODULE INT16S	swGetRInvWattFilter(void);
INVERTER_MODULE INT16S	swGetRInvDcVoltFilter(void);
INVERTER_MODULE INT16S	swGetRInvDCVFilter(void);
INVERTER_MODULE INT16S	swGetRInvDCIFilter(void);
INVERTER_MODULE INT16S	swGetRInvVarFilter(void);
INVERTER_MODULE INT16S	swGetRInvVAFilter(void);
INVERTER_MODULE INT16S	swGetRInvPFFilter(void);
INVERTER_MODULE INT16S	swGetInvStep(void);
INVERTER_MODULE INT16S	swGetRSinAmp(void);
INVERTER_MODULE INT16S	swGetPhaseLockStep(void);
INVERTER_MODULE INT16S	swGetPhaseLockLimit(void);
INVERTER_MODULE INT16U	swGetSinePeriodCntNew(void);
INVERTER_MODULE INT16U	swGetInverterPeriodCntSet(void);
INVERTER_MODULE INT8U	sbGetInverterPLStatus(void);
INVERTER_MODULE INT8U	sbGetInverterLinePhaseStatus(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INVERTER_MODULE void	sSetRInvVoltNew(INT16S wVolt);
INVERTER_MODULE void	sSetRInvCurrNew(INT16S wCurr);
INVERTER_MODULE void	sSetRInvWattNew(INT16S wWatt);
INVERTER_MODULE void	sSetRInvDcVoltNew(INT16S wVolt);
INVERTER_MODULE void	sSetRInvFreqNew(INT16S wFreq);
INVERTER_MODULE void	sSetInvStep(INT16S wVaule);
INVERTER_MODULE void	sSetRSinAmp(INT16S wValue);
INVERTER_MODULE void	sSetRNewSinAmp(INT16S wValue);
INVERTER_MODULE void	sSetPhaseLockStep(INT16S wTemp);
INVERTER_MODULE void	sSetPhaseLockLimit(INT16S wTemp);
INVERTER_MODULE void	sSetInverterPeriodCntSet(INT16U wTemp);

#endif	// __INVERTER_MODULE_H__

