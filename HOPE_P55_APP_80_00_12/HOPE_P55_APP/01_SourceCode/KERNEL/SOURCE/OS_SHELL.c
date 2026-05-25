
#define	 OS_GLOBALS
#include "Kernel\kernel.h"

extern void  OSInitSys (void);
extern void  OSInitRdyList (void);
extern void  OSInitTCBList (void);
extern INTOS OSFindHighPrio(void);
extern void	OSStartHighRdy(void);
extern INTOS OSFindHighPrio(void);

extern void OSIntCtxSw(void);
extern OS_STK*  OSTaskStkInit(void (*task)(void), OS_STK *ptos);         //macro/20100507 os error modify

/*
*************************************************************************************************
*                                             INITIALIZATION					*
*												*
* Description: This function is used to initialize the internals of RTOS and MUST be called 	*
*              prior to creating any RTOS object and, prior to calling OSStart().		*
*												*
* Arguments  : none										*
*												*
* Returns    : none										*
*************************************************************************************************
*/

void  OSInit (void)
{

	OSInitSys();                             

 	OSInitRdyList();                          
    
	OSInitTCBList();                            
   
#if	OS_TASK_IDLE_EN>0
	OSInitTaskIdle();        
#endif                   

}

/*
*************************************************************************************************
*                                          START MULTITASKING					*
*												*
* Description: This function is used to start the multitasking process which lets kernal	* 
*              manages the task that you have created.  Before you can call OSStart(), you 	*
*              MUST have called OSInit() and you MUST have created at least one task.		*
*												*
* Arguments  : none										*
*												*
* Returns    : none										*
*												*
*************************************************************************************************
*/

void  OSStart (void)
{
	OSPrioHighRdy = OSFindHighPrio();   
	OSPrioCur     = OSPrioHighRdy;
	OSTCBHighRdy  = &OSTCBTbl[OSPrioHighRdy]; /* Point to highest pri task ready to run	*/
	OSTCBCur      = OSTCBHighRdy;
	OSStartHighRdy();                         /* Execute target  code to start task      	*/
}




/* 
*************************************************************************************************
*                                             Create a task 					*
* Description: 	This function is used to have RTOS manage the execution of a task.  Tasks can 	*
*              	either be created prior to the start of multitasking or by a running task.  A 	*
*              	task cannot be created by an ISR.						*
*												*
* Arguments  : 	task    is a pointer to the task's code						*
*              	ptos    is a pointer to the task's top of stack. 				*
*              	prio    is the task's priority.  A unique priority MUST be assigned to each task* 
*                       and the lower the number, the higher the priority.			*
*		pq	pointer to a message queue related with task				*												*
*												*
* Returns    : 	none										*
*************************************************************************************************
*/
void  	OSTaskCreate (void (*task)(void), INTOS stksize, INTOS prio)
{
	OS_TCB	*ptcb;
	OS_STK	*psp;
	OS_STK  *ptos;

	
	ptos=OSStkPtr;
	
#if	OS_STK_CHK_EN>0
	OSTCBTbl[prio].OSTCBStkBot=ptos;
	OSTCBTbl[prio].OSTCBStkSize=stksize;
#endif

#if	OS_STK_GROWTH_UP>0
	OSStkPtr+=stksize;
#else
	OSStkPtr-=stksize;
#endif
	
	psp = OSTaskStkInit (task, ptos);
		
	ptcb=&OSTCBTbl[prio];
	
	ptcb->OSTCBStkPtr=psp;
	
	ptcb->TimerPeriod=0;
	
	ptcb->TimerCnt=0;
	
	ptcb->OSEvent=0;
	
	OSTaskRdy(prio);
	
}

/*
*************************************************************************************************
*                                               EXIT ISR					*
*												*
* Description: When the last nested ISR has completed, OS will call the scheduler to determine	* 
*              whether a new, high-priority task, is ready to run.				*
*												*
* Arguments  : none										*
*												*
* Returns    : none										*
*************************************************************************************************
*/

void  OSIntExit (void)
{
               
        OSPrioHighRdy =OSFindHighPrio();
        if (OSPrioHighRdy != OSPrioCur) 
        {              					/* No Sw if current task is highest rdy*/
        	OSPrioCur=OSPrioHighRdy;
                OSTCBHighRdy=&OSTCBTbl[OSPrioHighRdy];
                OSIntCtxSw();                           /* Perform interrupt level ctx switch  */
        }
        
}

/*
*************************************************************************************************
*                                               Stack Check					*
*												*
* Description: Calculate the stack usage of task						*												*
* Arguments  : prio:		the ID of task							*
* Returns    : if the Left stack size is less than 10,return OS_STK_FULL			*
*	       else return the used stack number						*
*************************************************************************************************
*/
#if	OS_STK_CHK_EN>0
INTOS	OSStkChk(INTOS	prio)
{
	OS_STK	*stk;
	INTOS	i;
	i=0;
	
	stk=OSTCBTbl[prio].OSTCBStkBot;
	
	while(1)
	{
		if((*stk)==0)
		{
			i++;
			if(i==10)
			{
				#if	OS_STK_GROWTH_UP>0
				return(stk-OSTCBTbl[prio].OSTCBStkBot-10);
				#else
				return(OSTCBTbl[prio].OSTCBStkBot-stk-10);
				#endif
			}
		}
		else
		{
			i=0;
		}
		#if	OS_STK_GROWTH_UP>0
		stk++;
		if(stk==OSTCBTbl[prio].OSTCBStkBot+OSTCBTbl[prio].OSTCBStkSize)
		{
			return(OS_STK_FULL);
		}
		#else
		stk--;
		if(stk==OSTCBTbl[prio].OSTCBStkBot-OSTCBTbl[prio].OSTCBStkSize)
		{
			return(OS_STK_FULL);
		}
		#endif
	}
}
#endif
			
		

