/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define			__EEPROM_PROCESS_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include		"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/


/********************************************************************************
* Constants																		*
********************************************************************************/
const struct EepromStruct1 strEepromDefaultTable1 = 	
{
	//Control State
	1,			//	uwSetMachineID					//	0	机器地址设置
	0,			//	uwSetParaEnable 				//	1	Dsp并机使能
	0,			//	uwSetMasterSlaver				//	2	主从机设置 
	0,			//	uwSetEepromAutoWrite			//	3	Eeprom自动写入
	0,			//	uwSetSystemOutputMode			//	4	系统输出模式 0:单机 1:单相并机
	cFanPerFormanceMode,//	uwSetFanWorkMode		//	5	风机运行模式 0: 性能模式1: 平衡模式 2: 静音模式 
	1,			//	uwTurboMode 		//	6	Turbo模式使能，默认使能
	1,			//	uwAutoInvEnable 	//	7	开机自动逆变，量产默认使能，调试阶段默认不使能
	1,			//	uwDCDCOpenLoopEnable//	8	DCDC开环使能
	1,			//	uwLogoEnable		//	9	Logo使能
	0,			//	uwAdcBiasAdj		//	10	用于通信数据显示美化，例如无PV时采样到非0值时置零，0：美化 1：不美化
	0,			//	uwSetReserve11		//	11	预留
	0,			//	uwSetReserve12		//	12	预留
	0,			//	uwSetReserve13		//	13	预留
	0,			//	uwSetReserve14		//	14	预留
	
	//PV
	1250, 		//	uwSetPV1StartVolt	//	15	PV1启动电压 0.01V
	0,			//	uwSetReserve16		//	16	预留
	600,		//	uwSetPV_PowerLimit	//	17	PV_最大功率	W
	0,			//	uwSetReserve18		//	18	预留
	0,			//	uwSetReserve19		//	19	预留
	0,			//	uwSetPV_Priority	//	20	"PV能量优先级(只在SUB模式下生效）"
	1,			//	uwPVAutoInvEnable 	//	21	单PV无电池开机自动逆变使能
	0,			//	uwSetRsvd22 		//	22	预留
	
	//Battery
	3,			//	uwSetBatType		//	23	电池类型 0: 胶体电池 1: 注水电池 2: 用户自定义 3: 锂电池 
	0,			//	uwSetBatSeriesNum	//	24	电池节数
	0,			//	uwSetBatCapacity	//	25	电池容量
	0,			//	uwSetRsvd26 		//	26	预留
	1,			//	uwSetBatMode		//	27	电池模式 0:电池相关的使用SOC，1:使用电压，2:无电池
	2,			//	uwSetChargePriority //	28	充电优先级      0: 市电优先 1: PV优先2: PV和市电3: 仅PV 
	cBatVoltReal3V6*cBatSerialPcs, 	//	uwSetBatConstVolt				//	29	电池恒压充电压
	cBatVoltReal3V4*cBatSerialPcs, 	//	uwSetBatFloatVolt				//	30	电池浮充电压
	0,			//	uwSetBatFloatTime			//	31	电池恒充时间
	6000,		//	uwSetBatMaxChgCurr			//	32	电池最大充电电流限幅值 0.01A
	13500,		//	uwSetBatMaxDcgCurr			//	33	电池最大放电电流限幅值 0.01A
	6000,		//	uwSetGridChgBatCurr 		//	34	电网至电池充电电流 0.01A
	1,			//	uwSetGridChgBatTotalEnable	//	35	电网充电总使能
	20, 		//	uwSetOnGridBatAutoStartChgSOC							//	36	并网时电池自动启动充电SOC点
	80, 		//	uwSetOnGridBatExitAutoChgSOC							//	37	并网时电池自动退出充电SOC点
	cBatVoltReal2V87*cBatSerialPcs, //	uwSetOnGridBatAutoStartChgVolt		//	38	并网时电池自动启动充电电压点
	cBatVoltReal3V37*cBatSerialPcs, //	uwSetOnGridBatExitAutoChgVolt		//	39	并网时电池自动退出充电电压点
	cBatVoltReal2V87*cBatSerialPcs, //	uwSetBatACRestartVolt				//	40	电池重启AC输出电压点
	cBatVoltReal2V75*cBatSerialPcs,	//	uwSetBatLowAlarmVolt				//	41	电池低压告警电压点
	cBatVoltReal2V63*cBatSerialPcs, //	uwSetBatLowShutDownVolt 			//	42	电池低压关机电压点
	15, 		//	uwSetBatACRestartSOC	//	43	电池重启AC输出SOC点
	10, 		//	uwSetBatLowAlarmSOC 	//	44	电池低压告警SOC点
	5,			//	uwSetBatLowShutDownSOC	//	45	电池低压关机SOC点
	cBatVoltReal3V75*cBatSerialPcs,			//	uwSetBatVoltOverShut		//	46	电池过压保护点
	0,			//	uwSetBatActivateEnable	//	47	电池激活使能
	0,			//	uwSetBMSComErrEnable	//	48	BMS通讯故障使能
	0,			//	uwSetBMSProtocol		//	49	BMS协议
	0,			//	uwSetBatParaEnable		//	50	电池并联使能
	0,			//	uwSetBatTempCompensateEnable							//	51	电池温度补偿使能
	0,			//	uwEEBatEqEn 			//	52	EQ使能
	cBatVoltReal3V65*cBatSerialPcs, 		//	uwEEBatEqVolt				//	53	EQ电压
	60, 		//	uwEEBatEqTime			//	54	EQ时间
	12,		    //	uwEEBatEqTimeout		//	55	EQ超时时间
	30, 		//	uwEEBatEqInterval		//	56	EQ间隔时间
	0,			//	uwEEBatEqActImd 		//	57	立即EQ使能
	0, 			//	uwSetRsvd58				//	58	预留
	0,			//	uwSetRsvd59 			//	59	预留
	1,			//	uwBatLowVoltDerateEnable		//	60	电池低压降额使能
	0,			//	uwSetRsvd61 			//	61	预留
	0,			//	uwSetRsvd62 			//	62	预留
	0,			//	uwSetRsvd63 			//	63	预留

	//AC
	1000,		//	uwSetACOutputRatedPower //	64	机器额定功率
	2200,		//	uwSetACOutputRatedVolt	//	65	额定输出电压
	0,			//	uwSetACOutputRatedFreq	//	66	额定输出频率 0: 50Hz,  1: 60Hz
	0,			//	uwSetGridInputRange 	//	67	电网输入范围 0: APL,  1: UPS
	0,			//	uwSetOutputPriority 	//	68	输出优先级 0：市电优先，1：光伏优先，2：市电和光伏 3：调度模式
	0,			//	uwSetWorkMode			//	69	工作模式	0: 卖电优先1: 防逆流 to Load（负载优先，电池优先2: 防逆流 to CT（负载优先，电池优先)3: 调度模式
	0,			//	uwSetRsvd70 			//	70	预留
	0,			//	uwSetRsvd71 			//	71	预留
	0,			//	uwSetRsvd72 			//	72	预留
	0,			//	uwSetGridPeakShavingEnable		//	73	电网最大输入功率限制使能
	1000,		//	uwSetGridPeakShavingPower		//	74	电网最大输入功率
	1000,		//	uwSetGridPeakShavingCurr 		//  75	电网最大输入电流
	1000,		//	uwMaxFeedPower 					//	76	最大馈网功率，实际等于 uwMaxFeedPower - 200偏置 = 0W
	0,			//	uwSetRsvd77 	//	77	预留
	0,			//	uwSetRsvd78 	//	78	预留
	0,			//	uwSetRsvd79 	//	79	预留
	0,			//	uwSetRsvd80 	//	80	预留
	0,			//	uwSetRsvd81 	//	81	预留
	30, 		//	uwSetRecconectWaitTime			//	82	并网等待时间 30s
	0,			//	uwSetAnti_IslandProtectEnable	//	83	主动孤岛保护使能
	0,			//	uwSetRsvd84 					//	84	预留
	0,			//	uwSetPowerSaveMode				//	85	节能模式
	1,			//	uwPowerConversion 				//	86	功率折算使能
	1,			//	uwSetOverTempRestartEn			//	87	过温重启使能
	1,			//	uwSetOverLoadRestartEn			//	88	过载重启使能
	0,			//	uwSetOverLoadBypassEn			//	89	过载转旁路使能
	15000,		//	uwFeedToLineTime 				//	90	离网转并网时间 15s
	0,			//	uwSetRsvd91 	//	91	预留
	0,			//	uwSetRsvd92 	//	92	预留
	0,			//	uwSetRsvd93 	//	93	预留
	0,			//	uwSetRsvd94 	//	94	预留
	0,			//	uwSetRsvd95 	//	95	预留
	0,			//	uwSetRsvd96 	//	96	预留
	0,			//	uwSetRsvd97 	//	97	预留
	0,			//	uwSetRsvd98 	//	98	预留
	0,			//	uwSetRsvd99 	//	99	预留
	0,			//	uwSetRsvd100	//	100 预留
	0,			//	uwSetRsvd101	//	101 预留

	//LineProtect
	0,			//	uwSetGrid1OVValue		//	102 电网过压1段(%)
	0,			//	uwSetGrid1OVTime		//	103 "电网过压1段时间(10ms)，最大655350ms,也就是655S"
	0,			//	uwSetGrid2OVValue		//	104 电网过压2段(%)
	0,			//	uwSetGrid2OVTime		//	105 电网过压2段时间(10ms)
	0,			//	uwSetGrid3OVValue		//	106 电网过压3段(%)
	0,			//	uwSetGrid3OVTime		//	107 电网过压3段时间(10ms)
	0,			//	uwSetGrid1UVValue		//	108 电网欠压1段(%)
	0,			//	uwSetGrid1UVTime		//	109 电网欠压1段时间(10ms)
	0,			//	uwSetGrid2UVValue		//	110 电网欠压2段(%)
	0,			//	uwSetGrid2UVTime		//	111 电网欠压2段时间(10ms)
	0,			//	uwSetGrid3UVValue		//	112 电网欠压3段(%)
	0,			//	uwSetGrid3UVTime		//	113 电网欠压3段时间(10ms)
	0,			//	uwSetGrid1OFValue		//	114 电网过频1段(0.01Hz)
	0,			//	uwSetGrid1OFTime		//	115 电网过频1段时间(10ms)
	0,			//	uwSetGrid2OFValue		//	116 电网过频2段(0.01Hz)
	0,			//	uwSetGrid2OFTime		//	117 电网过频2段时间(10ms)
	0,			//	uwSetGrid3OFValue		//	118 电网过频3段(0.01Hz)
	0,			//	uwSetGrid3OFTime		//	119 电网过频3段时间(10ms)
	0,			//	uwSetGrid1UFValue		//	120 电网欠频1段(0.01Hz)
	0,			//	uwSetGrid1UFTime		//	121 电网欠频1段时间(10ms)
	0,			//	uwSetGrid2UFValue		//	122 电网欠频2段(0.01Hz)
	0,			//	uwSetGrid2UFTime		//	123 电网欠频2段时间(10ms)
	0,			//	uwSetGrid3UFValue		//	124 电网欠频3段(0.01Hz)
	0,			//	uwSetGrid3UFTime		//	125 电网欠频3段时间(10ms)
	0,			//	uwSetRsvd126			//	126 预留
	0,			//	uwSetRsvd127			//	127 预留
	0,			//	uwSetRsvd128			//	128 预留
	0,			//	uwSetRsvd129			//	129 预留
	0,			//	uwSetRsvd130			//	130 预留
	0,			//	uwSetRsvd131			//	131 预留
	
	//ECO
	0,			//	uwSetECO_TimeOfUse			//	132 经济模式使能
	0,			//	uwSetECO_EffectiveWeek		//	133 生效星期
	0,			//	uwSetECO1_GridChargeEnable	//	134 规则1电网充电使能
	0,			//	uwSetECO1_GenChargeEnable	//	135 规则1油机充电使能
	0,			//	uwSetECO1_StartTime 		//	136 规则1起始时间
	0,			//	uwSetECO1_StopTime			//	137 规则1结束时间
	0,			//	uwSetECO1_Volt				//	138 规则1目标电压
	0,			//	uwSetECO1_SOC				//	139 规则1目标SOC（BMS连接采用）
	0,			//	uwSetECO1_Power 			//	140 规则1放电功率
	0,			//	uwSetECO1_WorkModeSet		//	141 规则1工作模式设定
	0,			//	uwSetECO2_GridChargeEnable	//	142 规则2电网充电使能
	0,			//	uwSetECO2_GenChargeEnable	//	143 规则2油机充电使能
	0,			//	uwSetECO2_StartTime 		//	144 规则2起始时间
	0,			//	uwSetECO2_StopTime			//	145 规则2结束时间
	0,			//	uwSetECO2_Volt				//	146 规则2目标电压
	0,			//	uwSetECO2_SOC				//	147 规则2目标SOC（BMS连接采用）
	0,			//	uwSetECO2_Power 			//	148 规则2放电功率
	0,			//	uwSetECO2_WorkModeSet		//	149 规则2工作模式设定
	0,			//	uwSetECO3_GridChargeEnable	//	150 规则3电网充电使能
	0,			//	uwSetECO3_GenChargeEnable	//	151 规则3油机充电使能
	0,			//	uwSetECO3_StartTime 		//	152 规则3起始时间
	0,			//	uwSetECO3_StopTime			//	153 规则3结束时间
	0,			//	uwSetECO3_Volt				//	154 规则3目标电压
	0,			//	uwSetECO3_SOC				//	155 规则3目标SOC（BMS连接采用）
	0,			//	uwSetECO3_Power 			//	156 规则3放电功率
	0,			//	uwSetECO3_WorkModeSet		//	157 规则3工作模式设定
	0,			//	uwSetECO4_GridChargeEnable	//	158 规则4电网充电使能
	0,			//	uwSetECO4_GenChargeEnable	//	159 规则4油机充电使能
	0,			//	uwSetECO4_StartTime 		//	160 规则4起始时间
	0,			//	uwSetECO4_StopTime			//	161 规则4结束时间
	0,			//	uwSetECO4_Volt				//	162 规则4目标电压
	0,			//	uwSetECO4_SOC				//	163 规则4目标SOC（BMS连接采用）
	0,			//	uwSetECO4_Power 			//	164 规则4放电功率
	0,			//	uwSetECO4_WorkModeSet		//	165 规则4工作模式设定
	0,			//	uwSetECO5_GridChargeEnable	//	166 规则5电网充电使能
	0,			//	uwSetECO5_GenChargeEnable	//	167 规则5油机充电使能
	0,			//	uwSetECO5_StartTime 		//	168 规则5起始时间
	0,			//	uwSetECO5_StopTime			//	169 规则5结束时间
	0,			//	uwSetECO5_Volt				//	170 规则5目标电压
	0,			//	uwSetECO5_SOC				//	171 规则5目标SOC（BMS连接采用）
	0,			//	uwSetECO5_Power 			//	172 规则5放电功率
	0,			//	uwSetECO5_WorkModeSet		//	173 规则5工作模式设定
	0,			//	uwSetECO6_GridChargeEnable	//	174 规则6电网充电使能
	0,			//	uwSetECO6_GenChargeEnable	//	175 规则6油机充电使能
	0,			//	uwSetECO6_StartTime 		//	176 规则6起始时间
	0,			//	uwSetECO6_StopTime			//	177 规则6结束时间
	0,			//	uwSetECO6_Volt				//	178 规则6目标电压
	0,			//	uwSetECO6_SOC				//	179 规则6目标SOC（BMS连接采用）
	0,			//	uwSetECO6_Power 			//	180 规则6放电功率
	0,			//	uwSetECO6_WorkModeSet		//	181 规则6工作模式设定
	0,			//	uwSetRsvd182				//	182 预留
	0,			//	uwSetRsvd183				//	183 预留
	0xAAAA, 	//	uwFlag1 					//	184 EEPROM标志
	0			//	uwEECheckCRC1				//	185 CRC校验
};

const struct EepromStruct2 strEepromDefaultTable2 = 	
{
	4096,		//uwEEPV1VoltAdj	//	186 PV1电压校准系数
	0,			//uwEEPV1VoltBias 	//	187 PV1电压校准偏置
	4096,		//uwEEPV2VoltAdj	//	188 PV2电压校准系数
	0,			//uwEEPV2VoltBias 	//	189 PV2电压校准偏置
	4096,		//uwEEPV1BatCurrAdj	//	190 PV1电流校准系数
	0,			//uwEEPV1BatCurrBias//	191 PV1电流校准偏置
	4096,		//uwEEPV2BatCurrAdj	//	192 PV2电流校准系数
	0,			//uwEEPV2BatCurrBias//	193 PV2电流校准偏置
	4096,		//uwEEBatVoltAdj	//	194 电池电压校准系数
	0,			//uwEEBatVoltBias 	//	195 电池电压校准偏置
	4096,		//uwEEBatCurrAdj	//	196 电池电流校准系数
	0,			//uwEEBatCurrBias 	//	197 电池电流校准偏置
	4096,		//uwEEBUSVoltAdj	//	198 Bus电压校准系数
	0,			//uwEEBUSVoltBias 	//	199 Bus电压校准偏置
	4096,		//uwEEBUSCurrAdj	//	200 Bus电流校准系数
	0,			//uwEEBUSCurrBias 	//	201 Bus电流校准偏置
	4096,		//uwEEInvVoltAdj	//	202 逆变电压校准系数
	0,			//uwEEInvVoltBias 	//	203 逆变电压校准偏置
	4096,		//uwEEInvCurrAdj	//	204 逆变电流校准系数
	0,			//uwEEInvCurrBias 	//	205 逆变电流校准偏置
	4096,		//uwEEGridVoltAdj 	//	206 电网电压校准系数
	0,			//uwEEGridVoltBias	//	207 电网电压校准偏置
	4096,		//uwEEGridCurrAdj 	//	208 电网电流校准系数
	0,			//uwEEGridCurrBias	//	209 电网电流校准偏置
	4096,		//uwEEOPVoltAdj		//	210 输出电压校准系数
	0,			//uwEEOpVoltBias	//	211 输出电压校准偏置
	4096,		//uwEEOPCurrAdj		//	212 输出电流校准系数
	0,			//uwEEOpCurrBias	//	213 输出电流校准偏置
	0,			//uwEEDischargeEneyCoeffH 	//	214 放电量校准高位
	0,			//uwEEDischargeEneyCoeffL 	//	215 放电量校准低位
	0,			//uwEEchargeEneyCoeffH		//	216 充电量校准高位
	0,			//uwEEchargeEneyCoeffL		//	217 充电量校准低位
	0,			//uwSetRsvd218		//	218 预留
	0,			//uwSetRsvd219		//	219 预留
	0,			//uwSetRsvd220		//	220 预留
	0,			//uwSetRsvd221		//	221 预留
	0,			//uwSetRsvd222		//	222 预留
	0,			//uwSetRsvd223		//	223 预留
	0,			//uwSetRsvd224		//	224 预留
	0,			//uwSetRsvd225		//	225 预留
	0,			//uwSetRsvd226		//	226 预留
	0,			//uwSetRsvd227		//	227 预留
	0,			//uwSetRsvd228		//	228 预留
	0,			//uwSetRsvd229		//	229 预留
	0,			//uwSetRsvd230		//	230 预留
	0,			//uwSetRsvd231		//	231 预留
	0,			//uwSetRsvd232		//	232 预留
	0,			//uwSetRsvd233		//	233 预留
	0xAAAA,		//uwFlag2 			//	234 EEPROM标志
	0			//uwEECheckCRC2		//	235 CRC校验
};

const struct EepromStruct3 strEepromDefaultTable3 = 	
{
	0,			//uwATE_SN1					//	236 机器序列号1
	0,			//uwATE_SN2					//	237 机器序列号2
	0,			//uwATE_SN3					//	238 机器序列号3
	0,			//uwATE_SN4					//	239 机器序列号4
	0,			//uwATE_SN5					//	240 机器序列号5
	18,			//uwATE_SNLen 				//	241 机器序列号长度
	0,			//uwATE_DispHwVer 			//	242 ATE写显示板版本号
	0,			//uwATE_CtrlHwVer 			//	243 ATE写控制板版本号
	0,			//uwATE_PowerHwVer			//	244 ATE写功率板版本号
	0,			//uwATE_UpdateFW			//	245 升级固件		1:升级模式
	0,			//uwATE_ResetSystem			//	246 复位重启
	0,			//uwATE_EEDefault 			//	247 EE恢复默认值
	0,			///uwATE_AgingMode 			//	248 老化模式
	0,			//uwATE_RemoteOnOff			//	249 远程控制开关
	0,			//uwATE_EEFactory 			//	250 EE恢复出厂设置
	0,			//uwATE_AgingBattVolt 		//	251 老化电池启动电压
	0,			//uwATE_AgingBattCurr 		//	252 老化电池放电电流
	0,			//uwATE_AgingPVPower		//	253 老化最大PV功率
	0,			//uwATE_AgingInvPower 		//	254 老化最大逆变功率
	0,			//uwATE_MPPTVoltCntl		//	255 MPPT电压点控制
	0,			//uwATE_E_totalClr			//	256 发电量发电时间清零设置
	0,			//uwATE_SafetyCode			//	257 安规设置
	0,			//uwATE_ISOsetting			//	258 绝缘阻抗设置
	0,			//uwATE_EleMeterProc		//	259 电表协议选择
	0,			//uwATE_ExCommBps 			//	260 Wifi通讯地址和波特率
	0,			//uwATE_EleMeterBps_Parity	//	261 与电表通讯波特率和校验位
	0,			//uwATE_EleMeterAddr		//	262 与电表通讯地址
	0,			//uwATE_EleMeterWREn		//	263 电表使能写，禁止读
	1,			//uwATE_EleMeterDataRegAddr //	264 电表Modbus地址
	0,			//uwATE_EleMeterData		//	265 电表数据
	0,			//uwATE_485CommBps			//	266 485通讯地址和波特率
	1,			//uwMenuRtnDftPageEn		//	267 自动返回到显示屏幕的第一页
	0,			//uwSetLCDBacklight			//	268 LCD背光
	1,			//uwSetBuzzerBeep 			//	269 蜂鸣器
	0,			//uwSetBmsBagAddr 			//	270 电池包地址
	0,			//uwSetClearEventLog		//	271 清除事件记录
	0,			//uwSetEventLogFunc			//	272 事件记录功能
	0,			//uwSetFaultLogFunc			//	273 故障记录功能
	0,			//uwSetLogType				//	274 Log查询类型
	0,			//uwSetLogIndex				//	275 Log索引
	0xAAAA,		//uwFlag3 					//	276 EEPROM标志
	0			//uwEECheckCRC3				//	277 CRC校验
};

/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16U g_uwFaultCode;

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
INT8U bEepromTaskPrio[cEEPROM_TASK_MAX];
INT8U bEepromTaskEvent[cEEPROM_TASK_MAX];

UNEEpromCfg1 uEepromCfg1;
UNEEpromCfg2 uEepromCfg2;
UNEEpromCfg3 uEepromCfg3;
UNEEpromCfg1 uEepromCfg1Temp;
UNEEpromCfg2 uEepromCfg2Temp;
UNEEpromCfg3 uEepromCfg3Temp;

union EEPROM_STATUS_TABLE
{
	struct EEPROM_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U bRwEnable:1;
		INT16U bRwBusy:1;
		INT16U bSecureLock:1;
		INT16U bSecureLockRst:1;
		
		// BIT4-7
		INT16U bEE1Mode:2;	// 00禁止,01需要保存,10延时计数,11执行保存
		INT16U bEE2Mode:2;	// 00禁止,01需要保存,10延时计数,11执行保存
		
		// BIT8-11
		INT16U bEE3Mode:2;	// 00禁止,01需要保存,10延时计数,11执行保存
		INT16U bEE4Mode:2;	// 00禁止,01需要保存,10延时计数,11执行保存
		
		// BIT12-15
		INT16U bRsvd4:4;
	} bits;
	INT16U data;
} fEepromStatus;
INT8U bEepromReadFlag;
INT8U bEepromSaveFlag;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sEepromTaskInitial(INT8U bTask, INT8U bPrio, INT8U bEvent);
void	sEepromDefaultWrite(INT16U *pEEpromTable, const INT16U *pDefaultTable, INT16U wIndex, INT16U wLen);
INT8U	sbEECheckCRC1(INT16U wLen);
INT8U	sbEECheckCRC2(INT16U wLen);
INT8U	sbEECheckCRC3(INT16U wLen);

INT16U	wTestEepromLen1 = cEepromTotalLength1;
INT16U	wTestEepromLen2 = cEepromTotalLength2;
INT16U	wTestEepromLen3 = cEepromTotalLength3;
/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sEepromInitial(void)
{
	fEepromStatus.data = 0x0000;
	bEepromReadFlag = 0;
	bEepromSaveFlag = 0;
	
	sSetEepromSecureLock(true);
	sSetEepromRwEnable(true);
	
	sEepromSoftwareReset();
	sEepromRead1();
	sEepromRead2();
	sEepromRead3();
	sEepromDataRangeChk();
	
	sEepromTaskInitial(cEEPROM_TASK1, cPrioInterface, eI2CEEpromUserSave);
	sEepromTaskInitial(cEEPROM_TASK2, cPrioInterface, eI2CEEpromFacSave);
	sEepromTaskInitial(cEEPROM_TASK3, cPrioInterface, eI2CEEpromUser2Save);
}

void	sEepromTaskInitial(INT8U bTask, INT8U bPrio, INT8U bEvent)
{
	bEepromTaskPrio[bTask] = bPrio;
	bEepromTaskEvent[bTask] = bEvent;
}

void	sEepromRead1(void)
{
	INT8U bCnt;
	
	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom1Address,cEepromTotalLength1,(INT8U *)uEepromCfg1.wEepromCfg1) == cEepromSuccess)
		{
			if(uEepromCfg1.EepromStructCfg1.strECOMode.uwFlag1 == 0xAAAA)
			{
				if(sbEECheckCRC1(cEepromTotalLength1/2 - 1) == true)
				{
					bEepromReadFlag |= 0x01;
					return;
				}
			}
		}
	}while(--bCnt != 0);
	
	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom1BackupAddress,cEepromTotalLength1,(INT8U *)uEepromCfg1.wEepromCfg1) == cEepromSuccess)
		{
			if(uEepromCfg1.EepromStructCfg1.strECOMode.uwFlag1 == 0xAAAA)
			{
				if(sbEECheckCRC1(cEepromTotalLength1/2 - 1) == true)
				{
					bEepromReadFlag |= 0x02;
					return;
				}
			}
		}
	}while(--bCnt != 0);
	
	sEepromDefaultSave1();
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
	sEepromSave1();
}

void	sEepromRead2(void)
{
	INT8U bCnt;
	
	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom2Address,cEepromTotalLength2,(INT8U *)uEepromCfg2.wEepromCfg2) == cEepromSuccess)
		{
			if(uEepromCfg2.EepromStructCfg2.uwFlag2 == 0xAAAA)
			{
				if(sbEECheckCRC2(cEepromTotalLength2/2 - 1) == true)
				{
					bEepromReadFlag |= 0x04;
					return;
				}
			}
		}
	}while(--bCnt != 0);
	
	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom2BackupAddress,cEepromTotalLength2,(INT8U *)uEepromCfg2.wEepromCfg2) == cEepromSuccess)
		{
			if(uEepromCfg2.EepromStructCfg2.uwFlag2 == 0xAAAA)
			{
				if(sbEECheckCRC2(cEepromTotalLength2/2 - 1) == true)
				{
					bEepromReadFlag |= 0x08;
					return;
				}
			}
		}
	}while(--bCnt != 0);
	
	sEepromDefaultSave2();
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
	sEepromSave2();
}

void	sEepromRead3(void)
{
	INT8U bCnt;
	
	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom3Address,cEepromTotalLength3,(INT8U *)uEepromCfg3.wEepromCfg3) == cEepromSuccess)
		{
			if(uEepromCfg3.EepromStructCfg3.uwFlag3 == 0xAAAA)
			{
				if(sbEECheckCRC3(cEepromTotalLength3/2 - 1) == true)
				{
					bEepromReadFlag |= 0x10;
					return;
				}
			}
		}
	}while(--bCnt != 0);

	bCnt = 3;
	do
	{
		if(sbEepromRead(cEeprom3BackupAddress,cEepromTotalLength3,(INT8U *)uEepromCfg3.wEepromCfg3) == cEepromSuccess)
		{
			if(uEepromCfg3.EepromStructCfg3.uwFlag3 == 0xAAAA)
			{
				if(sbEECheckCRC3(cEepromTotalLength3/2 - 1) == true)
				{
					bEepromReadFlag |= 0x20;
					return;
				}
			}
		}
	}while(--bCnt != 0);
	
	sEepromDefaultSave3();
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
	sEepromSave3();
}

void	sEepromSave1(void)
{
	INT16U i, CRC;
	INT16U *pbSrc, *pbDes;
	INT8U bCnt;
	
	uEepromCfg1.EepromStructCfg1.strECOMode.uwEECheckCRC1 = 0;
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg1.wEepromCfg1, (cEepromTotalLength1/2 - 1));
	uEepromCfg1.EepromStructCfg1.strECOMode.uwEECheckCRC1 = CRC;
	
	pbSrc = (INT16U *)&uEepromCfg1.wEepromCfg1;
	pbDes = (INT16U *)&uEepromCfg1Temp.wEepromCfg1;
	for(i = 0; i < cEepromTotalLength1/2; i++)
	{
		*pbDes = *pbSrc;
		pbSrc++;
		pbDes++;
	}
	
	bCnt = 3;
	do
	{
		if(cEepromSuccess == sbEepromWrite(cEeprom1Address,cEepromTotalLength1,(INT8U *)uEepromCfg1Temp.wEepromCfg1))
		{
			if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom1Address,cEepromTotalLength1,uEepromCfg1Temp.EepromStructCfg1.strECOMode.uwEECheckCRC1))
			{
				bEepromSaveFlag |= 0x01;
				
				bCnt = 3;
				do
				{
					if(cEepromSuccess == sbEepromWrite(cEeprom1BackupAddress,cEepromTotalLength1,(INT8U *)uEepromCfg1Temp.wEepromCfg1))
					{
						if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom1BackupAddress,cEepromTotalLength1,uEepromCfg1Temp.EepromStructCfg1.strECOMode.uwEECheckCRC1))
						{
							bEepromSaveFlag |= 0x02;
							return;
						}
					}
				}while(--bCnt != 0);
				
				g_uwFaultCode = cEEPROMFault;
				T_FAULT_DATA.bits.bEepromFault = true;
				OSEventSend(cPrioSuper, eSuperFault);
				return;
			}
		}
	}while(--bCnt != 0);
	
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
}

void	sEepromSave2(void)
{
	INT16U i, CRC;
	INT16U *pbSrc, *pbDes;
	INT8U bCnt;
	
	uEepromCfg2.EepromStructCfg2.uwEECheckCRC2 = 0;
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg2.wEepromCfg2, (cEepromTotalLength2/2 - 1));
	uEepromCfg2.EepromStructCfg2.uwEECheckCRC2 = CRC;	
	
	pbSrc = (INT16U *)&uEepromCfg2.wEepromCfg2;
	pbDes = (INT16U *)&uEepromCfg2Temp.wEepromCfg2;
	for(i = 0; i < cEepromTotalLength2/2; i++)
	{
		*pbDes = *pbSrc;
		pbSrc++;
		pbDes++;
	}
	
	bCnt = 3;
	do
	{
		if(cEepromSuccess == sbEepromWrite(cEeprom2Address,cEepromTotalLength2,(INT8U *)uEepromCfg2Temp.wEepromCfg2))
		{
			if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom2Address,cEepromTotalLength2,uEepromCfg2Temp.EepromStructCfg2.uwEECheckCRC2))
			{
				bEepromSaveFlag |= 0x04;
				
				bCnt = 3;
				do
				{
					if(cEepromSuccess == sbEepromWrite(cEeprom2BackupAddress,cEepromTotalLength2,(INT8U *)uEepromCfg2Temp.wEepromCfg2))
					{
						if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom2BackupAddress,cEepromTotalLength2,uEepromCfg2Temp.EepromStructCfg2.uwEECheckCRC2))
						{
							bEepromSaveFlag |= 0x08;
							return;
						}
					}
				}while(--bCnt != 0);
				
				g_uwFaultCode = cEEPROMFault;
				T_FAULT_DATA.bits.bEepromFault = true;
				OSEventSend(cPrioSuper, eSuperFault);
				return;
			}
		}
	}while(--bCnt != 0);
	
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
}

void	sEepromSave3(void)
{
	INT16U i, CRC;
	INT16U *pbSrc, *pbDes;
	INT8U bCnt;
	
	uEepromCfg3.EepromStructCfg3.uwEECheckCRC3 = 0;
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg3.wEepromCfg3, (cEepromTotalLength3/2 - 1));
	uEepromCfg3.EepromStructCfg3.uwEECheckCRC3 = CRC;	
	
	pbSrc = (INT16U *)&uEepromCfg3.wEepromCfg3;
	pbDes = (INT16U *)&uEepromCfg3Temp.wEepromCfg3;
	for(i = 0; i < cEepromTotalLength3/2; i++)
	{
		*pbDes = *pbSrc;
		pbSrc++;
		pbDes++;
	}
	
	bCnt = 3;
	do
	{
		if(cEepromSuccess == sbEepromWrite(cEeprom3Address,cEepromTotalLength3,(INT8U *)uEepromCfg3Temp.wEepromCfg3))
		{
			if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom3Address,cEepromTotalLength3,uEepromCfg3Temp.EepromStructCfg3.uwEECheckCRC3))
			{
				bEepromSaveFlag |= 0x10;
				bCnt = 3;
				do
				{
					if(cEepromSuccess == sbEepromWrite(cEeprom3BackupAddress,cEepromTotalLength3,(INT8U *)uEepromCfg3Temp.wEepromCfg3))
					{
						if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom3BackupAddress,cEepromTotalLength3,uEepromCfg3Temp.EepromStructCfg3.uwEECheckCRC3))
						{
							bEepromSaveFlag |= 0x20;
							return;
						}
					}
				}while(--bCnt != 0);
				
				g_uwFaultCode = cEEPROMFault;
				T_FAULT_DATA.bits.bEepromFault = true;
				OSEventSend(cPrioSuper, eSuperFault);
				return;
			}
		}
	}while(--bCnt != 0);
	
	g_uwFaultCode = cEEPROMFault;
	T_FAULT_DATA.bits.bEepromFault = true;
	OSEventSend(cPrioSuper, eSuperFault);
}

void	sEepromDefaultSave1(void)
{
	sEepromDefaultWrite((INT16U *)uEepromCfg1.wEepromCfg1, (const INT16U *)&strEepromDefaultTable1, 0, cEepromTotalLength1/2 - 1);
}

void	sEepromDefaultSave2(void)
{
	sEepromDefaultWrite((INT16U *)uEepromCfg2.wEepromCfg2, (const INT16U *)&strEepromDefaultTable2, 0, cEepromTotalLength2/2 - 1);
}

void	sEepromDefaultSave3(void)
{
	sEepromDefaultWrite((INT16U *)uEepromCfg3.wEepromCfg3, (const INT16U *)&strEepromDefaultTable3, 0, cEepromTotalLength3/2 - 1);
}

void	sEepromDefaultWrite(INT16U *pEEpromTable, const INT16U *pDefaultTable, INT16U wIndex, INT16U wLen)
{
	INT16U i, *pTemp;
	
	pTemp = pEEpromTable;
	for(i = 0; i < wLen; i ++)
	{
		*(pTemp + wIndex) = *(pDefaultTable + wIndex);
		wIndex++;
	}
}

INT8U	sbEECheckCRC1(INT16U wLen)
{
	INT16U CRC = 0;
	
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg1.wEepromCfg1, wLen);
	if( CRC == uEepromCfg1.EepromStructCfg1.strECOMode.uwEECheckCRC1)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

INT8U	sbEECheckCRC2(INT16U wLen)
{
	INT16U CRC = 0;
	
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg2.wEepromCfg2, wLen);
	if( CRC == uEepromCfg2.EepromStructCfg2.uwEECheckCRC2)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

INT8U	sbEECheckCRC3(INT16U wLen)
{
	INT16U CRC = 0;
	
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg3.wEepromCfg3, wLen);
	if( CRC == uEepromCfg3.EepromStructCfg3.uwEECheckCRC3)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

void	sEepromDataRangeChk(void)
{
//	INT16U wTemp;
	INT8U bEEPROM1Flag = false;
	INT8U bEEPROM2Flag = false;
	INT8U bEEPROM3Flag = false;
	
	// EEPROM1
	if(suwGetEEMachineID() != 1)
	{
		sSetEEMachineID(strEepromDefaultTable1.strControlState.uwSetMachineID);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEEParaEnable() != 0)
	{
		sSetEEParaEnable(strEepromDefaultTable1.strControlState.uwSetParaEnable);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEEMasterSlaver() != 0)
	{
		sSetEEMasterSlaver(strEepromDefaultTable1.strControlState.uwSetMasterSlaver);
		bEEPROM1Flag = true;
	}

	if((suwGetEEAutoWrite() != 0) && (suwGetEEAutoWrite() != 1))
	{
		sSetEEAutoWrite(strEepromDefaultTable1.strControlState.uwSetEepromAutoWrite);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEESystemOutputMode() != 0)
	{
		sSetEESystemOutputMode(strEepromDefaultTable1.strControlState.uwSetSystemOutputMode);
		bEEPROM1Flag = true;
	}
	if((suwGetEEFanWorkMode() != cFanPerFormanceMode) && (suwGetEEAutoWrite() != cFanPerSilentMode))
	//if(suwGetEEFanWorkMode() > cFanModeMax)
	{
		sSetEEFanWorkMode(strEepromDefaultTable1.strControlState.uwSetFanWorkMode);
		bEEPROM1Flag = true;
	}
	
	if((suwGetEETurboMode() != 0) && (suwGetEETurboMode() != 1))
	{
		sSetEETurboMode(strEepromDefaultTable1.strControlState.uwTurboMode);
		bEEPROM1Flag = true;
	}	

	if((suwGetEEAutoInvEnable() != 0) && (suwGetEEAutoInvEnable() != 1))
	{
		sSetEEAutoInvEnable(strEepromDefaultTable1.strControlState.uwAutoInvEnable);
		bEEPROM1Flag = true;
	}	

	if((suwGetEEDCDCOpenLoopEnable() != 0) && (suwGetEEDCDCOpenLoopEnable() != 1))
	{
		sSetEEDCDCOpenLoopEnable(strEepromDefaultTable1.strControlState.uwDCDCOpenLoopEnable);
		bEEPROM1Flag = true;
	}

	if((suwGetEELogoEnable() != 0) && (suwGetEELogoEnable() != 1))
	{
		sSetEELogoEnable(strEepromDefaultTable1.strControlState.uwLogoEnable);
		bEEPROM1Flag = true;
	}

	if((suwGetEEAdcBiasAdj() != 0) && (suwGetEEAdcBiasAdj() != 1))
	{
		sSetEEAdcBiasAdj(strEepromDefaultTable1.strControlState.uwAdcBiasAdj);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve11() != 0)
	{
		sSetEEReserve11(strEepromDefaultTable1.strControlState.uwSetReserve11);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve12() != 0)
	{
		sSetEEReserve12(strEepromDefaultTable1.strControlState.uwSetReserve12);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve13() != 0)
	{
		sSetEEReserve13(strEepromDefaultTable1.strControlState.uwSetReserve13);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve14() != 0)
	{
		sSetEEReserve14(strEepromDefaultTable1.strControlState.uwSetReserve14);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEEPV1StartVolt() < (uwGetMpptPvVoltMax()*10))
	{
		sSetEEPV1StartVolt(strEepromDefaultTable1.strPvData.uwSetPV1StartVolt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve16() != 0)
	{
		sSetEEReserve16(strEepromDefaultTable1.strPvData.uwSetReserve16);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEEPV_PowerLimit() > uwGetPvPowerMax())
	{
		sSetEEPV_PowerLimit(strEepromDefaultTable1.strPvData.uwSetPV_PowerLimit);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve18() != 0)
	{
		sSetEEReserve18(strEepromDefaultTable1.strPvData.uwSetReserve18);
		bEEPROM1Flag = true;
	}

	if(suwGetEEReserve19() != 0)
	{
		sSetEEReserve19(strEepromDefaultTable1.strPvData.uwSetReserve19);
		bEEPROM1Flag = true;
	}

	if(suwGetEEPV_Priority() > 2)
	{
		sSetEEPV_Priority(strEepromDefaultTable1.strPvData.uwSetPV_Priority);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPVAutoInvEnable() != 0) && (suwGetEEPVAutoInvEnable() != 1))
	{
		sSetEEPVAutoInvEnable(strEepromDefaultTable1.strPvData.uwPVAutoInvEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd22() != 0)
	{
		sSetEERsvd22(strEepromDefaultTable1.strPvData.uwSetRsvd22);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatType() > cBatType_MAX)
	{
		sSetEEBatType(strEepromDefaultTable1.strBatData.uwSetBatType);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEBatSeriesNum() > 2)
//	{
//		sSetEEBatSeriesNum(strEepromDefaultTable1.strBatData.uwSetBatSeriesNum);
//		bEEPROM1Flag = true;
//	}

	if(suwGetEEBatCapacity() > 0)
	{
		sSetEEBatCapacity(strEepromDefaultTable1.strBatData.uwSetBatCapacity);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd26() != 0)
	{
		sSetEERsvd26(strEepromDefaultTable1.strBatData.uwSetRsvd26);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatMode() > 2)
	{
		sSetEEBatMode(strEepromDefaultTable1.strBatData.uwSetBatMode);
		bEEPROM1Flag = true;
	}

	if(suwGetEEChargePriority() > cBatMode_MAX)
	{
		sSetEEChargePriority(strEepromDefaultTable1.strBatData.uwSetChargePriority);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEBatConstVolt() > (cBatVoltReal15V*uwGetBatSerialPcs()) \
//		|| suwGetEEBatConstVolt() < (cBatVoltReal12V*uwGetBatSerialPcs()))
//	{
//		sSetEEBatConstVolt(strEepromDefaultTable1.strBatData.uwSetBatConstVolt);
//		bEEPROM1Flag = true;
//	}
//
//	if(suwGetEEBatFloatVolt() > (cBatVoltReal15V*uwGetBatSerialPcs()) \
//		|| suwGetEEBatFloatVolt() < (cBatVoltReal12V*uwGetBatSerialPcs()))
//	{
//		sSetEEBatFloatVolt(strEepromDefaultTable1.strBatData.uwSetBatFloatVolt);
//		bEEPROM1Flag = true;
//	}

	if(suwGetEEBatFloatTime() > 100)		//100min
	{
		sSetEEBatFloatTime(strEepromDefaultTable1.strBatData.uwSetBatFloatTime);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEBatMaxChgCurr() > (uwGetSettingMaxChgCurr()*100))	
//	{
//		sSetEEBatMaxChgCurr(strEepromDefaultTable1.strBatData.uwSetBatMaxChgCurr);
//		bEEPROM1Flag = true;
//	}

//	if(suwGetEEBatMaxDcgCurr() > (uwGetSettingMaxDchgCurr()*100))	
//	{
//		sSetEEBatMaxDcgCurr(strEepromDefaultTable1.strBatData.uwSetBatMaxDcgCurr);
//		bEEPROM1Flag = true;
//	}
//
//	if(suwGetEEGridChgBatCurr() > (uwGetSettingMaxACChgCurr()*100))	
//	{
//		sSetEEGridChgBatCurr(strEepromDefaultTable1.strBatData.uwSetGridChgBatCurr);
//		bEEPROM1Flag = true;
//	}

	if((suwGetEEGridChgBatTotalEnable() != 0) && (suwGetEEGridChgBatTotalEnable() != 1))
	{
		sSetEEGridChgBatTotalEnable(strEepromDefaultTable1.strBatData.uwSetGridChgBatTotalEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEOnGridBatAutoStartChgSOC() > 100) 
	{
		sSetEEOnGridBatAutoStartChgSOC(strEepromDefaultTable1.strBatData.uwSetOnGridBatAutoStartChgSOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEOnGridBatExitAutoChgSOC() > 100) 
	{
		sSetEEOnGridBatExitAutoChgSOC(strEepromDefaultTable1.strBatData.uwSetOnGridBatExitAutoChgSOC);
		bEEPROM1Flag = true;
	}

//	if((suwGetEEOnGridBatAutoStartChgVolt() > cBatVoltReal15V * uwGetBatSerialPcs()) \
//		|| (suwGetEEOnGridBatAutoStartChgVolt() < cBatVoltReal10V * uwGetBatSerialPcs()) 
//	{
//		sSetEEOnGridBatAutoStartChgVolt(strEepromDefaultTable1.strBatData.uwSetOnGridBatAutoStartChgVolt);
//		bEEPROM1Flag = true;
//	}

//	if((suwGetEEOnGridBatExitAutoChgVolt() > cBatVoltReal15V * uwGetBatSerialPcs()) \
//		|| (suwGetEEOnGridBatExitAutoChgVolt() < cBatVoltReal10V * uwGetBatSerialPcs()) 
//	{
//		sSetEEOnGridBatExitAutoChgVolt(strEepromDefaultTable1.strBatData.uwSetOnGridBatExitAutoChgVolt);
//		bEEPROM1Flag = true;
//	}

//	if((suwGetEEBatACRestartVolt() > cBatVoltReal15V * uwGetBatSerialPcs()) \
//		|| (suwGetEEBatACRestartVolt() < cBatVoltReal10V * uwGetBatSerialPcs()) 
//	{
//		sSetEEBatACRestartVolt(strEepromDefaultTable1.strBatData.uwSetBatACRestartVolt);
//		bEEPROM1Flag = true;
//	}

//	if((suwGetEEBatLowAlarmVolt() > cBatVoltReal15V * uwGetBatSerialPcs()) \
//		|| (suwGetEEBatLowAlarmVolt() < cBatVoltReal10V * uwGetBatSerialPcs()) 
//	{
//		sSetEEBatLowAlarmVolt(strEepromDefaultTable1.strBatData.uwSetBatLowAlarmVolt);
//		bEEPROM1Flag = true;
//	}
//
//	if((suwGetEEBatLowShutDownVolt() > cBatVoltReal13V * uwGetBatSerialPcs()) \
//		|| (suwGetEEBatLowShutDownVolt() < cBatVoltReal8V5 * uwGetBatSerialPcs()) 
//	{
//		sSetEEBatLowShutDownVolt(strEepromDefaultTable1.strBatData.uwSetBatLowShutDownVolt);
//		bEEPROM1Flag = true;
//	}

	if(suwGetEEBatACRestartSOC() > 100) 
	{
		sSetEEBatACRestartSOC(strEepromDefaultTable1.strBatData.uwSetBatACRestartSOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatLowAlarmSOC() > 100) 
	{
		sSetEEBatLowAlarmSOC(strEepromDefaultTable1.strBatData.uwSetBatLowAlarmSOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatLowShutDownSOC() > 100) 
	{
		sSetEEBatLowShutDownSOC(strEepromDefaultTable1.strBatData.uwSetBatLowShutDownSOC);
		bEEPROM1Flag = true;
	}

//	if((suwGetEEBatVoltOverShut() > cBatVoltReal16V * uwGetBatSerialPcs()) \
//		|| (suwGetEEBatVoltOverShut() < cBatVoltReal12V * uwGetBatSerialPcs()) 
//	{
//		sSetEEBatVoltOverShut(strEepromDefaultTable1.strBatData.uwSetBatVoltOverShut);
//		bEEPROM1Flag = true;
//	}


	if((suwGetEEBatActivateEnable() != 0) && (suwGetEEBatActivateEnable() != 1))
	{
		sSetEEBatActivateEnable(strEepromDefaultTable1.strBatData.uwSetBatActivateEnable);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBMSComErrEnable() != 0) && (suwGetEEBMSComErrEnable() != 1))
	{
		sSetEEBMSComErrEnable(strEepromDefaultTable1.strBatData.uwSetBMSComErrEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBMSProtocol() > 100) 
	{
		sSetEEBMSProtocol(strEepromDefaultTable1.strBatData.uwSetBMSProtocol);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatParaEnable() != 0) && (suwGetEEBatParaEnable() != 1))
	{
		sSetEEBatParaEnable(strEepromDefaultTable1.strBatData.uwSetBatParaEnable);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatTempCompensateEnable() != 0) && (suwGetEEBatTempCompensateEnable() != 1))
	{
		sSetEEBatTempCompensateEnable(strEepromDefaultTable1.strBatData.uwSetBatTempCompensateEnable);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatEqEn() != 0) && (suwGetEEBatEqEn() != 1))
	{
		sSetEEEBatEqEn(strEepromDefaultTable1.strBatData.uwEEBatEqEn);
		bEEPROM1Flag = true;
	}

//	if((suwGetEEBatEqVolt() > cBatVoltReal15V * uwGetBatSerialPcs()) \
//		|| (suwGetEEBatEqVolt() < cBatVoltReal12V * uwGetBatSerialPcs()))
//	{
//		sSetEEEBatEqVolt(strEepromDefaultTable1.strBatData.uwEEBatEqVolt);
//		bEEPROM1Flag = true;
//	}

	if(suwGetEEBatEqTime() > 900 )	//min
	{
		sSetEEEBatEqTime(strEepromDefaultTable1.strBatData.uwEEBatEqTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatEqTimeout() > 900 )	//min
	{
		sSetEEEBatEqTimeout(strEepromDefaultTable1.strBatData.uwEEBatEqTimeout);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatEqInterval() > 900 )	//min
	{
		sSetEEEBatEqInterval(strEepromDefaultTable1.strBatData.uwEEBatEqInterval);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatEqActImd() != 0) && (suwGetEEBatEqActImd() != 1))	
	{
		sSetEEEBatEqActImd(strEepromDefaultTable1.strBatData.uwEEBatEqActImd);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd58() != 0)
	{
		sSetEERsvd58(strEepromDefaultTable1.strBatData.uwSetRsvd58);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd59() != 0)
	{
		sSetEERsvd59(strEepromDefaultTable1.strBatData.uwSetRsvd59);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatLowVoltDerateEnable() != 0) && (suwGetEEBatLowVoltDerateEnable() != 1))
	{
		sSetEEBatLowVoltDerateEnable(strEepromDefaultTable1.strBatData.uwBatLowVoltDerateEnable);
		bEEPROM1Flag = true;
	}
	
	if(suwGetEERsvd61() != 0)
	{
		sSetEERsvd61(strEepromDefaultTable1.strBatData.uwSetRsvd61);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd62() != 0)
	{
		sSetEERsvd62(strEepromDefaultTable1.strBatData.uwSetRsvd62);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd63() != 0)
	{
		sSetEERsvd63(strEepromDefaultTable1.strBatData.uwSetRsvd63);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEACOutputRatedPower() > uwGetInvWattMax())
//	{
//		sSetEEACOutputRatedPower(strEepromDefaultTable1.strAcData.uwSetACOutputRatedPower);
//		bEEPROM1Flag = true;
//	}

//	if((suwGetEEACOutputRatedVolt() != cAcVoltReal220V) \
//		&& (suwGetEEACOutputRatedVolt() != cAcVoltReal230V) \
//		&& (suwGetEEACOutputRatedVolt() != cAcVoltReal240V))
//	{
//		sSetEEACOutputRatedVolt(strEepromDefaultTable1.strAcData.uwSetACOutputRatedVolt);
//		bEEPROM1Flag = true;
//	}
		
	// 0：cFreq50hzConst
	// 2：cFreq60hzConst	
	if((suwGetEEACOutputRatedFreq() != 0) \
		&& (suwGetEEACOutputRatedFreq() != 1))
	{
		sSetEEACOutputRatedFreq(strEepromDefaultTable1.strAcData.uwSetACOutputRatedFreq);
		bEEPROM1Flag = true;
	}
		
	if((suwGetEEGridInputRange() != cAPL) \
		&& (suwGetEEGridInputRange() != cUPS))
	{
		sSetEEGridInputRange(strEepromDefaultTable1.strAcData.uwSetGridInputRange);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOutputPriority() != cDsgPriorityLINE) \
		&& (suwGetEEOutputPriority() != cDsgPriorityPV) \
		&& (suwGetEEOutputPriority() != cDsgPriorityBAT))
	{
		sSetEEOutputPriority(strEepromDefaultTable1.strAcData.uwSetOutputPriority);
		bEEPROM1Flag = true;
	}

	if(suwGetEEWorkMode() > 3) 
	{
		sSetEEWorkMode(strEepromDefaultTable1.strAcData.uwSetWorkMode);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd70() != 0) 
	{
		sSetEERsvd70(strEepromDefaultTable1.strAcData.uwSetRsvd70);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd71() != 0) 
	{
		sSetEERsvd71(strEepromDefaultTable1.strAcData.uwSetRsvd71);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd72() != 0) 
	{
		sSetEERsvd72(strEepromDefaultTable1.strAcData.uwSetRsvd72);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGridPeakShavingEnable() != 0) && (suwGetEEGridPeakShavingEnable() != 1))
	{
		sSetEEGridPeakShavingEnable(strEepromDefaultTable1.strAcData.uwSetGridPeakShavingEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGridPeakShavingPower() > cMaxACInputPower) 
	{
		sSetEEGridPeakShavingPower(strEepromDefaultTable1.strAcData.uwSetGridPeakShavingPower);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGridPeakShavingCurr() > cMaxACInputCurr) 
	{
		sSetEEGridPeakShavingCurr(strEepromDefaultTable1.strAcData.uwSetGridPeakShavingCurr);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEMaxFeedPower() >= ((INT16U)uwGetInvWattMax() + 200)) // -200W ~ 3200W
//	{
//		sSetEEMaxFeedPower(strEepromDefaultTable1.strAcData.uwMaxFeedPower);
//		bEEPROM1Flag = true;
//	}

	if(suwGetEERsvd77() != 0) 
	{
		sSetEERsvd77(strEepromDefaultTable1.strAcData.uwSetRsvd77);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd78() != 0) 
	{
		sSetEERsvd78(strEepromDefaultTable1.strAcData.uwSetRsvd78);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd79() != 0) 
	{
		sSetEERsvd79(strEepromDefaultTable1.strAcData.uwSetRsvd79);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd80() != 0) 
	{
		sSetEERsvd80(strEepromDefaultTable1.strAcData.uwSetRsvd80);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd81() != 0) 
	{
		sSetEERsvd81(strEepromDefaultTable1.strAcData.uwSetRsvd81);
		bEEPROM1Flag = true;
	}

	if(suwGetEERecconectWaitTime() > 600) 
	{
		sSetEERecconectWaitTime(strEepromDefaultTable1.strAcData.uwSetRecconectWaitTime);
		bEEPROM1Flag = true;
	}

	if((suwGetEEAnti_IslandProtectEnable() != 0) && (suwGetEEAnti_IslandProtectEnable() != 1))
	{
		sSetEEAnti_IslandProtectEnable(strEepromDefaultTable1.strAcData.uwSetAnti_IslandProtectEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd84() != 0) 
	{
		sSetEERsvd84(strEepromDefaultTable1.strAcData.uwSetRsvd84);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPowerSaveMode() != 0) && (suwGetEEPowerSaveMode() != 1))
	{
		sSetEEPowerSaveMode(strEepromDefaultTable1.strAcData.uwSetPowerSaveMode);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPowerConversion() != 0) && (suwGetEEPowerConversion() != 1)) 	// 功率折算使能
	{
		sSetEEPowerConversion(strEepromDefaultTable1.strAcData.uwPowerConversion);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOverTempRestartEn() != 0) && (suwGetEEOverTempRestartEn() != 1))
	{
		sSetEEOverTempRestartEn(strEepromDefaultTable1.strAcData.uwSetOverTempRestartEn);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOverLoadRestartEn() != 0) && (suwGetEEOverLoadRestartEn() != 1))
	{
		sSetEEOverLoadRestartEn(strEepromDefaultTable1.strAcData.uwSetOverLoadRestartEn);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOverLoadBypassEn() != 0) && (suwGetEEOverLoadBypassEn() != 1))
	{
		sSetEEOverLoadBypassEn(strEepromDefaultTable1.strAcData.uwSetOverLoadBypassEn);
		bEEPROM1Flag = true;
	}
	
	// 离网转并网时间 默认是15000.范围0-60000
	if(suwGetEEFeedToLineTime() >= 60000) 
	{
		sSetEEFeedToLineTime(strEepromDefaultTable1.strAcData.uwFeedToLineTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd91() != 0) 
	{
		sSetEERsvd91(strEepromDefaultTable1.strAcData.uwSetRsvd91);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd92() != 0) 
	{
		sSetEERsvd92(strEepromDefaultTable1.strAcData.uwSetRsvd92);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd93() != 0) 
	{
		sSetEERsvd93(strEepromDefaultTable1.strAcData.uwSetRsvd93);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd94() != 0) 
	{
		sSetEERsvd94(strEepromDefaultTable1.strAcData.uwSetRsvd94);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd95() != 0) 
	{
		sSetEERsvd95(strEepromDefaultTable1.strAcData.uwSetRsvd95);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd96() != 0) 
	{
		sSetEERsvd96(strEepromDefaultTable1.strAcData.uwSetRsvd96);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd97() != 0) 
	{
		sSetEERsvd97(strEepromDefaultTable1.strAcData.uwSetRsvd97);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd98() != 0) 
	{
		sSetEERsvd98(strEepromDefaultTable1.strReserve.uwSetRsvd98);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd99() != 0) 
	{
		sSetEERsvd99(strEepromDefaultTable1.strReserve.uwSetRsvd99);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd100() != 0) 
	{
		sSetEERsvd100(strEepromDefaultTable1.strReserve.uwSetRsvd100);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd101() != 0) 
	{
		sSetEERsvd101(strEepromDefaultTable1.strReserve.uwSetRsvd101);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd101() != 0) 
	{
		sSetEERsvd101(strEepromDefaultTable1.strReserve.uwSetRsvd101);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1OVValue() != 0) 
	{
		sSetEEGrid1OVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid1OVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1OVTime() != 0) 
	{
		sSetEEGrid1OVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid1OVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2OVValue() != 0) 
	{
		sSetEEGrid2OVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid2OVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2OVTime() != 0) 
	{
		sSetEEGrid2OVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid2OVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3OVValue() != 0) 
	{
		sSetEEGrid3OVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid3OVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3OVTime() != 0) 
	{
		sSetEEGrid3OVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid3OVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1UVValue() != 0) 
	{
		sSetEEGrid1UVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid1UVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1UVTime() != 0) 
	{
		sSetEEGrid1UVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid1UVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2UVValue() != 0) 
	{
		sSetEEGrid2UVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid2UVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2UVTime() != 0) 
	{
		sSetEEGrid2UVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid2UVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3UVValue() != 0) 
	{
		sSetEEGrid3UVValue(strEepromDefaultTable1.strLineProtect.uwSetGrid3UVValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3UVTime() != 0) 
	{
		sSetEEGrid3UVTime(strEepromDefaultTable1.strLineProtect.uwSetGrid3UVTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1OFValue() != 0) 
	{
		sSetEEGrid1OFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid1OFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1OFTime() != 0) 
	{
		sSetEEGrid1OFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid1OFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2OFValue() != 0) 
	{
		sSetEEGrid2OFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid2OFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2OFTime() != 0) 
	{
		sSetEEGrid2OFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid2OFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3OFValue() != 0) 
	{
		sSetEEGrid3OFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid3OFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3OFTime() != 0) 
	{
		sSetEEGrid3OFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid3OFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1UFValue() != 0) 
	{
		sSetEEGrid1UFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid1UFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid1UFTime() != 0) 
	{
		sSetEEGrid1UFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid1UFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2UFValue() != 0) 
	{
		sSetEEGrid2UFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid2UFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid2UFTime() != 0) 
	{
		sSetEEGrid2UFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid2UFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3UFValue() != 0) 
	{
		sSetEEGrid3UFValue(strEepromDefaultTable1.strLineProtect.uwSetGrid3UFValue);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGrid3UFTime() != 0) 
	{
		sSetEEGrid3UFTime(strEepromDefaultTable1.strLineProtect.uwSetGrid3UFTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd126() != 0) 
	{
		sSetEERsvd126(strEepromDefaultTable1.strLineProtect.uwSetRsvd126);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd127() != 0) 
	{
		sSetEERsvd127(strEepromDefaultTable1.strLineProtect.uwSetRsvd127);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd128() != 0) 
	{
		sSetEERsvd128(strEepromDefaultTable1.strLineProtect.uwSetRsvd128);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd129() != 0) 
	{
		sSetEERsvd129(strEepromDefaultTable1.strLineProtect.uwSetRsvd129);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd130() != 0) 
	{
		sSetEERsvd130(strEepromDefaultTable1.strLineProtect.uwSetRsvd130);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd131() != 0) 
	{
		sSetEERsvd131(strEepromDefaultTable1.strLineProtect.uwSetRsvd131);
		bEEPROM1Flag = true;
	}

	if((suwGetEEECO_TimeOfUse() != 0) && (suwGetEEECO_TimeOfUse() != 1))
	{
		sSetEEECO_TimeOfUse(strEepromDefaultTable1.strECOMode.uwSetECO_TimeOfUse);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO_EffectiveWeek() != 0)
	{
		sSetEEECO_EffectiveWeek(strEepromDefaultTable1.strECOMode.uwSetECO_EffectiveWeek);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_GridChargeEnable() != 0)
	{
		sSetEEECO1_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO1_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_GenChargeEnable() != 0)
	{
		sSetEEECO1_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO1_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_StartTime() != 0)
	{
		sSetEEECO1_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO1_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_StopTime() != 0)
	{
		sSetEEECO1_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO1_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_Volt() != 0)
	{
		sSetEEECO1_Volt(strEepromDefaultTable1.strECOMode.uwSetECO1_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_SOC() != 0)
	{
		sSetEEECO1_SOC(strEepromDefaultTable1.strECOMode.uwSetECO1_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_Power() != 0)
	{
		sSetEEECO1_Power(strEepromDefaultTable1.strECOMode.uwSetECO1_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO1_WorkModeSet() != 0)
	{
		sSetEEECO1_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO1_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_GridChargeEnable() != 0)
	{
		sSetEEECO2_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO2_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_GenChargeEnable() != 0)
	{
		sSetEEECO2_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO2_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_StartTime() != 0)
	{
		sSetEEECO2_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO2_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_StopTime() != 0)
	{
		sSetEEECO2_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO2_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_Volt() != 0)
	{
		sSetEEECO2_Volt(strEepromDefaultTable1.strECOMode.uwSetECO2_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_SOC() != 0)
	{
		sSetEEECO2_SOC(strEepromDefaultTable1.strECOMode.uwSetECO2_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_Power() != 0)
	{
		sSetEEECO2_Power(strEepromDefaultTable1.strECOMode.uwSetECO2_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO2_WorkModeSet() != 0)
	{
		sSetEEECO2_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO2_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_GridChargeEnable() != 0)
	{
		sSetEEECO3_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO3_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_GenChargeEnable() != 0)
	{
		sSetEEECO3_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO3_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_StartTime() != 0)
	{
		sSetEEECO3_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO3_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_StopTime() != 0)
	{
		sSetEEECO3_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO3_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_Volt() != 0)
	{
		sSetEEECO3_Volt(strEepromDefaultTable1.strECOMode.uwSetECO3_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_SOC() != 0)
	{
		sSetEEECO3_SOC(strEepromDefaultTable1.strECOMode.uwSetECO3_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_Power() != 0)
	{
		sSetEEECO3_Power(strEepromDefaultTable1.strECOMode.uwSetECO3_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO3_WorkModeSet() != 0)
	{
		sSetEEECO3_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO3_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_GridChargeEnable() != 0)
	{
		sSetEEECO4_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO4_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_GenChargeEnable() != 0)
	{
		sSetEEECO4_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO4_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_StartTime() != 0)
	{
		sSetEEECO4_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO4_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_StopTime() != 0)
	{
		sSetEEECO4_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO4_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_Volt() != 0)
	{
		sSetEEECO4_Volt(strEepromDefaultTable1.strECOMode.uwSetECO4_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_SOC() != 0)
	{
		sSetEEECO4_SOC(strEepromDefaultTable1.strECOMode.uwSetECO4_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_Power() != 0)
	{
		sSetEEECO4_Power(strEepromDefaultTable1.strECOMode.uwSetECO4_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO4_WorkModeSet() != 0)
	{
		sSetEEECO4_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO4_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_GridChargeEnable() != 0)
	{
		sSetEEECO5_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO5_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_GenChargeEnable() != 0)
	{
		sSetEEECO5_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO5_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_StartTime() != 0)
	{
		sSetEEECO5_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO5_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_StopTime() != 0)
	{
		sSetEEECO5_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO5_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_Volt() != 0)
	{
		sSetEEECO5_Volt(strEepromDefaultTable1.strECOMode.uwSetECO5_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_SOC() != 0)
	{
		sSetEEECO5_SOC(strEepromDefaultTable1.strECOMode.uwSetECO5_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_Power() != 0)
	{
		sSetEEECO5_Power(strEepromDefaultTable1.strECOMode.uwSetECO5_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO5_WorkModeSet() != 0)
	{
		sSetEEECO5_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO5_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_GridChargeEnable() != 0)
	{
		sSetEEECO6_GridChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO6_GridChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_GenChargeEnable() != 0)
	{
		sSetEEECO6_GenChargeEnable(strEepromDefaultTable1.strECOMode.uwSetECO6_GenChargeEnable);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_StartTime() != 0)
	{
		sSetEEECO6_StartTime(strEepromDefaultTable1.strECOMode.uwSetECO6_StartTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_StopTime() != 0)
	{
		sSetEEECO6_StopTime(strEepromDefaultTable1.strECOMode.uwSetECO6_StopTime);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_Volt() != 0)
	{
		sSetEEECO6_Volt(strEepromDefaultTable1.strECOMode.uwSetECO6_Volt);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_SOC() != 0)
	{
		sSetEEECO6_SOC(strEepromDefaultTable1.strECOMode.uwSetECO6_SOC);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_Power() != 0)
	{
		sSetEEECO6_Power(strEepromDefaultTable1.strECOMode.uwSetECO6_Power);
		bEEPROM1Flag = true;
	}

	if(suwGetEEECO6_WorkModeSet() != 0)
	{
		sSetEEECO6_WorkModeSet(strEepromDefaultTable1.strECOMode.uwSetECO6_WorkModeSet);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd182() != 0)
	{
		sSetEERsvd182(strEepromDefaultTable1.strECOMode.uwSetRsvd182);
		bEEPROM1Flag = true;
	}

	if(suwGetEERsvd183() != 0)
	{
		sSetEERsvd183(strEepromDefaultTable1.strECOMode.uwSetRsvd183);
		bEEPROM1Flag = true;
	}


	//EEPROM2
	if((suwGetEEPV1VoltAdj() < cEEAdjLimitLo) || (suwGetEEPV1VoltAdj() > cEEAdjLimitUp))
	{
		sSetEEPV1VoltAdj(strEepromDefaultTable2.uwEEPV1VoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV1VoltBias() < cEEBiasLimitLo) || (suwGetEEPV1VoltBias() > cEEBiasLimitUp))
	{
		sSetEEPV1VoltBias(strEepromDefaultTable2.uwEEPV1VoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV2VoltAdj() < cEEAdjLimitLo) || (suwGetEEPV2VoltAdj() > cEEAdjLimitUp))
	{
		sSetEEPV2VoltAdj(strEepromDefaultTable2.uwEEPV2VoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV2VoltBias() < cEEBiasLimitLo) || (suwGetEEPV2VoltBias() > cEEBiasLimitUp))
	{
		sSetEEPV2VoltBias(strEepromDefaultTable2.uwEEPV2VoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV1BatCurrAdj() < cEEAdjLimitLo) || (suwGetEEPV1BatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEPV1BatCurrAdj(strEepromDefaultTable2.uwEEPV1BatCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV1BatCurrBias() < cEEBiasLimitLo) || (suwGetEEPV1BatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEPV1BatCurrBias(strEepromDefaultTable2.uwEEPV1BatCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV2BatCurrAdj() < cEEAdjLimitLo) || (suwGetEEPV2BatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEPV2BatCurrAdj(strEepromDefaultTable2.uwEEPV2BatCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPV2BatCurrBias() < cEEBiasLimitLo) || (suwGetEEPV2BatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEPV2BatCurrBias(strEepromDefaultTable2.uwEEPV2BatCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatVoltAdj() < cEEAdjLimitLo) || (suwGetEEBatVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEBatVoltAdj(strEepromDefaultTable2.uwEEBatVoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatVoltBias() < cEEBiasLimitLo) || (suwGetEEBatVoltBias() > cEEBiasLimitUp))
	{
		sSetEEBatVoltBias(strEepromDefaultTable2.uwEEBatVoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatCurrAdj() < cEEAdjLimitLo) || (suwGetEEBatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEBatCurrAdj(strEepromDefaultTable2.uwEEBatCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatCurrBias() < cEEBiasLimitLo) || (suwGetEEBatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBatCurrBias(strEepromDefaultTable2.uwEEBatCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBUSVoltAdj() < cEEAdjLimitLo) || (suwGetEEBUSVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEBUSVoltAdj(strEepromDefaultTable2.uwEEBUSVoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBUSVoltBias() < cEEBiasLimitLo) || (suwGetEEBatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBUSVoltBias(strEepromDefaultTable2.uwEEBUSVoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBUSCurrAdj() < cEEAdjLimitLo) || (suwGetEEBUSCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEBUSCurrAdj(strEepromDefaultTable2.uwEEBUSCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBUSCurrBias() < cEEBiasLimitLo) || (suwGetEEBUSCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBUSCurrBias(strEepromDefaultTable2.uwEEBUSCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEInvVoltAdj() < cEEAdjLimitLo) || (suwGetEEInvVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEInvVoltAdj(strEepromDefaultTable2.uwEEInvVoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEInvVoltBias() < cEEBiasLimitLo) || (suwGetEEInvVoltBias() > cEEBiasLimitUp))
	{
		sSetEEInvVoltBias(strEepromDefaultTable2.uwEEInvVoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEInvCurrAdj() < cEEAdjLimitLo) || (suwGetEEInvCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEInvCurrAdj(strEepromDefaultTable2.uwEEInvCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEInvCurrBias() < cEEBiasLimitLo) || (suwGetEEInvCurrBias() > cEEBiasLimitUp))
	{
		sSetEEInvCurrBias(strEepromDefaultTable2.uwEEInvCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridVoltAdj() < cEEAdjLimitLo) || (suwGetEEGridVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEGridVoltAdj(strEepromDefaultTable2.uwEEGridVoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridVoltBias() < cEEBiasLimitLo) || (suwGetEEGridVoltBias() > cEEBiasLimitUp))
	{
		sSetEEGridVoltBias(strEepromDefaultTable2.uwEEGridVoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridCurrAdj() < cEEAdjLimitLo) || (suwGetEEGridCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEGridCurrAdj(strEepromDefaultTable2.uwEEGridCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridCurrBias() < cEEBiasLimitLo) || (suwGetEEGridCurrBias() > cEEBiasLimitUp))
	{
		sSetEEGridCurrBias(strEepromDefaultTable2.uwEEGridCurrBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOPVoltAdj() < cEEAdjLimitLo) || (suwGetEEOPVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEOPVoltAdj(strEepromDefaultTable2.uwEEOPVoltAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOpVoltBias() < cEEBiasLimitLo) || (suwGetEEOpVoltBias() > cEEBiasLimitUp))
	{
		sSetEEOpVoltBias(strEepromDefaultTable2.uwEEOpVoltBias);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOPCurrAdj() < cEEAdjLimitLo) || (suwGetEEOPCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEOPCurrAdj(strEepromDefaultTable2.uwEEOPCurrAdj);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOpCurrBias() < cEEBiasLimitLo) || (suwGetEEOpCurrBias() > cEEBiasLimitUp))
	{
		sSetEEOpCurrBias(strEepromDefaultTable2.uwEEOpCurrBias);
		bEEPROM2Flag = true;
	}

	if(suwGetEEDischargeEneyCoeffH() != 0)
	{
		sSetEEDischargeEneyCoeffH(strEepromDefaultTable2.uwEEDischargeEneyCoeffH);
		bEEPROM2Flag = true;
	}

	if(suwGetEEDischargeEneyCoeffL() != 0)
	{
		sSetEEDischargeEneyCoeffL(strEepromDefaultTable2.uwEEDischargeEneyCoeffL);
		bEEPROM2Flag = true;
	}

	if(suwGetEEchargeEneyCoeffH() != 0)
	{
		sSetEEchargeEneyCoeffH(strEepromDefaultTable2.uwEEchargeEneyCoeffH);
		bEEPROM2Flag = true;
	}

	if(suwGetEEchargeEneyCoeffL() != 0)
	{
		sSetEEchargeEneyCoeffL(strEepromDefaultTable2.uwEEchargeEneyCoeffL);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd218() != 0)
	{
		sSetEERsvd218(strEepromDefaultTable2.uwSetRsvd218);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd219() != 0)
	{
		sSetEERsvd219(strEepromDefaultTable2.uwSetRsvd219);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd220() != 0)
	{
		sSetEERsvd220(strEepromDefaultTable2.uwSetRsvd220);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd221() != 0)
	{
		sSetEERsvd221(strEepromDefaultTable2.uwSetRsvd221);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd222() != 0)
	{
		sSetEERsvd222(strEepromDefaultTable2.uwSetRsvd222);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd223() != 0)
	{
		sSetEERsvd223(strEepromDefaultTable2.uwSetRsvd223);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd224() != 0)
	{
		sSetEERsvd224(strEepromDefaultTable2.uwSetRsvd224);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd225() != 0)
	{
		sSetEERsvd225(strEepromDefaultTable2.uwSetRsvd225);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd226() != 0)
	{
		sSetEERsvd226(strEepromDefaultTable2.uwSetRsvd226);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd227() != 0)
	{
		sSetEERsvd227(strEepromDefaultTable2.uwSetRsvd227);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd228() != 0)
	{
		sSetEERsvd228(strEepromDefaultTable2.uwSetRsvd228);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd229() != 0)
	{
		sSetEERsvd229(strEepromDefaultTable2.uwSetRsvd229);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd230() != 0)
	{
		sSetEERsvd230(strEepromDefaultTable2.uwSetRsvd230);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd231() != 0)
	{
		sSetEERsvd231(strEepromDefaultTable2.uwSetRsvd231);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd232() != 0)
	{
		sSetEERsvd232(strEepromDefaultTable2.uwSetRsvd232);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd233() != 0)
	{
		sSetEERsvd233(strEepromDefaultTable2.uwSetRsvd233);
		bEEPROM2Flag = true;
	}

	//EEPROM3
	if(suwGetEEATE_SN1() > 9999)
	{
		sSetEEATE_SN1(strEepromDefaultTable3.uwATE_SN1);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SN2() > 9999)
	{
		sSetEEATE_SN2(strEepromDefaultTable3.uwATE_SN2);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SN3() > 9999)
	{
		sSetEEATE_SN3(strEepromDefaultTable3.uwATE_SN3);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SN4() > 9999)
	{
		sSetEEATE_SN4(strEepromDefaultTable3.uwATE_SN4);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SN5() > 9999)
	{
		sSetEEATE_SN5(strEepromDefaultTable3.uwATE_SN5);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SNLen() > 18)
	{
		sSetEEATE_SNLen(strEepromDefaultTable3.uwATE_SNLen);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_DispHwVer() != 0)
	{
		sSetEEATE_DispHwVer(strEepromDefaultTable3.uwATE_DispHwVer);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_CtrlHwVer() != cDspTempVersion)
	{
		sSetEEATE_CtrlHwVer(strEepromDefaultTable3.uwATE_CtrlHwVer);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_PowerHwVer() != cDspTempVersion)
	{
		sSetEEATE_PowerHwVer(strEepromDefaultTable3.uwATE_PowerHwVer);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_UpdateFW() != 0)
	{
		sSetEEATE_UpdateFW(strEepromDefaultTable3.uwATE_UpdateFW);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_ResetSystem() != 0)
	{
		sSetEEATE_ResetSystem(strEepromDefaultTable3.uwATE_ResetSystem);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EEDefault() != 0)
	{
		sSetEEATE_EEDefault(strEepromDefaultTable3.uwATE_EEDefault);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_AgingMode() != 0)
	{
		sSetEEATE_AgingMode(strEepromDefaultTable3.uwATE_AgingMode);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_RemoteOnOff() != 0)
	{
		sSetEEATE_RemoteOnOff(strEepromDefaultTable3.uwATE_RemoteOnOff);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EEFactory() != 0)
	{
		sSetEEATE_EEFactory(strEepromDefaultTable3.uwATE_EEFactory);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_AgingBattVolt() != 0)
	{
		sSetEEATE_AgingBattVolt(strEepromDefaultTable3.uwATE_AgingBattVolt);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_AgingBattCurr() != 0)
	{
		sSetEEATE_AgingBattCurr(strEepromDefaultTable3.uwATE_AgingBattCurr);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_AgingPVPower() != 0)
	{
		sSetEEATE_AgingPVPower(strEepromDefaultTable3.uwATE_AgingPVPower);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_AgingInvPower() != 0)
	{
		sSetEEATE_AgingInvPower(strEepromDefaultTable3.uwATE_AgingInvPower);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_MPPTVoltCntl() != 0)
	{
		sSetEEATE_MPPTVoltCntl(strEepromDefaultTable3.uwATE_MPPTVoltCntl);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_E_totalClr() != 0)
	{
		sSetEEATE_E_totalClr(strEepromDefaultTable3.uwATE_E_totalClr);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_SafetyCode() != 0)
	{
		sSetEEATE_SafetyCode(strEepromDefaultTable3.uwATE_SafetyCode);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_ISOsetting() != 0)
	{
		sSetEEATE_ISOsetting(strEepromDefaultTable3.uwATE_ISOsetting);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterProc() != 0)
	{
		sSetEEATE_EleMeterProc(strEepromDefaultTable3.uwATE_EleMeterProc);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_ExCommBps() != 0)
	{
		sSetEEATE_ExCommBps(strEepromDefaultTable3.uwATE_ExCommBps);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterBps_Parity() != 0)
	{
		sSetEEATE_EleMeterBps_Parity(strEepromDefaultTable3.uwATE_EleMeterBps_Parity);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterAddr() != 0)
	{
		sSetEEATE_EleMeterAddr(strEepromDefaultTable3.uwATE_EleMeterAddr);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterWREn() != 0)
	{
		sSetEEATE_EleMeterWREn(strEepromDefaultTable3.uwATE_EleMeterWREn);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterDataRegAddr() != 0)
	{
		sSetEEATE_EleMeterDataRegAddr(strEepromDefaultTable3.uwATE_EleMeterDataRegAddr);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_EleMeterData() != 0)
	{
		sSetEEATE_EleMeterData(strEepromDefaultTable3.uwATE_EleMeterData);
		bEEPROM3Flag = true;
	}

	if(suwGetEEATE_485CommBps() != 0)
	{
		sSetEEATE_485CommBps(strEepromDefaultTable3.uwATE_485CommBps);
		bEEPROM3Flag = true;
	}

	if((suwGetEEMenuRtnDftPageEn() != 0) && (suwGetEEMenuRtnDftPageEn() != 1))
	{
		sSetEEMenuRtnDftPageEn(strEepromDefaultTable3.uwMenuRtnDftPageEn);
		bEEPROM3Flag = true;
	}

	if((suwGetEELCDBacklight() != 0) && (suwGetEELCDBacklight() != 1))
	{
		sSetEELCDBacklight(strEepromDefaultTable3.uwSetLCDBacklight);
		bEEPROM3Flag = true;
	}

	if((suwGetEEBuzzerBeep() != 0) && (suwGetEEBuzzerBeep() != 1))
	{
		sSetEEBuzzerBeep(strEepromDefaultTable3.uwSetBuzzerBeep);
		bEEPROM3Flag = true;
	}

	if(suwGetEEBmsBagAddr() != 0)
	{
		sSetEEBmsBagAddr(strEepromDefaultTable3.uwSetBmsBagAddr);
		bEEPROM3Flag = true;
	}

	if(suwGetEEClearEventLog() != 0)
	{
		sSetEEClearEventLog(strEepromDefaultTable3.uwSetClearEventLog);
		bEEPROM3Flag = true;
	}

	if((suwGetEEEventLogFunc() != 0) && (suwGetEEEventLogFunc() != 1))
	{
		sSetEEEventLogFunc(strEepromDefaultTable3.uwSetEventLogFunc);
		bEEPROM3Flag = true;
	}

	if((suwGetEEFaultLogFunc() != 0) && (suwGetEEFaultLogFunc() != 1))
	{
		sSetEEFaultLogFunc(strEepromDefaultTable3.uwSetFaultLogFunc);
		bEEPROM3Flag = true;
	}

	if(suwGetEELogType() != 0)
	{
		sSetEELogType(strEepromDefaultTable3.uwSetLogType);
		bEEPROM3Flag = true;
	}

	if(suwGetEELogIndex() != 0)
	{
		sSetEELogIndex(strEepromDefaultTable3.uwSetLogIndex);
		bEEPROM3Flag = true;
	}

	if(bEEPROM1Flag == true)
	{
		sEepromSave1();
	}
	if(bEEPROM2Flag == true)
	{
		sEepromSave2();
	}
	if(bEEPROM3Flag == true)
	{
		sEepromSave3();
	}
}

void	sEepromDataVarRangeChk(void)
{
	INT16U uwBatSerialPcs;
	INT8U bEEPROM1Flag = 0;
	INT8U bEEPROM2Flag = 0;
//	INT8U bEEPROM3Flag = 0;

	uwBatSerialPcs = uwGetBatSerialPcs();
	if(suwGetEEBatSeriesNum() != uwBatSerialPcs)
	{
		sSetEEBatSeriesNum(uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	// 逆变额定电压
	if(uwGetModelLV() == true)
	{
		if((suwGetEEACOutputRatedVolt() != cAcVoltReal110V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal115V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal120V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal127V))
		{
			sSetEEACOutputRatedVolt(cAcVoltReal120V);
			bEEPROM1Flag = true;
		}
	}
	else
	{
		if((suwGetEEACOutputRatedVolt() != cAcVoltReal220V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal230V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal240V))
		{
			sSetEEACOutputRatedVolt(cAcVoltReal230V);
			bEEPROM1Flag = true;
		}
	}

	if(suwGetEEBatConstVolt() > (cBatVoltReal3V75*uwBatSerialPcs) \
		|| suwGetEEBatConstVolt() < (cBatVoltReal3V*uwBatSerialPcs))
	{
		sSetEEBatConstVolt(strEepromDefaultTable1.strBatData.uwSetBatConstVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatFloatVolt() > (cBatVoltReal3V75*uwBatSerialPcs) \
		|| suwGetEEBatFloatVolt() < (cBatVoltReal3V*uwBatSerialPcs))
	{
		sSetEEBatFloatVolt(strEepromDefaultTable1.strBatData.uwSetBatFloatVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if(suwGetEEBatMaxChgCurr() > (uwGetSettingMaxChgCurr()))	
	{
		sSetEEBatMaxChgCurr(strEepromDefaultTable1.strBatData.uwSetBatMaxChgCurr);
		bEEPROM1Flag = true;
	}
	
	if((suwGetEEBatMaxDcgCurr() > (uwGetSettingMaxDchgCurr())) \
		|| (suwGetEEBatMaxDcgCurr() == 0))
	{
		sSetEEBatMaxDcgCurr(strEepromDefaultTable1.strBatData.uwSetBatMaxDcgCurr);
		bEEPROM1Flag = true;
	}

	if(suwGetEEGridChgBatCurr() > (uwGetSettingMaxACChgCurr()))	
	{
		sSetEEGridChgBatCurr(strEepromDefaultTable1.strBatData.uwSetGridChgBatCurr);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOnGridBatAutoStartChgVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEOnGridBatAutoStartChgVolt() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEOnGridBatAutoStartChgVolt(strEepromDefaultTable1.strBatData.uwSetOnGridBatAutoStartChgVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOnGridBatExitAutoChgVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEOnGridBatExitAutoChgVolt() < cBatVoltReal3V * uwBatSerialPcs)) 
	{
		sSetEEOnGridBatExitAutoChgVolt(strEepromDefaultTable1.strBatData.uwSetOnGridBatExitAutoChgVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatACRestartVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatACRestartVolt() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEBatACRestartVolt(strEepromDefaultTable1.strBatData.uwSetBatACRestartVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatLowAlarmVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatLowAlarmVolt() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEBatLowAlarmVolt(strEepromDefaultTable1.strBatData.uwSetBatLowAlarmVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatLowShutDownVolt() > cBatVoltReal3V25 * uwBatSerialPcs) \
		|| (suwGetEEBatLowShutDownVolt() < cBatVoltReal2V12 * uwBatSerialPcs)) 
	{
		sSetEEBatLowShutDownVolt(strEepromDefaultTable1.strBatData.uwSetBatLowShutDownVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatVoltOverShut() > cBatVoltReal4V * uwBatSerialPcs) \
		|| (suwGetEEBatVoltOverShut() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEBatVoltOverShut(strEepromDefaultTable1.strBatData.uwSetBatVoltOverShut * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatEqVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatEqVolt() < cBatVoltReal4V * uwBatSerialPcs))
	{
		sSetEEEBatEqVolt(strEepromDefaultTable1.strBatData.uwEEBatEqVolt * uwBatSerialPcs);
		bEEPROM1Flag = true;
	}

	if(suwGetEEACOutputRatedPower() > ((INT16U)uwGetInvWattMax()))
	{
		sSetEEACOutputRatedPower(strEepromDefaultTable1.strAcData.uwSetACOutputRatedPower);
		bEEPROM1Flag = true;
	}

	if(suwGetEEMaxFeedPower() >= ((INT16U)uwGetInvWattMax() + 200)) // -200W ~ 3200W
	{
		sSetEEMaxFeedPower(strEepromDefaultTable1.strAcData.uwMaxFeedPower);
		bEEPROM1Flag = true;
	}

//	if(suwGetEEGridPeakShavingPower() != 0) 
//	{
//		sSetEEGridPeakShavingPower(strEepromDefaultTable1.strAcData.uwSetGridPeakShavingPower);
//		bEEPROM1Flag = true;
//	}

	if(bEEPROM1Flag != 0)
	{
		sSetEeprom1Mode(cEEPROM_SAVE_ENABLE);
	}
	if(bEEPROM2Flag != 0)
	{
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	if(bEEPROM2Flag != 0)
	{
		sSetEeprom3Mode(cEEPROM_SAVE_ENABLE);
	}
}


void	sEepromSaveMode1(INT16U wFilter)
{
	static INT16U wDelay = 0;
	
	switch(fEepromStatus.bits.bEE1Mode)
	{
		case cEEPROM_SAVE_DISABLE:
			
		break;
		case cEEPROM_SAVE_ENABLE:
			if(wFilter == 0)
			{
				fEepromStatus.bits.bEE1Mode = cEEPROM_SAVE_ACTION;
			}
			else
			{
				wDelay = 0;
				fEepromStatus.bits.bEE1Mode = cEEPROM_SAVE_DELAY;
			}
		break;
		case cEEPROM_SAVE_DELAY:
			if(++wDelay >= wFilter)
			{
				wDelay = 0;
				fEepromStatus.bits.bEE1Mode = cEEPROM_SAVE_ACTION;
			}
		break;
		case cEEPROM_SAVE_ACTION:
			OSEventSend(bEepromTaskPrio[cEEPROM_TASK1], bEepromTaskEvent[cEEPROM_TASK1]);
			fEepromStatus.bits.bEE1Mode = cEEPROM_SAVE_DISABLE;
		break;
		default:
			fEepromStatus.bits.bEE1Mode = cEEPROM_SAVE_DISABLE;
		break;
	}
}

void	sEepromSaveMode2(INT16U wFilter)
{
	static INT16U wDelay = 0;
	
	switch(fEepromStatus.bits.bEE2Mode)
	{
		case cEEPROM_SAVE_DISABLE:
			
		break;
		case cEEPROM_SAVE_ENABLE:
			if(wFilter == 0)
			{
				fEepromStatus.bits.bEE2Mode = cEEPROM_SAVE_ACTION;
			}
			else
			{
				wDelay = 0;
				fEepromStatus.bits.bEE2Mode = cEEPROM_SAVE_DELAY;
			}
		break;
		case cEEPROM_SAVE_DELAY:
			if(++wDelay >= wFilter)
			{
				wDelay = 0;
				fEepromStatus.bits.bEE2Mode = cEEPROM_SAVE_ACTION;
			}
		break;
		case cEEPROM_SAVE_ACTION:
			OSEventSend(bEepromTaskPrio[cEEPROM_TASK2], bEepromTaskEvent[cEEPROM_TASK2]);
			fEepromStatus.bits.bEE2Mode = cEEPROM_SAVE_DISABLE;
		break;
		default:
			fEepromStatus.bits.bEE2Mode = cEEPROM_SAVE_DISABLE;
		break;
	}
}

void	sEepromSaveMode3(INT16U wFilter)
{
	static INT16U wDelay = 0;
	
	switch(fEepromStatus.bits.bEE3Mode)
	{
		case cEEPROM_SAVE_DISABLE:
			
		break;
		case cEEPROM_SAVE_ENABLE:
			if(wFilter == 0)
			{
				fEepromStatus.bits.bEE3Mode = cEEPROM_SAVE_ACTION;
			}
			else
			{
				wDelay = 0;
				fEepromStatus.bits.bEE3Mode = cEEPROM_SAVE_DELAY;
			}
		break;
		case cEEPROM_SAVE_DELAY:
			if(++wDelay >= wFilter)
			{
				wDelay = 0;
				fEepromStatus.bits.bEE3Mode = cEEPROM_SAVE_ACTION;
			}
		break;
		case cEEPROM_SAVE_ACTION:
			OSEventSend(bEepromTaskPrio[cEEPROM_TASK3], bEepromTaskEvent[cEEPROM_TASK3]);
			fEepromStatus.bits.bEE3Mode = cEEPROM_SAVE_DISABLE;
		break;
		default:
			fEepromStatus.bits.bEE3Mode = cEEPROM_SAVE_DISABLE;
		break;
	}
}

void	sEepromSecureLockClr(INT16U	wFilter)
{
	static INT16U wCnt = 0;
	
	if(fEepromStatus.bits.bSecureLockRst == true)
	{
		wCnt = 0;
		fEepromStatus.bits.bSecureLockRst = false;
	}
	else if(fEepromStatus.bits.bSecureLock == false)
	{
		if(++wCnt >= wFilter)
		{
			wCnt = 0;
			fEepromStatus.bits.bSecureLock = true;
		}
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT8U	sbGetEepromRwEnable(void)
{
	return(fEepromStatus.bits.bRwEnable);
}

INT8U	sbGetEepromRwBusy(void)
{
	return(fEepromStatus.bits.bRwBusy);
}

INT8U	sbGetEepromSecureLock(void)
{
	return(fEepromStatus.bits.bSecureLock);
}

INT16U	swGetEeprom1MapData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cEepromTotalLength1)
	{
		pwTemp = (INT16U *)uEepromCfg1.wEepromCfg1;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

INT16U	swGetEeprom2MapData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cEepromTotalLength2)
	{
		pwTemp = (INT16U *)uEepromCfg2.wEepromCfg2;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}

INT16U	swGetEeprom3MapData(INT16U wAddrOffset)
{
	INT16U	*pwTemp;
	
	if(wAddrOffset < cEepromTotalLength3)
	{
		pwTemp = (INT16U *)uEepromCfg3.wEepromCfg3;
		pwTemp += wAddrOffset;
		return(*pwTemp);
	}
	else
	{
		return 0xFFFF;
	}
}


INT16U suwGetEEMachineID(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetMachineID;
}

INT16U suwGetEEParaEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetParaEnable;
}

INT16U suwGetEEMasterSlaver(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetMasterSlaver;
}

INT16U suwGetEEAutoWrite(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetEepromAutoWrite;
}

INT16U suwGetEESystemOutputMode(void)
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetSystemOutputMode;
}

INT16U suwGetEEFanWorkMode(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetFanWorkMode;
}

INT16U suwGetEETurboMode(void)
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwTurboMode;
}

INT16U suwGetEEAutoInvEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwAutoInvEnable;
}

INT16U suwGetEEDCDCOpenLoopEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwDCDCOpenLoopEnable;
}

INT16U suwGetEELogoEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwLogoEnable;
}

INT16U suwGetEEAdcBiasAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwAdcBiasAdj;
}

INT16U suwGetEEReserve11(void)
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve11;
}

INT16U suwGetEEReserve12(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve12;
}

INT16U suwGetEEReserve13(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve13;
}

INT16U suwGetEEReserve14(void) 
{
    return uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve14;
}

INT16U suwGetEEPV1StartVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV1StartVolt;
}

INT16U suwGetEEReserve16(void) 
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve16;
}

INT16U suwGetEEPV_PowerLimit(void) 
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV_PowerLimit;
}

INT16U suwGetEEReserve18(void) 
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve18;
}

INT16U suwGetEEReserve19(void)
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve19;
}

INT16U suwGetEEPV_Priority(void)
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV_Priority;
}

INT16U suwGetEEPVAutoInvEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strPvData.uwPVAutoInvEnable;
}

INT16U suwGetEERsvd22(void) {
    return uEepromCfg1.EepromStructCfg1.strPvData.uwSetRsvd22;
}

INT16U suwGetEEBatType(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatType;
}

INT16U suwGetEEBatSeriesNum(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatSeriesNum;
}

INT16U suwGetEEBatCapacity(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatCapacity;
}

INT16U suwGetEERsvd26(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd26;
}

INT16U suwGetEEBatMode(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMode;
}

INT16U suwGetEEChargePriority(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetChargePriority;
}

INT16U suwGetEEBatConstVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatConstVolt;
}

INT16U suwGetEEBatFloatVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatFloatVolt;
}

INT16U suwGetEEBatFloatTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatFloatTime;
}

INT16U suwGetEEBatMaxChgCurr(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMaxChgCurr;
}

INT16U suwGetEEBatMaxDcgCurr(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMaxDcgCurr;
}

INT16U suwGetEEGridChgBatCurr(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetGridChgBatCurr;
}

INT16U suwGetEEGridChgBatTotalEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetGridChgBatTotalEnable;
}

INT16U suwGetEEOnGridBatAutoStartChgSOC(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatAutoStartChgSOC;
}

INT16U suwGetEEOnGridBatExitAutoChgSOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatExitAutoChgSOC;
}

INT16U suwGetEEOnGridBatAutoStartChgVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatAutoStartChgVolt;
}

INT16U suwGetEEOnGridBatExitAutoChgVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatExitAutoChgVolt;
}

INT16U suwGetEEBatACRestartVolt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatACRestartVolt;
}

INT16U suwGetEEBatLowAlarmVolt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowAlarmVolt;
}

INT16U suwGetEEBatLowShutDownVolt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowShutDownVolt;
}

INT16U suwGetEEBatACRestartSOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatACRestartSOC;
}

INT16U suwGetEEBatLowAlarmSOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowAlarmSOC;
}

INT16U suwGetEEBatLowShutDownSOC(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowShutDownSOC;
}

INT16U suwGetEEBatVoltOverShut(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatVoltOverShut;
}

INT16U suwGetEEBatActivateEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatActivateEnable;
}

INT16U suwGetEEBMSComErrEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBMSComErrEnable;
}

INT16U suwGetEEBMSProtocol(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBMSProtocol;
}

INT16U suwGetEEBatParaEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatParaEnable;
}

INT16U suwGetEEBatTempCompensateEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatTempCompensateEnable;
}

INT16U suwGetEEBatEqEn(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqEn;
}

INT16U suwGetEEBatEqVolt(void) 

{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqVolt;
}

INT16U suwGetEEBatEqTime(void) {
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqTime;
}

INT16U suwGetEEBatEqTimeout(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqTimeout;
}

INT16U suwGetEEBatEqInterval(void)
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqInterval;
}

INT16U suwGetEEBatEqActImd(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqActImd;
}

INT16U suwGetEERsvd58(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd58;
}

INT16U suwGetEERsvd59(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd59;
}

INT16U suwGetEEBatLowVoltDerateEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwBatLowVoltDerateEnable;
}

INT16U suwGetEERsvd61(void) 

{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd61;
}

INT16U suwGetEERsvd62(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd62;
}

INT16U suwGetEERsvd63(void) 
{
    return uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd63;
}

INT16U suwGetEEACOutputRatedPower(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedPower;
}

INT16U suwGetEEACOutputRatedVolt(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedVolt;
}

INT16U suwGetEEACOutputRatedFreq(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedFreq;
}

INT16U suwGetEEGridInputRange(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridInputRange;
}

INT16U suwGetEEOutputPriority(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetOutputPriority;
}

INT16U suwGetEEWorkMode(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetWorkMode;
}

INT16U suwGetEERsvd70(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd70;
}

INT16U suwGetEERsvd71(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd71;
}

INT16U suwGetEERsvd72(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd72;
}

INT16U suwGetEEGridPeakShavingEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingEnable;
}

INT16U suwGetEEGridPeakShavingPower(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingPower;
}

INT16U suwGetEEGridPeakShavingCurr(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingCurr;
}

INT16U suwGetEEMaxFeedPower(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwMaxFeedPower;
}

INT16U suwGetEERsvd77(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd77;
}

INT16U suwGetEERsvd78(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd78;
}

INT16U suwGetEERsvd79(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd79;
}

INT16U suwGetEERsvd80(void) 

{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd80;
}

INT16U suwGetEERsvd81(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd81;
}

INT16U suwGetEERecconectWaitTime(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRecconectWaitTime;
}

INT16U suwGetEEAnti_IslandProtectEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetAnti_IslandProtectEnable;
}

INT16U suwGetEERsvd84(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd84;
}

INT16U suwGetEEPowerSaveMode(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetPowerSaveMode;
}

INT16U suwGetEEPowerConversion(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwPowerConversion;
}

INT16U suwGetEEOverTempRestartEn(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverTempRestartEn;
}

INT16U suwGetEEOverLoadRestartEn(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverLoadRestartEn;
}

INT16U suwGetEEOverLoadBypassEn(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverLoadBypassEn;
}

INT16U suwGetEEFeedToLineTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwFeedToLineTime;
}

INT16U suwGetEERsvd91(void)
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd91;
}

INT16U suwGetEERsvd92(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd92;
}

INT16U suwGetEERsvd93(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd93;
}

INT16U suwGetEERsvd94(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd94;
}

INT16U suwGetEERsvd95(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd95;
}

INT16U suwGetEERsvd96(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd96;
}

INT16U suwGetEERsvd97(void) 
{
    return uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd97;
}

INT16U suwGetEERsvd98(void) 

{
    return uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd98;
}

INT16U suwGetEERsvd99(void) 
{
    return uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd99;
}

INT16U suwGetEERsvd100(void) 
{
    return uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd100;
}

INT16U suwGetEERsvd101(void)
{
    return uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd101;
}

INT16U suwGetEEGrid1OVValue(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OVValue;
}

INT16U suwGetEEGrid1OVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OVTime;
}

INT16U suwGetEEGrid2OVValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OVValue;
}

INT16U suwGetEEGrid2OVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OVTime;
}

INT16U suwGetEEGrid3OVValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OVValue;
}

INT16U suwGetEEGrid3OVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OVTime;
}

INT16U suwGetEEGrid1UVValue(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UVValue;
}

INT16U suwGetEEGrid1UVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UVTime;
}

INT16U suwGetEEGrid2UVValue(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UVValue;
}

INT16U suwGetEEGrid2UVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UVTime;
}

INT16U suwGetEEGrid3UVValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UVValue;
}

INT16U suwGetEEGrid3UVTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UVTime;
}

INT16U suwGetEEGrid1OFValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OFValue;
}

INT16U suwGetEEGrid1OFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OFTime;
}

INT16U suwGetEEGrid2OFValue(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OFValue;
}

INT16U suwGetEEGrid2OFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OFTime;
}

INT16U suwGetEEGrid3OFValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OFValue;
}

INT16U suwGetEEGrid3OFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OFTime;
}

INT16U suwGetEEGrid1UFValue(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UFValue;
}

INT16U suwGetEEGrid1UFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UFTime;
}

INT16U suwGetEEGrid2UFValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UFValue;
}

INT16U suwGetEEGrid2UFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UFTime;
}

INT16U suwGetEEGrid3UFValue(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UFValue;
}

INT16U suwGetEEGrid3UFTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UFTime;
}

INT16U suwGetEERsvd126(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd126;
}

INT16U suwGetEERsvd127(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd127;
}

INT16U suwGetEERsvd128(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd128;
}

INT16U suwGetEERsvd129(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd129;
}

INT16U suwGetEERsvd130(void)
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd130;
}

INT16U suwGetEERsvd131(void) 
{
    return uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd131;
}


INT16U suwGetEEECO_TimeOfUse(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO_TimeOfUse;
}

INT16U suwGetEEECO_EffectiveWeek(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO_EffectiveWeek;
}

INT16U suwGetEEECO1_GridChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_GridChargeEnable;
}

INT16U suwGetEEECO1_GenChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_GenChargeEnable;
}

INT16U suwGetEEECO1_StartTime(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_StartTime;
}

INT16U suwGetEEECO1_StopTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_StopTime;
}

INT16U suwGetEEECO1_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_Volt;
}

INT16U suwGetEEECO1_SOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_SOC;
}

INT16U suwGetEEECO1_Power(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_Power;
}

INT16U suwGetEEECO1_WorkModeSet(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_WorkModeSet;
}

INT16U suwGetEEECO2_GridChargeEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_GridChargeEnable;
}

INT16U suwGetEEECO2_GenChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_GenChargeEnable;
}

INT16U suwGetEEECO2_StartTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_StartTime;
}

INT16U suwGetEEECO2_StopTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_StopTime;
}

INT16U suwGetEEECO2_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_Volt;
}

INT16U suwGetEEECO2_SOC(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_SOC;
}

INT16U suwGetEEECO2_Power(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_Power;
}

INT16U suwGetEEECO2_WorkModeSet(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_WorkModeSet;
}

INT16U suwGetEEECO3_GridChargeEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_GridChargeEnable;
}

INT16U suwGetEEECO3_GenChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_GenChargeEnable;
}

INT16U suwGetEEECO3_StartTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_StartTime;
}

INT16U suwGetEEECO3_StopTime(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_StopTime;
}

INT16U suwGetEEECO3_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_Volt;
}

INT16U suwGetEEECO3_SOC(void) 

{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_SOC;
}

INT16U suwGetEEECO3_Power(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_Power;
}

INT16U suwGetEEECO3_WorkModeSet(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_WorkModeSet;
}

INT16U suwGetEEECO4_GridChargeEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_GridChargeEnable;
}

INT16U suwGetEEECO4_GenChargeEnable(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_GenChargeEnable;
}

INT16U suwGetEEECO4_StartTime(void)

{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_StartTime;
}

INT16U suwGetEEECO4_StopTime(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_StopTime;
}

INT16U suwGetEEECO4_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_Volt;
}

INT16U suwGetEEECO4_SOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_SOC;
}

INT16U suwGetEEECO4_Power(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_Power;
}

INT16U suwGetEEECO4_WorkModeSet(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_WorkModeSet;
}

INT16U suwGetEEECO5_GridChargeEnable(void)

{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_GridChargeEnable;
}

INT16U suwGetEEECO5_GenChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_GenChargeEnable;
}

INT16U suwGetEEECO5_StartTime(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_StartTime;
}

INT16U suwGetEEECO5_StopTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_StopTime;
}

INT16U suwGetEEECO5_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_Volt;
}

INT16U suwGetEEECO5_SOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_SOC;
}

INT16U suwGetEEECO5_Power(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_Power;
}

INT16U suwGetEEECO5_WorkModeSet(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_WorkModeSet;
}

INT16U suwGetEEECO6_GridChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_GridChargeEnable;
}

INT16U suwGetEEECO6_GenChargeEnable(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_GenChargeEnable;
}

INT16U suwGetEEECO6_StartTime(void) 

{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_StartTime;
}

INT16U suwGetEEECO6_StopTime(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_StopTime;
}

INT16U suwGetEEECO6_Volt(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_Volt;
}

INT16U suwGetEEECO6_SOC(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_SOC;
}

INT16U suwGetEEECO6_Power(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_Power;
}

INT16U suwGetEEECO6_WorkModeSet(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_WorkModeSet;
}

INT16U suwGetEERsvd182(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetRsvd182;
}

INT16U suwGetEERsvd183(void) 
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwSetRsvd183;
}

INT16U suwGetEEFlag1(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwFlag1;
}

INT16U suwGetEECheckCRC1(void)
{
    return uEepromCfg1.EepromStructCfg1.strECOMode.uwEECheckCRC1;
}

INT16S suwGetEEPV1VoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV1VoltAdj;
}

INT16S suwGetEEPV1VoltBias(void)
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV1VoltBias;
}

INT16S suwGetEEPV2VoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV2VoltAdj;
}

INT16S suwGetEEPV2VoltBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV2VoltBias;
}

INT16S suwGetEEPV1BatCurrAdj(void)
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV1BatCurrAdj;
}

INT16S suwGetEEPV1BatCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV1BatCurrBias;
}

INT16S suwGetEEPV2BatCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV2BatCurrAdj;
}

INT16S suwGetEEPV2BatCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEPV2BatCurrBias;
}

INT16S suwGetEEBatVoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBatVoltAdj;
}

INT16S suwGetEEBatVoltBias(void) 

{
    return uEepromCfg2.EepromStructCfg2.uwEEBatVoltBias;
}

INT16S suwGetEEBatCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBatCurrAdj;
}

INT16S suwGetEEBatCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBatCurrBias;
}

INT16S suwGetEEBUSVoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBUSVoltAdj;
}

INT16S suwGetEEBUSVoltBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBUSVoltBias;
}

INT16S suwGetEEBUSCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEBUSCurrAdj;
}

INT16S suwGetEEBUSCurrBias(void)
{
    return uEepromCfg2.EepromStructCfg2.uwEEBUSCurrBias;
}

INT16S suwGetEEInvVoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEInvVoltAdj;
}

INT16S suwGetEEInvVoltBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEInvVoltBias;
}

INT16S suwGetEEInvCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEInvCurrAdj;
}

INT16S suwGetEEInvCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEInvCurrBias;
}

INT16S suwGetEEGridVoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEGridVoltAdj;
}

INT16S suwGetEEGridVoltBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEGridVoltBias;
}

INT16S suwGetEEGridCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEGridCurrAdj;
}

INT16S suwGetEEGridCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEGridCurrBias;
}

INT16S suwGetEEOPVoltAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEOPVoltAdj;
}

INT16S suwGetEEOpVoltBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEOpVoltBias;
}

INT16S suwGetEEOPCurrAdj(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEOPCurrAdj;
}

INT16S suwGetEEOpCurrBias(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEOpCurrBias;
}

INT16U suwGetEEDischargeEneyCoeffH(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEDischargeEneyCoeffH;
}

INT16U suwGetEEDischargeEneyCoeffL(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEDischargeEneyCoeffL;
}

INT16U suwGetEEchargeEneyCoeffH(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEchargeEneyCoeffH;
}

INT16U suwGetEEchargeEneyCoeffL(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEEchargeEneyCoeffL;
}

INT16U suwGetEERsvd218(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd218;
}

INT16U suwGetEERsvd219(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd219;
}

INT16U suwGetEERsvd220(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd220;
}

INT16U suwGetEERsvd221(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd221;
}

INT16U suwGetEERsvd222(void) 

{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd222;
}

INT16U suwGetEERsvd223(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd223;
}

INT16U suwGetEERsvd224(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd224;
}

INT16U suwGetEERsvd225(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd225;
}

INT16U suwGetEERsvd226(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd226;
}

INT16U suwGetEERsvd227(void)
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd227;
}

INT16U suwGetEERsvd228(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd228;
}

INT16U suwGetEERsvd229(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd229;
}

INT16U suwGetEERsvd230(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd230;
}

INT16U suwGetEERsvd231(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd231;
}

INT16U suwGetEERsvd232(void)
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd232;
}

INT16U suwGetEERsvd233(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwSetRsvd233;
}

INT16U suwGetEEFlag2(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwFlag2;
}

INT16U suwGetEECheckCRC2(void) 
{
    return uEepromCfg2.EepromStructCfg2.uwEECheckCRC2;
}

INT16U suwGetEEATE_SN1(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SN1;
}

INT16U suwGetEEATE_SN2(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SN2;
}

INT16U suwGetEEATE_SN3(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SN3;
}

INT16U suwGetEEATE_SN4(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SN4;
}

INT16U suwGetEEATE_SN5(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SN5;
}

INT16U suwGetEEATE_SNLen(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SNLen;
}

INT16U suwGetEEATE_DispHwVer(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_DispHwVer;
}

INT16U suwGetEEATE_CtrlHwVer(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_CtrlHwVer;
}

INT16U suwGetEEATE_PowerHwVer(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_PowerHwVer;
}

INT16U suwGetEEATE_UpdateFW(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_UpdateFW;
}

INT16U suwGetEEATE_ResetSystem(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_ResetSystem;
}

INT16U suwGetEEATE_EEDefault(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EEDefault;
}

INT16U suwGetEEATE_AgingMode(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_AgingMode;
}

INT16U suwGetEEATE_RemoteOnOff(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_RemoteOnOff;
}

INT16U suwGetEEATE_EEFactory(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EEFactory;
}

INT16U suwGetEEATE_AgingBattVolt(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_AgingBattVolt;
}

INT16U suwGetEEATE_AgingBattCurr(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_AgingBattCurr;
}

INT16U suwGetEEATE_AgingPVPower(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_AgingPVPower;
}

INT16U suwGetEEATE_AgingInvPower(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_AgingInvPower;
}

INT16U suwGetEEATE_MPPTVoltCntl(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_MPPTVoltCntl;
}

INT16U suwGetEEATE_E_totalClr(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_E_totalClr;
}

INT16U suwGetEEATE_SafetyCode(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_SafetyCode;
}

INT16U suwGetEEATE_ISOsetting(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_ISOsetting;
}

INT16U suwGetEEATE_EleMeterProc(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterProc;
}

INT16U suwGetEEATE_ExCommBps(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_ExCommBps;
}

INT16U suwGetEEATE_EleMeterBps_Parity(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterBps_Parity;
}

INT16U suwGetEEATE_EleMeterAddr(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterAddr;
}

INT16U suwGetEEATE_EleMeterWREn(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterWREn;
}

INT16U suwGetEEATE_EleMeterDataRegAddr(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterDataRegAddr;
}

INT16U suwGetEEATE_EleMeterData(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_EleMeterData;
}

INT16U suwGetEEATE_485CommBps(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwATE_485CommBps;
}

INT16U suwGetEEMenuRtnDftPageEn(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwMenuRtnDftPageEn;
}

INT16U suwGetEELCDBacklight(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetLCDBacklight;
}

INT16U suwGetEEBuzzerBeep(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetBuzzerBeep;
}

INT16U suwGetEEBmsBagAddr(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetBmsBagAddr;
}

INT16U suwGetEEClearEventLog(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetClearEventLog;
}

INT16U suwGetEEEventLogFunc(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetEventLogFunc;
}

INT16U suwGetEEFaultLogFunc(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetFaultLogFunc;
}

INT16U suwGetEELogType(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetLogType;
}

INT16U suwGetEELogIndex(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetLogIndex;
}

INT16U suwGetEEFlag3(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwFlag3;
}

INT16U suwGetEECheckCRC3(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwEECheckCRC3;
}


// 下面的数据是临时用一下
void	swGetEepromSOCSmoothEn(void)
{
	return true;
}


void	swGetBmsCellVoltNum(void)
{
	return 2;
}

void	swGetBmsRatedAH(void)
{
	return 3140;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetEepromRwEnable(INT8U bStatus)
{
	fEepromStatus.bits.bRwEnable = bStatus;
}

void	sSetEepromRwBusy(INT8U bStatus)
{
	fEepromStatus.bits.bRwBusy = bStatus;
}

void	sSetEepromSecureLock(INT8U bStatus)
{
	fEepromStatus.bits.bSecureLock = bStatus;
	fEepromStatus.bits.bSecureLockRst = ~fEepromStatus.bits.bSecureLock;
}

void	sSetEeprom1Mode(INT8U bMode)
{
	fEepromStatus.bits.bEE1Mode = bMode;
}

void	sSetEeprom2Mode(INT8U bMode)
{
	fEepromStatus.bits.bEE2Mode = bMode;
}

void	sSetEeprom3Mode(INT8U bMode)
{
	fEepromStatus.bits.bEE3Mode = bMode;
}


void sSetEEMachineID(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetMachineID = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEParaEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetParaEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEMasterSlaver(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetMasterSlaver = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEAutoWrite(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetEepromAutoWrite = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEESystemOutputMode(INT16U uwtemp) {
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetSystemOutputMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFanWorkMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetFanWorkMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEETurboMode(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwTurboMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEAutoInvEnable(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwAutoInvEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEDCDCOpenLoopEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwDCDCOpenLoopEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELogoEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwLogoEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEAdcBiasAdj(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwAdcBiasAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve11(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve11 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve12(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve12 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve13(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve13 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve14(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strControlState.uwSetReserve14 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1StartVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV1StartVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve16(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve16 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV_PowerLimit(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV_PowerLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve18(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve18 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEReserve19(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetReserve19 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV_Priority(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetPV_Priority = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPVAutoInvEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwPVAutoInvEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd22(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strPvData.uwSetRsvd22 = uwtemp;
    OS_EXIT_CRITICAL();
}
void sSetEEBatType(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatType = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatSeriesNum(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatSeriesNum = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatCapacity(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatCapacity = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd26(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd26 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatMode(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEChargePriority(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetChargePriority = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatConstVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatConstVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatFloatVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatFloatVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatFloatTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatFloatTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatMaxChgCurr(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMaxChgCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatMaxDcgCurr(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatMaxDcgCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridChgBatCurr(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetGridChgBatCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridChgBatTotalEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetGridChgBatTotalEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOnGridBatAutoStartChgSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatAutoStartChgSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOnGridBatExitAutoChgSOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatExitAutoChgSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOnGridBatAutoStartChgVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatAutoStartChgVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOnGridBatExitAutoChgVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetOnGridBatExitAutoChgVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatACRestartVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatACRestartVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatLowAlarmVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowAlarmVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatLowShutDownVolt(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowShutDownVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatACRestartSOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatACRestartSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatLowAlarmSOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowAlarmSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatLowShutDownSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatLowShutDownSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatVoltOverShut(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatVoltOverShut = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatActivateEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatActivateEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBMSComErrEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBMSComErrEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBMSProtocol(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBMSProtocol = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatParaEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatParaEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatTempCompensateEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetBatTempCompensateEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqEn(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqTimeout(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqTimeout = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqInterval(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqInterval = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEBatEqActImd(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwEEBatEqActImd = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd58(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd58 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd59(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd59 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatLowVoltDerateEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwBatLowVoltDerateEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd61(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd61 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd62(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd62 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd63(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strBatData.uwSetRsvd63 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEACOutputRatedPower(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEACOutputRatedVolt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEACOutputRatedFreq(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetACOutputRatedFreq = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridInputRange(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridInputRange = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOutputPriority(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetOutputPriority = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEWorkMode(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetWorkMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd70(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd70 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd71(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd71 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd72(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd72 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridPeakShavingEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridPeakShavingPower(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridPeakShavingCurr(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetGridPeakShavingCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEMaxFeedPower(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwMaxFeedPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd77(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd77 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd78(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd78 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd79(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd79 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd80(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd80 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd81(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd81 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERecconectWaitTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRecconectWaitTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEAnti_IslandProtectEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetAnti_IslandProtectEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd84(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd84 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPowerSaveMode(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetPowerSaveMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPowerConversion(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwPowerConversion = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOverTempRestartEn(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverTempRestartEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOverLoadRestartEn(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverLoadRestartEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOverLoadBypassEn(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetOverLoadBypassEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFeedToLineTime(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwFeedToLineTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd91(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd91 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd92(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd92 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd93(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd93 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd94(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd94 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd95(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd95 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd96(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd96 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd97(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strAcData.uwSetRsvd97 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd98(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd98 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd99(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd99 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd100(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd100 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd101(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strReserve.uwSetRsvd101 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OVTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OVTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OVTime(INT16U uwtemp)

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OFTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OFTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OFValue(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid1UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid2UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetGrid3UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd126(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd126 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd127(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd127 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd128(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd128 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd129(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd129 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd130(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd130 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd131(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strLineProtect.uwSetRsvd131 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO_TimeOfUse(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO_TimeOfUse = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO_EffectiveWeek(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO_EffectiveWeek = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_GridChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_StartTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_Volt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_SOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_WorkModeSet(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO1_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_GenChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_StartTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_Power(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO2_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_GenChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_Volt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_SOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO3_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO4_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO5_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_SOC(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetECO6_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd182(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetRsvd182 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd183(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwSetRsvd183 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFlag1(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwFlag1 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEECheckCRC1(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.strECOMode.uwEECheckCRC1 = uwtemp;
    OS_EXIT_CRITICAL();
}    

void sSetEEPV1VoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV1VoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1VoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV1VoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2VoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV2VoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2VoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV2VoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1BatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV1BatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1BatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV1BatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2BatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV2BatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2BatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEPV2BatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBatVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBatVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBUSVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBUSVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBUSCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEBUSCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEInvVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEInvVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEInvCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEInvCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEGridVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEGridVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEGridCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEGridCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOPVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEOPVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOpVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEOpVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOPCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEOPCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOpCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEOpCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEDischargeEneyCoeffH(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEDischargeEneyCoeffH = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEDischargeEneyCoeffL(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEDischargeEneyCoeffL = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEchargeEneyCoeffH(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEchargeEneyCoeffH = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEchargeEneyCoeffL(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEEchargeEneyCoeffL = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd218(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd218 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd219(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd219 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd220(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd220 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd221(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd221 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd222(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd222 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd223(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd223 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd224(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd224 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd225(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd225 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd226(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd226 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd227(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd227 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd228(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd228 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd229(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd229 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd230(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd230 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd231(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd231 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd232(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd232 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd233(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwSetRsvd233 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFlag2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwFlag2 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEECheckCRC2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.uwEECheckCRC2 = uwtemp;
    OS_EXIT_CRITICAL();
}
    
void sSetEEATE_SN1(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SN1 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SN2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SN2 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SN3(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SN3 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SN4(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SN4 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SN5(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SN5 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SNLen(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SNLen = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_DispHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_DispHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_CtrlHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_CtrlHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_PowerHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_PowerHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_UpdateFW(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_UpdateFW = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_ResetSystem(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_ResetSystem = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EEDefault(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EEDefault = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_AgingMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_AgingMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_RemoteOnOff(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_RemoteOnOff = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EEFactory(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EEFactory = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_AgingBattVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_AgingBattVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_AgingBattCurr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_AgingBattCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_AgingPVPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_AgingPVPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_AgingInvPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_AgingInvPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_MPPTVoltCntl(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_MPPTVoltCntl = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_E_totalClr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_E_totalClr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SafetyCode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_SafetyCode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_ISOsetting(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_ISOsetting = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterProc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterProc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_ExCommBps(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_ExCommBps = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterBps_Parity(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterBps_Parity = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterWREn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterWREn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterDataRegAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterDataRegAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterData(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_EleMeterData = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_485CommBps(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwATE_485CommBps = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEMenuRtnDftPageEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwMenuRtnDftPageEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELCDBacklight(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetLCDBacklight = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBuzzerBeep(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetBuzzerBeep = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBmsBagAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetBmsBagAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEClearEventLog(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetClearEventLog = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEventLogFunc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetEventLogFunc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFaultLogFunc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetFaultLogFunc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELogType(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetLogType = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELogIndex(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetLogIndex = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFlag3(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwFlag3 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEECheckCRC3(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwEECheckCRC3 = uwtemp;
    OS_EXIT_CRITICAL();
}




