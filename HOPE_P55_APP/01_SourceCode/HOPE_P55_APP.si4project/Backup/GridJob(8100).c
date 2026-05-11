/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__GRID_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      cTimer20ms
#define         cT500ms                         (500 / cTimerBase)
#define         cT1sec                          (1000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)

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
INT16S g_wRFixCapaReactivePower;
INT16S g_wRFixCapaReactivePowerKtest = -4;//-13;//80;//10;//-13;// 38;// -13;// 20;//260;


/********************************************************************************
* Output variables																*
********************************************************************************/
INT16U g_uwRatedGridPower;


/********************************************************************************
* Internal variables															*
********************************************************************************/
union GRID_STATUS_TABLE
{
	struct GRID_STATUS_BIT_FEILD
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
} fGridJob;

INT16U	uwGridStkChk = 0;				// 市电任务堆栈检测,堆栈大小

extern INT16S gi_wInvFeedCurrLimit;		// for test
extern INT16S gi_wInvFeedCurrLimitTemp;	// for test

INT16S	gi_wIslandDetectStep = 0;		// 并网控制器用
INT16S	g_wIslandDetectStep = 0;		// 孤岛检测临时用
INT16S	g_wIslandDetect = 0;			// 孤岛标识, 	1已经触发孤岛 0未触发
INT16U	g_uwIslandDetectDelay = 8;
INT16U	g_wToLineModeDelayTime = 3000;	// 20*3000 = 60000 = 60S 这个时间是不是在eeprom写的比较好？

INT16U	uwGridLossCount = 150;			// 150个市电周期
/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sGridJobInit(void);
void	sCalReactiveCurr220V(void);

void sIslandDetect(void);		// 孤岛检测
INT16S sRSTIslandChk(INT16S *pwIslandStep, INT16S *pwIslandStepPre, INT16S wLineFreq, INT16S *pwLineFreqPre, INT16S *pwIslandChkCnt);
void sIslandRecover(void);
void sGridChgBusVoltChk(void);


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sGridJob(void)
{
	INT16U	wEvent;
	
	sGridJobInit();
		
	while(1)
	{

		wEvent = OSEventPend();

		if(wEvent & (1 << eGridLineZero))
		{
			sLineZeroLossClr();											// 考虑一下这个的逻辑
			sSetRLineVoltNew(swRLineVoltCal());							// LINE.V
			sSetRLineCurrNew(swGetROpCurrNew() - swGetRInvCurrNew());	// LINE.I	for test

			sSetRLineWattNew(swGetROpWattNew() - swGetRInvWattNew());	// 市电有功功率

			sSetRLineFreqNew(swGetPreSinePeriodCntNew());				// 市电频率	软件锁相环得出
//			sSetRLineFreqNew(swGetLinePeriodCntNew());					// 市电频率	硬件锁相环得出
			
			sRLineRms3timeAvgUpdate();									// 市电电压历史平均值
			
			sRLineVoltChk(100);											// 市电电压异常检测
			sLineFreqChk(100);											// 市电频率异常检测
			sGridOverLoadChk(swGetwRlyChgPowerLimitTemp(),10);			// 电网过载告警检测/继电器过载/ 200ms 
			sGridCurrOverChk(1000,cT5sec);								// 电网过流故障检测/继电器过载/ 25A,5s 
			sGridCurrOver2Chk(1200,10);									// 电网过流故障检测/继电器过载/ 28A,100ms 
			sLinePhaseChk(3);											// 市电相位检测
			
			sGridChgBusVoltChk();

//			sIslandDetect();											// 孤岛检测

//			if((uwGridLossCount > 0) && (swGetRLineVoltFilter() > 600))		// 市电告警显示的一个延时。150个市电周期
//			{
//				uwGridLossCount--;
//			}
		}
		
		if(wEvent & (1 << eGeneralTimer))
		{	    
			sRLinePowerCal();											// 市电功率参数计算					
			sLineZeroLossChk(5);										// 市电丢失时刷新市电各项数据和参数(考虑一下这个的逻辑)
//			sCalReactiveCurr220V();										// 无功补偿计算
//			sIslandRecover();											// 孤岛恢复

			// for test													// 并网控制器并网电流给定软起，需要重新考虑实现方式
//			if(gi_wInvFeedCurrLimitTemp < gi_wInvFeedCurrLimit)
//			{
//				gi_wInvFeedCurrLimitTemp++;
//			}
//			else if(gi_wInvFeedCurrLimitTemp > gi_wInvFeedCurrLimit)
//			{
//				gi_wInvFeedCurrLimitTemp--;
//			}

			#if	OS_STK_CHK_EN>0
			uwGridStkChk = OSStkChk(cPrioGrid);	// 93word
			#endif
		}
	}
}

void	sGridJobInit(void)
{
	fGridJob.data = 0;
	
	g_wRFixCapaReactivePower = 0;
}
	
void	sCalReactiveCurr220V(void)
{
	INT8U bFreq = 5;	// 50hz/10	
	INT16S wFixCapReactivePowerTemp;
	
//	if(suwGetEEACOutputRatedFreq() == 6000)
//	{
//		bFreq = 6;	//60hz/10
//	}
	
//	g_wReactiveCurr220V= (INT16S) ((INT32U)1415  * bFreq * g_wCapaSize/1000);  // 1415= 220* 2 * pi *1024
//	wFixCapReactivePowerTemp= -(INT16S)((((INT32S)g_wReactiveCurr220V * g_uwRLineVolt * 7) /22 )>>10);
	
//	g_wReactiveCurr220V= (INT16S) ((INT32U)1415  * bFreq * g_wCapaSize/1000);  // 1415= 220* 2 * pi *1024
	wFixCapReactivePowerTemp = -(INT16S)(((INT32S)g_wRFixCapaReactivePowerKtest * bFreq * swGetRLineVoltNew() ) /2200);
	g_wRFixCapaReactivePower = wFixCapReactivePowerTemp;
	
//	g_wRFixCapaReactivePower =- g_wRFixCapaReactivePowerKtest;
//	eg: wRLineVolt= 2300 , wFixReactive=wReactiveCurr220V * 2300 *400 /2200 /1024  
}

void sIslandDetect(void)		// 孤岛检测
{
	//static INT16U s_uwIslandDetectDelay = 10;
	static INT16S s_wLineFreqPre = 0;
	static INT16S s_wIslandDetectStepPre = 0;
	static INT16S s_wIslandDetetChkCnt = 0;

	//if(suwGetFBInvCtrlSts() == cFBInvCtrlBus && suwGetEEPIslandChkEnable() && g_wPFAjustRef == 100)
	if(suwGetFBInvCtrlSts() == cFBInvCtrlBus && suwGetEEAnti_IslandProtectEnable())
	{
		if(g_uwIslandDetectDelay > 0)
		{
			g_uwIslandDetectDelay--;
		}
		else if(g_uwIslandDetectDelay == 0)
		{
			if(sRSTIslandChk(&g_wIslandDetectStep, &s_wIslandDetectStepPre, swGetRLineFreqNew(), &s_wLineFreqPre, &s_wIslandDetetChkCnt))
			{
				//g_uwIslandDetectDelay = 5;
				g_uwIslandDetectDelay = 5;//14;
			}
		}
	}
	else
	{
		g_wIslandDetectStep = 0;
		s_wIslandDetectStepPre = 0;
		g_uwIslandDetectDelay = 5;	
		s_wIslandDetetChkCnt = 0;
	}
	OS_ENTER_CRITICAL();
	gi_wIslandDetectStep = g_wIslandDetectStep;
	OS_EXIT_CRITICAL();
}

INT16S IslandTemp = 0;

INT16S sRSTIslandChk(INT16S *pwIslandStep, INT16S *pwIslandStepPre, INT16S wLineFreq, INT16S *pwLineFreqPre, INT16S *pwIslandChkCnt)
{
	if(*pwIslandStep == 0 && *pwIslandStepPre == 0)
	{
		*pwIslandStep = 1;
		IslandTemp = 1;	
	}
	else if(*pwIslandStep > *pwIslandStepPre)
	{
		if(wLineFreq > ((*pwLineFreqPre) + 	20))		//20 // + 0.2Hz
		{
			*pwIslandStepPre = *pwIslandStep;
			(*pwIslandStep) -= 1;
			IslandTemp = 2;
		}
		else
		{
			*pwIslandStep = 0;
			*pwIslandStepPre = 0;
			*pwIslandChkCnt = 0;
			IslandTemp = 3;
			return true;
		}
	}
	else
	{
		IslandTemp = 7;
		if(wLineFreq < ((*pwLineFreqPre) -15))
		{
			if(++(*pwIslandChkCnt) > 10)
			{
				g_wIslandDetect = 1;
				T_ALARM_DATA.bits.bGridActiveIsland = 1;
				OSEventSend(cPrioSuper, eSuperLineLoss);
				*pwIslandStep = 0;
				*pwIslandStepPre = 0;
				*pwIslandChkCnt = 0;
				IslandTemp = 4;
				return true;	
			}
			else
			{
				*pwIslandStepPre = *pwIslandStep;
				(*pwIslandStep) += 1;
				IslandTemp = 5;
			}
		}	
		else
		{
			*pwIslandStep = 0;
			*pwIslandStepPre = 0;
			*pwIslandChkCnt = 0;
			IslandTemp = 6;
			return true;
		}
	}
	*pwLineFreqPre = wLineFreq;
	return false;
}

void sIslandRecover(void)
{
	static INT16U wIslandDetecRestoreCnt = 0;
	
	if(g_wIslandDetect)
	{
		if((++wIslandDetecRestoreCnt > (g_wToLineModeDelayTime+20))
		&& (!sbGetLineFeedLossStatus()))
		{
			wIslandDetecRestoreCnt = 0;
			g_wIslandDetect = 0;
		}
		if(swGetWorkMode() == cLineMode || swGetWorkMode() == cBypassMode)
		{
			wIslandDetecRestoreCnt = 0;
			g_wIslandDetect = 0;					
		}
		//fGridJob.bit.uwIslandTrig = 1;
		T_ALARM_DATA.bits.bGridActiveIsland = true;
	}
	else
	{
		//fGridJob.bit.uwIslandTrig = 0;
		T_ALARM_DATA.bits.bGridActiveIsland = false;
	}
}

INT16S g_wGridChgBusVoltFlag = 0;

void sGridChgBusVoltChk(void) //仅并网时有效
{

	INT16S wValueTemp = 0;	// 母线 - 市电峰值；
//	INT16S wChkCnt = 0;

	wValueTemp = swGetBusVoltNew() - swGetRLineRms3timeAvgPeak();
	if(wValueTemp < 400)
	{
		g_wGridChgBusVoltFlag = 1;
	}
	else
	{
		g_wGridChgBusVoltFlag = 0;
	}

}
/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	sGetRatedGridPower(void)
{
	return g_uwRatedGridPower;
}
INT16U	sGetGridChgBusVoltFlag(void)
{
	return g_wGridChgBusVoltFlag;
}

INT16U	uwGetGridStkChk(void)
{
	return uwGridStkChk;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/


