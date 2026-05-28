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
	emuADC_RINV_CURR = 0,		// INV.I		// yyyy
	emuADC_RINV_VOLT,			// INV.V		// yyyy
	emuADC_RINV_WATT,			// INV.W		// yyyy
	emuADC_RINV_DCV,			// INV.DCV		// yyyy
	emuADC_ROP_VOLT,			// OP.V			// yyyy
	emuADC_ROP_CURR,			// OP.I			// yyyy
	emuADC_ROP_WATT,			// OP.W			// yyyy
	emuADC_RLINE_VOLT,			// LINE.V		// yyyy
	emuADC_RLINE_CURR,			// LINE.I
	emuADC_PBUS_VOLT,			// BUS.V		// yyyy
	emuADC_PBUS_CURR,			// BUS.I
	emuADC_BAT_VOLT,			// BAT.V		// yyyy
	emuADC_BAT_CURR,			// BAT.I		// yyyy
	emuADC_VBAT_VOLT,			// VBAT.V		// yyyy
	emuADC_PV1_VOLT,			// PV1.V		// yyyy
	emuADC_PV1_CURR,			// PV1.I		// yyyy
	emuADC_PV1_BAT_CURR,		// PV1.BAT.I	// yyyy
	emuADC_PV1_BAT_WATT,		// PV1.BAT.W	// yyyy
	emuADC_LLC_OCP_CURR, 		// LLC.OCP		// yyyy
	emuADC_LV12V_VOLT,			// LV_12V.V		// yyyy
	emuADC_AC12V_VOLT,			// AC_12V.V		// yyyy
	emuADC_VER_VOLT,			// VER.V		// yyyy
	emuADC_HS_BATH_TEMP,		// BATH.T		// yyyy
	emuADC_HS_TW_TEMP,			// TW.T			// yyyy
	emuADC_HS_INV_TEMP, 		// INV.T		// yyyy
	emuADC_HS_PV_TEMP,			// PV.T			// yyyy
	emuADC_HS_TRA_TEMP,			// TRA.T
	emuADC_HS_BATL_TEMP,		// BATL.T
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


INT16S	swRInvCurrCal(void);		// 0.01A
INT16S	swRInvVoltCal(void);		// 0.1V
INT16S	swRInvWattCal(void);		// 1W
INT16S	swRInvDCVCal(void);			// 0.001V
INT16S	swROpVoltCal(void); 		// 0.1V
INT16S	swROpCurrCal(void); 		// 0.01A
INT16S	swROpWattCal(void); 		// 1W
INT16S	swRLineVoltCal(void);		// 0.1V
INT16S	swBusVoltCal(void);			// 0.1V
INT16S	swBatVoltCal(void);			// 0.01V
INT16S	swBatCurrCal(void);			// 0.01A
INT16S	swBatVolt2Cal(void);		// 0.01V
INT16S	swPv1VoltCal(void);			// 0.01V
INT16S	swPv1CurrCal(void);			// 0.01A
INT16S	swPv1BatCurrCal(void);		// 0.01A
INT16S	swPv1BatWattCal(void);		// W	//未考虑倍率关系，应该还要除10000
INT16S	swLLCOCPCurrCal(void);		// 0.01A
INT16S	swLV12VVoltCal(void);		// 0.01V
INT16S	swAC12VVoltCal(void);		// 0.01V
INT16S	swVerVoltCal(void);			// 机型识别
INT16S	swHsTwTempCal(void);		// 0.1℃
INT16S	swHsInvTempCal(void);		// 0.1℃
INT16S	swHsPvTempCal(void);		// 0.1℃
INT16S	swHsBatHTempCal(void);		// BATH.T  0.1℃


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
// 未处理的采样值get函数，未更新
ADC_PROCESS INT16S	swGetAdcHsConTempResult1(void);
ADC_PROCESS INT16S	swGetAdcHsInvTempResult1(void);
ADC_PROCESS INT16S	swGetAdcHsGridTempResult1(void);
ADC_PROCESS INT16S	swGetAdcGridVoltResult1(void);
ADC_PROCESS INT16S	swGetAdcInvDCVResult1(void);
ADC_PROCESS INT16S	swGetAdcInvCurrResult1(void);
ADC_PROCESS INT16S	swGetAdcInvVoltResult1(void);
ADC_PROCESS INT16S	swGetAdcBusVoltResult1(void);
ADC_PROCESS INT16S	swGetAdcBatVoltResult1(void);
ADC_PROCESS INT16S	swGetAdcHsConTempResult2(void);
ADC_PROCESS INT16S	swGetAdcHsInvTempResult2(void);
ADC_PROCESS INT16S	swGetAdcHsGridTempResult2(void);
ADC_PROCESS INT16S	swGetAdcGridVoltResult2(void);
ADC_PROCESS INT16S	swGetAdcInvDCVResult2(void);
ADC_PROCESS INT16S	swGetAdcInvCurrResult2(void);
ADC_PROCESS INT16S	swGetAdcInvVoltResult2(void);
ADC_PROCESS INT16S	swGetAdcBusVoltResult2(void);
ADC_PROCESS INT16S	swGetAdcBatVoltResult2(void);
ADC_PROCESS INT16S	swGetAdcHsConTempSample(void);
ADC_PROCESS INT16S	swGetAdcHsInvTempSample(void);
ADC_PROCESS INT16S	swGetAdcHsGridTempSample(void);
ADC_PROCESS INT16S	swGetAdcGridVoltSample(void);
ADC_PROCESS INT16S	swGetAdcInvDCVSample(void);
ADC_PROCESS INT16S	swGetAdcInvCurrSample(void);
ADC_PROCESS INT16S	swGetAdcInvVoltSample(void);
ADC_PROCESS INT16S	swGetAdcBusVoltSample(void);
ADC_PROCESS INT16S	swGetAdcBatVoltSample(void);
ADC_PROCESS INT16S	swGetHwVersion1Sample(void);

// 采样的瞬时值
ADC_PROCESS INT16S	swGetAdcOpCurrReal(void);				// OP.I
ADC_PROCESS INT16S	swGetAdcInvVoltReal(void);				// INV.V
ADC_PROCESS INT16S	swGetAdcLLCOCPCurrReal(void);			// LLC.OCP
ADC_PROCESS INT16S	swGetAdcPv1BatCurrReal(void);			// PV.BAT.I
ADC_PROCESS INT16S	swGetAdcInvCurrReal(void);				// INV.I
ADC_PROCESS INT16S	swGetAdcGridVoltReal(void);				// GRID.V
ADC_PROCESS INT16S	swGetAdcLV12VoltReal(void);				// LV_12V.V
ADC_PROCESS INT16S	swGetAdcBusVoltReal(void);				// BUS.V
ADC_PROCESS INT16S	swGetAdcBatVoltReal(void);				// BAT.V
ADC_PROCESS INT16S	swGetAdcBatVolt2Real(void);				// VBAT.V
ADC_PROCESS INT16S	swGetAdcBatCurrReal(void);				// BAT.I
ADC_PROCESS INT16S	swGetAdcOpVoltReal(void);				// OP.V
ADC_PROCESS INT16S	swGetAdcAC12VoltReal(void);				// AC_12V.V
ADC_PROCESS INT16S	swGetAdcPv1VoltReal(void);				// PV.V

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
ADC_PROCESS void	sSetInvVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetInvVoltBias(INT16S wBias);
ADC_PROCESS void	sSetInvCurrAdj(INT16S wAdj);
ADC_PROCESS void	sSetInvCurrBias(INT16S wBias);
ADC_PROCESS void	sSetOpVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetOpVoltBias(INT16S wBias);
ADC_PROCESS void	sSetOpCurrAdj(INT16S wAdj);
ADC_PROCESS void	sSetOpCurrBias(INT16S wBias);
ADC_PROCESS void	sSetGridVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetGridVoltBias(INT16S wBias);
ADC_PROCESS void	sSetBusVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetBusVoltBias(INT16S wBias);
ADC_PROCESS void	sSetBatVolt2Adj(INT16S wAdj);
ADC_PROCESS void	sSetBatVolt2Bias(INT16S wBias);
ADC_PROCESS void	sSetBatVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetBatVoltBias(INT16S wBias);
ADC_PROCESS void	sSetBatCurrAdj(INT16S wAdj);
ADC_PROCESS void	sSetBatCurrBias(INT16S wBias);
ADC_PROCESS void	sSetPvVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetPvVoltBias(INT16S wBias);
ADC_PROCESS void	sSetPvBatCurrAdj(INT16S wAdj);
ADC_PROCESS void	sSetPvBatCurrBias(INT16S wBias);
ADC_PROCESS void	sSetLLCCurrAdj(INT16S wAdj);
ADC_PROCESS void	sSetLLCCurrBias(INT16S wBias);
ADC_PROCESS void	sSetLV12VoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetLV12VoltBias(INT16S wBias);
ADC_PROCESS void	sSetAC12VoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetAC12VoltBias(INT16S wBias);
ADC_PROCESS void	sSetVerVoltAdj(INT16S wAdj);
ADC_PROCESS void	sSetVerVoltBias(INT16S wBias);

#endif	// __ADC_PROCESS_H__

