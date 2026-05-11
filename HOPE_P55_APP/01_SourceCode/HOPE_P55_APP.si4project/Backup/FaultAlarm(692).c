/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__FAULT_ALARM_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/


/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/


/********************************************************************************
* External routine prototypes													*
********************************************************************************/
union T_FAULT_BASE T_FAULT_DATA;
union T_ALARM_BASE T_ALARM_DATA;


/********************************************************************************
* Input variables																*
********************************************************************************/
INT16U g_uwBatVoltOverCnt = 0;			// 电池软件过压故障
INT16U g_uwBatVoltOverRstCnt = 0;
INT16U g_uwDCDCCurrOverCnt = 0;			// DCDC软件过流故障
INT16U g_uwDCDCCurrOverRstCnt = 0;
INT16U g_uwLLCLPTempOverCnt = 0;		// LLC低压侧过温故障
INT16U g_uwLLCLPTempOverRstCnt = 0;
INT16U g_uwLLCTraTempOverCnt = 0;		// LLC变压器过温故障
INT16U g_uwLLCTraTempOverRstCnt = 0;
INT16U g_uwBusVoltOverCnt = 0;			// 母线软件过压故障
INT16U g_uwBusVoltOverRstCnt = 0;
INT16U g_uwBusVoltUnderCnt = 0;			// 母线欠压故障
INT16U g_uwBusVoltUnderRstCnt = 0;
INT16U g_uwBusSoftTimeOutCnt = 0;		// 母线软启故障
INT16U g_uwBusSoftTimeOutRstCnt = 0;
INT16U g_uwInvSoftTimeOutCnt = 0;		// 逆变软起故障
INT16U g_uwInvSoftTimeOutRstCnt = 0;
INT16U g_uwInvVoltHighCnt = 0;			// 逆变电压故障
INT16U g_uwInvVoltHighRstCnt = 0;
INT16U g_uwInvCurrOverCnt = 0;			// 逆变软件过流故障
INT16U g_uwInvCurrOverRstCnt = 0;
INT16U g_uwInvHWCurrOverCnt = 0;		// 逆变硬件过流故障
INT16U g_uwInvHWCurrOverRstCnt = 0;
INT16U g_uwInvShortCnt = 0;				// 逆变短路故障
INT16U g_uwInvShortRstCnt = 0;
INT16U g_uwInvCircirtTempOverCnt = 0;	// 逆变散热器过温故障
INT16U g_uwInvCircirtTempOverRstCnt = 0;
INT16U g_uwInvNtcConnectCnt = 0;		// 逆变散热器NTC未接
INT16U g_uwInvNtcConnectRstCnt = 0;
INT16U g_uwOverLoadCnt = 0;				// 负载过载故障
INT16U g_uwOverLoadRstCnt = 0;
INT16U g_uwOutputVoltLowCnt = 0;		// 输出电压低压故障
INT16U g_uwOutputVoltLowRstCnt = 0;
INT16U g_uwOutputVoltHighCnt = 0;		// 输出电压高压故障
INT16U g_uwOutputVoltHighRstCnt = 0;
INT16U g_uwBatHNtcConnectCnt = 0;		// 电池正 NTC未接/过温		
INT16U g_uwBatHNtcConnectRstCnt = 0;			
INT16U g_uwBatLNtcConnectCnt = 0;		// 电池负 NTC未接/过温 	
INT16U g_uwBatLNtcConnectRstCnt = 0;			
INT16U g_uwGridCurrOverCnt = 0;			// 市电过流
INT16U g_uwGridCurrOverRstCnt = 0;	
INT16U g_uwOPCurrOverCnt = 0;			// 输出电流过流
INT16U g_uwOPCurrOverRstCnt = 0;	

/********************************************************************************
* Output variables																*
********************************************************************************/



/********************************************************************************
* Internal variables															*
********************************************************************************/


/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sFaultAlarmInit(void)			// 故障告警标识初始化
{
	INT8U i;
	
	for(i = 0; i < cFaultBusNum; i++)
	{
		T_FAULT_DATA.uwData[i] = 0;
	}
	
	i = 0;
	for(i = 0; i < cAlarmBusNum; i++)
	{
		T_ALARM_DATA.uwData[i] = 0;
	}	
}

void sFaultRstCntProc(INT16U uwFilter)
{
	static INT16U s_uwOneSecCnt = 0;

	if(++s_uwOneSecCnt >= uwFilter)	//1sec
	{
		s_uwOneSecCnt = 0;
		g_uwBatVoltOverRstCnt++;	
		g_uwDCDCCurrOverRstCnt++;	
		g_uwLLCLPTempOverRstCnt++;
		g_uwLLCTraTempOverRstCnt++;	
		g_uwBusVoltOverRstCnt++;	
		g_uwBusVoltUnderRstCnt++;	
		g_uwBusSoftTimeOutRstCnt++;		
		g_uwInvSoftTimeOutRstCnt++;	
		g_uwInvVoltHighRstCnt++;	
		g_uwInvCurrOverRstCnt++;	
		g_uwInvHWCurrOverRstCnt++;	
		g_uwInvShortRstCnt++;
		g_uwInvCircirtTempOverRstCnt++;	
		g_uwInvNtcConnectRstCnt++;	
		g_uwOverLoadRstCnt++;	
		g_uwOutputVoltLowRstCnt++;
		g_uwOutputVoltHighRstCnt++;
		g_uwBatHNtcConnectRstCnt++;
		g_uwBatLNtcConnectRstCnt++;
		g_uwGridCurrOverCnt++;
		g_uwOPCurrOverCnt++;
		
	}

	if(g_uwBatVoltOverCnt > 0 && g_uwBatVoltOverCnt < 3)
	{
		if(g_uwBatVoltOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBatVoltOverRstCnt = 0;
			g_uwBatVoltOverCnt = 0;
		}
	}
	else
	{
		g_uwBatVoltOverRstCnt = 0;
	}

	if(g_uwDCDCCurrOverCnt > 0 && g_uwDCDCCurrOverCnt < 3)
	{
		if(g_uwDCDCCurrOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwDCDCCurrOverRstCnt = 0;
			g_uwDCDCCurrOverCnt = 0;
		}
	}
	else
	{
		g_uwDCDCCurrOverRstCnt = 0;
	}

	if(g_uwLLCLPTempOverCnt > 0 && g_uwLLCLPTempOverCnt < 3)
	{
		if(g_uwLLCLPTempOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwLLCLPTempOverRstCnt = 0;
			g_uwLLCLPTempOverCnt = 0;
		}
	}
	else
	{
		g_uwLLCLPTempOverRstCnt = 0;
	}

	if(g_uwLLCTraTempOverCnt > 0 && g_uwLLCTraTempOverCnt < 3)
	{
		if(g_uwLLCTraTempOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwLLCTraTempOverRstCnt = 0;
			g_uwLLCTraTempOverCnt = 0;
		}
	}
	else
	{
		g_uwLLCTraTempOverRstCnt = 0;
	}

	if(g_uwBusVoltOverCnt > 0 && g_uwBusVoltOverCnt < 3)
	{
		if(g_uwBusVoltOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBusVoltOverRstCnt = 0;
			g_uwBusVoltOverCnt = 0;
		}
	}
	else
	{
		g_uwBusVoltOverRstCnt = 0;
	}

	if(g_uwBusVoltUnderCnt > 0 && g_uwBusVoltUnderCnt < 3)
	{
		if(g_uwBusVoltUnderRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBusVoltUnderRstCnt = 0;
			g_uwBusVoltUnderCnt = 0;
		}
	}
	else
	{
		g_uwBusVoltUnderRstCnt = 0;
	}

	if(g_uwBusSoftTimeOutCnt > 0 && g_uwBusSoftTimeOutCnt < 3)
	{
		if(g_uwBusSoftTimeOutRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBusSoftTimeOutRstCnt = 0;
			g_uwBusSoftTimeOutCnt = 0;
		}
	}
	else
	{
		g_uwBusSoftTimeOutRstCnt = 0;
	}

	if(g_uwInvSoftTimeOutCnt > 0 && g_uwInvSoftTimeOutCnt < 3)
	{
		if(g_uwInvSoftTimeOutRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvSoftTimeOutRstCnt = 0;
			g_uwInvSoftTimeOutCnt = 0;
		}
	}
	else
	{
		g_uwInvSoftTimeOutRstCnt = 0;
	}

	if(g_uwInvVoltHighCnt > 0 && g_uwInvVoltHighCnt < 3)
	{
		if(g_uwInvVoltHighRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvVoltHighRstCnt = 0;
			g_uwInvVoltHighCnt = 0;
		}
	}
	else
	{
		g_uwInvVoltHighRstCnt = 0;
	}

	if(g_uwInvCurrOverCnt > 0 && g_uwInvCurrOverCnt < 3)
	{
		if(g_uwInvCurrOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvCurrOverRstCnt = 0;
			g_uwInvCurrOverCnt = 0;
		}
	}
	else
	{
		g_uwInvCurrOverRstCnt = 0;
	}

	if(g_uwInvHWCurrOverCnt > 0 && g_uwInvHWCurrOverCnt < 3)
	{
		if(g_uwInvHWCurrOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvHWCurrOverRstCnt = 0;
			g_uwInvHWCurrOverCnt = 0;
		}
	}
	else
	{
		g_uwInvHWCurrOverRstCnt = 0;
	}

	if(g_uwInvShortCnt > 0 && g_uwInvShortCnt < 3)
	{
		if(g_uwInvShortRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvShortRstCnt = 0;
			g_uwInvShortCnt = 0;
		}
	}
	else
	{
		g_uwInvShortRstCnt = 0;
	}

	if(g_uwInvCircirtTempOverCnt > 0 && g_uwInvCircirtTempOverCnt < 3)
	{
		if(g_uwInvCircirtTempOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvCircirtTempOverRstCnt = 0;
			g_uwInvCircirtTempOverCnt = 0;
		}
	}
	else
	{
		g_uwInvCircirtTempOverRstCnt = 0;
	}

	if(g_uwInvNtcConnectCnt > 0 && g_uwInvNtcConnectCnt < 3)
	{
		if(g_uwInvNtcConnectRstCnt > 3600)		//60*60 = 1H
		{
			g_uwInvNtcConnectRstCnt = 0;
			g_uwInvNtcConnectCnt = 0;
		}
	}
	else
	{
		g_uwInvNtcConnectRstCnt = 0;
	}

	if(g_uwOverLoadCnt > 0 && g_uwOverLoadCnt < 3)
	{
		if(g_uwOverLoadRstCnt > 3600)		//60*60 = 1H
		{
			g_uwOverLoadRstCnt = 0;
			g_uwOverLoadCnt = 0;
		}
	}
	else
	{
		g_uwOverLoadRstCnt = 0;
	}

	if(g_uwOutputVoltLowCnt > 0 && g_uwOutputVoltLowCnt < 3)
	{
		if(g_uwOutputVoltLowRstCnt > 3600)		//60*60 = 1H
		{
			g_uwOutputVoltLowRstCnt = 0;
			g_uwOutputVoltLowCnt = 0;
		}
	}
	else
	{
		g_uwOutputVoltLowRstCnt = 0;
	}

	if(g_uwOutputVoltHighCnt > 0 && g_uwOutputVoltHighCnt < 3)
	{
		if(g_uwOutputVoltHighRstCnt > 3600)		//60*60 = 1H
		{
			g_uwOutputVoltHighRstCnt = 0;
			g_uwOutputVoltHighCnt = 0;
		}
	}
	else
	{
		g_uwOutputVoltHighRstCnt = 0;
	}

	if(g_uwBatHNtcConnectCnt > 0 && g_uwBatHNtcConnectCnt < 3)
	{
		if(g_uwBatHNtcConnectRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBatHNtcConnectRstCnt = 0;
			g_uwBatHNtcConnectCnt = 0;
		}
	}
	else
	{
		g_uwBatHNtcConnectRstCnt = 0;
	}	

	if(g_uwBatLNtcConnectCnt > 0 && g_uwBatLNtcConnectCnt < 3)
	{
		if(g_uwBatLNtcConnectRstCnt > 3600)		//60*60 = 1H
		{
			g_uwBatLNtcConnectRstCnt = 0;
			g_uwBatLNtcConnectCnt = 0;
		}
	}
	else
	{
		g_uwBatLNtcConnectRstCnt = 0;
	}	

	if(g_uwGridCurrOverCnt > 0 && g_uwGridCurrOverCnt < 3)
	{
		if(g_uwGridCurrOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwGridCurrOverRstCnt = 0;
			g_uwGridCurrOverCnt = 0;
		}
	}
	else
	{
		g_uwGridCurrOverRstCnt = 0;
	}

	if(g_uwOPCurrOverCnt > 0 && g_uwOPCurrOverCnt < 3)
	{
		if(g_uwOPCurrOverRstCnt > 3600)		//60*60 = 1H
		{
			g_uwOPCurrOverRstCnt = 0;
			g_uwOPCurrOverCnt = 0;
		}
	}
	else
	{
		g_uwOPCurrOverRstCnt = 0;
	}
}



/********************************************************************************
* Output interface Routines														*
********************************************************************************/



