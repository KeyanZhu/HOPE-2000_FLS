/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__LLC_CONTROL_C__


/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"


/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sOpenLLCCtrl,".TI.ramfunc");


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
INT16U g_uwDCDCCtrlSts = cDCDCWait;							// DCDC控制器状态

INT16U g_uwLLCOn = false;									// LLC 默认封波
INT16U gi_wDCDCConvPWMValue = 0;							// 实际占空比
INT16U gi_wDCDCConvPWMPeriod = 0;							// 实际频率(周期值)
INT16U gi_wDCDCConvPWMDTSet = cDCDCConvPWMDTSetLimit;		// 发波死区

INT16U uwLLCSoftCnt = 0;									// 占空比软起计数
INT16U g_uwLLCPauseTime = 500;								// 起始状态保持时间
INT16U g_uwLLCMinDutyTime = 800;							// 最小占空比持续时间(启机占空比)
INT16U g_uwLLCSoftDutyRate = 300;							// 每次占空比软起时间
INT16U g_uwLLCSoftFreqRate = 4000;							// 每次频率软起时间
INT16U gi_wDCDCConvPWMPeriodStart = cDCDCConvertPeriodMax;	// 频率软起起始频率
INT16U gi_wDCDCConvPWMPeriodSet = cDCDCConvertPeriodDef;	// 频率软起截至频率

INT16U gi_wDCDCSoftDutyFinish = false;						// 占空比软起完成标志

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sDCDCParaInit(void)
{
	gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
	gi_wDCDCConvPWMDTSet = uwGetDcDcPWMDutySet();
}

void	sClrDCDCCtrlPara(void)			// for test
{
	mDisDCDCForcePWMOut();
	mDisDCDCHForcePWMOut();

	//First 800 cycle around 40ms to wait Bat SPS work up, and second 800 cycle to give a small duty to soft LLC.
	gi_wDCDCConvPWMValue = 0;
	gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
	gi_wDCDCConvPWMDTSet = uwGetDcDcPWMDutySet();
	g_uwLLCPauseTime = cWait40uSTimeSet;
	g_uwLLCMinDutyTime = cWait40uSTimeSet;

	mDCDCConvPRD12 = uwGetDcDcPWMPeriod();
	mDCDCConvPRD34 = uwGetDcDcPWMPeriod();

	mDCDCConvPWM1 = uwGetDcDcPWMPeriod();
	mDCDCConvPWM2 = 0;
	mDCDCConvPWM3 = uwGetDcDcPWMPeriod();
	mDCDCConvPWM4 = 0;
}
INT16U	gi_wDCDCConvPWMValueTest = 0;
INT16U	uwLLCSoftCntTest = 0;
void	sOpenLLCCtrl(void)
{
	INT16S wTemp;
	INT16S wPwmDutyMinTemp;

	if(!mChkDCDCLLCOn())
	{
		mDisDCDCForcePWMOut();
		mDisDCDCHForcePWMOut();
		
		g_uwDCDCCtrlSts = false;

		//First 800 cycle around 40ms to wait Bat SPS work up, and second 800 cycle to give a small duty to soft LLC.
		gi_wDCDCConvPWMValue = 0;
		gi_wDCDCConvPWMPeriod = cDCDCConvertPeriodMax;//uwGetDcDcPWMPeriod();
		g_uwLLCPauseTime = cWait40uSTimeSet;
		g_uwLLCMinDutyTime = 50000;//cWait40uSTimeSet;
		uwLLCSoftCntTest = 0;	// FOR TEST
		gi_wDCDCSoftDutyFinish = false;

		mDCDCConvPRD12 = cDCDCConvertPeriodMax;//uwGetDcDcPWMPeriod();
		mDCDCConvPRD34 = cDCDCConvertPeriodMax;//uwGetDcDcPWMPeriod();

		mDCDCConvPWM1 = cDCDCConvertPeriodMax;//uwGetDcDcPWMPeriod();
		mDCDCConvPWM2 = 0;
		mDCDCConvPWM3 = cDCDCConvertPeriodMax;//uwGetDcDcPWMPeriod();
		mDCDCConvPWM4 = 0;
	}
	else
	{
		// Step1:wait some time
		// Step2:run some time at minimum duty
		// Step3:Soft duty at Maximum frequency
		// Step4:Soft frequency when the duty done
		wPwmDutyMinTemp = (INT16U)((F32)uwGetDcDcPWMPeriod() * 0.15);	// 最小占空比限制在35%
		if(gi_wDCDCConvPWMDTSet <= cDCDCConvertDutyStart)//cDCDCConvertDuty1)
		{
			gi_wDCDCConvPWMDTSet = cDCDCConvertDutyStart;//cDCDCConvertDuty1;
		}
		else if(gi_wDCDCConvPWMDTSet > wPwmDutyMinTemp)
		{
			gi_wDCDCConvPWMDTSet = wPwmDutyMinTemp;
		}

		if(g_uwLLCPauseTime > 0)		// 进入发波，先进行一段时间封波保持，不立即发波
		{
			g_uwLLCPauseTime--;
			mDisDCDCForcePWMOut();
			mDisDCDCHForcePWMOut();
			gi_wDCDCConvPWMValue = 0;
			gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
		}
		else if(g_uwLLCMinDutyTime > 0)	// 最小占空比运行一段时间
		{
			g_uwLLCMinDutyTime--;
			gi_wDCDCConvPWMValue = cDCDCConvertDutyStart;
			gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
			mEnDCDCPWMOut();
			mEnDCDCHPWMOut();
			mEnDCDCForcePWMOut();
			mEnDCDCHForcePWMOut();
		}
		else if(gi_wDCDCConvPWMValue < ((uwGetDcDcPWMPeriod()>>1) - gi_wDCDCConvPWMDTSet))		// 占空比软起
		{
			if(++uwLLCSoftCnt >= g_uwLLCSoftDutyRate)
			{
				uwLLCSoftCnt = 0;
				gi_wDCDCConvPWMValue++;
			}
//			mEnDCDCPWMOut();
//			mEnDCDCHPWMOut();
//			mEnDCDCForcePWMOut();
//			mEnDCDCHForcePWMOut();

			// for test LLC打嗝
			// 3.3 * 64 * 2 = 423V
			// 3.6 * 64 * 2 = 461V
			if(swGetAdcBusVoltReal() >= 4500)	// BUS电容是500V
			{
				mDisDCDCForcePWMOut();
				mDisDCDCHForcePWMOut();
			}
			else if(swGetAdcBusVoltReal() <= 4400)	// BUS电容是500V
			{
				mEnDCDCPWMOut();
				mEnDCDCHPWMOut();
				mEnDCDCForcePWMOut();
				mEnDCDCHForcePWMOut();
			}
		}
		else	// 软起结束后保持占空比
		{
			gi_wDCDCConvPWMValue = (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet;
			
			// for test LLC打嗝
			if(swGetAdcBusVoltReal() >= 4500)	// BUS电容是500V
			{
				mDisDCDCForcePWMOut();
				mDisDCDCHForcePWMOut();
			}
			else if(swGetAdcBusVoltReal() <= 4400)	// BUS电容是500V
			{
				mEnDCDCPWMOut();
				mEnDCDCHPWMOut();
				mEnDCDCForcePWMOut();
				mEnDCDCHForcePWMOut();
			}
		}

		// 确保频率在设定范围内
//		if(gi_wDCDCConvPWMPeriod > uwGetDcDcPWMPeriod())
//		{
//			gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
//		}
//		else if(gi_wDCDCConvPWMPeriod < uwGetDcDcPWMPeriod())
//		{
//			gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
//		}
		if(gi_wDCDCConvPWMPeriod > cDCDCConvertPeriod)
		{
			gi_wDCDCConvPWMPeriod = cDCDCConvertPeriod;
		}
		else if(gi_wDCDCConvPWMPeriod < cDCDCConvertPeriodMax)
		{
			gi_wDCDCConvPWMPeriod = cDCDCConvertPeriodMax;
		}


		// 确保在当前频率下，占空比不超设定值，死区限制
		wTemp = (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet;
		if(gi_wDCDCConvPWMValue > wTemp)
		{
			gi_wDCDCConvPWMValue = wTemp;
		}

		// 占空比达到一定值后允许进入WORK
		// 电压阈值需要实时计算，占空比值可以写死 for test
		if((swGetAdcBusVoltReal() >= 3000) && (gi_wDCDCConvPWMValue > 300))
		{
			sSetDCDCCtrlSts(cDCDCWork);
		}

		// 更新频率和占空比
		mDCDCConvPRD12 = gi_wDCDCConvPWMPeriod;	// L
		mDCDCConvPWM1 = gi_wDCDCConvPWMPeriod - gi_wDCDCConvPWMValue;
		mDCDCConvPWM2 = gi_wDCDCConvPWMValue;
		
		mDCDCConvPRD34 = gi_wDCDCConvPWMPeriod;	// H
		mDCDCConvPWM3 = gi_wDCDCConvPWMPeriod - gi_wDCDCConvPWMValue;
		mDCDCConvPWM4 = gi_wDCDCConvPWMValue;
	}
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	suwGetDCDCCtrlSts(void)							// 获取DCDC控制器状态
{
	return g_uwDCDCCtrlSts;
}

INT16U	suwGetLLCCtrlSts(void)							// 获取LLC控制器状态
{
	return g_uwLLCOn;
}

INT16U	suwGetDCDCConvPWMPeriod(void)					// 获取DCDC驱动实际频率寄存器值
{
	return gi_wDCDCConvPWMPeriod;
}

INT16U	suwGetDCDCConvPWMValue(void)					// 获取DCDC占空比实际值
{
	return gi_wDCDCConvPWMValue;
}

INT16U	suwGetDCDCSoftDutyFinish(void)					// 占空比软起完成标志
{
	return gi_wDCDCSoftDutyFinish;
}



/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void sSetDCDCCtrlStsIsr(INT16U uwDCDCCtrlSts)
{
	if(uwDCDCCtrlSts == cDCDCWait)
	{
		//sClrDCDCCtrlPara();
		g_uwLLCOn = false;
	}
	else if(uwDCDCCtrlSts == cDCDCWork || uwDCDCCtrlSts == cDCDCSoft)
	{
		g_uwLLCOn = true;
	}
	g_uwDCDCCtrlSts = uwDCDCCtrlSts;
}

void sSetDCDCCtrlSts(INT16U uwDCDCCtrlSts)					// 设置DCDC控制器状态
{
	OS_ENTER_CRITICAL();
	sSetDCDCCtrlStsIsr(uwDCDCCtrlSts);
	OS_EXIT_CRITICAL();
}

void	sSetLLCCtrlSts(INT16U uwTemp)						// 直接设置LLC控制状态
{
	OS_ENTER_CRITICAL();
	g_uwLLCOn = uwTemp;
	OS_EXIT_CRITICAL();
}

void	suwSetDCDCConvPWMValue(INT16U uwTemp)				// 设置LLC占空比
{
	OS_ENTER_CRITICAL();
	gi_wDCDCConvPWMValue = uwTemp;
	OS_EXIT_CRITICAL();
}


