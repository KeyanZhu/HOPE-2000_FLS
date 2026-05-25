/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__OSCILLOGRAPH_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
typedef	INT16S (*pFuncOsc)(void);
enum	OSCILLOGRAPH_TRIG_DIR
{
	OSC_TRIG_DIR_START = 0,
	OSC_TRIG_DIR_NULL = OSC_TRIG_DIR_START,
	OSC_TRIG_DIR_EQU,		// 等于
	OSC_TRIG_DIR_NEQ,		// 不等于
	OSC_TRIG_DIR_GTR,		// 大于
	OSC_TRIG_DIR_GEQ,		// 大于或等于
	OSC_TRIG_DIR_LSS,		// 小于
	OSC_TRIG_DIR_LEQ,		// 小于或等于
	OSC_TRIG_DIR_END,
	OSC_TRIG_DIR_LEN = OSC_TRIG_DIR_END - OSC_TRIG_DIR_START
};
enum	OSCILLOGRAPH_MODE
{
	OSC_MODE_STANDBY = 0,
	OSC_MODE_READY,
	OSC_MODE_RUNNING,
	OSC_MODE_PARSING,
	OSC_MODE_UPLOAD,
	OSC_MODE_FINISHED
};
#define cErr_UnDataAddr			0x02
#define cErr_ParUnValid			0x12
#define	cOSC_SRC_NUM_MAX		100

/********************************************************************************
* Constants																		*
********************************************************************************/
pFuncOsc cGetDataSubArray[cOSC_SRC_NUM_MAX] =
{
	swReturnNull,
	swGetAdcInvVoltReal,			swGetAdcInvCurrReal,			swGetAdcBatVoltReal, 	//3
	swGetAdcOpVoltReal,				swGetAdcOpCurrReal, 			swGetAdcGridVoltReal,	//6
	swGetAdcBusVoltReal, 			swGetAdcBatCurrReal,			swGetAdcPv1VoltReal,	//9
	swGetAdcPv1BatCurrReal,			swGetAdcBusVoltReal,			swReturnNull,			//12
	swReturnNull,					swReturnNull, 					swReturnNull,			//15
	swReturnNull,					swReturnNull, 					swReturnNull,			//18
	
	swGetRInvVoltNew,				swGetRInvCurrNew,				swGetBatVoltNew, 		//21
	swGetROpVoltNew,				swGetROpCurrNew, 				swGetRLineVoltNew,		//24
	swGetBusVoltNew, 				swGetBusCurrNew,				swGetPv1VoltNew,		//27
	swGetPv1BatCurrNew,				swGetRInvDcVoltNew,				swReturnNull,			//30
	swReturnNull,					swReturnNull, 					swReturnNull,			//33
	swReturnNull,					swReturnNull, 					swReturnNull,			//36
	
	swGetRInvVoltFilter,			swGetRInvCurrFilter,			swGetBatVoltFilter, 	//39
	swGetROpVoltFilter,				swGetROpCurrFilter, 			swGetRLineVoltFilter,	//42
	swGetBusVoltFilter, 			swGetBusCurrFilter,				swGetPv1VoltFilter,		//45
	swGetPv1BatCurrFilter,			swReturnNull,					swReturnNull,			//48
	swReturnNull,					swReturnNull, 					swReturnNull,			//51
	swReturnNull,					swReturnNull, 					swReturnNull,			//54
	
	swGetdwUd,						swGetdwUq,						swGetdwUd_Filt, 		//57
	swGetdwUq_Filt,					swReturnNull, 					swReturnNull,			//60
	swGetInvVoltCntl, 				swGetwInvVref,					sGetLoopOutput,			//63
	
	swGetfPDCDCImo,					swReturnNull,					swReturnNull,			//66
	swReturnNull,					swReturnNull, 					swReturnNull,			//69
	swReturnNull,					swReturnNull, 					swReturnNull,			//72
	
	wGetRSinPointerwThetaTemp,		swGetRLineRms3timeAvgPeakTemp,	swGetInvKpwm,			//75
	swGetInvPWM,					swGetInvRPInvPWM,				swGetInvRNInvPWM,		//78
	swGetg_wLoopOutput,					swGetg_dwInvVoltCtrlVo,					swReturnNull,			//81
	
	swGetDefSrcAddr2,				swGetDefSrcAddr3,				swGetDefSrcAddr4,		//84
	swGetDefSrcAddr5,				swGetDefSrcAddr6,				swGetDefSrcAddr7,		//87
	swGetDefSrcAddr8,				swReturnNull,					swReturnNull,			//90
	
	swGetOscTestData1,				swGetOscTestData2,				swGetOscTestData3,		//93
	swGetOscTestData4,				swGetOscTestData5,				swGetOscTestData6,		//96
	swGetOscTestData7,				swGetOscTestData8,				swReturnNull,			//99
};

/********************************************************************************
* External variables															*
********************************************************************************/


/********************************************************************************
* External routine prototypes													*
********************************************************************************/


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16U	wOscMode;
INT16U	wOscSampRate;
INT16U	wOscChMux;
INT16U	wOscChNums;
INT16U	wOscChLen;
INT16U	wOscChSrc[8];
INT16U	wOscTrigLen;
INT16U	wOscTrigSrc;
INT16U	wOscTrigDir;
INT16S	wOscTrigVal;

/********************************************************************************
* Output variables																*
********************************************************************************/
UNOscillographData	strOscData;

/********************************************************************************
* Internal variables															*
********************************************************************************/
UNOscillographCmd	strOscCmd;
INT16U	wOscSampCnt;
INT16U	wOscChCnt;
INT16U	wOscTrigEn;
INT16U	wOscTrigCnt;
INT16U	wOscHeadCnt;
INT16U	wOscUploadCnt;
INT8U	bOscTestEnTrig;
INT16S	wOscTestData1;
INT16S	wOscTestData2;
INT16S	wOscTestData3;
INT16S	wOscTestData4;
INT16S	wOscTestData5;
INT16S	wOscTestData6;
INT16S	wOscTestData7;
INT16S	wOscTestData8;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sArrayConvert(INT16U *pBuff, INT16U start, INT16U end);
void	sOscParaUpdate(void);
void	cOscDataParsing(void);
void	sOscTestPara(void);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sOscillographInit(void)
{
	INT16S i;
	
	wOscMode = OSC_MODE_STANDBY;
	wOscSampRate = 0;
	wOscChMux = 0;
	wOscChNums = 0;
	wOscChLen = 0;
	for(i = 0; i < OSCILLOGRAPH_CHANNEL_NUM; i++)
	{
		wOscChSrc[i] = 0;
	}
	wOscTrigLen = 0;
	wOscTrigSrc = 0;
	wOscTrigDir = 0;
	wOscTrigVal = 0;
	for(i = 0; i < cOscillographDataLen; i++)
	{
		strOscData.wBuff[i] = 0;
	}
	wOscSampCnt = 0;
	wOscChCnt = 0;
	wOscTrigEn = 0;
	wOscTrigCnt = 0;
	wOscHeadCnt = 0;
}

void	sOscillographMode(void)
{
	switch(wOscMode)
	{
		case OSC_MODE_STANDBY:
			strOscCmd.Stru.wOscMode = 0;
			sOscTestPara();
		break;
		case OSC_MODE_READY:
			sOscParaUpdate();
			strOscCmd.Stru.wOscMode = 1;	// 设置录波参数
			wOscMode = OSC_MODE_RUNNING;
		break;
		case OSC_MODE_RUNNING:
			strOscCmd.Stru.wOscMode = 2;	// 录波中
		break;
		case OSC_MODE_PARSING:
			cOscDataParsing();
			wOscMode = OSC_MODE_UPLOAD;
		break;
		case OSC_MODE_UPLOAD:
			strOscCmd.Stru.wOscMode = 3;	// 录波完成
			//if(++wOscUploadCnt >= 100)		// 100*50ms=5s
			if(++wOscUploadCnt >= 600)		// 600*50ms=30s
			{
				wOscUploadCnt = 0;
				wOscMode = OSC_MODE_FINISHED;
			}
		break;
		case OSC_MODE_FINISHED:
			wOscMode = OSC_MODE_STANDBY;
		break;
		default:
			wOscMode = OSC_MODE_STANDBY;
		break;
	}
}

void	sOscillographCapturing(void)
{
	INT16U i, j, index;
	
	if(wOscMode != OSC_MODE_RUNNING)
	{
		return;
	}
	
	// 触发
	if(wOscTrigEn == false)
	{
		if(wOscTrigDir == OSC_TRIG_DIR_EQU)
		{
			if(cGetDataSubArray[wOscTrigSrc]() == wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else if(wOscTrigDir == OSC_TRIG_DIR_NEQ)
		{
			if(cGetDataSubArray[wOscTrigSrc]() != wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else if(wOscTrigDir == OSC_TRIG_DIR_GTR)
		{
			if(cGetDataSubArray[wOscTrigSrc]() > wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else if(wOscTrigDir == OSC_TRIG_DIR_GEQ)
		{
			if(cGetDataSubArray[wOscTrigSrc]() >= wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else if(wOscTrigDir == OSC_TRIG_DIR_LSS)
		{
			if(cGetDataSubArray[wOscTrigSrc]() < wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else if(wOscTrigDir == OSC_TRIG_DIR_LEQ)
		{
			if(cGetDataSubArray[wOscTrigSrc]() <= wOscTrigVal)
			{
				wOscTrigEn = true;
			}
		}
		else
		{
			wOscTrigEn = true;
		}
	}
	
	// 采样速率控制
	if(++wOscSampCnt < wOscSampRate)
	{
		return;
	}
	wOscSampCnt = 0;
	
	// 缓存录波数据
	for(i = 0, j = 0; i < OSCILLOGRAPH_CHANNEL_NUM; i++)
	{
		if(wOscChMux & (1 << i))
		{
			index = (INT16U)wOscChLen * j + wOscChCnt;
			if(index >= cOscillographDataLen)	index = cOscillographDataLen - 1;
			strOscData.wBuff[index] = cGetDataSubArray[wOscChSrc[i]]();
			j++;
		}
	}
	if(++wOscChCnt >= wOscChLen)
	{
		wOscChCnt = 0;
	}
	
	// 已经触发
	if(wOscTrigEn)
	{
		if(++wOscTrigCnt >= wOscTrigLen)
		{
			wOscTrigCnt = 0;
			wOscHeadCnt = wOscChCnt;
			wOscMode = OSC_MODE_PARSING;
		}
	}
}

INT16U	swOscillographDataRead(INT16U RdAddr)
{
	INT16U	*pwTemp;
	
	pwTemp = (INT16U *)&strOscData.wBuff;
	pwTemp += RdAddr - OSCILLOGRAPH_DATA_BASE_ADDR;
	return(*pwTemp);
}

INT16U	swOscillographCmdRead(INT16U RdAddr)
{
	INT16U	*pwTemp;
	
	pwTemp = (INT16U *)&strOscCmd.wBuff;
	pwTemp += RdAddr - OSCILLOGRAPH_CMD_BASE_ADDR;
	return(*pwTemp);
}

INT8U	swOscillographCmdWrite(INT16U WrAddr, INT16U WrData)
{
	INT16U ret = 0;
	
	WrAddr -= OSCILLOGRAPH_CMD_BASE_ADDR;
	switch(WrAddr)
	{
		case OSC_CMD_Status:
			if(WrData == 1)
			{
				if(wOscMode == OSC_MODE_STANDBY)
				{
					wOscMode = OSC_MODE_READY;
				}
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_TotalLen:
			if(WrData <= cOscillographDataLen)
			{
				strOscCmd.Stru.wTotalLen = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_SampRate:
			strOscCmd.Stru.wSampRate = WrData;
		break;
		case OSC_CMD_ChMux:
			if(WrData <= 0xFF)
			{
				strOscCmd.Stru.wChMux = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch1Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh1Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch2Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh2Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch3Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh3Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch4Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh4Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch5Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh5Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch6Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh6Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch7Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh7Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_Ch8Src:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wCh8Src = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_TrigSrc:
			if(WrData < cOSC_SRC_NUM_MAX)
			{
				strOscCmd.Stru.wTrigSrc = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_TrigDir:
			if(WrData < OSC_TRIG_DIR_LEN)
			{
				strOscCmd.Stru.wTrigDir = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_TrigVal:
			strOscCmd.Stru.wTrigVal = WrData;
		break;
		case OSC_CMD_TrigDly:
			if(WrData <= cOscillographDataLen)
			{
				strOscCmd.Stru.wTrigDly = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr1:
			if(WrData < RAM_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr1 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr2:
			if(WrData < RAM_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr2 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr3:
			if(WrData < RAM_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr3 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr4:
			if(WrData < RAM_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr4 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr5:
			if(WrData < FLASH_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr5 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr6:
			if(WrData < FLASH_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr6 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr7:
			if(WrData < FLASH_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr7 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		case OSC_CMD_DefSrcAddr8:
			if(WrData < FLASH_SIZE_MAX)
			{
				strOscCmd.Stru.wDefSrcAddr8 = WrData;
			}
			else
			{
				ret = cErr_ParUnValid;
			}
		break;
		default:
			ret = cErr_UnDataAddr;
		break;
	}
	
	return ret;
}

// 数组向左移动K位
void	sArrayConvert(INT16U *pBuff, INT16U start, INT16U end)
{
	INT16U k, temp;
	for (k = 0; k < (end - start + 1) / 2; k++)
	{
		temp = pBuff[start + k];
		pBuff[start + k] = pBuff[end - k];
		pBuff[end - k] = temp;
	}
}

void	sOscParaUpdate(void)
{
	INT16S i, wTemp;
	
	wOscSampCnt = 0;
	wOscSampRate = strOscCmd.Stru.wSampRate;
	wOscChMux = strOscCmd.Stru.wChMux;
	for(i = 0, wTemp = 0; i < OSCILLOGRAPH_CHANNEL_NUM; i++)
	{
		if(wOscChMux & (1 << i))
		{
			wTemp++;
		}
	}
	if(wTemp < 1)
	{
		wTemp = 1;
	}
	else if(wTemp > OSCILLOGRAPH_CHANNEL_NUM)
	{
		wTemp = OSCILLOGRAPH_CHANNEL_NUM;
	}
	
	wOscChNums = wTemp;
	wOscChCnt = 0;
	wOscChLen = strOscCmd.Stru.wTotalLen / wOscChNums;
	wOscChSrc[0] = strOscCmd.Stru.wCh1Src;
	wOscChSrc[1] = strOscCmd.Stru.wCh2Src;
	wOscChSrc[2] = strOscCmd.Stru.wCh3Src;
	wOscChSrc[3] = strOscCmd.Stru.wCh4Src;
	wOscChSrc[4] = strOscCmd.Stru.wCh5Src;
	wOscChSrc[5] = strOscCmd.Stru.wCh6Src;
	wOscChSrc[6] = strOscCmd.Stru.wCh7Src;
	wOscChSrc[7] = strOscCmd.Stru.wCh8Src;
	
	wTemp = (INT16S)wOscChLen - (INT16S)strOscCmd.Stru.wTrigDly;
	if(wTemp < 0)
	{
		wTemp = 0;
	}
	else if(wTemp > (INT16S)wOscChLen)
	{
		wTemp = (INT16S)wOscChLen;
	}
	wOscTrigEn = 0;
	wOscTrigCnt = 0;
	wOscTrigLen = wTemp;
	wOscTrigSrc = strOscCmd.Stru.wTrigSrc;
	wOscTrigDir = strOscCmd.Stru.wTrigDir;
	wOscTrigVal = strOscCmd.Stru.wTrigVal;
	for(i = 0; i < cOscillographDataLen; i++)
	{
		strOscData.wBuff[i] = 0;
	}
	wOscHeadCnt = 0;
	wOscUploadCnt = 0;
}

// 由于录波含有触发功能，数组是先进先出结构
// 因此数据不一定是旧数据在数组开始位置,新数据在数组末尾位置
// 所以数据需要重新整理再使用
void	cOscDataParsing(void)
{
	INT16U i;
	INT16U wStart, wHead, wEnd;
	
	wStart = 0;
	wHead = wOscHeadCnt;
	wEnd = wOscChLen - 1;
	
	if(wHead == 0)
	{
		return;
	}
	
	for(i = 0; i < wOscChNums; i++)
	{
		if(wEnd >= cOscillographDataLen) wEnd = cOscillographDataLen - 1;
		if(wHead > wEnd) wHead = wEnd;
		if(wStart > wHead) wStart = wHead;
		
		sArrayConvert(strOscData.wBuff, wStart, wHead - 1);
		sArrayConvert(strOscData.wBuff, wHead, wEnd);
		sArrayConvert(strOscData.wBuff, wStart, wEnd);
		
		wStart	+= wOscChLen;
		wHead	+= wOscChLen;
		wEnd	+= wOscChLen;
	}
}

INT16S	swReturnNull(void)
{
	return(0);	
}

void	sOscTestPara(void)
{
	if(bOscTestEnTrig != true)
	{
		return;
	}
	bOscTestEnTrig = false;
	wOscMode = OSC_MODE_READY;
	strOscCmd.Stru.wTotalLen = OSCILLOGRAPH_CACHE_LEN;
	strOscCmd.Stru.wSampRate = 1;	// 1*50us=50us
	strOscCmd.Stru.wChMux = 0x0F;	// CH1-CH4
	strOscCmd.Stru.wCh1Src = 1;
	strOscCmd.Stru.wCh2Src = 2;
	strOscCmd.Stru.wCh3Src = 3;
	strOscCmd.Stru.wCh4Src = 4;
	strOscCmd.Stru.wTrigSrc = 69;
	strOscCmd.Stru.wTrigDir = OSC_TRIG_DIR_NEQ;
	strOscCmd.Stru.wTrigVal = 0;
	strOscCmd.Stru.wTrigDly = 250;
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetDefSrcAddr1(void)
{
	INT16U *pSrcData = (INT16U *)(RAM_ADDR_START + strOscCmd.Stru.wDefSrcAddr1);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr2(void)
{
	INT16U *pSrcData = (INT16U *)(RAM_ADDR_START + strOscCmd.Stru.wDefSrcAddr2);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr3(void)
{
	INT16U *pSrcData = (INT16U *)(RAM_ADDR_START + strOscCmd.Stru.wDefSrcAddr3);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr4(void)
{
	INT16U *pSrcData = (INT16U *)(RAM_ADDR_START + strOscCmd.Stru.wDefSrcAddr4);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr5(void)
{
	INT16U *pSrcData = (INT16U *)(FLASH_ADDR_START + strOscCmd.Stru.wDefSrcAddr5);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr6(void)
{
	INT16U *pSrcData = (INT16U *)(FLASH_ADDR_START + strOscCmd.Stru.wDefSrcAddr6);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr7(void)
{
	INT16U *pSrcData = (INT16U *)(FLASH_ADDR_START + strOscCmd.Stru.wDefSrcAddr7);
	return *pSrcData;
}

INT16S	swGetDefSrcAddr8(void)
{
	INT16U *pSrcData = (INT16U *)(FLASH_ADDR_START + strOscCmd.Stru.wDefSrcAddr8);
	return *pSrcData;
}

INT16S	swGetOscTestData1(void)
{
	return wOscTestData1;
}

INT16S	swGetOscTestData2(void)
{
	return wOscTestData2;
}

INT16S	swGetOscTestData3(void)
{
	return wOscTestData3;
}

INT16S	swGetOscTestData4(void)
{
	return wOscTestData4;
}

INT16S	swGetOscTestData5(void)
{
	return wOscTestData5;
}

INT16S	swGetOscTestData6(void)
{
	return wOscTestData6;
}

INT16S	swGetOscTestData7(void)
{
	return wOscTestData7;
}

INT16S	swGetOscTestData8(void)
{
	return wOscTestData8;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetOscTestData1(INT16S wValue)
{
	wOscTestData1 = wValue;
}

void	sSetOscTestData2(INT16S wValue)
{
	wOscTestData2 = wValue;
}

void	sSetOscTestData3(INT16S wValue)
{
	wOscTestData3 = wValue;
}

void	sSetOscTestData4(INT16S wValue)
{
	wOscTestData4 = wValue;
}

void	sSetOscTestData5(INT16S wValue)
{
	wOscTestData5 = wValue;
}

void	sSetOscTestData6(INT16S wValue)
{
	wOscTestData6 = wValue;
}

void	sSetOscTestData7(INT16S wValue)
{
	wOscTestData7 = wValue;
}

void	sSetOscTestData8(INT16S wValue)
{
	wOscTestData8 = wValue;
}


