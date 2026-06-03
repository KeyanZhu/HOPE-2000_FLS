/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __EEEPROM_PROCESS_H__
#define __EEEPROM_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __EEPROM_PROCESS_C__
#define EEPROM
#else
#define EEPROM extern
#endif

#define	cEEPROM_TASK1					0
#define	cEEPROM_TASK2					1
#define	cEEPROM_TASK3					2
#define	cEEPROM_TASK_MAX				3

#define	cEEPROM_SAVE_DISABLE			0
#define	cEEPROM_SAVE_ENABLE				1
#define	cEEPROM_SAVE_DELAY				2
#define	cEEPROM_SAVE_ACTION				3

#define	cEEAdjLimitLo					2048
#define	cEEAdjLimitUp					8192
#define	cEEBiasLimitLo					((INT16S)-32000)	// Q7,250
#define	cEEBiasLimitUp					((INT16S)32000)		// Q7,250

#define	cEEBatVoltAdjDef				4096				// Q12
#define	cEEBatVoltAdjLimitLo			2048
#define	cEEBatVoltAdjLimitUp			8192

#define	cEEBatVoltBiasDef				0
#define	cEEBatVoltBiasLimitLo			((INT16S)-32000)	// Q7,-250
#define	cEEBatVoltBiasLimitUp			((INT16S)32000)		// Q7,+250


//新协议 20250409
typedef struct
{
	INT16U	uwSetMachineID;			//	0	机器地址设置
	INT16U	uwSetParaEnable;		//	1	Dsp并机使能
	INT16U	uwSetMasterSlaver;		//	2	主从机设置 
	INT16U	uwSetEepromAutoWrite;	//	3	Eeprom自动写入
	INT16U	uwSetSystemOutputMode;	//	4	系统输出模式  0:单机 1:单相并机
	INT16U	uwSetFanWorkMode;		//	5	风机运行模式 0:性能模式 1：平衡模式 2：静音模式
	INT16U	uwTurboMode; 			//	6	Turbo模式使能
	INT16U	uwAutoInvEnable; 		//	7	开机自动逆变
	INT16U	uwDCDCOpenLoopEnable;	//	8	DCDC开环使能
	INT16U	uwLogoEnable;			//	9	Logo使能
	INT16U	uwAdcBiasAdj;			//	10	用于通信数据显示美化，例如无PV时采样到非0值时置零，0：美化 1：不美化
	INT16U	uwSetReserve11;			//	11	预留
	INT16U	uwSetReserve12;			//	12	预留
	INT16U	uwSetReserve13;			//	13	预留
	INT16U	uwSetReserve14;			//	14	预留
}strControlStateSet;
#define cControlStateSetLength  ((sizeof(strControlStateSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetPV1StartVolt;		//	15	PV1启动电压
	INT16U	uwSetReserve16;			//	16	预留
	INT16U	uwSetPV_PowerLimit;		//	17	PV_最大功率
	INT16U	uwSetReserve18;			//	18	预留
	INT16U	uwSetReserve19;			//	19	预留
	INT16U	uwSetPV_Priority;		//	20	PV能量优先级(只在SUB模式下生效）0: BLU (电池 > 负载 > 电网)1: LBU (负载 > 电池 > 电网)2: LUB (负载 > 电网 > 电池) --只有并网馈电时生效
	INT16U	uwPVAutoInvEnable; 		//	21	单PV无电池开机自动逆变使能,如果有电池此项不生效
	INT16U	uwSetRsvd22; 			//	22	预留
}strPVDataSet;
#define cPVDataSetLength  ((sizeof(strPVDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetBatType;					// 23	电池类型0: 胶体电池 (AGM)1: 注水电池 (Flood)2: 用户自定义 (User defined)3: 锂电池 (Lithium)
	INT16U	uwSetBatSeriesNum;				// 24	电池节数
	INT16U	uwSetBatCapacity;				// 25	电池容量
	INT16U	uwSetRsvd26; 					// 26	预留
	INT16U	uwSetBatMode;					// 27	电池模式 0:电池相关的使用SOC，1:使用电压，2:无电池
	INT16U	uwSetChargePriority; 			// 28	充电优先级0: 市电优先 1: PV优先2: PV和市电3: 仅PV 
	INT16U	uwSetBatConstVolt;				// 29	电池恒压充电压
	INT16U	uwSetBatFloatVolt;				// 30	电池浮充电压
	INT16U	uwSetBatFloatTime;				// 31	电池恒充时间,恒压充转浮充的时间
	INT16U	uwSetBatMaxChgCurr;				// 32	电池最大充电电流限幅值
	INT16U	uwSetBatMaxDcgCurr;				// 33	电池最大放电电流限幅值
	INT16U	uwSetGridChgBatCurr; 			// 34	电网至电池充电电流
	INT16U	uwSetGridChgBatTotalEnable;		// 35	电网充电总使能
	INT16U	uwSetOnGridBatAutoStartChgSOC;	// 36	并网时电池自动启动充电SOC点
	INT16U	uwSetOnGridBatExitAutoChgSOC;	// 37	并网时电池自动退出充电SOC点
	INT16U	uwSetOnGridBatAutoStartChgVolt;	// 38	并网时电池自动启动充电电压点
	INT16U	uwSetOnGridBatExitAutoChgVolt;	// 39	并网时电池自动退出充电电压点
	INT16U	uwSetBatACRestartVolt;			// 40	电池重启AC输出电压点
	INT16U	uwSetBatLowAlarmVolt;			// 41	电池低压告警电压点
	INT16U	uwSetBatLowShutDownVolt; 		// 42	电池低压关机电压点
	INT16U	uwSetBatACRestartSOC;			// 43	电池重启AC输出SOC点
	INT16U	uwSetBatLowAlarmSOC; 			// 44	电池低压告警SOC点
	INT16U	uwSetBatLowShutDownSOC;			// 45	电池低压关机SOC点
	INT16U	uwSetBatVoltOverShut;			// 46	电池过压保护点
	INT16U	uwSetBatActivateEnable;			// 47	电池激活使能
	INT16U	uwSetBMSComErrEnable;			// 48	BMS通讯故障使能
	INT16U	uwSetBMSProtocol;				// 49	BMS协议
	INT16U	uwSetBatParaEnable;				// 50	电池并联使能
	INT16U	uwSetBatTempCompensateEnable;	// 51	电池温度补偿使能
	INT16U	uwEEBatEqEn; 					// 52	EQ使能
	INT16U	uwEEBatEqVolt;					// 53	EQ电压
	INT16U	uwEEBatEqTime;					// 54	EQ时间
	INT16U	uwEEBatEqTimeout;				// 55	EQ超时时间
	INT16U	uwEEBatEqInterval;				// 56	EQ间隔时间
	INT16U	uwEEBatEqActImd; 				// 57	立即EQ使能
	INT16U	uwSetRsvd58;					// 58	预留
	INT16U	uwSetRsvd59; 					// 59	预留
	INT16U	uwBatLowVoltDerateEnable; 		// 60	电池低压降额使能
	INT16U	uwSetRsvd61; 					// 61	预留
	INT16U	uwSetRsvd62; 					// 62	预留
	INT16U	uwSetRsvd63; 					// 63	预留
}strBattDataSet;
#define cBattDataSetLength  ((sizeof(strBattDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetACOutputRatedPower; 		//	64	机器额定功率
	INT16U	uwSetACOutputRatedVolt;			//	65	额定输出电压
	INT16U	uwSetACOutputRatedFreq;			//	66	额定输出频率
	INT16U	uwSetGridInputRange; 			//	67	电网输入范围 0: APL,  1: UPS
	INT16U	uwSetOutputPriority; 			//	68	输出优先级 0：市电优先，1：光伏优先，2：市电和光伏 3：调度模式
	INT16U	uwSetWorkMode;					//	69	工作模式0: 卖电优先1: 防逆流 to Load（负载优先，电池优先2: 防逆流 to CT（负载优先，电池优先)3: 调度模式
	INT16U	uwSetRsvd70; 					//	70	预留
	INT16U	uwSetRsvd71; 					//	71	预留
	INT16U	uwSetRsvd72; 					//	72	预留
	INT16U	uwSetGridPeakShavingEnable;		//	73	电网最大输入功率限制使能
	INT16U	uwSetGridPeakShavingPower;		//	74	电网最大输入功率
	INT16U	uwSetGridPeakShavingCurr;		//	75	电网最大输入电流
	INT16U	uwMaxFeedPower; 				//	76	最大馈网功率
	INT16S	uwSetRsvd77; 					//	77	预留
	INT16U	uwSetRsvd78; 					//	78	预留
	INT16U	uwSetRsvd79; 					//	79	预留
	INT16S	uwSetRsvd80; 					//	80	预留
	INT16S	uwSetRsvd81; 					//	81	预留
	INT16U	uwSetRecconectWaitTime;			//	82	并网等待时间
	INT16U	uwSetAnti_IslandProtectEnable;	//	83	主动孤岛保护使能
	INT16U	uwSetRsvd84;					//	84	预留
	INT16U	uwSetPowerSaveMode;				//	85	节能模式
	INT16U	uwPowerConversion;				//	86	功率折算使能	// for test
	INT16U	uwSetOverTempRestartEn;			//	87	过温重启使能
	INT16U	uwSetOverLoadRestartEn;			//	88	过载重启使能
	INT16U	uwSetOverLoadBypassEn;			//	89	过载转旁路使能
	INT16U	uwFeedToLineTime; 				//	90	离网转并网时间 ms
	INT16U	uwSetRsvd91; 					//	91	预留
	INT16U	uwSetRsvd92; 					//	92	预留
	INT16U	uwSetRsvd93; 					//	93	预留
	INT16U	uwSetRsvd94; 					//	94	预留
	INT16U	uwSetRsvd95; 					//	95	预留
	INT16U	uwSetRsvd96; 					//	96	预留
	INT16U	uwSetRsvd97; 					//	97	预留
}strAcDataSet;
#define cAcDataSetLength  ((sizeof(strAcDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U uwSetRsvd98;				//	98	预留
	INT16U uwSetRsvd99;				//	99	预留
	INT16U uwSetRsvd100;			//	100	预留
	INT16U uwSetRsvd101;			//	101	预留
}strReserveSet;
#define cReserveSetLength  ((sizeof(strReserveSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetGrid1OVValue;		//	102 电网过压1段(%)
	INT16U	uwSetGrid1OVTime;		//	103 电网过压1段时间(10ms)，最大655350ms,也就是655s
	INT16U	uwSetGrid2OVValue;		//	104 电网过压2段(%)
	INT16U	uwSetGrid2OVTime;		//	105 电网过压2段时间(10ms)
	INT16U	uwSetGrid3OVValue;		//	106 电网过压3段(%)
	INT16U	uwSetGrid3OVTime;		//	107 电网过压3段时间(10ms)
	INT16U	uwSetGrid1UVValue;		//	108 电网欠压1段(%)
	INT16U	uwSetGrid1UVTime;		//	109 电网欠压1段时间(10ms)
	INT16U	uwSetGrid2UVValue;		//	110 电网欠压2段(%)
	INT16U	uwSetGrid2UVTime;		//	111 电网欠压2段时间(10ms)
	INT16U	uwSetGrid3UVValue;		//	112 电网欠压3段(%)
	INT16U	uwSetGrid3UVTime;		//	113 电网欠压3段时间(10ms)
	INT16U	uwSetGrid1OFValue;		//	114 电网过频1段(0.01Hz)
	INT16U	uwSetGrid1OFTime;		//	115 电网过频1段时间(10ms)
	INT16U	uwSetGrid2OFValue;		//	116 电网过频2段(0.01Hz)
	INT16U	uwSetGrid2OFTime;		//	117 电网过频2段时间(10ms)
	INT16U	uwSetGrid3OFValue;		//	118 电网过频3段(0.01Hz)
	INT16U	uwSetGrid3OFTime;		//	119 电网过频3段时间(10ms)
	INT16U	uwSetGrid1UFValue;		//	120 电网欠频1段(0.01Hz)
	INT16U	uwSetGrid1UFTime;		//	121 电网欠频1段时间(10ms)
	INT16U	uwSetGrid2UFValue;		//	122 电网欠频2段(0.01Hz)
	INT16U	uwSetGrid2UFTime;		//	123 电网欠频2段时间(10ms)
	INT16U	uwSetGrid3UFValue;		//	124 电网欠频3段(0.01Hz)
	INT16U	uwSetGrid3UFTime;		//	125 电网欠频3段时间(10ms)
	INT16U	uwSetRsvd126;			//	126 预留
	INT16U	uwSetRsvd127;			//	127 预留
	INT16U	uwSetRsvd128;			//	128 预留
	INT16U	uwSetRsvd129;			//	129 预留
	INT16U	uwSetRsvd130;			//	130 预留
	INT16U	uwSetRsvd131;			//	131 预留
}strLineProtectSet;
#define cLineProtectSetLength  ((sizeof(strLineProtectSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetECO_TimeOfUse;			//	132 经济模式使能
	INT16U	uwSetECO_EffectiveWeek;		//	133 生效星期
	INT16U	uwSetECO1_GridChargeEnable;	//	134 规则1电网充电使能
	INT16U	uwSetECO1_GenChargeEnable;	//	135 规则1油机充电使能
	INT16U	uwSetECO1_StartTime; 		//	136 规则1起始时间
	INT16U	uwSetECO1_StopTime;			//	137 规则1结束时间
	INT16U	uwSetECO1_Volt;				//	138 规则1目标电压
	INT16U	uwSetECO1_SOC;				//	139 规则1目标SOC（BMS连接采用）
	INT16U	uwSetECO1_Power; 			//	140 规则1放电功率
	INT16U	uwSetECO1_WorkModeSet;		//	141 规则1工作模式设定
	INT16U	uwSetECO2_GridChargeEnable;	//	142 规则2电网充电使能
	INT16U	uwSetECO2_GenChargeEnable;	//	143 规则2油机充电使能
	INT16U	uwSetECO2_StartTime;		//	144 规则2起始时间
	INT16U	uwSetECO2_StopTime;			//	145 规则2结束时间
	INT16U	uwSetECO2_Volt;				//	146 规则2目标电压
	INT16U	uwSetECO2_SOC;				//	147 规则2目标SOC（BMS连接采用）
	INT16U	uwSetECO2_Power; 			//	148 规则2放电功率
	INT16U	uwSetECO2_WorkModeSet;		//	149 规则2工作模式设定
	INT16U	uwSetECO3_GridChargeEnable;	//	150 规则3电网充电使能
	INT16U	uwSetECO3_GenChargeEnable;	//	151 规则3油机充电使能
	INT16U	uwSetECO3_StartTime; 		//	152 规则3起始时间
	INT16U	uwSetECO3_StopTime;			//	153 规则3结束时间
	INT16U	uwSetECO3_Volt;				//	154 规则3目标电压
	INT16U	uwSetECO3_SOC;				//	155 规则3目标SOC（BMS连接采用）
	INT16U	uwSetECO3_Power; 			//	156 规则3放电功率
	INT16U	uwSetECO3_WorkModeSet;		//	157 规则3工作模式设定
	INT16U	uwSetECO4_GridChargeEnable;	//	158 规则4电网充电使能
	INT16U	uwSetECO4_GenChargeEnable;	//	159 规则4油机充电使能
	INT16U	uwSetECO4_StartTime; 		//	160 规则4起始时间
	INT16U	uwSetECO4_StopTime;			//	161 规则4结束时间
	INT16U	uwSetECO4_Volt;				//	162 规则4目标电压
	INT16U	uwSetECO4_SOC;				//	163 规则4目标SOC（BMS连接采用）
	INT16U	uwSetECO4_Power; 			//	164 规则4放电功率
	INT16U	uwSetECO4_WorkModeSet;		//	165 规则4工作模式设定
	INT16U	uwSetECO5_GridChargeEnable;	//	166 规则5电网充电使能
	INT16U	uwSetECO5_GenChargeEnable;	//	167 规则5油机充电使能
	INT16U	uwSetECO5_StartTime; 		//	168 规则5起始时间
	INT16U	uwSetECO5_StopTime;			//	169 规则5结束时间
	INT16U	uwSetECO5_Volt;				//	170 规则5目标电压
	INT16U	uwSetECO5_SOC;				//	171 规则5目标SOC（BMS连接采用）
	INT16U	uwSetECO5_Power; 			//	172 规则5放电功率
	INT16U	uwSetECO5_WorkModeSet;		//	173 规则5工作模式设定
	INT16U	uwSetECO6_GridChargeEnable;	//	174 规则6电网充电使能
	INT16U	uwSetECO6_GenChargeEnable;	//	175 规则6油机充电使能
	INT16U	uwSetECO6_StartTime; 		//	176 规则6起始时间
	INT16U	uwSetECO6_StopTime;			//	177 规则6结束时间
	INT16U	uwSetECO6_Volt;				//	178 规则6目标电压
	INT16U	uwSetECO6_SOC;				//	179 规则6目标SOC（BMS连接采用）
	INT16U	uwSetECO6_Power; 			//	180 规则6放电功率
	INT16U	uwSetECO6_WorkModeSet;		//	181 规则6工作模式设定
	INT16U	uwSetRsvd182;				//	182 预留
	INT16U	uwSetRsvd183;				//	183 预留
	INT16U	uwFlag1;					//	184 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC1;				//	185 CRC校验
}strECOModeSet;
#define cECOModeSetLength  ((sizeof(strECOModeSet)/sizeof(INT16U))*2)

struct EepromStruct1
{
	strControlStateSet strControlState;		//状态控制位设置
	strPVDataSet strPvData;					//PV参数设置
	strBattDataSet strBatData;				//电池参数设置
	strAcDataSet strAcData;					//AC参数设置
	strReserveSet strReserve;				//预留功能
	strLineProtectSet strLineProtect;		//市电保护参数设置
	strECOModeSet strECOMode;				//经济模式设置
};

struct EepromStruct2
{
	INT16S	uwEEPV1VoltAdj;				//	186 PV1电压校准系数
	INT16S	uwEEPV1VoltBias; 			//	187 PV1电压校准偏置
	INT16S	uwEEPV2VoltAdj;				//	188 PV2电压校准系数
	INT16S	uwEEPV2VoltBias; 			//	189 PV2电压校准偏置
	INT16S	uwEEPV1BatCurrAdj;			//	190 PV1电池电流校准系数
	INT16S	uwEEPV1BatCurrBias; 		//	191 PV1电池电流校准偏置
	INT16S	uwEEPV2BatCurrAdj;			//	192 PV2电池电流校准系数
	INT16S	uwEEPV2BatCurrBias; 		//	193 PV2电池电流校准偏置
	INT16S	uwEEBatVoltAdj;				//	194 电池电压校准系数
	INT16S	uwEEBatVoltBias; 			//	195 电池电压校准偏置
	INT16S	uwEEBatCurrAdj;				//	196 电池电流校准系数
	INT16S	uwEEBatCurrBias; 			//	197 电池电流校准偏置
	INT16S	uwEEBUSVoltAdj;				//	198 Bus电压校准系数
	INT16S	uwEEBUSVoltBias; 			//	199 Bus电压校准偏置
	INT16S	uwEEBUSCurrAdj;				//	200 Bus电流校准系数
	INT16S	uwEEBUSCurrBias; 			//	201 Bus电流校准偏置
	INT16S	uwEEInvVoltAdj;				//	202 逆变电压校准系数
	INT16S	uwEEInvVoltBias; 			//	203 逆变电压校准偏置
	INT16S	uwEEInvCurrAdj;				//	204 逆变电流校准系数
	INT16S	uwEEInvCurrBias; 			//	205 逆变电流校准偏置
	INT16S	uwEEGridVoltAdj; 			//	206 电网电压校准系数
	INT16S	uwEEGridVoltBias;			//	207 电网电压校准偏置
	INT16S	uwEEGridCurrAdj; 			//	208 电网电流校准系数
	INT16S	uwEEGridCurrBias;			//	209 电网电流校准偏置
	INT16S	uwEEOPVoltAdj;				//	210 输出电压校准系数
	INT16S	uwEEOpVoltBias;				//	211 输出电压校准偏置
	INT16S	uwEEOPCurrAdj;				//	212 输出电流校准系数
	INT16S	uwEEOpCurrBias;				//	213 输出电流校准偏置
	INT16U	uwEEDischargeEneyCoeffH; 	//	214 放电量校准高位
	INT16U	uwEEDischargeEneyCoeffL; 	//	215 放电量校准低位
	INT16U	uwEEchargeEneyCoeffH;		//	216 充电量校准高位
	INT16U	uwEEchargeEneyCoeffL;		//	217 充电量校准低位
	INT16U	uwSetRsvd218;				//	218 预留
	INT16U	uwSetRsvd219;				//	219 预留
	INT16U	uwSetRsvd220;				//	220 预留
	INT16U	uwSetRsvd221;				//	221 预留
	INT16U	uwSetRsvd222;				//	222 预留
	INT16U	uwSetRsvd223;				//	223 预留
	INT16U	uwSetRsvd224;				//	224 预留
	INT16U	uwSetRsvd225;				//	225 预留
	INT16U	uwSetRsvd226;				//	226 预留
	INT16U	uwSetRsvd227;				//	227 预留
	INT16U	uwSetRsvd228;				//	228 预留
	INT16U	uwSetRsvd229;				//	229 预留
	INT16U	uwSetRsvd230;				//	230 预留
	INT16U	uwSetRsvd231;				//	231 预留
	INT16U	uwSetRsvd232;				//	232 预留
	INT16U	uwSetRsvd233;				//	233 预留
	INT16U	uwFlag2;					//	276 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC2;				//	235 CRC校验
};

struct EepromStruct3
{
	INT16U	uwATE_SN1;					//	236 机器序列号1
	INT16U	uwATE_SN2;					//	237 机器序列号2
	INT16U	uwATE_SN3;					//	238 机器序列号3
	INT16U	uwATE_SN4;					//	239 机器序列号4
	INT16U	uwATE_SN5;					//	240 机器序列号5
	INT16U	uwATE_SNLen; 				//	241 机器序列号长度
	INT16U	uwATE_DispHwVer; 			//	242 ATE写显示板版本号
	INT16U	uwATE_CtrlHwVer; 			//	243 ATE写控制板版本号
	INT16U	uwATE_PowerHwVer;			//	244 ATE写功率板版本号
	INT16U	uwATE_UpdateFW;				//	245 升级固件
	INT16U	uwATE_ResetSystem;			//	246 复位重启
	INT16U	uwATE_EEDefault; 			//	247 EE恢复默认值
	INT16U	uwATE_AgingMode; 			//	248 老化模式
	INT16U	uwATE_RemoteOnOff;			//	249 远程控制开关
	INT16U	uwATE_EEFactory; 			//	250 EE恢复出厂设置
	INT16U	uwATE_AgingBattVolt; 		//	251 老化电池启动电压
	INT16U	uwATE_AgingBattCurr; 		//	252 老化电池放电电流
	INT16U	uwATE_AgingPVPower;			//	253 老化最大PV功率
	INT16U	uwATE_AgingInvPower; 		//	254 老化最大逆变功率
	INT16U	uwATE_MPPTVoltCntl;			//	255 MPPT电压点控制
	INT16U	uwATE_E_totalClr;			//	256 发电量发电时间清零设置
	INT16U	uwATE_SafetyCode;			//	257 安规设置
	INT16U	uwATE_ISOsetting;			//	258 绝缘阻抗设置
	INT16U	uwATE_EleMeterProc;			//	259 电表协议选择
	INT16U	uwATE_ExCommBps; 			//	260 Wifi通讯地址和波特率
	INT16U	uwATE_EleMeterBps_Parity;	//	261 与电表通讯波特率和校验位
	INT16U	uwATE_EleMeterAddr;			//	262 与电表通讯地址
	INT16U	uwATE_EleMeterWREn;			//	263 电表使能写，禁止读
	INT16U	uwATE_EleMeterDataRegAddr;	//	264 电表Modbus地址
	INT16U	uwATE_EleMeterData;			//	265 电表数据
	INT16U	uwATE_485CommBps;			//	266 485通讯地址和波特率
	INT16U	uwMenuRtnDftPageEn;			//	267 自动返回到显示屏幕的第一页
	INT16U	uwSetLCDBacklight;			//	268 LCD背光
	INT16U	uwSetBuzzerBeep; 			//	269 蜂鸣器
	INT16U	uwSetBmsBagAddr; 			//	270 电池包地址
	INT16U	uwSetClearEventLog;			//	271 清除事件记录
	INT16U	uwSetEventLogFunc;			//	272 事件记录功能
	INT16U	uwSetFaultLogFunc;			//	273 故障记录功能
	INT16U	uwSetLogType;				//	274 Log查询类型
	INT16U	uwSetLogIndex;				//	275 Log索引
	INT16U	uwFlag3;					//	276 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC3;				//	277 CRC校验
};


#define		cEepromTotalLength1		(sizeof(struct	EepromStruct1)*2)	// 370bytes
#define		cEepromTotalLength2		(sizeof(struct	EepromStruct2)*2)	// 100bytes
#define		cEepromTotalLength3		(sizeof(struct	EepromStruct3)*2)	// 84bytes

#define		cEeprom1Address			0		
#define		cEeprom2Address			0x200		//Check  if cEepromTotalLength1 over 0x200
#define		cEeprom3Address			0x300		//Check  if cEepromTotalLength2 over 0x100
#define		cEeprom1BackupAddress	0x500		
#define		cEeprom2BackupAddress	0x700		//Check  if cEepromTotalLength1 over 0x200
#define		cEeprom3BackupAddress	0x800		//Check  if cEepromTotalLength2 over 0x100
#define		cEepromResAddress		0xB00

typedef union 
{
	INT16U	wEepromCfg1[cEepromTotalLength1/2];
	struct  EepromStruct1 EepromStructCfg1;
}UNEEpromCfg1;

typedef union 
{
	INT16U	wEepromCfg2[cEepromTotalLength2/2];
	struct  EepromStruct2 EepromStructCfg2;
}UNEEpromCfg2;
//extern UNEEpromCfg2;

typedef union 
{
	INT16U	wEepromCfg3[cEepromTotalLength3/2];
	struct  EepromStruct3 EepromStructCfg3;
}UNEEpromCfg3;

extern UNEEpromCfg1 uEepromCfg1;
extern UNEEpromCfg2 uEepromCfg2;
extern UNEEpromCfg3 uEepromCfg3;

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
EEPROM	void	sEepromInitial(void);
EEPROM	void	sEepromRead1(void);
EEPROM	void	sEepromRead2(void);
EEPROM	void	sEepromRead3(void);
EEPROM	void	sEepromSave1(void);
EEPROM	void	sEepromSave2(void);
EEPROM	void	sEepromSave3(void);
EEPROM	void	sEepromDefaultSave1(void);
EEPROM	void	sEepromDefaultSave2(void);
EEPROM	void	sEepromDefaultSave3(void);
EEPROM	void	sEepromDataRangeChk(void);
EEPROM	void	sEepromDataVarRangeChk(void);

EEPROM	void	sEepromSaveMode1(INT16U wFilter);
EEPROM	void	sEepromSaveMode2(INT16U wFilter);
EEPROM	void	sEepromSaveMode3(INT16U wFilter);
EEPROM	void	sEepromSecureLockClr(INT16U	wFilter);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
EEPROM INT8U sbGetEepromRwEnable(void);
EEPROM INT8U sbGetEepromRwBusy(void);
EEPROM INT8U sbGetEepromSecureLock(void);
EEPROM INT16U swGetEeprom1MapData(INT16U wAddrOffset);
EEPROM INT16U swGetEeprom2MapData(INT16U wAddrOffset);
EEPROM INT16U swGetEeprom3MapData(INT16U wAddrOffset);
EEPROM INT16U suwGetEEMachineID(void);
EEPROM INT16U suwGetEEParaEnable(void);
EEPROM INT16U suwGetEEMasterSlaver(void);
EEPROM INT16U suwGetEEAutoWrite(void);
EEPROM INT16U suwGetEESystemOutputMode(void);
EEPROM INT16U suwGetEEFanWorkMode(void);
EEPROM INT16U suwGetEETurboMode(void);
EEPROM INT16U suwGetEEAutoInvEnable(void);
EEPROM INT16U suwGetEEDCDCOpenLoopEnable(void);
EEPROM INT16U suwGetEELogoEnable(void);
EEPROM INT16U suwGetEEAdcBiasAdj(void);
EEPROM INT16U suwGetEEReserve11(void);
EEPROM INT16U suwGetEEReserve12(void);
EEPROM INT16U suwGetEEReserve13(void);
EEPROM INT16U suwGetEEReserve14(void);
EEPROM INT16U suwGetEEPV1StartVolt(void);
EEPROM INT16U suwGetEEReserve16(void);
EEPROM INT16U suwGetEEPV_PowerLimit(void);
EEPROM INT16U suwGetEEReserve18(void);
EEPROM INT16U suwGetEEReserve19(void);
EEPROM INT16U suwGetEEPV_Priority(void);
EEPROM INT16U suwGetEEPVAutoInvEnable(void);
EEPROM INT16U suwGetEERsvd22(void);
EEPROM INT16U suwGetEEBatType(void);
EEPROM INT16U suwGetEEBatSeriesNum(void);
EEPROM INT16U suwGetEEBatCapacity(void);
EEPROM INT16U suwGetEERsvd26(void);
EEPROM INT16U suwGetEEBatMode(void);
EEPROM INT16U suwGetEEChargePriority(void);
EEPROM INT16U suwGetEEBatConstVolt(void);
EEPROM INT16U suwGetEEBatFloatVolt(void);
EEPROM INT16U suwGetEEBatFloatTime(void);
EEPROM INT16U suwGetEEBatMaxChgCurr(void);
EEPROM INT16U suwGetEEBatMaxDcgCurr(void);
EEPROM INT16U suwGetEEGridChgBatCurr(void);
EEPROM INT16U suwGetEEGridChgBatTotalEnable(void);
EEPROM INT16U suwGetEEOnGridBatAutoStartChgSOC(void);
EEPROM INT16U suwGetEEOnGridBatExitAutoChgSOC(void);
EEPROM INT16U suwGetEEOnGridBatAutoStartChgVolt(void);
EEPROM INT16U suwGetEEOnGridBatExitAutoChgVolt(void);
EEPROM INT16U suwGetEEBatACRestartVolt(void);
EEPROM INT16U suwGetEEBatLowAlarmVolt(void);
EEPROM INT16U suwGetEEBatLowShutDownVolt(void);
EEPROM INT16U suwGetEEBatACRestartSOC(void);
EEPROM INT16U suwGetEEBatLowAlarmSOC(void);
EEPROM INT16U suwGetEEBatLowShutDownSOC(void);
EEPROM INT16U suwGetEEBatVoltOverShut(void);
EEPROM INT16U suwGetEEBatActivateEnable(void);
EEPROM INT16U suwGetEEBMSComErrEnable(void);
EEPROM INT16U suwGetEEBMSProtocol(void);
EEPROM INT16U suwGetEEBatParaEnable(void);
EEPROM INT16U suwGetEEBatTempCompensateEnable(void);
EEPROM INT16U suwGetEEBatEqEn(void);
EEPROM INT16U suwGetEEBatEqVolt(void);
EEPROM INT16U suwGetEEBatEqTime(void);
EEPROM INT16U suwGetEEBatEqTimeout(void);
EEPROM INT16U suwGetEEBatEqInterval(void);
EEPROM INT16U suwGetEEBatEqActImd(void);
EEPROM INT16U suwGetEERsvd58(void); 
EEPROM INT16U suwGetEERsvd59(void);
EEPROM INT16U suwGetEEBatLowVoltDerateEnable(void);
EEPROM INT16U suwGetEERsvd61(void);
EEPROM INT16U suwGetEERsvd62(void);
EEPROM INT16U suwGetEERsvd63(void);
EEPROM INT16U suwGetEEACOutputRatedPower(void);
EEPROM INT16U suwGetEEACOutputRatedVolt(void);
EEPROM INT16U suwGetEEACOutputRatedFreq(void);
EEPROM INT16U suwGetEEGridInputRange(void);
EEPROM INT16U suwGetEEOutputPriority(void);
EEPROM INT16U suwGetEEWorkMode(void);
EEPROM INT16U suwGetEERsvd70(void);
EEPROM INT16U suwGetEERsvd71(void);
EEPROM INT16U suwGetEERsvd72(void);
EEPROM INT16U suwGetEEGridPeakShavingEnable(void);
EEPROM INT16U suwGetEEGridPeakShavingPower(void);
EEPROM INT16U suwGetEEGridPeakShavingCurr(void);
EEPROM INT16U suwGetEEMaxFeedPower(void);
EEPROM INT16U suwGetEERsvd77(void);
EEPROM INT16U suwGetEERsvd78(void);
EEPROM INT16U suwGetEERsvd79(void);
EEPROM INT16U suwGetEERsvd80(void);
EEPROM INT16U suwGetEERsvd81(void);
EEPROM INT16U suwGetEERecconectWaitTime(void);
EEPROM INT16U suwGetEEAnti_IslandProtectEnable(void);
EEPROM INT16U suwGetEERsvd84(void);
EEPROM INT16U suwGetEEPowerSaveMode(void);
EEPROM INT16U suwGetEEPowerConversion(void);
EEPROM INT16U suwGetEEOverTempRestartEn(void);
EEPROM INT16U suwGetEEOverLoadRestartEn(void);
EEPROM INT16U suwGetEEOverLoadBypassEn(void);
EEPROM INT16U suwGetEEFeedToLineTime(void);
EEPROM INT16U suwGetEERsvd91(void);
EEPROM INT16U suwGetEERsvd92(void);
EEPROM INT16U suwGetEERsvd93(void);
EEPROM INT16U suwGetEERsvd94(void);
EEPROM INT16U suwGetEERsvd95(void);
EEPROM INT16U suwGetEERsvd96(void);
EEPROM INT16U suwGetEERsvd97(void);
EEPROM INT16U suwGetEERsvd98(void);
EEPROM INT16U suwGetEERsvd99(void);
EEPROM INT16U suwGetEERsvd100(void);
EEPROM INT16U suwGetEERsvd101(void);
EEPROM INT16U suwGetEEGrid1OVValue(void);
EEPROM INT16U suwGetEEGrid1OVTime(void);
EEPROM INT16U suwGetEEGrid2OVValue(void);
EEPROM INT16U suwGetEEGrid2OVTime(void);
EEPROM INT16U suwGetEEGrid3OVValue(void);
EEPROM INT16U suwGetEEGrid3OVTime(void);
EEPROM INT16U suwGetEEGrid1UVValue(void);
EEPROM INT16U suwGetEEGrid1UVTime(void);
EEPROM INT16U suwGetEEGrid2UVValue(void);
EEPROM INT16U suwGetEEGrid2UVTime(void);
EEPROM INT16U suwGetEEGrid3UVValue(void);
EEPROM INT16U suwGetEEGrid3UVTime(void);
EEPROM INT16U suwGetEEGrid1OFValue(void);
EEPROM INT16U suwGetEEGrid1OFTime(void);
EEPROM INT16U suwGetEEGrid2OFValue(void);
EEPROM INT16U suwGetEEGrid2OFTime(void);
EEPROM INT16U suwGetEEGrid3OFValue(void);
EEPROM INT16U suwGetEEGrid3OFTime(void);
EEPROM INT16U suwGetEEGrid1UFValue(void);
EEPROM INT16U suwGetEEGrid1UFTime(void);
EEPROM INT16U suwGetEEGrid2UFValue(void);
EEPROM INT16U suwGetEEGrid2UFTime(void);
EEPROM INT16U suwGetEEGrid3UFValue(void);
EEPROM INT16U suwGetEEGrid3UFTime(void);
EEPROM INT16U suwGetEERsvd126(void);
EEPROM INT16U suwGetEERsvd127(void);
EEPROM INT16U suwGetEERsvd128(void);
EEPROM INT16U suwGetEERsvd129(void);
EEPROM INT16U suwGetEERsvd130(void);
EEPROM INT16U suwGetEERsvd131(void);
EEPROM INT16U suwGetEEECO_TimeOfUse(void);
EEPROM INT16U suwGetEEECO_EffectiveWeek(void);
EEPROM INT16U suwGetEEECO1_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO1_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO1_StartTime(void);
EEPROM INT16U suwGetEEECO1_StopTime(void);
EEPROM INT16U suwGetEEECO1_Volt(void);
EEPROM INT16U suwGetEEECO1_SOC(void);
EEPROM INT16U suwGetEEECO1_Power(void);
EEPROM INT16U suwGetEEECO1_WorkModeSet(void);
EEPROM INT16U suwGetEEECO2_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO2_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO2_StartTime(void);
EEPROM INT16U suwGetEEECO2_StopTime(void);
EEPROM INT16U suwGetEEECO2_Volt(void);
EEPROM INT16U suwGetEEECO2_SOC(void);
EEPROM INT16U suwGetEEECO2_Power(void);
EEPROM INT16U suwGetEEECO2_WorkModeSet(void);
EEPROM INT16U suwGetEEECO3_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO3_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO3_StartTime(void);
EEPROM INT16U suwGetEEECO3_StopTime(void);
EEPROM INT16U suwGetEEECO3_Volt(void);
EEPROM INT16U suwGetEEECO3_SOC(void);
EEPROM INT16U suwGetEEECO3_Power(void);
EEPROM INT16U suwGetEEECO3_WorkModeSet(void);
EEPROM INT16U suwGetEEECO4_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO4_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO4_StartTime(void);
EEPROM INT16U suwGetEEECO4_StopTime(void);
EEPROM INT16U suwGetEEECO4_Volt(void);
EEPROM INT16U suwGetEEECO4_SOC(void);
EEPROM INT16U suwGetEEECO4_Power(void);
EEPROM INT16U suwGetEEECO4_WorkModeSet(void);
EEPROM INT16U suwGetEEECO5_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO5_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO5_StartTime(void);
EEPROM INT16U suwGetEEECO5_StopTime(void);
EEPROM INT16U suwGetEEECO5_Volt(void);
EEPROM INT16U suwGetEEECO5_SOC(void);
EEPROM INT16U suwGetEEECO5_Power(void);
EEPROM INT16U suwGetEEECO5_WorkModeSet(void);
EEPROM INT16U suwGetEEECO6_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO6_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO6_StartTime(void);
EEPROM INT16U suwGetEEECO6_StopTime(void);
EEPROM INT16U suwGetEEECO6_Volt(void);
EEPROM INT16U suwGetEEECO6_SOC(void);
EEPROM INT16U suwGetEEECO6_Power(void);
EEPROM INT16U suwGetEEECO6_WorkModeSet(void);
EEPROM INT16U suwGetEERsvd182(void);
EEPROM INT16U suwGetEERsvd183(void); 
EEPROM INT16U suwGetEEFlag1(void);
EEPROM INT16U suwGetEECheckCRC1(void);
EEPROM INT16S suwGetEEPV1VoltAdj(void);
EEPROM INT16S suwGetEEPV1VoltBias(void);
EEPROM INT16S suwGetEEPV2VoltAdj(void);
EEPROM INT16S suwGetEEPV2VoltBias(void);
EEPROM INT16S suwGetEEPV1BatCurrAdj(void);
EEPROM INT16S suwGetEEPV1BatCurrBias(void);
EEPROM INT16S suwGetEEPV2BatCurrAdj(void);
EEPROM INT16S suwGetEEPV2BatCurrBias(void);
EEPROM INT16S suwGetEEBatVoltAdj(void);
EEPROM INT16S suwGetEEBatVoltBias(void);
EEPROM INT16S suwGetEEBatCurrAdj(void);
EEPROM INT16S suwGetEEBatCurrBias(void);
EEPROM INT16S suwGetEEBUSVoltAdj(void);
EEPROM INT16S suwGetEEBUSVoltBias(void);
EEPROM INT16S suwGetEEBUSCurrAdj(void);
EEPROM INT16S suwGetEEBUSCurrBias(void);
EEPROM INT16S suwGetEEInvVoltAdj(void);
EEPROM INT16S suwGetEEInvVoltBias(void);
EEPROM INT16S suwGetEEInvCurrAdj(void);
EEPROM INT16S suwGetEEInvCurrBias(void);
EEPROM INT16S suwGetEEGridVoltAdj(void);
EEPROM INT16S suwGetEEGridVoltBias(void);
EEPROM INT16S suwGetEEGridCurrAdj(void);
EEPROM INT16S suwGetEEGridCurrBias(void);
EEPROM INT16S suwGetEEOPVoltAdj(void);
EEPROM INT16S suwGetEEOpVoltBias(void);
EEPROM INT16S suwGetEEOPCurrAdj(void);
EEPROM INT16S suwGetEEOpCurrBias(void);
EEPROM INT16U suwGetEEDischargeEneyCoeffH(void);
EEPROM INT16U suwGetEEDischargeEneyCoeffL(void);
EEPROM INT16U suwGetEEchargeEneyCoeffH(void);
EEPROM INT16U suwGetEEchargeEneyCoeffL(void);
EEPROM INT16U suwGetEERsvd218(void);
EEPROM INT16U suwGetEERsvd219(void);
EEPROM INT16U suwGetEERsvd220(void);
EEPROM INT16U suwGetEERsvd221(void);
EEPROM INT16U suwGetEERsvd222(void);
EEPROM INT16U suwGetEERsvd223(void);
EEPROM INT16U suwGetEERsvd224(void);
EEPROM INT16U suwGetEERsvd225(void);
EEPROM INT16U suwGetEERsvd226(void);
EEPROM INT16U suwGetEERsvd227(void);
EEPROM INT16U suwGetEERsvd228(void);
EEPROM INT16U suwGetEERsvd229(void);
EEPROM INT16U suwGetEERsvd230(void);
EEPROM INT16U suwGetEERsvd231(void);
EEPROM INT16U suwGetEERsvd232(void);
EEPROM INT16U suwGetEERsvd233(void);
EEPROM INT16U suwGetEEFlag2(void);
EEPROM INT16U suwGetEECheckCRC2(void);
EEPROM INT16U suwGetEEATE_SN1(void);
EEPROM INT16U suwGetEEATE_SN2(void);
EEPROM INT16U suwGetEEATE_SN3(void);
EEPROM INT16U suwGetEEATE_SN4(void);
EEPROM INT16U suwGetEEATE_SN5(void);
EEPROM INT16U suwGetEEATE_SNLen(void);
EEPROM INT16U suwGetEEATE_DispHwVer(void);
EEPROM INT16U suwGetEEATE_CtrlHwVer(void);
EEPROM INT16U suwGetEEATE_PowerHwVer(void);
EEPROM INT16U suwGetEEATE_UpdateFW(void);
EEPROM INT16U suwGetEEATE_ResetSystem(void);
EEPROM INT16U suwGetEEATE_EEDefault(void);
EEPROM INT16U suwGetEEATE_AgingMode(void);
EEPROM INT16U suwGetEEATE_RemoteOnOff(void);
EEPROM INT16U suwGetEEATE_EEFactory(void);
EEPROM INT16U suwGetEEATE_AgingBattVolt(void);
EEPROM INT16U suwGetEEATE_AgingBattCurr(void);
EEPROM INT16U suwGetEEATE_AgingPVPower(void);
EEPROM INT16U suwGetEEATE_AgingInvPower(void);
EEPROM INT16U suwGetEEATE_MPPTVoltCntl(void);
EEPROM INT16U suwGetEEATE_E_totalClr(void);
EEPROM INT16U suwGetEEATE_SafetyCode(void);
EEPROM INT16U suwGetEEATE_ISOsetting(void);
EEPROM INT16U suwGetEEATE_EleMeterProc(void);
EEPROM INT16U suwGetEEATE_ExCommBps(void);
EEPROM INT16U suwGetEEATE_EleMeterBps_Parity(void);
EEPROM INT16U suwGetEEATE_EleMeterAddr(void);
EEPROM INT16U suwGetEEATE_EleMeterWREn(void);
EEPROM INT16U suwGetEEATE_EleMeterDataRegAddr(void);
EEPROM INT16U suwGetEEATE_EleMeterData(void);
EEPROM INT16U suwGetEEATE_485CommBps(void);
EEPROM INT16U suwGetEEMenuRtnDftPageEn(void);
EEPROM INT16U suwGetEELCDBacklight(void);
EEPROM INT16U suwGetEEBuzzerBeep(void);
EEPROM INT16U suwGetEEBmsBagAddr(void);
EEPROM INT16U suwGetEEClearEventLog(void);
EEPROM INT16U suwGetEEEventLogFunc(void);
EEPROM INT16U suwGetEEFaultLogFunc(void);
EEPROM INT16U suwGetEELogType(void);
EEPROM INT16U suwGetEELogIndex(void);
EEPROM INT16U suwGetEEFlag3(void);
EEPROM INT16U suwGetEECheckCRC3(void);

// 下面的数据是临时用一下
EEPROM void		swGetEepromSOCSmoothEn(void);
EEPROM void		swGetBmsCellVoltNum(void);
EEPROM void		swGetBmsRatedAH(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
EEPROM	void	sSetEepromRwEnable(INT8U bStatus);
EEPROM	void	sSetEepromRwBusy(INT8U bStatus);
EEPROM	void	sSetEepromSecureLock(INT8U bStatus);
EEPROM	void	sSetEeprom1Mode(INT8U bMode);
EEPROM	void	sSetEeprom2Mode(INT8U bMode);
EEPROM	void	sSetEeprom3Mode(INT8U bMode);
EEPROM	void	sSetEEMachineID(INT16U uwtemp);
EEPROM	void	sSetEEParaEnable(INT16U uwtemp);
EEPROM	void	sSetEEMasterSlaver(INT16U uwtemp);
EEPROM	void	sSetEEAutoWrite(INT16U uwtemp);
EEPROM	void	sSetEESystemOutputMode(INT16U uwtemp);
EEPROM	void	sSetEEFanWorkMode(INT16U uwtemp);
EEPROM	void	sSetEETurboMode(INT16U uwtemp);
EEPROM	void	sSetEEAutoInvEnable(INT16U uwtemp);
EEPROM	void	sSetEEDCDCOpenLoopEnable(INT16U uwtemp);
EEPROM	void	sSetEELogoEnable(INT16U uwtemp);
EEPROM	void	sSetEEAdcBiasAdj(INT16U uwtemp);
EEPROM	void	sSetEEReserve11(INT16U uwtemp);
EEPROM	void	sSetEEReserve12(INT16U uwtemp);
EEPROM	void	sSetEEReserve13(INT16U uwtemp);
EEPROM	void	sSetEEReserve14(INT16U uwtemp);
EEPROM	void	sSetEEPV1StartVolt(INT16U uwtemp);
EEPROM	void	sSetEEReserve16(INT16U uwtemp);
EEPROM	void	sSetEEPV_PowerLimit(INT16U uwtemp);
EEPROM	void	sSetEEReserve18(INT16U uwtemp);
EEPROM	void	sSetEEReserve19(INT16U uwtemp);
EEPROM	void	sSetEEPV_Priority(INT16U uwtemp);
EEPROM	void	sSetEEPVAutoInvEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd22(INT16U uwtemp);
EEPROM	void	sSetEEBatType(INT16U uwtemp);
EEPROM	void	sSetEEBatSeriesNum(INT16U uwtemp);
EEPROM	void	sSetEEBatCapacity(INT16U uwtemp);
EEPROM	void	sSetEERsvd26(INT16U uwtemp);
EEPROM	void	sSetEEBatMode(INT16U uwtemp);
EEPROM	void	sSetEEChargePriority(INT16U uwtemp);
EEPROM	void	sSetEEBatConstVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatFloatVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatFloatTime(INT16U uwtemp);
EEPROM	void	sSetEEBatMaxChgCurr(INT16U uwtemp);
EEPROM	void	sSetEEBatMaxDcgCurr(INT16U uwtemp);
EEPROM	void	sSetEEGridChgBatCurr(INT16U uwtemp);
EEPROM	void	sSetEEGridChgBatTotalEnable(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatAutoStartChgSOC(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatExitAutoChgSOC(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatAutoStartChgVolt(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatExitAutoChgVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatACRestartVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatLowAlarmVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatLowShutDownVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatACRestartSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatLowAlarmSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatLowShutDownSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatVoltOverShut(INT16U uwtemp);
EEPROM	void	sSetEEBatActivateEnable(INT16U uwtemp);
EEPROM	void	sSetEEBMSComErrEnable(INT16U uwtemp);
EEPROM	void	sSetEEBMSProtocol(INT16U uwtemp);
EEPROM	void	sSetEEBatParaEnable(INT16U uwtemp);
EEPROM	void	sSetEEBatTempCompensateEnable(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqEn(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqVolt(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqTime(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqTimeout(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqInterval(INT16U uwtemp);
EEPROM	void	sSetEEEBatEqActImd(INT16U uwtemp);
EEPROM	void 	sSetEERsvd58(INT16U uwtemp);
EEPROM	void	sSetEERsvd59(INT16U uwtemp);
EEPROM	void	sSetEEBatLowVoltDerateEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd61(INT16U uwtemp);
EEPROM	void	sSetEERsvd62(INT16U uwtemp);
EEPROM	void	sSetEERsvd63(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedPower(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedVolt(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedFreq(INT16U uwtemp);
EEPROM	void	sSetEEGridInputRange(INT16U uwtemp);
EEPROM	void	sSetEEOutputPriority(INT16U uwtemp);
EEPROM	void	sSetEEWorkMode(INT16U uwtemp);
EEPROM	void	sSetEERsvd70(INT16U uwtemp);
EEPROM	void	sSetEERsvd71(INT16U uwtemp);
EEPROM	void	sSetEERsvd72(INT16U uwtemp);
EEPROM	void	sSetEEGridPeakShavingEnable(INT16U uwtemp);
EEPROM	void	sSetEEGridPeakShavingPower(INT16U uwtemp);
EEPROM	void	sSetEEGridPeakShavingCurr(INT16U uwtemp);
EEPROM	void	sSetEEMaxFeedPower(INT16U uwtemp);
EEPROM	void	sSetEERsvd77(INT16U uwtemp);
EEPROM	void	sSetEERsvd78(INT16U uwtemp);
EEPROM	void	sSetEERsvd79(INT16U uwtemp);
EEPROM	void	sSetEERsvd80(INT16U uwtemp);
EEPROM	void	sSetEERsvd81(INT16U uwtemp);
EEPROM	void	sSetEERecconectWaitTime(INT16U uwtemp);
EEPROM	void	sSetEEAnti_IslandProtectEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd84(INT16U uwtemp);
EEPROM	void	sSetEEPowerSaveMode(INT16U uwtemp);
EEPROM	void	sSetEEPowerConversion(INT16U uwtemp);
EEPROM	void	sSetEEOverTempRestartEn(INT16U uwtemp);
EEPROM	void	sSetEEOverLoadRestartEn(INT16U uwtemp);
EEPROM	void	sSetEEOverLoadBypassEn(INT16U uwtemp);
EEPROM	void	sSetEEFeedToLineTime(INT16U uwtemp);
EEPROM	void	sSetEERsvd91(INT16U uwtemp);
EEPROM	void	sSetEERsvd92(INT16U uwtemp);
EEPROM	void	sSetEERsvd93(INT16U uwtemp);
EEPROM	void	sSetEERsvd94(INT16U uwtemp);
EEPROM	void	sSetEERsvd95(INT16U uwtemp);
EEPROM	void	sSetEERsvd96(INT16U uwtemp);
EEPROM	void	sSetEERsvd97(INT16U uwtemp);
EEPROM	void	sSetEERsvd98(INT16U uwtemp);
EEPROM	void	sSetEERsvd99(INT16U uwtemp);
EEPROM	void	sSetEERsvd100(INT16U uwtemp);
EEPROM	void	sSetEERsvd101(INT16U uwtemp);
EEPROM	void	sSetEEGrid1OVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid1OVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid2OVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid2OVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid3OVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid3OVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid1UVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid1UVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid2UVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid2UVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid3UVValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid3UVTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid1OFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid1OFTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid2OFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid2OFTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid3OFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid3OFTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid1UFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid1UFTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid2UFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid2UFTime(INT16U uwtemp);
EEPROM	void	sSetEEGrid3UFValue(INT16U uwtemp);
EEPROM	void	sSetEEGrid3UFTime(INT16U uwtemp);
EEPROM	void	sSetEERsvd126(INT16U uwtemp);
EEPROM	void	sSetEERsvd127(INT16U uwtemp);
EEPROM	void	sSetEERsvd128(INT16U uwtemp);
EEPROM	void	sSetEERsvd129(INT16U uwtemp);
EEPROM	void	sSetEERsvd130(INT16U uwtemp);
EEPROM	void	sSetEERsvd131(INT16U uwtemp);
EEPROM	void	sSetEEECO_TimeOfUse(INT16U uwtemp);		
EEPROM	void	sSetEEECO_EffectiveWeek(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO1_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO2_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO3_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO4_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO5_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO6_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEERsvd182(INT16U uwtemp);		
EEPROM	void	sSetEERsvd183(INT16U uwtemp);		
EEPROM	void	sSetEEFlag1(INT16U uwtemp);		
EEPROM	void	sSetEECheckCRC1(INT16U uwtemp);
EEPROM	void	sSetEEPV1VoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEPV1VoltBias(INT16S uwtemp);
EEPROM	void	sSetEEPV2VoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEPV2VoltBias(INT16S uwtemp);
EEPROM	void	sSetEEPV1BatCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEPV1BatCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEPV2BatCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEPV2BatCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEBatVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEBatVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEBatCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEBatCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEBUSVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEBUSVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEBUSCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEBUSCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEInvVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEInvVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEInvCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEInvCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEGridVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEGridVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEGridCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEGridCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEOPVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEOpVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEOPCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEOpCurrBias(INT16S uwtemp);
EEPROM	void	sSetEEDischargeEneyCoeffH(INT16U uwtemp);
EEPROM	void	sSetEEDischargeEneyCoeffL(INT16U uwtemp);
EEPROM	void	sSetEEchargeEneyCoeffH(INT16U uwtemp);
EEPROM	void	sSetEEchargeEneyCoeffL(INT16U uwtemp);
EEPROM	void	sSetEERsvd218(INT16U uwtemp);
EEPROM	void	sSetEERsvd219(INT16U uwtemp);
EEPROM	void	sSetEERsvd220(INT16U uwtemp);
EEPROM	void	sSetEERsvd221(INT16U uwtemp);
EEPROM	void	sSetEERsvd222(INT16U uwtemp);
EEPROM	void	sSetEERsvd223(INT16U uwtemp);
EEPROM	void	sSetEERsvd224(INT16U uwtemp);
EEPROM	void	sSetEERsvd225(INT16U uwtemp);
EEPROM	void	sSetEERsvd226(INT16U uwtemp);
EEPROM	void	sSetEERsvd227(INT16U uwtemp);
EEPROM	void	sSetEERsvd228(INT16U uwtemp);
EEPROM	void	sSetEERsvd229(INT16U uwtemp);
EEPROM	void	sSetEERsvd230(INT16U uwtemp);
EEPROM	void	sSetEERsvd231(INT16U uwtemp);
EEPROM	void	sSetEERsvd232(INT16U uwtemp);
EEPROM	void	sSetEERsvd233(INT16U uwtemp);
EEPROM	void	sSetEEFlag2(INT16U uwtemp);
EEPROM	void	sSetEECheckCRC2(INT16U uwtemp);
EEPROM	void	sSetEEATE_SN1(INT16U uwtemp);
EEPROM	void	sSetEEATE_SN2(INT16U uwtemp);
EEPROM	void	sSetEEATE_SN3(INT16U uwtemp);
EEPROM	void	sSetEEATE_SN4(INT16U uwtemp);
EEPROM	void	sSetEEATE_SN5(INT16U uwtemp);
EEPROM	void	sSetEEATE_SNLen(INT16U uwtemp);
EEPROM	void	sSetEEATE_DispHwVer(INT16U uwtemp);
EEPROM	void	sSetEEATE_CtrlHwVer(INT16U uwtemp);
EEPROM	void	sSetEEATE_PowerHwVer(INT16U uwtemp);
EEPROM	void	sSetEEATE_UpdateFW(INT16U uwtemp);
EEPROM	void	sSetEEATE_ResetSystem(INT16U uwtemp);
EEPROM	void	sSetEEATE_EEDefault(INT16U uwtemp);
EEPROM	void	sSetEEATE_AgingMode(INT16U uwtemp);
EEPROM	void	sSetEEATE_RemoteOnOff(INT16U uwtemp);
EEPROM	void	sSetEEATE_EEFactory(INT16U uwtemp);
EEPROM	void	sSetEEATE_AgingBattVolt(INT16U uwtemp);
EEPROM	void	sSetEEATE_AgingBattCurr(INT16U uwtemp);
EEPROM	void	sSetEEATE_AgingPVPower(INT16U uwtemp);
EEPROM	void	sSetEEATE_AgingInvPower(INT16U uwtemp);
EEPROM	void	sSetEEATE_MPPTVoltCntl(INT16U uwtemp);
EEPROM	void	sSetEEATE_E_totalClr(INT16U uwtemp);
EEPROM	void	sSetEEATE_SafetyCode(INT16U uwtemp);
EEPROM	void	sSetEEATE_ISOsetting(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterProc(INT16U uwtemp);
EEPROM	void	sSetEEATE_ExCommBps(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterBps_Parity(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterAddr(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterWREn(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterDataRegAddr(INT16U uwtemp);
EEPROM	void	sSetEEATE_EleMeterData(INT16U uwtemp);
EEPROM	void	sSetEEATE_485CommBps(INT16U uwtemp);
EEPROM	void	sSetEEMenuRtnDftPageEn(INT16U uwtemp);
EEPROM	void	sSetEELCDBacklight(INT16U uwtemp);
EEPROM	void	sSetEEBuzzerBeep(INT16U uwtemp);
EEPROM	void	sSetEEBmsBagAddr(INT16U uwtemp);
EEPROM	void	sSetEEClearEventLog(INT16U uwtemp);
EEPROM	void	sSetEEEventLogFunc(INT16U uwtemp);
EEPROM	void	sSetEEFaultLogFunc(INT16U uwtemp);
EEPROM	void	sSetEELogType(INT16U uwtemp);
EEPROM	void	sSetEELogIndex(INT16U uwtemp);
EEPROM	void	sSetEEFlag3(INT16U uwtemp);
EEPROM	void	sSetEECheckCRC3(INT16U uwtemp);


#endif	// __EEEPROM_PROCESS_H__


