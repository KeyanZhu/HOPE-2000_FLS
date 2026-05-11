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


//新协议 20260202
struct EepromStruct1
{
	INT16U	uwMachCode;					//	0 机型代码
	INT16U	uwEE_SN1;					//	1 机器序列号1
	INT16U	uwEE_SN2;					//	2 机器序列号2
	INT16U	uwEE_SN3;					//	3 机器序列号3
	INT16U	uwEE_SN4;					//	4 机器序列号4
	INT16U	uwEE_SN5;					//	5 机器序列号5
	INT16U	uwEE_SNLen;					//	6 机器序列号长度
	INT16U	uwEE_DispHwVer;				//	7 ATE写显示板版本号
	INT16U	uwEE_CtrlHwVer;				//	8 ATE写控制板版本号
	INT16U	uwEE_PowerHwVer;			//	9 ATE写功率板版本号
	INT16S	uwEEPV1VoltAdj;				//	10 PV1电压校准系数
	INT16S	uwEEPV1VoltBias; 			//	11 PV1电压校准偏置
	INT16S	uwEEPV2VoltAdj;				//	12 PV2电压校准系数
	INT16S	uwEEPV2VoltBias; 			//	13 PV2电压校准偏置
	INT16S	uwEEPV1BatCurrAdj;			//	14 PV1电池电流校准系数
	INT16S	uwEEPV1BatCurrBias; 		//	15 PV1电池电流校准偏置
	INT16S	uwEEPV2BatCurrAdj;			//	16 PV2电池电流校准系数
	INT16S	uwEEPV2BatCurrBias; 		//	17 PV2电池电流校准偏置
	INT16S	uwEEBatVoltAdj;				//	18 电池电压校准系数
	INT16S	uwEEBatVoltBias; 			//	19 电池电压校准偏置
	INT16S	uwEEBatCurrAdj;				//	20 电池电流校准系数
	INT16S	uwEEBatCurrBias; 			//	21 电池电流校准偏置
	INT16S	uwEEBUSVoltAdj;				//	22 Bus电压校准系数
	INT16S	uwEEBUSVoltBias; 			//	23 Bus电压校准偏置
	INT16S	uwEEBUSCurrAdj;				//	24 Bus电流校准系数
	INT16S	uwEEBUSCurrBias; 			//	25 Bus电流校准偏置
	INT16S	uwEEInvVoltAdj;				//	26 逆变电压校准系数
	INT16S	uwEEInvVoltBias; 			//	27 逆变电压校准偏置
	INT16S	uwEEInvCurrAdj;				//	28 逆变电流校准系数
	INT16S	uwEEInvCurrBias; 			//	29 逆变电流校准偏置
	INT16S	uwEEGridVoltAdj; 			//	30 电网电压校准系数
	INT16S	uwEEGridVoltBias;			//	31 电网电压校准偏置
	INT16S	uwEEGridCurrAdj; 			//	32 电网电流校准系数
	INT16S	uwEEGridCurrBias;			//	33 电网电流校准偏置
	INT16S	uwEEOPVoltAdj;				//	34 输出电压校准系数
	INT16S	uwEEOpVoltBias;				//	35 输出电压校准偏置
	INT16S	uwEEOPCurrAdj;				//	36 输出电流校准系数
	INT16S	uwEEOpCurrBias;				//	37 输出电流校准偏置
	INT16U	uwEEDischargeEneyCoeffH; 	//	38 放电量校准高位
	INT16U	uwEEDischargeEneyCoeffL; 	//	39 放电量校准低位
	INT16U	uwEEchargeEneyCoeffH;		//	40 充电量校准高位
	INT16U	uwEEchargeEneyCoeffL;		//	41 充电量校准低位
	INT16U	uwEEGenVoltAdj; 			//	42 Gen电压校准系数
	INT16U	uwEEGenVoltBias; 			//	43 Gen电压校准偏置
	INT16U	uwEEGenCurrAdj; 			//	44 Gen电流校准系数
	INT16U	uwEEGenCurrBias; 			//	45 Gen电流校准偏置
	INT16U	uwSetRsvd5; 				//	46 预留
	INT16U	uwSetRsvd6; 				//	47 预留
	INT16U	uwSetRsvd7; 				//	48 预留
	INT16U	uwSetRsvd8; 				//	49 预留
	INT16U	uwSetRsvd9; 				//	50 预留
	INT16U	uwSetRsvd10; 				//	51 预留
	INT16U	uwSetRsvd11; 				//	52 预留
	INT16U	uwSetRsvd12; 				//	53 预留
	INT16U	uwSetRsvd13; 				//	54 预留
	INT16U	uwSetRsvd14;				//	55 预留
	INT16U	uwSetRsvd15;				//	56 预留
	INT16U	uwSetRsvd16;				//	57 预留
	INT16U	uwSetRsvd17;				//	58 预留
	INT16U	uwSetRsvd18;				//	59 预留
	INT16U	uwSetRsvd19;				//	60 预留
	INT16U	uwSetRsvd20;				//	61 预留
	INT16U	uwSetRsvd21;				//	62 预留
	INT16U	uwSetRsvd22;				//	63 预留
	INT16U	uwSetRsvd23;				//	64 预留
	INT16U	uwSetRsvd24;				//	65 预留
	INT16U	uwSetRsvd25;				//	66 预留
	INT16U	uwSetRsvd26;				//	67 预留
	INT16U	uwSetRsvd27;				//	68 预留
	INT16U	uwSetRsvd28;				//	69 预留
	INT16U	uwSetRsvd29;				//	70 预留
	INT16U	uwSetRsvd30;				//	71 预留
	INT16U	uwSetRsvd31;				//	72 预留
	INT16U	uwSetRsvd32;				//	73 预留
	INT16U	uwSetRsvd33;				//	74 预留
	INT16U	uwSetRsvd34;				//	75 预留
	INT16U	uwSetRsvd35;				//	76 预留
	INT16U	uwSetRsvd36;				//	77 预留
	INT16U	uwSetRsvd37;				//	78 预留
	INT16U	uwSetRsvd38;				//	79 预留
	INT16U	uwSetRsvd39;				//	80 预留
	INT16U	uwSetRsvd40;				//	81 预留
	INT16U	uwSetRsvd41;				//	82 预留
	INT16U	uwSetRsvd42;				//	83 预留
	INT16U	uwSetRsvd43;				//	84 预留
	INT16U	uwSetRsvd44;				//	85 预留
	INT16U	uwSetRsvd45;				//	86 预留
	INT16U	uwSetRsvd46;				//	87 预留
	INT16U	uwSetRsvd47;				//	88 预留
	INT16U	uwSetRsvd48;				//	89 预留
	INT16U	uwSetRsvd49;				//	90 预留
	INT16U	uwSetRsvd50;				//	91 预留
	INT16U	uwSetRsvd51;				//	92 预留
	INT16U	uwSetRsvd52;				//	93 预留
	INT16U	uwFlag1;					//	94 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC1;				//	95 CRC校验
};

typedef struct
{
	INT16U	uwEEParallel;				//	96	并机使能
	INT16U	uwEEParalleltMasterSlaver;	//	97	并机角色 
	INT16U	uwEEParallelPhase; 			//	98	并机相位
	INT16U	uwEEParallelIID;			//	99	并机ID
	INT16U	uwSetSystemOutputMode;		//	100	系统输出模式
	INT16U	uwEEWorkMode;				//	101	工作模式
	INT16U	uwEEFanWorkMode; 			//	102	风机运行模式
	INT16U	uwEEPowerConversion;		//	103	功率折算使能
	INT16U	uwEEPowerSaveMode;			//	104	节能模式
	INT16U	uwEENoBatMode;				//	105	无电池模式
	INT16U	uwEELogoEnable;				//	106	logo使能
	INT16U	uwEEAdcBiasAdj;				//	107	采样偏置校准
	INT16U	eSetLeakCurrProtectEnable;	//	108	漏电流GFCI保护使能
	INT16U	eSetLeakCurrProtectValue;	//	109	漏电流GFCI保护阀值
	INT16U	eSetISOCheckEnable;			//	110	绝缘阻抗检测使能
	INT16U	eSetISOCheckValue;			//	111	绝缘阻抗检测阀值
	INT16U	uwEERsvd17;					//	112 预留
	INT16U	uwEERsvd18;					//	113 预留
	INT16U	uwEERsvd19;					//	114 预留
	INT16U	uwEERsvd20;					//	115 预留
	INT16U	uwEERsvd21;					//	116 预留
	INT16U	uwEERsvd22;					//	117 预留
	INT16U	uwEERsvd23;					//	118 预留
	INT16U	uwEERsvd24;					//	119 预留
	INT16U	uwEERsvd25;					//	120 预留
	INT16U	uwEERsvd26;					//	121 预留
	INT16U	uwEERsvd27;					//	122 预留
	INT16U	uwEERsvd28;					//	123 预留
	INT16U	uwEERsvd29;					//	124 预留
	INT16U	uwEERsvd30;					//	125 预留
	INT16U	uwEERsvd31;					//	126 预留
	INT16U	uwEERsvd32;					//	127 预留
}strControlStateSet;
#define cControlStateSetLength  ((sizeof(strControlStateSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwEEBatType;				//	128	电池类型
	INT16U	uwEEBatSeriesNum;			//	129	电池节数 在HOPE里面就是电芯节数
	INT16U	uwEEBatActivate;			//	130	电池激活
	INT16U	uwEEBatCapacity; 			//	131	电池额定容量 0.1AH
	INT16U	uwEELithiumMode; 			//	132	锂电池模式
	INT16U	uwEERsvd38; 				//	133 预留
	INT16U	uwEEBatMaxChgCurr;			//	134	电池最大充电电流限幅值
	INT16U	uwEEBatMaxDcgCurr;			//	135	电池最大放电电流限幅值
	INT16U	uwEEBatVoltage;				//	136	电池额定电压(电池节数)
	INT16U	uwEERsvd42; 				//	137 预留
	INT16U	uwEEGridChargeEn;			//	138	市电充电使能
	INT16U	uwEEGridMaxChargeCurr;		//	139	市电最大充电电流
	INT16U	uwEEGridStartChargeVolt;	//	140	市电开始充电电池电压
	INT16U	uwEEGridEndChargeVolt;		//	141	市电停止充电电池电压
	INT16U	uwEEGridStartChargeSOC;		//	142	市电开始充电电池SOC
	INT16U	uwEEGridEndChargeSOC; 		//	143	市电停止充电电池SOC
	INT16U	uwEERsvd49; 				//	144 预留
	INT16U	uwEEGenChargeEn;			//	145	油机充电使能
	INT16U	uwEEGenMaxChargeCurr;		//	146	油机最大充电电流
	INT16U	uwEEGenStartChargeVolt;		//	147	油机开始充电电池电压
	INT16U	uwEEGenEndChargeVolt;		//	148	油机停止充电电池电压
	INT16U	uwEEGenStartChargeSOC;		//	149	油机开始充电电池SOC
	INT16U	uwEEGenEndChargeSOC; 		//	150	油机停止充电电池SOC
	INT16U	uwEERsvd56; 				//	151 预留
	INT16U	uwSetBatConstVolt;			//	152	电池恒压充电压
	INT16U	uwSetBatFloatVolt;			//	153	电池浮充电压
	INT16U	uwSetBatFloatTime;			//	154	电池恒充时间
	INT16U	uwEEShutdownSOC;			//	155	电池停止输出SOC
	INT16U	uwEEShutdownVolt;			//	156	电池停止输出电压
	INT16U	uwEEBatRestartOutSOC; 		//	157	电池重启输出SOC恢复输出SOC
	INT16U	uwEEBatRestartOutVolt;		//	158	电池重启输出电压恢复输出电压
	INT16U	uwEELowBattSOC;				//	159	电池电量低电量SOC
	INT16U	uwEELowBattVolt; 			//	160	电池电量低电量电压
	INT16U	uwEERsvd66; 				//	161 预留
	INT16U	uwEERsvd67; 				//	162 预留
	INT16U	uwEEBattResistance; 		//	163 电池线路阻抗
	INT16U	uwSetBatVoltOverShut; 		//	164	电池过压保护点
	INT16U	uwSetBMSComErrEnable; 		//	165	BMS通讯故障使能
	INT16U	uwSetBatParaEnable;			//	166	电池并联使能
	INT16U	uwSetBatTempCompensateEnable; //167	电池温度补偿使能
	INT16U	uwSetBatTempCalibration; 	//	168	电池温度补偿系数
	INT16U	uwEERsvd74; 				//	169 预留
	INT16U	uwEERsvd75; 				//	170 预留
	INT16U	uwEEBatEqEn;				//	171	EQ使能
	INT16U	uwEEBatEqVolt;				//	172	EQ电压
	INT16U	uwEEBatEqTime;				//	173	EQ时间
	INT16U	uwEEBatEqTimeout;			//	174	EQ超时时间
	INT16U	uwEEBatEqInterval;			//	175	EQ间隔时间
	INT16U	uwEEBatEqActImd;			//	176	立即EQ使能
	INT16U	uwEERsvd82; 				//	177 预留
	INT16U	uwEERsvd83; 				//	178 预留
	INT16U	uwEEBatLowVoltDerateEnable; //	179	电池低压降额使能
	INT16U	uwEEBatPowerOutEn; 			//	180	电池出功使能
	INT16U	uwEEBMSErrStopEn; 			//	181	BMS异常停止工作
	INT16U	uwEESOCDisplayEn; 			//	182	主页显示SOC
	INT16U	uwEERsvd88; 				//	183 预留
	INT16U	uwEERsvd89; 				//	184 预留
	INT16U	uwEERsvd90; 				//	185 预留
	INT16U	uwEERsvd91; 				//	186 预留
	INT16U	uwEERsvd92; 				//	187 预留
	INT16U	uwEERsvd93; 				//	188 预留
	INT16U	uwEERsvd94; 				//	189 预留
	INT16U	uwEERsvd95; 				//	190 预留
	INT16U	uwEERsvd96; 				//	191 预留
	INT16U	uwBattAhReal; 				//	192 电池剩余容量
	INT16U	uwBattAhMax; 				//	193 电池最大容量	//
	INT16U	uwBattFullCnt; 				//	194 电池充满次数
	INT16U	uwBattEmptyCnt; 			//	195 电池放空次数
	INT16U	uwBattCycCnt; 				//	196 电池循环次数
	INT16U	uwBattAhRealShow; 			//	197 电池显示剩余容量
	INT16U	uwEESOCSmoothEn; 			//	198 SOC平滑使能
	INT16U	uwEERsvd104; 				//	199 预留
	INT16U	uwEERsvd105; 				//	200 预留
	INT16U	uwEERsvd106; 				//	201 预留
	INT16U	uwEERsvd107; 				//	202 预留
	INT16U	uwEERsvd108; 				//	203 预留
	INT16U	uwEERsvd109; 				//	204 预留
	INT16U	uwEERsvd110; 				//	205 预留
	INT16U	uwEERsvd111; 				//	206 预留
	INT16U	uwEERsvd112; 				//	207 预留
	INT16U	uwEERsvd113; 				//	208 预留
	INT16U	uwEERsvd114; 				//	209 预留
	INT16U	uwEERsvd115; 				//	210 预留
	INT16U	uwEERsvd116; 				//	211 预留
	INT16U	uwEERsvd117; 				//	212 预留
	INT16U	uwEERsvd118; 				//	213 预留
	INT16U	uwEERsvd119; 				//	214 预留
	INT16U	uwEERsvd120; 				//	215 预留
	INT16U	uwEERsvd121; 				//	216 预留
	INT16U	uwEERsvd122; 				//	217 预留
	INT16U	uwEERsvd123; 				//	218 预留
	INT16U	uwEERsvd124; 				//	219 预留
	INT16U	uwEERsvd125; 				//	220 预留
	INT16U	uwEERsvd126; 				//	221 预留
	INT16U	uwEERsvd127; 				//	222 预留
	INT16U	uwEERsvd128; 				//	223 预留
}strBattDataSet;
#define cBattDataSetLength  ((sizeof(strBattDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwEEPV1StartVolt;			//	224	PV1启动电压
	INT16U	uwEEPV2StartVolt;			//	225	PV2启动电压
	INT16U	uwEEPV1CurrrLimit;			//	226	PV1最大输入电流
	INT16U	uwEEPV2CurrrLimit;			//	227	PV2最大输入电流
	INT16U	uwEEPV1PowerLimit;			//	228	PV1最大输入功率
	INT16U	uwEEPV2PowerLimit;			//	229	PV2最大输入功率
	INT16U	uwEEMpptMultiPoint;			//	230	多峰扫描
	INT16U	uwEEPVInputMode;			//	231	PV输入模式
	INT16U	uwEERsvd137; 				//	232 预留
	INT16U	uwEERsvd138; 				//	233 预留
	INT16U	uwEERsvd139; 				//	234 预留
	INT16U	uwEERsvd140; 				//	235 预留
	INT16U	uwEERsvd141; 				//	236 预留
	INT16U	uwEERsvd142; 				//	237 预留
	INT16U	uwEERsvd143; 				//	238 预留
	INT16U	uwEERsvd144; 				//	239 预留
}strPVDataSet;
#define cPVDataSetLength  ((sizeof(strPVDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwEEGridInputRange;			//	240	电网输入范围
	INT16U	uwEEACOutputRatedPower;		//	241	机器额定功率
	INT16U	uwEEACOutputRatedVolt;		//	242	额定输出电压
	INT16U	uwEEACOutputRatedFreq;		//	243	额定输出频率
	INT16U	uwAutoInvEn;				//	244	开机自动逆变
	INT16U	uwDCDCOpenEn; 				//	245	DCDC开环使能
	INT16U	uwEERsvd151; 				//	246 预留
	INT16U	uwEERsvd152; 				//	247 预留
	INT16U	uwEEOverTempRestartEn;		//	248	过温重启使能
	INT16U	uwEEOverLoadRestartEn;		//	249	过载重启使能
	INT16U	uwEEOverLoadBypassEn;		//	250	过载转旁路使能
	INT16U	uwEERsvd156; 				//	251 预留
	INT16U	uwEERsvd157; 				//	252 预留
	INT16U	uwEERsvd158; 				//	253 预留
	INT16U	uwEEOnGridAlwayOn; 			//	254 市电常开（闭合）
	INT16U	uwEEOffGridImmediatelyOff; 	//	255 离网常断（断开）
	INT16U	uwEEPVPowerRlyOn; 			//	256 开启功率（PV）
	INT16U	uwEERlySocOn; 				//	257 锂电池模式下用SOC
	INT16U	uwEERlySocOff; 				//	258 锂电池模式下用SOC
	INT16U	uwEERlyVoltOn; 				//	259 自定义模式下用电压
	INT16U	uwEERlyVoltOff; 			//	260 自定义模式下用电压
	INT16U	uwEEOffGridWaitTime;		//	261	并网转离网等待时间
	INT16U	uwEEOnGridWaitTime;			//	262	离网转并网等待时间
	INT16U	uwEEIslandCheckEn;			//	263	主动孤岛检测使能
	INT16U	uwEERsvd169; 				//	264 预留
	INT16U	uwEEGridFeedEn;				//	265	馈电使能
	INT16U	uwEEGridMaxInputPowerLimitEn;//	266	电网最大输入功率限制使能
	INT16U	uwEEGridCurrLimit;			//	267	市电电流限制
	INT16U	uwEEGridInputPower;			//	268	市电最大买电功率
	INT16U	uwEEGridFeedPower;			//	269	市电最大卖电功率
	INT16U	uwEEGridVoltUpperLimit;		//	270	电网电压上限
	INT16U	uwEEGridVoltLowerLimit;		//	271	电网电压下限
	INT16U	uwEERsvd177; 				//	272 预留
	INT16U	uwEERsvd178; 				//	273 预留
	INT16U	uwEEZeroExportPower;		//	274 零馈电功率
	INT16U	uwEEGridPeakShaving;		//	275 电网削峰使能
	INT16U	uwEEGridPeakShavingPower;	//	276 电网削峰功率
	INT16U	uwEETurboMode;				//	277	Turbo模式使能
	INT16U	uwEETouMode;				//	278	Tou模式使能
	INT16U	uwEECloseGSRlyEn;			//	279	N对地继电器闭合使能
	INT16U	uwEEGridpowerslope;			//	280	并网功率斜率
	INT16U	uwEEGridpowerlimitation;	//	281	并网功率限制
	INT16U	uwPvAutoInvEn;				//	282	单PV无电池开机自动逆变使能,如果有电池此项不生效
	
	INT16U	uwEERsvd188; 				//	283 预留
	INT16U	uwEERsvd189; 				//	284 预留
	INT16U	uwEERsvd190; 				//	285 预留
	INT16U	uwEERsvd191; 				//	286 预留
	INT16U	uwEERsvd192; 				//	287 预留
	INT16U	uwEERsvd193; 				//	288 预留
	INT16U	uwEERsvd194; 				//	289 预留
	INT16U	uwEERsvd195; 				//	290 预留
	INT16U	uwEERsvd196; 				//	291 预留
	INT16U	uwEERsvd197; 				//	292 预留
	INT16U	uwEERsvd198; 				//	293 预留
	INT16U	uwEERsvd199; 				//	294 预留
	INT16U	uwEERsvd200; 				//	295 预留
	INT16U	uwEERsvd201; 				//	296 预留
	INT16U	uwEERsvd202; 				//	297 预留
	INT16U	uwEERsvd203; 				//	298 预留
	INT16U	uwEERsvd204; 				//	299 预留
	INT16U	uwEERsvd205; 				//	300 预留
	INT16U	uwEERsvd206; 				//	301 预留
	INT16U	uwEERsvd207; 				//	302 预留
	INT16U	uwEERsvd208; 				//	303 预留
	INT16U	uwEERsvd209; 				//	304 预留
	INT16U	uwEERsvd210; 				//	305 预留
	INT16U	uwEERsvd211; 				//	306 预留
	INT16U	uwEERsvd212; 				//	307 预留
	INT16U	uwEERsvd213; 				//	308 预留
	INT16U	uwEERsvd214; 				//	309 预留
	INT16U	uwEERsvd215; 				//	310 预留
	INT16U	uwEERsvd216; 				//	311 预留
	INT16U	uwEERsvd217; 				//	312 预留
	INT16U	uwEERsvd218; 				//	313 预留
	INT16U	uwEERsvd219; 				//	314 预留
	INT16U	uwEERsvd220; 				//	315 预留
	INT16U	uwEERsvd221; 				//	316 预留
	INT16U	uwEERsvd222; 				//	317 预留
	INT16U	uwEERsvd223; 				//	318 预留
	INT16U	uwEERsvd224; 				//	319 预留

	INT16U	eSetGenMode; 				//	320 油机模式
	INT16U	eSetGenInputEn; 			//	321 油机输入使能
	INT16U	eSetGenInputMaxPower; 		//	322 油机输入最大功率
	INT16U	eSetGenConnectToGridPortEn; //	323 油机接入电网端口使能位
	INT16U	eSetSmartLoad_OpenPower; 	//	324 智能负载启动功率
	INT16U	eSetSmartLoad_StartBatVolt; //	325 智能负载闭合电池电压点
	INT16U	eSetSmartLoad_ExitBatVolt; 	//	326 智能负载断开电池电压点
	INT16U	eSetSmartLoad_StartSOC; 	//	327 智能负载闭合电池SOC点
	INT16U	eSetSmartLoad_ExitSOC; 		//	328 智能负载断开电池SOC点
	INT16U	eSetOnGrid_SmartLoadEn; 	//	329 电网正常启用智能负载使能位
	INT16U	eSetOffGrid_SmartLoadDis; 	//	330 电网异常禁用智能负载使能位
	INT16U	uwEEDry1ContactMode; 		//	331 干接点1模式
	INT16U	uwEEDry2ContactMode; 		//	332 干接点2模式
}strAcDataSet;
#define cAcDataSetLength  ((sizeof(strAcDataSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwEERsvd238; 				//	333 预留
	INT16U	uwEERsvd239; 				//	334 预留
	INT16U	uwEERsvd240; 				//	335 预留
	INT16U	uwEERsvd241; 				//	336 预留
	INT16U	uwEERsvd242; 				//	337 预留
	INT16U	uwEERsvd243; 				//	338 预留
	INT16U	uwEERsvd244; 				//	339 预留
	INT16U	uwEERsvd245; 				//	340 预留
	INT16U	uwEERsvd246; 				//	341 预留
	INT16U	uwEERsvd247; 				//	342 预留
	INT16U	uwEERsvd248; 				//	343 预留
	INT16U	uwEERsvd249; 				//	344 预留
	INT16U	uwEERsvd250; 				//	345 预留
	INT16U	uwEERsvd251; 				//	346 预留
	INT16U	uwEERsvd252; 				//	347 预留
	INT16U	uwEERsvd253; 				//	348 预留
	INT16U	uwEERsvd254; 				//	349 预留
	INT16U	uwEERsvd255; 				//	350 预留
	INT16U	uwEERsvd256; 				//	351 预留
	INT16U	uwEERsvd257; 				//	352 预留
	INT16U	uwEERsvd258; 				//	353 预留
	INT16U	uwEERsvd259; 				//	354 预留
	INT16U	uwEERsvd260; 				//	355 预留
	INT16U	uwEERsvd261; 				//	356 预留
	INT16U	uwEERsvd262; 				//	357 预留
	INT16U	uwEERsvd263; 				//	358 预留
	INT16U	uwEERsvd264; 				//	359 预留
	INT16U	uwEERsvd265; 				//	360 预留
	INT16U	uwEERsvd266; 				//	361 预留
	INT16U	uwEERsvd267; 				//	362 预留
	INT16U	uwEERsvd268; 				//	363 预留
	INT16U	uwEERsvd269; 				//	364 预留
	INT16U	uwEERsvd270; 				//	365 预留
	INT16U	uwEERsvd271; 				//	366 预留
	INT16U	uwEERsvd272; 				//	367 预留
	INT16U	uwEERsvd273; 				//	368 预留
	INT16U	uwEERsvd274; 				//	369 预留
	INT16U	uwEERsvd275; 				//	370 预留
	INT16U	uwEERsvd276; 				//	371 预留
	INT16U	uwEERsvd277; 				//	372 预留
	INT16U	uwEERsvd278; 				//	373 预留
	INT16U	uwEERsvd279; 				//	374 预留
	INT16U	uwEERsvd280; 				//	375 预留
	INT16U	uwEERsvd281; 				//	376 预留
	INT16U	uwEERsvd282; 				//	377 预留
	INT16U	uwEERsvd283; 				//	378 预留
	INT16U	uwEERsvd284; 				//	379 预留
	INT16U	uwEERsvd285; 				//	380 预留
	INT16U	uwEERsvd286; 				//	381 预留
	INT16U	uwEERsvd287; 				//	382 预留
	INT16U	uwEERsvd288; 				//	383 预留
	INT16U	uwEERsvd289; 				//	384 预留
	INT16U	uwEERsvd290; 				//	385 预留
	INT16U	uwEERsvd291; 				//	386 预留
	INT16U	uwEERsvd292; 				//	387 预留
	INT16U	uwEERsvd293; 				//	388 预留
	INT16U	uwEERsvd294; 				//	389 预留
	INT16U	uwEERsvd295; 				//	390 预留
	INT16U	uwEERsvd296; 				//	391 预留
	INT16U	uwEERsvd297; 				//	392 预留
	INT16U	uwEERsvd298; 				//	393 预留
	INT16U	uwEERsvd299; 				//	394 预留
	INT16U	uwEERsvd300; 				//	395 预留
	INT16U	uwEERsvd301; 				//	396 预留
	INT16U	uwEERsvd302; 				//	397 预留
	INT16U	uwEERsvd303; 				//	398 预留
	INT16U	uwEERsvd304; 				//	399 预留
}strReserveSet;
#define cReserveSetLength  ((sizeof(strReserveSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwSetECO_TimeOfUse;			//	400 经济模式使能
	INT16U	uwSetECO_EffectiveWeek;		//	401 生效星期
	INT16U	uwSetECO1_GridChargeEnable;	//	402 规则1电网充电使能
	INT16U	uwSetECO1_GenChargeEnable;	//	403 规则1油机充电使能
	INT16U	uwSetECO1_StartTime; 		//	404 规则1起始时间
	INT16U	uwSetECO1_StopTime;			//	405 规则1结束时间
	INT16U	uwSetECO1_Volt;				//	406 规则1目标电压
	INT16U	uwSetECO1_SOC;				//	407 规则1目标SOC（BMS连接采用）
	INT16U	uwSetECO1_Power; 			//	408 规则1放电功率
	INT16U	uwSetECO1_WorkModeSet;		//	409 规则1工作模式设定
	INT16U	uwSetECO2_GridChargeEnable;	//	410 规则2电网充电使能
	INT16U	uwSetECO2_GenChargeEnable;	//	411 规则2油机充电使能
	INT16U	uwSetECO2_StartTime;		//	412 规则2起始时间
	INT16U	uwSetECO2_StopTime;			//	413 规则2结束时间
	INT16U	uwSetECO2_Volt;				//	414 规则2目标电压
	INT16U	uwSetECO2_SOC;				//	415 规则2目标SOC（BMS连接采用）
	INT16U	uwSetECO2_Power; 			//	416 规则2放电功率
	INT16U	uwSetECO2_WorkModeSet;		//	417 规则2工作模式设定
	INT16U	uwSetECO3_GridChargeEnable;	//	418 规则3电网充电使能
	INT16U	uwSetECO3_GenChargeEnable;	//	419 规则3油机充电使能
	INT16U	uwSetECO3_StartTime; 		//	420 规则3起始时间
	INT16U	uwSetECO3_StopTime;			//	421 规则3结束时间
	INT16U	uwSetECO3_Volt;				//	422 规则3目标电压
	INT16U	uwSetECO3_SOC;				//	423 规则3目标SOC（BMS连接采用）
	INT16U	uwSetECO3_Power; 			//	424 规则3放电功率
	INT16U	uwSetECO3_WorkModeSet;		//	425 规则3工作模式设定
	INT16U	uwSetECO4_GridChargeEnable;	//	426 规则4电网充电使能
	INT16U	uwSetECO4_GenChargeEnable;	//	427 规则4油机充电使能
	INT16U	uwSetECO4_StartTime; 		//	428 规则4起始时间
	INT16U	uwSetECO4_StopTime;			//	429 规则4结束时间
	INT16U	uwSetECO4_Volt;				//	430 规则4目标电压
	INT16U	uwSetECO4_SOC;				//	431 规则4目标SOC（BMS连接采用）
	INT16U	uwSetECO4_Power; 			//	432 规则4放电功率
	INT16U	uwSetECO4_WorkModeSet;		//	433 规则4工作模式设定
	INT16U	uwSetECO5_GridChargeEnable;	//	434 规则5电网充电使能
	INT16U	uwSetECO5_GenChargeEnable;	//	435 规则5油机充电使能
	INT16U	uwSetECO5_StartTime; 		//	436 规则5起始时间
	INT16U	uwSetECO5_StopTime;			//	437 规则5结束时间
	INT16U	uwSetECO5_Volt;				//	438 规则5目标电压
	INT16U	uwSetECO5_SOC;				//	439 规则5目标SOC（BMS连接采用）
	INT16U	uwSetECO5_Power; 			//	440 规则5放电功率
	INT16U	uwSetECO5_WorkModeSet;		//	441 规则5工作模式设定
	INT16U	uwSetECO6_GridChargeEnable;	//	442 规则6电网充电使能
	INT16U	uwSetECO6_GenChargeEnable;	//	443 规则6油机充电使能
	INT16U	uwSetECO6_StartTime; 		//	444 规则6起始时间
	INT16U	uwSetECO6_StopTime;			//	445 规则6结束时间
	INT16U	uwSetECO6_Volt;				//	446 规则6目标电压
	INT16U	uwSetECO6_SOC;				//	447 规则6目标SOC（BMS连接采用）
	INT16U	uwSetECO6_Power; 			//	448 规则6放电功率
	INT16U	uwSetECO6_WorkModeSet;		//	449 规则6工作模式设定
	INT16U	uwSetECO7_GridChargeEnable;	//	450 规则7电网充电使能
	INT16U	uwSetECO7_GenChargeEnable;	//	451 规则7油机充电使能
	INT16U	uwSetECO7_StartTime; 		//	452 规则7起始时间
	INT16U	uwSetECO7_StopTime;			//	453 规则7结束时间
	INT16U	uwSetECO7_Volt;				//	454 规则7目标电压
	INT16U	uwSetECO7_SOC;				//	455 规则7目标SOC（BMS连接采用）
	INT16U	uwSetECO7_Power; 			//	456 规则7放电功率
	INT16U	uwSetECO7_WorkModeSet;		//	457 规则7工作模式设定
	INT16U	uwSetECO8_GridChargeEnable;	//	458 规则8电网充电使能
	INT16U	uwSetECO8_GenChargeEnable;	//	459 规则8油机充电使能
	INT16U	uwSetECO8_StartTime; 		//	460 规则8起始时间
	INT16U	uwSetECO8_StopTime;			//	461 规则8结束时间
	INT16U	uwSetECO8_Volt;				//	462 规则8目标电压
	INT16U	uwSetECO8_SOC;				//	463 规则8目标SOC（BMS连接采用）
	INT16U	uwSetECO8_Power; 			//	464 规则8放电功率
	INT16U	uwSetECO8_WorkModeSet;		//	465 规则8工作模式设定
	INT16U	uwEERsvd371;				//	466 预留
	INT16U	uwEERsvd372;				//	467 预留
}strECOModeSet;
#define cECOModeSetLength  ((sizeof(strECOModeSet)/sizeof(INT16U))*2)

typedef struct
{
	INT16U	uwATE_UpdateFW;				//	468 升级固件
	INT16U	uwATE_SafetyCode; 			//	469 安规设置
	INT16U	uwATE_ISOsetting;			//	470 绝缘阻抗设置
	INT16U	uwATE_EleMeterProc;			//	471 电表协议选择
	INT16U	uwATE_ExCommBps;			//	472 Wifi通讯地址和波特率
	INT16U	uwATE_EleMeterBps_Parity; 	//	473 与电表通讯波特率和校验位
	INT16U	uwATE_EleMeterAddr;			//	474 与电表通讯地址
	INT16U	uwATE_EleMeterWREn;			//	475 电表使能写，禁止读
	INT16U	uwATE_EleMeterDataRegAddr;	//	476 电表Modbus地址
	INT16U	uwATE_EleMeterData;			//	477 电表数据
	INT16U	uwATE_485CommBps; 			//	478 485通讯地址和波特率
	INT16U	uwMenuRtnDftPageEn;			//	479 菜单回退默认界面使能位
	INT16U	uwSetLCDBacklight;			//	480 LCD背光
	INT16U	uwSetBuzzerBeep;			//	481 蜂鸣器
	INT16U	uwEERsvd387; 				//	482 预留
	INT16U	uwEERsvd388; 				//	483 预留
	INT16U	uwEERsvd389; 				//	484 预留
	INT16U	uwEERsvd390; 				//	485 预留
	INT16U	uwEERsvd391; 				//	486 预留
	INT16U	uwEERsvd392; 				//	487 预留
	INT16U	uwEERsvd393; 				//	488 预留
	INT16U	uwEERsvd394; 				//	489 预留
	INT16U	uwEERsvd395; 				//	490 预留
	INT16U	uwEERsvd396; 				//	491 预留
	INT16U	uwEERsvd397; 				//	492 预留
	INT16U	uwEERsvd398; 				//	493 预留
	INT16U	uwEERsvd399; 				//	494 预留
	INT16U	uwEERsvd400; 				//	495 预留
	INT16U	uwEERsvd401; 				//	496 预留
	INT16U	uwEERsvd402; 				//	497 预留
	INT16U	uwEERsvd403; 				//	498 预留
	INT16U	uwEERsvd404; 				//	499 预留
	INT16U	uwEERsvd405; 				//	500 预留
	INT16U	uwEERsvd406; 				//	501 预留
	INT16U	uwEERsvd407; 				//	502 预留
	INT16U	uwEERsvd408; 				//	503 预留
	INT16U	uwEERsvd409; 				//	504 预留
	INT16U	uwEERsvd410; 				//	505 预留
	INT16U	uwEERsvd411; 				//	506 预留
	INT16U	uwEERsvd412; 				//	507 预留
	INT16U	uwEERsvd413; 				//	508 预留
	INT16U	uwEERsvd414; 				//	509 预留
	INT16U	uwEERsvd415; 				//	510 预留
	INT16U	uwEERsvd416; 				//	511 预留
	INT16U	uwEERsvd417; 				//	512 预留
	INT16U	uwEERsvd418; 				//	513 预留
	INT16U	uwEERsvd419; 				//	514 预留
	INT16U	uwEERsvd420; 				//	515 预留
	INT16U	uwSetBmsBagAddr;			//	516 电池包地址
	INT16U	uwSetClearEventLog;			//	517 清除事件记录
	INT16U	uwSetEventLogFunc;			//	518 事件记录功能
	INT16U	uwSetFaultLogFunc;			//	519 故障记录功能
	INT16U	uwSetLogType; 				//	520 Log查询类型
	INT16U	uwSetLogIndex;				//	521 Log索引
	INT16U	uwEERsvd427; 				//	522 预留
	INT16U	uwEERsvd428; 				//	523 预留
	INT16U	uwEERsvd429; 				//	524 预留
	INT16U	uwEERsvd430; 				//	525 预留
	INT16U	uwEERsvd431; 				//	526 预留
	INT16U	uwEERsvd432; 				//	527 预留
	INT16U	uwEERsvd433; 				//	528 预留
	INT16U	uwEERsvd434; 				//	529 预留
	INT16U	uwEERsvd435; 				//	530 预留
	INT16U	uwEERsvd436; 				//	531 预留
	INT16U	uwFlag2;					//	532 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC2;				//	533 CRC校验
}strATESet;
#define cLineProtectSetLength  ((sizeof(strATESet)/sizeof(INT16U))*2)

struct EepromStruct2
{
	strControlStateSet strControlState;		//状态控制位设置
	strBattDataSet strBatData;				//电池参数设置
	strPVDataSet strPvData;					//PV参数设置
	strAcDataSet strAcData;					//AC参数设置
	strReserveSet strReserve;				//预留功能
	strECOModeSet strECOMode;				//经济模式设置
	strATESet strATESet;					//ATE设置
};

struct EepromStruct3
{
	INT16U	uwSetGrid1OVValue;		//	534 电网过压1段(%)
	INT16U	uwSetGrid1OVTime;		//	535 电网过压1段时间(10ms)，最大655350ms,也就是655s
	INT16U	uwSetGrid2OVValue;		//	536 电网过压2段(%)
	INT16U	uwSetGrid2OVTime;		//	537 电网过压2段时间(10ms)
	INT16U	uwSetGrid3OVValue;		//	538 电网过压3段(%)
	INT16U	uwSetGrid3OVTime;		//	539 电网过压3段时间(10ms)
	INT16U	uwSetGrid1UVValue;		//	540 电网欠压1段(%)
	INT16U	uwSetGrid1UVTime;		//	541 电网欠压1段时间(10ms)
	INT16U	uwSetGrid2UVValue;		//	542 电网欠压2段(%)
	INT16U	uwSetGrid2UVTime;		//	543 电网欠压2段时间(10ms)
	INT16U	uwSetGrid3UVValue;		//	544 电网欠压3段(%)
	INT16U	uwSetGrid3UVTime;		//	545 电网欠压3段时间(10ms)
	INT16U	uwSetGrid1OFValue;		//	546 电网过频1段(0.01Hz)
	INT16U	uwSetGrid1OFTime;		//	547 电网过频1段时间(10ms)
	INT16U	uwSetGrid2OFValue;		//	548 电网过频2段(0.01Hz)
	INT16U	uwSetGrid2OFTime;		//	549 电网过频2段时间(10ms)
	INT16U	uwSetGrid3OFValue;		//	550 电网过频3段(0.01Hz)
	INT16U	uwSetGrid3OFTime;		//	551 电网过频3段时间(10ms)
	INT16U	uwSetGrid1UFValue;		//	552 电网欠频1段(0.01Hz)
	INT16U	uwSetGrid1UFTime;		//	553 电网欠频1段时间(10ms)
	INT16U	uwSetGrid2UFValue;		//	554 电网欠频2段(0.01Hz)
	INT16U	uwSetGrid2UFTime;		//	555 电网欠频2段时间(10ms)
	INT16U	uwSetGrid3UFValue;		//	556 电网欠频3段(0.01Hz)
	INT16U	uwSetGrid3UFTime;		//	557 电网欠频3段时间(10ms)
	INT16U	uwSetRsvd558; 			//	558 预留
	INT16U	uwSetRsvd559;			//	559 预留
	INT16U	uwSetRsvd560;			//	560 预留
	INT16U	uwSetRsvd561;			//	561 预留
	INT16U	uwSetRsvd562;			//	562 预留
	INT16U	uwSetRsvd563;			//	563 预留
	INT16U	uwFlag3;				//	564 EEPROM标志,默认0xAAAA
	INT16U	uwEECheckCRC3;			//	565 CRC校验
};


#define		cEepromTotalLength1		(sizeof(struct	EepromStruct1)*2)	// 192bytes
#define		cEepromTotalLength2		(sizeof(struct	EepromStruct2)*2)	// 876bytes
#define		cEepromTotalLength3		(sizeof(struct	EepromStruct3)*2)	// 64bytes

#define		cEeprom1Address			0		
#define		cEeprom2Address			0x100		//Check  if cEepromTotalLength1 over 0x100
#define		cEeprom3Address			0x500		//Check  if cEepromTotalLength2 over 0x400
#define		cEeprom1BackupAddress	0x550		
#define		cEeprom2BackupAddress	0x650		//Check  if cEepromTotalLength1 over 0x100
#define		cEeprom3BackupAddress	0xA50		//Check  if cEepromTotalLength2 over 0x400
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

//EEPROM1
EEPROM INT16U suwGetEEMachineCode(void);
EEPROM INT16U suwGetEE_SN1(void);
EEPROM INT16U suwGetEE_SN2(void);
EEPROM INT16U suwGetEE_SN3(void);
EEPROM INT16U suwGetEE_SN4(void);
EEPROM INT16U suwGetEE_SN5(void);
EEPROM INT16U suwGetEE_SNLen(void);
EEPROM INT16U suwGetEE_DispHwVer(void);
EEPROM INT16U suwGetEE_CtrlHwVer(void);
EEPROM INT16U suwGetEE_PowerHwVer(void);
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
EEPROM INT16S suwGetEEGenVoltAdj(void);
EEPROM INT16S suwGetEEGenVoltBias(void);
EEPROM INT16S suwGetEEGenCurrAdj(void);
EEPROM INT16S suwGetEEGenCurrBias(void);
EEPROM INT16U suwGetSetRsvd5(void);
EEPROM INT16U suwGetSetRsvd6(void);
EEPROM INT16U suwGetSetRsvd7(void);
EEPROM INT16U suwGetSetRsvd8(void);
EEPROM INT16U suwGetSetRsvd9(void);
EEPROM INT16U suwGetSetRsvd10(void);
EEPROM INT16U suwGetSetRsvd11(void);
EEPROM INT16U suwGetSetRsvd12(void);
EEPROM INT16U suwGetSetRsvd13(void);
EEPROM INT16U suwGetSetRsvd14(void);
EEPROM INT16U suwGetSetRsvd15(void);
EEPROM INT16U suwGetSetRsvd16(void);
EEPROM INT16U suwGetSetRsvd17(void);
EEPROM INT16U suwGetSetRsvd18(void);
EEPROM INT16U suwGetSetRsvd19(void);
EEPROM INT16U suwGetSetRsvd20(void);
EEPROM INT16U suwGetSetRsvd21(void);
EEPROM INT16U suwGetSetRsvd22(void);
EEPROM INT16U suwGetSetRsvd23(void);
EEPROM INT16U suwGetSetRsvd24(void);
EEPROM INT16U suwGetSetRsvd25(void);
EEPROM INT16U suwGetSetRsvd26(void);
EEPROM INT16U suwGetSetRsvd27(void);
EEPROM INT16U suwGetSetRsvd28(void);
EEPROM INT16U suwGetSetRsvd29(void);
EEPROM INT16U suwGetSetRsvd30(void);
EEPROM INT16U suwGetSetRsvd31(void);
EEPROM INT16U suwGetSetRsvd32(void);
EEPROM INT16U suwGetSetRsvd33(void);
EEPROM INT16U suwGetSetRsvd34(void);
EEPROM INT16U suwGetSetRsvd35(void);
EEPROM INT16U suwGetSetRsvd36(void);
EEPROM INT16U suwGetSetRsvd37(void);
EEPROM INT16U suwGetSetRsvd38(void);
EEPROM INT16U suwGetSetRsvd39(void);
EEPROM INT16U suwGetSetRsvd40(void);
EEPROM INT16U suwGetSetRsvd41(void);
EEPROM INT16U suwGetSetRsvd42(void);
EEPROM INT16U suwGetSetRsvd43(void);
EEPROM INT16U suwGetSetRsvd44(void);
EEPROM INT16U suwGetSetRsvd45(void);
EEPROM INT16U suwGetSetRsvd46(void);
EEPROM INT16U suwGetSetRsvd47(void);
EEPROM INT16U suwGetSetRsvd48(void);
EEPROM INT16U suwGetSetRsvd49(void);
EEPROM INT16U suwGetSetRsvd50(void);
EEPROM INT16U suwGetSetRsvd51(void);
EEPROM INT16U suwGetSetRsvd52(void);
EEPROM INT16U suwGetEEFlag1(void);
EEPROM INT16U suwGetEECheckCRC1(void);

//EEPROM2
//strControlState
EEPROM	INT16U	suwGetEEParaEnable(void);
EEPROM	INT16U	suwGetEEMasterSlaver(void);
EEPROM	INT16U	suwGetEEParallelPhase(void);
EEPROM	INT16U	suwGetEEParallelIID(void);
EEPROM	INT16U	suwGetEESystemOutputMode(void);
EEPROM	INT16U	suwGetEEWorkMode(void);
EEPROM	INT16U	suwGetEEFanWorkMode(void);
EEPROM	INT16U	suwGetEEPowerConversion(void);
EEPROM	INT16U	suwGetEEPowerSaveMode(void);
EEPROM	INT16U	suwGetEENoBatMode(void);
EEPROM	INT16U	suwGetEELogoEnable(void);
EEPROM	INT16U	suwGetEEAdcBiasAdj(void);
EEPROM	INT16U	suwGetLeakCurrProtectEnable(void);
EEPROM	INT16U	suwGetLeakCurrProtectValue(void);
EEPROM	INT16U	suwGetISOCheckEnable(void);
EEPROM	INT16U	suwGetISOCheckValue(void);
EEPROM	INT16U	suwGetEERsvd17(void);
EEPROM	INT16U	suwGetEERsvd18(void);
EEPROM	INT16U	suwGetEERsvd19(void);
EEPROM	INT16U	suwGetEERsvd20(void);
EEPROM	INT16U	suwGetEERsvd21(void);
EEPROM	INT16U	suwGetEERsvd22(void);
EEPROM	INT16U	suwGetEERsvd23(void);
EEPROM	INT16U	suwGetEERsvd24(void);
EEPROM	INT16U	suwGetEERsvd25(void);
EEPROM	INT16U	suwGetEERsvd26(void);
EEPROM	INT16U	suwGetEERsvd27(void);
EEPROM	INT16U	suwGetEERsvd28(void);
EEPROM	INT16U	suwGetEERsvd29(void);
EEPROM	INT16U	suwGetEERsvd30(void);
EEPROM	INT16U	suwGetEERsvd31(void);
EEPROM	INT16U	suwGetEERsvd32(void);
//strBatData
EEPROM	INT16U	suwGetEEBatType(void);
EEPROM	INT16U	suwGetEEBatSeriesNum(void);
EEPROM	INT16U	suwGetEEBatActivateEnable(void);
EEPROM	INT16U	suwGetEEBatCapacity(void);
EEPROM	INT16U	suwGetEELithiumMode(void);
EEPROM	INT16U	suwGetEERsvd38(void);
EEPROM	INT16U	suwGetEEBatMaxChgCurr(void);
EEPROM	INT16U	suwGetEEBatMaxDcgCurr(void);
EEPROM	INT16U	suwGetEEBatVoltage(void);
EEPROM	INT16U	suwGetEERsvd42(void);
EEPROM	INT16U	suwGetEEGridChargeEn(void);
EEPROM	INT16U	suwGetEEGridChgBatCurr(void);
EEPROM	INT16U	suwGetEEOnGridBatAutoStartChgVolt(void);
EEPROM	INT16U	suwGetEEOnGridBatExitAutoChgVolt(void);
EEPROM	INT16U	suwGetEEOnGridBatAutoStartChgSOC(void);
EEPROM	INT16U	suwGetEEOnGridBatExitAutoChgSOC(void);
EEPROM	INT16U	suwGetEERsvd49(void);
EEPROM	INT16U	suwGetEEGenChargeEn(void);
EEPROM	INT16U	suwGetEEGenMaxChargeCurr(void);
EEPROM	INT16U	suwGetEEGenStartChargeVolt(void);
EEPROM	INT16U	suwGetEEGenEndChargeVolt(void);
EEPROM	INT16U	suwGetEEGenStartChargeSOC(void);
EEPROM	INT16U	suwGetEEGenEndChargeSOC(void);
EEPROM	INT16U	suwGetEERsvd56(void);
EEPROM	INT16U	suwGetEEBatFloatTime(void);
EEPROM	INT16U 	suwGetEEBatLowShutDownSOC(void);
EEPROM	INT16U	suwGetEEBatACRestartSOC(void);
EEPROM	INT16U	suwGetEEBatLowAlarmSOC(void);
EEPROM	INT16U	suwGetEEBatConstVolt(void);
EEPROM	INT16U	suwGetEEBatFloatVolt(void);
EEPROM	INT16U	suwGetEEBatLowShutDownVolt(void);
EEPROM	INT16U	suwGetEEBatACRestartVolt(void);
EEPROM	INT16U	suwGetEEBatLowAlarmVolt(void);
EEPROM	INT16U	suwGetEEBatVoltOverShut(void);
EEPROM	INT16U	suwGetEEBatEqVolt(void);
EEPROM	INT16U	suwGetEERsvd66(void);
EEPROM	INT16U	suwGetEERsvd67(void);
EEPROM	INT16U	suwGetEEBattResistance(void);
EEPROM	INT16U	suwGetEEBMSComErrEnable(void);
EEPROM	INT16U	suwGetEEBatParaEnable(void);
EEPROM	INT16U	suwGetEEBatTempCompensateEnable(void);
EEPROM	INT16U	suwGetBatTempCalibration(void);
EEPROM	INT16U	suwGetEERsvd74(void);
EEPROM	INT16U	suwGetEERsvd75(void);
EEPROM	INT16U	suwGetEEBatEqEn(void);
EEPROM	INT16U	suwGetEEBatEqTime(void);
EEPROM	INT16U	suwGetEEBatEqTimeout(void);
EEPROM	INT16U	suwGetEEBatEqInterval(void);
EEPROM	INT16U	suwGetEEBatEqActImd(void);
EEPROM	INT16U	suwGetEERsvd82(void);
EEPROM	INT16U	suwGetEERsvd83(void);
EEPROM	INT16U	suwGetEEBatLowVoltDerateEnable(void);
EEPROM	INT16U	suwGetEEBatPowerOutEn(void);
EEPROM	INT16U	suwGetEEBMSErrStopEn(void);
EEPROM	INT16U	suwGetEESOCDisplayEn(void);
EEPROM	INT16U	suwGetEERsvd88(void);
EEPROM	INT16U	suwGetEERsvd89(void);
EEPROM	INT16U	suwGetEERsvd90(void);
EEPROM	INT16U	suwGetEERsvd91(void);
EEPROM	INT16U	suwGetEERsvd92(void);
EEPROM	INT16U	suwGetEERsvd93(void);
EEPROM	INT16U	suwGetEERsvd94(void);
EEPROM	INT16U	suwGetEERsvd95(void);
EEPROM	INT16U	suwGetEERsvd96(void);
EEPROM	INT16U	suwGetEEBattAhReal(void);
EEPROM	INT16U	suwGetEEBattAhMax(void);
EEPROM	INT16U	suwGetEEBattFullCnt(void);
EEPROM	INT16U	suwGetEEBattEmptyCnt(void);
EEPROM	INT16U	suwGetEEBattCycCnt(void);
EEPROM	INT16U	suwGetEEBattAhRealShow(void);
EEPROM	INT16U	suwGetEESOCSmoothEn(void);
EEPROM	INT16U	suwGetEERsvd104(void);
EEPROM	INT16U	suwGetEERsvd105(void);
EEPROM	INT16U	suwGetEERsvd106(void);
EEPROM	INT16U	suwGetEERsvd107(void);
EEPROM	INT16U	suwGetEERsvd108(void);
EEPROM	INT16U	suwGetEERsvd109(void);
EEPROM	INT16U	suwGetEERsvd110(void);
EEPROM	INT16U	suwGetEERsvd111(void);
EEPROM	INT16U	suwGetEERsvd112(void);
EEPROM	INT16U	suwGetEERsvd113(void);
EEPROM	INT16U	suwGetEERsvd114(void);
EEPROM	INT16U	suwGetEERsvd115(void);
EEPROM	INT16U	suwGetEERsvd116(void);
EEPROM	INT16U	suwGetEERsvd117(void);
EEPROM	INT16U	suwGetEERsvd118(void);
EEPROM	INT16U	suwGetEERsvd119(void);
EEPROM	INT16U	suwGetEERsvd120(void);
EEPROM	INT16U	suwGetEERsvd121(void);
EEPROM	INT16U	suwGetEERsvd122(void);
EEPROM	INT16U	suwGetEERsvd123(void);
EEPROM	INT16U	suwGetEERsvd124(void);
EEPROM	INT16U	suwGetEERsvd125(void);
EEPROM	INT16U	suwGetEERsvd126(void);
EEPROM	INT16U	suwGetEERsvd127(void);
EEPROM	INT16U	suwGetEERsvd128(void);
//strPvData
EEPROM	INT16U	suwGetEEPV1StartVolt(void);
EEPROM	INT16U	suwGetEEPV1PowerLimit(void);
EEPROM	INT16U	suwGetEEPV2StartVolt(void);
EEPROM	INT16U	suwGetEEPV1CurrrLimit(void);
EEPROM	INT16U	suwGetEEPV2CurrrLimit(void);
EEPROM	INT16U	suwGetEEPV2PowerLimit(void);
EEPROM	INT16U	suwGetEEMpptMultiPoint(void);
EEPROM	INT16U	suwGetEEPVInputMode(void);
EEPROM	INT16U	suwGetEERsvd137(void);
EEPROM	INT16U	suwGetEERsvd138(void);
EEPROM	INT16U	suwGetEERsvd139(void);
EEPROM	INT16U	suwGetEERsvd140(void);
EEPROM	INT16U	suwGetEERsvd141(void);
EEPROM	INT16U	suwGetEERsvd142(void);
EEPROM	INT16U	suwGetEERsvd143(void);
EEPROM	INT16U	suwGetEERsvd144(void);
//strAcData
EEPROM	INT16U	suwGetEEGridInputRange(void);
EEPROM	INT16U	suwGetEEACOutputRatedFreq(void);
EEPROM	INT16U	suwGetEEACOutputRatedPower(void);
EEPROM	INT16U	suwGetEEACOutputRatedVolt(void);
EEPROM	INT16U	suwGetEEGridCurrLimit(void);
EEPROM	INT16U	suwGetEEGridInputPower(void);
EEPROM	INT16U	suwGetEEMaxFeedPower(void);
EEPROM	INT16U	suwGetEEGridVoltUpperLimit(void);
EEPROM	INT16U	suwGetEEGridVoltLowerLimit(void);
EEPROM	INT16U	suwGetEEAutoInvEnable(void);
EEPROM	INT16U	suwGetEEDCDCOpenLoopEnable(void);
EEPROM	INT16U	suwGetEERsvd151(void);
EEPROM	INT16U	suwGetEERsvd152(void);
EEPROM	INT16U	suwGetEEOverTempRestartEn(void);
EEPROM	INT16U	suwGetEEOverLoadRestartEn(void);
EEPROM	INT16U	suwGetEEOverLoadBypassEn(void);
EEPROM	INT16U	suwGetEERsvd156(void);
EEPROM	INT16U	suwGetEERsvd157(void);
EEPROM	INT16U	suwGetEERsvd158(void);
EEPROM	INT16U	suwGetEEOnGridAlwayOn(void);
EEPROM	INT16U	suwGetEEOffGridImmediatelyOff(void);
EEPROM	INT16U	suwGetEEPVPowerRlyOn(void);
EEPROM	INT16U	suwGetEERlySocOn(void);
EEPROM	INT16U	suwGetEERlySocOff(void);
EEPROM	INT16U	suwGetEERlyVoltOn(void);
EEPROM	INT16U	suwGetEERlyVoltOff(void);
EEPROM	INT16U	suwGetEEOffGridWaitTime(void);
EEPROM	INT16U	suwGetEEOnGridWaitTime(void);
EEPROM	INT16U	suwGetEEAnti_IslandProtectEnable(void);
EEPROM	INT16U	suwGetEERsvd169(void);
EEPROM	INT16U	suwGetEEFeedEnable(void);
EEPROM	INT16U	suwGetEEGridMaxInputPowerLimitEn(void);
EEPROM	INT16U	suwGetEERsvd177(void);
EEPROM	INT16U	suwGetEERsvd178(void);
EEPROM	INT16U	suwGetEEZeroExportPower(void);
EEPROM	INT16U	suwGetEEGridPeakShavingEnable(void);
EEPROM	INT16U	suwGetEEGridPeakShavingPower(void);
EEPROM	INT16U	suwGetEETurboMode(void);
EEPROM	INT16U	suwGetEETouMode(void);
EEPROM	INT16U	suwGetEECloseGSRlyEn(void);
EEPROM	INT16U	suwGetEEGridpowerslope(void);
EEPROM	INT16U	suwGetEEGridpowerlimitation(void);
EEPROM	INT16U	suwGetEEPVAutoInvEnable(void);
EEPROM	INT16U	suwGetEERsvd188(void);
EEPROM	INT16U	suwGetEERsvd189(void);
EEPROM	INT16U	suwGetEERsvd190(void);
EEPROM	INT16U	suwGetEERsvd191(void);
EEPROM	INT16U	suwGetEERsvd192(void);
EEPROM	INT16U	suwGetEERsvd193(void);
EEPROM	INT16U	suwGetEERsvd194(void);
EEPROM	INT16U	suwGetEERsvd195(void);
EEPROM	INT16U	suwGetEERsvd196(void);
EEPROM	INT16U	suwGetEERsvd197(void);
EEPROM	INT16U	suwGetEERsvd198(void);
EEPROM	INT16U	suwGetEERsvd199(void);
EEPROM	INT16U	suwGetEERsvd200(void);
EEPROM	INT16U	suwGetEERsvd201(void);
EEPROM	INT16U	suwGetEERsvd202(void);
EEPROM	INT16U	suwGetEERsvd203(void);
EEPROM	INT16U	suwGetEERsvd204(void);
EEPROM	INT16U	suwGetEERsvd205(void);
EEPROM	INT16U	suwGetEERsvd206(void);
EEPROM	INT16U	suwGetEERsvd207(void);
EEPROM	INT16U	suwGetEERsvd208(void);
EEPROM	INT16U	suwGetEERsvd209(void);
EEPROM	INT16U	suwGetEERsvd210(void);
EEPROM	INT16U	suwGetEERsvd211(void);
EEPROM	INT16U	suwGetEERsvd212(void);
EEPROM	INT16U	suwGetEERsvd213(void);
EEPROM	INT16U	suwGetEERsvd214(void);
EEPROM	INT16U	suwGetEERsvd215(void);
EEPROM	INT16U	suwGetEERsvd216(void);
EEPROM	INT16U	suwGetEERsvd217(void);
EEPROM	INT16U	suwGetEERsvd218(void);
EEPROM	INT16U	suwGetEERsvd219(void);
EEPROM	INT16U	suwGetEERsvd220(void);
EEPROM	INT16U	suwGetEERsvd221(void);
EEPROM	INT16U	suwGetEERsvd222(void);
EEPROM	INT16U	suwGetEERsvd223(void);
EEPROM	INT16U	suwGetEERsvd224(void);
EEPROM	INT16U	suwGetGenMode(void);
EEPROM	INT16U	suwGetGenInputEn(void);
EEPROM	INT16U	suwGetGenInputMaxPower(void);
EEPROM	INT16U	suwGetGenConnectToGridPortEn(void);
EEPROM	INT16U	suwGetSmartLoad_OpenPower(void);
EEPROM	INT16U	suwGetSmartLoad_StartBatVolt(void);
EEPROM	INT16U	suwGetSmartLoad_ExitBatVolt(void);
EEPROM	INT16U	suwGetSmartLoad_StartSOC(void);
EEPROM	INT16U	suwGetSmartLoad_ExitSOC(void);
EEPROM	INT16U	suwGetOnGrid_SmartLoadEn(void);
EEPROM	INT16U	suwGetOffGrid_SmartLoadDis(void);
EEPROM	INT16U	suwGetEEDry1ContactMode(void);
EEPROM	INT16U	suwGetEEDry2ContactMode(void);
//strReserve
EEPROM	INT16U	suwGetEERsvd238(void);
EEPROM	INT16U	suwGetEERsvd239(void);
EEPROM	INT16U	suwGetEERsvd240(void);
EEPROM	INT16U	suwGetEERsvd241(void);
EEPROM	INT16U	suwGetEERsvd242(void);
EEPROM	INT16U	suwGetEERsvd243(void);
EEPROM	INT16U	suwGetEERsvd244(void);
EEPROM	INT16U	suwGetEERsvd245(void);
EEPROM	INT16U	suwGetEERsvd246(void);
EEPROM	INT16U	suwGetEERsvd247(void);
EEPROM	INT16U	suwGetEERsvd248(void);
EEPROM	INT16U	suwGetEERsvd249(void);
EEPROM	INT16U	suwGetEERsvd250(void);
EEPROM	INT16U	suwGetEERsvd251(void);
EEPROM	INT16U	suwGetEERsvd252(void);
EEPROM	INT16U	suwGetEERsvd253(void);
EEPROM	INT16U	suwGetEERsvd254(void);
EEPROM	INT16U	suwGetEERsvd255(void);
EEPROM	INT16U	suwGetEERsvd256(void);
EEPROM	INT16U	suwGetEERsvd257(void);
EEPROM	INT16U	suwGetEERsvd258(void);
EEPROM	INT16U	suwGetEERsvd259(void);
EEPROM	INT16U	suwGetEERsvd260(void);
EEPROM	INT16U	suwGetEERsvd261(void);
EEPROM	INT16U	suwGetEERsvd262(void);
EEPROM	INT16U	suwGetEERsvd263(void);
EEPROM	INT16U	suwGetEERsvd264(void);
EEPROM	INT16U	suwGetEERsvd265(void);
EEPROM	INT16U	suwGetEERsvd266(void);
EEPROM	INT16U	suwGetEERsvd267(void);
EEPROM	INT16U	suwGetEERsvd268(void);
EEPROM	INT16U	suwGetEERsvd269(void);
EEPROM	INT16U	suwGetEERsvd270(void);
EEPROM	INT16U	suwGetEERsvd271(void);
EEPROM	INT16U	suwGetEERsvd272(void);
EEPROM	INT16U	suwGetEERsvd273(void);
EEPROM	INT16U	suwGetEERsvd274(void);
EEPROM	INT16U	suwGetEERsvd275(void);
EEPROM	INT16U	suwGetEERsvd276(void);
EEPROM	INT16U	suwGetEERsvd277(void);
EEPROM	INT16U	suwGetEERsvd278(void);
EEPROM	INT16U	suwGetEERsvd279(void);
EEPROM	INT16U	suwGetEERsvd280(void);
EEPROM	INT16U	suwGetEERsvd281(void);
EEPROM	INT16U	suwGetEERsvd282(void);
EEPROM	INT16U	suwGetEERsvd283(void);
EEPROM	INT16U	suwGetEERsvd284(void);
EEPROM	INT16U	suwGetEERsvd285(void);
EEPROM	INT16U	suwGetEERsvd286(void);
EEPROM	INT16U	suwGetEERsvd287(void);
EEPROM	INT16U	suwGetEERsvd288(void);
EEPROM	INT16U	suwGetEERsvd289(void);
EEPROM	INT16U	suwGetEERsvd290(void);
EEPROM	INT16U	suwGetEERsvd291(void);
EEPROM	INT16U	suwGetEERsvd292(void);
EEPROM	INT16U	suwGetEERsvd293(void);
EEPROM	INT16U	suwGetEERsvd294(void);
EEPROM	INT16U	suwGetEERsvd295(void);
EEPROM	INT16U	suwGetEERsvd296(void);
EEPROM	INT16U	suwGetEERsvd297(void);
EEPROM	INT16U	suwGetEERsvd298(void);
EEPROM	INT16U	suwGetEERsvd299(void);
EEPROM	INT16U	suwGetEERsvd300(void);
EEPROM	INT16U	suwGetEERsvd301(void);
EEPROM	INT16U	suwGetEERsvd302(void);
EEPROM	INT16U	suwGetEERsvd303(void);
EEPROM	INT16U	suwGetEERsvd304(void);
//strECOMode
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
EEPROM INT16U suwGetEEECO7_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO7_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO7_StartTime(void);
EEPROM INT16U suwGetEEECO7_StopTime(void);
EEPROM INT16U suwGetEEECO7_Volt(void);
EEPROM INT16U suwGetEEECO7_SOC(void);
EEPROM INT16U suwGetEEECO7_Power(void);
EEPROM INT16U suwGetEEECO7_WorkModeSet(void);
EEPROM INT16U suwGetEEECO8_GridChargeEnable(void);
EEPROM INT16U suwGetEEECO8_GenChargeEnable(void);
EEPROM INT16U suwGetEEECO8_StartTime(void);
EEPROM INT16U suwGetEEECO8_StopTime(void);
EEPROM INT16U suwGetEEECO8_Volt(void);
EEPROM INT16U suwGetEEECO8_SOC(void);
EEPROM INT16U suwGetEEECO8_Power(void);
EEPROM INT16U suwGetEEECO8_WorkModeSet(void);
EEPROM INT16U suwGetEERsvd371(void);
EEPROM INT16U suwGetEERsvd372(void); 
//strATESet
EEPROM INT16U suwGetEEATE_UpdateFW(void);
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
EEPROM INT16U suwGetEERsvd387(void);
EEPROM INT16U suwGetEERsvd388(void);
EEPROM INT16U suwGetEERsvd389(void);
EEPROM INT16U suwGetEERsvd390(void);
EEPROM INT16U suwGetEERsvd391(void);
EEPROM INT16U suwGetEERsvd392(void);
EEPROM INT16U suwGetEERsvd393(void);
EEPROM INT16U suwGetEERsvd394(void);
EEPROM INT16U suwGetEERsvd395(void);
EEPROM INT16U suwGetEERsvd396(void);
EEPROM INT16U suwGetEERsvd397(void);
EEPROM INT16U suwGetEERsvd398(void);
EEPROM INT16U suwGetEERsvd399(void);
EEPROM INT16U suwGetEERsvd400(void);
EEPROM INT16U suwGetEERsvd401(void);
EEPROM INT16U suwGetEERsvd402(void);
EEPROM INT16U suwGetEERsvd403(void);
EEPROM INT16U suwGetEERsvd404(void);
EEPROM INT16U suwGetEERsvd405(void);
EEPROM INT16U suwGetEERsvd406(void);
EEPROM INT16U suwGetEERsvd407(void);
EEPROM INT16U suwGetEERsvd408(void);
EEPROM INT16U suwGetEERsvd409(void);
EEPROM INT16U suwGetEERsvd410(void);
EEPROM INT16U suwGetEERsvd411(void);
EEPROM INT16U suwGetEERsvd412(void);
EEPROM INT16U suwGetEERsvd413(void);
EEPROM INT16U suwGetEERsvd414(void);
EEPROM INT16U suwGetEERsvd415(void);
EEPROM INT16U suwGetEERsvd416(void);
EEPROM INT16U suwGetEERsvd417(void);
EEPROM INT16U suwGetEERsvd418(void);
EEPROM INT16U suwGetEERsvd419(void);
EEPROM INT16U suwGetEERsvd420(void);
EEPROM INT16U suwGetEEBmsBagAddr(void);
EEPROM INT16U suwGetEEClearEventLog(void);
EEPROM INT16U suwGetEEEventLogFunc(void);
EEPROM INT16U suwGetEEFaultLogFunc(void);
EEPROM INT16U suwGetEELogType(void);
EEPROM INT16U suwGetEELogIndex(void);
EEPROM INT16U suwGetEERsvd427(void);
EEPROM INT16U suwGetEERsvd428(void);
EEPROM INT16U suwGetEERsvd429(void);
EEPROM INT16U suwGetEERsvd430(void);
EEPROM INT16U suwGetEERsvd431(void);
EEPROM INT16U suwGetEERsvd432(void);
EEPROM INT16U suwGetEERsvd433(void);
EEPROM INT16U suwGetEERsvd434(void);
EEPROM INT16U suwGetEERsvd435(void);
EEPROM INT16U suwGetEERsvd436(void);
EEPROM INT16U suwGetEEFlag2(void);
EEPROM INT16U suwGetEECheckCRC2(void);

//EEPROM3
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
EEPROM INT16U suwGetSetRsvd558(void);
EEPROM INT16U suwGetSetRsvd559(void);
EEPROM INT16U suwGetSetRsvd560(void);
EEPROM INT16U suwGetSetRsvd561(void);
EEPROM INT16U suwGetSetRsvd562(void);
EEPROM INT16U suwGetSetRsvd563(void);
EEPROM INT16U suwGetEEFlag3(void);
EEPROM INT16U suwGetEECheckCRC3(void);


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
EEPROM	void	sSetEepromRwEnable(INT8U bStatus);
EEPROM	void	sSetEepromRwBusy(INT8U bStatus);
EEPROM	void	sSetEepromSecureLock(INT8U bStatus);
EEPROM	void	sSetEeprom1Mode(INT8U bMode);
EEPROM	void	sSetEeprom2Mode(INT8U bMode);
EEPROM	void	sSetEeprom3Mode(INT8U bMode);

//EEPROM1
EEPROM	void	sSetEEMachineCode(INT16U uwtemp);
EEPROM	void	sSetEE_SN1(INT16U uwtemp);
EEPROM	void	sSetEE_SN2(INT16U uwtemp);
EEPROM	void	sSetEE_SN3(INT16U uwtemp);
EEPROM	void	sSetEE_SN4(INT16U uwtemp);
EEPROM	void	sSetEE_SN5(INT16U uwtemp);
EEPROM	void	sSetEE_SNLen(INT16U uwtemp);
EEPROM	void	sSetEE_DispHwVer(INT16U uwtemp);
EEPROM	void	sSetEE_CtrlHwVer(INT16U uwtemp);
EEPROM	void	sSetEE_PowerHwVer(INT16U uwtemp);
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
EEPROM	void	sSetEEGenVoltAdj(INT16S uwtemp);
EEPROM	void	sSetEEGenVoltBias(INT16S uwtemp);
EEPROM	void	sSetEEGenCurrAdj(INT16S uwtemp);
EEPROM	void	sSetEEGenCurrBias(INT16S uwtemp);
EEPROM	void	sSetSetRsvd5(INT16U uwtemp);
EEPROM	void	sSetSetRsvd6(INT16U uwtemp);
EEPROM	void	sSetSetRsvd7(INT16U uwtemp);
EEPROM	void	sSetSetRsvd8(INT16U uwtemp);
EEPROM	void	sSetSetRsvd9(INT16U uwtemp);
EEPROM	void	sSetSetRsvd10(INT16U uwtemp);
EEPROM	void	sSetSetRsvd11(INT16U uwtemp);
EEPROM	void	sSetSetRsvd12(INT16U uwtemp);
EEPROM	void	sSetSetRsvd13(INT16U uwtemp);
EEPROM	void	sSetSetRsvd14(INT16U uwtemp);
EEPROM	void	sSetSetRsvd15(INT16U uwtemp);
EEPROM	void	sSetSetRsvd16(INT16U uwtemp);
EEPROM	void	sSetSetRsvd17(INT16U uwtemp);
EEPROM	void	sSetSetRsvd18(INT16U uwtemp);
EEPROM	void	sSetSetRsvd19(INT16U uwtemp);
EEPROM	void	sSetSetRsvd20(INT16U uwtemp);
EEPROM	void	sSetSetRsvd21(INT16U uwtemp);
EEPROM	void	sSetSetRsvd22(INT16U uwtemp);
EEPROM	void	sSetSetRsvd23(INT16U uwtemp);
EEPROM	void	sSetSetRsvd24(INT16U uwtemp);
EEPROM	void	sSetSetRsvd25(INT16U uwtemp);
EEPROM	void	sSetSetRsvd26(INT16U uwtemp);
EEPROM	void	sSetSetRsvd27(INT16U uwtemp);
EEPROM	void	sSetSetRsvd28(INT16U uwtemp);
EEPROM	void	sSetSetRsvd29(INT16U uwtemp);
EEPROM	void	sSetSetRsvd30(INT16U uwtemp);
EEPROM	void	sSetSetRsvd31(INT16U uwtemp);
EEPROM	void	sSetSetRsvd32(INT16U uwtemp);
EEPROM	void	sSetSetRsvd33(INT16U uwtemp);
EEPROM	void	sSetSetRsvd34(INT16U uwtemp);
EEPROM	void	sSetSetRsvd35(INT16U uwtemp);
EEPROM	void	sSetSetRsvd36(INT16U uwtemp);
EEPROM	void	sSetSetRsvd37(INT16U uwtemp);
EEPROM	void	sSetSetRsvd38(INT16U uwtemp);
EEPROM	void	sSetSetRsvd39(INT16U uwtemp);
EEPROM	void	sSetSetRsvd40(INT16U uwtemp);
EEPROM	void	sSetSetRsvd41(INT16U uwtemp);
EEPROM	void	sSetSetRsvd42(INT16U uwtemp);
EEPROM	void	sSetSetRsvd43(INT16U uwtemp);
EEPROM	void	sSetSetRsvd44(INT16U uwtemp);
EEPROM	void	sSetSetRsvd45(INT16U uwtemp);
EEPROM	void	sSetSetRsvd46(INT16U uwtemp);
EEPROM	void	sSetSetRsvd47(INT16U uwtemp);
EEPROM	void	sSetSetRsvd48(INT16U uwtemp);
EEPROM	void	sSetSetRsvd49(INT16U uwtemp);
EEPROM	void	sSetSetRsvd50(INT16U uwtemp);
EEPROM	void	sSetSetRsvd51(INT16U uwtemp);
EEPROM	void	sSetSetRsvd52(INT16U uwtemp);
EEPROM	void	sSetEEFlag1(INT16U uwtemp);		
EEPROM	void	sSetEECheckCRC1(INT16U uwtemp);

//EEPROM2
//strControlState
EEPROM	void	sSetEEParaEnable(INT16U uwtemp);
EEPROM	void	sSetEEMasterSlaver(INT16U uwtemp);
EEPROM	void	sSetEEParallelPhase(INT16U uwtemp);
EEPROM	void	sSetEEParallelIID(INT16U uwtemp);
EEPROM	void	sSetEESystemOutputMode(INT16U uwtemp);
EEPROM	void	sSetEEWorkMode(INT16U uwtemp);
EEPROM	void	sSetEEFanWorkMode(INT16U uwtemp);
EEPROM	void	sSetEEPowerConversion(INT16U uwtemp);
EEPROM	void	sSetEEPowerSaveMode(INT16U uwtemp);
EEPROM	void	sSetEENoBatMode(INT16U uwtemp);
EEPROM	void	sSetEELogoEnable(INT16U uwtemp);
EEPROM	void	sSetEEAdcBiasAdj(INT16U uwtemp);
EEPROM	void	sSetLeakCurrProtectEnable(INT16U uwtemp);
EEPROM	void	sSetLeakCurrProtectValue(INT16U uwtemp);
EEPROM	void	sSetISOCheckEnable(INT16U uwtemp);
EEPROM	void	sSetISOCheckValue(INT16U uwtemp);
EEPROM	void	sSetEERsvd17(INT16U uwtemp);
EEPROM	void	sSetEERsvd18(INT16U uwtemp);
EEPROM	void	sSetEERsvd19(INT16U uwtemp);
EEPROM	void	sSetEERsvd20(INT16U uwtemp);
EEPROM	void	sSetEERsvd21(INT16U uwtemp);
EEPROM	void	sSetEERsvd22(INT16U uwtemp);
EEPROM	void	sSetEERsvd23(INT16U uwtemp);
EEPROM	void	sSetEERsvd24(INT16U uwtemp);
EEPROM	void	sSetEERsvd25(INT16U uwtemp);
EEPROM	void	sSetEERsvd26(INT16U uwtemp);
EEPROM	void	sSetEERsvd27(INT16U uwtemp);
EEPROM	void	sSetEERsvd28(INT16U uwtemp);
EEPROM	void	sSetEERsvd29(INT16U uwtemp);
EEPROM	void	sSetEERsvd30(INT16U uwtemp);
EEPROM	void	sSetEERsvd31(INT16U uwtemp);
EEPROM	void	sSetEERsvd32(INT16U uwtemp);
//strBatData
EEPROM	void	sSetEEBatType(INT16U uwtemp);
EEPROM	void	sSetEEBatSeriesNum(INT16U uwtemp);
EEPROM	void	sSetEEBatActivateEnable(INT16U uwtemp);
EEPROM	void	sSetEEBatCapacity(INT16U uwtemp);
EEPROM	void	sSetEELithiumMode(INT16U uwtemp);
EEPROM	void	sSetEERsvd38(INT16U uwtemp);
EEPROM	void	sSetEEBatMaxChgCurr(INT16U uwtemp);
EEPROM	void	sSetEEBatMaxDcgCurr(INT16U uwtemp);
EEPROM	void	sSetEEBatVoltage(INT16U uwtemp);
EEPROM	void	sSetEERsvd42(INT16U uwtemp);
EEPROM	void	sSetEEGridChargeEn(INT16U uwtemp);
EEPROM	void	sSetEEGridChgBatCurr(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatAutoStartChgVolt(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatExitAutoChgVolt(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatAutoStartChgSOC(INT16U uwtemp);
EEPROM	void	sSetEEOnGridBatExitAutoChgSOC(INT16U uwtemp);
EEPROM	void	sSetEERsvd49(INT16U uwtemp);
EEPROM	void	sSetEEGenChargeEn(INT16U uwtemp);
EEPROM	void	sSetEEGenMaxChargeCurr(INT16U uwtemp);
EEPROM	void	sSetEEGenStartChargeVolt(INT16U uwtemp);
EEPROM	void	sSetEEGenEndChargeVolt(INT16U uwtemp);
EEPROM	void	sSetEEGenStartChargeSOC(INT16U uwtemp);
EEPROM	void	sSetEEGenEndChargeSOC(INT16U uwtemp);
EEPROM	void	sSetEERsvd56(INT16U uwtemp);
EEPROM	void	sSetEEBatFloatTime(INT16U uwtemp);
EEPROM	void 	sSetEEBatLowShutDownSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatACRestartSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatLowAlarmSOC(INT16U uwtemp);
EEPROM	void	sSetEEBatConstVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatFloatVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatLowShutDownVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatACRestartVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatLowAlarmVolt(INT16U uwtemp);
EEPROM	void	sSetEEBatVoltOverShut(INT16U uwtemp);
EEPROM	void	sSetEEBatEqVolt(INT16U uwtemp);
EEPROM	void	sSetEERsvd66(INT16U uwtemp);
EEPROM	void	sSetEERsvd67(INT16U uwtemp);
EEPROM	void	sSetEEBattResistance(INT16U uwtemp);
EEPROM	void	sSetEEBMSComErrEnable(INT16U uwtemp);
EEPROM	void	sSetEEBatParaEnable(INT16U uwtemp);
EEPROM	void	sSetEEBatTempCompensateEnable(INT16U uwtemp);
EEPROM	void	sSetBatTempCalibration(INT16U uwtemp);
EEPROM	void	sSetEERsvd74(INT16U uwtemp);
EEPROM	void	sSetEERsvd75(INT16U uwtemp);
EEPROM	void	sSetEEBatEqEn(INT16U uwtemp);
EEPROM	void	sSetEEBatEqTime(INT16U uwtemp);
EEPROM	void	sSetEEBatEqTimeout(INT16U uwtemp);
EEPROM	void	sSetEEBatEqInterval(INT16U uwtemp);
EEPROM	void	sSetEEBatEqActImd(INT16U uwtemp);
EEPROM	void	sSetEERsvd82(INT16U uwtemp);
EEPROM	void	sSetEERsvd83(INT16U uwtemp);
EEPROM	void	sSetEEBatLowVoltDerateEnable(INT16U uwtemp);
EEPROM	void	sSetEEBatPowerOutEn(INT16U uwtemp);
EEPROM	void	sSetEEBMSErrStopEn(INT16U uwtemp);
EEPROM	void	sSetEESOCDisplayEn(INT16U uwtemp);
EEPROM	void	sSetEERsvd88(INT16U uwtemp);
EEPROM	void	sSetEERsvd89(INT16U uwtemp);
EEPROM	void	sSetEERsvd90(INT16U uwtemp);
EEPROM	void	sSetEERsvd91(INT16U uwtemp);
EEPROM	void	sSetEERsvd92(INT16U uwtemp);
EEPROM	void	sSetEERsvd93(INT16U uwtemp);
EEPROM	void	sSetEERsvd94(INT16U uwtemp);
EEPROM	void	sSetEERsvd95(INT16U uwtemp);
EEPROM	void	sSetEERsvd96(INT16U uwtemp);
EEPROM	void	sSetEEBattAhReal(INT16U uwtemp);
EEPROM	void	sSetEEBattAhMax(INT16U uwtemp);
EEPROM	void	sSetEEBattFullCnt(INT16U uwtemp);
EEPROM	void	sSetEEBattEmptyCnt(INT16U uwtemp);
EEPROM	void	sSetEEBattCycCnt(INT16U uwtemp);
EEPROM	void	sSetEEBattAhRealShow(INT16U uwtemp);
EEPROM	void	sSetEESOCSmoothEn(INT16U uwtemp);
EEPROM	void	sSetEERsvd104(INT16U uwtemp);
EEPROM	void	sSetEERsvd105(INT16U uwtemp);
EEPROM	void	sSetEERsvd106(INT16U uwtemp);
EEPROM	void	sSetEERsvd107(INT16U uwtemp);
EEPROM	void	sSetEERsvd108(INT16U uwtemp);
EEPROM	void	sSetEERsvd109(INT16U uwtemp);
EEPROM	void	sSetEERsvd110(INT16U uwtemp);
EEPROM	void	sSetEERsvd111(INT16U uwtemp);
EEPROM	void	sSetEERsvd112(INT16U uwtemp);
EEPROM	void	sSetEERsvd113(INT16U uwtemp);
EEPROM	void	sSetEERsvd114(INT16U uwtemp);
EEPROM	void	sSetEERsvd115(INT16U uwtemp);
EEPROM	void	sSetEERsvd116(INT16U uwtemp);
EEPROM	void	sSetEERsvd117(INT16U uwtemp);
EEPROM	void	sSetEERsvd118(INT16U uwtemp);
EEPROM	void	sSetEERsvd119(INT16U uwtemp);
EEPROM	void	sSetEERsvd120(INT16U uwtemp);
EEPROM	void	sSetEERsvd121(INT16U uwtemp);
EEPROM	void	sSetEERsvd122(INT16U uwtemp);
EEPROM	void	sSetEERsvd123(INT16U uwtemp);
EEPROM	void	sSetEERsvd124(INT16U uwtemp);
EEPROM	void	sSetEERsvd125(INT16U uwtemp);
EEPROM	void	sSetEERsvd126(INT16U uwtemp);
EEPROM	void	sSetEERsvd127(INT16U uwtemp);
EEPROM	void	sSetEERsvd128(INT16U uwtemp);
//strPvData
EEPROM	void	sSetEEPV1StartVolt(INT16U uwtemp);
EEPROM	void	sSetEEPV1PowerLimit(INT16U uwtemp);
EEPROM	void	sSetEEPV2StartVolt(INT16U uwtemp);
EEPROM	void	sSetEEPV1CurrrLimit(INT16U uwtemp);
EEPROM	void	sSetEEPV2CurrrLimit(INT16U uwtemp);
EEPROM	void	sSetEEPV2PowerLimit(INT16U uwtemp);
EEPROM	void	sSetEEMpptMultiPoint(INT16U uwtemp);
EEPROM	void	sSetEEPVInputMode(INT16U uwtemp);
EEPROM	void	sSetEERsvd137(INT16U uwtemp);
EEPROM	void	sSetEERsvd138(INT16U uwtemp);
EEPROM	void	sSetEERsvd139(INT16U uwtemp);
EEPROM	void	sSetEERsvd140(INT16U uwtemp);
EEPROM	void	sSetEERsvd141(INT16U uwtemp);
EEPROM	void	sSetEERsvd142(INT16U uwtemp);
EEPROM	void	sSetEERsvd143(INT16U uwtemp);
EEPROM	void	sSetEERsvd144(INT16U uwtemp);
//strAcData
EEPROM	void	sSetEEGridInputRange(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedFreq(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedPower(INT16U uwtemp);
EEPROM	void	sSetEEACOutputRatedVolt(INT16U uwtemp);
EEPROM	void	sSetEEGridCurrLimit(INT16U uwtemp);
EEPROM	void	sSetEEGridInputPower(INT16U uwtemp);
EEPROM	void	sSetEEMaxFeedPower(INT16U uwtemp);
EEPROM	void	sSetEEGridVoltUpperLimit(INT16U uwtemp);
EEPROM	void	sSeEEGridVoltLowerLimit(INT16U uwtemp);
EEPROM	void	sSetEEAutoInvEnable(INT16U uwtemp);
EEPROM	void	sSetEEDCDCOpenLoopEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd151(INT16U uwtemp);
EEPROM	void	sSetEERsvd152(INT16U uwtemp);
EEPROM	void	sSetEEOverTempRestartEn(INT16U uwtemp);
EEPROM	void	sSetEEOverLoadRestartEn(INT16U uwtemp);
EEPROM	void	sSetEEOverLoadBypassEn(INT16U uwtemp);
EEPROM	void	sSetEERsvd156(INT16U uwtemp);
EEPROM	void	sSetEERsvd157(INT16U uwtemp);
EEPROM	void	sSetEERsvd158(INT16U uwtemp);
EEPROM	void	sSetEEOnGridAlwayOn(INT16U uwtemp);
EEPROM	void	sSetEEOffGridImmediatelyOff(INT16U uwtemp);
EEPROM	void	sSetEEPVPowerRlyOn(INT16U uwtemp);
EEPROM	void	sSetEERlySocOn(INT16U uwtemp);
EEPROM	void	sSetEERlySocOff(INT16U uwtemp);
EEPROM	void	sSetEERlyVoltOn(INT16U uwtemp);
EEPROM	void	sSetEERlyVoltOff(INT16U uwtemp);
EEPROM	void	sSetEEOffGridWaitTime(INT16U uwtemp);
EEPROM	void	sSetEEOnGridWaitTime(INT16U uwtemp);
EEPROM	void	sSetEEAnti_IslandProtectEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd169(INT16U uwtemp);
EEPROM	void	sSetEEFeedEnable(INT16U uwtemp);
EEPROM	void	sSetEEGridMaxInputPowerLimitEn(INT16U uwtemp);
EEPROM	void	sSetEERsvd177(INT16U uwtemp);
EEPROM	void	sSetEERsvd178(INT16U uwtemp);
EEPROM	void	sSetEEZeroExportPower(INT16U uwtemp);
EEPROM	void	sSetEEGridPeakShavingEnable(INT16U uwtemp);
EEPROM	void	sSetEEGridPeakShavingPower(INT16U uwtemp);
EEPROM	void	sSetEETurboMode(INT16U uwtemp);
EEPROM	void	sSetEETouMode(INT16U uwtemp);
EEPROM	void	sSetEECloseGSRlyEn(INT16U uwtemp);
EEPROM	void	sSetEEGridpowerslope(INT16U uwtemp);
EEPROM	void	sSetEEGridpowerlimitation(INT16U uwtemp);
EEPROM	void	sSetEEPVAutoInvEnable(INT16U uwtemp);
EEPROM	void	sSetEERsvd188(INT16U uwtemp);
EEPROM	void	sSetEERsvd189(INT16U uwtemp);
EEPROM	void	sSetEERsvd190(INT16U uwtemp);
EEPROM	void	sSetEERsvd191(INT16U uwtemp);
EEPROM	void	sSetEERsvd192(INT16U uwtemp);
EEPROM	void	sSetEERsvd193(INT16U uwtemp);
EEPROM	void	sSetEERsvd194(INT16U uwtemp);
EEPROM	void	sSetEERsvd195(INT16U uwtemp);
EEPROM	void	sSetEERsvd196(INT16U uwtemp);
EEPROM	void	sSetEERsvd197(INT16U uwtemp);
EEPROM	void	sSetEERsvd198(INT16U uwtemp);
EEPROM	void	sSetEERsvd199(INT16U uwtemp);
EEPROM	void	sSetEERsvd200(INT16U uwtemp);
EEPROM	void	sSetEERsvd201(INT16U uwtemp);
EEPROM	void	sSetEERsvd202(INT16U uwtemp);
EEPROM	void	sSetEERsvd203(INT16U uwtemp);
EEPROM	void	sSetEERsvd204(INT16U uwtemp);
EEPROM	void	sSetEERsvd205(INT16U uwtemp);
EEPROM	void	sSetEERsvd206(INT16U uwtemp);
EEPROM	void	sSetEERsvd207(INT16U uwtemp);
EEPROM	void	sSetEERsvd208(INT16U uwtemp);
EEPROM	void	sSetEERsvd209(INT16U uwtemp);
EEPROM	void	sSetEERsvd210(INT16U uwtemp);
EEPROM	void	sSetEERsvd211(INT16U uwtemp);
EEPROM	void	sSetEERsvd212(INT16U uwtemp);
EEPROM	void	sSetEERsvd213(INT16U uwtemp);
EEPROM	void	sSetEERsvd214(INT16U uwtemp);
EEPROM	void	sSetEERsvd215(INT16U uwtemp);
EEPROM	void	sSetEERsvd216(INT16U uwtemp);
EEPROM	void	sSetEERsvd217(INT16U uwtemp);
EEPROM	void	sSetEERsvd218(INT16U uwtemp);
EEPROM	void	sSetEERsvd219(INT16U uwtemp);
EEPROM	void	sSetEERsvd220(INT16U uwtemp);
EEPROM	void	sSetEERsvd221(INT16U uwtemp);
EEPROM	void	sSetEERsvd222(INT16U uwtemp);
EEPROM	void	sSetEERsvd223(INT16U uwtemp);
EEPROM	void	sSetEERsvd224(INT16U uwtemp);
EEPROM	void	sSetGenMode(INT16U uwtemp);
EEPROM	void	sSetGenInputEn(INT16U uwtemp);
EEPROM	void	sSetGenInputMaxPower(INT16U uwtemp);
EEPROM	void	sSetGenConnectToGridPortEn(INT16U uwtemp);
EEPROM	void	sSetSmartLoad_OpenPower(INT16U uwtemp);
EEPROM	void	sSetSmartLoad_StartBatVolt(INT16U uwtemp);
EEPROM	void	sSetSmartLoad_ExitBatVolt(INT16U uwtemp);
EEPROM	void	sSetSmartLoad_StartSOC(INT16U uwtemp);
EEPROM	void	sSetSmartLoad_ExitSOC(INT16U uwtemp);
EEPROM	void	sSetOnGrid_SmartLoadEn(INT16U uwtemp);
EEPROM	void	sSetOffGrid_SmartLoadDis(INT16U uwtemp);
EEPROM	void	sSetEEDry1ContactMode(INT16U uwtemp);
EEPROM	void	sSetEEDry2ContactMode(INT16U uwtemp);
//strReserve
EEPROM	void	sSetEERsvd238(INT16U uwtemp);
EEPROM	void	sSetEERsvd239(INT16U uwtemp);
EEPROM	void	sSetEERsvd240(INT16U uwtemp);
EEPROM	void	sSetEERsvd241(INT16U uwtemp);
EEPROM	void	sSetEERsvd242(INT16U uwtemp);
EEPROM	void	sSetEERsvd243(INT16U uwtemp);
EEPROM	void	sSetEERsvd244(INT16U uwtemp);
EEPROM	void	sSetEERsvd245(INT16U uwtemp);
EEPROM	void	sSetEERsvd246(INT16U uwtemp);
EEPROM	void	sSetEERsvd247(INT16U uwtemp);
EEPROM	void	sSetEERsvd248(INT16U uwtemp);
EEPROM	void	sSetEERsvd249(INT16U uwtemp);
EEPROM	void	sSetEERsvd250(INT16U uwtemp);
EEPROM	void	sSetEERsvd251(INT16U uwtemp);
EEPROM	void	sSetEERsvd252(INT16U uwtemp);
EEPROM	void	sSetEERsvd253(INT16U uwtemp);
EEPROM	void	sSetEERsvd254(INT16U uwtemp);
EEPROM	void	sSetEERsvd255(INT16U uwtemp);
EEPROM	void	sSetEERsvd256(INT16U uwtemp);
EEPROM	void	sSetEERsvd257(INT16U uwtemp);
EEPROM	void	sSetEERsvd258(INT16U uwtemp);
EEPROM	void	sSetEERsvd259(INT16U uwtemp);
EEPROM	void	sSetEERsvd260(INT16U uwtemp);
EEPROM	void	sSetEERsvd261(INT16U uwtemp);
EEPROM	void	sSetEERsvd262(INT16U uwtemp);
EEPROM	void	sSetEERsvd263(INT16U uwtemp);
EEPROM	void	sSetEERsvd264(INT16U uwtemp);
EEPROM	void	sSetEERsvd265(INT16U uwtemp);
EEPROM	void	sSetEERsvd266(INT16U uwtemp);
EEPROM	void	sSetEERsvd267(INT16U uwtemp);
EEPROM	void	sSetEERsvd268(INT16U uwtemp);
EEPROM	void	sSetEERsvd269(INT16U uwtemp);
EEPROM	void	sSetEERsvd270(INT16U uwtemp);
EEPROM	void	sSetEERsvd271(INT16U uwtemp);
EEPROM	void	sSetEERsvd272(INT16U uwtemp);
EEPROM	void	sSetEERsvd273(INT16U uwtemp);
EEPROM	void	sSetEERsvd274(INT16U uwtemp);
EEPROM	void	sSetEERsvd275(INT16U uwtemp);
EEPROM	void	sSetEERsvd276(INT16U uwtemp);
EEPROM	void	sSetEERsvd277(INT16U uwtemp);
EEPROM	void	sSetEERsvd278(INT16U uwtemp);
EEPROM	void	sSetEERsvd279(INT16U uwtemp);
EEPROM	void	sSetEERsvd280(INT16U uwtemp);
EEPROM	void	sSetEERsvd281(INT16U uwtemp);
EEPROM	void	sSetEERsvd282(INT16U uwtemp);
EEPROM	void	sSetEERsvd283(INT16U uwtemp);
EEPROM	void	sSetEERsvd284(INT16U uwtemp);
EEPROM	void	sSetEERsvd285(INT16U uwtemp);
EEPROM	void	sSetEERsvd286(INT16U uwtemp);
EEPROM	void	sSetEERsvd287(INT16U uwtemp);
EEPROM	void	sSetEERsvd288(INT16U uwtemp);
EEPROM	void	sSetEERsvd289(INT16U uwtemp);
EEPROM	void	sSetEERsvd290(INT16U uwtemp);
EEPROM	void	sSetEERsvd291(INT16U uwtemp);
EEPROM	void	sSetEERsvd292(INT16U uwtemp);
EEPROM	void	sSetEERsvd293(INT16U uwtemp);
EEPROM	void	sSetEERsvd294(INT16U uwtemp);
EEPROM	void	sSetEERsvd295(INT16U uwtemp);
EEPROM	void	sSetEERsvd296(INT16U uwtemp);
EEPROM	void	sSetEERsvd297(INT16U uwtemp);
EEPROM	void	sSetEERsvd298(INT16U uwtemp);
EEPROM	void	sSetEERsvd299(INT16U uwtemp);
EEPROM	void	sSetEERsvd300(INT16U uwtemp);
EEPROM	void	sSetEERsvd301(INT16U uwtemp);
EEPROM	void	sSetEERsvd302(INT16U uwtemp);
EEPROM	void	sSetEERsvd303(INT16U uwtemp);
EEPROM	void	sSetEERsvd304(INT16U uwtemp);
//strECOMode
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
EEPROM	void	sSetEEECO7_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO7_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_GridChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_GenChargeEnable(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_StartTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_StopTime(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_Volt(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_SOC(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_Power(INT16U uwtemp);		
EEPROM	void	sSetEEECO8_WorkModeSet(INT16U uwtemp);		
EEPROM	void	sSetEERsvd371(INT16U uwtemp);		
EEPROM	void	sSetEERsvd372(INT16U uwtemp);		
//strATESet
EEPROM	void	sSetEEATE_UpdateFW(INT16U uwtemp);
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
EEPROM	void	sSetEERsvd387(INT16U uwtemp);		
EEPROM	void	sSetEERsvd388(INT16U uwtemp);	
EEPROM	void	sSetEERsvd389(INT16U uwtemp);		
EEPROM	void	sSetEERsvd390(INT16U uwtemp);	
EEPROM	void	sSetEERsvd391(INT16U uwtemp);	
EEPROM	void	sSetEERsvd392(INT16U uwtemp);	
EEPROM	void	sSetEERsvd393(INT16U uwtemp);	
EEPROM	void	sSetEERsvd394(INT16U uwtemp);	
EEPROM	void	sSetEERsvd395(INT16U uwtemp);	
EEPROM	void	sSetEERsvd396(INT16U uwtemp);	
EEPROM	void	sSetEERsvd397(INT16U uwtemp);		
EEPROM	void	sSetEERsvd398(INT16U uwtemp);	
EEPROM	void	sSetEERsvd399(INT16U uwtemp);
EEPROM	void	sSetEERsvd400(INT16U uwtemp);
EEPROM	void	sSetEERsvd401(INT16U uwtemp);
EEPROM	void	sSetEERsvd402(INT16U uwtemp);
EEPROM	void	sSetEERsvd403(INT16U uwtemp);
EEPROM	void	sSetEERsvd404(INT16U uwtemp);
EEPROM	void	sSetEERsvd405(INT16U uwtemp);
EEPROM	void	sSetEERsvd406(INT16U uwtemp);
EEPROM	void	sSetEERsvd407(INT16U uwtemp);
EEPROM	void	sSetEERsvd408(INT16U uwtemp);
EEPROM	void	sSetEERsvd409(INT16U uwtemp);
EEPROM	void	sSetEERsvd410(INT16U uwtemp);
EEPROM	void	sSetEERsvd411(INT16U uwtemp);
EEPROM	void	sSetEERsvd412(INT16U uwtemp);
EEPROM	void	sSetEERsvd413(INT16U uwtemp);
EEPROM	void	sSetEERsvd414(INT16U uwtemp);
EEPROM	void	sSetEERsvd415(INT16U uwtemp);
EEPROM	void	sSetEERsvd416(INT16U uwtemp);
EEPROM	void	sSetEERsvd417(INT16U uwtemp);
EEPROM	void	sSetEERsvd418(INT16U uwtemp);
EEPROM	void	sSetEERsvd419(INT16U uwtemp);
EEPROM	void	sSetEERsvd420(INT16U uwtemp);

EEPROM	void	sSetEEBmsBagAddr(INT16U uwtemp);
EEPROM	void	sSetEEClearEventLog(INT16U uwtemp);
EEPROM	void	sSetEEEventLogFunc(INT16U uwtemp);
EEPROM	void	sSetEEFaultLogFunc(INT16U uwtemp);
EEPROM	void	sSetEELogType(INT16U uwtemp);
EEPROM	void	sSetEELogIndex(INT16U uwtemp);
EEPROM	void	sSetEERsvd427(INT16U uwtemp);
EEPROM	void	sSetEERsvd428(INT16U uwtemp);
EEPROM	void	sSetEERsvd429(INT16U uwtemp);
EEPROM	void	sSetEERsvd430(INT16U uwtemp);
EEPROM	void	sSetEERsvd431(INT16U uwtemp);
EEPROM	void	sSetEERsvd432(INT16U uwtemp);
EEPROM	void	sSetEERsvd433(INT16U uwtemp);
EEPROM	void	sSetEERsvd434(INT16U uwtemp);
EEPROM	void	sSetEERsvd435(INT16U uwtemp);
EEPROM	void	sSetEERsvd436(INT16U uwtemp);
EEPROM	void	sSetEEFlag2(INT16U uwtemp);
EEPROM	void	sSetEECheckCRC2(INT16U uwtemp);

//EEPROM3
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
EEPROM	void	sSetSetRsvd558(INT16U uwtemp);
EEPROM	void	sSetSetRsvd559(INT16U uwtemp);
EEPROM	void	sSetSetRsvd560(INT16U uwtemp);
EEPROM	void	sSetSetRsvd561(INT16U uwtemp);
EEPROM	void	sSetSetRsvd562(INT16U uwtemp);
EEPROM	void	sSetSetRsvd563(INT16U uwtemp);
EEPROM	void	sSetEEFlag3(INT16U uwtemp);
EEPROM	void	sSetEECheckCRC3(INT16U uwtemp);


#endif	// __EEEPROM_PROCESS_H__


