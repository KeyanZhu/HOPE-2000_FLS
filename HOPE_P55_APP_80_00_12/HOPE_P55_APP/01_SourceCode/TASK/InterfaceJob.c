/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define			__INTERFACE_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define			cTimerBase						(cTimer50ms >> 1)

#define         cT50ms                          (50 / cTimerBase)
#define         cT100ms                         (100 / cTimerBase)
#define         cT200ms                         (200 / cTimerBase)
#define         cT500ms                         (500 / cTimerBase)
#define         cT1sec                          (1000 / cTimerBase)
#define         cT2sec                          (2000 / cTimerBase)
#define         cT3sec                          (3000 / cTimerBase)
#define         cT4sec                          (4000 / cTimerBase)
#define         cT5sec                          (5000 / cTimerBase)
#define         cT8sec                          (8000 / cTimerBase)
#define         cT10sec                         (10000 / cTimerBase)
#define         cT15sec                         (15000 / cTimerBase)
#define         cT30sec                         (30000 / cTimerBase)
#define         cT1min                          (60000 / cTimerBase)
#define         cT2min                          (120000 / cTimerBase)
#define         cT3min                          (180000 / cTimerBase)
#define         cT5min                          (300000 / cTimerBase)

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
union INTERFACE_STATUS_TABLE
{
	struct INTERFACE_STATUS_BIT_FEILD
	{
		INT16U bInitializeFlag:1;
		INT16U bRsvd1:3;
		
		INT16U bRsvd2:4;
		
		INT16U bRsvd3:4;
		
		INT16U bRsvd4:4;
	} bits;
	INT16U data;
} fInterfaceJob;

INT16U g_uwPassthrough = false;			// 透传标志
INT16U g_uwPassthroughUpdateFW = false;	// 透传升级标志

INT16U wPassthroughDelay = 0;
//INT32U sIdleCount = 0;

INT16U	uwInterfaceStkChk = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sInterfaceJobInit(void);
void	sDataUpdate(INT16U wFilter);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sInterfaceJob(void)
{
	INT16U	wEvent;

	sInterfaceJobInit();

	while(1)
	{
		wEvent = OSEventPend();

		if(wEvent & (1 << e485Parsing))	// TO RS484 BAT PACK
		{
			sSciRouting(c485_SCI);
			if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c485_SCI ,cTTL_SCI);
			}
			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_RS232)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c485_SCI ,c232_SCI);
			}
			else
			{
				sModBusParsing(c485_SCI);
			}
		}

		if(wEvent & (1 << eTTLParsing)) // TO TFT串口屏
		{
			sSciRouting(cTTL_SCI);
			if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,cTTL_SCI ,c485_SCI);
			}
			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS232_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,cTTL_SCI ,c232_SCI);
			}
			else
			{			
				sModBusParsing(cTTL_SCI);
			}
		}

//		if(wEvent & (1 << e232Parsing)) // TO RS232 WIFI
//		{
//			sSciRouting(c232_SCI);
//			if(g_uwPassthrough == SCI_PASSTHROUGH_RS232_MPPT)
//			{
//				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c232_SCI ,cTTL_SCI);
//			}
//			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_RS232)
//			{
//				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c232_SCI ,c485_SCI);
//			}
//			else
//			{			
//				sModBusParsing(c232_SCI);
//			}
//		}


		if(wEvent & (1 << eI2CEEpromFacSave))
		{
			if(sbGetEepromRwEnable())
			{
				sSetEepromRwBusy(true);
				sEepromSave2();
				sSetEepromRwBusy(false);
			}
		}

		if(wEvent & (1 << eI2CEEpromUserSave))
		{
			if(sbGetEepromRwEnable())
			{
				sSetEepromRwBusy(true);
				sEepromSave1();
				sSetEepromRwBusy(false);
			}
		}

		if(wEvent & (1 << eI2CEEpromUser2Save))
		{
			if(sbGetEepromRwEnable())
			{
				sSetEepromRwBusy(true);
				sEepromSave3();
				sSetEepromRwBusy(false);
			}
		}

		if(wEvent & (1 << eInterfaceTimer))	// 50ms
		{	
			// SCI
			sSciProtection(c485_SCI, cT1sec, cT10sec);
			sSciProtection(cTTL_SCI, cT1sec, cT10sec);
//			sSciProtection(c232_SCI, cT1sec, cT10sec);
			sSciRxTask(c485_SCI, cT50ms);						
			sSciRxTask(cTTL_SCI, cT50ms);
//			sSciRxTask(c232_SCI, cT50ms);
//			sCommConnectChk(c485_SCI, cT30sec);
//			sCommConnectChk(cMPPT_SCI, cT30sec);
//			sCommConnectChk(c232_SCI, cT30sec);
//			sEmsCommConnectChk(cT10sec);

			// EEPROM
			sEepromSaveMode1(cT2sec);
			sEepromSaveMode2(cT2sec);
			sEepromSaveMode3(cT2sec);
			sEepromSecureLockClr(cT3min);						

			// Data Update
			sDataUpdate(cT3sec);


			// OSCILLOGRAPH
			#if(OSCILLOGRAPH_ENABLE==1)
			sOscillographMode();
			#endif	

			#if	OS_STK_CHK_EN>0
			uwInterfaceStkChk = OSStkChk(cPrioInterface);
			#endif
		}
	}
}

void	sInterfaceJobInit(void)
{
	fInterfaceJob.data = 0;

	sFaultAlarmInit();

	sEepromInitial();
	sAdcInitial();
	
	sSciInitial(c485_SCI, MAX_SCIA_RX_SIZE, cPrioInterface, e485Parsing);
	sSciInitial(cTTL_SCI, MAX_SCIB_RX_SIZE, cPrioInterface, eTTLParsing);
//	sSciInitial(c232_SCI, MAX_SCIC_RX_SIZE, cPrioInterface, e232Parsing);

	#if(OSCILLOGRAPH_ENABLE==1)
	sOscillographInit();
	#endif
	
	sBatteryInitial();
	sInverterInitial();
	sLineInitial();
	sOutputInitial();
//	sFlashIapInit();

	sSoxInit();


	fInterfaceJob.bits.bInitializeFlag = true;
}

void	sDataUpdate(INT16U wFilter)
{
	sInvPowerConversion();				// 显示的功率折算
	sInverterRealtimeDataUpdate();		// 实时数据更新
	sInverterInformationDataUpdate();	// 设备信息更新
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT8U	sbGetInitializeFinished(void)
{
	return fInterfaceJob.bits.bInitializeFlag;
}

INT16U	swGetPassthrough(void)
{
	return g_uwPassthrough;
}

INT16U	uwGetInterfaceStkChk(void)
{
	return uwInterfaceStkChk;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	swSetPassthrough(INT16U wTemp)
{
	g_uwPassthrough = wTemp;
}

void	swSetPassthroughDelay(INT16U wTemp)
{
	wPassthroughDelay = wTemp;
}

