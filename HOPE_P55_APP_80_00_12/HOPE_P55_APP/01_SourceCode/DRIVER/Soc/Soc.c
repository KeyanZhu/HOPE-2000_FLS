/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		
File Name:		Soc.c
Author:			ke
Date:			
Description:	None
********************************************************************************/
#define			__SOC_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include		"Main.h"
#include 		"Soc.h"
#include 		"Soc_internal.h"

#define         SOC_MODULE_VERSION       100       //SOC模块版本V1.00


T_SocOutput sSocOutput = {0};

//SOC校准模块入口
void swSocCalibration(void)
{
	sSoc_OCV_Cali();//校准SOC
	sSoc_MaxAh_Cali();//校准AhMax

	if(sSocData.bCapacityCaliFlag != CAPACITY_CALI_DISABLE)
	{
		sSocOutput.bCaliFlg = 2;//容量校准
	}
	else if(sSocData.bVoltageCaliFlag != VOLTAGE_CALI_DISABLE)
	{
		sSocOutput.bCaliFlg = 1;//电压校准
	}
	else
	{
		sSocOutput.bCaliFlg = 0;//未校准
	}

	switch (sSocOutput.bCaliFlg) {
		case 0:
			//不校准
			sSocOutput.bSoc = sSocData.bNowSoc;
			sSocOutput.wRealCapacity = sSocData.wRealCapacity;
			sSocOutput.wMaxCapacity = sSocData.wMaxCapacity;
			break;
		case 1:
			//电压校准
			sSocOutput.bSoc = sSocData.bVoltageCaliSoc;
			sSocOutput.wRealCapacity = sSocData.wVoltCaliRealCapacity;//输出使用
			sSocOutput.wMaxCapacity = sSocData.wVoltCaliMaxCapacity;
			break;
		case 2:
			//容量校准
			sSocOutput.bSoc = sSocData.bCapacityCaliSoc;
			sSocOutput.wRealCapacity = sSocData.wCapaCaliMaxCapacity;
			sSocOutput.wMaxCapacity = sSocData.wCapaCaliRealCapacity;//输出使用
			break;
		default:
			break;
	}
	
	return;
}



INT16S wCellCurr = 0;
void sSocMain(INT16U cT100msec)
{
	static INT8U bInitFlg = 0;
	static INT16U uwSocWriteCount = 0;

	wCellCurr = -(swGetBatCurrNew()*10);	// SOC需求0.1A电流精度
	
	if(bInitFlg == 0)
	{
		bInitFlg = 1;
		sSocCaliInit();			//SOC模块初始化
	}
	
	sSoc_Updata();				// 数据更新
	sFullSocCheck();			// 电池充满判定
	sEmptySocCheck();			// 电池放空判断
	swSocCalibration();			// 校准逻辑
	
	sSoxAhCalc(wCellCurr);						// 实际电流积分、固定电压校准点
	sSocEstimate(swGetAvgCellTempNew()/10);		// 温度衰减
	sSohEstimate();								// AhMax计算、SOH计算

	sSoxAhCalc_Show(wCellCurr);					// 显示电流积分计算
	sSocFilter_Show(cT100msec*5);				// SOC平滑显示

	if(uwSocWriteCount++ >= 100)				// 10S
	{
		uwSocWriteCount = 0;
		if((suwGetEEBattAhReal() != swGetSoxAhReal()) || (suwGetEEBattAhRealShow() != swGetSoxAhRealShow()))
		{
			sSetEEBattAhReal(swGetSoxAhReal());
			sSetEEBattAhRealShow(swGetSoxAhRealShow());
			sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
		}
	}
}

INT16S	sGetCellCurr(void)
{
	return wCellCurr;
}



