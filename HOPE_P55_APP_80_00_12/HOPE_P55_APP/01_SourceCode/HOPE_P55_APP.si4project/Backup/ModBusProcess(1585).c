/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__MODBUS_PROCESS_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
// 通用协议
#define INFO_REG_BASE_ADDR		0xF800				// 系统信息数据起始地址
#define INFO_REG_LEN			0x100				// 系统信息数据长度

#define ATE_REG_BASE_ADDR		0x4100				// ATE数据寄存器起始地址
#define ATE_REG_BASE_LEN		0x100				// ATE数据寄存器长度

#define DBG_CMD_BASE_ADDR		0xFC00				// 调试命令起始地址
#define DBG_CMD_LEN				0x100				// 调试命令长度

#define REALDATA_REG_BASE_ADDR	0x1100				// 实时数据寄存器起始地址
#define REALDATA_REG_BASE_LEN	0x100				// 实时数据寄存器长度

#define EE_REG_BASE_ADDR		0x2100				// EEPROM数据寄存器起始地址
#define EE_REG_BASE_LEN			0X200//(cEepromTotalLength1 + cEepromTotalLength2 + cEepromTotalLength3) / 2//0xC0				// EEPROM数据寄存器长度

#define WIFI_IOT_REG_BASE_ADDR	0x5100				// IOT数据寄存器起始地址
#define WIFI_IOT_REG_BASE_LEN	0X200

#define EMS_REG_BASE_ADDR		0x0100				// 电池包EMS数据起始地址(汇总数据)
#define EMS_REG_LEN				0x80				// 电池包EMS数据长度

#define BMS_REG_BASE_ADDR		0x0200				// 电池包BMS数据起始地址(单包数据)
#define BMS_REG_LEN				0x80				// 电池包BMS数据长度

#define BMS_INFO_REG_BASE_ADDR	0xF800				// 电池包Info数据起始地址
#define BMS_INFO_REG_LEN		0x20				// 电池包Info数据长度


#define cMODBUS_REG_RX_MAX_LEN			((cSCI_RX_LEN - 9) >> 1)
#define cMODBUS_REG_TX_MAX_LEN			((cSCI_TX_LEN - 5) >> 1)
#define cMODBUS_SWAP_RX_MAX_LEN			cMODBUS_REG_RX_MAX_LEN
#define cMODBUS_SWAP_TX_MAX_LEN			cMODBUS_REG_TX_MAX_LEN - 4


#define cMODBUS_ADDR_DEF				0x01
#define cMODBUS_ADDR_MIN				0x01
#define cMODBUS_ADDR_MAX				0x01
#define cMODBUS_ADDR_HOST				0x1E	// 30
#define cMODBUS_ADDR_BACKUP				0x1F	// 31

#define cMODBUS_ADDR					0x00
#define cMODBUS_CMD						0x01
#define cMODBUS_REG_ADDR_H				0x02
#define cMODBUS_REG_ADDR_L				0x03
#define cMODBUS_REG_NUM_H				0x04
#define cMODBUS_REG_NUM_L				0x05
#define cMODBUS_CRC_H					0x02
#define cMODBUS_CRC_L					0x01
#define cMODBUS_SWAP_RD_ADDR_H			0x02
#define cMODBUS_SWAP_RD_ADDR_L			0x03
#define cMODBUS_SWAP_RD_NUM_H			0x04
#define cMODBUS_SWAP_RD_NUM_L			0x05
#define cMODBUS_SWAP_WR_ADDR_H			0x06
#define cMODBUS_SWAP_WR_ADDR_L			0x07
#define cMODBUS_SWAP_WR_NUM_H			0x08
#define cMODBUS_SWAP_WR_NUM_L			0x09
#define cMODBUS_SWAP_WR_NUM				0x0A


#define cMODBUS_WRITE_DATA_START		0x04
#define cMODBUS_MULTI_WRITE_DATA_START	0x07
#define cMODBUS_SWAP_ER_DATA_START		0x0B

#define cMODBUS_MIN_LEN					0x08
#define cMODBUS_CRC_LEN					0x02

#define cREAD_CMD						0x03
#define cWRITE_CMD						0x06
#define cWRITE_CMD_MULTI				0x10
#define cSYNC_CMD						0x17

#define cErr_UnCmd						0x01
#define cErr_UnDataAddr					0x02
#define cErr_UnDataValue				0x03
#define cErr_DeviceBusy					0x06
#define cErr_PassdErr					0x10
#define cErr_CrcErr						0x11
#define cErr_ParUnValid					0x12
#define cErr_SysLock					0x13


enum EEPROM_WRITE_DATA_ID	// IVDM
{
	EE_uwAddrStart = 0,

	// EEPROM1
	EE_uwSetMachineID = EE_uwAddrStart,	//	0	机器地址设置
	EE_uwSetParaEnable,				//	1	Dsp并机使能
	EE_uwSetMasterSlaver,			//	2	主从机设置 
	EE_uwSetEepromAutoWrite, 		//	3	Eeprom自动写入
	EE_uwSetSystemOutputMode,		//	4	系统输出模式
	EE_uwSetFanWorkMode, 			//	5	风机运行模式
	EE_uwTurboMode,					//	6	Turbo模式使能
	EE_uwAutoInvEnable,				//	7	开机自动逆变
	EE_uwDCDCOpenLoopEnable, 		//	8	DCDC开环使能
	EE_uwsLogoEnable,				//	9	logo使能
	EE_uwAdcBiasAdj,				//	10	用于通信数据显示美化，例如无PV时采样到非0值时置零，0：美化 1：不美化
	EE_uwSetReserve11,				//	11	预留
	EE_uwSetReserve12,				//	12	预留
	EE_uwSetReserve13,				//	13	预留
	EE_uwSetReserve14,				//	14	预留
	EE_uwSetPV1StartVolt,			//	15	PV1启动电压
	EE_uwSetReserve16,				//	16	预留
	EE_uwSetPV_PowerLimit,			//	17	PV_最大功率
	EE_uwSetReserve18,				//	18	预留
	EE_uwSetReserve19,				//	19	预留
	EE_uwSetPV_Priority,		 	//	20	"PV能量优先级
	EE_uwPVAutoInvEnable,			//	21	单PV无电池开机自动逆变使能,如果有电池此项不生效
	EE_uwSetRsvd22,					//	22	预留
	EE_uwSetBatType,				//	23	电池类型
	EE_uwSetBatSeriesNum,			//	24	电池节数
	EE_uwSetBatCapacity, 			//	25	电池容量
	EE_uwSetRsvd26,					//	26	预留
	EE_uwSetBatMode, 				//	27	电池模式
	EE_uwSetChargePriority,			//	28	充电优先级
	EE_uwSetBatConstVolt,			//	29	电池恒压充电压
	EE_uwSetBatFloatVolt,			//	30	电池浮充电压
	EE_uwSetBatFloatTime,			//	31	电池恒充时间
	EE_uwSetBatMaxChgCurr,			//	32	电池最大充电电流限幅值
	EE_uwSetBatMaxDcgCurr,			//	33	电池最大放电电流限幅值
	EE_uwSetGridChgBatCurr,			//	34	电网至电池充电电流
	EE_uwSetGridChgBatTotalEnable,	//	35	电网充电总使能
	EE_uwSetOnGridBatAutoStartChgSOC,	//	36	并网时电池自动启动充电SOC点
	EE_uwSetOnGridBatExitAutoChgSOC, 	//	37	并网时电池自动退出充电SOC点
	EE_uwSetOnGridBatAutoStartChgVolt,	//	38	并网时电池自动启动充电电压点
	EE_uwSetOnGridBatExitAutoChgVolt,	//	39	并网时电池自动退出充电电压点
	EE_uwSetBatACRestartVolt,		//	40	电池重启AC输出电压点
	EE_uwSetBatLowAlarmVolt, 		//	41	电池低压告警电压点
	EE_uwSetBatLowShutDownVolt,		//	42	电池低压关机电压点
	EE_uwSetBatACRestartSOC, 		//	43	电池重启AC输出SOC点
	EE_uwSetBatLowAlarmSOC,			//	44	电池低压告警SOC点
	EE_uwSetBatLowShutDownSOC,		//	45	电池低压关机SOC点
	EE_uwSetBatVoltOverShut, 		//	46	电池过压保护点
	EE_uwSetBatActivateEnable,		//	47	电池激活使能
	EE_uwSetBMSComErrEnable, 		//	48	BMS通讯故障使能
	EE_uwSetBMSProtocol, 			//	49	BMS协议
	EE_uwSetBatParaEnable,			//	50	电池并联使能
	EE_uwSetBatTempCompensateEnable, //	51	电池温度补偿使能
	EE_uwEEBatEqEn,					//	52	EQ使能
	EE_uwEEBatEqVolt,				//	53	EQ电压
	EE_uwEEBatEqTime,				//	54	EQ时间
	EE_uwEEBatEqTimeout,			//	55	EQ超时时间
	EE_uwEEBatEqInterval,			//	56	EQ间隔时间
	EE_uwEEBatEqActImd,				//	57	立即EQ使能
	EE_uwSetRsvd58,					//	58	预留
	EE_uwSetRsvd59,					//	59	预留
	EE_uwBatLowVoltDerateEnable, 	//	60	电池低压降额使能
	EE_uwSetRsvd61,					//	61	预留
	EE_uwSetRsvd62,					//	62	预留
	EE_uwSetRsvd63,					//	63	预留
	EE_uwSetACOutputRatedPower,		//	64	机器额定功率
	EE_uwSetACOutputRatedVolt,		//	65	额定输出电压
	EE_uwSetACOutputRatedFreq,		//	66	额定输出频率
	EE_uwSetGridInputRange,			//	67	电网输入范围
	EE_uwSetOutputPriority,			//	68	输出优先级
	EE_uwSetWorkMode,				//	69	工作模式
	EE_uwSetRsvd70,					//	70	预留
	EE_uwSetRsvd71,					//	71	预留
	EE_uwSetRsvd72,					//	72	预留
	EE_uwSetGridPeakShavingEnable,	//	73	电网最大输入功率限制使能
	EE_uwSetGridPeakShavingPower,	//	74	电网最大输入功率
	EE_uwSetGridPeakShavingCurr,	//	75	电网最大输入电流
	EE_uwMaxFeedPower,				//	76	最馈网功率
	EE_uwSetRsvd77,					//	77	预留
	EE_uwSetRsvd78,					//	78	预留
	EE_uwSetRsvd79,					//	79	预留
	EE_uwSetRsvd80,					//	80	预留
	EE_uwSetRsvd81,					//	81	预留
	EE_uwSetRecconectWaitTime,		//	82	并网等待时间
	EE_uwSetAnti_IslandProtectEnable,//	83	主动孤岛保护使能
	EE_uwSetRsvd84,					//	84	预留
	EE_uwSetPowerSaveMode,			//	85	节能模式
	EE_uwPowerConversion,			//	86	功率折算使能
	EE_uwSetOverTempRestartEn,		//	87	过温重启使能
	EE_uwSetOverLoadRestartEn,		//	88	过载重启使能
	EE_uwSetOverLoadBypassEn,		//	89	过载转旁路使能
	EE_uwFeedToLineTime,			//	90	离网转并网时间
	EE_uwSetRsvd91,					//	91	预留
	EE_uwSetRsvd92,					//	92	预留
	EE_uwSetRsvd93,					//	93	预留
	EE_uwSetRsvd94,					//	94	预留
	EE_uwSetRsvd95,					//	95	预留
	EE_uwSetRsvd96,					//	96	预留
	EE_uwSetRsvd97,					//	97	预留
	EE_uwSetRsvd98,					//	98	预留
	EE_uwSetRsvd99,					//	99	预留
	EE_uwSetRsvd100, 				//	100 预留
	EE_uwSetRsvd101, 				//	101 预留
	EE_uwSetGrid1OVValue,			//	102 电网过压1段(%)
	EE_uwSetGrid1OVTime, 			//	103 "电网过压1段时间(10ms)，
	EE_uwSetGrid2OVValue,			//	104 电网过压2段(%)
	EE_uwSetGrid2OVTime, 			//	105 电网过压2段时间(10ms)
	EE_uwSetGrid3OVValue,			//	106 电网过压3段(%)
	EE_uwSetGrid3OVTime, 			//	107 电网过压3段时间(10ms)
	EE_uwSetGrid1UVValue,			//	108 电网欠压1段(%)
	EE_uwSetGrid1UVTime, 			//	109 电网欠压1段时间(10ms)
	EE_uwSetGrid2UVValue,			//	110 电网欠压2段(%)
	EE_uwSetGrid2UVTime, 			//	111 电网欠压2段时间(10ms)
	EE_uwSetGrid3UVValue,			//	112 电网欠压3段(%)
	EE_uwSetGrid3UVTime, 			//	113 电网欠压3段时间(10ms)
	EE_uwSetGrid1OFValue,			//	114 电网过频1段(0.01Hz)
	EE_uwSetGrid1OFTime, 			//	115 电网过频1段时间(10ms)
	EE_uwSetGrid2OFValue,			//	116 电网过频2段(0.01Hz)
	EE_uwSetGrid2OFTime, 			//	117 电网过频2段时间(10ms)
	EE_uwSetGrid3OFValue,			//	118 电网过频3段(0.01Hz)
	EE_uwSetGrid3OFTime, 			//	119 电网过频3段时间(10ms)
	EE_uwSetGrid1UFValue,			//	120 电网欠频1段(0.01Hz)
	EE_uwSetGrid1UFTime, 			//	121 电网欠频1段时间(10ms)
	EE_uwSetGrid2UFValue,			//	122 电网欠频2段(0.01Hz)
	EE_uwSetGrid2UFTime, 			//	123 电网欠频2段时间(10ms)
	EE_uwSetGrid3UFValue,			//	124 电网欠频3段(0.01Hz)
	EE_uwSetGrid3UFTime, 			//	125 电网欠频3段时间(10ms)
	EE_uwSetRsvd126, 				//	126 预留
	EE_uwSetRsvd127, 				//	127 预留
	EE_uwSetRsvd128, 				//	128 预留
	EE_uwSetRsvd129, 				//	129 预留
	EE_uwSetRsvd130, 				//	130 预留
	EE_uwSetRsvd131, 				//	131 预留
	EE_uwSetECO_TimeOfUse,			//	132 经济模式使能
	EE_uwSetECO_EffectiveWeek,		//	133 生效星期
	EE_uwSetECO1_GridChargeEnable,	//	134 规则1电网充电使能
	EE_uwSetECO1_GenChargeEnable,	//	135 规则1油机充电使能
	EE_uwSetECO1_StartTime,			//	136 规则1起始时间
	EE_uwSetECO1_StopTime,			//	137 规则1结束时间
	EE_uwSetECO1_Volt,				//	138 规则1目标电压
	EE_uwSetECO1_SOC,				//	139 规则1目标SOC（BMS连接采用）
	EE_uwSetECO1_Power,				//	140 规则1放电功率
	EE_uwSetECO1_WorkModeSet,		//	141 规则1工作模式设定
	EE_uwSetECO2_GridChargeEnable,	//	142 规则2电网充电使能
	EE_uwSetECO2_GenChargeEnable,	//	143 规则2油机充电使能
	EE_uwSetECO2_StartTime,			//	144 规则2起始时间
	EE_uwSetECO2_StopTime,			//	145 规则2结束时间
	EE_uwSetECO2_Volt,				//	146 规则2目标电压
	EE_uwSetECO2_SOC,				//	147 规则2目标SOC（BMS连接采用）
	EE_uwSetECO2_Power,				//	148 规则2放电功率
	EE_uwSetECO2_WorkModeSet,		//	149 规则2工作模式设定
	EE_uwSetECO3_GridChargeEnable,	//	150 规则3电网充电使能
	EE_uwSetECO3_GenChargeEnable,	//	151 规则3油机充电使能
	EE_uwSetECO3_StartTime,			//	152 规则3起始时间
	EE_uwSetECO3_StopTime,			//	153 规则3结束时间
	EE_uwSetECO3_Volt,				//	154 规则3目标电压
	EE_uwSetECO3_SOC,				//	155 规则3目标SOC（BMS连接采用）
	EE_uwSetECO3_Power,				//	156 规则3放电功率
	EE_uwSetECO3_WorkModeSet,		//	157 规则3工作模式设定
	EE_uwSetECO4_GridChargeEnable,	//	158 规则4电网充电使能
	EE_uwSetECO4_GenChargeEnable,	//	159 规则4油机充电使能
	EE_uwSetECO4_StartTime,			//	160 规则4起始时间
	EE_uwSetECO4_StopTime,			//	161 规则4结束时间
	EE_uwSetECO4_Volt,				//	162 规则4目标电压
	EE_uwSetECO4_SOC,				//	163 规则4目标SOC（BMS连接采用）
	EE_uwSetECO4_Power,				//	164 规则4放电功率
	EE_uwSetECO4_WorkModeSet,		//	165 规则4工作模式设定
	EE_uwSetECO5_GridChargeEnable,	//	166 规则5电网充电使能
	EE_uwSetECO5_GenChargeEnable,	//	167 规则5油机充电使能
	EE_uwSetECO5_StartTime,			//	168 规则5起始时间
	EE_uwSetECO5_StopTime,			//	169 规则5结束时间
	EE_uwSetECO5_Volt,				//	170 规则5目标电压
	EE_uwSetECO5_SOC,				//	171 规则5目标SOC（BMS连接采用）
	EE_uwSetECO5_Power,				//	172 规则5放电功率
	EE_uwSetECO5_WorkModeSet,		//	173 规则5工作模式设定
	EE_uwSetECO6_GridChargeEnable,	//	174 规则6电网充电使能
	EE_uwSetECO6_GenChargeEnable,	//	175 规则6油机充电使能
	EE_uwSetECO6_StartTime,			//	176 规则6起始时间
	EE_uwSetECO6_StopTime,			//	177 规则6结束时间
	EE_uwSetECO6_Volt,				//	178 规则6目标电压
	EE_uwSetECO6_SOC,				//	179 规则6目标SOC（BMS连接采用）
	EE_uwSetECO6_Power,				//	180 规则6放电功率
	EE_uwSetECO6_WorkModeSet,		//	181 规则6工作模式设定
	EE_uwSetRsvd182, 				//	182 预留
	EE_uwSetRsvd183, 				//	183 预留
	EE_uwFlag1,						//	184 EEPROM标志
	EE_uwEECheckCRC1,				//	185 CRC校验
	
	//EEPROM2
	EE_uwEEPV1VoltAdj,				//	186 PV1电压校准系数
	EE_uwEEPV1VoltBias,				//	187 PV1电压校准偏置
	EE_uwEEPV2VoltAdj,				//	188 PV2电压校准系数
	EE_uwEEPV2VoltBias,				//	189 PV2电压校准偏置
	EE_uwEEPV1CurrAdj,				//	190 PV1电流校准系数
	EE_uwEEPV1CurrBias,				//	191 PV1电流校准偏置
	EE_uwEEPV2CurrAdj,				//	192 PV2电流校准系数
	EE_uwEEPV2CurrBias,				//	193 PV2电流校准偏置
	EE_uwEEBatVoltAdj,				//	194 电池电压校准系数
	EE_uwEEBatVoltBias,				//	195 电池电压校准偏置
	EE_uwEEBatCurrAdj,				//	196 电池电流校准系数
	EE_uwEEBatCurrBias,				//	197 电池电流校准偏置
	EE_uwEEBUSVoltAdj,				//	198 Bus电压校准系数
	EE_uwEEBUSVoltBias,				//	199 Bus电压校准偏置
	EE_uwEEBUSCurrAdj,				//	200 Bus电流校准系数
	EE_uwEEBUSCurrBias,				//	201 Bus电流校准偏置
	EE_uwEEInvVoltAdj,				//	202 逆变电压校准系数
	EE_uwEEInvVoltBias,				//	203 逆变电压校准偏置
	EE_uwEEInvCurrAdj,				//	204 逆变电流校准系数
	EE_uwEEInvCurrBias,				//	205 逆变电流校准偏置
	EE_uwEEGridVoltAdj,				//	206 电网电压校准系数
	EE_uwEEGridVoltBias, 			//	207 电网电压校准偏置
	EE_uwEEGridCurrAdj,				//	208 电网电流校准系数
	EE_uwEEGridCurrBias, 			//	209 电网电流校准偏置
	EE_uwEEOPVoltAdj,				//	210 输出电压校准系数
	EE_uwEEOpVoltBias,				//	211 输出电压校准偏置
	EE_uwEEOPCurrAdj,				//	212 输出电流校准系数
	EE_uwEEOpCurrBias,				//	213 输出电流校准偏置
	EE_uwEEDischargeEneyCoeffH,		//	214 放电量校准高位
	EE_uwEEDischargeEneyCoeffL,		//	215 放电量校准低位
	EE_uwEEchargeEneyCoeffH, 		//	216 充电量校准高位
	EE_uwEEchargeEneyCoeffL, 		//	217 充电量校准低位
	EE_uwSetRsvd218, 				//	218 预留
	EE_uwSetRsvd219, 				//	219 预留
	EE_uwSetRsvd220, 				//	220 预留
	EE_uwSetRsvd221, 				//	221 预留
	EE_uwSetRsvd222, 				//	222 预留
	EE_uwSetRsvd223, 				//	223 预留
	EE_uwSetRsvd224, 				//	224 预留
	EE_uwSetRsvd225, 				//	225 预留
	EE_uwSetRsvd226, 				//	226 预留
	EE_uwSetRsvd227, 				//	227 预留
	EE_uwSetRsvd228, 				//	228 预留
	EE_uwSetRsvd229, 				//	229 预留
	EE_uwSetRsvd230, 				//	230 预留
	EE_uwSetRsvd231, 				//	231 预留
	EE_uwSetRsvd232, 				//	232 预留
	EE_uwSetRsvd233, 				//	233 预留
	EE_uwFlag2,						//	234 EEPROM标志
	EE_uwEECheckCRC2,				//	235 CRC校验

	//EEPROM3
	EE_uwATE_SN1,					//	236 机器序列号1
	EE_uwATE_SN2,					//	237 机器序列号2
	EE_uwATE_SN3,					//	238 机器序列号3
	EE_uwATE_SN4,					//	239 机器序列号4
	EE_uwATE_SN5,					//	240 机器序列号5
	EE_uwATE_SNLen,					//	241 机器序列号长度
	EE_uwATE_DispHwVer,				//	242 ATE写显示板版本号
	EE_uwATE_CtrlHwVer,				//	243 ATE写控制板版本号
	EE_uwATE_PowerHwVer,			//	244 ATE写功率板版本号
	EE_uwATE_UpdateFW,				//	245 升级固件
	EE_uwATE_ResetSystem,			//	246 复位重启
	EE_uwATE_EEDefault,				//	247 EE恢复默认值
	EE_uwATE_AgingMode,				//	248 老化模式
	EE_uwATE_RemoteOnOff,			//	249 远程控制开关
	EE_uwATE_EEFactory,				//	250 EE恢复出厂设置
	EE_uwATE_AgingBattVolt,			//	251 老化电池启动电压
	EE_uwATE_AgingBattCurr,			//	252 老化电池放电电流
	EE_uwATE_AgingPVPower,			//	253 老化最大PV功率
	EE_uwATE_AgingInvPower,			//	254 老化最大逆变功率
	EE_uwATE_MPPTVoltCntl,			//	255 MPPT电压点控制
	EE_uwATE_E_totalClr, 			//	256 发电量发电时间清零设置
	EE_uwATE_SafetyCode, 			//	257 安规设置
	EE_uwATE_ISOsetting,			//	258 绝缘阻抗设置
	EE_uwATE_EleMeterProc,			//	259 电表协议选择
	EE_uwATE_ExCommBps,				//	260 Wifi通讯地址和波特率
	EE_uwATE_EleMeterBps_Parity, 	//	261 与电表通讯波特率和校验位
	EE_uwATE_EleMeterAddr,			//	262 与电表通讯地址
	EE_uwATE_EleMeterWREn,			//	263 电表使能写，禁止读
	EE_uwATE_EleMeterDataRegAddr,	//	264 电表Modbus地址
	EE_uwATE_EleMeterData,			//	265 电表数据
	EE_uwATE_485CommBps, 			//	266 485通讯地址和波特率
	EE_uwMenuRtnDftPageEn,			//	267 菜单回退默认界面使能位
	EE_uwSetLCDBacklight,			//	268 LCD背光
	EE_uwSetBuzzerBeep,				//	269 蜂鸣器
	EE_uwSetBmsBagAddr,				//	270 电池包地址
	EE_uwSetClearEventLog,			//	271 清除事件记录
	EE_uwSetEventLogFunc,			//	272 事件记录功能
	EE_uwSetFaultLogFunc,			//	273 故障记录功能
	EE_uwSetLogType, 				//	274 Log查询类型
	EE_uwSetLogIndex,				//	275 Log索引
	EE_uwFlag3,						//	276 EEPROM标志
	EE_uwEECheckCRC3,				//	277 CRC校验

	EE_wAddrEnd,
	EE_wLen = EE_wAddrEnd - EE_uwAddrStart
};


enum ATE_DATA_ID
{
	ATE_AddrStart = 0,
	eATEComFactoryReset = ATE_AddrStart,// 0	恢复出厂值
	eATEComFaultClear,			// 1	故障清除重启
	eATEComRemoteOff,			// 2	远程关机
	eATEComCodeUpdata,			// 3	程序升级
	eATEComYearMonth,			// 4	时间设置：年-月
	eATEComDayHour,				// 5	时间设置：日-时
	eATEComMinuteSecond,		// 6	时间设置：分-秒
	eATEComWeek,				// 7	时间设置：星期
	eATEComGenaInqury_YearMonth,// 8	发电量查询设定：年-月
	eATEComGenaInqury_Day,		// 9	发电量查询设定：天
	eATEComGenaRecordClear,		// 10	清除发电量记录
	eATEComEPOEnable,			// 11	急停使能
	eATEComQuickSettings,		// 12	模式快速设定
	eATEComInvChgWattSoftStartRate,	// 13	市电充电功率软起速率
	eATEComRsvd14,				// 14	预留
	eATEComRsvd15,				// 15	预留
	eATEComRsvd16,				// 16	预留
	eATEComRsvd17,				// 17	预留
	eATEComRsvd18,				// 18	预留
	eATEComRsvd19,				// 19	预留
	eATEComRsvd20,				// 20	预留
	eATEComRsvd21,				// 21	预留
	eATEComBatteyAddr,			// 22	电池包地址(GD设置)
	eATEComBattey2Addr,			// 23	电池包地址2(GD设置)
	eATEComRsvd24,				// 24	预留
	eATEComRsvd25,				// 25	预留
	eATEComRsvd26,				// 26	预留
	eATEComRsvd27,				// 27	预留
	eATEComRsvd28,				// 28	预留
	eATEComRsvd29,				// 29	预留
	eATEComRsvd30,				// 30	预留
	eATEComRsvd31,				// 31	预留
	eATEComRsvd32,				// 32	预留
	eATEPV1VoltAdj0,			// 33	PV1电压校准阶段0
	eATEPV1VoltAdj1,			// 34	PV1电压校准阶段1
	eATEPV1VoltAdj2,			// 35	PV1电压校准阶段2
	eATEPV1VoltAdj,				// 36	PV1电压单点校准
	eATEComRsvd37,				// 37	预留
	eATEComRsvd38,				// 38	预留
	eATEComRsvd39,				// 39	预留
	eATEComRsvd40,				// 40	预留
	eATEPV1BatCurrAdj0,			// 41	PV1电流校准阶段0
	eATEPV1BatCurrAdj1,			// 42	PV1电流校准阶段1
	eATEPV1BatCurrAdj2,			// 43	PV1电流校准阶段2
	eATEPV1BatCurrAdj,				// 44	PV1电流单点校准
	eATEComRsvd45,				// 45	预留
	eATEComRsvd46,				// 46	预留
	eATEComRsvd47,				// 47	预留
	eATEComRsvd48,				// 48	预留
	eATEBatVoltAdj0,			// 49	电池电压校准阶段0
	eATEBatVoltAdj1,			// 50	电池电压校准阶段1
	eATEBatVoltAdj2,			// 51	电池电压校准阶段2
	eATEBatVoltAdj,				// 52	电池电压单点校准
	eATEBatCurrAdj0,			// 53	电池电流校准阶段0
	eATEBatCurrAdj1,			// 54	电池电流校准阶段1
	eATEBatCurrAdj2,			// 55	电池电流校准阶段2
	eATEBatCurrAdj,				// 56	电池电流单点校准
	eATEGrid_Volt0,				// 57	电网电压校准阶段0
	eATEGrid_Volt1,				// 58	电网电压校准阶段1
	eATEGrid_Volt,				// 59	电网电压校准阶段
	eATEComRsvd60,				// 60	预留
	eATEComRsvd61,				// 61	预留
	eATEComRsvd62,				// 62	预留
	eATEINV_Volt0,				// 63	逆变电压校准阶段0
	eATEINV_Volt1,				// 64	逆变电压校准阶段1
	eATEINV_Volt,				// 65	逆变电压校准阶段
	eATEINV_Curr0,				// 66	逆变电流校准阶段0
	eATEINV_Curr1,				// 67	逆变电流校准阶段1
	eATEINV_Curr,				// 68	逆变电流校准阶段
	eATELoad_Curr0,				// 69	负载电流校准阶段0
	eATELoad_Curr1,				// 70	负载电流校准阶段1
	eATELoad_curr,				// 71	负载电流校准阶段
	eATEOut_Volt0,				// 72	输出电压校准阶段0
	eATEOut_Volt1,				// 73	输出电压校准阶段1
	eATEOut_Volt,				// 74	输出电压校准阶段
	eATEPos_Bus_Volt0,			// 75	BUS电压校准阶段0
	eATEPos_Bus_Volt1,			// 76	BUS电压校准阶段1
	eATEPos_Bus_Volt,			// 77	BUS电压校准阶段
	eATEPos_Bus_Curr0,			// 78	BUS电流校准阶段0
	eATEPos_Bus_Curr1,			// 79	BUS电流校准阶段1
	eATEPos_Bus_Curr,			// 80	BUS电压校准阶段
	eATEComRsvd81,				// 81	预留
	eATEComRsvd82,				// 82	预留
	eATEComRsvd83,				// 83	预留
	eATEComRsvd84,				// 84	预留
	eATEComRsvd85,				// 85	预留

	ATE_AddrEnd,			
	ATE_Len = ATE_AddrEnd - ATE_AddrStart

};

enum WIFI_DATA_ID
{
	WifiAddrStart = 0,
	uwIotType = WifiAddrStart,			// 0X5100	区分4G/WiFi
	uwIotTersion,		// 0X5101	iot 版本号
	uwIotIpAddressH,	// 0X5102	iot 设备的IP地址：如0xC0A86401=192.168.100.1
	uwIotIpAddressL,	// 0X5103	
	uwIotSimSn1,		// 0X5104	带有英文字符的20个长度:如：ICCID: 898604B3192270310904
	uwIotSimSn2,
	uwIotSimSn3,
	uwIotSimSn4,
	uwIotSimSn5,
	uwIotSimSn6,
	uwIotSimSn7,
	uwIotSimSn8,
	uwIotSimSn9,
	uwIotSimSn10,
	uwIotSimSn11,
	uwIotSimSn12,
	uwIotSimSn13,
	uwIotSimSn14,
	uwIotSimSn15,
	uwIotSimSn16,
	uwIotState,			// 0X5114	iot 设备的状态：
						// 			0：iot 设备没有与MCU 建立通信
						// 			1：连接路由器错误，有配置路由器
						// 			2：连接上路由器
						// 			3：连接上服务器
						// 			4：正在配置连接路由器或基站
						// 			5：正在升级IOT 设备程序
	
	uwIotRSSI,			// 0X5115	4G/WiFi的信号强度

	uwBleConn,			// 0X5116	蓝牙设备连接数
	uwReserved2,		// 0X5117
	uwReserved3,		// 0X5118
	uwReserved4,		// 0X5119
	uwReserved5,		// 0X511A
	uwReserved6,		// 0X511B
	uwReserved7,		// 0X511C
	uwReserved8,		// 0X511D
	uwReserved9,		// 0X511E

	Wifi_AddrEnd,
	Wifi_Len = Wifi_AddrEnd - WifiAddrStart
};


enum DBG_CMD_ID
{
	DBG_AddrStart = 0,	//0x00
	DBG_XXXXXXX00 = DBG_AddrStart,		
	DBG_XXXXXXX01,		//0x01
	DBG_XXXXXXX02,		//0x02
	DBG_XXXXXXX03,		//0x03
	DBG_XXXXXXX04,		//0x04
	DBG_XXXXXXX05,		//0x05
	DBG_XXXXXXX06,		//0x06
	DBG_XXXXXXX07,		//0x07
	DBG_XXXXXXX08,		//0x08
	DBG_XXXXXXX09,		//0x09
	DBG_XXXXXXX10,		//0x10
	DBG_XXXXXXX11,		//0x11
	DBG_XXXXXXX12,		//0x12
	DBG_XXXXXXX13,		//0x13
	DBG_XXXXXXX14,		//0x14
	DBG_XXXXXXX15,		//0x15
	DBG_XXXXXXX16,		//0x16
	DBG_XXXXXXX17,		//0x17
	DBG_XXXXXXX18,		//0x18
	DBG_XXXXXXX19,		//0x19
	DBG_XXXXXXX20,		//0x20
	DBG_XXXXXXX21,		//0x21
	DBG_XXXXXXX22,		//0x22
	DBG_XXXXXXX23,		//0x23
	DBG_XXXXXXX24,		//0x24
	DBG_XXXXXXX25,		//0x25
	DBG_XXXXXXX26,		//0x26
	DBG_XXXXXXX27,		//0x27
	DBG_XXXXXXX28,		//0x28
	DBG_XXXXXXX29,		//0x29
	DBG_XXXXXXX30,		//0x30
	DBG_XXXXXXX31,		//0x31
	DBG_XXXXXXX32,		//0x32
	DBG_XXXXXXX33,		//0x33
	DBG_XXXXXXX34,		//0x34
	DBG_XXXXXXX35,		//0x35
	DBG_XXXXXXX36,		//0x36
	DBG_XXXXXXX37,		//0x37
	DBG_XXXXXXX38,		//0x38
	DBG_XXXXXXX39,		//0x39
	DBG_XXXXXXX40,		//0x40
	DBG_XXXXXXX41,		//0x41
	DBG_XXXXXXX42,		//0x42
	DBG_XXXXXXX43,		//0x43
	DBG_XXXXXXX44,		//0x44
	DBG_XXXXXXX45,		//0x45
	DBG_XXXXXXX46,		//0x46
	DBG_XXXXXXX47,		//0x47
	DBG_XXXXXXX48,		//0x48
	DBG_XXXXXXX49,		//0x49
	DBG_XXXXXXX50,		//0x50
	DBG_XXXXXXX51,		//0x51
	DBG_XXXXXXX52,		//0x52
	DBG_XXXXXXX53,		//0x53
	DBG_XXXXXXX54,		//0x54
	DBG_XXXXXXX55,		//0x55
	DBG_XXXXXXX56,		//0x56
	DBG_XXXXXXX57,		//0x57
	DBG_XXXXXXX58,		//0x58
	DBG_XXXXXXX59,		//0x59
	DBG_XXXXXXX60,		//0x60
	DBG_XXXXXXX61,		//0x61
	DBG_XXXXXXX62,		//0x62
	DBG_XXXXXXX63,		//0x63
	DBG_XXXXXXX64,		//0x64
	DBG_XXXXXXX65,		//0x65
	DBG_XXXXXXX66,		//0x66
	DBG_XXXXXXX67,		//0x67
	DBG_XXXXXXX68,		//0x68
	DBG_XXXXXXX69,		//0x69
	DBG_XXXXXXX70,		//0x70
	DBG_XXXXXXX71,		//0x71
	DBG_XXXXXXX72,		//0x72
	DBG_XXXXXXX73,		//0x73
	DBG_XXXXXXX74,		//0x74
	DBG_XXXXXXX75,		//0x75
	DBG_XXXXXXX76,		//0x76
	DBG_XXXXXXX77,		//0x77
	DBG_XXXXXXX78,		//0x78
	DBG_XXXXXXX79,		//0x79
	DBG_XXXXXXX80,		//0x80
	DBG_XXXXXXX81,		//0x81
	DBG_XXXXXXX82,		//0x82
	DBG_XXXXXXX83,		//0x83
	DBG_XXXXXXX84,		//0x84
	DBG_XXXXXXX85,		//0x85
	DBG_XXXXXXX86,		//0x86
	DBG_XXXXXXX87,		//0x87
	DBG_XXXXXXX88,		//0x88
	DBG_XXXXXXX89,		//0x89
	DBG_XXXXXXX90,		//0x90
	DBG_XXXXXXX91,		//0x91
	DBG_XXXXXXX92,		//0x92
	DBG_XXXXXXX93,		//0x93
	DBG_XXXXXXX94,		//0x94
	DBG_XXXXXXX95,		//0x95
	DBG_XXXXXXX96,		//0x96
	DBG_XXXXXXX97,		//0x97
	DBG_XXXXXXX98,		//0x98
	DBG_XXXXXXX99,		//0x99
	DBG_XXXXXXX100,		//0x100
	DBG_XXXXXXX101,		//0x101
	DBG_XXXXXXX102,		//0x102
	DBG_XXXXXXX103,		//0x103
	DBG_XXXXXXX104,		//0x104
	DBG_XXXXXXX105,		//0x105
	DBG_XXXXXXX106,		//0x106
	DBG_XXXXXXX107,		//0x107
	DBG_XXXXXXX108,		//0x108
	DBG_XXXXXXX109,		//0x109
	DBG_XXXXXXX110,		//0x110
	DBG_XXXXXXX111,		//0x111
	DBG_XXXXXXX112,		//0x112
	DBG_XXXXXXX113,		//0x113
	DBG_XXXXXXX114,		//0x114
	DBG_XXXXXXX115,		//0x115
	DBG_XXXXXXX116,		//0x116
	DBG_XXXXXXX117,		//0x117
	DBG_XXXXXXX118,		//0x118
	DBG_XXXXXXX119,		//0x119
	
	DBG_AddrEnd,
	DBG_Len = DBG_AddrEnd - DBG_AddrStart
};

enum EMS_DATA_ID
{
	EMS_AddrStart = 0,
		
	EMS_ChargeVoltageLimit = EMS_AddrStart,
	EMS_DischargeVoltageLimit,
	EMS_ChargeCurrentLimit,
	EMS_DischargeCurrentLimit,
	EMS_StatusHigh,
	EMS_StatusLow,
	EMS_FaultFlagHigh,
	EMS_FaultFlagLow,
	EMS_AlarmFlagHigh,
	EMS_AlarmFlagLow,
	EMS_NoticeFlagHigh,
	EMS_NoticeFlagLow,
	EMS_TotalCurrent,
	EMS_TotalVoltage,
	EMS_TotalVoltageComp,
	EMS_Reservd02,
	EMS_TotalSOC,
	EMS_TotalSOH,
	EMS_TotalCapacityHigh,
	EMS_TotalCapacityLow,
	EMS_ParallelNumber,
	EMS_ParallelStatus,
	EMS_SerialNumber,
	EMS_SerialStatus,
	EMS_MaximumCellVoltageNo,
	EMS_MaximumCellVoltage,
	EMS_MinimumCellVoltageNo,
	EMS_MinimumCellVoltage,
	EMS_MaximumCellTemperatureNo,
	EMS_MaximumCellTemperature,
	EMS_MinimumCellTemperatureNo,
	EMS_MinimumCellTemperature,
	EMS_AddrEnd,
	EMS_Len = EMS_AddrEnd - EMS_AddrStart
};


enum BMS_INFO_DATA_ID
{
	BMS_INFO_AddrStart = 0,

	BMS_INFO_BmsType = EMS_AddrStart,
	BMS_INFO_BmsSubType,
	BMS_INFO_BmsCommProVer,
	BMS_INFO_BmsCommInfo,
 	BMS_INFO_BmsSN1,
	BMS_INFO_BmsSN2,
	BMS_INFO_BmsSN3,
	BMS_INFO_BmsSN4,
	BMS_INFO_BmsSN5,
 	BMS_INFO_BmsSNLen,
	BMS_INFO_BmsDispSwVer,
	BMS_INFO_BmsMCU1SwVer,
 	BMS_INFO_BmsMCU2SwVer,
	BMS_INFO_BmsDispHwVer,
	BMS_INFO_BmsCtrlHwVer,
	BMS_INFO_BmsPowerHwVer,
	BMS_INFO_AddrEnd,
	BMS_INFO_Len = BMS_INFO_AddrEnd - BMS_INFO_AddrStart
};

enum BMS_DATA_ID
{
	BMS_AddrStart = 0,
		
	BMS_ChargeVoltageLimit = BMS_AddrStart,
	BMS_DischargeVoltageLimit,
	BMS_ChargeCurrentLimit,
	BMS_DischargeCurrentLimit,
	BMS_StatusHigh,
	BMS_StatusLow,
	BMS_FaultFlagHigh,
	BMS_FaultFlagLow,
	BMS_AlarmFlagHigh,
	BMS_AlarmFlagLow,
	BMS_NoticeFlagHigh,
	BMS_NoticeFlagLow,
	BMS_TotalCurrent,
	BMS_TotalVoltage,
	BMS_TotalVoltageComp,
	BMS_Reservd02,
	BMS_TotalSOC,
	BMS_TotalSOH,
	BMS_TotalCapacityHigh,
	BMS_TotalCapacityLow,
	BMS_ParallelNumber,
	BMS_ParallelStatus,
	BMS_SerialNumber,
	BMS_SerialStatus,
	BMS_MaximumCellVoltageNo,
	BMS_MaximumCellVoltage,
	BMS_MinimumCellVoltageNo,
	BMS_MinimumCellVoltage,
	BMS_MaximumCellTemperatureNo,
	BMS_MaximumCellTemperature,
	BMS_MinimumCellTemperatureNo,
	BMS_MinimumCellTemperature,
	BMS_AddrEnd,
	BMS_Len = BMS_AddrEnd - BMS_AddrStart
};

/********************************************************************************
* Constants																		*
********************************************************************************/
INT8U bEmsBmsConnenctFlag = false;
INT16U wEmsBmsDisconnectCnt = 0;
INT16U wBmsTxCmd = 0;		// 1:EMS 数据 2：BMS数据  3：Info数据
INT16U g_uwBMSAddr = 0;		// wifi查询的当前BMS地址
INT16U g_uwBMSFlag = 0;		// BMS在线状态

/********************************************************************************
* External variables															*
********************************************************************************/

extern union INVERTER_REALTIME_DATA_TABLE strInverterRealtimeData;		// DSP实时数据

/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/


/********************************************************************************
* Output variables																*
********************************************************************************/


/********************************************************************************
* Internal variables															*
********************************************************************************/


/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sModBusRdProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen);
void	sModBusWrProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen);
void	sModBusSwapProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen);
void	sBuildRdFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT16U (*RdFunc)(INT16U));
void	sBuildWrFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U (*WrFunc)(INT16U, INT16U));
INT8U	sBuildSwapWrFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U (*WrFunc)(INT16U, INT16U));
void	sBuildFaultFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U ErrCode);
INT8U	sRxModBusBMSData(INT8U *RxBuff, INT8U sciid, INT16U (*WrFunc)(INT16U, INT16U), INT16U (*WrFunc2)(INT16U, INT16U),INT16U (*WrFunc3)(INT16U, INT16U));
void	sBuildUpgradeFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid);
INT16U	swInfoDataRead(INT16U RdAddr);
INT16U	swRealTimeDataRead(INT16U RdAddr);
INT16U	swWifiIotDataRead(INT16U RdAddr);
INT16U	swEESettingRead(INT16U RdAddr);
INT8U	swEESettingWrite(INT16U WrAddr, INT16U WrData);
INT8U	swATESettingWrite(INT16U WrAddr, INT16U WrData);
INT8U	swWifiIotWrite(INT16U WrAddr, INT16U WrData);
INT16U	swEMSDataWrite(INT16U WrAddr, INT16U WrData);
INT16U	swBmsInfoDataWrite(INT16U WrAddr, INT16U WrData);
INT16U	swBmsDataWrite(INT16U WrAddr, INT16U WrData);
INT16U	swSwapDataRead(INT16U RdAddr);
INT8U	swSwapDataWrite(INT16U WrAddr, INT16U WrData);
INT16U	swTestCmdRead(INT16U RdAddr);
INT8U	swTestCmdWrite(INT16U WrAddr, INT16U WrData);
INT8U	sGetCellVoltDefault(INT8U bNo);
void	sbBattVoltCopyToCell(void);
void 	sBmsInfoDataFramePolling(INT8U sciid,INT8U BmsAddr);
void 	sBmsFramePolling(INT8U sciid,INT8U BmsAddr);
void 	sEmsDataFramePolling(INT8U sciid);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sModBusParsing(INT8U sciid)
{
	INT8U	*RxBuff;
	INT8U	*TxBuff;
	INT8U	packet_len;
	INT16U	temp;
	INT8U	bSciIdTemp;
	
	bSciIdTemp = sciid;
	RxBuff = pbGetSciRxBuff(sciid);
	TxBuff = pbGetSciTxBuff(sciid);
	
	// 0X01：DSP ID
	// 0X02：MPPT ID
	// 0X1F: 广播
//	if((RxBuff[cMODBUS_ADDR] != 0x01) && (RxBuff[cMODBUS_ADDR] != cMODBUS_ADDR_BACKUP)\
//		&& (RxBuff[cMODBUS_ADDR] != 0x02) && (RxBuff[cMODBUS_ADDR] != 0x03)\
//		&& (RxBuff[cMODBUS_ADDR] != cMODBUS_ADDR_HOST))
//	{
//		return;
//	}
//	else if(RxBuff[cMODBUS_ADDR] == 0x02)
//	{
//		if(bSciIdTemp == c485_SCI)
//		{
//			swSetPassthrough(SCI_PASSTHROUGH_RS485_MPPT);
//			return;
//		}
//		else if(bSciIdTemp == c232_SCI)
//		{
//			swSetPassthrough(SCI_PASSTHROUGH_RS232_MPPT);
//			return;
//		}
//	}
//	else if(RxBuff[cMODBUS_ADDR] == 0x03)
//	{
//		if(bSciIdTemp == c232_SCI)
//		{
//			swSetPassthrough(SCI_PASSTHROUGH_RS485_RS232);
//			return;
//		}
//	}
//	else
//	{
//		swSetPassthrough(SCI_PASSTHROUGH_NULL);
//	}

	//GetEMSData Parsing
	if(sciid == c485_SCI)
	{	
		bEmsBmsConnenctFlag = sRxModBusBMSData(RxBuff,sciid,swEMSDataWrite,swBmsInfoDataWrite,swBmsDataWrite);
		if(bEmsBmsConnenctFlag == true)
		{
			wEmsBmsDisconnectCnt = 0;
			return;
		}
	}
	
	switch(RxBuff[cMODBUS_CMD])
	{
		case cREAD_CMD:
			packet_len = 8;
			sModBusRdProc(RxBuff, TxBuff, bSciIdTemp, 8);
		break;
		case cWRITE_CMD:
			packet_len = 8;
			sModBusWrProc(RxBuff, TxBuff, bSciIdTemp, 8);
		break;
		case cWRITE_CMD_MULTI:
			temp = (((INT16U)RxBuff[cMODBUS_REG_NUM_H] << 8) + RxBuff[cMODBUS_REG_NUM_L]) << 1;
			temp += 9;
			if(temp > cSCI_RX_LEN)
			{
				packet_len = cSCI_RX_LEN;
			}
			else
			{
				packet_len = (INT8U)temp;
			}
			sModBusWrProc(RxBuff, TxBuff, bSciIdTemp, packet_len);
		break;
		case cSYNC_CMD:
			temp = RxBuff[cMODBUS_SWAP_WR_NUM];
			temp += 13;
			if(temp > cSCI_RX_LEN)
			{
				packet_len = cSCI_RX_LEN;
			}
			else
			{
				packet_len = (INT8U)temp;
			}
			sModBusSwapProc(RxBuff, TxBuff, bSciIdTemp, packet_len);
		break;
		default:
			packet_len = 8;
		break;
	}
}


void	sModBusRdProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen)
{
	INT16U RdAddr, RdNums, wCRC;
	
	// 
	wCRC = ((INT16U)RxBuff[RxLen - cMODBUS_CRC_H] << 8) + RxBuff[RxLen - cMODBUS_CRC_L];
	if(wCRC != swModbusCrc16(&RxBuff[cMODBUS_ADDR], (RxLen - cMODBUS_CRC_LEN)))
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_CrcErr);
		return;
	}
	
	// 
	RdAddr = ((INT16U)RxBuff[cMODBUS_REG_ADDR_H] << 8) + RxBuff[cMODBUS_REG_ADDR_L];
	RdNums = ((INT16U)RxBuff[cMODBUS_REG_NUM_H] << 8) + RxBuff[cMODBUS_REG_NUM_L];
	
	// 
	if(RdNums > cMODBUS_REG_RX_MAX_LEN)
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_UnDataValue);
		return;
	}
	
	// 完整的EEPROM数据
	if((RdAddr >= EE_REG_BASE_ADDR) && (RdAddr < (EE_REG_BASE_ADDR + EE_REG_BASE_LEN)))
    {
		if((RdAddr + RdNums) <= (EE_REG_BASE_ADDR + EE_REG_BASE_LEN))
		{
	    	sBuildRdFrame(RxBuff, TxBuff, sciid, swEESettingRead);
		}
		else
		{
	    	sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	
	// DSP 实时数据
	else if((RdAddr >= REALDATA_REG_BASE_ADDR) && (RdAddr < (REALDATA_REG_BASE_ADDR + REALDATA_REG_BASE_LEN)))
	{
		if((RdAddr + RdNums) <=  (REALDATA_REG_BASE_ADDR + REALDATA_REG_BASE_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swRealTimeDataRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	
	// DSP 系统参数
	else if((RdAddr >= INFO_REG_BASE_ADDR) && (RdAddr < (INFO_REG_BASE_ADDR + INFO_REG_LEN)))
	{
		if((RdAddr + RdNums) <= (INFO_REG_BASE_ADDR + INFO_REG_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swInfoDataRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	// WIFI IOT下发的信息
	else if((RdAddr >= WIFI_IOT_REG_BASE_ADDR) && (RdAddr < (WIFI_IOT_REG_BASE_ADDR + WIFI_IOT_REG_BASE_LEN)))
	{
		if((RdAddr + RdNums) <= (WIFI_IOT_REG_BASE_ADDR + WIFI_IOT_REG_BASE_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swWifiIotDataRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	else if((RdAddr >= DBG_CMD_BASE_ADDR) && (RdAddr < (DBG_CMD_BASE_ADDR + DBG_CMD_LEN)))
	{
		if((RdAddr + RdNums) <= (DBG_CMD_BASE_ADDR + DBG_CMD_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swTestCmdRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
#if(OSCILLOGRAPH_ENABLE==1)
	else if((RdAddr >= OSCILLOGRAPH_DATA_BASE_ADDR) && (RdAddr < (OSCILLOGRAPH_DATA_BASE_ADDR + OSCILLOGRAPH_DATA_LEN)))
	{
		if((RdAddr + RdNums) <= (OSCILLOGRAPH_DATA_BASE_ADDR + OSCILLOGRAPH_DATA_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swOscillographDataRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	else if((RdAddr >= OSCILLOGRAPH_CMD_BASE_ADDR) && (RdAddr < (OSCILLOGRAPH_CMD_BASE_ADDR + OSCILLOGRAPH_CMD_LEN)))
	{
		if((RdAddr + RdNums) <= (OSCILLOGRAPH_CMD_BASE_ADDR + OSCILLOGRAPH_CMD_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swOscillographCmdRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
#endif
	else
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_UnDataAddr);
	}
}

void	sModBusWrProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen)
{
	INT16U WrAddr, WrNums, wCRC;
	
	// 
	wCRC = ((INT16U)RxBuff[RxLen - cMODBUS_CRC_H] << 8) + RxBuff[RxLen - cMODBUS_CRC_L];
	if(wCRC != swModbusCrc16(&RxBuff[cMODBUS_ADDR], (RxLen - cMODBUS_CRC_LEN)))
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_CrcErr);
		return;
	}
	
	// 
	WrAddr = ((INT16U)RxBuff[cMODBUS_REG_ADDR_H] << 8) + RxBuff[cMODBUS_REG_ADDR_L];
	if(RxBuff[cMODBUS_CMD] == cWRITE_CMD)
	{
		WrNums = 1;
	}
	else
	{
		WrNums = (RxBuff[cMODBUS_REG_NUM_H] << 8) + RxBuff[cMODBUS_REG_NUM_L];
	}
	
	// 
	if(WrNums > cMODBUS_REG_TX_MAX_LEN)
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_UnDataValue);
		return;
	}

	// EEPROM 设置
	if((WrAddr >= EE_REG_BASE_ADDR + EE_uwAddrStart) && (WrAddr < (EE_REG_BASE_ADDR + EE_REG_BASE_LEN)))
	{
		if((WrAddr + WrNums) <= (EE_REG_BASE_ADDR + EE_REG_BASE_LEN))
		{
			sBuildWrFrame(RxBuff, TxBuff, sciid, swEESettingWrite);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}

	// ATE老化参数设置
	else if((WrAddr >= ATE_REG_BASE_ADDR) && (WrAddr < (ATE_REG_BASE_ADDR + ATE_REG_BASE_LEN)))
	{
		if((WrAddr + WrNums) <= (ATE_REG_BASE_ADDR + ATE_REG_BASE_LEN))
		{
			sBuildWrFrame(RxBuff, TxBuff, sciid, swATESettingWrite);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	// WIFI IOT参数设置	 for 20240726
	else if((WrAddr >= WIFI_IOT_REG_BASE_ADDR) && (WrAddr < (WIFI_IOT_REG_BASE_ADDR + WIFI_IOT_REG_BASE_LEN)))
	{
		if((WrAddr + WrNums) <= (WIFI_IOT_REG_BASE_ADDR + WIFI_IOT_REG_BASE_LEN))
		{
			sBuildWrFrame(RxBuff, TxBuff, sciid, swWifiIotWrite);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	else if((WrAddr >= DBG_CMD_BASE_ADDR) && (WrAddr < (DBG_CMD_BASE_ADDR + DBG_CMD_LEN)))
	{
		if((WrAddr + WrNums) <= (DBG_CMD_BASE_ADDR + DBG_CMD_LEN))
		{
			sBuildWrFrame(RxBuff, TxBuff, sciid, swTestCmdWrite);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
#if(OSCILLOGRAPH_ENABLE==1)
	else if((WrAddr >= OSCILLOGRAPH_CMD_BASE_ADDR) && (WrAddr < (OSCILLOGRAPH_CMD_BASE_ADDR + OSCILLOGRAPH_CMD_LEN)))
	{
		if((WrAddr + WrNums) <= (OSCILLOGRAPH_CMD_BASE_ADDR + OSCILLOGRAPH_CMD_LEN))
		{
			sBuildWrFrame(RxBuff, TxBuff, sciid, swOscillographCmdWrite);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
#endif
	else
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
	}
}

void	sModBusSwapProc(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U RxLen)
{
/*NT16U RdAddr, RdNums, wCRC;
	INT16U WrAddr, WrNums;
	INT8U  bStatus;
	
	// 
	wCRC = ((INT16U)RxBuff[RxLen - cMODBUS_CRC_H] << 8) + RxBuff[RxLen - cMODBUS_CRC_L];
	if(wCRC != swModbusCrc16(&RxBuff[cMODBUS_ADDR], (RxLen - cMODBUS_CRC_LEN)))
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_CrcErr);
		return;
	}
	
	// 
	RdAddr = ((INT16U)RxBuff[cMODBUS_SWAP_RD_ADDR_H] << 8) + RxBuff[cMODBUS_SWAP_RD_ADDR_L];
	RdNums = ((INT16U)RxBuff[cMODBUS_SWAP_RD_NUM_H] << 8) + RxBuff[cMODBUS_SWAP_RD_NUM_L];
	if(RdNums > cMODBUS_SWAP_RX_MAX_LEN)
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_UnDataValue);
		return;
	}
	
	// 
	WrAddr = ((INT16U)RxBuff[cMODBUS_SWAP_WR_ADDR_H] << 8) + RxBuff[cMODBUS_SWAP_WR_ADDR_L];
	WrNums = ((INT16U)RxBuff[cMODBUS_SWAP_WR_NUM_H] << 8) + RxBuff[cMODBUS_SWAP_WR_NUM_L];
	if(WrNums > cMODBUS_SWAP_TX_MAX_LEN)
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_UnDataValue);
		return;
	}
	
	// 
	if((WrAddr >= SWAP_WR_REG_BASE_ADDR) && (WrAddr < (SWAP_WR_REG_BASE_ADDR + SWAP_WR_REG_BASE_LEN)))
	{
		if((WrAddr + WrNums) <=  (SWAP_WR_REG_BASE_ADDR + SWAP_WR_REG_BASE_LEN))
		{
			bStatus = sBuildSwapWrFrame(RxBuff, TxBuff, sciid, swSwapDataWrite);
			if(bStatus != 0)
			{
				sBuildFaultFrame(RxBuff, TxBuff, sciid, bStatus);
				return;
			}
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
			return;
		}
	}
	else
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		return;
	}
	
	if((RdAddr >= SWAP_RD_REG_BASE_ADDR) && (RdAddr < (SWAP_RD_REG_BASE_ADDR + SWAP_RD_REG_BASE_LEN)))
	{
		if((RdAddr + RdNums) <=  (SWAP_RD_REG_BASE_ADDR + SWAP_RD_REG_BASE_LEN))
		{
			sBuildRdFrame(RxBuff, TxBuff, sciid, swSwapDataRead);
		}
		else
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
		}
	}
	else
	{
		sBuildFaultFrame(RxBuff, TxBuff, sciid, cErr_ParUnValid);
	}*/
}

void	sBuildRdFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT16U (*RdFunc)(INT16U))
{
	INT16U RdAddr, RdNums, RdData, wCRC;
	INT8U i, TxLen;
	
	RdAddr = ((INT16U)RxBuff[cMODBUS_REG_ADDR_H] << 8) + RxBuff[cMODBUS_REG_ADDR_L];
	RdNums = ((INT16U)RxBuff[cMODBUS_REG_NUM_H] << 8) + RxBuff[cMODBUS_REG_NUM_L];
	
	TxBuff[cMODBUS_ADDR] = RxBuff[cMODBUS_ADDR];
	TxBuff[cMODBUS_CMD] = RxBuff[cMODBUS_CMD];
	TxBuff[2] = (RdNums << 1) & 0x00FF;
	TxLen = 3;
	
	for(i = 0; i < RdNums; i++)
	{
		RdData = (*RdFunc)(RdAddr);
		RdAddr++;
		
		TxBuff[TxLen++] = RdData >> 8;
		TxBuff[TxLen++] = RdData & 0x00FF;
	}
	
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], TxLen);
	TxBuff[TxLen++] = wCRC >> 8;
	TxBuff[TxLen++] = wCRC & 0x00FF;
	
	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid, TxBuff, TxLen);
		sSetCommConnected(sciid, true);
		//sRstCommLossCount();
	}
}

void	sBuildWrFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U (*WrFunc)(INT16U, INT16U))
{
	INT8U *pBuff = NULL;
	INT16U WrAddr, WrNums, WrData, wCRC;
	INT8U i, Status;
	
	WrAddr = ((INT16U)RxBuff[cMODBUS_REG_ADDR_H] << 8) + RxBuff[cMODBUS_REG_ADDR_L];
	if(RxBuff[cMODBUS_CMD] == cWRITE_CMD)
	{
		WrNums = 1;
		pBuff = &RxBuff[cMODBUS_WRITE_DATA_START];
	}
	else
	{
		WrNums = ((INT16U)RxBuff[cMODBUS_REG_NUM_H] << 8) + RxBuff[cMODBUS_REG_NUM_L];
		pBuff = &RxBuff[cMODBUS_MULTI_WRITE_DATA_START];
	}
	
	for(i = 0; i < WrNums; i++)
	{
		WrData = ((INT16U)pBuff[0] << 8) + pBuff[1];
		pBuff += 2;
		
		Status = (*WrFunc)(WrAddr, WrData);
		WrAddr++;
		
		if(Status != 0)
		{
			sBuildFaultFrame(RxBuff, TxBuff, sciid, Status);
			return;
		}
	}
	
	TxBuff[cMODBUS_ADDR] = RxBuff[cMODBUS_ADDR];
	TxBuff[cMODBUS_CMD] = RxBuff[cMODBUS_CMD];
	TxBuff[cMODBUS_REG_ADDR_H] = RxBuff[cMODBUS_REG_ADDR_H];
	TxBuff[cMODBUS_REG_ADDR_L] = RxBuff[cMODBUS_REG_ADDR_L];
	TxBuff[cMODBUS_REG_NUM_H] = RxBuff[cMODBUS_REG_NUM_H];
	TxBuff[cMODBUS_REG_NUM_L] = RxBuff[cMODBUS_REG_NUM_L];
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], 6);
	TxBuff[6] = wCRC >> 8;
	TxBuff[7] = wCRC & 0x00FF;
	
	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid, TxBuff, 8);
		sSetCommConnected(sciid, true);
		//sRstCommLossCount();
	}
}

void	sBuildSwapRdFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT16U (*RdFunc)(INT16U))
{
	INT16U RdAddr, RdNums, RdData, wCRC;
	INT8U i, TxLen;
	
	RdAddr = ((INT16U)RxBuff[cMODBUS_SWAP_RD_ADDR_H] << 8) + RxBuff[cMODBUS_SWAP_RD_ADDR_L];
	RdNums = ((INT16U)RxBuff[cMODBUS_SWAP_RD_NUM_H] << 8) + RxBuff[cMODBUS_SWAP_RD_NUM_L];
	
	TxBuff[cMODBUS_ADDR] = RxBuff[cMODBUS_ADDR];
	TxBuff[cMODBUS_CMD] = RxBuff[cMODBUS_CMD];
	TxBuff[2] = (RdNums << 1) & 0x00FF;
	TxLen = 3;
	
	for(i = 0; i < RdNums; i++)
	{
		RdData = (*RdFunc)(RdAddr);
		RdAddr++;
		
		TxBuff[TxLen++] = RdData >> 8;
		TxBuff[TxLen++] = RdData & 0x00FF;
	}
	
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], TxLen);
	TxBuff[TxLen++] = wCRC >> 8;
	TxBuff[TxLen++] = wCRC & 0x00FF;
	
	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid, TxBuff, TxLen);
		sSetCommConnected(sciid, true);
		//sRstCommLossCount();
	}
}

INT8U	sBuildSwapWrFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U (*WrFunc)(INT16U, INT16U))
{
	INT8U *pBuff = NULL;
	INT16U WrAddr, WrNums, WrData;
	INT8U i, Status;
	
	WrAddr = ((INT16U)RxBuff[cMODBUS_SWAP_WR_ADDR_H] << 8) + RxBuff[cMODBUS_SWAP_WR_ADDR_L];
	WrNums = ((INT16U)RxBuff[cMODBUS_SWAP_WR_NUM_H] << 8) + RxBuff[cMODBUS_SWAP_WR_NUM_L];
	pBuff = &RxBuff[cMODBUS_SWAP_ER_DATA_START];
	
	for(i = 0; i < WrNums; i++)
	{
		WrData = ((INT16U)pBuff[0] << 8) + pBuff[1];
		pBuff += 2;
		
		Status = (*WrFunc)(WrAddr, WrData);
		WrAddr++;
		
		if(Status != 0)
		{
			return Status;
		}
	}
	return 0;
}

void	sBuildFaultFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid, INT8U ErrCode)
{
	INT16U wCRC;
	
	TxBuff[cMODBUS_ADDR] = RxBuff[cMODBUS_ADDR];
	TxBuff[cMODBUS_CMD] = RxBuff[cMODBUS_CMD] + 0x80;
	TxBuff[2] = ErrCode;
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], 3);
	TxBuff[3] = wCRC >> 8;
	TxBuff[4] = wCRC & 0x00FF;
	
	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid, TxBuff, 5);
	}
}

// 查询电池包数据 50ms任务
void sBmsDataFramePolling(INT8U sciid, INT16U TimerBase)
{
	static INT16U wTxCnt = 0;
	static INT16U wEmsTxCnt = 0;
	static INT16U wInfoTxCnt = 0;
	static INT16U wBmsTxCnt = 0;
	
	if(suwGetEEBatType() != cBatType_LIB)
	{
		return;
	}

	if(++wTxCnt > TimerBase)
	{
		wTxCnt = 0;
		wEmsTxCnt++;
		wInfoTxCnt++;
		wBmsTxCnt++;
	}
//	wTxCnt++;


	if(wInfoTxCnt == 3)		//3s
	{
		wInfoTxCnt = 0;
		wBmsTxCnt = 0;
		wEmsTxCnt = 0;
		if((sbGetBMSAddr() != 0) && (uwGetBmsDataFlag() == cGET_BMSDATA_FLAG_READING))
		{
			sBmsInfoDataFramePolling(sciid,sbGetBMSAddr());
			wBmsTxCmd = 3;
		}
		else
		{
	//		wBmsTxCnt += 1;
		}
	}
	else if(wBmsTxCnt == 2)	//2S
	{
		wBmsTxCnt = 0;
		wEmsTxCnt = 0;
		if((sbGetBMSAddr() != 0) && (uwGetBmsDataFlag() == cGET_BMSDATA_FLAG_READING))
		{
			sBmsFramePolling(sciid,sbGetBMSAddr());
			wBmsTxCmd = 2;
		}
		else
		{
	//		wBmsTxCnt += 1;
		}

	}
	else if(wEmsTxCnt == 1)	//1s
	{
		//wTxCnt = 0;
		wEmsTxCnt = 0;
		sEmsDataFramePolling(sciid);
		wBmsTxCmd = 1;
	}

}


//查询电池包EMS数据
void sEmsDataFramePolling(INT8U sciid)
{
	INT16U wCRC;
	INT8U  TxLen;
	static INT8U  TxBuff[8] = {0};

	TxBuff[cMODBUS_ADDR] = cMODBUS_ADDR_HOST;	
	TxBuff[cMODBUS_CMD] = 3;
	TxBuff[cMODBUS_REG_ADDR_H] = EMS_REG_BASE_ADDR >> 8;
	TxBuff[cMODBUS_REG_ADDR_L] = EMS_REG_BASE_ADDR & 0x00FF;
	TxBuff[cMODBUS_REG_NUM_H] = 0;
	TxBuff[cMODBUS_REG_NUM_L] = 32;
	TxLen = 6;
	
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], TxLen);
	TxBuff[6] = wCRC >> 8;
	TxBuff[7] = wCRC & 0x00FF;

	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid,TxBuff, 8);
	}
}

INT8U	sRxModBusBMSData(INT8U *RxBuff, INT8U sciid, INT16U (*WrFunc)(INT16U, INT16U), INT16U (*WrFunc2)(INT16U, INT16U),INT16U (*WrFunc3)(INT16U, INT16U))
{
	INT8U *pBuff = NULL;
	INT16U WrAddr, WrNums, WrData,wCRC;
	INT8U i, Status;
	static INT16U wBmaDataReadOkFlag = 0;
	
	WrNums = RxBuff[2];
	pBuff = &RxBuff[3];

	// 
	if(RxBuff[1] != 3)
	{
		return false;
	}
	wCRC = ((INT16U)RxBuff[WrNums + 3] << 8) + RxBuff[WrNums + 4];
	if(wCRC != swModbusCrc16(&RxBuff[cMODBUS_ADDR], (WrNums + 3)) || (wCRC == 0))
	{
		return false;
	}
	
	if(wBmsTxCmd == 1)
	{
		WrAddr = EMS_REG_BASE_ADDR;
		for(i = 0; i < WrNums; i++)
		{
			WrData = ((INT16U)pBuff[0] << 8) + pBuff[1];
			pBuff += 2;
			
			Status = (*WrFunc)(WrAddr, WrData);
			WrAddr++;
			
			if(Status != 0)
			{
				return false;
			}
		}
	}
	else if(wBmsTxCmd == 3)
	{
		WrAddr = BMS_INFO_REG_BASE_ADDR;
		for(i = 0; i < WrNums; i++)
		{
			WrData = ((INT16U)pBuff[0] << 8) + pBuff[1];
			pBuff += 2;
			
			Status = (*WrFunc2)(WrAddr, WrData);
			WrAddr++;
			
			if(Status != 0)
			{
				return false;
			}
		}
		wBmaDataReadOkFlag |= 0x1;
	}
	else if(wBmsTxCmd == 2)
	{
		WrAddr = BMS_REG_BASE_ADDR;
		for(i = 0; i < WrNums; i++)
		{
			WrData = ((INT16U)pBuff[0] << 8) + pBuff[1];
			pBuff += 2;
			
			Status = (*WrFunc3)(WrAddr, WrData);
			WrAddr++;
			
			if(Status != 0)
			{
				return false;
			}
		}
		wBmaDataReadOkFlag |= 0x10;
	}
	else 
	{
		return false;
	}

	wBmsTxCmd = 0;
	if(wBmaDataReadOkFlag == 0x11)
	{
		wBmaDataReadOkFlag = 0;
		uwSetBmsDataFlag(cGET_BMSDATA_FLAG_READOK);
	}

	return true;
	
}

//查询电池包Info数据
void sBmsInfoDataFramePolling(INT8U sciid,INT8U BmsAddr)
{
	INT16U wCRC;
	INT8U  TxLen;
	static INT8U  TxBuff[8] = {0};

	TxBuff[cMODBUS_ADDR] = BmsAddr;	
	TxBuff[cMODBUS_CMD] = 3;
	TxBuff[cMODBUS_REG_ADDR_H] = 0xF8;
	TxBuff[cMODBUS_REG_ADDR_L] = 0;
	TxBuff[cMODBUS_REG_NUM_H] = 0;
	TxBuff[cMODBUS_REG_NUM_L] = 16;
	TxLen = 6;
	
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], TxLen);
	TxBuff[6] = wCRC >> 8;
	TxBuff[7] = wCRC & 0x00FF;

	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid,TxBuff, 8);
	}
}

//查询电池包Bms数据
void sBmsFramePolling(INT8U sciid,INT8U BmsAddr)
{
	INT16U wCRC;
	INT8U  TxLen;
	static INT8U  TxBuff[8] = {0};

	TxBuff[cMODBUS_ADDR] = BmsAddr;	
	TxBuff[cMODBUS_CMD] = 3;
	TxBuff[cMODBUS_REG_ADDR_H] = BMS_REG_BASE_ADDR >> 8;
	TxBuff[cMODBUS_REG_ADDR_L] = BMS_REG_BASE_ADDR & 0x00FF;
	TxBuff[cMODBUS_REG_NUM_H] = 0;
	TxBuff[cMODBUS_REG_NUM_L] = 32;
	TxLen = 6;
	
	wCRC = swModbusCrc16(&TxBuff[cMODBUS_ADDR], TxLen);
	TxBuff[6] = wCRC >> 8;
	TxBuff[7] = wCRC & 0x00FF;

	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid,TxBuff, 8);
	}
}

void	sBuildUpgradeFrame(INT8U *RxBuff, INT8U *TxBuff, INT8U sciid)
{
	TxBuff[0] = 'A';
	TxBuff[1] = '\r';
	
	if(sSciGetTxStatus(sciid) != cSciTxBusy)
	{
		sSciWrite(sciid, TxBuff, 2);
	}
}

INT16U	swInfoDataRead(INT16U RdAddr)
{
	RdAddr -= INFO_REG_BASE_ADDR;
	return swGetInverterInformationData(RdAddr);
}

INT16U	swRealTimeDataRead(INT16U RdAddr)
{
	RdAddr -= REALDATA_REG_BASE_ADDR;
	return swGetInverterRealtimeData(RdAddr);
}

INT16U	swWifiIotDataRead(INT16U RdAddr)
{
	RdAddr -= WIFI_IOT_REG_BASE_ADDR;
	return swGetWifiIotData(RdAddr);
}


INT16U	swGetEepromStaticCFG1Data(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < (cEepromTotalLength1 / 2))
	{
		pwTemp = (INT16U *)&uEepromCfg1;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}
INT16U	swGetEepromStaticCFG2Data(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < (cEepromTotalLength2 / 2))
	{
		pwTemp = (INT16U *)&uEepromCfg2;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}
INT16U	swGetEepromStaticCFG3Data(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < (cEepromTotalLength3 / 2))
	{
		pwTemp = (INT16U *)&uEepromCfg3;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

INT16U	swEESettingRead(INT16U RdAddr)
{
	INT16U wTemp;
	INT16U wEepromLen1 = 0,wEepromLen2 = 0,wEepromLen3 = 0;
	
	wEepromLen1 = cEepromTotalLength1 >> 1;	// 80
	wEepromLen2 = cEepromTotalLength2 >> 1;	// 160
	wEepromLen3 = cEepromTotalLength3 >> 1;	// 40

	RdAddr -= EE_REG_BASE_ADDR;
	if(RdAddr < (wEepromLen1))
	{
		wTemp = swGetEepromStaticCFG1Data(RdAddr - EE_uwAddrStart);
	}
	else if(RdAddr > (wEepromLen1 - 1) && RdAddr < (wEepromLen1 + wEepromLen2))
	{
		wTemp = swGetEepromStaticCFG2Data(RdAddr - wEepromLen1);
	}
	else if(RdAddr > (wEepromLen1 + wEepromLen2 - 1) && RdAddr < (wEepromLen1 + wEepromLen2 + wEepromLen3))
	{
		wTemp = swGetEepromStaticCFG3Data(RdAddr - wEepromLen1 - wEepromLen2);
	}
	else
	{
		wTemp = 0xFFFF;
	}
	
	return wTemp;
}

INT8U	swEESettingWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	INT8U DoEEPROM1Save = 0;
	INT8U DoEEPROM2Save = 0;
	INT8U DoEEPROM3Save = 0;
	
	WrAddr -= EE_REG_BASE_ADDR;
	switch(WrAddr)
	{
// 		EEPROM1
		case EE_uwSetMachineID:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetParaEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetMasterSlaver:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetEepromAutoWrite:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetSystemOutputMode:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetFanWorkMode:
			if(WrData <= cFanModeMax)	
			{
				sSetEEFanWorkMode(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwTurboMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEETurboMode(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwAutoInvEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAutoInvEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwDCDCOpenLoopEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEDCDCOpenLoopEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwsLogoEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEELogoEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwAdcBiasAdj:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAdcBiasAdj(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetReserve11:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetReserve12:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetReserve13:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetReserve14:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetPV1StartVolt:
			if(WrData <= (uwGetMpptPvVoltMax()*10))
			{
				sSetEEPV1StartVolt(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetReserve16:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetPV_PowerLimit:
			if(WrData <= uwGetPvPowerMax())	
			{
				sSetEEPV_PowerLimit(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetReserve18:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetReserve19:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetPV_Priority:
			if(WrData <= 2)	//0: BLU (电池 > 负载 > 电网)1: LBU (负载 > 电池 > 电网)2: LUB (负载 > 电网 > 电池) --只有并网馈电时生效
			{
				sSetEEPV_Priority(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwPVAutoInvEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPVAutoInvEnable(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd22:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetBatType:
			if(WrData <= 3)	//0: 胶体电池 (AGM)1: 注水电池 (Flood)2: 用户自定义 (User defined)3: 锂电池 (Lithium)
			{
				sSetEEBatType(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatSeriesNum:
//			if(WrData <= 2)	
//			{
//				sSetEEBatSeriesNum(WrData);
//				DoEEPROM1Save = true;
//			}
//		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatCapacity:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd26:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetBatMode:
			if(WrData <= 2)		//0: 市电优先 1: PV优先2: PV和市电3: 仅PV 
			{
				sSetEEBatMode(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetChargePriority:
			if(WrData <= 3)		//0: 市电优先 1: PV优先2: PV和市电3: 仅PV 
			{
				sSetEEChargePriority(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatConstVolt:
			if((WrData >= cBatVoltReal3V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatConstVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatFloatVolt:
			if((WrData >= cBatVoltReal3V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatFloatVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatFloatTime:
			if(WrData <= 100)		//Max 100分钟
			{
				sSetEEBatFloatTime(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatMaxChgCurr:
			if(WrData <= (uwGetSettingMaxChgCurr()))
			{
				sSetEEBatMaxChgCurr(WrData);
				if(suwGetEEGridChgBatCurr() > WrData)	// 设置的总充电电流比当前的市电充电电流小时更新一下市电电流
				{
					sSetEEGridChgBatCurr(WrData);
				}
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatMaxDcgCurr:
			if(WrData <= (uwGetSettingMaxDchgCurr()))
			{
				sSetEEBatMaxDcgCurr(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetGridChgBatCurr:
			if(WrData <= (uwGetSettingMaxACChgCurr()) && WrData <= suwGetEEBatMaxChgCurr())
			{
				sSetEEGridChgBatCurr(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetGridChgBatTotalEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEGridChgBatTotalEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOnGridBatAutoStartChgSOC:
			if(WrData <= 100)	
			{
				sSetEEOnGridBatAutoStartChgSOC(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOnGridBatExitAutoChgSOC:
			if(WrData <= 100)	
			{
				sSetEEOnGridBatExitAutoChgSOC(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOnGridBatAutoStartChgVolt:
			if((WrData >= cBatVoltReal10V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEOnGridBatAutoStartChgVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOnGridBatExitAutoChgVolt:
			if((WrData >= cBatVoltReal10V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEOnGridBatExitAutoChgVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatACRestartVolt:
			if((WrData >= cBatVoltReal10V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEBatACRestartVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatLowAlarmVolt:
			if((WrData >= cBatVoltReal8V5 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal13V * uwGetBatSerialPcs())) // min 8.5V, max 13V
			{
				sSetEEBatLowAlarmVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatLowShutDownVolt:
			if((WrData >= cBatVoltReal8V5 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal13V * uwGetBatSerialPcs())) // min 8.5V, max 13V
			{
				sSetEEBatLowShutDownVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatACRestartSOC:
			if(WrData <= 100)
			{
				sSetEEBatACRestartSOC(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatLowAlarmSOC:
			if(WrData <= 100)
			{
				sSetEEBatLowAlarmSOC(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatLowShutDownSOC:
			if(WrData <= 100)
			{
				sSetEEBatLowShutDownSOC(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatVoltOverShut:
			if((WrData >= cBatVoltReal12V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal16V * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatVoltOverShut(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatActivateEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatActivateEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBMSComErrEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBMSComErrEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBMSProtocol:
			if((WrData <= 99))
			{
				sSetEEBMSProtocol(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatParaEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatParaEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatTempCompensateEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatTempCompensateEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEEBatEqEn(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqVolt:
			if((WrData >= cBatVoltReal12V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEEBatEqVolt(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqTime:
			if(WrData <= 900)	//min
			{
				sSetEEEBatEqTime(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqTimeout:
			if(WrData <= 900)	//min
			{
				sSetEEEBatEqTimeout(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqInterval:
			if(WrData <= 900)	//min
			{
				sSetEEEBatEqInterval(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqActImd:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEEBatEqActImd(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd58:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd59:
			ret = cErr_ParUnValid;
		break;
		case EE_uwBatLowVoltDerateEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatLowVoltDerateEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd61:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd62:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd63:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetACOutputRatedPower:
			if(WrData <= ((INT16U)uwGetInvWattMax()))
			{
				sSetEEACOutputRatedPower(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetACOutputRatedVolt:
			if(uwGetModelLV())
			{
				if((WrData == cAcVoltReal110V)||(WrData == cAcVoltReal115V)||(WrData == cAcVoltReal120V)||(WrData == cAcVoltReal127V))
				{
					sSetEEACOutputRatedVolt(WrData);
					sInvWattResCal();
					DoEEPROM1Save = true;
				}
				else 
				{ 
					ret = cErr_ParUnValid; 
				}
			}
			else
			{
				//if((WrData == cAcVoltReal220V)||(WrData == cAcVoltReal230V)||(WrData == cAcVoltReal240V))
				if((WrData >= 500) && (WrData <= 2400))	// for test
				{
					sSetEEACOutputRatedVolt(WrData);
					sInvWattResCal();
					DoEEPROM1Save = true;
				}
				else 
				{ 
					ret = cErr_ParUnValid; 
				}
			}
		break;
		case EE_uwSetACOutputRatedFreq:
			// 0：cFreq50hzConst
			// 2：cFreq60hzConst	
			if((WrData == 0)||(WrData == 1))
			{
				sSetEEACOutputRatedFreq(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			} 
		break;
		case EE_uwSetGridInputRange:
			if((WrData == cAPL) || (WrData == cUPS))
			{
				sSetEEGridInputRange(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOutputPriority:
			if((WrData == cDsgPriorityLINE) || (WrData == cDsgPriorityPV) || (WrData == cDsgPriorityBAT))
			{
				sSetEEOutputPriority(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetWorkMode:
			if(WrData <= 3)
			{
				sSetEEWorkMode(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd70:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd71:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd72:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGridPeakShavingEnable:	//电网调峰/限流限功率使能
		{
			if(WrData <= 1)
			{
				sSetEEGridPeakShavingEnable(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwSetGridPeakShavingPower:
		{
			if(WrData <= ((INT16U)uwGetInvWattMax()))
			{
				sSetEEGridPeakShavingPower(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwSetGridPeakShavingCurr:
		{
			if(WrData <= cMaxACInputCurr)
			{
				sSetEEGridPeakShavingCurr(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwMaxFeedPower:
		{
			if(WrData <= ((INT16U)uwGetInvWattMax() + 200)) // -200W ~ 3200W
			{
				sSetEEMaxFeedPower(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwSetRsvd77:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd78:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd79:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd80:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd81:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRecconectWaitTime:
			if(WrData <= 600)		//秒
			{
				sSetEERecconectWaitTime(WrData);
				DoEEPROM1Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetAnti_IslandProtectEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAnti_IslandProtectEnable(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd84:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetPowerSaveMode:	
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPowerSaveMode(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwPowerConversion:	// 功率折算使能
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPowerConversion(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOverTempRestartEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverTempRestartEn(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOverLoadRestartEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverLoadRestartEn(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetOverLoadBypassEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverLoadBypassEn(WrData);
				DoEEPROM1Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwFeedToLineTime:
			if(WrData <= 60000)					// ms
			{
				sSetEEFeedToLineTime(WrData);
				DoEEPROM1Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetRsvd91:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd92:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd93:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd94:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd95:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd96:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd97:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd98:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd99:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd100:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd101:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1OVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1OVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2OVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2OVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3OVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3OVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1UVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1UVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2UVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2UVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3UVValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3UVTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1OFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1OFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2OFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2OFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3OFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3OFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1UFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid1UFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2UFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid2UFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3UFValue:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetGrid3UFTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd126:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd127:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd128:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd129:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd130:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd131:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO_TimeOfUse:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO_EffectiveWeek:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO1_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO2_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO3_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO4_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO5_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO6_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd182:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd183:
			ret = cErr_ParUnValid;
		break;
		case EE_uwFlag1:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEECheckCRC1:
			ret = cErr_ParUnValid;
		break;

		//EEPROM2
		case EE_uwEEPV1VoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1VoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV2VoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV2VoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1CurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1CurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV2CurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV2CurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBUSVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBUSVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBUSCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBUSCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEInvVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEInvVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEInvCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEInvCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOPVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOpVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOPCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOpCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEDischargeEneyCoeffH:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEDischargeEneyCoeffL:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEchargeEneyCoeffH:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEchargeEneyCoeffL:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd218:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd219:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd220:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd221:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd222:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd223:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd224:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd225:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd226:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd227:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd228:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd229:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd230:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd231:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd232:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd233:
			ret = cErr_ParUnValid;
		break;
		case EE_uwFlag2:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEECheckCRC2:
			ret = cErr_ParUnValid;
		break;

		//EEPROM3
		case EE_uwATE_SN1:
			if(WrData <= 9999)
			{
				sSetEEATE_SN1(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_SN2:
			if(WrData <= 9999)
			{
				sSetEEATE_SN2(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_SN3:
			if(WrData <= 9999)
			{
				sSetEEATE_SN3(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_SN4:
			if(WrData <= 9999)
			{
				sSetEEATE_SN4(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_SN5:
			if(WrData <= 9999)
			{
				sSetEEATE_SN5(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_SNLen:
			if(WrData <= 18)
			{
				sSetEEATE_SNLen(WrData);
				DoEEPROM3Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwATE_DispHwVer:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_CtrlHwVer:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_PowerHwVer:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_UpdateFW:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_ResetSystem:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EEDefault:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_AgingMode:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_RemoteOnOff:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EEFactory:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_AgingBattVolt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_AgingBattCurr:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_AgingPVPower:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_AgingInvPower:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_MPPTVoltCntl:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_E_totalClr:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_SafetyCode:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_ISOsetting:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterProc:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_ExCommBps:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterBps_Parity:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterAddr:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterWREn:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterDataRegAddr:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_EleMeterData:
			ret = cErr_ParUnValid;
		break;
		case EE_uwATE_485CommBps:
			ret = cErr_ParUnValid;
		break;
		case EE_uwMenuRtnDftPageEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEMenuRtnDftPageEn(WrData);
				DoEEPROM3Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetLCDBacklight:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEELCDBacklight(WrData);
				DoEEPROM3Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBuzzerBeep:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBuzzerBeep(WrData);
				DoEEPROM3Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBmsBagAddr:
			{
//				 if((1 <= WrData) && (WrData <= 16) && (sbGetEMSBMSConnect() || swGetPylonCanConnectFlag()))	//BMS通信成功的才可以写入
//				{
//					sSetEEBmsBagAddr(WrData);
//					g_uwBMSAddr = WrData;
//					uwSetBmsDataFlag(cGET_BMSDATA_FLAG_READING);
//				}
//				else
//				{ 
					ret = cErr_ParUnValid; 
//				}
			}

		break;
		case EE_uwSetClearEventLog:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetEventLogFunc:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetFaultLogFunc:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetLogType:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetLogIndex:
			ret = cErr_ParUnValid;
		break;
		case EE_uwFlag3:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEECheckCRC3:
			ret = cErr_ParUnValid;
		break;

		default:break;
	}
	
	if(DoEEPROM1Save != 0)
	{
		sSetEeprom1Mode(cEEPROM_SAVE_ENABLE);
	}
	if(DoEEPROM2Save != 0)
	{
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	if(DoEEPROM3Save != 0)
	{
		sSetEeprom3Mode(cEEPROM_SAVE_ENABLE);
	}
	
	return ret;
}

INT8U	swATESettingWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	INT8U DoEEStaticSave = false;
	INT8U DoEEDynamicSave = false;
	INT8U DoEERealtimeSave = false;
	INT8U DoEEFaultRecordSave = false;
	//INT16S wTempCmd;
	INT16S wTempData;
	//INT8U HData = 0,LData = 0;
	//INT16S wTemp1 = 0, wTemp2 = 0;
	
	WrAddr -= ATE_REG_BASE_ADDR;
	switch(WrAddr)
	{
		case eATEComFactoryReset:	// 0  1：EEPROM全部恢复默认值，2：恢复出厂设置(除校准参数外)
		{
			if(WrData == 1)
			{
				sEepromDefaultSave1();
				sEepromDefaultSave2();
				sEepromDefaultSave3();
				OSEventSend(cPrioInterface, eI2CEEpromUserSave);
				OSEventSend(cPrioInterface, eI2CEEpromFacSave);
				OSEventSend(cPrioInterface, eI2CEEpromUser2Save);
				sEepromDataVarRangeChk();	// 初始化机型参数
			}
			else if(WrData == 2)
			{
				sEepromDefaultSave1();
				OSEventSend(cPrioInterface, eI2CEEpromUserSave);
				sEepromDataVarRangeChk();	// 初始化机型参数
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		}
		break;
		case eATEComFaultClear:		// 1 故障清除重启
		{
			ret = cErr_UnDataAddr;
		}
		break;
		case eATEComRemoteOff:		// 2 远程关机
		{
			ret = cErr_UnDataAddr;
		}
		break;
		case eATEComCodeUpdata:
			ret = cErr_UnDataAddr;
		break;
		case eATEComYearMonth:
			ret = cErr_UnDataAddr;
		break;
		case eATEComDayHour:
			ret = cErr_UnDataAddr;
		break;
		case eATEComMinuteSecond:
			ret = cErr_UnDataAddr;
		break;
		case eATEComWeek:
			ret = cErr_UnDataAddr;
		break;
		case eATEComGenaInqury_YearMonth:
			ret = cErr_UnDataAddr;
		break;
		case eATEComGenaInqury_Day:
			ret = cErr_UnDataAddr;
		break;
		case eATEComGenaRecordClear:
			ret = cErr_UnDataAddr;
		break;
		case eATEComEPOEnable:
			ret = cErr_UnDataAddr;
		break;
		case eATEComQuickSettings:
			ret = cErr_UnDataAddr;
		break;
		case eATEComInvChgWattSoftStartRate:
			if((WrData <= 60) && (WrData >= 10))
			{
				sSetGridpowerslopeTime(WrData);		// ATE测试设置到10比较合适
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEComRsvd14:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd15:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd16:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd17:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd18:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd19:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd20:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd21:
			ret = cErr_UnDataAddr;
		break;
		case eATEComBatteyAddr:
			ret = cErr_UnDataAddr;
		break;
		case eATEComBattey2Addr:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd24:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd25:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd26:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd27:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd28:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd29:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd30:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd31:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd32:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1VoltAdj0:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1VoltAdj1:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1VoltAdj2:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1VoltAdj:
			if(WrData == cEnable)
			{
				if(suwGetEEPV1VoltAdj() != cEEBatVoltAdjDef)
				{
					sSetEEPV1VoltAdj(cEEBatVoltAdjDef);
					sSetPvVoltAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}
			else
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbPvVoltAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEComRsvd37:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd38:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd39:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd40:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1BatCurrAdj0:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1BatCurrAdj1:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1BatCurrAdj2:
			ret = cErr_UnDataAddr;
		break;
		case eATEPV1BatCurrAdj:
			if(WrData == cEnable)
			{
				if(suwGetEEPV1BatCurrAdj() != cEEBatVoltAdjDef)
				{
					sSetEEPV1BatCurrAdj(cEEBatVoltAdjDef);
					sSetPvBatCurrAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}
			else
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbPvBatCurrAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEComRsvd45:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd46:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd47:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd48:
			ret = cErr_UnDataAddr;
		break;
		case eATEBatVoltAdj0:		// 电池电压校准阶段0 初始化	
		{
			if(WrData == cEnable)
			{
				sBattVoltAdj0();
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		}
		break;
		case eATEBatVoltAdj1:		// 电池电压校准阶段1 记录一个点		低点		
		{
			//wTempCmd = WrData / 10000;
			wTempData = WrData % 10000;
			ret = sbBattVoltAdj1(wTempData);
		}
		break;
		case eATEBatVoltAdj2:		// 电池电压校准阶段2 另一个点		高点
		{
			//wTempCmd = WrData / 10000;
			wTempData = WrData % 10000;
			ret = sbBattVoltAdj2(wTempData);
			if(ret == 0)
			{
				DoEEStaticSave = true;
			}
		}
		break;
		case eATEBatVoltAdj:
			ret = cErr_UnDataAddr;
		break;
		case eATEBatCurrAdj0:
			ret = cErr_UnDataAddr;
		break;
		case eATEBatCurrAdj1:
			ret = cErr_UnDataAddr;
		break;
		case eATEBatCurrAdj2:
			ret = cErr_UnDataAddr;
		break;
		case eATEBatCurrAdj:
			ret = cErr_UnDataAddr;
		break;
		case eATEGrid_Volt0:
			if(WrData == cEnable)
			{
				if(suwGetEEGridVoltAdj() != cEEBatVoltAdjDef)
				{
					sSetEEGridVoltAdj(cEEBatVoltAdjDef);
					sSetGridVoltAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}	
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEGrid_Volt1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbLineVoltAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEGrid_Volt:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd60:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd61:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd62:
			ret = cErr_UnDataAddr;
		break;
		case eATEINV_Volt0:
			if(WrData == cEnable)
			{	// 默认系数4096，最小2048，最大8192
				if(suwGetEEInvVoltAdj() != cEEBatVoltAdjDef)	
				{
					sSetEEInvVoltAdj(cEEBatVoltAdjDef);
					sSetInvVoltAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEINV_Volt1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbInvVoltAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEINV_Volt:
			ret = cErr_UnDataAddr;
		break;
		case eATEINV_Curr0:
			if(WrData == cEnable)
			{
				if(suwGetEEInvCurrAdj() != cEEBatVoltAdjDef)
				{
					sSetEEInvCurrAdj(cEEBatVoltAdjDef);
					sSetInvCurrAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEINV_Curr1:
			{	
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbInvCurrAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEINV_Curr:
			ret = cErr_UnDataAddr;
		break;
		case eATELoad_Curr0:
			if(WrData == cEnable)
			{
				if(suwGetEEOPCurrAdj() != cEEBatVoltAdjDef)
				{
					sSetEEOPCurrAdj(cEEBatVoltAdjDef);
					sSetOpCurrAdj(4096);
					DoEEStaticSave = true;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATELoad_Curr1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbOPCurrAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATELoad_curr:
			ret = cErr_UnDataAddr;
		break;
		case eATEOut_Volt0:
			if(WrData == cEnable)
			{	// 默认系数4096，最小2048，最大8192
				if(suwGetEEOPVoltAdj() != cEEBatVoltAdjDef)	
				{
					sSetEEOPVoltAdj(cEEBatVoltAdjDef);
					sSetOpVoltAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEOut_Volt1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbOPVoltAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEOut_Volt:
			ret = cErr_UnDataAddr;
		break;
		case eATEPos_Bus_Volt0:
			if(WrData == cEnable)
			{
				if(suwGetEEBUSVoltAdj() != cEEBatVoltAdjDef)
				{
					sSetEEBUSVoltAdj(cEEBatVoltAdjDef);
					sSetBusVoltAdj(cEEBatVoltAdjDef);
//					sSetDCDCBusVoltOpenAdj(true);	// BUS强制打满占空比，推挽处于谐振状态，(BUS_Volt = VBat * 33.4)
					DoEEStaticSave = true;
				}
			}		
			else if(WrData == 2)	
			{
//				sSetDCDCBusVoltOpenAdj(false);		// 校准完之后BUS退出占空比强制打满状态
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEPos_Bus_Volt1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
				ret = sbBusVoltAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEPos_Bus_Volt:
			ret = cErr_UnDataAddr;
		break;
		case eATEPos_Bus_Curr0:
//			if(WrData == cEnable)
//			{
//				if(suwGetEEBUSCurrAdj() != cEEBatVoltAdjDef)
//				{
//					sSetEEBUSCurrAdj(cEEBatVoltAdjDef);
//					sSetBusCurrAdj(cEEBatVoltAdjDef);
//					DoEEStaticSave = true;
//				}
//			}		
//			else
//			{
				ret = cErr_ParUnValid;
//			}
		break;
		case eATEPos_Bus_Curr1:
			{
//				wTempData = WrData % 10000;
//				ret = sbBusCurrAdj(wTempData);
//				if(ret == 0)
//				{
//					DoEEStaticSave = true;
//				}
			}
		break;
		case eATEPos_Bus_Curr:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd81:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd82:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd83:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd84:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd85:
			ret = cErr_UnDataAddr;
		break;

		default:break;
	}
	
	if(DoEEStaticSave != 0)
	{
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	if(DoEEDynamicSave != 0)
	{
		//sSetEepromDynamicMode(cEEPROM_SAVE_MODE_ENABLE);
	}
	if(DoEERealtimeSave != 0)
	{
		//sSetEepromRealtimeMode(cEEPROM_SAVE_MODE_ENABLE);
	}
	if(DoEEFaultRecordSave != 0)
	{
		//sSetEepromFaultRecordMode(cEEPROM_SAVE_MODE_ENABLE);
	}

	return ret;
}

INT8U	swWifiIotWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	
	WrAddr -= WIFI_IOT_REG_BASE_ADDR;
	switch(WrAddr)	// 0X5100	区分4G/WiFi
	{
		case uwIotType:
		{
			if(1)
			{
				sSetWifiIotType(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;	
		case uwIotTersion:// 0X5101	iot 版本号
		{
			if(1)
			{
				sSetWifiIotTersion(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;	
		case uwIotIpAddressH:// 0X5102	iot 设备的IP地址：如0xC0A86401=192.168.100.1
		{
			if(1)
			{
				sSetWifiIotIpAddressH(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;	
		case uwIotIpAddressL:		// 0X5103	
		{
			if(1)
			{
				sSetWifiIotIpAddressL(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;		
		case uwIotSimSn1:				// 0X5104	带有英文字符的20个长度:如：ICCID: 898604B3192270310904
		{
			if(1)
			{
				sSetWifiIotSimSn1(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;	
		case uwIotSimSn2:				
		{
			if(1)
			{
				sSetWifiIotSimSn2(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn3:				
		{
			if(1)
			{
				sSetWifiIotSimSn3(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn4:				
		{
			if(1)
			{
				sSetWifiIotSimSn4(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn5:				
		{
			if(1)
			{
				sSetWifiIotSimSn5(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn6:				
		{
			if(1)
			{
				sSetWifiIotSimSn6(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn7:				
		{
			if(1)
			{
				sSetWifiIotSimSn7(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn8:				
		{
			if(1)
			{
				sSetWifiIotSimSn8(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn9:				
		{
			if(1)
			{
				sSetWifiIotSimSn9(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn10:				
		{
			if(1)
			{
				sSetWifiIotSimSn10(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn11:				
		{
			if(1)
			{
				sSetWifiIotSimSn11(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn12:				
		{
			if(1)
			{
				sSetWifiIotSimSn12(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn13:				
		{
			if(1)
			{
				sSetWifiIotSimSn13(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn14:				
		{
			if(1)
			{
				sSetWifiIotSimSn14(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn15:				
		{
			if(1)
			{
				sSetWifiIotSimSn15(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotSimSn16:				
		{
			if(1)
			{
				sSetWifiIotSimSn16(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwIotState:				// 0X5114	iot 设备的状态：
		// 			0：iot 设备没有与MCU 建立通信
		// 			1：连接路由器错误，有配置路由器
		// 			2：连接上路由器
		// 			3：连接上服务器
		// 			4：正在配置连接路由器或基站
		// 			5：正在升级IOT 设备程序
		{
			if(1)
			{
				sSetWifiIotState(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;					
		case uwIotRSSI:			// 0X5115	4G/WiFi的信号强度
		{
			if(1)
			{
				sSetWifiIotRSSI(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case uwBleConn:			// 0X5116	蓝牙设备连接数
		{
			if(1)
			{
				sSetWifiIotBleConn(WrData);
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		case uwReserved2:				ret = cErr_ParUnValid;break;	// 0X5117
		case uwReserved3:				ret = cErr_ParUnValid;break;	// 0X5118
		case uwReserved4:				ret = cErr_ParUnValid;break;	// 0X5119
		case uwReserved5:				ret = cErr_ParUnValid;break;	// 0X511A
		case uwReserved6:				ret = cErr_ParUnValid;break;	// 0X511B
		case uwReserved7:				ret = cErr_ParUnValid;break;	// 0X511C
		case uwReserved8:				ret = cErr_ParUnValid;break;	// 0X511D
		case uwReserved9:				ret = cErr_ParUnValid;break;	// 0X511E
		default:break;
	}
	
	return ret;
}

INT16U	swEMSDataWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	
	WrAddr -= EMS_REG_BASE_ADDR;
	switch(WrAddr)
	{
		case EMS_ChargeVoltageLimit:
//			swSetEmsDataChargeVoltageLimit(WrData);
		break;
		case EMS_DischargeVoltageLimit:
//			swSetEmsDataDischargeVoltageLimit(WrData);
		break;
		case EMS_ChargeCurrentLimit:
//			swSetEmsDataChargeCurrentLimit(WrData);
		break;
		case EMS_DischargeCurrentLimit:
//			swSetEmsDataDischargeCurrentLimit(WrData);
		break;
		case EMS_StatusHigh:
//			swSetEmsDataStatusHigh(WrData);
		break;
		case EMS_StatusLow:			
//			swSetEmsDataStatusLow(WrData);
		break;
		case EMS_FaultFlagHigh:			
//			swSetEmsDataFaultFlagHigh(WrData);
		break;
		case EMS_FaultFlagLow:			
//			swSetEmsDataFaultFlagLow(WrData);
		break;
		case EMS_AlarmFlagHigh:			
//			swSetEmsDataAlarmFlagHigh(WrData);
		break;
		case EMS_AlarmFlagLow:			
//			swSetEmsDataAlarmFlagLow(WrData);
		break;
		case EMS_NoticeFlagHigh:			
//			swSetEmsDataNoticeFlagHigh(WrData);
		break;
		case EMS_NoticeFlagLow:			
//			swSetEmsDataNoticeFlagLow(WrData);
		break;
		case EMS_TotalCurrent:			
//			swSetEmsDataTotalCurrent(WrData);
		break;
		case EMS_TotalVoltage:			
//			swSetEmsDataTotalVoltage(WrData);
		break;
		case EMS_TotalVoltageComp:			
//			swSetEmsDataTotalVoltageComp(WrData);
		break;
		case EMS_Reservd02:			
//			swSetEmsDataReservd02(WrData);
		break;
		case EMS_TotalSOC:			
//			swSetEmsDataTotalSOC(WrData);
		break;
		case EMS_TotalSOH:			
//			swSetEmsDataTotalSOH(WrData);
		break;
		case EMS_TotalCapacityHigh:			
//			swSetEmsDataTotalCapacityHigh(WrData);
		break;
		case EMS_TotalCapacityLow:			
//			swSetEmsDataTotalCapacityLow(WrData);
		break;
		case EMS_ParallelNumber:			
//			swSetEmsDataParallelNumber(WrData);
		break;
		case EMS_ParallelStatus:			
//			swSetEmsDataParallelStatus(WrData);
		break;
		case EMS_SerialNumber:			
//			swSetEmsDataSerialNumber(WrData);
		break;
		case EMS_SerialStatus:			
//			swSetEmsDataSerialStatus(WrData);
		break;
		case EMS_MaximumCellVoltageNo:			
//			swSetEmsDataMaximumCellVoltageNo(WrData);
		break;
		case EMS_MaximumCellVoltage:			
//			swSetEmsDataMaximumCellVoltag(WrData);
		break;
		case EMS_MinimumCellVoltageNo:			
//			swSetEmsDataMinimumCellVoltageNo(WrData);
		break;
		case EMS_MinimumCellVoltage:			
//			swSetEmsDataMinimumCellVoltage(WrData);
		break;
		case EMS_MaximumCellTemperatureNo:			
//			swSetEmsDataMaximumCellTemperatureNo(WrData);
		break;
		case EMS_MaximumCellTemperature:			
//			swSetEmsDataMaximumCellTemperature(WrData);
		break;
		case EMS_MinimumCellTemperatureNo:			
//			swSetEmsDataMinimumCellTemperatureNo(WrData);
		break;
		case EMS_MinimumCellTemperature:			
//			swSetEmsDataMinimumCellTemperature(WrData);	
		break;
		
		default:break;

	}
	return ret;
}

INT16U	swBmsInfoDataWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	
	WrAddr -= BMS_INFO_REG_BASE_ADDR;
	switch(WrAddr)
	{
		case BMS_INFO_BmsType:
//			swSetBmsInfoType(WrData);
		break;
		case BMS_INFO_BmsSubType:
//			swSetBmsInfoSubType(WrData);
		break;
		case BMS_INFO_BmsCommProVer:
//			swSetBmsInfoCommProVer(WrData);
		break;
		case BMS_INFO_BmsCommInfo:
//			swSetBmsInfoCommInfo(WrData);
		break;
		case BMS_INFO_BmsSN1:
//			swSetBmsInfoSerial1(WrData);
		break;
		case BMS_INFO_BmsSN2:			
//			swSetBmsInfoSerial2(WrData);
		break;
		case BMS_INFO_BmsSN3:			
//			swSetBmsInfoSerial3(WrData);
		break;
		case BMS_INFO_BmsSN4:			
//			swSetBmsInfoSerial4(WrData);
		break;
		case BMS_INFO_BmsSN5:			
//			swSetBmsInfoSerial5(WrData);
		break;
		case BMS_INFO_BmsSNLen:			
//			swSetBmsInfoSNLen(WrData);
		break;
		case BMS_INFO_BmsDispSwVer:			
//			swSetBmsInfoDispSwVer(WrData);
		break;
		case BMS_INFO_BmsMCU1SwVer:			
//			swSetBmsInfoMCU1SwVer(WrData);
		break;
		case BMS_INFO_BmsMCU2SwVer:			
//			swSetBmsInfoMCU2SwVer(WrData);
		break;
		case BMS_INFO_BmsDispHwVer:			
//			swSetBmsInfoDispHwVer(WrData);
		break;
		case BMS_INFO_BmsCtrlHwVer:			
//			swSetBmsInfoCtrlHwVer(WrData);
		break;
		case BMS_INFO_BmsPowerHwVer:			
//			swSetBmsInfoPowerHwVer(WrData);
		break;
		default:break;

	}
	return ret;


}

INT16U	swBmsDataWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	
	WrAddr -= BMS_REG_BASE_ADDR;
	switch(WrAddr)
	{
		case BMS_ChargeVoltageLimit:
//			swSetBmsChargeVoltageLimit(WrData);
		break;
		case BMS_DischargeVoltageLimit:
//			swSetBmsDischargeVoltageLimit(WrData);
		break;
		case BMS_ChargeCurrentLimit:
//			swSetBmsChargeCurrentLimit(WrData);
		break;
		case BMS_DischargeCurrentLimit:
//			swSetBmsDischargeCurrentLimit(WrData);
		break;
		case BMS_StatusHigh:
//			swSetBmsStatusHigh(WrData);
		break;
		case BMS_StatusLow:			
//			swSetBmsStatusLow(WrData);
		break;
		case BMS_FaultFlagHigh:			
//			swSetBmsFaultFlagHigh(WrData);
		break;
		case BMS_FaultFlagLow:			
//			swSetBmsFaultFlagLow(WrData);
		break;
		case BMS_AlarmFlagHigh:			
//			swSetBmsAlarmFlagHigh(WrData);
		break;
		case BMS_AlarmFlagLow:			
//			swSetBmsAlarmFlagLow(WrData);
		break;
		case BMS_NoticeFlagHigh:			
//			swSetBmsNoticeFlagHigh(WrData);
		break;
		case BMS_NoticeFlagLow:			
//			swSetBmsNoticeFlagLow(WrData);
		break;
		case BMS_TotalCurrent:			
//			swSetBmsPackCurrent(WrData);
		break;
		case BMS_TotalVoltage:			
//			swSetBmsPackVoltage(WrData);
		break;
		case BMS_TotalVoltageComp:			
//			swSetBmsPackVoltageReal(WrData);
		break;
		case BMS_Reservd02:			
//			swSetBmsReservd2(WrData);
		break;
		case BMS_TotalSOC:			
//			swSetBmsSOC(WrData);
		break;
		case BMS_TotalSOH:			
//			swSetBmsSOH(WrData);
		break;
		case BMS_TotalCapacityHigh:			
//			swSetBmsPackCapacityHigh(WrData);
		break;
		case BMS_TotalCapacityLow:			
//			swSetBmsPackCapacityLow(WrData);
		break;
		case BMS_ParallelNumber:			
//			swSetBmsParallelNumber(WrData);
		break;
		case BMS_ParallelStatus:			
//			swSetBmsParallelStatus(WrData);
		break;
		case BMS_SerialNumber:			
//			swSetBmsSerialNumber(WrData);
		break;
		case BMS_SerialStatus:			
//			swSetBmsSerialStatus(WrData);
		break;
		case BMS_MaximumCellVoltageNo:			
//			swSetBmsMaximumCellVoltageNo(WrData);
		break;
		case BMS_MaximumCellVoltage:			
//			swSetBmsMaximumCellVoltage(WrData);
		break;
		case BMS_MinimumCellVoltageNo:			
//			swSetBmsMinimumCellVoltageNo(WrData);
		break;
		case BMS_MinimumCellVoltage:			
//			swSetBmsMinimumCellVoltage(WrData);
		break;
		case BMS_MaximumCellTemperatureNo:			
//			swSetBmsMaximumCellTemperatureNo(WrData);
		break;
		case BMS_MaximumCellTemperature:			
//			swSetBmsMaximumCellTemperature(WrData);
		break;
		case BMS_MinimumCellTemperatureNo:			
//			swSetBmsMinimumCellTemperatureNo(WrData);
		break;
		case BMS_MinimumCellTemperature:			
//			swSetBmsMinimumCellTemperature(WrData);	
		break;
		
		default:break;

	}
	return ret;
}



INT16U	swSwapDataRead(INT16U RdAddr)
{
//	RdAddr -= SWAP_RD_REG_BASE_ADDR;
	return 0x55AA;//swGetEmsSwapData(RdAddr);
}

INT8U	swSwapDataWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
//	INT8U DoEEDynamicSave = 0;
//	INT8U DoEERealtimeSave = 0;
//	
//	WrAddr -= SWAP_WR_REG_BASE_ADDR;
//	switch(WrAddr)
//	{
//		case SWAP_WR_Reserved20:
//			if((WrData & 0x0001) != 0)
//			{
//				//OSEventSend(cPrioSuper, eSuperToShutdown);
//			}
//		break;
//		case SWAP_WR_Reserved3:
//		break;
//		default:break;
//	}
//	
//	if(DoEEDynamicSave != 0)
//	{
//		//sSetEepromDynamicMode(cEEPROM_SAVE_MODE_ENABLE);
//	}
//	
//	if(DoEERealtimeSave != 0)
//	{
//		//sSetEepromRealtimeMode(cEEPROM_SAVE_MODE_ENABLE);
//	}
	
	return ret;
}

// for test
extern INT16S 	wACoutFanPer;			// 功率折算风扇百分比
extern INT16S 	wInvTempFanPer;			// 逆变温度折算风扇百分比
extern INT16S 	wPvBatCurrFanPer;		// PV充电电池电流折算风扇百分比
extern INT16S 	wAcBatChgCurrFanPer;	// 市电充电电池电流折算风扇百分比
extern INT16S 	g_wRInvDCVoltCntl;
extern INT16U 	fChgMode;
extern INT16U 	gi_wDCDCConvPWMPeriod;

INT16U	swTestCmdRead(INT16U RdAddr)
{
	INT16U wTemp;
	
	RdAddr -= DBG_CMD_BASE_ADDR;
	switch(RdAddr)
	{
		case DBG_XXXXXXX00:			// DSP主版本号
			wTemp = cDspCtrlVersion;
		break;
		case DBG_XXXXXXX01:			// DSP子版本号
			wTemp = cDspTempVersion;
		break;
		case DBG_XXXXXXX02:			// IAP版本号
			wTemp = uwGetBootBV();
		break;
		case DBG_XXXXXXX03:			// 额定功率
			wTemp = sGetRatedGridPower();
		break;
		case DBG_XXXXXXX04:
			wTemp = swGetSinePeriodCntNew();
		break;
		case DBG_XXXXXXX05:
			wTemp = 5;
		break;
		case DBG_XXXXXXX06:
			wTemp = 6;
		break;
		case DBG_XXXXXXX07:			// WIFI使能信号
			wTemp = mWIFIEN;
		break;
		case DBG_XXXXXXX08:			// 待机模式
			wTemp = swGetStayStandby();
		break;
		case DBG_XXXXXXX09:			// 负载工作模式
			wTemp = swGetLoadOnSts();
		break;
		case DBG_XXXXXXX10:			// 逆变器工作模式
			wTemp = suwGetEEOutputPriority();
		break;
		case DBG_XXXXXXX11:			// BOOST辅助电源使能信号
			wTemp = mSPSEN;
		break;
		case DBG_XXXXXXX12:			// AC辅助电源使能信号
			wTemp = mAUXEN;
		break;
		case DBG_XXXXXXX13:			// DCDC控制器状态
			wTemp = suwGetLLCCtrlSts();
		break;
		case DBG_XXXXXXX14:			// DCDC频率
//			wTemp = (cCPU_FREQ/2/cDCDCPeriod);
			wTemp = (cCPU_FREQ/2/gi_wDCDCConvPWMPeriod);
		break;
		case DBG_XXXXXXX15:			// DCDC实际占空比
			wTemp = suwGetDCDCConvPWMValue();
		break;
		case DBG_XXXXXXX16:			// BUS电压参考(0.1V)
			wTemp = swGetDCDCBusVoltRef();
		break;
		case DBG_XXXXXXX17:			// BUS电流参考(0.01A)
			wTemp = swGetBusCurrFilter();
		break;
		case DBG_XXXXXXX18:			// 电池充放MOS使能
			wTemp = hoSRDRV;
		break;
		case DBG_XXXXXXX19:
			wTemp = 19;
		break;
		case DBG_XXXXXXX20:
			wTemp = 20;
		break;
		case DBG_XXXXXXX21:
			wTemp = 21;
		break;
		case DBG_XXXXXXX22:
			wTemp = 22;
		break;
		case DBG_XXXXXXX23:			// 风扇控制器状态(0性能 1平衡 2静音 3开环)
			wTemp = swGetFanWorkMode();
		break;
		case DBG_XXXXXXX24:			// 风扇控制频率(Hz)
			wTemp =  (cCPU_FREQ/2/cFanPeriod);
		break;
		case DBG_XXXXXXX25:			// 扇风控制占空比
			wTemp = swGetFanDuty();
		break;
		case DBG_XXXXXXX26:			// 风扇转速百分比
			wTemp = swGetFanDutyPct();
		break;
		case DBG_XXXXXXX27:			// 风扇堵转状态
			wTemp = swGetFanStatus();
		break;
		case DBG_XXXXXXX28:			// PV控制器状态(0待机 1使能 4开环)
			wTemp = suwGetPV1CtrlSts();
		break;
		case DBG_XXXXXXX29:			// PV_BUCK控制频率(Hz)
			wTemp = (cCPU_FREQ/2/cBuckPeriod);
		break;
		case DBG_XXXXXXX30:			// PV_BUCK占空比
			wTemp = suwGetPV1PWM();
		break;
		case DBG_XXXXXXX31:			// PV控制_MPPT电压参考(0.01V)
			wTemp = suwGetMpptVoltRef();
		break;
		case DBG_XXXXXXX32:			// PV控制_电池电压参考(0.01V)
			wTemp = suwGetPvChgBatVoltRef();
		break;
		case DBG_XXXXXXX33:			// 调试寄存器写入的PV充电目标电流(1A)
		{
			if(!swGetStayStandby())
			{
				wTemp = swGetPvChgBatCurrRef() / 10;
			}
			else
			{
				wTemp = suwGetSciPvBatChgLimit() / 10;
			}
		}
		break;
		case DBG_XXXXXXX34:			// PV控制器充电电流参考(1A)
			wTemp = suwGetPvBatChgLimit() / 10;
		break;
		case DBG_XXXXXXX35:			// PV防反MOS管
			wTemp = 0;//hoPVRLY;
		break;
		case DBG_XXXXXXX36:			// PV当前电流
			wTemp = swGetPv1BatCurrNew() * swGetBatVoltNew() / swGetPv1VoltNew();
		break;
		case DBG_XXXXXXX37:			// PV电池充电电流
			wTemp = swGetPv1BatCurrNew();
		break;
		case DBG_XXXXXXX38:			// PV负载电流前馈
			wTemp = swGetPvLoadCurrFeedWard();
		break;
		case DBG_XXXXXXX39:			// PV充电电流临时值
			wTemp = swGetPvChgBatCurrTemp();
		break;
		case DBG_XXXXXXX40:			// PV弱光吸收电路使能信号
			wTemp = mPVLOADEN;
		break;
		case DBG_XXXXXXX41:			// PV保险丝熔断使能
			wTemp = mPVFUSE;
		break;
		case DBG_XXXXXXX42:
			wTemp = 42;
		break;
		case DBG_XXXXXXX43:				// 逆变控制器状态(0待机 1开环 2闭环 3并网)
			wTemp = suwGetFBInvCtrlSts();
		break;
		case DBG_XXXXXXX44:				// 逆变频率参考
			wTemp = swGetRInvFreqNew();
		break;
		case DBG_XXXXXXX45:				// 逆变电压参考(0.1V)
			wTemp = uwGetInvRMSCtrlVolt();
		break;
		case DBG_XXXXXXX46:				// 逆变电流参考(0.01A)
			wTemp = swGetRInvCurrFilter();
		break;
		case DBG_XXXXXXX47:				// 逆变调制载波
			wTemp = swGetInvKpwm();
		break;
		case DBG_XXXXXXX48:				// 并网能量状态(0自动 1充电 2放电)
			wTemp = swGetInvFeedWorkMode();
		break;
		case DBG_XXXXXXX49:				// 并网BUS参考
			wTemp = swGetInvFeedBusVoltRef();
		break;
		case DBG_XXXXXXX50:				// 市电充电电池电流参考
			wTemp = swGetGridChgBatCurrRef()/100;
		break;
		case DBG_XXXXXXX51:				// 市电并网放电功率
			wTemp = swGetGridFeedWattRef();
		break;
		case DBG_XXXXXXX52:					// 电池侧需要的功率
			wTemp = swGetBatWattRef();
		break;
		case DBG_XXXXXXX53:					// 市电环路并网功率
			wTemp = swGetGridWattRef();
		break;
		case DBG_XXXXXXX54:					// 市电 控制的功率，正充电,负放电	
			wTemp = swGetInvCtrlPower();	
		break;
		case DBG_XXXXXXX55:					// 并网充放功率
			wTemp = swGetInvCurrTemp();
		break;
		case DBG_XXXXXXX56:					// 并网买电电流
			wTemp = swGetInvChgCurrLimit();
		break;
		case DBG_XXXXXXX57:					// 并网卖电电流
			wTemp = swGetInvFeedCurrLimit();
		break;
		case DBG_XXXXXXX58:					// 市电实际功率
			wTemp = swGetRLineWattNew();
		break;
		case DBG_XXXXXXX59:					// 负载优先时并网方向(0:Chg 1:Dsg)
			wTemp = swGetInvWorSUBGridDir();
		break;
		case DBG_XXXXXXX60:					// AC限流 使能
			wTemp = swGetACCurrLimitEn();	
		break;
		case DBG_XXXXXXX61:					// AC限流 电流 0.01A
			wTemp = swGetACCurrLimit();	
		break;
		case DBG_XXXXXXX62:					// AC限流 功率 W
			wTemp = swGetACPowerLimit();
		break;
		case DBG_XXXXXXX63:					// AC限流的实际参考功率
			wTemp = swGetACWattLimit();
		break;
		case DBG_XXXXXXX64:					// 最大馈电功率
			wTemp = swGetACFeedPowerLimit();
		break;
		case DBG_XXXXXXX65:					// 主功率负载量参考
			wTemp = swGetROpFeedWattTemp();
		break;
		case DBG_XXXXXXX66:					// OP继电器
			wTemp = hoROPRLY;
		break;
		case DBG_XXXXXXX67:					// 市电继电器
			wTemp = hoGRIDRLY;
		break;
		case DBG_XXXXXXX68:					// 最大并网功率限制(有些模式只允许并最大PV功率)
			wTemp = swGetMaxFeedPowerLimit();
		break;
		case DBG_XXXXXXX69:					// 根据市电设置充电电流得到逆变最大允许充电功率
			wTemp = swGetGridChgPowerLimitTemp();
		break;
		case DBG_XXXXXXX70:					// 继电器最大允许功率(只会在逆变充电时出现)
			wTemp = swGetwRlyChgPowerLimitTemp();
		break;
		case DBG_XXXXXXX71:					// 市电充电软起至额定功率值
			wTemp = swGetInvChgPowerLimitTemp();
		break;
		case DBG_XXXXXXX72:					// 市电放电软起至额定功率值
			wTemp = swGetInvDsgPowerLimitTemp();
		break;
		case DBG_XXXXXXX73:					// 充电电流软起临时值
			wTemp = swGetInvChgCurrLimitTemp();
		break;
		case DBG_XXXXXXX74:					// 放电电流软起临时值
			wTemp = swGetInvFeedCurrLimitTempTemp();
		break;
		case DBG_XXXXXXX75:	
			wTemp = 75;
		break;
		case DBG_XXXXXXX76:					// 逆变过温降功率
			wTemp = swGetInvTempDeratPowerLimit();
		break;
		case DBG_XXXXXXX77:					// 推挽过温降功率
			wTemp = swGetTwTempDeratPowerLimit();
		break;
		case DBG_XXXXXXX78:					// 推挽变压器温度降额功率
			wTemp = swGetTraTempDeratPowerLimit();
		break;
		case DBG_XXXXXXX79:					// 电池低压降并网功率
			wTemp = swGetBatVoltDeratPowerLimit();
		break;
		case DBG_XXXXXXX80:
			wTemp = uwGetInvWattRes();
		break;
		case DBG_XXXXXXX81:
			wTemp = 81;
		break;
		case DBG_XXXXXXX82:
			wTemp = g_wRInvDCVoltCntl;
		break;
		case DBG_XXXXXXX83:
			wTemp = 83;
		break;
		case DBG_XXXXXXX84:
			wTemp = 84;
		break;
		case DBG_XXXXXXX85:
			wTemp = 85;
		break;
		case DBG_XXXXXXX86:		// 电池最大充电功率
			wTemp = swGetBatChgPowerLimitTemp();
		break;
		case DBG_XXXXXXX87:		// 电池最大放电功率
			wTemp = swGetBatDsgPowerLimitTemp();
		break;
		case DBG_XXXXXXX88:		// 逆变过温降额电压
			wTemp = swGetInvTempDeratVoltLimit();
		break;
		case DBG_XXXXXXX89:		// 推挽温度降额电压
			wTemp = swGetTwTempDeratVoltLimit();
		break;
		case DBG_XXXXXXX90:		// 推挽变压器温度降额电压
			wTemp = swGetTraTempDeratVoltLimit();
		break;
		case DBG_XXXXXXX91:		// 电池欠压降额输出电压
			wTemp = swGetBatVoltDeratVoltLimit();
		break;
		case DBG_XXXXXXX92:		// BAT限流降额负载电压
			wTemp = swGetBatCurrDeratVoltLimit();
		break;
		case DBG_XXXXXXX93:
			wTemp = 93;
		break;
		case DBG_XXXXXXX94:
			wTemp = 94;
		break;
		case DBG_XXXXXXX95:
			wTemp = 95;
		break;
		case DBG_XXXXXXX96:	
			wTemp = suwGetBatVKp1();	// PV电池电压外环KP
		break;	
		case DBG_XXXXXXX97:	
			wTemp = suwGetBatVKi1();	// PV电池电压外环Ki
		break;	
		case DBG_XXXXXXX98:	
			wTemp = suwGetPv1VKp();		// PV电压外环Kp
		break;	
		case DBG_XXXXXXX99:	
			wTemp = suwGetPv1VKi();		// PV电压外环Ki
		break;	
		case DBG_XXXXXXX100:	
			wTemp = suwGetDCDCIKp1();		// PV电流环Kp
		break;	
		case DBG_XXXXXXX101:	
			wTemp = suwGetDCDCIKi1();		// PV电流环Ki
		break;	
		case DBG_XXXXXXX102:	
			wTemp = 102;
		break;	
		case DBG_XXXXXXX103:	
			wTemp = 103;
		break;	
		case DBG_XXXXXXX104:	
			wTemp = 104;
		break;	
		case DBG_XXXXXXX105:	
			wTemp = 105;
		break;	
		case DBG_XXXXXXX106:	
			wTemp = 106;
		break;	
		case DBG_XXXXXXX107:	
			wTemp = 107;
		break;	
		case DBG_XXXXXXX108:	
			wTemp = 108;
		break;	
		case DBG_XXXXXXX109:	
			wTemp = 109;
		break;	
		case DBG_XXXXXXX110:	
			wTemp = 110;
		break;	
		case DBG_XXXXXXX111:	
			wTemp = 111;
		break;	
		case DBG_XXXXXXX112:	
			wTemp = 112;
		break;	
		case DBG_XXXXXXX113:	
			wTemp = 113;
		break;	
		case DBG_XXXXXXX114:	
			wTemp = 114;
		break;	
		case DBG_XXXXXXX115:	
			wTemp = 115;
		break;	
		case DBG_XXXXXXX116:	
			wTemp = 116;
		break;	
		case DBG_XXXXXXX117:	
			wTemp = 117;
		break;	
		case DBG_XXXXXXX118:	
			wTemp = 118;
		break;	
		case DBG_XXXXXXX119:	
			wTemp = 119;
		break;	

		default:
			wTemp = 0xFFFF;
		break;
	}
	
	return wTemp;
}

INT8U	swTestCmdWrite(INT16U WrAddr, INT16U WrData)
{
	INT8U ret = 0;
	
	WrAddr -= DBG_CMD_BASE_ADDR;
	switch(WrAddr)
	{
		case DBG_XXXXXXX00:		
			;
		break;
		case DBG_XXXXXXX01:		
			;
		break;					
		case DBG_XXXXXXX02:		
			;
		break;
		case DBG_XXXXXXX03:	// 额定功率	
			;
		break;
		case DBG_XXXXXXX04:		
			;
		break;
		case DBG_XXXXXXX05:		
			;
		break;
		case DBG_XXXXXXX06:		
			;
		break;
		case DBG_XXXXXXX07:				// WIFI使能信号
		{
			if(WrData == true)
			{
				mWIFIENOn;
			}
			else
			{
				mWIFIENOff;
			}
		}
		break;
		case DBG_XXXXXXX08:				// 待机模式(1待机 0自动)
			if(WrData == true || WrData == false)
			{
				sSetStayStandby(WrData);
			}
		break;
		case DBG_XXXXXXX09:				// 负载工作模式	
			if(WrData <= 3)
			{
				sSetLoadOnSts(WrData);
			}
		break;
		case DBG_XXXXXXX10:				// 逆变器工作模式
			if(WrData <= cInvWorkSBU)
			{
				sSetEEOutputPriority(WrData);
				sSetEeprom1Mode(cEEPROM_SAVE_ENABLE);
			}
		break;
		case DBG_XXXXXXX11:				// 驱动辅源使能	
		{
			if(WrData == true)
			{
				mSPSENOn;
			}
			else
			{
				mSPSENOff;
			}
		}
		break;
		case DBG_XXXXXXX12:				// AC辅助电源使能信号
		{
			if(WrData == true)
			{
				mAUXENOn;
			}
			else
			{
				mAUXENOff;
			}
		}
		break;
		case DBG_XXXXXXX13:				// DCDC控制器状态
			if(WrData <= cDCDCWork)
			{
				sSetLLCCtrlSts(WrData);
			}
		break;
		case DBG_XXXXXXX14:				// DCDC频率	
			;
		break;
		case DBG_XXXXXXX15:				// DCDC实际占空比
			;
		break;
		case DBG_XXXXXXX16:				// BUS电压参考(0.1V)
			;
		break;
		case DBG_XXXXXXX17:
			;
		break;
		case DBG_XXXXXXX18:				// 电池充放MOS使能
		{
			if(WrData == true)
			{
				hoSRDRVOn;
			}
			else
			{
				hoSRDRVOff;
			}
		}
		break;
		case DBG_XXXXXXX19:		
			;
		break;
		case DBG_XXXXXXX20:		
			;
		break;
		case DBG_XXXXXXX21:		
			;
		break;
		case DBG_XXXXXXX22:		
			;
		break;
		case DBG_XXXXXXX23:				// 风扇控制器状态(0性能 1平衡 2静音 3开环)
			if(WrData <= cFanModeMax)	
			{
				sSetEEFanWorkMode(WrData);
				sSetEeprom1Mode(cEEPROM_SAVE_ENABLE);
			}
		break;
		case DBG_XXXXXXX24:				// 风扇控制频率(Hz)
			;
		break;
		case DBG_XXXXXXX25:				// 扇风控制占空比
			if(WrData <= cFanDutyMax)
			{
				sSetFanDuty(WrData);
			}
		break;
		case DBG_XXXXXXX26:				// 风扇转速百分比
			if(WrData <= 100)
			{
				sSetFanDutyPct(WrData);
			}
		break;
		case DBG_XXXXXXX27:				// 风扇堵转状态
			;	
		break;
		case DBG_XXXXXXX28:				// PV控制器状态(0待机 1使能 4开环)
			if(WrData <= cPVOpen && WrData != cPVSoft)
			{
				sSetPV1CtrlSts(WrData);
			}
		break;
		case DBG_XXXXXXX29:				// PV_BUCK控制频率(Hz)
			;
		break;
		case DBG_XXXXXXX30:				// PV_BUCK占空比
			if(WrData <= cBuckPeriod && suwGetPV1CtrlSts() == cPVOpen)		
			{
				sSetPv1PWM(WrData);
			}
		break;
		case DBG_XXXXXXX31:				// PV控制_MPPT电压参考(0.01V)
			;
		break;
		case DBG_XXXXXXX32:				// PV控制_电池电压参考(0.01V)
			if(WrData <= 400)			// 30V
			{
				sSetPvChgBatVoltRef(WrData);
			}
		break;
		case DBG_XXXXXXX33:				// 调试寄存器写入的PV充电目标电流(1A)
			if(WrData <= 90)			// 90A
			{
				sSetSciPvBatChgLimit(WrData * 10);
			}
		break;
		case DBG_XXXXXXX34:				// PV控制器充电电流参考(1A)	
			;
		break;
		case DBG_XXXXXXX35:				// PV防反管
		{
			if(WrData == true)
			{
				//hoPVRLYOn;
			}
			else
			{
				//hoPVRLYOff;
			}
		}
		break;
		case DBG_XXXXXXX36:				// PV侧当前电流
			;
		break;
		case DBG_XXXXXXX37:				// PV电池充电电流
			;
		break;
		case DBG_XXXXXXX38:				// PV负载电流前馈
			;
		break;
		case DBG_XXXXXXX39:				// PV充电电流临时值
			;
		break;
		case DBG_XXXXXXX40:				// PV弱光吸收电路使能信号
		{
			if(WrData == true)
			{
				mPVLOADENOn;
			}
			else
			{
				mPVLOADENOff;
			}
		}
		break;
		case DBG_XXXXXXX41:					// PV保险丝熔断使能		
		{
			if(WrData == true)				// OP.RLY
			{
				mPVFUSEOn;
			}
			else
			{
				mPVFUSEOff;
			}
		}
		break;
		case DBG_XXXXXXX42:
			;
		break;
		case DBG_XXXXXXX43:					// 逆变控制器状态(0待机 1开环 2闭环 3并网)
			if(WrData <= cFBInvCtrlBus)
			{
				sSetFBInvCtrlSts(WrData);
			}
		break;
		case DBG_XXXXXXX44:					// 逆变频率参考
			;
		break;
		case DBG_XXXXXXX45:					// 逆变电压参考(0.1V)
			if(WrData <= cAcVoltReal300V)	// 300V
			{
				sSetInvRMSCtrlVolt(WrData);
			}
		break;
		case DBG_XXXXXXX46:					// 逆变电流参考(0.01A)
			;
		break;
		case DBG_XXXXXXX47:					// 逆变调制载波赋值
			if(suwGetFBInvCtrlSts() == cFBInvOpenLoop)
			{
				if(WrData <= 3000)
				{
					sSetInvKpwm(WrData);
				}
			}
		break;
		case DBG_XXXXXXX48:					// 并网能量状态(0自动 1充电 2放电)
			if(WrData <= 2)
			{
				sSetInvFeedWorkMode(WrData);
			}
		break;
		case DBG_XXXXXXX49:					// 并网BUS参考
			if(WrData <= 6000)				// 600V
			{
				sSetInvFeedBusVoltRef(WrData);
			}
		break;
		case DBG_XXXXXXX50:					// 市电充电电池电流参考
			if(WrData <= 135)				// 135A
			{
				sSetGridChgBatCurrRef(WrData*100);
			}
		break;	
		case DBG_XXXXXXX51:					// 市电并网放电功率
			if(WrData <= ((INT16U)uwGetInvWattMax()))				
			{
				sSetGridFeedWattRef(WrData);
			}
		break;
		case DBG_XXXXXXX52:					// 电池侧需要的功率
			;
		break;
		case DBG_XXXXXXX53:					// 市电环路并网功率
			;
		break;
		case DBG_XXXXXXX54:					// 市电 控制的功率，正充电,负放电	
			;
		break;
		case DBG_XXXXXXX55:					// 并网充放功率			
			
		break;
		case DBG_XXXXXXX56:					// 并网买电电流				
			if(WrData <= 300)				// 30A
			{
				sSetInvChgCurrLimit(WrData);
			}
		break;
		case DBG_XXXXXXX57:					// 并网卖电电流		
			if(WrData <= 300)				// 30A
			{
				sSetInvFeedCurrLimit(WrData);
			}
		break;
		case DBG_XXXXXXX58:					// 市电实际功率
			;
		break;
		case DBG_XXXXXXX59:					// 负载优先时并网方向(0:Chg 1:Dsg)
			;
		break;
		case DBG_XXXXXXX60:		
			if(WrData <= 1)					// AC限流 使能
			{
				sSetACCurrLimitEn(WrData);
			}
		break;
		case DBG_XXXXXXX61:
			if(WrData <= 4500)				// AC限流 电流 0.01A
			{
				sSetACCurrLimit(WrData);
			}
		break;
		case DBG_XXXXXXX62:
			if(WrData <= 8000)				// AC限流 功率 W
			{
				sSetACPowerLimit(WrData);
			}
		break;
		case DBG_XXXXXXX63:					// AC限流的实际参考功率
			if(WrData <= 8000)				// AC限流 功率 W
			{
				sSetACWattLimit(WrData);
			}
		break;		
		case DBG_XXXXXXX64:					// 最大馈电功率
			;
		break;
		case DBG_XXXXXXX65:					// 主功率负载量参考
			;
		break;
		case DBG_XXXXXXX66:					// OP输出继电器(1吸合 0断开)
		{
			if(WrData == true)				// OP.RLY
			{
				sSetOPRelayOn(true);
			}
			else
			{
				sSetOPRelayOn(false);
			}
		}
		break;
		case DBG_XXXXXXX67:					// 市电接入继电器(1吸合 0断开)
		{
			if(WrData == true)				// GRID.RLY
			{
				sSetGridRelayOn(true);
			}
			else
			{
				sSetGridRelayOn(false);
			}
		}
		break;
		case DBG_XXXXXXX68:	// 最大并网功率限制(有些模式只允许并最大PV功率)
			;
		break;
		case DBG_XXXXXXX69:	// 根据市电设置充电电流得到逆变最大允许充电功率
			;
		break;
		case DBG_XXXXXXX70:	// 继电器最大允许功率(只会在逆变充电时出现)
			;
		break;
		case DBG_XXXXXXX71:	// 市电充电软起至额定功率值
			;
		break;
		case DBG_XXXXXXX72: // 市电放电软起至额定功率值
			;
		break;
		case DBG_XXXXXXX73:	// 充电电流软起临时值
			;
		break;
		case DBG_XXXXXXX74:	// 放电电流软起临时值
			;
		break;
		case DBG_XXXXXXX75:
			;
		break;
		case DBG_XXXXXXX76:	// 逆变过温降功率
			;
		break;
		case DBG_XXXXXXX77:	// 推挽过温降功率
			;
		break;
		case DBG_XXXXXXX78:	// 推挽变压器温度降额功率
			;
		break;
		case DBG_XXXXXXX79:	// 电池低压降并网功率
			;
		break;
		case DBG_XXXXXXX80:
			;
		break;
		case DBG_XXXXXXX81:
			;
		break;
		case DBG_XXXXXXX82:
			g_wRInvDCVoltCntl = WrData;
		break;
		case DBG_XXXXXXX83:
			;
		break;
		case DBG_XXXXXXX84:
			;
		break;
		case DBG_XXXXXXX85:
			;
		break;
		case DBG_XXXXXXX86:	// 电池最大充电功率
			;
		break;
		case DBG_XXXXXXX87: // 电池最大放电功率
			;
		break;
		case DBG_XXXXXXX88:	// 逆变过温降额电压
			;
		break;
		case DBG_XXXXXXX89:	// 推挽温度降额电压
			;
		break;
		case DBG_XXXXXXX90:	// 推挽变压器温度降额电压
			;
		break;
		case DBG_XXXXXXX91:	// 电池欠压降额输出电压
			;
		break;
		case DBG_XXXXXXX92:	//BAT限流降额负载电压
			;
		break;
		case DBG_XXXXXXX93:
			;
		break;
		case DBG_XXXXXXX94:
			;
		break;
		case DBG_XXXXXXX95:
			;
		break;
		case DBG_XXXXXXX96:
			sSetBatVKp1(WrData);	// PV电池电压外环KP
		break;
		case DBG_XXXXXXX97:
			sSetBatVKi1(WrData);	// PV电池电压外环Ki
		break;
		case DBG_XXXXXXX98:
			sSetPv1VKp(WrData);		// PV电压外环Kp
		break;
		case DBG_XXXXXXX99:
			sSetPv1VKi(WrData);		// PV电压外环Ki
		break;
		case DBG_XXXXXXX100:
			sSetDCDCIKp1(WrData);	// PV电流环Kp
		break;
		case DBG_XXXXXXX101:
			sSetDCDCIKi1(WrData);	// PV电流环Ki
		break;
		case DBG_XXXXXXX102:
			;
		break;
		case DBG_XXXXXXX103:
			;
		break;
		case DBG_XXXXXXX104:
			;
		break;
		case DBG_XXXXXXX105:
			;
		break;
		case DBG_XXXXXXX106:
			;
		break;
		case DBG_XXXXXXX107:
			;
		break;
		case DBG_XXXXXXX108:
			;
		break;
		case DBG_XXXXXXX109:
			;
		break;
		case DBG_XXXXXXX110:
			;
		break;
		case DBG_XXXXXXX111:
			;
		break;
		case DBG_XXXXXXX112:
			;
		break;
		case DBG_XXXXXXX113:
			;
		break;
		case DBG_XXXXXXX114:
			;
		break;
		case DBG_XXXXXXX115:
			;
		break;
		case DBG_XXXXXXX116:
			;
		break;
		case DBG_XXXXXXX117:
			;
		break;
		case DBG_XXXXXXX118:
			;
		break;
		case DBG_XXXXXXX119:
			;
		break;
		default:break;
	}
	
	return ret;
}

INT8U	sGetCellVoltDefault(INT8U bNo)
{
	INT8U	bEEDefault = false;
	
//	if((swGetEepromCellVoltAdj(bNo) == cEEBattVoltAdjDef) \
//		&& (swGetEepromCellVoltBias(bNo) == cEEBattVoltBiasDef))
//	{
//		bEEDefault = true;
//	}
	return bEEDefault;
}

void	sbBattVoltCopyToCell(void)
{
//	INT8U	bIndex;
//	
//	for(bIndex = 0; bIndex < cADC_CELL_VOLT_MAX; bIndex++)
//	{
//		sSetEepromCellVoltAdj(bIndex, swGetEepromBattVoltAdj());
//		sSetEepromCellVoltBias(bIndex, swGetEepromBattVoltBias());
//		sSetCellVoltAdj(bIndex, swGetEepromBattVoltAdj());
//		sSetCellVoltBias(bIndex, swGetEepromBattVoltBias());
//	}
//	
//	sSetEepromStaticMode(cEEPROM_SAVE_MODE_ENABLE);
}

void	sCommConnectChk(INT8U sciid, INT16U wFilter)
{
	
}

void	sEmsCommConnectChk(INT16U wFilter)
{
	if(bEmsBmsConnenctFlag == true)
	{
		if(wEmsBmsDisconnectCnt < wFilter)
		{
			wEmsBmsDisconnectCnt++;
		}
		else
		{
			wEmsBmsDisconnectCnt = 0;
			bEmsBmsConnenctFlag = false;
		}
	}
	
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT8U	sbGetCommConnected(INT8U sciid)
{
	return 0;
}

INT16U	sbGetBMSAddr(void)
{
	return g_uwBMSAddr;
}

INT8U	sbGetEMSBMSConnect(void)
{
	return bEmsBmsConnenctFlag;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetCommConnected(INT8U sciid, INT8U bStatus)
{

}

