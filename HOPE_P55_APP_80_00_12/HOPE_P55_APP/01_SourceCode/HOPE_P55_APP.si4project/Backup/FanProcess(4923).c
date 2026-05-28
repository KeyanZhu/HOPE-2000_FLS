/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__FAN_PROCESS_C__

/********************************************************************************
* Include head files															*
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


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/


/********************************************************************************
* Output variables																*
********************************************************************************/


/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16U	uwFanWorkMode = cFanPerFormanceMode;	// 风扇工作模式

INT16U wFanDuty = cFanDutyOff;
INT16U wFanDutyPct = 0;

INT16U wFanStatus = 0;
INT16U wFanSpeedOnCount = 0;
INT16U wFanSpeedOffCount = 0;
INT16U uwFanSpeedCount1Delay = 0;
INT16U uwFanSpeedCount2Delay = 0;
INT16U wFanPerRealTime = 0;				// 风扇当前转速百分比
INT16U wFanSelfCheckCnt = 0;			// 风扇开机自检时间
INT16U wFanSpeedChk = false;
INT16U	wFanStartCount = 0;

extern INT16U	PowerOffTese;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sFanSpeedCtrl(INT16U ubFilter1,INT16U ubFilter2);
void	sFanSpeedChk(INT16U uwFilter);
void	sFBFanSpeedCtrl(INT16U ubFilter1,INT16U ubFilter2);


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sFBFanSpeedProc(INT16U ubFilter1,INT16U ubFilter2)	// base 10ms
{
	sFBFanSpeedCtrl(100,500); 		// 风扇转速控制,1S,3s
	sFanSpeedChk(250);				// 风扇堵转检测,2.5S
	
	//mFanPWM = cFanDutyOff;		// 需要在线仿真时,打开这个屏蔽
}

INT16S 	wACoutFanPer = 100;			// 功率折算风扇百分比
INT16S 	wInvTempFanPer = 100;		// 逆变温度折算风扇百分比
INT16S 	wPvBatCurrFanPer = 100;		// PV充电电池电流折算风扇百分比
INT16S 	wAcBatChgCurrFanPer = 100;	// 市电充电电池电流折算风扇百分比

void	sFBFanSpeedCtrl(INT16U ubFilter1,INT16U ubFilter2)
{
	INT16U	wFanPer = 0;

	uwFanWorkMode = suwGetEEFanWorkMode();

	// 风扇转速计算
	if(uwFanWorkMode > cFanPerWaitMode)
	{
		if((uwFanWorkMode == cFanPerFormanceMode) || (uwFanWorkMode == cFanPerSilentMode))	// 智能模式/静音模式
		{
			wACoutFanPer = 30 + (INT16S)((INT32S)((INT16S)swAbs(swGetRInvWattFilter()) - 300) * (100 - 30) / (uwGetMaxFanDutyInvWatt() - 300));			// 逆变功率				折算风扇转速百分比
			wInvTempFanPer = 30 + (INT16S)((INT32S)((INT16S)swAbs(swGetHsInvTempFilter()) - 450) * (100 - 30) / (700 - 450));				// 逆变温度				折算风扇转速百分比
			wPvBatCurrFanPer = 30 + (INT16S)((INT32S)(swGetPv1BatCurrFilter() - 200) * (100 - 30) / (500 - 200));	// PV充电电池电流 		折算风扇转速百分比
			wAcBatChgCurrFanPer = 30 + (INT16S)((INT32S)((INT16S)swAbs(swGetBatCurrFilter()) - 30) * (100 - 30) / (80 - 30));	// 市电充电电池电流			折算风扇转速百分比

			Dnlimit(wACoutFanPer,0);
			Dnlimit(wInvTempFanPer,0);
			Dnlimit(wPvBatCurrFanPer,0);
			Dnlimit(wAcBatChgCurrFanPer,0);

			if(wACoutFanPer > wInvTempFanPer)
			{
				wFanPer = wACoutFanPer;
			}
			else
			{
				wFanPer = wInvTempFanPer;
			}
			if(wFanPer < wPvBatCurrFanPer)
			{
				wFanPer = wPvBatCurrFanPer;
			}
			if(wFanPer < wAcBatChgCurrFanPer)
			{
				wFanPer = wAcBatChgCurrFanPer;
			}
		}
	}
	else
	{
		wFanPer = 0;	// 模式0，风扇禁止启动
	}

	// 风扇转速限制
	if(uwFanWorkMode == cFanPerFormanceMode)		// 智能/性能模式
	{
		Uplimit(wFanPer,100);
//		wFanDutyPct = wFanPer;
	}
	else if(uwFanWorkMode == cFanPerSilentMode)		// 静音模式
	{
		Uplimit(wFanPer,65);
//		wFanDutyPct = wFanPer;
	}
	else if(uwFanWorkMode == cFanPerManualMode)		// 手动模式
	{
		wFanPer = wFanDutyPct;
		Uplimit(wFanPer,100);
	}

	if(wFanPer > 0)
	{
		wFanSpeedChk = true;
	}
	else
	{
		wFanSpeedChk = false;
	}
/*
	if(++wFanSelfCheckCnt < 500)					// 上电风扇拉满/相当于开机自检 5s
	{
		wFanPer = 20;								// fot test 上电开满转速风扇，单PV上电会烧辅源
		//wFanPer = 100;
		wFanDutyPct = wFanPer;
	}
	else
	{
		wFanSelfCheckCnt = 500;
		if(wFanPer < 30)		// 转速低于30不转
		{
			wFanPer = 0;
			wFanDutyPct = wFanPer;
		}
	}

	if(PowerOffTese > 0)	// 关机时，风扇不转
	{
		wFanPer = 0;
	}
	
	if(wFanPer > wFanDutyPct)
	{
		if(++wFanSpeedOnCount > ubFilter1)
		{
			wFanSpeedOnCount = 0;
			wFanDutyPct++;
		}
	}
	else if(wFanPer < wFanDutyPct)
	{
		if(++wFanSpeedOffCount > ubFilter2)
		{
			wFanSpeedOffCount = 0;
			wFanDutyPct--;
		}
	}
	else
	{
		wFanSpeedOnCount = 0;
		wFanSpeedOffCount = 0;
	}
*/	
	wFanDuty = (INT16S)((INT32S)cFanPeriod * wFanDutyPct / 100);
	Uplimit(wFanDuty,cFanPeriod);
	if(swGetWorkMode() != cPowerOnMode)
	{
		wFanStartCount++;
		if(wFanStartCount <= 250)		//5s
		{		
			mFanPWM = (INT16S)((INT32S)cFanPeriod * 20 / 100);
		}
		else
		{
			mFanPWM = wFanDuty;
			Uplimit(wFanStartCount, 300);
		}
	}
	else
	{
		mFanPWM = (INT16S)((INT32S)cFanPeriod * 20 / 100);
	}
	// mFanPWM = wFanDuty;
}


void	sFanSpeedChk(INT16U uwFilter)
{
	wFanStatus = (mFANINCLK2 << 1) + (mFANINCLK1);

	if(wFanSpeedChk)
	{
		if(mFANINCLK1)	// 风扇1堵转检测
		{
			if(++uwFanSpeedCount1Delay >= uwFilter)
			{
				T_ALARM_DATA.bits.bFAN1Alarm = true;
			}	
		}
		else
		{
			uwFanSpeedCount1Delay = 0;
			T_ALARM_DATA.bits.bFAN1Alarm = false;
		}

		if(mFANINCLK2)	// 风扇2堵转检测
		{
			if(++uwFanSpeedCount2Delay >= uwFilter)
			{
				T_ALARM_DATA.bits.bFAN2Alarm = true;
			}
		}
		else
		{
			uwFanSpeedCount2Delay = 0;
			T_ALARM_DATA.bits.bFAN2Alarm = false;
		}
	}
	else
	{
		T_ALARM_DATA.bits.bFAN1Alarm = false;
		T_ALARM_DATA.bits.bFAN2Alarm = false;
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	swGetFanDuty(void)
{
	return wFanDuty;
}

INT16U	swGetFanDutyPct(void)
{
	return wFanDutyPct;
}

INT16U	swGetFanStatus(void)
{
	return wFanStatus;
}


INT16U	swGetFanWorkMode(void)
{
	return uwFanWorkMode;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetFanDuty(INT16U wDuty)
{
	wFanDuty = wDuty;
}

void	sSetFanDutyPct(INT16U wDutyPct)
{
	wFanDutyPct = wDutyPct;
}




