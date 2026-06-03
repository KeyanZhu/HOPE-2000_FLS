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

typedef struct
{
	INT16U fConfigButton:1;
	INT16U fEnterButton:1;
	INT16U fESCButton:1;
	INT16U fUPButton:1;
	INT16U fDownButton:1;
	INT16U fLoadButton:1;	
	INT16U uwReserved:10;
}STRButtonSts;

STRButtonSts g_strButtonSts;

#define	fConfigButtonSts		g_strButtonSts.fConfigButton
#define	fEnterButtonSts			g_strButtonSts.fEnterButton
#define	fESCButtonSts			g_strButtonSts.fESCButton
#define	fUPButtonSts			g_strButtonSts.fUPButton
#define	fDownButtonSts			g_strButtonSts.fDownButton
#define	fLoadButtonSts			g_strButtonSts.fLoadButton

#define	cPressed			1
#define	cReleased			0

#define cSetStepInit		0
#define cSetStepOne			1
#define cSetStepTwo			2
#define cSetStepEsc			0xFF


INT16U	uwDispStkChk = 0;
INT16U	uwLedDelayCount = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sDisplayJobInit(void);
void	sLEDDisplay(void);
void 	ButtonInitial(void);
void 	sSetConfigButton(void);
void 	sSetEnterButton(void);
void 	sSetESCButton(void);
void 	sSetUpButton(void);
void 	sSetDownButton(void);
void 	sSetLoadButton(void);
void 	sButtonScan(void);

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
			sButtonScan();
			
			sLEDDisplay();

			if((swGetWorkMode() != cFaultMode) && (swGetWorkMode() != cPowerOnMode) && (fLoadButtonSts == cPressed))
			{
				if(swGetWorkMode() != cBatteryMode)
				{
					mLED3On;
				}
				else
				{
					mLED3Off;
				}
			}
			
			ButtonInitial();
			
			#if	OS_STK_CHK_EN>0
			uwDispStkChk = OSStkChk(cPrioDisplay);	// 114word
			#endif
		}
	}
}

void	sDisplayJobInit(void)
{
	fDisplayJob.data = 0;

	ButtonInitial();
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
void ButtonInitial(void)
{
	fConfigButtonSts	= cReleased;
	fEnterButtonSts		= cReleased;
	fESCButtonSts		= cReleased;
	fUPButtonSts		= cReleased;
	fDownButtonSts		= cReleased;
	fLoadButtonSts		= cReleased;
}


void sSetConfigButton(void)
{
	fConfigButtonSts = cPressed;
}

void sSetEnterButton(void)
{
	fEnterButtonSts = cPressed;
}

void sSetESCButton(void)
{
	fESCButtonSts = cPressed;
}

void sSetUpButton(void)
{
	fUPButtonSts = cPressed;
}

void sSetDownButton(void)
{
	fDownButtonSts = cPressed;
}

void sSetLoadButton(void)
{
	fLoadButtonSts = cPressed;
}

void sButtonScan(void)
{
	static INT16U s_ubOnPressCnt = 0;

	if(mBATONS)
	{
		if(s_ubOnPressCnt < 255)
		{
			s_ubOnPressCnt++;
		}
		
		if(s_ubOnPressCnt == 25)						// ³¤°´
		{
			sSetLoadButton();	
		}
	}
	else
	{
		if(s_ubOnPressCnt > 0 && s_ubOnPressCnt < 25)	// ¶Ì°´
		{
			sSetESCButton();
		}
		s_ubOnPressCnt = 0;
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


