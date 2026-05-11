/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__DEARTING_PROCESS_C__

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
union DERATING_STATUS_TABLE
{
	struct DERATING_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U	bInvTempDerate:1;	// 逆变过温降额
		INT16U	bTwTempDerate:1;	// 推挽过温降额
		INT16U	bTraTempDerate:1;	// 推挽散热器过温降额
		INT16U	bPvTempDerate:1;	// PV散热器过温降额
		
		// BIT4-7
		INT16U	bPvVoltDerate:1;	// PV电压降额/降充电电流
		INT16U	bBatVoltDerate:1;	// 电池欠压降额
		INT16U	bLineVoltDerate:1;//rsvd2:2
		INT16U	rsvd2:1;
		// BIT8-11
		INT16U	rsvd3:4;
		
		// BIT12-15
		INT16U	rsvd4:3;
		INT16U	DerateEn:1;			// 降额使能(默认使能，运行降额逻辑)
	} bits;
	INT16U data;
} fSysDeratingStatus;

INT16S	wTempDeratVoltNew;				// OP降额输出结果
INT16S	wTempDeratVoltFilter;
INT16S	wTempDeratPvBatCurrNew;			// PV降额输出结果
INT16S	wTempDeratPvBatCurrFilter;

INT16S 	wInvTempDeratePer;				// 逆变过温降额百分比
INT16S 	wInvTempDeratPowerLimit;		// 逆变过温降额功率
INT16S 	wInvTempDeratVoltLimit;			// 逆变过温降额电压

INT16S 	wTwTempDeratePer;				// 推挽过温降额百分比
INT16S 	wTwTempDeratPowerLimit;			// 推挽过温降额功率
INT16S 	wTwTempDeratVoltLimit;			// 推挽过温降额电压

INT16S 	wTraTempDeratePer;				// 变压器过温降额百分比
INT16S 	wTraTempDeratPowerLimit;		// 变压器过温降额功率
INT16S 	wTraTempDeratVoltLimit;			// 变压器过温降额电压

INT16S 	wPvTempDeratePer;				// PV过温降额百分比
INT16S 	wPvTempDeratCurrLimit;			// PV过温降额电流

INT16S  g_wBatDeratePer;				// BAT欠压降额百分比
INT16S 	wBatVoltDeratPowerLimit;		// BAT欠压功率降额
INT16S 	wBatVoltDeratVoltLimit;			// BAT欠压降额负载电压

INT16S 	wBatCurrDeratVoltLimit;			// BAT限流降额负载电压

INT16S  g_wLineDeratePer;				// 市电降额
INT16S 	wLineVoltDeratPowerLimit;		// 
/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16U uwInvTempStartDerat = 1240;		// 逆变温度降额范围
INT16U uwInvTempEndDerat = 1290;

INT16U uwTwTempStartDerat = 1140;		// 推挽温度降额范围
INT16U uwTwTempEndDerat = 1190;

INT16U uwTraTempStartDerat = 800;		// 推挽变压器温度降额范围
INT16U uwTraTempEndDerat = 850;

INT16U uwPvTempStartDerat = 850;		// PV温度降额范围
INT16U uwPvTempEndDerat = 910;



/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sDeratingDataReset(void);

void	sInvTempDerating(void);
void	sTwTempDerating(void);
void	sTraTempDerating(void);
void	sPvTempDerating(void);
void	sBatDerating(void);
void	sLineDerating(void);

INT16S  swDeratOutAdj(void);
INT16S  swDeratPvCurrAdj(void);

void	sSetTempDeratVoltNew(INT16S wVolt);
void	sSetPvTempDeratCurrNew(INT16S wVolt);


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sDeratingProcInit(void)
{
	fSysDeratingStatus.data = 0X0000;
	fSysDeratingStatus.bits.DerateEn = true;
	uwInvTempStartDerat = uwGetHsInvTempStartDerat();		// 逆变温度降额范围
	uwInvTempEndDerat = uwGetHsInvTempEndDerat();
	uwTwTempStartDerat = uwGetHsTwTempStartDerat();			// 推挽温度降额范围
	uwTwTempEndDerat = uwGetHsTwTempEndDerat();
	uwTraTempStartDerat = uwGetTraTempStartDerat();			// 推挽变压器温度降额范围
	uwTraTempEndDerat = uwGetTraTempEndDerat();
	uwPvTempStartDerat = uwGetPvTempStartDerat();			// PV温度降额范围
	uwPvTempEndDerat = uwGetPvTempEndDerat();
	sDeratingDataReset();		// 初始值
}

void	sDeratingProc(void)
{
	if(fSysDeratingStatus.bits.DerateEn)
	{
		sInvTempDerating();		// 逆变过温降额
		sTwTempDerating();		// 推挽过温降额
		sPvTempDerating();		// PV过温降额
//		sBatDerating();			// 电池欠压降额
		sLineDerating();		// 市电欠压电压降额
	}
	else
	{
		sDeratingDataReset();	// 初始值
	}

	sSetTempDeratVoltNew(swDeratOutAdj());		// 得到输出电压降额结果
	sSetPvTempDeratCurrNew(swDeratPvCurrAdj());	// 得到PV降额结果
}

void	sDeratingDataReset(void)
{
	wTempDeratVoltNew = uwGetInvRateVolt();			// OP降额输出结果
	wTempDeratVoltFilter = uwGetInvRateVolt();
	wTempDeratPvBatCurrNew = cMpptBatCurrMax;		// PV降额输出结果
	wTempDeratPvBatCurrFilter = cMpptBatCurrMax;

	wInvTempDeratePer = 100;						// 逆变过温降额百分比
	wInvTempDeratPowerLimit = uwGetInvWattMax();	// 逆变过温降额功率
	wInvTempDeratVoltLimit = uwGetInvRateVolt();	// 逆变过温降额电压

	wTwTempDeratePer = 100;							// 推挽过温降额百分比
	wTwTempDeratPowerLimit = uwGetInvWattMax();		// 推挽过温降额功率
	wTwTempDeratVoltLimit = uwGetInvRateVolt();		// 推挽过温降额电压

	wTraTempDeratePer = 100;						// 变压器过温降额百分比
	wTraTempDeratPowerLimit = uwGetInvWattMax();	// 变压器过温降额功率
	wTraTempDeratVoltLimit = uwGetInvRateVolt();	// 变压器过温降额电压

	wPvTempDeratePer = 100;							// PV过温降额百分比
	wPvTempDeratCurrLimit = cMpptBatCurrMax;		// PV过温降额功率


	g_wBatDeratePer = 100;							// BAT欠压降额百分比
	wBatVoltDeratPowerLimit = uwGetInvWattMax();	// BAT欠压功率降额
	wBatVoltDeratVoltLimit = uwGetInvRateVolt();	// BAT欠压降额负载电压
	
	wBatCurrDeratVoltLimit = uwGetInvRateVolt();	// BAT限流降额负载电压

	g_wLineDeratePer = 100;				// 市电
	wLineVoltDeratPowerLimit = uwGetInvWattMax();		//
}

void	sInvTempDerating(void)
{
	INT16U g_wHsTempDeratePerTemp;
	INT16S wTemp;

	wTemp = swGetHsInvTempFilter();	// 逆变当前温度
	if(wTemp < 0)
    {
        wTemp = 0;
    }
	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		g_wHsTempDeratePerTemp = 10;
	}
	else								
	{										
		g_wHsTempDeratePerTemp = 82;
	}
	
	if(wTemp <= uwInvTempStartDerat)	
	{
		wInvTempDeratePer = 100;
	}
	else if(wTemp > uwInvTempEndDerat)	
	{
		wInvTempDeratePer = g_wHsTempDeratePerTemp;
	}
	else
	{
		wInvTempDeratePer = g_wHsTempDeratePerTemp + (uwInvTempEndDerat - wTemp)\
							* (100 - g_wHsTempDeratePerTemp)/ (uwInvTempEndDerat - uwInvTempStartDerat);
	}

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		wInvTempDeratPowerLimit = (INT16S)((INT32S)sGetRatedGridPower() * wInvTempDeratePer / 100);
	}
	else
	{										
		wInvTempDeratVoltLimit = (INT16S)((INT32S)suwGetEEACOutputRatedVolt() * wInvTempDeratePer / 100);

		if(wInvTempDeratVoltLimit < uwGetInvDeratingVolt())
 		{
 			wInvTempDeratVoltLimit = uwGetInvDeratingVolt();
		}

		if(wInvTempDeratVoltLimit >= suwGetEEACOutputRatedVolt())
		{
			wInvTempDeratVoltLimit = suwGetEEACOutputRatedVolt();
		}
	}

	if(wInvTempDeratePer != 100)
	{
		fSysDeratingStatus.bits.bInvTempDerate = true;
	}
	else
	{
		fSysDeratingStatus.bits.bInvTempDerate = false;
	}
}

void	sTwTempDerating(void)
{
	INT16U g_wHsTempDeratePerTemp;
	INT16S wTemp;

	// wTemp = swGetHsTwTempFilter();	// 推挽当前温度
	wTemp = swGetLLCTempFilter();
    if(wTemp < 0)
    {
        wTemp = 0;
    }
	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		g_wHsTempDeratePerTemp = 10;
	}
	else								
	{										
		g_wHsTempDeratePerTemp = 82;
	}
	
	if(wTemp <= uwTwTempStartDerat)	
	{
		wTwTempDeratePer = 100;
	}
	else if(wTemp > uwTwTempEndDerat)	
	{
		wTwTempDeratePer = g_wHsTempDeratePerTemp;
	}
	else
	{
		wTwTempDeratePer = g_wHsTempDeratePerTemp + (uwTwTempEndDerat - wTemp)\
							* (100 - g_wHsTempDeratePerTemp)/ (uwTwTempEndDerat - uwTwTempStartDerat);
	}

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		wTwTempDeratPowerLimit = (INT16S)((INT32S)sGetRatedGridPower() * wTwTempDeratePer / 100);
	}
	else
	{										
		wTwTempDeratVoltLimit = (INT16S)((INT32S)suwGetEEACOutputRatedVolt() * wTwTempDeratePer / 100);

		if(wTwTempDeratVoltLimit < uwGetInvDeratingVolt())
 		{
 			wTwTempDeratVoltLimit = uwGetInvDeratingVolt();
		}

		if(wTwTempDeratVoltLimit >= suwGetEEACOutputRatedVolt())
		{
			wTwTempDeratVoltLimit = suwGetEEACOutputRatedVolt();
		}
	}

	if(wTwTempDeratePer != 100)
	{
		fSysDeratingStatus.bits.bTwTempDerate = true;
	}
	else
	{
		fSysDeratingStatus.bits.bTwTempDerate = false;
	}
}

void	sTraTempDerating(void)
{
	INT16U g_wHsTempDeratePerTemp;
	INT16S wTemp;

	wTemp = 0;//swGetHsTraTempFilter();	// 推挽变压器当前温度

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		g_wHsTempDeratePerTemp = 10;
	}
	else								
	{										
		g_wHsTempDeratePerTemp = 82;
	}

	if(wTemp <= uwTraTempStartDerat)	
	{
		wTraTempDeratePer = 100;
	}
	else if(wTemp > uwTraTempEndDerat)	
	{
		wTraTempDeratePer = g_wHsTempDeratePerTemp;
	}
	else
	{
		wTraTempDeratePer = g_wHsTempDeratePerTemp + (uwTraTempEndDerat - wTemp)\
							* (100 - g_wHsTempDeratePerTemp)/ (uwTraTempEndDerat - uwTraTempStartDerat);
	}

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		wTraTempDeratPowerLimit = (INT16S)((INT32S)sGetRatedGridPower() * wTraTempDeratePer / 100);
	}
	else
	{										
		wTraTempDeratVoltLimit = (INT16S)((INT32S)suwGetEEACOutputRatedVolt() * wTraTempDeratePer / 100);

		if(wTraTempDeratVoltLimit < uwGetInvDeratingVolt())
 		{
 			wTraTempDeratVoltLimit = uwGetInvDeratingVolt();
		}

		if(wTraTempDeratVoltLimit >= suwGetEEACOutputRatedVolt())
		{
			wTraTempDeratVoltLimit = suwGetEEACOutputRatedVolt();
		}
	}

	if(wTraTempDeratePer != 100)
	{
		fSysDeratingStatus.bits.bTraTempDerate = true;
	}
	else
	{
		fSysDeratingStatus.bits.bTraTempDerate = false;
	}
}

void	sPvTempDerating(void)
{
	INT16U g_wHsTempDeratePerTemp;
	INT16S wTemp;

	wTemp = swGetHsPvTempFilter();	// PV散热器当前温度
    if(wTemp < 0)
    {
        wTemp = 0;
    }
								
	g_wHsTempDeratePerTemp = 58;	// 60A * 0.58 ≈ 34.8A

	if(wTemp <= uwPvTempStartDerat)	
	{
		wPvTempDeratePer = 100;
	}
	else if(wTemp > uwPvTempEndDerat)	
	{
		wPvTempDeratePer = g_wHsTempDeratePerTemp;
	}
	else
	{
		wPvTempDeratePer = g_wHsTempDeratePerTemp + (uwPvTempEndDerat - wTemp)\
							* (100 - g_wHsTempDeratePerTemp)/ (uwPvTempEndDerat - uwPvTempStartDerat);
	}
									
	wPvTempDeratCurrLimit = (INT16S)((INT32S)cMpptBatCurrMax * wPvTempDeratePer / 100);

	if(wPvTempDeratCurrLimit < cMpptBatCurr35A)
	{
			wPvTempDeratCurrLimit = cMpptBatCurr35A;
	}

	if(wPvTempDeratCurrLimit >= cMpptBatCurrMax)//suwGetEEACOutputRatedVolt())
	{
		wPvTempDeratCurrLimit = cMpptBatCurrMax;//suwGetEEACOutputRatedVolt();
	}

	if(wPvTempDeratePer != 100)
	{
		fSysDeratingStatus.bits.bPvTempDerate = true;
	}
	else
	{
		fSysDeratingStatus.bits.bPvTempDerate = false;
	}
}

void	sBatDerating(void)
{
	INT16U g_wBatDeratePerTemp;
	static INT16U uwBatDeratROpVoltTemp = 0;
	static INT16U uwBatDeratROpVoltCnt = 0;
	INT16S wTemp;

//	if(suwGetEEBatUnderVoltDeratingEnable() == false)
//	{
//		return;
//	}
	if(swGetWorkMode() <= cPowerOnMode)
	{
		return;
	}

	wTemp = swGetBatVoltNew();	// 当前电池电压
	
	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		g_wBatDeratePerTemp = 10;
	}
	else
	{
		if(swGetTurobMode() == true) 
		{
			g_wBatDeratePerTemp = 52;
		}
		else
		{
			g_wBatDeratePerTemp = 82;
		}
	}
	
	if(wTemp >= cBatVoltStartDerat * uwGetBatSerialPcs())
	{
		g_wBatDeratePer = 100;
	}
	else if(wTemp <= cBatVoltEndDerat * uwGetBatSerialPcs())
	{
		g_wBatDeratePer = g_wBatDeratePerTemp;
	}
	else
	{
		g_wBatDeratePer = g_wBatDeratePerTemp + (wTemp - cBatVoltEndDerat * uwGetBatSerialPcs())\
						* (100 - g_wBatDeratePerTemp) / (cBatVoltStartDerat * uwGetBatSerialPcs() - cBatVoltEndDerat * uwGetBatSerialPcs());
	}

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		wTemp = (INT16S)((INT32S)suwGetEEBatMaxDcgCurr() * g_wBatDeratePer / 100);	// 电流
		wBatVoltDeratPowerLimit = (INT16S)((INT32S)wTemp * swGetBatVoltNew() / 1000);
		if(wBatVoltDeratPowerLimit > uwGetInvWattMax())
		{
			wBatVoltDeratPowerLimit = uwGetInvWattMax();
		}
//		wBatVoltDeratPowerLimit = (INT16S)((INT32S)sGetRatedGridPower() * g_wBatDeratePer / 100);
	}
	else
	{
		uwBatDeratROpVoltTemp = (INT16S)((INT32S)uwGetOPRMSRatedVolt() * g_wBatDeratePer / 100);

		if(swGetOPWattPercent() <= 20)	// 负载在20以内时不降额
		{
			uwBatDeratROpVoltTemp = suwGetEEACOutputRatedVolt();
		}

		// 增加软起，减缓功率波动
 		if(wBatVoltDeratVoltLimit > uwBatDeratROpVoltTemp)
		{
			wBatVoltDeratVoltLimit -= 1;
			uwBatDeratROpVoltCnt = 0;
		}
		else if(wBatVoltDeratVoltLimit < uwBatDeratROpVoltTemp)
		{
			if(++uwBatDeratROpVoltCnt > 10)	// 100ms	1V/s
			{
				uwBatDeratROpVoltCnt = 0;
				wBatVoltDeratVoltLimit += 1;
			}
		}
		else
		{
			wBatVoltDeratVoltLimit = uwBatDeratROpVoltTemp;
			uwBatDeratROpVoltCnt = 0;
		}
		
//		if(swGetTurobMode() == true)
//		{
//			if(wBatVoltDeratVoltLimit < cAcVoltReal120V)
//	 		{
//	 			wBatVoltDeratVoltLimit = cAcVoltReal120V;
//			}
//		}
//		else	// UPS
//		{
			if(wBatVoltDeratVoltLimit < uwGetInvDeratingVolt())
	 		{
	 			wBatVoltDeratVoltLimit = uwGetInvDeratingVolt();
			}
//		}

		if(wBatVoltDeratVoltLimit >= suwGetEEACOutputRatedVolt())
		{
			wBatVoltDeratVoltLimit = suwGetEEACOutputRatedVolt();
		}
	}

	if((g_wBatDeratePer != 100) && (((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus) \
		|| ((swGetWorkMode() == cBatteryMode) && suwGetFBInvCtrlSts() == cFBInvCtrlVolt)))
	{
		fSysDeratingStatus.bits.bBatVoltDerate = true;
		T_ALARM_DATA.bits.bBAT_UT = true;
	}
	else
	{
		fSysDeratingStatus.bits.bBatVoltDerate = false;
		T_ALARM_DATA.bits.bBAT_UT = false;
	}
}

void	sLineDerating(void)
{
	INT16U g_wLineDeratePerTemp;
	INT16S wTemp;
	wTemp = swGetRLineVoltNew();

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		g_wLineDeratePerTemp = 10;
	}
//	else
//	{
//		if(swGetTurobMode() == true) 
//		{
//			g_wLineDeratePerTemp = 52;
//		}
//		else
//		{
//			g_wLineDeratePerTemp = 82;
//		}
//	}

	if(wTemp >= cLineVoltStartDerat)	
	{
		g_wLineDeratePerTemp = 100;
	}
	else if(wTemp < cLineVoltEndDerat)	
	{
		g_wLineDeratePer = g_wLineDeratePerTemp;
	}
	else
	{
		g_wLineDeratePer = g_wLineDeratePerTemp + (wTemp - cLineVoltEndDerat)\
							* (100 - g_wLineDeratePerTemp)/(cLineVoltStartDerat - cLineVoltEndDerat);
	}

	if((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus)
	{
		if(swGetBatCurrNew() > 0)
		{
			wTemp = (INT16S)((INT32S)swGetBatCurrNew() * g_wLineDeratePer / 100);	// 电流
		}
		else
		{
			wTemp = (INT16S)((INT32S)swGetBatCurrNew() * g_wLineDeratePer / 100);	// 电流
			wTemp = - wTemp;
		}
		wLineVoltDeratPowerLimit = (INT16S)((INT32S)wTemp * swGetBatVoltNew() / 100);
		if(wLineVoltDeratPowerLimit > uwGetInvWattMax())
		{
			wLineVoltDeratPowerLimit = uwGetInvWattMax();
		}
	}
	
	if((g_wLineDeratePer != 100) && ((swGetWorkMode() == cLineMode) && suwGetFBInvCtrlSts() == cFBInvCtrlBus))
	{
		fSysDeratingStatus.bits.bLineVoltDerate = true;
	}
	else
	{
		fSysDeratingStatus.bits.bLineVoltDerate = false;
	}
}
extern INT16S g_wBatChgCurrLimit;			// 系统最大充电电流 0.01A
extern INT16S g_wBatDsgCurrLimit;			// 系统最大放电电流 0.01A
extern INT16S g_wBatSOCReal;				// 电池SOC
INT16S sOutputVoltDrtProc(INT16S wOutputVoltRated)
{
	INT16S wMaxDisCurr;
	INT16S wDisCurrAvg;
	
	static INT16S s_wOPVoltTempDerate = 0;
	static INT16S g_wOPVolt = 0;
	static INT16S g_wOPVoltCnt = 0;
	INT16S g_wOPVoltDereByTemp	= 0; 

	s_wOPVoltTempDerate = suwGetEEACOutputRatedVolt();
	g_wOPVoltDereByTemp	= suwGetEEACOutputRatedVolt();
	
	if(swGetWorkMode() == cBatteryMode)// 离网降电压 // 必须在电池模式
	{
		wDisCurrAvg = swGetBatCurrNew();					// 电池放电电流		// 0.01A
		if(wDisCurrAvg < 0)
		{
			wDisCurrAvg = -wDisCurrAvg;
		}
		g_wOPVoltDereByTemp = wTempDeratVoltNew;			// 温度降额、过压降额等降额值

		wMaxDisCurr = g_wBatDsgCurrLimit;					// 最大放电电流		// 0.01A //无通讯时是设置项决定，有通讯时是BMS传过来
		if(wMaxDisCurr > uwGetSettingMaxDchgCurr()/10)					// 系统额定最大放电电流
		{
			wMaxDisCurr = uwGetSettingMaxDchgCurr()/10;
		}

		// 软起，减缓功率波动
		if(wDisCurrAvg > wMaxDisCurr)					// 电流超了就降负载电压			// 离网只有放电
		{
			g_wOPVolt -= 1;
			g_wOPVoltCnt = 0;
		}
		else if((wDisCurrAvg - 0) < wMaxDisCurr)		// 没超就加回来
		{
			if(++g_wOPVoltCnt > 10)						// 100ms	1V/s
			{
				g_wOPVoltCnt = 0;
				g_wOPVolt += 1;
			}
		}
		
//		if(wDisCurrAvg < -wMaxDisCurr)					// 电流超了就降负载电压
//		{
//			g_wOPVolt -= 10;
//		}
//		else if((wDisCurrAvg - 20) > -wMaxDisCurr)		// 没超就加回来
//		{
//			g_wOPVolt += 10;
//		}

		if(g_wOPVolt > g_wOPVoltDereByTemp)	// 不能大于额定（2300）
		{
			g_wOPVolt = g_wOPVoltDereByTemp;
		}

		if(g_wOPVoltDereByTemp < s_wOPVoltTempDerate)//g_wOPVoltDereByTemp降额后的负载电压如果比额定小，那么额定也要跟随上
		{
			s_wOPVoltTempDerate -= 5;
		}
		else if(g_wOPVoltDereByTemp > s_wOPVoltTempDerate)//g_wOPVoltDereByTemp降额后的负载电压如果比额定大，那么额定也要跟随上 
		{
			s_wOPVoltTempDerate += 5;
		}

		if(s_wOPVoltTempDerate < g_wOPVolt)
		{
			g_wOPVolt = s_wOPVoltTempDerate;
		}
		
//		if(swGetTurobMode() == true)	// 小于额定就限制在下限电压值	// Turbo模式能使能表示一定在APL模式
		if(suwGetEEGridInputRange() == cAPL)	// APL
		{
			if(g_wOPVolt < cAcVoltReal190V)
	 		{
	 			g_wOPVolt = cAcVoltReal190V;
			}
		}
		else	// UPS
		{
			if(g_wOPVolt < cAcVoltReal190V)
	 		{
	 			g_wOPVolt = cAcVoltReal190V;
			}
		}
		
		if(g_wOPVolt > wOutputVoltRated)				// 大于额定就限制在额定电压
		{
			g_wOPVolt = wOutputVoltRated;
		}
		else if((g_wOPVolt + 400) < wOutputVoltRated) 	// 离目标值差距有点大，调节快一点
		{
			g_wOPVolt = wOutputVoltRated - 400;
		}

	}
	else
	{
		wOutputVoltRated = wTempDeratVoltNew;
		g_wOPVolt = wOutputVoltRated;					// 默认额定电压（2300）
		s_wOPVoltTempDerate = wOutputVoltRated;
	}
	wBatCurrDeratVoltLimit = g_wOPVolt;
	return(g_wOPVolt);
}

INT16S  swDeratOutAdj(void)
{
	INT16S	wDeratROpVolt = 0;

	if(wInvTempDeratVoltLimit < wTwTempDeratVoltLimit)
	{
		wDeratROpVolt = wInvTempDeratVoltLimit;
	}
	else if(wTwTempDeratVoltLimit < wBatVoltDeratVoltLimit)
	{
		wDeratROpVolt = wTwTempDeratVoltLimit;
	}
	else
	{
		wDeratROpVolt = wBatVoltDeratVoltLimit;
	}

	return wDeratROpVolt;
}


INT16S  swDeratPvCurrAdj(void)
{
	INT16S	wDeratPvCurr = 0;

	wDeratPvCurr = wPvTempDeratCurrLimit;

	return wDeratPvCurr;
}



// PV过温检测
INT16S	wTTemp = 0;
void	sPvTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = swGetHsPvTempFilter();
	
	if(uwCircirtTempOver || T_ALARM_DATA.bits.bPv1OTAlarm)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwPvTempEndDerat - cHsTemp10C, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_ALARM_DATA.bits.bPv1OTAlarm = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwPvTempEndDerat + cHsTemp01C, wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_ALARM_DATA.bits.bPv1OTAlarm = true;
//		sSetFaultCode(cPVCircirtTempOver);
	}
}

// 逆变过温检测 	
void	sInvOverTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = swGetHsInvTempFilter();
	
	if(uwCircirtTempOver || T_FAULT_DATA.bits.bInvHsOT || T_FAULT_DATA.bits.bInvHsNTCLoss)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwInvTempEndDerat - cHsTemp10C, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_FAULT_DATA.bits.bInvHsOT = false;
			T_FAULT_DATA.bits.bInvHsNTCLoss = false;	// 逆变散热器NTC未接故障同步恢复
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwInvTempEndDerat + cHsTemp01C, wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_FAULT_DATA.bits.bInvHsOT = true;
		sSetFaultCode(cInvCircirtTempOver);
	}
}

// 推挽过温检测
void	sTwTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = swGetLLCTempFilter();
	
	if(uwCircirtTempOver || T_FAULT_DATA.bits.bLlcLowSideOT)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwTwTempEndDerat - cHsTemp10C, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_FAULT_DATA.bits.bLlcLowSideOT = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwTwTempEndDerat + cHsTemp01C, wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_FAULT_DATA.bits.bLlcLowSideOT = true;
		sSetFaultCode(cLLCLPTempOver);
	}
}

// 推挽变压器过温检测
void	sTwTraTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = 0;//swGetHsTraTempFilter();
	
	if(uwCircirtTempOver || T_FAULT_DATA.bits.bLlcTXOT)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwTraTempEndDerat - cHsTemp10C, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_FAULT_DATA.bits.bLlcTXOT = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwTraTempEndDerat + cHsTemp01C, wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_FAULT_DATA.bits.bLlcTXOT = true;
		sSetFaultCode(cLLCTraTempOver);
	}
}

// 电池正NTC过温检测
void	sBatHTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = swGetBat1TempFilter();
	
	if(uwCircirtTempOver || T_FAULT_DATA.bits.bBatHOT)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwGetBatHNtcTempOver()-100, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_FAULT_DATA.bits.bBatHOT = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwGetBatHNtcTempOver(), wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_FAULT_DATA.bits.bBatHOT = true;
		sSetFaultCode(cBatHNtcConnect);
	}
}

// 电池负NTC过温检测
void	sBatLTempChk(INT16U wFilter1, INT16U wFilter2)
{
	static INT16U s_uwHsTempHighCnt = 0;
	INT16S wHsTemp;
	INT16U uwCircirtTempOver = false;
	
	wHsTemp = swGetBat2TempFilter();
	
	if(uwCircirtTempOver || T_FAULT_DATA.bits.bBatLOT)
	{
		if(sb16UUnderLevelChk(wHsTemp, uwGetBatLNtcTempOver()-100, wFilter2, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = false;
			T_FAULT_DATA.bits.bBatLOT = false;
		}
	}
	else
	{
		if(sb16UOverLevelChk(wHsTemp, uwGetBatLNtcTempOver(), wFilter1, &s_uwHsTempHighCnt))
		{
			uwCircirtTempOver = true;
		}
	}

	if(uwCircirtTempOver)
	{
		T_FAULT_DATA.bits.bBatLOT = true;
		sSetFaultCode(cBatLNtcConnect);
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	suwGetSysDeratingStatus(void)							// 系统降额状态标识
{
	return fSysDeratingStatus.data;
}

INT16U	suwGetSysDerateEn(void)									// 降额使能
{
	return fSysDeratingStatus.bits.DerateEn;
}


INT16S	swGetInvTempDeratVoltLimit(void)						// 逆变温度降额值
{
	return wInvTempDeratVoltLimit;
}

INT16S	swGetTwTempDeratVoltLimit(void)							// 推挽温度降额值
{
	return wTwTempDeratVoltLimit;
}

INT16S	swGetTraTempDeratVoltLimit(void)						// 推挽变压器温度降额值
{
	return wTraTempDeratVoltLimit;
}

INT16S	swGetTempDeratVoltNew(void)								// 温度降额输出电压
{
	return wTempDeratVoltNew;
}

INT16S	swGetTempDeratPvBatCurrNew(void)						// PV降额输出电流
{
	return wTempDeratPvBatCurrNew;
}


INT16S	swGetTempDeratVoltFilter(void)							// 温度降额输出电压
{
	return wTempDeratVoltFilter;
}

INT16S	swGetTempDeratPvBatCurrFilter(void)						// PV降额输出电流
{
	return wTempDeratPvBatCurrFilter;
}

INT16S	swGetBatVoltDeratVoltLimit(void)						// 电池欠压降额输出电压
{
	return wBatVoltDeratVoltLimit;
}

INT16S	swGetBatCurrDeratVoltLimit(void)						// BAT限流降额负载电压
{
	return wBatCurrDeratVoltLimit;
}

INT16S	swGetInvTempDeratPowerLimit(void)						// 逆变温度降额功率
{
	return wInvTempDeratPowerLimit;
}

INT16S	swGetTwTempDeratPowerLimit(void)						// 推挽温度降额功率
{
	return wTwTempDeratPowerLimit;
}

INT16S	swGetTraTempDeratPowerLimit(void)						// 推挽变压器温度降额功率
{
	return wTraTempDeratPowerLimit;
}


INT16S	swGetBatVoltDeratPowerLimit(void)						// 电池低压降并网功率
{
	return wBatVoltDeratPowerLimit;
}
INT16S	swGetLineVoltDeratPowerLimit(void)						
{
	return wLineVoltDeratPowerLimit;
}
/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetSysDerateEn(INT16U	DerateEn)						// 降额使能设置
{
	fSysDeratingStatus.bits.DerateEn = DerateEn;
}

void	sSetTempDeratVoltNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wTempDeratVoltNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wTempDeratVoltNew + (INT32S)wTempDeratVoltFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wTempDeratVoltFilter = dwTemp >> 5;
}

void	sSetPvTempDeratCurrNew(INT16S wVolt)
{
	static INT16S s_wRes = 0;
	INT32S dwTemp;
	
	wTempDeratPvBatCurrNew = wVolt;
	
	// Fc=a/(2*PI*t)=(1/32)/2/3.1415927/0.02s=0.25Hz
	dwTemp = (INT32S)wTempDeratPvBatCurrNew + (INT32S)wTempDeratPvBatCurrFilter * 31 + (INT32S)s_wRes;
	s_wRes = dwTemp & 0x001F;
	wTempDeratPvBatCurrFilter = dwTemp >> 5;
}



