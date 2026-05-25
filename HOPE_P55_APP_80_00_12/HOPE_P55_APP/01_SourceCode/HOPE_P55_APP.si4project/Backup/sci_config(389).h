/************************************************************************************
*File name:	SciConfig.h																*
*Description:	the sci driver settings												*
*************************************************************************************/
#define 	c485_SCI			cSCIA_ID
#define 	cTTL_SCI			cSCIB_ID
#define 	c232_SCI			cSCIC_ID
#define		cSCIA_ID			0
#define		cSCIB_ID			1
#define		cSCIC_ID			2

/************************************************************************************
*SCI ENABLE/DISANLE SWITCH															*
*0:			SCI DISABLE															*
*1:			SCI ENABLE																*
*************************************************************************************/
#define		SCI_SCIA_EN			1
#define		SCI_SCIB_EN			1
#define		SCI_SCIC_EN			1

/************************************************************************************
*Maxmam	Sci Number																	*
*************************************************************************************/
#define		MAX_SCI_NO			(SCI_SCIA_EN+SCI_SCIB_EN+SCI_SCIC_EN)

/************************************************************************************
*Maxmam	Sci buffer size																*
*************************************************************************************/
#if(SCI_SCIA_EN==1)
#define		MAX_SCIA_RX_SIZE	150
#else
#define		MAX_SCIA_RX_SIZE	0
#endif
#if(SCI_SCIB_EN==1)
#define		MAX_SCIB_RX_SIZE	150
#else
#define		MAX_SCIB_RX_SIZE	0
#endif
#if(SCI_SCIC_EN==1)
#define		MAX_SCIC_RX_SIZE	150
#else
#define		MAX_SCIC_RX_SIZE	0
#endif

#define		MAX_SCI_RX_SIZE		MAX_SCIA_RX_SIZE+MAX_SCIB_RX_SIZE+MAX_SCIC_RX_SIZE

