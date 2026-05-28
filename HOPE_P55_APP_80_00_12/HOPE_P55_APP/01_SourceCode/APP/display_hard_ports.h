/*================================================================================================*
 *FileName:  Display_Hw_port.h																																					*
 *																																																*
 *================================================================================================*/
#ifndef			__DISPLAY_HW_PORT_H__
#define			__DISPLAY_HW_PORT_H__


#define cCmdModeID			0x08
#define cWRModeID			0x0A

//Lcd Cmd define,

#define BIASThird4COCmd     0x52
#define RC256Cmd            0x30
#define SYSENCmd            0x02
#define LcdONCmd            0x06
#define WDTDIS              0x0a
#define TIMERDIS            0x08

// LCD control macro
#define	mLcdData()		    	hoLCDDATA	
#define	mLcdDataHigh()		 	hoLCDDATAOn
#define	mLcdDataLow()		  	hoLCDDATAOff

#define	mLcdClock()		    	hoLCDCLK
#define	mLcdClockHigh()	   		hoLCDCLKOn
#define	mLcdClockLow()			hoLCDCLKOff

#define	mLcdCs()		    	hoLCDCS
#define	mLcdCSHigh()		   	hoLCDCSOn
#define	mLcdCSLow()		    	hoLCDCSOff


#define	mLcdBacklight()		    hoLCDBL
#define	mLcdBacklightOn()		hoLCDBLOn
#define	mLcdBacklightOff()		hoLCDBLOff



#endif          //__DISPLAY_HW_PORT_H__

