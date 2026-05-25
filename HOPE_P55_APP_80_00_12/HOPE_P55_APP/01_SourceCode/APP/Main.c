/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define __MAIN_C__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include    "Main.h"


/********************************************************************************
* Macros                                                                        *
********************************************************************************/


/********************************************************************************
* Constants                                                                     *
********************************************************************************/


/********************************************************************************
* External variables                                                            *
********************************************************************************/


/********************************************************************************
* External routine prototypes                                                   *
********************************************************************************/


/********************************************************************************
* Input variables                                                               *
********************************************************************************/


/********************************************************************************
* Output variables                                                              *
********************************************************************************/


/********************************************************************************
* Internal variables                                                            *
********************************************************************************/


/********************************************************************************
* Internal routine prototypes                                                   *
********************************************************************************/


/********************************************************************************
* Routines' implementations                                                     *
********************************************************************************/
void main(void)
 {
    sInitialDSP();				// DSP芯片外设初始化
	sInvertVoltCtrlParaInit();	// 离网逆变环路初始化
	sFBINVPFCInitial();			// 并网BUS电压外环控制参数初始化
	sFBINVController2Init();	// 并网电流内环参数初始化
	sFBBUSController2Init();

    OSInit();

    OSTaskCreate(sSupervisorJob,cMaxSuperJobTaskSize,cPrioSuper);
    OSTimerStart(cPrioSuper,0,cTimer20ms);

    OSTaskCreate(sInvLoadOPJob,cMaxInvLoadOPJobTaskSize,cPrioInvLoadOP);
    OSTimerStart(cPrioInvLoadOP,1,cTimer10ms);

    OSTaskCreate(sGridJob,cMaxGridJobTaskSize,cPrioGrid);
    OSTimerStart(cPrioGrid,3,cTimer20ms);

    OSTaskCreate(sBusBatProtJob,cMaxBusBatProtJobTaskSize,cPrioBusBatProt);
    OSTimerStart(cPrioBusBatProt,6,cTimer20ms);

    OSTaskCreate(sParallelJob,cMaxParallelJobTaskSize,cPrioParallel);
    OSTimerStart(cPrioParallel,10,cTimer8ms);

    OSTaskCreate(sInterfaceJob,cMaxInterfaceJobTaskSize,cPrioInterface);
    OSTimerStart(cPrioInterface,12,cTimer50ms);

    OSTaskCreate(sDisplayJob,cMaxDisplayJobTaskSize,cPrioDisplay);
    OSTimerStart(cPrioDisplay,14,cTimer100ms);

    OSTaskCreate(sIdleJob,cMaxIdleJobTaskSize,cPrioIdle);
    OSTimerStart(cPrioIdle,15,cTimer50ms);

    OSStart();
}


void sOSTimerStop(void)
{
    OS_ENTER_CRITICAL();
    //OSTimerStop(cPrioSuper);
    OSTimerStop(cPrioInvLoadOP);
    OSTimerStop(cPrioGrid);
    OSTimerStop(cPrioBusBatProt);
    //OSTimerStop(cPrioParallel);
    OSTimerStop(cPrioInterface);
    //OSTimerStop(cPrioDisplay);
    OS_EXIT_CRITICAL();
}

void sOSTimerStart(void)
{
    OS_ENTER_CRITICAL();
    //OSTimerStart(cPrioSuper,0,cTimer20ms);
    OSTimerStart(cPrioInvLoadOP,1,cTimer10ms);
    OSTimerStart(cPrioGrid,3,cTimer20ms);
    OSTimerStart(cPrioBusBatProt,6,cTimer20ms);
    //OSTimerStart(cPrioParallel,10,cTimer8ms);
    OSTimerStart(cPrioInterface,12,cTimer50ms);
    //OSTimerStart(cPrioIdle,14,cTimer100ms);
    OS_EXIT_CRITICAL();
}

/********************************************************************************
* Output interface Routines                                                     *
********************************************************************************/


/********************************************************************************
* Input interface Routines                                                      *
********************************************************************************/


