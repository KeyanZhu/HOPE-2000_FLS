/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		LPBT
File Name:		SoxProcess.c
Author:			Andy
Date:			2019.08.15
Description:	None
********************************************************************************/
#define			__SOX_PROCESS_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include		"Main.h"
#include		"SoxProcess.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define			cEnergySelfLossCurrSleep		5	// 5mA,低功耗模式
#define			cEnergySelfLossCurrNoBl			40	// 40mA

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16U	wEnergyAhReal;			// 0.1AH
INT16U	wEnergyAhMax; 			// 0.1AH
INT16U	wEnergyPct80Volt;		// 1mV
INT16U	wEnergyPct20Volt;		// 1mV
INT16U	wEnergyPct05Volt;		// 1mV
INT16S	wEnergyCompCoeff;		// -0.01%/℃, <=5.00%
INT16S	wEnergyCompTemp;		// 1℃
INT16U	wEnergyPct20TwoVolt;	// 1mV

/********************************************************************************
* Output variables																*
********************************************************************************/
INT16U	wEnergySocNew;			// 1%
INT16U	wEnergySohNew;			// 1%
INT16U	wEnergyAhComp;			// 0.1AH

/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16U	wEnergySocTemp;			// 1%
INT16U	wEnergyAhRated;			// 0.1AH
INT16U	wEnergyAh0Pct5Rated;	// 0.1AH
INT16U	wEnergyAh20PctRated;	// 0.1AH
INT16U	wEnergyAh40PctRated;	// 0.1AH
INT16U	wEnergyAh50PctRated;	// 0.1AH
INT16U	wEnergyAh80PctRated;	// 0.1AH
INT16U	wEnergyAhStart;			// 0.1AH
INT16U	wEnergyAhEnd;			// 0.1AH
INT32U	dwEnergyAhTime;			// 100ms
INT16U	wEnergyAh01Pct;			// 0.1AH
INT16U	wEnergyAh05Pct;			// 0.1AH
INT16U	wEnergyAh20Pct;			// 0.1AH
INT16U	wEnergyAh80Pct;			// 0.1AH
INT16U	wEnergyAh99Pct;			// 0.1AH

INT16U	wOcvPauseEnterCurr;		// 0.1A
INT16U	wOcvPauseExitCurr;		// 0.1A
INT16U	wOcvPauseEnterCnt;		// 0.1ms
INT16U	wOcvPauseExitCnt;		// 0.1ms

union SOX_STATUS_TABLE
{
	struct SOX_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U	SocEmpty:1;
		INT16U	SocLess20Pct:1;
		INT16U	SocLarge80Pct:1;
		INT16U	SocFull:1;
		
		// BIT4-7
		INT16U	SohAccEn:1;
		INT16U	HaveLoadFlag:1;
		INT16U	rsvd2:2;
		
		// BIT8-11
		INT16U	SocLess05Pct:1;
		INT16U	SocOcvPause:1;
		INT16U	SocLess20Pct2:1;
		INT16U	rsvd3:1;
		
		// BIT12-15
		INT16U	rsvd4:4;
	} bits;
	INT16U data;
} fSoxStatus;

typedef struct{
	INT16U	wEnergySocShow;			// 1%
	INT16U	wEnergyAhRealShow;	    // 0.1AH
	INT16U  wCurrIntegralShow;       //显示SOC电流积分倍率
}SOC_SHOW;
SOC_SHOW sSocShow;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sSoxInit(void)
{
	wEnergySocNew = 0;
	wEnergySohNew = 100;
	wEnergyAhComp = 0;
	
	sSocShow.wEnergySocShow = 0;
	sSocShow.wCurrIntegralShow = 10;
	
	sSoxParaUpdate();
}

void	sSoxParaUpdate(void)
{
	wEnergyPct80Volt = swGetEepromCellVoltPct80();
	wEnergyPct20Volt = swGetEepromCellVoltPct20();
	wEnergyPct20TwoVolt = swGetEepromCellVoltPct20Two();
	wEnergyPct05Volt = wEnergyPct20Volt - 100;
	wEnergyCompCoeff = swGetEepromCellTempCoef();
	
	wEnergyAhRated = swGetBmsRatedAH();
	wEnergyAh0Pct5Rated = (wEnergyAhRated + 100) / 200;
	wEnergyAh20PctRated = wEnergyAhRated / 5;
	wEnergyAh40PctRated = wEnergyAh20PctRated * 2;
	wEnergyAh50PctRated = wEnergyAhRated >> 1;
	wEnergyAh80PctRated = wEnergyAh20PctRated * 4;
	
	wEnergyAhReal = swGetEepromBattAhReal();
	wEnergyAhComp = wEnergyAhReal;
	if(swGetEepromBattAhMax() >= wEnergyAhRated)
	{
		wEnergyAhMax = wEnergyAhRated;
	}
	else
	{
		wEnergyAhMax = swGetEepromBattAhMax();
	}
	wEnergyAh01Pct = ((INT32U)wEnergyAhMax * 41) >> 12;
	wEnergyAh05Pct = ((INT32U)wEnergyAhMax * 205) >> 12;
	wEnergyAh20Pct = ((INT32U)wEnergyAhMax * 819) >> 12;
	wEnergyAh80Pct = ((INT32U)wEnergyAhMax * 3277) >> 12;
	wEnergyAh99Pct = ((INT32U)wEnergyAhMax * 4055) >> 12;
	
	wEnergySocTemp = (INT16U)(((INT32U)wEnergyAhReal * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
	wEnergySocNew = wEnergySocTemp;
	wEnergySohNew = ((INT32U)wEnergyAhMax * 100 + (wEnergyAhRated >> 1)) / wEnergyAhRated;
	
	wOcvPauseEnterCurr = 100;	// 10.0A
	wOcvPauseExitCurr = 50;		// 5.0A
	wOcvPauseEnterCnt = 10;		// 10*100ms=1s
	wOcvPauseExitCnt = 3000;	// 3000*100ms=5mins
	
	sSocShow.wEnergyAhRealShow = swGetEepromBattAhRealShow();
	if((sSocShow.wEnergyAhRealShow >= wEnergyAhMax) || (sSocShow.wEnergyAhRealShow == 0)) sSocShow.wEnergyAhRealShow = wEnergyAhReal;
	sSocShow.wEnergySocShow = (INT16U)(((INT32U)sSocShow.wEnergyAhRealShow * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
}

void	sSoxOcvChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT8U bSocPct05Cnt = 0;
	static INT8U bSocPct20Cnt = 0;
	static INT8U bSocPct20Cnt2 = 0;
	static INT8U bSocPct80Cnt = 0;
	static INT16U wSocOcvPauseCnt = 0;
	INT16U wTemp;
	
	if((bBmsMode == cPowerOnMode) || (bBmsMode == cSleepMode) \
		|| (bBmsMode == cStandbyMode))
	{
		bSocPct05Cnt = 0;
		bSocPct20Cnt = 0;
		bSocPct20Cnt2 = 0;
		bSocPct80Cnt = 0;
		wSocOcvPauseCnt = 0;
		fSoxStatus.bits.SocEmpty = false;
		fSoxStatus.bits.SocLess05Pct = false;
		fSoxStatus.bits.SocLess20Pct = false;
		fSoxStatus.bits.SocLarge80Pct = false;
		fSoxStatus.bits.SocFull = false;
		fSoxStatus.bits.SocLess20Pct2 = false;
		fSoxStatus.bits.SocOcvPause = true;
	}
	else
	{
		fSoxStatus.bits.SocEmpty = sbGetCellVoltLoAlm();	// 2.5V
		fSoxStatus.bits.SocFull = (sbGetCellVoltHiAlm() || sbGetCellVoltFullFlag());		// 3.6V
		
//		if(fSoxStatus.bits.SocOcvPause == false)
//		{
//			if(sb16UOverLevelChk(swAbs(swGetBattCurrNew()),wOcvPauseEnterCurr,wOcvPauseEnterCnt,&wSocOcvPauseCnt) == true)
//			{
//				fSoxStatus.bits.SocOcvPause = true;
//			}
//		}
//		else
//		{
//			if(sb16UUnderLevelChk(swAbs(swGetBattCurrNew()),wOcvPauseExitCurr,wOcvPauseExitCnt,&wSocOcvPauseCnt) == true)
//			{
//				fSoxStatus.bits.SocOcvPause = false;
//			}
//		}
		
		if(swGetMinCellTempNew() <= 0)
		{
			wSocOcvPauseCnt = 100;
			fSoxStatus.bits.SocOcvPause = false;
		}
		else if(fSoxStatus.bits.SocOcvPause == false)
		{
			if(wSocOcvPauseCnt == 0)
			{
				fSoxStatus.bits.SocOcvPause = true;
			}
			else if(--wSocOcvPauseCnt <= 50)  // 5s
			{
				wSocOcvPauseCnt = 0;
				fSoxStatus.bits.SocOcvPause = true;
			}
		}
		else if(fSoxStatus.bits.SocOcvPause == true)
		{
			if(++wSocOcvPauseCnt >= 100)  // 10s
			{
				wSocOcvPauseCnt = 100;
				fSoxStatus.bits.SocOcvPause = false;
			}
		}
		
		if(fSoxStatus.bits.SocOcvPause == false)
		{
			if(fSoxStatus.bits.SocLess05Pct == true)
			{
				if(sb8UOverLevelChk(swGetMinCellVoltFiltNew(),wEnergyPct05Volt,wFilter2,&bSocPct05Cnt) == true)
				{
					fSoxStatus.bits.SocLess05Pct = false;
				}
			}
			else
			{
				if(sb8UUnderLevelChk(swGetMinCellVoltFiltNew(),wEnergyPct05Volt,wFilter1,&bSocPct05Cnt) == true)
				{
					fSoxStatus.bits.SocLess05Pct = true;
				}
			}
			
			if(fSoxStatus.bits.SocLess20Pct == true)
			{
				if(sb8UOverLevelChk(swGetMinCellVoltFiltNew(),wEnergyPct20Volt,wFilter2,&bSocPct20Cnt) == true)
				{
					fSoxStatus.bits.SocLess20Pct = false;
				}
			}
			else
			{
				if(sb8UUnderLevelChk(swGetMinCellVoltFiltNew(),wEnergyPct20Volt,wFilter1,&bSocPct20Cnt) == true)
				{
					fSoxStatus.bits.SocLess20Pct = true;
				}
			}
			
			if(fSoxStatus.bits.SocLarge80Pct == true)
			{
				if(sb8UUnderLevelChk(swGetMaxCellVoltFiltNew(),wEnergyPct80Volt,wFilter2,&bSocPct80Cnt) == true)
				{
					fSoxStatus.bits.SocLarge80Pct = false;
				}
			}
			else
			{
				if(sb8UOverLevelChk(swGetMaxCellVoltFiltNew(),wEnergyPct80Volt,wFilter1,&bSocPct80Cnt) == true)
				{
					fSoxStatus.bits.SocLarge80Pct = true;
				}
			}
			
			if(swGetSocNew() < 20)
			{
				if(fSoxStatus.bits.SocLess20Pct2 == true)		
				{
					if(sb8UUnderLevelChk(swGetMinCellVoltFiltNew(), wEnergyPct20TwoVolt, wFilter2,&bSocPct20Cnt2) == true)
					{
						fSoxStatus.bits.SocLess20Pct2 = false;
					}
				}
				else
				{
					if(swGetSohNew() >= 90)
					{
						wTemp = wEnergyPct20TwoVolt;
					}
					else if(swGetSohNew() >= 80)
					{
						wTemp = wEnergyPct20TwoVolt + 25;
					}
					else
					{
						wTemp = wEnergyPct20TwoVolt + 50;
					}
					if(sb8UOverLevelChk(swGetMinCellVoltFiltNew(), wTemp, wFilter1,&bSocPct20Cnt2) == true)
					{
						fSoxStatus.bits.SocLess20Pct2 = true;
					}
				}
			}
			else
			{
				bSocPct20Cnt2 = 0;
				fSoxStatus.bits.SocLess20Pct2 = false;
			}
		}
		else
		{
			bSocPct05Cnt = 0;
			bSocPct20Cnt = 0;
			bSocPct20Cnt2 = 0;
			bSocPct80Cnt = 0;
			fSoxStatus.bits.SocLess05Pct = false;
			fSoxStatus.bits.SocLess20Pct = false;
			fSoxStatus.bits.SocLess20Pct2 = false;
			fSoxStatus.bits.SocLarge80Pct = false;
		}
	}
}

void	sSoxAhCalc(INT16S wCurr)
{
	static INT32S	dwAhAcc = 0;
	static INT8U	bSelfAccCnt = 0;
	
	if((bBmsMode == cBatteryMode) || (bBmsMode == cChargeMode) \
		|| (bBmsMode == cDischargeMode))
	{
		dwAhAcc += wCurr;
	}
	else
	{
		if(++bSelfAccCnt >= 100)
		{
			bSelfAccCnt = 0;
			if(bBmsMode == cSleepMode)
			{
				dwAhAcc -= cEnergySelfLossCurrSleep;
			}
			else
			{
				dwAhAcc -= cEnergySelfLossCurrNoBl;
			}
		}
	}
	
	if(dwAhAcc <= -36000)
	{
		dwAhAcc += 36000;
		if(wEnergyAhReal > wEnergyAh01Pct)
		{
			wEnergyAhReal--;
		}
		
		fSoxStatus.bits.SohAccEn = false;
	}
	else if(dwAhAcc >= 36000)
	{
		dwAhAcc -= 36000;
		if(wEnergyAhReal < wEnergyAh99Pct)
		{
			wEnergyAhReal++;
		}
		
		if(fSoxStatus.bits.SohAccEn == true)
		{
			wEnergyAhEnd++;
		}
		else if(swGetMinCellTempNew() >= 20)	// 20℃
		{
			fSoxStatus.bits.SohAccEn = true;
		}
	}
	
	if(fSoxStatus.bits.SohAccEn == false)
	{
		wEnergyAhStart = wEnergyAhReal;
		wEnergyAhEnd = wEnergyAhStart;
		dwEnergyAhTime = 0;
	}
	else
	{
		if(++dwEnergyAhTime >= 180000)	// 180000*100ms=5H,0.2C
		{
			dwEnergyAhTime = 0;
			fSoxStatus.bits.SohAccEn = false;
		}
		if(swGetMinCellTempNew() <= 15)	// 15℃
		{
			fSoxStatus.bits.SohAccEn = false;
		}
	}

	if(swGetEepromSOCSmoothEn() == true)
	{
		if((sSocOutput.bCaliFlg == 1) || (sSocOutput.bCaliFlg == 0))
		{
			wEnergyAhReal = sSocOutput.wRealCapacity;
		}
	}
	else
	{
		if(fSoxStatus.bits.SocEmpty == true)
		{
			wEnergyAhReal = 0;
		}
		else if(fSoxStatus.bits.SocFull == true)
		{
			wEnergyAhReal = wEnergyAhMax;
		}
		else if(fSoxStatus.bits.SocLess05Pct == true)
		{
			if(wEnergyAhReal > wEnergyAh05Pct)
			{
				wEnergyAhReal = wEnergyAh05Pct;
			}
		}
		else if(fSoxStatus.bits.SocLess20Pct == true)
		{
			if(wEnergyAhReal > wEnergyAh20Pct)
			{
				wEnergyAhReal = wEnergyAh20Pct;
			}
		}
	//	else if(fSoxStatus.bits.SocLess20Pct2 == true)
	//	{
	//		if(wEnergyAhReal < wEnergyAh20Pct)
	//		{
	//			wEnergyAhReal = wEnergyAh20Pct;
	//		}
	//	}
		else if(fSoxStatus.bits.SocLarge80Pct == true)
		{
			if(wEnergyAhReal < wEnergyAh80Pct)
			{
				wEnergyAhReal = wEnergyAh80Pct;
			}
		}
	}
}

void	sSocEstimate(INT16S wTemp)
{
	INT16S	wDampPct;
	INT16S	wCompPct;
	
	if(wEnergyCompCoeff != 0)
	{
		if(wTemp < 25)
		{
			wDampPct = (INT16S)((INT32S)wEnergyCompCoeff * (25 - wEnergyCompTemp));
		}
		else
		{
			wDampPct = 0;
		}
		wCompPct = 10000 - wDampPct;
		if(wCompPct > 10000)
		{
			wCompPct = 10000;
		}
		else if(wCompPct < 0)
		{
			wCompPct = 0;
		}
		wEnergyAhComp = (INT16U)(((INT32U)wEnergyAhReal * wCompPct + 5000) / 10000);
	}
	else
	{
		wEnergyAhComp = wEnergyAhReal;
	}
	
	if(swGetEepromSOCSmoothEn() == true)
	{
		if((sSocOutput.bCaliFlg == 2) || (sSocOutput.bCaliFlg == 0))
		{
			wEnergySocTemp = (INT16U)(((INT32U)wEnergyAhComp * 100 + (sSocOutput.wMaxCapacity >> 1)) / sSocOutput.wMaxCapacity);
		}
		else
		{
			wEnergySocTemp = (INT16U)(((INT32U)wEnergyAhComp * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
		}
	}
	else
	{
	  wEnergySocTemp = (INT16U)(((INT32U)wEnergyAhComp * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
	}
}

void	sSocFilter(INT16U wFilter)
{
	static INT16U wSocCnt = 0;
	static INT16U wStepSize = 0;
	INT16U wSocTemp;
	INT16U wStepTemp;
	
	if(++wSocCnt >= wFilter)
	{
		wSocCnt = 0;
		
		wSocTemp = wEnergySocNew;
		
		if(wEnergySocTemp != wEnergySocNew)
		{
			if(wEnergySocTemp > wEnergySocNew)
			{
				wStepTemp = (wEnergySocTemp - wEnergySocNew) / 20;
			}
			else
			{
				wStepTemp = (wEnergySocNew - wEnergySocTemp) / 20;
			}
			wStepTemp++;
			if(wStepTemp > wStepSize)
			{
				wStepSize = wStepTemp;
			}
		}
		else
		{
			wStepSize = 0;
		}
		
		if(wEnergySocTemp > wEnergySocNew)
		{
			if((wSocTemp + wStepSize) >= 100)
			{
				wSocTemp = 100;
			}
			else if((wSocTemp + wStepSize) > wEnergySocTemp)
			{
				wSocTemp = wEnergySocTemp;
			}
			else
			{
				wSocTemp += wStepSize;
			}
		}
		else if(wEnergySocTemp < wEnergySocNew)
		{
			if(wStepSize >= wSocTemp)
			{
				wSocTemp = 0;
			}
			else if((wEnergySocTemp + wStepSize) > wSocTemp)
			{
				wSocTemp = wEnergySocTemp;
			}
			else
			{
				wSocTemp -= wStepSize;
			}
		}
		if(wSocTemp > 100)
		{
			wSocTemp = 100;
		}
		else if(wSocTemp < 1)
		{
			wSocTemp = 0;
		}
		wEnergySocNew = wSocTemp;
	}
}

void	sSohEstimate(void)
{
	INT16S wChgAh1, wChgAh2;
	INT16S wChgCurr, wChgMin;
	INT16S wAhAdj, wAhStep;
	INT16S wAhMax;
	
	if((swGetSocNew() != 100) || (fSoxStatus.bits.SohAccEn == false))
	{
		return;
	}
	fSoxStatus.bits.SohAccEn = false;
	
	// 充电电量太小时不校准
	wChgAh1 = wEnergyAhEnd - wEnergyAhStart;
	wChgAh2 = wEnergyAhMax - wEnergyAhStart;
	wChgMin = (INT16S)(((INT32S)dwEnergyAhTime + 300) / 600);		// to Minute
	if(wChgMin > 0)
	{
		wChgCurr = (INT16S)(((INT32S)wChgAh1 * 60) / wChgMin);		// to Current
	}
	else
	{
		wChgCurr = 0;
	}
	wEnergyAhStart = 0;
	wEnergyAhEnd = 0;
	dwEnergyAhTime = 0;
	if((wChgAh1 < wEnergyAh20PctRated) \
		|| (wChgAh2 < wEnergyAh20PctRated) \
		|| (wChgCurr < wEnergyAh20PctRated))
	{
		return;
	}
	
	wAhAdj = ((INT32S)wChgAh1 * wEnergyAhMax) / wChgAh2;
	
	// 根据充电能量,调节校正幅度
	if(wChgAh1 >= wEnergyAh80PctRated)
	{
		wAhStep = wEnergyAh0Pct5Rated;
	}
	else if(wChgAh1 >= wEnergyAh40PctRated)
	{
		wAhStep = (wEnergyAh0Pct5Rated + 1) >> 1;
	}
	else
	{
		wAhStep = (wEnergyAh0Pct5Rated + 2) >> 2;
	}
	
	wAhMax = wEnergyAhMax;
	if(wAhAdj > wEnergyAhMax)
	{
		wAhMax += wAhStep;
	}
	else if(wAhAdj < wEnergyAhMax)
	{
		wAhMax -= wAhStep;
	}
	
	// 最大可用容量限幅(50%~100%)
	if(wAhMax > wEnergyAhRated)
	{
		wAhMax = wEnergyAhRated;
	}
	else if(wAhMax < wEnergyAh50PctRated)
	{
		wAhMax = wEnergyAh50PctRated;
	}
	wEnergyAhMax = wAhMax;
	
	wEnergyAh01Pct = ((INT32U)wEnergyAhMax * 41) >> 12;
	wEnergyAh05Pct = ((INT32U)wEnergyAhMax * 205) >> 12;
	wEnergyAh20Pct = ((INT32U)wEnergyAhMax * 819) >> 12;
	wEnergyAh80Pct = ((INT32U)wEnergyAhMax * 3277) >> 12;
	wEnergyAh99Pct = ((INT32U)wEnergyAhMax * 4055) >> 12;
	wEnergySohNew = ((INT32U)wEnergyAhMax * 100 + (wEnergyAhRated >> 1)) / wEnergyAhRated;
}

void	sSoxAhCalc_Show(INT16S wCurr)
{
	static INT32S	dwAhAccShow = 0;//电流积分
	static INT8U	bSelfAccCnt = 0;//自耗电计数
	
	if((bBmsMode == cBatteryMode) || (bBmsMode == cChargeMode) || (bBmsMode == cDischargeMode))
	{
		dwAhAccShow += (wCurr * sSocShow.wCurrIntegralShow) / 10;
	}
	else
	{
		if(++bSelfAccCnt >= 100)
		{
			bSelfAccCnt = 0;
			if(bBmsMode == cSleepMode)
			{
				dwAhAccShow -= cEnergySelfLossCurrSleep;
			}
			else
			{
				dwAhAccShow -= cEnergySelfLossCurrNoBl;
			}
		}
	}
	
	if(dwAhAccShow <= -36000)
	{
		dwAhAccShow += 36000;
		if(sSocShow.wEnergyAhRealShow > wEnergyAh01Pct)
		{
			sSocShow.wEnergyAhRealShow--;
		}
	}
	else if(dwAhAccShow >= 36000)
	{
		dwAhAccShow -= 36000;
		if(sSocShow.wEnergyAhRealShow < wEnergyAh99Pct)
		{
			sSocShow.wEnergyAhRealShow++;
		}
	}
	
	sSocShow.wEnergySocShow = (INT16U)(((INT32U)sSocShow.wEnergyAhRealShow * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
}

void	sSocFilter_Show(INT16U wFilter)
{
	static INT16U wSocCnt = 0, wSocEmptyFullCnt = 0;
	static INT8U wSocEndStepDelay = 0, wSocEndDelayFlg = 0;//末端SOC校准时步进延时
	static INT8U wCurrIntegralEN = 0;//电流积分加速使能
	INT16U wSocTemp;
	INT16S sdiff;
	INT16U k = 5; // 调节因子，越大收敛越快
	INT32U scale = 0;
	
	uint16_t wBmsStatusLow;
	
	if(++wSocCnt >= wFilter)
	{
		wSocCnt = 0;
		
		sdiff = (INT16S)wEnergySocTemp - (INT16S)sSocShow.wEnergySocShow;
		if(((wEnergySocTemp == 0) || (wEnergySocTemp == 100)) && (sdiff != 0))
		{
			if(wSocEndDelayFlg == 0)
			{
			    (abs(sdiff) > 5)?(wSocEndStepDelay = 2):(wSocEndStepDelay = 5);//跳变大于5%，1S步进1%；跳变小于等于5%，2.5S步进1%
				wSocEndDelayFlg = 1;
			}
			if(++wSocEmptyFullCnt >= wSocEndStepDelay)
			{
			    if((sSocShow.wEnergySocShow < wEnergySocTemp) && (sSocShow.wEnergyAhRealShow < wEnergyAh99Pct))
				{
					sSocShow.wEnergyAhRealShow += wEnergyAh01Pct;
				}
				else if((sSocShow.wEnergySocShow > wEnergySocTemp) && (sSocShow.wEnergyAhRealShow > wEnergyAh01Pct))
				{
					sSocShow.wEnergyAhRealShow -= wEnergyAh01Pct;
				}
				else
				{
					sSocShow.wEnergyAhRealShow = wEnergyAhReal;
					sSocShow.wEnergySocShow = wEnergySocTemp;
					wSocEndDelayFlg = 0;
				}
				wSocEmptyFullCnt = 0;
				wCurrIntegralEN = 0;
				sSocShow.wCurrIntegralShow = 10;
			}
			wSocTemp = sSocShow.wEnergySocShow;
		}
		else
		{
			if((wCurrIntegralEN == 0) && (abs(sdiff) >= 1))
			{
				wCurrIntegralEN = 1;
			}
			else if((wCurrIntegralEN == 1) && (abs(sdiff) == 0))
			{
				wCurrIntegralEN = 0;
				sSocShow.wCurrIntegralShow = 10;
			}
		
			if(wCurrIntegralEN == 1)
			{
				scale = 30 + k * abs(sdiff); // 根据差值决定倍率大小 
				if(scale > 100)
				{
					scale = 100; // 电流积分倍率上限
				}
				if(scale < 10)
				{
					scale = 10;
				}

				wBmsStatusLow = swGetBmsDataBmsStatusLow(sbGetSciAddress());
				if(sdiff > 0)
				{ 
					if(wBmsStatusLow & 0x2000)
					{
						sSocShow.wCurrIntegralShow = scale;           // 充电 → 加速
					}
					else if(wBmsStatusLow & 0x1000)
					{
						sSocShow.wCurrIntegralShow = 100 / scale;     // 放电 → 减速
					}
					else
					{
						sSocShow.wCurrIntegralShow = 10;              // 静置
					}
				}
				else if(sdiff < 0)
				{
					if(wBmsStatusLow & 0x2000)
					{
						sSocShow.wCurrIntegralShow = 100 / scale;     // 充电 → 减速 
					}
					else if(wBmsStatusLow & 0x1000)
					{
						sSocShow.wCurrIntegralShow = scale;           // 放电 → 加速
					}
					else
					{
						sSocShow.wCurrIntegralShow = 10;              // 静置
					}
				}
			}
			wSocTemp = sSocShow.wEnergySocShow;
		}
		if(wSocTemp > 100)
		{
			wSocTemp = 100;
		}
		else if(wSocTemp < 1)
		{
			wSocTemp = 0;
		}
		wEnergySocNew = wSocTemp;
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	swGetSocNew(void)
{
	return(wEnergySocNew);
}

INT16U	swGetSohNew(void)
{
	return(wEnergySohNew);
}

INT16U	swGetSocReport(void)	// 仅用作通讯上报以及LCD/LED显示
{
	INT16U wTemp;
	
	// 显示EMS SOC功能开启后系统且并机数量大于1且不为单机模式时充电动画的soc按并机显示，否则按单机显示
	if(swGetEepromDisplayEMSSOCEn() && (sbGetCanAddress() != 0) && (swGetEmsDataParallelNumber() > 1))
	{
		if (swGetEmsDataTotalSOC() > 10)
		{
			wTemp = (swGetEmsDataTotalSOC() / 10);	// 向下取整
		}
		else if(swGetEmsDataTotalSOC() > 0)
		{
			wTemp = 1;
		}
		else
		{
			wTemp = 0;
		}
	}
	else
	{
		wTemp = wEnergySocNew;
	}
	
	return wTemp;
}

INT16U	swGetSoxAhReal(void)
{
	return(wEnergyAhReal);
}

INT16U	swGetSoxAhMax(void)
{
	return(wEnergyAhMax);
}

INT16U	swGetSoxAhComp(void)
{
	return(wEnergyAhComp);
}

INT16U	swGetSoxAhRealShow(void)
{
	return(sSocShow.wEnergyAhRealShow);
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetSoxAhReal(INT16U wAH)
{
	OS_CPU_SR  cpu_sr;
	INT16U wSoC;
	
	if(wAH > wEnergyAhMax)
	{
		wAH = wEnergyAhMax;
	}
	wSoC = (INT8U)(((INT32U)wAH * 100 + (wEnergyAhMax >> 1)) / wEnergyAhMax);
	
	OS_ENTER_CRITICAL();
	sSetEepromBattAhReal(wAH);
	wEnergyAhReal = wAH;
	wEnergySocTemp = wSoC;
	wEnergySocNew = wSoC;
	sSocShow.wEnergyAhRealShow = wAH;
	sSocShow.wEnergySocShow = wSoC;
	OS_EXIT_CRITICAL();
}

void	sSetSoxAhMax(INT16U wAH)
{
	OS_CPU_SR  cpu_sr;
	INT16U wSoH;
	
	if(wAH > wEnergyAhRated)
	{
		wAH = wEnergyAhRated;
	}
	wSoH = (INT8U)(((INT32U)wAH * 100 + (wEnergyAhRated >> 1)) / wEnergyAhRated);
	
	OS_ENTER_CRITICAL();
	sSetEepromBattAhMax(wAH);
	wEnergyAhMax = wAH;
	wEnergySohNew = wSoH;
	OS_EXIT_CRITICAL();
	
	sSetSoxAhReal(wEnergyAhReal);
}

void	sSetSoxCompTemp(INT16S wTemp)
{
	wEnergyCompTemp = wTemp;
}

