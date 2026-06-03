
#ifdef   OS_GLOBALS
#define  OS_EXT
#else
#define  OS_EXT  extern
#endif

/************************************************************************************************
*					Basic variables type definition				*
*************************************************************************************************/
#define BOOLEAN 	unsigned char  			
#define INT8U   	unsigned char  			
#define INT8S   	  signed char  			
#define INTOS		unsigned int				/* the smallest unit int the cpu	*/
#define INT16U  	unsigned int			
#define INT16S  	  signed int 			
#define INT32U  	unsigned long  			
#define INT32S  	  signed long    
#define INT64U  	unsigned long long
#define F32                  float

#define OS_STK		INTOS
#define OS_CPU_SR	INTOS                	/* Define size of CPU status register (PSR = 32 bits) */


/************************************************************************************************
*					Macro definitions					*
*************************************************************************************************/



#define	OS_ENTER_CRITICAL()		asm("	SETC	INTM")
#define	OS_EXIT_CRITICAL()		asm("	CLRC	INTM")
#define OS_TASK_SW()			asm("	TRAP	#31")

#ifndef StkDefine
#define StkDefine
//#pragma DATA_SECTION(OSSystemStk,"OSStack");
//OS_EXT 	OS_STK  OSSystemStk[OS_MAX_STK_SIZE];   /* Stack of SYSTEM task				*/
#endif



