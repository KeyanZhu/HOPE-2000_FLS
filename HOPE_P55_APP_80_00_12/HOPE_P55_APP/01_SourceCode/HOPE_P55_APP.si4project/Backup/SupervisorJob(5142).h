/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		F28P55X_DEMO
File Name:		SupervisorJob.h
Author:			xiaofeng
Date:			2024.07.12
Description:	None
********************************************************************************/
#ifndef __SUPERVISOR_JOB_H__
#define __SUPERVISOR_JOB_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef	__SUPERVISOR_JOB_C__
#define	SUPERVISOR_JOB
#else
#define	SUPERVISOR_JOB  extern
#endif

#define	cPowerOnMode			0	// 上电模式
#define	cStandbyMode			1	// 待机模式
#define	cBypassMode				2	// 旁路模式
#define	cBatteryMode			3	// 离网模式
#define	cFaultMode				4	// 故障模式
#define	cLineMode				5	// 市电模式
#define	cChgMode				6	// 充电模式
//below macro are used in Line mode
#define	cToBypassMode			12	// 切到旁路模式
#define	cToBatteryMode			13	// 切到电池模式
#define	cToLineMode				15	// 切到电网模式
#define	cToChgMode				16	// 切到充电模式
#define cLineLoss				10	// 


// 故障码
#define cNullFault				0	// 无故障
#define cPVVoltOver				1	// PV过压
#define cSolarInputCurrOver		2	// PV软件过流
#define cPVVoltLow				3	// PV欠压
//#define cSolarPowerAbnormal	5	// PV功率异常
#define cBatVoltOver			7	// 电池过压
//#define cDCDCSoftTimeOut		10	// LLC异常 DCDC软起超时
//#define cDCDCCurrOver			11	// Buck Boost软件过流
//#define cDCDCCTPSenserFault		15	// Buck Boost电流传感器故障1
//#define cDCDCCTNSenserFault		16	// Buck Boost电流传感器故障2
//#define cDCDCAvgCTPSenserFault	15	// Buck Boost电流传感器故障1
//#define cDCDCAvgCTNSenserFault	16	// Buck Boost电流传感器故障2
#define cOverLoad				17	// 过载保护
#define cInvShort				19	// 输出短路
#define cOPCTSenserFault		21	// 输出电流传感器故障
#define cInvVoltLow				22	// 逆变欠压
#define cInvVoltHigh			23	// 逆变过压
#define cInvCurrOver			24	// 逆变过流
#define cInvHWCurrOver			25	// 逆变硬件过流
#define cInvSoftTimeOut			26	// 逆变电压软启动失败
#define cRiNVDCVoltSenserFault	27	// 逆变电压直流分量异常
#define cRiNVDCCurrSenserFault	28	// 逆变电流直流分量异常
#define cINVCTSenserFault		29	// 逆变电流传感器故障 || CT反接
#define cBusVoltUnder			30	// 母线欠压
#define cBusVoltOver			31	// 母线过压
#define cBusSoftTimeOut			33  // 母线软起失败
#define cCircirtTempOver		34	// 散热器1温度保护
#define cInnelTempOver			35	// 散热器2温度保护//环境温度保护
#define cFanLock				37	// 外部风扇异常
//#define cGFCIFault			38	// 漏电流故障
//#define cGFCISenserFault		39	// 漏电流采样错误
//#define cISOChkFault			40	// 绝缘阻抗低
//#define cRelayChkFault		42	// 继电器检测失败

#define cGridVoltLow			52	// 电网欠压
#define cGridVoltHigh			53	// 电网过压
#define cGridFreqLow			54	// 电网欠频
#define cGridFreqHigh			55	// 电网过频


#define cPVShort				4	// PV短路
#define cPVCircirtTempOver		88	// PV温度过高
//#define cBatCircirtTempOver	89	// 电池温度过高
#define cInvCircirtTempOver		80	// 逆变温度过高
//#define cBATINCircuitFault	87	// 电池输入电路故障
#define cBootloadFail			90	// 主DSPBootLoad未烧写


//#define cCanCommFail			43	// 并机CAN通信异常
//#define cParaHOSTLineLoss		44	// 并机主机丢失
//#define cParaSYNLineLoss		45	// 并机同步信号异常
//#define cParaVersionDiff		46	// 并机版本不一致
//#define cParaOPSettingDiff	47	// 并机设置不一致
//#define cOPCurrCircuitFault	48	// 并机安装异常
//#define cInvNegPower			49	// 并机负功率保护
#define cEEPROMFault			50	// EEPROM故障
#define cDSPMCUComFail			51	// 主从CPU通信故障


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
SUPERVISOR_JOB void	sSupervisorJob(void);
//SUPERVISOR_JOB void	sSupervisorJobInit(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
SUPERVISOR_JOB INT16U	swGetWorkMode(void);
SUPERVISOR_JOB INT16U	swGetFaultCode(void);
SUPERVISOR_JOB INT16U	swGetLoadOnSts(void);
SUPERVISOR_JOB INT16U	swGetStayStandby(void);
SUPERVISOR_JOB void 	sFaultRstCntProc(void);
SUPERVISOR_JOB INT16U	swGetAgingStatus(void);



/********************************************************************************
* Input interface Routines														*
********************************************************************************/
SUPERVISOR_JOB void	sSetFaultCode(INT16U uwFaultCode);
SUPERVISOR_JOB void	sSetWorkMode(INT16U uwWorkMode);
SUPERVISOR_JOB void	sSetLoadOnSts(INT16U uwTemp);
SUPERVISOR_JOB void	sSetStayStandby(INT16U uwTemp);
SUPERVISOR_JOB void	sSetAgingStatus(INT16U uwTemp);


#endif	// __SUPERVISOR_JOB_H__

