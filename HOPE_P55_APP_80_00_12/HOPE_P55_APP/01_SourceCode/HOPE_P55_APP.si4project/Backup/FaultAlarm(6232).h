/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __FAULT_ALARM_H__
#define __FAULT_ALARM_H__


/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __FAULT_ALARM_C__
#define FAULT_ALARM
#else
#define FAULT_ALARM  extern
#endif

///////////////////////////////////////////////////////////////////故障码
// for test
#define cCircirtTempOver		34	// 散热器1温度保护
#define cInnelTempOver			35	// 散热器2温度保护

// PV
#define cPV1VoltOver			1 	// PV1过压故障				// 支持 改成告警生效
#define cPV2VoltOver			2 	// PV2过压故障
#define cPV1CurrOver			3 	// PV1过流故障				// 支持 改成告警生效
#define cPV2CurrOver			4 	// PV2过流故障
#define cPV1RevConnect			5	// PV1反接故障
#define cPV2RevConnect			6	// PV2反接故障
#define cPVPVArcDrawing			7	// PV拉弧故障
#define cPVShort				8 	// PV短路故障
#define cSolarPowerAbnormal		9	// PV过功率
#define cPVCircirtTempOver		10	// PV过温故障	 			// 支持 改成告警生效
#define cPVParaFail				11	// PV并联故障
#define cPVNtcConnect			12	// PV BUCK NTC未接 		// 支持 改成告警生效
#define cPVLLCNtcConnect		13	// PV-LLC-NTC未接

// BAT
#define cBatVoltOver 			14	// 电池软件过压故障				// 支持
#define cBatVoltUnder			15	// 电池欠压故障
#define cBatCurrOver			16	// 电池软件过流故障
#define cBatRevConnect			17	// 电池反接故障	
#define cBatSOCUnder			18	// 电池SOC低故障
#define cBatArcDrawing			19	// 电池拉弧故障

// BUS
#define cDCDCSoftTimeOut		20	// DCDC软启故障
#define cDCDCCurrOver			21	// DCDC软件过流故障			// 支持
#define cDCDCHWCurrOver			22	// DCDC硬件过流故障
#define cDCDCCircirtTempOver	23	// DCDC过温故障
#define cLLCSoftTimeOut			24	// LLC软启故障
#define cLLCCurrOver			25	// LLC软件过流故障
#define cLLCHWCurrOver			26	// LLC硬件过流故障
#define cLLCLPTempOver			27	// LLC低压侧过温故障			// 支持
#define cLLCTraTempOver			28	// LLC变压器过温故障			// 支持
#define cBusVoltOver			29	// 母线软件过压故障				// 支持
#define cBusHWVoltOver			30	// 母线硬件过压故障
#define cBusVoltUnder			31	// 母线欠压故障				// 支持
#define cBusSoftTimeOut			32	// 母线软启故障				// 支持

// INV
#define cInvSelfCheck			33	// 逆变自检故障
#define cInvSoftTimeOut			34	// 逆变软起故障				// 支持
#define cInvVoltHigh			35	// 逆变电压故障				// 支持
#define cInvCurrOver			36	// 逆变软件过流故障				// 支持
#define cInvHWCurrOver			37	// 逆变硬件过流故障				// 支持
#define cInvShort				38 	// 逆变短路故障				// 支持
#define cRINVDCVoltSenserFault	39	// 逆变电压直流分量故障
#define cRINVDCCurrSenserFault	40	// 逆变电流直流分量故障
#define cInvCircirtTempOver		41  // 逆变散热器过温故障			// 支持
#define cInvBackflow			42	// 逆变反灌故障
#define cInvTarRevConnect		43	// 逆变变压器反接故障
#define cInvTarOpen				44	// 逆变变压器绕组开路
#define cInvTarNtcConnect		45	// 逆变变压器NTC未接
#define cInvNtcConnect			46	// 逆变散热器NTC未接			// 支持
#define cInvTarTempOver			47	// 逆变变压器过温故障
// Load
#define cOverLoad				48	// 负载过载故障				// 支持
#define cOutputVoltLow			49	// 输出电压低压故障				// 支持
#define cOutputVoltHigh			50	// 输出电压高压故障				// 支持

// SYS
#define cEPOFault				51	// EPO故障
#define cBATTempOver			52	// 电池端过温故障
#define cFan1Fault				53	// 风扇1故障
#define cFan2Fault				54	// 风扇2故障
#define cFan3Fault				55	// 风扇3故障
#define cEEPROMFault			56	// EEPROM故障				// 支持


// 安规
#define cPvISOChkFault			57	// PV绝缘检测故障
#define cBusISOChkFault			58	// BUS绝缘对地故障
#define cGridRlyOpen			59	// 电网继电器开路故障
#define cGridRlyShort			60	// 电网继电器短路故障
#define cGenRlyOpen				61	// 油机继电器开路故障
#define cGenRlyShort			62	// 油机继电器短路故障
#define cInvRlyOpen				63	// 逆变继电器开路故障
#define cInvRlyShort			64	// 逆变继电器短路故障
#define cOpRlyOpen				65	// 负载继电器开路故障
#define cOpRlyShort				66	// 负载继电器短路故障
#define cPvRlyOpen				67	// PV继电器开路故障
#define cPvRlyShort				68	// PV继电器短路故障

// PARA 并机
#define cParaCarrierFault		69	// 并机载波故障
#define cParaCanCommFail		79	// 并机CAN通信故障
#define cParaHOSTLineLoss		71	// 并机主机丢失故障
#define cParaWaveFault			72	// 并机方波故障
#define cParaProtocolFault		73	// 并机协议错误
#define cParaCurrSharFault		74	// 并机均流故障
#define cParaModeFault			75	// 并机模式设置错误
#define cParaBatVoltDistinct	76	// 并机电池电压等级不同
#define cParaRatedVolt			77	// 并机额定电压等级不同

// 补充
#define cDCDCCTSenserFault		78	// DCDC电流传感器故障	
#define cINVCTSenserFault		79	// 逆变电流传感器故障				// 支持
#define cOPCTSenserFault 		80	// 输出电流传感器故障				// 支持
#define cGridCTSenserFault		81	// 市电电流传感器故障
#define cGenCTSenserFault		82	// 油机电流传感器故障
#define cPvCTSenserFault		83	// PV电流传感器故障				// 支持
#define cLineRevConnectFault	84	// 交流线反接故障
#define cBootloadFail			85	// 缺失BootLoader故障			// 支持

#define cAuxPowerFault			86	// 辅源故障	
#define cPVBusFastOV			87	// PVBus过压	
#define cWireFault				88	///接线故障

#define cBatHNtcConnect			89	// 电池正 NTC未接/过温				// 支持
#define cBatLNtcConnect			90	// 电池负 NTC未接/过温 			// 支持
#define cGridCurrOver			91	// 市电过流 					// 支持
#define cOPCurrOver				92	// 输出软件过流故障					// 支持
#define cModelFault				93	// 机型识别错误					// 支持

///////////////////////////////////////////////////////////////////告警码
// BAT	
#define cBatVoltOverAlarm 		1	// 电池过压告警	
#define cBatVoltLowAlarm 		2	// 电池欠压告警					// 支持
#define cBatSocLowAlarm			3	// 电池SOC低告警
#define cBatOpenAlarm			4	// 电池开路告警					// 支持

// Grid		
#define cGridVoltOverAlarm		5	// 电网过压告警					// 支持
#define cGridVoltLowAlarm		6	// 电网欠压告警					// 支持
#define cGridFreqOverAlarm		7	// 电网过频告警					// 支持
#define cGridFreqLowAlarm		8	// 电网欠频告警					// 支持
#define cGridReverseAlarm		9	// 电网反序告警
#define cGridLoadOverAlarm		10	// 电网过载告警					// 支持
#define cGridActiveIsland_Alarm	11	// 主动孤岛告警					// 支持
#define cGridUnbalance_Alarm	12	// 电网不平衡告警
#define cGridLackPhaseAlarm		13	// 电网缺相告警
#define cGridAbnormalAlarm		14	// 市电丢失

// Gen
#define cGenVoltOverAlarm		15	// 油机过压告警
#define cGenVoltLowAlarm		16	// 油机欠压告警
#define cGenFreqOverAlarm		17	// 油机过频告警
#define cGenFreqLowAlarm		18	// 油机欠频告警
#define cGenReverseAlarm		19	// 油机反序告警
#define cGenLoadOverAlarm		20	// 油机过载告警
#define cGenUnbalanceAlarm		21	// 油机不平衡告警
#define cGenLackPhaseAlarm		22	// 油机缺相告警
#define cGenAbnormalAlarm		23	// 油机丢失
	
//SYS	
#define cSinkTempOverDeratAlarm 24	// 散热器过温降额告警
#define cLoadOverAlarm 			25	// 负载过载告警					// 支持
#define cFan1Alarm 				26	// 风扇1告警					// 支持
#define cFan2Alarm 				27	// 风扇2告警					// 支持
#define cFan3Alarm 				28	// 风扇3告警
#define cSelfAgingAlarm 		29	// 老化模式告警
#define cBatWakeUpAlarm 		30	// 锂电唤醒告警
#define cMeterComAlarm 			31	// 防逆流设备通信告警
#define cComDSPToMCUAlarm 		32	// MCU通讯异常
#define cBatTempOverDerateAlarm 33	// 电池过温降额告警
#define cBatVoltLowDerateAlarm 	34	// 电池低压降额告警					// 支持

// BMS
#define cBMSComAlarm			35	// BMS通讯故障
#define cBMSVoltOverAlarm		36	// BMS过压告警					// 支持，只在BMS信息界面显示
#define cBMSVoltLowAlarm		37	// BMS欠压告警					// 支持，只在BMS信息界面显示
#define cBMSTempOverAlarm		38	// BMS过温告警
#define cBMSTempLowAlarm		39	// BMS低温告警
#define cBMSStopChargeAlarm		40	// BMS停充告警
#define cBMSStopDischargeAlarm	41	// BMS停放告警
#define cBMSForceChargeAlarm	42	// BMS强充告警
#define cBMSVersionError		43	// BMS版本错误
#define cBMSCellVoltHiAlarm		44 	// BMS电芯过压					// 支持，只在BMS信息界面显示
#define cBMSCellVoltLowAlarm	45	// BMS电芯欠压					// 支持，只在BMS信息界面显示
#define cBMSChgCurrHiAlarm		46 	// BMS电池充电过流				// 支持，只在BMS信息界面显示
#define cBMSDisChgCurrHiAlarm	47	// BMS电池放电过流				// 支持，只在BMS信息界面显示
#define cBMSCellTempHiAlarm		48	// BMS电芯过温					// 支持，只在BMS信息界面显示
#define cBMSCellTempLowAlarm	49	// BMS电芯低温					// 支持，只在BMS信息界面显示
#define cBMSHsTempHiAlarm		50	// BMS电池散热器温度高				// 支持，只在BMS信息界面显示
#define cBMSHsTempLowAlarm		51	// BMS电池散热器温度低
#define cBMSSampSensorAlarm		52	// BMS电池电流传感器异常				// 支持，只在BMS信息界面显示
#define cBMSOtherAlarm			53	// 其他BMS告警
#define cBMSOtherAlarm1			54	// 其他BMS告警
#define cBMSOtherAlarm2			55	// 其他BMS告警					// 支持，只在BMS信息界面显示

#define cPvBTNTCLossAlarm		56	// PV boost NTC未接		// 支持
#define cPv1OVAlarm				57	// PV1过压告警				// 支持
#define cPv2OVAlarm				58	// PV2过压告警	
#define cPv1UVAlarm				59	// PV1欠压告警				
#define cPv2UVAlarm				60	// PV2欠压告警
#define cPv1OCAlarm				61	// PV1过流告警				// 支持
#define cPv2OCAlarm				62	// PV2过流告警
#define cPv1OTAlarm				63	// PV1过温告警				// 支持
#define cPv2OTAlarm				64	// PV2过温告警


#define cFaultBusNum			10	// 故障缓存数组数量
#define cAlarmBusNum			5	// 告警缓存数组数量

union T_FAULT_BASE
{
	struct T_FAULT_BIT160_FEILD
	{
	//  故障信息1 大类汇总
		// BIT0-3
		INT16U	bFaultPV:1;					// PV类故障
		INT16U	bFaultBAT:1;				// 电池类故障
		INT16U	bFaultBUS:1;				// BUS类故障
		INT16U	bFaultINV:1;				// 逆变类故障
		
		// BIT4-7
		INT16U	bFaultGRID:1;				// 电网类故障
		INT16U	bFaultLOAD:1;				// 负载类故障
		INT16U	bFaultSYS:1;				// 系统类故障
		INT16U	bFaultSR:1;					// 安规类故障	 Safety Regulation
		
		// BIT8-11
		INT16U	bFaultPARA:1;				// 并机类故障
		INT16U 	bFaultRsvd3:3;				// 预留
		
		// BIT12-15
		INT16U 	bFaultRsvd4:4;				// 预留

	//  故障信息2 PV & Bat
		INT16U 	bPV1OV:1;					//PV1过压故障					支持
		INT16U 	bPV2OV:1;					//PV2过压故障 
		INT16U 	bPV1OC:1;					//PV1过流故障					支持
		INT16U 	bPV2OC:1;					//PV2过流故障

		INT16U 	bPV1Reverse:1;				//PV1反接故障 
		INT16U 	bPV2Reverse:1;				//PV2反接故障 
		INT16U 	bPVArc:1;					//PV拉弧故障	
		INT16U 	bPVShort:1;					//PV短路故障	

		INT16U 	bPVPowerAbnormal:1;			//PV过功率 
		INT16U 	bPVOT:1;					//PV过温故障					支持
		INT16U 	bPVParaFault:1;				//PV并联故障	
		INT16U 	bPVBoostNTCLoss:1;			//PV-BOOST/BUCK-NTC未接	

		INT16U 	bPVLLCNTCLoss:1;			//PV-LLC-NTC未接	
		INT16U 	bBatSoftOV:1;				//电池软件过压故障					支持
		INT16U 	bBatUV:1;					//电池欠压故障	
		INT16U 	bBatSoftOC:1;				//电池软件过流故障	

	//  故障信息3 Bat & BUS
		INT16U 	bBatReverse:1;				//电池反接故障	
		INT16U 	bBatSOCLow:1;				//电池SOC低故障	
		INT16U 	bBatArcFault:1;				//电池拉弧故障
		INT16U 	bDcDcSoftFault:1;			//DCDC软启故障
		
		INT16U 	bDcDcSoftOC:1;				//DCDC软件过流故障				支持
		INT16U 	bDcDcHardOC:1;				//DCDC硬件过流故障
		INT16U 	bDCDCOT:1;					//DCDC过温故障
		INT16U 	bLlcSoftFault:1;			//LLC软启故障
		
		INT16U 	bLlcSoftOC:1;				//LLC软件过流故障
		INT16U 	bLlcHardOC:1;				//LLC硬件过流故障	
		INT16U 	bLlcLowSideOT:1;			//LLC低压侧过温/NTC未接故障			支持
		INT16U 	bLlcTXOT:1;					//LLC变压器过温故障	
		
		INT16U 	bBusSoftOV:1;				//母线软件过压故障					支持
		INT16U 	bBusHardOV:1;				//母线硬件过压故障	
		INT16U 	bBusUV:1;					//母线欠压故障					支持
		INT16U 	bBusSoftFault:1;			//母线软启故障					支持

	//  故障信息4 INV & LOAD	
		INT16U 	bInvSelfCheckFault:1;		//逆变自检故障	
		INT16U 	bInvSoftFault:1;			//逆变软起故障					支持
		INT16U 	bInvVoltFault:1;			//逆变电压故障					支持	
		INT16U 	bInvSoftOC:1;				//逆变软件过流故障					支持	
		
		INT16U 	bInvHardOC:1;				//逆变硬件过流故障					支持	
		INT16U 	bInvShort:1;				//逆变短路故障					支持	
		INT16U 	bInvVoltDC:1;				//逆变电压直流分量故障	
		INT16U 	bInvCurrDC:1;				//逆变电流直流分量故障	
		
		INT16U 	bInvHsOT:1;					//逆变散热器过温故障 				支持	
		INT16U 	bInvNegPower:1;				//逆变反灌故障	
		INT16U 	bInvTXReverse:1;			//逆变变压器反接故障 
		INT16U 	bInvTXOpen:1;				//逆变变压器绕组开路 
		
		INT16U 	bInvTXNTCLoss:1;			//逆变变压器NTC未接	
		INT16U 	bInvHsNTCLoss:1;			//逆变散热器NTC未接				支持	
		INT16U 	bInvTXOT:1;					//逆变变压器过温故障 
		INT16U 	bLoadOverLoad:1;			//负载过载故障					支持	

	//  故障信息5 LOAD & 安规		
		INT16U 	bOutUV:1;					//输出电压低压故障					支持
		INT16U 	bOutOV:1;					//输出电压高压故障					支持
		INT16U 	bEPO:1;						//EPO故障	
		INT16U 	bBatOVT:1;					//BAT端过温故障	
		
		INT16U 	bFan1Fault:1;				//风扇1故障	
		INT16U 	bFan2Fault:1;				//风扇2故障	
		INT16U 	bFan3Fault:1;				//风扇3故障	
		INT16U 	bEepromFault:1;				//EEPROM故障					支持
		
		INT16U 	bSafePvIso:1;				//PV绝缘检测故障	
		INT16U 	bSafeBusIso:1;				//BUS绝缘对地故障	
		INT16U 	bGridRelayOpen:1;			//电网继电器开路故障 
		INT16U 	bGridRelayShort:1;			//电网继电器短路故障 
		
		INT16U 	bGenRelayOpen:1;			//油机继电器开路故障 
		INT16U 	bGenRelayShort:1;			//油机继电器短路故障 
		INT16U 	bInvRelayOpen:1;			//逆变继电器开路故障 
		INT16U 	bInvRelayShort:1;			//逆变继电器短路故障 

	//  故障信息6 安规	& 并机 & 补充
		INT16U 	bLoadRelayOpen:1;			//负载继电器开路故障 
		INT16U 	bLoadRelayShort:1;			//负载继电器短路故障 
		INT16U 	bPvRelayOpen:1;				//PV继电器开路故障 
		INT16U 	bPvRelayShort:1;			//PV继电器短路故障 
		
		INT16U 	bPWMSyncFault:1;			//并机载波故障	
		INT16U 	bParallelCANFault:1;		//并机CAN通信故障	
		INT16U 	bMasterLoss:1;				//并机主机丢失故障	
		INT16U 	bZeroSyncFault:1;			//并机方波故障	
		
		INT16U 	bParaVersionDiff:1;			//并机协议错误	
		INT16U 	bParaShareCurrFault:1;		//并机均流故障	
		INT16U 	bParaOpSetDiff:1;			//并机模式设置错误	
		INT16U 	bParaBatVoltSetDiff:1;		//并机电池电压等级不同
		
		INT16U 	bParaRateVoltSetDiff:1;		//并机额定电压等级不同
		INT16U 	bDCDCCTFault:1;				//DCDC电流传感器故障	
		INT16U 	bINVCTFault:1;				//逆变电流传感器故障 			支持	
		INT16U 	bOPCTFault:1;				//输出电流传感器故障 			支持	 

	//  故障信息7 并机 & 补充	
		INT16U 	bGridCTFault:1;				//市电电流传感器故障 
		INT16U 	bGenCTFault:1;				//油机电流传感器故障 
		INT16U 	bPVCTFault:1;				//PV电流传感器故障 			支持
		INT16U 	bInOutReverse:1;			//交流线反接故障	
		
		INT16U 	bBootloadFail:1;			//缺失BootLoader故障		支持
		INT16U 	bAuxPowerFault:1;			//辅源故障	
		INT16U 	bPVBusFastOV:1;				//PVBus过压 
		INT16U 	bWireFault:1;				//接线故障	
		
		INT16U	bBatHOT:1; 					//电池正过温					支持
		INT16U	bBatLOT:1; 					//电池负过温					支持
		INT16U 	bGridCurrOver:1;			//市电过流					支持
		INT16U 	bOPCurrOver:1;				//输出电流过流				支持
		
		INT16U	bModelFault:1; 				//机型识别错误
		INT16U	bFault7Rsvd4:3; 			// 预留
		

	//  故障信息8    补充	
		INT16U 	bFault8Rsvd1:4;				// 预留
		
		INT16U	bFault8Rsvd2:4; 			// 预留
		
		INT16U 	bFault8Rsvd3:4;				// 预留
		
		INT16U	bFault8Rsvd4:4; 			// 预留

	//  故障信息9    补充	
		INT16U 	bFault9Rsvd1:4;				// 预留
		
		INT16U	bFault9Rsvd2:4; 			// 预留
		
		INT16U 	bFault9Rsvd3:4;				// 预留
		
		INT16U	bFault9Rsvd4:4; 			// 预留

	//  故障信息10    补充	
		INT16U 	bFault10Rsvd1:4;			// 预留
		
		INT16U	bFault10Rsvd2:4; 			// 预留
		
		INT16U 	bFault10Rsvd3:4;			// 预留
		
		INT16U	bFault10Rsvd4:4; 			// 预留
	} bits;
	INT16U uwData[cFaultBusNum];
};

union T_ALARM_BASE
{
	struct T_ALARM_BIT80_FEILD
	{
	// 告警信息1 Bat & Grid & Gen  
		INT16U	bBatOVAlarm:1;				//电池过压告警	
		INT16U	bBatUVAlarm:1;				//电池欠压告警		支持
		INT16U	bBatSOCLowAlarm:1;			//电池SOC低告警	
		INT16U	bBatOpenAlarm:1;			//电池开路告警		支持
		
		INT16U	bGridOV:1;					//电网过压告警		支持
		INT16U	bGridUV:1;					//电网欠压告警		支持	
		INT16U	bGridOF:1;					//电网过频告警		支持	
		INT16U	bGridUF:1;					//电网欠频告警		支持
		
		INT16U	bGridReverse:1;				//电网反序告警	
		INT16U	bGridOverLoad:1;			//电网过载告警		支持
		INT16U	bGridActiveIsland:1;		//主动孤岛告警		支持	
		INT16U	bGridUnbalance:1;			//电网不平衡告警
		
		INT16U	bGridLackPhaseAlarm:1;		//电网缺相告警	
		INT16U	bGridAbnormalAlarm:1;		//市电丢失
		INT16U	bGenOV:1;					//油机过压告警	
		INT16U	bGenUV:1;					//油机欠压告警	

	// 告警信息2 Gen & sys	
		INT16U	bGenOF:1;					//油机过频告警	
		INT16U	bGenUF:1;					//油机欠频告警	
		INT16U	bGenReverse:1;				//油机反序告警	
		INT16U	bGenOverLoad:1;				//油机过载告警
		
		INT16U	bGenUnbalance:1;			//油机不平衡告警	
		INT16U	bGenLackPhaseAlarm:1;		//油机缺相告警	
		INT16U	bGenAbnormalAlarm:1;		//油机丢失	
		INT16U	bSinkOVTAlarm:1;			//散热器过温降额告警
		
		INT16U	bOverLoadAlarm:1;			//负载过载告警	  	支持	
		INT16U	bFAN1Alarm:1;				//风扇1告警			支持
		INT16U	bFAN2Alarm:1;				//风扇2告警			支持
		INT16U	bFAN3Alarm:1;				//风扇3告警
		
		INT16U	bSelfAgingAlarm:1;			//老化模式告警
		INT16U	bBatWakeUpAlarm:1;			//锂电唤醒告警
		INT16U	bMeterComAlarm:1;			//防逆流设备通信告警
		INT16U	bMCUCommuniAlarm:1;			//MCU通讯异常

	// 告警信息3 sys & BMS
		INT16U	bBAT_OT:1;					//电池过温降额告警	
		INT16U	bBAT_UT:1;					//电池低压降额告警			支持	
		INT16U	bBMSCommuniAlarm:1;			//BMS通讯故障 
		INT16U	bBMS_OV:1;					//BMS过压告警
		
		INT16U	bBMS_UV:1;					//BMS欠压告警 
		INT16U	bBMS_OT:1;					//BMS过温告警 
		INT16U	bBMS_UT:1;					//BMS低温告警 
		INT16U	bBMS_StopCharg:1;			//BMS停充告警
		
		INT16U	bBMS_StopDisCharg:1;		//BMS停放告警 
		INT16U	bBMS_ForceCharg:1;			//BMS强充告警 
		INT16U	bBMS_VersionError:1;		//BMS版本错误 
		INT16U	bBMS_CellOV:1;				//BMS电芯过压
		
		INT16U	bBMS_CellUV:1;				//BMS电芯欠压 
		INT16U	bBMS_ChgCurrHiAlarm:1;		//BMS电池充电过流	
		INT16U	bBMS_DischgCurrHiAlarm:1;	//BMS电池放电过流	
		INT16U	bBMS_CellOT:1;				//BMS电芯过温

	// 告警信息4 sys & BMS	
		INT16U	bBMS_CellUT:1;				//BMS电芯低温 
		INT16U	bBMS_HsTempHi_Alarm:1;		//BMS电池散热器温度高 
		INT16U	bBMS_HsTempLo_Alarm:1;		//BMS电池散热器温度低 
		INT16U	bBMS_SampSensor_Alarm:1;	//BMS电池电流传感器异常
		
		INT16U	bBMS_OtherAlarm:1;			//其他BMS告警
		INT16U 	bAlarm4Rsvd2:2;				// 预留
		INT16U	bPvBTNTCLoss:1;				// PV boost NTC未接

		INT16U	bPv1OVAlarm:1;				// PV1过压告警						支持	
		INT16U	bPv2OVAlarm:1;				// PV2过压告警	
		INT16U	bPv1UVAlarm:1;				// PV1欠压告警						支持	
		INT16U	bPv2UVAlarm:1;				// PV2欠压告警

		INT16U	bPv1OCAlarm:1;				// PV1过流告警						支持	
		INT16U	bPv2OCAlarm:1;				// PV2过流告警
		INT16U	bPv1OTAlarm:1;				// PV1过温告警						支持	
		INT16U	bPv2OTAlarm:1;				// PV2过温告警
		
	// 告警信息5 预留
		INT16U 	bAlarmLowBatCutOff:1;		// 电池低压断输出						支持	
		INT16U 	bAlarm5Rsvd1:3;				// 预留
		
		INT16U 	bAlarm5Rsvd2:4;				// 预留
		
		INT16U 	bAlarm5Rsvd3:4;				// 预留
		
		INT16U 	bAlarm5Rsvd4:4;				// 预留
	} bits;
	INT16U uwData[cAlarmBusNum];
};

FAULT_ALARM union T_FAULT_BASE T_FAULT_DATA;
FAULT_ALARM union T_ALARM_BASE T_ALARM_DATA;

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
FAULT_ALARM void	sFaultAlarmInit(void);			// 故障告警标识初始化


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
FAULT_ALARM void sFaultRstCntProc(INT16U uwFilter);



/********************************************************************************
* Input interface Routines														*
********************************************************************************/


#endif	// __FAULT_ALARM_H__

