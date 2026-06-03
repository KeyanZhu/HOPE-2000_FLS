/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __EEPROM_DRIVER_H__
#define __EEPROM_DRIVER_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"eeprom_config.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef	__EEPROM_DRIVER_C__
#define	EEPROM_DRIVER
#else
#define	EEPROM_DRIVER	extern
#endif

#define	cI2CAck				0
#define	cI2CNak				1

#define	cEepromSuccess		0
#define	cEepromFail			1
#define	cEepromInvalidAddr	2
#define	cEepromNoSpace		3
#define	cEepromVerifyOK		4

/********************************************************************************
* Routines' implementations														*
********************************************************************************/
EEPROM_DRIVER INT8U	sbEepromWrite(INT16U addr,INT16U length,INT8U *pbuf);
EEPROM_DRIVER INT8U	sbEepromRead(INT16U addr,INT16U length,INT8U *pbuf);
EEPROM_DRIVER INT8U	sbEepromReadChkWR(INT16U addr,INT16U length,INT16U CRC);
EEPROM_DRIVER void	sEepromSoftwareReset(void);
EEPROM_DRIVER INT16U	swEEMultiDataCRC16(INT8U *puchMsg, INT16U usDataLen);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/


/********************************************************************************
* Input interface Routines														*
********************************************************************************/


#endif	// __EEPROM_DRIVER_H__

