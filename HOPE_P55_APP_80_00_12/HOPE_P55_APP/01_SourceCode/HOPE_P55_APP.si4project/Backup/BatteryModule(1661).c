/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__BATTERY_MODULE_C__

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
INT16S g_wBatVoltRef = 720;//1440;
INT16S g_wSolarSigPowerLoad = false;
INT16S g_wSysLiBatActFlg;
INT16S gi_wChgCurrLimit;
INT16S gi_wDischgCurrLimit;

extern INT16U fChgMode;

INT16S g_wTriChgVoltLLimit = 560 ;
INT16S g_wTriChgVoltHLimit = 720;
INT16S g_wTriChgCurrLimitMax = 15;
INT16S g_wTriChgPowerLimit = 60;
INT16S g_wTriChgCurrLimit = 15;
INT16S g_wTriChgFlag = false;
INT16S g_wTriChgCnt = 0;
INT16S g_wTriChgCntRate = 100;


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16S wBusVoltNew;					// 0.1V
INT16S wBusCurrNew;					// 0.01A   未添加计算
INT16S wBatVoltNew;					// 0.01V
INT16S wBatVolt2New;				// 0.01V
INT16S wBatCurrNew;					// 1A
INT16S wPv1VoltNew;					// 0.01V
INT16S wPv1CurrNew;					// 0.1A
INT16S wPv1BatCurrNew;				// 0.1A
INT16S wPv1BatWattNew;				// W
INT16S wHsTwTempNew;				// 0.1℃
INT16S wHsInvTempNew;				// 0.1℃
INT16S wHsPvTempNew;				// 0.1℃
INT16S wHsBatHTempNew;				// 0.1℃
INT16S wBatWattNew;					// 1W
INT16S wPvWattNew;					// 1W
INT16S wLLCOCPCurrNew;				// 0.01A
INT16S wLV12VVoltNew;				// 0.01V
INT16S wAC12VVoltNew;				// 0.01V
INT16S wB1VoltNew;					// 0.01V
INT16S wB2VoltNew;					// 0.01V
INT16S wBVoltNew;					// 0.01V
INT16S wPvInCurrNew;				// 0.1A
INT16S wPvInTzCurrNew;				// 0.1A
INT16S wHsLLCTempNew;				// 0.1℃
INT16S wHsBat1TempNew;				// 0.1℃
INT16S wHsBat2TempNew;				// 0.1℃
INT16S wMinCellTempNew;				// 0.1℃
INT16S wMaxCellTempNew;				// 0.1℃
INT16S wAvgCellTempNew;				// 0.1℃
INT16S wMinCellVoltNew;				// 0.1V
INT16S wMaxCellVoltNew;				// 0.1V
INT16S wAvgCellVoltNew;				// 0.1V


INT16S wBusVoltFilter;				// 0.1V
INT16S wBusCurrFilter;				// 0.01A
INT16S wBatVoltFilter;				// 0.01V
INT16S wBatVolt2Filter;				// 0.01V
INT16S wBatCurrFilter;				// 1A
INT16S wPv1VoltFilter;				// 0.01V
INT16S wPv1CurrFilter;				// 0.1A
INT16S wPv1BatCurrFilter;			// 0.1A
INT16S wPv1BatWattFilter;			// W
INT16S wHsTwTempFilter;				// 0.1℃
INT16S wHsInvTempFilter;			// 0.1℃
INT16S wHsPvTempFilter;				// 0.1℃
INT16S wHsBatHTempFilter;			// 0.1℃
INT16S wBatWattFilter;				// 1W
INT16S wPvWattFilter;				// 1W
INT16S wLLCOCPCurrFilter;			// 0.01A
INT16S wLV12VVoltFilter;			// 0.01V
INT16S wAC12VVoltFilter;			// 0.01V
INT16S wB1VoltFilter;				// 0.01V
INT16S wB2VoltFilter;				// 0.01V
INT16S wBVoltFilter;				// 0.01V
INT16S wPvInCurrFilter;				// 0.01A
INT16S wPvInTzCurrFilter;			// 0.01A
INT16S wHsLLCTempFilter;			// 0.1℃
INT16S wHsBat1TempFilter;			// 0.1℃
INT16S wHsBat2TempFilter;			// 0.1℃
INT16S wMinCellTempFilter;			// 0.1℃
INT16S wMaxCellTempFilter;			// 0.1℃
INT16S wAvgCellTempFilter;			// 0.1℃
INT16S wMinCellVoltFilter;			// 0.1V
INT16S wMaxCellVoltFilter;			// 0.1V
INT16S wAvgCellVoltFilter;			// 0.1V



/********************************************************************************
* Output variables																*
********************************************************************************/
union BATTERY_STATUS_TABLE
{
	struct BATTERY_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U	bBatUnder:1;
		INT16U	bBatOver:1;
		INT16U	bBatOpen:1;
		INT16U	bBatChgOver:1;
		
		// BIT4-7
		INT16U	bBatLow:1;
		INT16U	bBatWeak:1;
		INT16U	bSOCFull:1;
		INT16U	bBatDanger:1;
		
		// BIT8-11
		INT16U	bBatStart:1;
		INT16U	bLowBatCutOff:1;
		INT16U	bHighBatCutOff:1;
		INT16U	rsvd3:1;
		
		// BIT12-15
		INT16U	bBusOver:1;
		INT16U	rsvd4:3;
	} bits;
	INT16U data;
} fBatteryStatus;
INT16S gi_wDCDCChgDischgEnDisable;

/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16S g_wBatLowVolt;		// cBatVoltReal44V;
INT16S g_wBatLowBackVolt;	// cBatVoltReal46V;
INT16S g_wBatUnderVolt;		// cBatVoltReal42V;
INT16S g_wBatUnderBackVolt;	// cBatVoltReal46V;
INT16S g_wBatWeakVolt;		// cBatVoltReal46V;
INT16S g_wBatWeakBackVolt;	// cBatVoltReal54V;
INT16S g_wBatCVVolt;		// cBatVoltReal54V;
INT16S g_wBatFloatVolt;		// cBatVoltReal54V;
INT16S g_wBatChgCurrLimit;		//
INT16S g_wBatDsgCurrLimit;		//
INT16S g_wBatSOCReal;		//
INT16U g_uwBatWeakChkCnt;
INT16U g_uwParaBatWeakChgFlg;
INT16S g_wBatDischgPct;		// 1%,市电模式下允许放电电流百分比
INT16S g_wBatVoltPct;		// 1%,根据电压计算得到SOC

INT16S g_wLowBatCutOffVoltVolt;		// cBatVoltReal42V;
INT16S g_wLowBatCutOffVoltBackVolt;	// cBatVoltReal46V;

INT16S g_wPv1UnderVolt = cMpptPvVolt10V;			// PV欠压告警值
INT16S g_wPv1UnderBackVolt = cMpptPvVolt11V;	// PV欠压告警恢复值

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sBatteryInitial(void)
{
	fBatteryStatus.data = 0;
	fBatteryStatus.bits.bBatStart = 1;
	
	g_uwBatWeakChkCnt = 0;
	g_uwParaBatWeakChgFlg = false;
	g_wBatDischgPct = 100;
	
	gi_wDCDCChgDischgEnDisable = cDCDCChgDischgDis;
	
	g_wBatUnderBackVolt = suwGetEEBatACRestartVolt();
	sBatteryParaUpdate();
}


void	sBatteryParaUpdate(void)
{
	INT16S wBatCVVoltTemp;
	INT16S wBatFloatVoltTemp;
	INT16S wBatUnderVoltTemp;
	INT16U uwBatSerialPcs;
	INT16S g_wBatChgCurrLimitTemp;		
	INT16S g_wBatDcgCurrLimitTemp;		
	INT16S g_wBatSOCRealTemp;		

	uwBatSerialPcs = uwGetBatSerialPcs();
	
	//if(fChgMode == cChgModeFloat)
	if(0)	// 锂电池不存在浮充
	{
		wBatCVVoltTemp = suwGetEEBatFloatVolt();
	}
	else
	{
		wBatCVVoltTemp = suwGetEEBatConstVolt();
	}
	wBatFloatVoltTemp = suwGetEEBatFloatVolt();
	wBatUnderVoltTemp = suwGetEEBatLowAlarmVolt();
	g_wBatChgCurrLimitTemp = suwGetEEBatMaxChgCurr()/10;
	g_wBatDcgCurrLimitTemp = suwGetEEBatMaxDcgCurr()/10;
	g_wBatSOCRealTemp = g_wBatVoltPct;
	if(g_wTriChgFlag == true)   //涓流充电
	{
		if(g_wBatChgCurrLimitTemp > g_wTriChgCurrLimit)
		{
			if(++g_wTriChgCnt > g_wTriChgCntRate)
			{
				g_wTriChgCnt = 0;
				g_wBatChgCurrLimitTemp --;
			}
		}
		else
		{
			g_wBatChgCurrLimitTemp = g_wTriChgCurrLimit;
		}
	}
	else
	{
		if(g_wBatChgCurrLimitTemp < suwGetEEBatMaxChgCurr()/10)
		{

			if(++g_wTriChgCnt > g_wTriChgCntRate)
			{
				g_wTriChgCnt = 0;
				g_wBatChgCurrLimitTemp ++;
			}
		}
		else
		{
			g_wBatChgCurrLimitTemp = suwGetEEBatMaxChgCurr()/10;
		}
	}
	
	if(wBatUnderVoltTemp < (cBatVoltReal2V50 * uwBatSerialPcs))
	{
		wBatUnderVoltTemp = cBatVoltReal2V50 * uwBatSerialPcs;
	}
	if(wBatFloatVoltTemp > wBatCVVoltTemp)
	{
		wBatFloatVoltTemp = wBatCVVoltTemp;
	}

	g_wBatCVVolt = wBatCVVoltTemp;
	g_wBatFloatVolt = wBatFloatVoltTemp;
	g_wBatUnderVolt = wBatUnderVoltTemp;
	g_wBatUnderBackVolt = g_wBatUnderVolt + cBatVoltReal1V;
	g_wBatLowVolt = g_wBatUnderVolt + (cBatVoltReal0V5 * uwBatSerialPcs);
	g_wBatLowBackVolt = g_wBatUnderVolt + (cBatVoltReal1V * uwBatSerialPcs);
	g_wBatChgCurrLimit = g_wBatChgCurrLimitTemp;	// 电池额定最大充电电流
	g_wBatDsgCurrLimit = g_wBatDcgCurrLimitTemp;	// 电池额定最大放电电流
	g_wBatSOCReal = g_wBatSOCRealTemp;
//	g_wBatWeakVolt = swGetEEBatWeakVolt();
//	g_wBatWeakBackVolt = swGetEEBatWeakBackVolt();
}


void	sBatVoltOverChk(INT16U uwBatOverLevel, INT16U uwFilter)
{
	static INT16U s_uwBatChkCnt = 0;
	
	if(T_FAULT_DATA.bits.bBatSoftOV)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, uwBatOverLevel - cBatVoltReal1V, uwFilter, &s_uwBatChkCnt))
		{
			T_FAULT_DATA.bits.bBatSoftOV = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, uwBatOverLevel, uwFilter, &s_uwBatChkCnt))
		{
			T_FAULT_DATA.bits.bBatSoftOV = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cBatVoltOver);
			}
		}
	}
}

void	sBatOverChgChk(INT16U uwFilter)
{
	static INT16U s_uwBatOverChgChkCnt = 0;
	if(fBatteryStatus.bits.bBatChgOver)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, g_wBatVoltRef, uwFilter, &s_uwBatOverChgChkCnt))
		{
			fBatteryStatus.bits.bBatChgOver = 0;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, (g_wBatVoltRef + cBatVoltReal0V5), uwFilter, &s_uwBatOverChgChkCnt))
		{
			fBatteryStatus.bits.bBatChgOver = 1;
		}
	}
}


void	sBusOverChk(INT16U uwBusOverLevel1, INT16U uwFilter1, INT16U uwBusOverLevel2, INT16U uwFilter2)
{
	static INT16U s_uwPBusChkCnt;
	static INT16U s_uwPBusChkCnt2;
	
	if(!T_FAULT_DATA.bits.bBusSoftOV)
	{
		if(sb16UOverLevelChk(wBusVoltNew, uwBusOverLevel1, uwFilter1, &s_uwPBusChkCnt)
			|| sb16UOverLevelChk(wBusVoltNew, uwBusOverLevel2, uwFilter2, &s_uwPBusChkCnt2))
		{
			T_FAULT_DATA.bits.bBusSoftOV = true;
			s_uwPBusChkCnt = 0;
			s_uwPBusChkCnt2 = 0;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cBusVoltOver);
			}
		}
	}
	else
	{
		if(sb16UUnderLevelChk(wBusVoltNew, uwBusOverLevel1 - cBusVoltReal20V, uwFilter1, &s_uwPBusChkCnt))
		{
			T_FAULT_DATA.bits.bBusSoftOV = false;
			s_uwPBusChkCnt = 0;
			s_uwPBusChkCnt2 = 0;
		}
	}
}

void	subBusUnderChk(INT16U uwBusUnderLevel, INT16U uwFilter)
{
	static INT16U s_uwPBusChkCnt;
	INT16U uwLineVolt;

	if(T_FAULT_DATA.bits.bBusUV == true)
	{
		//if(sb16UOverLevelChk(wBusVoltNew, uwBusUnderLevel + cBusVoltReal20V, uwFilter, &s_uwPBusChkCnt))
		if(sb16UOverLevelChk(wBusVoltNew, 0, uwFilter, &s_uwPBusChkCnt))	// 故障后没打DCDC驱动前BUS电压很低，如果恢复值设置太高没法恢复
		{
			s_uwPBusChkCnt = 0;
			T_FAULT_DATA.bits.bBusUV = false;
		}
	}
	else
	{
		//if(g_wSolarSigPowerLoad && swGetWorkMode() == cBatteryMode)
		if(swGetWorkMode() == cBatteryMode)
		{
			if(sb16UUnderLevelChk(wBusVoltNew, uwBusUnderLevel, uwFilter, &s_uwPBusChkCnt))
			{
				s_uwPBusChkCnt = 0;
				T_FAULT_DATA.bits.bBusUV = true;
				sSetFaultCode(cBusVoltUnder);
			}	
		}
		else
		{
			if((swGetWorkMode() == cLineMode) || (swGetWorkMode() == cChgMode))
			{
				uwLineVolt = swGetRLineVoltFilter();
				if(uwLineVolt < cAcVoltReal80V)
				{
					uwLineVolt = cAcVoltReal80V;
				}
				uwLineVolt = (INT16U)((((INT32U)uwLineVolt * 181) >> 7) + cBusVoltReal40V);
				if(uwBusUnderLevel < uwLineVolt)
				{
					uwBusUnderLevel = uwLineVolt;
				}
			}
			else
			{
				//uwLineVolt = (wBatVoltFilter * uwGetBatSerialPcs());
				uwLineVolt = (wBatVoltFilter * 18) / 10;
				if(uwLineVolt < cBusVoltReal100V)
				{
					uwLineVolt = cBusVoltReal100V;
				}
				if(uwBusUnderLevel > (uwLineVolt - cBusVoltReal100V))
				{
					uwBusUnderLevel = (uwLineVolt - cBusVoltReal100V);
				}
			}
		
			if((swGetWorkMode() == cLineMode || swGetWorkMode() == cBatteryMode) && (suwGetDCDCCtrlSts() == cDCDCWork))
			{
				if(sb16UUnderLevelChk(wBusVoltNew, uwBusUnderLevel, uwFilter, &s_uwPBusChkCnt))
				{
					s_uwPBusChkCnt = 0;
//					T_FAULT_DATA.bits.bBusUV = true;
//					sSetFaultCode(cBusVoltUnder);
				}
			}
			else
			{
				s_uwPBusChkCnt = 0;
			}
		}
	}
}

void	sBatOpenChk(INT16U uwBatOpenLevel, INT16U uwFilter)
{
	static INT16U s_uwBatChkCnt = 0;
	
	if(!T_ALARM_DATA.bits.bBatOpenAlarm)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, uwBatOpenLevel, uwFilter, &s_uwBatChkCnt))
		{
			T_ALARM_DATA.bits.bBatOpenAlarm = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, uwBatOpenLevel + (cBatVoltReal1V*uwGetBatSerialPcs()), uwFilter, &s_uwBatChkCnt))
		{
			T_ALARM_DATA.bits.bBatOpenAlarm = true;
		}
	}
}

//void	sBatOVAlarmChk(INT16U uwBatOpenLevel, INT16U uwFilter)
//{
//	static INT16U s_uwBatChkCnt = 0;
//	
//	if(!T_ALARM_DATA.bits.bBatOVAlarm)
//	{
//		if(sb16UUnderLevelChk(wBatVoltNew, uwBatOpenLevel, uwFilter, &s_uwBatChkCnt))
//		{
//			T_ALARM_DATA.bits.bBatOVAlarm = true;
//		}
//	}
//	else
//	{
//		if(sb16UOverLevelChk(wBatVoltNew, uwBatOpenLevel - (cBatVoltReal0V25*uwGetBatSerialPcs()), uwFilter, &s_uwBatChkCnt))
//		{
//			T_ALARM_DATA.bits.bBatOVAlarm = false;
//		}
//	}
//}
void	sBatOVAlarmChk(INT16U uwBatOverLevel, INT16U uwFilter)
{
	static INT16U s_uwBatChkCnt = 0;
	
	if(T_ALARM_DATA.bits.bBatOVAlarm)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, uwBatOverLevel - cBatVoltReal0V1, uwFilter, &s_uwBatChkCnt))
		{
			T_ALARM_DATA.bits.bBatOVAlarm = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, uwBatOverLevel, uwFilter, &s_uwBatChkCnt))
		{
			T_ALARM_DATA.bits.bBatOVAlarm = true;
		}
	}
}




void	sBatUnderChk(INT16U uwFilter)
{
	static INT16U s_uwBatChkCnt = 0;
	static INT16S wLowBatUnderVolt = 0;
	static INT16S wLowBatUnderBackVolt = 0;
	INT16S wOPWattPercent = 0;	// 负载百分比
	INT16U uwBatSerialPcs = 0;

	wOPWattPercent = swGetOPWattPercent();  // 负载百分比
	uwBatSerialPcs = uwGetBatSerialPcs();	// 电池节数

	wLowBatUnderVolt = cBatVoltReal2V8 * uwBatSerialPcs;//g_wBatUnderVolt;
//	if(wOPWattPercent < 20)
//	{
//		wLowBatUnderVolt = g_wBatUnderVolt;
		wLowBatUnderBackVolt = wLowBatUnderVolt + cBatVoltReal0V1;//*uwBatSerialPcs;
//	}
//	else if(wOPWattPercent < 50)
//	{
//		wLowBatUnderVolt = cBatVoltReal10V7 * uwBatSerialPcs;
//		wLowBatUnderBackVolt = wLowBatUnderVolt + cBatVoltReal0V5*uwBatSerialPcs;
//	}
//	else if(wOPWattPercent >= 50)
//	{
//		wLowBatUnderVolt = cBatVoltReal10V1 * uwBatSerialPcs;
//		wLowBatUnderBackVolt = wLowBatUnderVolt + cBatVoltReal0V5*uwBatSerialPcs;
//	}
	
	if(T_ALARM_DATA.bits.bBatUVAlarm == false)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, wLowBatUnderVolt, uwFilter, &s_uwBatChkCnt))
		{
			T_ALARM_DATA.bits.bBatUVAlarm = true;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, wLowBatUnderBackVolt, uwFilter, &s_uwBatChkCnt))
		{
			s_uwBatChkCnt = 0;
			T_ALARM_DATA.bits.bBatUVAlarm = false;
		}
	}
}

void	sLowBatCutOffChk(INT16U uwFilter)
{
	static INT16U s_uwLowBatCutOffChkCnt = 0;
	static INT16S wLowBatCutOffVolt = 0;
	INT16S wOPWattPercent = 0;	// 负载百分比
	INT16U uwBatSerialPcs = 0;

	wOPWattPercent = swGetOPWattPercent();  // 负载百分比
	uwBatSerialPcs = uwGetBatSerialPcs();	// 电池节数

	// 内置锂电池
	//if(suwGetEEBatType() == cBatType_USER || suwGetEEBatType() == cBatType_LIB)
	if(1)
	{
		wLowBatCutOffVolt = cBatVoltReal2V7 * uwBatSerialPcs;//suwGetEEBatLowShutDownVolt();
		g_wLowBatCutOffVoltBackVolt = cBatVoltReal2V75 * uwBatSerialPcs;
	}
//	else
//	{
//		wLowBatCutOffVolt = cBatVoltReal10V5 * uwBatSerialPcs;
//		if(wOPWattPercent < 20)
//		{
//			wLowBatCutOffVolt = cBatVoltReal10V5 * uwBatSerialPcs;
//		}
//		else if(wOPWattPercent < 50)
//		{
//			wLowBatCutOffVolt = cBatVoltReal10V2 * uwBatSerialPcs;
//		}
//		else if(wOPWattPercent >= 50)
//		{
//			wLowBatCutOffVolt = cBatVoltReal9V6 * uwBatSerialPcs;
//		}
//		g_wLowBatCutOffVoltBackVolt = cBatVoltReal12V * uwBatSerialPcs;
//	}


	if(T_ALARM_DATA.bits.bAlarmLowBatCutOff == false)
	{
		if(sb16UUnderLevelChk(wBatVoltNew, wLowBatCutOffVolt, uwFilter, &s_uwLowBatCutOffChkCnt))
		{
			T_ALARM_DATA.bits.bAlarmLowBatCutOff = true;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatVoltNew, g_wLowBatCutOffVoltBackVolt, uwFilter, &s_uwLowBatCutOffChkCnt))
		{
			s_uwLowBatCutOffChkCnt = 0;
			T_ALARM_DATA.bits.bAlarmLowBatCutOff = false;
		}
	}

	if(T_ALARM_DATA.bits.bAlarmLowBatCutOff)// 电池低压关输出
	{
		if(swGetWorkMode() == cBatteryMode)
		{
			sSetLoadOnSts(cFBWait);
			sSetWorkMode(cStandbyMode);
			sSetDCDCCtrlSts(cDCDCWait);	// 关DCDC
			sSetLoadOnSts(false);
//			sSetStayStandby(true);
		}
		sSetDCDCCtrlSts(cDCDCWait);	// 关DCDC
		sSetLoadOnSts(false);
		sSetStayStandby(true);
//		mKEYSPSOff;
	}
}

void	sOnGridBatLowChk(void)
{
	INT16S wSOCDischagePct = 100;
	INT16S wVoltDischagePct = 100;
	
	if(fBMSConnectFlg)
	{
//		if(mBMSBatSOC > (suwGetEEOnGridBatdischgedepth() + 5))
//		{
//			wSOCDischagePct = 100;
//		}
//		else if((mBMSBatSOC <= suwGetEEOnGridBatdischgedepth()) || fBMSStopDischgFlg)
//		{
//			wSOCDischagePct = 0;
//		}
//		else
//		{
//			wSOCDischagePct = (mBMSBatSOC -suwGetEEOnGridBatdischgedepth()) * 100 / 5;
//		}
	}
	
//	if(swGetBatVoltFilter() > (swGetEEBatStopFeedVolt() + 40))
//	{
//		wVoltDischagePct = 100;
//	}
//	else if(swGetBatVoltFilter() <= swGetEEBatStopFeedVolt())
//	{
//		wVoltDischagePct = 0;
//	}
//	else
//	{
//		wVoltDischagePct = ((INT32S)(swGetBatVoltFilter() -swGetEEBatStopFeedVolt()) * 100) / 40;
//	}
	
	if(wSOCDischagePct > wVoltDischagePct)
	{
		g_wBatDischgPct = wVoltDischagePct;
	}
	else
	{
		g_wBatDischgPct = wSOCDischagePct;
	}
}


void	sBatVoltRefAdj(void)
{
	if(g_wBatCVVolt != g_wBatVoltRef)
	{
		OS_ENTER_CRITICAL();
		g_wBatVoltRef = g_wBatCVVolt;
		OS_EXIT_CRITICAL();
	}
}

void	sBatPercentCal(void)
{
	static INT16S s_wBatPercentTemp = 0;
	static INT16S s_wBatPercentTempRes = 0;
	INT32S dwTemp;
	INT16S wBatteryInterval;
	INT16S wBatteryReal;
	INT16S wBatPercent;
	INT16U uwBatSerialPcs;
	INT16U uwBatUnderVolt = 0;
	INT16S wOPWattPercent = swGetOPWattPercent();	// 负载百分比

	uwBatSerialPcs = uwGetBatSerialPcs();
	if(wOPWattPercent < 20)
	{
		uwBatUnderVolt = suwGetEEBatLowAlarmVolt();
	}
	else if(wOPWattPercent < 50)
	{
		uwBatUnderVolt = cBatVoltReal10V7 * uwBatSerialPcs;
	}
	else if(wOPWattPercent >= 50)
	{
		uwBatUnderVolt = cBatVoltReal10V1 * uwBatSerialPcs;
	}
	
	wBatteryReal = (INT16S)swGetBatVoltFilter() - uwBatUnderVolt;
	wBatteryInterval = g_wBatFloatVolt - uwBatUnderVolt;
	wBatPercent = (INT16S)(((INT32S)wBatteryReal * 100) / wBatteryInterval);
	
	// Fc=a/(2*PI*t)=(1/255)/2/3.1415927/0.02s=0.0312Hz
	dwTemp = (INT32S)s_wBatPercentTemp * 255 + wBatPercent + s_wBatPercentTempRes;
	s_wBatPercentTempRes = dwTemp & 0x00FF;
	s_wBatPercentTemp = dwTemp >> 8;
	
	if(s_wBatPercentTemp < 0)
	{
		g_wBatVoltPct = 0;
	}
	else if(s_wBatPercentTemp > 100)
	{
		g_wBatVoltPct = 100;
	}
	else
	{
		g_wBatVoltPct = s_wBatPercentTemp;
	}
}


INT16S	swBatWattCal(void)
{
	INT16S	wBatWattTemp = 0;
	
	wBatWattTemp = (INT16S)(((INT32S)wBatVoltNew * wBatCurrNew + 50) / 100);
		
	return wBatWattTemp;
}

INT16S	swPvWattCal(void)
{
	INT16S	wBatWattTemp = 0;
	
	wBatWattTemp = (INT16S)(((INT32S)wPv1VoltNew * wPvInCurrNew + 500) / 1000);
		
	return wBatWattTemp;
}



void	sBusCurrOverChk(INT16U uwBusCurrOverLevel, INT16U uwFilter)
{
	static INT16U s_uwBusCurrChkCnt = 0;
	
	if(T_FAULT_DATA.bits.bDcDcSoftOC == true)
	{
		if(sb16UUnderLevelChk(wBusCurrNew, uwBusCurrOverLevel - 500, uwFilter, &s_uwBusCurrChkCnt))
		{
			T_FAULT_DATA.bits.bDcDcSoftOC = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBusCurrNew, uwBusCurrOverLevel, uwFilter, &s_uwBusCurrChkCnt))
		{
			T_FAULT_DATA.bits.bDcDcSoftOC = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cDCDCCurrOver);
			}
		}
	}
}

void	sBatCurrOverChk(INT16U uwBatCurrOverLevel, INT16U uwFilter,INT16U uwBatCurrOverLeve2, INT16U uwFilter2 )
{
	static INT16U s_uwBatCurrChkCnt = 0;
	static INT16U s_uwBatCurrChkCnt2 = 0;
	
	if(T_FAULT_DATA.bits.bDcDcSoftOC == true)
	{
		if(sb16UUnderLevelChk(wBatCurrNew, uwBatCurrOverLevel - 5, uwFilter, &s_uwBatCurrChkCnt))
		{
			T_FAULT_DATA.bits.bDcDcSoftOC = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wBatCurrNew, uwBatCurrOverLevel, uwFilter, &s_uwBatCurrChkCnt)\
		|| sb16UOverLevelChk(wBatCurrNew, uwBatCurrOverLeve2, uwFilter2, &s_uwBatCurrChkCnt2))
		{
			T_FAULT_DATA.bits.bDcDcSoftOC = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cBatCurrOver);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////// PV
void	sPv1VoltOverChk(INT16U uwPvOverLevel, INT16U uwFilter)
{
	static INT16U s_uwPvVoltChkCnt = 0;

	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}

	if(T_ALARM_DATA.bits.bPv1OVAlarm == true)
	{
		if(sb16UUnderLevelChk(wPv1VoltNew, uwPvOverLevel - 200, uwFilter, &s_uwPvVoltChkCnt))
		{
			T_ALARM_DATA.bits.bPv1OVAlarm = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wPv1VoltNew, uwPvOverLevel, uwFilter, &s_uwPvVoltChkCnt))
		{
			T_ALARM_DATA.bits.bPv1OVAlarm = true;
			mPV_FANENOff;
		}
	}
}

void	sPv1CurrOverChk(INT16U uwPvOverLevel, INT16U uwFilter)
{
	static INT16U s_uwPvCurrChkCnt = 0;
	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}	
	if(T_ALARM_DATA.bits.bPv1OCAlarm == true)
	{
		if(sb16UUnderLevelChk(wPv1BatCurrNew, uwPvOverLevel - 50, uwFilter, &s_uwPvCurrChkCnt))
		{
			T_ALARM_DATA.bits.bPv1OCAlarm = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wPv1BatCurrNew, uwPvOverLevel, uwFilter, &s_uwPvCurrChkCnt))
		{
			T_ALARM_DATA.bits.bPv1OCAlarm = true;
			mPV_FANENOff;
		}
	}
}

void	sPv1UnderChk(INT16U uwFilter)
{
	static INT16U s_uwPv1ChkCnt = 0;
	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}	
	if(T_ALARM_DATA.bits.bPv1UVAlarm == false)
	{
		if(sb16UUnderLevelChk(wPv1VoltNew, g_wPv1UnderVolt, uwFilter, &s_uwPv1ChkCnt))
		{
			T_ALARM_DATA.bits.bPv1UVAlarm = true;
			mPV_FANENOff;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wPv1VoltNew, g_wPv1UnderBackVolt, uwFilter, &s_uwPv1ChkCnt))
		{
			T_ALARM_DATA.bits.bPv1UVAlarm = false;
		}
	}
}
void sTrickleChg(void)//涓流充电
{
	INT16S wTemp = 0;
	static INT16S wCntTemp = 0;
	wTemp = swGetBatVoltNew();
	

	if((wTemp <= g_wTriChgVoltLLimit) || (wTemp >= g_wTriChgVoltHLimit))
	{
		g_wTriChgFlag =true;			

		g_wTriChgCurrLimit =  g_wTriChgPowerLimit *100 / wTemp;
		
		if(g_wTriChgCurrLimit > g_wTriChgCurrLimitMax)
		{
			g_wTriChgCurrLimit = g_wTriChgCurrLimitMax;
		}	
		wCntTemp = 0;
	}
	else
	{
		if(++wCntTemp > 250)
		{
			g_wTriChgFlag = false;
			wCntTemp = 0;
		}
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetBusVoltNew(void)
{
	return wBusVoltNew;
}

INT16S	swGetBusCurrNew(void)
{
	return wBusCurrNew;
}

INT16S	swGetBatVoltNew(void)
{
	return wBatVoltNew;
}

INT16S	swGetBatVolt2New(void)
{
	return wBatVolt2New;
}


INT16S	swGetBatCurrNew(void)
{
	return wBatCurrNew;
}

INT16S	swGetPv1VoltNew(void)
{
	return wPv1VoltNew;
}

INT16S	swGetPv1CurrNew(void)
{
	return wPv1CurrNew;
}

INT16S	swGetPv1BatCurrNew(void)
{
	return wPv1BatCurrNew;
}

INT16S	swGetHsTwTempNew(void)
{
	return wHsTwTempNew;
}

INT16S	swGetHsInvTempNew(void)
{
	return wHsInvTempNew;
}

INT16S	swGetHsPvTempNew(void)
{
	return wHsPvTempNew;
}

INT16S	swGetHsBatHTempNew(void)
{
	return wHsBatHTempNew;
}

INT16S	swGetBatWattNew(void)
{
	return wBatWattNew;
}

INT16S	swGetPvWattNew(void)
{
	return wPvWattNew;
}

INT16S	swGetLLCOCPCurrNew(void)
{
	return wLLCOCPCurrNew;
}

INT16S	swGetLV12VVoltNew(void)
{
	return wLV12VVoltNew;
}

INT16S	swGetAC12VVoltNew(void)
{
	return wAC12VVoltNew;
}

INT16S	swGetB1VoltNew(void)
{
	return wB1VoltNew;
}

INT16S	swGetB2VoltNew(void)
{
	return wB2VoltNew;
}

INT16S	swGetBVoltNew(void)
{
	return wBVoltNew;
}

INT16S	swGetPvInCurrNew(void)
{
	return wPvInCurrNew;
}

INT16S	swGetPvInTzCurrNew(void)
{
	return wPvInTzCurrNew;
}

INT16S	swGetLLCTempNew(void)
{
	return wHsLLCTempNew;
}

INT16S	swGetBat1TempNew(void)
{
	return wHsBat1TempNew;
}

INT16S	swGetBat2TempNew(void)
{
	return wHsBat2TempNew;
}

INT16S	swGetMinCellTempNew(void)
{
	return wMinCellTempNew;
}

INT16S	swGetMaxCellTempNew(void)
{
	return wMaxCellTempNew;
}

INT16S	swGetAvgCellTempNew(void)
{
	return wAvgCellTempNew;
}

INT16S	swGetMinCellVoltNew(void)
{
	return wMinCellVoltNew;
}

INT16S	swGetMaxCellVoltNew(void)
{
	return wMaxCellVoltNew;
}

INT16S	swGetAvgCellVoltNew(void)
{
	return wAvgCellVoltNew;
}

//////////////////////////////////////////////////// Filter
INT16S	swGetBusVoltFilter(void)
{
	return wBusVoltFilter;
}

INT16S	swGetBusCurrFilter(void)
{
	return wBusCurrFilter;
}

INT16S	swGetBatVoltFilter(void)
{
	return wBatVoltFilter;
}

INT16S	swGetBatVolt2Filter(void)
{
	return wBatVolt2Filter;
}

INT16S	swGetBatCurrFilter(void)
{
	return wBatCurrFilter;
}

INT16S	swGetPv1VoltFilter(void)
{
	return wPv1VoltFilter;
}

INT16S	swGetPv1CurrFilter(void)
{
	return wPv1CurrFilter;
}

INT16S	swGetPv1BatCurrFilter(void)
{
//	if(suwGetPV1CtrlSts() == cPVWork || suwGetEEAdcBiasAdj())
//	{
		return wPv1BatCurrFilter;
//	}
//	else
//	{
//		return 0;
//	}
}

INT16S	swGetHsTwTempFilter(void)
{
	return wHsTwTempFilter;
}

INT16S	swGetHsInvTempFilter(void)
{
	return wHsInvTempFilter;
}

INT16S	swGetHsPvTempFilter(void)
{
	return wHsPvTempFilter;
}

INT16S	swGetHsBatHTempFilter(void)
{
	return wHsBatHTempFilter;
}

INT16S	swGetBatWattFilter(void)
{
	return wBatWattFilter;
}

INT16S	swGetPvWattFilter(void)
{
//	if(suwGetPV1CtrlSts() == cPVWork || suwGetEEAdcBiasAdj())
//	{
		return wPvWattFilter;
//	}
//	else
//	{
//		return 0;
//	}
}

INT16S	swGetLLCOCPCurrFilter(void)
{
	return wLLCOCPCurrFilter;
}

INT16S	swGetLV12VVoltFilter(void)
{
	return wLV12VVoltFilter;
}

INT16S	swGetAC12VVoltFilter(void)
{
	return wAC12VVoltFilter;
}

INT16S	swGetB1VoltFilter(void)
{
	return wB1VoltFilter;
}

INT16S	swGetB2VoltFilter(void)
{
	return wB2VoltFilter;
}

INT16S	swGetBVoltFilter(void)
{
	return wBVoltFilter;
}

INT16S	swGetPvInCurrFilter(void)
{
	return wPvInCurrFilter;
}

INT16S	swGetPvInTzCurrFilter(void)
{
	return wPvInTzCurrFilter;
}

INT16S	swGetLLCTempFilter(void)
{
	return wHsLLCTempFilter;
}

INT16S	swGetBat1TempFilter(void)
{
	return wHsBat1TempFilter;
}

INT16S	swGetBat2TempFilter(void)
{
	return wHsBat2TempFilter;
}

INT16S	swGetMinCellTempFilter(void)
{
	return wMinCellTempFilter;
}

INT16S	swGetMaxCellTempFilter(void)
{
	return wMaxCellTempFilter;
}

INT16S	swGetAvgCellTempFilter(void)
{
	return wAvgCellTempFilter;
}

INT16S	swGetMinCellVoltFilter(void)
{
	return wMinCellVoltFilter;
}

INT16S	swGetMaxCellVoltFilter(void)
{
	return wMaxCellVoltFilter;
}

INT16S	swGetAvgCellVoltFilter(void)
{
	return wAvgCellVoltFilter;
}

//////////////
INT16S	swGetBatDischgPct(void)
{
	return g_wBatDischgPct;
}

INT16S	swGetBatVoltRef(void)
{
	return g_wBatVoltRef;
}

INT16S	swGetBatVoltPct(void)
{
	return g_wBatVoltPct;
}

INT16S	swGetBatSOCReal(void)
{
	return g_wBatSOCReal;
}

INT16S	swGetBatDsgCurrLimit(void)
{
	return g_wBatDsgCurrLimit;
}


INT8U	subGetBatUnderSts(void)
{
	return fBatteryStatus.bits.bBatUnder;
}

INT8U	subGetParaBatOpenSts(void)
{
	if(fBatteryStatus.bits.bBatOpen)// || g_uniInputStatus.BIT.uwBatOpen)
	{
		return true;
	}
	else
	{
		return false;
	}
}
INT16S	swGetTriChgFlag(void)
{
	return g_wTriChgFlag;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetBusVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wBusVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBusVoltNew + (INT32S)wBusVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBusVoltFilter = dwTemp >> 5;
}

void	sSetBusCurrNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wBusCurrNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBusCurrNew + (INT32S)wBusCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBusCurrFilter = dwTemp >> 5;
}

void	sSetBatVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	// 防止校准参数导致出现负压
	if(wVolt < 0)
	{
		wVolt = 0;
	}
	wBatVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBatVoltNew + (INT32S)wBatVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBatVoltFilter = dwTemp >> 5;
}

void	sSetBatVolt2New(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	// 防止校准参数导致出现负压
	if(wVolt < 0)
	{
		wVolt = 0;
	}
	wBatVolt2New = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBatVolt2New + (INT32S)wBatVolt2Filter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBatVolt2Filter = dwTemp >> 5;
}


void	sSetBatCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	// if(suwGetPV1CtrlSts() == cPVWork)	// PV控制器工作时，才计算相关参数
	// {
	// 	wBatCurrNew = wCurr - wPv1BatCurrNew;
	// }
	// else
	// {
		wBatCurrNew = wCurr;
	// }
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBatCurrNew + (INT32S)wBatCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBatCurrFilter = dwTemp >> 5;
}

void	sSetPv1VoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	if(wVolt < 200)
	{
		wVolt = 0;
	}
	wPv1VoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPv1VoltNew + (INT32S)wPv1VoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPv1VoltFilter = dwTemp >> 5;
}

void	sSetPv1CurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wPv1CurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPv1CurrNew + (INT32S)wPv1CurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPv1CurrFilter = dwTemp >> 5;
}


void	sSetPv1BatCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wPv1BatCurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPv1BatCurrNew + (INT32S)wPv1BatCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPv1BatCurrFilter = dwTemp >> 5;
}

void	sSetPv1BatWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wPv1BatWattNew = wWatt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPv1BatWattNew + (INT32S)wPv1BatWattFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPv1BatWattFilter = dwTemp >> 5;
}


void	sSetHsTwTempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsTwTempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsTwTempNew + (INT32S)wHsTwTempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsTwTempFilter = dwTemp >> 5;
}

void	sSetHsInvTempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsInvTempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsInvTempNew + (INT32S)wHsInvTempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsInvTempFilter = dwTemp >> 5;
}

void	sSetHsPvTempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsPvTempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsPvTempNew + (INT32S)wHsPvTempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsPvTempFilter = dwTemp >> 5;
}

void	sSetHsBatHTempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsBatHTempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsBatHTempNew + (INT32S)wHsBatHTempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsBatHTempFilter = dwTemp >> 5;
}

/////////////

void	sSetBatWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wBatWattNew = wWatt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBatWattNew + (INT32S)wBatWattFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBatWattFilter = dwTemp >> 5;
}

void	sSetPvWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wPvWattNew = wWatt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPvWattNew + (INT32S)wPvWattFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPvWattFilter = dwTemp >> 5;
}

void	sSetLLCOCPCurrNew(INT16S wLLCOCPCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wLLCOCPCurrNew = wLLCOCPCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wLLCOCPCurrNew + (INT32S)wLLCOCPCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wLLCOCPCurrFilter = dwTemp >> 5;
}

void	sSetLV12VVoltNew(INT16S wLV12VVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wLV12VVoltNew = wLV12VVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wLV12VVoltNew + (INT32S)wLV12VVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wLV12VVoltFilter = dwTemp >> 5;
}

void	sSetAC12VVoltNew(INT16S wAC12VVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wAC12VVoltNew = wAC12VVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wAC12VVoltNew + (INT32S)wAC12VVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wAC12VVoltFilter = dwTemp >> 5;
}

void	sSetB1VoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	// 防止校准参数导致出现负压
	if(wVolt < 0)
	{
		wVolt = 0;
	}
	wB1VoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wB1VoltNew + (INT32S)wB1VoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wB1VoltFilter = dwTemp >> 5;
}

void	sSetB2VoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	// 防止校准参数导致出现负压
	if(wVolt < 0)
	{
		wVolt = 0;
	}
	wB2VoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wB2VoltNew + (INT32S)wB2VoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wB2VoltFilter = dwTemp >> 5;
}

void	sSetBVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	// 防止校准参数导致出现负压
	if(wVolt < 0)
	{
		wVolt = 0;
	}
	wBVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wBVoltNew + (INT32S)wBVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wBVoltFilter = dwTemp >> 5;
}

void	sSetPvInCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wPvInCurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPvInCurrNew + (INT32S)wPvInCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPvInCurrFilter = dwTemp >> 5;
}

void	sSetPvInTzCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wPvInTzCurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wPvInTzCurrNew + (INT32S)wPvInTzCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wPvInTzCurrFilter = dwTemp >> 5;
}

void	sSetHsLLCTempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsLLCTempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsLLCTempNew + (INT32S)wHsLLCTempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsLLCTempFilter = dwTemp >> 5;
}

void	sSetHsBat1TempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsBat1TempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsBat1TempNew + (INT32S)wHsBat1TempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsBat1TempFilter = dwTemp >> 5;
}

void	sSetHsBat2TempNew(INT16S wTemp)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wHsBat2TempNew = wTemp;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wHsBat2TempNew + (INT32S)wHsBat2TempFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wHsBat2TempFilter = dwTemp >> 5;
}

void	sSetMinCellTempNew(void)
{
	// 最低电芯温度
	if(wHsBat1TempNew <= wHsBat2TempNew)
	{
		wMinCellTempNew = wHsBat1TempNew;
		wMaxCellTempNew = wHsBat2TempNew;
	}
	else
	{
		wMinCellTempNew = wHsBat2TempNew;
		wMaxCellTempNew = wHsBat1TempNew;
	}

	// 最高电芯温度
	if(wHsBat1TempFilter <= wHsBat2TempFilter)
	{
		wMinCellTempFilter = wHsBat1TempFilter;
		wMaxCellTempFilter = wHsBat2TempFilter;
	}
	else
	{
		wMinCellTempFilter = wHsBat2TempFilter;
		wMaxCellTempFilter = wHsBat1TempFilter;
	}

	// 电芯平均温度
	wAvgCellTempNew = (wHsBat1TempNew + wHsBat2TempNew) >> 1;
	wAvgCellTempFilter = (wHsBat1TempFilter + wHsBat2TempFilter) >> 1;
}

void	sSetMinCellVoltNew(void)
{
	if(wB1VoltNew <= wB2VoltNew)
	{
		wMinCellVoltNew = wB1VoltNew;
		wMaxCellVoltNew = wB2VoltNew;
	}
	else
	{
		wMinCellVoltNew = wB2VoltNew;
		wMaxCellVoltNew = wB1VoltNew;
	}

	if(wB1VoltFilter <= wB2VoltFilter)
	{
		wMinCellVoltFilter = wB1VoltFilter;
		wMaxCellVoltFilter = wB2VoltFilter;
	}
	else
	{
		wMinCellVoltFilter = wB2VoltFilter;
		wMaxCellVoltFilter = wB1VoltFilter;
	}

	wAvgCellVoltNew = (wB1VoltNew + wB2VoltNew) >> 1;
	wAvgCellVoltFilter = (wB1VoltFilter + wB2VoltFilter) >> 1;
}

