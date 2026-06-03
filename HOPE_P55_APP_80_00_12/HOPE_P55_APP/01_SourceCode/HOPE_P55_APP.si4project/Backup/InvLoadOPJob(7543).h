/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INVLOADOP_JOB_H__
#define __INVLOADOP_JOB_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INVLOADOP_JOB_C__
#define INVLOADOP_JOB
#else
#define INVLOADOP_JOB  extern
#endif

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INVLOADOP_JOB void		sInvLoadOPJob(void);
INVLOADOP_JOB void		sInvLoadParaUpdate(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INVLOADOP_JOB INT16U	uwGetInvLoadStkChk(void);

INVLOADOP_JOB INT16S	swGetBusVoltRef(void);
INVLOADOP_JOB INT16S	swGetInvBusVoltRef(void);
INVLOADOP_JOB INT16U	swGetDCDCBusVoltRef(void);
INVLOADOP_JOB INT16S	swGetInvDCVoltRef(void);
INVLOADOP_JOB INT16S	swGetInvDCCurrRef(void);
INVLOADOP_JOB INT16S	swGetInvRMSCtrlVolt(void);
INVLOADOP_JOB INT16S	swGetOPRMSRatedVolt(void);

INVLOADOP_JOB INT16S	swGetOutputVoltCntl(void);

INVLOADOP_JOB INT16U	uwGetOPRMSRatedVolt(void);
INVLOADOP_JOB INT16U	uwGetInvRMSCtrlVolt(void);
INVLOADOP_JOB INT16S	swGetGRIDChgDischgEnDisable(void);


INVLOADOP_JOB INT16U	swGetTurobMode(void);

INVLOADOP_JOB INT16U	suwGetSysPvChgEn(void);


INVLOADOP_JOB INT16S	swGetBatWattRef(void);
INVLOADOP_JOB INT16S	swGetGridWattRef(void);	
INVLOADOP_JOB INT16S	swGetInvCurrTemp(void);	

INVLOADOP_JOB INT16U	swGetPvChgBatCurrRef(void);

INVLOADOP_JOB INT16U	swGetACCurrLimitEn(void);					// AC限流 使能
INVLOADOP_JOB INT16S	swGetACCurrLimit(void);						// AC限流 电流 0.01A
INVLOADOP_JOB INT16S	swGetACPowerLimit(void);					// AC限流 功率 W
INVLOADOP_JOB INT16S	swGetACWattLimit(void);						// AC限流实际功率 W
INVLOADOP_JOB INT16S	swGetACFeedPowerLimit(void);				// 设置的最大馈电功率 W
INVLOADOP_JOB INT16S	swGetROpFeedWattTemp(void);			// 主功率负载量参考 W

INVLOADOP_JOB INT16S	swGetInvFeedWorkMode(void);					// 逆变器能量调度方向(0按照设置自动识别 1充电 2放电)
INVLOADOP_JOB INT16S	swGetGridChgBatCurrRef(void);				// 市电充电电池电流参考
INVLOADOP_JOB INT16S	swGetGridFeedWattRef(void);					// 市电并网放电功率
INVLOADOP_JOB INT16S	swGetInvCtrlPower(void);					// 市电 控制的功率，正充电,负放电
INVLOADOP_JOB INT16S	swGetPvLoadCurrFeedWard(void);				// PV负载电流前馈

INVLOADOP_JOB INT16S	swGetMaxFeedPowerLimit(void);				// 最大并网功率限制(有些模式只允许并最大PV功率)
INVLOADOP_JOB INT16S	swGetGridChgPowerLimitTemp(void);			// 根据市电设置充电电流得到逆变最大允许充电功率
INVLOADOP_JOB INT16S	swGetwRlyChgPowerLimitTemp(void);			// 继电器最大允许功率(只会在逆变充电时出现)
INVLOADOP_JOB INT16S	swGetInvChgPowerLimitTemp(void);			// 市电充电软起至额定功率值
INVLOADOP_JOB INT16S	swGetInvDsgPowerLimitTemp(void);			// 市电放电软起至额定功率值
INVLOADOP_JOB INT16S	swGetInvChgCurrLimitTemp(void); 					// 充电电流软起临时值
INVLOADOP_JOB INT16S	swGetInvFeedCurrLimitTempTemp(void); 				// 放电电流软起临时值

INVLOADOP_JOB INT16S	swGetPvChgBatCurrTemp(void); // PV充电电流临时值

INVLOADOP_JOB INT16S	swGetBatChgPowerLimitTemp(void); // 电池最大充电功率
INVLOADOP_JOB INT16S	swGetBatDsgPowerLimitTemp(void); // 电池最大放电功率
INVLOADOP_JOB INT16S	swGetInvWorSUBGridDir(void); // 负载优先模式下的并网方向

INVLOADOP_JOB INT16S	swGetWattDeratePerTemp(void); 
INVLOADOP_JOB INT16S	swGetWattDeratROpVolt(void);
/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INVLOADOP_JOB void		sInvRMSCtrlVolt(INT16U uwVolt);
INVLOADOP_JOB void		sSetInvRMSCtrlVolt(INT16U uwVolt);
INVLOADOP_JOB void		sSetTurobMode(INT16U uwVolt);
INVLOADOP_JOB void		sSetOPRMSRatedVolt(INT16U uwVolt);
INVLOADOP_JOB void		sSetDCDCBusVoltRef(INT16U uwTemp);

INVLOADOP_JOB void		sSetACCurrLimitEn(INT16U uwTemp);
INVLOADOP_JOB void		sSetACCurrLimit(INT16U uwTemp);
INVLOADOP_JOB void		sSetACPowerLimit(INT16U uwTemp);
INVLOADOP_JOB void		sSetACWattLimit(INT16U uwTemp);

INVLOADOP_JOB void		sSetInvFeedWorkMode(INT16U uwTemp);
INVLOADOP_JOB void		sSetGridChgBatCurrRef(INT16U uwTemp);
INVLOADOP_JOB void		sSetGridFeedWattRef(INT16U uwTemp);
INVLOADOP_JOB void		sSetInvChgCurrSoftStartRate(INT16S uwTemp);
INVLOADOP_JOB void		sSetGridpowerslopeTime(INT16U uwTemp);


#endif	// __INVLOADOP_JOB_H__

