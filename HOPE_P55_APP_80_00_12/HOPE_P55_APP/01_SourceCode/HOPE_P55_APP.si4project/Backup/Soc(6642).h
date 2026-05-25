/********************************************************************************
Right Reserve:	Guangzhou Felicity Solar Technology Co., Ltd
Project:		
File Name:		Soc.h
Author:			ke
Date:			
Description:	None
********************************************************************************/
#ifndef __SOC_H__
#define __SOC_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include		"OS_CPU.h"


typedef  struct 
{
	INT8U  bCaliFlg;              //校准标志   0：未校准  1：电压校准  2：容量校准
	INT8U  bSoc;                  //1%
//	INT8U  bSoh;                  //1%
	INT16U wMaxCapacity;          //0.1mAh
	INT16U wRealCapacity;         //0.1mAh
}T_SocOutput;


extern T_SocOutput sSocOutput;


extern void sSocMain(INT16U cT100msec);



#endif	// __SOC_H__

