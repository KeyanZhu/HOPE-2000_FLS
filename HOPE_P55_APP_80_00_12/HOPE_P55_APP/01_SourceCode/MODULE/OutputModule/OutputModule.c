/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__OUTPUT_MODULE_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      cTimer10ms
#define         cT10ms                         (10 / cTimerBase)
#define         cT20ms                         (20 / cTimerBase)
#define         cT30ms                         (30 / cTimerBase)
#define         cT50ms                         (50 / cTimerBase)
#define         cT200ms                         (200 / cTimerBase)
#define         cT1sec                          (5000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)
#define         cT20sec                          (20000 / cTimerBase)
#define         cT30sec                          (30000 / cTimerBase)
#define         cT1min                          (60000 / cTimerBase)


/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S wRLineWattFilter;		// 1W
extern INT16S wRLineVAFilter;

/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16S wROpVoltNew;				// 0.1V
INT16S wROpCurrNew;				// 0.01A
INT16S wROpFreqNew;				// 0.01Hz
INT16S wROpWattNew;				// 1W
INT16S wROpNLineNVoltNew;		// 0.1V
INT16S wNEVoltNew;				// 0.1V
INT16S wROpVarNew;				// 1Var
INT16S wROpVANew;				// 1VA
INT16S wROpPFNew;				// 0.001

INT16S wROpVoltFilter;			// 0.1V
INT16S wROpCurrFilter;			// 0.01A
INT16S wROpFreqFilter;			// 0.01Hz
INT16S wROpWattFilter;			// 1W
INT16S wROpNLineNVoltFilter;	// 0.1V
INT16S wNEVoltFilter;			// 0.1V
INT16S wROpVarFilter;			// 1Var
INT16S wROpVAFilter;			// 1VA
INT16S wROpPFFilter;			// 0.001
INT16S wROpVAFilterConversion;	// 1VA	折算功率

INT16S g_wOPBatPercent = 0;			// 1%
INT16S g_wROPBatPercent = 0;		// 1%
INT16S g_wOPWattBatPercent = 0;		// 1%
INT16S g_wROPWattBatPercent = 0;	// 1%
INT16S g_wOPPercent = 0;			// 1%
INT16S g_wROPPercent = 0;			// 1%
INT16S g_wOPWattPercent = 0;		// 1%
INT16S g_wROPWattPercent = 0;		// 1%
INT16S g_wOPVAPercent = 0;			// 1%
INT16S g_wROPVAPercent = 0;			// 1%
INT16U g_uwOverLoadLevel1Cnt = 0;
INT16U g_uwOverLoadLevel2Cnt = 0;
INT16U g_uwOverLoadLevel3Cnt = 0;
INT16U g_uwOverLoadLevel4Cnt = 0;
INT16U g_uwOverLoadRstDelayCnt = 0;

INT16S g_wRLinePercent = 0;			// 1%
//INT16S g_wRLinePercent = 0;			// 1%
INT16S g_wRLineWattPercent = 0;		// 1%
INT16S g_wRLinePWattPercent = 0;	// 1%
INT16S g_wRLineVAPercent = 0;		// 1%
INT16S g_wRLinePVAPercent = 0;		// 1%

INT16U g_uwOPCurrOverLevel1 = 650;
INT16U g_uwOPCurrOverLevel2 = 800;
INT16U g_uwOPCurrOverLevel3 = 1000;

/********************************************************************************
* Output variables																*
********************************************************************************/
union OUTPUT_STATUS_TABLE
{
	struct OUTPUT_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U	bOverLoadBypass:1;
		INT16U	bOverLoadAlarm:1;
		INT16U	rsvd1:2;
		
		// BIT4-7
		INT16U	rsvd2:4;
		
		// BIT8-11
		INT16U	rsvd3:4;
		
		// BIT12-15
		INT16U	rsvd4:4;
	} bits;
	INT16U data;
} fOutputStatus;

/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16S wConvertMaxWatt;
INT16S wConvertBatMaxWatt;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sOutputInitial(void)
{
	g_uwOverLoadLevel1Cnt = 0;
	g_uwOverLoadLevel2Cnt = 0;
	g_uwOverLoadLevel3Cnt = 0;
	g_uwOverLoadRstDelayCnt = 0;

	fOutputStatus.data = 0;
	wConvertMaxWatt = uwGetInvWattMax();
	wConvertBatMaxWatt = uwGetInvWattMax();
	sOutputParaUpdate();
}

void	sOutputParaUpdate(void)
{
	
}

void	sROpPowerCal(void)
{
	static INT16S s_wVarRes = 0;
	static INT16S s_wVARes = 0;
	static INT16S s_wPFRes = 0;
	INT32S dwTemp;
	
	dwTemp = ((INT32S)wROpVoltNew * wROpCurrNew + 500) / 1000;
	if(swAbs(dwTemp) < swAbs(wROpWattNew))
	{
		dwTemp = wROpWattNew;
	}
	wROpVANew = dwTemp;
	
	dwTemp = ((INT32S)wROpVANew * wROpVANew) - ((INT32S)wROpWattNew * wROpWattNew);
	if(dwTemp > 0)
	{
		wROpVarNew = swRoot((INT32U)dwTemp);
	}
	else
	{
		wROpVarNew = 0;
	}
	
	if(wROpVANew != 0)
	{
		wROpPFNew = ((INT32S)wROpWattNew * 1000) / wROpVANew;
	}
	else
	{
		wROpPFNew = 0;
	}
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpVarNew + (INT32S)wROpVarFilter * 31 + (INT32S)s_wVarRes;
	s_wVarRes = dwTemp & 0x001F;
	wROpVarFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpVANew + (INT32S)wROpVAFilter * 31 + (INT32S)s_wVARes;
	s_wVARes = dwTemp & 0x001F;
	wROpVAFilter = dwTemp >> 5;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpPFNew + (INT32S)wROpPFFilter * 31 + (INT32S)s_wPFRes;
	s_wPFRes = dwTemp & 0x001F;
	wROpPFFilter = dwTemp >> 5;

	// 视在折算功率
	if(suwGetEEPowerConversion())
	{
		dwTemp = ((INT32S)(-uwGetLoadConversionWatt()) * (-uwGetLoadConversionWatt())) \
				+ ((INT32S)wROpVarFilter * wROpVarFilter);
		wROpVAFilterConversion = swRoot((INT32U)dwTemp);
	}
}


void	sOPPercentCal(void)
{
	static INT16U s_uwOverLoadBypassCnt = 0;
	INT16S wTempPercent;
	INT16S uwInvWattMax = 0;

	uwInvWattMax = uwGetInvWattMax();
	if(swGetWorkMode() == cPowerOnMode)
	{
		g_wOPWattPercent = 0;
		g_wROPWattPercent = 0;
		g_wOPVAPercent = 0;	
		g_wROPVAPercent = 0;
		g_wOPPercent = 0;
		return ;
	}
	
	// Turbo模式下，负载百分比折算按照额定功率折算
//	if((suwGetEETurboMode() && suwGetEEGridInputRange() == cAPL))	
	if(0)	
	{
		wConvertMaxWatt = uwInvWattMax;
		wConvertBatMaxWatt  = uwInvWattMax;
	}
	else
	{
		// 计算功率折算
//		if(swGetWorkMode() == cBatteryMode)
//		{
			wConvertMaxWatt = (INT16S)(((INT32S)swGetROpVoltNew() * swGetROpVoltNew()) / uwGetInvWattRes());
			//wConvertMaxWatt = (INT16S)(((INT32S)swGetRInvVoltNew() * swGetRInvVoltNew()) / uwGetInvWattRes());
//		}
//		else
//		{
//			wConvertMaxWatt = uwInvWattMax;
//			wConvertBatMaxWatt  = uwInvWattMax;
//		}	

		// U平方 * R 	= 功率
		// U平方 / 功率 = R
		// U平方 / R 	= 功率

		// 2300 * 2300 = 5,290,000;
		// 5,290,000 / 1000 = 5290;
		// 5,290,000 / 2000 = 2645;
		// 5,290,000 / 3000 = 1763;
		// 额定1K，投载2K，瞬时计算得出5,290,000 / 2000 = 2645;
		// 等效电阻(2645) × 额定功率(1000) = 2645000;
		// 开方得到1,626.34
		wConvertBatMaxWatt = wConvertMaxWatt;
		
		if(wConvertMaxWatt > uwInvWattMax) 	// 额定功率
		{
			wConvertMaxWatt = uwInvWattMax;
		}
		else if(wConvertMaxWatt < 150)		// 90V电压折算满功率为153W
		{
			wConvertMaxWatt = 150;
		}

		if(wConvertBatMaxWatt > uwInvWattMax) 
		{
			wConvertBatMaxWatt = uwInvWattMax;
		}
		else if(wConvertBatMaxWatt < 150)
		{
			wConvertBatMaxWatt = 150;
		}
	}
	
	// 以折算功率作为满功率计算负载百分比	
	// OP
	if(swGetWorkMode() == cBatteryMode)		//需要以离网0.8K有功作为满功率折算百分比
	{
		g_wOPWattPercent = (INT16S)((INT32S)wROpWattFilter * 100 / wConvertBatMaxWatt);
		g_wROPWattPercent = (INT16S)((INT32S)wROpWattFilter * 100 / wConvertBatMaxWatt);
		g_wOPVAPercent = (INT16S)((INT32S)wROpVAFilter * 100 / wConvertMaxWatt);	
		g_wROPVAPercent = (INT16S)((INT32S)wROpVAFilter * 100 / wConvertMaxWatt);
	}
	else			// 1K满功率
	{
		g_wOPWattPercent = (INT16S)((INT32S)wROpWattFilter * 100 / wConvertMaxWatt);
		g_wROPWattPercent = (INT16S)((INT32S)wROpWattFilter * 100 / wConvertMaxWatt);
		g_wOPVAPercent = (INT16S)((INT32S)wROpVAFilter * 100 / wConvertMaxWatt);	
		g_wROPVAPercent = (INT16S)((INT32S)wROpVAFilter * 100 / wConvertMaxWatt);
	}

//	// GRID
//	g_wRLineWattPercent = (INT16S)((INT32S)wRLineWattFilter * 100 / wConvertMaxWatt);
//	g_wRLinePWattPercent = (INT16S)((INT32S)wRLineWattFilter * 100 / wConvertMaxWatt);
//	g_wRLineVAPercent = (INT16S)((INT32S)wRLineVAFilter * 100 / wConvertMaxWatt);	
//	g_wRLinePVAPercent = (INT16S)((INT32S)wRLineVAFilter * 100 / wConvertMaxWatt);
	
	if(g_wOPWattPercent > g_wOPVAPercent)
	{
		g_wOPPercent = g_wOPWattPercent;
	}
	else
	{
		g_wOPPercent = g_wOPVAPercent;
	}
	
	if(g_wROPWattPercent > g_wROPVAPercent)
	{
		g_wROPPercent = g_wROPWattPercent;
	}
	else
	{
		g_wROPPercent = g_wROPVAPercent;
	}
	
	if(g_wOPPercent < g_wROPPercent)
	{
		g_wOPPercent = g_wROPPercent;
	}
//	if(g_wOPPercent < g_wRLineWattPercent)
//	{
//		g_wOPPercent = g_wRLineWattPercent;
//	}
	
	//if(g_uwMachineType == cOffGrid3LoadBat)
	if(1)
	{
		if(swGetWorkMode() == cBatteryMode)
		{
			wTempPercent = g_wOPPercent;
		}
		else if(swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode || swGetWorkMode() == cChgMode)
		{
			//wTempPercent = (INT32S)g_wROPPercent * suwGetACOutputRatedVolt() / wRLineVoltNew;
			//wTempPercent = wTempPercent * suwGetACOutputRatedVolt() / wRLineVoltNew;
			wTempPercent = (INT32S)g_wROPPercent * 2300 / wROpVoltFilter;
			wTempPercent = (INT32S)wTempPercent * 2300 / wROpVoltFilter;
		}
		else
		{
			wTempPercent = 0;
		}
		
//		#warn 过载允许旁路
		//if(swGetEEOverLoadBpsEn())
		if(1)
		{
			if(fOutputStatus.bits.bOverLoadBypass == true)
			{
				if(sb16UUnderLevelChk(wTempPercent, 85, 5, &s_uwOverLoadBypassCnt))
				{
					fOutputStatus.bits.bOverLoadBypass = false;
				}
			}
			else
			{
				if(sb16UOverLevelChk(wTempPercent, 100, 5, &s_uwOverLoadBypassCnt))
				{
					fOutputStatus.bits.bOverLoadBypass = true;
				}			
			}
		}
		else
		{
			fOutputStatus.bits.bOverLoadBypass = false;
			s_uwOverLoadBypassCnt = 0;
		}
	}
	else
	{
		fOutputStatus.bits.bOverLoadBypass = false;
		s_uwOverLoadBypassCnt = 0;
	}
}

INT16S wOverLoadBatToLineEnDisable = 0;
void	sOverLoadChk(void)
{
	if(swGetWorkMode() != cBatteryMode)
	{
		g_uwOverLoadLevel1Cnt = 0;
		g_uwOverLoadLevel2Cnt = 0;
		g_uwOverLoadLevel3Cnt = 0;
		g_wOPPercent  = 0;
		return ;
	}
		
	if(g_wOPPercent > 200)
	{
		if(g_uwOverLoadLevel1Cnt < 7000) g_uwOverLoadLevel1Cnt++;
		if(g_uwOverLoadLevel2Cnt < 7000) g_uwOverLoadLevel2Cnt++;
		if(g_uwOverLoadLevel3Cnt < 7000) g_uwOverLoadLevel3Cnt++;
		g_uwOverLoadRstDelayCnt = 10;
	}
	else if(g_wOPPercent > 150)
	{
		if(g_uwOverLoadLevel1Cnt > 0) g_uwOverLoadLevel1Cnt--;
		if(g_uwOverLoadLevel2Cnt < 7000) g_uwOverLoadLevel2Cnt++;
		if(g_uwOverLoadLevel3Cnt < 7000) g_uwOverLoadLevel3Cnt++;
		g_uwOverLoadRstDelayCnt = 10;		
	}
	else if(g_wOPPercent > 110)
	{
		if(g_uwOverLoadLevel1Cnt > 0) g_uwOverLoadLevel1Cnt--;
		if(g_uwOverLoadLevel2Cnt > 0) g_uwOverLoadLevel2Cnt--;
		if(g_uwOverLoadLevel3Cnt < 7000) g_uwOverLoadLevel3Cnt++;
		g_uwOverLoadRstDelayCnt = 10;			
	}
	else
	{
		if(g_uwOverLoadRstDelayCnt > 0)
		{
			g_uwOverLoadRstDelayCnt--;
		}
		else
		{
			if(g_uwOverLoadLevel1Cnt > 5) g_uwOverLoadLevel1Cnt = 5;
			if(g_uwOverLoadLevel2Cnt > 60) g_uwOverLoadLevel2Cnt = 60;
			if(g_uwOverLoadLevel3Cnt > 60) g_uwOverLoadLevel3Cnt = 60;
		}
		if(g_uwOverLoadLevel1Cnt > 0) g_uwOverLoadLevel1Cnt--;
		if(g_uwOverLoadLevel2Cnt > 0) g_uwOverLoadLevel2Cnt--;
		if(g_uwOverLoadLevel3Cnt > 0) g_uwOverLoadLevel3Cnt--;	
	}

	// 市电模式不检测百分比过载，任务里面检测过流过载
	// 离网逆变控制器不工作时不检测过载，防止电池低压关逆变后触发过载故障
	if((swGetWorkMode() != cBypassMode) && (swGetWorkMode() != cLineMode)\
		&& (swGetLoadOnSts() == cFBInvCtrlVolt))
	{
		if(g_uwOverLoadLevel1Cnt >= 5 );//|| g_uwOverLoadLevel2Cnt >= 550 || g_uwOverLoadLevel3Cnt > 1050)
		{
			T_FAULT_DATA.bits.bLoadOverLoad = true;
			sSetFaultCode(cOverLoad);
			g_uwOverLoadLevel1Cnt = 0;
			g_uwOverLoadLevel2Cnt = 0;
			g_uwOverLoadLevel3Cnt = 0;
		}
	}
	else
	{
		if(g_uwOverLoadLevel1Cnt > 5) g_uwOverLoadLevel1Cnt = 5;
		if(g_uwOverLoadLevel2Cnt > 1000) g_uwOverLoadLevel2Cnt = 1000;
		if(g_uwOverLoadLevel3Cnt > 6000) g_uwOverLoadLevel3Cnt = 6000;
	}

	if((swGetWorkMode() == cBatteryMode))
	{
		if(T_ALARM_DATA.bits.bOverLoadAlarm)	// 负载过载告警 // 离网模式
		{
			if(g_uwOverLoadLevel3Cnt < 50)
			{
				T_ALARM_DATA.bits.bOverLoadAlarm = false;
			}
		}
		else
		{
			if(g_uwOverLoadLevel3Cnt > 500)
			{
				T_ALARM_DATA.bits.bOverLoadAlarm = true;
			}
		}
	}
}

void	sOpVoltHighChk(INT8U ubFilter)
{
	static INT16U s_uwROpVoltHighCnt = 0;
	INT8U ubOpVoltHigh = false;

	if(T_FAULT_DATA.bits.bOutOV == true)
	{
		if(sb16UUnderLevelChk(wROpVoltNew, uwGetLoadVoltOver() - cAcVoltReal10V, ubFilter, &s_uwROpVoltHighCnt))
		{
			s_uwROpVoltHighCnt = 0;
			T_FAULT_DATA.bits.bOutOV = false;
		}
	}
	else
	{
		//	if(swGetWorkMode() == cBatteryMode || swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode)
		if(hoROPRLY)
		{
			if(sb16UOverLevelChk(wROpVoltNew, uwGetLoadVoltOver(), ubFilter, &s_uwROpVoltHighCnt))
			{
				ubOpVoltHigh = true;
			}
			if(ubOpVoltHigh)
			{
				s_uwROpVoltHighCnt = 0;
				T_FAULT_DATA.bits.bOutOV = true;
				sSetFaultCode(cOutputVoltHigh);
			}
		}
	}
}

void	sOpVoltLowChk(INT8U ubFilter)
{
	static INT16U s_uwROpVoltLowCnt = 0;
	INT8U ubOpVoltLow = false;
	INT16U ubOpVolt = 1700;

	if(suwGetEEGridInputRange() == cAPL)
	{
		ubOpVolt = uwGetLoadVoltLowAPL();
	}
	else if(suwGetEEGridInputRange() == cUPS)
	{
		ubOpVolt = uwGetLoadVoltLowUPS();
	}
	else
	{
		ubOpVolt = cAcVoltReal90V;
	}

	if(T_FAULT_DATA.bits.bOutUV == true)
	{
		//if(sb16UOverLevelChk(wROpVoltNew, ubOpVolt + cAcVoltReal10V, ubFilter, &s_uwROpVoltLowCnt))
		if(sb16UOverLevelChk(wROpVoltNew, 0, ubFilter, &s_uwROpVoltLowCnt)) //故障后没打逆变驱动前电压很低，如果恢复值设置太高没法恢复
		{
			s_uwROpVoltLowCnt = 0;
			T_FAULT_DATA.bits.bOutUV = false;
		}
	}
	else
	{
		if((swGetWorkMode() == cBatteryMode || swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode || swGetWorkMode() == cChgMode)\
		&& (suwGetFBInvCtrlSts() == cFBInvCtrlVolt))
		{
			if(sb16UUnderLevelChk(wROpVoltNew, ubOpVolt, ubFilter, &s_uwROpVoltLowCnt))
			{
				ubOpVoltLow = true;
			}
			if(ubOpVoltLow)
			{
				s_uwROpVoltLowCnt = 0;
				T_FAULT_DATA.bits.bOutUV = true;
				sSetFaultCode(cOutputVoltLow);
			}
		}
	}

}

void	sOPCurrOverChk()
{
	static INT16U s_uwOPOverLoadChkCnt = 0;
	static INT16U s_uwOPOverLoadChkCnt1 = 0;
	static INT16U s_uwOPOverLoadChkCnt2 = 0;
	static INT16U s_uwOPOverLoadChkCnt3 = 0;

	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}
	if(T_FAULT_DATA.bits.bOPCurrOver == true)
	{
		if(sb16UUnderLevelChk(wROpCurrNew, g_uwOPCurrOverLevel1 - 50, cT20ms, &s_uwOPOverLoadChkCnt))
		{
			s_uwOPOverLoadChkCnt = 0;
			T_FAULT_DATA.bits.bOPCurrOver = false;
		}
	}
	else
	{
		if((sb16UOverLevelChk(wROpCurrNew, g_uwOPCurrOverLevel1, cT20sec, &s_uwOPOverLoadChkCnt1))\
		|| (sb16UOverLevelChk(wROpCurrNew, g_uwOPCurrOverLevel2, cT1sec, &s_uwOPOverLoadChkCnt2))\
		|| (sb16UOverLevelChk(wROpCurrNew, g_uwOPCurrOverLevel3, cT30ms, &s_uwOPOverLoadChkCnt3)))
		{
			s_uwOPOverLoadChkCnt = 0;
			T_FAULT_DATA.bits.bOPCurrOver = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cOPCurrOver);
			}
		}
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetROpVoltNew(void)
{
	return wROpVoltNew;
}

INT16S	swGetROpCurrNew(void)
{
	return wROpCurrNew;
}

INT16S	swGetROpFreqNew(void)
{
	return wROpFreqNew;
}

INT16S	swGetROpWattNew(void)
{
	return wROpWattNew;
}

INT16S	swGetROpNLineNVoltNew(void)
{
	return wROpNLineNVoltNew;
}

INT16S	swGetNEVoltNew(void)
{
	return wNEVoltNew;
}

INT16S	swGetROpVarNew(void)
{
	return wROpVarNew;
}

INT16S	swGetROpVANew(void)
{
	return wROpVANew;
}

INT16S	swGetROpPFNew(void)
{
	return wROpPFNew;
}

INT16S	swGetROpVoltFilter(void)
{
	return wROpVoltFilter;
}

INT16S	swGetROpCurrFilter(void)
{
	return wROpCurrFilter;
}

INT16S	swGetROpWattFilter(void)
{
	return wROpWattFilter;
}

INT16S	swGetROpNLineNVoltFilter(void)
{
	return wROpNLineNVoltFilter;
}

INT16S	swGetNEVoltFilter(void)
{
	return wNEVoltFilter;
}

INT16S	swGetROpVarFilter(void)
{
	return wROpVarFilter;
}

INT16S	swGetROpVAFilter(void)
{
	return wROpVAFilter;
}

INT16S	swGetROpVAFilterConversion(void)
{
	return wROpVAFilterConversion;
}

INT16S	swGetROpPFFilter(void)
{
	return wROpPFFilter;
}

INT16S	swGetROpFreqFilter(void)
{
	return wROpFreqFilter;
}

INT8U	sbGetOverLoadBypass(void)
{
	return fOutputStatus.bits.bOverLoadBypass;
}

INT8U	sbGetOverLoadAlarm(void)
{
	return fOutputStatus.bits.bOverLoadAlarm;
}

INT16S	swGetOPWattPercent(void)	// 有功
{
	return g_wOPWattPercent;
}

INT16S	swGetOPPercent(void)	// 最大
{
	return g_wOPPercent;
}

INT16S	swGetwOverLoadBatToLineEnDisable(void)
{
	return wOverLoadBatToLineEnDisable;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetROpVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;

	wROpVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpVoltNew + (INT32S)wROpVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wROpVoltFilter = dwTemp >> 5;
}

void	sSetROpCurrNew(INT16S wCurr)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wROpCurrNew = wCurr;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpCurrNew + (INT32S)wROpCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wROpCurrFilter = dwTemp >> 5;
}

void	sSetROpFreqNew(INT16U wInvFreq, INT16U wLineFreq)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	if(swGetWorkMode() == cBatteryMode)
	{
		wROpFreqNew = wInvFreq;
	}
	else if(swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode || swGetWorkMode() == cChgMode || swGetWorkMode() == cToChgMode)
	{
		wROpFreqNew = wLineFreq;
	}
	else
	{
		wROpFreqNew = 0;
	}
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpFreqNew + (INT32S)wROpFreqFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wROpFreqFilter = dwTemp >> 5;
}

void	sSetROpWattNew(INT16S wWatt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	if(wWatt < 0)
	{
		wWatt = 0;
	}
	wROpWattNew = wWatt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wROpWattNew + (INT32S)wROpWattFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wROpWattFilter = dwTemp >> 5;
}


