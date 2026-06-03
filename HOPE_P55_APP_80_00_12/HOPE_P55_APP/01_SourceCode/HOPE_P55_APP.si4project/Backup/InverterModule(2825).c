/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__INV_MODULE_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/


/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
//INT16U g_wOPRMSRatedVolt;
extern INT16S g_wSolarSigPowerLoad;

//INT16S gi_wSinePointMax;
//INT16S g_wRSinPointer;
//INT16S g_wRSinPointerwThetaTemp;

/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16S wRInvVoltNew;		// 0.1V
INT16S wRInvCurrNew;		// 0.01A
INT16S wRInvWattNew;		// 1W


INT16S wRInvFreqNew;		// 0.01Hz
INT16S wRInvDcVoltNew;		// 0.1V
INT16S wRInvDCVNew;			// 0.001V
INT16S wRInvDCINew;			// 0.001A
INT16S wRInvVarNew;			// 1Var
INT16S wRInvVANew;			// 1VA
INT16S wRInvPFNew;			// 0.001

INT16S wRInvVoltFilter;		// 0.1V
INT16S wRInvCurrFilter;		// 0.01A
INT16S wRInvFreqFilter;		// 0.01Hz
INT16S wRInvWattFilter;		// 1W
INT16S wRInvDcVoltFilter;	// 0.1V
INT16S wRInvDCVFilter;		// 0.001V
INT16S wRInvDCIFilter;		// 0.001A
INT16S wRInvVarFilter;		// 1Var
INT16S wRInvVAFilter;		// 1VA
INT16S wRInvPFFilter;		// 0.001

INT32U gi_udwSineZeroTimeOld;	// 上次逆变过零CAP值,50Hz=1800000,60Hz=1500000
INT16U gi_uwSinePeriodCntNew;	// 逆变周期值,50Hz=20000,60Hz=16667
INT16U gi_uwInvertTd;
INV_TD g_strInvLineTd;

INT16S g_wPhaseLockStep = 8;
INT16S g_wPhaseLockLimit = 120;//120;
//INT16U g_uwStepHighLimit = 120;
INT16U g_uwPhaseLossLimit = 2000;//500;//250;//2000;
INT16U g_uwPhaseOKLimit = 250;//125;//75;//250;
INT16U g_uwPeriodOKLimit = 200;//50;//25;//200;

INT16U wRSinPionterDeltaQ15;

/********************************************************************************
* Output variables																*
********************************************************************************/


/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16S g_wPwmPeriod = cPWMCntlPeriod50Hz;

INT16S g_wRSinAmp = 10408;	// 230*1.4142*32=10408
INT16S g_wOPSinVpp = 10408;
INT16S g_wRNewSinAmp = 0;
INT16S g_wRNewSinAmpTemp;

INT32S g_dwRInvDCVoltSum;
INT16S g_wRInvDCVoltCnt;

INT16S g_wRInvDCVoltCntl;
INT16S g_wRDCVoltP;
INT16S g_wRDCVoltI;
INT16S g_wRDCVoltI_Res;

INT16S g_wRInvDCCurrCtrl;
INT16S g_wRDCCurrP;
INT16S g_wRDCCurrI;
INT16S g_wRDCCurrI_Res;
INT16U g_wRInvDCOverChkCnt;

INT16U g_uwInverterPeriodCntSet;
INT16U g_uwInverterPeriodCntLow;
INT16U g_uwInverterPeriodCntHigh;
INT16U g_uwInverterPeriodCntNew;

INT16U g_uwPeriodDelta;
INT16U g_uwPhaseDelta;

union INVERTER_STATUS_TABLE fInverterStatus;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sInverterPhaseLock(INT16U wInvPeriodCnt,INV_TD *pInvTd,INT16U wRefPeriodCnt,INT16U wStep);
void 	sAdjPhase(INT16U wStep);
void	sFreeRun(void);
INV_TD	*spGetInvTd(void);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sInverterInitial(void)
{
	sInverterParaUpdate();
	
	g_dwRInvDCVoltSum = 0;
	g_wRInvDCVoltCnt = 0;
	
	g_wRInvDCVoltCntl = 0;
	g_wRDCVoltP = 0;
	g_wRDCVoltI = 0;
	g_wRDCVoltI_Res = 0;
	
	g_wRInvDCCurrCtrl = 0;
	g_wRDCCurrP = 0;
	g_wRDCCurrI = 0;
	g_wRDCCurrI_Res = 0;
	g_wRInvDCOverChkCnt = 0;
	
	if(suwGetEEACOutputRatedFreq() == cFreq60hzConst)
	{
		// 离网控制参数
		g_uwInverterPeriodCntSet = cPeriod60Hz;
		g_uwInverterPeriodCntNew = cPeriod60Hz;
		g_uwInverterPeriodCntLow = cPeriod67Hz;
		g_uwInverterPeriodCntHigh = cPeriod38Hz;
		
		wRSinPionterDeltaQ15 = 19661;	// 20000 * 16384 / 16666.67

		sFBINVControl60hzParaInit();
	}
	else if(suwGetEEACOutputRatedFreq() == cFreq50hzConst)
	{
		// 离网控制参数
		g_uwInverterPeriodCntSet = cPeriod50Hz;
		g_uwInverterPeriodCntNew = cPeriod50Hz;
		g_uwInverterPeriodCntLow = cPeriod67Hz;
		g_uwInverterPeriodCntHigh = cPeriod38Hz;
		
		wRSinPionterDeltaQ15 = 16384;	// 20000 * 16384 / 20000

		sFBINVControl50hzParaInit();
	}	

	sSetFBInvCtrlSts(cFBWait);
}


void	sInverterParaUpdate(void)
{
	// (2300/10)*1.41421*32=10408
	g_wOPSinVpp = (INT16S)(((INT32S)uwGetOPRMSRatedVolt() * 2317) >> 9);
	//g_wOPSinVpp = 0;//(INT16S)(((INT32S)uwGetOPRMSRatedVolt() * 2317) >> 9);
}

void	sRInvPowerCal(void)
{
	static INT16S s_wVarRes = 0;
	static INT16S s_wVARes = 0;
	static INT16S s_wPFRes = 0;
	INT32S dwTemp;
	
	dwTemp = ((INT32S)wRInvVoltNew * wRInvCurrNew + 500) / 1000;
	if(swAbs(dwTemp) < swAbs(wRInvWattNew))
	{
		dwTemp = wRInvWattNew;
	}
	wRInvVANew = swAbs(dwTemp);
	
	dwTemp = ((INT32S)wRInvVANew * wRInvVANew) - ((INT32S)wRInvWattNew * wRInvWattNew);
	if(dwTemp > 0)
	{
		wRInvVarNew = swRoot((INT32U)dwTemp);
	}
	else	
	{
		wRInvVarNew = 0;
	}
	
	if(wRInvVANew != 0)
	{
		wRInvPFNew = ((INT32S)wRInvWattNew * 1000) / wRInvVANew;
	}
	else
	{
		wRInvPFNew = 0;
	}
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvVarNew + (INT32S)wRInvVarFilter * 31 + (INT32S)s_wVarRes;
	s_wVarRes = dwTemp & 0x001F;
	wRInvVarFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvVANew + (INT32S)wRInvVAFilter * 31 + (INT32S)s_wVARes;
	s_wVARes = dwTemp & 0x001F;
	wRInvVAFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvPFNew + (INT32S)wRInvPFFilter * 31 + (INT32S)s_wPFRes;
	s_wPFRes = dwTemp & 0x001F;
	wRInvPFFilter = dwTemp >> 5;
}

void	sInverterPhaseLock(INT16U wInvPeriodCnt,INV_TD *pInvTd,INT16U wRefPeriodCnt,INT16U wStep)
{
	static INT8U s_wPhaseLockCnt = 0;
	INT16U wInvPeriodLast;
	INT16U wInvTd;
	
	wInvPeriodLast = swGetSinePeriodCntNew();
	wInvTd = pInvTd->InvTd;
	if(wInvPeriodCnt >= wRefPeriodCnt)
	{
		fInverterStatus.bits.LineFGInvF = 0;
		g_uwPeriodDelta = wInvPeriodCnt - wRefPeriodCnt;
	}
	else if(wInvPeriodCnt < wRefPeriodCnt)
	{
		fInverterStatus.bits.LineFGInvF = 1;
		g_uwPeriodDelta = wRefPeriodCnt - wInvPeriodCnt;
	}
	if(pInvTd->IntConflict)
	{
		g_uwPhaseDelta = wInvTd;
		fInverterStatus.bits.InvPhaseLead = 1;
	}
	else
	{
		if((wInvPeriodCnt >> 1) >= wInvTd)						/*	若差很小，表示逆变滞后							*/
		{
			fInverterStatus.bits.InvPhaseLead = 0;				/*	逆变滞后 情况1			   				*/
			g_uwPhaseDelta = wInvTd; 							/*	相位差等于InvTd	     		 			*/
		}
		else
		{
			fInverterStatus.bits.InvPhaseLead = 1;				/*	否则逆变超前								*/
			if (wInvPeriodCnt >= wInvTd)
			{
				if (wRefPeriodCnt > wInvTd)
				{
					g_uwPhaseDelta = wInvPeriodCnt - wInvTd;	/*	情况5									*/
				}
				else
				{
					g_uwPhaseDelta = 0;							/*	则宁可保守估计为零，也不用本周			*/
									   							/*	期逆变减上周期市电。 情况4						*/
				}
			}
			else
			{
				if (wInvTd < wRefPeriodCnt)						/*	逆变在市电的一个周期内由滞后变成					*/
				{												/*	超前但是由于不知道本周期的相位差					*/
					g_uwPhaseDelta = wRefPeriodCnt - wInvTd;	/*	所以过去把它当成了滞后的情况导致					*/
																/*	向相反的方向调节。现在改成逆变超					*/
				}												/*	前相位角为零。情况3							*/
				else
				{
					g_uwPhaseDelta = 0;							/*	所有的周期都大却又不算异常						*/
																/*	如果与此试点本该超前，但此时它比					*/
					g_uwPeriodDelta = wInvTd - wInvPeriodCnt;	/*	因为预测的市电早就该过零了。 情况2					*/
					fInverterStatus.bits.LineFGInvF = 1;		/*	不管过去市电与逆变的关系现在必定市电最大*/
				}
			}
		}
	}
	
	wStep = 18;
	//	if((g_uwPhaseDelta <= g_uwPhaseOKLimit) && (g_uwPeriodDelta <= g_uwPeriodOKLimit)
	//	|| (!suwGetGridInputRange() && g_uwParaMode == cMasterMode))
	if((g_uwPhaseDelta <= g_uwPhaseOKLimit) && (g_uwPeriodDelta <= g_uwPeriodOKLimit))
	{						// g_uwPhaseOKLimit = 250				g_uwPeriodOKLimit = 200
		if(!fInverterStatus.bits.PhaseLocked)
		{
			if(++s_wPhaseLockCnt > 5)
			{
				s_wPhaseLockCnt = 0;
				OS_ENTER_CRITICAL();
				fInverterStatus.bits.PhaseLocked = 1;
				OS_EXIT_CRITICAL();
			}
		}
	}
	else
	{
		s_wPhaseLockCnt = 0;
		if(g_uwPhaseDelta > g_uwPhaseLossLimit)	// g_uwPhaseLossLimit = 2000
		{
			OS_ENTER_CRITICAL();
			fInverterStatus.bits.PhaseLocked = 0;
			OS_EXIT_CRITICAL();
		}
	}
	
	if(fInverterStatus.bits.LineFGInvF)  					/*	Delta F >0								*/
	{
		if(fInverterStatus.bits.InvPhaseLead)				/*	Delta P <0								*/
		{
			g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew + wStep;
		}
		else
		{
			sAdjPhase(wStep);
		}
	}
	else 													/*	Delta F <0								*/
	{
		if (fInverterStatus.bits.InvPhaseLead)				/*	Delta P <0								*/
		{
			sAdjPhase(wStep);
		}
		else												/*	Delta P >0								*/
		{
			g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew - wStep;
		}
	}
	
	if(g_uwInverterPeriodCntNew >= wInvPeriodLast)
	{
		if(g_uwInverterPeriodCntNew >= (wInvPeriodLast+g_wPhaseLockLimit))
		{
			g_uwInverterPeriodCntNew = wInvPeriodLast+g_wPhaseLockLimit;
		}
	}
	else
	{
		if(wInvPeriodLast >= (g_uwInverterPeriodCntNew+g_wPhaseLockLimit))
		{
			g_uwInverterPeriodCntNew = wInvPeriodLast-g_wPhaseLockLimit;
		}
	}
}

void 	sAdjPhase(INT16U wStep)
{
	INT32U dwPhaseGoOn = 0;
	INT32U dwPhasePause = 0;
	INT32U dwPhaseDelta1 = 0;
	
	dwPhaseGoOn = ((INT32U)g_uwPeriodDelta) * ((INT32U)g_uwPeriodDelta - wStep) + 4 * (INT32U)g_uwPeriodDelta * wStep + 2 * wStep * wStep;											
	dwPhasePause = ((INT32U)g_uwPeriodDelta) * ((INT32U)g_uwPeriodDelta - wStep) + 2 * (INT32U)g_uwPeriodDelta * wStep;												  
    dwPhaseDelta1 = (2 * wStep * (INT32U)g_uwPhaseDelta);
    
	if(fInverterStatus.bits.InvPhaseLead)
	{
		if (dwPhaseDelta1 >= dwPhaseGoOn)	
		{
			g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew + wStep;
		}
		else								
		{
			if (dwPhaseDelta1 >= dwPhasePause)	
			{}
			else
			{
				g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew - wStep;
			}
		}
	}
	else
	{
		if (dwPhaseDelta1 >= dwPhaseGoOn)
		{
			g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew - wStep;
		}
		else
		{
			if (dwPhaseDelta1 >= dwPhasePause)
			{}
			else
			{
				g_uwInverterPeriodCntNew = g_uwInverterPeriodCntNew + wStep;
			}
		}
	}
}

void	sFreeRun(void)	// Off-grid frequency automatically restores default frequency.
{
	INT16U wInvFreqDelta;
	
	if(g_uwInverterPeriodCntNew > swGetInverterPeriodCntSet())
	{
		wInvFreqDelta = g_uwInverterPeriodCntNew - swGetInverterPeriodCntSet();
		if(wInvFreqDelta > 8)
		{
			g_uwInverterPeriodCntNew -= 8;
		}
		else
		{
			g_uwInverterPeriodCntNew = swGetInverterPeriodCntSet();
			OS_ENTER_CRITICAL();
			fInverterStatus.bits.PhaseLocked = 1;
			OS_EXIT_CRITICAL();
		}
	}
	else
	{
		wInvFreqDelta = swGetInverterPeriodCntSet() - g_uwInverterPeriodCntNew;
		if(wInvFreqDelta > 8)
		{
			g_uwInverterPeriodCntNew += 8;
		}
		else
		{
			g_uwInverterPeriodCntNew = swGetInverterPeriodCntSet();
			OS_ENTER_CRITICAL();
			fInverterStatus.bits.PhaseLocked = 1;
			OS_EXIT_CRITICAL();
		}
	}
}

INV_TD	*spGetInvTd(void)
{
	if(gi_uwInvertTd>65000)
	{
		g_strInvLineTd.InvTd=65535-gi_uwInvertTd;
		g_strInvLineTd.IntConflict=1;
	}
	else
	{
		g_strInvLineTd.InvTd=gi_uwInvertTd;
		g_strInvLineTd.IntConflict=0;
	}
	return(&g_strInvLineTd);
}

void	sFrePhaseLockProc(void)
{
	INT16U wTemp;

	// 频率值和过欠频保护值接近时，可能会触发保护导致系统认为市电丢失无法锁相
//	if(sbGetLineVoltLossStatus() == false && sbGetLineFreqLossStatus() == false\
//	&& swGetWorkMode() != cPowerOnMode && (swGetRLineVoltFilter() >= 600))
	if(swGetWorkMode() != cPowerOnMode && (swGetRLineVoltFilter() >= 600))
	{
		sInverterPhaseLock(swGetSinePeriodCntNew(),spGetInvTd(),swGetPreSinePeriodCntNew(),swGetPhaseLockStep());	// 软件
		//sInverterPhaseLock(swGetSinePeriodCntNew(),spGetInvTd(),swGetLinePeriodCntNew(),swGetPhaseLockStep());	// 硬件
	}
	else
	{
		sFreeRun();
	}
	
	if(g_uwInverterPeriodCntNew > (g_uwInverterPeriodCntHigh + 100))
	{
		g_uwInverterPeriodCntNew = g_uwInverterPeriodCntHigh + 100;
	}
	else if(g_uwInverterPeriodCntNew < (g_uwInverterPeriodCntLow - 100))
	{
		g_uwInverterPeriodCntNew = g_uwInverterPeriodCntLow - 100;
	}
	
	wTemp = ((INT32U)cPeriod50Hz * 16384 + (g_uwInverterPeriodCntNew >> 1)) / g_uwInverterPeriodCntNew;
	OS_ENTER_CRITICAL();
	wRSinPionterDeltaQ15 = wTemp;
	OS_EXIT_CRITICAL();
}


void	sRVoltRegu(INT16U wRTrackVolt, INT16U wRKVoltrack1, INT16U wRKVoltrack2)
{
	static INT16S s_wRVoltError0 = 0;
	INT16S wRVoltError;
	INT16S wTemp;
	
	g_wRNewSinAmpTemp = g_wRNewSinAmp;
	
	wRVoltError = (INT16S)wRTrackVolt - (INT16S)wRInvVoltNew;
	if(wRVoltError >= 500)	// 100
	{
		wRVoltError = 500;
	}
	else if(wRVoltError <= -500)
	{
		wRVoltError = -500;
	}
	
	wTemp = wRKVoltrack1*wRVoltError - wRKVoltrack2*s_wRVoltError0;
	g_wRNewSinAmpTemp = g_wRNewSinAmpTemp+wTemp;
	s_wRVoltError0 = wRVoltError;
	
	if(g_wSolarSigPowerLoad)
	{
		if(g_wRNewSinAmpTemp > 11312)	//250*32*1.414
		{
			g_wRNewSinAmpTemp = 11312;
		}
		else if(g_wRNewSinAmpTemp < 1)
		{
			g_wRNewSinAmpTemp = 1;
		}
	}
	else
	{
		if(g_wRNewSinAmpTemp > 12669)	//280*32*1.414
		{
			g_wRNewSinAmpTemp = 12669;
		}
		else if(g_wRNewSinAmpTemp < 1)
		{
			g_wRNewSinAmpTemp = 1;
		}
	}
	
	OS_ENTER_CRITICAL();
	g_wRNewSinAmp = g_wRNewSinAmpTemp;
	OS_EXIT_CRITICAL();
}

void	sRInvDCVoltCntl(INT16S wInvDCVoltRef, INT16U wVoltKp, INT16U wVoltKi)
{
	INT16S wInvDCVoltError;
	INT16S wInvDCVoltAvg;
	
	if(g_wRInvDCVoltCnt < 4)
	{
		g_wRInvDCVoltCnt++;
		g_dwRInvDCVoltSum += wRInvDcVoltFilter;
	}
	else
	{
		wInvDCVoltAvg = g_dwRInvDCVoltSum / g_wRInvDCVoltCnt;
		g_dwRInvDCVoltSum = 0;
		g_wRInvDCVoltCnt = 0;
		
		wInvDCVoltError = wInvDCVoltRef - wInvDCVoltAvg; 
		if(wInvDCVoltError >= 0)//5)//20)
		{
			g_wRDCVoltI--;
		}
		else if(wInvDCVoltError <= -1)//5)//-20)
		{
			g_wRDCVoltI++;
		}
		if(g_wRDCVoltI >= 300)
		{
			g_wRDCVoltI = 300;
		}
		else if(g_wRDCVoltI <= -300)
		{
			g_wRDCVoltI = -300;
		}
		OS_ENTER_CRITICAL();
		g_wRInvDCVoltCntl = g_wRDCVoltI / 10;
		OS_EXIT_CRITICAL();
	}
}

void	sClrInvDCVoltCntlPara(void)
{
	g_dwRInvDCVoltSum = 0;
	g_wRInvDCVoltCnt = 0;
	
	g_wRInvDCVoltCntl = 0;
	g_wRDCVoltP = 0;
	g_wRDCVoltI = 0;
	g_wRDCVoltI_Res = 0;
}

void	sClrInvDCCurrCntlPara(void)
{
	g_wRInvDCCurrCtrl = 0;
	g_wRDCCurrP = 0;
	g_wRDCCurrI = 0;
	g_wRDCCurrI_Res = 0;
	g_wRInvDCOverChkCnt = 0;
}



void	sInvVoltHighChk(INT8U ubFilter)
{
	static INT16U s_uwRInvVoltHighCnt = 0;
	INT8U ubInvVoltHigh = false;

	if(T_FAULT_DATA.bits.bInvVoltFault == true)
	{
		if((sb16UUnderLevelChk(wRInvVoltNew, uwGetInvVoltOverBack(), ubFilter, &s_uwRInvVoltHighCnt))\
		||(sb16UOverLevelChk(wRInvVoltNew, 0, ubFilter, &s_uwRInvVoltHighCnt)))
		{
			s_uwRInvVoltHighCnt = 0;
			T_FAULT_DATA.bits.bInvVoltFault = false;
		}
	}
	else
	{
		//if(swGetWorkMode() == cBatteryMode && (suwGetFBInvCtrlSts() == cFBInvCtrlVolt || suwGetFBInvCtrlSts() == cFBInvOpenLoop))
		if((suwGetFBInvCtrlSts() == cFBInvCtrlVolt || suwGetFBInvCtrlSts() == cFBInvOpenLoop))
		{
			if((sb16UOverLevelChk(wRInvVoltNew, uwGetInvVoltOver(), ubFilter, &s_uwRInvVoltHighCnt))\
			|| (sb16UUnderLevelChk(wRInvVoltNew, cAcVoltReal90V, ubFilter, &s_uwRInvVoltHighCnt)))
			{
				ubInvVoltHigh = true;
			}
			
			if(ubInvVoltHigh)
			{
				s_uwRInvVoltHighCnt = 0;
				sSetFaultCode(cInvVoltHigh);
				T_FAULT_DATA.bits.bInvVoltFault = true;
			}
		}
	}
}

void	sInvCurrOverChk(INT8U ubFilter)
{
	static INT16U s_uwRInvCurrOverCnt = 0;

	if(T_FAULT_DATA.bits.bInvSoftOC == true)
	{
		if(sb16UUnderLevelChk(wRInvCurrNew, uwGetInvCurrOver() - 500, ubFilter, &s_uwRInvCurrOverCnt))
		{
			s_uwRInvCurrOverCnt = 0;
			T_FAULT_DATA.bits.bInvSoftOC = false;
		}
	}
	else
	{
		if(swGetWorkMode() == cBatteryMode && (suwGetFBInvCtrlSts() == cFBInvCtrlVolt || suwGetFBInvCtrlSts() == cFBInvOpenLoop))
		{
			if(sb16UOverLevelChk(wRInvCurrNew, uwGetInvCurrOver(), ubFilter, &s_uwRInvCurrOverCnt))
			{
				s_uwRInvCurrOverCnt = 0;
				T_FAULT_DATA.bits.bInvSoftOC = true;
				if(swGetWorkMode() != cFaultMode)
				{
					sSetFaultCode(cInvCurrOver);
				}
			}
		}
	}
}


void	sInvShortChk(INT16U uwFilter)	// 逆变输出短路检测
{
	static INT16U s_uwRInvShortCnt = 0;
	INT16U uwInvShort = false;
	
	if(swGetWorkMode() == cBatteryMode|| swGetWorkMode() == cToBatteryMode)	// for test 20241012
	{
		if(swGetRInvVoltNew() < cAcVoltReal50V && wRInvCurrNew > cInv01A)	// 短路时：低压 大电流	// 50V  1A
		{
			if(++s_uwRInvShortCnt > uwFilter)
			{
				s_uwRInvShortCnt = 0;
				uwInvShort = true;
			}
		}
		else
		{
			s_uwRInvShortCnt = 0;
		}
		
		if(uwInvShort)
		{
			s_uwRInvShortCnt = 0;
			sSetFaultCode(cInvShort);
			T_FAULT_DATA.bits.bInvShort = true;
		}
	}
	else
	{
		s_uwRInvShortCnt = 0;
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetRInvVoltNew(void)			// 0.1V
{
	return wRInvVoltNew;
}

INT16S	swGetRInvCurrNew(void)			// 0.01A
{
	return wRInvCurrNew;
}

INT16S	swGetRInvFreqNew(void)			// 0.01Hz
{
	return wRInvFreqNew;
}

INT16S	swGetRInvWattNew(void)			// 1W
{
	return wRInvWattNew;
}

INT16S	swGetRInvDcVoltNew(void)	// 0.1V
{
	return wRInvDcVoltNew;
}

INT16S	swGetRInvDCVNew(void)			// 0.01V
{
	return wRInvDCVNew;
}

INT16S	swGetRInvDCINew(void)			// 0.001A
{
	return wRInvDCINew;
}

INT16S	swGetRInvVarNew(void)			// 1var
{
	return wRInvVarNew;
}

INT16S	swGetRInvVANew(void)			// 1VA
{
	return wRInvVANew;
}

INT16S	swGetRInvPFNew(void)			// 0.001
{
	return wRInvPFNew;
}

INT16S	swGetRInvVoltFilter(void)
{
	return wRInvVoltFilter;
}

INT16S	swGetRInvCurrFilter(void)
{
	return wRInvCurrFilter;
}

INT16S	swGetRInvFreqFilter(void)
{
	return wRInvFreqFilter;
}

INT16S	swGetRInvWattFilter(void)
{
	return wRInvWattFilter;
}

INT16S	swGetRInvDcVoltFilter(void)
{
	return wRInvDcVoltFilter;
}

INT16S	swGetRInvDCVFilter(void)
{
	return wRInvDCVFilter;
}

INT16S	swGetRInvDCIFilter(void)
{
	return wRInvDCIFilter;
}

INT16S	swGetRInvVarFilter(void)
{
	return wRInvVarFilter;
}

INT16S	swGetRInvVAFilter(void)
{
	return wRInvVAFilter;
}

INT16S	swGetRInvPFFilter(void)
{
	return wRInvPFFilter;
}

INT16S	swGetInvStep(void)
{
	return g_wPwmPeriod;	
}

INT16S	swGetRSinAmp(void)
{
	return g_wRSinAmp;
}

INT16S	swGetPhaseLockStep(void)
{
	return g_wPhaseLockStep;
}

INT16S	swGetPhaseLockLimit(void)
{
	return g_wPhaseLockLimit;
}

INT16U	swGetSinePeriodCntNew(void)
{
	return gi_uwSinePeriodCntNew;	
}

INT16U	swGetInverterPeriodCntSet(void)
{
	return g_uwInverterPeriodCntSet;
}

INT8U	sbGetInverterPLStatus(void)
{
	OS_ENTER_CRITICAL();
	//if(fInv.PhaseLocked)// || !gi_wParallelEnable)
	if(fInverterStatus.bits.PhaseLocked)
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

INT8U	sbGetInverterLinePhaseStatus(void)
{
	return fInverterStatus.bits.PhaseLocked;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetRInvVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRInvVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvVoltNew + (INT32S)wRInvVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRInvVoltFilter = dwTemp >> 5;
}

void	sSetRInvCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRInvCurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvCurrNew + (INT32S)wRInvCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRInvCurrFilter = dwTemp >> 5;
}

void	sSetRInvWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRInvWattNew = wWatt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvWattNew + (INT32S)wRInvWattFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRInvWattFilter = dwTemp >> 5;
}

void	sSetRInvDcVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wRInvDcVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvDcVoltNew + (INT32S)wRInvDcVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRInvDcVoltFilter = dwTemp >> 5;
}



void	sSetRInvFreqNew(INT16S wFreq)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	if(wFreq != 0)
	{
		wRInvFreqNew = 100000000 / wFreq;
	}
	else
	{
		wRInvFreqNew = 0;
	}
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wRInvFreqNew + (INT32S)wRInvFreqFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wRInvFreqFilter = dwTemp >> 5;
}




void	sSetInvStep(INT16S wVaule)
{
	OS_ENTER_CRITICAL();
	g_wPwmPeriod = wVaule; 
	OS_EXIT_CRITICAL();
}

void	sSetRSinAmp(INT16S wValue)
{
	OS_ENTER_CRITICAL();
	g_wRSinAmp = wValue;
	OS_EXIT_CRITICAL();
}

void	sSetRNewSinAmp(INT16S wValue)
{
	OS_ENTER_CRITICAL();
	g_wRNewSinAmp = wValue;
	OS_EXIT_CRITICAL();
}

void	sSetPhaseLockStep(INT16S wTemp)
{
	OS_ENTER_CRITICAL();
	g_wPhaseLockStep = wTemp;
	OS_EXIT_CRITICAL();
}

void	sSetPhaseLockLimit(INT16S wTemp)
{
	OS_ENTER_CRITICAL();
	g_wPhaseLockLimit = wTemp;
	OS_EXIT_CRITICAL();
}

void	sSetInverterPeriodCntSet(INT16U wTemp)
{
	OS_ENTER_CRITICAL();
	g_uwInverterPeriodCntSet = wTemp;
	OS_EXIT_CRITICAL();
}

