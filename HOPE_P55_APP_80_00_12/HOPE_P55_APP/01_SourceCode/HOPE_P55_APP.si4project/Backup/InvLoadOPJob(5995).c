    /********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__INVLOADOP_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"


/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      cTimer10ms
#define         cT50ms                         (50 / cTimerBase)
#define         cT100ms                         (100 / cTimerBase)
#define         cT250ms                         (250 / cTimerBase)
#define         cT500ms                         (500 / cTimerBase)
#define         cT1sec                          (1000 / cTimerBase)
#define         cT1sec5                          (1500 / cTimerBase)
#define         cT2sec                          (2000 / cTimerBase)
#define         cT3sec                          (3000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)
#define         cT10sec                         (10000 / cTimerBase)
#define         cT15sec                         (15000 / cTimerBase)
#define         cT25sec                         (25000 / cTimerBase)
#define         cT30sec                         (30000 / cTimerBase)
#define         cT50sec                         (50000 / cTimerBase)
#define         cT1min                          (60000 / cTimerBase)
#define         cT2min                          (120000 / cTimerBase)
#define         cT5min                          (300000 / cTimerBase)
#define         cT10min                         (600000 / cTimerBase)
#define         cT20min                         (1200000 / cTimerBase)	// 16U
#define         cT30min                         (1800000 / cTimerBase)	// 32
#define         cT60min                         (3200000 / cTimerBase)	// 32




/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16U gi_uwInvCurrHWHiIntCnt;


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/


/********************************************************************************
* Output variables																*
********************************************************************************/
INT16U g_uwInvRMSCtrlVolt;	// 逆变软起控制电压
INT16U g_wOPRMSRatedVolt;	// 输出额定电压(用户设置的)
INT16S wOutputVoltCntl;		// 写入控制器参考计算的额定输出电压(经过了降额后的最终结果)
INT16U g_wInvDCVoltCntlEn;	// 逆变直流分量补偿使能
INT16S g_wInvDCVoltRef;		// 逆变直流分量补偿参考

INT16U	uwWattDeratePerTemp;
INT16S	wWattDeratROpVolt = 2300;		// 功率降额负载电压

INT16U  g_wKeyOffflag = 0;

extern INT16S g_wOPSinVpp;	// for test

/********************************************************************************
* Internal variables															*
********************************************************************************/
union INVLOADOP_STATUS_TABLE
{
	struct INVLOADOP_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U bRsvd1:4;
		
		// BIT4-7
		INT16U bRsvd2:4;
		
		// BIT8-11
		INT16U bRsvd3:4;
		
		// BIT12-15
		INT16U bRsvd4:4;
	} bits;
	INT16U data;
} fInvLoadOPJob;

union CHGDSG_STATUS_TABLE
{
	struct CHGDSG_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U	bPvChgEn:1;			// PV充电使能
		INT16U	bLineChgEn:1;		// 市电充电使能
		INT16U	rsvd1:2;
		
		// BIT4-7
		INT16U	rsvd2:4;
		
		// BIT8-11
		INT16U	bPvDsgEn:1;			// PV放电使能
		INT16U	bLineDsgEn:1;		// 市电放电使能
		INT16U	rsvd3:2;
		
		// BIT12-15
		INT16U	rsvd4:4;
	} bits;
	INT16U data;
} fSysChgDsgStatus;


INT16U	uwInvLoadStkChk = 0;

INT16U g_uwTurboMode = true;	// Turbo模式使能标识
INT16S g_wInvWattCT = -100;		// CT反接检测功率阈值,单位:W

// 并网充放电方向和功率计算，逆变器模式识别
INT16U	uwInvFeedWorkMode = 0;				// 逆变器能量调度方向(0按照用户设置自动识别 1充电 2放电)
INT16U	uwInvWorkPriority = 0;				// 逆变器运行模式/能量调度优先级
INT16U	uwInvWorSUBGridDir = 0;				// SUB模式下，市电能量方向(0:充电 1:放电)

INT16S 	wGridChgPowerLimitTemp = 0;			// 根据市电设置充电电流得到逆变最大允许充电功率
INT16S 	wPvChgPowerTemp = 0;				// 根据PV实际充电电流得到逆变最大允许充电功率
INT16S 	wRlyChgPowerLimitTemp = 0;			// 继电器最大允许功率(只会在逆变充电时出现)
INT16S 	wBatChgPowerLimitTemp = 0;			// 电池总允许的充电功率/用户设置/通讯读电池包
INT16S 	wBatDsgPowerLimitTemp = 0;			// 电池总允许的放电功率/通讯读电池包/额定值
INT16S 	wMaxFeedPowerLimit = 0;				// 最大并网功率限制(有些模式只允许并最大PV功率)

INT16S 	wGridFeedWattRef = 0;				// 市电并网放电功率/老化用/手动给定
INT16S 	wGridChgBatCurrRef = 0;				// 市电充电电池充电电流/老化用/手动给定
INT16S 	wGridWattRef = 0;					// 自动计算的并网功率给定
INT16S 	wBatWattRef = 0;					// 自动计算的电池功率
F32		fLoadWattErrKI = 0;					// 并网功率的误差补偿积分结果
INT16S	wInvFrrdWattErr = 0;				// 逆变馈电并网功率
INT16S	wPVCurrErr = 0;						// PV多余能量
INT16S	g_wRLineWattNewTemp = 0;			// 临时计算的市电功率

INT16U	uwGridpowerslopeTime = 100;//140;//240;//60;	// 电网功率软起斜率
INT16S 	wInvChgPowerLimitTemp = 0;			// 市电充电软起至额定功率值
INT16S 	wInvDsgPowerLimitTemp = 0;			// 市电放电软起至额定功率值

INT16S 	gi_wInvChgCurrLimitTemp = 0;		// 充电电流软起临时值
INT16S 	gi_wInvFeedCurrLimitTempTemp = 0;	// 放电电流软起临时值
INT16S 	gi_wInvChgCurrSoftStartRate = 1;	// 充电电流软起速率
INT16U	g_uwGridBusVoltRef = 0;				// 并网BUS参考 0.1V
INT16S 	wInvCtrlPower = 0;					// 控制的功率，正充电,负放电
INT16S 	wInvCurrTemp = 0;					// 计算的实际需要并网的电流值(控制器前)
INT16S 	wInvCurrFeedTemp = 0;				// 计算的实际设置并网的卖电流值(控制器前)

extern  INT16S gi_wInvFeedCurrLimit;		// 并网最大卖电电流 电池向市电馈电
extern  INT16S gi_wInvChgCurrLimit;			// 并网最大买电电流 市电给电池充电
extern  INT16S gi_wBatChgInvLimit;			// 并网充放电电流限制值,动态调整,负数卖电,正数买电
extern  INT16S gi_wInvFeedCurrLimitTemp;	// 并网最大卖电电流 电池向市电馈电

INT16U	g_uwACCurrLimitEn = false;			// AC限流 		使能
INT16S	g_wACCurrLimit = 2500;				// AC限流 		电流
INT16S	g_wACPowerLimit = 6400;				// AC限流 		功率
INT16S	g_wACWattLimit = 0;					// AC实际限流 		功率
INT16S	g_wACFeedPowerLimit = 0;			// 馈电功率

extern INT16S g_wBatChgCurrLimit;			// 系统最大充电电流 0.01A
extern INT16S g_wBatDsgCurrLimit;			// 系统最大放电电流 0.01A
extern INT16S g_wBatSOCReal;				// 电池SOC
extern INT16S g_wRInvDCVoltCntl;

INT16U g_uwOPLoadLevelCnt = 0;
INT16U g_uwOpLoadRstDelayCnt = 0;

INT16U fChgMode = cChgModeNO;
/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sInvLoadOPJobInit(void);
void	sFBInvVoltCtrlAdj(void);
void	sTurboWattCtrlProc(void);
void	sGridPowerPriorityProc(void);			// 充放电功率分配
void	sPvChgModeProc(void);
void	sPvLowVoltChk(void);					//名字不合适，后续改
void	sChgModeChk(void);
INT16U	uwBatChgVoltChk(void);					// 待定生效，暂时不生效(一体机不用)

void	sInvCurrCTRebConChk(INT8U ubFilter);
void	sInvPowerOffChk(void);
void	sControllerRefUpdate(void);
void 	sPowerSavingModeChk(INT16S uwWatt,INT16U uwFilter1,INT16U uwFilter2);
void 	sInvHardOCChk(void);
void 	sOPOverLoadLowvolt(void);
/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sInvLoadOPJob(void)
{
	INT16U	wEvent;
	
	sInvLoadOPJobInit();

	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eInvLoadOPSinZero))	// base 20ms
		{
			sInvPowerOffChk();												// for test 关机检测,后续考虑采用Super状态机里面的关机事件
		
			sSetRInvVoltNew(swRInvVoltCal());								// INV.V
			sSetRInvCurrNew(swRInvCurrCal());								// INV.I
			sSetRInvWattNew(swRInvWattCal());								// INV.W
			sSetRInvDcVoltNew(swRInvDCVCal());								// INV.DCV
			sSetRInvFreqNew(swGetSinePeriodCntNew());						// INV.HZ
			sSetROpVoltNew(swROpVoltCal());									// OP.V
			sSetROpCurrNew(swROpCurrCal());									// OP.I
			sSetROpWattNew(swROpWattCal());									// OP.W
			sSetROpFreqNew(swGetRInvFreqFilter(), swGetRLineFreqFilter());	// OP.HZ

			sRInvPowerCal();												// 逆变功率参数计算
			sROpPowerCal();													// OP功率参数计算
			sOPPercentCal();												// 负载百分比计算

			sFrePhaseLockProc();											// 硬件锁相(已经改成了软件锁相)

			sTurboWattCtrlProc();											// Turbo模式控制
			sGridPowerPriorityProc();										// 市电充放电功率分配
			sControllerRefUpdate(); 										// BUS电压自动调整			// 没用
			sFBInvVoltCtrlAdj();											// 逆变输出电压调整
			
			sInvVoltHighChk(10);											// 逆变过压检测
			sInvShortChk(5);												// 逆变短路检测
			sInvCurrOverChk(5);												// 逆变过流检测

			sOpVoltHighChk(10);												// OP过压检测
			sOpVoltLowChk(75);												// OP欠压
//			sOPCurrOverChk(700,10);											// OP过流    25A 

		}
		
		if(wEvent & (1 << eInvLoadOPTimer))		// base 10ms
		{
			sPvChgModeProc();												// PV充电检测
			sBuckMpptMethod();												// MPPT追踪算法
			sChgModeChk();													// 充电模式检测 for test
			sBuckMpptDisturb(cT5sec);
//			sPvLowVoltChk();												// PV弱光吸收检测开启

			sDeratingProc();												// 降额参数计算
			
			sFBFanSpeedProc(cT1min,cT1min);									// 风扇控制
			
//			sOverLoadChk();													// 输出过载检测

			if(swGetWorkMode() > cPowerOnMode)
			{
				sPvTempChk(cT3sec,cT5sec);									// PV过温检测
				sInvOverTempChk(cT3sec,cT5sec);								// 逆变过温检测
				sTwTempChk(cT3sec,cT5sec);									// LLC过温检测
//				sBatHTempChk(cT3sec,cT5sec); 								// 电池正NTC过温检测
			}
			
//			#if	OS_STK_CHK_EN>0
//			uwInvLoadStkChk = OSStkChk(cPrioInvLoadOP);		// 99word
//			#endif
		}
	}
}

void	sFBInvVoltCtrlAdj(void)								// 逆变输出电压调整
{
	// 1.获取用户设定额定值
	// 在离网软起时，如果存在输出降额，存在逆变软起失败的风险
	if(g_wOPRMSRatedVolt != suwGetEEACOutputRatedVolt())
	{
		g_wOPRMSRatedVolt = suwGetEEACOutputRatedVolt();	// 逆变器软起目标/用户设定
	}

	// 取最小值去软起
	if(swGetTempDeratVoltNew() > suwGetEEACOutputRatedVolt())
	{
		g_wOPRMSRatedVolt = suwGetEEACOutputRatedVolt();
	}
	else
	{
		g_wOPRMSRatedVolt = swGetTempDeratVoltNew();
	}

	// 2.输出降额等限制
	wOutputVoltCntl = g_uwInvRMSCtrlVolt;					// 离网逆变时，控制器的电压给定，由额定值和降额值计算给出

	if(swGetTempDeratVoltNew() < wOutputVoltCntl)			// 温度降额输出电压结果
	{
		wOutputVoltCntl = swGetTempDeratVoltNew();
//		g_wOPRMSRatedVolt = swGetTempDeratVoltNew();		// 目的是为了在温度高的时候也可以启动逆变/合理？(这个值在降额时会反复)
	}

	// 电池离网限流，并网不用特殊做处理，因为并网的功率是直接计算给出的
	if(wOutputVoltCntl > (sOutputVoltDrtProc(suwGetEEACOutputRatedVolt())))
	{
		wOutputVoltCntl = (sOutputVoltDrtProc(suwGetEEACOutputRatedVolt()));
	}

	if(wOutputVoltCntl > wWattDeratROpVolt)			
	{
		wOutputVoltCntl = wWattDeratROpVolt;
	}

//	if(wOutputVoltCntl > sOPOverLoadLowvolt())			
//	{
//		wOutputVoltCntl = sOPOverLoadLowvolt();
//	}
//	sOPOverLoadLowvolt();

	// 3.电压调整给到控制器目标
	if(suwGetFBInvCtrlSts() == cFBInvCtrlVolt || suwGetFBInvCtrlSts() == cFBInvOpenLoop)
	{
		// 逆变电压调整
		if(swGetStayStandby() == true)						// 设定在待机使能时，机器会运行这里给逆变控制器电压
		{
//			if(suwGetSysDerateEn() == true)					// 降额使能的时候，使用wOutputVoltCntl,这个电压上限受制于降额
//			{
//				sRVoltRegu(wOutputVoltCntl,3,1);
//			}
//			else
			{
				sRVoltRegu(g_uwInvRMSCtrlVolt,3,1);			// 不使能降额时，电压由通讯给入
			}
		}
		else
		{
			sRVoltRegu(wOutputVoltCntl,3,1);				// 在待机使能禁止时，会跑这里给逆变参考
		}

		// 逆变电压直流分量补偿
		if(g_wInvDCVoltCntlEn)
		{
			sRInvDCVoltCntl(g_wInvDCVoltRef,15,1);	// g_wInvDCVoltRef 默认 = 0,未生效
		}
	}
	else
	{
		sSetRSinAmp(g_wOPSinVpp);
		sSetRNewSinAmp(g_wOPSinVpp);
		sClrInvDCVoltCntlPara();
	}
}

void	sPvLowVoltChk(void)	//名字不合适，后续改
{
	if(T_ALARM_DATA.bits.bPv1UVAlarm)	// == true,表示PV丢失或者PV弱，吸收电路打开
	{
		mPVLOADENOn;
	}
	else								// == false,表示PV存在或者PV强，吸收电路关闭
	{
		mPVLOADENOff;
	}
}


INT16U	uwPvChgWorkCnt = 0;		// for test
INT16U	uwPvChgWaitCnt = 0;
INT16U	uwPvChgBatCurrRef = 0;
INT16U	uwPvChgBatCurrTemp = 0;
INT16S	g_wPvLoadCurrFeedWard = 0;
INT16S	g_wPvLoadCurrFeedWard1 = 0;
INT16S	g_wPvLoadCurrFeedWard2 = 0;
INT16S	g_wPvLoadCurrFeedWard3 = 0;
INT16U	uwPvChgCurrTemp = 0;

INT16U	uwPvBatCurrLimit = 0;
INT16U	uwPvWattLimit = 0;
INT16U	swGetPv1VoltFilterTest =  0;
INT16U	uwPvWattLimitTemp = 0;

//INT16U	uwPvCurrLimit = 0;

void	sPvChgModeProc(void)
{
	// PV充电初始电流参考给定
	if(!swGetStayStandby()) // == 0 就是在自动模式(量产模式)
	{
		uwPvChgBatCurrTemp = g_wBatChgCurrLimit * 10;	// 自动获取EEPROM设置/用户设置
	}
	else
	{
		uwPvChgBatCurrTemp = suwGetSciPvBatChgLimit();	// Debug寄存器写入
	}

	// PV实际能允许的额定理论最大功率
	uwPvWattLimit = (INT16U)(((INT32U)swGetPv1VoltFilter() * cMpptPVCurrMax) / 1000);	
	Uplimit(uwPvWattLimit,suwGetEEPV1PowerLimit());
	
	uwPvBatCurrLimit = (INT16U)(((INT32U)uwPvWattLimit * 1000) / swGetBatVoltNew());
	Uplimit(uwPvBatCurrLimit,cMpptBatCurrMax);
	Uplimit(uwPvChgBatCurrTemp,uwPvBatCurrLimit);	// PV允许充电最大值限制
	
	// PV叠加负载电流前馈
	if(suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		//uwPvChgBatCurrTemp += g_wPvLoadCurrFeedWard;	// 前馈要不要使能，加一个调试设置(还没加)
		//Uplimit(uwPvChgBatCurrTemp,cMpptBatCurrMax);	// PV给电池的充电电流给定，不能超过额定电流
	}
	else if(suwGetFBInvCtrlSts() == cFBInvCtrlVolt)
	{
		g_wPvLoadCurrFeedWard3 = (INT16S)((INT32S)swGetROpWattNew() * 1000  / swGetBatVoltNew());	// 0.1A
		UpDownLimit(g_wPvLoadCurrFeedWard3,cMpptBatCurrMax,0);
		uwPvChgBatCurrTemp += g_wPvLoadCurrFeedWard3;	// 前馈要不要使能，加一个调试设置(还没加)
		Uplimit(uwPvChgBatCurrTemp,cMpptBatCurrMax);	// PV给电池的充电电流给定，不能超过额定电流100A
		Uplimit(uwPvChgBatCurrTemp,uwPvBatCurrLimit);	// PV允许充电最大值限制
	}
	else
	{
		g_wPvLoadCurrFeedWard3 = 0;
	}


	// PV降额
//	Uplimit(uwPvChgBatCurrTemp,swGetTempDeratPvBatCurrFilter());	// PV给电池的充电电流给定，不能超过额定电流
//	uwPvWattLimitTemp = uwPvChgBatCurrTemp * swGetBatVoltNew();
//	Uplimit(uwPvWattLimitTemp,suwGetEEPV1PowerLimit());
	// PV负端采样控制参考
	uwPvChgCurrTemp = (((INT32U)uwPvChgBatCurrTemp * swGetBatVoltNew()) / swGetPv1VoltFilter());
//	uwPvChgCurrTemp = ((INT32U)uwPvWattLimitTemp) / swGetPv1VoltFilter();

	Uplimit(uwPvChgCurrTemp,cMpptPVCurrMax);	// PV侧输入限制23A

	// for test
	fSysChgDsgStatus.bits.bPvChgEn = true;
	
	// PV充电检测
	if(!swGetStayStandby())	// 不在待机模式就去自动检测充电
	{
		if(swGetWorkMode() != cPowerOnMode && swGetWorkMode() != cFaultMode \
		&& (fSysChgDsgStatus.bits.bPvChgEn == true))
		{
			// 如果单PV无电池开机自动逆变不使能,同时电池开路，则不开PV控制器
			if((suwGetEEPVAutoInvEnable() == 0) && (T_ALARM_DATA.bits.bBatOpenAlarm))
			{
				if(++uwPvChgWaitCnt >= cT3sec)
				{
					uwPvChgWorkCnt = 0;
					uwPvChgWaitCnt = 0;
					sSetPV1CtrlSts(cPVWait);
				}
			}
			else if((!T_ALARM_DATA.bits.bPv1UVAlarm) && (!T_ALARM_DATA.bits.bPv1OVAlarm)\
			&& (!T_ALARM_DATA.bits.bPv1OCAlarm ) && (!T_ALARM_DATA.bits.bPv1OTAlarm) \
			&& (suwGetPV1CtrlSts() != cPVWork))
			{
				if(++uwPvChgWorkCnt >= cT10sec)
				{
					uwPvChgWorkCnt = 0;
					uwPvChgWaitCnt = 0;
					sSetPV1CtrlSts(cPVWork);
					sMPPTParaInit();
				}
			}
			else if((T_ALARM_DATA.bits.bPv1UVAlarm) || (T_ALARM_DATA.bits.bPv1OVAlarm)\
			|| (T_ALARM_DATA.bits.bPv1OCAlarm) || (T_ALARM_DATA.bits.bPv1OTAlarm) \
			&& (suwGetPV1CtrlSts() != cPVWait))
			{
				if(++uwPvChgWaitCnt >= cT3sec)
				{
					uwPvChgWorkCnt = 0;
					uwPvChgWaitCnt = 0;
					sSetPV1CtrlSts(cPVWait);
				}
			}
		}
		else
		{
			uwPvChgWorkCnt = 0;
			uwPvChgWaitCnt = 0;
			sSetPV1CtrlSts(cPVWait);
		}
	}

	// 给到PV控制器的电池充电电流控制参考
	if(suwGetPV1CtrlSts() == cPVWork)				// 在PV Work的时候才软起电流，否则以最小电流运行
	{
		if(uwPvChgBatCurrRef < uwPvChgCurrTemp)		// PV控制器的目标电流 0.1A
		{
			uwPvChgBatCurrRef += 1;
		}
		else
		{
			uwPvChgBatCurrRef = uwPvChgCurrTemp;
		}
	}
	else
	{
		uwPvChgBatCurrRef = cMpptBatCurr0A;
	}

	// 给到PV控制器的电池电压控制参考
	sSetPvChgBatVoltRef(swGetBatVoltRef());
}

void	sChgModeChk(void)
{
	static INT16U uwChgToCCCnt = 0;
	static INT16U uwChgToCVCnt = 0;
	static INT16U uwChgToFloatCnt = 0;
	static INT32U uwChgToNOCnt = 0;

	if(suwGetPV1CtrlSts() == cPVWork || swGetWorkMode() == cLineMode)
	{
		if((swGetBatVoltFilter() >= suwGetEEBatFloatVolt()) && (swGetBatCurrFilter() < 0) \
			&& (swGetBatCurrFilter() > (-(INT16S)suwGetEEBatMaxChgCurr()/10))\
			&& (fChgMode  == cChgModeCC || fChgMode == cChgModeCV) && (suwGetEEBatType() != cBatType_LIB))
		{
			if(uwChgToFloatCnt++ > cT2min)
			{
				uwChgToFloatCnt = 0;
				fChgMode = cChgModeFloat;
			}
		}
		else
		{
			uwChgToFloatCnt = 0;
		}
		
		if(fChgMode == cChgModeNO)
		{
			fChgMode = cChgModeCC;
		}
		else if(fChgMode == cChgModeCC)
		{
			if(swGetBatVoltFilter() >= suwGetEEBatConstVolt() - cBatVoltReal0V3)
			{
				if(uwChgToCVCnt++ > cT10sec)
				{
					uwChgToCVCnt = 0;
					fChgMode = cChgModeCV;
				}
			}
			else
			{
				uwChgToCVCnt = 0;
			}
		}
		else if(fChgMode == cChgModeCV)
		{
			if(swGetBatVoltFilter() <= (suwGetEEBatConstVolt() - cBatVoltReal2V))
			{
				if(uwChgToCCCnt++ > cT10sec)
				{
					uwChgToCCCnt = 0;
					fChgMode = cChgModeCC;
				}
			}
			else
			{
				uwChgToCCCnt = 0;
			}
		}
		else if(fChgMode == cChgModeFloat)
		{
			if(swGetBatVoltFilter() <= (suwGetEEBatFloatVolt() - cBatVoltReal2V))
			{
				if(uwChgToCCCnt++ > cT10sec)
				{
					uwChgToCCCnt = 0;
					uwChgToNOCnt = 0;
					fChgMode = cChgModeCC;
				}
			}
			else
			{
				uwChgToCCCnt = 0;
			}

			if(swGetBatVoltFilter() <= (suwGetEEBatFloatVolt() - cBatVoltReal0V5))	// 60分钟退出浮充模式
			{
				if(uwChgToNOCnt++ > cT60min)
				{
					uwChgToNOCnt = 0;
					fChgMode = cChgModeNO;
				}
			}
			else
			{
				uwChgToNOCnt = 0;
			}
		}
		else
		{
			;
		}
	}
	else
	{
		uwChgToCCCnt = 0;
		uwChgToCVCnt = 0;
		uwChgToFloatCnt = 0;
		uwChgToNOCnt = 0;
		fChgMode = cChgModeNO;
	}
}

INT16U	uwBatChgVoltChk(void)	// 待定生效，暂时不生效(一体机不用)
{
	INT16U	uwBatChgVolt;
	
	if(fChgMode == cChgModeFloat)
	{
		uwBatChgVolt = suwGetEEBatFloatVolt();
	}
	else
	{
		uwBatChgVolt = suwGetEEBatConstVolt();
	}

	if((suwGetEEBatType() != cBatType_LIB) && (suwGetEEBatType() != cBatType_USER))
	{
		uwBatChgVolt = cBatVoltReal3V65 * uwGetBatSerialPcs();
	}

	return uwBatChgVolt;
}


INT16S wROpFeedWattTemp = 0;
void	sGridPowerPriorityProc(void)			// 充放电功率分配，优先级
{
	INT16S wBatAcChgCurrTemp;
	INT16S wPvChgCurrTemp;
//	INT16S wInvChgCurrMaxTemp;
	INT16S wBatChgCurrTemp;
	INT16S wBatDsgCurrTemp;
	
	static INT16S wInvChgPowerCntTemp = 0;
	static INT16S wInvDsgPowerCntTemp = 0;
	
	uwInvWorkPriority = suwGetEEWorkMode();					// 获取用户设置的逆变器工作模式
	g_uwACCurrLimitEn = suwGetEEGridPeakShavingEnable();	// 用户设置的AC限流使能
	g_wACPowerLimit = suwGetEEGridPeakShavingPower();		// 用户设置的AC限流功率
	g_wACCurrLimit = suwGetEEGridCurrLimit();				// 用户设置的AC限流电流

	// 1. 市电充电功率限制值:根据市电充电电流折算逆变功率
	if(suwGetEEGridChgBatCurr() != 0)
	{
		if((g_wBatChgCurrLimit > 0) && (suwGetPV1CtrlSts() == cPVWork))
		{
			wBatAcChgCurrTemp = g_wBatChgCurrLimit * 10 - swGetPv1BatCurrNew();//0.1A
			if(wBatAcChgCurrTemp < 0)	// 负数时，与正数做对比，因为芯片存储的问题，会用补码的形式存负数
			{							// 程序调用的时候不做处理的话，就会是一个很大的数，限幅时先和正最大值做对比的话就会被限制在正最大值
				wBatAcChgCurrTemp = 0;
			}
			UpDownLimit(wBatAcChgCurrTemp,suwGetEEGridChgBatCurr(),0);
		}
		else
		{
			wBatAcChgCurrTemp = suwGetEEGridChgBatCurr();
			Uplimit(wBatAcChgCurrTemp,g_wBatChgCurrLimit * 10);
		}

		if(wBatAcChgCurrTemp > 0)
		{
			wBatAcChgCurrTemp = (INT16S)(((INT32S)wBatAcChgCurrTemp * 136) >> 7);						// 0.94 efficiency
			wGridChgPowerLimitTemp = (INT16S)((INT32S)wBatAcChgCurrTemp * swGetBatVoltNew() / 1000);	// 电池充电电流折算到逆变充电功率	
			Uplimit(wGridChgPowerLimitTemp,uwGetInvWattMax());
		}
		else
		{
			wGridChgPowerLimitTemp = 0;
		}
	}
	else
	{
		wGridChgPowerLimitTemp = 0;
	}
	

	// 2. PV当前能并网的功率值:根据PV实际充电电流折算逆变功率
	if(suwGetPV1CtrlSts() == cPVWork)	// PV控制器工作时，才计算相关参数
	//if(0)	// PV控制器工作时，才计算相关参数
	{
		wPvChgCurrTemp = swGetPv1BatCurrNew();												// 读实际值 最大60A 0.01A
		wPvChgCurrTemp = (INT16S)(((INT32S)wPvChgCurrTemp * 136) >> 7);							// 0.94 efficiency
		wPvChgPowerTemp = (INT16S)((INT32S)wPvChgCurrTemp * swGetBatVoltNew() / 1000);			// PV充电电流折算到充电功率
		Uplimit(wPvChgPowerTemp,600);															// 额定600W
	}
	else
	{
		wPvChgCurrTemp  = 0;
		wPvChgPowerTemp = 0;
	}

	// 3. 根据继电器电流限制最大充电功率
//	wInvChgCurrMaxTemp = cMaxACInputCurr - swGetROpCurrNew();
//	wRlyChgPowerLimitTemp = ((INT32S)wInvChgCurrMaxTemp * swGetRLineVoltNew()) / 1000;
	wRlyChgPowerLimitTemp = ((INT32S)cMaxACInputCurr * swGetRLineVoltNew()) / 1000;
	UpDownLimit(wRlyChgPowerLimitTemp,2000,-2000);	// 2000W

	// 4. 根据用户设置/通讯读取的电池最大充电电流计算电池充电最大功率
	wBatChgCurrTemp = g_wBatChgCurrLimit;														// 0.01A
	wBatChgCurrTemp = (INT16S)(((INT32S)wBatChgCurrTemp * 136) >> 7);							// 0.94 efficiency
	wBatChgPowerLimitTemp = (INT16S)((INT32S)wBatChgCurrTemp * swGetBatVoltNew() / 100); 		// 电池充电电流折算到逆变充电功率	
	Uplimit(wBatChgPowerLimitTemp,uwGetInvWattMax());

	// 5. 根据用户设置/通讯读取的电池最大放电电流计算电池放电最大功率
	wBatDsgCurrTemp = g_wBatDsgCurrLimit;														// 0.01A
	wBatDsgCurrTemp = (INT16S)(((INT32S)wBatDsgCurrTemp * 136) >> 7);							// 0.94 efficiency
	wBatDsgPowerLimitTemp = (INT16S)((INT32S)wBatDsgCurrTemp * swGetBatVoltNew() / 100); 		// 电池充电电流折算到逆变充电功率	
	Uplimit(wBatDsgPowerLimitTemp,uwGetInvWattMax());

	// 6. AC实际需要限流功率,取设置量最小值
	if(g_wACPowerLimit > ((INT16S)((INT32S)g_wACCurrLimit * swGetRLineVoltNew() / 1000)))
	{
		g_wACWattLimit = ((INT16S)((INT32S)g_wACCurrLimit * swGetRLineVoltNew() / 1000));
	}
	else
	{
		g_wACWattLimit = g_wACPowerLimit;
	}

	g_wACFeedPowerLimit = suwGetEEMaxFeedPower() - 200;		// 用户设置的馈网功率
	UpDownLimit(g_wACFeedPowerLimit,wPvChgPowerTemp+200,-200);
	wROpFeedWattTemp = swGetROpWattNew();					// 实际的负载功率参考

	// 7. 模式和并网充电/带载功率值计算
	if(uwInvFeedWorkMode == cInvFeedWorkAuto)	// 根据用户设置自动计算并网充电和带载功率，和方向
	{
		if(uwInvWorkPriority == cInvWorkUSB)	// 后备模式 Backup Mode	// HOPE工作
		{
			// 后备模式：市电充电+带载，逆变器不并网带载
			// 市电参考功率，方向仅充电
			// AC限流使能时需要把负载功率减去，剩下的自然就是市电能出的最大功率
			// 电池侧可充/放的功率 正充电，负放电
			if(g_uwACCurrLimitEn) // AC限流使能
			{
				wGridWattRef = g_wACWattLimit - wROpFeedWattTemp;
			}
			else // AC限流禁止
			{
				wGridWattRef = wGridChgPowerLimitTemp;
			}
			wMaxFeedPowerLimit = 0;	// 此模式不允许并网带载
			//Uplimit(wGridWattRef,wBatDsgPowerLimitTemp);	// 电池包最大充电功率
			Uplimit(wGridWattRef,wGridChgPowerLimitTemp);	// 充电功率不超过设置值
			UpDownLimit(wGridWattRef,uwGetInvWattMax(),0);		// 限制最小0，防止采样出问题导致控制器工作在并网馈电区间
			wBatWattRef = wGridWattRef;						// 这个参数在这个模式意义不大，赋值是为了调试寄存器显示
		}
		else if(uwInvWorkPriority == cInvWorkSUB)	// 电池优先 Batt First
		{
			if(g_uwACCurrLimitEn) // AC限流使能
			{
				// 负载小于AC限流功率时，市电带载，PV和市电多余的能量给电池充电
				// 负载大于AC限流功率时，PV补充带载，PV补充后还不够时，电池补充带载
				// 电池补充还不满足负载时，AC限流失效
				// 电池侧可充/放的功率 正充电，负放电
				wBatWattRef = wPvChgPowerTemp + g_wACWattLimit - wROpFeedWattTemp;			// PV实时功率+AC限流功率-负载功率就是电池该给的功率
				wMaxFeedPowerLimit = uwGetInvWattMax();											// 此模式并网带载功率最大值系统额定功率
			}
			else // AC限流禁止
			{
				// PV带载,PV不足市电补,电池不出功
				// 负载小于总充电功率时，自动转充电
				// 电池侧可充/放的功率 正充电，负放电
				wBatWattRef = wPvChgPowerTemp + wGridChgPowerLimitTemp - wROpFeedWattTemp;	// PV实时功率+市电充电功率-负载功率就是电池该给的功率
				wMaxFeedPowerLimit = wPvChgPowerTemp;										// 此模式并网带载功率最大值是PV当前功率最大值

				// PV不存在，转市电充电
			}
			wGridWattRef = wBatWattRef - wPvChgPowerTemp;									// 电池功率减PV功率就是市电该给的功率
			Uplimit(wBatWattRef,wGridChgPowerLimitTemp);									// 限制市电充电在设置的最大功率 保证市电充电功率不超
			UpDownLimit(wBatWattRef,uwGetInvWattMax(),-uwGetInvWattMax());								// 限制充放电功率在额定功率上
			Uplimit(wGridWattRef,wGridChgPowerLimitTemp);									// 限制市电充电在设置的最大功率 保证市电充电功率不超
			UpDownLimit(wGridWattRef,uwGetInvWattMax(),-uwGetInvWattMax());								// 限制充放电功率在额定功率上
		}
		else  if(uwInvWorkPriority == cInvWorkSBU)	// 负载优先 Load First
		{
			// 电池包有通讯连接时以电池包SOC作为此模式市电充放电状态切换
			// 优化:切换时可以加个延时 3-5S左右
			// 负载很大的时候，如果设置的电压上下切换值比较相近，有存在频繁切换充/放电的情况，大载会把电池电压拉低
			if(sbGetEMSBMSConnect())// || swGetPylonCanConnectFlag())
			{
				if(g_wBatSOCReal <= suwGetEEOnGridBatAutoStartChgSOC())
				{
					uwInvWorSUBGridDir = cInvWorSUBGridDirChg;// 市电给电池充电
				}
				else if(g_wBatSOCReal >= suwGetEEOnGridBatExitAutoChgSOC())
				{
					uwInvWorSUBGridDir = cInvWorSUBGridDirDsg;// 电池并网放电到负载
				}
			}
			else	// 电池包没有通讯时，以电池电压作为此模式市电充放电状态切换
			{
				if(swGetBatVoltNew() <= suwGetEEOnGridBatAutoStartChgVolt())
				{
					uwInvWorSUBGridDir = cInvWorSUBGridDirChg;// 市电给电池充电
				}
				else if(swGetBatVoltNew() >= suwGetEEOnGridBatExitAutoChgVolt())
				{
					uwInvWorSUBGridDir = cInvWorSUBGridDirDsg;// 电池并网放电到负载
				}
			}

			if(uwInvWorSUBGridDir == cInvWorSUBGridDirChg)		// 市电充电
			{
				if(g_uwACCurrLimitEn)	// AC限流使能
				{
					wGridWattRef = g_wACWattLimit - wROpFeedWattTemp;
				}
				else
				{
					wGridWattRef = wGridChgPowerLimitTemp;
				}
				wMaxFeedPowerLimit = 0;	// 此模式不允许并网带载
				Uplimit(wGridWattRef,wGridChgPowerLimitTemp);	// 充电功率不超过设置值
				UpDownLimit(wGridWattRef,uwGetInvWattMax(),0);		// 限制最小0，防止采样出问题导致控制器工作在并网馈电区间
				wBatWattRef = wGridWattRef;						// 这个参数在这个模式意义不大，赋值是为了调试寄存器显示
			}
			else	// 逆变并网带载
			{
				//wROpFeedWattTemp += g_wACFeedPowerLimit;
				wGridWattRef = -(wROpFeedWattTemp);
				wMaxFeedPowerLimit = uwGetInvWattMax();
				UpDownLimit(wGridWattRef,0,-uwGetInvWattMax());
				wBatWattRef = wGridWattRef;						// 这个参数在这个模式意义不大，赋值是为了调试寄存器显示
			}
		}
		else
		{
			wBatWattRef = 0;
			wGridWattRef = 0;
			wMaxFeedPowerLimit = 0;
		}
	}
	else if(uwInvFeedWorkMode == cInvFeedWorkOnlyChg)	// 市电仅充电
	{
		// 市电充电功率限制值:根据市电充电电流折算逆变功率
		wBatAcChgCurrTemp = wGridChgBatCurrRef;														// 手动模式设置量
		wBatAcChgCurrTemp = (INT16S)(((INT32S)wBatAcChgCurrTemp * 136) >> 7);						// 0.94 efficiency
		wGridChgPowerLimitTemp = (INT16S)((INT32S)wBatAcChgCurrTemp * swGetBatVoltNew() / 10000);	// 电池充电电流折算到逆变充电功率	
		Uplimit(wGridChgPowerLimitTemp,uwGetInvWattMax());												// 3200W
		wBatWattRef = wGridChgPowerLimitTemp;

		// 电池侧可充/放的功率 正充电，负放电
		wGridWattRef = wGridChgPowerLimitTemp;
		wMaxFeedPowerLimit = 0;							// 此模式不允许并网带载
		UpDownLimit(wGridWattRef,uwGetInvWattMax(),0);		// 限制最小0，防止采样出问题导致控制器工作在并网馈电区间
	}
	else if(uwInvFeedWorkMode == cInvFeedWorkOnlyDsg)	// 市电仅放电
	{
		// 电池侧可充/放的功率 正充电，负放电
		wBatWattRef = -wGridFeedWattRef;				// 手动模式设置量
		wGridWattRef = -wGridFeedWattRef;
//		wROpFeedWattTemp = wGridFeedWattRef;			// for test 加上这个应该可以解决手动模式馈电功率不准的问题
		wMaxFeedPowerLimit = uwGetInvWattMax();
		UpDownLimit(wGridWattRef,0,-uwGetInvWattMax());
	}
	else
	{
		wBatWattRef = 0;
		wGridWattRef = 0;
		wMaxFeedPowerLimit = 0;
	}

	// 8. 并网带载时的补偿,只补偿放电带载的功率
	g_wRLineWattNewTemp = swGetRLineVoltNew();//wROpFeedWattTemp - swGetRInvWattNew();	// 市电功率
	//g_wRLineWattNewTemp = swGetRLineWattNew();					// 市电功率 正是消耗电，负是馈网功率

	// if(wGridWattRef < 0)
	if(0)
	{
//*****PV前馈
		// 并网环路在馈电带载时，给PV环路加个负载前馈，让PV发电满足BAT+LOAD
		// 优化成离网模式根据实际载量计算前馈，区分并网功率 
		
		// PV给电池充电 + 逆变并网带载的电流参考
		g_wPvLoadCurrFeedWard1 = (INT16S)((INT32S)(-wGridWattRef) * 1000  / swGetBatVoltNew());	// 0.01A
		UpDownLimit(g_wPvLoadCurrFeedWard1,cMpptBatCurrMax,0);

		// 馈电功率的PV前馈参考
//		g_wPvLoadCurrFeedWard2 = (INT16S)((INT32S)(g_wACFeedPowerLimit) * 10000  / swGetBatVoltNew());	
//		UpDownLimit(g_wPvLoadCurrFeedWard2,cMpptBatCurrMax,0);

		// PV前馈
		g_wPvLoadCurrFeedWard = g_wPvLoadCurrFeedWard1 + g_wPvLoadCurrFeedWard2;
		UpDownLimit(g_wPvLoadCurrFeedWard,cMpptBatCurrMax,0);

		// PV多余能量 这里计算还有问题
//		wPVCurrErr = uwPvChgBatCurrTemp - swGetPv1BatCurrNew() - g_wPvLoadCurrFeedWard2;
//		if(wPVCurrErr > 0)
//		{
//			wPVCurrErr = 0;
//		}

		// PV多余能量并网
//		wInvFrrdWattErr = (INT16S)((INT32S)wPVCurrErr * swGetBatVoltNew() / 10000);
//		if(wInvFrrdWattErr > 0)
//		{
//			wInvFrrdWattErr = 0;
//		}
//*****PV前馈END

		// 负载误差补偿
		if(g_uwACCurrLimitEn)	// AC限流使能
		{
			if(uwInvWorkPriority == cInvWorkSBU && uwInvWorSUBGridDir == cInvWorSUBGridDirDsg)
			{
				if(uwInvFeedWorkMode == cInvFeedWorkAuto)
				{
					fLoadWattErrKI += (F32)(swGetRInvWattNew() - wROpFeedWattTemp) * 0.01; 		// 功率积分,0.01
				}
				else
				{
					fLoadWattErrKI = 0;	// 可以改成手动模式下的功率补偿
				}
			}
			else if(g_wACWattLimit < (wROpFeedWattTemp))
			{
				fLoadWattErrKI += (F32)(g_wACWattLimit - g_wRLineWattNewTemp) * 0.01; 			// 功率积分,0.01
			}
		}
		else
		{
			if(uwInvFeedWorkMode == cInvFeedWorkAuto)
			{
				fLoadWattErrKI += (F32)(swGetRInvWattNew() - (wROpFeedWattTemp)) * 0.01; 		// 功率积分,0.01
			}
			else
			{
				fLoadWattErrKI = 0;	// 可以改成手动模式下的功率补偿
			}
		}
		UpDownLimit(fLoadWattErrKI,100.0,-100.0);												// Err ±100W
	}
	else
	{
		fLoadWattErrKI = 0;
		g_wPvLoadCurrFeedWard = 0;
		wInvFrrdWattErr = 0;
	}
	wGridWattRef += fLoadWattErrKI;		// 叠加并网带载积分补偿
	wGridWattRef += wInvFrrdWattErr;	// 叠加实际允许的馈电功率

	// 9. 逆变充电功率限制值,软起控制
	if((swGetWorkMode() == cLineMode) && (suwGetFBInvCtrlSts() == cFBInvCtrlBus))
//	if(1)
	{
		if(wInvChgPowerLimitTemp < sGetRatedGridPower())
		{
			wInvChgPowerCntTemp++;
			wInvChgPowerLimitTemp = ((INT32S)wInvChgPowerCntTemp * sGetRatedGridPower()) / (uwGridpowerslopeTime * 50);
		}
		else
		{
			wInvChgPowerCntTemp = 0;
			wInvChgPowerLimitTemp = sGetRatedGridPower();
		}
	}
	else
	{
		wInvChgPowerCntTemp = 0;
		wInvChgPowerLimitTemp = 0;
	}
	
	// 10. 逆变放电功率限制值,软起控制
	if((swGetWorkMode() == cLineMode) && (suwGetFBInvCtrlSts() == cFBInvCtrlBus))
//	if(1)
	{
		if(wInvDsgPowerLimitTemp < sGetRatedGridPower())
		{
			wInvDsgPowerCntTemp++;
			wInvDsgPowerLimitTemp = ((INT32S)wInvDsgPowerCntTemp * sGetRatedGridPower()) / (uwGridpowerslopeTime * 50);
		}
		else
		{
			wInvDsgPowerCntTemp = 0;
			wInvDsgPowerLimitTemp = sGetRatedGridPower();
		}
	}
	else
	{
		wInvDsgPowerCntTemp = 0;
		wInvDsgPowerLimitTemp = 0;
	}

	// 11. 市电功率最大值限幅
	wInvCtrlPower = -(wGridWattRef);											// 以上充电正,放电负，以下取反，充电是负，放电是正
	UpDownLimit(wInvCtrlPower,uwGetInvWattMax(),-uwGetInvWattMax());			// 并网充放电功率上下限在系统额定值
//	 UpDownLimit(wInvCtrlPower,wMaxFeedPowerLimit,-wGridChgPowerLimitTemp);		// 并网放电功率上限根据模式自动切换在系统最大值和PV实时功率
	//Uplimit(wInvCtrlPower,(wBatDsgPowerLimitTemp + wPvChgPowerTemp));			// PV+电池最大放电功率
	UpDownLimit(wInvCtrlPower,wInvChgPowerLimitTemp,-wInvDsgPowerLimitTemp);	// 系统最大充放电功率(刚进入并网时软起功率)
//	UpDownLimit(wInvCtrlPower,uwGetInvWattMax(),-wRlyChgPowerLimitTemp);		// 继电器最大功率(限制并网充电功率，馈电带载限制在额定值)

	// 12. 市电充放电功率降额限幅
//	UpDownLimit(wInvCtrlPower,swGetInvTempDeratPowerLimit(),-swGetInvTempDeratPowerLimit());	// 逆变过温降功率
//	UpDownLimit(wInvCtrlPower,swGetTwTempDeratPowerLimit(),-swGetTwTempDeratPowerLimit());		// 推挽过温降功率
//	UpDownLimit(wInvCtrlPower,swGetTraTempDeratPowerLimit(),-swGetTraTempDeratPowerLimit());	// 推挽变压器温度降额功率
//	UpDownLimit(wInvCtrlPower,swGetBatVoltDeratPowerLimit(),-swGetBatVoltDeratPowerLimit());	// 电池低压降并网功率
//	UpDownLimit(wInvCtrlPower,swGetLineVoltDeratPowerLimit(),-swGetLineVoltDeratPowerLimit());  //市电充电电压降额
//	UpDownLimit(wInvCtrlPower,100,-100);	// for test

	// 13. 给到并网控制器的值
	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)  
//	if(1)
	{
		// 充电电流软起
		if(gi_wInvChgCurrLimitTemp < uwGetInvFreeCntlCurrMax())
		{
			gi_wInvChgCurrLimitTemp += gi_wInvChgCurrSoftStartRate;
			//gi_wInvChgCurrLimitTemp++;
		}
		else
		{
			gi_wInvChgCurrLimitTemp = uwGetInvFreeCntlCurrMax();
		}
		
		// 放电电流软起
		if(gi_wInvFeedCurrLimitTempTemp < uwGetInvFreeCntlCurrMax())
		{
			gi_wInvFeedCurrLimitTempTemp++;
		}
		else
		{
			gi_wInvFeedCurrLimitTempTemp = uwGetInvFreeCntlCurrMax();
		}

		// 目前实际功率是正功率放电，负功率是充电
		wInvCurrTemp = (INT16S)((INT32S)wInvCtrlPower * 1414 / swGetRLineVoltNew() / 10);	// 主计算算出的并网充/带载电流
		UpDownLimit(wInvCurrTemp,gi_wInvChgCurrLimitTemp,-gi_wInvFeedCurrLimitTempTemp);
		wInvCurrFeedTemp = (INT16S)((INT32S)g_wACFeedPowerLimit * 1414 / swGetRLineVoltNew() / 10);	// 设置的卖电功率
		UpDownLimit(wInvCurrFeedTemp,gi_wInvChgCurrLimitTemp,-gi_wInvFeedCurrLimitTempTemp);
		
		gi_wBatChgInvLimit = wInvCurrTemp;						// for test

		if(wInvCurrTemp > 0)									// 正，放电
		{
			g_uwGridBusVoltRef = (INT16U)((INT32U)4000);//suwGetEEBatLowShutDownVolt() * uwGetTransformerRatio() / 100);
			sSetInvFeedBusVoltRef(g_uwGridBusVoltRef);
			gi_wInvChgCurrLimit = -8;
			gi_wInvFeedCurrLimit = wInvCurrTemp;
		}
		else if(wInvCurrTemp < 0)								// 负，充电
		{
			g_uwGridBusVoltRef = (INT16U)((INT32U)swGetBatVoltRef() * 64 / 10);//4700);//swGetBatVoltRef() * uwGetTransformerRatio() / 100);	// 2880 * 180 / 100
			sSetInvFeedBusVoltRef(g_uwGridBusVoltRef);
			gi_wInvChgCurrLimit = -(wInvCurrTemp) + (-5);
			gi_wInvFeedCurrLimit = 8;
//			gi_wInvFeedCurrLimit = wInvCurrFeedTemp;//8;
		}
		else
		{
			gi_wInvChgCurrLimit = 0;
			gi_wInvFeedCurrLimit = 0;
//			gi_wInvFeedCurrLimit = wInvCurrFeedTemp;	// for test 如果出现一直不卖电的时候，再打开这里看看 
		}
	}
	else
	{
		// 模式识别，待机模式（单步调试）时跳过这段代码，使用上位机设置对应参数
		if(swGetStayStandby() == 0)
		{
			gi_wInvChgCurrLimit = 0;
			gi_wInvFeedCurrLimit = 0;
			gi_wBatChgInvLimit = 0;
			gi_wInvFeedCurrLimitTemp =0;//20;

			gi_wInvChgCurrLimitTemp = 0;
			gi_wInvFeedCurrLimitTempTemp = 0;
		}
	}	
}


INT16S g_wBusVoltRef;
INT16U uwStandardRefVolt = 0;
extern INT16S g_wInvBusVoltRef;
INT16U g_wDCDCBusVoltRef = 3800;	// 母线软起目标
void	sControllerRefUpdate(void)
{
	static INT16S wBatVoltAvgTemp = 0;
	static INT16S wBatVoltAvgRes = 0;
	INT16U uwBusVoltRefTemp = 0;
	INT16U uwLineVoltMax = 0;
//	INT16U uwStandardRefVolt;
	INT16S wBusVoltRef;
	
	// 市电峰值电压
	if(!sbGetLineLossStatus() && swGetWorkMode() != cBatteryMode && swGetWorkMode() != cChgMode)
	{
		uwLineVoltMax = swGetRLineVoltNew();
		uwLineVoltMax = (INT16S)(((INT32U)uwLineVoltMax * 191) >> 7) + cBusVoltReal20V;
	}
	
	uwBusVoltRefTemp = uwLineVoltMax;
	if(sbGetLineLossStatus() && subGetParaBatOpenSts())	// Solar power load single
	{
		uwBusVoltRefTemp = 0;
	}
	
	// 低通滤波
	wBatVoltAvgTemp = (INT16S)swGetBatVoltNew() + wBatVoltAvgTemp*3 + wBatVoltAvgRes;
	wBatVoltAvgRes = wBatVoltAvgTemp & 0x0003;
	wBatVoltAvgTemp = wBatVoltAvgTemp >> 2;
	uwStandardRefVolt = wBatVoltAvgTemp;
//	if(g_wSysLiBatActFlg)
//	{
//		uwStandardRefVolt = g_wBatVoltRef;	
//	}
//	else if(uwStandardRefVolt > (cBatVoltReal15V*cBatSerialPcs))
	if(uwStandardRefVolt > (cBatVoltReal15V*uwGetBatSerialPcs()))
	{
		uwStandardRefVolt = cBatVoltReal15V*uwGetBatSerialPcs();
	}
	
	uwStandardRefVolt = (INT16U)((((INT32U)uwStandardRefVolt) * uwGetTransformerRatio())/100);
	if(uwStandardRefVolt > uwBusVoltRefTemp)
	{
		uwBusVoltRefTemp = uwStandardRefVolt;
	}
	
	// 限制母线电压范围
	if(uwGetModelLV())
	{
		if(uwBusVoltRefTemp < cBusVoltReal190V)
		{
			uwBusVoltRefTemp = cBusVoltReal190V;
		}
		else if(uwBusVoltRefTemp > cBusVoltReal240V)
		{
			uwBusVoltRefTemp = cBusVoltReal240V;
		}
	}
	else
	{
		if(uwBusVoltRefTemp < cBusVoltReal380V)
		{
			uwBusVoltRefTemp = cBusVoltReal380V;
		}
		else if(uwBusVoltRefTemp > cBusVoltReal480V)
		{
			uwBusVoltRefTemp = cBusVoltReal480V;
		}
	}

	// 母线电压软起
	wBusVoltRef = g_wBusVoltRef;
	if(suwGetDCDCCtrlSts() == cDCDCWait && suwGetFBInvCtrlSts() == cFBWait)
	{
		wBusVoltRef = uwBusVoltRefTemp;
	}
	else if(wBusVoltRef > uwBusVoltRefTemp)
	{
		wBusVoltRef -= cBusVoltReal1V;
	}
	else if(wBusVoltRef < (uwBusVoltRefTemp - cBusVoltReal10V))
	{
		wBusVoltRef = (uwBusVoltRefTemp - cBusVoltReal10V) + cBusVoltReal1V;
	}
	else if(wBusVoltRef < (uwBusVoltRefTemp - cBusVoltReal1V))
	{
		wBusVoltRef += cBusVoltReal1V;
	}
	else
	{
		wBusVoltRef = uwBusVoltRefTemp;
	}
	
	// 限制母线电压范围
	if(uwGetModelLV())
	{
		if(wBusVoltRef < cBusVoltReal190V)
		{
			wBusVoltRef = cBusVoltReal190V;
		}
		else if(wBusVoltRef > cBusVoltReal240V)
		{
			wBusVoltRef = cBusVoltReal240V;
		}
	}
	else
	{
		if(wBusVoltRef < cBusVoltReal380V)
		{
			wBusVoltRef = cBusVoltReal380V;
		}
		else if(wBusVoltRef > cBusVoltReal480V)
		{
			wBusVoltRef = cBusVoltReal480V;
		}
	}

	if(suwGetDCDCCtrlSts() == cDCDCSoft)
	{
		wBusVoltRef = wBusVoltRef - cBusVoltReal30V;
	}

	if(swGetAgingStatus() == false)
	{
		OS_ENTER_CRITICAL();
		g_wBusVoltRef = wBusVoltRef;
		g_wDCDCBusVoltRef = g_wBusVoltRef + cBusVoltReal20V;	// max 500V	
		g_wInvBusVoltRef = g_wBusVoltRef;						// max 480V
		if(uwGetModelLV())
		{
			if(g_wDCDCBusVoltRef > cBusVoltReal240V)				// max 240V 			
			{
				g_wDCDCBusVoltRef = cBusVoltReal240V;
			}
		}
		else
		{
			if(g_wDCDCBusVoltRef > cBusVoltReal480V)				// max 480V 			
			{
				g_wDCDCBusVoltRef = cBusVoltReal480V;
			}
		}
		OS_EXIT_CRITICAL();
	}
	else
	{	
		OS_ENTER_CRITICAL();
		g_wBusVoltRef = wBusVoltRef;
		g_wDCDCBusVoltRef = g_wBusVoltRef;		// max 480V
		if(uwGetModelLV())
		{
			g_wInvBusVoltRef = cBusVoltReal200V;	// max 200V
		}
		else
		{
			g_wInvBusVoltRef = cBusVoltReal400V;	// max 400V
		}
		OS_EXIT_CRITICAL();
	}
}

void	sTurboWattCtrlProc(void)			// Turbo模式实现
{
	INT16S wWattTemp;
	wWattDeratROpVolt = suwGetEEACOutputRatedVolt();
	if((suwGetEETurboMode() == false) \
		|| (suwGetFBInvCtrlSts() == cFBInvCtrlBus) || (swGetAgingStatus() == true))
	{
		g_uwTurboMode = false;
		wWattDeratROpVolt = suwGetEEACOutputRatedVolt();
		return;
	}
	else
	{
		g_uwTurboMode = true;
	}

	wWattTemp = swGetROpWattNew();
	if((wWattTemp > uwGetInvWattMax()) && (swGetWorkMode() == cBatteryMode))
	{
		uwWattDeratePerTemp = (wWattTemp - uwGetInvWattMax()) / 10;
		wWattDeratROpVolt -= (uwWattDeratePerTemp);
		if(wWattDeratROpVolt < uwGetInvDeratingVolt())
		{
			wWattDeratROpVolt = uwGetInvDeratingVolt();
		}
	}
	else
	{
		uwWattDeratePerTemp = 1;
		wWattDeratROpVolt += uwWattDeratePerTemp;
		if(wWattDeratROpVolt >= suwGetEEACOutputRatedVolt())
		{
			wWattDeratROpVolt = suwGetEEACOutputRatedVolt();
		}
	}

}

void	sInvLoadOPJobInit(void)
{
	fInvLoadOPJob.data = 0;
	fSysChgDsgStatus.data = 0;
	
	g_uwInvRMSCtrlVolt = 0;
	g_wOPRMSRatedVolt = 0;
	g_wInvDCVoltCntlEn = false;					// 默认不补偿
	
	g_wInvDCVoltRef = 0;

	g_wBusVoltRef = 0;
	g_wInvBusVoltRef = 0;
	g_wDCDCBusVoltRef = 0;
	
	wWattDeratROpVolt = suwGetEEACOutputRatedVolt();
	sMPPTParaInit();		// MPPT参数初始化
}
void	sInvLoadParaUpdate(void)
{
	if(uwGetModelLV())	// LV 110V
	{
		g_wBusVoltRef = cBusVoltReal190V;
		g_wInvBusVoltRef = cBusVoltReal190V;
		g_wDCDCBusVoltRef = cBusVoltReal190V;
		
		g_uwInvRMSCtrlVolt = 0;
		g_wOPRMSRatedVolt = suwGetEEACOutputRatedVolt();	// 1200;
	}
	else	// 常规230V
	{
		g_wBusVoltRef = cBusVoltReal360V;
		g_wInvBusVoltRef = cBusVoltReal360V;
		g_wDCDCBusVoltRef = cBusVoltReal360V;
		
		g_uwInvRMSCtrlVolt = 0;
		g_wOPRMSRatedVolt = suwGetEEACOutputRatedVolt();	// 2300;
	}
}


INT16U	PowerOffTese = 0;

//INT16U	uwShutdownSts = 0;// 逆变器关机标志
//void	sInvPowerOffChk(void)
//{
//	static INT16U s_uwToShutdown = 0;
//	static INT16U s_uwToShutdownCount = 0;
//	static INT16U s_uwShutdownCount = 0;
//	static INT16U s_uwShutdownCmdCount = 0;
//
//	// 检测不允许关机的条件，触发后直接退出关机逻辑
//	if((swGetPv1VoltNew() > cMpptPvVolt60V) || (swGetRLineVoltNew() > cLineVolt60V))
//	{
//		s_uwToShutdown = 0;
//		s_uwToShutdownCount = 0;
//		s_uwShutdownCount = 0;
//		s_uwShutdownCmdCount = 0;
////		mPVSPSSDOn;	// PV辅源是否要保持这个逻辑？
//		return;
//	}
////	mPVSPSSDOff;	// PV辅源是否要保持这个逻辑？
//
//	// 检测是否允许关机动作
//	if(mBATONS == false)
//	{
//		if((++s_uwShutdownCount > cT100ms) && (uwShutdownSts == false))
//		{
//			uwShutdownSts = true;
//			//OSISREventSend(cPrioSuper, eSuperToShutdown);	// 最终优化方向是这个
//		}
//	}
//	else
//	{
//		s_uwToShutdown = 0;
//		s_uwToShutdownCount = 0;
//		s_uwShutdownCount = 0;
//		s_uwShutdownCmdCount = 0;
//		if(uwShutdownSts == true)
//		{
//			//OSISREventSend(cPrioSuper, eSuperToStandby);
//			sSetLoadOnSts(false);
//		}
//		uwShutdownSts = false;
//	}
//
//	// 执行关机动作
//	if(uwShutdownSts == true)
//	{
//		if(s_uwToShutdown > 0)
//		{
//			sSetGridRelayOn(false);
////			sSetGridNRelayOn(false);
//			sSetOPRelayOn(false);
////			sSetInvRelayOn(false);
//		}
//	
//		if(s_uwToShutdown == 0)
//		{
//			sSetGridRelayOn(false);
////			sSetGridNRelayOn(false);
//			sSetOPRelayOn(false);
////			sSetInvRelayOn(false);
//
//			if(++s_uwToShutdownCount > cT100ms)
//			{
//				s_uwToShutdownCount = 0;
//				s_uwToShutdown = 1;
//			}
//		}
//		else if(s_uwToShutdown == 1)
//		{
//			sSetPV1CtrlSts(cPVWait);
//			sSetDCDCCtrlSts(cDCDCWait);
//
//			//if(++s_uwToBatModeCount > cT20sec)
//			//if((++s_uwToBatModeCount > cT20sec) && (swGetBusVoltNew() <= cBusVoltReal60V))	// 并且BUS电压低于60V
//			if(swGetBusVoltNew() <= cBusVoltReal80V)	// BUS电压低于60V
//			{
//				s_uwToShutdownCount = 0;
//				s_uwToShutdown = 2;
//			}
//			else
//			{
//				if((suwGetFBInvCtrlSts() != cFBInvOpenLoop) && (suwGetFBInvCtrlSts() != cFBInvCtrlVolt))
//				{
//					sSetFBInvCtrlSts(cFBInvOpenLoop);
//				}
//			}
//		}
//		else if(s_uwToShutdown == 2)
//		{
//			sSetFBInvCtrlSts(cFBWait);
//			
//			if(++s_uwToShutdownCount > cT1sec)
//			{
//				s_uwToShutdownCount = 0;
//				s_uwToShutdown = 3;
//			}
//		}
//		else if(s_uwToShutdown == 3)
//		{
//			mKEYSPSOff;
//		}
//	}
//	else
//	{
//		s_uwToShutdown = 0;
//		s_uwToShutdownCount = 0;
//		s_uwShutdownCmdCount = 0;
//	}
//
//	//超时逻辑
//
//}


void	sInvPowerOffChk(void)
{
	static INT8U	bChkEn = 3;	// 开机按键必须松开后,才允许检测关机按键
	static INT16U	wChkCnt = 0;
	
	if(bChkEn == true)
	{
		if(mBATONS == false)
		{
			wChkCnt++;
			if(wChkCnt >= 50)
			{
				sSetDCDCCtrlSts(cDCDCWait);	// 关DCDC
				sSetLoadOnSts(false);
				 sSetStayStandby(true);
				 mPV_FANENOff;
				g_wKeyOffflag = 1;
			}
		}
		else
		{
			if(g_wKeyOffflag == 1)
			{
				sSetDCDCCtrlSts(cDCDCWait);	// 关DCDC
				sSetLoadOnSts(false);
				sSetStayStandby(true);
//				mPV_FANENOff;
				mKEYSPSOff;
			}
			wChkCnt = 0;
			bChkEn = false;
		}
	}
	else if(bChkEn == 3)	// 开机按键必须松开后,才允许检测关机按键
	{
		if(mBATONS == false)
		{
			bChkEn = true;
		}
	}
	else
	{
		bChkEn = true;
	}

}


// 负功率检测（CT焊反）
// 考虑一下，只检测一次，一次之后就不再检测，需要界定进入功率
void	sInvCurrCTRebConChk(INT8U ubFilter)
{
	static INT16U s_uwCTRebConCnt = 0;
	INT8U ubCTRebCon = false;
	
	if(swGetWorkMode() == cBatteryMode || swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode)
	{
		if(sb16UUnderLevelChk(swGetROpWattNew(), g_wInvWattCT, ubFilter, &s_uwCTRebConCnt))
		{
			ubCTRebCon = true;
		}
		
		if(ubCTRebCon)
		{
			s_uwCTRebConCnt = 0;
			T_FAULT_DATA.bits.bOPCTFault = true;
			sSetFaultCode(cOPCTSenserFault);
		}
	}
	else
	{
		s_uwCTRebConCnt = 0;
	}
}

//省电模式，逻辑：输出功率低于设定值一段时间后关逆变控制器，后续每隔一段时间开逆变控制器扫描一次，每次200ms
//如果检测到功率则开输出
void sPowerSavingModeChk(INT16S uwWatt,INT16U uwFilter1,INT16U uwFilter2)
{
	static INT16U uwPowerSavingCnt = 0;
	static INT16U uwPowerSavingLossCnt = 0;
	static INT16U uwPowerSavingBackCnt = 0;
	static INT16U uwPowerSavingLossFlag = false;

	//省电模式需在工作离网模式
	if((!suwGetEEPowerSaveMode()) || (swGetWorkMode() != cBatteryMode))
	{
		return;
	}

	if(swGetROpWattNew() < uwWatt)
	{
		uwPowerSavingBackCnt = 0;
		if(++uwPowerSavingLossCnt > uwFilter1)
		{
			uwPowerSavingLossCnt = 0;
			if(swGetInvPWMEn() != false)
			{
				uwPowerSavingLossFlag = true;
				sSetFBInvCtrlSts(cFBWait);		// 关逆变
				sSetInvPWMEn(false);
			}
		}
		if(uwPowerSavingLossFlag == true)
		{
			uwPowerSavingCnt++;
			if(uwPowerSavingCnt > uwFilter2)	// 30s
			{
				uwPowerSavingCnt = 0;
				sSetFBInvCtrlSts(cFBInvCtrlVolt);
			}
			else if(uwPowerSavingCnt > 10)		// 200ms
			{
				if(swGetInvPWMEn() != false)
				{
					//uwPowerSavingLossFlag == true;
					sSetFBInvCtrlSts(cFBWait);	// 关逆变
					sSetInvPWMEn(false);
				}
			}
		}
	}
	else
	{
		uwPowerSavingLossCnt = 0;
		if(++uwPowerSavingBackCnt > 5)			// 100ms
		{
			uwPowerSavingBackCnt = 0;
			uwPowerSavingLossFlag = false;
			if(suwGetFBInvCtrlSts() != cFBInvCtrlVolt)
			{
				sSetFBInvCtrlSts(cFBInvCtrlVolt);
			}
		}
	}


}

void sInvHardOCChk(void)
{
/*	if(mINVIOVER)
	{
		if(gi_uwInvCurrHWHiIntCnt > 0)
		{
			gi_uwInvCurrHWHiIntCnt--;
		}
	}
	if(gi_uwInvCurrHWHiIntCnt == 0)
	{
		T_FAULT_DATA.bits.bInvHardOC = false;
	}*/
}

void sOPOverLoadLowvolt(void)
{
	INT16S wOPWatTemp = 0;
	static INT16S wOPVoltDreatTemp = 0;
	wOPVoltDreatTemp = suwGetEEACOutputRatedVolt();
	wOPWatTemp = swGetROpWattNew();
	
	if(wOPWatTemp > 1050)
	{
		g_uwOPLoadLevelCnt++;
		g_uwOpLoadRstDelayCnt = 10;
	
		if(((wOPWatTemp >= 2000) && (g_uwOPLoadLevelCnt > 0))\
		|| ((wOPWatTemp <  2000) &&(wOPWatTemp >= 1700) && (g_uwOPLoadLevelCnt > cT500ms))\
		|| ((wOPWatTemp <  1700) &&(wOPWatTemp >= 1400) && (g_uwOPLoadLevelCnt > cT1sec5))\
		|| ((wOPWatTemp <  1400) &&(wOPWatTemp >= 1200) && (g_uwOPLoadLevelCnt > cT25sec))\
		|| ((wOPWatTemp <  1200) &&(wOPWatTemp >= 1050) && (g_uwOPLoadLevelCnt > cT50sec)))
		{
			if(wOPVoltDreatTemp > wWattDeratROpVolt) 		
			{
				wOPVoltDreatTemp = wWattDeratROpVolt;
			}
			else
			{
				wOPVoltDreatTemp++;
			}
			if(wOPVoltDreatTemp > suwGetEEACOutputRatedVolt())
			{
				wOPVoltDreatTemp = suwGetEEACOutputRatedVolt();
			}
			if(wOPVoltDreatTemp < uwGetInvDeratingVolt())
			{
				wOPVoltDreatTemp = uwGetInvDeratingVolt();
			}
		}
		else if(((wOPWatTemp >= 2000) && (g_uwOPLoadLevelCnt > cT50ms))\
			|| ((wOPWatTemp <  2000) &&(wOPWatTemp >= 1700) && (g_uwOPLoadLevelCnt > cT250ms))\
			|| ((wOPWatTemp <  1700) &&(wOPWatTemp >= 1400) && (g_uwOPLoadLevelCnt > cT2sec))\
			|| ((wOPWatTemp <  1400) &&(wOPWatTemp >= 1200) && (g_uwOPLoadLevelCnt > cT30sec))\
			|| ((wOPWatTemp <  1200) &&(wOPWatTemp >= 1050) && (g_uwOPLoadLevelCnt > cT1min)))
		{
			T_FAULT_DATA.bits.bLoadOverLoad = true;
			sSetFaultCode(cOverLoad);
			g_uwOPLoadLevelCnt = 0;
		}
		else
		{
			wOPVoltDreatTemp = suwGetEEACOutputRatedVolt();
		}
	}
	else
	{
		if(g_uwOpLoadRstDelayCnt > 0)
		{
			g_uwOpLoadRstDelayCnt--;
		}
		else
		{
			if(g_uwOPLoadLevelCnt > 10) g_uwOPLoadLevelCnt = 10;
		}
		if(g_uwOPLoadLevelCnt > 0) g_uwOPLoadLevelCnt--;
		
		if(wOPVoltDreatTemp < suwGetEEACOutputRatedVolt())
		{
			wOPVoltDreatTemp++;
		}
		else
		{
			wOPVoltDreatTemp = suwGetEEACOutputRatedVolt();
		}
		
	}
	return(wOPVoltDreatTemp);
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	uwGetInvLoadStkChk(void)
{
	return uwInvLoadStkChk;
}

INT16U	uwGetOPRMSRatedVolt(void)
{
	return g_wOPRMSRatedVolt;
}

INT16U	uwGetInvRMSCtrlVolt(void)
{
	return g_uwInvRMSCtrlVolt;
}

INT16S	swGetOutputVoltCntl(void)
{
	return wOutputVoltCntl;
}

INT16U	swGetTurobMode(void)
{
	return g_uwTurboMode;
}

INT16U	swGetDCDCBusVoltRef(void)
{
	return g_wDCDCBusVoltRef;
}

INT16U	swGetPvChgBatCurrRef(void)
{
	return uwPvChgBatCurrRef;
}


INT16S	swGetBatWattRef(void)		// 电池并网功率
{
	return wBatWattRef;
}


INT16S	swGetGridWattRef(void)		// 市电并网环路功率
{
	return wGridWattRef;
}

INT16S	swGetInvCurrTemp(void)		// 并网充放功率
{
	return wInvCurrTemp;
}


INT16U	suwGetSysPvChgEn(void)
{
	return fSysChgDsgStatus.bits.bPvChgEn;
}

INT16U	swGetACCurrLimitEn(void)		// AC限流 使能
{
	return g_uwACCurrLimitEn;
}

INT16S	swGetACCurrLimit(void)		// AC限流 电流 0.01A
{
	return g_wACCurrLimit;
}


INT16S	swGetACPowerLimit(void)		// AC限流 功率 W
{
	return g_wACPowerLimit;
}

INT16S	swGetACWattLimit(void)		// AC限流实际功率 W
{
	return g_wACWattLimit;
}


INT16S	swGetACFeedPowerLimit(void)		// 设置的最大馈电功率 W
{
	return g_wACFeedPowerLimit;
}

INT16S	swGetROpFeedWattTemp(void)			// 主功率负载量参考 W
{
	return wROpFeedWattTemp;
}

INT16S	swGetInvFeedWorkMode(void)			// 逆变器能量调度方向(0按照设置自动识别 1充电 2放电)
{
	return uwInvFeedWorkMode;
}

INT16S	swGetGridChgBatCurrRef(void)			// 市电充电电池电流参考
{
	return wGridChgBatCurrRef;
}


INT16S	swGetGridFeedWattRef(void)			// 市电并网放电功率
{
	return wGridFeedWattRef;
}


INT16S	swGetInvCtrlPower(void)			// 市电 控制的功率，正充电,负放电
{
	return wInvCtrlPower;
}


INT16S	swGetPvLoadCurrFeedWard(void)			// PV负载电流前馈
{
	return g_wPvLoadCurrFeedWard;
}

INT16S	swGetMaxFeedPowerLimit(void)			// 最大并网功率限制(有些模式只允许并最大PV功率)
{
	return wMaxFeedPowerLimit;
}

INT16S	swGetGridChgPowerLimitTemp(void)			// 根据市电设置充电电流得到逆变最大允许充电功率
{
	return wGridChgPowerLimitTemp;
}

INT16S	swGetwRlyChgPowerLimitTemp(void)			// 继电器最大允许功率(只会在逆变充电时出现)
{
	return wRlyChgPowerLimitTemp;
}

		
INT16S	swGetInvChgPowerLimitTemp(void)	// 市电充电软起至额定功率值
{
	return wInvChgPowerLimitTemp;
}

INT16S	swGetInvDsgPowerLimitTemp(void)	// 市电放电软起至额定功率值
{
	return wInvDsgPowerLimitTemp;
}


INT16S	swGetInvChgCurrLimitTemp(void) // 充电电流软起临时值
{
	return gi_wInvChgCurrLimitTemp;
}

INT16S	swGetInvFeedCurrLimitTempTemp(void) // 放电电流软起临时值
{
	return gi_wInvFeedCurrLimitTempTemp;
}

INT16S	swGetPvChgBatCurrTemp(void) // PV充电电流临时值
{
	return uwPvChgBatCurrTemp;
}


INT16S	swGetBatChgPowerLimitTemp(void) // 电池最大充电功率
{
	return wBatChgPowerLimitTemp;
}

INT16S	swGetBatDsgPowerLimitTemp(void) // 电池最大放电功率
{
	return wBatDsgPowerLimitTemp;
}


INT16S	swGetInvWorSUBGridDir(void) // 负载优先模式下的并网方向
{
	return uwInvWorSUBGridDir;
}

INT16S	swGetWattDeratROpVolt(void) // 
{
	return wWattDeratROpVolt;
}
INT16S	swGetWattDeratePerTemp(void) 
{
	return uwWattDeratePerTemp;
}
/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetInvRMSCtrlVolt(INT16U uwVolt)
{
	g_uwInvRMSCtrlVolt = uwVolt;
}

void	sSetTurobMode(INT16U uwVolt)
{
	g_uwTurboMode = uwVolt;
}

void	sSetOPRMSRatedVolt(INT16U uwVolt)
{
	g_wOPRMSRatedVolt = uwVolt;
}

void	sSetDCDCBusVoltRef(INT16U uwTemp)
{
	g_wDCDCBusVoltRef = uwTemp;
}


void	sSetACCurrLimitEn(INT16U uwTemp)
{
	g_uwACCurrLimitEn = uwTemp;
}

void	sSetACCurrLimit(INT16U uwTemp)
{
	g_wACCurrLimit = uwTemp;
}

void	sSetACPowerLimit(INT16U uwTemp)
{
	g_wACPowerLimit = uwTemp;
}

void	sSetACWattLimit(INT16U uwTemp)
{
	g_wACWattLimit = uwTemp;
}

void	sSetInvFeedWorkMode(INT16U uwTemp)
{
	uwInvFeedWorkMode = uwTemp;
}


void	sSetGridChgBatCurrRef(INT16U uwTemp)
{
	wGridChgBatCurrRef = uwTemp;
}

void	sSetGridFeedWattRef(INT16U uwTemp)
{
	wGridFeedWattRef = uwTemp;
}

void	sSetInvChgCurrSoftStartRate(INT16S uwTemp)
{
	gi_wInvChgCurrSoftStartRate = uwTemp;
}

void	sSetGridpowerslopeTime(INT16U uwTemp)
{
	uwGridpowerslopeTime = uwTemp;
}





