/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        F28P55X_DEMO
File Name:      Initial.h
Author:         xiaofeng
Date:           2024.07.11
Description:    None
********************************************************************************/
#ifndef __INITIAL_H__
#define __INITIAL_H__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
//#include      "OS_CPU.h"

/********************************************************************************
* Macros                                                                        *
********************************************************************************/

#ifdef  __INITIAL_C__
#define INITIAL
#else
#define INITIAL extern
#endif


// The following values are used to validate PLL Frequency using DCC
#define   DCC_COUNTER0_TOLERANCE   1

#define CHAR_LENGTH     8
#define FRAME_LENGTH    1


//#################################################################################################//
#define ADCRESULT0			AdcaResultRegs.ADCRESULT0
#define ADCRESULT1			AdcaResultRegs.ADCRESULT1
#define ADCRESULT2			AdcaResultRegs.ADCRESULT2
#define ADCRESULT3			AdcaResultRegs.ADCRESULT3				
#define ADCRESULT4			AdcaResultRegs.ADCRESULT4
#define ADCRESULT5			AdcaResultRegs.ADCRESULT5
#define ADCRESULT6			AdcaResultRegs.ADCRESULT6
#define ADCRESULT7			AdcaResultRegs.ADCRESULT7
#define ADCRESULT8			AdcaResultRegs.ADCRESULT8
#define ADCRESULT9			AdcaResultRegs.ADCRESULT9
#define ADCRESULT10			AdcaResultRegs.ADCRESULT10
#define ADCRESULT11			AdcaResultRegs.ADCRESULT11
#define ADCRESULT12			AdcaResultRegs.ADCRESULT12
#define ADCRESULT13			AdcaResultRegs.ADCRESULT13
#define ADCRESULT14			AdcaResultRegs.ADCRESULT14
#define ADCRESULT15			AdcaResultRegs.ADCRESULT15

//#define ADCBRESULT0			AdcbResultRegs.ADCRESULT0
//#define ADCBRESULT1			AdcbResultRegs.ADCRESULT1
//#define ADCBRESULT2			AdcbResultRegs.ADCRESULT2
//#define ADCBRESULT3			AdcbResultRegs.ADCRESULT3

// INV
#define cPWMCntlPeriod50Hz          3906    // 19.2k = 150MHz/2/(3906) = 52us

// DCDC
#define cDCDCPeriod					1974 	// 38K   = 150MHz/2/(1974) = 26.3us

/******************PIN define********************/
// LED4
#define mLED4     			GpioDataRegs.GPADAT.bit.GPIO20
#define mLED4Off 			GpioDataRegs.GPASET.bit.GPIO20 = 1
#define mLED4On 			GpioDataRegs.GPACLEAR.bit.GPIO20 = 1
#define mLED4Toggle 		GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1
// LED5
#define mLED5     			GpioDataRegs.GPADAT.bit.GPIO21
#define mLED5Off 			GpioDataRegs.GPASET.bit.GPIO21 = 1
#define mLED5On 			GpioDataRegs.GPACLEAR.bit.GPIO21 = 1
#define mLED5Toggle 		GpioDataRegs.GPATOGGLE.bit.GPIO21 = 1

/********************************************************************************
* Routines' implementations                                                     *
********************************************************************************/
INITIAL void    sInitialDSP(void);

INITIAL void    sDelay4us(void);
INITIAL void    sDelay1ms(INT8U ms);

/********************************************************************************
* Output interface Routines                                                     *
********************************************************************************/



/********************************************************************************
* Input interface Routines                                                      *
********************************************************************************/



#endif  // __INITIAL_H__

