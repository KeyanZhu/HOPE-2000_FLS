/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__SCI_ROUTE_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define cSCI_ROUTE_ADDR					0x00
#define cSCI_ROUTE_CMD					0x01
#define cSCI_ROUTE_REG_ADDR_H			0x02
#define cSCI_ROUTE_REG_ADDR_L			0x03
#define cSCI_ROUTE_REG_NUM_H			0x04
#define cSCI_ROUTE_REG_NUM_L			0x05
#define cSCI_ROUTE_CRC_H				0x02
#define cSCI_ROUTE_CRC_L				0x01

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
INT8U bRouteProt = cROUTE_PROT_FELICITY;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/

extern INT16U g_uwPassthroughUpdateFW;
extern INT16U gi_wLineWaveDetectEn;	//for test

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sSciRouting(INT8U sciid)
{
	INT8U	*RxBuff;
	//INT16U id, func, addr, nums;
	INT16U id, addr, nums;
	INT16U temp;
	
	RxBuff = pbGetSciRxBuff(sciid);
	
	// 
	id = RxBuff[cSCI_ROUTE_ADDR];
	//func = RxBuff[cSCI_ROUTE_CMD];
	addr = ((INT16U)RxBuff[cSCI_ROUTE_REG_ADDR_H] << 8) + RxBuff[cSCI_ROUTE_REG_ADDR_L];
	nums = ((INT16U)RxBuff[cSCI_ROUTE_REG_NUM_H] << 8) + RxBuff[cSCI_ROUTE_REG_NUM_L];
	
	// Route
	if(RxBuff[0]=='F'&&RxBuff[1]=='5'&&RxBuff[2]=='D'&&RxBuff[3]=='N'&&RxBuff[6]=='\r')
	{
		temp = 0x01;//sbGetSciAddress();
		if((RxBuff[4]=='0'&&RxBuff[5]=='1'))
		{
//			OS_ENTER_CRITICAL();
			// 关DCDC控制器、逆变控制器
			sSetDCDCCtrlSts(cDCDCWait);
			sSetFBInvCtrlSts(cFBWait);
			gi_wLineWaveDetectEn = false;	// for test
			// 继电器打到逆变 --> 负载
			hoROPRLYOff;
//			sSetOPRelayOn(false);

			// Flag擦除
//			IAP_BootFlagErase();

			// 跳转进入boot程序运行
			asm("   LB  0x80000");
			while(1);
//			OS_EXIT_CRITICAL();
			
			///OSEventSend(cPrioSuper, eSuperToUpgrade);
		}
		else if((RxBuff[4]==((temp/10)+'0'))&&(RxBuff[5]==((temp%10)+'0')))
		{
			//OSEventSend(cPrioSuper, eSuperToUpgrade);
		}
		bRouteProt = cROUTE_PROT_FELICITY;
	}
	else if(RxBuff[0]=='G'&&RxBuff[1]=='3'&&RxBuff[2]=='R'&&RxBuff[3]=='B'&&RxBuff[6]=='\r')	// MPPT从机
	{
		temp = 0x02;//sbGetSciAddress();
		if((RxBuff[4]=='0'&&RxBuff[5]=='2') || temp == 0x02)
		{
			if(sciid == c485_SCI)
			{
				swSetPassthrough(SCI_PASSTHROUGH_RS485_MPPT);
				g_uwPassthroughUpdateFW = true;
			}
			else if(sciid == c232_SCI)
			{
				swSetPassthrough(SCI_PASSTHROUGH_RS232_MPPT);
				g_uwPassthroughUpdateFW = true;
			}
		}
		else if((RxBuff[4]==((temp/10)+'0'))&&(RxBuff[5]==((temp%10)+'0')))
		{
			//OSEventSend(cPrioSuper, eSuperToUpgrade);
		}
		bRouteProt = cROUTE_PROT_FELICITY;
		return;
	}
	else if((RxBuff[0]=='G'&&RxBuff[1]=='5'&&RxBuff[2]=='R'&&RxBuff[3]=='C'&&RxBuff[6]=='\r')\
		 || (RxBuff[0]=='G'&&RxBuff[1]=='R'&&RxBuff[2]=='4'&&RxBuff[3]=='C'&&RxBuff[6]=='\r')\
		 || (RxBuff[0]=='G'&&RxBuff[1]=='3'&&RxBuff[2]=='C'&&RxBuff[3]=='C'&&RxBuff[6]=='\r'))
	{
		temp = 0x03;//sbGetSciAddress();
//		if((RxBuff[4]=='0'&&RxBuff[5]=='3') || temp == 0x03)
		if(((RxBuff[4]=='0'&&RxBuff[5]=='3') || temp == 0x03) && (uwGetRTDataEMSConnectNumber()>1))
		{
			// 只有一节电池包，并且电量小于20就不允许透传升级 20241119 待添加
			
			swSetPassthrough(SCI_PASSTHROUGH_RS485_RS232);
			g_uwPassthroughUpdateFW = true;
		}
		else if((RxBuff[4]==((temp/10)+'0'))&&(RxBuff[5]==((temp%10)+'0')))
		{
			//OSEventSend(cPrioSuper, eSuperToUpgrade);
		}
		bRouteProt = cROUTE_PROT_FELICITY;
		return;
	}
	else if(((sciid == c485_SCI) && (id != 0x02) && (swGetPassthrough() == SCI_PASSTHROUGH_RS485_MPPT))\
		  ||((sciid == c232_SCI) && (id != 0x02) && (swGetPassthrough() == SCI_PASSTHROUGH_RS232_MPPT))\
		  ||((sciid == c232_SCI) && (id != 0x03) && (swGetPassthrough() == SCI_PASSTHROUGH_RS485_RS232)))
	{
		if(g_uwPassthroughUpdateFW == false)
		{
			swSetPassthrough(SCI_PASSTHROUGH_NULL);
		}
		bRouteProt = cROUTE_PROT_FELICITY;
		return;
	}
	else if(id >= 0x20)
	{
		bRouteProt = cROUTE_PROT_TEST;
	}
	else if(id >= 0x20)								// 可显字符
	{
		bRouteProt = cROUTE_PROT_PYLON;
	}
	else if((addr == 0x0000) && (nums == 0x1000))	// 高低字节反
	{
		bRouteProt = cROUTE_PROT_LUXPOWER;
	}
	else if(addr < 0x0100)
	{
		bRouteProt = cROUTE_PROT_VOLTRONIC;
	}
	else
	{
		bRouteProt = cROUTE_PROT_FELICITY;
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT8U	sbGetRouteProt(void)
{
	return bRouteProt;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetRouteProt(INT8U prot)
{
	bRouteProt = prot;
}

