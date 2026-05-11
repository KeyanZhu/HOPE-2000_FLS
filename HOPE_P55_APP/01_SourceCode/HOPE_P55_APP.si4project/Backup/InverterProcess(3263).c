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

extern INT16U g_uwFaultCode;

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
	memset(&fPowerFlowMsg, 0, sizeof(fPowerFlowMsg));
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
		strInvParameterData.Field.uwInvWattRes = 4840;							// = (2200 * 2200 / 1000)
		
		// PV参数
		strInvParameterData.Field.uwMpptPvVoltMax = cMpptPvVolt55V;				// PV最高电压55V
		strInvParameterData.Field.uwPvPowerMax = 600;							// PV最大充电功率 600W
		strInvParameterData.Field.uwPvChgBatVoltRef = 720;						// PV充电电池电压参考 7.2V
		
		// 电池参数
		strInvParameterData.Field.uwSettingMaxChgCurr = 1600;					// 电池最大充电电流 160A	// 精度可能有问题
		strInvParameterData.Field.uwSettingMaxDcgCurr = 1800;					// 电池最大放电电流 180A	// 精度可能有问题
		strInvParameterData.Field.uwSettingMaxACChgCurr = 1600;				// 市电最大充电电流 160A	// 精度可能有问题
		strInvParameterData.Field.uwBusVoltOver1 = cBusVoltReal475V;			// Bus过压1 
		strInvParameterData.Field.uwBusVoltOver2 = cBusVoltReal480V;			// Bus过压2 
		strInvParameterData.Field.uwBusVoltOver3 = cBusVoltReal550V;			// Bus过压3 中断级
		strInvParameterData.Field.uwBusVoltLow1 = cBusVoltReal300V;				// Bus低压1 
		strInvParameterData.Field.uwDcDcPWMPeriod = cDCDCPeriod; 				// DcDc频率 86K = 150MHz/2/(872)
		strInvParameterData.Field.uwDcDcPWMDutySet = 30;//17;					// DcDc占空比 (872/2-30)/872 = 41.2%
		

		// 逆变参数
		strInvParameterData.Field.uwInvVAMax = 1100;							// 额定视在功率
		strInvParameterData.Field.uwInvWattMax = 1100;							// 额定有功功率		
		strInvParameterData.Field.uwInvRateVolt = cAcVoltReal230V;				// 逆变额定电压 230V		
		strInvParameterData.Field.uwInvDeratingVolt = cAcVoltReal150V;			// 逆变降额最低电压
		strInvParameterData.Field.uwInvFreeCntlCurrMax = 71;    				// 3.535A(1000W*1.414/200V=7.07A)
		strInvParameterData.Field.uwInvVoltOver = cAcVoltReal280V;    			// 逆变输出过压值 280V
		strInvParameterData.Field.uwInvVoltOverBack = cAcVoltReal270V;    		// 逆变输出过压恢复值 270V
		strInvParameterData.Field.uwInvCurrOver = cInv10A;    					// 逆变输出过流值 10A
		strInvParameterData.Field.uwHsInvTempStartDerat = cHsTemp124C;			// 逆变散热器开始降额温度
		strInvParameterData.Field.uwHsInvTempEndDerat = cHsTemp129C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwHsTwTempStartDerat = cHsTemp114C;			// 推挽散热器开始降额温度
		strInvParameterData.Field.uwHsTwTempEndDerat = cHsTemp119C;				// 逆变散热器停止降额温度
		strInvParameterData.Field.uwTraTempStartDerat = cHsTemp80C; 			// 推挽变压器温度开始降额温度
		strInvParameterData.Field.uwTraTempEndDerat = cHsTemp85C;				// 推挽变压器温度停止降额温度
		strInvParameterData.Field.uwPvTempStartDerat = cHsTemp85C;				// PV温度降额开始降额温度
		strInvParameterData.Field.uwPvTempEndDerat = cHsTemp91C;				// PV温度降额停止降额温度
		strInvParameterData.Field.uwBatHNtcTempOver = cHsTemp66C;				//待确定  // 电池正端温度过高
		strInvParameterData.Field.uwBatLNtcTempOver = cHsTemp66C;				// 电池负端温度过高
		strInvParameterData.Field.uwMaxFanDutyInvWatt = 600;					// 风扇满转时的逆变功率 300W
		
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
//	sSetInvCurrAdj(suwGetEEInvCurrAdj());
//	sSetInvCurrBias(suwGetEEInvCurrBias());
}

INT16S	wWattSumErr = 0;

INT16U	uwPowerConversion = 0;
void	sInvPowerConversion(void)	// 功率折算
{
	INT16U wWattSumAbs;			// 总功率(绝对值)
	INT16S wWattSum;		
	INT16S wRLineWattTemp;
	INT16S wROPWattTemp;
	INT16S wWattSumErrTemp;

	if(swGetWorkMode() == cLineMode)	// for test 
	{
		// 没开馈电使能时，不显示负功率
		if((suwGetEEFeedEnable() == 0) && (swGetRLineWattFilter() < 0))
		{
			wRLineWattTemp = 0;
		}
		else
		{
			wRLineWattTemp = swGetRLineWattFilter();
		}
	}
	else
	{
		wRLineWattTemp = 0;
	}

	// 空载时输出电流采样波动比较大时可能会出现负的输出功率，做个处理
	if((suwGetEEAdcBiasAdj() == 0) && (swGetROpWattFilter() < 0)) 
	{
		wROPWattTemp = 0;
	}
	else
	{
		wROPWattTemp = swGetROpWattFilter();
	}

	uwPowerConversion = suwGetEEPowerConversion();
	if(uwPowerConversion)
	{
		wWattSumAbs = swAbs(swGetBatWattFilter()) + swAbs(swGetPvWattFilter()) \
						 + swAbs(wRLineWattTemp) + swAbs(wROPWattTemp);
		wWattSum = swGetBatWattFilter() + swGetPvWattFilter() + wRLineWattTemp + (-wROPWattTemp);
		
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
		strInvPowerConversionData.Field.wLoadWatt = -wROPWattTemp - (INT16S)((INT32S)wROPWattTemp * wWattSum / wWattSumAbs);
		// for test
		wWattSumErrTemp = strInvPowerConversionData.Field.wBatWatt + strInvPowerConversionData.Field.wPvWatt \
						+strInvPowerConversionData.Field.wGridWatt + strInvPowerConversionData.Field.wLoadWatt;
		strInvPowerConversionData.Field.wLoadWatt = strInvPowerConversionData.Field.wLoadWatt - wWattSumErrTemp; // 负载功率增加误差补偿

		strInvPowerConversionData.Field.wInvWatt = swGetRInvWattFilter();
		strInvPowerConversionData.Field.wXXXXWatt = 0;

	}
	else
	{
		strInvPowerConversionData.Field.wBatWatt = swGetBatWattFilter();
		strInvPowerConversionData.Field.wPvWatt = swGetPvWattFilter();
		strInvPowerConversionData.Field.wGridWatt = wRLineWattTemp;
		strInvPowerConversionData.Field.wInvWatt = swGetRInvWattFilter();
		strInvPowerConversionData.Field.wLoadWatt = wROPWattTemp;
		strInvPowerConversionData.Field.wXXXXWatt = 0;
	}
	
	// for test
	wWattSumErr = strInvPowerConversionData.Field.wBatWatt + strInvPowerConversionData.Field.wPvWatt \
					+strInvPowerConversionData.Field.wGridWatt + strInvPowerConversionData.Field.wLoadWatt;
}

void	sPowerFlowMsgUpdate(void)
{
	//BAT
	fPowerFlowMsg.bits.bbatteryIcon = ((T_ALARM_DATA.bits.bBatOpenAlarm == false) ? 1 : 0);
	fPowerFlowMsg.bits.bbatteryFlow = ((swAbs(swGetBatWattFilter()) > 10) ? 1 : 0);
	fPowerFlowMsg.bits.bbatteryEngyDir = ((swGetBatCurrFilter() > 5) ? 1 : 0);

	//PV
	fPowerFlowMsg.bits.bPVIcon = ((T_ALARM_DATA.bits.bPv1UVAlarm == false) ? 1 : 0);
	fPowerFlowMsg.bits.bPVFlow = ((swGetPvWattFilter() > 10) ? 1 : 0);

	//LOAD
	fPowerFlowMsg.bits.bLoadIcon = ((uwGetOPRelayOn() == true) ? 1 : 0);
	fPowerFlowMsg.bits.bLoadFlow = ((swGetROpWattFilter() > 10) ? 1 : 0);

	//LINE
	fPowerFlowMsg.bits.bLineIcon = ((T_ALARM_DATA.bits.bGridUV == false) ? 1 : 0);
	fPowerFlowMsg.bits.bLineFlow = ((swAbs(swGetRLineWattFilter()) > 10) ? 1 : 0);
	fPowerFlowMsg.bits.bLineEngyDir = ((swGetRLineWattFilter() < 0) ? 1 : 0);

	//GEN
	fPowerFlowMsg.bits.bGenIcon = 0;//(() ? 1 : 0);
	fPowerFlowMsg.bits.bGenFlow = 0;//(() ? 1 : 0);

	//SmartLoad
	fPowerFlowMsg.bits.bSmartLoadIcon = 0;//(() ? 1 : 0);
	fPowerFlowMsg.bits.bSmartLoadFlow = 0;//(() ? 1 : 0);
}

void	sInverterRealtimeDataUpdate(void)
{
	//State
	strInverterRealtimeData.Field.uwSettingDataSn++;
	strInverterRealtimeData.Field.uwWorkMode = swGetWorkMode();
	strInverterRealtimeData.Field.uwState1 = 0;
	strInverterRealtimeData.Field.uwState2 = 0;
	strInverterRealtimeData.Field.uwState3 = 0;
	strInverterRealtimeData.Field.uwState4 = 0;
	strInverterRealtimeData.Field.uwState5 = 0;
	strInverterRealtimeData.Field.uwState6 = 0;

	//Parallel
	strInverterRealtimeData.Field.uwParallelMode = 0;
	strInverterRealtimeData.Field.uwParallelState1 = 0;
	strInverterRealtimeData.Field.uwParallelState2 = 0;
	strInverterRealtimeData.Field.uwReserve12 = 0;
	strInverterRealtimeData.Field.uwReserve13 = 0;
	strInverterRealtimeData.Field.uwReserve14 = 0;
	strInverterRealtimeData.Field.uwReserve15 = 0;
	strInverterRealtimeData.Field.uwReserve16 = 0;

	//Time
	strInverterRealtimeData.Field.uwYearMonth = 0;
	strInverterRealtimeData.Field.uwDayHour = 0;
	strInverterRealtimeData.Field.uwMinuteSecond = 0;
	strInverterRealtimeData.Field.uwWeek = 0;

	//Alarm & Fault
	strInverterRealtimeData.Field.uwAlarmCode = 0;//SwGetWarningCode();
	strInverterRealtimeData.Field.uwFaultCode = swGetFaultCode();
	strInverterRealtimeData.Field.uwAlarmState1 = T_ALARM_DATA.uwData[0];
	strInverterRealtimeData.Field.uwAlarmState2 = T_ALARM_DATA.uwData[1];
	strInverterRealtimeData.Field.uwAlarmState3 = T_ALARM_DATA.uwData[2];
	strInverterRealtimeData.Field.uwAlarmState4 = T_ALARM_DATA.uwData[3];
	strInverterRealtimeData.Field.uwReserve27   = T_ALARM_DATA.uwData[4];
	strInverterRealtimeData.Field.uwReserve28   = 0;
	strInverterRealtimeData.Field.uwReserve29   = 0;
	strInverterRealtimeData.Field.uwReserve30   = 0;
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
	strInverterRealtimeData.Field.uwReserve41 = 0;
	strInverterRealtimeData.Field.uwReserve42 = 0;
	strInverterRealtimeData.Field.uwReserve43 = 0;
	strInverterRealtimeData.Field.uwReserve44 = 0;

	//Energy Information
	strInverterRealtimeData.Field.uwPowerFlowMsg = fPowerFlowMsg.data;
	strInverterRealtimeData.Field.wBatPowerConvertion = strInvPowerConversionData.Field.wBatWatt;
	strInverterRealtimeData.Field.wPVPowerConvertion = strInvPowerConversionData.Field.wPvWatt;
	strInverterRealtimeData.Field.wGridPowerConvertion = strInvPowerConversionData.Field.wGridWatt;
	strInverterRealtimeData.Field.wGenPowerConvertion = 0;
	strInverterRealtimeData.Field.wLoadPowerConvertion = strInvPowerConversionData.Field.wLoadWatt;
	strInverterRealtimeData.Field.uwOnGridLoadPowerConvertion = 0;
	strInverterRealtimeData.Field.uwBatSocConvertion = swGetSocNew();
	strInverterRealtimeData.Field.uwReserve53 = wConvertMaxWatt;	// 功率百分比计算参考
	strInverterRealtimeData.Field.uwReserve54 = wWattSumErr;		// for test
	strInverterRealtimeData.Field.uwReserve55 = 0;
	strInverterRealtimeData.Field.uwReserve56 = 0;
	strInverterRealtimeData.Field.uwReserve57 = 0;
	strInverterRealtimeData.Field.uwReserve58 = 0;
	strInverterRealtimeData.Field.uwReserve59 = 0;
	strInverterRealtimeData.Field.uwReserve60 = 0;
	strInverterRealtimeData.Field.uwReserve61 = 0;
	strInverterRealtimeData.Field.uwReserve62 = 0;
	strInverterRealtimeData.Field.uwReserve63 = 0;
	strInverterRealtimeData.Field.uwReserve64 = 0;

	//PV
	strInverterRealtimeData.Field.uwPv1Volt = swGetPv1VoltFilter();
	strInverterRealtimeData.Field.uwPv1InputCurr = swGetPvInCurrFilter();
	strInverterRealtimeData.Field.uwPv1InputPower = swGetPv1VoltFilter() * swGetPvInCurrFilter();
//	if(suwGetEEPowerConversion())
//	{
//		strInverterRealtimeData.Field.uwPv1IndCurr = (INT16S)((INT32S)strInvPowerConversionData.Field.wPvWatt * 10000 / swGetBatVoltFilter());
//		strInverterRealtimeData.Field.uwPv1OutPower = strInvPowerConversionData.Field.wPvWatt;
//	}
//	else
//	{
		strInverterRealtimeData.Field.uwPv1IndCurr = swGetPv1CurrFilter();
		strInverterRealtimeData.Field.uwPv1OutPower = swGetPvWattFilter();
//	}
	strInverterRealtimeData.Field.uwPv2Volt = 0;
	strInverterRealtimeData.Field.uwPv2InputCurr = 0;
	strInverterRealtimeData.Field.uwPv2IndCurr = 0;
	strInverterRealtimeData.Field.uwPv2InputPower = 0;
	strInverterRealtimeData.Field.uwPv2OutPower = 0;
	strInverterRealtimeData.Field.uwPVPosInsResVal = 0;
	strInverterRealtimeData.Field.uwPVNegInsResVal = 0;
	strInverterRealtimeData.Field.uwReserve77 = 0;
	strInverterRealtimeData.Field.uwReserve78 = 0;
	strInverterRealtimeData.Field.uwReserve79 = 0;
	strInverterRealtimeData.Field.uwReserve80 = 0;

	//GRID
//	if(swGetWorkMode() == cLineMode || suwGetEEAdcBiasAdj())	// for test 需查找不接市电为啥会有数据
//	{
		strInverterRealtimeData.Field.wGrid_Volt = swGetRLineVoltFilter();
		strInverterRealtimeData.Field.wGrid_Freq = swGetRLineFreqFilter();
//		if(suwGetEEPowerConversion())
//		{
//			strInverterRealtimeData.Field.wGrid_Curr = (INT16S)((INT32S)strInvPowerConversionData.Field.wGridWatt * 1000 / swGetRLineVoltFilter());
//			strInverterRealtimeData.Field.wGrid_Watt = strInvPowerConversionData.Field.wGridWatt;
//			strInverterRealtimeData.Field.wGrid_VA = 0;//swGetRLineVAFilterConversion();
//		}
//		else
//		{
			strInverterRealtimeData.Field.wGrid_Curr = swGetRLineCurrFilter();
			strInverterRealtimeData.Field.wGrid_Watt = swGetRLineWattFilter();
			strInverterRealtimeData.Field.wGrid_VA = swGetRLineVAFilter();
//		}
		strInverterRealtimeData.Field.wGrid_VAR = swGetRLineVarFilter();
		strInverterRealtimeData.Field.wGrid_PF = swGetRLinePFFilter();
		strInverterRealtimeData.Field.wGrid_DCI = 0;
//	}
//	else
//	{
//		strInverterRealtimeData.Field.wGrid_Volt = 0;
//		strInverterRealtimeData.Field.wGrid_Curr = 0;
//		strInverterRealtimeData.Field.wGrid_Freq = 0;
//		strInverterRealtimeData.Field.wGrid_Watt = 0;
//		strInverterRealtimeData.Field.wGrid_VA = 0;
//		strInverterRealtimeData.Field.wGrid_VAR = 0;
//		strInverterRealtimeData.Field.wGrid_PF = 0;
//		strInverterRealtimeData.Field.wGrid_DCI = 0;
//	}
	strInverterRealtimeData.Field.uwReserve89 = 0;
	strInverterRealtimeData.Field.uwReserve90 = 0;
	strInverterRealtimeData.Field.uwReserve91 = 0;
	strInverterRealtimeData.Field.uwReserve92 = 0;

	//INV
	strInverterRealtimeData.Field.wINV_Volt = swGetRInvVoltFilter();
	strInverterRealtimeData.Field.wINV_Curr = swGetRInvCurrFilter();
	strInverterRealtimeData.Field.wINV_Freq = swGetRInvFreqFilter();
	strInverterRealtimeData.Field.wINV_Watt = swGetRInvWattFilter();
	strInverterRealtimeData.Field.wINV_VA = swGetRInvVAFilter();
	strInverterRealtimeData.Field.wINV_VAR = swGetRInvVarFilter();
	strInverterRealtimeData.Field.wINV_PF = swAbs(swGetRInvPFFilter());
	strInverterRealtimeData.Field.wINV_DCV = swGetRInvDcVoltFilter();
	strInverterRealtimeData.Field.wINV_DCI = 0;//swGetRInvDcCurrFilter();
	strInverterRealtimeData.Field.uwReserve102 = 0;
	strInverterRealtimeData.Field.uwReserve103 = 0;
	strInverterRealtimeData.Field.uwReserve104 = 0;

	//LOAD
	strInverterRealtimeData.Field.wLoad_Volt = swGetROpVoltFilter();
	strInverterRealtimeData.Field.wLoad_Freq = swGetROpFreqFilter();
//	if(suwGetEEPowerConversion())
//	{
//		strInverterRealtimeData.Field.wLoad_Curr = -(INT16S)((INT32S)strInvPowerConversionData.Field.wLoadWatt * 1000 / swGetROpVoltFilter());
//		strInverterRealtimeData.Field.wLoad_Watt = -strInvPowerConversionData.Field.wLoadWatt;
//		strInverterRealtimeData.Field.wLoad_VA =  swGetROpVAFilterConversion();
//	}
//	else
//	{
		strInverterRealtimeData.Field.wLoad_Curr = swGetROpCurrFilter();
		strInverterRealtimeData.Field.wLoad_Watt = swGetROpWattFilter();
		strInverterRealtimeData.Field.wLoad_VA =  swGetROpVAFilter();
//	}
	strInverterRealtimeData.Field.wLoad_VAR = swGetROpVarFilter();
	strInverterRealtimeData.Field.uwLoad_Persent = swGetOPPercent();
	strInverterRealtimeData.Field.wLoad_DCV = 0;
	strInverterRealtimeData.Field.uwReserve113 = 0;
	strInverterRealtimeData.Field.uwReserve114 = 0;
	strInverterRealtimeData.Field.uwReserve115 = 0;
	strInverterRealtimeData.Field.uwReserve116 = 0;

	//GEN
	strInverterRealtimeData.Field.wGenVolt = 0;
	strInverterRealtimeData.Field.wGenCurr = 0;
	strInverterRealtimeData.Field.wGenFreq = 0;
	strInverterRealtimeData.Field.wGenWatt = 0;
	strInverterRealtimeData.Field.wGenVA =  0;
	strInverterRealtimeData.Field.wGenVAR = 0;
	strInverterRealtimeData.Field.uwGenPersent = 0;
	strInverterRealtimeData.Field.wGenDCV = 0;
	strInverterRealtimeData.Field.uwReserve125 = 0;
	strInverterRealtimeData.Field.uwReserve126 = 0;
	strInverterRealtimeData.Field.uwReserve127 = 0;
	strInverterRealtimeData.Field.uwReserve128 = 0;

	//SmartLoad
	strInverterRealtimeData.Field.wSmartLoadVolt = 0;
	strInverterRealtimeData.Field.wSmartLoadCurr = 0;
	strInverterRealtimeData.Field.wSmartLoadFreq = 0;
	strInverterRealtimeData.Field.wSmartLoadWatt = 0;
	strInverterRealtimeData.Field.wSmartLoadVA =  0;
	strInverterRealtimeData.Field.wSmartLoadVAR = 0;
	strInverterRealtimeData.Field.uwSmartLoadPersent = 0;
	strInverterRealtimeData.Field.wSmartLoadDCV = 0;
	strInverterRealtimeData.Field.uwReserve137 = 0;
	strInverterRealtimeData.Field.uwReserve138 = 0;

	//Battery
	strInverterRealtimeData.Field.wBatVolt = swGetBatVoltFilter();
//	if(suwGetEEPowerConversion())
//	{
//		strInverterRealtimeData.Field.wBatCurr = -(INT16S)((INT32S)strInvPowerConversionData.Field.wBatWatt * 10000 / swGetBatVoltFilter());
//		strInverterRealtimeData.Field.wBatPower = -strInvPowerConversionData.Field.wBatWatt;
//	}
//	else
//	{
		strInverterRealtimeData.Field.wBatCurr = -swGetBatCurrFilter();
		strInverterRealtimeData.Field.wBatPower = -swGetBatWattFilter();
//	}
	strInverterRealtimeData.Field.uwBatSOC = swGetSocNew();//swGetBatSOCReal();
	strInverterRealtimeData.Field.uwReserve143 = swGetMaxCellVoltNew();	// 最大单体电池电压
	strInverterRealtimeData.Field.uwReserve144 = swGetMinCellVoltNew();	// 最小单体电池电压
	strInverterRealtimeData.Field.uwReserve145 = swGetMaxCellTempNew(); // 最大单体电池温度
	strInverterRealtimeData.Field.uwReserve146 = swGetMaxCellTempNew(); // 最小单体电池温度

	//BUS
	strInverterRealtimeData.Field.uwBusVolt = swGetBusVoltFilter();
	strInverterRealtimeData.Field.wBusCurr = swGetBusCurrFilter();
	strInverterRealtimeData.Field.wBusPower = 0;
	strInverterRealtimeData.Field.eAnalogBusPosIso = 0;
	strInverterRealtimeData.Field.eAnalogBusNegIso = 0;
	strInverterRealtimeData.Field.uwReserve152 = 0;
	strInverterRealtimeData.Field.uwReserve153 = 0;
	strInverterRealtimeData.Field.uwReserve154 = 0;
	
	//Temperature
	strInverterRealtimeData.Field.wBoostTemp = 0;
	strInverterRealtimeData.Field.wInvTemp = swGetHsInvTempFilter();
	strInverterRealtimeData.Field.wTraTemp = 0;
	strInverterRealtimeData.Field.wPVTemp = swGetHsPvTempFilter();
	strInverterRealtimeData.Field.wEnviTemp = 0;
	strInverterRealtimeData.Field.wBatHTemp = swGetBat1TempFilter();
	strInverterRealtimeData.Field.wBatLTemp = swGetBat2TempFilter();
	strInverterRealtimeData.Field.wLLCHTemp = swGetLLCTempFilter();
	strInverterRealtimeData.Field.wLLCTraTemp = 0;
	strInverterRealtimeData.Field.uwReserve164 = 0;
	strInverterRealtimeData.Field.uwReserve165 = 0;
	strInverterRealtimeData.Field.uwReserve166 = 0;
	strInverterRealtimeData.Field.uwReserve167 = 0;
	strInverterRealtimeData.Field.uwReserve168 = 0;
	strInverterRealtimeData.Field.uwReserve169 = 0;
	strInverterRealtimeData.Field.eAnalogLeakCurr = 0;

	//Res 171~192
	strInverterRealtimeData.Field.uwReserve171 = 0;
	strInverterRealtimeData.Field.uwReserve172 = 0;
	strInverterRealtimeData.Field.uwReserve173 = 0;
	strInverterRealtimeData.Field.uwReserve174 = 0;
	strInverterRealtimeData.Field.uwReserve175 = 0;
	strInverterRealtimeData.Field.uwReserve176 = 0;
	strInverterRealtimeData.Field.uwReserve177 = 0;
	strInverterRealtimeData.Field.uwReserve178 = 0;
	strInverterRealtimeData.Field.uwReserve179 = 0;
	strInverterRealtimeData.Field.uwReserve180 = 0;
	strInverterRealtimeData.Field.uwReserve181 = 0;
	strInverterRealtimeData.Field.uwReserve182 = 0;
	strInverterRealtimeData.Field.uwReserve183 = 0;
	strInverterRealtimeData.Field.uwReserve184 = 0;
	strInverterRealtimeData.Field.uwReserve185 = 0;
	strInverterRealtimeData.Field.uwReserve186 = 0;
	strInverterRealtimeData.Field.uwReserve187 = 0;
	strInverterRealtimeData.Field.uwReserve188 = 0;
	strInverterRealtimeData.Field.uwReserve189 = 0;
	strInverterRealtimeData.Field.uwReserve190 = 0;
	strInverterRealtimeData.Field.uwReserve191 = 0;
	strInverterRealtimeData.Field.uwReserve192 = 0;

	//Power generation
	strInverterRealtimeData.Field.uwPV1TotalGenEnergyH 	 = 0;//(INT16U)(swGetPV1DayEnergy() >> 16);
	strInverterRealtimeData.Field.uwPV1TotalGenEnergyL 	 = 0;//(INT16U)(swGetPV1DayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwPV2TotalGenEnergyH 	 = 0;//(INT16U)(swGetPV2DayEnergy() >> 16);
	strInverterRealtimeData.Field.uwPV2TotalGenEnergyL 	 = 0;//(INT16U)(swGetPV2DayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwBatTotalChargeH 	 = 0;//(INT16U)(swGetBatChargDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwBatTotalChargeL 	 = 0;//(INT16U)(swGetBatChargDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwBatTotalDisChargeH   = 0;//(INT16U)(swGetBatDisChargDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwBatTotalDisChargeL 	 = 0;//(INT16U)(swGetBatDisChargDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwGridTotalCostEnergyH = 0;//(INT16U)(swGetGridDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwGridTotalCostEnergyL = 0;//(INT16U)(swGetGridDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwGridTotalGenEnergyH  = 0;//(INT16U)(swGetSupplyGridDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwGridTotalGenEnergyL  = 0;//(INT16U)(swGetSupplyGridDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwLoadTotalCostEnergyH = 0;//(INT16U)(swGetLoadDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwLoadTotalCostEnergyL = 0;//(INT16U)(swGetLoadDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwGenTotalCostEnergyH  = 0;//(INT16U)(swGetGenDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwGenTotalCostEnergyL  = 0;//(INT16U)(swGetGenDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwSmartLoadTotalDraEnergyH  = 0;//(INT16U)(swGetSmartLoadDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwSmartLoadTotalDraEnergyL  = 0;//(INT16U)(swGetSmartLoadDayEnergy() & 0x0000FFFF);
	strInverterRealtimeData.Field.uwSmartLoadTotalCostEnergyH = 0;//(INT16U)(swGetSmartLoadDayEnergy() >> 16);
	strInverterRealtimeData.Field.uwSmartLoadTotalCostEnergyL = 0;//(INT16U)(swGetSmartLoadDayEnergy() & 0x0000FFFF);
	//Res 213~224
	strInverterRealtimeData.Field.uwReserve213 = 0;
	strInverterRealtimeData.Field.uwReserve214 = 0;
	strInverterRealtimeData.Field.uwReserve215 = 0;
	strInverterRealtimeData.Field.uwReserve216 = 0;
	strInverterRealtimeData.Field.uwReserve217 = 0;
	strInverterRealtimeData.Field.uwReserve218 = 0;
	strInverterRealtimeData.Field.uwReserve219 = 0;
	strInverterRealtimeData.Field.uwReserve220 = 0;
	strInverterRealtimeData.Field.uwReserve221 = 0;
	strInverterRealtimeData.Field.uwReserve222 = 0;
	strInverterRealtimeData.Field.uwReserve223 = 0;
	strInverterRealtimeData.Field.uwReserve224 = 0;

	//Time Energy
	strInverterRealtimeData.Field.uwPV1DayGenEnergy = 0;
	strInverterRealtimeData.Field.uwPV1MonthGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV1MonthGenEnergyL = 0;
	strInverterRealtimeData.Field.uwPV1YearGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV1YearGenEnergyL = 0;
	strInverterRealtimeData.Field.uwPV2DayGenEnergy = 0;
	strInverterRealtimeData.Field.uwPV2MonthGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV2MonthGenEnergyL = 0;
	strInverterRealtimeData.Field.uwPV2YearGenEnergyH = 0;
	strInverterRealtimeData.Field.uwPV2YearGenEnergyL = 0;
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
	strInverterRealtimeData.Field.uwGenDayCostEnergy = 0;
	strInverterRealtimeData.Field.uwGenMonthCostEnergyH = 0;
	strInverterRealtimeData.Field.uwGenMonthCostEnergyL = 0;
	strInverterRealtimeData.Field.uwGenYearCostEnergyH = 0;
	strInverterRealtimeData.Field.uwGenYearCostEnergyL = 0;
	strInverterRealtimeData.Field.uwSmartLoadDayCostEnergy = 0;
	strInverterRealtimeData.Field.uwSmartLoadMonthCostEnergyH = 0;
	strInverterRealtimeData.Field.uwSmartLoadMonthCostEnergyL = 0;
	strInverterRealtimeData.Field.uwSmartLoadYearCostEnergyH = 0;
	strInverterRealtimeData.Field.uwSmartLoadYearCostEnergyL = 0;
	//Res 272~288
	strInverterRealtimeData.Field.uwReserve272 = 0;
	strInverterRealtimeData.Field.uwReserve273 = 0;
	strInverterRealtimeData.Field.uwReserve274 = 0;
	strInverterRealtimeData.Field.uwReserve275 = 0;
	strInverterRealtimeData.Field.uwReserve276 = 0;
	strInverterRealtimeData.Field.uwReserve277 = 0;
	strInverterRealtimeData.Field.uwReserve278 = 0;
	strInverterRealtimeData.Field.uwReserve279 = 0;
	strInverterRealtimeData.Field.uwReserve280 = 0;
	strInverterRealtimeData.Field.uwReserve281 = 0;
	strInverterRealtimeData.Field.uwReserve282 = 0;
	strInverterRealtimeData.Field.uwReserve283 = 0;
	strInverterRealtimeData.Field.uwReserve284 = 0;
	strInverterRealtimeData.Field.uwReserve285 = 0;
	strInverterRealtimeData.Field.uwReserve286 = 0;
	strInverterRealtimeData.Field.uwReserve287 = 0;
	strInverterRealtimeData.Field.uwReserve288 = 0;

	//BMS
//	if(sbGetEMSBMSConnect())
//	{
//		strInverterRealtimeData.Field.uwBMSWIFIBatMeterStatus = uwGetBMSWIFIBatMeterStatus();
//		strInverterRealtimeData.Field.uwBMSCurrentBMSAddr = sbGetBMSAddr();
//		strInverterRealtimeData.Field.uwBMSFlag = swGetEmsDataParallelStatus();
//		strInverterRealtimeData.Field.uwBMS1ChargeVoltLimit = swGetBmsChargeVoltageLimit();
//		strInverterRealtimeData.Field.uwBMS1DischargeVoltLimit = swGetBmsDischargeVoltageLimit();
//		strInverterRealtimeData.Field.uwBMS1ChargeCurrLimit = swGetBmsChargeCurrentLimit();
//		strInverterRealtimeData.Field.uwBMS1DischargeCurrLimit = swGetBmsDischargeCurrentLimit();
//		strInverterRealtimeData.Field.uwBMS1BmsStatusHi = swGetBmsStatusHigh();
//		strInverterRealtimeData.Field.uwBMS1BmsStatusLo = swGetBmsStatusLow();
//		strInverterRealtimeData.Field.uwBMS1FaultFlagHi = swGetBmsFaultFlagHigh();
//		strInverterRealtimeData.Field.uwBMS1FaultFlagLo = swGetBmsFaultFlagLow();
//		strInverterRealtimeData.Field.uwBMS1AlarmFlagHi = swGetBmsAlarmFlagHigh();	
//		strInverterRealtimeData.Field.uwBMS1AlarmFlagLo = swGetBmsAlarmFlagLow();
//		strInverterRealtimeData.Field.uwBMS1NoticeFlagHi = swGetBmsNoticeFlagHigh();
//		strInverterRealtimeData.Field.uwBMS1NoticeFlagLo = swGetBmsNoticeFlagLow();
//		strInverterRealtimeData.Field.wBMS1TotalCurr = swGetBmsPackCurrent();
//		strInverterRealtimeData.Field.uwBMS1TotalVolt = swGetBmsPackVoltage();
//		strInverterRealtimeData.Field.uwBMS1Rsvd306 = swGetBmsPackVoltageReal();
//		strInverterRealtimeData.Field.uwBMS1Rsvd307 = swGetBmsReservd2();
//		strInverterRealtimeData.Field.uwBMS1TotalSOC = swGetBmsSOC();
//		strInverterRealtimeData.Field.uwBMS1TotalSOH = swGetBmsSOH();
//		strInverterRealtimeData.Field.uwBMS1TotalCapacityHigh = swGetBmsPackCapacityHigh();
//		strInverterRealtimeData.Field.uwBMS1TotalCapacityLow = swGetBmsPackCapacityLow();
//		strInverterRealtimeData.Field.uwBMS1ParallelNumber = swGetBmsParallelNumber();
//		strInverterRealtimeData.Field.uwBMS1ParallelStatus = swGetBmsParallelStatus();
//		strInverterRealtimeData.Field.uwReserve314 = swGetBmsSerialNumber();
//		strInverterRealtimeData.Field.uwReserve315 = swGetBmsSerialStatus();
//		strInverterRealtimeData.Field.uwBMS1MaximumCellVoltNo = swGetBmsMaximumCellVoltageNo();
//		strInverterRealtimeData.Field.uwBMS1MaximumCellVolt = swGetBmsMaximumCellVoltage();
//		strInverterRealtimeData.Field.uwBMS1MinimumCellVoltNo = swGetBmsMinimumCellVoltageNo();
//		strInverterRealtimeData.Field.uwBMS1MinimumCellVolt = swGetBmsMinimumCellVoltage();
//		strInverterRealtimeData.Field.uwBMS1MaximumCellTempeNo = swGetBmsMaximumCellTemperatureNo();
//		strInverterRealtimeData.Field.wBMS1MaximumCellTempe = swGetBmsMaximumCellTemperature();
//		strInverterRealtimeData.Field.uwBMS1MinimumCellTempeNo = swGetBmsMinimumCellTemperatureNo();
//		strInverterRealtimeData.Field.wBMS1MinmumCellTempe = swGetBmsMinimumCellTemperature();
//		strInverterRealtimeData.Field.uwBMSSN1 = 0;
//		strInverterRealtimeData.Field.uwBMSSN2 = 0;
//		strInverterRealtimeData.Field.uwBMSSN3 = 0;
//		strInverterRealtimeData.Field.uwBMSSN4 = 0;
//		strInverterRealtimeData.Field.uwBMSSN5 = 0;
//		strInverterRealtimeData.Field.uwReserve329 = 0;
//		strInverterRealtimeData.Field.uwReserve330 = 0;
//		strInverterRealtimeData.Field.uwReserve331 = 0;
//		strInverterRealtimeData.Field.uwReserve332 = 0;
//	}
//	else
//	{
		strInverterRealtimeData.Field.uwBMSWIFIBatMeterStatus = 0;
		strInverterRealtimeData.Field.uwBMSCurrentBMSAddr = 0;
		strInverterRealtimeData.Field.uwBMSFlag = 0;
		strInverterRealtimeData.Field.uwBMS1ChargeVoltLimit = 0;
		strInverterRealtimeData.Field.uwBMS1DischargeVoltLimit = 0;
		strInverterRealtimeData.Field.uwBMS1ChargeCurrLimit = 0;
		strInverterRealtimeData.Field.uwBMS1DischargeCurrLimit = 0;
		strInverterRealtimeData.Field.uwBMS1BmsStatusHi = 0;
		strInverterRealtimeData.Field.uwBMS1BmsStatusLo = 0;
		strInverterRealtimeData.Field.uwBMS1FaultFlagHi = 0;
		strInverterRealtimeData.Field.uwBMS1FaultFlagLo = 0;
		strInverterRealtimeData.Field.uwBMS1AlarmFlagHi = 0;	
		strInverterRealtimeData.Field.uwBMS1AlarmFlagLo = 0;
		strInverterRealtimeData.Field.uwBMS1NoticeFlagHi = 0;
		strInverterRealtimeData.Field.uwBMS1NoticeFlagLo = 0;
		strInverterRealtimeData.Field.wBMS1TotalCurr = 0;
		strInverterRealtimeData.Field.uwBMS1TotalVolt = 0;
		strInverterRealtimeData.Field.uwBMS1Rsvd306 = 0;
		strInverterRealtimeData.Field.uwBMS1Rsvd307 = 0;
		strInverterRealtimeData.Field.uwBMS1TotalSOC = 0;
		strInverterRealtimeData.Field.uwBMS1TotalSOH = 0;
		strInverterRealtimeData.Field.uwBMS1TotalCapacityHigh = 0;
		strInverterRealtimeData.Field.uwBMS1TotalCapacityLow = 0;
		strInverterRealtimeData.Field.uwBMS1ParallelNumber = 0;
		strInverterRealtimeData.Field.uwBMS1ParallelStatus = 0;
		strInverterRealtimeData.Field.uwReserve314 = 0;
		strInverterRealtimeData.Field.uwReserve315 = 0;
		strInverterRealtimeData.Field.uwBMS1MaximumCellVoltNo = 0;
		strInverterRealtimeData.Field.uwBMS1MaximumCellVolt = 0;
		strInverterRealtimeData.Field.uwBMS1MinimumCellVoltNo = 0;
		strInverterRealtimeData.Field.uwBMS1MinimumCellVolt = 0;
		strInverterRealtimeData.Field.uwBMS1MaximumCellTempeNo = 0;
		strInverterRealtimeData.Field.wBMS1MaximumCellTempe = 0;
		strInverterRealtimeData.Field.uwBMS1MinimumCellTempeNo = 0;
		strInverterRealtimeData.Field.wBMS1MinmumCellTempe = 0;
		strInverterRealtimeData.Field.uwBMSSN1 = 0;
		strInverterRealtimeData.Field.uwBMSSN2 = 0;
		strInverterRealtimeData.Field.uwBMSSN3 = 0;
		strInverterRealtimeData.Field.uwBMSSN4 = 0;
		strInverterRealtimeData.Field.uwBMSSN5 = 0;
		strInverterRealtimeData.Field.uwReserve329 = 0;
		strInverterRealtimeData.Field.uwReserve330 = 0;
		strInverterRealtimeData.Field.uwReserve331 = 0;
		strInverterRealtimeData.Field.uwReserve332 = 0;
//	}


	//EMS
//	if(sbGetEMSBMSConnect())
//	{
//		strInverterRealtimeData.Field.uwEMSTotalSOC = swGetEmsDataTotalSOC();
//		strInverterRealtimeData.Field.uwEMSConnectNumber = swGetEmsDataParallelNumber();
//		strInverterRealtimeData.Field.uwEmsBatLimitVolt = swGetEmsDataChargeVoltageLimit();
//		strInverterRealtimeData.Field.uwReserve336 = 0;
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
//		strInverterRealtimeData.Field.uwReserve336 = 0;
//		strInverterRealtimeData.Field.uwEmsBatCutOffVol = swGetPylonDataDcgVoltLimit();
//		strInverterRealtimeData.Field.uwEmsBatMaxChgCurrent = swGetPylonDataChgCurrLimit();
//		strInverterRealtimeData.Field.uwEmsMaxDisChgCurr = swGetPylonDataDcgCurrLimit();
//		strInverterRealtimeData.Field.uwEmsFaultCode = swGetPylonDataBmsProtect();
//		strInverterRealtimeData.Field.uwEmsFlag = 1;
//		strInverterRealtimeData.Field.uwEmsBatPackSeries = 0;
//	}
//	else
//	{
		strInverterRealtimeData.Field.uwEMSTotalSOC = 0;
		strInverterRealtimeData.Field.uwEMSConnectNumber = 0;
		strInverterRealtimeData.Field.uwEmsBatLimitVolt = 0;
		strInverterRealtimeData.Field.uwReserve336 = 0;
		strInverterRealtimeData.Field.uwEmsBatCutOffVol = 0;
		strInverterRealtimeData.Field.uwEmsBatMaxChgCurrent = 0;
		strInverterRealtimeData.Field.uwEmsMaxDisChgCurr = 0;
		strInverterRealtimeData.Field.uwEmsFaultCode = 0;
		strInverterRealtimeData.Field.uwEmsFlag = 0;
		strInverterRealtimeData.Field.uwEmsBatPackSeries = 0;
//	}
	//Res 343~352
	strInverterRealtimeData.Field.uwReserve343 = 0;
	strInverterRealtimeData.Field.uwReserve344 = 0;
	strInverterRealtimeData.Field.uwReserve345 = 0;
	strInverterRealtimeData.Field.uwReserve346 = 0;
	strInverterRealtimeData.Field.uwReserve347 = 0;
	strInverterRealtimeData.Field.uwReserve348 = 0;
	strInverterRealtimeData.Field.uwReserve349 = 0;
	strInverterRealtimeData.Field.uwReserve350 = 0;
	strInverterRealtimeData.Field.uwReserve351 = 0;
	strInverterRealtimeData.Field.uwReserve352 = 0;

	#warn 故障记录需要放到中断去处理，产生故障时，刷新以下数据，每次只记录当前值，记录故障前先清除原有数据
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
	strInverterRealtimeData.Field.uwReserve371 = 0;
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
	//Res 384~432
	strInverterRealtimeData.Field.uwReserve384 = 0;
	strInverterRealtimeData.Field.uwReserve385 = 0;
	strInverterRealtimeData.Field.uwReserve386 = 0;
	strInverterRealtimeData.Field.uwReserve387 = 0;
	strInverterRealtimeData.Field.uwReserve388 = 0;
	strInverterRealtimeData.Field.uwReserve389 = 0;
	strInverterRealtimeData.Field.uwReserve390 = 0;
	strInverterRealtimeData.Field.uwReserve391 = 0;
	strInverterRealtimeData.Field.uwReserve392 = 0;
	strInverterRealtimeData.Field.uwReserve393 = 0;
	strInverterRealtimeData.Field.uwReserve394 = 0;
	strInverterRealtimeData.Field.uwReserve395 = 0;
	strInverterRealtimeData.Field.uwReserve396 = 0;
	strInverterRealtimeData.Field.uwReserve397 = 0;
	strInverterRealtimeData.Field.uwReserve398 = 0;
	strInverterRealtimeData.Field.uwReserve399 = 0;
	strInverterRealtimeData.Field.uwReserve400 = 0;
	strInverterRealtimeData.Field.uwReserve401 = 0;
	strInverterRealtimeData.Field.uwReserve402 = 0;
	strInverterRealtimeData.Field.uwReserve403 = 0;
	strInverterRealtimeData.Field.uwReserve404 = 0;
	strInverterRealtimeData.Field.uwReserve405 = 0;
	strInverterRealtimeData.Field.uwReserve406 = 0;
	strInverterRealtimeData.Field.uwReserve407 = 0;
	strInverterRealtimeData.Field.uwReserve408 = 0;
	strInverterRealtimeData.Field.uwReserve409 = 0;
	strInverterRealtimeData.Field.uwReserve410 = 0;
	strInverterRealtimeData.Field.uwReserve411 = 0;
	strInverterRealtimeData.Field.uwReserve412 = 0;
	strInverterRealtimeData.Field.uwReserve413 = 0;
	strInverterRealtimeData.Field.uwReserve414 = 0;
	strInverterRealtimeData.Field.uwReserve415 = 0;
	strInverterRealtimeData.Field.uwReserve416 = 0;
	strInverterRealtimeData.Field.uwReserve417 = 0;
	strInverterRealtimeData.Field.uwReserve418 = 0;
	strInverterRealtimeData.Field.uwReserve419 = 0;
	strInverterRealtimeData.Field.uwReserve420 = 0;
	strInverterRealtimeData.Field.uwReserve421 = 0;
	strInverterRealtimeData.Field.uwReserve422 = 0;
	strInverterRealtimeData.Field.uwReserve423 = 0;
	strInverterRealtimeData.Field.uwReserve424 = 0;
	strInverterRealtimeData.Field.uwReserve425 = 0;
	strInverterRealtimeData.Field.uwReserve426 = 0;
	strInverterRealtimeData.Field.uwReserve427 = 0;
	strInverterRealtimeData.Field.uwReserve428 = 0;
	strInverterRealtimeData.Field.uwReserve429 = 0;
	strInverterRealtimeData.Field.uwReserve430 = 0;
	strInverterRealtimeData.Field.uwReserve431 = 0;
	strInverterRealtimeData.Field.uwReserve432 = 0;

}


//0202 0100 1223 1000 0100	// 0100后两位00是补位数用的
void	sInverterInformationDataUpdate(void)
{
	strInverterInformationData.Field.uwInflogType 	 	= uwGetType();			// 设备大类 IVDM:0X59
	strInverterInformationData.Field.uwInflogSubType 	= uwGetSubType();		// 设备子类 IVDM3624:0X0205
	strInverterInformationData.Field.uwInflogCommProVer = 0;					// 通讯协议版本号
	strInverterInformationData.Field.uwInflogCommInfo	= 0x0003;				// 03：波特率9600
	strInverterInformationData.Field.uwInflogSN1 	  	= suwGetEE_SN1();	// SN码，ATE时扫码枪识别写入
	strInverterInformationData.Field.uwInflogSN2 	  	= suwGetEE_SN2();
	strInverterInformationData.Field.uwInflogSN3 	  	= suwGetEE_SN3();
	strInverterInformationData.Field.uwInflogSN4 	  	= suwGetEE_SN4();
	strInverterInformationData.Field.uwInflogSN5 	  	= suwGetEE_SN5();
	strInverterInformationData.Field.uwInflogSNLen   	= suwGetEE_SNLen();	// SN码长度，ATE时扫码枪识别写入，默认18位SN
	strInverterInformationData.Field.uwInflogMVer		= cDspCtrlVersion;		// 主DSP主版本号
	strInverterInformationData.Field.uwInflogMIAPVer	= g_uwBootBV;			// 主DSP IAP版本号
	strInverterInformationData.Field.uwInflogMSubVer	= cDspTempVersion;		// 主DSP子版本号

	strInverterInformationData.Field.uwInflogSVer		= 0;					// 从DSP主版本号
	strInverterInformationData.Field.uwInflogSIAPVer	= 0;					// 从DSP IAP版本号
	strInverterInformationData.Field.uwInflogSSubVer	= 0;					// 从DSP子版本号
	strInverterInformationData.Field.uwInflogDVer		= 0xFFFF;				// 显示板软件主版本号
	strInverterInformationData.Field.uwInflogDIAPVer	= 0xFFFF;				// 显示板软件IAP版本号
	strInverterInformationData.Field.uwInflogDSubVer	= 0xFFFF;				// 显示板软件子版本号
	strInverterInformationData.Field.uwInflogCtrlHwVer  = g_uwBootHV;			// 控制板硬件版本号 //sbGetFlashHwVersion();
	strInverterInformationData.Field.uwInflogPowerHwVer = 1000;					// 功率板硬件版本号
	strInverterInformationData.Field.uwInflogDispHwVer  = 0xFFFF;				// 显示板硬件版本号
	strInverterInformationData.Field.uwInflogOpType 	= 0x0001;				// 1:单相机  3:三相机 	

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
	strInverterInformationData.Field.uwInflogCurrBmsAddr 	= 0;//sbGetBMSAddr();
	strInverterInformationData.Field.uwInflogBmsType 		= 0;//swGetBmsInfoType();
	strInverterInformationData.Field.uwInflogBmsSubType 	= 0;//swGetBmsInfoSubType();
	strInverterInformationData.Field.uwInflogBmsCommProVer  = 0;//swGetBmsInfoCommProVer();
	strInverterInformationData.Field.uwInflogBmsCommInfo 	= 0;//swGetBmsInfoCommInfo();
	strInverterInformationData.Field.uwInflogBmsSN1		  	= 0;//swGetBmsInfoSerial1();
	strInverterInformationData.Field.uwInflogBmsSN2  		= 0;//swGetBmsInfoSerial2();
	strInverterInformationData.Field.uwInflogBmsSN3		  	= 0;//swGetBmsInfoSerial3();
	strInverterInformationData.Field.uwInflogBmsSN4		  	= 0;//swGetBmsInfoSerial4();
	strInverterInformationData.Field.uwInflogBmsSN5		  	= 0;//swGetBmsInfoSerial5();
	strInverterInformationData.Field.uwInflogBmsSNLen		= 0;//swGetBmsInfoSNLen();
	strInverterInformationData.Field.uwInflogBmsDispSwVer   = 0;//swGetBmsInfoDispSwVer();
	strInverterInformationData.Field.uwInflogBmsMCU1SwVer   = 0;//swGetBmsInfoMCU1SwVer();
	strInverterInformationData.Field.uwInflogBmsMCU2SwVer   = 0;//swGetBmsInfoMCU2SwVer();
	strInverterInformationData.Field.uwInflogBmsDispHwVer   = 0;//swGetBmsInfoDispHwVer();
	strInverterInformationData.Field.uwInflogBmsCtrlHwVer   = 0;//swGetBmsInfoCtrlHwVer();
	strInverterInformationData.Field.uwInflogBmsPowerHwVer  = 0;//swGetBmsInfoPowerHwVer();
	strInverterInformationData.Field.uwReservd1  = 0;
	strInverterInformationData.Field.uwLCDDispSwVer  = 0;
	strInverterInformationData.Field.uwReservd2  = 0;
	strInverterInformationData.Field.uwReservd3  = 0;
	strInverterInformationData.Field.uwReservd4  = 0;
	strInverterInformationData.Field.uwReservd5  = 0;
	strInverterInformationData.Field.uwReservd6  = 0;
	strInverterInformationData.Field.uwReservd7  = 0;
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
		g_uwFaultCode = cBootloadFail;
//		sSetFaultCode(cBootloadFail);
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
INT16U	uwGetLLCHTempStartDerat(void)
{
	return 0;//strInvParameterData.Field.uwLLCHTempStartDerat;
}

INT16U	uwGetLLCHTempEndDerat(void)
{
	return 0;//strInvParameterData.Field.uwLLCHTempEndDerat;
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

INT16S	uwGetGridInputWattMax(void)
{
	return strInvParameterData.Field.uwGridInputWattMax;
}

INT16S	uwGetGridInputCurrMax(void)
{
	return strInvParameterData.Field.uwGridInputCurrMax;
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

INT16U	uwGetGridCurrOver1(void)
{
	return strInvParameterData.Field.uwGridInputCurrOver1;
}

INT16U	uwGetGridCurrOver2(void)
{
	return strInvParameterData.Field.uwGridInputCurrOver2;
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
	strWifiIotData.Field.uwIotVersion = uwTemp;
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

void	sSetWifiIotRSSI(INT16S uwTemp)
{
	strWifiIotData.Field.uwIotRSSI = uwTemp;
}

void	sSetWifiIotBleConn(INT16U uwTemp)
{
	strWifiIotData.Field.uwIotBleConn = uwTemp;
}

// 读取单台电池板数据状态标志
void	uwSetBmsDataFlag(INT16U uwTemp)
{
	strBMSWIFIBatMeterStatus.bits.bGetBmsDataFlag = uwTemp;
}


