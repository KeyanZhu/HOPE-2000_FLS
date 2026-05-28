/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        F28P55X_DEMO
File Name:      Main.h
Author:         xiaofeng
Date:           2024.07.11
Description:    None
********************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

// for test
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

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include 	<string.h>
#include 	<stdint.h>
#include 	<stdbool.h>

#include 	"kernel.h"

#include 	"Library.h"

#include 	"f28P55x_device.h"
#include 	"f28P55x_examples.h"

#include 	"Initial.h"
#include 	"interrupt.h"

#include 	"SupervisorJob.h"
#include 	"InvLoadOPJob.h"
#include 	"GridJob.h"
#include 	"BusBatProtJob.h"
#include 	"ParallelJob.h"
#include 	"InterfaceJob.h"
#include 	"DisplayJob.h"
#include 	"IdleJob.h"

#include 	"sci_driver.h"

#include 	"SciRoute.h"
#include    "SciPassthrough.h"
#include 	"ModBusProcess.h"
#include 	"InverterProcess.h"

#include 	"AdcProcess.h"



// Task priority define
#define cPrioSuper                      0
#define cPrioInvLoadOP                  1
#define cPrioGrid                       2
#define cPrioBusBatProt                 3
#define cPrioParallel                   4
#define cPrioInterface                  5
#define cPrioDisplay                    6
#define cPrioIdle                       7
#define cPrioTaskEnd                    8

// Task stack size define
#define cMaxSuperJobTaskSize            400
#define cMaxInvLoadOPJobTaskSize        700
#define cMaxGridJobTaskSize             500
#define cMaxBusBatProtJobTaskSize       500
#define cMaxParallelJobTaskSize         500
#define cMaxInterfaceJobTaskSize        500
#define cMaxDisplayJobTaskSize          400
#define cMaxIdleJobTaskSize             300

// Task timer define
#define cTimer1ms                       2
#define cTimer2ms                       4
#define cTimer5ms                       10
#define cTimer8ms                       16
#define cTimer10ms                      20
#define cTimer20ms                      40
#define cTimer50ms                      100
#define cTimer100ms                     200

// SUPERVISOR_JOB task event define
#define eSuperTimer                     0
//#define eSuperInitialOK               1
#define eSuperFault                     2
#define eSuperLineLoss                  3
//#define eSuperGFCIOver                4
#define eSuperToStandby                 5
#define eSuperToBat                     6
#define eSuperToLine                    7
#define eSuperOPRlyOn                   8
#define eSuperOPRlyOff                  9
#define eSuperToBypass                  10
//#define eSuperUserSelect              12
//#define eSuperUserSelect2             13
//#define eSuperUserSelect3             14
#define eSuperSelectPoint               15

// INVLOADOP task event define
#define eInvLoadOPTimer                 0
#define eInvLoadOPInvZero               1
#define eInvLoadOPSinZero               2
#define eInvLoadOPOutputZero            3

// GRID task event define
#define eGridTimer                      0
#define eGridLineZero                   1
#define eGridSLineZero                  2
#define eGridTLineZero                  3
#define eSYNZero                        4

// BUSBATPROT task event define
#define eGeneralTimer                   0

// PARALLEL task event define
#define eParallelTimer                  0
#define eParallelCANParsing             1
#define eParaToLineMode                 2
#define eParaToBatMode                  3
#define eParaToStandbyMode              4
#define eParaToFaultMode                5
#define eParaToBypassMode               6
#define eParaToShutDownMode             7
#define eParaOPRlyOn                    8
#define eParaOPRlyOff                   9
#define eParaBusSoftOn                  10
#define eParaToMasterRelease            11
#define eParaSYNLineLoss                12
#define eParaDataSet                    13
#define eParaSelectPoint                15

// INTERFACE task event define
#define eInterfaceTimer                 0
#define eEepromTimer                    eInterfaceTimer
#define eI2CEEpromUserSave              1
#define eI2CEEpromUser2Save             2
#define eI2CEEpromUser3Save             3
#define eI2CEEpromFacSave               4
#define eI2CEEpromFac2Save              5
#define eMCUDSPDataParsing              6
#define eEepromSaveCounter              7
#define eEepromSaveKeyNum               8
#define eEepromWaitTime                 9
#define eEepromSaveSetDate              10
#define eMPPTParsing                    11
#define e485Parsing                     12
#define e232Parsing                     13

// DISPLAY task event define
#define eDisplayTimer                   0

// IDLE task event define
#define eIdleTimer                      0

#define cHsTemp01C					1		// 1бу
#define cHsTemp15C					15		// 1бу
#define cHsTemp50C					50		// 1бу
#define cHsTemp55C					55		// 1бу
#define cHsTemp60C					60		// 1бу
#define cHsTemp65C					65		// 1бу
#define cHsTemp70C					70		// 1бу
#define cHsTemp75C					75		// 1бу
#define cHsTemp77C					77		// 1бу
#define cHsTemp78C					78		// 1бу
#define cHsTemp80C					80		// 1бу
#define cHsTemp84C					84		// 1бу
#define cHsTemp85C					85		// 1бу
#define cHsTemp86C					86		// 1бу
#define cHsTemp90C					90		// 1бу
#define cHsTemp91C					91		// 1бу
#define cHsTemp94C					94		// 1бу
#define cHsTemp95C					95		// 1бу

/********************************************************************************
* Routines' implementations                                                     *
********************************************************************************/
extern void sOSTimerStop(void);
extern void sOSTimerStart(void);

/********************************************************************************
* Output interface Routines                                                     *
********************************************************************************/


/********************************************************************************
* Input interface Routines                                                      *
********************************************************************************/


#endif  // __MAIN_H__

