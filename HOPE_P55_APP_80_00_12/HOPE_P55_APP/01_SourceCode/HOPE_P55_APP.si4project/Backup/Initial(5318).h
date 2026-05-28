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

#define CMPSS1_INV_BASE 		CMPSS1_BASE
#define CMPSS_PVCURR_BASE 		CMPSS4_BASE

//#################################################################################################//
#define ADCARESULT0			AdcaResultRegs.ADCRESULT0	// INV.V	A0
#define ADCARESULT1			AdcaResultRegs.ADCRESULT1	// INV.I	A2
#define ADCARESULT2			AdcaResultRegs.ADCRESULT2	// OP.I		A3
#define ADCARESULT3			AdcaResultRegs.ADCRESULT3	// VBAT.V	A4
#define ADCARESULT4			AdcaResultRegs.ADCRESULT4	// BUS.V	A5
#define ADCARESULT5			AdcaResultRegs.ADCRESULT5	// GRID.V	A6
#define ADCARESULT6			AdcaResultRegs.ADCRESULT6	// BAT.V	A9
#define ADCARESULT7			AdcaResultRegs.ADCRESULT7	// AC_12V.V	A11
#define ADCARESULT8			AdcaResultRegs.ADCRESULT8	// LV_12V.V	A12
#define ADCARESULT9			AdcaResultRegs.ADCRESULT9	// OP.V		A14
#define ADCARESULT10		AdcaResultRegs.ADCRESULT10	// LLC.OCP	A15
#define ADCARESULT11		AdcaResultRegs.ADCRESULT11	// VAR		A16
#define ADCARESULT12		AdcaResultRegs.ADCRESULT12	// BAT.I	A18
#define ADCARESULT13		AdcaResultRegs.ADCRESULT13	// B1.V		A28
#define ADCARESULT14		AdcaResultRegs.ADCRESULT14	// INV.T	A26
#define ADCARESULT15		AdcaResultRegs.ADCRESULT15	// 

#define ADCBRESULT0			AdcbResultRegs.ADCRESULT0	// PV.I				B7
#define ADCBRESULT1			AdcbResultRegs.ADCRESULT1	// PV.INCURR.TZ		B30
#define ADCBRESULT2			AdcbResultRegs.ADCRESULT2	// PV.INCURR		B0
#define ADCBRESULT3			AdcbResultRegs.ADCRESULT3	// PV.V				B1
#define ADCBRESULT4			AdcbResultRegs.ADCRESULT4	// B2.V				B4
#define ADCBRESULT5			AdcbResultRegs.ADCRESULT5	// PV.T				B27
#define ADCBRESULT6			AdcbResultRegs.ADCRESULT6	// BAT1.T			B5
#define ADCBRESULT7			AdcbResultRegs.ADCRESULT7	// BAT2.T			B11
#define ADCBRESULT8			AdcbResultRegs.ADCRESULT8	// LLC.T			B26
#define ADCBRESULT9			AdcbResultRegs.ADCRESULT9
#define ADCBRESULT10		AdcbResultRegs.ADCRESULT10
#define ADCBRESULT11		AdcbResultRegs.ADCRESULT11
#define ADCBRESULT12		AdcbResultRegs.ADCRESULT12
#define ADCBRESULT13		AdcbResultRegs.ADCRESULT13
#define ADCBRESULT14		AdcbResultRegs.ADCRESULT14
#define ADCBRESULT15		AdcbResultRegs.ADCRESULT15

#define ADCCRESULT0			AdccResultRegs.ADCRESULT0	// B.V		// C27
#define ADCCRESULT1			AdccResultRegs.ADCRESULT1
#define ADCCRESULT2			AdccResultRegs.ADCRESULT2
#define ADCCRESULT3			AdccResultRegs.ADCRESULT3				
#define ADCCRESULT4			AdccResultRegs.ADCRESULT4
#define ADCCRESULT5			AdccResultRegs.ADCRESULT5
#define ADCCRESULT6			AdccResultRegs.ADCRESULT6
#define ADCCRESULT7			AdccResultRegs.ADCRESULT7
#define ADCCRESULT8			AdccResultRegs.ADCRESULT8
#define ADCCRESULT9			AdccResultRegs.ADCRESULT9
#define ADCCRESULT10		AdccResultRegs.ADCRESULT10
#define ADCCRESULT11		AdccResultRegs.ADCRESULT11
#define ADCCRESULT12		AdccResultRegs.ADCRESULT12
#define ADCCRESULT13		AdccResultRegs.ADCRESULT13
#define ADCCRESULT14		AdccResultRegs.ADCRESULT14
#define ADCCRESULT15		AdccResultRegs.ADCRESULT15

//#define ADCBRESULT0			AdcbResultRegs.ADCRESULT0
//#define ADCBRESULT1			AdcbResultRegs.ADCRESULT1
//#define ADCBRESULT2			AdcbResultRegs.ADCRESULT2
//#define ADCBRESULT3			AdcbResultRegs.ADCRESULT3



/******************PIN define********************/
//继电器
// OP.RLY		逆变侧继电器
#define hoROPRLY     		GpioDataRegs.GPCDAT.bit.GPIO67
#define hoROPRLYOn 			GpioDataRegs.GPCSET.bit.GPIO67 = 1
#define hoROPRLYOff 		GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1
// GRID.RLY		市电继电器
#define hoGRIDRLY     		GpioDataRegs.GPBDAT.bit.GPIO59
#define hoGRIDRLYOn 		GpioDataRegs.GPBSET.bit.GPIO59 = 1
#define hoGRIDRLYOff 		GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1

// HW.OVER		硬件保护信号
#define mPVIOVER     		GpioDataRegs.GPCDAT.bit.GPIO79 		// PV.OVP		PV过流信号
#define mBATVOVER     		GpioDataRegs.GPCDAT.bit.GPIO78 		// BAT.OVP		电池过压信号
#define mBUSVOVER     		GpioDataRegs.GPCDAT.bit.GPIO77 		// BUS.OVP		BUS过压信号

// FAN CLK IN	风扇堵转检测
#define mFANINCLK1     		(GpioDataRegs.GPBDAT.bit.GPIO44)
#define mFANINCLK2     		(GpioDataRegs.GPBDAT.bit.GPIO45)

//电池软起 预充
// STAR.EN		电池软起使能
#define hoSTAR     			GpioDataRegs.GPCDAT.bit.GPIO74
#define hoSTAROn 			GpioDataRegs.GPCSET.bit.GPIO74 = 1
#define hoSTAROff 			GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1
// SR.DRV		电池充放MOS使能
#define hoSRDRV     		GpioDataRegs.GPCDAT.bit.GPIO73
#define hoSRDRVOn 			GpioDataRegs.GPCSET.bit.GPIO73 = 1
#define hoSRDRVOff 			GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1

// KEY.SNESE	开关键
#define mBATONS     		GpioDataRegs.GPCDAT.bit.GPIO72
#define mBATONSOn 			GpioDataRegs.GPCSET.bit.GPIO72 = 1
#define mBATONSOff 			GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1
// KEY2.SNESE	预留按键
#define mKEY2ONS     		GpioDataRegs.GPCDAT.bit.GPIO70
#define mKEY2ONSOn 			GpioDataRegs.GPCSET.bit.GPIO70 = 1
#define mKEY2ONSOff 		GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1

// PV.FUSE	  	PV保险丝熔断使能
#define mPVFUSE     		GpioDataRegs.GPCDAT.bit.GPIO71
#define mPVFUSEOff 			GpioDataRegs.GPCCLEAR.bit.GPIO71 = 1
#define mPVFUSEOn 			GpioDataRegs.GPCSET.bit.GPIO71 = 1

// PV.LOAD.EN	PV弱光吸收电路使能信号
#define mPVLOADEN     		GpioDataRegs.GPBDAT.bit.GPIO58
#define mPVLOADENOff 		GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1
#define mPVLOADENOn 		GpioDataRegs.GPBSET.bit.GPIO58 = 1

// SPS.EN	 	BOOST辅助电源使能信号
#define mSPSEN     			GpioDataRegs.GPBDAT.bit.GPIO57
#define mSPSENOff 			GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1
#define mSPSENOn 			GpioDataRegs.GPBSET.bit.GPIO57 = 1

// KEY.SPS(ONOFF)		关机信号/SYS辅源
#define mKEYSPS     		GpioDataRegs.GPBDAT.bit.GPIO56
#define mKEYSPSOff 			GpioDataRegs.GPBSET.bit.GPIO56 = 1
#define mKEYSPSOn 			GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1

// LCD
#define hoLCDBL     		GpioDataRegs.GPCDAT.bit.GPIO69
#define hoLCDBLOn 			GpioDataRegs.GPCSET.bit.GPIO69 = 1
#define hoLCDBLOff 			GpioDataRegs.GPCCLEAR.bit.GPIO69 = 1

#define hoLCDCS     		GpioDataRegs.GPCDAT.bit.GPIO68
#define hoLCDCSOn 			GpioDataRegs.GPCSET.bit.GPIO68 = 1
#define hoLCDCSOff 			GpioDataRegs.GPCCLEAR.bit.GPIO68 = 1

#define hoLCDCLK     		GpioDataRegs.GPADAT.bit.GPIO27
#define hoLCDCLKOn 			GpioDataRegs.GPASET.bit.GPIO27 = 1
#define hoLCDCLKOff 		GpioDataRegs.GPACLEAR.bit.GPIO27 = 1

#define hoLCDDATA     		GpioDataRegs.GPADAT.bit.GPIO26
#define hoLCDDATAOn 		GpioDataRegs.GPASET.bit.GPIO26 = 1
#define hoLCDDATAOff 		GpioDataRegs.GPACLEAR.bit.GPIO26 = 1

#define hoLCDEn     		GpioDataRegs.GPADAT.bit.GPIO25			// LCD的供电使能
#define hoLCDEnOn 			GpioDataRegs.GPASET.bit.GPIO25 = 1
#define hoLCDEnOff 			GpioDataRegs.GPACLEAR.bit.GPIO25 = 1


// WIFI.EN	 	WIFI使能信号
#define mWIFIEN     		GpioDataRegs.GPCDAT.bit.GPIO65
#define mWIFIENOff 			GpioDataRegs.GPCCLEAR.bit.GPIO65 = 1
#define mWIFIENOn 			GpioDataRegs.GPCSET.bit.GPIO65 = 1

// AUX.EN	  	AC辅助电源使能信号
#define mAUXEN     			GpioDataRegs.GPCDAT.bit.GPIO66
#define mAUXENOn 			GpioDataRegs.GPCCLEAR.bit.GPIO66 = 1
#define mAUXENOff 			GpioDataRegs.GPCSET.bit.GPIO66 = 1

// LED1
#define mLED1     			GpioDataRegs.GPADAT.bit.GPIO11
#define mLED1Off 			GpioDataRegs.GPASET.bit.GPIO11 = 1
#define mLED1On 			GpioDataRegs.GPACLEAR.bit.GPIO11 = 1
#define mLED1Toggle 		GpioDataRegs.GPATOGGLE.bit.GPIO11 = 1
// LED2
#define mLED2     			GpioDataRegs.GPADAT.bit.GPIO12
#define mLED2Off 			GpioDataRegs.GPASET.bit.GPIO12 = 1
#define mLED2On 			GpioDataRegs.GPACLEAR.bit.GPIO12 = 1
#define mLED2Toggle 		GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1
// LED3 (Run led)
#define mLED3     			GpioDataRegs.GPBDAT.bit.GPIO46
#define mLED3Off 			GpioDataRegs.GPBSET.bit.GPIO46 = 1
#define mLED3On 			GpioDataRegs.GPBCLEAR.bit.GPIO46 = 1
#define mLED3Toggle 		GpioDataRegs.GPBTOGGLE.bit.GPIO46 = 1
// LED4	(fault led)
#define mLED4     			GpioDataRegs.GPADAT.bit.GPIO29
#define mLED4Off 			GpioDataRegs.GPASET.bit.GPIO29 = 1
#define mLED4On 			GpioDataRegs.GPACLEAR.bit.GPIO29 = 1
#define mLED4Toggle 		GpioDataRegs.GPATOGGLE.bit.GPIO29 = 1

// BEEP
#define mBEEP     			GpioDataRegs.GPADAT.bit.GPIO16
#define mBEEPOff 			GpioDataRegs.GPACLEAR.bit.GPIO16 = 1
#define mBEEPOn 			GpioDataRegs.GPASET.bit.GPIO16 = 1
#define mBEEPToggle 		GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1

// EEPROM	取消WP这个控制IO，硬件默认接GND即可正常写数据
// 			需要注意的是某些AT24C512的WP管脚使能电平不一致，需要按照EEPROM数据手册来设计电路
#define hoEEWPON     		;//GpioDataRegs.GPBDAT.bit.GPIO43
#define hoEEWPONOn 			;//GpioDataRegs.GPBSET.bit.GPIO43 = 1
#define hoEEWPONOff 		;//GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1

#define mI2CBitDelay()		sDelay4us()
#define mI2CClockHigh()		GpioDataRegs.GPBSET.bit.GPIO32 = 1
#define mI2CClockLow()		GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1
#define mI2CDataHigh()		GpioDataRegs.GPASET.bit.GPIO24 = 1
#define mI2CDataLow()		GpioDataRegs.GPACLEAR.bit.GPIO24 = 1
#define mI2CReadData()		GpioDataRegs.GPADAT.bit.GPIO24

#define mI2COutDataPort()	EALLOW;\
							GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;\
							GpioCtrlRegs.GPAMUX2.bit.GPIO24= 0;\
							GpioDataRegs.GPASET.bit.GPIO24 = 1;\
							GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;\
							EDIS

#define mI2CInDataPort()	EALLOW;\
							GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1;\
							GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;\
							GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;\
							EDIS

/********************************************************************************
* Routines' implementations                                                     *
********************************************************************************/
INITIAL void    sInitialDSP(void);
INITIAL void	sInitComIsr(void);

INITIAL void    sDelay4us(void);
INITIAL void    sDelay1ms(INT8U ms);

/********************************************************************************
* Output interface Routines                                                     *
********************************************************************************/



/********************************************************************************
* Input interface Routines                                                      *
********************************************************************************/



#endif  // __INITIAL_H__

