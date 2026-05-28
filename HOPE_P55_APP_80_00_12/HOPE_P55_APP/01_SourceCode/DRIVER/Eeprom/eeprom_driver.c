/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__EEPROM_DRIVER_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define		cI2CAck				0
#define		cI2CNak				1

#define		cEepromSuccess		0
#define		cEepromFail			1
#define		cEepromInvalidAddr	2
#define		cEepromNoSpace		3
#define		cEepromVerifyOK		4

#define		cEepromWriteAddr	0xA4	// 0b1010(Default) 010(Addr,0Low,1High) 0(R/W,0Write,1Read)
#define		cEepromReadAddr		0xA5	// 0b1010(Default) 010(Addr,0Low,1High) 1(R/W,0Write,1Read)

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S gi_wEepromWaitFlag;

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


/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sI2CBitStart(void);
void	sI2CBitStop(void);
void	sI2CBitOut(INT8U bit);
INT8U	sI2CBitIn(void);
INT8U	sI2CAckIn(void);
void	sI2CByteOut(INT8U data);
INT8U	sI2CByteIn(void);
void	sEEInvertUint8(INT8U *dBuf, INT8U *srcBuf);
INT16U	swEEOneDataCRC16(INT8U ucChar,INT16U usRCin);
INT8U	sTaskEepromPageWrite(INT16U addr,INT16U length,INT8U *pdata);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sI2CBitStart(void)		
{
	mI2CBitDelay();
	mI2COutDataPort();
	mI2CDataHigh();
	mI2CClockHigh();
	mI2CBitDelay();
	mI2CBitDelay();
	mI2CBitDelay();
	mI2CDataLow();	
	mI2CBitDelay();
	mI2CClockLow();
}

void	sI2CBitStop(void)		
{
	mI2COutDataPort();
	mI2CBitDelay();
	mI2CDataLow();
	mI2CClockHigh();
	mI2CBitDelay();
	mI2CDataHigh();	
}

void	sI2CBitOut(INT8U bit)
{	
	mI2COutDataPort();
	mI2CClockLow();
	if(bit)
	{
		mI2CDataHigh();
	}
	else
	{
		mI2CDataLow();
	}
	mI2CBitDelay();
	mI2CClockHigh();
	mI2CBitDelay();
	mI2CClockLow();
}

INT8U	sI2CBitIn(void)		
{
	INT8U	temp;
	
	mI2CInDataPort();
	mI2CClockLow();
	mI2CBitDelay();
	mI2CClockHigh();
	mI2CBitDelay();
	temp=mI2CReadData();
	mI2CClockLow();
	if(temp==0)
		return(0);
	else
		return(1);
}

INT8U	sI2CAckIn(void)		
{
	INT8U ack;
	
	mI2CDataHigh();
	ack=sI2CBitIn();
	return(ack);
}

void	sI2CByteOut(INT8U data)
{
	INT8U	i;
	INT8U 	BitMask;
	
	BitMask=0x0080;
	
	for(i=0;i<8;i++)
	{
		sI2CBitOut(data&BitMask);
		BitMask=BitMask>>1;
	}
}

INT8U	sI2CByteIn(void)
{
	INT8U data;
	INT8U i;
	
	data=0;
	
	for(i=0;i<8;i++)
	{
		data<<=1;
		data+=sI2CBitIn();
	}
	return(data);
}

void	sEEInvertUint8(INT8U *dBuf, INT8U *srcBuf)
{
	INT8U i;
	INT8U tmp;
	
	tmp = 0;
	for(i = 0; i < 8; i++)
	{
		if(*srcBuf & (1 << i))
		{
			tmp |= 1 << (7 - i);
		}
	}
	*dBuf = tmp;
}

void	sEEInvertUint16(INT16U *dBuf, INT16U *srcBuf)
{
	INT8U i;
	INT16U tmp;
	
	tmp = 0;
	for(i = 0; i < 16; i++)
	{
		if(*srcBuf & (1 << i))
		{
			tmp |= 1 << (15 - i);
		}
	}
	*dBuf = tmp;
}

INT16U	swEEOneDataCRC16(INT8U ucChar,INT16U usRCin)
{
	INT16U usCPoly = 0x8005;
	INT8U i;
	
	sEEInvertUint8(&ucChar, &ucChar);
	usRCin ^= (ucChar << 8);
	for(i = 0; i < 8; i++)
	{
		if(usRCin & 0x8000)
		{
			usRCin = (usRCin << 1) ^ usCPoly;
		}
		else
		{
			usRCin = usRCin << 1;
		}
	}
	return usRCin;
}

INT16U	swEEMultiDataCRC16(INT8U *puchMsg, INT16U usDataLen)
{
	INT16U usRCin = 0xFFFF;
	INT8U ucChar = 0;
	
	while(usDataLen--)	
	{
		ucChar = *(puchMsg++);
		usRCin = swEEOneDataCRC16(ucChar,usRCin);
	}
	
	sEEInvertUint16(&usRCin, &usRCin);
	
	ucChar = usRCin >> 8;
	return(usRCin << 8 | ucChar);
}

INT8U	sbEepromPageWrite(INT16U addr,INT16U length,INT8U *pdata)
{
	INT8U ack;
	INT16U i;
	
	sI2CBitStart();
	sI2CByteOut(0xA0|((addr>>7)&0x00FE));
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CByteOut(addr&0x00FF);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	for(i=0;i<length;i++)
	{
		sI2CByteOut((*(pdata+i))&0x00FF);
		ack=sI2CAckIn();
		if(ack==cI2CNak)
		{
			sI2CBitStop();
			return(cEepromFail);
		}
	}
	
	sI2CBitStop();
	
	for(i=0;i<5000;i++)
	{
		mI2CBitDelay();
	}
	return(cEepromSuccess);
}

INT8U	sbEepromWrite(INT16U addr,INT16U length,INT8U *pbuf)
{
	INT8U	*pdata;
	INT8U	i;
	//INT16U	address;
	INT8U	temp;
	INT8U	reminder;
	INT8U	loopnum;
	INT8U	forthgoer;
	
	if(addr>cMaxAddrSize)
	{
		return(cEepromInvalidAddr);
	}
	if(addr+length>cMaxAddrSize+1)
	{
		return(cEepromNoSpace);
	}
	
	temp=addr-(addr/cPageSize)*cPageSize;
	if(temp==0)
	{
		forthgoer=0;
	}
	else
	{
		forthgoer=cPageSize-temp;
	}
	
	if(length<forthgoer)
	{
		forthgoer=length;
	}
	
	loopnum=(length-forthgoer)/cPageSize;
	reminder=length-forthgoer-loopnum*cPageSize;
	
	pdata=pbuf;
	//address=addr;
	hoEEWPONOff;
	if(forthgoer>0)
	{
		temp=sTaskEepromPageWrite(addr,forthgoer,pdata);
		if(temp!=cEepromSuccess)
		{
			hoEEWPONOn;
			return(temp);
		}
		addr+=forthgoer;
		pdata+=forthgoer/2;
	}
	if(loopnum>0)
	{
		for(i=0;i<loopnum;i++)
		{
			temp=sTaskEepromPageWrite(addr,cPageSize,pdata);
			if(temp!=cEepromSuccess)
			{
				hoEEWPONOn;
				return(temp);
			}
			addr+=cPageSize;
			pdata+=cPageSize/2;
		}
	}
	
	if(reminder>0)
	{
		temp=sTaskEepromPageWrite(addr,reminder,pdata);
		if(temp!=cEepromSuccess)
		{
			hoEEWPONOn;
			return(temp);
		}
	}
	hoEEWPONOn;
	return(cEepromSuccess);
}

INT8U	sbEepromRead(INT16U addr,INT16U length,INT8U *pbuf)
{
	INT8U i;
	INT8U ack;
	INT8U temp;
	
	if(addr>cMaxAddrSize)
	{
		return(cEepromInvalidAddr);
	}
	if(addr+length>cMaxAddrSize)
	{
		return(cEepromNoSpace);
	}
	
	sI2CBitStart();
	sI2CByteOut(cEepromWriteAddr);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CByteOut((addr>>8)&0x00FF);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}

	sI2CByteOut(addr&0x00FF);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CBitStart();
	
	sI2CByteOut(cEepromReadAddr);
	
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	
	for(i=0;i<length;i++)
	{
		temp=sI2CByteIn();
		if((i%2)==0)
		{
			*(pbuf+i/2)=(temp<<8);
		}
		else
		{
			*(pbuf+i/2)+=temp;
		}
		if(i<length-1)
		{
			sI2CBitOut(cI2CAck);
		}
	}
	sI2CBitOut(cI2CNak);
	sI2CBitStop();
	return(cEepromSuccess);		
}

INT8U	sbEepromReadChkWR(INT16U addr,INT16U length,INT16U CRC)
{
	INT8U i;
	INT8U ack;
	INT8U temp;
	INT16U wTemp;
	INT16U usRCin = 0xFFFF;
	
	if(addr>cMaxAddrSize)
	{
		return(cEepromInvalidAddr);
	}
	if(addr+length>cMaxAddrSize)
	{
		return(cEepromNoSpace);
	}
	
	sI2CBitStart();
	sI2CByteOut(cEepromWriteAddr);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CByteOut((addr>>8)&0x00FF);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}

	sI2CByteOut(addr&0x00FF);
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CBitStart();
	
	sI2CByteOut(cEepromReadAddr);
	
	ack=sI2CAckIn();
	if(ack==cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	for(i=0;i<length;i++)
	{
		temp=sI2CByteIn();
		if((i%2)==0)
		{
			wTemp=(temp<<8);
		}
		else
		{
			wTemp+=temp;
			if(i<length-2)
			{
				usRCin = swEEOneDataCRC16(wTemp,usRCin);
			}
		}
		
		if(i<length-1)
		{
			sI2CBitOut(cI2CAck);
		}
	}
	sI2CBitOut(cI2CNak);
	sI2CBitStop();
	
	if(wTemp == CRC)
	{
		sEEInvertUint16(&usRCin, &usRCin);
		wTemp = usRCin >> 8;
		wTemp = (usRCin << 8 | wTemp);
		if(wTemp == CRC)
		{
			return(cEepromVerifyOK);
		}
		else
		{
			return(cEepromSuccess); 
		}
	}
	else
	{
		return(cEepromSuccess);	
	}
}

void	sEepromSoftwareReset(void)
{
	INT8U	i,j=0;	
	INT16U	wdata=0;
	
	while(j++<5)
	{
		for(i=0;i<9;i++)
		{
			wdata<<=1;
			wdata+=sI2CBitIn();
		}
		
		if(wdata==0x01FF)
			break;
		else
			wdata = 0;
	}
}

INT8U	sTaskEepromPageWrite(INT16U addr,INT16U length,INT8U *pdata)
{
	INT8U ack;
	INT16U i;
	
	sI2CBitStart();
	sI2CByteOut(cEepromWriteAddr);
	ack = sI2CAckIn();
	if(ack == cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}

	sI2CByteOut((addr >> 8) & 0x00FF);
	ack = sI2CAckIn();
	if(ack == cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	sI2CByteOut(addr & 0x00FF);
	ack = sI2CAckIn();
	if(ack == cI2CNak)
	{
		sI2CBitStop();
		return(cEepromFail);
	}
	
	for(i = 0;i < length;i ++)
	{
		if((i%2) == 0)
		{
			sI2CByteOut((*(pdata + i/2))>>8);
		}
		else
		{
			sI2CByteOut((*(pdata + i/2))& 0x00FF);
		}
		ack = sI2CAckIn();
		if(ack == cI2CNak)
		{
			sI2CBitStop();
			return(cEepromFail);
		}
	}
	
	sI2CBitStop();
	while(1)
	{
		gi_wEepromWaitFlag = 1;
		while(OSMaskEventPend(~((INT16U)1<<eEepromWaitTime)) == 0);
		return(cEepromSuccess);
	}
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


