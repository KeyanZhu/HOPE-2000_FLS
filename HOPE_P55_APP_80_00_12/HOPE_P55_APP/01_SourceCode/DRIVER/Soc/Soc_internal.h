/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		
File Name:		Soc_internal.h
Author:			ke
Date:			
Description:	None
********************************************************************************/
#ifndef __SOC_INTERNAL_H__
#define __SOC_INTERNAL_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"
#include 		"Soc.h"


/*************************配置项********************************************************************************/
#define CHGOCV_SOCSTART             90      //充电校准起始SOC
#define DHGOCV_SOCSTART             20      //放电校准起始SOC

#define FULL_VOLTAGE                350     //满充电压10mV（×电芯数使用）3.5V
#define FULL_CURRENT                50      //满充电流0.1A
#define FULL_DELAY                  600     //满充延时100ms

#define OCV_SAMPLE_COUNT            30      //OCV采样次数
#define INTERPOLATIONRATE           10000   //插值计算倍率

#define CHG_TEMP_LIST_MAXNUM        5
#define CHG_CURRENT_LIST_MAXNUM     4
#define CHG_SOC_LIST_MAXNUM         21
extern INT16S bChgTempList[CHG_TEMP_LIST_MAXNUM];//℃
extern INT16S bChgCurrentList[CHG_CURRENT_LIST_MAXNUM];//0.1C
extern const INT16U cwChgOCVMap[CHG_TEMP_LIST_MAXNUM][CHG_CURRENT_LIST_MAXNUM][CHG_SOC_LIST_MAXNUM];

#define DHG_TEMP_LIST_MAXNUM        6
#define DHG_CURRENT_LIST_MAXNUM     4
#define DHG_SOC_LIST_MAXNUM         31
extern INT16S bDhgTempList[DHG_TEMP_LIST_MAXNUM];//℃
extern INT16S bDhgCurrentList[DHG_CURRENT_LIST_MAXNUM];//0.1C
extern const INT16U cwDhgOCVMap[DHG_TEMP_LIST_MAXNUM][DHG_CURRENT_LIST_MAXNUM][DHG_SOC_LIST_MAXNUM];
/***************************************************************************************************************/


/**********************************内部使用*********************************************/
//电池模式
#define BATT_MODE_CHG               1       //充电
#define BATT_MODE_DHG               2       //放电

//电压校准，容量校准
#define VOLTAGE_CALI_DISABLE        0       //未校准
#define VOLTAGE_CALI_CHG            1       //充电校准
#define VOLTAGE_CALI_DHG            2       //放电校准
#define CAPACITY_CALI_DISABLE       0       //未校准
#define CAPACITY_CALI_ENABLE        1       //容量校准
/***************************************************************************************/

typedef struct
{
    INT16U buffer[OCV_SAMPLE_COUNT];
    INT16U index;
    INT16U count;
    INT32U sum;
} T_AvgFilter;

typedef struct
{
	INT8U bNowSoc;                //1%
	INT8U bCellNum;               //电芯串数
	
	INT16U wRealCapacity;         //10mAh
	INT16U wMaxCapacity;          //10mAh
	INT16U wRatedCapacity;        //10mAh
	
	INT16U wMaxCellVoltage;       //1mV
	INT16U wMinCellVoltage;       //1mV
	
	INT16S wMaxCellTemplate;      //0.1℃
	INT16S wMinCellTemplate;      //0.1℃

	INT16S wCurrent;              //1mA
	INT16S wBattVoltage;          //0.01V
}T_SocInput;

typedef struct
{
	INT8U bChgStartSoc;			 //充电校准起始SOC
	INT8U bDhgStartSoc;			 //放电校准起始SOC
	
	INT16U wFullSocVoltage;      //10mV
	INT16U wFullSocCurrent;		 //0.1A
	INT16U wFullSocDelay;		 //100ms
	
	INT16U wInterpolationRate;   //插值计算倍率
	
	union {
        INT16U wFuncFlags;					 //功能项
        struct {
            INT16U bFullFunc        : 1;	 //总压满充判断功能
            INT16U bEnableFuncRecv  : 15;
        } tBits;
    } uFunction;
}T_SocConfig;


typedef struct 
{
	INT8U  bBattMode;             //电池模式   1：充电      2：放电
	INT8U  bFullFlag;		      //满充标志
	INT8U  bEmptyFlag;		      //放空标志
	INT8U  bBaseSoc;              //OCV表起始SOC值
	
	INT8U  bSocListNumMax;
	INT8U  bTempListNumMax;
	INT8U  bCurrentListNumMax;
	INT16S  bCurrentList[5];
	INT16S  bTempList[6];
	
	INT8U  bCellNum;                //电芯串数
	INT8U  bNowSoc;                 //当前SOC
	INT16U wRealCapacity;			//实际容量
	INT16U wMaxCapacity;            //实际MaxAh
	
	INT8U  bVoltageCaliFlag;        //电压校准标志   0：未校准  1：充电校准  2：放电校准
	INT8U  bVoltageCaliSoc;         //电压校准SOC
	INT16U wVoltCaliMaxCapacity;    //电压校准最大容量
	INT16U wVoltCaliRealCapacity;   //电压校准实际容量
	
	INT8U  bCapacityCaliFlag;       //容量校准标志   0：未校准  1：校准
	INT8U  bCapacityCaliSoc;        //容量校准SOC
	INT16U wCapaCaliMaxCapacity;    //容量校准最大容量
	INT16U wCapaCaliRealCapacity;   //容量校准实际容量

	INT16U wRatedCapacity;          //10mAh标定容量
	
	INT16S wBattVoltage;            //0.01V
	INT16S wCellVoltage;            //1mv
	INT16S wCellTemplate;           //0.1℃
	INT16S wCurrent;                //1mA
	
	INT16U wSocTableFind[35];
}T_SocData;

extern T_AvgFilter sCellVoltFilter;
extern T_AvgFilter sCurrentFilter;

extern T_SocConfig sSocConfig;
extern T_SocData sSocData;


extern void sSocCaliInit(void);
extern void AvgFilter_Init(T_AvgFilter *f);
extern void sSoc_OCV_Cali(void);
extern void sSoc_MaxAh_Cali(void);
extern void sSoc_Config(void);
extern void sSoc_Updata(void);
extern void sFullSocCheck(void);
extern void sEmptySocCheck(void);



#endif	// __SOC_INTERNAL_H__
