/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __LINE_MODULE_H__
#define __LINE_MODULE_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __LINE_MODULE_C__
#define LINE_MODULE
#else
#define LINE_MODULE extern
#endif

union LINE_STATUS_TABLE
{
	struct LINE_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U VoltLoss:1;
		INT16U FreqLoss:1;
		INT16U VoltLongTimeLoss: 1;
		INT16U rsvd1:1;
		
		// BIT4-7
		INT16U WaveLoss:1;
		INT16U PhaseLoss:1;
		INT16U rsvd2:2;
		
		// BIT8-11
		INT16U FeedVoltLoss:1;
		INT16U FeedFreqLoss:1;
		INT16U FeedVoltLongTimeLoss:1;
		INT16U LineVoltHLoss:1;			// 市电电压高压loss
		
		// BIT12-15
		INT16U WavePeakLoss:1;
		INT16U LineVoltLLoss:1;			// 市电电压低压loss
		INT16U LineFreqHLoss:1;			// 市电过频loss
		INT16U LineFreqLLoss:1;			// 市电欠频loss
	} bits;
	INT16U data;
} ;
extern union LINE_STATUS_TABLE fRLineStatus;

#define mGetLineStatusVoltLoss()		fRLineStatus.bits.VoltLoss
#define mGetLineStatusVoltHLoss()		fRLineStatus.bits.LineVoltHLoss
#define mGetLineStatusVoltLLoss()		fRLineStatus.bits.LineVoltLLoss
#define mGetLineStatusFreqLoss()		fRLineStatus.bits.FreqLoss
#define mGetLineStatusFreqHLoss()		fRLineStatus.bits.LineFreqHLoss
#define mGetLineStatusFreqLLoss()		fRLineStatus.bits.LineFreqLLoss


#define mGetLineStatusWaveLoss()		fRLineStatus.bits.WaveLoss
#define mSetLineStatusWaveLoss(x)		fRLineStatus.bits.WaveLoss=x

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
LINE_MODULE	void	sLineInitial(void);
LINE_MODULE	void	sLineParaUpdate(void);
LINE_MODULE	void	sRLinePowerCal(void);
LINE_MODULE	void	sRLineRms3timeAvgUpdate(void);
LINE_MODULE	void	sLineZeroLossClr(void);
LINE_MODULE	void	sLineZeroLossChk(INT16U	uwFilter);
LINE_MODULE	void	sRLineVoltChk(INT8U bFilter);
LINE_MODULE	void	sLineFreqChk(INT8U bFilter);
LINE_MODULE void	sGridOverLoadChk(INT16U uwGridOverLoadLevel, INT16U uwFilter);
LINE_MODULE void	sGridCurrOverChk(INT16U uwGridCurrOverLevel, INT16U uwFilter);
LINE_MODULE void	sGridCurrOver2Chk(INT16U uwGridCurrOverLevel, INT16U uwFilter);

LINE_MODULE	void	sRLineXXSecondsAveVoltCal(INT16U wSeconds);
LINE_MODULE	INT16U	swGetRLineLongTimeAverage(void);
LINE_MODULE	void	sLineVoltLTAvgCalChk(void);
LINE_MODULE	void	sLinePhaseChk(INT8U bFilter);
LINE_MODULE	void	sLineWaveChk(INT16S wLinvVolt, INT16S wSinValue, INT16S wOPCurr);
LINE_MODULE void	sFBSinepointBiasUpdate(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
LINE_MODULE INT16S	swGetRLineVoltNew(void);
LINE_MODULE INT16S	swGetRLineCurrNew(void);
LINE_MODULE INT16U	suwGetRLineChgCurrNew(void);	// 电网硬件充电电流
LINE_MODULE INT16S	swGetRLineFreqNew(void);
LINE_MODULE INT16S	swGetRLineWattNew(void);
LINE_MODULE INT16S	swGetRLineMidVoltNew(void);
LINE_MODULE INT16S	swGetRLineMidDcVoltNew(void);
LINE_MODULE INT16S	swGetRLineVarNew(void);
LINE_MODULE INT16S	swGetRLineVANew(void);
LINE_MODULE INT16S	swGetRLinePFNew(void);
LINE_MODULE INT16S	swGetRLineVoltFilter(void);
LINE_MODULE INT16S	swGetRLineCurrFilter(void);
LINE_MODULE INT16S	swGetRLineFreqFilter(void);
LINE_MODULE INT16S	swGetRLineWattFilter(void);
LINE_MODULE INT16S	swGetRLineMidVoltFilter(void);
LINE_MODULE INT16S	swGetRLineMidDcVoltFilter(void);
LINE_MODULE INT16S	swGetRLineVarFilter(void);
LINE_MODULE INT16S	swGetRLineVAFilter(void);
LINE_MODULE INT16S	swGetRLinePFFilter(void);
LINE_MODULE INT8U	sbGetLineVoltLossStatus(void);
LINE_MODULE INT8U	sbGetLineFreqLossStatus(void);
LINE_MODULE INT8U	sbGetLineWaveLossStatus(void);
LINE_MODULE INT8U	sbGetLinePhaseLossStatus(void);
LINE_MODULE INT8U	sbGetLineLossStatus(void);
LINE_MODULE INT8U	sbGetPalLineLossStatus(void);
LINE_MODULE INT8U	sbGetLineFeedLossStatus(void);
LINE_MODULE INT16U	swGetLinePeriodCntNew(void);

LINE_MODULE INT16S	swGetRLineRms3timeAvgPeakTemp(void);
LINE_MODULE INT16U	swGetRLineRms3timeAvgPeak(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
LINE_MODULE void	sSetRLineVoltNew(INT16S wVolt);
LINE_MODULE void	sSetRLineCurrNew(INT16S wCurr);
LINE_MODULE	void	sSetRLineFreqNew(INT16U uwLinePeriod);
LINE_MODULE void	sSetRLineWattNew(INT16S wWatt);
LINE_MODULE void	sSetRLineMidVoltNew(INT16S wVolt);
LINE_MODULE void	sSetRLineMidDcVoltNew(INT16S wVolt);

#endif	// __LINE_MODULE_H__

