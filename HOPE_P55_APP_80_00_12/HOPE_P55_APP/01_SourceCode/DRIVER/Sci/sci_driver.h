/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifdef	SCI_DRIVER
#define	SCI_DRV
#else
#define	SCI_DRV	extern
#endif

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"sci_config.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
// return value of write operation
#define	cSciTxRdy				0
#define	cSciTxBusy				1

#define cSCI_RX_LEN				255
#define cSCI_TX_LEN				255//384//512//255	// for test 20241202

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
SCI_DRV	void	sSciInitial(INT8U sciid, INT8U rx_size, INT8U prio, INT8U event);							
SCI_DRV	void	sSciRxTask(INT8U sciid, INT8U bTimeout);
SCI_DRV	void	sSciRxISR(INT8U sciid);
SCI_DRV	void	sSciTxISR(INT8U sciid);
SCI_DRV	INT8U	sSciGetTxStatus(INT8U sciid);
SCI_DRV	INT8U	sSciWrite(INT8U sciid,INT8U *pstart,INT16U Length);
SCI_DRV	void	sSciProtection(INT8U sciid, INT16U wRxErrCnt, INT16U wTxBusyCnt);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
SCI_DRV	INT8U	bGetSciRxLen(INT8U sciid);
SCI_DRV	INT8U	*pbGetSciRxBuff(INT8U sciid);
SCI_DRV	INT8U	*pbGetSciTxBuff(INT8U sciid);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/


