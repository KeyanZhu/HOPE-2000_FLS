/*===========================================================================*
 *																																					 *
 *===========================================================================*/
#include	"display_driver.h"
#include	"display_hard_ports.h"
#include	"Main.h"



//Dispaly buffer
VIEWBUF	ViewBuf[VRAMSIZE];
VIEWBUF View1SFlash;


#ifdef     CF_LCD
static void sSendToLcdNBit(INT8U Nbit, INT8U pData);
static void sSendCmdIDToLcd(INT8U CmdID);
static void sSendAddrToLcd(INT8U Addr);
static void sLcdInit(void);
#endif      //CF_LCD

void sLcdDelay1us(void);

void sLcdDelay1us(void)
{
	INT8U	i;
	for(i = 0;i<=50;i++)	//8
	{
	    asm(" NOP ");
	} 
}

//=================================================================================
//Function Name:	sDisplayUpdate
//description: update display VRAM 
//=================================================================================
void sDisplayUpdate(void)
{
	  INT16U i;
	  
  #ifdef CF_LCD    
    mLcdCSLow();
    sLcdDelay1us();
  	sSendCmdIDToLcd(cWRModeID);
  	sSendAddrToLcd(0);
  	for (i = 0; i < VRAMSIZE; i++)
  	{	
        mLcdClockLow();
        sLcdDelay1us();
  	    if (1 == ViewBuf[i].BIT.val)
  	    {
  	        mLcdDataHigh();
  	    }
  	    else
  	    {
  		    mLcdDataLow();
  	    }
        sLcdDelay1us();
  	    mLcdClockHigh();
  	    sLcdDelay1us();
  		
  	}
  	mLcdCSHigh();
  	sLcdDelay1us();
	
  #endif  //CF_LCD   		
}   


void sDisplayUpdateData(void)
{
//	INT8U i;	  
//	for(i = 0; i < VRAMSIZE; i++)
//	{
//		if(0 != ViewBuf[i].BIT.timeout)
//		{    
//			if(ViewBuf[i].BIT.timeout > ViewBuf[i].BIT.Duty50)
//			ViewBuf[i].BIT.val = ViewBuf[i].BIT.SetVal; 
//			ViewBuf[i].BIT.timeout--; 					      			          
//		}    
//	}  

	if(View1SFlash.BIT.timeout > 0)
	{
		View1SFlash.BIT.timeout--;
	}
	else
	{
		if(View1SFlash.BIT.val != 0)
		{
			View1SFlash.BIT.timeout = cFLASH_TIME_1S - 1;
		}
	}

	View1SFlash.BIT.val = 0;

}
   
//=================================================================================
//Function Name:	mSetVramBit
//description: Set display bit in veiw buffer	
//input:
//			1)bitAddr:	Address of the bit in VRAM
//          2)bVal:     value
//			3)Time:		flashing periods,Bit7: force update
//return:   0x80 or 0      foe synchronization		
//=================================================================================
void sSendBitToVram(INT8U bitAddr, INT8U bVal, INT8U Time)  
{   
//    if((0 == ViewBuf[bitAddr].BIT.timeout || (Time & 0x80) != 0)&& bitAddr < VRAMSIZE)
//    {
//        Time &= 0x7F;
//        ViewBuf[bitAddr].BIT.val = bVal;
//        ViewBuf[bitAddr].BIT.SetVal = bVal;
//        ViewBuf[bitAddr].BIT.timeout = Time;
//        ViewBuf[bitAddr].BIT.Duty50 = Time >> 1; 
//    }

	if(bitAddr < VRAMSIZE)
	{
		if(Time == cFLASH_TIME_1S)
		{
			View1SFlash.BIT.val = 1;
		}

		if(Time == 0xFF)
		{
			ViewBuf[bitAddr].BIT.val = 0;
			ViewBuf[bitAddr].BIT.timeout = 0;			
		}
		else if((Time == cFLASH_TIME_1S && View1SFlash.BIT.timeout == 0) || Time == 0)
		{
			ViewBuf[bitAddr].BIT.val = bVal;
			ViewBuf[bitAddr].BIT.timeout = Time;			
		}
	}

}   
//=================================================================================
//Function Name:	sClearVramRect
//description: Clear view area	
//=================================================================================
void sClearVramArea(void)
{   
	INT16U i;
    for(i = 0; i < VRAMSIZE; i++)
    {
        ViewBuf[i].BIT.val = DISPLAY_OFF;  
    }
}  
//=================================================================================
//Function Name:	sSetVramArea
//description: set view area	
//=================================================================================
void sSetVramArea(void)
{   
	INT16U i;
	for(i = 0; i < VRAMSIZE; i++)
	{
		ViewBuf[i].BIT.val = DISPLAY_ON;
		ViewBuf[i].BIT.timeout = 0;
		ViewBuf[i].BIT.Duty50 = 0;  
	}
	
}  
void sBackLightOn(void)
{
	mLcdBacklightOn();

//	ViewBuf[VRAMSIZE-1].BIT.val = DISPLAY_ON;
//	ViewBuf[VRAMSIZE-1].BIT.timeout = 0;  
//	ViewBuf[VRAMSIZE-1].BIT.Duty50 = 0; 
}
void sBackLightOff(void)
{
	mLcdBacklightOff();    
}
void sDisplayDevInit(void)
{
	INT8U i;
	for(i = 0; i < VRAMSIZE; i++)
	{
		ViewBuf[i].BIT.val = DISPLAY_OFF;
		ViewBuf[i].BIT.timeout = 0; 
		ViewBuf[i].BIT.Duty50 = 0;  
	}
  #ifdef     CF_LCD 
    mLcdCSLow();
    sLcdDelay1us();
  	sSendCmdIDToLcd(cWRModeID);
  	sSendAddrToLcd(0);
  	for (i = 0; i < VRAMSIZE; i++)
  	{	
          mLcdClockLow();
          sLcdDelay1us();
  	    if (1 == ViewBuf[i].BIT.val)
  	    {
  	        mLcdDataHigh();
  	    }
  	    else
  	    {
  		    mLcdDataLow();
  	    }
          sLcdDelay1us();
  	    mLcdClockHigh();
  	    sLcdDelay1us();
  		
  	}
  	mLcdCSHigh();
  	sLcdDelay1us();   
    	
   sLcdInit();
  #endif  
}

void sDisplayHwInit(void)
{    
  #ifdef     CF_LCD
    sLcdInit();
  #endif
}

#ifdef     CF_LCD  
static void sLcdInit(void)
{	
	mLcdClockHigh();
	sLcdDelay1us();
	
	mLcdCSLow();
	sLcdDelay1us();
    
	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, BIASThird4COCmd);
	
	mLcdCSHigh();
	sLcdDelay1us();
	
  	mLcdCSLow();
	sLcdDelay1us();
	
	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, RC256Cmd);
	
	mLcdCSHigh();
	sLcdDelay1us();
	
 	mLcdCSLow();
	sLcdDelay1us();
	
	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, WDTDIS);
	
	mLcdCSHigh();
	sLcdDelay1us();
	
  	mLcdCSLow();
	sLcdDelay1us();
	
	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, TIMERDIS);
	
	mLcdCSHigh();
	sLcdDelay1us();
	sLcdDelay1us();
	
  	mLcdCSLow();
	sLcdDelay1us();

	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, SYSENCmd);
	
	mLcdCSHigh();
	sLcdDelay1us();
	mLcdCSLow();
	sLcdDelay1us();
	
	sSendCmdIDToLcd(cCmdModeID);
	sSendToLcdNBit(8, LcdONCmd);
	
	mLcdCSHigh();
	sLcdDelay1us();
}

static void sSendToLcdNBit(INT8U Nbit, INT8U pData)
{	

	for(; Nbit > 0; Nbit--)
	{
		mLcdClockLow();
		sLcdDelay1us();
		if (0 != (pData & 0x80))
		{
			mLcdDataHigh();
		}
		else
		{
			mLcdDataLow();
		}
		sLcdDelay1us();
		mLcdClockHigh();
		sLcdDelay1us();
		pData <<= 1;
	}
}


static void sSendCmdIDToLcd(INT8U CmdID)
{
	sSendToLcdNBit(4, CmdID<<4);
}
static void sSendAddrToLcd(INT8U Addr)
{
	sSendToLcdNBit(5, Addr<<3);
}
#endif 


