/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__INV_CONTROL_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sInverterVoltCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sInverterCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sdwInvVoltCntl,".TI.ramfunc");
#pragma CODE_SECTION(swFBVoltLoopCntl,".TI.ramfunc");


/********************************************************************************
* Constants																		*
********************************************************************************/
#define cCntl_InvVoltKv				24
#define cCntl_InvVoltKi				700

typedef struct
{
	INT16S wInvVoltCntl;
	INT16S wInvCurrCntl;
	INT16S wLoadCurrCntl;
	INT16S wInvDCVoltCntl;
	INT16S wInvVref;
	INT16S wInvVoltError;
	INT16S wReptCtrl[1][384];
	INT16S wRctrlFvalue;
	INT16S wRepetCtrlValue;
	INT16S wRepetCtrlValuePre[3];
	INT16S wKRctrl1;
	INT16S wKRctrl2;
	INT16S wRepetCtrlUp;
	INT16S wRepetCtrUnder;
	INT16S wKv;
	INT16S wKi;
	INT16S wKs;
	INT16S wShareCurrCtrlEn;
	INT16S wOPShareCurrCntl;
	INT16S wOPShareCurrCntl_1;
	INT16S wOPShareCurrCntl_Filter;
	INT16S wOPShareCurrCntlErr;
	INT16S wOPShareCurrCntlErr_1;
	INT16S wOPShareCurrCntlErr_Filter;
	INT16S wOPShareCurrCntlVal;
	INT32S dwVBeforeSaturation;
	INT16S wInvVoltCurrLimit;
	INT16S wRepeatCntlClrCnt;
	INT32S dwVoltLimit;
	INT32S g_dwK_0[3];
}StrInvVoltCtrlPara;

StrInvVoltCtrlPara g_strInvVoltCtrlPara;

typedef struct
{
	INT32S dwBusVoltSum;
	INT32S dwBatVoltSum;
	INT16S wLoopCnt;
	INT16S wBusVoltAvg;
	INT16S wBatVoltAvg;
	INT16S wBusVoltErr;
	INT16S wBatVoltErr;
	INT16S wBatVoltKp;
	INT16S wBusVoltKp;
	INT16S wBusVoltKi;
	INT16S wDCDCBusKpFast;
	INT16S wDCDCBusKiFast;
	INT16S wDCDCBusKpSlow;
	INT16S wDCDCBusKiSlow;
	INT32S dwBusVolt_P;
	INT32S dwBusVolt_I;
	INT32S dwBusVoltMo;
	INT32S dwDCDCIref;
	INT32S dwDCDCILimit;
	INT16S wDCDCIerr;
	INT16S wDCDCIKp;
	INT16S wDCDCIKi;
	INT32S dwDCDCI_P;
	INT32S dwDCDCI_I[4];
	INT32S dwDCDCPWM;
}StrDCDCCtrlPara;

StrDCDCCtrlPara g_strDCDCCtrlPara;


typedef struct
{
	INT32S dwBusVoltSum;
	INT16S wBusVoltAvg;
	INT16S wFBCntLoop;
	INT16S wBusVoltErr;
	INT16S wBusVoltKp;
	INT16S wFBCtrlSwitch;
	INT16S wFBVerr_P;
	INT16S wFBVerr_P_1;
	INT16S wFBVm_P;
	INT16S wFBVm_P_1;
	INT16S wFBVm_P_res;
	INT16S wFBVmo;
	INT16S wFBVmoComp;
	INT16S wFBKvd_1;
	INT16S wFBKvd_2;
	INT16S wFBKvn_1;
	INT16S wFBKvn_2;
	INT16S wFBImo_P;
	INT16S wFB_Is_P;
	INT16S wFBKCurrFB;
	INT16S wFB_Ierr_P;
	INT16S wFB_Ierr_P_0;
	INT16S wFB_Ierr_P_1;
	INT16S wFBCurrKi;
	INT16S wFB_Icmp_P;
	INT16S wFB_Icmp_P_1;
	INT16S wFB_Icmp_P_2;
	INT16S wDCDCCntlBusVoltErr;
}StrInvCurrCtrlPara;

StrInvCurrCtrlPara g_strInvCurrCtrlPara;


INT16S g_wInvCurrCntlPre[3];


/********************************************************************************
* External variables															*
********************************************************************************/
extern	INT16S	SinTab384[384];
extern	INT16S	CosTab384[384];

extern INT16S g_wRFixCapaReactivePower;

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
INT16S* pSinTab = SinTab384;
INT16S* pCosTab = CosTab384;

extern INT16S g_wPwmPeriod;
extern INT16S g_wRSinAmp;
INT16U g_uwFBInvCtrlSts = cFBWait;
INT16S gi_wInvPWMEn;

INT16S g_wKpwm = 833;	//Q7 cPWMCntlPeriod50Hz/360V*128	// 20241025 需要重新计算
INT16S g_wVref;
INT16S g_wLoopOutput;
INT16S g_wInvPWM;
INT16S g_wR_PWMDirectionPre;

INT16S g_wKv = 20;//24;//cCntl_InvVoltKv;
INT16S g_wKi = 680;//500;//cCntl_InvVoltKi;
INT16S g_wInvVoltCurrLimit = 600;//    cCntl_InvCurrLimit;	// Q5//  (1100W/220V*1.414*32

INT16S g_wRInvVoltCntl;
INT16S g_wRInvCurrCntl;
INT16S g_wRLoadCurrCntl;
extern INT16S g_wRInvDCVoltCntl;
extern INT16S g_wReactiveCurrTanRate;
INT16S g_wSinValueR = 0;
INT16S wShareCtrlEn =0;
INT16S gi_wROPShareCurrCntl;
INT32S g_dwInvVoltCtrlVo;

INT32U g_dwRSinPionterQ15 = 0;
INT16S g_wRSinPointer = 0;
INT16S g_wRSinPointerTemp = 0;
INT16S g_wRSinPointerwThetaTemp = 0;
INT16S gi_wSinePointOneSix = 64;
INT16S gi_wSinePointOneFour = 96;
INT16S gi_wSinePointTwoSix = 128;
INT16S gi_wSinePointThreeSix = 192;
INT16S gi_wSinePointFourSix = 256;
INT16S gi_wSinePointFiveSix = 320;
INT16S gi_wSinePointMax = 384;
INT16S gi_wSinePointMaxTwo = 768;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INT16U wTestInvPwmCntSet = 9999;
INT16U wTestInvPwmCnt = 9999;

INT16U	g_wRSinAmpTest = 10408;
INT16U	g_wKpwmTest = 833;
void	sInverterCtrl(void)	// 开环
{
	g_wRSinAmp = g_wRSinAmpTest;//10408;//	230*1.414*32	// 写入固定值，不受采样影响
	g_wKpwm = g_wKpwmTest;									// 写入固定值，不受采样影响
	g_wVref = (INT16S)(((INT32S)g_wRSinAmp * pSinTab[g_wRSinPointer] >> 14));	// 正弦化
	g_wLoopOutput = (INT16S)((INT32S)g_wVref * g_wKpwm >> 12); 

	if(g_wLoopOutput > (g_wPwmPeriod - 1))
	{
		g_wLoopOutput = g_wPwmPeriod - 1;
	}
	if(g_wLoopOutput < -(g_wPwmPeriod -1))
	{
		g_wLoopOutput = -(g_wPwmPeriod -1);
	}
	
	if(g_wLoopOutput > 0 || (g_wR_PWMDirectionPre == 0 && g_wLoopOutput == 0))    
	{
		g_wInvPWM = g_wLoopOutput + 75;
		if(g_wInvPWM > (g_wPwmPeriod -2))
		{
			g_wInvPWM = (g_wPwmPeriod -2);
		}
		else if(g_wInvPWM < 1)
		{
			g_wInvPWM = 1;
		}
		
		mRPInvPWM = g_wPwmPeriod - g_wInvPWM;	
		mRNInvPWM = g_wPwmPeriod - 1;

		if(g_wR_PWMDirectionPre != 0)
		{
			g_wR_PWMDirectionPre = 0;
			mDisForceNUPWM();
		}
		else
		{
			mEnForceNULow();	//NU LOW, ND HIGH
		}
	}
	else
	{
		g_wInvPWM = -g_wLoopOutput;
		g_wInvPWM = g_wInvPWM + 75;
		if(g_wInvPWM > (g_wPwmPeriod -2))
		{
			g_wInvPWM = (g_wPwmPeriod -2);
		}
		else if(g_wInvPWM < 1)
		{
			g_wInvPWM = 1;
		}

		mRPInvPWM = g_wInvPWM;
		mRNInvPWM = 1;

		if(g_wR_PWMDirectionPre != 1)
		{
			g_wR_PWMDirectionPre = 1;
			mDisForceNUPWM();
		}
		else
		{
			mEnForceNUHigh();	//NU HIGH, ND LOW
		} 	
	}
}

void	sInitInvVoltCntlPara(void)
{
	g_strInvVoltCtrlPara.wRctrlFvalue = 100;
	g_strInvVoltCtrlPara.wKRctrl1 = 197;
	g_strInvVoltCtrlPara.wKRctrl2 = 29;
	g_strInvVoltCtrlPara.wRepetCtrlUp = 640;
	g_strInvVoltCtrlPara.wRepetCtrUnder = -640;
	g_strInvVoltCtrlPara.wKv = 24;//48;
	g_strInvVoltCtrlPara.wKi = 700;//300;	
	g_strInvVoltCtrlPara.wKs = 24;//24;
	g_strInvVoltCtrlPara.wInvVoltCurrLimit = 1251;	//39.1A*32
	g_strInvVoltCtrlPara.wRepeatCntlClrCnt = 0;
	g_strInvVoltCtrlPara.wOPShareCurrCntl_1 = 0;
	g_strInvVoltCtrlPara.wOPShareCurrCntlErr_1 = 0;
}

void	sInvVoltCntlParaClr(void)
{
	g_strInvVoltCtrlPara.wRepeatCntlClrCnt = 0;
	g_strInvVoltCtrlPara.wOPShareCurrCntl_1 = 0;
	g_strInvVoltCtrlPara.wOPShareCurrCntlErr_1 = 0;
	g_strInvVoltCtrlPara.wRepetCtrlValuePre[0] = 0;
	g_strInvVoltCtrlPara.wRepetCtrlValuePre[1] = 0;
	g_strInvVoltCtrlPara.wRepetCtrlValuePre[2] = 0;
	g_strInvVoltCtrlPara.g_dwK_0[0] =0;
	g_strInvVoltCtrlPara.g_dwK_0[1] =0;
	g_strInvVoltCtrlPara.g_dwK_0[2] =0;
	g_wInvCurrCntlPre[0] = 0;
	g_wInvCurrCntlPre[1] = 0;
	g_wInvCurrCntlPre[2] = 0;
}

void	sInvertVoltCtrlParaInit(void)
{
	sInitInvVoltCntlPara();
	sSetInvVoltCtrlParaKv(g_wKv);
	sSetInvVoltCtrlParaKi(g_wKi);
	sSetInvVoltCtrlParaCurrLimit(g_wInvVoltCurrLimit);
	g_wR_PWMDirectionPre = 2;
}

void	sInvertVoltCtrlParaClr(void)
{
	sInvVoltCntlParaClr();
	g_wR_PWMDirectionPre = 2;
}

INT32S	sdwInvVoltCntl(INT16S wInvVoltCntlQ5, INT16S wInvCurrCntlQ5,
									INT16S wLoadCurrCntlQ5, INT16S wInvDCVoltCntlQ5,INT16S wShareCurrCntlQ5, INT16S wShareCntlEn,
									INT16S wInvSinpoint, INT16S wInvSinpointMax, INT16S wInvSinAmp, INT16S wInvSinValue,INT16S Phase)
{
	INT16S wInvVoltErrorRCtrl;
	INT16S wSintemp;
	if(Phase > 2)
	{
		return 0;
	}
	
	g_strInvVoltCtrlPara.wInvVoltCntl 	= 	wInvVoltCntlQ5;
	g_strInvVoltCtrlPara.wInvCurrCntl 	= 	wInvCurrCntlQ5;
	g_strInvVoltCtrlPara.wLoadCurrCntl 	= 	wLoadCurrCntlQ5;

	//参考电压计算
	g_strInvVoltCtrlPara.wInvVref = (INT16S)(((INT32S)wInvSinAmp * wInvSinValue >> 14)) + wInvDCVoltCntlQ5;

	// 电压误差计算与限幅
	g_strInvVoltCtrlPara.wInvVoltError = g_strInvVoltCtrlPara.wInvVref - g_strInvVoltCtrlPara.wInvVoltCntl;
	if(g_strInvVoltCtrlPara.wInvVoltError > 3200) 
	{
		g_strInvVoltCtrlPara.wInvVoltError = 3200;    //100*32=3200
	}
	else if(g_strInvVoltCtrlPara.wInvVoltError < -3200)
	{
		g_strInvVoltCtrlPara.wInvVoltError = -3200;
	} 

//	if(g_strInvVoltCtrlPara.wRepeatCntlClrCnt < wInvSinpointMax)
//	{
//		if(g_strInvVoltCtrlPara.wRepeatCntlClrCnt < 384)
//		{
//			g_strInvVoltCtrlPara.wReptCtrl[g_strInvVoltCtrlPara.wRepeatCntlClrCnt] = 0;
//		}
//		g_strInvVoltCtrlPara.wRepeatCntlClrCnt++;
//	}
//	else
	{
		/***************************** Repeat control**********************/
		// 1. 取电压误差作为重复控制输入
		wInvVoltErrorRCtrl = g_strInvVoltCtrlPara.wInvVoltError;
		// 2. 计算历史相位索引（上一周期对应点）
		wSintemp = wInvSinpoint + wInvSinpointMax - 8;
		if(wSintemp >= wInvSinpointMax)
		{
		    wSintemp -= wInvSinpointMax;
		}
		// 3. 更新重复控制历史数组（加权修正）
		g_strInvVoltCtrlPara.wReptCtrl[Phase][wSintemp]=(INT16S)(((INT32S)g_strInvVoltCtrlPara.wRctrlFvalue*(g_strInvVoltCtrlPara.wReptCtrl[Phase][wSintemp]+wInvVoltErrorRCtrl))>>8);   
		// 4. 计算当前重复控制输出（融合历史输出与历史误差）
		g_strInvVoltCtrlPara.wRepetCtrlValue = (INT16S)(((INT32S)g_strInvVoltCtrlPara.wKRctrl1*g_strInvVoltCtrlPara.wRepetCtrlValuePre[Phase]\
							+(INT32S)g_strInvVoltCtrlPara.wKRctrl2*g_strInvVoltCtrlPara.wReptCtrl[Phase][wInvSinpoint])>>8);
		// 5. 重复控制输出限幅
		if(g_strInvVoltCtrlPara.wRepetCtrlValue > g_strInvVoltCtrlPara.wRepetCtrlUp)   
		{
		    g_strInvVoltCtrlPara.wRepetCtrlValue = g_strInvVoltCtrlPara.wRepetCtrlUp;
		}
		else if(g_strInvVoltCtrlPara.wRepetCtrlValue < g_strInvVoltCtrlPara.wRepetCtrUnder)    
		{
		    g_strInvVoltCtrlPara.wRepetCtrlValue = g_strInvVoltCtrlPara.wRepetCtrUnder;
		}
		// 6. 更新历史状态，将重复控制结果叠加到电压误差
		g_strInvVoltCtrlPara.wRepetCtrlValuePre[Phase] = g_strInvVoltCtrlPara.wRepetCtrlValue;
		g_strInvVoltCtrlPara.wInvVoltError += g_strInvVoltCtrlPara.wRepetCtrlValue;           		//delete repeat control
		/***************************** Repeat control**********************/
	}

	//电压环输出
	g_strInvVoltCtrlPara.dwVBeforeSaturation = ((INT32S)g_strInvVoltCtrlPara.wInvVoltError*g_strInvVoltCtrlPara.wKv>>7)\
												+ g_strInvVoltCtrlPara.wLoadCurrCntl;	
	//负载电流均衡
	if(wShareCntlEn)
	{
		// 保存当前均流控制量
		g_strInvVoltCtrlPara.wOPShareCurrCntl = wShareCurrCntlQ5;
		// 均流控制量一阶滤波
		g_strInvVoltCtrlPara.wOPShareCurrCntl_Filter = (g_strInvVoltCtrlPara.wOPShareCurrCntl + g_strInvVoltCtrlPara.wOPShareCurrCntl_1) >> 1;
		g_strInvVoltCtrlPara.wOPShareCurrCntl_1 = g_strInvVoltCtrlPara.wOPShareCurrCntl;
		g_strInvVoltCtrlPara.wOPShareCurrCntlErr = g_strInvVoltCtrlPara.wOPShareCurrCntl_Filter - g_strInvVoltCtrlPara.wLoadCurrCntl;
		// 计算均流误差并滤波
		g_strInvVoltCtrlPara.wOPShareCurrCntlErr_Filter = (g_strInvVoltCtrlPara.wOPShareCurrCntlErr + g_strInvVoltCtrlPara.wOPShareCurrCntlErr_1) >> 1;
		g_strInvVoltCtrlPara.wOPShareCurrCntlErr_1 = g_strInvVoltCtrlPara.wOPShareCurrCntlErr;
		// 计算均流控制输出并叠加到电压环输出
		g_strInvVoltCtrlPara.wOPShareCurrCntlVal = (INT16S)(((INT32S)g_strInvVoltCtrlPara.wOPShareCurrCntlErr_Filter  * g_strInvVoltCtrlPara.wKs) >> 5);
		g_strInvVoltCtrlPara.dwVBeforeSaturation += g_strInvVoltCtrlPara.wOPShareCurrCntlVal;
	}
	
	// 限幅
	if(g_strInvVoltCtrlPara.dwVBeforeSaturation > g_strInvVoltCtrlPara.wInvVoltCurrLimit)
	{
		g_strInvVoltCtrlPara.dwVBeforeSaturation = g_strInvVoltCtrlPara.wInvVoltCurrLimit;			//43<<5  
		g_strInvVoltCtrlPara.wInvCurrCntl = g_strInvVoltCtrlPara.wInvCurrCntl * 2 - g_wInvCurrCntlPre[Phase];
	}
	else if(g_strInvVoltCtrlPara.dwVBeforeSaturation < -g_strInvVoltCtrlPara.wInvVoltCurrLimit)
	{
		g_strInvVoltCtrlPara.dwVBeforeSaturation = -g_strInvVoltCtrlPara.wInvVoltCurrLimit;		 	//43<<5    
		g_strInvVoltCtrlPara.wInvCurrCntl = g_strInvVoltCtrlPara.wInvCurrCntl * 2 - g_wInvCurrCntlPre[Phase];
	}
	g_wInvCurrCntlPre[Phase] = g_strInvVoltCtrlPara.wInvCurrCntl;
	
	// 电流环输出计算
	g_strInvVoltCtrlPara.dwVoltLimit = ((g_strInvVoltCtrlPara.dwVBeforeSaturation - g_strInvVoltCtrlPara.wInvCurrCntl)*g_strInvVoltCtrlPara.wKi >> 7);

	// 滤波，用系数 123 和 133（总和 256）对电压限制值进行加权平均（类似低通滤波），降低输出波动
	g_strInvVoltCtrlPara.g_dwK_0[Phase] = ((g_strInvVoltCtrlPara.dwVoltLimit * 123) + (g_strInvVoltCtrlPara.g_dwK_0[Phase] * 133)) >> 8;
	// 叠加电压反馈
	g_strInvVoltCtrlPara.dwVoltLimit = g_strInvVoltCtrlPara.g_dwK_0[Phase] + g_strInvVoltCtrlPara.wInvVoltCntl;
//	g_strInvVoltCtrlPara.dwVoltLimit = g_strInvVoltCtrlPara.g_dwK_0[Phase] + (INT16S)((F32)g_strInvVoltCtrlPara.wInvVoltCntl*0.7) \
//										+ (INT16S)((F32)g_strInvVoltCtrlPara.wInvVref * 0.3);								// 叠加了正弦参考可降低带RCD载THDU
		
	if(g_strInvVoltCtrlPara.dwVoltLimit > 16000)  g_strInvVoltCtrlPara.dwVoltLimit = 16000;			//500V max     
	if(g_strInvVoltCtrlPara.dwVoltLimit < -16000) g_strInvVoltCtrlPara.dwVoltLimit = -16000;		//500V max   

	return(g_strInvVoltCtrlPara.dwVoltLimit);
}


void	sInverterVoltCtrl(void)		// 闭环
{
	INT16S wTempLimit = 0;
	
	wTempLimit = swGetAdcInvCurrReal();
	if(wTempLimit > 1131)  //8A
	{
		wTempLimit = 1131;
	}
	else if(wTempLimit < -1131)
	{
		wTempLimit = -1131;
	}
	g_wRInvVoltCntl = mInvVoltQ5(swGetAdcInvVoltReal());
	g_wRInvCurrCntl = mInvCurrQ5(swGetAdcInvCurrReal());
	g_wRLoadCurrCntl = mOPCurrQ5(wTempLimit);
	
	gi_wROPShareCurrCntl = 0;
	
	g_dwInvVoltCtrlVo = sdwInvVoltCntl(g_wRInvVoltCntl,g_wRInvCurrCntl,\
					g_wRLoadCurrCntl,g_wRInvDCVoltCntl,gi_wROPShareCurrCntl,wShareCtrlEn,\
					g_wRSinPointer,gi_wSinePointMax,g_wRSinAmp,pSinTab[g_wRSinPointer],PhaseR);
	
	g_wLoopOutput = (INT16S)((g_dwInvVoltCtrlVo * g_wKpwm) >> 12);
	if(g_wLoopOutput > (g_wPwmPeriod - 40))
	{
		g_wLoopOutput = g_wPwmPeriod - 40;
	}
	if(g_wLoopOutput < -(g_wPwmPeriod -40))
	{
		g_wLoopOutput = -(g_wPwmPeriod -40);
	}
	
	if(g_wLoopOutput > 0 || (g_wR_PWMDirectionPre == 0 && g_wLoopOutput == 0))    
	{
		g_wInvPWM = g_wLoopOutput;// + 75;
		if(g_wInvPWM > (g_wPwmPeriod -2))
		{
			g_wInvPWM = (g_wPwmPeriod -2);
		}
		else if(g_wInvPWM < 1)
		{
			g_wInvPWM = 1;
		}
		
		mRPInvPWM = g_wPwmPeriod - g_wInvPWM;	
		mRNInvPWM = g_wPwmPeriod - 1;

		if(g_wR_PWMDirectionPre != 0)
		{
			g_wR_PWMDirectionPre = 0;
			mDisForceNUPWM();
		}
		else
		{
			mEnForceNULow();	//NU LOW, ND HIGH
		}
	}
	else
	{
		g_wInvPWM = -g_wLoopOutput;
		g_wInvPWM = g_wInvPWM;// + 75;
		if(g_wInvPWM > (g_wPwmPeriod -2))
		{
			g_wInvPWM = (g_wPwmPeriod -2);
		}
		else if(g_wInvPWM < 1)
		{
			g_wInvPWM = 1;
		}

		mRPInvPWM = g_wInvPWM;
		mRNInvPWM = 1;

		if(g_wR_PWMDirectionPre != 1)
		{
			g_wR_PWMDirectionPre = 1;
			mDisForceNUPWM();
		}
		else
		{
			mEnForceNUHigh();	//NU HIGH, ND LOW
		} 	
	}
}

// 并网
extern INT16S g_wRInvDCCurrCtrl;


void sInitInvCurrCntlPara(void)
{
	g_strInvCurrCtrlPara.wBusVoltKp = 20;//25;//50;//4*32;// 4*Q5  //12 while 4*32,FB  feeding 3000w,bus is not statable.
	g_strInvCurrCtrlPara.wFBKvn_1 = 4509;
	g_strInvCurrCtrlPara.wFBKvn_2 = 4204;
	g_strInvCurrCtrlPara.wFBKvd_1 = 14065;
	g_strInvCurrCtrlPara.wFBKvd_2 = 5872;
	g_strInvCurrCtrlPara.wFBVm_P_res = 0;
	g_strInvCurrCtrlPara.wFBVmoComp = 4096;     //voltage compensation
	g_strInvCurrCtrlPara.wFBKCurrFB = 1;  //1:100
	
	g_strInvCurrCtrlPara.wFBCurrKi = 15;//30;//8;
	g_strInvCurrCtrlPara.wBusVoltErr=g_strInvCurrCtrlPara.wFBVerr_P_1 = g_strInvCurrCtrlPara.wFBVm_P = g_strInvCurrCtrlPara.wFBVm_P_1= g_strInvCurrCtrlPara.wFBVm_P_res=0;
	g_strInvCurrCtrlPara.wFB_Ierr_P_0=g_strInvCurrCtrlPara.wFB_Ierr_P_1 = g_strInvCurrCtrlPara.wFB_Ierr_P=g_strInvCurrCtrlPara.wFB_Icmp_P_1 = g_strInvCurrCtrlPara.wFB_Icmp_P_2 = g_strInvCurrCtrlPara.wFB_Icmp_P =0;
	
}

void sInvCurrCntlParaClr(void)
{
	g_strInvCurrCtrlPara.wFBCtrlSwitch = 1;
	g_strInvCurrCtrlPara.wFBCntLoop = 0;
	g_strInvCurrCtrlPara.wBusVoltErr=0;
	g_strInvCurrCtrlPara.wFBVerr_P_1 = 0;
	g_strInvCurrCtrlPara.wFBVm_P = 0;
	g_strInvCurrCtrlPara.wFBVm_P_1 = 0;
	g_strInvCurrCtrlPara.wFBVm_P_res=0;
	g_strInvCurrCtrlPara.wFB_Ierr_P_0=0;
	g_strInvCurrCtrlPara.wFB_Ierr_P_1 = 0;
	g_strInvCurrCtrlPara.wFB_Ierr_P=0;
	g_strInvCurrCtrlPara.wFB_Icmp_P_1 = 0;
	g_strInvCurrCtrlPara.wFB_Icmp_P_2 = 0;
	g_strInvCurrCtrlPara.wFB_Icmp_P = 0;
	g_strInvCurrCtrlPara.dwBusVoltSum = 0;
	g_strInvCurrCtrlPara.wBusVoltAvg = 0;
	g_strInvCurrCtrlPara.wFBVmo =0;
	g_strInvCurrCtrlPara.wDCDCCntlBusVoltErr =0;
}

void sInvCurrCntlCurrLoopClr(void)
{
	g_strInvCurrCtrlPara.wFB_Ierr_P_0=0;
	g_strInvCurrCtrlPara.wFB_Ierr_P_1 = 0;
	g_strInvCurrCtrlPara.wFB_Ierr_P=0;
	g_strInvCurrCtrlPara.wFB_Icmp_P_1 = 0;
	g_strInvCurrCtrlPara.wFB_Icmp_P_2 = 0;
	g_strInvCurrCtrlPara.wFB_Icmp_P = 0;
	g_strDCDCCtrlPara.wBusVoltErr = 0;
}
void sInvCurrCntlVoltaLoopClr(void)
{
	g_strInvCurrCtrlPara.wFBCntLoop = 0;
	g_strInvCurrCtrlPara.wBusVoltErr=0;
	g_strInvCurrCtrlPara.wFBVerr_P_1 = 0;
	g_strInvCurrCtrlPara.wFBVm_P = 0;
	g_strInvCurrCtrlPara.wFBVm_P_1 = 0;
	g_strInvCurrCtrlPara.wFBVm_P_res=0;
	g_strInvCurrCtrlPara.dwBusVoltSum =0;
	g_strInvCurrCtrlPara.wFBVmo =0;
}

INT16S swFBVoltLoopCntl(INT16S wBusVolt10, INT16S wBusVref,INT16S wBatChgInvLimit,
							INT16S wInvChgCurrLimit, INT16S wInvFeedCurrLimit,INT16S Phase)
{
	INT32S dwTemp = 0;
	
	if(Phase >2)
	{
		return 0;
	}
	g_strInvCurrCtrlPara.dwBusVoltSum += wBusVolt10;
	if(++g_strInvCurrCtrlPara.wFBCntLoop & 0x08)
	{
		g_strInvCurrCtrlPara.wBusVoltAvg = (INT16S)(g_strInvCurrCtrlPara.dwBusVoltSum>>3);
		g_strInvCurrCtrlPara.dwBusVoltSum = 0;

		g_strInvCurrCtrlPara.wBusVoltErr = wBusVref - g_strInvCurrCtrlPara.wBusVoltAvg;           //controll bus voltage
		
		g_strInvCurrCtrlPara.wFBCntLoop = 0;
		
		if(g_strInvCurrCtrlPara.wBusVoltErr > 300) g_strInvCurrCtrlPara.wBusVoltErr = 300;
		if(g_strInvCurrCtrlPara.wBusVoltErr < -300) g_strInvCurrCtrlPara.wBusVoltErr = -300;
		
		g_strInvCurrCtrlPara.wFBVerr_P = (INT16S)(((INT32S)g_strInvCurrCtrlPara.wBusVoltErr * g_strInvCurrCtrlPara.wBusVoltKp) >> 5);
//		wFBVerr_PTest = g_strInvCurrCtrlPara.wFBVerr_P;
		
		if(g_strInvCurrCtrlPara.wFBCtrlSwitch == 1)
		{
			g_strInvCurrCtrlPara.wFBCtrlSwitch = 0;
			g_strInvCurrCtrlPara.wFBVerr_P_1 = g_strInvCurrCtrlPara.wFBVerr_P;
		}

		dwTemp = (INT32S)g_strInvCurrCtrlPara.wFBKvd_1 * g_strInvCurrCtrlPara.wFBVm_P\
				- (INT32S)g_strInvCurrCtrlPara.wFBKvd_2 * g_strInvCurrCtrlPara.wFBVm_P_1\
				+ (INT32S)g_strInvCurrCtrlPara.wFBKvn_1 * g_strInvCurrCtrlPara.wFBVerr_P\
				- (INT32S)g_strInvCurrCtrlPara.wFBKvn_2 * g_strInvCurrCtrlPara.wFBVerr_P_1\
				+ g_strInvCurrCtrlPara.wFBVm_P_res;
			
		g_strInvCurrCtrlPara.wFBVm_P_1 = g_strInvCurrCtrlPara.wFBVm_P;							
		g_strInvCurrCtrlPara.wFBVm_P =(INT16S)(dwTemp >> 13);
	
		g_strInvCurrCtrlPara.wFBVm_P_res = dwTemp & 0x01FFF;
		g_strInvCurrCtrlPara.wFBVerr_P_1 = g_strInvCurrCtrlPara.wFBVerr_P;

		g_strInvCurrCtrlPara.wDCDCCntlBusVoltErr =(INT16S)(((INT32S)g_strInvCurrCtrlPara.wFBVm_P - wBatChgInvLimit) >> 4);// 7	

		if(g_strInvCurrCtrlPara.wFBVm_P > (wInvChgCurrLimit + 600)) 
		{
			g_strInvCurrCtrlPara.wFBVm_P = wInvChgCurrLimit+600;		//boost from grid
		}
		else if(g_strInvCurrCtrlPara.wFBVm_P < -(wInvFeedCurrLimit + 600))  
		{
			g_strInvCurrCtrlPara.wFBVm_P = -(wInvFeedCurrLimit + 600);	//feeding to grid
		}
		
		if(g_strInvCurrCtrlPara.wFBVm_P_1 > (wInvChgCurrLimit + 600))  
		{
			g_strInvCurrCtrlPara.wFBVm_P_1 = wInvChgCurrLimit+600;
		}
		else if(g_strInvCurrCtrlPara.wFBVm_P_1 < -(wInvFeedCurrLimit + 600)) 
		{
			g_strInvCurrCtrlPara.wFBVm_P_1 = -(wInvFeedCurrLimit + 600);
		}

		g_strInvCurrCtrlPara.wFBVmo = g_strInvCurrCtrlPara.wFBVm_P;
		if(g_strInvCurrCtrlPara.wFBVmo > wInvChgCurrLimit)   g_strInvCurrCtrlPara.wFBVmo = wInvChgCurrLimit;		//boost from grid
		else if(g_strInvCurrCtrlPara.wFBVmo < -wInvFeedCurrLimit)  g_strInvCurrCtrlPara.wFBVmo = -wInvFeedCurrLimit;//feeding to grid
	}
	return g_strInvCurrCtrlPara.wFBVmo;
}


void	sFBINVPFCInitial(void)
{
	sInitInvCurrCntlPara();			// 并网BUS电压外环控制参数初始化
}

void	sClearFBRam(void)
{
	g_wR_PWMDirectionPre = 2;
	sInvCurrCntlParaClr();			// 并网BUS电压外环参数初始化
}

void	sClearFBRCurrRam(void)
{
	sInvCurrCntlVoltaLoopClr();		// 并网BUS电压外环参数清除
}

INT16S sGetLoopOutput(void)
{
	return g_wLoopOutput;
}

void	sSetFBInvCtrlStsIsr(INT16U uwFBCtrlSts)
{
	if(uwFBCtrlSts == cFBWait)
	{
		EPwm1Regs.AQCTLA.all = 0x0555;
		EPwm1Regs.AQCTLB.all = 0x0555;
		EPwm1Regs.DBCTL.bit.OUT_MODE = 0;		
		EPwm1Regs.CMPA.bit.CMPA = 0xFFFF;	 
		EPwm1Regs.CMPB.all = 0xFFFF;
		
		EPwm2Regs.AQCTLA.all = 0x0555;
		EPwm2Regs.AQCTLB.all = 0x0555;
		EPwm2Regs.DBCTL.bit.OUT_MODE = 0;		
		EPwm2Regs.CMPA.bit.CMPA = 0xFFFF;	 
		EPwm2Regs.CMPB.all = 0xFFFF; 
		
		//hoRINVPWMENOff;
		mDisINVPWMOut();
		sClearFBRam();
		sInvertVoltCtrlParaClr();
		

		// 新控制器 for test
		sInvVoltLoopCtrlInit();
		sFBINVController2Init();
		sFBBUSController2Init();
	}
	else
	{
		if(g_uwFBInvCtrlSts == cFBWait)
		{
			EPwm1Regs.AQCTLA.all = 0;
			EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
			EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
			EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			EPwm2Regs.AQCTLA.all = 0;
			EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
			EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
			EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
			
			if(uwFBCtrlSts == cFBInvCtrlBus)
			{
				//g_wInvBusVoltRef = swGetBusVoltFilter();	// for test
			}
			wTestInvPwmCnt = wTestInvPwmCntSet;	// for test
		}
	}
	g_uwFBInvCtrlSts = uwFBCtrlSts;
}

void	sSetFBInvCtrlSts(INT16U uwFBCtrlSts)
{
	OS_ENTER_CRITICAL();
	sSetFBInvCtrlStsIsr(uwFBCtrlSts);
	OS_EXIT_CRITICAL();	
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetRSinPointer(void)
{
	return g_wRSinPointer;
}

INT16U	suwGetFBInvCtrlSts(void)
{
	return g_uwFBInvCtrlSts;
}

INT16S	swGetInvKpwm(void)
{
	return g_wKpwm;
}

INT16S	swGetInvVref(void)
{
	return g_wVref;
}

INT16S	swGetInvPWMEn(void)
{
	return gi_wInvPWMEn;
}

INT16S	swGetInvRPInvPWM(void)
{
	return mRPInvPWM;
}

INT16S	swGetInvRNInvPWM(void)
{
	return mRNInvPWM;
}

INT16S	swGetInvLPInvPWM(void)
{
	return mLPInvPWM;
}

INT16S	swGetInvLNInvPWM(void)
{
	return mLNInvPWM;
}

INT16S	swGetDCDCCtrlFBBusErr(void)
{
	return g_strInvCurrCtrlPara.wDCDCCntlBusVoltErr;
}

INT16S	swGetInvVoltCntl(void)
{
	return g_strInvVoltCtrlPara.wInvVoltCntl;
}

INT16S	swGetwInvVref(void)
{
	return g_strInvVoltCtrlPara.wInvVref;
}
INT16S	swGetInvPWM(void)
{
	return g_wInvPWM;
}
INT16S	swGetg_wLoopOutput(void)
{
	return g_wLoopOutput;
}


INT16S	swGetg_dwInvVoltCtrlVo(void)
{
	return g_dwInvVoltCtrlVo;
}


/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetInvKpwm(INT16S wValue)
{
	OS_ENTER_CRITICAL();
	g_wKpwm = wValue;
	OS_EXIT_CRITICAL();
}

void	sSetInvPWMEn(INT16S wValue)
{
	OS_ENTER_CRITICAL();
	gi_wInvPWMEn = wValue;
	OS_EXIT_CRITICAL();
}

void	sSetInvVoltCtrlParaKv(INT16S wValue)
{
	g_strInvVoltCtrlPara.wKv = wValue;
}

void	sSetInvVoltCtrlParaKi(INT16S wValue)
{
	g_strInvVoltCtrlPara.wKi = wValue;
}

void	sSetInvVoltCtrlParaCurrLimit(INT16S wValue)
{
	g_strInvVoltCtrlPara.wInvVoltCurrLimit = wValue;
}
void	sSetRSinPointer(INT16S wValue)
{
	OS_ENTER_CRITICAL();
	g_wRSinPointer = wValue;
	OS_EXIT_CRITICAL();
}



