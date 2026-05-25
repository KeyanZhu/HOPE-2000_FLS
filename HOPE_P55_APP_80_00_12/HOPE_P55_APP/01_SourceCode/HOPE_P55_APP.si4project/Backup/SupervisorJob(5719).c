/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__SUPERVISOR_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      (cTimer20ms >> 1)
#define         cT100ms                         (100 / cTimerBase)
#define         cT200ms                         (200 / cTimerBase)
#define         cT300ms                         (300 / cTimerBase)
#define         cT1sec                          (1000 / cTimerBase)
#define         cT2sec                          (2000 / cTimerBase)
#define         cT3sec                          (3000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)
#define         cT7sec                          (7000 / cTimerBase)

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16U	uwGridLossCount;

extern INT16U g_uwBatVoltOverCnt;			// 电池软件过压故障
extern INT16U g_uwDCDCCurrOverCnt;			// DCDC软件过流故障
extern INT16U g_uwLLCLPTempOverCnt;			// LLC低压侧过温故障
extern INT16U g_uwLLCTraTempOverCnt;		// LLC变压器过温故障
extern INT16U g_uwBusVoltOverCnt;			// 母线软件过压故障
extern INT16U g_uwBusVoltUnderCnt;			// 母线欠压故障
extern INT16U g_uwBusSoftTimeOutCnt;		// 母线软启故障
extern INT16U g_uwInvSoftTimeOutCnt;		// 逆变软起故障
extern INT16U g_uwInvVoltHighCnt;			// 逆变电压故障
extern INT16U g_uwInvCurrOverCnt;			// 逆变软件过流故障
extern INT16U g_uwInvHWCurrOverCnt;			// 逆变硬件过流故障
extern INT16U g_uwInvShortCnt;				// 逆变短路故障
extern INT16U g_uwInvCircirtTempOverCnt;	// 逆变散热器过温故障
extern INT16U g_uwInvNtcConnectCnt;			// 逆变散热器NTC未接
extern INT16U g_uwOverLoadCnt;				// 负载过载故障
extern INT16U g_uwOutputVoltLowCnt;			// 输出电压低压故障
extern INT16U g_uwOutputVoltHighCnt;		// 输出电压高压故障
extern INT16U g_uwBatHNtcConnectCnt;		// 电池正 NTC未接/过温		
extern INT16U g_uwBatLNtcConnectCnt;		// 电池负 NTC未接/过温 	
extern INT16U g_uwGridCurrOverCnt;			// 市电过流
extern INT16U g_uwOPCurrOverCnt;			// 输出电流过流


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/


/********************************************************************************
* Output variables																*
********************************************************************************/
INT16U g_uwWorkMode;
INT16U g_uwFaultCode = 0;
INT16U g_wAgingMode = 0;			// 老化状态

/********************************************************************************
* Internal variables															*
********************************************************************************/
union SUPERVISOR_STATUS_TABLE
{
	struct SUPERVISOR_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U Rsvd1:4;
		
		// BIT4-7
		INT16U Rsvd2:4;
		
		// BIT8-11
		INT16U Rsvd3:4;
		
		// BIT12-15
		INT16U Rsvd4:4;
	} bits;
	INT16U data;
} fSupervisorJob;
INT16U g_uwSuperEvent;

typedef union
{
	INT16U uwEnergyInfo;
	struct
	{
		INT16U uwPVChgEn:1;
		INT16U uwACChgEn:1;
		INT16U uwFeedPowerEn:1;
		INT16U uwGridModePVBatPowerLoadEn:1;
		INT16U uwReseved:12;
	}Bit;
}UEnergyInfo;
UEnergyInfo uniEnergyInfo;

INT16U g_uwLoadOnSts = false;
INT16U g_uwStayStandby = true;	// 默认待机，不允许自动启动主功率

union STATE_STATUS_TABLE
{
	struct STATE_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U bBatOk:1;
		INT16U bPvOk:1;
		INT16U bLineOk:1;
		INT16U bLoadOn:1;
		
		// BIT4-7
		INT16U BypassEn:1;
		INT16U rsvd2:3;
		
		// BIT8-11
		INT16U rsvd3:4;
		
		// BIT12-15
		INT16U rsvd4:4;
	} bits;
	INT16U data;
} ;
union STATE_STATUS_TABLE fStateStatus;

INT16U	uwSuperStkChk = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sShutdownMode(void);
void	sPowerOnMode(void);
void	sStandbyMode(void);
void	sLineMode(void);
void	sBypassMode(void);
void	sBatteryMode(void);
void	sChgMode(void);
void	sFaultMode(void);
void	sToLineMode(void);
void	sToBypassMode(void);
void	sToBatteryMode(void);
void	sToChgMode(void);
INT8U	sbWaitSystemSteady(INT8U bFilter);
INT8U	sbSystemInitialize(void);
INT8U	sbModelIdentify(INT8U bFilter);
INT8U	sbAdcOffsetInitial(INT8U bFilter);
INT16U	sVoltACCal(INT16U wVoltRms, INT16S wVoltDcAvg);
INT16U	sStandbyToLineRelayCheck(INT16U *pRlyStep);
INT16U	sBatteryToLineRelayCheck(INT16U *pRlyStep);
INT16U	sStandbyToBypassRelayCheck(INT16U *pRlyStep);
INT16U	sBypassToLineRelayCheck(INT16U *pRlyStep);
void    sSupervisorJobInit(void);
/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sSupervisorJob(void)
{
	sSupervisorJobInit();
	
	OSMaskEventPend(1 << eSuperTimer);
	OSMaskEventPend(1 << eSuperTimer);
	while(1)
	{
		if(g_uwWorkMode == cFaultMode)
		{
			sFaultMode();
		}
		else if(g_uwWorkMode == cStandbyMode)
		{
			sStandbyMode();
		}
		else if(g_uwWorkMode == cLineMode)
		{
			sLineMode();
		}
		else if(g_uwWorkMode == cBatteryMode)
		{
			sBatteryMode();
		}
		else if(g_uwWorkMode == cBypassMode)
		{
			sBypassMode();
		}
		else if(g_uwWorkMode == cChgMode)
		{
			sChgMode();
		}
		else if(g_uwWorkMode == cToLineMode)
		{
			sToLineMode();
		}
		else if(g_uwWorkMode == cToBatteryMode)
		{
			sToBatteryMode();
		}
		else if(g_uwWorkMode == cToBypassMode)
		{
			sToBypassMode();
		}
		else if(g_uwWorkMode == cToChgMode)
		{
			sToChgMode();
		}
		else if(g_uwWorkMode == cPowerOnMode)
		{
			sPowerOnMode();
		}
//		else if(g_uwWorkMode == cShutdownMode)	// 关机模式
//		{
//			sShutdownMode();
//		}
		else
		{
			g_uwWorkMode = cStandbyMode;
		}
	}
}

void	sSupervisorJobInit(void)
{
	fSupervisorJob.data = 0;
	g_uwWorkMode = cPowerOnMode;
}


void	sShutdownMode(void)
{
	INT16U wEvent;
	INT16U i;
	
	// Initial	
	hoROPRLYOff;				// 断OP继电器
	hoGRIDRLYOff;				// 断市电继电器
//	hoPVRLYOff;					// 断PV充电继电器
	sSetDCDCCtrlSts(cDCDCWait);	// DCDC待机
	sSetFBInvCtrlSts(cFBWait);	// 逆变待机
	sSetPV1CtrlSts(cPVWait);	// PV待机
	g_uwLoadOnSts = 0;			// 负载模式待机
	
	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperTimer))
		{
			
		}

		for(i = 0; i < cT200ms; i++)
		{
			OSMaskEventPend(1 << eSuperTimer);
		}
		
//		mSPSSDOff;
	}
}


void	sPowerOnMode(void)
{
	INT8U bNextMode;
	
	// Initial
	sSetDCDCCtrlSts(cDCDCWait);
	sSetFBInvCtrlSts(cFBWait);
	sSetPV1CtrlSts(cPVWait);
	
	// 继电器上电状态
	hoROPRLYOff;
	hoGRIDRLYOff;
	sSetOPRelayOn(false);
	sSetGridRelayOn(false);

	// 关机信号/SYS辅源
	mKEYSPSOn;

	sSetBATSPSRlyOn(true);	// 这个信号没有用
	
	while(1)
	{
		bNextMode = sbWaitSystemSteady(cT100ms);
		/*
		if(bNextMode == cShutdownMode)
		{
			g_uwWorkMode = cShutdownMode;
			return;
		}
		else if(bNextMode == cUpgradeMode)
		{
			g_uwWorkMode = cUpgradeMode;
			return;
		}*/
		
		
		bNextMode = sbSystemInitialize();
		/*
		if(bNextMode == cShutdownMode)
		{
			g_uwWorkMode = cShutdownMode;
			return;
		}
		else if(bNextMode == cUpgradeMode)
		{
			g_uwWorkMode = cUpgradeMode;
			return;
		}
		*/
		
		bNextMode = sbModelIdentify(cT300ms);	// 机型识别
//		if(bNextMode == cShutdownMode)
//		{
//			g_uwWorkMode = cShutdownMode;
//			return;
//		}
//		else if(bNextMode == cUpgradeMode)
//		{
//			g_uwWorkMode = cUpgradeMode;
//			return;
//		}
		
		bNextMode = sbAdcOffsetInitial(cT200ms);
		/*
		if(bNextMode == cShutdownMode)
		{
			g_uwWorkMode = cShutdownMode;
			return;
		}
		else if(bNextMode == cUpgradeMode)
		{
			g_uwWorkMode = cUpgradeMode;
			return;
		}
		else */
		if(g_uwFaultCode != 0)
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		else if(bNextMode == cFaultMode)
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		g_uwWorkMode = cStandbyMode;
		return;
	}
}

INT16U g_uwReturnFromFault = false;	// for test

void	sFaultMode(void)
{
	INT16U wEvent;
	
	INT16U uwFaultCodeTemp = 0;
	INT16U uwFaultChgCnt = 0;
	INT16U uwFaultRestartFlg = 0;
	INT16U uwFaultRestartCnt = 0;
	
	hoROPRLYOff;				// 断OP继电器
	hoGRIDRLYOff;				// 断市电继电器
//	hoPVRLYOff; 				// 断PV充电继电器
	sSetGridRelayOn(false);
	sSetOPRelayOn(false);
	
	sSetDCDCCtrlSts(cDCDCWait); // DCDC待机
	sSetFBInvCtrlSts(cFBWait);	// 逆变待机
//	sSetPV1CtrlSts(cPVWait);	// PV待机
	g_uwLoadOnSts = 0;			// 负载模式待机
	mDisDCDCForcePWMOut();		// DCDC低压侧封波
	mDisDCDCHForcePWMOut();		// DCDC高压侧封波
//	mDisPV1PWMOut();			// PV封波
	mDisINVPWMOut();			// 逆变封波

	uwFaultCodeTemp = g_uwFaultCode;		// 获取故障码
	if(uwFaultCodeTemp == cBatVoltOver)		// 电池软件过压故障
	{
		g_uwBatVoltOverCnt++;
	}
	if(uwFaultCodeTemp == cDCDCCurrOver)	// DCDC软件过流故障
	{
		g_uwDCDCCurrOverCnt++;
	}
	if(uwFaultCodeTemp == cLLCLPTempOver)	// LLC低压侧过温故障
	{
		g_uwLLCLPTempOverCnt++;
	}
	if(uwFaultCodeTemp == cLLCTraTempOver)	// LLC变压器过温故障
	{
		g_uwLLCTraTempOverCnt++;
	}
	if(uwFaultCodeTemp == cBusVoltOver)		// 母线软件过压故障
	{
		g_uwBusVoltOverCnt++;
	}
	if(uwFaultCodeTemp == cBusVoltUnder)	// 母线欠压故障
	{
		g_uwBusVoltUnderCnt++;
	}
	if(uwFaultCodeTemp == cBusSoftTimeOut)	// 母线软启故障
	{
		g_uwBusSoftTimeOutCnt++;
	}
	if(uwFaultCodeTemp == cInvSoftTimeOut)	// 逆变软起故障
	{
		g_uwInvSoftTimeOutCnt++;
	}
	if(uwFaultCodeTemp == cInvVoltHigh)		// 逆变电压故障
	{
		g_uwInvVoltHighCnt++;
	}
	if(uwFaultCodeTemp == cInvCurrOver)		// 逆变软件过流故障
	{
		g_uwInvCurrOverCnt++;
	}
	if(uwFaultCodeTemp == cInvHWCurrOver)		// 逆变硬件过流故障
	{
		g_uwInvHWCurrOverCnt++;
	}
	if(uwFaultCodeTemp == cInvShort)			// 逆变短路故障
	{
		g_uwInvShortCnt++;
	}
	if(uwFaultCodeTemp == cInvCircirtTempOver)	// 逆变散热器过温故障
	{
		g_uwInvCircirtTempOverCnt++;
	}
	if(uwFaultCodeTemp == cInvNtcConnect)		// 逆变散热器NTC未接
	{
		g_uwInvNtcConnectCnt++;
	}
	if(uwFaultCodeTemp == cOverLoad)			// 输出过载
	{
		g_uwOverLoadCnt++;
	}
	if(uwFaultCodeTemp == cOutputVoltLow)		// 输出电压低压故障
	{
		g_uwOutputVoltLowCnt++;
	}
	if(uwFaultCodeTemp == cOutputVoltHigh)		// 输出电压高压故障
	{
		g_uwOutputVoltHighCnt++;
	}
	if(uwFaultCodeTemp == cBatHNtcConnect)		// 电池正 NTC未接/过温		
	{
		g_uwBatHNtcConnectCnt++;
	}
	if(uwFaultCodeTemp == cBatLNtcConnect)		// 电池负 NTC未接/过温		
	{
		g_uwBatLNtcConnectCnt++;
	}
	if(uwFaultCodeTemp == cGridCurrOver)		// 市电过流		
	{
		g_uwGridCurrOverCnt++;
	}
	if(uwFaultCodeTemp == cOPCurrOver)			// 输出电流过流		
	{
		g_uwOPCurrOverCnt++;
	}

	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperTimer))
		{
			// --------------------------------故障码遍历
			if(uwFaultCodeTemp == 0)
			{
				uwFaultCodeTemp = g_uwFaultCode;
			}
			else if(uwFaultCodeTemp != g_uwFaultCode)
			{
				if(uwFaultChgCnt < 500)
				{
					uwFaultChgCnt++;
				}
				else
				{
					uwFaultChgCnt = 0;
					g_uwFaultCode = uwFaultCodeTemp;
				}
			}
			else
			{
				uwFaultChgCnt = 0;
			}

			// --------------------------------故障检测清除
			// 14 电池软件过压
			if(uwFaultCodeTemp == cBatVoltOver)	
			{
				if(T_FAULT_DATA.bits.bBatSoftOV == false && g_uwBatVoltOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 21 DCDC软件过流故障
			else if(uwFaultCodeTemp == cDCDCCurrOver)	
			{
				if(T_FAULT_DATA.bits.bDcDcSoftOC == false && g_uwDCDCCurrOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 27 LLC低压侧过温故障
			else if(uwFaultCodeTemp == cLLCLPTempOver)	
			{
				if(T_FAULT_DATA.bits.bLlcLowSideOT == false && g_uwLLCLPTempOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 28 LLC变压器过温故障
			else if(uwFaultCodeTemp == cLLCTraTempOver)	
			{
				if(T_FAULT_DATA.bits.bLlcTXOT == false && g_uwLLCTraTempOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 29 母线软件过压故障
			else if(uwFaultCodeTemp == cBusVoltOver)	
			{
				if(T_FAULT_DATA.bits.bBusSoftOV == false && g_uwBusVoltOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 31 母线欠压故障
			else if(uwFaultCodeTemp == cBusVoltUnder)	
			{
				if(T_FAULT_DATA.bits.bBusUV == false && g_uwBusVoltUnderCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 32 母线软启故障
			else if(uwFaultCodeTemp == cBusSoftTimeOut)	
			{
				//if(T_FAULT_DATA.bits.bBusSoftFault == false && g_uwBusSoftTimeOutCnt < 3)	
				if(g_uwBusSoftTimeOutCnt < 3)							// 自动恢复
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 34 逆变软起故障
			else if(uwFaultCodeTemp == cInvSoftTimeOut)	
			{
				//if(T_FAULT_DATA.bits.bInvSoftFault == false && g_uwInvSoftTimeOutCnt < 3)	
				if(g_uwInvSoftTimeOutCnt < 3)							// 自动恢复
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 35 逆变电压故障
			else if(uwFaultCodeTemp == cInvVoltHigh)	
			{
				if(T_FAULT_DATA.bits.bInvVoltFault == false && g_uwInvVoltHighCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 36 逆变软件过流故障
			else if(uwFaultCodeTemp == cInvCurrOver)	
			{
				if(T_FAULT_DATA.bits.bInvSoftOC == false && g_uwInvCurrOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 37 逆变硬件过流故障
			else if(uwFaultCodeTemp == cInvHWCurrOver)	
			{
				if(T_FAULT_DATA.bits.bInvHardOC == false && g_uwInvHWCurrOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 38 逆变短路故障-----不可恢复
			else if(uwFaultCodeTemp == cInvShort)	
			{
				if(T_FAULT_DATA.bits.bInvShort == false && g_uwInvShortCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 41 逆变散热器过温故障
			else if(uwFaultCodeTemp == cInvCircirtTempOver)	
			{
				if(T_FAULT_DATA.bits.bInvHsOT == false && g_uwInvCircirtTempOverCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 46 逆变散热器NTC未接
			else if(uwFaultCodeTemp == cInvNtcConnect)	
			{
				if(T_FAULT_DATA.bits.bInvHsNTCLoss == false && g_uwInvNtcConnectCnt < 3)
				{
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 48 负载过载故障
			else if(uwFaultCodeTemp == cOverLoad)	
			{
				if(suwGetEEOverLoadRestartEn() && g_uwOverLoadCnt < 3)//\
				//T_FAULT_DATA.bits.bLoadOverLoad == false)// 进入故障那里没有写恢复逻辑
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 49 输出电压低压故障
			else if(uwFaultCodeTemp == cOutputVoltLow)	
			{
				if(T_FAULT_DATA.bits.bOutUV == false && g_uwOutputVoltLowCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 50 输出电压高压故障
			else if(uwFaultCodeTemp == cOutputVoltHigh)	
			{
				if(T_FAULT_DATA.bits.bOutOV == false && g_uwOutputVoltHighCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 56 EEPROM故障-----不可恢复
			else if(uwFaultCodeTemp == cEEPROMFault)	
			{
				if(T_FAULT_DATA.bits.bEepromFault == false)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 79 逆变电流传感器故障-----不可恢复
			else if(uwFaultCodeTemp == cINVCTSenserFault)	
			{
				if(T_FAULT_DATA.bits.bINVCTFault == false)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 80 输出电流传感器故障-----不可恢复
			else if(uwFaultCodeTemp == cOPCTSenserFault)	
			{
				if(T_FAULT_DATA.bits.bOPCTFault == false)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 85 缺失BootLoader故障-----不可恢复
			else if(uwFaultCodeTemp == cBootloadFail)	
			{
				if(T_FAULT_DATA.bits.bBootloadFail == false)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 89 电池正 NTC未接/过温
			else if(uwFaultCodeTemp == cBatHNtcConnect)	
			{
				if(T_FAULT_DATA.bits.bBatHOT == false && g_uwBatHNtcConnectCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 90 电池负 NTC未接/过温
			else if(uwFaultCodeTemp == cBatLNtcConnect)	
			{
				if(T_FAULT_DATA.bits.bBatLOT == false && g_uwBatLNtcConnectCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 91 市电过流
			else if(uwFaultCodeTemp == cGridCurrOver)	
			{
				if(T_FAULT_DATA.bits.bGridCurrOver == false && g_uwGridCurrOverCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 92 输出电流过流
			else if(uwFaultCodeTemp == cOPCurrOver)	
			{
				if(T_FAULT_DATA.bits.bOPCurrOver == false && g_uwOPCurrOverCnt < 3)
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}
			// 93 机型识别错误
			else if(uwFaultCodeTemp == cModelFault)	
			{
				if(T_FAULT_DATA.bits.bModelFault == false)	//不可恢复
				{												
					uwFaultRestartFlg = true;
				}
				else
				{
					uwFaultRestartFlg = false;
				}
			}

			// --------------------------------检测退出故障模式
			if(uwFaultRestartFlg || g_uwReturnFromFault)
			{
				if(++uwFaultRestartCnt > 500)	// 大概10s
				{
//					if(mChkOPRlyOn() && mChkGridRlyOn()) 
//					{
//						g_uwWorkMode = cBypassMode;
//					}
//					else
//					{
						g_uwWorkMode = cStandbyMode;
//					}
					g_uwFaultCode = 0;
					g_uwReturnFromFault = false;
					return;
				}
			}
			else
			{
				uwFaultRestartCnt = 0;
			}
		}
	}
}


void	sStandbyMode(void)
{
	INT16U wEvent;
	INT16U uwSteadyDelayCnt = 250;
	INT16S wLineSuddenlyLoss = false;	// for test
	static INT16U s_OnInvDelay = 0;

	s_OnInvDelay = 0;

	hoROPRLYOff;				// 断OP继电器
	hoGRIDRLYOff;				// 断市电继电器
	sSetOPRelayOn(false);
	sSetGridRelayOn(false);
	
	sSetDCDCCtrlSts(cDCDCWait);	// DCDC待机
	sSetFBInvCtrlSts(cFBWait);	// 逆变待机
	sSetPV1CtrlSts(cPVWait);	// PV待机
	
	g_uwLoadOnSts = 0;			// 负载模式待机

	sSetRSinAmp(0);
	sSetRNewSinAmp(0);

	hoSTAROn;		// 电池软起/预充，到这里了默认认为电容已经充电完成，关掉预充，下一步打开充放电MOS管
	hoSRDRVOn;		// 电池充放电MOS使能
	mSPSENOn;		// 12V驱动辅源使能
	mPVLOADENOn;	// PV弱光吸收电阻，默认关闭
	mWIFIENOn;		//wifi使能
//	mPV_FANENOn;	//PV防反
	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(g_uwSuperEvent & (1 << eSuperLineLoss))
		{
			
		}

		if(wEvent & (1 << eSuperTimer))
		{	
			if(uwSteadyDelayCnt > 0)
			{
				uwSteadyDelayCnt--;
			}
			else if(!g_uwStayStandby)	// 自动模式
			{
				//if(subGetParaBatOpenSts())
				if(0)
				{
					if(sbGetPalLineLossStatus()==false && wLineSuddenlyLoss == false)
					//if(sbGetPalLineLossStatus() == false)
					{
						if(g_uwLoadOnSts)
						{
							g_uwWorkMode = cToBypassMode;
							return;
						}
					}
				}
				else
				{
//					if(sbGetPalLineLossStatus() == false && wLineSuddenlyLoss == false \
//					&& g_wAgingMode == false)
//					if(sbGetInverterPLStatus() == true && (T_ALARM_DATA.bits.bGridUV == false)\
//						&& (T_ALARM_DATA.bits.bGridOV == false) && (T_ALARM_DATA.bits.bGridUF == false)\
//						&& (T_ALARM_DATA.bits.bGridOF == false))
//					{
//						g_uwWorkMode = cToLineMode;
//						sSetLoadOnSts(cFBInvCtrlBus);	// 直接进入市电模式/市电带载
//						return;
//					}
//					else 
					if(g_uwLoadOnSts == cFBInvCtrlVolt)
					{
						// mSPSENOn;
						g_uwWorkMode = cToBatteryMode;
						return;
					}
					else if(g_uwLoadOnSts == cToChgMode)
					{
						g_uwWorkMode = cToChgMode;
						return;
					}
//					else if(g_uwLoadOnSts == cFBInvCtrlBus)
//					{
//						g_uwWorkMode = cToLineMode;
//						return;
//					}
				}
			}
			else
			{
					// 手动模式，各控制器工作靠通讯指令执行
			}

			// 自动开机检测	7秒
			if(suwGetEEAutoInvEnable() == true\
			&& (g_uwWorkMode != cFaultMode) && (g_uwFaultCode == 0)\
			&& (T_ALARM_DATA.bits.bBatOpenAlarm == false) && (T_ALARM_DATA.bits.bAlarmLowBatCutOff == false))
			{
				if((s_OnInvDelay++) >= cT1sec)	// 1S
				{
					s_OnInvDelay = 0;
					if(swGetWorkMode() != cBatteryMode)
					{
						/******************************************************************* 	
							闭环离网软起，进入电池模式
							正常进入电池模式后，若触发故障进入故障模式
							在故障清除时进入待机模式会自动跳转进入电池模式（此时延时不存在 因为g_uwWorkMode还是等于cFBInvCtrlVolt）
						 	此逻辑暂时先不修改，看后续实际情况 
						*******************************************************************/
						sSetLoadOnSts(cFBInvCtrlVolt);
					}
				}
			}
			else if(sbGetInverterPLStatus() == true && (T_ALARM_DATA.bits.bGridUV == false)\
				&& (T_ALARM_DATA.bits.bGridOV == false) && (T_ALARM_DATA.bits.bGridUF == false)\
				&& (T_ALARM_DATA.bits.bGridOF == false))
			{
				if( (T_ALARM_DATA.bits.bAlarmLowBatCutOff == true))
				{
					if((s_OnInvDelay++) >= cT7sec)	
					{
						s_OnInvDelay = 0;
						/*******************************************************************	
						电池低压时，市电存在则跳转到市电模式充电
						*******************************************************************/
//						sSetLoadOnSts(cFBInvCtrlBus);	// 直接进入市电模式/市电带载
						sSetLoadOnSts(cToChgMode);
					}
				}
			}
			else
			{
				s_OnInvDelay = 0;
			}
			
			#if	OS_STK_CHK_EN>0
			uwSuperStkChk = OSStkChk(cPrioSuper);	// 64word
			#endif
		}
	}
}


void	sLineMode(void)
{
	INT16U wEvent;

	INT16U uwInvCtrlStartDelay = 2;

	sSetGridRelayOn(true);
	
    while(1)
    {
        wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(wEvent & (1 << eSuperToStandby))
		{
			g_uwWorkMode = cStandbyMode;
			return;
		}
		
		if(wEvent & (1 << eSuperOPRlyOff))
		{
			sSetOPRelayOn(false);
		}
		
		if(wEvent & (1 << eSuperOPRlyOn))
		{
			if(!uwGetOPRelayOn())
			{
				sOSTimerStop();
				sRlyDelayProc(RLY_CROSSZERO,cOPRlyDelayTime,eSuperSelectPoint,cPrioSuper);
				sOSTimerStart();
				sSetOPRelayOn(true);
			}
		}
		
		if(wEvent & (1 << eSuperLineLoss))
		{
			wEvent |= (1 << eSuperToBat);
		}
		
		if(wEvent & (1 << eSuperToBat))
		{
			uwGridLossCount = 150;	// 市电Loss
			sSetFBInvCtrlSts(cFBWait);

			if(T_ALARM_DATA.bits.bBatOpenAlarm == false && uwGetOPRelayOn() && (suwGetDCDCCtrlSts() == cDCDCWork))
			{
				sSetGridRelayOn(false);
			
				if(suwGetDCDCCtrlSts() != cDCDCWork)
				{
					sSetDCDCCtrlSts(cDCDCWork);
				}
				
				if(suwGetEEGridInputRange() == cUPS)	// UPS
				{
					sOSTimerStop();
					sRlyDelayProc(RLY_DELAY,cDelay5ms,eSuperSelectPoint,cPrioSuper);
					sOSTimerStart();
				}
				else	// APL
				{
					sOSTimerStop();
					sRlyDelayProc(RLY_DELAY,cDelay10ms,eSuperSelectPoint,cPrioSuper);
					sOSTimerStart();
				}
				sSetFBInvCtrlSts(cFBWait);
				sSetLoadOnSts(2);
				g_uwWorkMode = cBatteryMode;

				return;
			}
			else
			{
				sSetFBInvCtrlSts(cFBWait);
				sSetDCDCCtrlSts(cDCDCWait);
				g_uwWorkMode = cStandbyMode;
				return;
			}
		}
		
        if(wEvent & (1 << eSuperTimer))
        {
			// 电网loss进入电池模式
			if((T_ALARM_DATA.bits.bGridUV == true) || (T_ALARM_DATA.bits.bGridOV == true)\
			|| (T_ALARM_DATA.bits.bGridUF == true) || (T_ALARM_DATA.bits.bGridOF == true)\
			|| (sGetGridChgBusVoltFlag() == true))
			{	
				OSEventSend(cPrioSuper, eSuperToBat);
			}

			// 切并网控制器
			if(uwInvCtrlStartDelay > 0)
			{
				uwInvCtrlStartDelay--;
			}
			else if(suwGetFBInvCtrlSts() != cFBInvCtrlBus)	// 可以考虑优化成在过零点切入并网控制器？
			{
				sSetFBInvCtrlSts(cFBInvCtrlBus);
			}

			if((g_uwLoadOnSts != 1) && (g_uwLoadOnSts != 2) && (g_uwLoadOnSts != 3))
			{
				sSetOPRelayOn(false);
				sSetGridRelayOn(false);
				g_uwWorkMode = cStandbyMode;
				return;
			}

//			#if	OS_STK_CHK_EN>0
//			uwSuperStkChk = OSStkChk(cPrioSuper);	// 64word
//			#endif
		}
    }
}

void	sBatteryMode(void)
{
	INT16U wEvent;
	static INT16U uwLineOKDelay = 0;
//	static INT16U uwOffInvDelay = 0;

	// Initial
	sSetBATSPSRlyOn(true);
	sSetOPRelayOn(true);

	// Initial
	if(suwGetDCDCCtrlSts() != cDCDCWork)
	{
		sSetDCDCCtrlSts(cDCDCWork);
	}
	if(suwGetFBInvCtrlSts() != cFBInvCtrlVolt)
	{
		sSetFBInvCtrlSts(cFBInvCtrlVolt);
	}
	
	while(1)
	{
		wEvent = OSEventPend();

		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(wEvent & (1 << eSuperToStandby))
		{
			g_uwWorkMode = cStandbyMode;
			return;
		}
		
		if(wEvent & (1 << eSuperOPRlyOn))
		{
			if(!uwGetOPRelayOn())
			{
				sOSTimerStop();
				sRlyDelayProc(RLY_CROSSZERO,cOPRlyDelayTime,eSuperSelectPoint,cPrioSuper);
				sOSTimerStart();
				sSetOPRelayOn(true);
			}
		}
		
		if(wEvent & (1 << eSuperOPRlyOff))
		{
			sSetOPRelayOn(false);
			if(g_uwLoadOnSts == 0)
			{
				g_uwWorkMode = cStandbyMode;
				return;
			}
		}
		
		if(wEvent & (1 << eSuperToLine))
		{
			sOSTimerStop();
			sRlyDelayProc(RLY_CROSSZERO,cGRIDRlyDelayTime,eSuperSelectPoint,cPrioSuper);// 检测市电过零点
			sRlyDelayProc(RLY_DELAY,cDelay7ms,eSuperSelectPoint,cPrioSuper);			// 延时7ms延时打开继电器，当继电器吸合时刚好在过零点
			sOSTimerStart();
			sSetFBInvCtrlSts(cFBWait);
			sSetGridRelayOn(true);		// 吸合市电继电器
			g_uwWorkMode = cLineMode;
			return;
		}
		
		if(wEvent & (1 << eSuperLineLoss))
		{
			uwLineOKDelay = 0;
		}
		
		if(wEvent & (1 << eSuperTimer))
		{
			// 检测是否允许切市电模式运行
			if(sbGetInverterPLStatus() == true && (sGetGridChgBusVoltFlag() == false)\
			&& (T_ALARM_DATA.bits.bGridUV == false) && (T_ALARM_DATA.bits.bGridOV == false)\
			&& (T_ALARM_DATA.bits.bGridUF == false) && (T_ALARM_DATA.bits.bGridOF == false))
			{	
				if(uwLineOKDelay < 500)	// 10S
				{
					uwLineOKDelay++;
				}
//				if(uwLineOKDelay < (suwGetEEFeedToLineTime() / cTimerBase))	// 可设置
//				{
//					uwLineOKDelay++;
//				}
				else if(1) 
				{
					uwLineOKDelay = 0;
					OSEventSend(cPrioSuper, eSuperToLine);	// for test
				}
			}
			else	// 离网模式运行
			{
				uwLineOKDelay = 0;
				//hoGRIDRLYOff;						
				sSetGridRelayOn(false);				// 保证市电继电器断开
				
				if(0)								//if(subGetParaBatUnderSts()) //电池开路，切待机
				{
					g_uwWorkMode = cStandbyMode;
					return;
				}
				sSetInvRMSCtrlVolt(uwGetOPRMSRatedVolt());
			}

			if((g_uwLoadOnSts != 1) && (g_uwLoadOnSts != 2) && (g_uwLoadOnSts != 3))
			{
				g_uwWorkMode = cStandbyMode;
				return;
			}

			#if	OS_STK_CHK_EN>0
			uwSuperStkChk = OSStkChk(cPrioSuper);	// 64word
			#endif
		}
	}
}


void	sBypassMode(void)
{
	INT16U wEvent;
	
	// Initial

	while(1)
	{
		wEvent = OSEventPend();

		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(wEvent & (1 << eSuperTimer))
		{
			g_uwWorkMode = cStandbyMode;
			return;
		}
	}
}


void	sChgMode(void)
{
	INT16U  wEvent;
	
	// Initial

	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(wEvent & (1 << eSuperTimer))
		{
			
		}
	}
}


void	sToLineMode(void)
{
    INT16U wEvent;
	INT16U wToLineMode = 0;
	INT16U wLineOkDelayCnt = 0;
	INT16U wBusSoftTimeout = 3000;//750;		// 60S
	INT16U wDelayCnt = 0;
	
    // Initial

    while(1)
    {
        wEvent = OSEventPend();

		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
        if(wEvent & (1 << eSuperTimer))
        {
			if(wToLineMode == 0)			// 并网倒秒
			{
				if(++wLineOkDelayCnt >= 50)	// for test
				{
					wLineOkDelayCnt = 0;
					wToLineMode = 1;
				}
			}
			else if(wToLineMode == 1)		// 软起BUS
			{
				if(suwGetDCDCCtrlSts() == cDCDCWork)// && suwGetDCDCSoftDutyFinish())
				{
					wBusSoftTimeout = 3000;
					wToLineMode = 2;
				}
				else
				{
//					if((T_ALARM_DATA.bits.bAlarmLowBatCutOff == true))
//					{
//						sSetGridChgBatLowCutFlag(true)   //电池低压充电
//					}
//					else
//					{
//						sSetGridChgBatLowCutFlag(false)   //正常推挽软起
//					}
					
					sSetDCDCCtrlSts(cDCDCSoft);
				}
				
				if(--wBusSoftTimeout == 0)
				{
					wBusSoftTimeout = 3000;
					g_uwFaultCode = cBusSoftTimeOut;
					T_FAULT_DATA.bits.bBusSoftFault = true;
					g_uwWorkMode = cFaultMode;
					return;
				}
			}
			else if(wToLineMode == 2)		// ISO检查
			{
				wToLineMode = 3;
			}
			else if(wToLineMode == 3)		// 继电器检查	跳转到ToLine模式前已经锁相完成
			{
				sOSTimerStop();
				sRlyDelayProc(RLY_CROSSZERO,cGRIDRlyDelayTime,eSuperSelectPoint,cPrioSuper);// 检测市电过零点
				sRlyDelayProc(RLY_DELAY,cDelay1ms,eSuperSelectPoint,cPrioSuper);			// 延时1ms延时打开继电器，当继电器吸合时刚好在过零点
				sOSTimerStart();
				sSetGridRelayOn(true);		// 吸合市电继电器
				sSetFBInvCtrlSts(cFBWait);	// 继电器吸合时间5ms左右，所以这里关切逆变待机完全来得及
				if(++wDelayCnt > 10)
				{
					wDelayCnt = 0;
					wToLineMode = 4;
				}
			}
			else
			{
				sOSTimerStop();
				sRlyDelayProc(RLY_CROSSZERO,cBatSwitchLineSCRDelayTime,eSuperSelectPoint,cPrioSuper);
				sRlyDelayProc(RLY_DELAY,cDelay2ms,eSuperSelectPoint,cPrioSuper);
				sOSTimerStart();
				sSetOPRelayOn(true);				// 吸合负载继电器
				g_uwWorkMode = cLineMode;	// 检查完所有之后，没问题跳到电网模式
				return;
			}
        }
    }
}


void	sToBatteryMode(void)
{
	INT16U wEvent;
	INT16U wToBatMode = 0;
	INT16U wBusSoftTimeout = 3000;
	INT16S wInvSoftTimeOutDelay = 500;

	// Initial
	sSetFBInvCtrlSts(cFBWait);
	sSetDCDCCtrlSts(cDCDCWait);

	sSetRSinAmp(0);
	sSetRNewSinAmp(0);

	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
		if(wEvent & (1 << eSuperTimer))
		{
			if(g_uwLoadOnSts == 0 || subGetParaBatOpenSts() || T_ALARM_DATA.bits.bAlarmLowBatCutOff)
			{
				g_uwWorkMode = cStandbyMode;
				return;
			}
			else
			{
				if(wToBatMode == 0)	// 软起BUS
				{
					if(suwGetDCDCCtrlSts() == cDCDCWork)
					{
						wBusSoftTimeout = 3000;
						wToBatMode = 1;
					}
					else
					{
						sSetDCDCCtrlSts(cDCDCSoft);
					}
					
					if(--wBusSoftTimeout == 0)	// 60S
					{
						wBusSoftTimeout = 3000;
						g_uwFaultCode = cBusSoftTimeOut;
						T_FAULT_DATA.bits.bBusSoftFault = true;
						g_uwWorkMode = cFaultMode;
						return;
					}
				}
				else if(wToBatMode == 1)	// 设置逆变初始值和状态
				{
					sSetInvRMSCtrlVolt(0);	// 初始值
					sSetRSinAmp(0);
					sSetRNewSinAmp(0);
					if(suwGetFBInvCtrlSts() != cFBInvCtrlVolt)
					{
						sSetFBInvCtrlSts(cFBInvCtrlVolt);
					}
					wToBatMode = 2;
				}
				else if(wToBatMode == 2)	// 软起逆变
				{
					if(uwGetInvRMSCtrlVolt() < uwGetOPRMSRatedVolt())
					{
						sSetInvRMSCtrlVolt(uwGetInvRMSCtrlVolt() + 100);	// 软起步进1V,20ms调整一次，相当于一秒50V
					}
					else
					{
						sSetInvRMSCtrlVolt(uwGetOPRMSRatedVolt());
						if(swGetRInvVoltNew() > (uwGetOPRMSRatedVolt() - 200))
						{
							wInvSoftTimeOutDelay = 500;

							// 待逆变软起完成后，在逆变过零点切OP继电器
							sOSTimerStop();
							sRlyDelayProc(RLY_CROSSZERO,cBatSwitchLineSCRDelayTime,eSuperSelectPoint,cPrioSuper);
							sRlyDelayProc(RLY_DELAY,cDelay2ms,eSuperSelectPoint,cPrioSuper);
							sOSTimerStart();
							sSetOPRelayOn(true);				// 吸合负载继电器
							g_uwWorkMode = cBatteryMode;
							return;
						}
					}

					if(--wInvSoftTimeOutDelay == 0)	// 500 大约是10S
					{
						wInvSoftTimeOutDelay = 500;
						g_uwFaultCode = cInvSoftTimeOut;
						T_FAULT_DATA.bits.bInvSoftFault = true;
						g_uwWorkMode = cFaultMode;			// 软起失败
						return;
					}
				}
			}

//			#if	OS_STK_CHK_EN>0
//			uwSuperStkChk = OSStkChk(cPrioSuper);	// 64word
//			#endif
		}
	}
}


void	sToBypassMode(void)
{
    INT16U wEvent;
	INT16U wToBypassMode = 0;
	INT16U wLineOkDelayCnt = 0;
	
    // Initial

    while(1)
    {
        wEvent = OSEventPend();

		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
        if(wEvent & (1 << eSuperTimer))
        {
            if(wToBypassMode == 0)			// 并网倒秒
			{
				if(++wLineOkDelayCnt >= 50)	// for test
				{
					wLineOkDelayCnt = 0;
					wToBypassMode = 1;
				}
			}
			else if(wToBypassMode == 1)		// 继电器检查
			{
				wToBypassMode = 2;
			}
			else
			{
				g_uwWorkMode = cBypassMode;
				return;
			}
        }
    }
}

void	sToChgMode(void)
{
    INT16U  wEvent;
	
    // Initial
	
    while(1)
    {
        wEvent = OSEventPend();
		
		if(wEvent & (1 << eSuperFault))
		{
			g_uwWorkMode = cFaultMode;
			return;
		}
		
        if(wEvent & (1 << eSuperTimer))
        {
            
        }
    }
}

INT8U	sbWaitSystemSteady(INT8U bFilter)
{
	TASK_EVENT	wEvent;
	INT8U	bWaitCnt = 0;
	
	while(1)
	{
		wEvent = OSEventPend();
		/*
		if(wEvent & (1 << eSuperToShutdown))
		{
			return cShutdownMode;
		}
		
		if(wEvent & (1 << eSuperToUpgrade))
        {
			return cUpgradeMode;
        }
		*/
		if(wEvent & (1 << eSuperTimer))
		{
			if(++bWaitCnt >= bFilter)
			{
				return cPowerOnMode;
			}
		}
	}
}

INT8U	sbSystemInitialize(void)
{
	TASK_EVENT	wEvent;
	
	while(1)
	{
		wEvent = OSEventPend();
		
//		if(wEvent & (1 << eSuperToShutdown))
//		{
//			return cShutdownMode;
//		}
//		
//		if(wEvent & (1 << eSuperToUpgrade))
//        {
//			return cUpgradeMode;
//        }
		
		if(wEvent & (1 << eSuperTimer))
		{
			if(sbGetInitializeFinished())
			{
				sInitComIsr();			// 初始化通信中断
				return cPowerOnMode;	
			}
		}
	}
}

INT8U	sbModelIdentify(INT8U bFilter)
{
	TASK_EVENT	wEvent;
	
	sbInverterIdentifyInitial();
	
	while(1)
	{
		wEvent = OSEventPend();
		
//		if(wEvent & (1 << eSuperToShutdown))
//		{
//			return cShutdownMode;
//		}
//		
//		if(wEvent & (1 << eSuperToUpgrade))
//        {
//			return cUpgradeMode;
//        }
		
		if(wEvent & (1 << eSuperTimer))
		{
			if(sbInverterIdentify(bFilter))
			{
				return cPowerOnMode;
			}
		}
	}
}


INT8U	sbAdcOffsetInitial(INT8U bFilter)
{
	TASK_EVENT	wEvent;
	
	sAdcOffsetInitial();
	
	while(1)
	{
		wEvent = OSEventPend();
		/*
		if(wEvent & (1 << eSuperToShutdown))
		{
			return cShutdownMode;
		}
		
		if(wEvent & (1 << eSuperToUpgrade))
        {
			return cUpgradeMode;
        }
		*/
		if(wEvent & (1 << eSuperTimer))
		{
			if(sbAdcOffsetCalc(bFilter))
			{
//				if(g_uwFaultCode != 0)	// 开启后,报EEPROM故障 20250509
//				{
//					return cFaultMode;
//				}
				if(g_uwWorkMode == cFaultMode)	// 改识别这个
				{
					return cFaultMode;
				}
				return cPowerOnMode;
			}
		}
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	swGetWorkMode(void)
{
    return g_uwWorkMode;
}

INT16U	swGetFaultCode(void)
{
    return g_uwFaultCode;
}

INT16U	swGetLoadOnSts(void)
{
    return g_uwLoadOnSts;
}

INT16U	swGetStayStandby(void)
{
    return g_uwStayStandby;
}

INT16U	swGetAgingStatus(void)
{
    return g_wAgingMode;
}

INT16U	uwGetSuperStkChk(void)
{
	return uwSuperStkChk;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetFaultCode(INT16U uwFaultCode)
{
	if(g_uwWorkMode != cPowerOnMode && g_uwWorkMode != cFaultMode)
	{
		g_uwFaultCode = uwFaultCode;
		OSEventSend(cPrioSuper, eSuperFault);
	}
}

void	sSetWorkMode(INT16U uwWorkMode)
{
	g_uwWorkMode = uwWorkMode;
}

void	sSetLoadOnSts(INT16U uwTemp)
{
    g_uwLoadOnSts = uwTemp;
}

void	sSetStayStandby(INT16U uwTemp)
{
    g_uwStayStandby = uwTemp;
}

void	sSetAgingStatus(INT16U uwTemp)
{
    g_wAgingMode = uwTemp;
}


