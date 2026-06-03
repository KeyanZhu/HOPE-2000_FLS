#include "display_map.h"
//#include "display_driver.h"                                        
#include "display_vp.h"
#include "Main.h"


#define mSetVramBit(bitADDR, bTime)         sSendBitToVram(bitADDR, DISPLAY_ON, bTime)
#define mClearVramBit(bitADDR)              sSendBitToVram(bitADDR, DISPLAY_OFF, 0)


void sBuzzerOperation(INT8U ubPeriod, INT8U ubBeepCnt, INT8U ubBeepOnTime, INT8U ubBeepOffTime);
static void sFigGroupDisplayNumNew(INT8U bFirstFigID, INT16U bFigNum, INT16U bNum, INT8U bTime);



void	sPvIco(void)
{
	static INT16U wCnt = 0;
	
	if((!T_ALARM_DATA.bits.bPv1UVAlarm))
	{
		if(wCnt++ >= 50)	// 5S
		{
			sSendBitToVram(cBIT_S22, DISPLAY_ON, cALWAYS_LIGHT);
		}
	}
	else
	{
		wCnt = 0;
		mClearVramBit(cBIT_S22);
	}
}

void	sGridIco(void)
{
	if((T_ALARM_DATA.bits.bGridUV == false) && (T_ALARM_DATA.bits.bGridOV == false)\
	&& (T_ALARM_DATA.bits.bGridUF == false) && (T_ALARM_DATA.bits.bGridOF == false))
	{
		sSendBitToVram(cBIT_S23, DISPLAY_ON, cALWAYS_LIGHT);	// 输出插座
	}
	else
	{
		mClearVramBit(cBIT_S23);
	}
}

void	sLoadIco(void)
{
	if(hoROPRLY)
	{
		sSendBitToVram(cBIT_S27, DISPLAY_ON, cALWAYS_LIGHT);	// EPS
		sSendBitToVram(cBIT_S10, DISPLAY_ON, cALWAYS_LIGHT);	// 输出插座
	}
	else
	{
		mClearVramBit(cBIT_S27);
		mClearVramBit(cBIT_S10);
	}
}


void	sDisplayWifi(void)
{
	INT16U	uwWifiIotState = 0;
	static INT16U s_uwWifiTimeCount = 0;
	static INT16U s_uwWifiOnOffTimeCount = 0;
	static INT16U s_uwWifiOnTime = 0;
	static INT16U s_uwWifiOffTime = 0;

	/*	uwWifiIotState = 0; // iot 设备没有与MCU 建立通信			// WIFI灭
		uwWifiIotState = 1; // 连接路由器错误，有配置路由器	// 优化显示WIFI灭       			      // WIFI亮1秒，灭2秒
		uwWifiIotState = 2; // 连接上路由器						// WIFI亮1秒，灭1秒
		uwWifiIotState = 3; // 连接上服务器						// WIFI常亮
		uwWifiIotState = 4; // 正在配置连接路由器或基站					// 优化显示WIFI灭          // WIFI亮1秒，灭2秒
		uwWifiIotState = 5; // 正在升级IOT 设备程序					// WIFI亮0.5秒，灭0.5秒 
	*/
	uwWifiIotState = uwGetWifiIotState();
	switch(uwWifiIotState)
	{
		case 0:	s_uwWifiTimeCount = 0;  break;
		case 1: s_uwWifiTimeCount = 0;  break;
		case 2:	s_uwWifiTimeCount = 20; s_uwWifiOnTime = 10; s_uwWifiOffTime = 10;break;
		case 3:	s_uwWifiTimeCount = 10; s_uwWifiOnTime = 10; s_uwWifiOffTime = 0; break;
		case 4:	s_uwWifiTimeCount = 0;	break;
		case 5:	s_uwWifiTimeCount = 10; s_uwWifiOnTime = 5;  s_uwWifiOffTime = 5; break;
		default: s_uwWifiTimeCount = 0; break;
	}

	if(s_uwWifiTimeCount > 0)
	{
		s_uwWifiOnOffTimeCount++;
		if(s_uwWifiOnOffTimeCount < s_uwWifiOnTime)
		{
			sSendBitToVram(cBIT_S6, DISPLAY_ON, cALWAYS_LIGHT);
		}
		else if(s_uwWifiOnOffTimeCount < s_uwWifiTimeCount && s_uwWifiOffTime > 0)
		{
			mClearVramBit(cBIT_S6);
		}
		else
		{
			sSendBitToVram(cBIT_S6, DISPLAY_ON, cALWAYS_LIGHT);
			s_uwWifiOnOffTimeCount = 0;
		}
	}
	else
	{
		s_uwWifiOnOffTimeCount = 0;
		mClearVramBit(cBIT_S6);
	}
}

void	sDisplayInPut(void)
{
	INT16S 	wTemp;

	//wTemp = -swGetBatWattFilter();		// 总的充电功率
	wTemp = swGetPvWattNew() +swGetRLineWattNew();		// PV功率 +市电功率
	if(wTemp > 9999)
	{
		wTemp = 9999;
	}
	if(wTemp < 0)
	{
		wTemp = 0;
	}
	
	sSendBitToVram(cBIT_S2, DISPLAY_ON, cALWAYS_LIGHT);				// INPUT 图标
	sSendBitToVram(cBIT_S3, DISPLAY_ON, cALWAYS_LIGHT);				// W 图标
	sFigGroupDisplayNumNew(FIG1_13SEG, 4, wTemp, cALWAYS_LIGHT);	// 数码管显示四位数据
}

void	sDisplayOutPut(void)
{
	INT16S 	wTemp;

	wTemp = swGetROpWattFilter();		// OP功率
	if(wTemp > 9999)
	{
		wTemp = 9999;
	}
	if(wTemp < 0)
	{
		wTemp = 0;
	}
	
	sSendBitToVram(cBIT_S8, DISPLAY_ON, cALWAYS_LIGHT);				// OUTPUT 图标
	sSendBitToVram(cBIT_S9, DISPLAY_ON, cALWAYS_LIGHT);				// W 图标
	sFigGroupDisplayNumNew(FIG5_13SEG, 4, wTemp, cALWAYS_LIGHT); 	// 数码管显示四位数据
}

INT16U uwSOCMax = 0;	// for test
INT16U uwSOCMin = 0;	// for test
void	sDisplaySOC(void)
{
	INT16U 	wTemp;
	INT16U wSocCnt = 0;
	static INT16U wSocChgCnt = 0;

	// 需要优化：存在故障/告警 直接return;

	wTemp = swGetSocNew();				// SOC值
	if(wTemp > 100)
	{
		wTemp = 100;
	}

	// SOC指示条点数计算
	uwSOCMin = wTemp / 10;	// 静态显示区间
	if(uwSOCMin > 0)
	{
		uwSOCMin -= 1;
	}
	
	// 充电标识存在,SOC会有充电流动
	if((suwGetPV1CtrlSts() == cPVWork) || (suwGetFBInvCtrlSts() == cFBInvCtrlBus))//临时这样写
	{	
		if(++wSocChgCnt >= 5)	// 动态显示区间，500ms
		{
			wSocChgCnt = 0;
			//if(uwSOCMax < 9)				// 循环亮满
			if(uwSOCMax < 9)//(uwSOCMin + 1))	// 电量+1格闪动
			{
				uwSOCMax++;
			}
			else
			{
				uwSOCMax = uwSOCMin;
			}
		}
		
		for(wSocCnt = 0; wSocCnt <= uwSOCMin; wSocCnt++)	// 循环结构，改掉，改成数组方式
		{
			sSendBitToVram(SOC_TAB[wSocCnt ], DISPLAY_ON, cALWAYS_LIGHT);
		}
		wSocCnt = 0;
		if(uwSOCMax > uwSOCMin)
		{
			for(wSocCnt = uwSOCMin; wSocCnt <= uwSOCMax; wSocCnt++)
			{
				sSendBitToVram(SOC_TAB[wSocCnt], DISPLAY_ON, cALWAYS_LIGHT);
			}
			wSocCnt = 0;
		}
	}
	else if(wTemp > 0)	//  不充电就是在放电，放电不需要动态
	{
		wSocChgCnt = 0;
		for(wSocCnt = 0; wSocCnt <= uwSOCMin; wSocCnt++)
		{
			sSendBitToVram(SOC_TAB[wSocCnt ], DISPLAY_ON, cALWAYS_LIGHT);
		}
		wSocCnt = 0;
	}
	else
	{

	}

	sSendBitToVram(cBIT_S4, DISPLAY_ON, cALWAYS_LIGHT);					// SOC的百分号
	if(wTemp < 100)
	{
		sFigGroupDisplayNumNew(FIG12_13SEG, 2, wTemp, cALWAYS_LIGHT);  // 数码管显示四位数据
	}
	else
	{
		sSendBitToVram(cBIT_14BC, DISPLAY_ON, cALWAYS_LIGHT);			// SOC显示100的1
		sFigGroupDisplayNumNew(FIG12_13SEG, 1, 0, cALWAYS_LIGHT);
		sFigGroupDisplayNumNew(FIG13_13SEG, 1, 0, cALWAYS_LIGHT);
	}
}

void	sDisplayChgTimer(void)
{
	INT16U 	uwTemp;

	uwTemp = 60;

	if(uwTemp > 999)
	{
		uwTemp = 999;
	}
	
	sSendBitToVram(cBIT_S11, DISPLAY_ON, cALWAYS_LIGHT);			// MIN 图标
	sFigGroupDisplayNumNew(FIG9_13SEG, 3, uwTemp, cALWAYS_LIGHT);  // 数码管显示四位数据
}

void	sDisplayFault(void)
{
	INT16U 	uwTemp;

	uwTemp = swGetFaultCode();
	
	sSendBitToVram(cBIT_S1, DISPLAY_ON, cALWAYS_LIGHT); 			// 常亮
	sFigGroupDisplayNumNew(FIG12_13SEG, 2, uwTemp, cALWAYS_LIGHT);  // 数码管显示四位数据
}

void	sDisplayAlarm(void)
{
	INT16U	uwTemp;
	
	uwTemp = 0;
		
	sSendBitToVram(cBIT_S1, DISPLAY_ON, cFLASH_TIME_1S); 			// 常亮
	sFigGroupDisplayNumNew(FIG12_13SEG, 2, uwTemp, cALWAYS_LIGHT);	// 数码管显示四位数据

}

void sDisplay(void)      //100ms
{ 
	static INT16U wCnt = 0;
	static INT16U uwSocFaultCnt = 0;

	if(wCnt == 1)
	{
		sDisplayHwInit();
	}
	sClearVramArea();

	if(swGetWorkMode() == cPowerOnMode)
	{
		sSetVramArea();
	}
	else
	{
		// 市电输入插头图标
		sGridIco();
		
		// PV图标
		sPvIco();

		// 低温图标
		if(swGetBat1TempFilter() < 0 || swGetBat2TempFilter() < 0)		// 临时这样写
		{
			sSendBitToVram(cBIT_S5, DISPLAY_ON, cFLASH_TIME_1S);		// 闪烁
		}

		// 高温图标
		if(swGetBat1TempFilter() > 500 || swGetBat2TempFilter() > 500)	// 临时这样写
		{
			sSendBitToVram(cBIT_S7, DISPLAY_ON, cFLASH_TIME_1S);		// 闪烁
		}

		// WIFI图标
		sDisplayWifi();

		// EPS图标不知道干啥用，先合并在load里面
		// 输出插座图标
		sLoadIco();

		// 输入部分
		sDisplayInPut();

		// 输出部分
		sDisplayOutPut();

		// 充放时间部分
		sDisplayChgTimer();

		// SOC、故障、告警的逻辑，故障/告警和SOC循环显示 2s切换一次
		if(swGetWorkMode() == cFaultMode)	// 故障存在
		{
			uwSocFaultCnt++;
			if(uwSocFaultCnt <= 20)
			{	
				sDisplayFault();
			}
			else if(uwSocFaultCnt <= 40)
			{
				sDisplaySOC();// SOC显示
			}
			else 
			{
				uwSocFaultCnt = 0;
			}
			sSendBitToVram(cBIT_S1, DISPLAY_ON, cALWAYS_LIGHT);
		}
		else  if(0)							// 告警存在
		{
			uwSocFaultCnt++;
			if(uwSocFaultCnt <= 20)
			{	
				sDisplayAlarm();
			}
			else if(uwSocFaultCnt <= 40)
			{
				sDisplaySOC();// SOC显示
			}
			else 
			{
				uwSocFaultCnt = 0;
			}
			sSendBitToVram(cBIT_S1, DISPLAY_ON, cFLASH_TIME_1S);
		}
		else								// SOC显示
		{
			uwSocFaultCnt = 0;
			sDisplaySOC();
		}
	}

	// 数据写入显示屏
	if(++wCnt >= 5)	// 500ms
	{
		wCnt = 0;
		sDisplayHwInit();
		sDisplayUpdateData();
		sDisplayUpdate();	
	}
}

void sBuzzerProc(void)
{
	if(suwGetEEBuzzerBeep())
	{
		if(swGetWorkMode() == cFaultMode)
		{
			sBuzzerOperation(1,1,3,0);//long
		}
//		else if(fConfigButtonSts || fLoadButtonSts|| (swGetLoadOnSts() == 2 && swGetWorkMode() == cToBatteryMode))
//		{
//			sBuzzerOperation(26,1,25,0);//2.5s
//		}
//		else if(fEnterButtonSts || fESCButtonSts || fUPButtonSts || fDownButtonSts)
//		{
//			sBuzzerOperation(2,1,1,0);//0.1s
//		}
		else if(swGetFaultCode() == cOverLoad)
		{
			sBuzzerOperation(5,1,1,0);//every 0.5s
		}
		else if(swGetFaultCode() == cCircirtTempOver || swGetFaultCode() == cInnelTempOver)
		{
			sBuzzerOperation(10,3,1,1);//every 1s beep 3 times
		}
		else
		{
			sBuzzerOperation(0,0,0,0);
		}	
	}
	else
	{
		sBuzzerOperation(0,0,0,0);
	}
}

void sBuzzerOperation(INT8U ubPeriod, INT8U ubBeepCnt, INT8U ubBeepOnTime, INT8U ubBeepOffTime)
{
	static INT8U s_ubPeriodCnt = 0;
	static INT8U s_ubBeepCnt = 0;
	static INT8U s_ubBeepOnTimeCnt = 0;
	static INT8U s_ubBeepOffTimeCnt = 0;
	static INT8U s_ubBeepOnoffCnt = 0;

	if(s_ubPeriodCnt > 0) 
	{
		s_ubPeriodCnt--;
	}
	else
	{
		s_ubPeriodCnt = ubPeriod;
		s_ubBeepCnt = ubBeepCnt;
		s_ubBeepOnTimeCnt = ubBeepOnTime;
		s_ubBeepOffTimeCnt = ubBeepOffTime;
		s_ubBeepOnoffCnt = 0;
	}

	if(s_ubBeepCnt > 0)
	{
		if(mBEEP)
		{
			if(++s_ubBeepOnoffCnt >= s_ubBeepOnTimeCnt)
			{
				s_ubBeepOnoffCnt = 0;
				mBEEPOff;
				s_ubBeepCnt--;
			}
		}
		else
		{
			if(++s_ubBeepOnoffCnt >= s_ubBeepOffTimeCnt)
			{
				s_ubBeepOnoffCnt = 0;
				mBEEPOn;
			}			
		}
	}
	else
	{
		mBEEPOff;
	}
}

static void sViewFigModuleNew(INT8U bSegNum, INT8U bFigID, INT16U bChar, INT8U bTime)
{
    Seg13_Field sTemp;
    bFigID *= bSegNum;
    
    sTemp.bByte = Seg13CodeTab[bChar];
    bFigID += FIG_7SEG_POS;
    
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.a, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.b, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.c, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.d, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.e, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.f, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.g, bTime); 
	sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.i, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.j, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.k, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.l, bTime);
    sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.m, bTime);
	sSendBitToVram(Figure13SEG_TAB[bFigID++], sTemp.Seg.h, bTime);
}

static void sFigGroupDisplayNumNew(INT8U bFirstFigID, INT16U bFigNum, INT16U bNum, INT8U bTime)
{
	INT16U bChar,bIsMostBit = 0;
	
	if(4 == bFigNum)  
	{
		bFigNum = 1000;
	}
	else if(3 == bFigNum)  
	{
		bFigNum = 100;
	}
	else if(2 == bFigNum)
	{
		bFigNum = 10;
	}
	else
	{
		bFigNum = 1; 
	}
	    
	bNum %= (bFigNum*10);   	    

	for(; 0 != bFigNum ;)
	{
	    bChar = bNum/bFigNum;
        
	    bNum %= bFigNum;
	    if(0 == bChar && bFigNum != 1 && 0 == bIsMostBit)
	    {
			sViewFigModuleNew(cFIG_TYPE_13, bFirstFigID++, cCharSpace, bTime);
	    }
	    else
	    {
			sViewFigModuleNew(cFIG_TYPE_13, bFirstFigID++, bChar, bTime); 
			bIsMostBit = 1;
	    }
	    bFigNum /= 10;     
	}
} 



