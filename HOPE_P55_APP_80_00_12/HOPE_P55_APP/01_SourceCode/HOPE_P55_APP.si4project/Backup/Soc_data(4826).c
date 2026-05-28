/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		
File Name:		Soc_algo.c
Author:			ke
Date:			
Description:	None
********************************************************************************/
#define			__SOC_ALGO_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include		"Main.h"
#include 		"Soc_internal.h"


T_SocConfig sSocConfig = {0};
T_SocInput sSocInput = {0};

//校准模块初始化
void sSocCaliInit(void)
{
	AvgFilter_Init(&sCellVoltFilter);
	AvgFilter_Init(&sCurrentFilter);
	
	sSoc_Config();
}

//校准模块配置
void sSoc_Config(void)
{
	sSocConfig.bChgStartSoc = CHGOCV_SOCSTART;					  //充电校准起始SOC
	sSocConfig.bDhgStartSoc = DHGOCV_SOCSTART;					  //放电校准起始SOC
	sSocConfig.wInterpolationRate = INTERPOLATIONRATE;			  //插值计算精度
	
	sSocConfig.wFullSocVoltage = FULL_VOLTAGE;					  //满充电压
	sSocConfig.wFullSocCurrent = FULL_CURRENT;					  //满充电流
	sSocConfig.wFullSocDelay = FULL_DELAY;						  //满充延时
	
	sSocConfig.uFunction.wFuncFlags = 0;
	sSocConfig.uFunction.tBits.bFullFunc = 1;                    //判断总压满充功能
}

//输入参数
static INT8U sSoc_Input(void)
{
	sSocInput.wMaxCellVoltage = 3000;//swGetMaxCellVoltNew(); 	     //1mV
	sSocInput.wMinCellVoltage = 3000;//swGetMinCellVoltNew();  	 //1mV
	sSocInput.wMaxCellTemplate = 40;//swGetMaxCellTempNew();      //1℃
	sSocInput.wMinCellTemplate = 38;//swGetMinCellTempNew();      //1℃
	sSocInput.wCurrent = swGetBatCurrNew()*10; 		   		 //0.1A
	sSocInput.wBattVoltage = swGetBatVoltNew();				 //0.01V
	
	sSocInput.bNowSoc = swGetSocNew();                       //1%
	sSocInput.wRealCapacity = swGetSoxAhRealShow();		     //0.1Ah
	
	if(sSocInput.bCellNum != suwGetEEBatSeriesNum())
	{
		sSocInput.bCellNum = suwGetEEBatSeriesNum();	   		 //电芯串数
	}
	if(sSocInput.wRatedCapacity != suwGetEEBatCapacity())
	{
		sSocInput.wRatedCapacity = suwGetEEBatCapacity();	   	 //0.1Ah
	}
	if(sSocInput.wMaxCapacity != swGetSoxAhMax())
	{
		sSocInput.wMaxCapacity = swGetSoxAhMax();	     	 	//0.1Ah
	}
	
	if((sSocInput.wRatedCapacity == 0) || (sSocInput.wMaxCapacity == 0)) return 0;
	
	return 1;

}

//数据更新
void sSoc_Updata(void)
{
//	uint16_t wBmsStatusLow;
	int i = 0;

	if(!sSoc_Input()) return;
	
	if(sSocData.bCellNum != sSocInput.bCellNum)
	{
		sSocData.bCellNum = sSocInput.bCellNum;	   		 //电芯串数
	}
	if(sSocData.wMaxCapacity != sSocInput.wMaxCapacity)
	{
		sSocData.wMaxCapacity = sSocInput.wMaxCapacity;
	}
	if(sSocData.wRatedCapacity != sSocInput.wRatedCapacity)
	{
		sSocData.wRatedCapacity = sSocInput.wRatedCapacity;
	}
	
	//wBmsStatusLow = swGetBmsDataBmsStatusLow(sbGetSciAddress());	// 充放电状态检测
	//if(wBmsStatusLow & 0x2000) // 充电
	if(swGetBatCurrNew() < 0)	 // 充电	 // HOPE
	{
		sSocData.wCellVoltage = sSocInput.wMaxCellVoltage;
		sSocData.wCellTemplate = sSocInput.wMinCellTemplate;
		sSocData.wCurrent = abs(sSocInput.wCurrent);
		
		if(sSocData.bBattMode != BATT_MODE_CHG)
		{
			sSocData.bTempListNumMax = CHG_TEMP_LIST_MAXNUM;
			sSocData.bCurrentListNumMax = CHG_CURRENT_LIST_MAXNUM;
			sSocData.bSocListNumMax = CHG_SOC_LIST_MAXNUM;
			
			memset(sSocData.bTempList, 0, sizeof(sSocData.bTempList));
			memcpy(sSocData.bTempList, bChgTempList, sizeof(bChgTempList));
			//for (int i = 0; i < CHG_CURRENT_LIST_MAXNUM; i++) 	// BMS
			for (i = 0; i < CHG_CURRENT_LIST_MAXNUM; i++)
			{
				sSocData.bCurrentList[i] = 0;
				sSocData.bCurrentList[i] = bChgCurrentList[i] * sSocData.wRatedCapacity / 10;
			}
			
			AvgFilter_Init(&sCellVoltFilter);
			AvgFilter_Init(&sCurrentFilter);
		}
		sSocData.bBattMode = BATT_MODE_CHG;
	}
	else
	{
		sSocData.wCellVoltage = sSocInput.wMinCellVoltage;
		sSocData.wCellTemplate = sSocInput.wMinCellTemplate;
		sSocData.wCurrent = abs(sSocInput.wCurrent);
		
		if(sSocData.bBattMode != BATT_MODE_DHG)
		{
			sSocData.bTempListNumMax = DHG_TEMP_LIST_MAXNUM;
			sSocData.bCurrentListNumMax = DHG_CURRENT_LIST_MAXNUM;
			sSocData.bSocListNumMax = DHG_SOC_LIST_MAXNUM;
			
			memset(sSocData.bTempList, 0, sizeof(sSocData.bTempList));
			memcpy(sSocData.bTempList, bDhgTempList, sizeof(bDhgTempList));
			for (i = 0; i < DHG_CURRENT_LIST_MAXNUM; i++) 
			{
				sSocData.bCurrentList[i] = 0;
				sSocData.bCurrentList[i] = bDhgCurrentList[i] * sSocData.wRatedCapacity / 10;
			}
			
			AvgFilter_Init(&sCellVoltFilter);
			AvgFilter_Init(&sCurrentFilter);
		}
		sSocData.bBattMode = BATT_MODE_DHG;
	}
	
	if(sSocData.bBattMode == BATT_MODE_CHG) sSocData.bBaseSoc = 80;
	else 									sSocData.bBaseSoc = 0;
	
	sSocData.bNowSoc = sSocInput.bNowSoc;
	sSocData.wRealCapacity = sSocInput.wRealCapacity;
	sSocData.wBattVoltage = sSocInput.wBattVoltage;
	
	//if((bBmsMode == cPowerOnMode) || (bBmsMode == cStandbyMode))	// BMS
	if((swGetWorkMode() == cPowerOnMode) || (swGetWorkMode() == cStandbyMode))	// HOPE 20260312
	{
		sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DISABLE;
		sSocData.bCapacityCaliFlag = CAPACITY_CALI_DISABLE;
		
		sSocData.bVoltageCaliSoc = sSocInput.bNowSoc;
		sSocData.bCapacityCaliSoc = sSocInput.bNowSoc;
	}
}

//满充判断
void sFullSocCheck(void)
{
	static INT8U bFullCount = 0;
	
	if(sSocData.bFullFlag)
	{
		//if(!sbGetCellVoltHiAlm() && (sSocData.wBattVoltage < (sSocConfig.wFullSocVoltage * sSocData.bCellNum)))
		if(!(T_ALARM_DATA.bits.bBatOVAlarm) && (sSocData.wBattVoltage < (sSocConfig.wFullSocVoltage * sSocData.bCellNum)))
		{
			sSocData.bFullFlag = 0;
			bFullCount = 0;
			return;
		}
	}
	else
	{
		//if(sbGetCellVoltHiAlm())
		if(T_ALARM_DATA.bits.bBatOVAlarm)
		{
			sSocData.bFullFlag = 1;
			bFullCount = 0;
			return;
		}
		
		if(sSocConfig.uFunction.tBits.bFullFunc)
		{
			if((sSocData.wBattVoltage >= (sSocConfig.wFullSocVoltage * sSocData.bCellNum)) && (sSocData.wCurrent <= sSocConfig.wFullSocCurrent))
			{
				if(++bFullCount >= sSocConfig.wFullSocDelay)
				{
					sSocData.bFullFlag = 1;
					bFullCount = 0;
				}
				return;
			}
			bFullCount = 0;
		}
	}
}

//放空判断
void sEmptySocCheck(void)
{
	if(sSocData.bEmptyFlag)
	{
		//if(!sbGetCellVoltLoAlm())
		if(!T_ALARM_DATA.bits.bBatUVAlarm)
		{
			sSocData.bEmptyFlag = 0;
			return;
		}
	}
	else
	{
		//if(sbGetCellVoltLoAlm())
		if(T_ALARM_DATA.bits.bBatUVAlarm)
		{
			sSocData.bEmptyFlag = 1;
			return;
		}
	}

}

