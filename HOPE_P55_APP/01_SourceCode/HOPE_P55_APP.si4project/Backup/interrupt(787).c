/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/

#include    "main.h"
#include    "Kernel\source\OS_HEAD.h"

#pragma CODE_SECTION(isrINV,".TI.ramfunc");
#pragma CODE_SECTION(isrDCDC,".TI.ramfunc");
#pragma CODE_SECTION(isrOSTimeBase,".TI.ramfunc");

//extern volatile INT32U g_dwErrorFlag;
//extern MCAN_RxBufElement rxMsg1;

extern INT16S  wTheta;
extern INT16S* pSinTab;
extern INT16S* pCosTab;

INT16U gi_uwOPRelayOn = false;		// OP继电器
INT16U gi_uwGridRelayOn = false;	// 市电继电器

INT16U gi_uwBATSPSRlyOn = true;		// 辅源SPS

extern INT32U gi_udwLineZeroTimeNew;	// 当前市电过零CAP值,50Hz=1800000,60Hz=1500000
extern INT32U gi_udwLineZeroTimeOld;	// 上次市电过零CAP值,50Hz=1800000,60Hz=1500000
extern INT16U gi_uwLinePeriodCntNew;	// 市电周期值,50Hz=20000,60Hz=16667
extern INT16S gi_wRGeneratorWaveChkCnt;
extern INT16S gi_wRGeneratorVoltMax;
extern INT16S gi_wRGeneratorVoltMin;

extern INT32U gi_udwSineZeroTimeOld;	// 上次逆变过零CAP值,50Hz=1800000,60Hz=1500000
extern INT16U gi_uwSinePeriodCntNew;	// 逆变周期值,50Hz=20000,60Hz=16667

extern INT16U gi_uwInvertTd;
extern INT16S g_wRSinPointerwThetaTemp;

INT16S gi_wIntPionter;
extern INT32U g_dwRSinPionterQ15;
extern INT16U wRSinPionterDeltaQ15;
extern INT16S g_wRSinPointer;
extern INT16S gi_wSinePointMax;

extern INT16S g_wRSinAmp;
extern INT16S g_wRNewSinAmp;

INT16S g_wRInvOverCurrCnt = 0;
INT16S g_wRInvOverCurrPCnt = 0;
INT16U gi_uwBusVoltHiIntCnt = 0;
INT16U gi_uwBatVoltHiIntCnt = 0;
INT16U gi_uwInvCurrHWHiIntCnt = 0;

INT16S gi_wEepromWaitFlag = 0;
INT16S gi_wEepromWaitCnt = 0;

INT16S gi_wLineCrossZero = false;

INT16U gi_wLineWaveDetectEn = true;

extern INT32U gi_udwPreLineZeroTimeNew;

interrupt void isrLineZero(void)
{
	INT32U dwCapTemp;
	INT32U dwPeriodTemp;
	
	dwCapTemp = ECap1Regs.CAP1; // 当前次过零值

	// 50HZ = 2400000
	// 60HZ = 2000000
	dwPeriodTemp = (INT16U)((dwCapTemp - gi_udwLineZeroTimeOld) / cPLL_FREQ_DIV);
	gi_wRGeneratorWaveChkCnt = 0;
	gi_wRGeneratorVoltMax = 0;
	gi_wRGeneratorVoltMin = 0;
	
	//Check if new line period is noise. Yes, Do not care.
	if(dwPeriodTemp < cPeriod70Hz || dwPeriodTemp > cPeriod35Hz)
	{
		// To recieve more interrupts from this PIE group, acknowledge this interrupt 
		ECap1Regs.ECCLR.bit.CEVT1 = 1;
		ECap1Regs.ECCLR.bit.INT = 1;
		ECap1Regs.ECCTL2.bit.REARM = 1;
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
		return;
	}

	gi_uwLinePeriodCntNew = dwPeriodTemp;
	gi_udwLineZeroTimeNew = dwCapTemp;
	gi_udwLineZeroTimeOld = dwCapTemp;

//	sAdcLineIsr();
//
//	gi_wLineCrossZero = true;
//	OSISREventSend(cPrioGrid, eGridLineZero);

    ECap1Regs.ECCLR.bit.CEVT1 = 1;
	ECap1Regs.ECCLR.bit.INT = 1;
	ECap1Regs.ECCTL2.bit.REARM = 1;
	
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}


interrupt void isrINV(void)
{
	INT32U dwCapTemp;
	INT16S wInvCurrTemp;
	INT16S wRInvOverCurrFlg;
	INT16S wPBusOverVoltFlg;
	AdcaRegs.ADCSOCFRC1.all = 0X7FFF;// Software triggered ADC conversion
	AdcbRegs.ADCSOCFRC1.all = 0X03FF;// Software triggered ADC conversion
	AdccRegs.ADCSOCFRC1.all = 0X0001;// Software triggered ADC conversion

	if(gi_wIntPionter == 0)//swGetInvSinPointBias())
	{		
		dwCapTemp = ECap1Regs.TSCTR;
		gi_uwSinePeriodCntNew = (INT16U)((dwCapTemp - gi_udwSineZeroTimeOld) / cPLL_FREQ_DIV);	
		gi_uwInvertTd = (INT16U)((dwCapTemp - gi_udwPreLineZeroTimeNew) / cPLL_FREQ_DIV);		// 软件锁相环
		//gi_uwInvertTd = (INT16U)((dwCapTemp - gi_udwLineZeroTimeNew) / cPLL_FREQ_DIV);			// 硬件捕获锁相
		gi_udwSineZeroTimeOld = dwCapTemp;
		
		OSISREventSend(cPrioInvLoadOP, eInvLoadOPSinZero);	// 逆变过零
	}

	gi_wIntPionter++;
	g_dwRSinPionterQ15 += wRSinPionterDeltaQ15;
	g_wRSinPointer = (g_dwRSinPionterQ15 + 8192) >> 14;
	if(g_wRSinPointer >= gi_wSinePointMax)
	{
		g_wRSinPointer = 0;
		g_dwRSinPionterQ15 = 0;
		gi_wIntPionter = 0;
		g_wRSinAmp = g_wRNewSinAmp;	// 逆变赋值，load计算给出
	}
	
	sAdcINVIsr();

	// fast protect
	wInvCurrTemp = swGetAdcInvCurrReal();
	if(wInvCurrTemp >= cInv45A || wInvCurrTemp < -cInv45A)	// 继电器30A,1.5倍就是45A
	{
		g_wRInvOverCurrCnt++;
		g_wRInvOverCurrPCnt++;
		wRInvOverCurrFlg = 1;
	}
	else
	{
		g_wRInvOverCurrCnt = 0;
		wRInvOverCurrFlg = 0;
	}

	if(swGetAdcBusVoltReal() >= 5000)//uwGetBusVoltOver3())	// BUS电容是550V，触发后会封逆变
	{
		wPBusOverVoltFlg = 1;
	}
	else
	{
		wPBusOverVoltFlg = 0;
	}

	// 
	if(swGetWorkMode() != cPowerOnMode)
	{
		if(swGetWorkMode() != cBatteryMode)
		{
			//if(g_wRInvOverCurrCnt > gi_wSinePointTwoSix)
			if(g_wRInvOverCurrCnt >= 20)	// for test
			{
				g_wRInvOverCurrCnt = 0;
				T_FAULT_DATA.bits.bInvSoftOC = true;
				sSetFaultCode(cInvCurrOver);
			}
		}
		else
		{
			if(g_wRInvOverCurrCnt > 50)
			{
				g_wRInvOverCurrCnt = 0;
				T_FAULT_DATA.bits.bInvSoftOC = true;
				sSetFaultCode(cInvCurrOver);
			}
		}
	}

	if(suwGetFBInvCtrlSts() != cFBWait)
	{
		if(wRInvOverCurrFlg || wPBusOverVoltFlg)
		{
			if(swGetInvPWMEn())
			{
				sSetInvPWMEn(false);
			}
		}
		else if(!swGetInvPWMEn())
		{
			if(suwGetFBInvCtrlSts() == cFBInvCtrlBus)
			{
				if(gi_wLineCrossZero == true)
				{
					sSetInvPWMEn(true);
					sClearFBRCurrRam();
					sFBINVController2Init();
					sFBBUSController2Init();
				}
			}
			else
			{
				sSetInvPWMEn(true);
			}
		}
	}
	else
	{
		sSetInvPWMEn(false);
	}

	if(suwGetFBInvCtrlSts() == cFBWait || swGetInvPWMEn() == false)
	{
		mDisINVPWMOut();
		g_wRSinAmp = 0;
	}
	else
	{
		mEnINVPWMOut();
	}
	
	if(suwGetFBInvCtrlSts() == cFBInvCtrlVolt)
	{
//		sInverterVoltCtrl();		// 离网闭环逆变控制器
//		sInvVoltRealLoopCtrl();
//		sInvCurrRealLoopCtrl();
	}
	else
	{
		if(suwGetFBInvCtrlSts() == cFBInvCtrlBus)
		{
//			sFBBUSController2();	// 并网BUS电压外环
//			sFBINVController2();	// 并网逆变电流内环
		}
		else if(suwGetFBInvCtrlSts() == cFBInvOpenLoop)
		{
			sInverterCtrl();		// 离网开环逆变控制器
		}
	}

	gi_wLineCrossZero = false;

	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


interrupt void isrDCDC(void)
{
	AdcaRegs.ADCSOCFRC1.all = 0X7FFF;// Software triggered ADC conversion
	AdcbRegs.ADCSOCFRC1.all = 0X03FF;// Software triggered ADC conversion
	AdccRegs.ADCSOCFRC1.all = 0X0001;// Software triggered ADC conversion

	// BUS快速过压检测
	if(swGetAdcBusVoltReal() >= 4800)	// BUS电容是500V
	{
		if(++gi_uwBusVoltHiIntCnt >= 50)
		{
			gi_uwBusVoltHiIntCnt = 50;
			sSetDCDCCtrlSts(cDCDCWait);
			T_FAULT_DATA.bits.bBusSoftOV = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cBusVoltOver);
			}
		}
	}
	else if(gi_uwBusVoltHiIntCnt > 0)
	{
		gi_uwBusVoltHiIntCnt--;
	}

	// 电池快速过压检测
	if(swGetBatVoltNew() >= (cBatVoltReal3V75 * uwGetBatSerialPcs()) && (swGetWorkMode() != cPowerOnMode))
	{
		if(++gi_uwBatVoltHiIntCnt >= 50)
		{
			gi_uwBatVoltHiIntCnt = 50;
			sSetDCDCCtrlSts(cDCDCWait);
			T_FAULT_DATA.bits.bBatSoftOV = true;
			if(swGetWorkMode() != cFaultMode)
			{
				sSetFaultCode(cBatVoltOver);
			}
		}
	}
	else if(gi_uwBatVoltHiIntCnt > 0)
	{
		gi_uwBatVoltHiIntCnt--;
	}

	// ADC采样
	sAdcDCDCIsr();

	// DCDC开环控制
	sOpenLLCCtrl();	

	// PV Ctrl
	if(suwGetPV1CtrlSts() == cPVWait)
	{		
		mPV1BuckPWM = 0;
		mDisPV1PWMOut();
		sClrPv1CtrlPara();
	}
	else
	{
		mEnPV1PWMOut();
		if(suwGetPV1CtrlSts() == cDCDCWork || suwGetPV1CtrlSts() == cDCDCSoft)
		{
			sPV1Control();		// PV闭环控制(无软起，直接就是work模式)
		}
		else if(suwGetPV1CtrlSts() == cDCDCOpen)
		{
			sPV1OpenControl();	// PV开环发波，占空比由Modbus调试寄存器写入
		}
	}

	// 软件锁相环
	//if(!mGetLineStatusVoltLoss() || !mGetLineStatusFreqLoss())	// 改为软件锁相环后，市电采样更新在软件过零点处
	if(1)
	{
		sPhaseLockControl(swGetAdcGridVoltReal(),0,0);
		g_wRSinPointerwThetaTemp = wTheta;// + swGetInvSinPointBias();
		if(g_wRSinPointerwThetaTemp >= gi_wSinePointMax)
		{
			g_wRSinPointerwThetaTemp -= gi_wSinePointMax;
		}
		else if(g_wRSinPointerwThetaTemp < 0)
		{
			g_wRSinPointerwThetaTemp += gi_wSinePointMax;
		}

		// 市电丢失快速检测
		//gi_wLineWaveDetectEn = false;	// for test
		if(gi_wLineWaveDetectEn)
		{
			sLineWaveChk(swGetAdcGridVoltReal(), pSinTab[g_wRSinPointerwThetaTemp], swGetAdcOpCurrReal());
		}
		else
		{
			if(mGetLineStatusWaveLoss() == true)
			{
				mSetLineStatusWaveLoss(false);
			}
		}
	}

	sRlyActionDriver(g_wRSinPointer);
	
	#if(OSCILLOGRAPH_ENABLE==1)
	sOscillographCapturing();
	#endif

	EPwm2Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void isrEPWM3(void)
{	
	EPwm3Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void isrFAN(void)  // @20K
{	
	EPwm6Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void isrOSTimeBase(void)
{
    OSTimerTick();
	
//	OSIntExit();	// 加了之后程序会乱发信号，死机等，谨慎调试

	if(gi_wEepromWaitFlag)
	{
		if(gi_wEepromWaitCnt++ > 40)
		{
			gi_wEepromWaitCnt = 0;
			gi_wEepromWaitFlag = 0;
			OSISREventSend(cPrioInterface,eEepromWaitTime);
		}
	}
	else
	{
		gi_wEepromWaitCnt = 0;
	}

	if(gi_uwOPRelayOn)
	{
		hoROPRLYOn;
	}
	else
	{
		hoROPRLYOff;
	}
	
	if(gi_uwGridRelayOn)
	{
		hoGRIDRLYOn;
	}
	else
	{
		hoGRIDRLYOff;
	}

    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;	
}

interrupt void isrSCIAReceive(void)
{
	sSciRxISR(cSCIA_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void isrSCIATransmit(void)
{
	sSciTxISR(cSCIA_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void isrSCIBReceive(void)
{
	sSciRxISR(cSCIB_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void isrSCIBTransmit(void)
{
	sSciTxISR(cSCIB_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

interrupt void isrSCICReceive(void)
{
	sSciRxISR(cSCIC_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

interrupt void isrSCICTransmit(void)
{
	sSciTxISR(cSCIC_ID);
	
	// To recieve more interrupts from this PIE group, acknowledge this interrupt 
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

interrupt void isrADCA(void)
{
	// ADC数据处理

    // Clear the interrupt flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    // Check if overflow has occurred
    if(AdcaRegs.ADCINTOVF.bit.ADCINT1 == 1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	uwGetBATSPSRlyOn(void)
{
	return gi_uwBATSPSRlyOn;
}

INT16U	uwGetOPRelayOn(void)
{
	return gi_uwOPRelayOn;
}

INT16U	uwGetGridRelayOn(void)
{
	return gi_uwGridRelayOn;
}


INT16S	wGetRSinPointerwThetaTemp(void)
{
	return	g_wRSinPointerwThetaTemp;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetOPRelayOn(INT16U uwState)
{
	gi_uwOPRelayOn = uwState;
}

void	sSetGridRelayOn(INT16U uwState)
{
	gi_uwGridRelayOn = uwState;
}


void	sSetBATSPSRlyOn(INT16U uwState)
{
	gi_uwBATSPSRlyOn = uwState;
}



