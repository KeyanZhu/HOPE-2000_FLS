/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__LINE_MODULE_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include	"Main.h"
#include	"Kernel\source\OS_HEAD.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sLineWaveChk,".TI.ramfunc");


/********************************************************************************
* Constants																		*
********************************************************************************/
#define	cIncreaseFun  0
#define	cDecreaseFun  1



/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S gi_wSinePointOneFour;
extern INT16S gi_wSinePointMaxTwo;

extern INT16S wRInvWattNew;		// 1W
extern INT16S wRInvVoltNew;		// 0.1V
//extern INT16S g_wReactiveCurrTanRate;	// FB控制器内使用

/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16S wRLineVoltNew;			// 0.1V
INT16S wRLineCurrNew;			// 0.01A
INT16U wRLineFreqNew;			// 0.01Hz
INT16S wRLineWattNew;			// 1W,买电为正,卖电为负
INT16S wRLineMidVoltNew;		// 0.1V
INT16S wRLineMidDcVoltNew;		// 0.1V
INT16S wRLineVarNew;			// 1Var
INT16S wRLineVANew;				// 1VA
INT16S wRLinePFNew;				// 0.001

INT16S wRLineVoltFilter;		// 0.1V
INT16S wRLineCurrFilter;		// 0.01A
INT16U wRLineFreqFilter;		// 0.01Hz
INT16S wRLineWattFilter;		// 1W
INT16S wRLineMidVoltFilter;		// 0.1V
INT16S wRLineMidDcVoltFilter;	// 0.1V
INT16S wRLineVarFilter;			// 1Var
INT16S wRLineVAFilter;			// 1VA
INT16S wRLinePFFilter;			// 0.001

INT16U g_uwRLineRms3time[3] = {0};
INT16U g_uwRLineRms3timeAvg;
INT16U g_uwRLineRms3timeAvgPeak;

INT16U wRLineZeroLossCnt;

INT32U gi_udwLineZeroTimeNew = 0;	// 当前市电过零CAP值,50Hz=1800000,60Hz=1500000
INT32U gi_udwLineZeroTimeOld = 0;	// 上次市电过零CAP值,50Hz=1800000,60Hz=1500000
INT16U gi_uwLinePeriodCntNew = 0;	// 市电周期值,50Hz=20000,60Hz=16667

INT16S gi_wRGeneratorWaveChkCnt = 0;
INT16S gi_wRGeneratorVoltMax = 0;
INT16S gi_wRGeneratorVoltMin = 0;

INT16S	wBiasTest = 0;
/********************************************************************************
* Output variables																*
********************************************************************************/
union LINE_STATUS_TABLE fRLineStatus;

/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16U	g_uwLineVoltHLoss = cLineVolt280V;
INT16U	g_uwLineVoltH2Loss = cLineVolt280V;
INT16U	g_uwLineVoltLLoss = cLineVolt80V;//cLineVolt90V;
INT16U	g_uwLineVoltL2Loss = cLineVolt80V;//cLineVolt90V;
INT16U	g_uwLineVoltHBack = cLineVolt270V;
INT16U	g_uwLineVoltLBack = cLineVolt90V;
INT16U	g_uwLineFreqHLoss = cLineFreq65Hz;//cLineFreq52Hz;
INT16U	g_uwLineFreqH2Loss = cLineFreq65Hz;//cLineFreq52Hz;
INT16U	g_uwLineFreqLLoss = cLineFreq40Hz;//cLineFreq47Hz5;
INT16U	g_uwLineFreqL2Loss = cLineFreq40Hz;//cLineFreq47Hz5;
INT16U	g_uwLineFreqHBack = cLineFreq63Hz;//cLineFreq51Hz;
INT16U	g_uwLineFreqLBack = cLineFreq42Hz;//cLineFreq48Hz5;
INT16U  g_uwLineFreqFastHLoss =cLineFreq50Hz2;
INT16U  g_uwLineFreqFastLLoss =cLineFreq49Hz8;

INT16U	g_wVoltLLossTime =20;
INT16U 	g_wVoltL2LossTime =20;
INT16U 	g_wVoltHLossTime =20;
INT16U 	g_wVoltH2LossTime =20;
INT16U 	g_wFreHLossTime  = 30;
INT16U	g_wFreH2LossTime = 5;
INT16U	g_wFreLLossTime  = 30;
INT16U	g_wFreL2LossTime = 5;

INT32U g_dwLvrtLossTime;
INT32U g_dwHvrtLossTime;
INT16U g_uwLineFreFastLossFlag;
#define LineAveVoltArrayLenth		60
INT16U wRLineAveVoltArray[LineAveVoltArrayLenth];
INT16U g_uwRLineXXSecondsAveVolt;
INT16U wRLineLTVolt;

//INT16S gi_wLineWaveDetectEn = 1;

//INT16U g_wPFRemainder =0;
//INT16U g_uwPFValue = 100;
//INT16S g_wPFAjustRef =100;
//INT16S g_wReactiveCurrTanRateTemp;
//INT16S g_PowerCompenSation =0;
//INT16S g_TestPFCal;
//INT16S g_wReactiveKAdj = 103;
//INT16S g_wPFReactivBiasLineVoltAdj =100;
//INT16S g_wPFTestAdj =100;
//INT16S g_wReactiveCurrTanRateAdj;
//INT16S g_wPowerFactorReactivBias;
//INT32S g_dwOneOfTenPowerRate;
//INT16U g_uwPFValueSet = 100;
//INT16S wPowerIndexTest;

INT16U	uwRLineChgCurr;
INT16U	uwRLineChgCurrTemp;

extern INT16U	uwGridLossCount;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
INT16S swGetCalculate(INT16S x, INT16S y, INT32S m, INT32S dwOneOfTenRate,INT16S wInDecreasFun);


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sLineInitial(void)
{
	INT8U i;
	
	sLineParaUpdate();
	
	g_dwLvrtLossTime = 0;
	g_dwHvrtLossTime = 0;
	g_uwLineFreFastLossFlag = 0;
	wRLineLTVolt = 0;
	for(i = 0; i < LineAveVoltArrayLenth; i++)
	{
		*(wRLineAveVoltArray + i) = 0;
	}
}

void	sLineParaUpdate(void)
{
	
}

void	sRLinePowerCal(void)
{
	static INT16S s_wVarRes = 0;
	static INT16S s_wVARes = 0;
	static INT16S s_wPFRes = 0;
	INT32S dwTemp;

	//dwTemp = ((INT32S)wRLineVoltNew * wRLineCurrNew + 500) / 1000;
	if(swGetWorkMode() != cLineMode && swGetWorkMode() != cChgMode)					
	{
		dwTemp = 0;
	}
	else
	{
		dwTemp = swGetROpVANew() + swGetRInvVANew();	// 市电电流无采样，通过OP和INV折算
	}
	if(swAbs(dwTemp) < swAbs(wRLineWattNew))
	{
		dwTemp = wRLineWattNew;
	}
	wRLineVANew = swAbs(dwTemp);
	
	dwTemp = ((INT32S)wRLineVANew * wRLineVANew) - ((INT32S)wRLineWattNew * wRLineWattNew);
	if(dwTemp > 0)
	{
		wRLineVarNew = swRoot((INT32U)dwTemp);
	}
	else
	{
		wRLineVarNew = 0;
	}
	
	if(wRLineVANew != 0)
	{
		wRLinePFNew = ((INT32S)wRLineWattNew * 1000) / wRLineVANew;
	}
	else
	{
		wRLinePFNew = 0;
	}
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineVarNew + (INT32S)wRLineVarFilter * 31 + (INT32S)s_wVarRes;
	s_wVarRes = dwTemp & 0x001F;
	wRLineVarFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineVANew + (INT32S)wRLineVAFilter * 31 + (INT32S)s_wVARes;
	s_wVARes = dwTemp & 0x001F;
	wRLineVAFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLinePFNew + (INT32S)wRLinePFFilter * 31 + (INT32S)s_wPFRes;
	s_wPFRes = dwTemp & 0x001F;
	wRLinePFFilter = dwTemp >> 5;
}

void	sRLineRms3timeAvgUpdate(void)
{
	g_uwRLineRms3time[0] = g_uwRLineRms3time[1];
	g_uwRLineRms3time[1] = g_uwRLineRms3time[2];
	g_uwRLineRms3time[2] = wRLineVoltNew;
	
	g_uwRLineRms3timeAvg = (g_uwRLineRms3time[0] + g_uwRLineRms3time[1] + g_uwRLineRms3time[2]) / 3;	// 市电电压三次历史值平均
	g_uwRLineRms3timeAvgPeak = (INT16U)(((INT32U)g_uwRLineRms3timeAvg * 181) >> 7);						// ×1.141 = 市电电压对应的直流幅值
}

void	sLineZeroLossClr(void)
{
	wRLineZeroLossCnt = 0;
}

void	sLineZeroLossChk(INT16U	uwFilter)
{
	wRLineZeroLossCnt++;
	if(wRLineZeroLossCnt > uwFilter)
	{
		wRLineZeroLossCnt = 0;
		
		fRLineStatus.bits.VoltLoss = 1;
		fRLineStatus.bits.LineVoltHLoss = 1;
		fRLineStatus.bits.LineVoltLLoss = 1;
		fRLineStatus.bits.FreqLoss = 1;
		fRLineStatus.bits.LineFreqHLoss = 1;
		fRLineStatus.bits.LineFreqLLoss = 1;
		fRLineStatus.bits.PhaseLoss = 0;
		fRLineStatus.bits.WaveLoss = 1;
		wRLineVoltNew = 0;
		wRLineCurrNew = 0;
		wRLineWattNew = 0;
		wRLineMidVoltNew = 0;
		wRLineFreqNew = 0;
		wRLineVoltFilter = 0;
		wRLineCurrFilter = 0;
		wRLineWattFilter = 0;
		wRLineMidVoltFilter = 0;
		wRLineFreqFilter = 0;

		T_ALARM_DATA.bits.bGridUV = true;
		T_ALARM_DATA.bits.bGridOV = true;
		T_ALARM_DATA.bits.bGridUF = true;
		T_ALARM_DATA.bits.bGridOF = true;
	}

	// 按照模式，更新市电保护值
	if(uwGetModelLV())
	{
		if(suwGetEEGridInputRange() == cAPL)
		{
			g_uwLineVoltHLoss = cLineVolt140V;
			g_uwLineVoltH2Loss = cLineVolt140V;
			g_uwLineVoltLLoss = cLineVolt65V;
			g_uwLineVoltL2Loss = cLineVolt65V;
			g_uwLineVoltHBack = cLineVolt135V;
			g_uwLineVoltLBack = cLineVolt70V;
			g_uwLineFreqHLoss = cLineFreq65Hz;
			g_uwLineFreqH2Loss = cLineFreq65Hz;
			g_uwLineFreqLLoss = cLineFreq40Hz;
			g_uwLineFreqL2Loss = cLineFreq40Hz;
			g_uwLineFreqHBack = cLineFreq63Hz;
			g_uwLineFreqLBack = cLineFreq42Hz;	
		
		}	
		else	// UPS
		{	
			g_uwLineVoltHLoss = cLineVolt140V;
			g_uwLineVoltH2Loss = cLineVolt140V;
			g_uwLineVoltLLoss = cLineVolt90V;
			g_uwLineVoltL2Loss = cLineVolt90V;
			g_uwLineVoltHBack = cLineVolt135V;
			g_uwLineVoltLBack = cLineVolt95V;
			g_uwLineFreqHLoss = cLineFreq65Hz;
			g_uwLineFreqH2Loss = cLineFreq65Hz;
			g_uwLineFreqLLoss = cLineFreq40Hz;
			g_uwLineFreqL2Loss = cLineFreq40Hz;
			g_uwLineFreqHBack = cLineFreq63Hz;
			g_uwLineFreqLBack = cLineFreq42Hz;
		}
	}
	else
	{
		if(suwGetEEGridInputRange() == cAPL)
		{
			g_uwLineVoltHLoss = cLineVolt280V;
			g_uwLineVoltH2Loss = cLineVolt280V;
			g_uwLineVoltLLoss = cLineVolt80V;
			g_uwLineVoltL2Loss = cLineVolt80V;//cLineVolt90V;
			g_uwLineVoltHBack = cLineVolt270V;
			g_uwLineVoltLBack = cLineVolt90V;//cLineVolt100V;
			g_uwLineFreqHLoss = cLineFreq65Hz;
			g_uwLineFreqH2Loss = cLineFreq65Hz;
			g_uwLineFreqLLoss = cLineFreq40Hz;
			g_uwLineFreqL2Loss = cLineFreq40Hz;
			g_uwLineFreqHBack = cLineFreq63Hz;
			g_uwLineFreqLBack = cLineFreq42Hz;	
		}	
		else	// UPS
		{	
			g_uwLineVoltHLoss = cLineVolt280V;
			g_uwLineVoltH2Loss = cLineVolt280V;
			g_uwLineVoltLLoss = cLineVolt80V;
			g_uwLineVoltL2Loss = cLineVolt80V;
			g_uwLineVoltHBack = cLineVolt270V;
			g_uwLineVoltLBack = cLineVolt90V;
			g_uwLineFreqHLoss = cLineFreq65Hz;
			g_uwLineFreqH2Loss = cLineFreq65Hz;
			g_uwLineFreqLLoss = cLineFreq40Hz;
			g_uwLineFreqL2Loss = cLineFreq40Hz;
			g_uwLineFreqHBack = cLineFreq63Hz;
			g_uwLineFreqLBack = cLineFreq42Hz;	
		}
	}

}


void	sRLineVoltChk(INT8U bFilter)
{
	static	INT16U	s_uwRFeedLineVChkCnt = 0;
	static	INT16U	s_uwUnderCnt = 0;
	static	INT16U	s_uwUnder2Cnt = 0;
	static	INT16U	s_uwOverCnt = 0;
	static	INT16U	s_uwOver2Cnt = 0;
	
	if(T_ALARM_DATA.bits.bGridUV || T_ALARM_DATA.bits.bGridOV)
	{
		if(sb16UInRangeChk(wRLineVoltNew,g_uwLineVoltHBack,g_uwLineVoltLBack,bFilter,&s_uwRFeedLineVChkCnt) == true)
		{
			T_ALARM_DATA.bits.bGridUV = false;
			T_ALARM_DATA.bits.bGridOV = false;
			s_uwUnderCnt = 0;
			s_uwUnder2Cnt = 0;
			s_uwOverCnt = 0;
			s_uwOver2Cnt = 0;
		}
	}
	else
	{
		// 市电一阶欠压丢失
		if(sb16UUnderLevelChk(wRLineVoltNew, g_uwLineVoltLLoss, g_wVoltLLossTime + g_dwLvrtLossTime, &s_uwUnderCnt) == true)
		{
			T_ALARM_DATA.bits.bGridUV = true;
		}
		
		// 市电二阶欠压丢失
		if(sb16UUnderLevelChk(wRLineVoltNew, g_uwLineVoltL2Loss, g_wVoltL2LossTime+ g_dwLvrtLossTime, &s_uwUnder2Cnt) == true)
		{
			T_ALARM_DATA.bits.bGridUV = true;
		}
		
		// 市电一阶过压丢失
		if(sb16UOverLevelChk(wRLineVoltNew, g_uwLineVoltHLoss, g_wVoltHLossTime + g_dwHvrtLossTime, &s_uwOverCnt) == true)
		{
			T_ALARM_DATA.bits.bGridOV = true;
		}
		
		// 市电二阶过压丢失
		if(sb16UOverLevelChk(wRLineVoltNew, g_uwLineVoltH2Loss, g_wVoltH2LossTime+g_dwHvrtLossTime, &s_uwOver2Cnt)== true)
		{
			T_ALARM_DATA.bits.bGridOV = true;
		}
	}
}


void	sLineFreqChk(INT8U bFilter)
{
	static	 INT16U	s_uwLineFeedFChkCnt = 0;
	static 	 INT16U s_uwUnderRCnt = 0;
	static 	 INT16U s_uwUnder2RCnt = 0;
	static   INT16U s_uwOverRCnt = 0;
	static   INT16U s_uwOver2RCnt = 0;
	INT16U uwLineFreqHBackTemp;
	INT16U uwLineFreqLBackTemp;
	
	if(T_ALARM_DATA.bits.bGridUF || T_ALARM_DATA.bits.bGridOF)
	{	
		//if(g_uwLineFreFastLossFlag&&(swGetEEStandard() == cItaly))
		if(0)
		{
			uwLineFreqHBackTemp = cLineFreq63Hz;//cLineFreq50Hz1;
			uwLineFreqLBackTemp = cLineFreq42Hz;//cLineFreq49Hz9;
		}
		else
		{
			uwLineFreqHBackTemp = g_uwLineFreqHBack;
			uwLineFreqLBackTemp =g_uwLineFreqLBack;
		}
		if(sb16UInRangeChk(wRLineFreqNew,uwLineFreqHBackTemp,uwLineFreqLBackTemp,bFilter,&s_uwLineFeedFChkCnt) == true)
		{
			T_ALARM_DATA.bits.bGridUF = false;
			T_ALARM_DATA.bits.bGridOF = false;
			s_uwUnderRCnt = 0;
			s_uwUnder2RCnt = 0;
			s_uwOverRCnt = 0;
			s_uwOver2RCnt = 0;
		}
	}
	else
	{
		// 市电一阶欠频丢失
		if(sb16UUnderLevelChk(wRLineFreqNew, g_uwLineFreqLLoss, g_wFreLLossTime, &s_uwUnderRCnt) == true)
		{
			T_ALARM_DATA.bits.bGridUF = true;
		}

		// 市电二阶欠频丢失
		if(sb16UUnderLevelChk(wRLineFreqNew, g_uwLineFreqL2Loss, g_wFreL2LossTime, &s_uwUnder2RCnt) == true)
		{
			T_ALARM_DATA.bits.bGridUF = true;
		}

		// 市电一阶过频丢失
		if(sb16UOverLevelChk(wRLineFreqNew, g_uwLineFreqHLoss, g_wFreHLossTime, &s_uwOverRCnt))
		{
			T_ALARM_DATA.bits.bGridOF = true;	
		}

		// 市电二阶过频丢失
		if(sb16UOverLevelChk(wRLineFreqNew, g_uwLineFreqH2Loss, g_wFreH2LossTime, &s_uwOver2RCnt))
		{
			T_ALARM_DATA.bits.bGridOF = true;
		}
		
		//if(hoMSEN3 &&(swGetEEStandard()==cItaly))
		if(0)
		{
			if(sb16UOverLevelChk(wRLineFreqNew, g_uwLineFreqFastHLoss, 1, &s_uwOverRCnt))
			{
//				fRLineStatus.bits.FeedFreqLoss = 1;
//				fRLineStatus.bits.LineFreqHLoss = 1;
//				g_uwLineFreFastLossFlag = 1;
			}
			if(sb16UUnderLevelChk(wRLineFreqNew, g_uwLineFreqFastLLoss, 1, &s_uwUnderRCnt) == true)
			{
//				fRLineStatus.bits.FeedFreqLoss = 1;
//				fRLineStatus.bits.LineFreqLLoss = 1;
//				g_uwLineFreFastLossFlag = 1;
			}
		}
	}
}	

void	sGridOverLoadChk(INT16U uwGridOverLoadLevel, INT16U uwFilter)
{
	static INT16U s_uwGridOverLoadChkCnt = 0;
	
	if(T_ALARM_DATA.bits.bGridOverLoad == true)
	{
		if(sb16UUnderLevelChk(wRLineWattNew, uwGridOverLoadLevel - 500, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_ALARM_DATA.bits.bGridOverLoad = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wRLineWattNew, uwGridOverLoadLevel, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_ALARM_DATA.bits.bGridOverLoad = true;
		}
	}
}

void	sGridCurrOverChk(INT16U uwGridOverCurrLevel, INT16U uwFilter)
{
	static INT16U s_uwGridOverLoadChkCnt = 0;

	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}
	if(T_FAULT_DATA.bits.bGridCurrOver == true)
	{
		if(sb16UUnderLevelChk(wRLineCurrNew, uwGridOverCurrLevel - 500, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_FAULT_DATA.bits.bGridCurrOver = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wRLineCurrNew, uwGridOverCurrLevel, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_FAULT_DATA.bits.bGridCurrOver = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cGridCurrOver);
			}
		}
	}
}

void	sGridCurrOver2Chk(INT16U uwGridOverCurrLevel, INT16U uwFilter)
{
	static INT16U s_uwGridOverLoadChkCnt = 0;

	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}
	if(T_FAULT_DATA.bits.bGridCurrOver == true)
	{
		if(sb16UUnderLevelChk(wRLineCurrNew, uwGridOverCurrLevel - 500, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_FAULT_DATA.bits.bGridCurrOver = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wRLineCurrNew, uwGridOverCurrLevel, uwFilter, &s_uwGridOverLoadChkCnt))
		{
			T_FAULT_DATA.bits.bGridCurrOver = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cGridCurrOver);
			}
		}
	}
}
void	sRLineXXSecondsAveVoltCal(INT16U wSeconds)
{
	static INT16U wCycleCnt = 0;
	static INT32U dwLineSum = 0;
	static INT16U wLineArrayCnt = 0;
	
	dwLineSum += wRLineVoltNew;
	wCycleCnt++;
	if(wCycleCnt >= wSeconds * 50)
	{
		OS_ENTER_CRITICAL();
		g_uwRLineXXSecondsAveVolt = (INT16U)(dwLineSum / wCycleCnt);
		*(wRLineAveVoltArray + wLineArrayCnt) = g_uwRLineXXSecondsAveVolt;
		OS_EXIT_CRITICAL();
		if(++wLineArrayCnt >= LineAveVoltArrayLenth)
		{
			wLineArrayCnt = 0;
		}
		dwLineSum = 0;
		wCycleCnt = 0;
	}
}

INT16U	swGetRLineLongTimeAverage(void)
{
	INT16U wTempCnt = 0;
	INT32U dwTempSum = 0;
	INT16U wTempAverageVolt = 0;
	
	for(wTempCnt = 0; wTempCnt < LineAveVoltArrayLenth; wTempCnt++)	
	{
		dwTempSum += *(wRLineAveVoltArray + wTempCnt);
	}
	wTempAverageVolt = (INT16U)(dwTempSum / LineAveVoltArrayLenth);
	return(wTempAverageVolt);
}

void	sLineVoltLTAvgCalChk(void)
{
	static INT16S s_wDelayCnt = 0;
	
	sRLineXXSecondsAveVoltCal(10);
	if(++s_wDelayCnt > 500)
	{
		s_wDelayCnt = 0;
	}
	
	if(s_wDelayCnt == 0)
	{
		wRLineLTVolt = swGetRLineLongTimeAverage();
//		if(wRLineLTVolt > suwGetEELineVoltLTLoss())
//		{
//			fRLineStatus.bits.FeedVoltLongTimeLoss = 1;
//			uniWarningCode.BIT.uwLineVoltHLTLoss = 1;
//		}
//		else if(wRLineLTVolt < (suwGetEELineVoltLTLoss() - 10))
//		{
//			fRLineStatus.bits.FeedVoltLongTimeLoss = 0;
//			uniWarningCode.BIT.uwLineVoltHLTLoss = 0;
//		}
	}
	fRLineStatus.bits.VoltLongTimeLoss = fRLineStatus.bits.FeedVoltLongTimeLoss;
}

void	sLinePhaseChk(INT8U bFilter)
{
//	static	 INT8U	s_ubLinePhaseChkCnt = 0;
	if(fRLineStatus.bits.PhaseLoss)
//	{
//		if(!g_uwLinePhaseErr)
//		{
//			if(++s_ubLinePhaseChkCnt > bFilter)
//			{
//				s_ubLinePhaseChkCnt = 0;
//				fRLineStatus.bits.PhaseLoss = 0;
//			}
//		}
//		else
//		{
//			s_ubLinePhaseChkCnt = 0;
//		}
//	}
//	else
//	{
//		if(g_uwLinePhaseErr)
//		{
//			if(++s_ubLinePhaseChkCnt > bFilter)
//			{
//				s_ubLinePhaseChkCnt = 0;
//				fRLineStatus.bits.PhaseLoss = 1;
//			}
//		}
//		else
//		{
//			s_ubLinePhaseChkCnt = 0;
//		}
//	}
	
	if(swGetWorkMode() == cBypassMode || swGetWorkMode() == cLineMode)
	{
		fRLineStatus.bits.PhaseLoss = 0;
//		s_ubLinePhaseChkCnt = 0;
	}
}

INT16S	g_uwRLineRms3timeAvgPeakTemp = 0;
void	sLineWaveChk(INT16S wLinvVolt, INT16S wSinValue, INT16S wOPCurr)
{
	static INT16U wWaveLossCnt = 0;
	static INT16U wWaveOkCnt = 0;
	INT16S wLineWaveVoltHighLoss;
	INT16S wLineWaveVoltLowLoss;
	INT16S wTemp;

	// 市电模式，UPS
	//if(suwGetEEGridInputRange())	// for test
	if(1)
	{
		wTemp = (INT16S)(((INT32S)g_uwRLineRms3timeAvgPeak * wSinValue) >> 14);		// 正弦化
		g_uwRLineRms3timeAvgPeakTemp = wTemp;
		wLineWaveVoltHighLoss = wTemp + cLineVolt70V;
		wLineWaveVoltLowLoss = wTemp - cLineVolt70V;
		if(((wLinvVolt > wLineWaveVoltHighLoss) || (wLinvVolt < wLineWaveVoltLowLoss))
			&& wOPCurr < cOp15A && wOPCurr > -cOp15A)
		{
			wWaveOkCnt = 0;
			if(fRLineStatus.bits.WaveLoss == false)
			{
				if(++wWaveLossCnt >= 20)//30
				{
					fRLineStatus.bits.WaveLoss = true;
					T_ALARM_DATA.bits.bGridAbnormalAlarm = true;
					OSISREventSend(cPrioSuper, eSuperLineLoss);
				}
			}
		}
		else
		{
			wWaveLossCnt = 0;
			if(fRLineStatus.bits.WaveLoss == true)
			{
				if(++wWaveOkCnt >= gi_wSinePointMaxTwo)
				{
					T_ALARM_DATA.bits.bGridAbnormalAlarm = false;
					fRLineStatus.bits.WaveLoss = false;
				}
			}
		}
	}
	else	// 市电模式，APL
	{
		if(((wLinvVolt < 500 && wLinvVolt > -500) || wLinvVolt > 3950 || wLinvVolt < -3950)
			&& wOPCurr < cOp15A && wOPCurr > -cOp15A)
		{
			if(wWaveLossCnt < gi_wSinePointOneFour)	// 5ms
			{
				wWaveLossCnt++;
			}
			else
			{
				fRLineStatus.bits.WaveLoss = true;
				T_ALARM_DATA.bits.bGridAbnormalAlarm = true;
				OSISREventSend(cPrioSuper, eSuperLineLoss);
				wWaveOkCnt = 0;
			}
		}
		else
		{
			wWaveLossCnt = 0;
			if(wWaveOkCnt < gi_wSinePointMaxTwo)
			{
				wWaveOkCnt++;
			}
			else
			{
				T_ALARM_DATA.bits.bGridAbnormalAlarm = false;
				fRLineStatus.bits.WaveLoss = false;
			}
		}
		
		wTemp = (INT16S)(((INT32S)swGetPreSinePeriodCntNew()) >> 7);	// 52*2.5 = 130 = 1>>7
		if(wTemp < 76)	// eg:(50Hz:20000)/128=156*52us=8.1ms
		{
			wTemp = 76;	// 76*52 = 3.952ms
		}
		if(wLinvVolt > gi_wRGeneratorVoltMax)
		{
			gi_wRGeneratorVoltMax = wLinvVolt;
		}
		else if(wLinvVolt < gi_wRGeneratorVoltMin)
		{
			gi_wRGeneratorVoltMin = wLinvVolt;
		}
		if(((gi_wRGeneratorVoltMax - gi_wRGeneratorVoltMin) > 400)
			|| wOPCurr > cOp5A || wOPCurr < -cOp5A)
		{
			gi_wRGeneratorWaveChkCnt = 0;
			gi_wRGeneratorVoltMax = wLinvVolt;
			gi_wRGeneratorVoltMin = wLinvVolt;
		}
		if(++gi_wRGeneratorWaveChkCnt >= wTemp)
		{
			wWaveOkCnt = 0;
			gi_wRGeneratorWaveChkCnt = 0;
			fRLineStatus.bits.WaveLoss = true;
			T_ALARM_DATA.bits.bGridAbnormalAlarm = true;
			OSISREventSend(cPrioSuper, eSuperLineLoss);
		}
	}
}

INT16S	swGetCalculate(INT16S x, INT16S y, INT32S m, INT32S dwOneOfTenRate,INT16S wInDecreasFun)
{
	INT32S dwTemp;
	INT16S wResult;
	
	if(m < 0)
	{
		return x;
	}
	else
	{		
		dwTemp = m % dwOneOfTenRate;
		if(wInDecreasFun == cDecreaseFun)
		{
			wResult = (INT16S)((dwTemp * (x - y)) / dwOneOfTenRate);
			wResult = x - wResult;
		}
		else
		{
			wResult = (INT16S)((dwTemp * (y - x)) / dwOneOfTenRate);
			wResult = wResult + x;
		}				
		return wResult;
	}
}


INT16S	swGetRLineRms3timeAvgPeakTemp(void)
{
	return g_uwRLineRms3timeAvgPeakTemp;
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetRLineVoltNew(void)
{
	return wRLineVoltNew;
}

INT16S	swGetRLineCurrNew(void)
{
	return wRLineCurrNew;
}

INT16U	suwGetRLineChgCurrNew(void)
{
	return uwRLineChgCurr;
}

INT16S	swGetRLineFreqNew(void)
{
	return wRLineFreqNew;
}

INT16S	swGetRLineWattNew(void)
{
	return wRLineWattNew;
}

INT16S	swGetRLineMidVoltNew(void)
{
	return wRLineMidVoltNew;
}

INT16S	swGetRLineMidDcVoltNew(void)
{
	return wRLineMidDcVoltNew;
}

INT16S	swGetRLineVarNew(void)
{
	return wRLineVarNew;
}

INT16S	swGetRLineVANew(void)
{
	return wRLineVANew;
}

INT16S	swGetRLinePFNew(void)
{
	return wRLinePFNew;
}

INT16S	swGetRLineVoltFilter(void)
{
	return wRLineVoltFilter;
}

INT16S	swGetRLineCurrFilter(void)
{
	return wRLineCurrFilter;
}

INT16S	swGetRLineFreqFilter(void)
{
	return wRLineFreqFilter;
}

INT16S	swGetRLineWattFilter(void)
{
	return wRLineWattFilter;
}

INT16S	swGetRLineMidVoltFilter(void)
{
	return wRLineMidVoltFilter;
}

INT16S	swGetRLineMidDcVoltFilter(void)
{
	return wRLineMidDcVoltFilter;
}

INT16S	swGetRLineVarFilter(void)
{
	return wRLineVarFilter;
}

INT16S	swGetRLineVAFilter(void)
{
	return wRLineVAFilter;
}

INT16S	swGetRLinePFFilter(void)
{
	return wRLinePFFilter;
}

INT16U	swGetLinePeriodCntNew(void)
{
	return gi_uwLinePeriodCntNew;
}

INT16U	swGetRLineRms3timeAvgPeak(void)
{
	return g_uwRLineRms3timeAvgPeak;
}


INT8U	sbGetLineVoltLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if((T_ALARM_DATA.bits.bGridUV == true) || (T_ALARM_DATA.bits.bGridOV == true))
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else 
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetLineFreqLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if((T_ALARM_DATA.bits.bGridUF == true) || (T_ALARM_DATA.bits.bGridOF == true))
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else 
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetLineWaveLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if(fRLineStatus.bits.WaveLoss)
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else 
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetLinePhaseLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if(fRLineStatus.bits.PhaseLoss)
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetLineLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if((T_ALARM_DATA.bits.bGridUV == true) || (T_ALARM_DATA.bits.bGridOV == true)\
	|| (T_ALARM_DATA.bits.bGridUF == true) || (T_ALARM_DATA.bits.bGridOF == true))
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else 
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetPalLineLossStatus(void)
{
	OS_ENTER_CRITICAL();

	if((T_ALARM_DATA.bits.bGridUV == true) || (T_ALARM_DATA.bits.bGridOV == true)\
	|| (T_ALARM_DATA.bits.bGridUF == true) || (T_ALARM_DATA.bits.bGridOF == true))
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

INT8U	sbGetLineFeedLossStatus(void)
{
	OS_ENTER_CRITICAL();
	if((T_ALARM_DATA.bits.bGridUV == true) || (T_ALARM_DATA.bits.bGridOV == true)\
	|| (T_ALARM_DATA.bits.bGridUF == true) || (T_ALARM_DATA.bits.bGridOF == true))
	{
		OS_EXIT_CRITICAL();
		return(true);
	}
	else 
	{
		OS_EXIT_CRITICAL();
		return(false);
	}
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetRLineVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRLineVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineVoltNew + (INT32S)wRLineVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRLineVoltFilter = dwTemp >> 5;
}

void	sSetRLineCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	if(swGetWorkMode() != cLineMode && swGetWorkMode() != cChgMode)
	{
		wRLineCurrNew = 0;
		wRLineCurrFilter = 0;
	}
	else
	{
		wRLineCurrNew = (INT16S)(((INT32S)wRLineVANew * 1000) / wRLineVoltNew);
		
		// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
		dwTemp = (INT32S)wRLineCurrNew + (INT32S)wRLineCurrFilter * 31 + (INT32S)s_wRes;
		s_wRes = dwTemp & 0x001F;
		wRLineCurrFilter = dwTemp >> 5;
	}

}

void	sSetRLineFreqNew(INT16U uwLinePeriod)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	if(uwLinePeriod != 0)
	{
		wRLineFreqNew = 100000000 / uwLinePeriod;
	}
	else
	{
		wRLineFreqNew = 0;
	}

	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineFreqNew + (INT32S)wRLineFreqFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRLineFreqFilter = dwTemp >> 5;
}

void	sSetRLineWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	if(swGetWorkMode() != cLineMode && swGetWorkMode() != cChgMode)
	{
		wRLineWattNew = 0;
		wRLineWattFilter = 0;
	}
	else
	{
		wRLineWattNew = wWatt;
	//	wRLineWattNew = (INT16S)(((INT32S)wRLineVoltFilter * wRLineCurrFilter) / 1000);
		
		// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
		dwTemp = (INT32S)wRLineWattNew + (INT32S)wRLineWattFilter * 31 + (INT32S)s_wRes;
		s_wRes = dwTemp & 0x001F;
		wRLineWattFilter = dwTemp >> 5;
	}
}

void	sSetRLineMidVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRLineMidVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineMidVoltNew + (INT32S)wRLineMidVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRLineMidVoltFilter = dwTemp >> 5;
}

void	sSetRLineMidDcVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRLineMidDcVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRLineMidDcVoltNew + (INT32S)wRLineMidDcVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRLineMidDcVoltFilter = dwTemp >> 5;
}


