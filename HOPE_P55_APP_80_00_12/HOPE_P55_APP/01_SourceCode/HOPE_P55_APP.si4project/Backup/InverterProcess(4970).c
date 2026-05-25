/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define	__INVERTER_PROCESS_C__

/********************************************************************************
* Include head files                                                            *
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
union INVERTER_REALTIME_DATA_TABLE strInverterRealtimeData;
union INVERTER_INFORMATION_DATA_TABLE strInverterInformationData;
union INVERTER_SWAP_MCU_DATA_TABLE strInverterSwapMcuData;
union WIFI_IOT_DATA_TABLE strWifiIotData;
union INV_PARAMETER_DATA_TABLE strInvParameterData;
union INV_POWER_CONVERSION_DATA_TABLE strInvPowerConversionData;
union BMS_WIFI_Bat_MeterStatus strBMSWIFIBatMeterStatus;


/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16U 	g_uwModelVar;
INT8U	bModelRsvd00;
INT8U	bModelRsvd01;
INT8U	bModelRsvd02;
INT8U	bModelRsvd03;
INT8U	bModelRsvd04;
INT8U	bModelRsvd05;
INT8U	bModelRsvd06;
INT8U	bModelRsvd07;
INT8U	bModelRsvd08;
INT8U	bModelRsvd09;
INT8U	bModelRsvd10;

INT16U 	g_uwBootBV = 0;
INT16U 	g_uwBootHV = 0;

extern INT16U g_uwRatedGridPower;
extern INT16S wConvertMaxWatt;
extern INT16S wConvertBatMaxWatt;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sInvParaUpdate(void);
void	sDspIapVer(void);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/

void	sInverterSetUpdate(void)
{
	OS_ENTER_CRITICAL();
//	sBatteryParaUpdate();
//	sInverterParaUpdate();
//	sOutputParaUpdate();
//	sLineParaUpdate();
	sInvLoadParaUpdate();	// 
	sDeratingProcInit();	// 降额部分参数初始化
	sDCDCParaInit();		// DCDC参数初始化
	OS_EXIT_CRITICAL();
}

void	sbInverterIdentifyInitial(void)
{
	g_uwModelVar = 0;
	bModelRsvd00 = 0;
	bModelRsvd01 = 0;
	bModelRsvd02 = 0;
	bModelRsvd03 = 0;
	bModelRsvd04 = 0;
	bModelRsvd05 = 0;
	bModelRsvd06 = 0;
	bModelRsvd07 = 0;
	bModelRsvd08 = 0;
	bModelRsvd09 = 0;
	bModelRsvd10 = 0;
	strBMSWIFIBatMeterStatus.wData = 0;
	memset(&strInvPowerConversionData, 0, sizeof(strInvPowerConversionData));
	memset(&strInvParameterData, 0, sizeof(strInvParameterData));
}

INT8U	sbInverterIdentify(INT8U bFilter)
{
	INT8U	bModelChkOk = false;
	INT16S	wModelValue;
	
	wModelValue = swVerVoltCal();//swGetHwVersion1Real();
	
#if(cMODEL_RSVD00_LO_LIMIT == 0)
	if(wModelValue <= cMODEL_RSVD00_UP_LIMIT)
#else
	if((wModelValue >= cMODEL_RSVD00_LO_LIMIT) && (wModelValue <= cMODEL_RSVD00_UP_LIMIT))
#endif
	{
		bModelRsvd00++;
	}
	else if((wModelValue >= cMODEL_RSVD01_LO_LIMIT) && (wModelValue <= cMODEL_RSVD01_UP_LIMIT))
	{
		bModelRsvd01++;
	}
	else if((wModelValue >= cMODEL_RSVD02_LO_LIMIT) && (wModelValue <= cMODEL_RSVD02_UP_LIMIT))
	{
		bModelRsvd02++;
	}
	else if((wModelValue >= cMODEL_RSVD03_LO_LIMIT) && (wModelValue <= cMODEL_RSVD03_UP_LIMIT))
	{
		bModelRsvd03++;
	}
	else if((wModelValue >= cMODEL_RSVD04_LO_LIMIT) && (wModelValue <= cMODEL_RSVD04_UP_LIMIT))
	{
		bModelRsvd04++;
	}
	else if((wModelValue >= cMODEL_RSVD05_LO_LIMIT) && (wModelValue <= cMODEL_RSVD05_UP_LIMIT))
	{
		bModelRsvd05++;
	}
	else if((wModelValue >= cMODEL_RSVD06_LO_LIMIT) && (wModelValue <= cMODEL_RSVD06_UP_LIMIT))
	{
		bModelRsvd06++;
	}
	else if((wModelValue >= cMODEL_RSVD07_LO_LIMIT) && (wModelValue <= cMODEL_RSVD07_UP_LIMIT))
	{
		bModelRsvd07++;
	}
	else if((wModelValue >= cMODEL_RSVD08_LO_LIMIT) && (wModelValue <= cMODEL_RSVD08_UP_LIMIT))
	{
		bModelRsvd08++;
	}
	else if((wModelValue >= cMODEL_RSVD09_LO_LIMIT) && (wModelValue <= cMODEL_RSVD09_UP_LIMIT))
	{
		bModelRsvd09++;
	}
	else if((wModelValue >= cMODEL_RSVD10_LO_LIMIT) && (wModelValue <= cMODEL_RSVD10_UP_LIMIT))
	{
		bModelRsvd10++;
	}
	else if(wModelValue >= cMODEL_RSVD10_UP_LIMIT)
	{
		bModelRsvd10++;
	}
	
	if(bModelRsvd00 >= bFilter)
	{
		g_uwModelVar = cCtrlHOPE1000;
		bModelChkOk = true;
	}
	else if(bModelRsvd01 >= bFilter)
	{
		g_uwModelVar = cCtrlHOPE2000;
		bModelChkOk = true;
	}
	else if(bModelRsvd02 >= bFilter)
	{
		g_uwModelVar = 3;
		bModelChkOk = true;
	}
	else if(bModelRsvd03 >= bFilter)
	{
		g_uwModelVar = 3;
		bModelChkOk = true;
	}
	else if(bModelRsvd04 >= bFilter)
	{
		g_uwModelVar = 4;
		bModelChkOk = true;
	}
	else if(bModelRsvd05 >= bFilter)
	{
		g_uwModelVar = 5;
		bModelChkOk = true;
	}
	else if(bModelRsvd06 >= bFilter)
	{
		g_uwModelVar = 6;
		bModelChkOk = true;
	}
	else if(bModelRsvd07 >= bFilter)
	{	
		g_uwModelVar = 7;
		bModelChkOk = true;
	}
	else if(bModelRsvd08 >= bFilter)
	{
		g_uwModelVar = 8;
		bModelChkOk = true;
	}
	else if(bModelRsvd09 >= bFilter)
	{	
		g_uwModelVar = 9;
		bModelChkOk = true;
	}
	else if(bModelRsvd10 >= bFilter)
	{
		g_uwModelVar = 10;
		bModelChkOk = true;
	}

	// for test
	g_uwModelVar = cCtrlHOPE2000;
	bModelChkOk = true;

	
	if(bModelChkOk == true)
	{
		sInvParaUpdate();
		sEepromDataVarRangeChk();
		sInverterSetUpdate();	// 根据机型，修改参数
		sBatteryInitial();		// 电池参数识别机型后重新初始化
		sInvWattResCal();		// 重新计算等效阻抗

		sDspIapVer();
		return true;
	}
	else
	{
		return false;
	}
}


void	sInvParaUpdate(void)
{
	if(g_uwModelVar == cCtrlHOPE1000)
	{
		// 基本信息
		strInvParameterData.Field.uwModelLV = false;							// LV机型使能
		strInvParameterData.Field.uwType = MACHINE_TYPE_HOPE;					// 设备大类
		strInvParameterData.Field.uwSubType = MACHINE_SUB_TYPE_HOPE1000;		// 设备子类
		strInvParameterData.Field.uwBatSerialPcs = 1;							// 电池节数 一节3.3V
		strInvParameterData.Field.uwTransformerRatio = cTransformerRatio64;		// DCDC LLC变压器变比
		strInvParameterData.Field.uwCTdirection = cReverse;						// OP电流采样CT方向
		strInvParameterData.Field.uwInvCurrRatio = 6876;						// 逆变电流采样系数
		strInvParameterData.Field.uwInvWattRes = 10580;							// = (2300 * 2300 / 500)
		
		// PV参数
		strInvParameterData.Field.uwMpptPvVoltMax = cMpptPvVolt55V;				// PV最高电压55V
		strInvParameterData.Field.uwPvPowerMax = 300;							// PV最大充电功率 300W
		strInvParameterData.Field.uwPvChgBatVoltRef = 350;						// PV充电电池电压参考 3.5V
		
		// 电池参数
		strInvParameterData.Field.uwSettingMaxChgCurr = 12000;					// 电池最大充电电流 120A
		strInvParameterData.Field.uwSettingMaxDcgCurr = 13500;					// 电池最大放电电流 135A
		strInvParameterData.Field.uwSettingMaxACChgCurr = 12000;				// 市电最大充电电流 120A
		strInvParameterData.Field.uwBusVoltOver1 = cBusVoltReal560V;			// Bus过压1 
		strInvParameterData.Field.uwBusVoltOver2 = cBusVoltReal570V;			// Bus过压2 
		strInvParameterData.Field.uwBusVoltOver3 = cBusVoltReal580V;			// Bus过压3 中断级
		strInvParameterData.Field.uwBusVoltLow1 = cBusVoltReal300V;				// Bus低压1 
		strInvParameterData.Field.uwDcDcPWMPeriod = cDCDCPeriod; 				// DcDc频率 33K = 120MHz/2/(1818)
		strInvParameterData.Field.uwDcDcPWMDutySet = 17;						// DcDc占空比 (1818/2-159)/1818 = 41.2%
		

		// 逆变参数
		strInvParameterData.Field.uwInvVAMax = 500;								// 额定视在功率
		strInvParameterData.Field.uwInvWattMax = 500;							// 额定有功功率		
		strInvParameterData.Field.uwInvRateVolt = cAcVoltReal230V;				// 逆变额定电压 230V		
		strInvParameterData.Field.uwInvDeratingVolt = cAcVoltReal150V;			// 逆变降额最低电压
		strInvParameterData.Field.uwInvFreeCntlCurrMax = 350;    				// 3.535A(500W*1.414/200V=3.535A)
		strInvParameterData.Field.uwInvVoltOver = cAcVoltReal280V;    			// 逆变输出过压值 280V
		strInvParameterData.Field.uwInvVoltOverBack = cAcVoltReal270V;    		// 逆变输出过压恢复值 270V
		strInvParameterData.Field.uwInvCurrOver = cInv05A;    					// 逆变输出过流值 25A
		strInvParameterData.Field.uwHsInvTempStartDerat = cHsTemp82C;			// 逆变散热器开始降额温度
		strInvParameterData.Field.uwHsInvTempEndDerat = cHsTemp87C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwHsTwTempStartDerat = cHsTemp75C;			// 推挽散热器开始降额温度
		strInvParameterData.Field.uwHsTwTempEndDerat = cHsTemp90C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwTraTempStartDerat = cHsTemp80C; 			// 推挽变压器温度开始降额温度
		strInvParameterData.Field.uwTraTempEndDerat = cHsTemp85C;				// 推挽变压器温度停止降额温度
		strInvParameterData.Field.uwPvTempStartDerat = cHsTemp72C;				// PV温度降额开始降额温度
		strInvParameterData.Field.uwPvTempEndDerat = cHsTemp77C;				// PV温度降额停止降额温度
		strInvParameterData.Field.uwBatHNtcTempOver = cHsTemp66C;				// 电池正端温度过高
		strInvParameterData.Field.uwBatLNtcTempOver = cHsTemp66C;				// 电池负端温度过高
		strInvParameterData.Field.uwMaxFanDutyInvWatt = 260;					// 风扇满转时的逆变功率 250W
		
		// 市电参数
		
		// 负载参数
		strInvParameterData.Field.uwLoadVoltOver = cAcVoltReal280V;					// 输出过压值	280V
		strInvParameterData.Field.uwLoadVoltLowAPL = cAcVoltReal90V;				// 输出低压值 APL 90V
		strInvParameterData.Field.uwLoadVoltLowUPS = cAcVoltReal170V;				// 输出低压值 UPS 170V
	}

	else if(g_uwModelVar == cCtrlHOPE2000)
	{
		// 基本信息
		strInvParameterData.Field.uwModelLV = false;							// LV机型使能
		strInvParameterData.Field.uwType = MACHINE_TYPE_HOPE;					// 设备大类
		strInvParameterData.Field.uwSubType = MACHINE_SUB_TYPE_HOPE2000;		// 设备子类
		strInvParameterData.Field.uwBatSerialPcs = 2;							// 电池节数 一节3.3V
		strInvParameterData.Field.uwTransformerRatio = cTransformerRatio64;		// DCDC LLC变压器变比
		strInvParameterData.Field.uwCTdirection = cReverse;						// OP电流采样CT方向
		strInvParameterData.Field.uwInvCurrRatio = 6876;						// 逆变电流采样系数
		strInvParameterData.Field.uwInvWattRes = 4840;							// = (2200 * 2200 / 500)
		
		// PV参数
		strInvParameterData.Field.uwMpptPvVoltMax = cMpptPvVolt55V;				// PV最高电压55V
		strInvParameterData.Field.uwPvPowerMax = 600;							// PV最大充电功率 300W
		strInvParameterData.Field.uwPvChgBatVoltRef = 700;						// PV充电电池电压参考 7.0V
		
		// 电池参数
		strInvParameterData.Field.uwSettingMaxChgCurr = 12000;					// 电池最大充电电流 120A
		strInvParameterData.Field.uwSettingMaxDcgCurr = 13500;					// 电池最大放电电流 135A
		strInvParameterData.Field.uwSettingMaxACChgCurr = 12000;				// 市电最大充电电流 120A
		strInvParameterData.Field.uwBusVoltOver1 = cBusVoltReal560V;			// Bus过压1 
		strInvParameterData.Field.uwBusVoltOver2 = cBusVoltReal570V;			// Bus过压2 
		strInvParameterData.Field.uwBusVoltOver3 = cBusVoltReal580V;			// Bus过压3 中断级
		strInvParameterData.Field.uwBusVoltLow1 = cBusVoltReal300V;				// Bus低压1 
		strInvParameterData.Field.uwDcDcPWMPeriod = cDCDCPeriod; 				// DcDc频率 33K = 120MHz/2/(1818)
		strInvParameterData.Field.uwDcDcPWMDutySet = 17;						// DcDc占空比 (1818/2-159)/1818 = 41.2%
		

		// 逆变参数
		strInvParameterData.Field.uwInvVAMax = 2000;								// 额定视在功率
		strInvParameterData.Field.uwInvWattMax = 2000;							// 额定有功功率		
		strInvParameterData.Field.uwInvRateVolt = cAcVoltReal230V;				// 逆变额定电压 230V		
		strInvParameterData.Field.uwInvDeratingVolt = cAcVoltReal150V;			// 逆变降额最低电压
		strInvParameterData.Field.uwInvFreeCntlCurrMax = 707;    				// 3.535A(1000W*1.414/200V=7.07A)
		strInvParameterData.Field.uwInvVoltOver = cAcVoltReal280V;    			// 逆变输出过压值 280V
		strInvParameterData.Field.uwInvVoltOverBack = cAcVoltReal270V;    		// 逆变输出过压恢复值 270V
		strInvParameterData.Field.uwInvCurrOver = cInv10A;    					// 逆变输出过流值 10A
		strInvParameterData.Field.uwHsInvTempStartDerat = cHsTemp82C;			// 逆变散热器开始降额温度
		strInvParameterData.Field.uwHsInvTempEndDerat = cHsTemp87C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwHsTwTempStartDerat = cHsTemp75C;			// 推挽散热器开始降额温度
		strInvParameterData.Field.uwHsTwTempEndDerat = cHsTemp90C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwTraTempStartDerat = cHsTemp80C; 			// 推挽变压器温度开始降额温度
		strInvParameterData.Field.uwTraTempEndDerat = cHsTemp85C;				// 推挽变压器温度停止降额温度
		strInvParameterData.Field.uwPvTempStartDerat = cHsTemp72C;				// PV温度降额开始降额温度
		strInvParameterData.Field.uwPvTempEndDerat = cHsTemp77C;				// PV温度降额停止降额温度
		strInvParameterData.Field.uwBatHNtcTempOver = cHsTemp66C;				// 电池正端温度过高
		strInvParameterData.Field.uwBatLNtcTempOver = cHsTemp66C;				// 电池负端温度过高
		strInvParameterData.Field.uwMaxFanDutyInvWatt = 260;					// 风扇满转时的逆变功率 250W
		
		// 市电参数
		
		// 负载参数
		strInvParameterData.Field.uwLoadVoltOver = cAcVoltReal280V;					// 输出过压值	280V
		strInvParameterData.Field.uwLoadVoltLowAPL = cAcVoltReal90V;				// 输出低压值 APL 90V
		strInvParameterData.Field.uwLoadVoltLowUPS = cAcVoltReal170V;				// 输出低压值 UPS 170V
	}
	else
	{
		T_FAULT_DATA.bits.bModelFault = true;
		sSetFaultCode(cModelFault);
	}

	g_uwRatedGridPower = strInvParameterData.Field.uwInvWattMax;
	wConvertMaxWatt = strInvParameterData.Field.uwInvWattMax;
	wConvertBatMaxWatt = strInvParameterData.Field.uwInvWattMax;
	sSetPvChgBatVoltRef(strInvParameterData.Field.uwPvChgBatVoltRef);

	// 目前机型不一样，电流采样系数不一样，所以识别机型后需要重新更新一下校准系数
	sSetInvCurrAdj(suwGetEEInvCurrAdj());
	sSetInvCurrBias(suwGetEEInvCurrBias());
}

INT16S	wWattSumErr = 0;

INT16U	uwPowerConversion = 0;
void	sInvPowerConversion(void)	// 功率折算
{
	INT16U wWattSumAbs;			// 总功率(绝对值)
	INT16S wWattSum;		
	INT16S wRLineWattTemp;		

	if(swGetWorkMode() == cLineMode)	// for test 
	{
		wRLineWattTemp = swGetRLineWattFilter();
	}
	else
	{
		wRLineWattTemp = 0;
	}

	uwPowerConversion = suwGetEEPowerConversion();
	if(uwPowerConversion)
	{
		wWattSumAbs = swAbs(swGetBatWattFilter()) + swAbs(swGetPvWattFilter()) \
						 + swAbs(wRLineWattTemp) + swAbs(swGetROpWattFilter());
		wWattSum = swGetBatWattFilter() + swGetPvWattFilter() + wRLineWattTemp + (-swGetROpWattFilter());
		
		//	电池功率
		if(swGetBatWattFilter() > 0)
		{
			strInvPowerConversionData.Field.wBatWatt = swGetBatWattFilter() - (INT16S)((INT32S)swGetBatWattFilter() * wWattSum / wWattSumAbs);
		}
		else
		{
			strInvPowerConversionData.Field.wBatWatt = swGetBatWattFilter() + (INT16S)((INT32S)swGetBatWattFilter() * wWattSum / wWattSumAbs);
		}
		
		//	PV功率
		strInvPowerConversionData.Field.wPvWatt = swGetPvWattFilter() - (INT16S)((INT32S)swGetPvWattFilter() * wWattSum / wWattSumAbs);
		if(strInvPowerConversionData.Field.wPvWatt < 0)
		{
			strInvPowerConversionData.Field.wPvWatt = 0;
		}
		
		//	市电功率
		if(wRLineWattTemp > 0)
		{
			strInvPowerConversionData.Field.wGridWatt = wRLineWattTemp - (INT16S)((INT32S)wRLineWattTemp * wWattSum / wWattSumAbs);
		}
		else
		{
			strInvPowerConversionData.Field.wGridWatt = wRLineWattTemp + (INT16S)((INT32S)wRLineWattTemp * wWattSum / wWattSumAbs);
		}	
		
		//	负载功率
		strInvPowerConversionData.Field.wLoadWatt = -swGetROpWattFilter() - (INT16S)((INT32S)swGetROpWattFilter() * wWattSum / wWattSumAbs);

		strInvPowerConversionData.Field.wInvWatt = swGetRInvWattFilter();
		strInvPowerConversionData.Field.wXXXXWatt = 0;

	}
	else
	{
		strInvPowerConversionData.Field.wBatWatt = swGetBatWattFilter();
		strInvPowerConversionData.Field.wPvWatt = swGetPvWattFilter();
		strInvPowerConversionData.Field.wGridWatt = wRLineWattTemp;
		strInvPowerConversionData.Field.wInvWatt = swGetRInvWattFilter();
		strInvPowerConversionData.Field.wLoadWatt = swGetROpWattFilter();
		strInvPowerConversionData.Field.wXXXXWatt = 0;
	}
	
	// for test
	wWattSumErr = strInvPowerConversionData.Field.wBatWatt + strInvPowerConversionData.Field.wPvWatt \
					+strInvPowerConversionData.Field.wGridWatt + strInvPowerConversionData.Field.wLoadWatt;
}

void	sInverterRealtimeDataUpdate(void)
{
	//State
	strInverterRealtimeData.Field.uwSettingDataSn++;	// 这个要放到EEPROM设置里面，设置一次自加一
	strInverterRealtimeData.Field.uwWorkMode = swGetWorkMode();
	strInverterRealtimeData.Field.uwState1 = 0;
	strInverterRealtimeData.Field.uwState2= 0;
	strInverterRealtimeData.Field.uwState3 = 0;
	strInverterRealtimeData.Field.uwState4 = 0;

	//Time
	strInverterRealtimeData.Field.uwYearMonth = 0;
	strInverterRealtimeData.Field.uwDayHour = 0;
	strInverterRealtimeData.Field.uwMinuteSecond = 0;
	strInverterRealtimeData.Field.uwWeek = 0;

	//Alarm & Fault
	strInverterRealtimeData.Field.uwAlarmCode = 0;
	strInverterRealtimeData.Field.uwFaultCode = swGetFaultCode();
	strInverterRealtimeData.Field.uwAlarmState1 = T_ALARM_DATA.uwData[0];
	strInverterRealtimeData.Field.uwAlarmState2 = T_ALARM_DATA.uwData[1];
	strInverterRealtimeData.Field.uwAlarmState3 = T_ALARM_DATA.uwData[2];
	strInverterRealtimeData.Field.uwAlarmState4 = T_ALARM_DATA.uwData[3];
	strInverterRealtimeData.Field.uwReserve16   = T_ALARM_DATA.uwData[4];
	strInverterRealtimeData.Field.uwFaultState1 = T_FAULT_DATA.uwData[0];
	strInverterRealtimeData.Field.uwFaultState2 = T_FAULT_DATA.uwData[1];
	strInverterRealtimeData.Field.uwFaultState3 = T_FAULT_DATA.uwData[2];
	strInverterRealtimeData.Field.uwFaultState4 = T_FAULT_DATA.uwData[3];
	strInverterRealtimeData.Field.uwFaultState5 = T_FAULT_DATA.uwData[4];
	strInverterRealtimeData.Field.uwFaultState6 = T_FAULT_DATA.uwData[5];
	strInverterRealtimeData.Field.uwFaultState7 = T_FAULT_DATA.uwData[6];
	strInverterRealtimeData.Field.uwFaultState8 = T_FAULT_DATA.uwData[7];
	strInverterRealtimeData.Field.uwFaultState9 = T_FAULT_DATA.uwData[8];
	strInverterRealtimeData.Field.uwFaultState10 = T_FAULT_DATA.uwData[9];
	strInverterRealtimeData.Field.uwReserve27 = 0;

	//PV
	strInverterRealtimeData.Field.uwPV1Volt = swGetPv1VoltFilter();
	strInverterRealtimeData.Field.uwPv1RlyVolt = 0;
	strInverterRealtimeData.Field.wPV1IndCurr = swGetPv1BatCurrFilter();
	strInverterRealtimeData.Field.uwPV1Power = swGetPvWattFilter();
	strInverterRealtimeData.Field.uwReserve32 = 0;
	strInverterRealtimeData.Field.uwReserve33 = 0;
	strInverterRealtimeData.Field.uwReserve34 = 0;
	strInverterRealtimeData.Field.uwReserve35 = 0;
	strInverterRealtimeData.Field.uwReserve36 = 0;
	strInverterRealtimeData.Field.uwReserve37 = 0;

	//Battery
	strInverterRealtimeData.Field.wBatVolt = swGetBatVoltFilter();
	strInverterRealtimeData.Field.wIBatCurr = -swGetBatCurrFilter();
	strInverterRealtimeData.Field.wBatPower = -swGetBatWattFilter();
	strInverterRealtimeData.Field.uwBatSOC = swGetBatSOCReal();
	strInverterRealtimeData.Field.uwReserve42 = 0;
	strInverterRealtimeData.Field.uwReserve43 = 0;
	strInverterRealtimeData.Field.uwReserve44 = 0;
	strInverterRealtimeData.Field.uwReserve45 = 0;

	//BUS
	strInverterRealtimeData.Field.uwBusVolt = swGetBusVoltFilter();
	strInverterRealtimeData.Field.wMidBusCurr = swGetBusCurrFilter();
	strInverterRealtimeData.Field.uwReserve48 = 0;
	strInverterRealtimeData.Field.uwReserve49 = 0;
	
	//Temperature
	strInverterRealtimeData.Field.wTwTempe 	= swGetLLCTempFilter();
	strInverterRealtimeData.Field.wInvTempe = swGetHsInvTempFilter();
	strInverterRealtimeData.Field.wTraTempe = 0;//swGetHsTraTempFilter();
	strInverterRealtimeData.Field.wPVTempe 	= swGetHsPvTempFilter();
	strInverterRealtimeData.Field.wEnviTempe= 0;
	strInverterRealtimeData.Field.wBatHTemp = swGetBat1TempFilter();
	strInverterRealtimeData.Field.wBatLTemp = swGetBat2TempFilter();

	//AC
	strInverterRealtimeData.Field.wGrid_Volt = swGetRLineVoltFilter();
	strInverterRealtimeData.Field.wGrid_Freq = swGetRLineFreqFilter();
	strInverterRealtimeData.Field.wGrid_Curr = swGetRLineCurrFilter();
	strInverterRealtimeData.Field.wGrid_Watt = swGetRLineWattFilter();
	strInverterRealtimeData.Field.wGrid_VA = swGetRLineVAFilter();
	strInverterRealtimeData.Field.wGrid_VAR = swGetRLineVarFilter();
	strInverterRealtimeData.Field.wGrid_PF = swGetRLinePFFilter();
	strInverterRealtimeData.Field.wGrid_DCI = 0;
	strInverterRealtimeData.Field.wINV_Volt = swGetRInvVoltFilter();
	strInverterRealtimeData.Field.wINV_Curr =swGetRInvCurrFilter();
	strInverterRealtimeData.Field.wINV_Freq = swGetRInvFreqFilter();
	strInverterRealtimeData.Field.wINV_Watt = swGetRInvWattFilter();
	strInverterRealtimeData.Field.wINV_VA = swGetRInvVAFilter();
	strInverterRealtimeData.Field.wINV_VAR = swGetRInvVarFilter();
	strInverterRealtimeData.Field.wINV_PF = swGetRInvPFFilter();
	strInverterRealtimeData.Field.wINV_DCV = swGetRInvDcVoltFilter();
	strInverterRealtimeData.Field.wINV_DCI = 0;
	strInverterRealtimeData.Field.wLoad_Volt = swGetROpVoltFilter();
	strInverterRealtimeData.Field.wLoad_Freq = swGetROpFreqFilter();
	strInverterRealtimeData.Field.wLoad_Curr = swGetROpCurrFilter();
	strInverterRealtimeData.Field.wLoad_Watt = swGetROpWattFilter();
	strInverterRealtimeData.Field.wLoad_VA =  swGetROpVAFilter();
	strInverterRealtimeData.Field.wLoad_VAR = swGetROpVarFilter();
	strInverterRealtimeData.Field.uwLoad_Persent = swGetOPPercent();
	strInverterRealtimeData.Field.wLoad_DCV = 0;
	strInverterRealtimeData.Field.uwReserve82 = 0;
	strInverterRealtimeData.Field.uwReserve83 = 0;
	strInverterRealtimeData.Field.uwReserve84 = 0;
	strInverterRealtimeData.Field.uwReserve85 = 0;
	strInverterRealtimeData.Field.uwReserve86 = 00;

	//Energy Information
	strInverterRealtimeData.Field.wLinePowerConvertion = strInvPowerConversionData.Field.wGridWatt;
	strInverterRealtimeData.Field.wReserve88 = 0;
	strInverterRealtimeData.Field.wLoadPowerConvertion = strInvPowerConversionData.Field.wLoadWatt;
	strInverterRealtimeData.Field.wBatPowerConvertion = strInvPowerConversionData.Field.wBatWatt;
	strInverterRealtimeData.Field.wPVPowerConvertion = strInvPowerConversionData.Field.wPvWatt;
	strInverterRealtimeData.Field.uwPowerFlowMsg = wWattSumErr; // for test
	strInverterRealtimeData.Field.uwReserve93 = wConvertMaxWatt;	// 功率百分比计算参考
	strInverterRealtimeData.Field.uwReserve94 = 0;
	strInverterRealtimeData.Field.uwReserve95 = 0;
	strInverterRealtimeData.Field.uwReserve96 = 0;

	//Power generation
	strInverterRealtimeData.Field.uwPV1TotalGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV1TotalGenEnergyL = 0;
	strInverterRealtimeData.Field.uwReserve99 = 0;
	strInverterRealtimeData.Field.uwReserve100 = 0;
	strInverterRealtimeData.Field.uwBatTotalChargeH = 0;
	strInverterRealtimeData.Field.uwBatTotalChargeL = 0;
	strInverterRealtimeData.Field.uwBatTotalDisChargeH = 0;
	strInverterRealtimeData.Field.uwBatTotalDisChargeL = 0;
	strInverterRealtimeData.Field.uwGridTotalCostEnergyH = 0;
	strInverterRealtimeData.Field.uwGridTotalCostEnergyL = 0;
	strInverterRealtimeData.Field.uwGridTotalGenEnergyH = 0;
	strInverterRealtimeData.Field.uwGridTotalGenEnergyL = 0;
	strInverterRealtimeData.Field.uwLoadTotalCostEnergyH = 0;
	strInverterRealtimeData.Field.uwLoadTotalCostEnergyL = 0;
	strInverterRealtimeData.Field.uwReserve111 = 0;
	strInverterRealtimeData.Field.uwReserve112 = 0;
	strInverterRealtimeData.Field.uwReserve113 = 0;
	strInverterRealtimeData.Field.uwReserve114 = 0;
	strInverterRealtimeData.Field.uwPV1DayGenEnergy = 0;
	strInverterRealtimeData.Field.uwPV1MonthGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV1MonthGenEnergyL = 0;
	strInverterRealtimeData.Field.uwPV1YearGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV1YearGenEnergyL = 0;
	strInverterRealtimeData.Field.uwReserve120 = 0;
	strInverterRealtimeData.Field.uwReserve121 = 0;
	strInverterRealtimeData.Field.uwReserve122 = 0;
	strInverterRealtimeData.Field.uwReserve123 = 0;
	strInverterRealtimeData.Field.uwReserve124 = 0;
	strInverterRealtimeData.Field.uwPVTotalGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPVTotalGenEnergyL = 0;
	strInverterRealtimeData.Field.uwBatDayCharge = 0;
	strInverterRealtimeData.Field.uwBatMonthChargeH = 0;
	strInverterRealtimeData.Field.uwBatMonthChargeL = 0;
	strInverterRealtimeData.Field.uwBatYearChargeH = 0;
	strInverterRealtimeData.Field.uwBatYearChargeL = 0;
	strInverterRealtimeData.Field.uwBatDayDisCharge = 0;
	strInverterRealtimeData.Field.uwBatMonthDisChargeH = 0;
	strInverterRealtimeData.Field.uwBatMonthDisChargeL = 0;
	strInverterRealtimeData.Field.uwBatYearDisChargeH = 0;
	strInverterRealtimeData.Field.uwBatYearDisChargeL = 0;
	strInverterRealtimeData.Field.uwGridDayCostEnergy = 0;
	strInverterRealtimeData.Field.uwGridMonthCostEnergyH = 0;
	strInverterRealtimeData.Field.uwGridMonthCostEnergyL = 0;
	strInverterRealtimeData.Field.uwGridYearCostEnergyH = 0;
	strInverterRealtimeData.Field.uwGridYearCostEnergyL = 0;
	strInverterRealtimeData.Field.uwGridDayGenEnergy = 0;
	strInverterRealtimeData.Field.uwGridMonthGenEnergyH = 0;
	strInverterRealtimeData.Field.uwGridMonthGenEnergyL = 0;
	strInverterRealtimeData.Field.uwGridYearGenEnergyH = 0;
	strInverterRealtimeData.Field.uwGridYearGenEnergyL = 0;
	strInverterRealtimeData.Field.uwLoadDayCostEnergy = 0;
	strInverterRealtimeData.Field.uwLoadMonthCostEnergyH = 0;
	strInverterRealtimeData.Field.uwLoadMonthCostEnergyL = 0;
	strInverterRealtimeData.Field.uwLoadYearCostEnergyH = 0;
	strInverterRealtimeData.Field.uwLoadYearCostEnergyL = 0;
	strInverterRealtimeData.Field.uwReserve152 = 0;
	strInverterRealtimeData.Field.uwReserve153 = 0;
	strInverterRealtimeData.Field.uwReserve154 = 0;
	strInverterRealtimeData.Field.uwReserve155 = 0;
	strInverterRealtimeData.Field.uwReserve156 = 0;

	//BMS
//	strInverterRealtimeData.Field.uwBMSWIFIBatMeterStatus = uwGetBMSWIFIBatMeterStatus();
//	strInverterRealtimeData.Field.uwBMS1CurrentBMSAddr = sbGetBMSAddr();
//	strInverterRealtimeData.Field.uwBMSFlag = swGetEmsDataParallelStatus();
//	strInverterRealtimeData.Field.uwBMS1ChargeVoltLimit = swGetBmsChargeVoltageLimit();
//	strInverterRealtimeData.Field.uwBMS1DischargeVoltLimit = swGetBmsDischargeVoltageLimit();
//	strInverterRealtimeData.Field.uwBMS1ChargeCurrLimit = swGetBmsChargeCurrentLimit();
//	strInverterRealtimeData.Field.uwBMS1DischargeCurrLimit = swGetBmsDischargeCurrentLimit();
//	strInverterRealtimeData.Field.uwBMS1BmsStatusHi = swGetBmsStatusHigh();
//	strInverterRealtimeData.Field.uwBMS1BmsStatusLo = swGetBmsStatusLow();
//	strInverterRealtimeData.Field.uwBMS1FaultFlagHi = swGetBmsFaultFlagHigh();
//	strInverterRealtimeData.Field.uwBMS1FaultFlagLo = swGetBmsFaultFlagLow();
//	strInverterRealtimeData.Field.uwBMS1AlarmFlagHi = swGetBmsAlarmFlagHigh();  
//	strInverterRealtimeData.Field.uwBMS1AlarmFlagLo = swGetBmsAlarmFlagLow();
//	strInverterRealtimeData.Field.uwBMS1NoticeFlagHi = swGetBmsNoticeFlagHigh();
//	strInverterRealtimeData.Field.uwBMS1NoticeFlagLo = swGetBmsNoticeFlagLow();
//	strInverterRealtimeData.Field.wBMS1TotalCurr = swGetBmsPackCurrent();
//	strInverterRealtimeData.Field.uwBMS1TotalVolt = swGetBmsPackVoltage();
//	strInverterRealtimeData.Field.uwBMS1Rsvd174 = swGetBmsPackVoltageReal();
//	strInverterRealtimeData.Field.uwBMS1Rsvd175 = swGetBmsReservd2();
//	strInverterRealtimeData.Field.uwBMS1TotalSOC = swGetBmsSOC();
//	strInverterRealtimeData.Field.uwBMS1TotalSOH = swGetBmsSOH();
//	strInverterRealtimeData.Field.uwBMS1TotalCapacityHigh = swGetBmsPackCapacityHigh();
//	strInverterRealtimeData.Field.uwBMS1TotalCapacityLow = swGetBmsPackCapacityLow();
//	strInverterRealtimeData.Field.uwBMS1ParallelNumber = swGetBmsParallelNumber();
//	strInverterRealtimeData.Field.uwBMS1ParallelStatus = swGetBmsParallelStatus();
//	strInverterRealtimeData.Field.uwReserve182 = swGetBmsSerialNumber();
//	strInverterRealtimeData.Field.uwReserve183 = swGetBmsSerialStatus();
//	strInverterRealtimeData.Field.uwBMS1MaximumCellVoltNo = swGetBmsMaximumCellVoltageNo();
//	strInverterRealtimeData.Field.uwBMS1MaximumCellVolt = swGetBmsMaximumCellVoltage();
//	strInverterRealtimeData.Field.uwBMS1MinimumCellVoltNo = swGetBmsMinimumCellVoltageNo();
//	strInverterRealtimeData.Field.uwBMS1MinimumCellVolt = swGetBmsMinimumCellVoltage();
//	strInverterRealtimeData.Field.uwBMS1MaximumCellTempeNo = swGetBmsMaximumCellTemperatureNo();
//	strInverterRealtimeData.Field.wBMS1MaximumCellTempe = swGetBmsMaximumCellTemperature();
//	strInverterRealtimeData.Field.uwBMS1MinimumCellTempeNo = swGetBmsMinimumCellTemperatureNo();
//	strInverterRealtimeData.Field.wBMS1MinmumCellTempe = swGetBmsMinimumCellTemperature();
//	strInverterRealtimeData.Field.uwBMSSN1 = 0;
//	strInverterRealtimeData.Field.uwBMSSN2 = 0;
//	strInverterRealtimeData.Field.uwBMSSN3 = 0;
//	strInverterRealtimeData.Field.uwBMSSN4 = 0;
//	strInverterRealtimeData.Field.uwBMSSN5 = 0;
//	strInverterRealtimeData.Field.uwReserve197 = 0;
//	strInverterRealtimeData.Field.uwReserve198 = 0;
//	strInverterRealtimeData.Field.uwReserve199 = 0;
//	strInverterRealtimeData.Field.uwReserve200 = 0;

	//EMS
//	if(sbGetEMSBMSConnect())
//	{
//		strInverterRealtimeData.Field.uwEMSTotalSOC = swGetEmsDataTotalSOC();
//		strInverterRealtimeData.Field.uwEMSConnectNumber = swGetEmsDataParallelNumber();
//		strInverterRealtimeData.Field.uwEmsBatLimitVolt = swGetEmsDataChargeVoltageLimit();
//		strInverterRealtimeData.Field.uwReserve204 = 0;
//		strInverterRealtimeData.Field.uwEmsBatCutOffVol = swGetEmsDataDischargeVoltageLimit();
//		strInverterRealtimeData.Field.uwEmsBatMaxChgCurrent = swGetEmsDataChargeCurrentLimit();
//		strInverterRealtimeData.Field.uwEmsMaxDisChgCurr = swGetEmsDataDischargeCurrentLimit();
//		strInverterRealtimeData.Field.uwEmsFaultCode = swGetEmsDataFaultFlagLow();
//		strInverterRealtimeData.Field.uwEmsFlag = 1;
//		strInverterRealtimeData.Field.uwEmsBatPackSeries = 0;
//	}
//	else if(swGetPylonCanConnectFlag())
//	{
//		strInverterRealtimeData.Field.uwEMSTotalSOC = swGetPylonDataTotalSOC()*10;
//		strInverterRealtimeData.Field.uwEMSConnectNumber = swGetPylonDataModuleNum();
//		strInverterRealtimeData.Field.uwEmsBatLimitVolt = swGetPylonDataChgVoltLimit();
//		strInverterRealtimeData.Field.uwReserve204 = 0;
//		strInverterRealtimeData.Field.uwEmsBatCutOffVol = swGetPylonDataDcgVoltLimit();
//		strInverterRealtimeData.Field.uwEmsBatMaxChgCurrent = swGetPylonDataChgCurrLimit();
//		strInverterRealtimeData.Field.uwEmsMaxDisChgCurr = swGetPylonDataDcgCurrLimit();
//		strInverterRealtimeData.Field.uwEmsFaultCode = swGetPylonDataBmsProtect();
//		strInverterRealtimeData.Field.uwEmsFlag = 1;
//		strInverterRealtimeData.Field.uwEmsBatPackSeries = 0;
//	}
//	else
//	{
//		strInverterRealtimeData.Field.uwEMSTotalSOC = 0;
//		strInverterRealtimeData.Field.uwEMSConnectNumber = 0;
//		strInverterRealtimeData.Field.uwEmsBatLimitVolt = 0;
//		strInverterRealtimeData.Field.uwReserve204 = 0;
//		strInverterRealtimeData.Field.uwEmsBatCutOffVol = 0;
//		strInverterRealtimeData.Field.uwEmsBatMaxChgCurrent = 0;
//		strInverterRealtimeData.Field.uwEmsMaxDisChgCurr = 0;
//		strInverterRealtimeData.Field.uwEmsFaultCode = 0;
//		strInverterRealtimeData.Field.uwEmsFlag = 0;
//		strInverterRealtimeData.Field.uwEmsBatPackSeries = 0;
//	}

//	#warn 故障记录需要放到中断去处理，产生故障时，刷新以下数据，每次只记录当前值，记录故障前先清除原有数据
	//Fault record 
	strInverterRealtimeData.Field.uwRecordlogType = 0;
	strInverterRealtimeData.Field.uwRecordlogIndex = 0;
	strInverterRealtimeData.Field.uwRecordlogStatus = 0;
	strInverterRealtimeData.Field.uwRecordlogNumber = 0;
	strInverterRealtimeData.Field.uwRecordlogYearMonth = 0;
	strInverterRealtimeData.Field.uwRecordlogDayHour = 0;
	strInverterRealtimeData.Field.uwRecordlogMinuteSecond = 0;
	strInverterRealtimeData.Field.uwRecordlogPV1Volt = 0;
	strInverterRealtimeData.Field.uwRecordlogPV2Volt = 0;
	strInverterRealtimeData.Field.wRecordlogPV1IndCurr = 0;
	strInverterRealtimeData.Field.wRecordlogPV2IndCurr = 0;
	strInverterRealtimeData.Field.uwRecordlogBatVolt = 0;
	strInverterRealtimeData.Field.wRecordlogBatCurr = 0;
	strInverterRealtimeData.Field.uwRecordlogBusVolt = 0;
	strInverterRealtimeData.Field.wRecordlogBoostTempe = 0;
	strInverterRealtimeData.Field.wRecordlogInvTempe = 0;
	strInverterRealtimeData.Field.wRecordlogEnviTempe = 0;
	strInverterRealtimeData.Field.wRecordlogPCB1Tempe = 0;
	strInverterRealtimeData.Field.uwReserve229 = 0;
	strInverterRealtimeData.Field.wRecordlogGridVolt = 0;
	strInverterRealtimeData.Field.wRecordlogGridCurr = 0;
	strInverterRealtimeData.Field.wRecordlogGridFreq = 0;
	strInverterRealtimeData.Field.wRecordlogINVVolt = 0;
	strInverterRealtimeData.Field.wRecordlogINVCurr = 0;
	strInverterRealtimeData.Field.wRecordlogINVFreq = 0;
	strInverterRealtimeData.Field.wRecordlogINVWatt = 0;
	strInverterRealtimeData.Field.wRecordlogLoadVolt = 0;
	strInverterRealtimeData.Field.wRecordlogLoadCurr = 0;
	strInverterRealtimeData.Field.wRecordlogLoadFreq = 0;
	strInverterRealtimeData.Field.wRecordlogLoadWatt = 0;
	strInverterRealtimeData.Field.wRecordlogLoadVA = 0;
	strInverterRealtimeData.Field.uwReserve242 = 0;
	strInverterRealtimeData.Field.uwReserve243 = 0;
	strInverterRealtimeData.Field.uwReserve244 = 0;
	strInverterRealtimeData.Field.uwReserve245 = 0;
	strInverterRealtimeData.Field.uwReserve246 = 0;
	strInverterRealtimeData.Field.uwReserve247 = 0;
	strInverterRealtimeData.Field.uwReserve248 = 0;
	strInverterRealtimeData.Field.uwReserve249 = 0;
	strInverterRealtimeData.Field.uwReserve250 = 0;
	strInverterRealtimeData.Field.uwReserve251 = 0;

}


//0202 0100 1223 1000 0100	// 0100后两位00是补位数用的
void	sInverterInformationDataUpdate(void)
{
	strInverterInformationData.Field.uwType 	  = uwGetType();				// 设备大类 IVEM:0X50
	strInverterInformationData.Field.uwSubType 	  = uwGetSubType();			// 设备子类 IVEM:0X040E
	strInverterInformationData.Field.uwCommProVer = 0;						// 通讯协议版本号
	strInverterInformationData.Field.uwCommInfo	  = 0x0003;					// 03：波特率9600
	strInverterInformationData.Field.uwSerial1 	  = suwGetEEATE_SN1();
	strInverterInformationData.Field.uwSerial2 	  = suwGetEEATE_SN2();		// SN码，ATE时扫码枪识别写入
	strInverterInformationData.Field.uwSerial3 	  = suwGetEEATE_SN3();
	strInverterInformationData.Field.uwSerial4 	  = suwGetEEATE_SN4();
	strInverterInformationData.Field.uwSerial5 	  = suwGetEEATE_SN5();
	strInverterInformationData.Field.uwSNLen   	  = suwGetEEATE_SNLen();	// SN码长度，ATE时扫码枪识别写入，默认18位SN
	strInverterInformationData.Field.uwDispSwVer  = 1000;					// 显示板软件版本号
	strInverterInformationData.Field.uwMCU1SwVer  = cDspCtrlVersion;		// DSP软件版本号
	strInverterInformationData.Field.uwMCU2SwVer  = 0;						// MPPT小板软件版本号
	strInverterInformationData.Field.uwDispHwVer  = MACHINE_HW_VERSION;		// 显示板硬件版本号
	strInverterInformationData.Field.uwCtrlHwVer  = g_uwBootHV;				// 控制板硬件版本号 //sbGetFlashHwVersion();
	strInverterInformationData.Field.uwPowerHwVer = 1000;					// 功率板硬件版本号

	strInverterInformationData.Field.uwOpType 	  = 0x0001;					// 1:单相机  3:三相机 	
	strInverterInformationData.Field.uwDspIapVer  = g_uwBootBV;				// DSP控制板IAP版本号
	
	strInverterInformationData.Field.uwDspTempVersion  = cDspTempVersion;	// DSP临时版本号，如V203_04的04

//	strInverterInformationData.Field.uwReserved2  = 2;
//	strInverterInformationData.Field.uwReserved3  = 3;
//	strInverterInformationData.Field.uwReserved4  = 4;
//	strInverterInformationData.Field.uwReserved5  = 5;
//	strInverterInformationData.Field.uwReserved6  = 6;
//	strInverterInformationData.Field.uwReserved7  = 7;
//	strInverterInformationData.Field.uwReserved8  = 8;
//	strInverterInformationData.Field.uwReserved9  = 9;
//	strInverterInformationData.Field.uwReserved10 = 10;
//	strInverterInformationData.Field.uwReserved11 = 11;
//	strInverterInformationData.Field.uwReserved12 = 12;
//	strInverterInformationData.Field.uwReserved13 = 13;
//	strInverterInformationData.Field.uwReserved14 = 14;
//	strInverterInformationData.Field.uwReserved15 = 15;
//	strInverterInformationData.Field.uwReserved16 = 16;
//	strInverterInformationData.Field.uwReserved17 = 17;
//	strInverterInformationData.Field.uwReserved18 = 18;
//	strInverterInformationData.Field.uwReserved19 = 19;
//	strInverterInformationData.Field.uwReserved20 = 20;
//	strInverterInformationData.Field.uwReserved21 = 21;
//	strInverterInformationData.Field.uwReserved22 = 22;
//	strInverterInformationData.Field.uwReserved23 = 23;
//	strInverterInformationData.Field.uwReserved24 = 24;
//	strInverterInformationData.Field.uwReserved25 = 25;
//	strInverterInformationData.Field.uwReserved26 = 26;
//	strInverterInformationData.Field.uwReserved27 = 27;
//	strInverterInformationData.Field.uwReserved28 = 28;
//	strInverterInformationData.Field.uwReserved29 = 29;
//	strInverterInformationData.Field.uwReserved30 = 30;
//	strInverterInformationData.Field.uwReserved31 = 31;
//
	// BMS	
//	strInverterInformationData.Field.uwBmsCurrBMSAddr = sbGetBMSAddr();
//	strInverterInformationData.Field.uwBmsType 		  = swGetBmsInfoType();
//	strInverterInformationData.Field.uwBmsSubType 	  = swGetBmsInfoSubType();
//	strInverterInformationData.Field.uwBmsCommProVer  = swGetBmsInfoCommProVer();
//	strInverterInformationData.Field.uwBmsCommInfo 	  = swGetBmsInfoCommInfo();
//	strInverterInformationData.Field.uwBmsSN1		  = swGetBmsInfoSerial1();
//	strInverterInformationData.Field.uwBmsSN2  		  = swGetBmsInfoSerial2();
//	strInverterInformationData.Field.uwBmsSN3		  = swGetBmsInfoSerial3();
//	strInverterInformationData.Field.uwBmsSN4		  = swGetBmsInfoSerial4();
//	strInverterInformationData.Field.uwBmsSN5		  = swGetBmsInfoSerial5();
//	strInverterInformationData.Field.uwBmsSNLen		  = swGetBmsInfoSNLen();
//	strInverterInformationData.Field.uwBmsDispSwVer   = swGetBmsInfoDispSwVer();
//	strInverterInformationData.Field.uwBmsMCU1SwVer   = swGetBmsInfoMCU1SwVer();
//	strInverterInformationData.Field.uwBmsMCU2SwVer   = swGetBmsInfoMCU2SwVer();
//	strInverterInformationData.Field.uwBmsDispHwVer   = swGetBmsInfoDispHwVer();
//	strInverterInformationData.Field.uwBmsCtrlHwVer   = swGetBmsInfoCtrlHwVer();
//	strInverterInformationData.Field.uwBmsPowerHwVer  = swGetBmsInfoPowerHwVer();
}

void sInvWattResCal(void)
{
	INT16U wTemp;
	INT16U wTempMax,wTempMin;

	if(uwGetModelLV())
	{
		wTempMax = (INT16U)((INT32U)1270 * 1270 / uwGetInvVAMax()); 		// 127V
		wTempMin = (INT16U)((INT32U)650 * 650 / uwGetInvVAMax());			// 65V
	}
	else
	{
		wTempMax = (INT16U)((INT32U)2400 * 2400 / uwGetInvVAMax()); 		// 240V
		wTempMin = (INT16U)((INT32U)900 * 900 / uwGetInvVAMax());			// 90V
	}

	wTemp = (INT16U)((INT32U)suwGetEEACOutputRatedVolt() * suwGetEEACOutputRatedVolt() / uwGetInvVAMax());
	UpDownLimit(wTemp,wTempMax,wTempMin);	

	strInvParameterData.Field.uwInvWattRes = wTemp;
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	swGetInverterRealtimeData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cINVERTER_REALTIME_DATA_LEN)
	{
		pwTemp = (INT16U *)&strInverterRealtimeData;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

INT16U	swGetInverterInformationData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cINVERTER_INFORMATION_DATA_LEN)
	{
		pwTemp = (INT16U *)&strInverterInformationData;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

INT16U	swGetWifiIotData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cWIFI_IOT_DATA_LEN)
	{
		pwTemp = (INT16U *)&strWifiIotData;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

// IAP版本识别
void	sDspIapVer(void)
{
	INT8U *pBootBegin;
	INT8U *pBootBV, *pBootHV;
	INT8U RxBuff[4];
	// IAP标志与IAP软件版本，电路板硬件版本识别
	pBootBegin  = (INT8U *)0x080000;
	pBootBV 	= (INT8U *)0x080003;	// boot软件版本号
	pBootHV 	= (INT8U *)0x080005;	// 机器硬件版本号
	
	//if((*pBootBegin == 0xFFFF) || (*pBootBV != 0x3031) || (*pBootHV != 0x3031))
	if((*pBootBegin == 0xFFFF)) // 0XFFFF = 没有烧录IAP
	{
		T_FAULT_DATA.bits.bBootloadFail = true;
		sSetFaultCode(cBootloadFail);
	}
	else
	{
		g_uwBootBV = (INT16U)(*pBootBV);
		RxBuff[0] = g_uwBootBV & 0x00FF;
		RxBuff[1] = (g_uwBootBV & 0xFF00) >> 8;
		g_uwBootHV = (INT16U)(*pBootHV);
		RxBuff[2] = g_uwBootHV & 0x00FF;
		RxBuff[3] = (g_uwBootHV & 0xFF00) >> 8;

		g_uwBootBV = (RxBuff[1] -'0') * 10 + (RxBuff[0] -'0');
		g_uwBootHV = (RxBuff[3] -'0') * 10 + (RxBuff[2] -'0');
	}
}

INT16U	uwGetBootBV(void)	// boot软件版本号
{
	return g_uwBootBV;
}
INT16U	uwGetBootHV(void) // 机器硬件版本号
{
	return g_uwBootHV;
}



INT16U	uwGetModelVar(void)
{
	return g_uwModelVar;
}

INT16U	uwGetModelLV(void)
{
	return strInvParameterData.Field.uwModelLV;
}

INT16U	uwGetType(void)
{
	return strInvParameterData.Field.uwType;
}

INT16U	uwGetSubType(void)
{
	return strInvParameterData.Field.uwSubType;
}

INT16U	uwGetBatSerialPcs(void)
{
	return strInvParameterData.Field.uwBatSerialPcs;
}

INT16U	uwGetTransformerRatio(void)
{
	return strInvParameterData.Field.uwTransformerRatio;
}

INT16U	uwGetInvVAMax(void)
{
	return strInvParameterData.Field.uwInvVAMax;
}

INT16S	uwGetInvWattMax(void)
{
	return strInvParameterData.Field.uwInvWattMax;
}

INT16S	uwGetInvRateVolt(void)
{
	return strInvParameterData.Field.uwInvRateVolt;
}

INT16S	uwGetInvDeratingVolt(void)
{
	return strInvParameterData.Field.uwInvDeratingVolt;
}

INT16S	uwGetInvFreeCntlCurrMax(void)
{
	return strInvParameterData.Field.uwInvFreeCntlCurrMax;
}

INT16U	uwGetInvVoltOver(void)
{
	return strInvParameterData.Field.uwInvVoltOver;
}

INT16U	uwGetInvVoltOverBack(void)
{
	return strInvParameterData.Field.uwInvVoltOverBack;
}

INT16U	uwGetInvCurrOver(void)
{
	return strInvParameterData.Field.uwInvCurrOver;
}

INT16U	uwGetCTdirection(void)
{
	return strInvParameterData.Field.uwCTdirection;
}

INT16U	uwGetInvCurrRatio(void)
{
	return strInvParameterData.Field.uwInvCurrRatio;
}

INT16U	uwGetInvWattRes(void)
{
	return strInvParameterData.Field.uwInvWattRes;
}

INT16U	uwGetSettingMaxChgCurr(void)
{
	return strInvParameterData.Field.uwSettingMaxChgCurr;
}

INT16U	uwGetSettingMaxDchgCurr(void)
{
	return strInvParameterData.Field.uwSettingMaxDcgCurr;
}

INT16U	uwGetSettingMaxACChgCurr(void)
{
	return strInvParameterData.Field.uwSettingMaxACChgCurr;
}

INT16U	uwGetBusVoltOver1(void)
{
	return strInvParameterData.Field.uwBusVoltOver1;
}

INT16U	uwGetBusVoltOver2(void)
{
	return strInvParameterData.Field.uwBusVoltOver2;
}

INT16U	uwGetBusVoltOver3(void)
{
	return strInvParameterData.Field.uwBusVoltOver3;
}

INT16U	uwGetBusVoltLow1(void)
{
	return strInvParameterData.Field.uwBusVoltLow1;
}

INT16U	uwGetDcDcPWMPeriod(void)
{
	return strInvParameterData.Field.uwDcDcPWMPeriod;
}

INT16U	uwGetDcDcPWMDutySet(void)
{
	return strInvParameterData.Field.uwDcDcPWMDutySet;
}

// temp
INT16U	uwGetHsInvTempStartDerat(void)
{
	return strInvParameterData.Field.uwHsInvTempStartDerat;
}

INT16U	uwGetHsInvTempEndDerat(void)
{
	return strInvParameterData.Field.uwHsInvTempEndDerat;
}

INT16U	uwGetHsTwTempStartDerat(void)
{
	return strInvParameterData.Field.uwHsTwTempStartDerat;
}

INT16U	uwGetHsTwTempEndDerat(void)
{
	return strInvParameterData.Field.uwHsTwTempEndDerat;
}

INT16U	uwGetTraTempStartDerat(void)
{
	return strInvParameterData.Field.uwTraTempStartDerat;
}

INT16U	uwGetTraTempEndDerat(void)
{
	return strInvParameterData.Field.uwTraTempEndDerat;
}

INT16U	uwGetPvTempStartDerat(void)
{
	return strInvParameterData.Field.uwPvTempStartDerat;
}

INT16U	uwGetPvTempEndDerat(void)
{
	return strInvParameterData.Field.uwPvTempEndDerat;
}

INT16U	uwGetBatHNtcTempOver(void)
{
	return strInvParameterData.Field.uwBatHNtcTempOver;
}

INT16U	uwGetBatLNtcTempOver(void)
{
	return strInvParameterData.Field.uwBatLNtcTempOver;
}

INT16S	uwGetMaxFanDutyInvWatt(void)
{
	return strInvParameterData.Field.uwMaxFanDutyInvWatt;
}

INT16U	uwGetMpptPvVoltMax(void)
{
	return strInvParameterData.Field.uwMpptPvVoltMax;
}

INT16U	uwGetPvPowerMax(void)
{
	return strInvParameterData.Field.uwPvPowerMax;
}

INT16U	uwGetPvChgBatVoltRef(void)
{
	return strInvParameterData.Field.uwPvChgBatVoltRef;
}

INT16U	uwGetLoadVoltOver(void)
{
	return strInvParameterData.Field.uwLoadVoltOver;
}

INT16U	uwGetLoadVoltLowAPL(void)
{
	return strInvParameterData.Field.uwLoadVoltLowAPL;
}

INT16U	uwGetLoadVoltLowUPS(void)
{
	return strInvParameterData.Field.uwLoadVoltLowUPS;
}

// WIFI IOT
INT16U	uwGetWifiIotState(void)
{
	return strWifiIotData.Field.uwIotState;
}

INT16U	uwGetBMSWIFIBatMeterStatus(void)
{
	return strBMSWIFIBatMeterStatus.wData;
}

// 读取单台电池板数据状态标志
INT16U	uwGetBmsDataFlag(void)
{
	return strBMSWIFIBatMeterStatus.bits.bGetBmsDataFlag;
}

INT16S	uwGetBatConversionWatt(void)
{
	return strInvPowerConversionData.Field.wBatWatt;
}

INT16S	uwGetPvConversionWatt(void)
{
	return strInvPowerConversionData.Field.wPvWatt;
}

INT16S	uwGetGridConversionWatt(void)
{
	return strInvPowerConversionData.Field.wGridWatt;
}

INT16S	uwGetLoadConversionWatt(void)
{
	return strInvPowerConversionData.Field.wLoadWatt;
}

INT16U	uwGetRTDataEMSConnectNumber(void)
{
	return strInverterRealtimeData.Field.uwEMSConnectNumber;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetWifiIotType(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotType = uwTemp;
}

void	sSetWifiIotTersion(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotTersion = uwTemp;
}

void	sSetWifiIotIpAddressH(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotIpAddressH = uwTemp;
}

void	sSetWifiIotIpAddressL(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotIpAddressL = uwTemp;
}

void	sSetWifiIotSimSn1(INT16U uwTemp)	// SN1
{
	strWifiIotData.Field.uwIotSimSn1 = uwTemp;
}

void	sSetWifiIotSimSn2(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn2 = uwTemp;
}

void	sSetWifiIotSimSn3(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn3 = uwTemp;
}

void	sSetWifiIotSimSn4(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn4 = uwTemp;
}

void	sSetWifiIotSimSn5(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn5 = uwTemp;
}

void	sSetWifiIotSimSn6(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn6 = uwTemp;
}

void	sSetWifiIotSimSn7(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn7 = uwTemp;
}

void	sSetWifiIotSimSn8(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn8 = uwTemp;
}

void	sSetWifiIotSimSn9(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn9 = uwTemp;
}

void	sSetWifiIotSimSn10(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn10 = uwTemp;
}

void	sSetWifiIotSimSn11(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn11 = uwTemp;
}

void	sSetWifiIotSimSn12(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn12 = uwTemp;
}

void	sSetWifiIotSimSn13(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn13 = uwTemp;
}

void	sSetWifiIotSimSn14(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn14 = uwTemp;
}

void	sSetWifiIotSimSn15(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn15 = uwTemp;
}

void	sSetWifiIotSimSn16(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotSimSn16 = uwTemp;
}

void	sSetWifiIotState(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotState = uwTemp;
}

void	sSetWifiIotRSSI(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotRSSI = uwTemp;
}

void	sSetWifiIotBleConn(INT16U uwTemp)
{
	strWifiIotData.Field.uwBleConn = uwTemp;
}

// 读取单台电池板数据状态标志
void	uwSetBmsDataFlag(INT16U uwTemp)
{
	strBMSWIFIBatMeterStatus.bits.bGetBmsDataFlag = uwTemp;
}


