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

// -------------------------------------LLC	 	// 86K
#define cDCDCPeriod						872 	// 88K = 150MHz/2/(852)	PWM寄存器值
#define cDCDCConvertPeriod				872		// 88K	852	// 88K = 140MHz/2/(852)
#define cDCDCConvertPeriodDef			872		// 88K	852	// 88K = 140MHz/2/(852)
#define cDCDCConvertPeriodMax			872		// 88K	852	// 88K = 140MHz/2/(852)
#define cDCDCConvertPeriodMax47Pct		410		// 88K	313	// 88K = 140MHz/2/(852)*47%
 
#define cDCDCConvertDuty1				9 		// 1%
#define cDCDCConvertDuty2				17		// 2%	
#define cDCDCConvertDuty3				26		// 3%
#define cDCDCConvertDuty4				35		// 4%
#define cDCDCConvertDuty5				44		// 5%
#define cDCDCConvertDuty6				52		// 6%
#define cDCDCConvertDuty7				61		// 7%
#define cDCDCConvertDuty10				87		// 10%
#define cDCDCConvertDuty11				96		// 11%
#define cDCDCConvertDuty12				105		// 12%
#define cDCDCConvertDuty13				113		// 13%
#define cDCDCConvertDuty15				131		// 15%
#define cDCDCConvertDuty16				140		// 16%
#define cDCDCConvertDuty17				148		// 17%


#define cDCDCConvertDutyStart			16//9//11//5		// 占空比最低14才能软起    	  // LLC起始占空比
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
LLC_CONTROL INT16U	suwGetDCDCConvPWMValue1(void);
LLC_CONTROL INT16U	suwGetLLCMinDutyTime(void);		
LLC_CONTROL INT16U	suwGetLLCSoftDutyRate(void);		
LLC_CONTROL INT16U	suwGetGridChgBatLowCutFlag(void);		
LLC_CONTROL INT16U	suwGetChgModeFlagEn(void);			
LLC_CONTROL INT16U	suwGetDCDCLowPWMDutyLimit(void);				
LLC_CONTROL INT16U	suwGetDCDCHighPWMDutyLimit(void);			
LLC_CONTROL INT16U	suwGetDCDCHighPWMDuty(void);		
LLC_CONTROL INT16U	suwGetDCDCLowPWMDuty(void);		
LLC_CONTROL INT16U	suwGetTrueflag(void);		

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
LLC_CONTROL void	sSetDCDCCtrlSts(INT16U uwDCDCCtrlSts);					// 设置DCDC控制器状态
LLC_CONTROL void	sSetLLCCtrlSts(INT16U uwTemp);							// 直接设置LLC控制状态
LLC_CONTROL void	suwSetDCDCConvPWMValue(INT16U uwTemp);					// 设置LLC占空比
LLC_CONTROL void	suwSetDCDCConvPWMValue1(INT16U uwTemp);	
LLC_CONTROL void	sSetLLCSoftDutyRate(INT16U uwTemp);		
LLC_CONTROL void	sSetLLCMinDutyTime(INT16U uwTemp);		
LLC_CONTROL void	sSetGridChgBatLowCutFlag(INT16U uwTemp);		
LLC_CONTROL void	sSetChgModeFlagEn(INT16U uwTemp);		
LLC_CONTROL void	sSetDCDCLowPWMDutyLimit(INT16U uwTemp);		
LLC_CONTROL void	sSetDCDCHighPWMDutyLimit(INT16U uwTemp);		
LLC_CONTROL void	sSetTrueflag(INT16U uwTemp);		


#endif	// __LLC_CONTROL_H__

