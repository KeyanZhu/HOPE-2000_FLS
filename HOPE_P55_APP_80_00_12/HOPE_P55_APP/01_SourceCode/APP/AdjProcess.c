/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define			__ADJ_PROCESS_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include "Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define cErr_UnCmd						0x01
#define cErr_UnDataAddr					0x02
#define cErr_UnDataValue				0x03
#define cErr_DeviceBusy					0x06
#define cErr_PassdErr					0x10
#define cErr_CrcErr						0x11
#define cErr_ParUnValid					0x12
#define cErr_SysLock					0x13

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/


/********************************************************************************
* Output variables																*
********************************************************************************/


/********************************************************************************
* Internal variables															*
********************************************************************************/
INT16S wBatt1Ref;
INT16S wBatt2Ref;
INT16S wBatt1Real;
INT16S wBatt2Real;
/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sBattVoltAdj0(void);
INT8U	sbBattVoltAdj1(INT16S wVolt);
INT8U	sbBattVoltAdj2(INT16S wVolt);
INT8U	sbBattVoltAdj(INT16S wVolt);
INT8U	sbBattCurrAdj(INT16S wCurr);
INT8U	sbPvVoltAdj(INT16S wVolt);
INT8U	sbPvBatCurrAdj(INT16S wCurr);
INT8U	sbInvVoltAdj(INT16S wVolt);
INT8U	sbInvCurrAdj(INT16S wVolt);
INT8U	sbLineVoltAdj(INT16S wVolt);
INT8U	sbOPCurrAdj(INT16S wVolt);
INT8U	sbOPVoltAdj(INT16S wVolt);
INT8U	sbBusVoltAdj(INT16S wVolt);
INT8U	sbConvertVoltAdj(INT16S wVolt);
INT8U	sbPDCDCCurrAdj(INT16S wVolt);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/

void	sBattVoltAdj0(void)
{
	if((suwGetEEBatVoltAdj() != cEEBatVoltAdjDef) \
		|| (suwGetEEBatVoltBias() != cEEBatVoltBiasDef))
	{
		//sSetBalancePassivePause(true);	// 关闭充放电等
		
		sSetEEBatVoltAdj(cEEBatVoltAdjDef);
		sSetEEBatVoltBias(cEEBatVoltBiasDef);
		
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	
	sSetBatVoltAdj(cEEBatVoltAdjDef);
	sSetBatVoltBias(cEEBatVoltBiasDef);
	wBatt1Ref = 0;
	wBatt2Ref = 0;
	wBatt1Real = 0;
	wBatt2Real = 0;
}

INT8U	sbBattVoltAdj1(INT16S wVolt)
{
	INT8U	ret = 0;
	
	if(((wVolt > 0) && (wVolt <= 7500)) \
		&& (suwGetEEBatVoltAdj() == cEEBatVoltAdjDef) \
		&& (suwGetEEBatVoltBias() == cEEBatVoltBiasDef))
	{
		wBatt1Ref = wVolt;
		wBatt1Real = swGetBatVoltFilter();
		if(swAbs(wBatt1Real - wBatt1Ref) > 500)
		{
			ret = cErr_ParUnValid;
		}
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbBattVoltAdj2(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj, wBias;
	
	if((wVolt > 0) && (wVolt <= 7500) && (wBatt1Ref > 0) \
		&& (suwGetEEBatVoltAdj() == cEEBatVoltAdjDef) \
		&& (suwGetEEBatVoltBias() == cEEBatVoltBiasDef))
	{
		wBatt2Ref = wVolt;
		wBatt2Real = swGetBatVoltFilter();
		if((swAbs(wBatt2Real - wBatt2Ref) <= 500) \
			&& (swAbs(wBatt2Real - wBatt1Real) >= 200) \
			&& (swAbs(wBatt2Ref - wBatt1Ref) >= 200))
		{
			wAdj = (INT16S)(((INT32S)swAbs(wBatt2Ref - wBatt1Ref) << 12) / swAbs(wBatt2Real - wBatt1Real));
			wBias = (((INT32S)wBatt2Ref << 12) - ((INT32S)wBatt2Real * wAdj)) >> 5;
			if((wAdj > cEEBatVoltAdjLimitLo) && (wAdj < cEEBatVoltAdjLimitUp) \
				&& (wBias > cEEBatVoltBiasLimitLo) && (wBias < cEEBatVoltBiasLimitUp))
			{
				if(((INT16S)suwGetEEBatVoltAdj() != wAdj) || (suwGetEEBatVoltBias() != wBias))
				{
					sSetEEBatVoltAdj(wAdj);
					sSetEEBatVoltBias(wBias);
					
					sSetBatVoltAdj(wAdj);
					sSetBatVoltBias(wBias);
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		}
		else
		{
			ret = cErr_ParUnValid;
		}
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbBattVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetBatVoltFilter()) <= 500) \
		&& (swGetBatVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEBatVoltAdj() + swGetBatVoltFilter()) / swGetBatVoltFilter());
		if(wAdj > cEEBatVoltAdjLimitUp)
		{
			wAdj = cEEBatVoltAdjLimitUp;
		}
		else if(wAdj < cEEBatVoltAdjLimitLo)
		{
			wAdj = cEEBatVoltAdjLimitLo;
		}
		
		sSetBatVoltAdj(wAdj);
		sSetEEBatVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbBattCurrAdj(INT16S wCurr)
{
	INT8U	ret = 0;
//	INT16S	wAdj, wAdjPre;
//	INT16S	wCurrAbs;
//	
//	wCurrAbs = swAbs(swGetBattCurrFiltNew());
// 	if((wCurr >= 250) && (wCurrAbs >= 250))
//	{
//		if(swGetBattCurrFiltNew() > 0)
//		{
//			wAdjPre = swGetEepromBattChgCurrAdj();
//		}
//		else
//		{
//			wAdjPre = swGetEepromBattDsgCurrAdj();
//		}
//		wAdj = (INT16S)(((INT32S)wCurr * wAdjPre) / wCurrAbs);
//		if(wAdj > cEEBattCurrAdjLimitUp)
//		{
//			wAdj = cEEBattCurrAdjLimitUp;
//		}
//		else if(wAdj < cEEBattCurrAdjLimitLo)
//		{
//			wAdj = cEEBattCurrAdjLimitLo;
//		}
//		
//		sSetEepromBattChgCurrAdj(wAdj);
//		sSetBattChgCurrAdj(wAdj);
//		sSetEepromBattDsgCurrAdj(wAdj);
//		sSetBattDsgCurrAdj(wAdj);
//		
//		sSetEepromStaticMode(cEEPROM_SAVE_MODE_ENABLE);
//	}
//	else
//	{
//		ret = cErr_ParUnValid;
//	}
	
	return ret;
}

INT8U	sbPvVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetPv1VoltFilter()) <= 500) \
		&& (swGetPv1VoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEPV1VoltAdj() + swGetPv1VoltFilter()) / swGetPv1VoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetPvVoltAdj(wAdj);
		sSetEEPV1VoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbPvBatCurrAdj(INT16S wCurr)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if(1)
	{
		wAdj = (INT16S)(((INT32S)wCurr * suwGetEEPV1BatCurrAdj() + swGetPv1BatCurrFilter()) / swGetPv1BatCurrFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetPvBatCurrAdj(wAdj);
		sSetEEPV1BatCurrAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbInvVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetRInvVoltFilter()) <= 500) \
		&& (swGetRInvVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEInvVoltAdj() + swGetRInvVoltFilter()) / swGetRInvVoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetInvVoltAdj(wAdj);
		sSetEEInvVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbInvCurrAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if(1)
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEInvCurrAdj() + swGetRInvCurrFilter()) / swGetRInvCurrFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetInvCurrAdj(wAdj);
		sSetEEInvCurrAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbLineVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetRLineVoltFilter()) <= 500) \
		&& (swGetRLineVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEGridVoltAdj() + swGetRLineVoltFilter()) / swGetRLineVoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetGridVoltAdj(wAdj);
		sSetEEGridVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}
INT8U	sbOPCurrAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if(1)
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEOPCurrAdj() + swGetROpCurrFilter()) / swGetROpCurrFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetOpCurrAdj(wAdj);
		sSetEEOPCurrAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbOPVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetROpVoltFilter()) <= 500) \
		&& (swGetROpVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEOPVoltAdj() + swGetROpVoltFilter()) / swGetROpVoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetOpVoltAdj(wAdj);
		sSetEEOPVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbBusVoltAdj(INT16S wVolt)
{
	INT8U	ret = 0;
	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetBusVoltFilter()) <= 500) \
		&& (swGetBusVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * suwGetEEBUSVoltAdj() + swGetBusVoltFilter()) / swGetBusVoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetBusVoltAdj(wAdj);
		sSetEEBUSVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	
	return ret;
}

INT8U	sbBusCurrAdj(INT16S wCurr)
{
	INT8U	ret = 0;
//	INT16S	wAdj;
//	
//	if((swAbs((INT16S)wCurr - (INT16S)swGetBusCurrFilter()) <= 100) \
//		&& (swGetBusCurrFilter() >= 300) && (wCurr >= 300))
//	{
//		wAdj = (INT16S)(((INT32S)wCurr * suwGetEEBUSCurrAdj() + swGetBusCurrFilter()) / swGetBusCurrFilter());
//		if(wAdj > 8192)
//		{
//			wAdj = 8192;
//		}
//		else if(wAdj < 2048)
//		{
//			wAdj = 2048;
//		}
//		sSetBusCurrAdj(wAdj);
//		sSetEEBUSCurrAdj(wAdj);
//		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
//	}
//	else
//	{
		ret = cErr_ParUnValid;
//	}
	
	return ret;
}

INT8U	sbConvertVoltAdj(INT16S wVolt)	// LLC 电压校准
{
	INT8U	ret = 0;
/*	INT16S	wAdj;
	
	if((swAbs((INT16S)wVolt - (INT16S)swGetConverterVoltFilter()) <= 500) \
		&& (swGetConverterVoltFilter() >= 1000) && (wVolt >= 1000))
	{
		wAdj = (INT16S)(((INT32S)wVolt * swGetEepromPConvertVoltAdj()) / swGetConverterVoltFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetLLCVoltAdj(wAdj);
		sSetEepromPConvertVoltAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	*/
	return ret;
}


INT8U	sbPDCDCCurrAdj(INT16S wVolt)
{
	INT8U	ret = 0;
/*	INT16S	wAdj;
	
//	if((swAbs((INT16S)wVolt - (INT16S)swGetDcDcCurrFilter()) <= 500) \
//		&& (swGetDcDcCurrFilter() >= 1000) && (wVolt >= 1000))
	if(1)
	{
		wAdj = (INT16S)(((INT32S)wVolt * swGetEepromPDCDCCurrAdj()) / swGetDcDcCurrFilter());
		if(wAdj > 8192)
		{
			wAdj = 8192;
		}
		else if(wAdj < 2048)
		{
			wAdj = 2048;
		}
		sSetDCDCCurrAdj(wAdj);
		sSetEepromPDCDCCurrAdj(wAdj);
		sSetEeprom2Mode(cEEPROM_SAVE_ENABLE);
	}
	else
	{
		ret = cErr_ParUnValid;
	}
	*/
	return ret;
}





/********************************************************************************
* Input interface Routines														*
********************************************************************************/



