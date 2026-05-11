/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __DCDC_CONTROL_H__
#define __DCDC_CONTROL_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"


/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __LLC_CONTROL_C__
#define LLC_CONTROL
#else
#define LLC_CONTROL  extern
#endif

#define cDCDCWait			0
#define cDCDCWork			1
#define cDCDCSoft			2
#define cDCDCOpenSoft		3
#define cDCDCOpen			4


// LLC状态
#define 		mChkDCDCLLCOn()     	g_uwLLCOn
#define 		mDCDCLLCOn() 			g_uwLLCOn = 1
#define 		mDCDCLLCOff() 			g_uwLLCOn = 0


// LLC相关PWM发波寄存器和封波
#define			mDCDCConvPRD12			EPwm3Regs.TBPRD
#define			mDCDCConvPWM1			EPwm3Regs.CMPA.bit.CMPA		// DCDC L
#define			mDCDCConvPWM2			EPwm3Regs.CMPB.bit.CMPB
#define			mDCDCConvPRD34			EPwm4Regs.TBPRD
#define			mDCDCConvPWM3			EPwm4Regs.CMPA.bit.CMPA		// DCDC H
#define			mDCDCConvPWM4			EPwm4Regs.CMPB.bit.CMPB


// AQCSFRC 封波
#define			mEnDCDCForcePWMOut()	EALLOW;\
										EPwm3Regs.AQCSFRC.all = 0x00;\
										EDIS
#define			mDisDCDCForcePWMOut()	EALLOW;\
										EPwm3Regs.AQCSFRC.all = 0x05;\
										EDIS
#define			mEnDCDCHForcePWMOut()	EALLOW;\
										EPwm4Regs.AQCSFRC.all = 0x00;\
										EDIS
#define			mDisDCDCHForcePWMOut()	EALLOW;\
										EPwm4Regs.AQCSFRC.all = 0x05;\
										EDIS

// TZ 封波
#define			mEnDCDCPWMOut()			EALLOW;\
										EPwm3Regs.TZCLR.bit.OST=1;\
										EDIS
#define			mDisDCDCPWMOut()		EALLOW;\
										EPwm3Regs.TZFRC.bit.OST=1;\
										EDIS
#define			mEnDCDCHPWMOut()		EALLOW;\
										EPwm4Regs.TZCLR.bit.OST=1;\
										EDIS
#define			mDisDCDCHPWMOut()		EALLOW;\
										EPwm4Regs.TZFRC.bit.OST=1;\
										EDIS
										
// -------------------------------------LLC		// 100K	
//#define cDCDCPeriod						600 	// 100K = 120MHz/2/(600)	PWM寄存器值	(cCPU_FREQ/2/cDCDCPeriod)
//#define cDCDCConvertPeriod				600		// 100K	600	// 100K = 120MHz/2/(600)
//#define cDCDCConvertPeriodDef			600		// 100K	600	// 100K = 120MHz/2/(600)
//#define cDCDCConvertPeriodMax			600		// 100K	600	// 100K = 120MHz/2/(600)
//#define cDCDCConvertPeriodMax47Pct		282 	// 100K	564	// 100K = 120MHz/2/(600)*47%
//
//#define cDCDCConvertDuty1				6		// 1%
//#define cDCDCConvertDuty2				12		// 2%	
//#define cDCDCConvertDuty3				18		// 3%
//#define cDCDCConvertDuty4				24		// 4%
//#define cDCDCConvertDuty5				30		// 5%
//#define cDCDCConvertDuty6				36		// 6%
//#define cDCDCConvertDuty7				42		// 7%
//#define cDCDCConvertDuty10				60		// 10%
//#define cDCDCConvertDuty11				66		// 11%
//#define cDCDCConvertDuty13				78		// 12%
//#define cDCDCConvertDuty15				90		// 11%
//#define cDCDCConvertDuty17				102		// 17%

// -------------------------------------LLC	 	// 90K
#define cDCDCPeriod						667 	// 90K = 120MHz/2/(1818)	PWM寄存器值
#define cDCDCConvertPeriod				667		// 90K	667	// 90K = 120MHz/2/(667)
#define cDCDCConvertPeriodDef			667		// 90K	667	// 90K = 120MHz/2/(667)
#define cDCDCConvertPeriodMax			667		// 90K	667	// 90K = 120MHz/2/(667)
#define cDCDCConvertPeriodMax47Pct		313		// 90K	313	// 90K = 120MHz/2/(667)*47%
 
#define cDCDCConvertDuty1				7 		// 1%
#define cDCDCConvertDuty2				13		// 2%	
#define cDCDCConvertDuty3				20		// 3%
#define cDCDCConvertDuty4				27		// 4%
#define cDCDCConvertDuty5				33		// 5%
#define cDCDCConvertDuty6				40		// 6%
#define cDCDCConvertDuty7				47		// 7%
#define cDCDCConvertDuty10				67		// 10%
#define cDCDCConvertDuty11				73		// 11%
#define cDCDCConvertDuty12				80		// 12%
#define cDCDCConvertDuty13				87		// 13%
#define cDCDCConvertDuty15				100		// 15%
#define cDCDCConvertDuty16				107		// 16%
#define cDCDCConvertDuty17				113		// 17%

// -------------------------------------LLC		// 50K
//#define cDCDCPeriod						1200 	// 50K = 120MHz/2/(1200)	PWM寄存器值
//#define cDCDCConvertPeriod				1200	// 50K	1200	// 38K = 120MHz/2/(1200)
//#define cDCDCConvertPeriodDef			1200	// 50K	1200	// 38K = 120MHz/2/(1200)
//#define cDCDCConvertPeriodMax			1200	// 50K	1200	// 38K = 120MHz/2/(1200)
//#define cDCDCConvertPeriodMax47Pct		564 	// 50K	564		// 38K = 120MHz/2/(1200)*47%
//
//#define cDCDCConvertDuty1				12		// 1%
//#define cDCDCConvertDuty105				18		// 1.5%
//#define cDCDCConvertDuty2				24		// 2%	
//#define cDCDCConvertDuty3				36		// 3%
//#define cDCDCConvertDuty4				48		// 4%
//#define cDCDCConvertDuty5				60		// 5%
//#define cDCDCConvertDuty6				72		// 6%
//#define cDCDCConvertDuty7				84		// 7%
//#define cDCDCConvertDuty10				120		// 10%
//#define cDCDCConvertDuty11				132		// 11%
//#define cDCDCConvertDuty15				180		// 11%
//#define cDCDCConvertDuty17				204		// 17%

#define cDCDCConvertDutyStart			9//11//5		// 占空比最低14才能软起    	  // LLC起始占空比 
#define cDCDCConvertDutyLimit1			cDCDCConvertDuty10
#define cDCDCConvertDutyLimit2			cDCDCConvertDuty17
#define cDCDCConvPWMDTSetLimit			159//cDCDCConvertDuty7//cDCDCConvertDuty12	// 死区限制

#define	cWait40uSTimeSet				1000


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
LLC_CONTROL void	sDCDCParaInit(void);									// DCDC控制器初始化
LLC_CONTROL void	sClrDCDCCtrlPara(void);									// DCDC控制器参数清零
LLC_CONTROL void	sOpenLLCCtrl(void);										// 开环LLC控制器


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
LLC_CONTROL INT16U	suwGetDCDCCtrlSts(void);								// 获取DCDC控制器状态
LLC_CONTROL INT16U	suwGetLLCCtrlSts(void);									// 获取LLC控制器状态
LLC_CONTROL INT16U	suwGetDCDCConvPWMPeriod(void);							// 获取DCDC驱动实际频率寄存器值
LLC_CONTROL INT16U	suwGetDCDCConvPWMValue(void);							// 获取DCDC占空比实际值
LLC_CONTROL INT16U	suwGetDCDCSoftDutyFinish(void);							// 占空比软起完成标志

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
LLC_CONTROL void	sSetDCDCCtrlSts(INT16U uwDCDCCtrlSts);					// 设置DCDC控制器状态
LLC_CONTROL void	sSetLLCCtrlSts(INT16U uwTemp);							// 直接设置LLC控制状态
LLC_CONTROL void	suwSetDCDCConvPWMValue(INT16U uwTemp);					// 设置LLC占空比


#endif	// __LLC_CONTROL_H__

