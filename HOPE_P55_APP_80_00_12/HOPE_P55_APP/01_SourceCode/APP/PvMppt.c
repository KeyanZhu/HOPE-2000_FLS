/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__PVMPPT_CONTROL_C__

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
union BAT_CHG_CTRL_STATUS_TABLE
{
	struct BAT_CHG_CTRL_STATUS_BIT_FEILD
	{
		INT16U bBuckChgEn:1;
		INT16U bBuckPwmInit:1;
		INT16U bPvSwitchOn:1;
		INT16U bRsvd1:1;
		
		INT16U bPvVoltLoopSel:1;	// 0=BATT LOOP,1=PV LOOP
		INT16U bMpptSoftStart:1;	// 刚进入强制启动MPPT(X秒后失效)
		INT16U bMpptPause:1;		// 暂停MPPT
		INT16U bMppVoltLimit:1;

		INT16U bBuckSoftStart:1;	// BUCK2,BUCK3刚开始的时候缓起标志
		INT16U bRsvd3:3;
		
		INT16U bRsvd4:4;
	} bits;
	INT16U data;
} fBatChgCtrl;


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
// Mppt Ctrl
INT16S	wMppVoltLoLimit;	// 0.1V
INT16U	wMpptInterval;
INT16S	wMpptVoltStep;
INT16S	wMpptVoltRef;		// PV扰动输出的PV电压

INT16S	wMpptVoltPre;
INT32S	dwMpptWattPre;


/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sMPPTParaInit(void)
{
	sSetPvVoltRef(swGetPv1VoltNew());							// 此赋值没啥用，优化时可酌情删除
	
	wMppVoltLoLimit = cMPPT_VOLT_MIN_LIMIT;
	if(wMppVoltLoLimit < cMPPT_VOLT_MIN_LIMIT)
	{
		wMppVoltLoLimit = cMPPT_VOLT_MIN_LIMIT;
	}
	
	wMpptInterval = 25;		// 25*20ms=500ms
	wMpptVoltStep = 10;	//0.2V	// 0.1V
	wMpptVoltRef = 3800;	// 46V
	
	wMpptVoltRef = (INT16S)((INT32S)swGetPv1VoltNew() * 218 >> 8);	// MPP=0.85*OPEN
	if(wMpptVoltRef < wMppVoltLoLimit)
	{
		wMpptVoltRef = wMppVoltLoLimit;
	}
	wMpptVoltPre = wMpptVoltRef;
	dwMpptWattPre = 0;
}


INT32S	dwWattTemp = 0;
void	sBuckMpptMethod(void)
{
	static INT16U wCnt = 0;
	INT16S	wVoltTemp;
	
	INT16S	wMpptVoltTemp;
	INT16S	wInputVoltUpLimit;
	
	if(fBatChgCtrl.bits.bMpptPause == true)
	{
		wCnt = 0;
		wMpptVoltRef = swGetPv1VoltNew();
		dwMpptWattPre = 0;
		wMpptVoltPre = wMpptVoltRef + wMpptVoltStep;
		return;
	}
	
	if(++wCnt < wMpptInterval)
	{
		return;
	}
	wCnt = 0;
	
	wVoltTemp = swGetPv1VoltNew();
	dwWattTemp = (INT32U)swGetPv1VoltNew() * swGetPvInCurrNew();	// 追踪功率参考
	wInputVoltUpLimit = swGetPv1VoltNew() + cPV_INPUT_VOLT_ERR;
	wMpptVoltTemp = wMpptVoltRef;
	if(wMpptVoltRef <= wMppVoltLoLimit)
	{
		if(dwWattTemp >= 120000)		// 12W
		{
			wMpptVoltTemp = wMpptVoltRef + wMpptVoltStep;
		}
		else
		{
			wMpptVoltTemp = wMpptVoltRef;
		}
	}
	else if(swGetPv1VoltNew() > wInputVoltUpLimit)
	{
		wMpptVoltTemp = wMpptVoltRef - wMpptVoltStep;
	}
	else if(dwWattTemp < dwMpptWattPre)
	{
		if(wVoltTemp < wMpptVoltPre)
		{
			wMpptVoltTemp = wMpptVoltRef + wMpptVoltStep;
		}
		else
		{
			wMpptVoltTemp = wMpptVoltRef - wMpptVoltStep;
		}
	}
	else
	{
		if(wVoltTemp <= wMpptVoltPre)	// 这里会一直让电压往左边跑
		//if(wVoltTemp < wMpptVoltPre)
		{
			wMpptVoltTemp = wMpptVoltRef - wMpptVoltStep;
		}
		else
		{
			wMpptVoltTemp = wMpptVoltRef + wMpptVoltStep;
		}
	}
	wMpptVoltPre = wVoltTemp;
	dwMpptWattPre = dwWattTemp;
	
	//限制扰动结果不超过上次扰动的±2V
//	if(wMpptVoltTemp > wMpptVoltPre + 20)
//	{
//		wMpptVoltTemp = wMpptVoltPre +20;
//	}
//	if(wMpptVoltTemp < wMpptVoltPre - 20)
//	{
//		wMpptVoltTemp = wMpptVoltPre - 20;
//	}
	//限制扰动结果不超过上次扰动的±2V
//	UpDownLimit(wMpptVoltTemp, wMpptVoltPre + 20, wMpptVoltPre - 20);
	
	if(wMpptVoltTemp < wMppVoltLoLimit)
	{
		wMpptVoltRef = wMppVoltLoLimit;
	}
	else
	{
		wMpptVoltRef = wMpptVoltTemp;
	}
}

void	sBuckMpptDisturb(INT16U wFilter)
{
	static	INT16U   wChkCnt = 0;
	INT16S	wMpptVoltTemp;
	
	// 如果连续5秒MPPT电压比PV电压高且电流为很小,则需强制拉低至PV电压0.85左右
	if((wMpptVoltRef > (swGetPv1VoltNew() + wMpptVoltStep)) \
		&& (swGetAdcPv1BatCurrReal() < cMPPT_CURR_MIN_LIMIT))
	{
		wChkCnt++;
	}
	else
	{
		wChkCnt = 0;
	}
	
	if(wChkCnt >= wFilter)
	{
		wChkCnt = 0;
		
		wMpptVoltTemp = (INT16S)((INT32S)swGetPv1VoltNew() * 218 >> 8);
		if(wMpptVoltTemp < wMppVoltLoLimit)
		{
			wMpptVoltRef = wMppVoltLoLimit;
		}
		else
		{
			wMpptVoltRef = wMpptVoltTemp;
		}
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	suwGetMpptVoltRef(void)			// PV扰动输出的PV电压
{
	return wMpptVoltRef;
}

INT16U	suwGetPvMpptPause(void)
{
	return fBatChgCtrl.bits.bMpptPause;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetPvMpptPause(INT16S wTemp)
{
	fBatChgCtrl.bits.bMpptPause = wTemp;
}
void    sSetPvVoltLoopSel(INT16S wTemp)
{
    fBatChgCtrl.bits.bPvVoltLoopSel = wTemp;
}


