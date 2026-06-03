
#include	"OS_CPU.h"

//extern	void c_int0(void);

OS_STK*  OSTaskStkInit(void (*task)(void), OS_STK *ptos)
{
	OS_STK	*stk;
	stk=ptos;   				/* 		Load stack pointer         	*/
	
	*stk++= (INTOS) 0x0000;		/*		ST0=0						*/
	*stk++= (INTOS) 0x0000;		/*		T=0							*/
	*stk++= (INTOS)	0x0000;		/*		AL=0						*/
	*stk++= (INTOS) 0x0000;		/*		AH=0						*/
	*stk++= (INTOS) 0x0000;		/*		PL=0						*/
	*stk++= (INTOS) 0x0000;		/*		PH=0						*/
	*stk++= (INTOS) 0x0000;		/*		AR0=0						*/
	*stk++= (INTOS) 0x0000;		/*		AR1=0						*/
	*stk++= (INTOS) 0x0A0A;		/*		ST1=0					
								Interrupts are enabled				*/
	*stk++= (INTOS) 0x0000;		/*		DP=0						*/
	*stk++= (INTOS) 0x018D;		/*		IER=0x010D					*/	// for test, IER is the same as the initial value
	*stk++= (INTOS)	0x0000;		/*		DBGSTAT=0					*/
	*stk++= (INT32U) task & 0x0000FFFF;		/*		PC:L H			*/
	*stk++= (INT32U) task >>16;
	
	*stk++= (INTOS) 0x0A0A;		/*		ST1=0					
								Interrupts are enabled				*/
	*stk++= (INTOS) 0x0000;		/*		DP=0						*/
	
	*stk++= (INTOS) 0x0000;		/*		RPC							*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XT							*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR7						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR6						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR5						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR4						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR3						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		XAR2						*/
	*stk++= (INTOS) 0x0000;		/*									*/
	*stk++= (INTOS) 0x0000;		/*		AR1H:AR0H					*/
	*stk++= (INTOS) 0x0000;		/*									*/
	
	stk++;		
	return(stk);
}


