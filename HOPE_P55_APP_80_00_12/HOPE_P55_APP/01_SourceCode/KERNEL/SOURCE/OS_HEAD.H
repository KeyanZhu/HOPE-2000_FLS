
//#ifdef   OS_GLOBALS
//#define  OS_EXT
//#else
#define  OS_EXT  extern
//#endif

#include "kernel\ports\OS_CPU.h"
#include "kernel\ports\os_config.h"


/*
*************************************************************************************************
*                                          task ready control					*
*												*
* Description: 	These two macros control the ready bit of a task in OSRdyMap			*											*
* 		OSTaskRdy insert a ready task into the OSRdyMap 				*
*		OSTaskSuspend	delete a redy task from OSRdyMap				*
*************************************************************************************************
*/

#define	OSTaskRdy(prio)			OSRdyMap|=(1<<(prio))
#define OSTaskSuspend(prio)		OSRdyMap&=~(1<<(prio))


/************************************************************************************************/
/*				constant for stack check					*/
/************************************************************************************************/
#if	OS_STK_CHK_EN>0
#define	OS_STK_FULL	0
#endif

/************************************************************************************************/
/*				macro for CPU USEAGE CALCULATION				*/
/************************************************************************************************/

#if	OS_TASK_IDLE_EN>0
#define	OSGetCPUTimeFree()		OSCpuFree
#endif

/************************************************************************************************/
/*				macro for timer							*/
/************************************************************************************************/

#define OSTimerStart(prio,cnt,period)	OSTCBTbl[(prio)].TimerCnt=(cnt); OSTCBTbl[(prio)].TimerPeriod=(period)
#define OSTimerStop(prio)		OSTCBTbl[(prio)].TimerPeriod=0
		
/************************************************************************************************/
/*				macro for event							*/
/************************************************************************************************/

#define	OSISREventSend(prio,EventId)	OSTCBTbl[(prio)].OSEvent|=1<<(EventId);OSTaskRdy((prio))

/*
*************************************************************************************************
*                                        SYSTEM EVENT DEFINE					*
*************************************************************************************************/

#define 	OS_EVENTID_TIMER		0

/*
*************************************************************************************************
*                                        CONSTANT FOR TIMER					*
*************************************************************************************************/
#define false			 		0
#define true					1



















