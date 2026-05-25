/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__BUSBATPROT_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      (cTimer20ms >> 1)
#define         cT100ms                         (100 / cTimerBase)
#define         cT200ms                         (200 / cTimerBase)
#define         cT500ms                         (500 / cTimerBase)
#define         cT1sec                          (1000 / cTimerBase)
#define         cT2sec                          (2000 / cTimerBase)
#define         cT3sec                          (3000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/


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
union BUSBATPROT_STATUS_TABLE
{
	struct BUSBATPROT_STATUS_BIT_FEILD
	{
		// BIT0-3
		INT16U bRsvd1:4;
		
		// BIT4-7
		INT16U bRsvd2:4;
		
		// BIT8-11
		INT16U bRsvd3:4;
		
		// BIT12-15
		INT16U bRsvd4:4;
	} bits;
	INT16U data;
} fBusBatProtJob;

INT16U	uwBusBatProtStkChk = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sBusBatProtInit(void);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sBusBatProtJob(void)
{
	INT16U wEvent;

	sBusBatProtInit();
	
	while(1)
	{
		wEvent = OSEventPend();
		
		if(wEvent & (1 << eGeneralTimer))
		{	
			sSetBusVoltNew(swBusVoltCal());			// BUS.V
//			sSetBusCurrNew(swBusCurrCal());			// BUS.I

			sSetBatVoltNew(swBatVoltCal());			// BAT.V
			sSetBatVolt2New(swBatVolt2Cal());		// VBAT.V	双重保护用
			sSetBatCurrNew(swBatCurrCal());			// BAT.I
			sSetBatWattNew(swBatWattCal());			// BAT.W
			sSetB1VoltNew(swB1VoltCal());			// 电芯1电压
			sSetB2VoltNew(swB2VoltCal());			// 电芯2电压
			sSetBVoltNew(swBVoltCal());				// 电芯串联总压
			
			sSetPv1VoltNew(swPv1VoltCal());			// PV1.V
			sSetPv1CurrNew(swPvL1CurrCal());		// PV1.I	// PV电感电流
			sSetPvWattNew(swPvWattCal());			// PV.W
			sSetPv1BatCurrNew(swPv1BatCurrCal());	// PV1.BAT.I
			sSetPv1BatWattNew(swPv1BatWattCal());	// PV1.BAT.W
			sSetPvInCurrNew(swPvInCurrCal());		// 
			sSetPvInTzCurrNew(swPvInTzCurrCal());	// 

			sSetLLCOCPCurrNew(swLLCOCPCurrCal());	// LLC.OCP.CURR
			sSetLV12VVoltNew(swLV12VVoltCal());		// LV_12V.V
			sSetAC12VVoltNew(swAC12VVoltCal());		// AC_12V.V

//			sSetHsBatHTempNew(swHsBatHTempCal());	// BATH.T
//			sSetHsTwTempNew(swHsTwTempCal());		// TW.T
			sSetHsInvTempNew(swHsInvTempCal());		// INV.T
			sSetHsPvTempNew(swHsPvTempCal());		// PV1.T
			sSetHsLLCTempNew(swHsLLCTempCal());		// LLC.T
			sSetHsBat1TempNew(swHsBat1TempCal());	// BAT1.T
			sSetHsBat2TempNew(swHsBat2TempCal());	// BAT2.T	
			
			sBatteryParaUpdate();					// 电池参数更新

			sBatVoltRefAdj();						// 14.4V * swGetBatSerialPcs()
			sBatPercentCal();						// SOC预估

			// PV
			sPv1VoltOverChk(uwGetMpptPvVoltMax(), cT3sec);						// PV过压故障,55V,3S
			sPv1CurrOverChk(cMpptBatCurr100A, cT1sec);							// PV过流故障,100A,1S
			sPv1UnderChk(cT5sec);												// PV欠压告警,11.5V,5S

			// BAT
			sBatVoltOverChk((cBatVoltReal3V65*uwGetBatSerialPcs()), cT5sec);	// 电池过压故障,3.65V,5S
			sBatUnderChk(cT200ms);												// 电池欠压告警,200ms
			sBatOpenChk((cBatVoltReal2V12*uwGetBatSerialPcs()), cT1sec);		// 电池开路检测,单节2.12V,200ms
			sLowBatCutOffChk(cT3sec);											// 电池低压关输出检测					// 待优化

			// BUS
			sBusOverChk(4750, cT1sec, 4800, cT100ms);							// BUS过压检测故障,1段,1s   ,1段,100ms
			subBusUnderChk(uwGetBusVoltLow1(), cT5sec);							// BUS欠压故障,100V,5S
//			sBusCurrOverChk(cDCDC15A, cT1sec);									// BUS过流故障,15A,1S
			sBatCurrOverChk(200, cT1sec);	// 200A

			#if	OS_STK_CHK_EN>0
			uwBusBatProtStkChk = OSStkChk(cPrioBusBatProt);	// 93word
			#endif
		}
	}
}

void	sBusBatProtInit(void)
{
	fBusBatProtJob.data = 0;
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	uwGetBusBatProtStkChk(void)
{
	return uwBusBatProtStkChk;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


