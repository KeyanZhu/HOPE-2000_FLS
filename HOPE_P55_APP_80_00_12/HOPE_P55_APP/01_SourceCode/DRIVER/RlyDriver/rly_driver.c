/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__RLY_DRIVER__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"
//#include 	"kernel\kernel.h"
#include	"kernel\source\OS_HEAD.H"

/********************************************************************************
* Macros 																		*
********************************************************************************/


/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S g_wPwmPeriod;
extern INT16S gi_wSinePointMax;
extern INT16S gi_wSinePointThreeSix;
extern INT16S g_wRSinPointer;

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
INT16U wRlyActionPointer = RLY_ACTION_NULL;
INT8U bRlyActionEvent = RLY_EVENT_NULL;
INT8U bRlyRelatedTask = 0;
INT16U wRlyActionPointer2 = RLY_ACTION_NULL;
INT8U bRlyActionEvent2 = RLY_EVENT_NULL;
INT8U bRlyRelatedTask2 = 0;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
#pragma CODE_SECTION(sRlyActionDriver,".TI.ramfunc");	
void	sSetRlyPointer(unsigned char relaytype,unsigned int pointer,unsigned char event,unsigned char prio)
{
	INT16U wRlyActionPointerTemp;
	if(relaytype == RLY_DELAY)
	{
		wRlyActionPointerTemp = (INT16U)((INT32U)pointer * 4500 / g_wPwmPeriod);
		OS_ENTER_CRITICAL();
		wRlyActionPointerTemp = (wRlyActionPointerTemp + g_wRSinPointer + 1) % gi_wSinePointMax;
		OS_EXIT_CRITICAL();
	}
	else if(relaytype == RLY_CROSSZERO)
	{
		wRlyActionPointerTemp = (INT16U)((INT32U)pointer * 4500 / g_wPwmPeriod);
		wRlyActionPointerTemp = wRlyActionPointerTemp % gi_wSinePointMax;
		OS_ENTER_CRITICAL();
		wRlyActionPointerTemp = (gi_wSinePointMax - wRlyActionPointerTemp) % gi_wSinePointMax;
		OS_EXIT_CRITICAL();
	}
	else if(relaytype == RLY_ZEROPOINT)
	{
		OS_ENTER_CRITICAL();
		wRlyActionPointerTemp = ((g_wRSinPointer + 2) / gi_wSinePointThreeSix + 1) * gi_wSinePointThreeSix;
		wRlyActionPointerTemp = wRlyActionPointerTemp % gi_wSinePointMax;
		OS_EXIT_CRITICAL();
	}
	else
	{
		wRlyActionPointerTemp = pointer;
	}
	if(wRlyActionPointer == RLY_ACTION_NULL)
	{
		OS_ENTER_CRITICAL();
		wRlyActionPointer=wRlyActionPointerTemp;
		bRlyActionEvent=event;
		bRlyRelatedTask=prio;
		OS_EXIT_CRITICAL();
	}
	else
	{
		OS_ENTER_CRITICAL();
		wRlyActionPointer2=wRlyActionPointerTemp;
		bRlyActionEvent2=event;
		bRlyRelatedTask2=prio;
		OS_EXIT_CRITICAL();
	}
}

void	sRlyActionDriver(unsigned int pointer)
{
	INT16U wTemp;
	
	// 由于锁相总点数384个点不变,锁相是通过增加跳点或者重复点，使累加到384时实际时间不同来动态调整跟踪频率;
	// 所以如果只使用一个点作为RLY动作执行条件，当刚好此点一直存在跳点时，会导致动作由于一直无法满足条件而不能执行;
	// 但由于锁相频率只允许在38-67Hz之间,所以只会存在一个跳点的情况，即用相邻的两个点作为判断条件一定能满足要求;
	if(wRlyActionPointer!=RLY_ACTION_NULL)
	{
		wTemp = wRlyActionPointer + 1;
		if(wTemp >= gi_wSinePointMax)
		{
			wTemp = 0;
		}
		if((wRlyActionPointer == pointer) || (wTemp == pointer))
		{
			OSISREventSend(bRlyRelatedTask,bRlyActionEvent);
			wRlyActionPointer=RLY_ACTION_NULL;
			bRlyActionEvent=RLY_EVENT_NULL;
		}
	}
	if(wRlyActionPointer2!=RLY_ACTION_NULL)
	{
		wTemp = wRlyActionPointer2 + 1;
		if(wTemp >= gi_wSinePointMax)
		{
			wTemp = 0;
		}
		if((wRlyActionPointer2 == pointer) || (wTemp == pointer))
		{
			OSISREventSend(bRlyRelatedTask2,bRlyActionEvent2);
			wRlyActionPointer2=RLY_ACTION_NULL;
			bRlyActionEvent2=RLY_EVENT_NULL;
		}
	}
}

void	sRlyDelayProc(unsigned char relaytype,unsigned int pointer,unsigned char event,unsigned char prio)
{
	sSetRlyPointer(relaytype,pointer,event,prio);
	while(OSMaskEventPend(~((INT16U)1<<event)) == 0);
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


