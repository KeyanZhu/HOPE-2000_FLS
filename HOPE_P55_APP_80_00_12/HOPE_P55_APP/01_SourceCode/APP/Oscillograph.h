/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __OSCILLOGRAPH_H__
#define __OSCILLOGRAPH_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __OSCILLOGRAPH_C__
#define OSCILLOGRAPH
#else
#define OSCILLOGRAPH  extern
#endif

#define	OSCILLOGRAPH_ENABLE				1		// 1=使能,0=禁止
#define	OSCILLOGRAPH_CACHE_LEN			4096	//2000	// 默认2000,支持最大8096(由RAM决定)	// 20230726 -- 157的ARM不够用了
#define	OSCILLOGRAPH_CHANNEL_NUM		8		//8		// 默认8,支持最大8通道

struct	strOscillographData
{
	INT16U wBuff[OSCILLOGRAPH_CACHE_LEN];
};

struct	strOscillographCmd
{
	INT16U wOscMode;
	INT16U wTotalLen;
	INT16U wSampRate;	// 1=1个中断周期(20kHz)
	INT16U wChMux;
	INT16U wCh1Src;
	INT16U wCh2Src;
	INT16U wCh3Src;
	INT16U wCh4Src;
	INT16U wCh5Src;
	INT16U wCh6Src;
	INT16U wCh7Src;
	INT16U wCh8Src;
	INT16U wTrigSrc;
	INT16U wTrigDir;
	INT16U wTrigVal;
	INT16U wTrigDly;
	INT16U wDefSrcAddr1;
	INT16U wDefSrcAddr2;
	INT16U wDefSrcAddr3;
	INT16U wDefSrcAddr4;
	INT16U wDefSrcAddr5;
	INT16U wDefSrcAddr6;
	INT16U wDefSrcAddr7;
	INT16U wDefSrcAddr8;
} ;

// DSP is a 16-bit processor, so the variable length is calculated according to the 16-bit length
#define	cOscillographDataLen	sizeof(struct strOscillographData)
#define	cOscillographCmdLen		sizeof(struct strOscillographCmd)

typedef union
{
	INT16U wBuff[cOscillographDataLen];
	struct strOscillographData Stru;
}UNOscillographData;

typedef union
{
	INT16U wBuff[cOscillographCmdLen];
	struct strOscillographCmd Stru;
}UNOscillographCmd;

#define OSCILLOGRAPH_DATA_BASE_ADDR	0xD000					// 录波器数据寄存器起始地址
#define OSCILLOGRAPH_DATA_LEN		cOscillographDataLen	// 录波器数据寄存器长度

#define OSCILLOGRAPH_CMD_BASE_ADDR	0xFD00					// 录波器命令起始地址
#define OSCILLOGRAPH_CMD_LEN		cOscillographCmdLen		// 录波器命令长度

enum	OSCILLOGRAPH_CMD_ID
{
	OSC_CMD_AddrStart = 0,	//0x00
	OSC_CMD_Status = OSC_CMD_AddrStart,
	OSC_CMD_TotalLen,		//0x01
	OSC_CMD_SampRate,		//0x02
	OSC_CMD_ChMux,			//0x03
	OSC_CMD_Ch1Src,			//0x04
	OSC_CMD_Ch2Src,			//0x05
	OSC_CMD_Ch3Src,			//0x06
	OSC_CMD_Ch4Src,			//0x07
	OSC_CMD_Ch5Src,			//0x08
	OSC_CMD_Ch6Src,			//0x09
	OSC_CMD_Ch7Src,			//0x0A
	OSC_CMD_Ch8Src,			//0x0B
	OSC_CMD_TrigSrc,		//0x0C
	OSC_CMD_TrigDir,		//0x0D
	OSC_CMD_TrigVal,		//0x0E
	OSC_CMD_TrigDly,		//0x0F
	OSC_CMD_DefSrcAddr1,	//0x10
	OSC_CMD_DefSrcAddr2,	//0x11
	OSC_CMD_DefSrcAddr3,	//0x12
	OSC_CMD_DefSrcAddr4,	//0x13
	OSC_CMD_DefSrcAddr5,	//0x14
	OSC_CMD_DefSrcAddr6,	//0x15
	OSC_CMD_DefSrcAddr7,	//0x16
	OSC_CMD_DefSrcAddr8,	//0x17
	OSC_CMD_AddrEnd,
	OSC_CMD_Len = OSC_CMD_AddrEnd - OSC_CMD_AddrStart
};

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
OSCILLOGRAPH	void	sOscillographInit(void);
OSCILLOGRAPH	void	sOscillographMode(void);
OSCILLOGRAPH	void	sOscillographCapturing(void);
OSCILLOGRAPH	INT16U	swOscillographDataRead(INT16U RdAddr);
OSCILLOGRAPH	INT16U	swOscillographCmdRead(INT16U RdAddr);
OSCILLOGRAPH	INT8U	swOscillographCmdWrite(INT16U WrAddr, INT16U WrData);
OSCILLOGRAPH	INT16S	swReturnNull(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
OSCILLOGRAPH	INT16S	swGetDefSrcAddr1(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr2(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr3(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr4(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr5(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr6(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr7(void);
OSCILLOGRAPH	INT16S	swGetDefSrcAddr8(void);
OSCILLOGRAPH	INT16S	swGetOscTestData1(void);
OSCILLOGRAPH	INT16S	swGetOscTestData2(void);
OSCILLOGRAPH	INT16S	swGetOscTestData3(void);
OSCILLOGRAPH	INT16S	swGetOscTestData4(void);
OSCILLOGRAPH	INT16S	swGetOscTestData5(void);
OSCILLOGRAPH	INT16S	swGetOscTestData6(void);
OSCILLOGRAPH	INT16S	swGetOscTestData7(void);
OSCILLOGRAPH	INT16S	swGetOscTestData8(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
OSCILLOGRAPH	void	sSetOscTestData1(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData2(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData3(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData4(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData5(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData6(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData7(INT16S wValue);
OSCILLOGRAPH	void	sSetOscTestData8(INT16S wValue);

#endif	// __OSCILLOGRAPH_H__


