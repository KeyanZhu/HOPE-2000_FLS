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
	1,			//	uwMachCode;				//	0 机型代码
	0,			//	uwEE_SN1;				//	1 机器序列号1
	0,			//	uwEE_SN2;				//	2 机器序列号2
	0,			//	uwEE_SN3;				//	3 机器序列号3
	0,			//	uwEE_SN4;				//	4 机器序列号4
	0,			//	uwEE_SN5;				//	5 机器序列号5
	18,			//	uwEE_SNLen;				//	6 机器序列号长度
	0,			//	uwEE_DispHwVer;			//	7 ATE写显示板版本号
	0,			//	uwEE_CtrlHwVer;			//	8 ATE写控制板版本号
	0,			//	uwEE_PowerHwVer;		//	9 ATE写功率板版本号
	4096,		//	uwEEPV1VoltAdj			//	10 PV1电压校准系数
	0,			//	uwEEPV1VoltBias 		//	11 PV1电压校准偏置
	4096,		//	uwEEPV2VoltAdj			//	12 PV2电压校准系数
	0,			//	uwEEPV2VoltBias 		//	13 PV2电压校准偏置
	4096,		//	uwEEPV1BatCurrAdj		//	14 PV1电流校准系数
	0,			//	uwEEPV1BatCurrBias		//	15 PV1电流校准偏置
	4096,		//	uwEEPV2BatCurrAdj		//	16 PV2电流校准系数
	0,			//	uwEEPV2BatCurrBias		//	17 PV2电流校准偏置
	4096,		//	uwEEBatVoltAdj			//	18 电池电压校准系数
	0,			//	uwEEBatVoltBias 		//	19 电池电压校准偏置
	4096,		//	uwEEBatCurrAdj			//	20 电池电流校准系数
	0,			//	uwEEBatCurrBias 		//	21 电池电流校准偏置
	4096,		//	uwEEBUSVoltAdj			//	22 Bus电压校准系数
	0,			//	uwEEBUSVoltBias 		//	23 Bus电压校准偏置
	4096,		//	uwEEBUSCurrAdj			//	24 Bus电流校准系数
	0,			//	uwEEBUSCurrBias 		//	25 Bus电流校准偏置
	4096,		//	uwEEInvVoltAdj			//	26 逆变电压校准系数
	0,			//	uwEEInvVoltBias 		//	27 逆变电压校准偏置
	4096,		//	uwEEInvCurrAdj			//	28 逆变电流校准系数
	0,			//	uwEEInvCurrBias 		//	29 逆变电流校准偏置
	4096,		//	uwEEGridVoltAdj 		//	30 电网电压校准系数
	0,			//	uwEEGridVoltBias		//	31 电网电压校准偏置
	4096,		//	uwEEGridCurrAdj 		//	32 电网电流校准系数
	0,			//	uwEEGridCurrBias		//	33 电网电流校准偏置
	4096,		//	uwEEOPVoltAdj			//	34 输出电压校准系数
	0,			//	uwEEOpVoltBias			//	35 输出电压校准偏置
	4096,		//	uwEEOPCurrAdj			//	36 输出电流校准系数
	0,			//	uwEEOpCurrBias			//	37 输出电流校准偏置
	0,			//	uwEEDischargeEneyCoeffH //	38 放电量校准高位
	0,			//	uwEEDischargeEneyCoeffL //	39 放电量校准低位
	0,			//	uwEEchargeEneyCoeffH	//	40 充电量校准高位
	0,			//	uwEEchargeEneyCoeffL	//	41 充电量校准低位
	4096,		//	uwEEGenVoltAdj; 		//	42 Gen电压校准系数
	0,			//	uwEEGenVoltBias; 		//	43 Gen电压校准偏置
	4096,		//	uwEEGenCurrAdj; 		//	44 Gen电流校准系数
	0,			//	uwEEGenCurrBias; 		//	45 Gen电流校准偏置
	0,			//	uwSetRsvd5; 			//	46 预留
	0,			//	uwSetRsvd6; 			//	47 预留
	0,			//	uwSetRsvd7; 			//	48 预留
	0,			//	uwSetRsvd8; 			//	49 预留
	0,			//	uwSetRsvd9; 			//	50 预留
	0,			//	uwSetRsvd10; 			//	51 预留
	0,			//	uwSetRsvd11; 			//	52 预留
	0,			//	uwSetRsvd12; 			//	53 预留
	0,			//	uwSetRsvd13; 			//	54 预留
	0,			//	uwSetRsvd14;			//	55 预留
	0,			//	uwSetRsvd15;			//	56 预留
	0,			//	uwSetRsvd16;			//	57 预留
	0,			//	uwSetRsvd17;			//	58 预留
	0,			//	uwSetRsvd18;			//	59 预留
	0,			//	uwSetRsvd19;			//	60 预留
	0,			//	uwSetRsvd20;			//	61 预留
	0,			//	uwSetRsvd21;			//	62 预留
	0,			//	uwSetRsvd22;			//	63 预留
	0,			//	uwSetRsvd23;			//	64 预留
	0,			//	uwSetRsvd24;			//	65 预留
	0,			//	uwSetRsvd25;			//	66 预留
	0,			//	uwSetRsvd26;			//	67 预留
	0,			//	uwSetRsvd27;			//	68 预留
	0,			//	uwSetRsvd28;			//	69 预留
	0,			//	uwSetRsvd29;			//	70 预留
	0,			//	uwSetRsvd30;			//	71 预留
	0,			//	uwSetRsvd31;			//	72 预留
	0,			//	uwSetRsvd32;			//	73 预留
	0,			//	uwSetRsvd33;			//	74 预留
	0,			//	uwSetRsvd34;			//	75 预留
	0,			//	uwSetRsvd35;			//	76 预留
	0,			//	uwSetRsvd36;			//	77 预留
	0,			//	uwSetRsvd37;			//	78 预留
	0,			//	uwSetRsvd38;			//	79 预留
	0,			//	uwSetRsvd39;			//	80 预留
	0,			//	uwSetRsvd40;			//	81 预留
	0,			//	uwSetRsvd41;			//	82 预留
	0,			//	uwSetRsvd42;			//	83 预留
	0,			//	uwSetRsvd43;			//	84 预留
	0,			//	uwSetRsvd44;			//	85 预留
	0,			//	uwSetRsvd45;			//	86 预留
	0,			//	uwSetRsvd46;			//	87 预留
	0,			//	uwSetRsvd47;			//	88 预留
	0,			//	uwSetRsvd48;			//	89 预留
	0,			//	uwSetRsvd49;			//	90 预留
	0,			//	uwSetRsvd50;			//	91 预留
	0,			//	uwSetRsvd51;			//	92 预留
	0,			//	uwSetRsvd52;			//	93 预留
	0xAAAA, 	//	uwFlag1 				//	184 EEPROM标志
	0			//	uwEECheckCRC1			//	185 CRC校验
};

const struct EepromStruct2 strEepromDefaultTable2 = 	
{
	//Control State
	0,			//	uwEEParallel;				//	96	并机使能
	0,			//	uwEEParalleltMasterSlaver;	//	97	并机角色 
	0,			//	uwEEParallelPhase; 			//	98	并机相位
	1,			//	uwEEParallelIID;			//	99	并机ID
	0,			//	uwSetSystemOutputMode;		//	100	系统输出模式
	0,			//	uwEEWorkMode;				//	101	工作模式
	cFanPerFormanceMode,//	uwEEFanWorkMode; 	//	102	风机运行模式
	1,			//	uwEEPowerConversion;		//	103	功率折算使能
	0,			//	uwEEPowerSaveMode;			//	104	节能模式
	0,			//	uwEENoBatMode;				//	105	无电池模式
	1,			//	uwEELogoEnable;				//	106	logo使能
	1,			//	uwEEAdcBiasAdj;				//	107	采样偏置校准
	0,			//	eSetLeakCurrProtectEnable;	//	108	漏电流GFCI保护使能
	0,			//	eSetLeakCurrProtectValue;	//	109	漏电流GFCI保护阀值
	0,			//	eSetISOCheckEnable;			//	110	绝缘阻抗检测使能
	0,			//	eSetISOCheckValue;			//	111	绝缘阻抗检测阀值
	0,			//	uwEERsvd17;					//	112 预留
	0,			//	uwEERsvd18;					//	113 预留
	0,			//	uwEERsvd19;					//	114 预留
	0,			//	uwEERsvd20;					//	115 预留
	0,			//	uwEERsvd21;					//	116 预留
	0,			//	uwEERsvd22;					//	117 预留
	0,			//	uwEERsvd23;					//	118 预留
	0,			//	uwEERsvd24;					//	119 预留
	0,			//	uwEERsvd25;					//	120 预留
	0,			//	uwEERsvd26;					//	121 预留
	0,			//	uwEERsvd27;					//	122 预留
	0,			//	uwEERsvd28;					//	123 预留
	0,			//	uwEERsvd29;					//	124 预留
	0,			//	uwEERsvd30;					//	125 预留
	0,			//	uwEERsvd31;					//	126 预留
	0,			//	uwEERsvd32;					//	127 预留

	//Battery
	2,			//	uwEEBatType;				//	128	电池类型
	2,			//	uwEEBatSeriesNum;			//	129	电池节数
	0,			//	uwEEBatActivate;			//	130	电池激活
	3140,		//	uwEEBatCapacity; 			//	131	电池容量
	1,			//	uwEELithiumMode; 			//	132	锂电池模式
	0,			//	uwEERsvd38; 				//	133 预留
	1600,		//	uwEEBatMaxChgCurr;			//	134	电池最大充电电流限幅值
	2200,		//	uwEEBatMaxDcgCurr;			//	135	电池最大放电电流限幅值
	cBatVoltReal3V3*cBatSerialPcs, 				//	uwEEBatVoltage;				//	136	电池额定电压(电池节数)
	0,			//	uwEERsvd42; 				//	137 预留
	1,			//	uwEEGridChargeEn;			//	138	市电充电使能
	1600,		//	uwEEGridMaxChargeCurr;		//	139	市电最大充电电流
	cBatVoltReal2V87*cBatSerialPcs, 			//	uwEEGridStartChargeVolt;	//	140	市电开始充电电池电压
	cBatVoltReal3V37*cBatSerialPcs, 			//	uwEEGridEndChargeVolt;		//	141	市电停止充电电池电压
	20, 		//	uwEEGridStartChargeSOC;		//	142	市电开始充电电池SOC
	80, 		//	uwEEGridEndChargeSOC; 		//	143	市电停止充电电池SOC
	0,			//	uwEERsvd49; 				//	144 预留
	0,			//	uwEEGenChargeEn;			//	145	油机充电使能
	0,			//	uwEEGenMaxChargeCurr;		//	146	油机最大充电电流
	0,			//	uwEEGenStartChargeVolt;		//	147	油机开始充电电池电压
	0,			//	uwEEGenEndChargeVolt;		//	148	油机停止充电电池电压
	0,			//	uwEEGenStartChargeSOC;		//	149	油机开始充电电池SOC
	0,			//	uwEEGenEndChargeSOC; 		//	150	油机停止充电电池SOC
	0,			//	uwEERsvd56; 				//	151 预留
	cBatVoltReal3V6*cBatSerialPcs, 				//	uwSetBatConstVolt;			//	152	电池恒压充电压
	cBatVoltReal3V4*cBatSerialPcs, 				//	uwSetBatFloatVolt;			//	153	电池浮充电压
	0,			//	uwSetBatFloatTime;			//	154	电池恒充时间
	5,			//	uwEEShutdownSOC;			//	155	电池停止输出SOC
	cBatVoltReal2V8*cBatSerialPcs, 			//	uwEEShutdownVolt;			//	156	电池停止输出电压
	15, 		//	uwEEBatRestartOutSOC; 		//	157	电池重启输出SOC恢复输出SOC
	cBatVoltReal2V87*cBatSerialPcs, 			//	uwEEBatRestartOutVolt;		//	158	电池重启输出电压恢复输出电压
	10, 		//	uwEELowBattSOC;				//	159	电池电量低电量SOC
	cBatVoltReal2V8*cBatSerialPcs,				//	uwEELowBattVolt; 			//	160	电池电量低电量电压
	0,			//	uwEERsvd66; 				//	161 预留
	0,			//	uwEERsvd67; 				//	162 预留
	0,			//	uwEEBattResistance; 		//	163 电池线路阻抗
	cBatVoltReal3V75*cBatSerialPcs,				//	uwSetBatVoltOverShut; 		//	164	电池过压保护点
	0,			//	uwSetBMSComErrEnable; 		//	165	BMS通讯故障使能？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
	0,			//	uwSetBatParaEnable;			//	166	电池并联使能
	0,			//	uwSetBatTempCompensateEnable; //167	电池温度补偿使能
	0,			//	uwSetBatTempCalibration; 	//	168	电池温度补偿系数
	0,			//	uwEERsvd74; 				//	169 预留
	0,			//	uwEERsvd75; 				//	170 预留
	0,			//	uwEEBatEqEn;				//	171	EQ使能
	cBatVoltReal3V65*cBatSerialPcs, 			//	uwEEBatEqVolt;				//	172	EQ电压
	60, 		//	uwEEBatEqTime;				//	173	EQ时间
	12,		    //	uwEEBatEqTimeout;			//	174	EQ超时时间
	30, 		//	uwEEBatEqInterval;			//	175	EQ间隔时间
	0,			//	uwEEBatEqActImd;			//	176	立即EQ使能
	0,			//	uwEERsvd82; 				//	177 预留
	0,			//	uwEERsvd83; 				//	178 预留
	1,			//	uwEEBatLowVoltDerateEnable; //	179	电池低压降额使能
	1,			//	uwEEBatPowerOutEn; 			//	180	电池出功使能
	1,			//	uwEEBMSErrStopEn; 			//	181	BMS异常停止工作
	1,			//	uwEESOCDisplayEn; 			//	182	主页显示SOC
	0,			//	uwEERsvd88; 				//	183 预留
	0,			//	uwEERsvd89; 				//	184 预留
	0,			//	uwEERsvd90; 				//	185 预留
	0,			//	uwEERsvd91; 				//	186 预留
	0,			//	uwEERsvd92; 				//	187 预留
	0,			//	uwEERsvd93; 				//	188 预留
	0,			//	uwEERsvd94; 				//	189 预留
	0,			//	uwEERsvd95; 				//	190 预留
	0,			//	uwEERsvd96; 				//	191 预留
	0,			//	uwBattAhReal; 				//	192 电池剩余容量
	3140,		//	uwBattAhMax; 				//	193 电池最大容量
	0,			//	uwBattFullCnt; 				//	194 电池充满次数
	0,			//	uwBattEmptyCnt; 			//	195 电池放空次数
	0,			//	uwBattCycCnt; 				//	196 电池循环次数
	0,			//	uwBattAhRealShow; 			//	197 电池显示剩余容量？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
	1,			//	uwEESOCSmoothEn; 			//	198 SOC平滑使能
	0,			//	uwEERsvd104; 				//	199 预留
	0,			//	uwEERsvd105; 				//	200 预留
	0,			//	uwEERsvd106; 				//	201 预留
	0,			//	uwEERsvd107; 				//	202 预留
	0,			//	uwEERsvd108; 				//	203 预留
	0,			//	uwEERsvd109; 				//	204 预留
	0,			//	uwEERsvd110; 				//	205 预留
	0,			//	uwEERsvd111; 				//	206 预留
	0,			//	uwEERsvd112; 				//	207 预留
	0,			//	uwEERsvd113; 				//	208 预留
	0,			//	uwEERsvd114; 				//	209 预留
	0,			//	uwEERsvd115; 				//	210 预留
	0,			//	uwEERsvd116; 				//	211 预留
	0,			//	uwEERsvd117; 				//	212 预留
	0,			//	uwEERsvd118; 				//	213 预留
	0,			//	uwEERsvd119; 				//	214 预留
	0,			//	uwEERsvd120; 				//	215 预留
	0,			//	uwEERsvd121; 				//	216 预留
	0,			//	uwEERsvd122; 				//	217 预留
	0,			//	uwEERsvd123; 				//	218 预留
	0,			//	uwEERsvd124; 				//	219 预留
	0,			//	uwEERsvd125; 				//	220 预留
	0,			//	uwEERsvd126; 				//	221 预留
	0,			//	uwEERsvd127; 				//	222 预留
	0,			//	uwEERsvd128; 				//	223 预留

	//PV
	1250, 		//	uwEEPV1StartVolt;			//	224	PV1启动电压
	0, 			//	uwEEPV2StartVolt;			//	225	PV2启动电压
	2300,		//	uwEEPV1CurrrLimit;			//	226	PV1最大输入电流
	0, 			//	uwEEPV2CurrrLimit;			//	227	PV2最大输入电流
	600,		//	uwEEPV1PowerLimit;			//	228	PV1最大输入功率
	0, 			//	uwEEPV2PowerLimit;			//	229	PV2最大输入功率
	1, 			//	uwEEMpptMultiPoint;			//	230	多峰扫描
	0, 			//	uwEEPVInputMode;			//	231	PV输入模式
	0, 			//	uwEERsvd137; 				//	232 预留
	0, 			//	uwEERsvd138; 				//	233 预留
	0, 			//	uwEERsvd139; 				//	234 预留
	0, 			//	uwEERsvd140; 				//	235 预留
	0, 			//	uwEERsvd141; 				//	236 预留
	0, 			//	uwEERsvd142; 				//	237 预留
	0, 			//	uwEERsvd143; 				//	238 预留
	0, 			//	uwEERsvd144; 				//	239 预留

	//AC
	0,			//	uwEEGridInputRange;			//	240	电网输入范围
	1000,		//	uwEEACOutputRatedPower;		//	241	机器额定功率
	2200,		//	uwEEACOutputRatedVolt;		//	242	额定输出电压
	0,			//	uwEEACOutputRatedFreq;		//	243	额定输出频率
	1,			//	uwAutoInvEn;				//	244	开机自动逆变
	1,			//	uwDCDCOpenEn; 				//	245	DCDC开环使能
	0,			//	uwEERsvd151; 				//	246 预留
	0,			//	uwEERsvd152; 				//	247 预留
	1,			//	uwEEOverTempRestartEn;		//	248	过温重启使能
	1,			//	uwEEOverLoadRestartEn;		//	249	过载重启使能
	0,			//	uwEEOverLoadBypassEn;		//	250	过载转旁路使能
	0,			//	uwEERsvd156; 				//	251 预留
	0,			//	uwEERsvd157; 				//	252 预留
	0,			//	uwEERsvd158; 				//	253 预留
	0,			//	uwEEOnGridAlwayOn; 			//	254 市电常开（闭合）
	0,			//	uwEEOffGridImmediatelyOff; 	//	255 离网常断（断开）
	300,		//	uwEEPVPowerRlyOn; 			//	256 开启功率（PV）
	80,			//	uwEERlySocOn; 				//	257 锂电池模式下用SOC
	20,			//	uwEERlySocOff; 				//	258 锂电池模式下用SOC
	cBatVoltReal3V4*cBatSerialPcs,				//	uwEERlyVoltOn; 				//	259 自定义模式下用电压
	cBatVoltReal2V87*cBatSerialPcs,				//	uwEERlyVoltOff; 			//	260 自定义模式下用电压
	0,			//	uwEEOffGridWaitTime;		//	261	并网转离网等待时间
	15000,		//	uwEEOnGridWaitTime;			//	262	离网转并网等待时间
	0,			//	uwEEIslandCheckEn;			//	263	主动孤岛检测使能
	0,			//	uwEERsvd169; 				//	264 预留
	0,			//	uwEEGridFeedEn;				//	265	馈电使能
	0,			//	uwEEGridMaxInputPowerLimitEn;//	266	电网最大输入功率限制使能
	1000,		//	uwEEGridCurrLimit;			//	267	市电电流限制
	cInvWattMax,//	uwEEGridInputPower;			//	268	市电最大买电功率
	500,		//	uwEEGridFeedPower;			//	269	市电最大卖电功率,实际等于 uwMaxFeedPower - 200偏置 = 0W
	2650,		//	uwEEGridVoltUpperLimit;		//	270	电网电压上限
	900,		//	uwEEGridVoltLowerLimit;		//	271	电网电压下限
	0,			//	uwEERsvd177; 				//	272 预留
	0,			//	uwEERsvd178; 				//	273 预留
	50,			//	uwEEZeroExportPower;		//	274 零馈电功率
	0,			//	uwEEGridPeakShaving;		//	275 电网削峰使能
	2000,		//	uwEEGridPeakShavingPower;	//	276 电网削峰功率
	1,			//	uwEETurboMode;				//	277	Turbo模式使能
	0,			//	uwEETouMode;				//	278	Tou模式使能
	0,			//	uwEECloseGSRlyEn;			//	279	N对地继电器闭合使能
	0,			//	uwEEGridpowerslope;			//	280	并网功率斜率
	0,			//	uwEEGridpowerlimitation;	//	281	并网功率限制
	0,			//	uwPvAutoInvEn;				//	282	单PV无电池开机自动逆变使能,如果有电池此项不生效

	//Res 188~224
	0,			//	uwEERsvd188; 				//	283 预留
	0,			//	uwEERsvd189; 				//	284 预留
	0,			//	uwEERsvd190; 				//	285 预留
	0,			//	uwEERsvd191; 				//	286 预留
	0,			//	uwEERsvd192; 				//	287 预留
	0,			//	uwEERsvd193; 				//	288 预留
	0,			//	uwEERsvd194; 				//	289 预留
	0,			//	uwEERsvd195; 				//	290 预留
	0,			//	uwEERsvd196; 				//	291 预留
	0,			//	uwEERsvd197; 				//	292 预留
	0,			//	uwEERsvd198; 				//	293 预留
	0,			//	uwEERsvd199; 				//	294 预留
	0,			//	uwEERsvd200; 				//	295 预留
	0,			//	uwEERsvd201; 				//	296 预留
	0,			//	uwEERsvd202; 				//	297 预留
	0,			//	uwEERsvd203; 				//	298 预留
	0,			//	uwEERsvd204; 				//	299 预留
	0,			//	uwEERsvd205; 				//	300 预留
	0,			//	uwEERsvd206; 				//	301 预留
	0,			//	uwEERsvd207; 				//	302 预留
	0,			//	uwEERsvd208; 				//	303 预留
	0,			//	uwEERsvd209; 				//	304 预留
	0,			//	uwEERsvd210; 				//	305 预留
	0,			//	uwEERsvd211; 				//	306 预留
	0,			//	uwEERsvd212; 				//	307 预留
	0,			//	uwEERsvd213; 				//	308 预留
	0,			//	uwEERsvd214; 				//	309 预留
	0,			//	uwEERsvd215; 				//	310 预留
	0,			//	uwEERsvd216; 				//	311 预留
	0,			//	uwEERsvd217; 				//	312 预留
	0,			//	uwEERsvd218; 				//	313 预留
	0,			//	uwEERsvd219; 				//	314 预留
	0,			//	uwEERsvd220; 				//	315 预留
	0,			//	uwEERsvd221; 				//	316 预留
	0,			//	uwEERsvd222; 				//	317 预留
	0,			//	uwEERsvd223; 				//	318 预留
	0,			//	uwEERsvd224; 				//	319 预留

	//GEN
	0,			//	eSetGenMode; 				//	320 油机模式
	0,			//	eSetGenInputEn; 			//	321 油机输入使能
	0,			//	eSetGenInputMaxPower; 		//	322 油机输入最大功率
	0,			//	eSetGenConnectToGridPortEn; //	323 油机接入电网端口使能位
	0,			//	eSetSmartLoad_OpenPower; 	//	324 智能负载启动功率
	0,			//	eSetSmartLoad_StartBatVolt; //	325 智能负载闭合电池电压点
	0,			//	eSetSmartLoad_ExitBatVolt; 	//	326 智能负载断开电池电压点
	0,			//	eSetSmartLoad_StartSOC; 	//	327 智能负载闭合电池SOC点
	0,			//	eSetSmartLoad_ExitSOC; 		//	328 智能负载断开电池SOC点
	0,			//	eSetOnGrid_SmartLoadEn; 	//	329 电网正常启用智能负载使能位
	0,			//	eSetOffGrid_SmartLoadDis; 	//	330 电网异常禁用智能负载使能位
	0,			//	uwEEDry1ContactMode; 		//	331 干接点1模式
	0,			//	uwEEDry2ContactMode; 		//	332 干接点2模式

	//Res 238~304
	0,			//	uwEERsvd238; 				//	333 预留
	0,			//	uwEERsvd239; 				//	334 预留
	0,			//	uwEERsvd240; 				//	335 预留
	0,			//	uwEERsvd241; 				//	336 预留
	0,			//	uwEERsvd242; 				//	337 预留
	0,			//	uwEERsvd243; 				//	338 预留
	0,			//	uwEERsvd244; 				//	339 预留
	0,			//	uwEERsvd245; 				//	340 预留
	0,			//	uwEERsvd246; 				//	341 预留
	0,			//	uwEERsvd247; 				//	342 预留
	0,			//	uwEERsvd248; 				//	343 预留
	0,			//	uwEERsvd249; 				//	344 预留
	0,			//	uwEERsvd250; 				//	345 预留
	0,			//	uwEERsvd251; 				//	346 预留
	0,			//	uwEERsvd252; 				//	347 预留
	0,			//	uwEERsvd253; 				//	348 预留
	0,			//	uwEERsvd254; 				//	349 预留
	0,			//	uwEERsvd255; 				//	350 预留
	0,			//	uwEERsvd256; 				//	351 预留
	0,			//	uwEERsvd257; 				//	352 预留
	0,			//	uwEERsvd258; 				//	353 预留
	0,			//	uwEERsvd259; 				//	354 预留
	0,			//	uwEERsvd260; 				//	355 预留
	0,			//	uwEERsvd261; 				//	356 预留
	0,			//	uwEERsvd262; 				//	357 预留
	0,			//	uwEERsvd263; 				//	358 预留
	0,			//	uwEERsvd264; 				//	359 预留
	0,			//	uwEERsvd265; 				//	360 预留
	0,			//	uwEERsvd266; 				//	361 预留
	0,			//	uwEERsvd267; 				//	362 预留
	0,			//	uwEERsvd268; 				//	363 预留
	0,			//	uwEERsvd269; 				//	364 预留
	0,			//	uwEERsvd270; 				//	365 预留
	0,			//	uwEERsvd271; 				//	366 预留
	0,			//	uwEERsvd272; 				//	367 预留
	0,			//	uwEERsvd273; 				//	368 预留
	0,			//	uwEERsvd274; 				//	369 预留
	0,			//	uwEERsvd275; 				//	370 预留
	0,			//	uwEERsvd276; 				//	371 预留
	0,			//	uwEERsvd277; 				//	372 预留
	0,			//	uwEERsvd278; 				//	373 预留
	0,			//	uwEERsvd279; 				//	374 预留
	0,			//	uwEERsvd280; 				//	375 预留
	0,			//	uwEERsvd281; 				//	376 预留
	0,			//	uwEERsvd282; 				//	377 预留
	0,			//	uwEERsvd283; 				//	378 预留
	0,			//	uwEERsvd284; 				//	379 预留
	0,			//	uwEERsvd285; 				//	380 预留
	0,			//	uwEERsvd286; 				//	381 预留
	0,			//	uwEERsvd287; 				//	382 预留
	0,			//	uwEERsvd288; 				//	383 预留
	0,			//	uwEERsvd289; 				//	384 预留
	0,			//	uwEERsvd290; 				//	385 预留
	0,			//	uwEERsvd291; 				//	386 预留
	0,			//	uwEERsvd292; 				//	387 预留
	0,			//	uwEERsvd293; 				//	388 预留
	0,			//	uwEERsvd294; 				//	389 预留
	0,			//	uwEERsvd295; 				//	390 预留
	0,			//	uwEERsvd296; 				//	391 预留
	0,			//	uwEERsvd297; 				//	392 预留
	0,			//	uwEERsvd298; 				//	393 预留
	0,			//	uwEERsvd299; 				//	394 预留
	0,			//	uwEERsvd300; 				//	395 预留
	0,			//	uwEERsvd301; 				//	396 预留
	0,			//	uwEERsvd302; 				//	397 预留
	0,			//	uwEERsvd303; 				//	398 预留
	0,			//	uwEERsvd304; 				//	399 预留

	//ECO
	0,			//	uwSetECO_TimeOfUse			//	400 经济模式使能
	0,			//	uwSetECO_EffectiveWeek		//	401 生效星期
	0,			//	uwSetECO1_GridChargeEnable	//	402 规则1电网充电使能
	0,			//	uwSetECO1_GenChargeEnable	//	403 规则1油机充电使能
	0,			//	uwSetECO1_StartTime 		//	404 规则1起始时间
	0,			//	uwSetECO1_StopTime			//	405 规则1结束时间
	0,			//	uwSetECO1_Volt				//	406 规则1目标电压
	0,			//	uwSetECO1_SOC				//	407 规则1目标SOC（BMS连接采用）
	0,			//	uwSetECO1_Power 			//	408 规则1放电功率
	0,			//	uwSetECO1_WorkModeSet		//	409 规则1工作模式设定
	0,			//	uwSetECO2_GridChargeEnable	//	410 规则2电网充电使能
	0,			//	uwSetECO2_GenChargeEnable	//	411 规则2油机充电使能
	0,			//	uwSetECO2_StartTime 		//	412 规则2起始时间
	0,			//	uwSetECO2_StopTime			//	413 规则2结束时间
	0,			//	uwSetECO2_Volt				//	414 规则2目标电压
	0,			//	uwSetECO2_SOC				//	415 规则2目标SOC（BMS连接采用）
	0,			//	uwSetECO2_Power 			//	416 规则2放电功率
	0,			//	uwSetECO2_WorkModeSet		//	417 规则2工作模式设定
	0,			//	uwSetECO3_GridChargeEnable	//	418 规则3电网充电使能
	0,			//	uwSetECO3_GenChargeEnable	//	419 规则3油机充电使能
	0,			//	uwSetECO3_StartTime 		//	420 规则3起始时间
	0,			//	uwSetECO3_StopTime			//	421 规则3结束时间
	0,			//	uwSetECO3_Volt				//	422 规则3目标电压
	0,			//	uwSetECO3_SOC				//	423 规则3目标SOC（BMS连接采用）
	0,			//	uwSetECO3_Power 			//	424 规则3放电功率
	0,			//	uwSetECO3_WorkModeSet		//	425 规则3工作模式设定
	0,			//	uwSetECO4_GridChargeEnable	//	426 规则4电网充电使能
	0,			//	uwSetECO4_GenChargeEnable	//	427 规则4油机充电使能
	0,			//	uwSetECO4_StartTime 		//	428 规则4起始时间
	0,			//	uwSetECO4_StopTime			//	429 规则4结束时间
	0,			//	uwSetECO4_Volt				//	430 规则4目标电压
	0,			//	uwSetECO4_SOC				//	431 规则4目标SOC（BMS连接采用）
	0,			//	uwSetECO4_Power 			//	432 规则4放电功率
	0,			//	uwSetECO4_WorkModeSet		//	433 规则4工作模式设定
	0,			//	uwSetECO5_GridChargeEnable	//	434 规则5电网充电使能
	0,			//	uwSetECO5_GenChargeEnable	//	435 规则5油机充电使能
	0,			//	uwSetECO5_StartTime 		//	436 规则5起始时间
	0,			//	uwSetECO5_StopTime			//	437 规则5结束时间
	0,			//	uwSetECO5_Volt				//	438 规则5目标电压
	0,			//	uwSetECO5_SOC				//	439 规则5目标SOC（BMS连接采用）
	0,			//	uwSetECO5_Power 			//	440 规则5放电功率
	0,			//	uwSetECO5_WorkModeSet		//	441 规则5工作模式设定
	0,			//	uwSetECO6_GridChargeEnable	//	442 规则6电网充电使能
	0,			//	uwSetECO6_GenChargeEnable	//	443 规则6油机充电使能
	0,			//	uwSetECO6_StartTime 		//	444 规则6起始时间
	0,			//	uwSetECO6_StopTime			//	445 规则6结束时间
	0,			//	uwSetECO6_Volt				//	446 规则6目标电压
	0,			//	uwSetECO6_SOC				//	447 规则6目标SOC（BMS连接采用）
	0,			//	uwSetECO6_Power 			//	448 规则6放电功率
	0,			//	uwSetECO6_WorkModeSet		//	449 规则6工作模式设定
	0,			//	uwSetECO7_GridChargeEnable	//	450 规则7电网充电使能
	0,			//	uwSetECO7_GenChargeEnable	//	451 规则7油机充电使能
	0,			//	uwSetECO7_StartTime 		//	452 规则7起始时间
	0,			//	uwSetECO7_StopTime			//	453 规则7结束时间
	0,			//	uwSetECO7_Volt				//	454 规则7目标电压
	0,			//	uwSetECO7_SOC				//	455 规则7目标SOC（BMS连接采用）
	0,			//	uwSetECO7_Power 			//	456 规则7放电功率
	0,			//	uwSetECO7_WorkModeSet		//	457 规则7工作模式设定
	0,			//	uwSetECO8_GridChargeEnable	//	458 规则8电网充电使能
	0,			//	uwSetECO8_GenChargeEnable	//	459 规则8油机充电使能
	0,			//	uwSetECO8_StartTime 		//	460 规则8起始时间
	0,			//	uwSetECO8_StopTime			//	461 规则8结束时间
	0,			//	uwSetECO8_Volt				//	462 规则8目标电压
	0,			//	uwSetECO8_SOC				//	463 规则8目标SOC（BMS连接采用）
	0,			//	uwSetECO8_Power 			//	464 规则8放电功率
	0,			//	uwSetECO8_WorkModeSet		//	465 规则8工作模式设定
	0,			//	uwEERsvd371;				//	466 预留
	0,			//	uwEERsvd372;				//	467 预留
	0,			//	uwATE_UpdateFW;				//	468 升级固件
	0,			//	uwATE_SafetyCode; 			//	469 安规设置
	0,			//	uwATE_ISOsetting;			//	470 绝缘阻抗设置
	0,			//	uwATE_EleMeterProc;			//	471 电表协议选择
	0,			//	uwATE_ExCommBps;			//	472 Wifi通讯地址和波特率
	0,			//	uwATE_EleMeterBps_Parity; 	//	473 与电表通讯波特率和校验位
	0,			//	uwATE_EleMeterAddr;			//	474 与电表通讯地址
	0,			//	uwATE_EleMeterWREn;			//	475 电表使能写，禁止读
	1,			//	uwATE_EleMeterDataRegAddr;	//	476 电表Modbus地址
	0,			//	uwATE_EleMeterData;			//	477 电表数据
	0,			//	uwATE_485CommBps; 			//	478 485通讯地址和波特率
	1,			//	uwMenuRtnDftPageEn;			//	479 菜单回退默认界面使能位
	1,			//	uwSetLCDBacklight;			//	480 LCD背光
	1,			//	uwSetBuzzerBeep;			//	481 蜂鸣器
	0,			//	uwEERsvd387; 				//	482 预留
	0,			//	uwEERsvd388; 				//	483 预留
	0,			//	uwEERsvd389; 				//	484 预留
	0,			//	uwEERsvd390; 				//	485 预留
	0,			//	uwEERsvd391; 				//	486 预留
	0,			//	uwEERsvd392; 				//	487 预留
	0,			//	uwEERsvd393; 				//	488 预留
	0,			//	uwEERsvd394; 				//	489 预留
	0,			//	uwEERsvd395; 				//	490 预留
	0,			//	uwEERsvd396; 				//	491 预留
	0,			//	uwEERsvd397; 				//	492 预留
	0,			//	uwEERsvd398; 				//	493 预留
	0,			//	uwEERsvd399; 				//	494 预留
	0,			//	uwEERsvd400; 				//	495 预留
	0,			//	uwEERsvd401; 				//	496 预留
	0,			//	uwEERsvd402; 				//	497 预留
	0,			//	uwEERsvd403; 				//	498 预留
	0,			//	uwEERsvd404; 				//	499 预留
	0,			//	uwEERsvd405; 				//	500 预留
	0,			//	uwEERsvd406; 				//	501 预留
	0,			//	uwEERsvd407; 				//	502 预留
	0,			//	uwEERsvd408; 				//	503 预留
	0,			//	uwEERsvd409; 				//	504 预留
	0,			//	uwEERsvd410; 				//	505 预留
	0,			//	uwEERsvd411; 				//	506 预留
	0,			//	uwEERsvd412; 				//	507 预留
	0,			//	uwEERsvd413; 				//	508 预留
	0,			//	uwEERsvd414; 				//	509 预留
	0,			//	uwEERsvd415; 				//	510 预留
	0,			//	uwEERsvd416; 				//	511 预留
	0,			//	uwEERsvd417; 				//	512 预留
	0,			//	uwEERsvd418; 				//	513 预留
	0,			//	uwEERsvd419; 				//	514 预留
	0,			//	uwEERsvd420; 				//	515 预留
	0,			//	uwSetBmsBagAddr;			//	516 电池包地址
	0,			//	uwSetClearEventLog;			//	517 清除事件记录
	0,			//	uwSetEventLogFunc;			//	518 事件记录功能
	0,			//	uwSetFaultLogFunc;			//	519 故障记录功能
	0,			//	uwSetLogType; 				//	520 Log查询类型
	0,			//	uwSetLogIndex;				//	521 Log索引
	0,			//	uwEERsvd427; 				//	522 预留
	0,			//	uwEERsvd428; 				//	523 预留
	0,			//	uwEERsvd429; 				//	524 预留
	0,			//	uwEERsvd430; 				//	525 预留
	0,			//	uwEERsvd431; 				//	526 预留
	0,			//	uwEERsvd432; 				//	527 预留
	0,			//	uwEERsvd433; 				//	528 预留
	0,			//	uwEERsvd434; 				//	529 预留
	0,			//	uwEERsvd435; 				//	530 预留
	0,			//	uwEERsvd436; 				//	531 预留
	0xAAAA,		//	uwFlag2 					//	532 EEPROM标志
	0			//	uwEECheckCRC2				//	533 CRC校验
};

const struct EepromStruct3 strEepromDefaultTable3 = 	
{
	//LineProtect
	0,			//	uwSetGrid1OVValue		//	534 电网过压1段(%)
	0,			//	uwSetGrid1OVTime		//	535 电网过压1段时间(10ms)，最大655350ms,也就是655S
	0,			//	uwSetGrid2OVValue		//	536 电网过压2段(%)
	0,			//	uwSetGrid2OVTime		//	537 电网过压2段时间(10ms)
	0,			//	uwSetGrid3OVValue		//	538 电网过压3段(%)
	0,			//	uwSetGrid3OVTime		//	539 电网过压3段时间(10ms)
	0,			//	uwSetGrid1UVValue		//	540 电网欠压1段(%)
	0,			//	uwSetGrid1UVTime		//	541 电网欠压1段时间(10ms)
	0,			//	uwSetGrid2UVValue		//	542 电网欠压2段(%)
	0,			//	uwSetGrid2UVTime		//	543 电网欠压2段时间(10ms)
	0,			//	uwSetGrid3UVValue		//	544 电网欠压3段(%)
	0,			//	uwSetGrid3UVTime		//	545 电网欠压3段时间(10ms)
	0,			//	uwSetGrid1OFValue		//	546 电网过频1段(0.01Hz)
	0,			//	uwSetGrid1OFTime		//	547 电网过频1段时间(10ms)
	0,			//	uwSetGrid2OFValue		//	548 电网过频2段(0.01Hz)
	0,			//	uwSetGrid2OFTime		//	549 电网过频2段时间(10ms)
	0,			//	uwSetGrid3OFValue		//	550 电网过频3段(0.01Hz)
	0,			//	uwSetGrid3OFTime		//	551 电网过频3段时间(10ms)
	0,			//	uwSetGrid1UFValue		//	552 电网欠频1段(0.01Hz)
	0,			//	uwSetGrid1UFTime		//	553 电网欠频1段时间(10ms)
	0,			//	uwSetGrid2UFValue		//	554 电网欠频2段(0.01Hz)
	0,			//	uwSetGrid2UFTime		//	555 电网欠频2段时间(10ms)
	0,			//	uwSetGrid3UFValue		//	556 电网欠频3段(0.01Hz)
	0,			//	uwSetGrid3UFTime		//	557 电网欠频3段时间(10ms)
	0,			//	uwSetRsvd558			//	558 预留
	0,			//	uwSetRsvd559			//	559 预留
	0,			//	uwSetRsvd560			//	560 预留
	0,			//	uwSetRsvd561			//	561 预留
	0,			//	uwSetRsvd562			//	562 预留
	0,			//	uwSetRsvd563			//	563 预留
	0xAAAA,		//	uwFlag3 				//	564 EEPROM标志
	0			//	uwEECheckCRC3			//	565 CRC校验
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
			if(uEepromCfg1.EepromStructCfg1.uwFlag1 == 0xAAAA)
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
			if(uEepromCfg1.EepromStructCfg1.uwFlag1 == 0xAAAA)
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
			if(uEepromCfg2.EepromStructCfg2.strATESet.uwFlag2 == 0xAAAA)
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
			if(uEepromCfg2.EepromStructCfg2.strATESet.uwFlag2 == 0xAAAA)
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
	
	uEepromCfg1.EepromStructCfg1.uwEECheckCRC1 = 0;
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg1.wEepromCfg1, (cEepromTotalLength1/2 - 1));
	uEepromCfg1.EepromStructCfg1.uwEECheckCRC1 = CRC;
	
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
			if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom1Address,cEepromTotalLength1,uEepromCfg1Temp.EepromStructCfg1.uwEECheckCRC1))
			{
				bEepromSaveFlag |= 0x01;
				
				bCnt = 3;
				do
				{
					if(cEepromSuccess == sbEepromWrite(cEeprom1BackupAddress,cEepromTotalLength1,(INT8U *)uEepromCfg1Temp.wEepromCfg1))
					{
						if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom1BackupAddress,cEepromTotalLength1,uEepromCfg1Temp.EepromStructCfg1.uwEECheckCRC1))
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
	
	uEepromCfg2.EepromStructCfg2.strATESet.uwEECheckCRC2 = 0;
	CRC = swEEMultiDataCRC16((INT8U *)uEepromCfg2.wEepromCfg2, (cEepromTotalLength2/2 - 1));
	uEepromCfg2.EepromStructCfg2.strATESet.uwEECheckCRC2 = CRC;	
	
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
			if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom2Address,cEepromTotalLength2,uEepromCfg2Temp.EepromStructCfg2.strATESet.uwEECheckCRC2))
			{
				bEepromSaveFlag |= 0x04;
				
				bCnt = 3;
				do
				{
					if(cEepromSuccess == sbEepromWrite(cEeprom2BackupAddress,cEepromTotalLength2,(INT8U *)uEepromCfg2Temp.wEepromCfg2))
					{
						if(cEepromVerifyOK == sbEepromReadChkWR(cEeprom2BackupAddress,cEepromTotalLength2,uEepromCfg2Temp.EepromStructCfg2.strATESet.uwEECheckCRC2))
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
	if( CRC == uEepromCfg1.EepromStructCfg1.uwEECheckCRC1)
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
	if( CRC == uEepromCfg2.EepromStructCfg2.strATESet.uwEECheckCRC2)
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

	//EEPROM1
	if(suwGetEEMachineCode() > 9999)
	{
		sSetEEMachineCode(strEepromDefaultTable1.uwMachCode);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SN1() > 9999)
	{
		sSetEE_SN1(strEepromDefaultTable1.uwEE_SN1);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SN2() > 9999)
	{
		sSetEE_SN2(strEepromDefaultTable1.uwEE_SN2);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SN3() > 9999)
	{
		sSetEE_SN3(strEepromDefaultTable1.uwEE_SN3);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SN4() > 9999)
	{
		sSetEE_SN4(strEepromDefaultTable1.uwEE_SN4);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SN5() > 9999)
	{
		sSetEE_SN5(strEepromDefaultTable1.uwEE_SN5);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_SNLen() > 18)
	{
		sSetEE_SNLen(strEepromDefaultTable1.uwEE_SNLen);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_DispHwVer() != 0)
	{
		sSetEE_DispHwVer(strEepromDefaultTable1.uwEE_DispHwVer);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_CtrlHwVer() != cDspTempVersion)
	{
		sSetEE_CtrlHwVer(strEepromDefaultTable1.uwEE_CtrlHwVer);
		bEEPROM1Flag = true;
	}

	if(suwGetEE_PowerHwVer() != cDspTempVersion)
	{
		sSetEE_PowerHwVer(strEepromDefaultTable1.uwEE_PowerHwVer);
		bEEPROM1Flag = true;
	}
	
	if((suwGetEEPV1VoltAdj() < cEEAdjLimitLo) || (suwGetEEPV1VoltAdj() > cEEAdjLimitUp))
	{
		sSetEEPV1VoltAdj(strEepromDefaultTable1.uwEEPV1VoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV1VoltBias() < cEEBiasLimitLo) || (suwGetEEPV1VoltBias() > cEEBiasLimitUp))
	{
		sSetEEPV1VoltBias(strEepromDefaultTable1.uwEEPV1VoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV2VoltAdj() < cEEAdjLimitLo) || (suwGetEEPV2VoltAdj() > cEEAdjLimitUp))
	{
		sSetEEPV2VoltAdj(strEepromDefaultTable1.uwEEPV2VoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV2VoltBias() < cEEBiasLimitLo) || (suwGetEEPV2VoltBias() > cEEBiasLimitUp))
	{
		sSetEEPV2VoltBias(strEepromDefaultTable1.uwEEPV2VoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV1BatCurrAdj() < cEEAdjLimitLo) || (suwGetEEPV1BatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEPV1BatCurrAdj(strEepromDefaultTable1.uwEEPV1BatCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV1BatCurrBias() < cEEBiasLimitLo) || (suwGetEEPV1BatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEPV1BatCurrBias(strEepromDefaultTable1.uwEEPV1BatCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV2BatCurrAdj() < cEEAdjLimitLo) || (suwGetEEPV2BatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEPV2BatCurrAdj(strEepromDefaultTable1.uwEEPV2BatCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEPV2BatCurrBias() < cEEBiasLimitLo) || (suwGetEEPV2BatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEPV2BatCurrBias(strEepromDefaultTable1.uwEEPV2BatCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatVoltAdj() < cEEAdjLimitLo) || (suwGetEEBatVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEBatVoltAdj(strEepromDefaultTable1.uwEEBatVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatVoltBias() < cEEBiasLimitLo) || (suwGetEEBatVoltBias() > cEEBiasLimitUp))
	{
		sSetEEBatVoltBias(strEepromDefaultTable1.uwEEBatVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatCurrAdj() < cEEAdjLimitLo) || (suwGetEEBatCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEBatCurrAdj(strEepromDefaultTable1.uwEEBatCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBatCurrBias() < cEEBiasLimitLo) || (suwGetEEBatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBatCurrBias(strEepromDefaultTable1.uwEEBatCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBUSVoltAdj() < cEEAdjLimitLo) || (suwGetEEBUSVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEBUSVoltAdj(strEepromDefaultTable1.uwEEBUSVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBUSVoltBias() < cEEBiasLimitLo) || (suwGetEEBatCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBUSVoltBias(strEepromDefaultTable1.uwEEBUSVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBUSCurrAdj() < cEEAdjLimitLo) || (suwGetEEBUSCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEBUSCurrAdj(strEepromDefaultTable1.uwEEBUSCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEBUSCurrBias() < cEEBiasLimitLo) || (suwGetEEBUSCurrBias() > cEEBiasLimitUp))
	{
		sSetEEBUSCurrBias(strEepromDefaultTable1.uwEEBUSCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEInvVoltAdj() < cEEAdjLimitLo) || (suwGetEEInvVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEInvVoltAdj(strEepromDefaultTable1.uwEEInvVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEInvVoltBias() < cEEBiasLimitLo) || (suwGetEEInvVoltBias() > cEEBiasLimitUp))
	{
		sSetEEInvVoltBias(strEepromDefaultTable1.uwEEInvVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEInvCurrAdj() < cEEAdjLimitLo) || (suwGetEEInvCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEInvCurrAdj(strEepromDefaultTable1.uwEEInvCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEInvCurrBias() < cEEBiasLimitLo) || (suwGetEEInvCurrBias() > cEEBiasLimitUp))
	{
		sSetEEInvCurrBias(strEepromDefaultTable1.uwEEInvCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGridVoltAdj() < cEEAdjLimitLo) || (suwGetEEGridVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEGridVoltAdj(strEepromDefaultTable1.uwEEGridVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGridVoltBias() < cEEBiasLimitLo) || (suwGetEEGridVoltBias() > cEEBiasLimitUp))
	{
		sSetEEGridVoltBias(strEepromDefaultTable1.uwEEGridVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGridCurrAdj() < cEEAdjLimitLo) || (suwGetEEGridCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEGridCurrAdj(strEepromDefaultTable1.uwEEGridCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGridCurrBias() < cEEBiasLimitLo) || (suwGetEEGridCurrBias() > cEEBiasLimitUp))
	{
		sSetEEGridCurrBias(strEepromDefaultTable1.uwEEGridCurrBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOPVoltAdj() < cEEAdjLimitLo) || (suwGetEEOPVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEOPVoltAdj(strEepromDefaultTable1.uwEEOPVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOpVoltBias() < cEEBiasLimitLo) || (suwGetEEOpVoltBias() > cEEBiasLimitUp))
	{
		sSetEEOpVoltBias(strEepromDefaultTable1.uwEEOpVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOPCurrAdj() < cEEAdjLimitLo) || (suwGetEEOPCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEOPCurrAdj(strEepromDefaultTable1.uwEEOPCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEOpCurrBias() < cEEBiasLimitLo) || (suwGetEEOpCurrBias() > cEEBiasLimitUp))
	{
		sSetEEOpCurrBias(strEepromDefaultTable1.uwEEOpCurrBias);
		bEEPROM1Flag = true;
	}

	if(suwGetEEDischargeEneyCoeffH() != 0)
	{
		sSetEEDischargeEneyCoeffH(strEepromDefaultTable1.uwEEDischargeEneyCoeffH);
		bEEPROM1Flag = true;
	}

	if(suwGetEEDischargeEneyCoeffL() != 0)
	{
		sSetEEDischargeEneyCoeffL(strEepromDefaultTable1.uwEEDischargeEneyCoeffL);
		bEEPROM1Flag = true;
	}

	if(suwGetEEchargeEneyCoeffH() != 0)
	{
		sSetEEchargeEneyCoeffH(strEepromDefaultTable1.uwEEchargeEneyCoeffH);
		bEEPROM1Flag = true;
	}

	if(suwGetEEchargeEneyCoeffL() != 0)
	{
		sSetEEchargeEneyCoeffL(strEepromDefaultTable1.uwEEchargeEneyCoeffL);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGenVoltAdj() < cEEAdjLimitLo) || (suwGetEEGenVoltAdj() > cEEAdjLimitUp))
	{
		sSetEEGenVoltAdj(strEepromDefaultTable1.uwEEGenVoltAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGenVoltBias() < cEEBiasLimitLo) || (suwGetEEGenVoltBias() > cEEBiasLimitUp))
	{
		sSetEEGenVoltBias(strEepromDefaultTable1.uwEEGenVoltBias);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGenCurrAdj() < cEEAdjLimitLo) || (suwGetEEGenCurrAdj() > cEEAdjLimitUp))
	{
		sSetEEGenCurrAdj(strEepromDefaultTable1.uwEEGenCurrAdj);
		bEEPROM1Flag = true;
	}

	if((suwGetEEGenCurrBias() < cEEBiasLimitLo) || (suwGetEEGenCurrBias() > cEEBiasLimitUp))
	{
		sSetEEGenCurrBias(strEepromDefaultTable1.uwEEGenCurrBias);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd5() != 0)
	{
		sSetSetRsvd5(strEepromDefaultTable1.uwSetRsvd5);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd6() != 0)
	{
		sSetSetRsvd6(strEepromDefaultTable1.uwSetRsvd6);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd7() != 0)
	{
		sSetSetRsvd7(strEepromDefaultTable1.uwSetRsvd7);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd8() != 0)
	{
		sSetSetRsvd8(strEepromDefaultTable1.uwSetRsvd8);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd9() != 0)
	{
		sSetSetRsvd9(strEepromDefaultTable1.uwSetRsvd9);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd10() != 0)
	{
		sSetSetRsvd10(strEepromDefaultTable1.uwSetRsvd10);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd11() != 0)
	{
		sSetSetRsvd11(strEepromDefaultTable1.uwSetRsvd11);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd12() != 0)
	{
		sSetSetRsvd12(strEepromDefaultTable1.uwSetRsvd12);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd13() != 0)
	{
		sSetSetRsvd13(strEepromDefaultTable1.uwSetRsvd13);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd14() != 0)
	{
		sSetSetRsvd14(strEepromDefaultTable1.uwSetRsvd14);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd15() != 0)
	{
		sSetSetRsvd15(strEepromDefaultTable1.uwSetRsvd15);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd16() != 0)
	{
		sSetSetRsvd16(strEepromDefaultTable1.uwSetRsvd16);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd17() != 0)
	{
		sSetSetRsvd17(strEepromDefaultTable1.uwSetRsvd17);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd18() != 0)
	{
		sSetSetRsvd18(strEepromDefaultTable1.uwSetRsvd18);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd19() != 0)
	{
		sSetSetRsvd19(strEepromDefaultTable1.uwSetRsvd19);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd20() != 0)
	{
		sSetSetRsvd20(strEepromDefaultTable1.uwSetRsvd20);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd21() != 0)
	{
		sSetSetRsvd21(strEepromDefaultTable1.uwSetRsvd21);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd22() != 0)
	{
		sSetSetRsvd22(strEepromDefaultTable1.uwSetRsvd22);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd23() != 0)
	{
		sSetSetRsvd23(strEepromDefaultTable1.uwSetRsvd23);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd24() != 0)
	{
		sSetSetRsvd24(strEepromDefaultTable1.uwSetRsvd24);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd25() != 0)
	{
		sSetSetRsvd25(strEepromDefaultTable1.uwSetRsvd25);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd26() != 0)
	{
		sSetSetRsvd26(strEepromDefaultTable1.uwSetRsvd26);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd27() != 0)
	{
		sSetSetRsvd27(strEepromDefaultTable1.uwSetRsvd27);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd28() != 0)
	{
		sSetSetRsvd28(strEepromDefaultTable1.uwSetRsvd28);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd29() != 0)
	{
		sSetSetRsvd29(strEepromDefaultTable1.uwSetRsvd29);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd30() != 0)
	{
		sSetSetRsvd30(strEepromDefaultTable1.uwSetRsvd30);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd31() != 0)
	{
		sSetSetRsvd31(strEepromDefaultTable1.uwSetRsvd31);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd32() != 0)
	{
		sSetSetRsvd32(strEepromDefaultTable1.uwSetRsvd32);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd33() != 0)
	{
		sSetSetRsvd33(strEepromDefaultTable1.uwSetRsvd33);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd34() != 0)
	{
		sSetSetRsvd34(strEepromDefaultTable1.uwSetRsvd34);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd35() != 0)
	{
		sSetSetRsvd35(strEepromDefaultTable1.uwSetRsvd35);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd36() != 0)
	{
		sSetSetRsvd36(strEepromDefaultTable1.uwSetRsvd36);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd37() != 0)
	{
		sSetSetRsvd37(strEepromDefaultTable1.uwSetRsvd37);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd38() != 0)
	{
		sSetSetRsvd38(strEepromDefaultTable1.uwSetRsvd38);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd39() != 0)
	{
		sSetSetRsvd39(strEepromDefaultTable1.uwSetRsvd39);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd40() != 0)
	{
		sSetSetRsvd40(strEepromDefaultTable1.uwSetRsvd40);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd41() != 0)
	{
		sSetSetRsvd41(strEepromDefaultTable1.uwSetRsvd41);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd42() != 0)
	{
		sSetSetRsvd42(strEepromDefaultTable1.uwSetRsvd42);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd43() != 0)
	{
		sSetSetRsvd43(strEepromDefaultTable1.uwSetRsvd43);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd44() != 0)
	{
		sSetSetRsvd44(strEepromDefaultTable1.uwSetRsvd44);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd45() != 0)
	{
		sSetSetRsvd45(strEepromDefaultTable1.uwSetRsvd45);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd46() != 0)
	{
		sSetSetRsvd46(strEepromDefaultTable1.uwSetRsvd46);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd47() != 0)
	{
		sSetSetRsvd47(strEepromDefaultTable1.uwSetRsvd47);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd48() != 0)
	{
		sSetSetRsvd48(strEepromDefaultTable1.uwSetRsvd48);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd49() != 0)
	{
		sSetSetRsvd49(strEepromDefaultTable1.uwSetRsvd49);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd50() != 0)
	{
		sSetSetRsvd50(strEepromDefaultTable1.uwSetRsvd50);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd51() != 0)
	{
		sSetSetRsvd51(strEepromDefaultTable1.uwSetRsvd51);
		bEEPROM1Flag = true;
	}

	if(suwGetSetRsvd52() != 0)
	{
		sSetSetRsvd52(strEepromDefaultTable1.uwSetRsvd52);
		bEEPROM1Flag = true;
	}
	
	// EEPROM2
	if((suwGetEEParaEnable() != 0) && (suwGetEEParaEnable() != 1))
	{
		sSetEEParaEnable(strEepromDefaultTable2.strControlState.uwEEParallel);
		bEEPROM2Flag = true;
	}
	
	if((suwGetEEMasterSlaver() != 0) && (suwGetEEMasterSlaver() != 1))
	{
		sSetEEMasterSlaver(strEepromDefaultTable2.strControlState.uwEEParalleltMasterSlaver);
		bEEPROM2Flag = true;
	}

	if((suwGetEEParallelPhase() != 0) && (suwGetEEParallelPhase() != 1) && (suwGetEEParallelPhase() != 2))
	{
		sSetEEParallelPhase(strEepromDefaultTable2.strControlState.uwEEParallelPhase);
		bEEPROM2Flag = true;
	}

	if((suwGetEEParallelIID() < 1) || (suwGetEEParallelIID() > 16))
	{
		sSetEEParallelIID(strEepromDefaultTable2.strControlState.uwEEParallelIID);
		bEEPROM2Flag = true;
	}

	if(suwGetEESystemOutputMode() > 6)
	{
		sSetEESystemOutputMode(strEepromDefaultTable2.strControlState.uwSetSystemOutputMode);
		bEEPROM2Flag = true;
	}

	if(suwGetEEWorkMode() > 2)
	{
		sSetEEWorkMode(strEepromDefaultTable2.strControlState.uwEEWorkMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEEFanWorkMode() != cFanPerFormanceMode) && (suwGetEEFanWorkMode() != cFanPerSilentMode))
	//if(suwGetEEFanWorkMode() > cFanModeMax)
	{
		sSetEEFanWorkMode(strEepromDefaultTable2.strControlState.uwEEFanWorkMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPowerConversion() != 0) && (suwGetEEPowerConversion() != 1)) 	// 功率折算使能
	{
		sSetEEPowerConversion(strEepromDefaultTable2.strControlState.uwEEPowerConversion);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPowerSaveMode() != 0) && (suwGetEEPowerSaveMode() != 1))
	{
		sSetEEPowerSaveMode(strEepromDefaultTable2.strControlState.uwEEPowerSaveMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEENoBatMode() != 0) && (suwGetEENoBatMode() != 1))
	{
		sSetEENoBatMode(strEepromDefaultTable2.strControlState.uwEENoBatMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEELogoEnable() != 0) && (suwGetEELogoEnable() != 1))
	{
		sSetEELogoEnable(strEepromDefaultTable2.strControlState.uwEELogoEnable);
		bEEPROM2Flag = true;
	}

	if((suwGetEEAdcBiasAdj() != 0) && (suwGetEEAdcBiasAdj() != 1))
	{
		sSetEEAdcBiasAdj(strEepromDefaultTable2.strControlState.uwEEAdcBiasAdj);
		bEEPROM2Flag = true;
	}

	if(suwGetLeakCurrProtectEnable() != 0)
	{
		sSetLeakCurrProtectEnable(strEepromDefaultTable2.strControlState.eSetLeakCurrProtectEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetLeakCurrProtectValue() != 0)
	{
		sSetLeakCurrProtectValue(strEepromDefaultTable2.strControlState.eSetLeakCurrProtectValue);
		bEEPROM2Flag = true;
	}

	if(suwGetISOCheckEnable() != 0)
	{
		sSetISOCheckEnable(strEepromDefaultTable2.strControlState.eSetISOCheckEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetISOCheckValue() != 0)
	{
		sSetISOCheckValue(strEepromDefaultTable2.strControlState.eSetISOCheckValue);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd17() != 0)
	{
		sSetEERsvd17(strEepromDefaultTable2.strControlState.uwEERsvd17);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd18() != 0)
	{
		sSetEERsvd18(strEepromDefaultTable2.strControlState.uwEERsvd18);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd19() != 0)
	{
		sSetEERsvd19(strEepromDefaultTable2.strControlState.uwEERsvd19);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd20() != 0)
	{
		sSetEERsvd20(strEepromDefaultTable2.strControlState.uwEERsvd20);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd21() != 0)
	{
		sSetEERsvd21(strEepromDefaultTable2.strControlState.uwEERsvd21);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd22() != 0)
	{
		sSetEERsvd22(strEepromDefaultTable2.strControlState.uwEERsvd22);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd23() != 0)
	{
		sSetEERsvd23(strEepromDefaultTable2.strControlState.uwEERsvd23);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd24() != 0)
	{
		sSetEERsvd24(strEepromDefaultTable2.strControlState.uwEERsvd24);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd25() != 0)
	{
		sSetEERsvd25(strEepromDefaultTable2.strControlState.uwEERsvd25);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd26() != 0)
	{
		sSetEERsvd26(strEepromDefaultTable2.strControlState.uwEERsvd26);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd27() != 0)
	{
		sSetEERsvd27(strEepromDefaultTable2.strControlState.uwEERsvd27);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd28() != 0)
	{
		sSetEERsvd28(strEepromDefaultTable2.strControlState.uwEERsvd28);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd29() != 0)
	{
		sSetEERsvd29(strEepromDefaultTable2.strControlState.uwEERsvd29);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd30() != 0)
	{
		sSetEERsvd30(strEepromDefaultTable2.strControlState.uwEERsvd30);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd31() != 0)
	{
		sSetEERsvd31(strEepromDefaultTable2.strControlState.uwEERsvd31);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd32() != 0)
	{
		sSetEERsvd32(strEepromDefaultTable2.strControlState.uwEERsvd32);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatType() != 2) && (suwGetEEBatType() != 3))
	{
		sSetEEBatType(strEepromDefaultTable2.strBatData.uwEEBatType);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatSeriesNum() > 20)
	{
		sSetEEBatSeriesNum(strEepromDefaultTable2.strBatData.uwEEBatSeriesNum);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatActivateEnable() != 0) && (suwGetEEBatActivateEnable() != 1))
	{
		sSetEEBatActivateEnable(strEepromDefaultTable2.strBatData.uwEEBatActivate);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatCapacity() > 65535)
	{
		sSetEEBatCapacity(strEepromDefaultTable2.strBatData.uwEEBatCapacity);
		bEEPROM2Flag = true;
	}

	if(suwGetEELithiumMode() > 100)
	{
		sSetEELithiumMode(strEepromDefaultTable2.strBatData.uwEELithiumMode);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd38() != 0)
	{
		sSetEERsvd38(strEepromDefaultTable2.strBatData.uwEERsvd38);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd42() != 0)
	{
		sSetEERsvd42(strEepromDefaultTable2.strBatData.uwEERsvd42);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridChargeEn() != 0) && (suwGetEEGridChargeEn() != 1))
	{
		sSetEEGridChargeEn(strEepromDefaultTable2.strBatData.uwEEGridChargeEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEEOnGridBatAutoStartChgSOC() > 100) 
	{
		sSetEEOnGridBatAutoStartChgSOC(strEepromDefaultTable2.strBatData.uwEEGridStartChargeSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEOnGridBatExitAutoChgSOC() > 100) 
	{
		sSetEEOnGridBatExitAutoChgSOC(strEepromDefaultTable2.strBatData.uwEEGridEndChargeSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd49() != 0)
	{
		sSetEERsvd49(strEepromDefaultTable2.strBatData.uwEERsvd49);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGenChargeEn() != 0) && (suwGetEEGenChargeEn() != 1))
	{
		sSetEEGenChargeEn(strEepromDefaultTable2.strBatData.uwEEGenChargeEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGenMaxChargeCurr() != 0)
	{
		sSetEEGenMaxChargeCurr(strEepromDefaultTable2.strBatData.uwEEGenMaxChargeCurr);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGenStartChargeVolt() != 0)
	{
		sSetEEGenStartChargeVolt(strEepromDefaultTable2.strBatData.uwEEGenStartChargeVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGenEndChargeVolt() != 0)
	{
		sSetEEGenEndChargeVolt(strEepromDefaultTable2.strBatData.uwEEGenEndChargeVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGenStartChargeSOC() > 100) 
	{
		sSetEEGenStartChargeSOC(strEepromDefaultTable2.strBatData.uwEEGenStartChargeSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGenStartChargeSOC() > 100) 
	{
		sSetEEGenEndChargeSOC(strEepromDefaultTable2.strBatData.uwEEGenEndChargeSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd56() != 0)
	{
		sSetEERsvd56(strEepromDefaultTable2.strBatData.uwEERsvd56);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatFloatTime() > 100)		//100min
	{
		sSetEEBatFloatTime(strEepromDefaultTable2.strBatData.uwSetBatFloatTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatLowShutDownSOC() > 100) 
	{
		sSetEEBatLowShutDownSOC(strEepromDefaultTable2.strBatData.uwEEShutdownSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatACRestartSOC() > 100) 
	{
		sSetEEBatACRestartSOC(strEepromDefaultTable2.strBatData.uwEEBatRestartOutSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatLowAlarmSOC() > 100) 
	{
		sSetEEBatLowAlarmSOC(strEepromDefaultTable2.strBatData.uwEELowBattSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd66() != 0)
	{
		sSetEERsvd66(strEepromDefaultTable2.strBatData.uwEERsvd66);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd67() != 0)
	{
		sSetEERsvd67(strEepromDefaultTable2.strBatData.uwEERsvd67);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattResistance() > 200)
	{
		sSetEEBattResistance(strEepromDefaultTable2.strBatData.uwEEBattResistance);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBMSComErrEnable() != 0) && (suwGetEEBMSComErrEnable() != 1))
	{
		sSetEEBMSComErrEnable(strEepromDefaultTable2.strBatData.uwSetBMSComErrEnable);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatParaEnable() != 0) && (suwGetEEBatParaEnable() != 1))
	{
		sSetEEBatParaEnable(strEepromDefaultTable2.strBatData.uwSetBatParaEnable);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatTempCompensateEnable() != 0) && (suwGetEEBatTempCompensateEnable() != 1))
	{
		sSetEEBatTempCompensateEnable(strEepromDefaultTable2.strBatData.uwSetBatTempCompensateEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetBatTempCalibration() > 65535)
	{
		sSetBatTempCalibration(strEepromDefaultTable2.strBatData.uwSetBatTempCalibration);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd74() != 0)
	{
		sSetEERsvd74(strEepromDefaultTable2.strBatData.uwEERsvd74);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd75() != 0)
	{
		sSetEERsvd75(strEepromDefaultTable2.strBatData.uwEERsvd75);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatEqEn() != 0) && (suwGetEEBatEqEn() != 1))
	{
		sSetEEBatEqEn(strEepromDefaultTable2.strBatData.uwEEBatEqEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatEqTime() > 900 )	//min
	{
		sSetEEBatEqTime(strEepromDefaultTable2.strBatData.uwEEBatEqTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatEqTimeout() > 900 )	//min
	{
		sSetEEBatEqTimeout(strEepromDefaultTable2.strBatData.uwEEBatEqTimeout);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatEqInterval() > 900 )	//min
	{
		sSetEEBatEqInterval(strEepromDefaultTable2.strBatData.uwEEBatEqInterval);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatEqActImd() != 0) && (suwGetEEBatEqActImd() != 1))	
	{
		sSetEEBatEqActImd(strEepromDefaultTable2.strBatData.uwEEBatEqActImd);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd82() != 0)
	{
		sSetEERsvd82(strEepromDefaultTable2.strBatData.uwEERsvd82);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd83() != 0)
	{
		sSetEERsvd83(strEepromDefaultTable2.strBatData.uwEERsvd83);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatLowVoltDerateEnable() != 0) && (suwGetEEBatLowVoltDerateEnable() != 1))
	{
		sSetEEBatLowVoltDerateEnable(strEepromDefaultTable2.strBatData.uwEEBatLowVoltDerateEnable);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatPowerOutEn() != 0) && (suwGetEEBatPowerOutEn() != 1))
	{
		sSetEEBatPowerOutEn(strEepromDefaultTable2.strBatData.uwEEBatPowerOutEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBMSErrStopEn() != 0) && (suwGetEEBMSErrStopEn() != 1))
	{
		sSetEEBMSErrStopEn(strEepromDefaultTable2.strBatData.uwEEBMSErrStopEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEESOCDisplayEn() != 0) && (suwGetEESOCDisplayEn() != 1))
	{
		sSetEESOCDisplayEn(strEepromDefaultTable2.strBatData.uwEESOCDisplayEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd88() != 0)
	{
		sSetEERsvd88(strEepromDefaultTable2.strBatData.uwEERsvd88);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd89() != 0)
	{
		sSetEERsvd89(strEepromDefaultTable2.strBatData.uwEERsvd89);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd90() != 0)
	{
		sSetEERsvd90(strEepromDefaultTable2.strBatData.uwEERsvd90);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd91() != 0)
	{
		sSetEERsvd91(strEepromDefaultTable2.strBatData.uwEERsvd91);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd92() != 0)
	{
		sSetEERsvd92(strEepromDefaultTable2.strBatData.uwEERsvd92);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd93() != 0)
	{
		sSetEERsvd93(strEepromDefaultTable2.strBatData.uwEERsvd93);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd94() != 0)
	{
		sSetEERsvd94(strEepromDefaultTable2.strBatData.uwEERsvd94);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd95() != 0)
	{
		sSetEERsvd95(strEepromDefaultTable2.strBatData.uwEERsvd95);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd96() != 0)
	{
		sSetEERsvd96(strEepromDefaultTable2.strBatData.uwEERsvd96);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattAhReal() >= 3140)
	{
		sSetEEBattAhReal(strEepromDefaultTable2.strBatData.uwBattAhReal);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattAhMax() >= 3140)
	{
		sSetEEBattAhMax(strEepromDefaultTable2.strBatData.uwBattAhMax);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattFullCnt() >= 0XFFFF)
	{
		sSetEEBattFullCnt(strEepromDefaultTable2.strBatData.uwBattFullCnt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattEmptyCnt() >= 0XFFFF)
	{
		sSetEEBattEmptyCnt(strEepromDefaultTable2.strBatData.uwBattEmptyCnt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattCycCnt() >= 0XFFFF)
	{
		sSetEEBattCycCnt(strEepromDefaultTable2.strBatData.uwBattCycCnt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBattAhRealShow() >= 3140)
	{
		sSetEEBattAhRealShow(strEepromDefaultTable2.strBatData.uwBattAhRealShow);
		bEEPROM2Flag = true;
	}

	if(suwGetEESOCSmoothEn() >= 1)
	{
		sSetEESOCSmoothEn(strEepromDefaultTable2.strBatData.uwEESOCSmoothEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd104() != 0)
	{
		sSetEERsvd104(strEepromDefaultTable2.strBatData.uwEERsvd104);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd105() != 0)
	{
		sSetEERsvd105(strEepromDefaultTable2.strBatData.uwEERsvd105);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd106() != 0)
	{
		sSetEERsvd106(strEepromDefaultTable2.strBatData.uwEERsvd106);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd107() != 0)
	{
		sSetEERsvd107(strEepromDefaultTable2.strBatData.uwEERsvd107);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd108() != 0)
	{
		sSetEERsvd108(strEepromDefaultTable2.strBatData.uwEERsvd108);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd109() != 0)
	{
		sSetEERsvd109(strEepromDefaultTable2.strBatData.uwEERsvd109);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd110() != 0)
	{
		sSetEERsvd110(strEepromDefaultTable2.strBatData.uwEERsvd110);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd111() != 0)
	{
		sSetEERsvd111(strEepromDefaultTable2.strBatData.uwEERsvd111);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd112() != 0)
	{
		sSetEERsvd112(strEepromDefaultTable2.strBatData.uwEERsvd112);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd113() != 0)
	{
		sSetEERsvd113(strEepromDefaultTable2.strBatData.uwEERsvd113);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd114() != 0)
	{
		sSetEERsvd114(strEepromDefaultTable2.strBatData.uwEERsvd114);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd115() != 0)
	{
		sSetEERsvd115(strEepromDefaultTable2.strBatData.uwEERsvd115);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd116() != 0)
	{
		sSetEERsvd116(strEepromDefaultTable2.strBatData.uwEERsvd116);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd117() != 0)
	{
		sSetEERsvd117(strEepromDefaultTable2.strBatData.uwEERsvd117);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd118() != 0)
	{
		sSetEERsvd118(strEepromDefaultTable2.strBatData.uwEERsvd118);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd119() != 0)
	{
		sSetEERsvd119(strEepromDefaultTable2.strBatData.uwEERsvd119);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd120() != 0)
	{
		sSetEERsvd120(strEepromDefaultTable2.strBatData.uwEERsvd120);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd121() != 0)
	{
		sSetEERsvd121(strEepromDefaultTable2.strBatData.uwEERsvd121);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd122() != 0)
	{
		sSetEERsvd122(strEepromDefaultTable2.strBatData.uwEERsvd122);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd123() != 0)
	{
		sSetEERsvd123(strEepromDefaultTable2.strBatData.uwEERsvd123);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd124() != 0)
	{
		sSetEERsvd124(strEepromDefaultTable2.strBatData.uwEERsvd124);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd125() != 0)
	{
		sSetEERsvd125(strEepromDefaultTable2.strBatData.uwEERsvd125);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd126() != 0)
	{
		sSetEERsvd126(strEepromDefaultTable2.strBatData.uwEERsvd126);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd127() != 0)
	{
		sSetEERsvd127(strEepromDefaultTable2.strBatData.uwEERsvd127);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd128() != 0)
	{
		sSetEERsvd128(strEepromDefaultTable2.strBatData.uwEERsvd128);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV2StartVolt() != 0)
	{
		sSetEEPV2StartVolt(strEepromDefaultTable2.strPvData.uwEEPV2StartVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV1CurrrLimit() != 0)
	{
		sSetEEPV1CurrrLimit(strEepromDefaultTable2.strPvData.uwEEPV1CurrrLimit);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV2CurrrLimit() != 0)
	{
		sSetEEPV2CurrrLimit(strEepromDefaultTable2.strPvData.uwEEPV2CurrrLimit);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV2PowerLimit() != 0)
	{
		sSetEEPV2PowerLimit(strEepromDefaultTable2.strPvData.uwEEPV2PowerLimit);
		bEEPROM2Flag = true;
	}

	if((suwGetEEMpptMultiPoint() != 0) && (suwGetEEMpptMultiPoint() != 1))
	{
		sSetEEMpptMultiPoint(strEepromDefaultTable2.strPvData.uwEEMpptMultiPoint);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPVInputMode() != 0) && (suwGetEEPVInputMode() != 1))
	{
		sSetEEPVInputMode(strEepromDefaultTable2.strPvData.uwEEPVInputMode);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd137() != 0)
	{
		sSetEERsvd137(strEepromDefaultTable2.strPvData.uwEERsvd137);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd138() != 0)
	{
		sSetEERsvd138(strEepromDefaultTable2.strPvData.uwEERsvd138);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd139() != 0)
	{
		sSetEERsvd139(strEepromDefaultTable2.strPvData.uwEERsvd139);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd140() != 0)
	{
		sSetEERsvd140(strEepromDefaultTable2.strPvData.uwEERsvd140);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd141() != 0)
	{
		sSetEERsvd141(strEepromDefaultTable2.strPvData.uwEERsvd141);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd142() != 0)
	{
		sSetEERsvd142(strEepromDefaultTable2.strPvData.uwEERsvd142);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd143() != 0)
	{
		sSetEERsvd143(strEepromDefaultTable2.strPvData.uwEERsvd143);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd144() != 0)
	{
		sSetEERsvd144(strEepromDefaultTable2.strPvData.uwEERsvd144);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridInputRange() != cAPL) && (suwGetEEGridInputRange() != cUPS) \
		&& (suwGetEEGridInputRange() != cGEN))
	{
		sSetEEGridInputRange(strEepromDefaultTable2.strAcData.uwEEGridInputRange);
		bEEPROM2Flag = true;
	}
	
	// 0：cFreq50hzConst
	// 1：cFreq60hzConst	
	if((suwGetEEACOutputRatedFreq() != 0) \
		&& (suwGetEEACOutputRatedFreq() != 1))
	{
		sSetEEACOutputRatedFreq(strEepromDefaultTable2.strAcData.uwEEACOutputRatedFreq);
		bEEPROM2Flag = true;
	}

	if((suwGetEEAutoInvEnable() != 0) && (suwGetEEAutoInvEnable() != 1))
	{
		sSetEEAutoInvEnable(strEepromDefaultTable2.strAcData.uwAutoInvEn);
		bEEPROM2Flag = true;
	}	

	if((suwGetEEDCDCOpenLoopEnable() != 0) && (suwGetEEDCDCOpenLoopEnable() != 1))
	{
		sSetEEDCDCOpenLoopEnable(strEepromDefaultTable2.strAcData.uwDCDCOpenEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd151() != 0)
	{
		sSetEERsvd151(strEepromDefaultTable2.strAcData.uwEERsvd151);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd152() != 0)
	{
		sSetEERsvd152(strEepromDefaultTable2.strAcData.uwEERsvd152);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOverTempRestartEn() != 0) && (suwGetEEOverTempRestartEn() != 1))
	{
		sSetEEOverTempRestartEn(strEepromDefaultTable2.strAcData.uwEEOverTempRestartEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOverLoadRestartEn() != 0) && (suwGetEEOverLoadRestartEn() != 1))
	{
		sSetEEOverLoadRestartEn(strEepromDefaultTable2.strAcData.uwEEOverLoadRestartEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOverLoadBypassEn() != 0) && (suwGetEEOverLoadBypassEn() != 1))
	{
		sSetEEOverLoadBypassEn(strEepromDefaultTable2.strAcData.uwEEOverLoadBypassEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd156() != 0)
	{
		sSetEERsvd156(strEepromDefaultTable2.strAcData.uwEERsvd156);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd157() != 0)
	{
		sSetEERsvd157(strEepromDefaultTable2.strAcData.uwEERsvd157);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd158() != 0)
	{
		sSetEERsvd158(strEepromDefaultTable2.strAcData.uwEERsvd158);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOnGridAlwayOn() != 0) && (suwGetEEOnGridAlwayOn() != 1))
	{
		sSetEEOnGridAlwayOn(strEepromDefaultTable2.strAcData.uwEEOnGridAlwayOn);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOffGridImmediatelyOff() != 0) && (suwGetEEOffGridImmediatelyOff() != 1))
	{
		sSetEEOffGridImmediatelyOff(strEepromDefaultTable2.strAcData.uwEEOffGridImmediatelyOff);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPVPowerRlyOn() > 6400)
	{
		sSetEEPVPowerRlyOn(strEepromDefaultTable2.strAcData.uwEEPVPowerRlyOn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERlySocOn() > 100)
	{
		sSetEERlySocOn(strEepromDefaultTable2.strAcData.uwEERlySocOn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERlySocOff() > 100)
	{
		sSetEERlySocOff(strEepromDefaultTable2.strAcData.uwEERlySocOff);
		bEEPROM2Flag = true;
	}

	if(suwGetEEOffGridWaitTime() > 60000) 
	{
		sSetEEOffGridWaitTime(strEepromDefaultTable2.strAcData.uwEEOffGridWaitTime);
		bEEPROM2Flag = true;
	}

	// 离网转并网时间 默认是15000.范围0-60000
	if(suwGetEEOnGridWaitTime() > 60000) 
	{
		sSetEEOnGridWaitTime(strEepromDefaultTable2.strAcData.uwEEOnGridWaitTime);
		bEEPROM2Flag = true;
	}

	if((suwGetEEAnti_IslandProtectEnable() != 0) && (suwGetEEAnti_IslandProtectEnable() != 1))
	{
		sSetEEAnti_IslandProtectEnable(strEepromDefaultTable2.strAcData.uwEEIslandCheckEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd169() != 0)
	{
		sSetEERsvd169(strEepromDefaultTable2.strAcData.uwEERsvd169);
		bEEPROM2Flag = true;
	}

	if((suwGetEEFeedEnable() != 0) && (suwGetEEFeedEnable() != 1))
	{
		sSetEEFeedEnable(strEepromDefaultTable2.strAcData.uwEEGridFeedEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridMaxInputPowerLimitEn() != 0) && (suwGetEEGridMaxInputPowerLimitEn() != 1))
	{
		sSetEEGridMaxInputPowerLimitEn(strEepromDefaultTable2.strAcData.uwEEGridMaxInputPowerLimitEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd177() != 0)
	{
		sSetEERsvd177(strEepromDefaultTable2.strAcData.uwEERsvd177);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd178() != 0)
	{
		sSetEERsvd178(strEepromDefaultTable2.strAcData.uwEERsvd178);
		bEEPROM2Flag = true;
	}

	if(suwGetEEZeroExportPower() > 100)
	{
		sSetEEZeroExportPower(strEepromDefaultTable2.strAcData.uwEEZeroExportPower);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridPeakShavingEnable() != 0) && (suwGetEEGridPeakShavingEnable() != 1))
	{
		sSetEEGridPeakShavingEnable(strEepromDefaultTable2.strAcData.uwEEGridPeakShaving);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridPeakShavingPower() > 7500)
	{
		sSetEEGridPeakShavingPower(strEepromDefaultTable2.strAcData.uwEEGridPeakShavingPower);
		bEEPROM2Flag = true;
	}

	if((suwGetEETurboMode() != 0) && (suwGetEETurboMode() != 1))
	{
		sSetEETurboMode(strEepromDefaultTable2.strAcData.uwEETurboMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEETouMode() != 0) && (suwGetEETouMode() != 1))
	{
		sSetEETouMode(strEepromDefaultTable2.strAcData.uwEETouMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEECloseGSRlyEn() != 0) && (suwGetEECloseGSRlyEn() != 1))
	{
		sSetEECloseGSRlyEn(strEepromDefaultTable2.strAcData.uwEECloseGSRlyEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridpowerslope() > 65535)
	{
		sSetEEGridpowerslope(strEepromDefaultTable2.strAcData.uwEEGridpowerslope);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridpowerlimitation() > 1200)
	{
		sSetEEGridpowerlimitation(strEepromDefaultTable2.strAcData.uwEEGridpowerlimitation);
		bEEPROM2Flag = true;
	}

	if((suwGetEEPVAutoInvEnable() != 0) && (suwGetEEPVAutoInvEnable() != 1))
	{
		sSetEEPVAutoInvEnable(strEepromDefaultTable2.strAcData.uwPvAutoInvEn);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd188() != 0)
	{
		sSetEERsvd188(strEepromDefaultTable2.strAcData.uwEERsvd188);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd189() != 0)
	{
		sSetEERsvd189(strEepromDefaultTable2.strAcData.uwEERsvd189);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd190() != 0)
	{
		sSetEERsvd190(strEepromDefaultTable2.strAcData.uwEERsvd190);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd191() != 0)
	{
		sSetEERsvd191(strEepromDefaultTable2.strAcData.uwEERsvd191);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd192() != 0)
	{
		sSetEERsvd192(strEepromDefaultTable2.strAcData.uwEERsvd192);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd193() != 0)
	{
		sSetEERsvd193(strEepromDefaultTable2.strAcData.uwEERsvd193);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd194() != 0)
	{
		sSetEERsvd194(strEepromDefaultTable2.strAcData.uwEERsvd194);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd195() != 0)
	{
		sSetEERsvd195(strEepromDefaultTable2.strAcData.uwEERsvd195);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd196() != 0)
	{
		sSetEERsvd196(strEepromDefaultTable2.strAcData.uwEERsvd196);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd197() != 0)
	{
		sSetEERsvd197(strEepromDefaultTable2.strAcData.uwEERsvd197);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd198() != 0)
	{
		sSetEERsvd198(strEepromDefaultTable2.strAcData.uwEERsvd198);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd199() != 0)
	{
		sSetEERsvd199(strEepromDefaultTable2.strAcData.uwEERsvd199);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd200() != 0)
	{
		sSetEERsvd200(strEepromDefaultTable2.strAcData.uwEERsvd200);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd201() != 0)
	{
		sSetEERsvd201(strEepromDefaultTable2.strAcData.uwEERsvd201);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd202() != 0)
	{
		sSetEERsvd202(strEepromDefaultTable2.strAcData.uwEERsvd202);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd203() != 0)
	{
		sSetEERsvd203(strEepromDefaultTable2.strAcData.uwEERsvd203);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd204() != 0)
	{
		sSetEERsvd204(strEepromDefaultTable2.strAcData.uwEERsvd204);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd205() != 0)
	{
		sSetEERsvd205(strEepromDefaultTable2.strAcData.uwEERsvd205);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd206() != 0)
	{
		sSetEERsvd206(strEepromDefaultTable2.strAcData.uwEERsvd206);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd207() != 0)
	{
		sSetEERsvd207(strEepromDefaultTable2.strAcData.uwEERsvd207);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd208() != 0)
	{
		sSetEERsvd208(strEepromDefaultTable2.strAcData.uwEERsvd208);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd209() != 0)
	{
		sSetEERsvd209(strEepromDefaultTable2.strAcData.uwEERsvd209);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd210() != 0)
	{
		sSetEERsvd210(strEepromDefaultTable2.strAcData.uwEERsvd210);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd211() != 0)
	{
		sSetEERsvd211(strEepromDefaultTable2.strAcData.uwEERsvd211);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd212() != 0)
	{
		sSetEERsvd212(strEepromDefaultTable2.strAcData.uwEERsvd212);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd213() != 0)
	{
		sSetEERsvd213(strEepromDefaultTable2.strAcData.uwEERsvd213);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd214() != 0)
	{
		sSetEERsvd214(strEepromDefaultTable2.strAcData.uwEERsvd214);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd215() != 0)
	{
		sSetEERsvd215(strEepromDefaultTable2.strAcData.uwEERsvd215);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd216() != 0)
	{
		sSetEERsvd216(strEepromDefaultTable2.strAcData.uwEERsvd216);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd217() != 0)
	{
		sSetEERsvd217(strEepromDefaultTable2.strAcData.uwEERsvd217);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd218() != 0)
	{
		sSetEERsvd218(strEepromDefaultTable2.strAcData.uwEERsvd218);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd219() != 0)
	{
		sSetEERsvd219(strEepromDefaultTable2.strAcData.uwEERsvd219);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd220() != 0)
	{
		sSetEERsvd220(strEepromDefaultTable2.strAcData.uwEERsvd220);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd221() != 0)
	{
		sSetEERsvd221(strEepromDefaultTable2.strAcData.uwEERsvd221);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd222() != 0)
	{
		sSetEERsvd222(strEepromDefaultTable2.strAcData.uwEERsvd222);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd223() != 0)
	{
		sSetEERsvd223(strEepromDefaultTable2.strAcData.uwEERsvd223);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd224() != 0)
	{
		sSetEERsvd224(strEepromDefaultTable2.strAcData.uwEERsvd224);
		bEEPROM2Flag = true;
	}

	if(suwGetGenMode() > 2)
	{
		sSetGenMode(strEepromDefaultTable2.strAcData.eSetGenMode);
		bEEPROM2Flag = true;
	}

	if(suwGetGenInputEn() != 0)
	{
		sSetGenInputEn(strEepromDefaultTable2.strAcData.eSetGenInputEn);
		bEEPROM2Flag = true;
	}

	if(suwGetGenInputMaxPower() != 0)
	{
		sSetGenInputMaxPower(strEepromDefaultTable2.strAcData.eSetGenInputMaxPower);
		bEEPROM2Flag = true;
	}

	if(suwGetGenConnectToGridPortEn() != 0)
	{
		sSetGenConnectToGridPortEn(strEepromDefaultTable2.strAcData.eSetGenConnectToGridPortEn);
		bEEPROM2Flag = true;
	}

	if(suwGetSmartLoad_OpenPower() != 0)
	{
		sSetSmartLoad_OpenPower(strEepromDefaultTable2.strAcData.eSetSmartLoad_OpenPower);
		bEEPROM2Flag = true;
	}

	if(suwGetSmartLoad_StartBatVolt() != 0)
	{
		sSetSmartLoad_StartBatVolt(strEepromDefaultTable2.strAcData.eSetSmartLoad_StartBatVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetSmartLoad_ExitBatVolt() != 0)
	{
		sSetSmartLoad_ExitBatVolt(strEepromDefaultTable2.strAcData.eSetSmartLoad_ExitBatVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetSmartLoad_StartSOC() != 0)
	{
		sSetSmartLoad_StartSOC(strEepromDefaultTable2.strAcData.eSetSmartLoad_StartSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetSmartLoad_ExitSOC() != 0)
	{
		sSetSmartLoad_ExitSOC(strEepromDefaultTable2.strAcData.eSetSmartLoad_ExitSOC);
		bEEPROM2Flag = true;
	}

	if(suwGetOnGrid_SmartLoadEn() != 0)
	{
		sSetOnGrid_SmartLoadEn(strEepromDefaultTable2.strAcData.eSetOnGrid_SmartLoadEn);
		bEEPROM2Flag = true;
	}

	if(suwGetOffGrid_SmartLoadDis() != 0)
	{
		sSetOffGrid_SmartLoadDis(strEepromDefaultTable2.strAcData.eSetOffGrid_SmartLoadDis);
		bEEPROM2Flag = true;
	}

	if((suwGetEEDry1ContactMode() != 0) && (suwGetEEDry1ContactMode() != 1))
	{
		sSetEEDry1ContactMode(strEepromDefaultTable2.strAcData.uwEEDry1ContactMode);
		bEEPROM2Flag = true;
	}

	if((suwGetEEDry2ContactMode() != 0) && (suwGetEEDry2ContactMode() != 1))
	{
		sSetEEDry2ContactMode(strEepromDefaultTable2.strAcData.uwEEDry2ContactMode);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd238() != 0)
	{
		sSetEERsvd238(strEepromDefaultTable2.strReserve.uwEERsvd238);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd239() != 0)
	{
		sSetEERsvd239(strEepromDefaultTable2.strReserve.uwEERsvd239);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd240() != 0)
	{
		sSetEERsvd240(strEepromDefaultTable2.strReserve.uwEERsvd240);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd241() != 0)
	{
		sSetEERsvd241(strEepromDefaultTable2.strReserve.uwEERsvd241);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd242() != 0)
	{
		sSetEERsvd242(strEepromDefaultTable2.strReserve.uwEERsvd242);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd243() != 0)
	{
		sSetEERsvd243(strEepromDefaultTable2.strReserve.uwEERsvd243);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd244() != 0)
	{
		sSetEERsvd244(strEepromDefaultTable2.strReserve.uwEERsvd244);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd245() != 0)
	{
		sSetEERsvd245(strEepromDefaultTable2.strReserve.uwEERsvd245);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd246() != 0)
	{
		sSetEERsvd246(strEepromDefaultTable2.strReserve.uwEERsvd246);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd247() != 0)
	{
		sSetEERsvd247(strEepromDefaultTable2.strReserve.uwEERsvd247);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd248() != 0)
	{
		sSetEERsvd248(strEepromDefaultTable2.strReserve.uwEERsvd248);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd249() != 0)
	{
		sSetEERsvd249(strEepromDefaultTable2.strReserve.uwEERsvd249);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd250() != 0)
	{
		sSetEERsvd250(strEepromDefaultTable2.strReserve.uwEERsvd250);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd251() != 0)
	{
		sSetEERsvd251(strEepromDefaultTable2.strReserve.uwEERsvd251);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd252() != 0)
	{
		sSetEERsvd252(strEepromDefaultTable2.strReserve.uwEERsvd252);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd253() != 0)
	{
		sSetEERsvd253(strEepromDefaultTable2.strReserve.uwEERsvd253);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd254() != 0)
	{
		sSetEERsvd254(strEepromDefaultTable2.strReserve.uwEERsvd254);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd255() != 0)
	{
		sSetEERsvd255(strEepromDefaultTable2.strReserve.uwEERsvd255);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd256() != 0)
	{
		sSetEERsvd256(strEepromDefaultTable2.strReserve.uwEERsvd256);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd257() != 0)
	{
		sSetEERsvd257(strEepromDefaultTable2.strReserve.uwEERsvd257);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd258() != 0)
	{
		sSetEERsvd258(strEepromDefaultTable2.strReserve.uwEERsvd258);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd259() != 0)
	{
		sSetEERsvd259(strEepromDefaultTable2.strReserve.uwEERsvd259);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd260() != 0)
	{
		sSetEERsvd260(strEepromDefaultTable2.strReserve.uwEERsvd260);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd261() != 0)
	{
		sSetEERsvd261(strEepromDefaultTable2.strReserve.uwEERsvd261);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd262() != 0)
	{
		sSetEERsvd262(strEepromDefaultTable2.strReserve.uwEERsvd262);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd263() != 0)
	{
		sSetEERsvd263(strEepromDefaultTable2.strReserve.uwEERsvd263);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd264() != 0)
	{
		sSetEERsvd264(strEepromDefaultTable2.strReserve.uwEERsvd264);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd265() != 0)
	{
		sSetEERsvd265(strEepromDefaultTable2.strReserve.uwEERsvd265);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd266() != 0)
	{
		sSetEERsvd266(strEepromDefaultTable2.strReserve.uwEERsvd266);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd267() != 0)
	{
		sSetEERsvd267(strEepromDefaultTable2.strReserve.uwEERsvd267);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd268() != 0)
	{
		sSetEERsvd268(strEepromDefaultTable2.strReserve.uwEERsvd268);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd269() != 0)
	{
		sSetEERsvd269(strEepromDefaultTable2.strReserve.uwEERsvd269);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd270() != 0)
	{
		sSetEERsvd270(strEepromDefaultTable2.strReserve.uwEERsvd270);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd271() != 0)
	{
		sSetEERsvd271(strEepromDefaultTable2.strReserve.uwEERsvd271);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd272() != 0)
	{
		sSetEERsvd272(strEepromDefaultTable2.strReserve.uwEERsvd272);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd273() != 0)
	{
		sSetEERsvd273(strEepromDefaultTable2.strReserve.uwEERsvd273);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd274() != 0)
	{
		sSetEERsvd274(strEepromDefaultTable2.strReserve.uwEERsvd274);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd275() != 0)
	{
		sSetEERsvd275(strEepromDefaultTable2.strReserve.uwEERsvd275);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd276() != 0)
	{
		sSetEERsvd276(strEepromDefaultTable2.strReserve.uwEERsvd276);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd277() != 0)
	{
		sSetEERsvd277(strEepromDefaultTable2.strReserve.uwEERsvd277);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd278() != 0)
	{
		sSetEERsvd278(strEepromDefaultTable2.strReserve.uwEERsvd278);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd279() != 0)
	{
		sSetEERsvd279(strEepromDefaultTable2.strReserve.uwEERsvd279);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd280() != 0)
	{
		sSetEERsvd280(strEepromDefaultTable2.strReserve.uwEERsvd280);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd281() != 0)
	{
		sSetEERsvd281(strEepromDefaultTable2.strReserve.uwEERsvd281);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd282() != 0)
	{
		sSetEERsvd282(strEepromDefaultTable2.strReserve.uwEERsvd282);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd283() != 0)
	{
		sSetEERsvd283(strEepromDefaultTable2.strReserve.uwEERsvd283);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd284() != 0)
	{
		sSetEERsvd284(strEepromDefaultTable2.strReserve.uwEERsvd284);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd285() != 0)
	{
		sSetEERsvd285(strEepromDefaultTable2.strReserve.uwEERsvd285);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd286() != 0)
	{
		sSetEERsvd286(strEepromDefaultTable2.strReserve.uwEERsvd286);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd287() != 0)
	{
		sSetEERsvd287(strEepromDefaultTable2.strReserve.uwEERsvd287);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd288() != 0)
	{
		sSetEERsvd288(strEepromDefaultTable2.strReserve.uwEERsvd288);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd289() != 0)
	{
		sSetEERsvd289(strEepromDefaultTable2.strReserve.uwEERsvd289);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd290() != 0)
	{
		sSetEERsvd290(strEepromDefaultTable2.strReserve.uwEERsvd290);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd291() != 0)
	{
		sSetEERsvd291(strEepromDefaultTable2.strReserve.uwEERsvd291);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd292() != 0)
	{
		sSetEERsvd292(strEepromDefaultTable2.strReserve.uwEERsvd292);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd293() != 0)
	{
		sSetEERsvd293(strEepromDefaultTable2.strReserve.uwEERsvd293);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd294() != 0)
	{
		sSetEERsvd294(strEepromDefaultTable2.strReserve.uwEERsvd294);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd295() != 0)
	{
		sSetEERsvd295(strEepromDefaultTable2.strReserve.uwEERsvd295);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd296() != 0)
	{
		sSetEERsvd296(strEepromDefaultTable2.strReserve.uwEERsvd296);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd297() != 0)
	{
		sSetEERsvd297(strEepromDefaultTable2.strReserve.uwEERsvd297);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd298() != 0)
	{
		sSetEERsvd298(strEepromDefaultTable2.strReserve.uwEERsvd298);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd299() != 0)
	{
		sSetEERsvd299(strEepromDefaultTable2.strReserve.uwEERsvd299);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd300() != 0)
	{
		sSetEERsvd300(strEepromDefaultTable2.strReserve.uwEERsvd300);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd301() != 0)
	{
		sSetEERsvd301(strEepromDefaultTable2.strReserve.uwEERsvd301);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd302() != 0)
	{
		sSetEERsvd302(strEepromDefaultTable2.strReserve.uwEERsvd302);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd303() != 0)
	{
		sSetEERsvd303(strEepromDefaultTable2.strReserve.uwEERsvd303);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd304() != 0)
	{
		sSetEERsvd304(strEepromDefaultTable2.strReserve.uwEERsvd304);
		bEEPROM2Flag = true;
	}

	if((suwGetEEECO_TimeOfUse() != 0) && (suwGetEEECO_TimeOfUse() != 1))
	{
		sSetEEECO_TimeOfUse(strEepromDefaultTable2.strECOMode.uwSetECO_TimeOfUse);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO_EffectiveWeek() != 0)
	{
		sSetEEECO_EffectiveWeek(strEepromDefaultTable2.strECOMode.uwSetECO_EffectiveWeek);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_GridChargeEnable() != 0)
	{
		sSetEEECO1_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO1_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_GenChargeEnable() != 0)
	{
		sSetEEECO1_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO1_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_StartTime() != 0)
	{
		sSetEEECO1_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO1_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_StopTime() != 0)
	{
		sSetEEECO1_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO1_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_Volt() != 0)
	{
		sSetEEECO1_Volt(strEepromDefaultTable2.strECOMode.uwSetECO1_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_SOC() != 0)
	{
		sSetEEECO1_SOC(strEepromDefaultTable2.strECOMode.uwSetECO1_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_Power() != 0)
	{
		sSetEEECO1_Power(strEepromDefaultTable2.strECOMode.uwSetECO1_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO1_WorkModeSet() != 0)
	{
		sSetEEECO1_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO1_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_GridChargeEnable() != 0)
	{
		sSetEEECO2_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO2_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_GenChargeEnable() != 0)
	{
		sSetEEECO2_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO2_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_StartTime() != 0)
	{
		sSetEEECO2_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO2_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_StopTime() != 0)
	{
		sSetEEECO2_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO2_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_Volt() != 0)
	{
		sSetEEECO2_Volt(strEepromDefaultTable2.strECOMode.uwSetECO2_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_SOC() != 0)
	{
		sSetEEECO2_SOC(strEepromDefaultTable2.strECOMode.uwSetECO2_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_Power() != 0)
	{
		sSetEEECO2_Power(strEepromDefaultTable2.strECOMode.uwSetECO2_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO2_WorkModeSet() != 0)
	{
		sSetEEECO2_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO2_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_GridChargeEnable() != 0)
	{
		sSetEEECO3_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO3_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_GenChargeEnable() != 0)
	{
		sSetEEECO3_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO3_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_StartTime() != 0)
	{
		sSetEEECO3_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO3_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_StopTime() != 0)
	{
		sSetEEECO3_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO3_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_Volt() != 0)
	{
		sSetEEECO3_Volt(strEepromDefaultTable2.strECOMode.uwSetECO3_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_SOC() != 0)
	{
		sSetEEECO3_SOC(strEepromDefaultTable2.strECOMode.uwSetECO3_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_Power() != 0)
	{
		sSetEEECO3_Power(strEepromDefaultTable2.strECOMode.uwSetECO3_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO3_WorkModeSet() != 0)
	{
		sSetEEECO3_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO3_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_GridChargeEnable() != 0)
	{
		sSetEEECO4_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO4_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_GenChargeEnable() != 0)
	{
		sSetEEECO4_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO4_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_StartTime() != 0)
	{
		sSetEEECO4_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO4_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_StopTime() != 0)
	{
		sSetEEECO4_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO4_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_Volt() != 0)
	{
		sSetEEECO4_Volt(strEepromDefaultTable2.strECOMode.uwSetECO4_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_SOC() != 0)
	{
		sSetEEECO4_SOC(strEepromDefaultTable2.strECOMode.uwSetECO4_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_Power() != 0)
	{
		sSetEEECO4_Power(strEepromDefaultTable2.strECOMode.uwSetECO4_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO4_WorkModeSet() != 0)
	{
		sSetEEECO4_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO4_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_GridChargeEnable() != 0)
	{
		sSetEEECO5_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO5_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_GenChargeEnable() != 0)
	{
		sSetEEECO5_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO5_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_StartTime() != 0)
	{
		sSetEEECO5_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO5_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_StopTime() != 0)
	{
		sSetEEECO5_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO5_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_Volt() != 0)
	{
		sSetEEECO5_Volt(strEepromDefaultTable2.strECOMode.uwSetECO5_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_SOC() != 0)
	{
		sSetEEECO5_SOC(strEepromDefaultTable2.strECOMode.uwSetECO5_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_Power() != 0)
	{
		sSetEEECO5_Power(strEepromDefaultTable2.strECOMode.uwSetECO5_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO5_WorkModeSet() != 0)
	{
		sSetEEECO5_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO5_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_GridChargeEnable() != 0)
	{
		sSetEEECO6_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO6_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_GenChargeEnable() != 0)
	{
		sSetEEECO6_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO6_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_StartTime() != 0)
	{
		sSetEEECO6_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO6_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_StopTime() != 0)
	{
		sSetEEECO6_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO6_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_Volt() != 0)
	{
		sSetEEECO6_Volt(strEepromDefaultTable2.strECOMode.uwSetECO6_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_SOC() != 0)
	{
		sSetEEECO6_SOC(strEepromDefaultTable2.strECOMode.uwSetECO6_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_Power() != 0)
	{
		sSetEEECO6_Power(strEepromDefaultTable2.strECOMode.uwSetECO6_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO6_WorkModeSet() != 0)
	{
		sSetEEECO6_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO6_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_GridChargeEnable() != 0)
	{
		sSetEEECO7_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO7_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_GenChargeEnable() != 0)
	{
		sSetEEECO7_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO7_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_StartTime() != 0)
	{
		sSetEEECO7_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO7_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_StopTime() != 0)
	{
		sSetEEECO7_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO7_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_Volt() != 0)
	{
		sSetEEECO7_Volt(strEepromDefaultTable2.strECOMode.uwSetECO7_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_SOC() != 0)
	{
		sSetEEECO7_SOC(strEepromDefaultTable2.strECOMode.uwSetECO7_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_Power() != 0)
	{
		sSetEEECO7_Power(strEepromDefaultTable2.strECOMode.uwSetECO7_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO7_WorkModeSet() != 0)
	{
		sSetEEECO7_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO7_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_GridChargeEnable() != 0)
	{
		sSetEEECO8_GridChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO8_GridChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_GenChargeEnable() != 0)
	{
		sSetEEECO8_GenChargeEnable(strEepromDefaultTable2.strECOMode.uwSetECO8_GenChargeEnable);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_StartTime() != 0)
	{
		sSetEEECO8_StartTime(strEepromDefaultTable2.strECOMode.uwSetECO8_StartTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_StopTime() != 0)
	{
		sSetEEECO8_StopTime(strEepromDefaultTable2.strECOMode.uwSetECO8_StopTime);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_Volt() != 0)
	{
		sSetEEECO8_Volt(strEepromDefaultTable2.strECOMode.uwSetECO8_Volt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_SOC() != 0)
	{
		sSetEEECO8_SOC(strEepromDefaultTable2.strECOMode.uwSetECO8_SOC);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_Power() != 0)
	{
		sSetEEECO8_Power(strEepromDefaultTable2.strECOMode.uwSetECO8_Power);
		bEEPROM2Flag = true;
	}

	if(suwGetEEECO8_WorkModeSet() != 0)
	{
		sSetEEECO8_WorkModeSet(strEepromDefaultTable2.strECOMode.uwSetECO8_WorkModeSet);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd371() != 0)
	{
		sSetEERsvd371(strEepromDefaultTable2.strECOMode.uwEERsvd371);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd372() != 0)
	{
		sSetEERsvd372(strEepromDefaultTable2.strECOMode.uwEERsvd372);
		bEEPROM2Flag = true;
	}

	if((suwGetEEATE_UpdateFW() != 0) && (suwGetEEATE_UpdateFW() != 1))
	{
		sSetEEATE_UpdateFW(strEepromDefaultTable2.strATESet.uwATE_UpdateFW);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_SafetyCode() != 0)
	{
		sSetEEATE_SafetyCode(strEepromDefaultTable2.strATESet.uwATE_SafetyCode);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_ISOsetting() != 0)
	{
		sSetEEATE_ISOsetting(strEepromDefaultTable2.strATESet.uwATE_ISOsetting);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterProc() != 0)
	{
		sSetEEATE_EleMeterProc(strEepromDefaultTable2.strATESet.uwATE_EleMeterProc);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_ExCommBps() > 65535)
	{
		sSetEEATE_ExCommBps(strEepromDefaultTable2.strATESet.uwATE_ExCommBps);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterBps_Parity() != 0)
	{
		sSetEEATE_EleMeterBps_Parity(strEepromDefaultTable2.strATESet.uwATE_EleMeterBps_Parity);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterAddr() != 0)
	{
		sSetEEATE_EleMeterAddr(strEepromDefaultTable2.strATESet.uwATE_EleMeterAddr);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterWREn() != 0)
	{
		sSetEEATE_EleMeterWREn(strEepromDefaultTable2.strATESet.uwATE_EleMeterWREn);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterDataRegAddr() != 0)
	{
		sSetEEATE_EleMeterDataRegAddr(strEepromDefaultTable2.strATESet.uwATE_EleMeterDataRegAddr);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_EleMeterData() != 0)
	{
		sSetEEATE_EleMeterData(strEepromDefaultTable2.strATESet.uwATE_EleMeterData);
		bEEPROM2Flag = true;
	}

	if(suwGetEEATE_485CommBps() > 65535)
	{
		sSetEEATE_485CommBps(strEepromDefaultTable2.strATESet.uwATE_485CommBps);
		bEEPROM2Flag = true;
	}

	if((suwGetEEMenuRtnDftPageEn() != 0) && (suwGetEEMenuRtnDftPageEn() != 1))
	{
		sSetEEMenuRtnDftPageEn(strEepromDefaultTable2.strATESet.uwMenuRtnDftPageEn);
		bEEPROM2Flag = true;
	}

	if((suwGetEELCDBacklight() != 0) && (suwGetEELCDBacklight() != 1))
	{
		sSetEELCDBacklight(strEepromDefaultTable2.strATESet.uwSetLCDBacklight);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBuzzerBeep() != 0) && (suwGetEEBuzzerBeep() != 1))
	{
		sSetEEBuzzerBeep(strEepromDefaultTable2.strATESet.uwSetBuzzerBeep);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd387() != 0)
	{
		sSetEERsvd387(strEepromDefaultTable2.strATESet.uwEERsvd387);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd388() != 0)
	{
		sSetEERsvd388(strEepromDefaultTable2.strATESet.uwEERsvd388);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd389() != 0)
	{
		sSetEERsvd389(strEepromDefaultTable2.strATESet.uwEERsvd389);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd390() != 0)
	{
		sSetEERsvd390(strEepromDefaultTable2.strATESet.uwEERsvd390);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd391() != 0)
	{
		sSetEERsvd391(strEepromDefaultTable2.strATESet.uwEERsvd391);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd392() != 0)
	{
		sSetEERsvd392(strEepromDefaultTable2.strATESet.uwEERsvd392);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd393() != 0)
	{
		sSetEERsvd393(strEepromDefaultTable2.strATESet.uwEERsvd393);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd394() != 0)
	{
		sSetEERsvd394(strEepromDefaultTable2.strATESet.uwEERsvd394);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd395() != 0)
	{
		sSetEERsvd395(strEepromDefaultTable2.strATESet.uwEERsvd395);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd396() != 0)
	{
		sSetEERsvd396(strEepromDefaultTable2.strATESet.uwEERsvd396);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd397() != 0)
	{
		sSetEERsvd397(strEepromDefaultTable2.strATESet.uwEERsvd397);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd398() != 0)
	{
		sSetEERsvd398(strEepromDefaultTable2.strATESet.uwEERsvd398);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd399() != 0)
	{
		sSetEERsvd399(strEepromDefaultTable2.strATESet.uwEERsvd399);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd400() != 0)
	{
		sSetEERsvd400(strEepromDefaultTable2.strATESet.uwEERsvd400);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd401() != 0)
	{
		sSetEERsvd401(strEepromDefaultTable2.strATESet.uwEERsvd401);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd402() != 0)
	{
		sSetEERsvd402(strEepromDefaultTable2.strATESet.uwEERsvd402);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd403() != 0)
	{
		sSetEERsvd403(strEepromDefaultTable2.strATESet.uwEERsvd403);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd404() != 0)
	{
		sSetEERsvd404(strEepromDefaultTable2.strATESet.uwEERsvd404);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd405() != 0)
	{
		sSetEERsvd405(strEepromDefaultTable2.strATESet.uwEERsvd405);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd406() != 0)
	{
		sSetEERsvd406(strEepromDefaultTable2.strATESet.uwEERsvd406);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd407() != 0)
	{
		sSetEERsvd407(strEepromDefaultTable2.strATESet.uwEERsvd407);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd408() != 0)
	{
		sSetEERsvd408(strEepromDefaultTable2.strATESet.uwEERsvd408);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd409() != 0)
	{
		sSetEERsvd409(strEepromDefaultTable2.strATESet.uwEERsvd409);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd410() != 0)
	{
		sSetEERsvd410(strEepromDefaultTable2.strATESet.uwEERsvd410);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd411() != 0)
	{
		sSetEERsvd411(strEepromDefaultTable2.strATESet.uwEERsvd411);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd412() != 0)
	{
		sSetEERsvd412(strEepromDefaultTable2.strATESet.uwEERsvd412);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd413() != 0)
	{
		sSetEERsvd413(strEepromDefaultTable2.strATESet.uwEERsvd413);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd414() != 0)
	{
		sSetEERsvd414(strEepromDefaultTable2.strATESet.uwEERsvd414);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd415() != 0)
	{
		sSetEERsvd415(strEepromDefaultTable2.strATESet.uwEERsvd415);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd416() != 0)
	{
		sSetEERsvd416(strEepromDefaultTable2.strATESet.uwEERsvd416);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd417() != 0)
	{
		sSetEERsvd417(strEepromDefaultTable2.strATESet.uwEERsvd417);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd418() != 0)
	{
		sSetEERsvd418(strEepromDefaultTable2.strATESet.uwEERsvd418);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd419() != 0)
	{
		sSetEERsvd419(strEepromDefaultTable2.strATESet.uwEERsvd419);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd420() != 0)
	{
		sSetEERsvd420(strEepromDefaultTable2.strATESet.uwEERsvd420);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBmsBagAddr() > 16)
	{
		sSetEEBmsBagAddr(strEepromDefaultTable2.strATESet.uwSetBmsBagAddr);
		bEEPROM2Flag = true;
	}

	if((suwGetEEClearEventLog() != 0) && (suwGetEEClearEventLog() != 1))
	{
		sSetEEClearEventLog(strEepromDefaultTable2.strATESet.uwSetClearEventLog);
		bEEPROM2Flag = true;
	}

	if((suwGetEEEventLogFunc() != 0) && (suwGetEEEventLogFunc() != 1))
	{
		sSetEEEventLogFunc(strEepromDefaultTable2.strATESet.uwSetEventLogFunc);
		bEEPROM2Flag = true;
	}

	if((suwGetEEFaultLogFunc() != 0) && (suwGetEEFaultLogFunc() != 1))
	{
		sSetEEFaultLogFunc(strEepromDefaultTable2.strATESet.uwSetFaultLogFunc);
		bEEPROM2Flag = true;
	}

	if((suwGetEELogType() != 0) && (suwGetEELogType() != 1))
	{
		sSetEELogType(strEepromDefaultTable2.strATESet.uwSetLogType);
		bEEPROM2Flag = true;
	}

	if(suwGetEELogIndex() > 9)
	{
		sSetEELogIndex(strEepromDefaultTable2.strATESet.uwSetLogIndex);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd427() != 0)
	{
		sSetEERsvd427(strEepromDefaultTable2.strATESet.uwEERsvd427);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd428() != 0)
	{
		sSetEERsvd428(strEepromDefaultTable2.strATESet.uwEERsvd428);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd429() != 0)
	{
		sSetEERsvd429(strEepromDefaultTable2.strATESet.uwEERsvd429);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd430() != 0)
	{
		sSetEERsvd430(strEepromDefaultTable2.strATESet.uwEERsvd430);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd431() != 0)
	{
		sSetEERsvd431(strEepromDefaultTable2.strATESet.uwEERsvd431);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd432() != 0)
	{
		sSetEERsvd432(strEepromDefaultTable2.strATESet.uwEERsvd432);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd433() != 0)
	{
		sSetEERsvd433(strEepromDefaultTable2.strATESet.uwEERsvd433);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd434() != 0)
	{
		sSetEERsvd434(strEepromDefaultTable2.strATESet.uwEERsvd434);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd435() != 0)
	{
		sSetEERsvd435(strEepromDefaultTable2.strATESet.uwEERsvd435);
		bEEPROM2Flag = true;
	}

	if(suwGetEERsvd436() != 0)
	{
		sSetEERsvd436(strEepromDefaultTable2.strATESet.uwEERsvd436);
		bEEPROM2Flag = true;
	}
	
	//EEPROM3
	if(suwGetEEGrid1OVValue() != 0) 
	{
		sSetEEGrid1OVValue(strEepromDefaultTable3.uwSetGrid1OVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1OVTime() != 0) 
	{
		sSetEEGrid1OVTime(strEepromDefaultTable3.uwSetGrid1OVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2OVValue() != 0) 
	{
		sSetEEGrid2OVValue(strEepromDefaultTable3.uwSetGrid2OVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2OVTime() != 0) 
	{
		sSetEEGrid2OVTime(strEepromDefaultTable3.uwSetGrid2OVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3OVValue() != 0) 
	{
		sSetEEGrid3OVValue(strEepromDefaultTable3.uwSetGrid3OVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3OVTime() != 0) 
	{
		sSetEEGrid3OVTime(strEepromDefaultTable3.uwSetGrid3OVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1UVValue() != 0) 
	{
		sSetEEGrid1UVValue(strEepromDefaultTable3.uwSetGrid1UVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1UVTime() != 0) 
	{
		sSetEEGrid1UVTime(strEepromDefaultTable3.uwSetGrid1UVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2UVValue() != 0) 
	{
		sSetEEGrid2UVValue(strEepromDefaultTable3.uwSetGrid2UVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2UVTime() != 0) 
	{
		sSetEEGrid2UVTime(strEepromDefaultTable3.uwSetGrid2UVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3UVValue() != 0) 
	{
		sSetEEGrid3UVValue(strEepromDefaultTable3.uwSetGrid3UVValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3UVTime() != 0) 
	{
		sSetEEGrid3UVTime(strEepromDefaultTable3.uwSetGrid3UVTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1OFValue() != 0) 
	{
		sSetEEGrid1OFValue(strEepromDefaultTable3.uwSetGrid1OFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1OFTime() != 0) 
	{
		sSetEEGrid1OFTime(strEepromDefaultTable3.uwSetGrid1OFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2OFValue() != 0) 
	{
		sSetEEGrid2OFValue(strEepromDefaultTable3.uwSetGrid2OFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2OFTime() != 0) 
	{
		sSetEEGrid2OFTime(strEepromDefaultTable3.uwSetGrid2OFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3OFValue() != 0) 
	{
		sSetEEGrid3OFValue(strEepromDefaultTable3.uwSetGrid3OFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3OFTime() != 0) 
	{
		sSetEEGrid3OFTime(strEepromDefaultTable3.uwSetGrid3OFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1UFValue() != 0) 
	{
		sSetEEGrid1UFValue(strEepromDefaultTable3.uwSetGrid1UFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid1UFTime() != 0) 
	{
		sSetEEGrid1UFTime(strEepromDefaultTable3.uwSetGrid1UFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2UFValue() != 0) 
	{
		sSetEEGrid2UFValue(strEepromDefaultTable3.uwSetGrid2UFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid2UFTime() != 0) 
	{
		sSetEEGrid2UFTime(strEepromDefaultTable3.uwSetGrid2UFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3UFValue() != 0) 
	{
		sSetEEGrid3UFValue(strEepromDefaultTable3.uwSetGrid3UFValue);
		bEEPROM3Flag = true;
	}

	if(suwGetEEGrid3UFTime() != 0) 
	{
		sSetEEGrid3UFTime(strEepromDefaultTable3.uwSetGrid3UFTime);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd558() != 0) 
	{
		sSetSetRsvd558(strEepromDefaultTable3.uwSetRsvd558);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd559() != 0) 
	{
		sSetSetRsvd559(strEepromDefaultTable3.uwSetRsvd559);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd560() != 0) 
	{
		sSetSetRsvd560(strEepromDefaultTable3.uwSetRsvd560);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd561() != 0) 
	{
		sSetSetRsvd561(strEepromDefaultTable3.uwSetRsvd561);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd562() != 0) 
	{
		sSetSetRsvd562(strEepromDefaultTable3.uwSetRsvd562);
		bEEPROM3Flag = true;
	}

	if(suwGetSetRsvd563() != 0) 
	{
		sSetSetRsvd563(strEepromDefaultTable3.uwSetRsvd563);
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
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatMaxChgCurr() > (uwGetSettingMaxChgCurr()))	
	{
		sSetEEBatMaxChgCurr(strEepromDefaultTable2.strBatData.uwEEBatMaxChgCurr);
		bEEPROM2Flag = true;
	}
	
	if((suwGetEEBatMaxDcgCurr() > (uwGetSettingMaxDchgCurr())) \
		|| (suwGetEEBatMaxDcgCurr() == 0))
	{
		sSetEEBatMaxDcgCurr(strEepromDefaultTable2.strBatData.uwEEBatMaxDcgCurr);
		bEEPROM2Flag = true;
	}

//	if(suwGetEEBatVoltage() != (cBatVoltReal12V*uwBatSerialPcs))
	if((suwGetEEBatVoltage() != cBatVoltReal3V))// && (suwGetEEBatVoltage() != cBatVoltReal24V))
	{
		sSetEEBatVoltage(cBatVoltReal3V * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridChgBatCurr() > (uwGetSettingMaxACChgCurr()))	
	{
		sSetEEGridChgBatCurr(strEepromDefaultTable2.strBatData.uwEEGridMaxChargeCurr);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOnGridBatAutoStartChgVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEOnGridBatAutoStartChgVolt() < cBatVoltReal2V50 * uwBatSerialPcs))
	{
		sSetEEOnGridBatAutoStartChgVolt(strEepromDefaultTable2.strBatData.uwEEGridStartChargeVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEOnGridBatExitAutoChgVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEOnGridBatExitAutoChgVolt() < cBatVoltReal2V50 * uwBatSerialPcs)) 
	{
		sSetEEOnGridBatExitAutoChgVolt(strEepromDefaultTable2.strBatData.uwEEGridEndChargeVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatConstVolt() > (cBatVoltReal3V75*uwBatSerialPcs) \
		|| suwGetEEBatConstVolt() < (cBatVoltReal4V*uwBatSerialPcs))
	{
		sSetEEBatConstVolt(strEepromDefaultTable2.strBatData.uwSetBatConstVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if(suwGetEEBatFloatVolt() > (cBatVoltReal3V75*uwBatSerialPcs) \
		|| suwGetEEBatFloatVolt() < (cBatVoltReal4V*uwBatSerialPcs))
	{
		sSetEEBatFloatVolt(strEepromDefaultTable2.strBatData.uwSetBatFloatVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatLowShutDownVolt() > cBatVoltReal3V25 * uwBatSerialPcs) \
		|| (suwGetEEBatLowShutDownVolt() < cBatVoltReal2V12 * uwBatSerialPcs)) 
	{
		sSetEEBatLowShutDownVolt(strEepromDefaultTable2.strBatData.uwEEShutdownVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatACRestartVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatACRestartVolt() < cBatVoltReal2V50 * uwBatSerialPcs))
	{
		sSetEEBatACRestartVolt(strEepromDefaultTable2.strBatData.uwEEBatRestartOutVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatLowAlarmVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatLowAlarmVolt() < cBatVoltReal2V50 * uwBatSerialPcs))
	{
		sSetEEBatLowAlarmVolt(strEepromDefaultTable2.strBatData.uwEELowBattVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatVoltOverShut() > cBatVoltReal4V * uwBatSerialPcs) \
		|| (suwGetEEBatVoltOverShut() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEBatVoltOverShut(strEepromDefaultTable2.strBatData.uwSetBatVoltOverShut * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEEBatEqVolt() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEEBatEqVolt() < cBatVoltReal3V * uwBatSerialPcs))
	{
		sSetEEBatEqVolt(strEepromDefaultTable2.strBatData.uwEEBatEqVolt * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV1StartVolt() > uwGetMpptPvVoltMax())
	{
		sSetEEPV1StartVolt(strEepromDefaultTable2.strPvData.uwEEPV1StartVolt);
		bEEPROM2Flag = true;
	}

	if(suwGetEEPV1PowerLimit() > uwGetPvPowerMax())
	{
		sSetEEPV1PowerLimit(strEepromDefaultTable2.strPvData.uwEEPV1PowerLimit);
		bEEPROM2Flag = true;
	}

	if(suwGetEEACOutputRatedPower() > ((INT16U)uwGetInvWattMax()))
	{
		sSetEEACOutputRatedPower(strEepromDefaultTable2.strAcData.uwEEACOutputRatedPower);
		bEEPROM2Flag = true;
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
			bEEPROM2Flag = true;
		}
	}
	else
	{
		if((suwGetEEACOutputRatedVolt() != cAcVoltReal220V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal230V) \
			&& (suwGetEEACOutputRatedVolt() != cAcVoltReal240V))
		{
			sSetEEACOutputRatedVolt(cAcVoltReal230V);
			bEEPROM2Flag = true;
		}
	}

	if((suwGetEERlyVoltOn() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEERlyVoltOn() < cBatVoltReal2V75 * uwBatSerialPcs))
	{
		sSetEERlyVoltOn(strEepromDefaultTable2.strAcData.uwEERlyVoltOn * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if((suwGetEERlyVoltOff() > cBatVoltReal3V75 * uwBatSerialPcs) \
		|| (suwGetEERlyVoltOff() < cBatVoltReal2V75 * uwBatSerialPcs))
	{
		sSetEERlyVoltOff(strEepromDefaultTable2.strAcData.uwEERlyVoltOff * uwBatSerialPcs);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridCurrLimit() > 1000)//uwGetGridInputCurrMax())
	{
		sSetEEGridCurrLimit(strEepromDefaultTable2.strAcData.uwEEGridCurrLimit);
		bEEPROM2Flag = true;
	}

	if(suwGetEEGridInputPower() > 1000)//> uwGetGridInputWattMax())
	{
		sSetEEGridInputPower(cMaxACInputPower);
		bEEPROM2Flag = true;
	}

	if(suwGetEEMaxFeedPower() >= ((INT16U)uwGetInvWattMax() + 200)) // -200W ~ 3200W
	{
		sSetEEMaxFeedPower(strEepromDefaultTable2.strAcData.uwEEGridFeedPower);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridVoltUpperLimit() > cAcVoltReal300V) || (suwGetEEGridVoltLowerLimit() < cAcVoltReal240V))
	{
		sSetEEGridVoltUpperLimit(strEepromDefaultTable2.strAcData.uwEEGridVoltUpperLimit);
		bEEPROM2Flag = true;
	}

	if((suwGetEEGridVoltUpperLimit() > cAcVoltReal220V) || (suwGetEEGridVoltLowerLimit() < cAcVoltReal90V)) 
	{
		sSeEEGridVoltLowerLimit(strEepromDefaultTable2.strAcData.uwEEGridVoltLowerLimit);
		bEEPROM2Flag = true;
	}

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

//EEPROM1
INT16U suwGetEEMachineCode(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwMachCode;
}

INT16U suwGetEE_SN1(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SN1;
}

INT16U suwGetEE_SN2(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SN2;
}

INT16U suwGetEE_SN3(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SN3;
}

INT16U suwGetEE_SN4(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SN4;
}

INT16U suwGetEE_SN5(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SN5;
}

INT16U suwGetEE_SNLen(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_SNLen;
}

INT16U suwGetEE_DispHwVer(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_DispHwVer;
}

INT16U suwGetEE_CtrlHwVer(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_CtrlHwVer;
}

INT16U suwGetEE_PowerHwVer(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEE_PowerHwVer;
}

INT16S suwGetEEPV1VoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV1VoltAdj;
}

INT16S suwGetEEPV1VoltBias(void)
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV1VoltBias;
}

INT16S suwGetEEPV2VoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV2VoltAdj;
}

INT16S suwGetEEPV2VoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV2VoltBias;
}

INT16S suwGetEEPV1BatCurrAdj(void)
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV1BatCurrAdj;
}

INT16S suwGetEEPV1BatCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV1BatCurrBias;
}

INT16S suwGetEEPV2BatCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV2BatCurrAdj;
}

INT16S suwGetEEPV2BatCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEPV2BatCurrBias;
}

INT16S suwGetEEBatVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBatVoltAdj;
}

INT16S suwGetEEBatVoltBias(void) 

{
    return uEepromCfg1.EepromStructCfg1.uwEEBatVoltBias;
}

INT16S suwGetEEBatCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBatCurrAdj;
}

INT16S suwGetEEBatCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBatCurrBias;
}

INT16S suwGetEEBUSVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBUSVoltAdj;
}

INT16S suwGetEEBUSVoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBUSVoltBias;
}

INT16S suwGetEEBUSCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEBUSCurrAdj;
}

INT16S suwGetEEBUSCurrBias(void)
{
    return uEepromCfg1.EepromStructCfg1.uwEEBUSCurrBias;
}

INT16S suwGetEEInvVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEInvVoltAdj;
}

INT16S suwGetEEInvVoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEInvVoltBias;
}

INT16S suwGetEEInvCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEInvCurrAdj;
}

INT16S suwGetEEInvCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEInvCurrBias;
}

INT16S suwGetEEGridVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGridVoltAdj;
}

INT16S suwGetEEGridVoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGridVoltBias;
}

INT16S suwGetEEGridCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGridCurrAdj;
}

INT16S suwGetEEGridCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGridCurrBias;
}

INT16S suwGetEEOPVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEOPVoltAdj;
}

INT16S suwGetEEOpVoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEOpVoltBias;
}

INT16S suwGetEEOPCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEOPCurrAdj;
}

INT16S suwGetEEOpCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEOpCurrBias;
}

INT16U suwGetEEDischargeEneyCoeffH(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEDischargeEneyCoeffH;
}

INT16U suwGetEEDischargeEneyCoeffL(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEDischargeEneyCoeffL;
}

INT16U suwGetEEchargeEneyCoeffH(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEchargeEneyCoeffH;
}

INT16U suwGetEEchargeEneyCoeffL(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEchargeEneyCoeffL;
}

INT16S suwGetEEGenVoltAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGenVoltAdj;
}

INT16S suwGetEEGenVoltBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGenVoltBias;
}

INT16S suwGetEEGenCurrAdj(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGenCurrAdj;
}

INT16S suwGetEEGenCurrBias(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwEEGenCurrBias;
}

INT16U suwGetSetRsvd5(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd5;
}

INT16U suwGetSetRsvd6(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd6;
}

INT16U suwGetSetRsvd7(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd7;
}

INT16U suwGetSetRsvd8(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd8;
}

INT16U suwGetSetRsvd9(void) 

{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd9;
}

INT16U suwGetSetRsvd10(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd10;
}

INT16U suwGetSetRsvd11(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd11;
}

INT16U suwGetSetRsvd12(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd12;
}

INT16U suwGetSetRsvd13(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd13;
}

INT16U suwGetSetRsvd14(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd14;
}

INT16U suwGetSetRsvd15(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd15;
}

INT16U suwGetSetRsvd16(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd16;
}

INT16U suwGetSetRsvd17(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd17;
}

INT16U suwGetSetRsvd18(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd18;
}

INT16U suwGetSetRsvd19(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd19;
}

INT16U suwGetSetRsvd20(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd20;
}

INT16U suwGetSetRsvd21(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd21;
}

INT16U suwGetSetRsvd22(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd22;
}

INT16U suwGetSetRsvd23(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd23;
}

INT16U suwGetSetRsvd24(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd24;
}

INT16U suwGetSetRsvd25(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd25;
}

INT16U suwGetSetRsvd26(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd26;
}

INT16U suwGetSetRsvd27(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd27;
}

INT16U suwGetSetRsvd28(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd28;
}

INT16U suwGetSetRsvd29(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd29;
}

INT16U suwGetSetRsvd30(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd30;
}

INT16U suwGetSetRsvd31(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd31;
}

INT16U suwGetSetRsvd32(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd32;
}

INT16U suwGetSetRsvd33(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd33;
}

INT16U suwGetSetRsvd34(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd34;
}

INT16U suwGetSetRsvd35(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd35;
}

INT16U suwGetSetRsvd36(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd36;
}

INT16U suwGetSetRsvd37(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd37;
}

INT16U suwGetSetRsvd38(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd38;
}

INT16U suwGetSetRsvd39(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd39;
}

INT16U suwGetSetRsvd40(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd40;
}

INT16U suwGetSetRsvd41(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd41;
}

INT16U suwGetSetRsvd42(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd42;
}

INT16U suwGetSetRsvd43(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd43;
}

INT16U suwGetSetRsvd44(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd44;
}

INT16U suwGetSetRsvd45(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd45;
}

INT16U suwGetSetRsvd46(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd46;
}

INT16U suwGetSetRsvd47(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd47;
}

INT16U suwGetSetRsvd48(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd48;
}

INT16U suwGetSetRsvd49(void)
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd49;
}

INT16U suwGetSetRsvd50(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd50;
}

INT16U suwGetSetRsvd51(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd51;
}

INT16U suwGetSetRsvd52(void) 
{
    return uEepromCfg1.EepromStructCfg1.uwSetRsvd52;
}

INT16U suwGetEEFlag1(void)
{
    return uEepromCfg1.EepromStructCfg1.uwFlag1;
}

INT16U suwGetEECheckCRC1(void)
{
    return uEepromCfg1.EepromStructCfg1.uwEECheckCRC1;
}

//EEPROM2
//strControlState
INT16U	suwGetEEParaEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallel;
}

INT16U	suwGetEEMasterSlaver(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEParalleltMasterSlaver;
}

INT16U	suwGetEEParallelPhase(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallelPhase;
}

INT16U	suwGetEEParallelIID(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallelIID;
}

INT16U	suwGetEESystemOutputMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwSetSystemOutputMode;
}

INT16U	suwGetEEWorkMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEWorkMode;
}

INT16U	suwGetEEFanWorkMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEFanWorkMode;
}

INT16U	suwGetEEPowerConversion(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEPowerConversion;
}

INT16U	suwGetEEPowerSaveMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEPowerSaveMode;
}

INT16U	suwGetEENoBatMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEENoBatMode;
}

INT16U	suwGetEELogoEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEELogoEnable;
}

INT16U	suwGetEEAdcBiasAdj(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEEAdcBiasAdj;
}

INT16U	suwGetLeakCurrProtectEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.eSetLeakCurrProtectEnable;
}

INT16U	suwGetLeakCurrProtectValue(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.eSetLeakCurrProtectValue;
}

INT16U	suwGetISOCheckEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.eSetISOCheckEnable;
}

INT16U	suwGetISOCheckValue(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.eSetISOCheckValue;
}

INT16U	suwGetEERsvd17(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd17;
}

INT16U	suwGetEERsvd18(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd18;
}

INT16U	suwGetEERsvd19(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd19;
}

INT16U	suwGetEERsvd20(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd20;
}

INT16U	suwGetEERsvd21(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd21;
}

INT16U	suwGetEERsvd22(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd22;
}

INT16U	suwGetEERsvd23(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd23;
}

INT16U	suwGetEERsvd24(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd24;
}

INT16U	suwGetEERsvd25(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd25;
}

INT16U	suwGetEERsvd26(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd26;
}

INT16U	suwGetEERsvd27(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd27;
}

INT16U	suwGetEERsvd28(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd28;
}

INT16U	suwGetEERsvd29(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd29;
}

INT16U	suwGetEERsvd30(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd30;
}

INT16U	suwGetEERsvd31(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd31;
}

INT16U	suwGetEERsvd32(void)
{
    return uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd32;
}

//strBatData
INT16U	suwGetEEBatType(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatType;
}

INT16U	suwGetEEBatSeriesNum(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatSeriesNum;
}

INT16U	suwGetEEBatActivateEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatActivate;
}

INT16U	suwGetEEBatCapacity(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatCapacity;
}

INT16U	suwGetEELithiumMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEELithiumMode;
}

INT16U	suwGetEERsvd38(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd38;
}

INT16U	suwGetEEBatMaxChgCurr(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatMaxChgCurr;
}

INT16U	suwGetEEBatMaxDcgCurr(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatMaxDcgCurr;
}

INT16U	suwGetEEBatVoltage(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatVoltage;
}

INT16U	suwGetEERsvd42(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd42;
}

INT16U	suwGetEEGridChargeEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridChargeEn;
}

INT16U	suwGetEEGridChgBatCurr(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridMaxChargeCurr;
}

INT16U	suwGetEEOnGridBatAutoStartChgVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridStartChargeVolt;
}

INT16U	suwGetEEOnGridBatExitAutoChgVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridEndChargeVolt;
}

INT16U	suwGetEEOnGridBatAutoStartChgSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridStartChargeSOC;
}

INT16U	suwGetEEOnGridBatExitAutoChgSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridEndChargeSOC;
}

INT16U	suwGetEERsvd49(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd49;
}

INT16U	suwGetEEGenChargeEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenChargeEn;
}

INT16U	suwGetEEGenMaxChargeCurr(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenMaxChargeCurr;
}

INT16U	suwGetEEGenStartChargeVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenStartChargeVolt;
}

INT16U	suwGetEEGenEndChargeVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenEndChargeVolt;
}

INT16U	suwGetEEGenStartChargeSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenStartChargeSOC;
}

INT16U	suwGetEEGenEndChargeSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenEndChargeSOC;
}

INT16U	suwGetEERsvd56(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd56;
}

INT16U	suwGetEEBatFloatTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatFloatTime;
}

INT16U 	suwGetEEBatLowShutDownSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEShutdownSOC;
}

INT16U	suwGetEEBatACRestartSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatRestartOutSOC;
}

INT16U	suwGetEEBatLowAlarmSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEELowBattSOC;
}

INT16U	suwGetEEBatConstVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatConstVolt;
}

INT16U	suwGetEEBatFloatVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatFloatVolt;
}

INT16U	suwGetEEBatLowShutDownVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEShutdownVolt;
}

INT16U	suwGetEEBatACRestartVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatRestartOutVolt;
}

INT16U	suwGetEEBatLowAlarmVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEELowBattVolt;
}

INT16U	suwGetEEBatVoltOverShut(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatVoltOverShut;
}

INT16U	suwGetEEBatEqVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqVolt;
}

INT16U	suwGetEERsvd66(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd66;
}

INT16U	suwGetEERsvd67(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd67;
}

INT16U	suwGetEEBattResistance(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBattResistance;
}

INT16U	suwGetEEBMSComErrEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBMSComErrEnable;
}

INT16U	suwGetEEBatParaEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatParaEnable;
}

INT16U	suwGetEEBatTempCompensateEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatTempCompensateEnable;
}

INT16U	suwGetBatTempCalibration(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatTempCalibration;
}

INT16U	suwGetEERsvd74(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd74;
}

INT16U	suwGetEERsvd75(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd75;
}

INT16U	suwGetEEBatEqEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqEn;
}

INT16U	suwGetEEBatEqTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqTime;
}

INT16U	suwGetEEBatEqTimeout(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqTimeout;
}

INT16U	suwGetEEBatEqInterval(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqInterval;
}

INT16U	suwGetEEBatEqActImd(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqActImd;
}

INT16U	suwGetEERsvd82(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd82;
}

INT16U	suwGetEERsvd83(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd83;
}

INT16U	suwGetEEBatLowVoltDerateEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatLowVoltDerateEnable;
}

INT16U	suwGetEEBatPowerOutEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatPowerOutEn;
}

INT16U	suwGetEEBMSErrStopEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEEBMSErrStopEn;
}

INT16U	suwGetEESOCDisplayEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEESOCDisplayEn;
}

INT16U	suwGetEERsvd88(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd88;
}

INT16U	suwGetEERsvd89(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd89;
}

INT16U	suwGetEERsvd90(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd90;
}

INT16U	suwGetEERsvd91(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd91;
}

INT16U	suwGetEERsvd92(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd92;
}

INT16U	suwGetEERsvd93(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd93;
}

INT16U	suwGetEERsvd94(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd94;
}

INT16U	suwGetEERsvd95(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd95;
}

INT16U	suwGetEERsvd96(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd96;
}

INT16U	suwGetEEBattAhReal(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhReal;
}

INT16U	suwGetEEBattAhMax(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhMax;
}

INT16U	suwGetEEBattFullCnt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattFullCnt;
}

INT16U	suwGetEEBattEmptyCnt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattEmptyCnt;
}

INT16U	suwGetEEBattCycCnt(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattCycCnt;
}

INT16U	suwGetEEBattAhRealShow(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhRealShow;
}

INT16U	suwGetEESOCSmoothEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEESOCSmoothEn;
}

INT16U	suwGetEERsvd104(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd104;
}

INT16U	suwGetEERsvd105(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd105;
}

INT16U	suwGetEERsvd106(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd106;
}

INT16U	suwGetEERsvd107(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd107;
}

INT16U	suwGetEERsvd108(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd108;
}

INT16U	suwGetEERsvd109(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd109;
}

INT16U	suwGetEERsvd110(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd110;
}

INT16U	suwGetEERsvd111(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd111;
}

INT16U	suwGetEERsvd112(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd112;
}

INT16U	suwGetEERsvd113(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd113;
}

INT16U	suwGetEERsvd114(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd114;
}

INT16U	suwGetEERsvd115(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd115;
}

INT16U	suwGetEERsvd116(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd116;
}

INT16U	suwGetEERsvd117(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd117;
}

INT16U	suwGetEERsvd118(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd118;
}

INT16U	suwGetEERsvd119(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd119;
}

INT16U	suwGetEERsvd120(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd120;
}

INT16U	suwGetEERsvd121(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd121;
}

INT16U	suwGetEERsvd122(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd122;
}

INT16U	suwGetEERsvd123(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd123;
}

INT16U	suwGetEERsvd124(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd124;
}

INT16U	suwGetEERsvd125(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd125;
}

INT16U	suwGetEERsvd126(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd126;
}

INT16U	suwGetEERsvd127(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd127;
}

INT16U	suwGetEERsvd128(void)
{
    return uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd128;
}

//strPvData
INT16U	suwGetEEPV1StartVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1StartVolt;
}

INT16U	suwGetEEPV1PowerLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1PowerLimit;
}

INT16U	suwGetEEPV2StartVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2StartVolt;
}

INT16U	suwGetEEPV1CurrrLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1CurrrLimit;
}

INT16U	suwGetEEPV2CurrrLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2CurrrLimit;
}

INT16U	suwGetEEPV2PowerLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2PowerLimit;
}

INT16U	suwGetEEMpptMultiPoint(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEMpptMultiPoint;
}

INT16U	suwGetEEPVInputMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEEPVInputMode;
}

INT16U	suwGetEERsvd137(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd137;
}

INT16U	suwGetEERsvd138(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd138;
}

INT16U	suwGetEERsvd139(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd139;
}

INT16U	suwGetEERsvd140(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd140;
}

INT16U	suwGetEERsvd141(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd141;
}

INT16U	suwGetEERsvd142(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd142;
}

INT16U	suwGetEERsvd143(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd143;
}

INT16U	suwGetEERsvd144(void)
{
    return uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd144;
}

//strAcData
INT16U	suwGetEEGridInputRange(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridInputRange;
}

INT16U	suwGetEEACOutputRatedFreq(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedFreq;
}

INT16U	suwGetEEACOutputRatedPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedPower;
}

INT16U	suwGetEEACOutputRatedVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedVolt;
}

INT16U	suwGetEEGridCurrLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridCurrLimit;
}

INT16U	suwGetEEGridInputPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridInputPower;
}

INT16U	suwGetEEMaxFeedPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridFeedPower;
}

INT16U	suwGetEEGridVoltUpperLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridVoltUpperLimit;
}

INT16U	suwGetEEGridVoltLowerLimit(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridVoltLowerLimit;
}

INT16U	suwGetEEAutoInvEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwAutoInvEn;
}

INT16U	suwGetEEDCDCOpenLoopEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwDCDCOpenEn;
}

INT16U	suwGetEERsvd151(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd151;
}

INT16U	suwGetEERsvd152(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd152;
}

INT16U	suwGetEEOverTempRestartEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverTempRestartEn;
}

INT16U	suwGetEEOverLoadRestartEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverLoadRestartEn;
}

INT16U	suwGetEEOverLoadBypassEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverLoadBypassEn;
}

INT16U	suwGetEERsvd156(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd156;
}

INT16U	suwGetEERsvd157(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd157;
}

INT16U	suwGetEERsvd158(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd158;
}

INT16U	suwGetEEOnGridAlwayOn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOnGridAlwayOn;
}

INT16U	suwGetEEOffGridImmediatelyOff(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOffGridImmediatelyOff;
}

INT16U	suwGetEEPVPowerRlyOn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEPVPowerRlyOn;
}

INT16U	suwGetEERlySocOn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERlySocOn;
}

INT16U	suwGetEERlySocOff(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERlySocOff;
}

INT16U	suwGetEERlyVoltOn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERlyVoltOn;
}

INT16U	suwGetEERlyVoltOff(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERlyVoltOff;
}

INT16U	suwGetEEOffGridWaitTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOffGridWaitTime;
}

INT16U	suwGetEEOnGridWaitTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEOnGridWaitTime;
}

INT16U	suwGetEEAnti_IslandProtectEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEIslandCheckEn;
}

INT16U	suwGetEERsvd169(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd169;
}

INT16U	suwGetEEFeedEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridFeedEn;
}

INT16U	suwGetEEGridMaxInputPowerLimitEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridMaxInputPowerLimitEn;
}

INT16U	suwGetEERsvd177(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd177;
}

INT16U	suwGetEERsvd178(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd178;
}

INT16U	suwGetEEZeroExportPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEZeroExportPower;
}

INT16U	suwGetEEGridPeakShavingEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridPeakShaving;
}

INT16U	suwGetEEGridPeakShavingPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridPeakShavingPower;
}

INT16U	suwGetEETurboMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEETurboMode;
}

INT16U	suwGetEETouMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEETouMode;
}

INT16U	suwGetEECloseGSRlyEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEECloseGSRlyEn;
}

INT16U	suwGetEEGridpowerslope(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridpowerslope;
}

INT16U	suwGetEEGridpowerlimitation(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridpowerlimitation;
}

INT16U	suwGetEEPVAutoInvEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwPvAutoInvEn;
}

INT16U	suwGetEERsvd188(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd188;
}

INT16U	suwGetEERsvd189(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd189;
}

INT16U	suwGetEERsvd190(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd190;
}

INT16U	suwGetEERsvd191(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd191;
}

INT16U	suwGetEERsvd192(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd192;
}

INT16U	suwGetEERsvd193(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd193;
}

INT16U	suwGetEERsvd194(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd194;
}

INT16U	suwGetEERsvd195(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd195;
}

INT16U	suwGetEERsvd196(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd196;
}

INT16U	suwGetEERsvd197(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd197;
}

INT16U	suwGetEERsvd198(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd198;
}

INT16U	suwGetEERsvd199(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd199;
}

INT16U	suwGetEERsvd200(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd200;
}

INT16U	suwGetEERsvd201(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd201;
}

INT16U	suwGetEERsvd202(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd202;
}

INT16U	suwGetEERsvd203(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd203;
}

INT16U	suwGetEERsvd204(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd204;
}

INT16U	suwGetEERsvd205(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd205;
}

INT16U	suwGetEERsvd206(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd206;
}

INT16U	suwGetEERsvd207(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd207;
}

INT16U	suwGetEERsvd208(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd208;
}

INT16U	suwGetEERsvd209(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd209;
}

INT16U	suwGetEERsvd210(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd210;
}

INT16U	suwGetEERsvd211(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd211;
}

INT16U	suwGetEERsvd212(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd212;
}

INT16U	suwGetEERsvd213(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd213;
}

INT16U	suwGetEERsvd214(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd214;
}

INT16U	suwGetEERsvd215(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd215;
}

INT16U	suwGetEERsvd216(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd216;
}

INT16U	suwGetEERsvd217(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd217;
}

INT16U	suwGetEERsvd218(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd218;
}

INT16U	suwGetEERsvd219(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd219;
}

INT16U	suwGetEERsvd220(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd220;
}

INT16U	suwGetEERsvd221(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd221;
}

INT16U	suwGetEERsvd222(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd222;
}

INT16U	suwGetEERsvd223(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd223;
}

INT16U	suwGetEERsvd224(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd224;
}

INT16U	suwGetGenMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetGenMode;
}

INT16U	suwGetGenInputEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetGenInputEn;
}

INT16U	suwGetGenInputMaxPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetGenInputMaxPower;
}

INT16U	suwGetGenConnectToGridPortEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetGenConnectToGridPortEn;
}

INT16U	suwGetSmartLoad_OpenPower(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_OpenPower;
}

INT16U	suwGetSmartLoad_StartBatVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_StartBatVolt;
}

INT16U	suwGetSmartLoad_ExitBatVolt(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_ExitBatVolt;
}

INT16U	suwGetSmartLoad_StartSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_StartSOC;
}

INT16U	suwGetSmartLoad_ExitSOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_ExitSOC;
}

INT16U	suwGetOnGrid_SmartLoadEn(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetOnGrid_SmartLoadEn;
}

INT16U	suwGetOffGrid_SmartLoadDis(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.eSetOffGrid_SmartLoadDis;
}

INT16U	suwGetEEDry1ContactMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEDry1ContactMode;
}

INT16U	suwGetEEDry2ContactMode(void)
{
    return uEepromCfg2.EepromStructCfg2.strAcData.uwEEDry2ContactMode;
}

//strReserve
INT16U	suwGetEERsvd238(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd238;
}

INT16U	suwGetEERsvd239(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd239;
}

INT16U	suwGetEERsvd240(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd240;
}

INT16U	suwGetEERsvd241(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd241;
}

INT16U	suwGetEERsvd242(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd242;
}

INT16U	suwGetEERsvd243(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd243;
}

INT16U	suwGetEERsvd244(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd244;
}

INT16U	suwGetEERsvd245(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd245;
}

INT16U	suwGetEERsvd246(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd246;
}

INT16U	suwGetEERsvd247(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd247;
}

INT16U	suwGetEERsvd248(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd248;
}

INT16U	suwGetEERsvd249(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd249;
}

INT16U	suwGetEERsvd250(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd250;
}

INT16U	suwGetEERsvd251(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd251;
}

INT16U	suwGetEERsvd252(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd252;
}

INT16U	suwGetEERsvd253(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd253;
}

INT16U	suwGetEERsvd254(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd254;
}

INT16U	suwGetEERsvd255(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd255;
}

INT16U	suwGetEERsvd256(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd256;
}

INT16U	suwGetEERsvd257(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd257;
}

INT16U	suwGetEERsvd258(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd258;
}

INT16U	suwGetEERsvd259(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd259;
}

INT16U	suwGetEERsvd260(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd260;
}

INT16U	suwGetEERsvd261(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd261;
}

INT16U	suwGetEERsvd262(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd262;
}

INT16U	suwGetEERsvd263(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd263;
}

INT16U	suwGetEERsvd264(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd264;
}

INT16U	suwGetEERsvd265(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd265;
}

INT16U	suwGetEERsvd266(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd266;
}

INT16U	suwGetEERsvd267(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd267;
}

INT16U	suwGetEERsvd268(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd268;
}

INT16U	suwGetEERsvd269(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd269;
}

INT16U	suwGetEERsvd270(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd270;
}

INT16U	suwGetEERsvd271(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd271;
}

INT16U	suwGetEERsvd272(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd272;
}

INT16U	suwGetEERsvd273(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd273;
}

INT16U	suwGetEERsvd274(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd274;
}

INT16U	suwGetEERsvd275(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd275;
}

INT16U	suwGetEERsvd276(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd276;
}

INT16U	suwGetEERsvd277(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd277;
}

INT16U	suwGetEERsvd278(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd278;
}

INT16U	suwGetEERsvd279(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd279;
}

INT16U	suwGetEERsvd280(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd280;
}

INT16U	suwGetEERsvd281(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd281;
}

INT16U	suwGetEERsvd282(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd282;
}

INT16U	suwGetEERsvd283(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd283;
}

INT16U	suwGetEERsvd284(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd284;
}

INT16U	suwGetEERsvd285(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd285;
}

INT16U	suwGetEERsvd286(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd286;
}

INT16U	suwGetEERsvd287(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd287;
}

INT16U	suwGetEERsvd288(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd288;
}

INT16U	suwGetEERsvd289(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd289;
}

INT16U	suwGetEERsvd290(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd290;
}

INT16U	suwGetEERsvd291(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd291;
}

INT16U	suwGetEERsvd292(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd292;
}

INT16U	suwGetEERsvd293(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd293;
}

INT16U	suwGetEERsvd294(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd294;
}

INT16U	suwGetEERsvd295(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd295;
}

INT16U	suwGetEERsvd296(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd296;
}

INT16U	suwGetEERsvd297(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd297;
}

INT16U	suwGetEERsvd298(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd298;
}

INT16U	suwGetEERsvd299(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd299;
}

INT16U	suwGetEERsvd300(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd300;
}

INT16U	suwGetEERsvd301(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd301;
}

INT16U	suwGetEERsvd302(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd302;
}

INT16U	suwGetEERsvd303(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd303;
}

INT16U	suwGetEERsvd304(void)
{
    return uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd304;
}

//strECOMode
INT16U suwGetEEECO_TimeOfUse(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO_TimeOfUse;
}

INT16U suwGetEEECO_EffectiveWeek(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO_EffectiveWeek;
}

INT16U suwGetEEECO1_GridChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_GridChargeEnable;
}

INT16U suwGetEEECO1_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_GenChargeEnable;
}

INT16U suwGetEEECO1_StartTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_StartTime;
}

INT16U suwGetEEECO1_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_StopTime;
}

INT16U suwGetEEECO1_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_Volt;
}

INT16U suwGetEEECO1_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_SOC;
}

INT16U suwGetEEECO1_Power(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_Power;
}

INT16U suwGetEEECO1_WorkModeSet(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_WorkModeSet;
}

INT16U suwGetEEECO2_GridChargeEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_GridChargeEnable;
}

INT16U suwGetEEECO2_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_GenChargeEnable;
}

INT16U suwGetEEECO2_StartTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_StartTime;
}

INT16U suwGetEEECO2_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_StopTime;
}

INT16U suwGetEEECO2_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_Volt;
}

INT16U suwGetEEECO2_SOC(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_SOC;
}

INT16U suwGetEEECO2_Power(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_Power;
}

INT16U suwGetEEECO2_WorkModeSet(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_WorkModeSet;
}

INT16U suwGetEEECO3_GridChargeEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_GridChargeEnable;
}

INT16U suwGetEEECO3_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_GenChargeEnable;
}

INT16U suwGetEEECO3_StartTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_StartTime;
}

INT16U suwGetEEECO3_StopTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_StopTime;
}

INT16U suwGetEEECO3_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_Volt;
}

INT16U suwGetEEECO3_SOC(void) 

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_SOC;
}

INT16U suwGetEEECO3_Power(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_Power;
}

INT16U suwGetEEECO3_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_WorkModeSet;
}

INT16U suwGetEEECO4_GridChargeEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_GridChargeEnable;
}

INT16U suwGetEEECO4_GenChargeEnable(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_GenChargeEnable;
}

INT16U suwGetEEECO4_StartTime(void)

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_StartTime;
}

INT16U suwGetEEECO4_StopTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_StopTime;
}

INT16U suwGetEEECO4_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_Volt;
}

INT16U suwGetEEECO4_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_SOC;
}

INT16U suwGetEEECO4_Power(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_Power;
}

INT16U suwGetEEECO4_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_WorkModeSet;
}

INT16U suwGetEEECO5_GridChargeEnable(void)

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_GridChargeEnable;
}

INT16U suwGetEEECO5_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_GenChargeEnable;
}

INT16U suwGetEEECO5_StartTime(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_StartTime;
}

INT16U suwGetEEECO5_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_StopTime;
}

INT16U suwGetEEECO5_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_Volt;
}

INT16U suwGetEEECO5_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_SOC;
}

INT16U suwGetEEECO5_Power(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_Power;
}

INT16U suwGetEEECO5_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_WorkModeSet;
}

INT16U suwGetEEECO6_GridChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_GridChargeEnable;
}

INT16U suwGetEEECO6_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_GenChargeEnable;
}

INT16U suwGetEEECO6_StartTime(void) 

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_StartTime;
}

INT16U suwGetEEECO6_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_StopTime;
}

INT16U suwGetEEECO6_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_Volt;
}

INT16U suwGetEEECO6_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_SOC;
}

INT16U suwGetEEECO6_Power(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_Power;
}

INT16U suwGetEEECO6_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_WorkModeSet;
}

INT16U suwGetEEECO7_GridChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_GridChargeEnable;
}

INT16U suwGetEEECO7_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_GenChargeEnable;
}

INT16U suwGetEEECO7_StartTime(void) 

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_StartTime;
}

INT16U suwGetEEECO7_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_StopTime;
}

INT16U suwGetEEECO7_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_Volt;
}

INT16U suwGetEEECO7_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_SOC;
}

INT16U suwGetEEECO7_Power(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_Power;
}

INT16U suwGetEEECO7_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_WorkModeSet;
}

INT16U suwGetEEECO8_GridChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_GridChargeEnable;
}

INT16U suwGetEEECO8_GenChargeEnable(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_GenChargeEnable;
}

INT16U suwGetEEECO8_StartTime(void) 

{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_StartTime;
}

INT16U suwGetEEECO8_StopTime(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_StopTime;
}

INT16U suwGetEEECO8_Volt(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_Volt;
}

INT16U suwGetEEECO8_SOC(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_SOC;
}

INT16U suwGetEEECO8_Power(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_Power;
}

INT16U suwGetEEECO8_WorkModeSet(void)
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_WorkModeSet;
}

INT16U suwGetEERsvd371(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwEERsvd371;
}

INT16U suwGetEERsvd372(void) 
{
    return uEepromCfg2.EepromStructCfg2.strECOMode.uwEERsvd372;
}


//strATESet
INT16U suwGetEEATE_UpdateFW(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_UpdateFW;
}

INT16U suwGetEEATE_SafetyCode(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_SafetyCode;
}

INT16U suwGetEEATE_ISOsetting(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_ISOsetting;
}

INT16U suwGetEEATE_EleMeterProc(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterProc;
}

INT16U suwGetEEATE_ExCommBps(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_ExCommBps;
}

INT16U suwGetEEATE_EleMeterBps_Parity(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterBps_Parity;
}

INT16U suwGetEEATE_EleMeterAddr(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterAddr;
}

INT16U suwGetEEATE_EleMeterWREn(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterWREn;
}

INT16U suwGetEEATE_EleMeterDataRegAddr(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterDataRegAddr;
}

INT16U suwGetEEATE_EleMeterData(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterData;
}

INT16U suwGetEEATE_485CommBps(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwATE_485CommBps;
}

INT16U suwGetEEMenuRtnDftPageEn(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwMenuRtnDftPageEn;
}

INT16U suwGetEELCDBacklight(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetLCDBacklight;
}

INT16U suwGetEEBuzzerBeep(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetBuzzerBeep;
}

INT16U suwGetEERsvd387(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd387;
}

INT16U suwGetEERsvd388(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd388;
}

INT16U suwGetEERsvd389(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd389;
}

INT16U suwGetEERsvd390(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd390;
}

INT16U suwGetEERsvd391(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd391;
}

INT16U suwGetEERsvd392(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd392;
}

INT16U suwGetEERsvd393(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd393;
}

INT16U suwGetEERsvd394(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd394;
}

INT16U suwGetEERsvd395(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd395;
}

INT16U suwGetEERsvd396(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd396;
}

INT16U suwGetEERsvd397(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd397;
}

INT16U suwGetEERsvd398(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd398;
}

INT16U suwGetEERsvd399(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd399;
}

INT16U suwGetEERsvd400(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd400;
}

INT16U suwGetEERsvd401(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd401;
}

INT16U suwGetEERsvd402(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd402;
}

INT16U suwGetEERsvd403(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd403;
}

INT16U suwGetEERsvd404(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd404;
}

INT16U suwGetEERsvd405(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd405;
}

INT16U suwGetEERsvd406(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd406;
}

INT16U suwGetEERsvd407(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd407;
}

INT16U suwGetEERsvd408(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd408;
}

INT16U suwGetEERsvd409(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd409;
}

INT16U suwGetEERsvd410(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd410;
}

INT16U suwGetEERsvd411(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd411;
}

INT16U suwGetEERsvd412(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd412;
}

INT16U suwGetEERsvd413(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd413;
}

INT16U suwGetEERsvd414(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd414;
}

INT16U suwGetEERsvd415(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd415;
}

INT16U suwGetEERsvd416(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd416;
}

INT16U suwGetEERsvd417(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd417;
}

INT16U suwGetEERsvd418(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd418;
}

INT16U suwGetEERsvd419(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd419;
}

INT16U suwGetEERsvd420(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd420;
}

INT16U suwGetEEBmsBagAddr(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetBmsBagAddr;
}

INT16U suwGetEEClearEventLog(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetClearEventLog;
}

INT16U suwGetEEEventLogFunc(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetEventLogFunc;
}

INT16U suwGetEEFaultLogFunc(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetFaultLogFunc;
}

INT16U suwGetEELogType(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetLogType;
}

INT16U suwGetEELogIndex(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwSetLogIndex;
}

INT16U suwGetEERsvd427(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd427;
}

INT16U suwGetEERsvd428(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd428;
}

INT16U suwGetEERsvd429(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd429;
}

INT16U suwGetEERsvd430(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd430;
}

INT16U suwGetEERsvd431(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd431;
}

INT16U suwGetEERsvd432(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd432;
}

INT16U suwGetEERsvd433(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd433;
}

INT16U suwGetEERsvd434(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd434;
}

INT16U suwGetEERsvd435(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd435;
}

INT16U suwGetEERsvd436(void)
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd436;
}

INT16U suwGetEEFlag2(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwFlag2;
}

INT16U suwGetEECheckCRC2(void) 
{
    return uEepromCfg2.EepromStructCfg2.strATESet.uwEECheckCRC2;
}
 
//EEPROM3
INT16U suwGetEEGrid1OVValue(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1OVValue;
}

INT16U suwGetEEGrid1OVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1OVTime;
}

INT16U suwGetEEGrid2OVValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2OVValue;
}

INT16U suwGetEEGrid2OVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2OVTime;
}

INT16U suwGetEEGrid3OVValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3OVValue;
}

INT16U suwGetEEGrid3OVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3OVTime;
}

INT16U suwGetEEGrid1UVValue(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1UVValue;
}

INT16U suwGetEEGrid1UVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1UVTime;
}

INT16U suwGetEEGrid2UVValue(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2UVValue;
}

INT16U suwGetEEGrid2UVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2UVTime;
}

INT16U suwGetEEGrid3UVValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3UVValue;
}

INT16U suwGetEEGrid3UVTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3UVTime;
}

INT16U suwGetEEGrid1OFValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1OFValue;
}

INT16U suwGetEEGrid1OFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1OFTime;
}

INT16U suwGetEEGrid2OFValue(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2OFValue;
}

INT16U suwGetEEGrid2OFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2OFTime;
}

INT16U suwGetEEGrid3OFValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3OFValue;
}

INT16U suwGetEEGrid3OFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3OFTime;
}

INT16U suwGetEEGrid1UFValue(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1UFValue;
}

INT16U suwGetEEGrid1UFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid1UFTime;
}

INT16U suwGetEEGrid2UFValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2UFValue;
}

INT16U suwGetEEGrid2UFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid2UFTime;
}

INT16U suwGetEEGrid3UFValue(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3UFValue;
}

INT16U suwGetEEGrid3UFTime(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetGrid3UFTime;
}

INT16U suwGetSetRsvd558(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd558;
}

INT16U suwGetSetRsvd559(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd559;
}

INT16U suwGetSetRsvd560(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd560;
}

INT16U suwGetSetRsvd561(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd561;
}

INT16U suwGetSetRsvd562(void)
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd562;
}

INT16U suwGetSetRsvd563(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwSetRsvd563;
}

INT16U suwGetEEFlag3(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwFlag3;
}

INT16U suwGetEECheckCRC3(void) 
{
    return uEepromCfg3.EepromStructCfg3.uwEECheckCRC3;
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

//EEPROM1
void sSetEEMachineCode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwMachCode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SN1(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SN1 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SN2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SN2 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SN3(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SN3 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SN4(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SN4 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SN5(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SN5 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_SNLen(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_SNLen = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_DispHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_DispHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_CtrlHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_CtrlHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEE_PowerHwVer(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEE_PowerHwVer = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1VoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV1VoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1VoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV1VoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2VoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV2VoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2VoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV2VoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1BatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV1BatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV1BatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV1BatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2BatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV2BatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEPV2BatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEPV2BatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBatVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBatVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBatCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBatCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBatCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBUSVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBUSVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBUSCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBUSCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEBUSCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEInvVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEInvVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEInvCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEInvCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEInvCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGridVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGridVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGridCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGridCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGridCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOPVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEOPVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOpVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEOpVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOPCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEOPCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEOpCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEOpCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEDischargeEneyCoeffH(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEDischargeEneyCoeffH = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEDischargeEneyCoeffL(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEDischargeEneyCoeffL = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEchargeEneyCoeffH(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEchargeEneyCoeffH = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEchargeEneyCoeffL(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEchargeEneyCoeffL = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGenVoltAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGenVoltAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGenVoltBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGenVoltBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGenCurrAdj(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGenCurrAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGenCurrBias(INT16S uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEEGenCurrBias = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd5(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd5 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd6(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd6 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd7(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd7 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd8(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd8 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd9(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd9 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd10(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd10 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd11(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd11 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd12(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd12 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd13(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd13 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd14(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd14 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd15(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd15 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd16(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd16 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd17(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd17 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd18(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd18 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd19(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd19 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd20(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd20 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd21(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd21 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd22(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd22 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd23(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd23 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd24(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd24 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd25(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd25 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd26(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd26 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd27(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd27 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd28(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd28 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd29(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd29 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd30(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd30 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd31(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd31 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd32(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd32 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd33(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd33 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd34(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd34 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd35(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd35 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd36(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd36 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd37(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd37 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd38(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd38 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd39(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd39 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd40(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd20 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd41(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd41 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd42(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd42 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd43(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd43 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd44(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd44 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd45(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd45 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd46(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd46 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd47(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd47 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd48(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd48 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd49(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd49 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd50(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd50 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd51(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd51 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd52(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwSetRsvd52 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFlag1(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwFlag1 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEECheckCRC1(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg1.EepromStructCfg1.uwEECheckCRC1 = uwtemp;
    OS_EXIT_CRITICAL();
}  

//EEPROM2
//strControlState
void	sSetEEParaEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallel = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEMasterSlaver(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEParalleltMasterSlaver = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEParallelPhase(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallelPhase = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEParallelIID(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEParallelIID = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEESystemOutputMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwSetSystemOutputMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEWorkMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEWorkMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEFanWorkMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEFanWorkMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPowerConversion(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEPowerConversion = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPowerSaveMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEPowerSaveMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEENoBatMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEENoBatMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEELogoEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEELogoEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEAdcBiasAdj(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEEAdcBiasAdj = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetLeakCurrProtectEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.eSetLeakCurrProtectEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetLeakCurrProtectValue(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.eSetLeakCurrProtectValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetISOCheckEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.eSetISOCheckEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetISOCheckValue(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.eSetISOCheckValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd17(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd17 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd18(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd18 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd19(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd19 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd20(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd20 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd21(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd21 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd22(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd22 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd23(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd23 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd24(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd24 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd25(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd25 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd26(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd26 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd27(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd27 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd28(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd28 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd29(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd29 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd30(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd30 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd31(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd31 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd32(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strControlState.uwEERsvd32 = uwtemp;
    OS_EXIT_CRITICAL();
}

//strBatData
void	sSetEEBatType(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatType = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatSeriesNum(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatSeriesNum = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatActivateEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatActivate = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatCapacity(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatCapacity = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEELithiumMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEELithiumMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd38(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd38 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatMaxChgCurr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatMaxChgCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatMaxDcgCurr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatMaxDcgCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatVoltage(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatVoltage = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd42(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd42 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridChargeEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridChargeEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridChgBatCurr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridMaxChargeCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridBatAutoStartChgVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridStartChargeVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridBatExitAutoChgVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridEndChargeVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridBatAutoStartChgSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridStartChargeSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridBatExitAutoChgSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGridEndChargeSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd49(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd49 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenChargeEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenChargeEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenMaxChargeCurr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenMaxChargeCurr = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenStartChargeVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenStartChargeVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenEndChargeVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenEndChargeVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenStartChargeSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenStartChargeSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGenEndChargeSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEGenEndChargeSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd56(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd56 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatFloatTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatFloatTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void 	sSetEEBatLowShutDownSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEShutdownSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatACRestartSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatRestartOutSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatLowAlarmSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEELowBattSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatConstVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatConstVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatFloatVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatFloatVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatLowShutDownVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEShutdownVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatACRestartVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatRestartOutVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatLowAlarmVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEELowBattVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatVoltOverShut(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatVoltOverShut = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd66(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd66 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd67(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd67 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattResistance(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBattResistance = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBMSComErrEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBMSComErrEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatParaEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatParaEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatTempCompensateEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatTempCompensateEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetBatTempCalibration(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwSetBatTempCalibration = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd74(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd74 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd75(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd75 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqTimeout(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqTimeout = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqInterval(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqInterval = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatEqActImd(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatEqActImd = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd82(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd82 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd83(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd83 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatLowVoltDerateEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatLowVoltDerateEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBatPowerOutEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBatPowerOutEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBMSErrStopEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEEBMSErrStopEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEESOCDisplayEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEESOCDisplayEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd88(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd88 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd89(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd89 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd90(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd90 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd91(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd91 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd92(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd92 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd93(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd93 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd94(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd94 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd95(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd95 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd96(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd96 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattAhReal(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhReal = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattAhMax(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhMax = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattFullCnt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattFullCnt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattEmptyCnt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattEmptyCnt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattCycCnt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattCycCnt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEBattAhRealShow(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwBattAhRealShow = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEESOCSmoothEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEESOCSmoothEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd104(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd104 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd105(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd105 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd106(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd106 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd107(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd107 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd108(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd108 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd109(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd109 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd110(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd110 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd111(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd111 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd112(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd112 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd113(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd113 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd114(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd114 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd115(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd115 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd116(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd116 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd117(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd117 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd118(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd118 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd119(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd119 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd120(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd120 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd121(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd121 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd122(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd122 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd123(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd123 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd124(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd124 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd125(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd125 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd126(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd126 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd127(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd127 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd128(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strBatData.uwEERsvd128 = uwtemp;
    OS_EXIT_CRITICAL();
}

//strPvData
void	sSetEEPV1StartVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1StartVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPV1PowerLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1PowerLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPV2StartVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2StartVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPV1CurrrLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV1CurrrLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPV2CurrrLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2CurrrLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPV2PowerLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPV2PowerLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEMpptMultiPoint(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEMpptMultiPoint = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPVInputMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEEPVInputMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd137(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd137 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd138(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd138 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd139(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd139 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd140(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd140 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd141(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd141 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd142(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd142 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd143(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd143 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd144(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strPvData.uwEERsvd144 = uwtemp;
    OS_EXIT_CRITICAL();
}

//strAcData
void	sSetEEGridInputRange(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridInputRange = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEACOutputRatedFreq(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedFreq = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEACOutputRatedPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEACOutputRatedVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEACOutputRatedVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridCurrLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridCurrLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridInputPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridInputPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEMaxFeedPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridFeedPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridVoltUpperLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridVoltUpperLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSeEEGridVoltLowerLimit(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridVoltLowerLimit = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEAutoInvEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwAutoInvEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEDCDCOpenLoopEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwDCDCOpenEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd151(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd151 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd152(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd152 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOverTempRestartEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverTempRestartEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOverLoadRestartEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverLoadRestartEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOverLoadBypassEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOverLoadBypassEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd156(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd156 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd157(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd157 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd158(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd158 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridAlwayOn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOnGridAlwayOn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOffGridImmediatelyOff(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOffGridImmediatelyOff = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPVPowerRlyOn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEPVPowerRlyOn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERlySocOn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERlySocOn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERlySocOff(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERlySocOff = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERlyVoltOn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERlyVoltOn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERlyVoltOff(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERlyVoltOff = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOffGridWaitTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOffGridWaitTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEOnGridWaitTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEOnGridWaitTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEAnti_IslandProtectEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEIslandCheckEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd169(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd169 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEFeedEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridFeedEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridMaxInputPowerLimitEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridMaxInputPowerLimitEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd177(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd177 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd178(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd178 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEZeroExportPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEZeroExportPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridPeakShavingEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridPeakShaving = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridPeakShavingPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridPeakShavingPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEETurboMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEETurboMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEETouMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEETouMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEECloseGSRlyEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEECloseGSRlyEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridpowerslope(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridpowerslope = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEGridpowerlimitation(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEGridpowerlimitation = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEPVAutoInvEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwPvAutoInvEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd188(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd188 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd189(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd189 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd190(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd190 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd191(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd191 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd192(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd192 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd193(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd193 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd194(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd194 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd195(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd195 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd196(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd196 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd197(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd197 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd198(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd198 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd199(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd199 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd200(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd200 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd201(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd201 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd202(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd202 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd203(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd203 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd204(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd204 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd205(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd205 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd206(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd206 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd207(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd207 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd208(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd208 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd209(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd209 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd210(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd210 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd211(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd211 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd212(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd212 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd213(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd213 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd214(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd214 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd215(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd215 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd216(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd216 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd217(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd217 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd218(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd218 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd219(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd219 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd220(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd220 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd221(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd221 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd222(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd222 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd223(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd223 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd224(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEERsvd224 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetGenMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetGenMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetGenInputEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetGenInputEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetGenInputMaxPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetGenInputMaxPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetGenConnectToGridPortEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetGenConnectToGridPortEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetSmartLoad_OpenPower(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_OpenPower = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetSmartLoad_StartBatVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_StartBatVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetSmartLoad_ExitBatVolt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_ExitBatVolt = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetSmartLoad_StartSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_StartSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetSmartLoad_ExitSOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetSmartLoad_ExitSOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetOnGrid_SmartLoadEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetOnGrid_SmartLoadEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetOffGrid_SmartLoadDis(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.eSetOffGrid_SmartLoadDis = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEDry1ContactMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEDry1ContactMode = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEEDry2ContactMode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strAcData.uwEEDry2ContactMode = uwtemp;
    OS_EXIT_CRITICAL();
}

//strReserve
void	sSetEERsvd238(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd238 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd239(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd239 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd240(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd240 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd241(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd241 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd242(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd242 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd243(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd243 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd244(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd244 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd245(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd245 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd246(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd246 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd247(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd247 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd248(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd248 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd249(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd249 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd250(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd250 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd251(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd251 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd252(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd252 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd253(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd253 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd254(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd254 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd255(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd255 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd256(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd256 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd257(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd257 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd258(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd258 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd259(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd259 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd260(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd260 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd261(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd261 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd262(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd262 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd263(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd263 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd264(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd264 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd265(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd265 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd266(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd266 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd267(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd267 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd268(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd268 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd269(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd269 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd270(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd270 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd271(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd271 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd272(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd272 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd273(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd273 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd274(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd274 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd275(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd275 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd276(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd276 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd277(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd277 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd278(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd278 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd279(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd279 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd280(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd280 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd281(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd281 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd282(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd282 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd283(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd283 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd284(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd284 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd285(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd285 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd286(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd286 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd287(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd287 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd288(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd288 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd289(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd289 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd290(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd290 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd291(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd291 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd292(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd292 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd293(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd293 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd294(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd294 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd295(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd295 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd296(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd296 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd297(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd297 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd298(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd298 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd299(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd299 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd300(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd300 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd301(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd301 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd302(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd302 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd303(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd303 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd304(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strReserve.uwEERsvd304 = uwtemp;
    OS_EXIT_CRITICAL();
}

//strECOMode
void sSetEEECO_TimeOfUse(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO_TimeOfUse = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO_EffectiveWeek(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO_EffectiveWeek = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_GridChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_StartTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_Volt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_SOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO1_WorkModeSet(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO1_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_GenChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_StartTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_Power(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO2_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO2_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_GenChargeEnable(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_Volt(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_SOC(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO3_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO3_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_StopTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO4_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO4_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_SOC(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO5_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO5_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_SOC(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO6_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO6_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_SOC(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO7_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO7_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_GridChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_GridChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_GenChargeEnable(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_GenChargeEnable = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_StartTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_StartTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_StopTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_StopTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_Volt(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_Volt = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_SOC(INT16U uwtemp) 

{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_SOC = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_Power(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_Power = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEECO8_WorkModeSet(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwSetECO8_WorkModeSet = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd371(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwEERsvd371 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEERsvd372(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strECOMode.uwEERsvd372 = uwtemp;
    OS_EXIT_CRITICAL();
}  

//strATESet
void sSetEEATE_UpdateFW(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_UpdateFW = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_SafetyCode(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_SafetyCode = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_ISOsetting(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_ISOsetting = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterProc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterProc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_ExCommBps(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_ExCommBps = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterBps_Parity(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterBps_Parity = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterWREn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterWREn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterDataRegAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterDataRegAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_EleMeterData(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_EleMeterData = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEATE_485CommBps(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwATE_485CommBps = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEMenuRtnDftPageEn(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwMenuRtnDftPageEn = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELCDBacklight(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetLCDBacklight = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBuzzerBeep(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetBuzzerBeep = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd387(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd387 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd388(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd388 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd389(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd389 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd390(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd390 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd391(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd391 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd392(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd392 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd393(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd393 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd394(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd394 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd395(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd395 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd396(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd396 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd397(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd397 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd398(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd398 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd399(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd399 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd400(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd400 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd401(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd401 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd402(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd402 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd403(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd403 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd404(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd404 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd405(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd405 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd406(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd406 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd407(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd407 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd408(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd408 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd409(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd409 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd410(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd410 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd411(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd411 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd412(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd412 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd413(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd413 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd414(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd414 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd415(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd415 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd416(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd416 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd417(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd417 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd418(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd418 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd419(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd419 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd420(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd420 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEBmsBagAddr(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetBmsBagAddr = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEClearEventLog(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetClearEventLog = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEEventLogFunc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetEventLogFunc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFaultLogFunc(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetFaultLogFunc = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELogType(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetLogType = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEELogIndex(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwSetLogIndex = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd427(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd427 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd428(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd428 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd429(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd429 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd430(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd430 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd431(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd431 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd432(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd432 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd433(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd433 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd434(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd434 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd435(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd435 = uwtemp;
    OS_EXIT_CRITICAL();
}

void	sSetEERsvd436(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEERsvd436 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEFlag2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwFlag2 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEECheckCRC2(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg2.EepromStructCfg2.strATESet.uwEECheckCRC2 = uwtemp;
    OS_EXIT_CRITICAL();
}


//EEPROM3
void sSetEEGrid1OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OVTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OVTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3OVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OVTime(INT16U uwtemp)

{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3OVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UVValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3UVValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UVTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3UVTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1OFTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2OFTime(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OFValue(INT16U uwtemp)
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3OFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3OFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3OFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid1UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid1UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid2UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid2UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UFValue(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3UFValue = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetEEGrid3UFTime(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetGrid3UFTime = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd558(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd558 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd559(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd559 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd560(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd560 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd561(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd561 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd562(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd562 = uwtemp;
    OS_EXIT_CRITICAL();
}

void sSetSetRsvd563(INT16U uwtemp) 
{
    OS_ENTER_CRITICAL();
    uEepromCfg3.EepromStructCfg3.uwSetRsvd563 = uwtemp;
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




