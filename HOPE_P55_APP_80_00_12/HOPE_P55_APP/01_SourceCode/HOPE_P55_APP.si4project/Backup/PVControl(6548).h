/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __PV_CONTROL_H__
#define __PV_CONTROL_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __PV_CONTROL_C__
#define PV_CONTROL
#else
#define PV_CONTROL  extern
#endif

#define cPVWait			0
#define cPVWork			1
#define cPVSoft			2
#define cPVOpenSoft		3
#define cPVOpen			4

#define cPVDCM			0						
#define cPVCCM			1


#define	mPV1BuckPWM						EPwm5Regs.CMPA.bit.CMPA
#define	mPV1BuckPWMA					EPwm5Regs.CMPA.bit.CMPA
#define	mPV1BuckPWMB					EPwm5Regs.CMPB.bit.CMPB

#define	mDisPV1PWMOut()					EALLOW;\
										EPwm5Regs.TZCTL.bit.TZA = TZ_FORCE_LO;\
										EPwm5Regs.TZFRC.bit.OST=1;\
										EDIS
#define	mEnPV1PWMOut()					EALLOW;\
										EPwm5Regs.TZCLR.bit.OST=1;\
										EDIS

// -------------------------------------Buck	50K
#define	cBuckPeriod						1500					// 50k=150MHz/2/(1500)

#define	cPWM_DEAD_TIME					150						// 150/150MHz=1us
#define	cPWM_FREQ						50000					// 50kHz
#define	cPWM_PERIOD						1500					// 150MHz/2/50kHz/1
#define	cPWM_PERIOD_10					15000					// 150MHz/2/50kHz/1*10
#define	cPWM_DUTY_LIMIT_UP				1425					// 1500*0.95
#define	cPWM_DUTY_LIMIT_DOWN			75						// 1500*0.05
#define	cPWM_DUTY_10_LIMIT_UP			14250					// 1500*95%*10
#define	cPWM_DUTY_10_LIMIT_UP_Q12		((INT32S)14250 * 4096)	// 1500*95%*10*4096
#define	cPWM_DUTY_10_LIMIT_DOWN			750						// 1500*0.05*10
#define	cPWM_DUTY_10_LIMIT_DOWN_Q12		((INT32S)750 * 4096)	// 1500*0.05*10*4096
#define	cPWM_DUTY_SCALE					10

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
PV_CONTROL void		sPvParaInit(void);								// 控制器参数初始化
PV_CONTROL void 	sClrPv1CtrlPara(void);							// 控制器参数复位	
PV_CONTROL void 	sPV1OpenControl(void);							// 开环控制
PV_CONTROL void 	sPV1Control(void);								// 闭环控制


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
PV_CONTROL INT16U	suwGetPV1CtrlSts(void);							// PV控制器状态
PV_CONTROL INT16U	suwGetPV1PWM(void);								// PV BUCK 实际发波占空比
PV_CONTROL INT16U	suwGetPvChgBatVoltRef(void);					// PV充电电池电压参考
PV_CONTROL INT16U	suwGetPvBatChgLimit(void);						// PV控制器充电电流参考	// 不能设置，由模式自动选择
PV_CONTROL INT16U	suwGetSciPvBatChgLimit(void);					// 调试寄存器写入的PV充电目标电流
PV_CONTROL INT16U	suwGetUserPvBatChgLimit(void); 	  				// 用户设置的充电电流
PV_CONTROL INT16U	suwGetPvVoltRef(void);		 	  				// PV电压参考 80V

PV_CONTROL INT16U	suwGetBatVKp1(void);
PV_CONTROL INT16U	suwGetBatVKi1(void);
PV_CONTROL INT16U	suwGetPv1VKp(void);
PV_CONTROL INT16U	suwGetPv1VKi(void);
PV_CONTROL INT16U	suwGetDCDCIKp1(void);
PV_CONTROL INT16U	suwGetDCDCIKi1(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
PV_CONTROL void 	sSetPV1CtrlSts(INT16U uwPV1CtrlSts);			// 控制器状态设置
PV_CONTROL void		sSetPv1PWM(INT16U uwTemp);						// PV BUCK 实际发波占空比
PV_CONTROL void		sSetPvChgBatVoltRef(INT16U uwTemp);				// PV充电电池电压参考
PV_CONTROL void		sSetSciPvBatChgLimit(INT16U uwTemp);			// 调试寄存器写入的PV充电目标电流
PV_CONTROL void		sSetUserPvBatChgLimit(INT16U uwTemp);			// 用户设置的充电电流
PV_CONTROL void		sSetPvVoltRef(INT16U uwTemp);					// PV电压参考 80V

PV_CONTROL void		sSetBatVKp1(INT16U uwTemp);
PV_CONTROL void		sSetBatVKi1(INT16U uwTemp);
PV_CONTROL void		sSetPv1VKp(INT16U uwTemp);
PV_CONTROL void		sSetPv1VKi(INT16U uwTemp);
PV_CONTROL void		sSetDCDCIKp1(INT16U uwTemp);
PV_CONTROL void		sSetDCDCIKi1(INT16U uwTemp);

#endif	// __PV_CONTROL_H__

