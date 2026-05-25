/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INVERTER_PROCESS_H__
#define __INVERTER_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INVERTER_PROCESS_C__
#define INVERTER_PROCESS
#else
#define INVERTER_PROCESS extern
#endif


// 机型识别
#define	cMODEL_RSVD00_LO_LIMIT			0
#define	cMODEL_RSVD00_UP_LIMIT			205
#define	cMODEL_RSVD01_LO_LIMIT			cMODEL_RSVD00_UP_LIMIT
#define	cMODEL_RSVD01_UP_LIMIT			614
#define	cMODEL_RSVD02_LO_LIMIT			cMODEL_RSVD01_UP_LIMIT
#define	cMODEL_RSVD02_UP_LIMIT			1024
#define	cMODEL_RSVD03_LO_LIMIT			cMODEL_RSVD02_UP_LIMIT
#define	cMODEL_RSVD03_UP_LIMIT			1434
#define	cMODEL_RSVD04_LO_LIMIT			cMODEL_RSVD03_UP_LIMIT
#define	cMODEL_RSVD04_UP_LIMIT			1843
#define	cMODEL_RSVD05_LO_LIMIT			cMODEL_RSVD04_UP_LIMIT
#define	cMODEL_RSVD05_UP_LIMIT			2253
#define	cMODEL_RSVD06_LO_LIMIT			cMODEL_RSVD05_UP_LIMIT
#define	cMODEL_RSVD06_UP_LIMIT			2662
#define	cMODEL_RSVD07_LO_LIMIT			cMODEL_RSVD06_UP_LIMIT
#define	cMODEL_RSVD07_UP_LIMIT			3072
#define	cMODEL_RSVD08_LO_LIMIT			cMODEL_RSVD07_UP_LIMIT
#define	cMODEL_RSVD08_UP_LIMIT			3482
#define	cMODEL_RSVD09_LO_LIMIT			cMODEL_RSVD08_UP_LIMIT
#define	cMODEL_RSVD09_UP_LIMIT			3891
#define	cMODEL_RSVD10_LO_LIMIT			cMODEL_RSVD09_UP_LIMIT
#define	cMODEL_RSVD10_UP_LIMIT			4096


#define	cGET_BMSDATA_FLAG_WAIT			0	// 等待中
#define	cGET_BMSDATA_FLAG_READING		1	// 读取中
#define	cGET_BMSDATA_FLAG_READOK		2	// 读取完成

union BMS_WIFI_Bat_MeterStatus
{
	struct BMS_WIFI_Bat_MeterStatus_FEILD
	{
		// BIT0-7
		INT16U	bWiFiRestart:1;				// WIFI复位重启			置1
		INT16U	bBmsCnonect:1;				// 电池包连接状态			1：已连   0：未连
		INT16U	bElectricityMeter:1;		// 电表连接状态    		1：已连   0：未连
		INT16U	bGetBmsDataFlag:2;			// 读取单台电池板数据状态标志,0：等待中 1：读取中  2：读取完成
		INT16U	bReserve1:3;				// 预留
		
		// BIT8-11
		INT16U	bReserve2:4;				// 预留
		// BIT12-15
		INT16U	bReserve3:4;				// 预留
	}bits;
	INT16U wData;
};

struct	INVERTER_REALTIME_DATA_FEILD
{
	INT16U	uwSettingDataSn; 	//	0	设置参数区流水号
	INT16U	uwWorkMode;			//	1	模式/Mode
	INT16U	uwState1;			//	2	状态位1（按bit区分）
	INT16U	uwState2;			//	3	状态位2（按bit区分）
	INT16U	uwState3;			//	4	状态位3（按bit区分）
	INT16U	uwState4;			//	5	状态位4（按bit区分）
	INT16U	uwState5;			//	6	状态位5（按bit区分）
	INT16U	uwState6;			//	7	状态位6（按bit区分）
	INT16U	uwParallelMode;		//	8	并机模式
	INT16U	uwParallelState1;	//	9	并机状态位1（按bit区分）
	INT16U	uwParallelState2;	//	10	并机状态位2（按bit区分）
	INT16U	uwReserve12; 		//	11	预留12
	INT16U	uwReserve13; 		//	12	预留13
	INT16U	uwReserve14; 		//	13	预留14
	INT16U	uwReserve15; 		//	14	预留15
	INT16U	uwReserve16; 		//	15	预留16
	
	INT16U	uwYearMonth; 		//	16	时间：年-月
	INT16U	uwDayHour;			//	17	时间：日-时
	INT16U	uwMinuteSecond;		//	18	时间：分-秒
	INT16U	uwWeek;				//	19	时间：星期
	INT16U	uwAlarmCode; 		//	20	告警码
	INT16U	uwFaultCode; 		//	21	故障码
	INT16U	uwAlarmState1;		//	22	警告标志 1
	INT16U	uwAlarmState2;		//	23	警告标志 2
	INT16U	uwAlarmState3;		//	24	警告标志 3
	INT16U	uwAlarmState4;		//	25	警告标志 4
	INT16U	uwReserve27;		//	26	预留27
	INT16U	uwReserve28;		//	27	预留28
	INT16U	uwReserve29;		//	28	预留29
	INT16U	uwReserve30;		//	29	预留30
	INT16U	uwFaultState1;		//	30	故障标志1
	INT16U	uwFaultState2;		//	31	故障标志2
	
	INT16U	uwFaultState3;		//	32	故障标志3
	INT16U	uwFaultState4;		//	33	故障标志4
	INT16U	uwFaultState5;		//	34	故障标志5
	INT16U	uwFaultState6;		//	35	故障标志6
	INT16U	uwFaultState7;		//	36	故障标志7
	INT16U	uwFaultState8;		//	37	故障标志8
	INT16U	uwFaultState9;		//	38	故障标志9
	INT16U	uwFaultState10;		//	39	故障标志10
	INT16U	uwReserve41; 		//	40	预留41
	INT16U	uwReserve42; 		//	41	预留42
	INT16U	uwReserve43; 		//	42	预留43
	INT16U	uwReserve44; 		//	43	预留44
	INT16U	uwPowerFlowMsg;		//	44	能流信息
	INT16S	wBatPowerConvertion; //	45	电池折算功率
	INT16S	wPVPowerConvertion;	//	46	PV输入折算功率
	INT16S	wGridPowerConvertion;//	47	总市电折算功率
	
	INT16S	wGenPowerConvertion;//	48	总油机折算功率
	INT16U	wLoadPowerConvertion;//	49	负载用电折算功率
	INT16U	uwOnGridLoadPowerConvertion;//	50	并网侧负载功率
	INT16U	uwBatSocConvertion;	//	51	电池折算SOC
	INT16U	uwReserve53;			//	52	预留53
	INT16U	uwReserve54;			//	53	预留54
	INT16U	uwReserve55;			//	54	预留55
	INT16U	uwReserve56;			//	55	预留56
	INT16U	uwReserve57;			//	56	预留57
	INT16U	uwReserve58;			//	57	预留58
	INT16U	uwReserve59;			//	58	预留59
	INT16U	uwReserve60;			//	59	预留60
	INT16U	uwReserve61;			//	60	预留61
	INT16U	uwReserve62;			//	61	预留62
	INT16U	uwReserve63;			//	62	预留63
	INT16U	uwReserve64;			//	63	预留64
	
	INT16U	uwPv1Volt;			//	64	PV1电压
	INT16U	uwPv1InputCurr;		//	65	PV1输入电流
	INT16S	uwPv1IndCurr; 		//	66	PV1电感电流
	INT16S	uwPv1InputPower; 	//	67	PV1输入功率
	INT16U	uwPv1OutPower; 		//	68	PV1输出功率
	INT16U	uwPv2Volt;			//	69	PV2电压
	INT16U	uwPv2InputCurr;		//	70	PV2输入电流
	INT16S	uwPv2IndCurr; 		//	71	PV2电感电流
	INT16S	uwPv2InputPower; 	//	72	PV2输入功率
	INT16U	uwPv2OutPower; 		//	73	PV2输出功率
	INT16U	uwPVPosInsResVal;	//	74	PV正绝缘阻抗数值
	INT16U	uwPVNegInsResVal; 	//	75	PV负绝缘阻抗数值
	INT16U	uwReserve77; 		//	76	预留77
	INT16U	uwReserve78; 		//	77	预留78
	INT16U	uwReserve79; 		//	78	预留79
	INT16U	uwReserve80; 		//	79	预留80

	INT16S	wGrid_Volt;			//	80	电网电压
	INT16S	wGrid_Curr;			//	81	电网电流
	INT16S	wGrid_Freq;			//	82	电网频率
	INT16S	wGrid_Watt;			//	83	电网有功功率
	INT16S	wGrid_VA;			//	84	电网视在功率
	INT16S	wGrid_VAR;			//	85	电网无功功率
	INT16S	wGrid_PF;			//	86	电网功率因数（0.01）
	INT16S	wGrid_DCI;			//	87	电网电流直流分量
	INT16U	uwReserve89; 		//	88	预留89
	INT16U	uwReserve90; 		//	89	预留90
	INT16U	uwReserve91; 		//	90	预留91
	INT16U	uwReserve92; 		//	91	预留92
	INT16S	wINV_Volt;			//	92	逆变电压
	INT16S	wINV_Curr;			//	93	逆变电流
	INT16S	wINV_Freq;			//	94	逆变频率
	INT16S	wINV_Watt;			//	95	逆变有功功率
	
	INT16S	wINV_VA; 			//	96	逆变视在功率
	INT16S	wINV_VAR;			//	97	逆变无功功率
	INT16S	wINV_PF; 			//	98	逆变功率因数（0.01）
	INT16S	wINV_DCV;			//	99	逆变电压直流分量
	INT16S	wINV_DCI;			//	100	逆变电流直流分量
	INT16U	uwReserve102; 		//	101	预留102
	INT16U	uwReserve103; 		//	102	预留103
	INT16U	uwReserve104; 		//	103	预留104
	INT16S	wLoad_Volt;			//	104	负载电压
	INT16S	wLoad_Curr;			//	105	负载电流
	INT16S	wLoad_Freq;			//	106	负载频率
	INT16S	wLoad_Watt;			//	107	负载有功功率
	INT16S	wLoad_VA;			//	108	负载视在功率
	INT16S	wLoad_VAR;			//	109	负载无功功率
	INT16U	uwLoad_Persent;		//	110	负载百分比
	INT16S	wLoad_DCV;			//	111	负载电压直流分量
	
	INT16U	uwReserve113; 		//	112	预留113
	INT16U	uwReserve114; 		//	113	预留114
	INT16U	uwReserve115; 		//	114	预留115
	INT16U	uwReserve116; 		//	115	预留116
	INT16U	wGenVolt;			//	116	油机电压
	INT16U	wGenCurr;			//	117	油机电流
	INT16U	wGenFreq;			//	118	油机频率
	INT16U	wGenWatt;			//	119	油机有功功率
	INT16U	wGenVA;				//	120	油机视在功率
	INT16U	wGenVAR;			//	121	油机无功功率
	INT16U	uwGenPersent;		//	122	油机百分比
	INT16U	wGenDCV;			//	123	油机电压直流分量
	INT16U	uwReserve125; 		//	124	预留125
	INT16U	uwReserve126; 		//	125	预留126
	INT16U	uwReserve127; 		//	126	预留127
	INT16U	uwReserve128; 		//	127	预留128

	INT16U	wSmartLoadVolt;		//	128	智能负载电压
	INT16U	wSmartLoadCurr;		//	129	智能负载电流
	INT16U	wSmartLoadFreq;		//	130	智能负载频率
	INT16U	wSmartLoadWatt;		//	131	智能负载有功功率
	INT16U	wSmartLoadVA;		//	132	智能负载视在功率
	INT16U	wSmartLoadVAR;		//	133	智能负载无功功率
	INT16U	uwSmartLoadPersent;	//	134	智能负载百分比
	INT16U	wSmartLoadDCV;		//	135	智能负载电压直流分量
	INT16U	uwReserve137; 		//	136	预留137
	INT16U	uwReserve138; 		//	137	预留138
	INT16S	wBatVolt;			//	138	Bat电压
	INT16S	wBatCurr;			//	139	Bat电流
	INT16S	wBatPower;			//	140	Bat功率
	INT16U	uwBatSOC;			//	141	BatSOC
	INT16U	uwReserve143; 		//	142	预留143
	INT16U	uwReserve144; 		//	143	预留144
	
	INT16U	uwReserve145; 		//	144	预留145
	INT16U	uwReserve146; 		//	145	预留146
	INT16U	uwBusVolt;			//	146	Bus总电压
	INT16S	wBusCurr; 			//	147	Bus电流
	INT16S	wBusPower;			//	148	Bus功率
	INT16U	eAnalogBusPosIso;	//	149	Bus正对地绝缘阻抗
	INT16U	eAnalogBusNegIso;	//	150	Bus负对地绝缘阻抗
	INT16U	uwReserve152;		//	151	预留152
	INT16U	uwReserve153;		//	152	预留153
	INT16U	uwReserve154;		//	153	预留154
	INT16S	wBoostTemp; 		//	154	推挽温度
	INT16S	wInvTemp; 			//	155	逆变温度
	INT16S	wTraTemp; 			//	156	推挽变压器温度
	INT16S	wPVTemp;			//	157	Pv温度
	INT16S	wEnviTemp;			//	158	环境温度
	INT16S	wBatHTemp; 			//	159	电池正温度
	
	INT16S	wBatLTemp; 			//	160	电池负温度
	INT16S	wLLCHTemp;			//	161	LLC高压侧温度
	INT16S	wLLCTraTemp;		//	162	LLC变压器温度
	INT16U	uwReserve164; 		//	163	预留164
	INT16U	uwReserve165; 		//	164	预留165
	INT16U	uwReserve166; 		//	165	预留166
	INT16U	uwReserve167; 		//	166	预留167
	INT16U	uwReserve168; 		//	167	预留168
	INT16U	uwReserve169; 		//	168	预留169
	INT16U	eAnalogLeakCurr; 	//	169	漏电流
	INT16U	uwReserve171; 		//	170	预留171
	INT16U	uwReserve172; 		//	171	预留172
	INT16U	uwReserve173; 		//	172	预留173
	INT16U	uwReserve174; 		//	173	预留174
	INT16U	uwReserve175; 		//	174	预留175
	INT16U	uwReserve176; 		//	175	预留176
	
	INT16U	uwReserve177; 		//	176	预留177
	INT16U	uwReserve178; 		//	177	预留178
	INT16U	uwReserve179; 		//	178	预留179
	INT16U	uwReserve180; 		//	179	预留180
	INT16U	uwReserve181; 		//	180	预留181
	INT16U	uwReserve182; 		//	181	预留182
	INT16U	uwReserve183; 		//	182	预留183
	INT16U	uwReserve184; 		//	183	预留184
	INT16U	uwReserve185; 		//	184	预留185
	INT16U	uwReserve186; 		//	185	预留186
	INT16U	uwReserve187; 		//	186	预留187
	INT16U	uwReserve188; 		//	187	预留188
	INT16U	uwReserve189; 		//	188	预留189
	INT16U	uwReserve190; 		//	189	预留190
	INT16U	uwReserve191; 		//	190	预留191
	INT16U	uwReserve192; 		//	191	预留192
	
	INT16U	uwPV1TotalGenEnergyH;	//	192	PV1总发电量高位（0.1KWh）
	INT16U	uwPV1TotalGenEnergyL;	//	193	PV1总发电量低位
	INT16U	uwPV2TotalGenEnergyH; 	//	194	PV1总发电量高位（0.1KWh）
	INT16U	uwPV2TotalGenEnergyL;	//	195 PV1总发电量低位
	INT16U	uwBatTotalChargeH;		//	196 Bat总充电量高位（0.1KWh）
	INT16U	uwBatTotalChargeL;		//	197 Bat总充电量低位（0.1KWh）
	INT16U	uwBatTotalDisChargeH;	//	198 Bat总放电量高位（0.1KWh）
	INT16U	uwBatTotalDisChargeL;	//	199 Bat总放电量低位（0.1KWh）
	INT16U	uwGridTotalCostEnergyH;	//	200 电网总取电量高位（0.1KWh）
	INT16U	uwGridTotalCostEnergyL;	//	201 电网总取电量低位（0.1KWh）
	INT16U	uwGridTotalGenEnergyH;	//	202 电网总馈电量高位（0.1KWh）
	INT16U	uwGridTotalGenEnergyL;	//	203 电网总馈电量低位（0.1KWh）
	INT16U	uwLoadTotalCostEnergyH;	//	204 负载总耗电量高位（0.1KWh）
	INT16U	uwLoadTotalCostEnergyL;	//	205 负载总耗电量低位（0.1KWh）
	INT16U	uwGenTotalCostEnergyH;	//	206 油机总耗电量高位（0.1KWh）
	INT16U	uwGenTotalCostEnergyL;	//	207 油机总耗电量低位（0.1KWh）
	
	INT16U	uwSmartLoadTotalDraEnergyH;//	208 智能负载总取电量高位（0.1KWh）
	INT16U	uwSmartLoadTotalDraEnergyL;//	209 智能负载总取电量低位（0.1KWh）
	INT16U	uwSmartLoadTotalCostEnergyH;//	210 智能负载总耗电量高位（0.1KWh）
	INT16U	uwSmartLoadTotalCostEnergyL;//	211 智能负载总耗电量低位（0.1KWh）
	INT16U	uwReserve213;			//	212 预留213
	INT16U	uwReserve214;			//	213 预留214
	INT16U	uwReserve215;			//	214 预留215
	INT16U	uwReserve216;			//	215 预留216
	INT16U	uwReserve217;			//	216 预留217
	INT16U	uwReserve218;			//	217 预留218
	INT16U	uwReserve219;			//	218 预留219
	INT16U	uwReserve220;			//	219 预留220
	INT16U	uwReserve221;			//	220 预留221
	INT16U	uwReserve222;			//	221 预留222
	INT16U	uwReserve223;			//	222 预留223
	INT16U	uwReserve224;			//	223 预留224
	
	INT16U	uwPV1DayGenEnergy;		//	224 PV1日发电量（0.1KWh），移至GD处计算
	INT16U	uwPV1MonthGenEnergyH;	//	225 PV1月发电量高位（0.1KWh）
	INT16U	uwPV1MonthGenEnergyL;	//	226 PV1月发电量低位（0.1KWh）
	INT16U	uwPV1YearGenEnergyH; 	//	227 PV1年发电量高位（0.1KWh）
	INT16U	uwPV1YearGenEnergyL; 	//	228 PV1年发电量低位（0.1KWh）
	INT16U	uwPV2DayGenEnergy;		//	229 PV2日发电量（0.1KWh），移至GD处计算
	INT16U	uwPV2MonthGenEnergyH;	//	230 PV2月发电量高位（0.1KWh）
	INT16U	uwPV2MonthGenEnergyL;	//	231 PV2月发电量低位（0.1KWh）
	INT16U	uwPV2YearGenEnergyH; 	//	232 PV2年发电量高位（0.1KWh）
	INT16U	uwPV2YearGenEnergyL; 	//	233 PV2年发电量低位（0.1KWh）
	INT16U	uwPVTotalGenEnergyH; 	//	234 PV发电量查询：总-高位
	INT16U	uwPVTotalGenEnergyL; 	//	235 PV发电量查询：总-低位
	INT16U	uwBatDayCharge;			//	236 Bat日充电量（0.1KWh）
	INT16U	uwBatMonthChargeH;		//	237 Bat月充电量高位（0.1KWh）
	INT16U	uwBatMonthChargeL;		//	238 Bat月充电量低位（0.1KWh）
	INT16U	uwBatYearChargeH;		//	239 Bat年充电量高位（0.1KWh）
	
	INT16U	uwBatYearChargeL;		//	240 Bat年充电量低位（0.1KWh）
	INT16U	uwBatDayDisCharge;		//	241 Bat日放电量（0.1KWh）
	INT16U	uwBatMonthDisChargeH;	//	242 Bat月放电量高位（0.1KWh）
	INT16U	uwBatMonthDisChargeL;	//	243 Bat月放电量低位（0.1KWh）
	INT16U	uwBatYearDisChargeH; 	//	244 Bat年放电量高位（0.1KWh）
	INT16U	uwBatYearDisChargeL; 	//	245 Bat年放电量低位（0.1KWh）
	INT16U	uwGridDayCostEnergy; 	//	246 Grid日取电量（0.1KWh）
	INT16U	uwGridMonthCostEnergyH;	//	247 Grid月取电量高位（0.1KWh）
	INT16U	uwGridMonthCostEnergyL;	//	248 Grid月取电量低位（0.1KWh）
	INT16U	uwGridYearCostEnergyH;	//	249 Grid年取电量高位（0.1KWh）
	INT16U	uwGridYearCostEnergyL;	//	250 Grid年取电量低位（0.1KWh）
	INT16U	uwGridDayGenEnergy;		//	251 Grid日馈电量（0.1KWh）
	INT16U	uwGridMonthGenEnergyH;	//	252 Grid月馈电量高位（0.1KWh）
	INT16U	uwGridMonthGenEnergyL;	//	253 Grid月馈电量低位（0.1KWh）
	INT16U	uwGridYearGenEnergyH;	//	254 Grid年馈电量高位（0.1KWh）
	INT16U	uwGridYearGenEnergyL;	//	255 Grid年馈电量低位（0.1KWh）
	
	INT16U	uwLoadDayCostEnergy; 	//	256 Load日耗电量（0.1KWh）
	INT16U	uwLoadMonthCostEnergyH;	//	257 Load月耗电量高位（0.1KWh）
	INT16U	uwLoadMonthCostEnergyL;	//	258 Load月耗电量低位（0.1KWh）
	INT16U	uwLoadYearCostEnergyH;	//	259 Load年耗电量高位（0.1KWh）
	INT16U	uwLoadYearCostEnergyL;	//	260 Load年耗电量低位（0.1KWh）
	INT16U	uwGenDayCostEnergy; 	//	261 Gen日耗电量（0.1KWh）
	INT16U	uwGenMonthCostEnergyH;	//	262 Gen月耗电量高位（0.1KWh）
	INT16U	uwGenMonthCostEnergyL;	//	263 Gen月耗电量低位（0.1KWh）
	INT16U	uwGenYearCostEnergyH;	//	264 Gen年耗电量高位（0.1KWh）
	INT16U	uwGenYearCostEnergyL;	//	265 Gen年耗电量低位（0.1KWh）
	INT16U	uwSmartLoadDayCostEnergy; 	//	266 智能负载日耗电量（0.1KWh）
	INT16U	uwSmartLoadMonthCostEnergyH;//	267 智能负载月耗电量高位（0.1KWh）
	INT16U	uwSmartLoadMonthCostEnergyL;//	268 智能负载月耗电量低位（0.1KWh）
	INT16U	uwSmartLoadYearCostEnergyH;	//	269 智能负载年耗电量高位（0.1KWh）
	INT16U	uwSmartLoadYearCostEnergyL;	//	270 智能负载年耗电量低位（0.1KWh）
	INT16U	uwReserve272;			//	271 预留272
	
	INT16U	uwReserve273;			//	272 预留273
	INT16U	uwReserve274;			//	273 预留274
	INT16U	uwReserve275;			//	274 预留275
	INT16U	uwReserve276;			//	275 预留276
	INT16U	uwReserve277;			//	276 预留277
	INT16U	uwReserve278;			//	277 预留278
	INT16U	uwReserve279;			//	278 预留279
	INT16U	uwReserve280;			//	279 预留280
	INT16U	uwReserve281;			//	280 预留281
	INT16U	uwReserve282;			//	281 预留282
	INT16U	uwReserve283;			//	282 预留283
	INT16U	uwReserve284;			//	283 预留284
	INT16U	uwReserve285;			//	284 预留285
	INT16U	uwReserve286;			//	285 预留286
	INT16U	uwReserve287;			//	286 预留287
	INT16U	uwReserve288;			//	287 预留288
	
	INT16U	uwBMSWIFIBatMeterStatus; //	288 BMSwifi状态
	INT16U	uwBMSCurrentBMSAddr;	//	289 当前电池包通讯地址
	INT16U	uwBMSFlag;				//	290 BMS在线状态
	INT16U	uwBMS1ChargeVoltLimit;	//	291 充电电压限制
	INT16U	uwBMS1DischargeVoltLimit;//	292 放电电压限制
	INT16U	uwBMS1ChargeCurrLimit;	//	293 充电电流限制
	INT16U	uwBMS1DischargeCurrLimit;//	294 放电电流限制
	INT16U	uwBMS1BmsStatusHi;		//	295 充放状态高
	INT16U	uwBMS1BmsStatusLo;		//	296 充放状态低
	INT16U	uwBMS1FaultFlagHi;		//	297 故障标志高
	INT16U	uwBMS1FaultFlagLo;		//	298 故障标志低
	INT16U	uwBMS1AlarmFlagHi;		//	299 告警标志高
	INT16U	uwBMS1AlarmFlagLo;		//	300 告警标志低
	INT16U	uwBMS1NoticeFlagHi;		//	301 提示标志高
	INT16U	uwBMS1NoticeFlagLo;		//	302 提示标志低
	INT16S	wBMS1TotalCurr;			//	303 总电流
	
	INT16U	uwBMS1TotalVolt; 		//	304 总电压
	INT16U	uwBMS1Rsvd306; 			//	305 预留306
	INT16U	uwBMS1Rsvd307; 			//	306 预留307
	INT16U	uwBMS1TotalSOC;			//	307 总SOC
	INT16U	uwBMS1TotalSOH;			//	308 总SOH
	INT16U	uwBMS1TotalCapacityHigh;//	309 总容量
	INT16U	uwBMS1TotalCapacityLow;	//	310 总容量
	INT16U	uwBMS1ParallelNumber;	//	311 串/并联数量
	INT16U	uwBMS1ParallelStatus;	//	312 串/并联状态
	INT16U	uwReserve314;			//	313 预留314
	INT16U	uwReserve315;			//	314 预留315
	INT16U	uwBMS1MaximumCellVoltNo; //	315 最高电芯电压编号
	INT16U	uwBMS1MaximumCellVolt;	//	316 最高电芯电压
	INT16U	uwBMS1MinimumCellVoltNo; //	317 最低电芯电压编号
	INT16U	uwBMS1MinimumCellVolt;	//	318 最低电芯电压
	INT16U	uwBMS1MaximumCellTempeNo;//	319 最高电芯温度编号
	
	INT16S	wBMS1MaximumCellTempe;	//	320 最高电芯温度
	INT16U	uwBMS1MinimumCellTempeNo;//	321 最低电芯温度编号
	INT16S	wBMS1MinmumCellTempe;	//	322 最低电芯温度
	INT16U	uwBMSSN1;				//	323 电池包机器序列号
	INT16U	uwBMSSN2;				//	324 
	INT16U	uwBMSSN3;				//	325 
	INT16U	uwBMSSN4;				//	326 
	INT16U	uwBMSSN5;				//	327 
	INT16U	uwReserve329;			//	328 预留329
	INT16U	uwReserve330;			//	329 预留330
	INT16U	uwReserve331;			//	330 预留331
	INT16U	uwReserve332;			//	331 预留332
	INT16U	uwEMSTotalSOC;			//	332 总SOC
	INT16U	uwEMSConnectNumber;		//	333 并联数量
	INT16U	uwEmsBatLimitVolt;		//	334 推荐充电截至电压
	INT16U	uwReserve336;			//	335 预留336
	
	INT16U	uwEmsBatCutOffVol;		//	336 推荐放电截止电压
	INT16U	uwEmsBatMaxChgCurrent;	//	337 充电电流限制
	INT16U	uwEmsMaxDisChgCurr	;	//	338 放电电流限制
	INT16U	uwEmsFaultCode;			//	339 故障标志低
	INT16U	uwEmsFlag;				//	340 BMS标志
	INT16U	uwEmsBatPackSeries;		//	341 电池包系列
	INT16U	uwReserve343;			//	342 预留343
	INT16U	uwReserve344;			//	343 预留344
	INT16U	uwReserve345;			//	344 预留345
	INT16U	uwReserve346;			//	345 预留346
	INT16U	uwReserve347;			//	346 预留347
	INT16U	uwReserve348;			//	347 预留348
	INT16U	uwReserve349;			//	348 预留349
	INT16U	uwReserve350;			//	349 预留350
	INT16U	uwReserve351;			//	350 预留351
	INT16U	uwReserve352;			//	351 预留352
	
	INT16U	uwRecordlogType; 		//	352 Log类型
	INT16U	uwRecordlogIndex;		//	353 Log序号
	INT16U	uwRecordlogStatus;		//	354 Log状态
	INT16U	uwRecordlogNumber;		//	355 故障码/事件码
	INT16U	uwRecordlogYearMonth;	//	356 时间：年-月
	INT16U	uwRecordlogDayHour;		//	357 时间：日-时
	INT16U	uwRecordlogMinuteSecond; //	358 时间：分-秒
	INT16U	uwRecordlogPV1Volt;		//	359 PV1电压
	INT16U	uwRecordlogPV2Volt;		//	360 PV2电压
	INT16S	wRecordlogPV1IndCurr;	//	361 PV1电感电流
	INT16S	wRecordlogPV2IndCurr;	//	362 PV2电感电流
	INT16U	uwRecordlogBatVolt;		//	363 Bat电压
	INT16S	wRecordlogBatCurr;		//	364 Bat电流
	INT16U	uwRecordlogBusVolt;		//	365 Bus总电压
	INT16S	wRecordlogBoostTempe;	//	366 推挽低压侧温度
	INT16S	wRecordlogInvTempe;		//	367 逆变温度
	
	INT16S	wRecordlogEnviTempe; 	//	368 推挽变压器温度
	INT16S	wRecordlogPCB1Tempe; 	//	369 PV散热器温度
	INT16U	uwReserve371;			//	370 预留371
	INT16S	wRecordlogGridVolt;		//	371 电网电压
	INT16S	wRecordlogGridCurr;		//	372 电网电流
	INT16S	wRecordlogGridFreq;		//	373 电网频率
	INT16S	wRecordlogINVVolt;		//	374 逆变电压
	INT16S	wRecordlogINVCurr;		//	375 逆变电流
	INT16S	wRecordlogINVFreq;		//	376 逆变频率
	INT16S	wRecordlogINVWatt;		//	377 逆变有功功率
	INT16S	wRecordlogLoadVolt;		//	378 负载电压
	INT16S	wRecordlogLoadCurr;		//	379 负载电流
	INT16S	wRecordlogLoadFreq;		//	380 负载频率
	INT16S	wRecordlogLoadWatt;		//	381 负载有功功率
	INT16S	wRecordlogLoadVA;		//	382 负载视在功率
	INT16U	uwReserve384;			//	383 预留384
	
	INT16U	uwReserve385;			//	384 预留385
	INT16U	uwReserve386;			//	385 预留386
	INT16U	uwReserve387;			//	386 预留387
	INT16U	uwReserve388;			//	387 预留388
	INT16U	uwReserve389;			//	388 预留389
	INT16U	uwReserve390;			//	389 预留390
	INT16U	uwReserve391;			//	390 预留391
	INT16U	uwReserve392;			//	391 预留392
	INT16U	uwReserve393;			//	392 预留393
	INT16U	uwReserve394;			//	393 预留394
	INT16U	uwReserve395;			//	394 预留395
	INT16U	uwReserve396;			//	395 预留396
	INT16U	uwReserve397;			//	396 预留397
	INT16U	uwReserve398;			//	397 预留398
	INT16U	uwReserve399;			//	398 预留399
	INT16U	uwReserve400;			//	399 预留400

	INT16U	uwReserve401;			//	400 预留401
	INT16U	uwReserve402;			//	401 预留402
	INT16U	uwReserve403;			//	402 预留403
	INT16U	uwReserve404;			//	403 预留404
	INT16U	uwReserve405;			//	404 预留405
	INT16U	uwReserve406;			//	405 预留406
	INT16U	uwReserve407;			//	406 预留407
	INT16U	uwReserve408;			//	407 预留408
	INT16U	uwReserve409;			//	408 预留409
	INT16U	uwReserve410;			//	409 预留410
	INT16U	uwReserve411;			//	410 预留411
	INT16U	uwReserve412;			//	411 预留412
	INT16U	uwReserve413;			//	412 预留413
	INT16U	uwReserve414;			//	413 预留414
	INT16U	uwReserve415;			//	414 预留415
	INT16U	uwReserve416;			//	415 预留416

	INT16U	uwReserve417;			//	416 预留417
	INT16U	uwReserve418;			//	417 预留418
	INT16U	uwReserve419;			//	418 预留419
	INT16U	uwReserve420;			//	419 预留420
	INT16U	uwReserve421;			//	420 预留421
	INT16U	uwReserve422;			//	421 预留422
	INT16U	uwReserve423;			//	422 预留423
	INT16U	uwReserve424;			//	423 预留424
	INT16U	uwReserve425;			//	424 预留425
	INT16U	uwReserve426;			//	425 预留426
	INT16U	uwReserve427;			//	426 预留427
	INT16U	uwReserve428;			//	427 预留428
	INT16U	uwReserve429;			//	428 预留429
	INT16U	uwReserve430;			//	429 预留430
	INT16U	uwReserve431;			//	430 预留431
	INT16U	uwReserve432;			//	431 预留432
};

struct	INVERTER_INFORMATION_DATA_FEILD
{
	INT16U uwInflogType;
	INT16U uwInflogSubType;
	INT16U uwInflogCommProVer;
	INT16U uwInflogCommInfo;
	INT16U uwInflogSN1;
	INT16U uwInflogSN2;
	INT16U uwInflogSN3;
	INT16U uwInflogSN4;
	INT16U uwInflogSN5;
	INT16U uwInflogSNLen;
	INT16U uwInflogMVer;
	INT16U uwInflogMIAPVer;
	INT16U uwInflogMSubVer;
	INT16U uwInflogSVer;
	INT16U uwInflogSIAPVer;
	INT16U uwInflogSSubVer;
	INT16U uwInflogDVer;
	
	INT16U uwInflogDIAPVer;
	INT16U uwInflogDSubVer;
	INT16U uwInflogCtrlHwVer;
	INT16U uwInflogPowerHwVer;
	INT16U uwInflogDispHwVer;
	INT16U uwInflogOpType;
	INT16U uwInflogRsvd1;
	INT16U uwInflogRsvd2;
	INT16U uwInflogRsvd3;
	INT16U uwInflogRsvd4;
	INT16U uwInflogRsvd5;
	INT16U uwInflogRsvd6;
	INT16U uwInflogRsvd7;
	INT16U uwInflogRsvd8;
	INT16U uwInflogRsvd9;
	INT16U uwInflogRsvd10;
	INT16U uwInflogRsvd11;
	INT16U uwInflogRsvd12;
	INT16U uwInflogRsvd13;
	INT16U uwInflogRsvd14;
	INT16U uwInflogRsvd15;
	INT16U uwInflogRsvd16;
	INT16U uwInflogRsvd17;
	INT16U uwInflogRsvd18;
	INT16U uwInflogRsvd19;
	INT16U uwInflogRsvd20;
	INT16U uwInflogRsvd21;
	INT16U uwInflogRsvd22;
	INT16U uwInflogRsvd23;
	INT16U uwInflogRsvd24;
	INT16U uwInflogRsvd25;
	INT16U uwInflogRsvd26;

	// BMS	
	INT16U uwInflogCurrBmsAddr;
	INT16U uwInflogBmsType;
	INT16U uwInflogBmsSubType;
	INT16U uwInflogBmsCommProVer;
	INT16U uwInflogBmsCommInfo;
	INT16U uwInflogBmsSN1;
	INT16U uwInflogBmsSN2;
	INT16U uwInflogBmsSN3;
	INT16U uwInflogBmsSN4;
	INT16U uwInflogBmsSN5;
	INT16U uwInflogBmsSNLen;
	INT16U uwInflogBmsDispSwVer;
	INT16U uwInflogBmsMCU1SwVer;
	INT16U uwInflogBmsMCU2SwVer;
	INT16U uwInflogBmsDispHwVer;
	INT16U uwInflogBmsCtrlHwVer;
	INT16U uwInflogBmsPowerHwVer;
	INT16U uwReservd1;
	INT16U uwLCDDispSwVer;
	INT16U uwReservd2;
	INT16U uwReservd3;
	INT16U uwReservd4;
	INT16U uwReservd5;
	INT16U uwReservd6;
	INT16U uwReservd7;
};

union BMS_STATUS_TABLE
{
	struct BMS_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U rsvd1:3;
		INT16U FullCharge:1;			// 定时/SOC误差大使能,充满停止
		
		// BIT4-7
		INT16U ChargeImmediately2:1;	// 低于10%使能,高于等于20%停止
		INT16U ChargeImmediately1:1;	// 低于 5%使能,高于等于10%停止
		INT16U DischargeEnable:1;
		INT16U ChargeEnable:1;
		
		// BIT8-11
		INT16U DischargeMOS:1;
		INT16U ChargeMOS:1;
		INT16U DischargeSoftMOS:1;
		INT16U ChargeSoftMOS:1;
		
		// BIT12-15
		INT16U Discharging:1;
		INT16U Charging:1;
		INT16U rsvd4:2;
	} bits;
	INT16U data;
} ;

struct	INVERTER_SWAP_MCU_DATA_FEILD
{
	INT32U dwTimestamp;
	INT16U wLoadOnOff;
	INT16U wReserved1;
	INT16U wMCUFaultFlag;
	INT16U wReserved2;
	INT16S wBusVolt;
	INT16S wCtrlPanelTemp;
	INT16S wRLineVolt;
	INT16S wRLineFreq;
	INT16S wReserved3;
	INT16S wReserved4;
	INT16S wCTRLineCurr;
	INT16S wCTRLineWatt;
	INT16S wCTRLineVar;
	INT16S wCTRLineVA;
	INT16S wBMSBatVolt;
	INT16S wBMSBatCurr;
	INT16S wBMSSOC;
	union BMS_STATUS_TABLE wBMSStatus;
	INT16S wBMSChargeVoltLimit;
	INT16S wBMSDischargeVoltLimit;
	INT16S wBMSChargeCurrLimit;
	INT16S wBMSDischargeCurrLimit;
	INT16S wTimeCtrlEnable;
	INT16S wTimeCtrlPower;	// 正表示充电,负表示放电
	INT16S wTimeCtrlVolt;
	INT16S wTimeCtrlSOC;
	INT16U wDRMStatus;
};

struct	WIFI_IOT_DATA_FEILD
{
	INT16U uwIotType;			// 0X5100	区分4G/WiFi
	INT16U uwIotVersion;		// 0X5101	iot 版本号
	INT16U uwIotIpAddressH;		// 0X5102	iot 设备的IP地址：如0xC0A86401=192.168.100.1
	INT16U uwIotIpAddressL;		// 0X5103	
	INT16U uwIotSimSn1;			// 0X5104	带有英文字符的20个长度:如：ICCID: 898604B3192270310904
	INT16U uwIotSimSn2;
	INT16U uwIotSimSn3;
	INT16U uwIotSimSn4;
	INT16U uwIotSimSn5;
	INT16U uwIotSimSn6;
	INT16U uwIotSimSn7;
	INT16U uwIotSimSn8;
	INT16U uwIotSimSn9;
	INT16U uwIotSimSn10;
	INT16U uwIotSimSn11;
	INT16U uwIotSimSn12;
	INT16U uwIotSimSn13;
	INT16U uwIotSimSn14;
	INT16U uwIotSimSn15;
	INT16U uwIotSimSn16;
	INT16U uwIotState;			// 0X5114	iot 设备的状态：
								// 			0：iot 设备没有与MCU 建立通信
								// 			1：连接路由器错误，有配置路由器
								// 			2：连接上路由器
								// 			3：连接上服务器
								// 			4：正在配置连接路由器或基站
								// 			5：正在升级IOT 设备程序
	
	INT16S uwIotRSSI;			// 0X5115	4G/WiFi的信号强度
	INT16U uwIotBleConn;		// 0X5116	蓝牙设备连接数
	
	INT16U uwReserved2;			// 0X5117
	INT16U uwReserved3;			// 0X5118
	INT16U uwReserved4;			// 0X5119
	INT16U uwReserved5;			// 0X511A
	INT16U uwReserved6;			// 0X511B
	INT16U uwReserved7;			// 0X511C
	INT16U uwReserved8;			// 0X511D
	INT16U uwReserved9;			// 0X511E
};


struct	INV_PARAMETER_DATA_FEILD
{
	// 基本信息
	INT16U uwModelLV;				// LV机型使能
	INT16U uwType;					// 设备大类
	INT16U uwSubType; 				// 设备子类
	INT16U uwBatSerialPcs;			// 电池节数
	INT16U uwTransformerRatio;		// 推挽变比
	INT16U uwCTdirection;			// CT方向
	INT16U uwInvCurrRatio;			// 逆变电流采样系数
	INT16U uwInvWattRes;			// 逆变等效电阻

	// PV参数
	INT16U uwMpptPvVoltMax;			// PV最大电压
	INT16U uwPvPowerMax;			// PV最大功率
	INT16U uwPvChgBatVoltRef;		// PV充电电池电压参考

	// 电池参数
	INT16U uwSettingMaxChgCurr;		// 最大充电电流
	INT16U uwSettingMaxDcgCurr;		// 最大放电电流
	INT16U uwSettingMaxACChgCurr;	// 最大市电充电电流
	INT16U uwBusVoltOver1;			// Bus过压1
	INT16U uwBusVoltOver2;			// Bus过压2
	INT16U uwBusVoltOver3;			// Bus过压3 中断级
	INT16U uwBusVoltLow1;			// Bus低压1
	INT16U uwDcDcPWMPeriod;			// DcDc频率
	INT16U uwDcDcPWMDutySet;		// DcDc占空比

	// 逆变参数
	INT16U uwInvVAMax;				// 最大逆变视在功率
	INT16S uwInvWattMax;			// 最大逆变有功功率
	INT16S uwInvRateVolt;			// 逆变额定电压
	INT16S uwInvDeratingVolt;		// 逆变降额最低电压
	INT16S uwInvFreeCntlCurrMax;	// 最大逆变馈电控制电流
	INT16U uwInvVoltOver;			// 逆变输出过压值
	INT16U uwInvVoltOverBack;		// 逆变输出过压恢复值
	INT16U uwInvCurrOver;			// 逆变输出过流值
	INT16U uwHsInvTempStartDerat;	// 逆变散热器开始降额温度
	INT16U uwHsInvTempEndDerat;		// 逆变散热器停止降额温度
	INT16U uwHsTwTempStartDerat;	// 推挽散热器开始降额温度
	INT16U uwHsTwTempEndDerat;		// 推挽散热器停止降额温度
	INT16U uwTraTempStartDerat;		// 推挽变压器温度开始降额温度
	INT16U uwTraTempEndDerat;		// 推挽变压器温度停止降额温度
	INT16U uwPvTempStartDerat;		// PV温度降额开始降额温度
	INT16U uwPvTempEndDerat;		// PV温度降额停止降额温度
	INT16U uwBatHNtcTempOver;		// 电池正端温度过高值
	INT16U uwBatLNtcTempOver;		// 电池负端温度过高值
	INT16S uwMaxFanDutyInvWatt;		// 风扇满转时的逆变功率

	// 市电参数
	INT16U uwGridInputWattMax;		// 市电最大输入功率
	INT16U uwGridInputCurrMax;		// 市电最大输入电流
	INT16U uwGridInputCurrOver1;	// 市电过流值1
	INT16U uwGridInputCurrOver2;	// 市电过流值2

	// 负载参数
	INT16U uwLoadVoltOver;			// 输出过压值
	INT16U uwLoadVoltLowAPL;		// 输出低压值 APL
	INT16U uwLoadVoltLowUPS;		// 输出低压值 UPS
	
};

struct	INV_POWER_CONVERSION_DATA_FEILD
{
	INT16S wBatWatt;				// 电池功率
	INT16S wPvWatt;					// PV功率
	INT16S wGridWatt; 				// 市电功率
	INT16S wInvWatt; 				// 逆变功率
	INT16S wLoadWatt; 				// 负载功率
	INT16S wXXXXWatt; 				// XXXX功率
};

union POWER_FLOW_MSG_TABLE
{
	struct POWER_FLOW_MSG_BIT_FEILD
	{
		INT16U bbatteryIcon:1;		// 电池显示图标和静态连线
		INT16U bbatteryFlow:1;		// 电池有功率时线条有动态流动
		INT16U bbatteryEngyDir:1;	// 电池动态流动方向(0:充电,1:放电)
		INT16U bPVIcon:1;			// PV显示图标和静态连线
		
		INT16U bPVFlow:1;			// PV有功率时线条有动态流动
		INT16U bLoadIcon:1;			// 负载显示图标和静态连线
		INT16U bLoadFlow:1;			// 负载有功率时线条有动态流动
		INT16U bLineIcon:1;			// 市电显示图标和静态连线

		INT16U bLineFlow:1;			// 市电有功率时线条有动态流动
		INT16U bLineEngyDir:1;		// 市电动态流动方向(0:买电,1:馈电)
		INT16U bGenIcon:1;			// 电机显示图标和静态连线
		INT16U bGenFlow:1;			// 电机有功率时线条有动态流动
		
		INT16U bSmartLoadIcon:1;	// 智能负载显示图标和静态连线
		INT16U bSmartLoadFlow:1;	// 智能负载有功率时线条有动态流动
		INT16U bRsvd4:2;
	} bits;
	INT16U data;
};

INVERTER_PROCESS union POWER_FLOW_MSG_TABLE fPowerFlowMsg;

#define	cINVERTER_REALTIME_DATA_LEN		sizeof(struct INVERTER_REALTIME_DATA_FEILD)
#define	cINVERTER_INFORMATION_DATA_LEN	sizeof(struct INVERTER_INFORMATION_DATA_FEILD)
#define	cINVERTER_SWAP_MCU_DATA_LEN		sizeof(struct INVERTER_SWAP_MCU_DATA_FEILD)
#define	cWIFI_IOT_DATA_LEN				sizeof(struct WIFI_IOT_DATA_FEILD)
#define	cINV_PARAMETER_DATA_LEN			sizeof(struct INV_PARAMETER_DATA_FEILD)
#define	cINV_POWER_CONVERSION_DATA_LEN	sizeof(struct INV_POWER_CONVERSION_DATA_FEILD)

union INVERTER_REALTIME_DATA_TABLE
{
	struct	INVERTER_REALTIME_DATA_FEILD	Field;
	INT16U	Table[cINVERTER_REALTIME_DATA_LEN];
};

union INVERTER_INFORMATION_DATA_TABLE
{
	struct	INVERTER_INFORMATION_DATA_FEILD	Field;
	INT16U	Table[cINVERTER_INFORMATION_DATA_LEN];
};

union INVERTER_SWAP_MCU_DATA_TABLE
{
	struct	INVERTER_SWAP_MCU_DATA_FEILD	Field;
	INT16U	Table[cINVERTER_SWAP_MCU_DATA_LEN];
};

union WIFI_IOT_DATA_TABLE
{
	struct	WIFI_IOT_DATA_FEILD	Field;
	INT16U	Table[cWIFI_IOT_DATA_LEN];
};

union INV_PARAMETER_DATA_TABLE
{
	struct	INV_PARAMETER_DATA_FEILD	Field;
	INT16U	Table[cINV_PARAMETER_DATA_LEN];
};

union INV_POWER_CONVERSION_DATA_TABLE
{
	struct	INV_POWER_CONVERSION_DATA_FEILD Field;
	INT16U	Table[cINV_POWER_CONVERSION_DATA_LEN];
};


extern union INVERTER_SWAP_MCU_DATA_TABLE strInverterSwapMcuData;
#define mBMSBatVolt				strInverterSwapMcuData.Field.wBMSBatVolt
#define mBMSBatCurr				strInverterSwapMcuData.Field.wBMSBatCurr
#define mBMSBatSOC				strInverterSwapMcuData.Field.wBMSSOC
#define mBMSChargeEnable		strInverterSwapMcuData.Field.wBMSStatus.bits.ChargeEnable
#define mBMSDischargeEnable		strInverterSwapMcuData.Field.wBMSStatus.bits.DischargeEnable
#define mBMSForceCharge			strInverterSwapMcuData.Field.wBMSStatus.bits.ChargeImmediately1
#define mBMSBatCVVolt			strInverterSwapMcuData.Field.wBMSChargeVoltLimit
#define mBMSBatCutOffVolt		strInverterSwapMcuData.Field.wBMSDischargeVoltLimit
#define mBMSBatMaxChgCurr		strInverterSwapMcuData.Field.wBMSChargeCurrLimit
#define mBMSBatMaxDischgCurr	strInverterSwapMcuData.Field.wBMSDischargeCurrLimit

#define fBMSConnectFlg			(strInverterSwapMcuData.Field.wBMSBatVolt!=0)
#define fBMSStopChargeFlg		!strInverterSwapMcuData.Field.wBMSStatus.bits.ChargeEnable
#define fBMSStopDischgFlg		!strInverterSwapMcuData.Field.wBMSStatus.bits.DischargeEnable
#define fBMSForceChgFlg			strInverterSwapMcuData.Field.wBMSStatus.bits.ChargeImmediately1

#define mTIMECtrlEnable			strInverterSwapMcuData.Field.wTimeCtrlEnable
#define mTIMECtrlPower			strInverterSwapMcuData.Field.wTimeCtrlPower
#define mTIMECtrlVolt			strInverterSwapMcuData.Field.wTimeCtrlVolt
#define mTIMECtrlSOC			strInverterSwapMcuData.Field.wTimeCtrlSOC

#define mCTRLineCurr			strInverterSwapMcuData.Field.wCTRLineCurr
#define mCTRLineWatt			strInverterSwapMcuData.Field.wCTRLineWatt

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INVERTER_PROCESS void	sInverterSetUpdate(void);
INVERTER_PROCESS void	sbInverterIdentifyInitial(void);
INVERTER_PROCESS INT8U	sbInverterIdentify(INT8U bFilter);

INVERTER_PROCESS void	sInvPowerConversion(void);	// 功率折算
INVERTER_PROCESS void	sPowerFlowMsgUpdate(void);
INVERTER_PROCESS void	sInverterRealtimeDataUpdate(void);
INVERTER_PROCESS void	sInverterInformationDataUpdate(void);
INVERTER_PROCESS void	sInvWattResCal(void);

INVERTER_PROCESS void	sAlarmFlagChk(INT16U uwFilter);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INVERTER_PROCESS INT16U	swGetInverterRealtimeData(INT16U wAddrOffset);
INVERTER_PROCESS INT16U	swGetInverterInformationData(INT16U wAddrOffset);
INVERTER_PROCESS INT16U	swGetWifiIotData(INT16U wAddrOffset);

INVERTER_PROCESS INT16U	uwGetModelVar(void);
INVERTER_PROCESS INT16U	uwGetModelLV(void);
INVERTER_PROCESS INT16U	uwGetType(void);
INVERTER_PROCESS INT16U	uwGetSubType(void);
INVERTER_PROCESS INT16U	uwGetBatSerialPcs(void);
INVERTER_PROCESS INT16U	uwGetTransformerRatio(void);
INVERTER_PROCESS INT16U	uwGetInvVAMax(void);
INVERTER_PROCESS INT16S	uwGetInvWattMax(void);
INVERTER_PROCESS INT16S	uwGetInvRateVolt(void);
INVERTER_PROCESS INT16S	uwGetInvDeratingVolt(void);
INVERTER_PROCESS INT16S	uwGetInvFreeCntlCurrMax(void);
INVERTER_PROCESS INT16U	uwGetInvVoltOver(void);
INVERTER_PROCESS INT16U	uwGetInvVoltOverBack(void);
INVERTER_PROCESS INT16U	uwGetInvCurrOver(void);
INVERTER_PROCESS INT16U	uwGetCTdirection(void);
INVERTER_PROCESS INT16U	uwGetInvCurrRatio(void);
INVERTER_PROCESS INT16U	uwGetInvWattRes(void);
INVERTER_PROCESS INT16U	uwGetSettingMaxChgCurr(void);
INVERTER_PROCESS INT16U	uwGetSettingMaxDchgCurr(void);
INVERTER_PROCESS INT16U	uwGetSettingMaxACChgCurr(void);
INVERTER_PROCESS INT16U	uwGetBusVoltOver1(void);
INVERTER_PROCESS INT16U	uwGetBusVoltOver2(void);
INVERTER_PROCESS INT16U	uwGetBusVoltOver3(void);
INVERTER_PROCESS INT16U	uwGetBusVoltLow1(void);
INVERTER_PROCESS INT16U	uwGetDcDcPWMPeriod(void);
INVERTER_PROCESS INT16U	uwGetDcDcPWMDutySet(void);

INVERTER_PROCESS INT16U	uwGetLLCHTempStartDerat(void);
INVERTER_PROCESS INT16U	uwGetLLCHTempEndDerat(void);
INVERTER_PROCESS INT16U	uwGetTraTempStartDerat(void);
INVERTER_PROCESS INT16U	uwGetTraTempEndDerat(void);
INVERTER_PROCESS INT16U	uwGetPvTempStartDerat(void);
INVERTER_PROCESS INT16U	uwGetPvTempEndDerat(void);
INVERTER_PROCESS INT16U	uwGetBatHNtcTempOver(void);
INVERTER_PROCESS INT16U	uwGetBatLNtcTempOver(void);
INVERTER_PROCESS INT16S	uwGetMaxFanDutyInvWatt(void);
INVERTER_PROCESS INT16S	uwGetGridInputWattMax(void);
INVERTER_PROCESS INT16S	uwGetGridInputCurrMax(void);
INVERTER_PROCESS INT16U	uwGetMpptPvVoltMax(void);
INVERTER_PROCESS INT16U	uwGetPvPowerMax(void);
INVERTER_PROCESS INT16U	uwGetPvChgBatVoltRef(void);
INVERTER_PROCESS INT16U	uwGetGridCurrOver1(void);
INVERTER_PROCESS INT16U	uwGetGridCurrOver2(void);
INVERTER_PROCESS INT16U	uwGetLoadVoltOver(void);
INVERTER_PROCESS INT16U	uwGetLoadVoltLowAPL(void);
INVERTER_PROCESS INT16U	uwGetLoadVoltLowUPS(void);


INVERTER_PROCESS INT16U	uwGetBootBV(void);	// boot软件版本号
INVERTER_PROCESS INT16U	uwGetBootHV(void); // 机器硬件版本号


INVERTER_PROCESS INT16U	uwGetWifiIotState(void);	
INVERTER_PROCESS INT16U	uwGetBMSWIFIBatMeterStatus(void);
INVERTER_PROCESS INT16U	uwGetBmsDataFlag(void);

INVERTER_PROCESS INT16S	uwGetBatConversionWatt(void);
INVERTER_PROCESS INT16S	uwGetPvConversionWatt(void);
INVERTER_PROCESS INT16S	uwGetGridConversionWatt(void);
INVERTER_PROCESS INT16S	uwGetLoadConversionWatt(void);
INVERTER_PROCESS INT16U	uwGetRTDataEMSConnectNumber(void);

INVERTER_PROCESS INT16U	uwGetHsInvTempStartDerat(void);
INVERTER_PROCESS INT16U	uwGetHsInvTempEndDerat(void);
INVERTER_PROCESS INT16U	uwGetHsTwTempStartDerat(void);
INVERTER_PROCESS INT16U	uwGetHsTwTempEndDerat(void);


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INVERTER_PROCESS void	sSetWifiIotType(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotTersion(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotIpAddressH(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotIpAddressL(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn1(INT16U uwTemp);	// SN1
INVERTER_PROCESS void	sSetWifiIotSimSn2(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn3(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn4(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn5(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn6(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn7(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn8(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn9(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn10(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn11(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn12(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn13(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn14(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn15(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotSimSn16(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotState(INT16U uwTemp);
INVERTER_PROCESS void	sSetWifiIotRSSI(INT16S uwTemp);
INVERTER_PROCESS void	sSetWifiIotBleConn(INT16U uwTemp);
INVERTER_PROCESS void	uwSetBmsDataFlag(INT16U uwTemp);

#endif	// __INVERTER_PROCESS_H__


