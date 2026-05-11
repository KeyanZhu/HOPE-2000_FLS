/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__DISPLAY_JOB_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define         cTimerBase                      cTimer100ms
#define         cT1sec                          (1000 / cTimerBase)

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
union DISPLAY_STATUS_TABLE
{
	struct DISPLAY_STATUS_BIT_FEILD
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
} fDisplayJob;



INT16U	uwDispStkChk = 0;
INT16U	uwLedDelayCount = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sDisplayJobInit(void);
void	sLEDDisplay(void);


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sDisplayJob(void)
{
	INT16U	wEvent;
	
	sDisplayJobInit();
	
	while(1)
	{

		wEvent = OSEventPend();
		
		if(wEvent & (1 << eDisplayTimer))	// base 100ms
		{
//			sLEDDisplay();

//			if((swGetWorkMode() != cFaultMode) && (swGetWorkMode() != cPowerOnMode) && (fLoadButtonSts == cPressed))
//			{
//				if(swGetWorkMode() != cBatteryMode)
//				{
//					mLED3On;
//				}
//				else
//				{
//					mLED3Off;
//				}
//			}
			
			
			#if	OS_STK_CHK_EN>0
			uwDispStkChk = OSStkChk(cPrioDisplay);	// 114word
			#endif
		}
	}
}

void	sDisplayJobInit(void)
{
	fDisplayJob.data = 0;

}

void	sLEDDisplay(void)
{
	if(swGetWorkMode() == cPowerOnMode)
	{
		mLED1On;
		mLED2On;
		mLED3On;
		mLED4On;
		uwLedDelayCount = 0;
	}
	else
	{
		/*if((swGetWorkMode() == cFaultMode) || (swGetFaultCode() != 0)\
		|| (T_FAULT_DATA.uwData[0] > 0) || (T_FAULT_DATA.uwData[0] > 0)\
		|| (T_FAULT_DATA.uwData[2] > 0) || (T_FAULT_DATA.uwData[3] > 0)\
		|| (T_FAULT_DATA.uwData[4] > 0) || (T_FAULT_DATA.uwData[5] > 0)\
		|| (T_FAULT_DATA.uwData[6] > 0) || (T_FAULT_DATA.uwData[7] > 0)\
		|| (T_FAULT_DATA.uwData[8] > 0) || (T_FAULT_DATA.uwData[9] > 0))*/
		if((swGetWorkMode() == cFaultMode))
		{
			mLED4On;
		}
		else if((T_ALARM_DATA.uwData[0] > 0)\
		|| (T_ALARM_DATA.uwData[1] > 0) || (T_ALARM_DATA.uwData[2] > 0)
		|| (T_ALARM_DATA.uwData[3] > 0) || (T_ALARM_DATA.uwData[4] > 0))
		{
			if(uwLedDelayCount <= 5)
			{
				mLED4On;
			}
			else if(uwLedDelayCount <= 10)
			{
				mLED4Off;
			}
		}

		if(++uwLedDelayCount >= 10)
		{
			uwLedDelayCount = 0;
		}
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	uwGetDispStkChk(void)
{
	return uwDispStkChk;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


