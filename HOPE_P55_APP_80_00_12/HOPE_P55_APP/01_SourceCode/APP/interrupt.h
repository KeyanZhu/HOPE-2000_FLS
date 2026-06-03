/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/

#ifndef _Interrupt_H_
#define _Interrupt_H_
//#include "cpu\registers.h"
#define INT16U  	unsigned int
#define INT16S  	  signed int

/********************************************************************************
* define 																		*
********************************************************************************/

										
																				
										
						
/********************************************************************************
* Routines' implementations														*
********************************************************************************/										
extern interrupt void isrSCIAReceive(void);
extern interrupt void isrSCIATransmit(void);
extern interrupt void isrSCIBReceive(void);
extern interrupt void isrSCIBTransmit(void);
extern interrupt void isrSCICReceive(void);
extern interrupt void isrSCICTransmit(void);

extern interrupt void isrLineZero(void);

extern interrupt void isrADCA(void);	

extern interrupt void isrINV(void);
extern interrupt void isrDCDC(void);
extern interrupt void isrEPWM3(void);
extern interrupt void isrFAN(void);

//extern interrupt void isrCANA0(void);

extern interrupt void isrOSTimeBase(void);
extern interrupt void OSCtxSw(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
extern  INT16U	uwGetBATSPSRlyOn(void);
extern 	INT16U	uwGetOPRelayOn(void);
extern	INT16U	uwGetGridRelayOn(void);

extern 	INT16S	wGetRSinPointerwThetaTemp(void);



/********************************************************************************
* Input interface Routines														*
********************************************************************************/
extern 	void	sSetOPRelayOn(INT16U uwState);
extern 	void	sSetBATSPSRlyOn(INT16U uwState);
extern	void	sSetGridRelayOn(INT16U uwState);
extern	void	sSetRSinPionterQ15(INT16U uwState);


#endif


