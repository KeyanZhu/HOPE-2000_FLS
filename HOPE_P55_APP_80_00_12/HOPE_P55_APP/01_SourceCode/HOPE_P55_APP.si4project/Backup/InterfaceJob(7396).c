/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		F28P55X_DEMO
File Name:		InterfaceJob.c
Author:			xiaofeng
Date:			2024.07.12
Description:	None
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

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sInterfaceJobInit(void);


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
		
		if(wEvent & (1 << e485Parsing))
		{
			sSciRouting(c485_SCI);
			if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c485_SCI ,cMPPT_SCI);
			}
			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_RS232)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c485_SCI ,c232_SCI);
			}
			else
			{
				if(sbGetRouteProt() == cROUTE_PROT_TEST)
				{
//					sTestParsing(c485_SCI);
				}
				else
				{				
					sModBusParsing(c485_SCI);
				}
			}
		}

		if(wEvent & (1 << e232Parsing))
		{
			sSciRouting(c232_SCI);
			if(g_uwPassthrough == SCI_PASSTHROUGH_RS232_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c232_SCI ,cMPPT_SCI);
			}
			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_RS232)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,c232_SCI ,c485_SCI);
			}
			else
			{
				if(sbGetRouteProt() == cROUTE_PROT_TEST)
				{
//					sTestParsing(c232_SCI);
				}
				else
				{				
					sModBusParsing(c232_SCI);
				}
			}
		}

		if(wEvent & (1 << eMPPTParsing))
		{		
			sSciRouting(cMPPT_SCI);
			if(g_uwPassthrough == SCI_PASSTHROUGH_RS485_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,cMPPT_SCI ,c485_SCI);
			}
			else if(g_uwPassthrough == SCI_PASSTHROUGH_RS232_MPPT)
			{
				sSciPassthrough(SCI_PASSTHROUGH_MPPT ,cMPPT_SCI ,c232_SCI);
			}
			else
			{
				if(sbGetRouteProt() == cROUTE_PROT_TEST)
				{
//					sTestParsing(cMPPT_SCI);
				}
				else
				{				
//					sDSPSciParsing(cMPPT_SCI);
				}
			}
		}
		
		if(wEvent & (1 << eInterfaceTimer))	// 50ms
		{	
			// SCI
			sSciProtection(c485_SCI, cT1sec, cT10sec);
			sSciProtection(cMPPT_SCI, cT1sec, cT10sec);
			sSciProtection(c232_SCI, cT1sec, cT10sec);
			sSciRxTask(c485_SCI, cT50ms);						
			sSciRxTask(cMPPT_SCI, cT50ms);
			sSciRxTask(c232_SCI, cT50ms);
			sCommConnectChk(c485_SCI, cT30sec);
			sCommConnectChk(cMPPT_SCI, cT30sec);
			sCommConnectChk(c232_SCI, cT30sec);	

			sInverterRealtimeDataUpdate();
			sInverterInformationDataUpdate();
		}
	}
}

void	sInterfaceJobInit(void)
{
	fInterfaceJob.data = 0;

	sSciInitial(c485_SCI, MAX_SCIA_RX_SIZE, cPrioInterface, e485Parsing);
	sSciInitial(cMPPT_SCI, MAX_SCIB_RX_SIZE, cPrioInterface, eMPPTParsing);
	sSciInitial(c232_SCI, MAX_SCIC_RX_SIZE, cPrioInterface, e232Parsing);

	fInterfaceJob.bits.bInitializeFlag = true;
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


