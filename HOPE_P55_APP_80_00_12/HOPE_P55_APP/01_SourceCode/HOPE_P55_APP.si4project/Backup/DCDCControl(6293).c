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
INT16U gi_wDCDCConvPWMValue1 = 0;							// 实际占空比
INT16U gi_wDCDCConvPWMPeriod = 0;							// 实际频率(周期值)
INT16U gi_wDCDCConvPWMDTSet = cDCDCConvPWMDTSetLimit;		// 发波死区

INT16U uwLLCSoftCnt = 0;									// 占空比软起计数
INT16U g_uwLLCPauseTime = 500;								// 起始状态保持时间
INT16U g_uwLLCMinDutyTime = 800;							// 最小占空比持续时间(启机占空比)
INT16U g_uwLLCSoftDutyRate = 100;//300;							// 每次占空比软起时间
INT16U g_uwLLCSoftFreqRate = 4000;							// 每次频率软起时间
INT16U gi_wDCDCConvPWMPeriodStart = cDCDCConvertPeriodMax;	// 频率软起起始频率
INT16U gi_wDCDCConvPWMPeriodSet = cDCDCConvertPeriodDef;	// 频率软起截至频率

INT16U gi_wDCDCSoftDutyFinish = false;						// 占空比软起完成标志
INT16U gi_wGridChgBatLowCutFlag = false;						// 电池低压充电占空比软起完成标志


INT16U gi_wDCDCHighPWMDuty = 0;							// 高压侧占空比
INT16U gi_wDCDCLowPWMDuty = 0;							// 低压侧占空比
INT16U gi_wChgModeFlagEn = false;					//高压充电标志		
INT16U gi_wHighSoftFinish = 0;	
INT16U gi_wHighSoftFinishCnt = 0;


INT16U gi_wDCDCHighPWMDutyLimit = 100;					//高压侧占空比限制
INT16U gi_wDCDCHighPWMDutyLimitRate = 2000;					//高压侧占空比限制
INT16U gi_wDCDCHighPWMDutyLimitRateCnt = 0;					//高压侧占空比限制
INT16U uwHighSoftCnt = 0;									// 占空比软起计数
INT16U g_uwHighPauseTime = 1000;	
INT16U g_uwHighSoftDutyRate = 1000;
INT16U gi_wDCDCHighPWMDutyLimitInit = 100;					//高压侧占空比限制初始值


INT16U gi_wDCDCLowPWMDutyLimit = 50;					//低压侧占空比限制
INT16U gi_wDCDCLowPWMDutyLimitRate = 2000;					//低压侧占空比限制
INT16U gi_wDCDCLowPWMDutyLimitRateCnt = 0;					//低压侧占空比限制
INT16U uwLowSoftCnt = 0;									// 占空比软起计数
INT16U g_uwLowPauseTime = 6000;	
INT16U g_uwLowSoftDutyRate = 2000;
INT16U gi_wDCDCLowPWMDutyLimitInit = 100;					//高压侧占空比限制初始值
INT16U gi_Trueflag = 0;				



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

	gi_wDCDCHighPWMDuty = 0;							// 高压侧占空比
	gi_wDCDCLowPWMDuty = 0;							// 低压侧占空比
	gi_wDCDCHighPWMDutyLimit = 100;					//高压侧占空比限制
	
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
	INT16S wLimitTemp;
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
		g_uwLLCMinDutyTime = 30000;//50000;//cWait40uSTimeSet;   //35000 150
		uwLLCSoftCntTest = 0;	// FOR TEST
		gi_wDCDCSoftDutyFinish = false;

		gi_wDCDCHighPWMDuty = 0;						// 高压侧占空比
		gi_wDCDCLowPWMDuty = 0;							// 低压侧占空比
		gi_wDCDCHighPWMDutyLimit = 100;					//高压侧占空比限制

//		gi_wDCDCHighPWMDutyLimit = 100;					//高压侧占空比限制
		gi_wDCDCHighPWMDutyLimitRate = 2000;					//高压侧占空比限制
		gi_wDCDCHighPWMDutyLimitRateCnt = 0;					//高压侧占空比限制
		uwHighSoftCnt = 0;									// 占空比软起计数
		g_uwHighPauseTime = cWait40uSTimeSet;	
		g_uwHighSoftDutyRate = 1000;

		gi_wDCDCLowPWMDutyLimit = 50;					//低压侧占空比限制
		gi_wDCDCLowPWMDutyLimitRate = 2000;					//低压侧占空比限制
		gi_wDCDCLowPWMDutyLimitRateCnt = 0;					//低压侧占空比限制
		uwLowSoftCnt = 0;									// 占空比软起计数
		g_uwLowPauseTime = cWait40uSTimeSet;	
		g_uwLowSoftDutyRate = 1000;
		
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
		if(gi_wDCDCConvPWMDTSet <= cDCDCConvertDutyStart)
		{
			gi_wDCDCConvPWMDTSet = cDCDCConvertDutyStart;
		}
		else if(gi_wDCDCConvPWMDTSet > wPwmDutyMinTemp)
		{
			gi_wDCDCConvPWMDTSet = wPwmDutyMinTemp;
		}

		if(gi_wChgModeFlagEn == true)//  进入高压充电发波逻辑
		{
		  //低压侧封波              高压侧软起
			if(g_uwHighPauseTime > 0)		// 进入发波，开启高压侧先进行一段时间封波保持，不立即发波
			{
				g_uwHighPauseTime--;
				mDisDCDCForcePWMOut();
				mDisDCDCHForcePWMOut();
				gi_wDCDCHighPWMDuty = 0;
				gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
			}
			else if(gi_wDCDCHighPWMDuty < gi_wDCDCHighPWMDutyLimit)					//高压侧占空比限制)		// 占空比软起
			{
				if(++uwHighSoftCnt >= g_uwHighSoftDutyRate)
				{
					uwHighSoftCnt = 0;
					gi_wDCDCHighPWMDuty++;
				}

				mEnDCDCHPWMOut();
				mEnDCDCHForcePWMOut();		
			}
			else	// 软起结束后保持占空比
			{
				gi_wDCDCHighPWMDuty = gi_wDCDCHighPWMDutyLimit;					//高压侧占空比限制;
	
				mEnDCDCHPWMOut();
				mEnDCDCHForcePWMOut();	
			}
			
			if((swGetTriChgFlag() == false) && (gi_wDCDCHighPWMDuty > 80))            //退出涓流时增加高压侧占空比直至打满, 且低压侧打占空比
//			if(gi_Trueflag == true)
			{
				if(gi_wDCDCHighPWMDutyLimit < (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet)
				{
					if(++gi_wDCDCHighPWMDutyLimitRateCnt >= gi_wDCDCHighPWMDutyLimitRate)
					{
						gi_wDCDCHighPWMDutyLimitRateCnt = 0;
						gi_wDCDCHighPWMDutyLimit++;
					}
				}
				else
				{
					gi_wDCDCHighPWMDutyLimit = (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet;
					if(++gi_wHighSoftFinishCnt > 30000)
					{
						gi_wHighSoftFinishCnt = 0;
						gi_wHighSoftFinish = true;
					}
						
				}
				//高压侧互补后  软起低压侧
				if(gi_wHighSoftFinish == true)
				{				
					if(g_uwLowPauseTime > 0)		// 进入发波，开启低压侧先进行一段时间封波保持，不立即发波
					{
						g_uwLowPauseTime--;
						gi_wDCDCLowPWMDuty = 0;
						gi_wDCDCConvPWMPeriod = uwGetDcDcPWMPeriod();
					}
					else if(gi_wDCDCLowPWMDuty < gi_wDCDCLowPWMDutyLimit)					//低压侧占空比限制)		// 占空比软起
					{
						if(++uwLowSoftCnt >= g_uwLowSoftDutyRate)
						{
							uwLowSoftCnt = 0;
							gi_wDCDCLowPWMDuty++;
						}
					
						mEnDCDCPWMOut();
						mEnDCDCForcePWMOut();		
					}
					else	// 软起结束后保持占空比
					{
						gi_wDCDCLowPWMDutyLimit = gi_wDCDCLowPWMDutyLimit;					//高压侧占空比限制;
			
						mEnDCDCPWMOut();
						mEnDCDCForcePWMOut();		
					
					}
					
					if(gi_wDCDCLowPWMDutyLimit < (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet)
					{
						if(++gi_wDCDCLowPWMDutyLimitRateCnt >= gi_wDCDCLowPWMDutyLimitRate)
						{
							gi_wDCDCLowPWMDutyLimitRateCnt = 0;
							gi_wDCDCLowPWMDutyLimit++;
						}
					}
					else
					{
						gi_wDCDCLowPWMDutyLimit = (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet;
//						gi_wHighSoftFinish = true;
						
					}
						
				}
				else
				{

				}
			}
			else
			{
				gi_wHighSoftFinish = false;
				mDisDCDCForcePWMOut();
				mEnDCDCHPWMOut();
				mEnDCDCHForcePWMOut();	
			}
			
			//高压侧占空比大于低压侧占空比
			if(gi_wDCDCLowPWMDutyLimit > gi_wDCDCHighPWMDutyLimit)
			{
				gi_wDCDCLowPWMDutyLimit =  gi_wDCDCHighPWMDutyLimit;
			}

			
			//   高压侧占空比限制
			wLimitTemp = (gi_wDCDCConvPWMPeriod >> 1) - gi_wDCDCConvPWMDTSet;
			if(gi_wDCDCHighPWMDutyLimit > wLimitTemp)
			{
				gi_wDCDCHighPWMDutyLimit = wLimitTemp;
			}
			if(gi_wDCDCHighPWMDuty > wLimitTemp)
			{
				gi_wDCDCHighPWMDuty = wLimitTemp;
			}
			if(gi_wDCDCHighPWMDuty > gi_wDCDCHighPWMDutyLimit)
			{
				gi_wDCDCHighPWMDuty = gi_wDCDCHighPWMDutyLimit;
			}
			//   低压侧占空比限制
			if(gi_wDCDCLowPWMDutyLimit > wLimitTemp)
			{
				gi_wDCDCLowPWMDutyLimit = wLimitTemp;
			}
			if(gi_wDCDCLowPWMDuty > wLimitTemp)
			{
				gi_wDCDCLowPWMDuty = wLimitTemp;
			}
			if(gi_wDCDCLowPWMDuty > gi_wDCDCLowPWMDutyLimit)
			{
				gi_wDCDCLowPWMDuty = gi_wDCDCLowPWMDutyLimit;
			}
//			Uplimit(gi_wDCDCHighPWMDuty, gi_wDCDCHighPWMDutyLimit);
//			Uplimit(gi_wDCDCHighPWMDuty, wLimitTemp);
			
			if((swGetAdcBusVoltReal() >= 3000) && (gi_wDCDCHighPWMDuty > 40))
			{
				sSetDCDCCtrlSts(cDCDCWork);
			}
			
			mDCDCConvPRD12 = gi_wDCDCConvPWMPeriod;	// L
			mDCDCConvPWM1 = gi_wDCDCConvPWMPeriod - gi_wDCDCLowPWMDuty;
			mDCDCConvPWM2 = gi_wDCDCLowPWMDuty;

			mDCDCConvPRD34 = gi_wDCDCConvPWMPeriod;	// H
			mDCDCConvPWM3 = gi_wDCDCConvPWMPeriod - gi_wDCDCHighPWMDuty;
			mDCDCConvPWM4 = gi_wDCDCHighPWMDuty;

			
			
		}
		else //if(gi_wGridChgBatLowCutFlag == false)
		{
			//正常推挽软起
	
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
	//			mDisDCDCForcePWMOut();
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
				// for test LLC打嗝
				// 3.3 * 64 * 2 = 423V
				// 3.6 * 64 * 2 = 461V
				if(suwGetFBInvCtrlSts() != cFBInvCtrlBus)
				{
					if(swGetAdcBusVoltReal() >= 4800)	// BUS电容是500V
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

	//					mDisDCDCForcePWMOut();
	//		//			mEnDCDCPWMOut();
	//					mEnDCDCHPWMOut();
	//		//			mEnDCDCForcePWMOut();
	//					mEnDCDCHForcePWMOut();						
					}
				}		
				else 		// 并网时，不允许DCDC打嗝
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
				if(suwGetFBInvCtrlSts() != cFBInvCtrlBus)
				{
					if(swGetAdcBusVoltReal() >= 4800)	// BUS电容是500V
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

	//					mDisDCDCForcePWMOut();
	//				//	mEnDCDCPWMOut();
	//					mEnDCDCHPWMOut();
	//				//	mEnDCDCForcePWMOut();
	//					mEnDCDCHForcePWMOut();

					}
				}		
				else 
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
INT16U	suwGetDCDCConvPWMValue1(void)					// 获取DCDC占空比实际值
{
	return gi_wDCDCConvPWMValue1;
}
INT16U	suwGetLLCMinDutyTime(void)					// 获取DCDC占空比实际值
{
	return g_uwLLCMinDutyTime;
}
INT16U	suwGetLLCSoftDutyRate(void)					// 获取DCDC占空比实际值
{
	return g_uwLLCSoftDutyRate;
}
INT16U	suwGetGridChgBatLowCutFlag(void)					
{
	return gi_wGridChgBatLowCutFlag;
}

INT16U	suwGetChgModeFlagEn(void)					
{
	return gi_wChgModeFlagEn;
}

INT16U	suwGetDCDCHighPWMDutyLimit(void)					
{
	return gi_wDCDCHighPWMDutyLimit;
}
INT16U	suwGetDCDCLowPWMDutyLimit(void)					
{
	return gi_wDCDCLowPWMDutyLimit;
}
INT16U	suwGetDCDCHighPWMDuty(void)					
{
	return gi_wDCDCHighPWMDuty;
}
INT16U	suwGetDCDCLowPWMDuty(void)					
{
	return gi_wDCDCLowPWMDuty;
}

INT16U	suwGetTrueflag(void)					
{
	return gi_Trueflag;
}


INT16U	suwGetHighSoftFinish(void)					
{
	return gi_wHighSoftFinish;
}




/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetHighSoftFinish(INT16U uwTemp)						// 直接设置LLC控制状态
{
	OS_ENTER_CRITICAL();
	gi_wHighSoftFinish = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetLLCMinDutyTime(INT16U uwTemp)						// 直接设置LLC控制状态
{
	OS_ENTER_CRITICAL();
	g_uwLLCMinDutyTime = uwTemp;
	OS_EXIT_CRITICAL();
}
void	sSetLLCSoftDutyRate(INT16U uwTemp)						// 直接设置LLC控制状态
{
	OS_ENTER_CRITICAL();
	g_uwLLCSoftDutyRate = uwTemp;
	OS_EXIT_CRITICAL();
}

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
void	suwSetDCDCConvPWMValue1(INT16U uwTemp)				// 设置LLC占空比
{
	OS_ENTER_CRITICAL();
	gi_wDCDCConvPWMValue1 = uwTemp;
	OS_EXIT_CRITICAL();
}
void	sSetGridChgBatLowCutFlag(INT16U uwTemp)			
{
	OS_ENTER_CRITICAL();
	gi_wGridChgBatLowCutFlag = uwTemp;
	OS_EXIT_CRITICAL();
}
void	sSetChgModeFlagEn(INT16U uwTemp)			
{
	OS_ENTER_CRITICAL();
	gi_wChgModeFlagEn = uwTemp;
	OS_EXIT_CRITICAL();
}
void	sSetDCDCLowPWMDutyLimit(INT16U uwTemp)			
{
	OS_ENTER_CRITICAL();
	gi_wDCDCLowPWMDutyLimit = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetDCDCHighPWMDutyLimit(INT16U uwTemp)			
{
	OS_ENTER_CRITICAL();
	gi_wDCDCHighPWMDutyLimit = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetTrueflag(INT16U uwTemp)			
{
	OS_ENTER_CRITICAL();
	gi_Trueflag = uwTemp;
	OS_EXIT_CRITICAL();
}

