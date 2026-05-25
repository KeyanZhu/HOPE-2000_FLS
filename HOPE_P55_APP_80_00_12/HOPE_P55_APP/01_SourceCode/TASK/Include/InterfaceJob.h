/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INTERFACE_JOB_H__
#define __INTERFACE_JOB_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INTERFACE_JOB_C__
#define	INTERFACE_JOB
#else
#define	INTERFACE_JOB	extern
#endif

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INTERFACE_JOB	void	sInterfaceJob(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INTERFACE_JOB	INT8U	sbGetInitializeFinished(void);
INTERFACE_JOB   INT16U	swGetPassthrough(void);
INTERFACE_JOB 	INT16U	uwGetInterfaceStkChk(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INTERFACE_JOB	void	swSetPassthrough(INT16U wTemp);
INTERFACE_JOB	void	swSetPassthroughDelay(INT16U wTemp);


#endif	// __INTERFACE_JOB_H__

