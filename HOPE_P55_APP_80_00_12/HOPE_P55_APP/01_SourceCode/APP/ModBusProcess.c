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
#define REALDATA_REG_BASE_LEN	0x1C0				// 实时数据寄存器长度

#define EE_REG_BASE_ADDR		0x2100				// EEPROM数据寄存器起始地址
#define EE_REG_BASE_LEN			0X900//(cEepromTotalLength1 + cEepromTotalLength2 + cEepromTotalLength3) / 2//0xC0				// EEPROM数据寄存器长度

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

	//EEPROM1
	EE_uwMachCode = EE_uwAddrStart,	//	0 机型代码
	EE_uwEE_SN1,					//	1 机器序列号1
	EE_uwEE_SN2,					//	2 机器序列号2
	EE_uwEE_SN3,					//	3 机器序列号3
	EE_uwEE_SN4,					//	4 机器序列号4
	EE_uwEE_SN5,					//	5 机器序列号5
	EE_uwEE_SNLen,					//	6 机器序列号长度
	EE_uwEE_DispHwVer,				//	7 ATE写显示板版本号
	EE_uwEE_CtrlHwVer,				//	8 ATE写控制板版本号
	EE_uwEE_PowerHwVer,				//	9 ATE写功率板版本号
	EE_uwEEPV1VoltAdj,				//	10 PV1电压校准系数
	EE_uwEEPV1VoltBias,				//	11 PV1电压校准偏置
	EE_uwEEPV2VoltAdj,				//	12 PV2电压校准系数
	EE_uwEEPV2VoltBias,				//	13 PV2电压校准偏置
	EE_uwEEPV1CurrAdj,				//	14 PV1电流校准系数
	EE_uwEEPV1CurrBias,				//	15 PV1电流校准偏置
	EE_uwEEPV2CurrAdj,				//	16 PV2电流校准系数
	EE_uwEEPV2CurrBias,				//	17 PV2电流校准偏置
	EE_uwEEBatVoltAdj,				//	18 电池电压校准系数
	EE_uwEEBatVoltBias,				//	19 电池电压校准偏置
	EE_uwEEBatCurrAdj,				//	20 电池电流校准系数
	EE_uwEEBatCurrBias,				//	21 电池电流校准偏置
	EE_uwEEBUSVoltAdj,				//	22 Bus电压校准系数
	EE_uwEEBUSVoltBias,				//	23 Bus电压校准偏置
	EE_uwEEBUSCurrAdj,				//	24 Bus电流校准系数
	EE_uwEEBUSCurrBias,				//	25 Bus电流校准偏置
	EE_uwEEInvVoltAdj,				//	26 逆变电压校准系数
	EE_uwEEInvVoltBias,				//	27 逆变电压校准偏置
	EE_uwEEInvCurrAdj,				//	28 逆变电流校准系数
	EE_uwEEInvCurrBias,				//	29 逆变电流校准偏置
	EE_uwEEGridVoltAdj,				//	30 电网电压校准系数
	EE_uwEEGridVoltBias, 			//	31 电网电压校准偏置
	EE_uwEEGridCurrAdj,				//	32 电网电流校准系数
	EE_uwEEGridCurrBias, 			//	33 电网电流校准偏置
	EE_uwEEOPVoltAdj,				//	34 输出电压校准系数
	EE_uwEEOpVoltBias,				//	35 输出电压校准偏置
	EE_uwEEOPCurrAdj,				//	36 输出电流校准系数
	EE_uwEEOpCurrBias,				//	37 输出电流校准偏置
	EE_uwEEDischargeEneyCoeffH,		//	38 放电量校准高位
	EE_uwEEDischargeEneyCoeffL,		//	39 放电量校准低位
	EE_uwEEchargeEneyCoeffH, 		//	40 充电量校准高位
	EE_uwEEchargeEneyCoeffL, 		//	41 充电量校准低位
	EE_uwEEGenVoltAdj, 				//	42 Gen电压校准系数
	EE_uwEEGenVoltBias, 			//	43 Gen电压校准偏置
	EE_uwEEGenCurrAdj, 				//	44 Gen电流校准系数
	EE_uwEEGenCurrBias, 			//	45 Gen电流校准偏置
	EE_uwSetRsvd5, 					//	46 预留
	EE_uwSetRsvd6, 					//	47 预留
	EE_uwSetRsvd7, 					//	48 预留
	EE_uwSetRsvd8, 					//	49 预留
	EE_uwSetRsvd9, 					//	50 预留
	EE_uwSetRsvd10, 				//	51 预留
	EE_uwSetRsvd11, 				//	52 预留
	EE_uwSetRsvd12, 				//	53 预留
	EE_uwSetRsvd13, 				//	54 预留
	EE_uwSetRsvd14, 				//	55 预留
	EE_uwSetRsvd15, 				//	56 预留
	EE_uwSetRsvd16, 				//	57 预留
	EE_uwSetRsvd17, 				//	58 预留
	EE_uwSetRsvd18, 				//	59 预留
	EE_uwSetRsvd19, 				//	60 预留
	EE_uwSetRsvd20, 				//	61 预留
	EE_uwSetRsvd21, 				//	62 预留
	EE_uwSetRsvd22, 				//	63 预留
	EE_uwSetRsvd23, 				//	64 预留
	EE_uwSetRsvd24, 				//	65 预留
	EE_uwSetRsvd25, 				//	66 预留
	EE_uwSetRsvd26, 				//	67 预留
	EE_uwSetRsvd27, 				//	68 预留
	EE_uwSetRsvd28, 				//	69 预留
	EE_uwSetRsvd29, 				//	70 预留
	EE_uwSetRsvd30, 				//	71 预留
	EE_uwSetRsvd31, 				//	72 预留
	EE_uwSetRsvd32, 				//	73 预留
	EE_uwSetRsvd33, 				//	74 预留
	EE_uwSetRsvd34, 				//	75 预留
	EE_uwSetRsvd35, 				//	76 预留
	EE_uwSetRsvd36, 				//	77 预留
	EE_uwSetRsvd37, 				//	78 预留
	EE_uwSetRsvd38, 				//	79 预留
	EE_uwSetRsvd39, 				//	80 预留
	EE_uwSetRsvd40, 				//	81 预留
	EE_uwSetRsvd41, 				//	81 预留
	EE_uwSetRsvd42, 				//	81 预留
	EE_uwSetRsvd43, 				//	81 预留
	EE_uwSetRsvd44, 				//	81 预留
	EE_uwSetRsvd45, 				//	81 预留
	EE_uwSetRsvd46, 				//	81 预留
	EE_uwSetRsvd47, 				//	81 预留
	EE_uwSetRsvd48, 				//	81 预留
	EE_uwSetRsvd49, 				//	81 预留
	EE_uwSetRsvd50, 				//	91 预留
	EE_uwSetRsvd51, 				//	92 预留
	EE_uwSetRsvd52, 				//	93 预留
	EE_uwFlag1,						//	94 EEPROM标志
	EE_uwEECheckCRC1,				//	95 CRC校验

	// EEPROM2
	EE_uwEEParallel,				//	96	并机使能
	EE_uwEEParalleltMasterSlaver,	//	97	并机角色 
	EE_uwEEParallelPhase, 			//	98	并机相位
	EE_uwEEParallelIID,				//	99	并机ID
	EE_uwSetSystemOutputMode,		//	100	系统输出模式
	EE_uwEEWorkMode,				//	101	工作模式
	EE_uwEEFanWorkMode, 			//	102	风机运行模式
	EE_uwEEPowerConversion,			//	103	功率折算使能
	EE_uwEEPowerSaveMode,			//	104	节能模式
	EE_uwEENoBatMode,				//	105	无电池模式
	EE_uwEELogoEnable,				//	106	logo使能
	EE_uwEEAdcBiasAdj,				//	107	采样偏置校准
	EE_eSetLeakCurrProtectEnable,	//	108	漏电流GFCI保护使能
	EE_eSetLeakCurrProtectValue,	//	109	漏电流GFCI保护阀值
	EE_eSetISOCheckEnable,			//	110	绝缘阻抗检测使能
	EE_eSetISOCheckValue,			//	111	绝缘阻抗检测阀值
	EE_uwEERsvd17, 					//	112 预留
	EE_uwEERsvd18, 					//	113 预留
	EE_uwEERsvd19, 					//	114 预留
	EE_uwEERsvd20, 					//	115 预留
	EE_uwEERsvd21, 					//	116 预留
	EE_uwEERsvd22, 					//	117 预留
	EE_uwEERsvd23, 					//	118 预留
	EE_uwEERsvd24, 					//	119 预留
	EE_uwEERsvd25, 					//	120 预留
	EE_uwEERsvd26, 					//	121 预留
	EE_uwEERsvd27, 					//	122 预留
	EE_uwEERsvd28, 					//	123 预留
	EE_uwEERsvd29, 					//	124 预留
	EE_uwEERsvd30, 					//	125 预留
	EE_uwEERsvd31, 					//	126 预留
	EE_uwEERsvd32, 					//	127 预留
	EE_uwEEBatType,					//	128	电池类型
	EE_uwEEBatSeriesNum,			//	129	电池节数
	EE_uwEEBatActivate,				//	130	电池激活
	EE_uwEEBatCapacity, 			//	131	电池容量
	EE_uwEELithiumMode, 			//	132	锂电池模式
	EE_uwEERsvd38, 					//	133 预留
	EE_uwEEBatMaxChgCurr,			//	134	电池最大充电电流限幅值
	EE_uwEEBatMaxDcgCurr,			//	135	电池最大放电电流限幅值
	EE_uwEEBatVoltage,				//	136	电池额定电压(电池节数)
	EE_uwEERsvd42, 					//	137 预留
	EE_uwEEGridChargeEn,			//	138	市电充电使能
	EE_uwEEGridMaxChargeCurr,		//	139	市电最大充电电流
	EE_uwEEGridStartChargeVolt,		//	140	市电开始充电电池电压
	EE_uwEEGridEndChargeVolt,		//	141	市电停止充电电池电压
	EE_uwEEGridStartChargeSOC,		//	142	市电开始充电电池SOC
	EE_uwEEGridEndChargeSOC, 		//	143	市电停止充电电池SOC
	EE_uwEERsvd49, 					//	144 预留
	EE_uwEEGenChargeEn,				//	145	油机充电使能
	EE_uwEEGenMaxChargeCurr,		//	146	油机最大充电电流
	EE_uwEEGenStartChargeVolt,		//	147	油机开始充电电池电压
	EE_uwEEGenEndChargeVolt,		//	148	油机停止充电电池电压
	EE_uwEEGenStartChargeSOC,		//	149	油机开始充电电池SOC
	EE_uwEEGenEndChargeSOC, 		//	150	油机停止充电电池SOC
	EE_uwEERsvd56, 					//	151 预留
	EE_uwSetBatConstVolt,			//	152	电池恒压充电压
	EE_uwSetBatFloatVolt,			//	153	电池浮充电压
	EE_uwSetBatFloatTime,			//	154	电池恒充时间
	EE_uwEEShutdownSOC,				//	155	电池停止输出SOC
	EE_uwEEShutdownVolt,			//	156	电池停止输出电压
	EE_uwEEBatRestartOutSOC, 		//	157	电池重启输出SOC恢复输出SOC
	EE_uwEEBatRestartOutVolt,		//	158	电池重启输出电压恢复输出电压
	EE_uwEELowBattSOC,				//	159	电池电量低电量SOC
	EE_uwEELowBattVolt, 			//	160	电池电量低电量电压
	EE_uwEERsvd66, 					//	161 预留
	EE_uwEERsvd67, 					//	162 预留
	EE_uwEEBattResistance, 			//	163 电池线路阻抗
	EE_uwSetBatVoltOverShut, 		//	164	电池过压保护点
	EE_uwSetBMSComErrEnable, 		//	165	BMS通讯故障使能
	EE_uwSetBatParaEnable,			//	166	电池并联使能
	EE_uwSetBatTempCompensateEnable, //	167	电池温度补偿使能
	EE_uwSetBatTempCalibration, 	//	168	电池温度补偿系数
	EE_uwEERsvd74, 					//	169 预留
	EE_uwEERsvd75, 					//	170 预留
	EE_uwEEBatEqEn,					//	171	EQ使能
	EE_uwEEBatEqVolt,				//	172	EQ电压
	EE_uwEEBatEqTime,				//	173	EQ时间
	EE_uwEEBatEqTimeout,			//	174	EQ超时时间
	EE_uwEEBatEqInterval,			//	175	EQ间隔时间
	EE_uwEEBatEqActImd,				//	176	立即EQ使能
	EE_uwEERsvd82, 					//	177 预留
	EE_uwEERsvd83, 					//	178 预留
	EE_uwEEBatLowVoltDerateEnable, 	//	179	电池低压降额使能
	EE_uwEEBatPowerOutEn, 			//	180	电池出功使能
	EE_uwEEBMSErrStopEn, 			//	181	BMS异常停止工作
	EE_uwEESOCDisplayEn, 			//	182	主页显示SOC
	EE_uwEERsvd88, 					//	183 预留
	EE_uwEERsvd89, 					//	184 预留
	EE_uwEERsvd90, 					//	185 预留
	EE_uwEERsvd91, 					//	186 预留
	EE_uwEERsvd92, 					//	187 预留
	EE_uwEERsvd93, 					//	188 预留
	EE_uwEERsvd94, 					//	189 预留
	EE_uwEERsvd95, 					//	190 预留
	EE_uwEERsvd96, 					//	191 预留
	EE_uwEEBattAhReal, 					//	192 预留
	EE_uwEEBattAhMax, 					//	193 预留
	EE_uwEEBattFullCnt, 					//	194 预留
	EE_uwEEBattEmptyCnt, 				//	195 预留
	EE_uwEEBattCycCnt, 				//	196 预留
	EE_uwEEBattAhRealShow, 				//	197 预留
	EE_uwEESOCSmoothEn, 				//	198 预留
	EE_uwEERsvd104, 				//	199 预留
	EE_uwEERsvd105, 				//	200 预留
	EE_uwEERsvd106, 				//	201 预留
	EE_uwEERsvd107, 				//	202 预留
	EE_uwEERsvd108, 				//	203 预留
	EE_uwEERsvd109, 				//	204 预留
	EE_uwEERsvd110, 				//	205 预留
	EE_uwEERsvd111, 				//	206 预留
	EE_uwEERsvd112, 				//	207 预留
	EE_uwEERsvd113, 				//	208 预留
	EE_uwEERsvd114, 				//	209 预留
	EE_uwEERsvd115, 				//	210 预留
	EE_uwEERsvd116, 				//	211 预留
	EE_uwEERsvd117, 				//	212 预留
	EE_uwEERsvd118, 				//	213 预留
	EE_uwEERsvd119, 				//	214 预留
	EE_uwEERsvd120, 				//	215 预留
	EE_uwEERsvd121, 				//	216 预留
	EE_uwEERsvd122, 				//	217 预留
	EE_uwEERsvd123, 				//	218 预留
	EE_uwEERsvd124, 				//	219 预留
	EE_uwEERsvd125, 				//	220 预留
	EE_uwEERsvd126, 				//	221 预留
	EE_uwEERsvd127, 				//	222 预留
	EE_uwEERsvd128, 				//	223 预留
	EE_uwEEPV1StartVolt,			//	224	PV1启动电压
	EE_uwEEPV2StartVolt,			//	225	PV2启动电压
	EE_uwEEPV1CurrrLimit,			//	226	PV1最大输入电流
	EE_uwEEPV2CurrrLimit,			//	227	PV2最大输入电流
	EE_uwEEPV1PowerLimit,			//	228	PV1最大输入功率
	EE_uwEEPV2PowerLimit,			//	229	PV2最大输入功率
	EE_uwEEMpptMultiPoint,			//	230	多峰扫描
	EE_uwEEPVInputMode,				//	231	PV输入模式
	EE_uwEERsvd137, 				//	232 预留
	EE_uwEERsvd138, 				//	233 预留
	EE_uwEERsvd139, 				//	234 预留
	EE_uwEERsvd140, 				//	235 预留
	EE_uwEERsvd141, 				//	236 预留
	EE_uwEERsvd142, 				//	237 预留
	EE_uwEERsvd143, 				//	238 预留
	EE_uwEERsvd144, 				//	239 预留
	EE_uwEEGridInputRange,			//	240	电网输入范围
	EE_uwEEACOutputRatedPower,		//	241	机器额定功率
	EE_uwEEACOutputRatedVolt,		//	242	额定输出电压
	EE_uwEEACOutputRatedFreq,		//	243	额定输出频率
	EE_uwAutoInvEn,					//	244	开机自动逆变
	EE_uwDCDCOpenEn, 				//	245	DCDC开环使能
	EE_uwEERsvd151, 				//	246 预留
	EE_uwEERsvd152, 				//	247 预留
	EE_uwEEOverTempRestartEn,		//	248	过温重启使能
	EE_uwEEOverLoadRestartEn,		//	249	过载重启使能
	EE_uwEEOverLoadBypassEn,		//	250	过载转旁路使能
	EE_uwEERsvd156, 				//	251 预留
	EE_uwEERsvd157, 				//	252 预留
	EE_uwEERsvd158, 				//	253 预留
	EE_uwEEOnGridAlwayOn, 			//	254 市电常开（闭合）
	EE_uwEEOffGridImmediatelyOff, 	//	255 离网常断（断开）
	EE_uwEEPVPowerRlyOn, 			//	256 开启功率（PV）
	EE_uwEERlySocOn, 				//	257 锂电池模式下用SOC
	EE_uwEERlySocOff, 				//	258 锂电池模式下用SOC
	EE_uwEERlyVoltOn, 				//	259 自定义模式下用电压
	EE_uwEERlyVoltOff, 				//	260 自定义模式下用电压
	EE_uwEEOffGridWaitTime,			//	261	并网转离网等待时间
	EE_uwEEOnGridWaitTime,			//	262	离网转并网等待时间
	EE_uwEEIslandCheckEn,			//	263	主动孤岛检测使能
	EE_uwEERsvd169, 				//	264 预留
	EE_uwEEGridFeedEn,				//	265	馈电使能
	EE_uwEEGridMaxInputPowerLimitEn,//	266	电网最大输入功率限制使能
	EE_uwEEGridCurrLimit,			//	267	市电电流限制
	EE_uwEEGridInputPower,			//	268	市电最大买电功率
	EE_uwEEGridFeedPower,			//	269	市电最大卖电功率
	EE_uwEEGridVoltUpperLimit,		//	270	电网电压上限
	EE_uwEEGridVoltLowerLimit,		//	271	电网电压下限
	EE_uwEERsvd177, 				//	272 预留
	EE_uwEERsvd178, 				//	273 预留
	EE_uwEEZeroExportPower,			//	274 零馈电功率
	EE_uwEEGridPeakShaving,			//	275 电网削峰使能
	EE_uwEEGridPeakShavingPower,	//	276 电网削峰功率
	EE_uwEETurboMode,				//	277	Turbo模式使能
	EE_uwEETouMode,					//	278	Tou模式使能
	EE_uwEECloseGSRlyEn,			//	279	N对地继电器闭合使能
	EE_uwEEGridpowerslope,			//	280	并网功率斜率
	EE_uwEEGridpowerlimitation,		//	281	并网功率限制
	EE_uwPvAutoInvEn,				//	282	单PV无电池开机自动逆变使能,如果有电池此项不生效
	EE_uwEERsvd188, 				//	283 预留
	EE_uwEERsvd189, 				//	284 预留
	EE_uwEERsvd190, 				//	285 预留
	EE_uwEERsvd191, 				//	286 预留
	EE_uwEERsvd192, 				//	287 预留
	EE_uwEERsvd193, 				//	288 预留
	EE_uwEERsvd194, 				//	289 预留
	EE_uwEERsvd195, 				//	290 预留
	EE_uwEERsvd196, 				//	291 预留
	EE_uwEERsvd197, 				//	292 预留
	EE_uwEERsvd198, 				//	293 预留
	EE_uwEERsvd199, 				//	294 预留
	EE_uwEERsvd200, 				//	295 预留
	EE_uwEERsvd201, 				//	296 预留
	EE_uwEERsvd202, 				//	297 预留
	EE_uwEERsvd203, 				//	298 预留
	EE_uwEERsvd204, 				//	299 预留
	EE_uwEERsvd205, 				//	300 预留
	EE_uwEERsvd206, 				//	301 预留
	EE_uwEERsvd207, 				//	302 预留
	EE_uwEERsvd208, 				//	303 预留
	EE_uwEERsvd209, 				//	304 预留
	EE_uwEERsvd210, 				//	305 预留
	EE_uwEERsvd211, 				//	306 预留
	EE_uwEERsvd212, 				//	307 预留
	EE_uwEERsvd213, 				//	308 预留
	EE_uwEERsvd214, 				//	309 预留
	EE_uwEERsvd215, 				//	310 预留
	EE_uwEERsvd216, 				//	311 预留
	EE_uwEERsvd217, 				//	312 预留
	EE_uwEERsvd218, 				//	313 预留
	EE_uwEERsvd219, 				//	314 预留
	EE_uwEERsvd220, 				//	315 预留
	EE_uwEERsvd221, 				//	316 预留
	EE_uwEERsvd222, 				//	317 预留
	EE_uwEERsvd223, 				//	318 预留
	EE_uwEERsvd224, 				//	319 预留
	EE_eSetGenMode, 				//	320 油机模式
	EE_eSetGenInputEn, 				//	321 油机输入使能
	EE_eSetGenInputMaxPower, 		//	322 油机输入最大功率
	EE_eSetGenConnectToGridPortEn, 	//	323 油机接入电网端口使能位
	EE_eSetSmartLoad_OpenPower, 	//	324 智能负载启动功率
	EE_eSetSmartLoad_StartBatVolt, 	//	325 智能负载闭合电池电压点
	EE_eSetSmartLoad_ExitBatVolt, 	//	326 智能负载断开电池电压点
	EE_eSetSmartLoad_StartSOC, 		//	327 智能负载闭合电池SOC点
	EE_eSetSmartLoad_ExitSOC, 		//	328 智能负载断开电池SOC点
	EE_eSetOnGrid_SmartLoadEn, 		//	329 电网正常启用智能负载使能位
	EE_eSetOffGrid_SmartLoadDis, 	//	330 电网异常禁用智能负载使能位
	EE_uwEEDry1ContactMode, 		//	331 干接点1模式
	EE_uwEEDry2ContactMode, 		//	332 干接点2模式
	EE_uwEERsvd238, 				//	333 预留
	EE_uwEERsvd239, 				//	334 预留
	EE_uwEERsvd240, 				//	335 预留
	EE_uwEERsvd241, 				//	336 预留
	EE_uwEERsvd242, 				//	337 预留
	EE_uwEERsvd243, 				//	338 预留
	EE_uwEERsvd244, 				//	339 预留
	EE_uwEERsvd245, 				//	340 预留
	EE_uwEERsvd246, 				//	341 预留
	EE_uwEERsvd247, 				//	342 预留
	EE_uwEERsvd248, 				//	343 预留
	EE_uwEERsvd249, 				//	344 预留
	EE_uwEERsvd250, 				//	345 预留
	EE_uwEERsvd251, 				//	346 预留
	EE_uwEERsvd252, 				//	347 预留
	EE_uwEERsvd253, 				//	348 预留
	EE_uwEERsvd254, 				//	349 预留
	EE_uwEERsvd255, 				//	350 预留
	EE_uwEERsvd256, 				//	351 预留
	EE_uwEERsvd257, 				//	352 预留
	EE_uwEERsvd258, 				//	353 预留
	EE_uwEERsvd259, 				//	354 预留
	EE_uwEERsvd260, 				//	355 预留
	EE_uwEERsvd261, 				//	356 预留
	EE_uwEERsvd262, 				//	357 预留
	EE_uwEERsvd263, 				//	358 预留
	EE_uwEERsvd264, 				//	359 预留
	EE_uwEERsvd265, 				//	360 预留
	EE_uwEERsvd266, 				//	361 预留
	EE_uwEERsvd267, 				//	362 预留
	EE_uwEERsvd268, 				//	363 预留
	EE_uwEERsvd269, 				//	364 预留
	EE_uwEERsvd270, 				//	365 预留
	EE_uwEERsvd271, 				//	366 预留
	EE_uwEERsvd272, 				//	367 预留
	EE_uwEERsvd273, 				//	368 预留
	EE_uwEERsvd274, 				//	369 预留
	EE_uwEERsvd275, 				//	370 预留
	EE_uwEERsvd276, 				//	371 预留
	EE_uwEERsvd277, 				//	372 预留
	EE_uwEERsvd278, 				//	373 预留
	EE_uwEERsvd279, 				//	374 预留
	EE_uwEERsvd280, 				//	375 预留
	EE_uwEERsvd281, 				//	376 预留
	EE_uwEERsvd282, 				//	377 预留
	EE_uwEERsvd283, 				//	378 预留
	EE_uwEERsvd284, 				//	379 预留
	EE_uwEERsvd285, 				//	380 预留
	EE_uwEERsvd286, 				//	381 预留
	EE_uwEERsvd287, 				//	382 预留
	EE_uwEERsvd288, 				//	383 预留
	EE_uwEERsvd289, 				//	384 预留
	EE_uwEERsvd290, 				//	385 预留
	EE_uwEERsvd291, 				//	386 预留
	EE_uwEERsvd292, 				//	387 预留
	EE_uwEERsvd293, 				//	388 预留
	EE_uwEERsvd294, 				//	389 预留
	EE_uwEERsvd295, 				//	390 预留
	EE_uwEERsvd296, 				//	391 预留
	EE_uwEERsvd297, 				//	392 预留
	EE_uwEERsvd298, 				//	393 预留
	EE_uwEERsvd299, 				//	394 预留
	EE_uwEERsvd300, 				//	395 预留
	EE_uwEERsvd301, 				//	396 预留
	EE_uwEERsvd302, 				//	397 预留
	EE_uwEERsvd303, 				//	398 预留
	EE_uwEERsvd304, 				//	399 预留
	EE_uwSetECO_TimeOfUse,			//	400 经济模式使能
	EE_uwSetECO_EffectiveWeek,		//	401 生效星期
	EE_uwSetECO1_GridChargeEnable,	//	402 规则1电网充电使能
	EE_uwSetECO1_GenChargeEnable,	//	403 规则1油机充电使能
	EE_uwSetECO1_StartTime,			//	404 规则1起始时间
	EE_uwSetECO1_StopTime,			//	405 规则1结束时间
	EE_uwSetECO1_Volt,				//	406 规则1目标电压
	EE_uwSetECO1_SOC,				//	407 规则1目标SOC（BMS连接采用）
	EE_uwSetECO1_Power,				//	408 规则1放电功率
	EE_uwSetECO1_WorkModeSet,		//	409 规则1工作模式设定
	EE_uwSetECO2_GridChargeEnable,	//	410 规则2电网充电使能
	EE_uwSetECO2_GenChargeEnable,	//	411 规则2油机充电使能
	EE_uwSetECO2_StartTime,			//	412 规则2起始时间
	EE_uwSetECO2_StopTime,			//	413 规则2结束时间
	EE_uwSetECO2_Volt,				//	414 规则2目标电压
	EE_uwSetECO2_SOC,				//	415 规则2目标SOC（BMS连接采用）
	EE_uwSetECO2_Power,				//	416 规则2放电功率
	EE_uwSetECO2_WorkModeSet,		//	417 规则2工作模式设定
	EE_uwSetECO3_GridChargeEnable,	//	418 规则3电网充电使能
	EE_uwSetECO3_GenChargeEnable,	//	419 规则3油机充电使能
	EE_uwSetECO3_StartTime,			//	420 规则3起始时间
	EE_uwSetECO3_StopTime,			//	421 规则3结束时间
	EE_uwSetECO3_Volt,				//	422 规则3目标电压
	EE_uwSetECO3_SOC,				//	423 规则3目标SOC（BMS连接采用）
	EE_uwSetECO3_Power,				//	424 规则3放电功率
	EE_uwSetECO3_WorkModeSet,		//	425 规则3工作模式设定
	EE_uwSetECO4_GridChargeEnable,	//	426 规则4电网充电使能
	EE_uwSetECO4_GenChargeEnable,	//	427 规则4油机充电使能
	EE_uwSetECO4_StartTime,			//	428 规则4起始时间
	EE_uwSetECO4_StopTime,			//	429 规则4结束时间
	EE_uwSetECO4_Volt,				//	430 规则4目标电压
	EE_uwSetECO4_SOC,				//	431 规则4目标SOC（BMS连接采用）
	EE_uwSetECO4_Power,				//	432 规则4放电功率
	EE_uwSetECO4_WorkModeSet,		//	433 规则4工作模式设定
	EE_uwSetECO5_GridChargeEnable,	//	434 规则5电网充电使能
	EE_uwSetECO5_GenChargeEnable,	//	435 规则5油机充电使能
	EE_uwSetECO5_StartTime,			//	436 规则5起始时间
	EE_uwSetECO5_StopTime,			//	437 规则5结束时间
	EE_uwSetECO5_Volt,				//	438 规则5目标电压
	EE_uwSetECO5_SOC,				//	439 规则5目标SOC（BMS连接采用）
	EE_uwSetECO5_Power,				//	440 规则5放电功率
	EE_uwSetECO5_WorkModeSet,		//	441 规则5工作模式设定
	EE_uwSetECO6_GridChargeEnable,	//	442 规则6电网充电使能
	EE_uwSetECO6_GenChargeEnable,	//	443 规则6油机充电使能
	EE_uwSetECO6_StartTime,			//	444 规则6起始时间
	EE_uwSetECO6_StopTime,			//	445 规则6结束时间
	EE_uwSetECO6_Volt,				//	446 规则6目标电压
	EE_uwSetECO6_SOC,				//	447 规则6目标SOC（BMS连接采用）
	EE_uwSetECO6_Power,				//	448 规则6放电功率
	EE_uwSetECO6_WorkModeSet,		//	449 规则6工作模式设定
	EE_uwSetECO7_GridChargeEnable,	//	450 规则7电网充电使能
	EE_uwSetECO7_GenChargeEnable,	//	451 规则7油机充电使能
	EE_uwSetECO7_StartTime,			//	452 规则7起始时间
	EE_uwSetECO7_StopTime,			//	453 规则7结束时间
	EE_uwSetECO7_Volt,				//	454 规则7目标电压
	EE_uwSetECO7_SOC,				//	455 规则7目标SOC（BMS连接采用）
	EE_uwSetECO7_Power,				//	456 规则7放电功率
	EE_uwSetECO7_WorkModeSet,		//	457 规则7工作模式设定
	EE_uwSetECO8_GridChargeEnable,	//	458 规则8电网充电使能
	EE_uwSetECO8_GenChargeEnable,	//	459 规则8油机充电使能
	EE_uwSetECO8_StartTime,			//	460 规则8起始时间
	EE_uwSetECO8_StopTime,			//	461 规则8结束时间
	EE_uwSetECO8_Volt,				//	462 规则8目标电压
	EE_uwSetECO8_SOC,				//	463 规则8目标SOC（BMS连接采用）
	EE_uwSetECO8_Power,				//	464 规则8放电功率
	EE_uwSetECO8_WorkModeSet,		//	465 规则8工作模式设定
	EE_uwEERsvd371, 				//	466 预留
	EE_uwEERsvd372, 				//	467 预留
	EE_uwATE_UpdateFW,				//	468 升级固件
	EE_uwATE_SafetyCode, 			//	469 安规设置
	EE_uwATE_ISOsetting,			//	470 绝缘阻抗设置
	EE_uwATE_EleMeterProc,			//	471 电表协议选择
	EE_uwATE_ExCommBps,				//	472 Wifi通讯地址和波特率
	EE_uwATE_EleMeterBps_Parity, 	//	473 与电表通讯波特率和校验位
	EE_uwATE_EleMeterAddr,			//	474 与电表通讯地址
	EE_uwATE_EleMeterWREn,			//	475 电表使能写，禁止读
	EE_uwATE_EleMeterDataRegAddr,	//	476 电表Modbus地址
	EE_uwATE_EleMeterData,			//	477 电表数据
	EE_uwATE_485CommBps, 			//	478 485通讯地址和波特率
	EE_uwMenuRtnDftPageEn,			//	479 菜单回退默认界面使能位
	EE_uwSetLCDBacklight,			//	480 LCD背光
	EE_uwSetBuzzerBeep,				//	481 蜂鸣器
	EE_uwEERsvd387, 				//	482 预留
	EE_uwEERsvd388, 				//	483 预留
	EE_uwEERsvd389, 				//	484 预留
	EE_uwEERsvd390, 				//	485 预留
	EE_uwEERsvd391, 				//	486 预留
	EE_uwEERsvd392, 				//	487 预留
	EE_uwEERsvd393, 				//	488 预留
	EE_uwEERsvd394, 				//	489 预留
	EE_uwEERsvd395, 				//	490 预留
	EE_uwEERsvd396, 				//	491 预留
	EE_uwEERsvd397, 				//	492 预留
	EE_uwEERsvd398, 				//	493 预留
	EE_uwEERsvd399, 				//	494 预留
	EE_uwEERsvd400, 				//	495 预留
	EE_uwEERsvd401, 				//	496 预留
	EE_uwEERsvd402, 				//	497 预留
	EE_uwEERsvd403, 				//	498 预留
	EE_uwEERsvd404, 				//	499 预留
	EE_uwEERsvd405, 				//	500 预留
	EE_uwEERsvd406, 				//	501 预留
	EE_uwEERsvd407, 				//	502 预留
	EE_uwEERsvd408, 				//	503 预留
	EE_uwEERsvd409, 				//	504 预留
	EE_uwEERsvd410, 				//	505 预留
	EE_uwEERsvd411, 				//	506 预留
	EE_uwEERsvd412, 				//	507 预留
	EE_uwEERsvd413, 				//	508 预留
	EE_uwEERsvd414, 				//	509 预留
	EE_uwEERsvd415, 				//	510 预留
	EE_uwEERsvd416, 				//	511 预留
	EE_uwEERsvd417, 				//	512 预留
	EE_uwEERsvd418, 				//	513 预留
	EE_uwEERsvd419, 				//	514 预留
	EE_uwEERsvd420, 				//	515 预留
	EE_uwSetBmsBagAddr,				//	516 电池包地址
	EE_uwSetClearEventLog,			//	517 清除事件记录
	EE_uwSetEventLogFunc,			//	518 事件记录功能
	EE_uwSetFaultLogFunc,			//	519 故障记录功能
	EE_uwSetLogType, 				//	520 Log查询类型
	EE_uwSetLogIndex,				//	521 Log索引
	EE_uwEERsvd427, 				//	522 预留
	EE_uwEERsvd428, 				//	523 预留
	EE_uwEERsvd429, 				//	524 预留
	EE_uwEERsvd430, 				//	525 预留
	EE_uwEERsvd431, 				//	526 预留
	EE_uwEERsvd432, 				//	527 预留
	EE_uwEERsvd433, 				//	528 预留
	EE_uwEERsvd434, 				//	529 预留
	EE_uwEERsvd435, 				//	530 预留
	EE_uwEERsvd436, 				//	531 预留
	EE_uwFlag2,						//	532 EEPROM标志
	EE_uwEECheckCRC2,				//	533 CRC校验

	//EEPROM3
	EE_uwSetGrid1OVValue,			//	534 电网过压1段(%)
	EE_uwSetGrid1OVTime, 			//	535 电网过压1段时间(10ms)
	EE_uwSetGrid2OVValue,			//	536 电网过压2段(%)
	EE_uwSetGrid2OVTime, 			//	537 电网过压2段时间(10ms)
	EE_uwSetGrid3OVValue,			//	538 电网过压3段(%)
	EE_uwSetGrid3OVTime, 			//	539 电网过压3段时间(10ms)
	EE_uwSetGrid1UVValue,			//	540 电网欠压1段(%)
	EE_uwSetGrid1UVTime, 			//	541 电网欠压1段时间(10ms)
	EE_uwSetGrid2UVValue,			//	542 电网欠压2段(%)
	EE_uwSetGrid2UVTime, 			//	543 电网欠压2段时间(10ms)
	EE_uwSetGrid3UVValue,			//	544 电网欠压3段(%)
	EE_uwSetGrid3UVTime, 			//	545 电网欠压3段时间(10ms)
	EE_uwSetGrid1OFValue,			//	546 电网过频1段(0.01Hz)
	EE_uwSetGrid1OFTime, 			//	547 电网过频1段时间(10ms)
	EE_uwSetGrid2OFValue,			//	548 电网过频2段(0.01Hz)
	EE_uwSetGrid2OFTime, 			//	549 电网过频2段时间(10ms)
	EE_uwSetGrid3OFValue,			//	550 电网过频3段(0.01Hz)
	EE_uwSetGrid3OFTime, 			//	551 电网过频3段时间(10ms)
	EE_uwSetGrid1UFValue,			//	552 电网欠频1段(0.01Hz)
	EE_uwSetGrid1UFTime, 			//	553 电网欠频1段时间(10ms)
	EE_uwSetGrid2UFValue,			//	554 电网欠频2段(0.01Hz)
	EE_uwSetGrid2UFTime, 			//	555 电网欠频2段时间(10ms)
	EE_uwSetGrid3UFValue,			//	556 电网欠频3段(0.01Hz)
	EE_uwSetGrid3UFTime, 			//	557 电网欠频3段时间(10ms)
	EE_uwSetRsvd558, 				//	558 预留
	EE_uwSetRsvd559, 				//	559 预留
	EE_uwSetRsvd560, 				//	560 预留
	EE_uwSetRsvd561, 				//	561 预留
	EE_uwSetRsvd562, 				//	562 预留
	EE_uwSetRsvd563, 				//	563 预留
	EE_uwFlag3,						//	564 EEPROM标志
	EE_uwEECheckCRC3,				//	565 CRC校验

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
	uwATE_ResetSystem,			// 16 	复位重启
	uwATE_AgingMode,			// 17 	老化模式
	uwATE_AgingBattVolt,		// 18 	老化电池启动电压
	uwATE_AgingBattCurr,		// 19 	老化电池放电电流
	uwATE_AgingPVPower,			// 20 	老化最大PV功率
	uwATE_AgingInvPower,		// 21 	老化最大逆变功率
	uwATE_MPPTVoltCntl,			// 22 	MPPT电压点控制
	uwATE_E_totalClr, 			// 23 	发电量发电时间清零设置
	eATEComRsvd25,				// 24	预留
	eATEComRsvd26,				// 25	预留
	eATEComRsvd27,				// 26	预留
	eATEComRsvd28,				// 27	预留
	eATEComRsvd29,				// 28	预留
	eATEComRsvd30,				// 29	预留
	eATEComRsvd31,				// 30	预留
	eATEComRsvd32,				// 31	预留
	eATEComRsvd33,				// 32	预留
	eATEComRsvd34,				// 33	预留
	eATEComBatteyAddr,			// 34	电池包地址(GD设置)
	eATEComBattey2Addr,			// 35	电池包地址2(GD设置)
	eATEComRsvd37,				// 36	预留
	eATEComRsvd38,				// 37	预留
	eATEComRsvd39,				// 38	预留
	eATEComRsvd40,				// 39	预留
	eATEComRsvd41,				// 40	预留
	eATEComRsvd42,				// 41	预留
	eATEComRsvd43,				// 42	预留
	eATEComRsvd44,				// 43	预留
	eATEComRsvd45,				// 44	预留
	eATEPV1VoltAdj0,			// 45	PV1电压校准阶段0
	eATEPV1VoltAdj1,			// 46	PV1电压校准阶段1
	eATEPV1VoltAdj2,			// 47	PV1电压校准阶段2
	eATEPV1VoltAdj,				// 48	PV1电压单点校准
	eATEComRsvd50,				// 49	预留
	eATEComRsvd51,				// 50	预留
	eATEComRsvd52,				// 51	预留
	eATEComRsvd53,				// 52	预留
	eATEPV1BatCurrAdj0,			// 53	PV1电流校准阶段0
	eATEPV1BatCurrAdj1,			// 54	PV1电流校准阶段1
	eATEPV1BatCurrAdj2,			// 55	PV1电流校准阶段2
	eATEPV1BatCurrAdj,			// 56	PV1电流单点校准
	eATEComRsvd58,				// 57	预留
	eATEComRsvd59,				// 58	预留
	eATEComRsvd60,				// 59	预留
	eATEComRsvd61,				// 60	预留
	eATEBatVoltAdj0,			// 61	电池电压校准阶段0
	eATEBatVoltAdj1,			// 62	电池电压校准阶段1
	eATEBatVoltAdj2,			// 63	电池电压校准阶段2
	eATEBatVoltAdj,				// 64	电池电压单点校准
	eATEBatCurrAdj0,			// 65	电池电流校准阶段0
	eATEBatCurrAdj1,			// 66	电池电流校准阶段1
	eATEBatCurrAdj2,			// 67	电池电流校准阶段2
	eATEBatCurrAdj,				// 68	电池电流单点校准
	eATEGrid_Volt0,				// 69	电网电压校准阶段0
	eATEGrid_Volt1,				// 70	电网电压校准阶段1
	eATEGrid_Volt,				// 71	电网电压校准阶段
	eATEGrid_Curr0,				// 72	电网电流校准阶段0
	eATEGrid_Curr1,				// 73	电网电流校准阶段1
	eATEGrid_Curr,				// 74	电网电流校准阶段
	eATEINV_Volt0,				// 75	逆变电压校准阶段0
	eATEINV_Volt1,				// 76	逆变电压校准阶段1
	eATEINV_Volt,				// 77	逆变电压校准阶段
	eATEINV_Curr0,				// 78	逆变电流校准阶段0
	eATEINV_Curr1,				// 79	逆变电流校准阶段1
	eATEINV_Curr,				// 80	逆变电流校准阶段
	eATELoad_Curr0,				// 81	负载电流校准阶段0
	eATELoad_Curr1,				// 82	负载电流校准阶段1
	eATELoad_curr,				// 83	负载电流校准阶段
	eATEOut_Volt0,				// 84	输出电压校准阶段0
	eATEOut_Volt1,				// 85	输出电压校准阶段1
	eATEOut_Volt,				// 86	输出电压校准阶段
	eATEPos_Bus_Volt0,			// 87	BUS电压校准阶段0
	eATEPos_Bus_Volt1,			// 88	BUS电压校准阶段1
	eATEPos_Bus_Volt,			// 89	BUS电压校准阶段
	eATEPos_Bus_Curr0,			// 90	BUS电流校准阶段0
	eATEPos_Bus_Curr1,			// 91	BUS电流校准阶段1
	eATEPos_Bus_Curr,			// 92	BUS电压校准阶段
	eATEComRsvd94,				// 93	预留
	eATEComRsvd95,				// 94	预留
	eATEComRsvd96,				// 95	预留

	ATE_AddrEnd,			
	ATE_Len = ATE_AddrEnd - ATE_AddrStart

};

enum WIFI_DATA_ID
{
	WifiAddrStart = 0,
	uwIotType = WifiAddrStart,			// 0X5100	区分4G/WiFi
	uwIotVersion,		// 0X5101	iot 版本号
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

	uwIotBleConn,		// 0X5116	蓝牙设备连接数
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

INT16U g_uwClearEventLog = 0;
INT16U g_uwEventLogFunc = 0;
INT16U g_uwSetFaultLogFunc = 0;
INT16U g_uwSetLogType = 0;
INT16U g_uwSetLogIndex = 0;

INT16U g_uwATE_UpdateFW = 0;
INT16U g_uwATE_ExCommBps = 0;
INT16U g_uwATE_485CommBps = 0;

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
	
	wEepromLen1 = cEepromTotalLength1 >> 1;	// 192
	wEepromLen2 = cEepromTotalLength2 >> 1;	// 876
	wEepromLen3 = cEepromTotalLength3 >> 1;	// 64

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
		//EEPROM1
		case EE_uwMachCode:
			if(WrData <= 9999)
			{
				sSetEEMachineCode(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SN1:
			if(WrData <= 9999)
			{
				sSetEE_SN1(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SN2:
			if(WrData <= 9999)
			{
				sSetEE_SN2(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SN3:
			if(WrData <= 9999)
			{
				sSetEE_SN3(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SN4:
			if(WrData <= 9999)
			{
				sSetEE_SN4(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SN5:
			if(WrData <= 9999)
			{
				sSetEE_SN5(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_SNLen:
			if(WrData <= 18)
			{
				sSetEE_SNLen(WrData);
				DoEEPROM1Save = true;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case EE_uwEE_DispHwVer:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEE_CtrlHwVer:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEE_PowerHwVer:
			ret = cErr_ParUnValid;
		break;
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
		case EE_uwEEGenVoltAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGenVoltBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGenCurrAdj:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGenCurrBias:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd5:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd6:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd7:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd8:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd9:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd10:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd11:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd12:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd13:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd14:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd15:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd16:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd17:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd18:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd19:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd20:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd21:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd22:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd23:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd24:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd25:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd26:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd27:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd28:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd29:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd30:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd31:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd32:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd33:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd34:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd35:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd36:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd37:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd38:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd39:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd40:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd41:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd42:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd43:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd44:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd45:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd46:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd47:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd48:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd49:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd50:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd51:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd52:
			ret = cErr_ParUnValid;
		break;
		case EE_uwFlag1:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEECheckCRC1:
			ret = cErr_ParUnValid;
		break;

		//EEPROM2
		case EE_uwEEParallel:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEParaEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEParalleltMasterSlaver:
			if((WrData == 0)||(WrData == 1))
			{
				sSetEEMasterSlaver(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEParallelPhase:
			if((WrData == 0)||(WrData == 1)||(WrData == 2))
			{
				sSetEEParallelPhase(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEParallelIID:
			if((WrData <= 16) && (WrData >= 1))
			{
				sSetEEParallelIID(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetSystemOutputMode:
			if(WrData <= 6)	
			{
				sSetEESystemOutputMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEWorkMode:
			if(WrData <= 2)
			{
				sSetEEWorkMode(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEFanWorkMode:
			if(WrData <= cFanModeMax)	
			{
				sSetEEFanWorkMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPowerConversion:	// 功率折算使能
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPowerConversion(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPowerSaveMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPowerSaveMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEENoBatMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEENoBatMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEELogoEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEELogoEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEAdcBiasAdj:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAdcBiasAdj(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_eSetLeakCurrProtectEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetLeakCurrProtectValue:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetISOCheckEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetISOCheckValue:
			ret = cErr_ParUnValid;
		break;
		//Res17~32
		case EE_uwEERsvd17:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd18:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd19:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd20:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd21:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd22:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd23:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd24:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd25:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd26:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd27:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd28:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd29:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd30:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd31:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd32:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatType:
			if((WrData == 2)||(WrData == 3))	//2: 用户自定义 (User defined)3: 锂电池 (Lithium)
			{
				sSetEEBatType(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatSeriesNum:
//			if(WrData <= 2)	
//			{
//				sSetEEBatSeriesNum(WrData);
//				DoEEPROM2Save = true;
//			}
//		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatActivate:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatActivateEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatCapacity:
			if(WrData <= 65535)	
			{
				sSetEEBatCapacity(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEELithiumMode:
			if(WrData <= 100)
			{
				sSetEELithiumMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd38:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatMaxChgCurr:
			if(WrData <= (uwGetSettingMaxChgCurr()))
			{
				sSetEEBatMaxChgCurr(WrData);
				if(suwGetEEGridChgBatCurr() > WrData)	// 设置的总充电电流比当前的市电充电电流小时更新一下市电电流
				{
					sSetEEGridChgBatCurr(WrData);
				}
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatMaxDcgCurr:
			if(WrData <= (uwGetSettingMaxDchgCurr()))
			{
				sSetEEBatMaxDcgCurr(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatVoltage:
			if((WrData == cBatVoltReal6V4))//||(WrData == cBatVoltReal24V))
			{
				sSetEEBatVoltage(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd42:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridChargeEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEGridChargeEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridMaxChargeCurr:
			if(WrData <= (uwGetSettingMaxACChgCurr()) && WrData <= suwGetEEBatMaxChgCurr())
			{
				sSetEEGridChgBatCurr(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridStartChargeVolt:
			if((WrData >= cBatVoltReal10V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEOnGridBatAutoStartChgVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridEndChargeVolt:
			if((WrData >= cBatVoltReal10V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEOnGridBatExitAutoChgVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridStartChargeSOC:
			if(WrData <= 100)	
			{
				sSetEEOnGridBatAutoStartChgSOC(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridEndChargeSOC:
			if(WrData <= 100)	
			{
				sSetEEOnGridBatExitAutoChgSOC(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd49:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGenChargeEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEGenChargeEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGenMaxChargeCurr:
			ret = cErr_ParUnValid; 
		break;
		case EE_uwEEGenStartChargeVolt:
			ret = cErr_ParUnValid; 
		break;
		case EE_uwEEGenEndChargeVolt:
			ret = cErr_ParUnValid; 
		break;
		case EE_uwEEGenStartChargeSOC:
			if(WrData <= 100)	
			{
				sSetEEGenStartChargeSOC(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGenEndChargeSOC:
			if(WrData <= 100)	
			{
				sSetEEGenEndChargeSOC(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd56:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetBatConstVolt:
			if((WrData >= cBatVoltReal2V8 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal4V * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatConstVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatFloatVolt:
			if((WrData >= cBatVoltReal2V8 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V65 * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatFloatVolt(WrData);
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEShutdownSOC:
			if(WrData <= 100)
			{
				sSetEEBatLowShutDownSOC(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEShutdownVolt:
			if((WrData >= cBatVoltReal2V50 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 8.5V, max 13V
			{
				sSetEEBatLowShutDownVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatRestartOutSOC:
			if(WrData <= 100)
			{
				sSetEEBatACRestartSOC(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatRestartOutVolt:
			if((WrData >= cBatVoltReal2V50 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 10V, max 15V
			{
				sSetEEBatACRestartVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEELowBattSOC:
			if(WrData <= 100)
			{
				sSetEEBatLowAlarmSOC(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEELowBattVolt:
			if((WrData >= cBatVoltReal2V50 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 8.5V, max 13V
			{
				sSetEEBatLowAlarmVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd66:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd67:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBattResistance:
			if(WrData <= 200)
			{
				sSetEEBattResistance(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatVoltOverShut:
			if((WrData >= cBatVoltReal2V50 * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal3V75 * uwGetBatSerialPcs())) // min 12V, max 15V
			{
				sSetEEBatVoltOverShut(WrData);
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetBatTempCalibration:
			if(WrData <= 65535)
			{
				sSetBatTempCalibration(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd74:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd75:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatEqEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatEqEn(WrData);
				DoEEPROM2Save = true;
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
				sSetEEBatEqVolt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqTime:
			if(WrData <= 900)	//min
			{
				sSetEEBatEqTime(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqTimeout:
			if(WrData <= 900)	//min
			{
				sSetEEBatEqTimeout(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqInterval:
			if(WrData <= 900)	//min
			{
				sSetEEBatEqInterval(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatEqActImd:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatEqActImd(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd82:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd83:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBatLowVoltDerateEnable:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatLowVoltDerateEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBatPowerOutEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBatPowerOutEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEBMSErrStopEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEBMSErrStopEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEESOCDisplayEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEESOCDisplayEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		//Res88~128
		case EE_uwEERsvd88:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd89:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd90:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd91:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd92:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd93:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd94:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd95:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd96:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEBattAhReal:				//电池剩余容量
		{
			if(WrData <= 3140)	// 0.1AH
			{
				sSetEEBattAhReal(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEBattAhMax:				// 电池最大容量
		{
			if(WrData <= 3140)	// 0.1AH
			{
				sSetEEBattAhMax(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEBattFullCnt:			// 电池充满次数
		{
			if(WrData <= 9999)
			{
				sSetEEBattFullCnt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEBattEmptyCnt:			// 电池放空次数
		{
			if(WrData <= 9999)
			{
				sSetEEBattEmptyCnt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEBattCycCnt:			// 电池循环次数
		{
			if(WrData <= 9999)
			{
				sSetEEBattCycCnt(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEBattAhRealShow:		// 电池显示剩余容量
		{
			if(WrData <= 3140)
			{
				sSetEEBattAhRealShow(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEESOCSmoothEn:		// SOC平滑使能
		{
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEESOCSmoothEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEERsvd104:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd105:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd106:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd107:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd108:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd109:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd110:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd111:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd112:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd113:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd114:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd115:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd116:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd117:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd118:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd119:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd120:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd121:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd122:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd123:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd124:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd125:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd126:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd127:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd128:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1StartVolt:
			if(WrData <= uwGetMpptPvVoltMax())
			{
				sSetEEPV1StartVolt(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPV2StartVolt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1CurrrLimit:
			if(WrData <= 2000)
			{
				sSetEEPV1CurrrLimit(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPV2CurrrLimit:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEPV1PowerLimit:
			if(WrData <= 650)//uwGetPvPowerMax())	
			{
				sSetEEPV1PowerLimit(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPV2PowerLimit:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEMpptMultiPoint:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEMpptMultiPoint(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPVInputMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPVInputMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		//Res137~144
		case EE_uwEERsvd137:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd138:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd139:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd140:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd141:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd142:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd143:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd144:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridInputRange:
			if((WrData == cAPL) || (WrData == cUPS) || (WrData == cGEN))
			{
				sSetEEGridInputRange(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEACOutputRatedPower:
			if(WrData <= ((INT16U)uwGetInvWattMax()))
			{
				sSetEEACOutputRatedPower(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEACOutputRatedVolt:
			if(uwGetModelLV())
			{
				if((WrData == cAcVoltReal110V)||(WrData == cAcVoltReal115V)||(WrData == cAcVoltReal120V)||(WrData == cAcVoltReal127V))
				{
					sSetEEACOutputRatedVolt(WrData);
					sInvWattResCal();
					DoEEPROM2Save = true;
				}
				else 
				{ 
					ret = cErr_ParUnValid; 
				}
			}
			else
			{
				if((WrData == cAcVoltReal220V)||(WrData == cAcVoltReal230V)||(WrData == cAcVoltReal240V))
				{
					sSetEEACOutputRatedVolt(WrData);
					sInvWattResCal();
					DoEEPROM2Save = true;
				}
				else 
				{ 
					ret = cErr_ParUnValid; 
				}
			}
		break;
		case EE_uwEEACOutputRatedFreq:
			// 0：cFreq50hzConst
			// 2：cFreq60hzConst	
			if((WrData == 0)||(WrData == 1))
			{
				sSetEEACOutputRatedFreq(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			} 
		break;
		case EE_uwAutoInvEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAutoInvEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwDCDCOpenEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEDCDCOpenLoopEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd151:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd152:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOverTempRestartEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverTempRestartEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEOverLoadRestartEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverLoadRestartEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEOverLoadBypassEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOverLoadBypassEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd156:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd157:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd158:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEOnGridAlwayOn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOnGridAlwayOn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEOffGridImmediatelyOff:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEOffGridImmediatelyOff(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEPVPowerRlyOn:
			if(WrData <= 6400)
			{
				sSetEEPVPowerRlyOn(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERlySocOn:
			if(WrData <= 100)
			{
				sSetEERlySocOn(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERlySocOff:
			if(WrData <= 100)
			{
				sSetEERlySocOff(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERlyVoltOn:
			if((WrData >= cBatVoltReal11V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 11V, max 15V
			{
				sSetEERlyVoltOn(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERlyVoltOff:
			if((WrData >= cBatVoltReal11V * uwGetBatSerialPcs())\
				&& (WrData <= cBatVoltReal15V * uwGetBatSerialPcs())) // min 11V, max 15V
			{
				sSetEERlyVoltOff(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEOffGridWaitTime:
			if(WrData <= 60000)					// ms
			{
				sSetEEOffGridWaitTime(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEOnGridWaitTime:
			if(WrData <= 60000)					// ms
			{
				sSetEEOnGridWaitTime(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEIslandCheckEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEAnti_IslandProtectEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEERsvd169:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEGridFeedEn:
		{
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEFeedEnable(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridMaxInputPowerLimitEn:
		{
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEGridMaxInputPowerLimitEn(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridCurrLimit:
		{
			if(WrData <= 1000)//uwGetGridInputCurrMax())
			{
				sSetEEGridCurrLimit(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridInputPower:
		{
			if(WrData <= 1000)//((INT16U)uwGetGridInputWattMax()))
			{
				sSetEEGridInputPower(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridFeedPower:
		{
			if(WrData <= ((INT16U)uwGetInvWattMax() + 200)) // -200W ~ 3200W
			{
				sSetEEMaxFeedPower(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridVoltUpperLimit:
		{
			if(WrData <= (cAcVoltReal300V) && (WrData >= (cAcVoltReal240V))) 
			{
				sSetEEGridVoltUpperLimit(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEEGridVoltLowerLimit:
		{
			if(WrData <= (cAcVoltReal220V) && (WrData >= (cAcVoltReal90V)))
			{
				sSeEEGridVoltLowerLimit(WrData);
				DoEEPROM2Save = true;
			}
			else 
			{ 
				ret = cErr_ParUnValid; 
			}
		}
		break;
		case EE_uwEERsvd177:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd178:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEZeroExportPower:
			if(WrData <= 100)
			{
				sSetEEZeroExportPower(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridPeakShaving:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEGridPeakShavingEnable(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridPeakShavingPower:
			if(WrData <= 7500)
			{
				sSetEEGridPeakShavingPower(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEETurboMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEETurboMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEETouMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEETouMode(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEECloseGSRlyEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEECloseGSRlyEn(WrData);
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridpowerslope:
			if(WrData <= 65535)
			{
				sSetEEGridpowerslope(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEGridpowerlimitation:
			if(WrData <= 1200)
			{
				sSetEEGridpowerlimitation(WrData);
				DoEEPROM2Save = true;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwPvAutoInvEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEPVAutoInvEnable(WrData);
				DoEEPROM2Save = true;
			}
			else
			{
				ret = cErr_ParUnValid; 
			}
		break;
		//Res188~224
		case EE_uwEERsvd188:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd189:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd190:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd191:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd192:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd193:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd194:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd195:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd196:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd197:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd198:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd199:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd200:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd201:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd202:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd203:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd204:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd205:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd206:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd207:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd208:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd209:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd210:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd211:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd212:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd213:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd214:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd215:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd216:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd217:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd218:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd219:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd220:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd221:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd222:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd223:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd224:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetGenMode:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetGenInputEn:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetGenInputMaxPower:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetGenConnectToGridPortEn:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetSmartLoad_OpenPower:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetSmartLoad_StartBatVolt:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetSmartLoad_ExitBatVolt:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetSmartLoad_StartSOC:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetSmartLoad_ExitSOC:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetOnGrid_SmartLoadEn:
			ret = cErr_ParUnValid;
		break;
		case EE_eSetOffGrid_SmartLoadDis:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEEDry1ContactMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEDry1ContactMode(WrData);
				DoEEPROM2Save = true;
			}
			else
			{
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwEEDry2ContactMode:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEDry2ContactMode(WrData);
				DoEEPROM2Save = true;
			}
			else
			{
				ret = cErr_ParUnValid; 
			}
		break;
		//Res238~304
		case EE_uwEERsvd238:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd239:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd240:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd241:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd242:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd243:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd244:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd245:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd246:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd247:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd248:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd249:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd250:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd251:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd252:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd253:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd254:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd255:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd256:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd257:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd258:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd259:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd260:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd261:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd262:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd263:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd264:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd265:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd266:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd267:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd268:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd269:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd270:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd271:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd272:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd273:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd274:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd275:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd276:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd277:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd278:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd279:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd280:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd281:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd282:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd283:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd284:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd285:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd286:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd287:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd288:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd289:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd290:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd291:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd292:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd293:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd294:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd295:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd296:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd297:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd298:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd299:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd300:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd301:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd302:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd303:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd304:
			ret = cErr_ParUnValid;
		break;
		//ECO
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
		case EE_uwSetECO7_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO7_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_GridChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_GenChargeEnable:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_StartTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_StopTime:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_Volt:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_SOC:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_Power:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetECO8_WorkModeSet:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd371:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd372:
			ret = cErr_ParUnValid;
		break;
		//ATE
		case EE_uwATE_UpdateFW:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: 升级模式
			{
//				sSetEEATE_UpdateFW(WrData);
//				DoEEPROM2Save = true;
				g_uwATE_UpdateFW = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
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
			if(WrData <= 65535)
			{
//				sSetEEATE_ExCommBps(WrData);
//				DoEEPROM2Save = true;
				g_uwATE_ExCommBps = WrData;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
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
			if(WrData <= 65535)
			{
//				sSetEEATE_485CommBps(WrData);
//				DoEEPROM2Save = true;
				g_uwATE_485CommBps = WrData;
			}
			else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwMenuRtnDftPageEn:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
				sSetEEMenuRtnDftPageEn(WrData);
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
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
				DoEEPROM2Save = true;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		//Res387~420
		case EE_uwEERsvd387:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd388:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd389:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd390:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd391:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd392:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd393:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd394:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd395:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd396:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd397:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd398:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd399:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd400:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd401:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd402:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd403:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd404:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd405:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd406:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd407:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd408:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd409:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd410:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd411:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd412:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd413:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd414:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd415:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd416:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd417:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd418:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd419:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd420:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetBmsBagAddr:
			{
				 if((1 <= WrData) && (WrData <= 16))// && (sbGetEMSBMSConnect() || swGetPylonCanConnectFlag()))	//BMS通信成功的才可以写入
				{
//					sSetEEBmsBagAddr(WrData);
					g_uwBMSAddr = WrData;
					uwSetBmsDataFlag(cGET_BMSDATA_FLAG_READING);
				}
				else
				{ 
					ret = cErr_ParUnValid; 
				}
			}
		break;
		case EE_uwSetClearEventLog:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: 清除
			{
//				sSetEEClearEventLog(WrData);
//				DoEEPROM2Save = true;
				g_uwClearEventLog = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetEventLogFunc:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
//				sSetEEEventLogFunc(WrData);
//				DoEEPROM2Save = true;
				g_uwEventLogFunc = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetFaultLogFunc:
			if((WrData == 0)||(WrData == 1))	//0：disable, 1: enable
			{
//				sSetEEFaultLogFunc(WrData);
//				DoEEPROM2Save = true;
				g_uwSetFaultLogFunc = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetLogType:
			if((WrData == 0)||(WrData == 1))	//0:Fault, 1: Event
			{
//				sSetEELogType(WrData);
//				DoEEPROM2Save = true;
				g_uwSetLogType = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		case EE_uwSetLogIndex:
			if(WrData <= 9)
			{
//				sSetEELogIndex(WrData);
//				DoEEPROM2Save = true;
				g_uwSetLogIndex = WrData;
			}
		    else
			{ 
				ret = cErr_ParUnValid; 
			}
		break;
		//Res427~436
		case EE_uwEERsvd427:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd428:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd429:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd430:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd431:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd432:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd433:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd434:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd435:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEERsvd436:
			ret = cErr_ParUnValid;
		break;
		case EE_uwFlag2:
			ret = cErr_ParUnValid;
		break;
		case EE_uwEECheckCRC2:
			ret = cErr_ParUnValid;
		break;

		//EEPROM3
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
		case EE_uwSetRsvd558:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd559:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd560:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd561:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd562:
			ret = cErr_ParUnValid;
		break;
		case EE_uwSetRsvd563:
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
		case eATEComFactoryReset:	// 0
		{
			if(WrData == 1)			// 1：EEPROM全部恢复默认值
			{
				sEepromDefaultSave1();
				sEepromDefaultSave2();
				sEepromDefaultSave3();
				OSEventSend(cPrioInterface, eI2CEEpromUserSave);
				OSEventSend(cPrioInterface, eI2CEEpromFacSave);
				OSEventSend(cPrioInterface, eI2CEEpromUser2Save);
				sEepromDataVarRangeChk();	// 初始化机型参数
			}
			else if(WrData == 2)	// 2：恢复出厂设置(除校准参数及法规外)
			{
				sEepromDefaultSave2();
				OSEventSend(cPrioInterface, eI2CEEpromFacSave);
				sEepromDataVarRangeChk();	// 初始化机型参数
			}
			else if(WrData == 3)	// 3：恢复出厂设置(除校准参数外)
			{
				sEepromDefaultSave2();
				sEepromDefaultSave3();
				OSEventSend(cPrioInterface, eI2CEEpromFacSave);
				OSEventSend(cPrioInterface, eI2CEEpromUser2Save);
				sEepromDataVarRangeChk();	// 初始化机型参数
			}
			else if(WrData == 4)	// 4：恢复出厂设置(除法规外)
			{
				sEepromDefaultSave1();
				sEepromDefaultSave2();
				OSEventSend(cPrioInterface, eI2CEEpromUserSave);
				OSEventSend(cPrioInterface, eI2CEEpromFacSave);
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
			// 故障模式下，写1复位故障，重启
			if((WrData == cEnable || WrData == cDisable) && (swGetWorkMode() == cFaultMode))
			{
//				sSetATEFaultClear(WrData);
			}
			else
			{
				ret = cErr_ParUnValid;
			}
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
		case eATEComEPOEnable:			// 11	急停使能
			ret = cErr_UnDataAddr;
		break;
		case eATEComQuickSettings:
			ret = cErr_UnDataAddr;
		break;
		case eATEComInvChgWattSoftStartRate:
		{
			if((WrData <= 60) && (WrData >= 10))
			{
				sSetGridpowerslopeTime(WrData);		// ATE测试设置到10比较合适
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		}
		break;
		case eATEComRsvd14:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd15:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_ResetSystem:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_AgingMode:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_AgingBattVolt:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_AgingBattCurr:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_AgingPVPower:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_AgingInvPower:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_MPPTVoltCntl:
			ret = cErr_UnDataAddr;
		break;
		case uwATE_E_totalClr:
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
		case eATEComRsvd33:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd34:
			ret = cErr_UnDataAddr;
		break;
		case eATEComBatteyAddr:
			ret = cErr_UnDataAddr;
		break;
		case eATEComBattey2Addr:
			ret = cErr_UnDataAddr;
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
		case eATEComRsvd41:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd42:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd43:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd44:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd45:
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
		{
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
		}
		break;
		case eATEComRsvd50:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd51:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd52:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd53:
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
		{
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
		}
		break;
		case eATEComRsvd58:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd59:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd60:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd61:
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
		{
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
		case eATEGrid_Curr0:
		{
			if(WrData == cEnable)
			{
				if(suwGetEEGridCurrAdj() != cEEBatVoltAdjDef)
				{
					sSetEEGridCurrAdj(cEEBatVoltAdjDef);
//					sSetGridCurrAdj(4096);
					DoEEStaticSave = true;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		}
		break;
		case eATEGrid_Curr1:
			{
				//wTempCmd = WrData / 10000;
				wTempData = WrData % 10000;
//				ret = sbGridCurrAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEGrid_Curr:
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
			ret = cErr_UnDataAddr;
		break;
		case eATELoad_Curr1:
			ret = cErr_UnDataAddr;
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
			if(WrData == cEnable)
			{
				if(suwGetEEBUSCurrAdj() != cEEBatVoltAdjDef)
				{
					sSetEEBUSCurrAdj(cEEBatVoltAdjDef);
//					sSetBusCurrAdj(cEEBatVoltAdjDef);
					DoEEStaticSave = true;
				}
			}		
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case eATEPos_Bus_Curr1:
			{
				wTempData = WrData % 10000;
				ret = sbBusCurrAdj(wTempData);
				if(ret == 0)
				{
					DoEEStaticSave = true;
				}
			}
		break;
		case eATEPos_Bus_Curr:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd94:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd95:
			ret = cErr_UnDataAddr;
		break;
		case eATEComRsvd96:
			ret = cErr_UnDataAddr;
		break;

		default:break;
	}
	
	if(DoEEStaticSave != 0)
	{
		sSetEeprom1Mode(cEEPROM_SAVE_ENABLE);
//		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
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
		case uwIotVersion:// 0X5101	iot 版本号
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
		case uwIotBleConn:		// 0X5116	蓝牙设备连接数
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
//		case EMS_ChargeVoltageLimit:
//			swSetEmsDataChargeVoltageLimit(WrData);
//		break;
//		case EMS_DischargeVoltageLimit:
//			swSetEmsDataDischargeVoltageLimit(WrData);
//		break;
//		case EMS_ChargeCurrentLimit:
//			swSetEmsDataChargeCurrentLimit(WrData);
//		break;
//		case EMS_DischargeCurrentLimit:
//			swSetEmsDataDischargeCurrentLimit(WrData);
//		break;
//		case EMS_StatusHigh:
//			swSetEmsDataStatusHigh(WrData);
//		break;
//		case EMS_StatusLow:			
//			swSetEmsDataStatusLow(WrData);
//		break;
//		case EMS_FaultFlagHigh:			
//			swSetEmsDataFaultFlagHigh(WrData);
//		break;
//		case EMS_FaultFlagLow:			
//			swSetEmsDataFaultFlagLow(WrData);
//		break;
//		case EMS_AlarmFlagHigh:			
//			swSetEmsDataAlarmFlagHigh(WrData);
//		break;
//		case EMS_AlarmFlagLow:			
//			swSetEmsDataAlarmFlagLow(WrData);
//		break;
//		case EMS_NoticeFlagHigh:			
//			swSetEmsDataNoticeFlagHigh(WrData);
//		break;
//		case EMS_NoticeFlagLow:			
//			swSetEmsDataNoticeFlagLow(WrData);
//		break;
//		case EMS_TotalCurrent:			
//			swSetEmsDataTotalCurrent(WrData);
//		break;
//		case EMS_TotalVoltage:			
//			swSetEmsDataTotalVoltage(WrData);
//		break;
//		case EMS_TotalVoltageComp:			
//			swSetEmsDataTotalVoltageComp(WrData);
//		break;
//		case EMS_Reservd02:			
//			swSetEmsDataReservd02(WrData);
//		break;
//		case EMS_TotalSOC:			
//			swSetEmsDataTotalSOC(WrData);
//		break;
//		case EMS_TotalSOH:			
//			swSetEmsDataTotalSOH(WrData);
//		break;
//		case EMS_TotalCapacityHigh:			
//			swSetEmsDataTotalCapacityHigh(WrData);
//		break;
//		case EMS_TotalCapacityLow:			
//			swSetEmsDataTotalCapacityLow(WrData);
//		break;
//		case EMS_ParallelNumber:			
//			swSetEmsDataParallelNumber(WrData);
//		break;
//		case EMS_ParallelStatus:			
//			swSetEmsDataParallelStatus(WrData);
//		break;
//		case EMS_SerialNumber:			
//			swSetEmsDataSerialNumber(WrData);
//		break;
//		case EMS_SerialStatus:			
//			swSetEmsDataSerialStatus(WrData);
//		break;
//		case EMS_MaximumCellVoltageNo:			
//			swSetEmsDataMaximumCellVoltageNo(WrData);
//		break;
//		case EMS_MaximumCellVoltage:			
//			swSetEmsDataMaximumCellVoltag(WrData);
//		break;
//		case EMS_MinimumCellVoltageNo:			
//			swSetEmsDataMinimumCellVoltageNo(WrData);
//		break;
//		case EMS_MinimumCellVoltage:			
//			swSetEmsDataMinimumCellVoltage(WrData);
//		break;
//		case EMS_MaximumCellTemperatureNo:			
//			swSetEmsDataMaximumCellTemperatureNo(WrData);
//		break;
//		case EMS_MaximumCellTemperature:			
//			swSetEmsDataMaximumCellTemperature(WrData);
//		break;
//		case EMS_MinimumCellTemperatureNo:			
//			swSetEmsDataMinimumCellTemperatureNo(WrData);
//		break;
//		case EMS_MinimumCellTemperature:			
//			swSetEmsDataMinimumCellTemperature(WrData);	
//		break;
		
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
//		case BMS_INFO_BmsType:
//			swSetBmsInfoType(WrData);
//		break;
//		case BMS_INFO_BmsSubType:
//			swSetBmsInfoSubType(WrData);
//		break;
//		case BMS_INFO_BmsCommProVer:
//			swSetBmsInfoCommProVer(WrData);
//		break;
//		case BMS_INFO_BmsCommInfo:
//			swSetBmsInfoCommInfo(WrData);
//		break;
//		case BMS_INFO_BmsSN1:
//			swSetBmsInfoSerial1(WrData);
//		break;
//		case BMS_INFO_BmsSN2:			
//			swSetBmsInfoSerial2(WrData);
//		break;
//		case BMS_INFO_BmsSN3:			
//			swSetBmsInfoSerial3(WrData);
//		break;
//		case BMS_INFO_BmsSN4:			
//			swSetBmsInfoSerial4(WrData);
//		break;
//		case BMS_INFO_BmsSN5:			
//			swSetBmsInfoSerial5(WrData);
//		break;
//		case BMS_INFO_BmsSNLen:			
//			swSetBmsInfoSNLen(WrData);
//		break;
//		case BMS_INFO_BmsDispSwVer:			
//			swSetBmsInfoDispSwVer(WrData);
//		break;
//		case BMS_INFO_BmsMCU1SwVer:			
//			swSetBmsInfoMCU1SwVer(WrData);
//		break;
//		case BMS_INFO_BmsMCU2SwVer:			
//			swSetBmsInfoMCU2SwVer(WrData);
//		break;
//		case BMS_INFO_BmsDispHwVer:			
//			swSetBmsInfoDispHwVer(WrData);
//		break;
//		case BMS_INFO_BmsCtrlHwVer:			
//			swSetBmsInfoCtrlHwVer(WrData);
//		break;
//		case BMS_INFO_BmsPowerHwVer:			
//			swSetBmsInfoPowerHwVer(WrData);
//		break;
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
//		case BMS_ChargeVoltageLimit:
//			swSetBmsChargeVoltageLimit(WrData);
//		break;
//		case BMS_DischargeVoltageLimit:
//			swSetBmsDischargeVoltageLimit(WrData);
//		break;
//		case BMS_ChargeCurrentLimit:
//			swSetBmsChargeCurrentLimit(WrData);
//		break;
//		case BMS_DischargeCurrentLimit:
//			swSetBmsDischargeCurrentLimit(WrData);
//		break;
//		case BMS_StatusHigh:
//			swSetBmsStatusHigh(WrData);
//		break;
//		case BMS_StatusLow:			
//			swSetBmsStatusLow(WrData);
//		break;
//		case BMS_FaultFlagHigh:			
//			swSetBmsFaultFlagHigh(WrData);
//		break;
//		case BMS_FaultFlagLow:			
//			swSetBmsFaultFlagLow(WrData);
//		break;
//		case BMS_AlarmFlagHigh:			
//			swSetBmsAlarmFlagHigh(WrData);
//		break;
//		case BMS_AlarmFlagLow:			
//			swSetBmsAlarmFlagLow(WrData);
//		break;
//		case BMS_NoticeFlagHigh:			
//			swSetBmsNoticeFlagHigh(WrData);
//		break;
//		case BMS_NoticeFlagLow:			
//			swSetBmsNoticeFlagLow(WrData);
//		break;
//		case BMS_TotalCurrent:			
//			swSetBmsPackCurrent(WrData);
//		break;
//		case BMS_TotalVoltage:			
//			swSetBmsPackVoltage(WrData);
//		break;
//		case BMS_TotalVoltageComp:			
//			swSetBmsPackVoltageReal(WrData);
//		break;
//		case BMS_Reservd02:			
//			swSetBmsReservd2(WrData);
//		break;
//		case BMS_TotalSOC:			
//			swSetBmsSOC(WrData);
//		break;
//		case BMS_TotalSOH:			
//			swSetBmsSOH(WrData);
//		break;
//		case BMS_TotalCapacityHigh:			
//			swSetBmsPackCapacityHigh(WrData);
//		break;
//		case BMS_TotalCapacityLow:			
//			swSetBmsPackCapacityLow(WrData);
//		break;
//		case BMS_ParallelNumber:			
//			swSetBmsParallelNumber(WrData);
//		break;
//		case BMS_ParallelStatus:			
//			swSetBmsParallelStatus(WrData);
//		break;
//		case BMS_SerialNumber:			
//			swSetBmsSerialNumber(WrData);
//		break;
//		case BMS_SerialStatus:			
//			swSetBmsSerialStatus(WrData);
//		break;
//		case BMS_MaximumCellVoltageNo:			
//			swSetBmsMaximumCellVoltageNo(WrData);
//		break;
//		case BMS_MaximumCellVoltage:			
//			swSetBmsMaximumCellVoltage(WrData);
//		break;
//		case BMS_MinimumCellVoltageNo:			
//			swSetBmsMinimumCellVoltageNo(WrData);
//		break;
//		case BMS_MinimumCellVoltage:			
//			swSetBmsMinimumCellVoltage(WrData);
//		break;
//		case BMS_MaximumCellTemperatureNo:			
//			swSetBmsMaximumCellTemperatureNo(WrData);
//		break;
//		case BMS_MaximumCellTemperature:			
//			swSetBmsMaximumCellTemperature(WrData);
//		break;
//		case BMS_MinimumCellTemperatureNo:			
//			swSetBmsMinimumCellTemperatureNo(WrData);
//		break;
//		case BMS_MinimumCellTemperature:			
//			swSetBmsMinimumCellTemperature(WrData);	
//		break;
		
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
			wTemp = sGetCellCurr();
		break;
		case DBG_XXXXXXX06:
			wTemp = swGetSoxAhReal();
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
			wTemp = suwGetEEWorkMode();
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
			wTemp = sOPOverLoadLowvolt(suwGetEEACOutputRatedVolt());//mKEYSPS;//suwGetGridChgBatLowCutFlag();
		break;
		case DBG_XXXXXXX20:
			wTemp = swGetOPLoadLevelCnt();
		break;
		case DBG_XXXXXXX21:
			wTemp = suwGetPv1PWMB();
		break;
		case DBG_XXXXXXX22:
			wTemp = swGetToShutdown();
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
			wTemp = swGetfPDCDCImo();//0;//hoPVRLY;
		break;
		case DBG_XXXXXXX36:			// PV当前电流
			wTemp = swGetPvInCurrNew();//swGetPv1BatCurrNew() * swGetBatVoltNew() / swGetPv1VoltNew();
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
			wTemp = suwGetDCDCConvPWMValue1();
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
			wTemp = sGetGridChgBusVoltFlag();//mPV_FANEN;//swGetCtrlVoltFlag();
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
			wTemp = 0;
		break;
		case DBG_XXXXXXX81:
			wTemp = suwGetDCDCHighPWMDuty();
		break;
		case DBG_XXXXXXX82:
			wTemp = suwGetDCDCLowPWMDuty();
		break;
		case DBG_XXXXXXX83:
			wTemp = sGetCellCurr();
		break;
		case DBG_XXXXXXX84:
			wTemp = swGetSoxAhReal();
		break;
		case DBG_XXXXXXX85:
			wTemp = swGetSoxAhRealShow();
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
			wTemp = suwGetDCDCHighPWMDutyLimit();
		break;
		case DBG_XXXXXXX94:
			wTemp = suwGetDCDCLowPWMDutyLimit();
		break;
		case DBG_XXXXXXX95:
			wTemp = suwGetChgModeFlagEn();
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
				sSetEEWorkMode(WrData);
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
			sSetTrueflag(WrData);
		break;
		case DBG_XXXXXXX20:		
			sSetHighSoftFinish(WrData);
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
				sMPPTParaInit();
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
			if(WrData <= 730)			// 30V
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
			suwSetDCDCConvPWMValue1(WrData);
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
			if(WrData == true)
			{
				mPV_FANENOn;
			}
			else
			{
				mPV_FANENOff;
			};
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
			if(WrData == true)
			{
				mKEYSPSOff;
			}
			else
			{
				mKEY2ONSOn;
			};
		break;
		case DBG_XXXXXXX82:
			if(WrData == true)
			{
				mPV_FANENOn;
			}
			else
			{
				mPV_FANENOff;
			};//g_wRInvDCVoltCntl = WrData;
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
			sSetDCDCHighPWMDutyLimit(WrData);
		break;
		case DBG_XXXXXXX94:
			sSetDCDCLowPWMDutyLimit(WrData);
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

INT16U	sbGetClearEventLog(void)
{
	return g_uwClearEventLog;
}

INT16U	sbGetEventLogFunc(void)
{
	return g_uwEventLogFunc;
}

INT16U	sbGetFaultLogFunc(void)
{
	return g_uwSetFaultLogFunc;
}

INT16U	sbGetLogType(void)
{
	return g_uwSetLogType;
}

INT16U	sbGetLogIndex(void)
{
	return g_uwSetLogIndex;
}

INT16U	sbGetUpdateFW(void)
{
	return g_uwATE_UpdateFW;
}

INT16U	sbGetExCommBps(void)
{
	return g_uwATE_ExCommBps;
}

INT16U	sbGet485CommBps(void)
{
	return g_uwATE_485CommBps;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetCommConnected(INT8U sciid, INT8U bStatus)
{

}

