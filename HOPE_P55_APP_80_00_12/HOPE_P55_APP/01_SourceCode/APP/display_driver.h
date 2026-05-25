/*================================================================================================*
 *FileName:  display_drv.h																																					*
 *																																																*
 *================================================================================================*/
#ifndef			__DISPLAY_DRV_H__
#define			__DISPLAY_DRV_H__

#include "display_config.h"
#include "KERNEL\ports\OS_CPU.h"   

#define cALWAYS_LIGHT           0
#define cFLASH_TIME_1S          2 

typedef union 
{
    INT16U bByte;
    struct
    {
        INT16U SetVal:1;
        INT16U Duty50:4;
        INT16U timeout:4;
        INT16U val:1;            
    }BIT;    
}VIEWBUF;

				
//Interface function for other ".c" files
void sDisplayUpdate(void);
void sSendBitToVram(INT8U bitAddr, INT8U bVal, INT8U Time);
void sClearVramArea(void);
void sSetVramArea(void);
void sBackLightOn(void);
void sBackLightOff(void);
void sDisplayDevInit(void);
void sDisplayHwInit(void); 
void sDisplayUpdateData(void);
void sDisplayUpdate(void);

#endif			//__DISPLAY_DRV_H__
