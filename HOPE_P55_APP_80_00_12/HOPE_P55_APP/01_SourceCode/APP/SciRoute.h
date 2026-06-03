/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __SCI_ROUTE_H__
#define __SCI_ROUTE_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __SCI_ROUTE_C__
#define SCI_ROUTE
#else
#define SCI_ROUTE  extern
#endif

#define	cROUTE_PROT_FELICITY				0
#define	cROUTE_PROT_PYLON					1
#define	cROUTE_PROT_LUXPOWER				2
#define	cROUTE_PROT_VOLTRONIC				3
#define	cROUTE_PROT_TEST					4

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
SCI_ROUTE	void	sSciRouting(INT8U sciid);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
SCI_ROUTE	INT8U	sbGetRouteProt(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
SCI_ROUTE	void	sSetRouteProt(INT8U prot);

#endif	// __SCI_ROUTE_H__

