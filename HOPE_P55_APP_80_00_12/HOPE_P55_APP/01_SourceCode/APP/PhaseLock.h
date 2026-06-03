/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __PHASE_LOCK_H__
#define __PHASE_LOCK_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __PHASE_LOCK_C__
#define PHASE_LOCK
#else
#define PHASE_LOCK  extern
#endif


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
PHASE_LOCK void sPhaseLockInitial(void);
PHASE_LOCK void sPhaseLockControl(INT16S wPhaseLockInputR,INT16S wPhaseLockInputS,INT16S wPhaseLockInputT);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
PHASE_LOCK INT16S	swGetPllTheta(void);
PHASE_LOCK INT16S	swGetInvSinPointBias(void);
PHASE_LOCK INT16S	swGetPreSinePeriodCntNew(void);
PHASE_LOCK INT16S	swGetdwUd(void);
PHASE_LOCK INT16S	swGetdwUq(void);
PHASE_LOCK INT16S	swGetdwUd_Filt(void);
PHASE_LOCK INT16S	swGetdwUq_Filt(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/

#endif	// __PHASE_LOCK_H__

