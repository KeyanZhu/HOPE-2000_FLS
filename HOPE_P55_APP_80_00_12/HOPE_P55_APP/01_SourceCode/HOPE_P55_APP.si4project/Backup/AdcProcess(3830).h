/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __ADC_PROCESS_H__
#define __ADC_PROCESS_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __ADC_PROCESS_C__
#define ADC_PROCESS
#else
#define ADC_PROCESS  extern
#endif

#define mInvVoltQ5(x)	(INT16S)(((INT32S)x * 3277 + 512) >> 10)	// 0.1V->Q5
#define mInvCurrQ5(x)	(INT16S)(((INT32S)x * 328 + 512) >> 10)		// 0.01A->Q5
#define mOPCurrQ5(x)	(INT16S)(((INT32S)x * 328 + 512) >> 10)		// 0.01A->Q5

#define mInvVoltQ7(x)	(INT16S)(((INT32S)x * 128) / 10)		// 0.1V->Q7
#define mInvCurrQ7(x)	(INT16S)(((INT32S)x * 128) / 10)		// 0.01A->Q7
#define mOPCurrQ7(x)	(INT16S)(((INT32S)x * 128) / 10)		// 0.01A->Q7


enum EMUADC_SAMPLE_ITEM
{
	emuADC_RINV_CURR = 0,		// INV.I		//
	emuADC_RINV_VOLT,			// INV.V		//
	emuADC_RINV_WATT,			// INV.W		//
	emuADC_RINV_DCV,			// INV.DCV		//
	emuADC_ROP_VOLT,			// OP.V			//
	emuADC_ROP_CURR,			// OP.I			//
	emuADC_ROP_WATT,			// OP.W			//
	emuADC_RLINE_VOLT,			// LINE.V		//
	emuADC_RLINE_CURR,			// LINE.I
	emuADC_PBUS_VOLT,			// BUS.V		//
	emuADC_PBUS_CURR,			// BUS.I
	emuADC_BAT_VOLT,			// BAT.V		//
	emuADC_BAT_CURR,			// BAT.I		//
	emuADC_VBAT_VOLT,			// VBAT.V		//
	emuADC_B1_VOLT,				// B1.V			//
	emuADC_B2_VOLT,				// B2.V			//
	emuADC_B_VOLT,				// B.V			//
	emuADC_PV1_VOLT,			// PV1.V		//
	emuADC_PVL1_CURR,			// PV1.I		//
	emuADC_PVIN_CURR,			// PVIN.I		//
	emuADC_PVINTZ_CURR,			// PVINTZ.I		//
	emuADC_PV1_BAT_CURR,		// PV1.BAT.I	//
	emuADC_PV1_BAT_WATT,		// PV1.BAT.W	//
	emuADC_LLC_OCP_CURR, 		// LLC.OCP		//
	emuADC_LV12V_VOLT,			// LV_12V.V		//
	emuADC_AC12V_VOLT,			// AC_12V.V		//
	emuADC_VER_VOLT,			// VER.V		//
	emuADC_HS_TW_TEMP,			// TW.T			//
	emuADC_HS_INV_TEMP, 		// INV.T		//
	emuADC_HS_PV_TEMP,			// PV.T			//
	emuADC_HS_TRA_TEMP,			// TRA.T
	emuADC_HS_BATH_TEMP,		// BATH.T		//
	emuADC_HS_BATL_TEMP,		// BATL.T
	emuADC_HS_BAT1_TEMP,		// BAT1.T
	emuADC_HS_BAT2_TEMP,		// BAT2.T
	emuADC_HS_LLC_TEMP,			// LLC.T
	emuADC_ITEM_MAX
};


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
ADC_PROCESS	void	sAdcInitial(void);
ADC_PROCESS	void	sAdcCoeffInit(void);
ADC_PROCESS	void	sAdcINVIsr(void);
ADC_PROCESS	void	sAdcDCDCIsr(void);
ADC_PROCESS	void	sAdcLineIsr(void);
ADC_PROCESS	void	sAdcOffsetInitial(void);
ADC_PROCESS	INT8U	sbAdcOffsetCalc(INT8U bFilter);

ADC_PROCESS	INT16S	swRInvCurrCal(void);			// 0.01A
ADC_PROCESS	INT16S	swRInvVoltCal(void); 			// 0.1V
ADC_PROCESS	INT16S	swRInvWattCal(void); 			// 1W
ADC_PROCESS	INT16S	swRInvDCVCal(void);				// 0.001V
ADC_PROCESS	INT16S	swROpVoltCal(void);				// 0.1V
ADC_PROCESS	INT16S	swROpCurrCal(void);				// 0.01A
ADC_PROCESS	INT16S	swROpWattCal(void);				// 1W
ADC_PROCESS	INT16S	swRLineVoltCal(void);			// 0.1V	
ADC_PROCESS	INT16S	swBusVoltCal(void);				// 0.1V
ADC_PROCESS	INT16S	swBatVoltCal(void);				// 0.01V
ADC_PROCESS	INT16S	swBatCurrCal(void);				// 0.01A
ADC_PROCESS	INT16S	swBatVolt2Cal(void); 			// 0.01V
ADC_PROCESS	INT16S	swB1VoltCal(void);				// 0.01V
ADC_PROCESS	INT16S	swB2VoltCal(void);				// 0.01V
ADC_PROCESS	INT16S	swBVoltCal(void);				// 0.01V	
ADC_PROCESS	INT16S	swPv1VoltCal(void);				// 0.01V
ADC_PROCESS	INT16S	swPvL1CurrCal(void);			// 0.01A
ADC_PROCESS	INT16S	swPv1BatCurrCal(void);			// 0.01A
ADC_PROCESS	INT16S	swPv1BatWattCal(void);			// W	//未考虑倍率关系，应该还要除1000
ADC_PROCESS	INT16S	swPvInTzCurrCal(void);	 		// 0.01A
ADC_PROCESS	INT16S	swPvInCurrCal(void);			// 0.01A
ADC_PROCESS	INT16S	swLLCOCPCurrCal(void);			// 0.01A
ADC_PROCESS	INT16S	swLV12VVoltCal(void);			// 0.01V
ADC_PROCESS	INT16S	swAC12VVoltCal(void);			// 0.01V
ADC_PROCESS	INT16S	swHsBat1TempCal(void);			// BAT1.T  0.1℃
ADC_PROCESS	INT16S	swHsBat2TempCal(void);			// BAT1.T  0.1℃
ADC_PROCESS	INT16S	swHsLLCTempCal(void); 			// LLC.T 0.1℃
ADC_PROCESS	INT16S	swHsInvTempCal(void);			// 0.1℃
ADC_PROCESS	INT16S	swHsPvTempCal(void); 			// 0.1℃
ADC_PROCESS	INT16S	swVerVoltCal(void);				// 机型识别

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
///////////////////////////////////////Result1
ADC_PROCESS	INT16S	swGetAdcInvVoltResult1(void);				// INV.V
ADC_PROCESS	INT16S	swGetAdcInvCurrResult1(void);				// INV.I
ADC_PROCESS	INT16S	swGetAdcOpCurrResult1(void);				// OP.I
ADC_PROCESS	INT16S	swGetAdcBatVolt2Result1(void);				// VBAT.V
ADC_PROCESS	INT16S	swGetAdcBusVoltResult1(void);				// BUS.V
ADC_PROCESS	INT16S	swGetAdcGridVoltResult1(void);				// GRID.V
ADC_PROCESS	INT16S	swGetAdcBatVoltResult1(void);				// BAT.V
ADC_PROCESS	INT16S	swGetAdcAC12VoltResult1(void);				// AC_12V.V
ADC_PROCESS	INT16S	swGetAdcLV12VoltResult1(void);				// LV_12V.V
ADC_PROCESS	INT16S	swGetAdcOpVoltResult1(void);				// OP.V
ADC_PROCESS	INT16S	swGetAdcLLCOCPCurrResult1(void);			// LLC.OCP
ADC_PROCESS	INT16S	swGetAdcVarResult1(void);					// VAR
ADC_PROCESS	INT16S	swGetAdcBatCurrResult1(void);				// BAT.I
ADC_PROCESS	INT16S	swGetAdcB1VoltResult1(void);				// B1.V
ADC_PROCESS	INT16S	swGetAdcPv1BatCurrResult1(void);			// PV.BAT.I	// PV电感电流
ADC_PROCESS	INT16S	swGetAdcPvInTzCurrResult1(void);			// PVIN.I.TZ
ADC_PROCESS	INT16S	swGetAdcPvInCurrResult1(void);				// PVIN.I
ADC_PROCESS	INT16S	swGetAdcPv1VoltResult1(void);				// PV.V
ADC_PROCESS	INT16S	swGetAdcB2VoltResult1(void);				// B2.V
ADC_PROCESS	INT16S	swGetAdcBVoltResult1(void);					// B.V


///////////////////////////////////////Result2
ADC_PROCESS	INT16S	swGetAdcInvVoltResult2(void);				// INV.V
ADC_PROCESS	INT16S	swGetAdcInvCurrResult2(void);				// INV.I
ADC_PROCESS	INT16S	swGetAdcOpCurrResult2(void);				// OP.I
ADC_PROCESS	INT16S	swGetAdcBatVolt2Result2(void);				// VBAT.V
ADC_PROCESS	INT16S	swGetAdcBusVoltResult2(void);				// BUS.V
ADC_PROCESS	INT16S	swGetAdcGridVoltResult2(void);				// GRID.V
ADC_PROCESS	INT16S	swGetAdcBatVoltResult2(void);				// BAT.V
ADC_PROCESS	INT16S	swGetAdcAC12VoltResult2(void);				// AC_12V.V
ADC_PROCESS	INT16S	swGetAdcLV12VoltResult2(void);				// LV_12V.V
ADC_PROCESS	INT16S	swGetAdcOpVoltResult2(void);				// OP.V
ADC_PROCESS	INT16S	swGetAdcLLCOCPCurrResult2(void);			// LLC.OCP
ADC_PROCESS	INT16S	swGetAdcVarResult2(void);					// VAR
ADC_PROCESS	INT16S	swGetAdcBatCurrResult2(void);				// BAT.I
ADC_PROCESS	INT16S	swGetAdcB1VoltResult2(void);				// B1.V
ADC_PROCESS	INT16S	swGetAdcPv1BatCurrResult2(void);			// PV.BAT.I	// PV电感电流
ADC_PROCESS	INT16S	swGetAdcPvInTzCurrResult2(void);			// PVIN.I.TZ
ADC_PROCESS	INT16S	swGetAdcPvInCurrResult2(void);				// PVIN.I
ADC_PROCESS	INT16S	swGetAdcPv1VoltResult2(void);				// PV.V
ADC_PROCESS	INT16S	swGetAdcB2VoltResult2(void);				// B2.V
ADC_PROCESS	INT16S	swGetAdcBVoltResult2(void);					// B.V




/////////////////////Sample
ADC_PROCESS	INT16S	swGetAdcInvVoltSample(void);				// INV.V
ADC_PROCESS	INT16S	swGetAdcInvCurrSample(void);				// INV.I
ADC_PROCESS	INT16S	swGetAdcOpCurrSample(void);					// OP.I
ADC_PROCESS	INT16S	swGetAdcBatVolt2Sample(void);				// VBAT.V
ADC_PROCESS	INT16S	swGetAdcBusVoltSample(void);				// BUS.V
ADC_PROCESS	INT16S	swGetAdcGridVoltSample(void);				// GRID.V
ADC_PROCESS	INT16S	swGetAdcBatVoltSample(void);				// BAT.V
ADC_PROCESS	INT16S	swGetAdcAC12VoltSample(void);				// AC_12V.V
ADC_PROCESS	INT16S	swGetAdcLV12VoltSample(void);				// LV_12V.V
ADC_PROCESS	INT16S	swGetAdcOpVoltSample(void);					// OP.V
ADC_PROCESS	INT16S	swGetAdcLLCOCPCurrSample(void);				// LLC.OCP
ADC_PROCESS	INT16S	swGetAdcVarSample(void);					// VAR
ADC_PROCESS	INT16S	swGetAdcBatCurrSample(void);				// BAT.I
ADC_PROCESS	INT16S	swGetAdcB1VoltSample(void);					// B1.V
ADC_PROCESS	INT16S	swGetAdcPv1BatCurrSample(void);				// PV.BAT.I	// PV电感电流
ADC_PROCESS	INT16S	swGetAdcPvInTzCurrSample(void);				// PVIN.I.TZ
ADC_PROCESS	INT16S	swGetAdcPvInCurrSample(void);				// PVIN.I
ADC_PROCESS	INT16S	swGetAdcPv1VoltSample(void);				// PV.V
ADC_PROCESS	INT16S	swGetAdcB2VoltSample(void);					// B2.V
ADC_PROCESS	INT16S	swGetAdcBVoltSample(void);					// B.V


// 采样的瞬时值
ADC_PROCESS	INT16S	swGetAdcInvVoltReal(void);				// INV.V
ADC_PROCESS	INT16S	swGetAdcInvCurrReal(void);				// INV.I
ADC_PROCESS	INT16S	swGetAdcOpCurrReal(void);				// OP.I
ADC_PROCESS	INT16S	swGetAdcBatVolt2Real(void);				// VBAT.V
ADC_PROCESS	INT16S	swGetAdcBusVoltReal(void);				// BUS.V
ADC_PROCESS	INT16S	swGetAdcGridVoltReal(void);				// GRID.V
ADC_PROCESS	INT16S	swGetAdcBatVoltReal(void);				// BAT.V
ADC_PROCESS	INT16S	swGetAdcAC12VoltReal(void);				// AC_12V.V
ADC_PROCESS	INT16S	swGetAdcLV12VoltReal(void);				// LV_12V.V
ADC_PROCESS	INT16S	swGetAdcOpVoltReal(void);				// OP.V
ADC_PROCESS	INT16S	swGetAdcLLCOCPCurrReal(void);			// LLC.OCPS
ADC_PROCESS	INT16S	swGetAdcVarReal(void);					// VAR
ADC_PROCESS	INT16S	swGetAdcBatCurrReal(void);				// BAT.I
ADC_PROCESS	INT16S	swGetAdcB1VoltReal(void);				// B1.V
ADC_PROCESS	INT16S	swGetAdcPv1BatCurrReal(void);			// PV.BAT.I	// PV电感电流
ADC_PROCESS	INT16S	swGetAdcPvInTzCurrReal(void);			// PVIN.I.TZ
ADC_PROCESS	INT16S	swGetAdcPvInCurrReal(void);				// PVIN.I
ADC_PROCESS	INT16S	swGetAdcPv1VoltReal(void);				// PV.V
ADC_PROCESS	INT16S	swGetAdcB2VoltReal(void);				// B2.V
ADC_PROCESS	INT16S	swGetAdcBVoltReal(void);				// B.V


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
ADC_PROCESS	void	sSetInvVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetInvVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetInvCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetInvCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetGridVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetGridVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetOpVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetOpVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetOpCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetOpCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetBatVolt2Adj(INT16S wAdj);
ADC_PROCESS	void	sSetBatVolt2Bias(INT16S wBias);
ADC_PROCESS	void	sSetBusVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetBusVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetBatVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetBatVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetAC12VoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetAC12VoltBias(INT16S wBias);
ADC_PROCESS	void	sSetLV12VoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetLV12VoltBias(INT16S wBias);
ADC_PROCESS	void	sSetLLCCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetLLCCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetBatCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetBatCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetB1VoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetB1VoltBias(INT16S wBias);
ADC_PROCESS	void	sSetB2VoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetB2VoltBias(INT16S wBias);
ADC_PROCESS	void	sSetBVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetBVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetPvVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetPvVoltBias(INT16S wBias);
ADC_PROCESS	void	sSetPvBatCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetPvBatCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetPvInCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetPvInCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetPvInTzCurrAdj(INT16S wAdj);
ADC_PROCESS	void	sSetPvInTzCurrBias(INT16S wBias);
ADC_PROCESS	void	sSetVerVoltAdj(INT16S wAdj);
ADC_PROCESS	void	sSetVerVoltBias(INT16S wBias);


#endif	// __ADC_PROCESS_H__

