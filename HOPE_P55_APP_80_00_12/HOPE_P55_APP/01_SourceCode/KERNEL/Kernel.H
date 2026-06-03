
#ifdef   OS_GLOBALS
#define  OS_EXT
#else
#define  OS_EXT  extern
#endif

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

#define	OSEventPend()			OSMaskEventPend(0)

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


/*
*************************************************************************************************
*                                       TASK CONTROL BLOCK 					*
*************************************************************************************************/

typedef struct{
		OS_STK	*OSTCBStkPtr; 		/*		Pointer to current top of stack	*/
    
		#if	OS_STK_CHK_EN>0
		OS_STK	*OSTCBStkBot;		/*		Pointer to bottom of stack	*/
		
		INTOS	OSTCBStkSize;		/*		stack size			*/
		#endif
		
		INT16U	TimerPeriod;		/*		timer period			*/
		
		INT16U	TimerCnt;		/*		timer counter			*/
		
		TASK_EVENT	OSEvent;	/*		event 				*/
		
		TASK_EVENT	OSEventBitMask;	/*		event mask bits			*/
		}OS_TCB;
		

/*
*************************************************************************************************
*                                        TASK SCHED VARIABLES DEFINE				*
*************************************************************************************************/
OS_EXT  INT16U	OSRdyMap;

OS_EXT  OS_TCB	OSTCBTbl[OS_LOWEST_PRIO + 1];	/* Table of TCB                           	*/

OS_EXT  INTOS   OSPrioHighRdy;	         	/* Priority of highest priority in ready table  */
OS_EXT  INTOS   OSPrioCur;	            	/* Priority of current task  			*/
OS_EXT  OS_TCB	*OSTCBHighRdy;			/* Pointer to highest priority TCB R-to-R 	*/
OS_EXT  OS_TCB  *OSTCBCur;			/* Pointer to currently running TCB  		*/

//OS_EXT 	OS_STK  OSSystemStk[OS_MAX_STK_SIZE];   /* Stack of SYSTEM task				*/


OS_EXT	OS_STK	*OSStkPtr;


/*
*************************************************************************************************
*                                      CPU USAGE 						*
*************************************************************************************************/

#if	OS_TASK_IDLE_EN>0

OS_EXT  INT32U  	OSIdleCtr;
OS_EXT	INT16U		OSTime;
OS_EXT	INTOS		OSCpuFree;

#endif

/*
*************************************************************************************************
*                                      PRIORITY RESOLUTION TABLE 						*
*************************************************************************************************/

#if	OS_TABLE_IN_FLASH>0
extern 	const INTOS  OSUnMapTbl[16];
#else
extern 	 INTOS  OSUnMapTbl[16];
#endif



/*
*************************************************************************************************
*                                        SYSTEM FUNCTION LIST					*
*************************************************************************************************
*/
void		OSInit (void);

void		OSStart (void);

void  		OSTaskCreate (void (*task)(void), INTOS stksize, INTOS prio);

TASK_EVENT	OSMaskEventPend(TASK_EVENT mask);

TASK_EVENT	OSEventGet(void);

void		OSEventSend(INTOS prio,INTOS EventId);

void  		OSIntExit (void);

void		OSTimerTick(void);

#if		OS_STK_CHK_EN>0
INTOS		OSStkChk(INTOS	prio);
#endif
















