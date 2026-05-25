/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		SCI_DRIVER

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#define cQBufNormal				0
#define cQBufFull				1
#define	cQBufEmpty				2

// return value of read operation
#define	cSciRxRdy				0
#define	cSciRxBusy				1
#define	cSciRxBufEmpty			1

// SCIA
#define mSciAEnableRxInt()			SciaRegs.SCICTL2.bit.RXBKINTENA=1
#define mSciADisableRxInt()			SciaRegs.SCICTL2.bit.RXBKINTENA=0
#define	mSciAEnableTxInt()			SciaRegs.SCICTL2.bit.TXINTENA=1
#define	mSciADisableTxInt()			SciaRegs.SCICTL2.bit.TXINTENA=0
#define	SCIA_RX_STATUS				SciaRegs.SCIRXST.all
#define	SCIA_RX_RDY_STATUS			SciaRegs.SCIRXST.bit.RXRDY
#define SCIA_TX_RDY_STATUS			SciaRegs.SCICTL2.bit.TXRDY
#define SCIA_RX_DATA				SciaRegs.SCIRXBUF.bit.SAR
#define mSciATxData(x)				SciaRegs.SCITXBUF.all=x
#define SCIA_RX_ERROR				SciaRegs.SCIRXST.bit.RXERROR
#define mSciASwReset(x)				SciaRegs.SCICTL1.bit.SWRESET=x

// SCIB
#define mSciBEnableRxInt()			ScibRegs.SCICTL2.bit.RXBKINTENA=1
#define mSciBDisableRxInt()			ScibRegs.SCICTL2.bit.RXBKINTENA=0
#define	mSciBEnableTxInt()			ScibRegs.SCICTL2.bit.TXINTENA=1
#define	mSciBDisableTxInt()			ScibRegs.SCICTL2.bit.TXINTENA=0
#define	SCIB_RX_STATUS				ScibRegs.SCIRXST.all
#define	SCIB_RX_RDY_STATUS			ScibRegs.SCIRXST.bit.RXRDY
#define SCIB_TX_RDY_STATUS			ScibRegs.SCICTL2.bit.TXRDY
#define SCIB_RX_DATA				ScibRegs.SCIRXBUF.bit.SAR
#define mSciBTxData(x)				ScibRegs.SCITXBUF.all=x
#define SCIB_RX_ERROR				ScibRegs.SCIRXST.bit.RXERROR
#define mSciBSwReset(x)				ScibRegs.SCICTL1.bit.SWRESET=x

// SCIC
#define mSciCEnableRxInt()			ScicRegs.SCICTL2.bit.RXBKINTENA=1	// LIN --> RXENA
#define mSciCDisableRxInt()			ScicRegs.SCICTL2.bit.RXBKINTENA=0	// LIN --> RXENA
#define	mSciCEnableTxInt()			ScicRegs.SCICTL2.bit.TXINTENA=1		// LIN --> TXENA
#define	mSciCDisableTxInt()			ScicRegs.SCICTL2.bit.TXINTENA=0		// LIN --> TXENA
#define	SCIC_RX_STATUS				ScicRegs.SCIRXST.all
#define	SCIC_RX_RDY_STATUS			ScicRegs.SCIRXST.bit.RXRDY
#define SCIC_TX_RDY_STATUS			ScicRegs.SCICTL2.bit.TXRDY
#define SCIC_RX_DATA				ScicRegs.SCIRXBUF.bit.SAR			// LIN --> RD
#define mSciCTxData(x)				ScicRegs.SCITXBUF.all=x				// LIN --> RD
#define SCIC_RX_ERROR				ScicRegs.SCIRXST.bit.RXERROR
#define mSciCSwReset(x)				ScicRegs.SCICTL1.bit.SWRESET=x		// LIN --> SWnRST


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
typedef struct{
	INT8U	*pIn;
	INT8U	*pOut;
	INT8U	*pStart;
	INT16U	length;
	INT16U	size;
}QUEUE;

typedef struct{
	INT8U	bTxStatus;
	INT16U	wTxLength;
	INT8U	*pbTx;
	QUEUE	*pqRx;
}SciDrvStruct;

SciDrvStruct SciList[MAX_SCI_NO];
SciDrvStruct *pSciIndex[MAX_SCI_NO];
QUEUE QList[MAX_SCI_NO];
INT8U bSciRxBuf[MAX_SCI_RX_SIZE];
INT8U *pSciBuf = bSciRxBuf;
INT8U bSciNo = 0;

typedef struct{
	INT8U bRxLen;
	INT8U bRxLenTemp;
	INT8U bRxBuf[cSCI_RX_LEN];
	INT8U bTxBuf[cSCI_TX_LEN];
	INT8U bTaskPrio;
	INT8U bRxEvent;
	INT8U bTimeout;
	INT8U bConnectFlag;
	INT16U wDisconnectCnt;
}SciDataStruct;
SciDataStruct strSciDataList[MAX_SCI_NO];
INT8U bSciRxErrCnt[MAX_SCI_NO];
INT8U bSciTxBusyCnt[MAX_SCI_NO];

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/
void	sQInit(QUEUE *pq,INT8U *start,INT16U size); 
INT8U	sQDataIn(QUEUE	*pq,INT8U data); 
INT8U	sQDataOut(QUEUE *pq,INT8U *pdata);
INT8U	sSciRead(INT8U	sciid,INT8U *pBuf);
INT8U	sbSciGetRxData(INT8U sciid);
INT8U	sbSciGetRxRdy(INT8U sciid);
INT8U	sbSciGetTxRdy(INT8U sciid);
void	sSciTxData(INT8U sciid,INT8U data);
void	sSciStopTx(INT8U sciid);
void	sSciStartTx(INT8U sciid);
INT8U	sbSciGetRxError(INT8U sciid);
void	sSciSwReset(INT8U sciid, INT8U value);

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sSciInitial(INT8U sciid, INT8U rx_size, INT8U prio, INT8U event)
{
	QUEUE *pq;
	SciDrvStruct *psci;
	SciDataStruct *pSciData;
	
	psci=&SciList[bSciNo];
	pSciIndex[sciid]=psci;
	
	psci->pqRx=&QList[bSciNo];
	pq=psci->pqRx;
	sQInit(pq,pSciBuf,rx_size);
	pSciBuf+=rx_size;
	bSciNo++;
	
	psci->bTxStatus=cSciTxRdy;
	psci->wTxLength=0;
	
	pSciData = &strSciDataList[sciid];
	memset(&strSciDataList[sciid], 0, sizeof(SciDataStruct)); // for test
	pSciData->bTaskPrio = prio;
	pSciData->bRxEvent = event;
}

void	sSciRxTask(INT8U sciid, INT8U bTimeout)
{
	INT8U bTemp = cSciRxRdy;
	SciDataStruct *pSciData;
	
	pSciData = &strSciDataList[sciid];
	
	while(bTemp == cSciRxRdy)
	{
		bTemp = sSciRead(sciid, &pSciData->bRxBuf[pSciData->bRxLenTemp]);
		if(bTemp == cSciRxRdy)
		{
			pSciData->bTimeout = bTimeout;
			if(pSciData->bTimeout < 1)
			{
				pSciData->bTimeout = 1;
			}
			
			if(pSciData->bRxLenTemp < cSCI_RX_LEN)
			{
				pSciData->bRxLenTemp++;
			}
		}
	}
	
	if(pSciData->bRxLenTemp != 0)
	{
		if(pSciData->bTimeout == 0)
		{
			pSciData->bRxLen = pSciData->bRxLenTemp;
			pSciData->bRxLenTemp = 0;
			OSEventSend(pSciData->bTaskPrio,pSciData->bRxEvent);
		}
		else
		{
			pSciData->bTimeout--;
		}
	}
}

/************************************************************************************
*Function name: sQInit																*
*Parameters:	pq: pointer to queue structure to be initialized					*
*				start:start address of ring buffer									*
*				size:the size of the ring buffer									*
*Description:	initialize a queue structure										*
*************************************************************************************/
void	sQInit(QUEUE *pq,INT8U *start,INT16U size)
{
	pq->pIn=start;
	pq->pOut=start;
	pq->pStart=start;
	pq->length=0;
	pq->size=size;
}

/************************************************************************************
*Function name: sQDataIn															*
*Parameters:	pq: pointer to queue structure to be initialized					*
*				data:the data to be inserted into the queue 						*
*Returns:		cQBufNormal:data has been inserted into the queue					*
*				cQBufFull:the buffer is full										*
*Description:	insert a data into the queue										*
*************************************************************************************/
INT8U	sQDataIn(QUEUE	*pq,INT8U data)
{
	if(pq->length==pq->size)
	{
		if(pq->pIn==pq->pStart)
		{
			*(pq->pStart+pq->size-1)=data;
		}
		else
		{
			*(pq->pIn-1)=data;
		}
		return(cQBufFull);
	}
	else
	{
		*(pq->pIn)=data;
		pq->length++;
		if(pq->pIn==pq->pStart+pq->size-1)
		{
			pq->pIn=pq->pStart;
		}
		else
		{
			
			pq->pIn++;
		}
		return(cQBufNormal);
	}
}
/************************************************************************************
*Function name: sQDataOut															*
*Parameters:	pq: pointer to queue structure to be initialized					*
*				pdata:the address to save the data									*
*Returns:		cQBufNormal:data has been inserted into the queue					*
*				cQBufEmpty:the buffer is empty										*
*Description:	Get a data from the queue											*
*************************************************************************************/
INT8U	sQDataOut(QUEUE *pq,INT8U *pdata)
{
	if(pq->length==0)
	{
		return(cQBufEmpty);
	}
	*pdata=*(pq->pOut);
	pq->length--;
	if(pq->pOut==pq->pStart+pq->size-1)
	{
		pq->pOut=pq->pStart;
	}
	else
	{
		pq->pOut++;
	}	
	return(cQBufNormal);
}

INT8U bTestRxBuff[256];	// for test
INT8U bTestRxLen = 0;	// for test
/************************************************************************************
*Function Name: sSciRxISR															*
*Parameters:	sciid:		sci id													*
*Description:	This function is executed in Sci rx interrupt io2sci rx compare 	*
*				interrupt.															*
*************************************************************************************/
void	sSciRxISR(INT8U sciid)
{
	INT8U	data;
	SciDrvStruct		*psci;
	QUEUE			*pq;
	
	psci=pSciIndex[sciid];
	pq=psci->pqRx;
	
	if(sbSciGetRxRdy(sciid)==cSciRxRdy)
	{
		data=sbSciGetRxData(sciid);
		sQDataIn(pq,data);
		if(bTestRxLen < 255)
		{
			bTestRxBuff[bTestRxLen] = data;	// for test
			bTestRxLen++;
		}
	}
}

	
/************************************************************************************
*Function Name: sSciRead															*
*Parameters:	sciid:		sci id													*
*				*pBuf:		address to save data received							*
*Returns:		cSciRxBufEmpty: receive  buffer is empty							*
*				cSciRxRdy:		get one byte data successfully						*
*Description:	This function is executed in AP 									*
*************************************************************************************/
INT8U	sSciRead(INT8U	sciid,INT8U *pBuf)
{
	QUEUE			*pq;
	INT8U	temp;
	SciDrvStruct		*psci;	
	
	psci=pSciIndex[sciid];
	pq=psci->pqRx;
	
	
	OS_ENTER_CRITICAL();
	temp=sQDataOut(pq,pBuf);
	OS_EXIT_CRITICAL();
	
	if(temp==cQBufEmpty)
	{
		return(cSciRxBufEmpty);
	}
	else 
	{
		return(cSciRxRdy);
	}
}
	

/************************************************************************************
*Function Name: sSciTxISR															*
*Parameters:	sciid:		sci id													*
*Description:	This function is executed in Sci Tx interrupt io2sci Tx compare 	*
*				interrupt.															*
*************************************************************************************/
void	sSciTxISR(INT8U sciid)
{
	SciDrvStruct		*psci;
	
	psci=pSciIndex[sciid];		
	
	if(sbSciGetTxRdy(sciid)==cSciTxRdy)
	{
		if(psci->wTxLength==0)
		{
			psci->bTxStatus=cSciTxRdy;			
			sSciStopTx(sciid);
		}
		else
		{
			sSciTxData(sciid,*(psci->pbTx));
			(psci->pbTx)++;
			(psci->wTxLength)--;
		}
	}	
}
/************************************************************************************
*Function Name: sSciWrite															*
*Parameters:	sciid:		sci id													*
*				*pstart:	start address of data to be sent						*
*				wLength:	the length of data to be send							*
*Returns:		cSciTxBufFull:	transmit  buffer is empty							*
*				cSciTxRdy:		send one byte data successfully 					*
*Description:	This function is executed in AP 									*
*************************************************************************************/
INT8U	sSciWrite(INT8U sciid,INT8U *pstart,INT16U Length)
{
	SciDrvStruct		*psci;
	
	psci=pSciIndex[sciid];
	
	if(psci->bTxStatus==cSciTxBusy)
	{
		return(cSciTxBusy);
	}
	
	OS_ENTER_CRITICAL();
	psci->pbTx=pstart;
	psci->wTxLength=Length;
	psci->bTxStatus=cSciTxBusy;
	sSciTxData(sciid,*(psci->pbTx));    
	(psci->pbTx)++;
	psci->wTxLength--;
	OS_EXIT_CRITICAL();
	
	return(cSciTxRdy);
}

/************************************************************************************
*Function Name: sSciGetTxStatus 													*
*Parameters:	sciid:		sci id													*
*Returns:		sci tx status		cSciTxRdy										*
									cSciTxBusy										*
*Description:	Get the sci trasmit status											*
*************************************************************************************/	
INT8U	sSciGetTxStatus(INT8U sciid)
{
	SciDrvStruct		*psci;
	
	psci=pSciIndex[sciid];
	
	return(psci->bTxStatus);
}

void	sSciProtection(INT8U sciid, INT16U wRxErrCnt, INT16U wTxBusyCnt)
{
	// rx error check
	if(sbSciGetRxError(sciid) == 1)
	{
		bSciRxErrCnt[sciid]++;
	}
	else
	{
		bSciRxErrCnt[sciid] = 0;
	}

	// tx busy check
	if(sSciGetTxStatus(sciid) != cSciTxRdy)
	{
		bSciTxBusyCnt[sciid]++;
	}
	else
	{
		bSciTxBusyCnt[sciid] = 0;
	}
	
	if((bSciRxErrCnt[sciid] > wRxErrCnt) || (bSciTxBusyCnt[sciid] > wTxBusyCnt))
	{
		bSciRxErrCnt[sciid] = 0;
		bSciTxBusyCnt[sciid] = 0;
		
		OS_ENTER_CRITICAL();
		sSciSwReset(sciid, 0);
		sSciSwReset(sciid, 1);
		SciList[sciid].bTxStatus = cSciTxRdy;
		SciList[sciid].wTxLength = 0;
		OS_EXIT_CRITICAL();
	}
}


/************************************************************************************
*Get Sci Rx Data																	*
*************************************************************************************/
INT8U	sbSciGetRxData(INT8U sciid)
{
	INT16U wTemp;
	
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		wTemp = SCIA_RX_DATA;
		return (INT8U)wTemp;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		wTemp = SCIB_RX_DATA;
		return (INT8U)wTemp;
	}
#endif

#if	SCI_SCIC_EN==1
		if(sciid==cSCIC_ID)
		{
			wTemp = SCIC_RX_DATA;
			return (INT8U)wTemp;
		}
#endif


	return 0;
}

/************************************************************************************
*Get Sci Rx ready status															*
*************************************************************************************/
INT8U	sbSciGetRxRdy(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		if(SCIA_RX_RDY_STATUS == 1)
		{
			return(cSciRxRdy);
		}
		else 
		{
			return(cSciRxBusy);
		}
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		if(SCIB_RX_RDY_STATUS)
		{
			return(cSciRxRdy);
		}
		else 
		{
			return(cSciRxBusy);
		}
	}
#endif

#if	SCI_SCIC_EN==1
		if(sciid==cSCIC_ID)
		{
			if(SCIC_RX_RDY_STATUS)
			{
				return(cSciRxRdy);
			}
			else 
			{
				return(cSciRxBusy);
			}
		}
#endif

	return (cSciRxBusy);
}
/************************************************************************************
*Get Sci Tx status																	*
*************************************************************************************/
INT8U	sbSciGetTxRdy(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		if(SCIA_TX_RDY_STATUS == 1)
		{
			return(cSciTxRdy);
		}
		else 
		{
			return(cSciTxBusy);
		}
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		if(SCIB_TX_RDY_STATUS == 1)
		{
			return(cSciTxRdy);
		}
		else 
		{
			return(cSciTxBusy);
		}
	}
#endif

#if	SCI_SCIC_EN==1
		if(sciid==cSCIC_ID)
		{
			if(SCIC_TX_RDY_STATUS == 1)
			{
				return(cSciTxRdy);
			}
			else 
			{
				return(cSciTxBusy);
			}
		}
#endif


	return(cSciTxBusy);
}

/************************************************************************************
*tx a byte and enable tx interrupt													*
*************************************************************************************/
void	sSciTxData(INT8U sciid,INT8U data)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciAEnableTxInt();
		mSciATxData(data);
		return;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBEnableTxInt();		
		mSciBTxData(data);
		return;
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		mSciCEnableTxInt(); 	
		mSciCTxData(data);
		return;
	}
#endif

}

/************************************************************************************
*disable tx interrupt																*
*************************************************************************************/			
void	sSciStopTx(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciADisableTxInt();
		return;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBDisableTxInt();
		return;
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		mSciCDisableTxInt();
		return;
	}
#endif

}

/************************************************************************************
*Enable tx interrupt																*
*************************************************************************************/			
void	sSciStartTx(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciAEnableTxInt();
		return;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBEnableTxInt();
		return;
	}
#endif

#if	SCI_SCIC_EN==1
		if(sciid==cSCIC_ID)
		{
			mSciCEnableTxInt();
			return;
		}
#endif

}

/************************************************************************************
*Disable rx interrupt																*
*************************************************************************************/
void	sSciStopRx(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciADisableRxInt();
		return;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBDisableRxInt();
		return;
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		mSciCDisableRxInt();
		return;
	}
#endif

}

/************************************************************************************
*Enable rx interrupt																*
*************************************************************************************/
void	sSciStartRx(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciAEnableRxInt();
		return;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBEnableRxInt();
		return;
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		mSciCEnableRxInt();
		return;
	}
#endif

}

INT8U	sbSciGetRxError(INT8U sciid)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		return SCIA_RX_ERROR;
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		return SCIB_RX_ERROR;
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		return SCIC_RX_ERROR;
	}
#endif
	
	return 0;
}

void	sSciSwReset(INT8U sciid, INT8U value)
{
#if	SCI_SCIA_EN==1
	if(sciid==cSCIA_ID)
	{
		mSciASwReset(value);
	}
#endif

#if	SCI_SCIB_EN==1
	if(sciid==cSCIB_ID)
	{
		mSciBSwReset(value);
	}
#endif

#if	SCI_SCIC_EN==1
	if(sciid==cSCIC_ID)
	{
		mSciCSwReset(value);
	}
#endif

}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT8U	bGetSciRxLen(INT8U sciid)
{
	return strSciDataList[sciid].bRxLen;
}

INT8U	*pbGetSciRxBuff(INT8U sciid)
{
	return strSciDataList[sciid].bRxBuf;
}

INT8U	*pbGetSciTxBuff(INT8U sciid)
{
	return strSciDataList[sciid].bTxBuf;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/


