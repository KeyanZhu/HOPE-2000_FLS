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
#include 		"Soc_internal.h"

typedef struct {
	INT8U bTableL;
	INT8U bTableH;
	INT32S wFactor;
} T_FindIndex;

T_AvgFilter sCellVoltFilter;
T_AvgFilter sCurrentFilter;

T_SocData sSocData;


//采样滤波初始化
void AvgFilter_Init(T_AvgFilter *f)
{
    memset(f, 0, sizeof(T_AvgFilter));
}

//电压校准前检查
static INT8U sSocV_CaliCheck(void)
{
	static INT8U bBattModeLast = 0;
	
	if(sSocData.bEmptyFlag) //放空
	{
		sSocData.bVoltageCaliSoc = 0;
		sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
	    sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
		sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DHG;
		return 1;
	}
	else if(sSocData.bFullFlag) //满充
	{
		sSocData.bVoltageCaliSoc = 100;
		sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
    	sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
		sSocData.bVoltageCaliFlag = VOLTAGE_CALI_CHG;
		return 1;
	}
	
	//电池状态转换进入一次
	if(sSocData.bBattMode != bBattModeLast)
	{
		bBattModeLast = sSocData.bBattMode;
		return 0;
	}
	
	//充放电状态检查 2A
    if(sSocData.wCurrent < 20)
    {
		sSocData.bVoltageCaliSoc = 0;
		sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
		sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
		sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DISABLE;
        return 1;
    }
	
	//校准点判断
	if(sSocData.bBattMode == BATT_MODE_CHG)
	{
		if((sSocData.bNowSoc < sSocConfig.bChgStartSoc) && (sSocData.wCellVoltage < sSocData.wSocTableFind[sSocConfig.bChgStartSoc - sSocData.bBaseSoc]))
		{
			sSocData.bVoltageCaliSoc = 0;//重新校准
			sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
			sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DISABLE;
			return 1;
		}
	}
	else
	{
		if((sSocData.bNowSoc > sSocConfig.bDhgStartSoc) && (sSocData.wCellVoltage > sSocData.wSocTableFind[sSocConfig.bDhgStartSoc]))
		{
			sSocData.bVoltageCaliSoc = 100;//重新校准
			sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
			sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DISABLE;
			return 1;
		}
	}
	
	return 0;
}

//采样滤波
INT16S AvgFilter_Update(T_AvgFilter *f, INT16U sample)
{
    if (f->count >= OCV_SAMPLE_COUNT)
    {
        f->sum -= f->buffer[f->index];
    }

    f->buffer[f->index] = sample;
    f->sum += sample;

    f->index++;
    if (f->index >= OCV_SAMPLE_COUNT)
    {
        f->index = 0;
    }

    if (f->count < OCV_SAMPLE_COUNT)
    {
        f->count++;
    }

    return (INT16S)(f->sum / f->count);
}

//插值索引及因子查找
static T_FindIndex sSocV_FindIndex(INT16S wValue, INT16S *bList, INT8U bListMax)
{
	INT8U i = 0, bIndex = 0;
	INT16S tempSpan = 0;//计算倍率因子用
	T_FindIndex sFindIndex;
	
	if(wValue <= bList[0])
	{
        bIndex = 0;// 小于等于最小温度
    }
	else if(wValue >= bList[bListMax - 1])
	{
        bIndex = bListMax - 1;// 大于等于最大温度
    }
	else
	{
        for(i = 1; i < bListMax; i++)
		{
	        if(wValue < bList[i])
			{
                bIndex = i - 1;  // 使用前一个索引
                break;
            }
		}
	}
    sFindIndex.bTableL = bIndex;
	if(bIndex >= bListMax - 1)
	{
        sFindIndex.bTableH = bIndex;
        sFindIndex.wFactor = 0;
    }
	else
	{
		sFindIndex.bTableH = bIndex + 1;
		
        tempSpan = bList[sFindIndex.bTableH] - bList[sFindIndex.bTableL];
		if(tempSpan > 0)
		{
            sFindIndex.wFactor = ((INT32S)(wValue - bList[sFindIndex.bTableL]) * sSocConfig.wInterpolationRate) / tempSpan;
            if(sFindIndex.wFactor < 0) sFindIndex.wFactor = 0;
            if(sFindIndex.wFactor > sSocConfig.wInterpolationRate) sFindIndex.wFactor = sSocConfig.wInterpolationRate;
        }
		else
		{
            sFindIndex.wFactor = 0;
        }
    }
	
	return sFindIndex;
}

//电压校准输出处理
static INT8U sSocV_EndProcess(INT8U VCaliSoc)
{
//	static INT8U bLastSoc = 0, bFirstFlg = 1;//防止SOC抖动用
//	
//	if(bFirstFlg)
//	{
//		bLastSoc = VCaliSoc;
//		bFirstFlg = 0;
//	}
//	if(sSocData.bBattMode == BATT_MODE_CHG)
//	{
//		if(VCaliSoc < bLastSoc)  VCaliSoc = bLastSoc;
//	}
//	else
//	{
//		if(VCaliSoc > bLastSoc)  VCaliSoc = bLastSoc;
//	}
//	bLastSoc = VCaliSoc;
	
	if(VCaliSoc == 0)
	{
		if(!sSocData.bEmptyFlag)   VCaliSoc = 1;
	}
	if(VCaliSoc >= 100)
	{
		if(!sSocData.bFullFlag)   VCaliSoc = 99;
	}
	
	return VCaliSoc;
}


//容量校准
void sSoc_MaxAh_Cali(void)
{
	const INT8S bLowTempValue[4] = {10,0,-10,-20};//低温值
	const INT8U bCapacityFactor[4] = {95,80,70,50};//容量衰减系数
	static INT8U bMaxAhFactor = 100;
	
	const INT16S wTempJumpValue = 0;//℃
	
	//if((bBmsMode == cPowerOnMode) || (bBmsMode == cStandbyMode))	// BMS
	if((swGetWorkMode() == cPowerOnMode) || (swGetWorkMode() == cStandbyMode))	// HOPE 20260312
    {
		return;
    }

	//温度过低判断
	if((sSocData.wCellTemplate <= wTempJumpValue) && (sSocData.bCapacityCaliFlag == CAPACITY_CALI_DISABLE))
	{
		sSocData.bCapacityCaliFlag = CAPACITY_CALI_ENABLE;
	}
	else if((sSocData.wCellTemplate >= bLowTempValue[0]) && (sSocData.bCapacityCaliFlag == CAPACITY_CALI_ENABLE))
	{
		sSocData.bCapacityCaliFlag = CAPACITY_CALI_DISABLE;
	}
	
	//AhMax衰减处理
	if(sSocData.bCapacityCaliFlag == CAPACITY_CALI_ENABLE)
	{
		//if(sbGetCellVoltLoAlm()) //低压告警 BMS
		if(T_ALARM_DATA.bits.bBatUVAlarm) //低压告警 HOPE 20260312
		{
			sSocData.bCapacityCaliSoc = 0;
			sSocData.wCapaCaliMaxCapacity = sSocData.wMaxCapacity * bMaxAhFactor;
			sSocData.wCapaCaliRealCapacity = sSocData.bCapacityCaliSoc * sSocData.wCapaCaliMaxCapacity / 100;
			return;
		}
		//else if(sbGetCellVoltHiAlm()) //过压告警
		else if(T_ALARM_DATA.bits.bBatOVAlarm) //过压告警 HOPE 20260312
		{
			sSocData.bCapacityCaliSoc = 100;
			sSocData.wCapaCaliMaxCapacity = sSocData.wMaxCapacity * bMaxAhFactor;
			sSocData.wCapaCaliRealCapacity = sSocData.bCapacityCaliSoc * sSocData.wCapaCaliMaxCapacity / 100;
			return;
		}
		
		for(INT8U i = 0; i < (sizeof(bLowTempValue) / sizeof(bLowTempValue[0])); i++)
		{
			if(sSocData.wCellTemplate >= bLowTempValue[i])
			{
				bMaxAhFactor = bCapacityFactor[i];
				break;
			}
		}
	}
	
	sSocData.bCapacityCaliSoc = sSocData.bNowSoc;
	sSocData.wCapaCaliMaxCapacity = sSocData.wMaxCapacity * bMaxAhFactor;
	sSocData.wCapaCaliRealCapacity = sSocData.bCapacityCaliSoc * sSocData.wCapaCaliMaxCapacity / 100;
	
	return;
}



//电压校准
void sSoc_OCV_Cali(void)
{
    INT8U i = 0;
	T_FindIndex sTableT = {0};
	T_FindIndex sTableC = {0};
    INT16U wVal_LT_LC, wVal_LT_HC, wVal_HT_LC, wVal_HT_HC;//四个角点的值
	INT32S dwVal_T_LC, dwVal_T_HC; 
	INT16U bVoltageCaliSocScale = 100;//SOC折算
    
    if(sSocV_CaliCheck())  return;
	
	sSocData.wCellVoltage = AvgFilter_Update(&sCellVoltFilter, sSocData.wCellVoltage);
	sSocData.wCurrent     = AvgFilter_Update(&sCurrentFilter, sSocData.wCurrent);

    sTableT = sSocV_FindIndex(sSocData.wCellTemplate, sSocData.bTempList, sSocData.bTempListNumMax);
	sTableC = sSocV_FindIndex(sSocData.wCurrent, sSocData.bCurrentList, sSocData.bCurrentListNumMax);
	
    for(i = 0; i < sSocData.bSocListNumMax; i++)
    {
		// 获取四个角点的OCV值
		if(sSocData.bBattMode == BATT_MODE_CHG)
		{
			wVal_LT_LC = cwChgOCVMap[sTableT.bTableL][sTableC.bTableL][i];
			wVal_LT_HC = cwChgOCVMap[sTableT.bTableL][sTableC.bTableH][i];
			wVal_HT_LC = cwChgOCVMap[sTableT.bTableH][sTableC.bTableL][i];
			wVal_HT_HC = cwChgOCVMap[sTableT.bTableH][sTableC.bTableH][i];
		}
		else
		{
			wVal_LT_LC = cwDhgOCVMap[sTableT.bTableL][sTableC.bTableL][i];
			wVal_LT_HC = cwDhgOCVMap[sTableT.bTableL][sTableC.bTableH][i];
			wVal_HT_LC = cwDhgOCVMap[sTableT.bTableH][sTableC.bTableL][i];
			wVal_HT_HC = cwDhgOCVMap[sTableT.bTableH][sTableC.bTableH][i];
		}
        
        // 在电流维度上插值（低温）
		dwVal_T_LC = (INT32S)wVal_LT_LC * sSocConfig.wInterpolationRate + ((INT32S)(wVal_LT_HC - wVal_LT_LC) * sTableC.wFactor);
        
        // 在电流维度上插值（高温）
        dwVal_T_HC = (INT32S)wVal_HT_LC * sSocConfig.wInterpolationRate + ((INT32S)(wVal_HT_HC - wVal_HT_LC) * sTableC.wFactor);
        
        // 在温度维度上插值，得到最终值
        INT32S finalValue = dwVal_T_LC + ((dwVal_T_HC - dwVal_T_LC) * sTableT.wFactor / sSocConfig.wInterpolationRate);
        
        // 转换回整数
        sSocData.wSocTableFind[i] = (INT16U)(finalValue / sSocConfig.wInterpolationRate);
    }

	if(sSocData.wCellVoltage <= sSocData.wSocTableFind[0])
	{
		if(sSocData.bBattMode == BATT_MODE_DHG)
		{
			sSocData.bVoltageCaliSoc = 0;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DHG;
		}
		else
		{
			sSocData.bVoltageCaliSoc = sSocConfig.bChgStartSoc;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_CHG;
		}
	}
	else if(sSocData.wCellVoltage >= sSocData.wSocTableFind[sSocData.bSocListNumMax - 1])
	{
		if(sSocData.bBattMode == BATT_MODE_CHG)
		{
			sSocData.bVoltageCaliSoc = 100;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_CHG;
		}
		else
		{
			sSocData.bVoltageCaliSoc = sSocConfig.bDhgStartSoc;
			sSocData.bVoltageCaliFlag = VOLTAGE_CALI_DHG;
		}
	}
	else
	{
		for(i = 0; i < sSocData.bSocListNumMax - 1; i++)
		{
			if(sSocData.wCellVoltage < sSocData.wSocTableFind[i])
			{
				sSocData.bVoltageCaliSoc = sSocData.bBaseSoc + i;
				sSocData.bVoltageCaliFlag = (sSocData.bBattMode == BATT_MODE_CHG) ? VOLTAGE_CALI_CHG : VOLTAGE_CALI_DHG;
				break;
			}
		}
	}

	if(sSocData.bBattMode == BATT_MODE_CHG)  bVoltageCaliSocScale = sSocData.bNowSoc;
	else                                     bVoltageCaliSocScale = 100 - sSocData.bNowSoc;
	sSocData.bVoltageCaliSoc = ((bVoltageCaliSocScale * sSocData.bVoltageCaliSoc) + ((100-bVoltageCaliSocScale) * sSocData.bNowSoc)) / 100;
	
	sSocData.bVoltageCaliSoc = sSocV_EndProcess(sSocData.bVoltageCaliSoc);//末端处理
	
	sSocData.wVoltCaliMaxCapacity = sSocData.wMaxCapacity;
	sSocData.wVoltCaliRealCapacity = sSocData.bVoltageCaliSoc * sSocData.wVoltCaliMaxCapacity / 100;
	
	return;
}


