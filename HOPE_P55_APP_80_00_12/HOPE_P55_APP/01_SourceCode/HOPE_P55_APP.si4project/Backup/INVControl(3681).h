/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INV_CONTROL_H__
#define __INV_CONTROL_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INV_CONTROL_C__
#define INV_CONTROL
#else
#define INV_CONTROL  extern
#endif

#define cFBWait				0
#define cFBInvOpenLoop		1
#define cFBInvCtrlVolt		2
#define cFBInvCtrlBus		3

// INV
#define 		cPWMCntlPeriod50Hz      3906    // 19.2k = 150MHz/2/(3906) = 52us

#define			mRPInvPWM				EPwm1Regs.CMPA.bit.CMPA
#define			mRNInvPWM				EPwm2Regs.CMPA.bit.CMPA
#define			mLPInvPWM				EPwm1Regs.CMPB.bit.CMPB
#define			mLNInvPWM				EPwm2Regs.CMPB.bit.CMPB

#define			mEnINVPWMOut()			EALLOW;\
										EPwm1Regs.TZCLR.bit.OST=1;\
										EPwm2Regs.TZCLR.bit.OST=1;\
										EDIS
#define			mDisINVPWMOut()			EALLOW;\
										EPwm1Regs.TZFRC.bit.OST=1;\
										EPwm2Regs.TZFRC.bit.OST=1;\
										EDIS

#define 		mEnForceLUHigh()		EPwm1Regs.AQCSFRC.bit.CSFA = 2;\
										EPwm1Regs.AQCSFRC.bit.CSFB = 1;
#define 		mEnForceLULow()			EPwm1Regs.AQCSFRC.bit.CSFA = 1;\
										EPwm1Regs.AQCSFRC.bit.CSFB = 2;
#define 		mDisForceLUPWM()		EPwm1Regs.AQCSFRC.bit.CSFA = 0;\
										EPwm1Regs.AQCSFRC.bit.CSFB = 0;

#define 		mEnForceNUHigh()		EPwm2Regs.AQCSFRC.bit.CSFA = 2;\
										EPwm2Regs.AQCSFRC.bit.CSFB = 1;
#define 		mEnForceNULow()			EPwm2Regs.AQCSFRC.bit.CSFA = 1;\
										EPwm2Regs.AQCSFRC.bit.CSFB = 2;
#define 		mDisForceNUPWM()		EPwm2Regs.AQCSFRC.bit.CSFA = 0;\
										EPwm2Regs.AQCSFRC.bit.CSFB = 0;

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INV_CONTROL void	sInvertVoltCtrlParaInit(void);
INV_CONTROL void	sInverterCtrl(void);
INV_CONTROL void	sInverterVoltCtrl(void);
INV_CONTROL void	sSetFBInvCtrlStsIsr(INT16U uwFBCtrlSts);
INV_CONTROL void	sSetFBInvCtrlSts(INT16U uwFBCtrlSts);
INV_CONTROL void	sFBINVPFCInitial(void);
INV_CONTROL void	sClearFBRCurrRam(void);
INV_CONTROL INT16S swFBVoltLoopCntl(INT16S wBusVolt10, INT16S wBusVref,INT16S wBatChgInvLimit,INT16S wInvChgCurrLimit, INT16S wInvFeedCurrLimit,INT16S Phase);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INV_CONTROL INT16S	swGetRSinPointer(void);
INV_CONTROL INT16U	suwGetFBInvCtrlSts(void);
INV_CONTROL INT16S	swGetInvKpwm(void);
INV_CONTROL INT16S	swGetInvVref(void);
INV_CONTROL INT16S	swGetInvRPInvPWM(void);
INV_CONTROL INT16S	swGetInvRNInvPWM(void);
INV_CONTROL INT16S	swGetInvLPInvPWM(void);
INV_CONTROL INT16S	swGetInvLNInvPWM(void);

INV_CONTROL INT16S	swGetInvPWMEn(void);

INV_CONTROL INT16S  sGetLoopOutput(void);
INV_CONTROL INT16S	swGetDCDCCtrlFBBusErr(void);

INV_CONTROL INT16S	swGetInvVoltCntl(void);
INV_CONTROL INT16S	swGetwInvVref(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INV_CONTROL void	sSetInvKpwm(INT16S wValue);
INV_CONTROL	void	sSetInvPWMEn(INT16S wValue);
INV_CONTROL void	sSetInvVoltCtrlParaKv(INT16S wValue);
INV_CONTROL void	sSetInvVoltCtrlParaKi(INT16S wValue);
INV_CONTROL void	sSetInvVoltCtrlParaCurrLimit(INT16S wValue);


#endif	// __INV_CONTROL_H__

