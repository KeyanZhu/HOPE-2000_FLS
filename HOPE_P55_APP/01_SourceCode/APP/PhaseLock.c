/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__PHASE_LOCK_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"
#include    "Kernel\source\OS_HEAD.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sPhaseLockControl,".TI.ramfunc");

/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S g_wRSinPointer;
extern INT16S *pSinTab;
extern INT16S g_wInvDCCurrCtrl;
extern INT16S g_wInvDCCurrCtrlTemp;
extern INT16S g_wRSinAmp;
//extern INT16S g_wSSinAmp;
//extern INT16S g_wTSinAmp;
extern INT16S g_wRNewSinAmp;
//extern INT16S g_wSNewSinAmp;
//extern INT16S g_wTNewSinAmp;
extern INT16S gi_wSinePointMax;

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
INT16S wSinTheta,wCosTheta;
INT16S wSinIndex,wCosIndex;
INT16S wTheta0 = 0;
INT32S dwUr_PrePhasDely90 = 0;
INT32S dwUs_PrePhasDely90 = 0;
INT32S dwUt_PrePhasDely90 = 0;
INT32S dwUr_Pre = 0;
INT32S dwUs_Pre = 0;
INT32S dwUt_Pre = 0;
INT32S dwUd_PreFilt = 0;
INT32S dwUq_PreFilt = 0;

INT32S dwFreqIntCtrl = 0;
INT32S dwFreSatErr = 0;
INT32S dwPreThetaAmp = 0;

INT16S wSampAmpGain = 10;
INT16S wDIVIDE3 = 341;		// 341=0.3333*1024   Q10;
INT16S wDIVIDESQRT3 = 591;	// 591=0.57735*1024  Q10;
INT16S wSQRT3 = 1774;		// 1774=1.732*1024   Q10;
INT16S wI_SQRT3 = 591;		// 591=0.57735*1024  Q10;
INT16S wKP_PLL = 1034;		// KP=(314/311)*1024 (Q10)
INT16S wKI_PLL = 6;			// KI=Kp*(1/0.0087)*Ts*1024 (Q(10)
INT16S wKAW_PLL = 6;		// KAW=(1/0.0087)*Ts*1024 (Q(10)  Anti-Windup Gain

INT16S wTheta;
INT16S wCosTheta;
INT16S wSinTheta;
INT32S dwUd;
INT32S dwUq;

INT32S dwUr_PhasDely90,dwUs_PhasDely90,dwUt_PhasDely90;
INT32S dwUr_PosSeq,dwUs_PosSeq,dwUt_PosSeq;
INT32S dwUalfa,dwUbeta;
INT32S dwUd_Filt;
INT32S dwUq_Filt;

INT32S dwFreRegPreSat;
INT32S dwFreReg;
INT32S dwFreVal;
INT32S dwThetaAmp;
INT32S dwThetaTemp;
INT16U g_uwLineWaveLockFlag = true;

INT16S g_wInvSinPointBias = 5;

INT32S dwPllFre = 5000;

INT32U gi_udwPreLineZeroTimeNew = 0;	// 当前市电过零CAP值,50Hz=1800000,60Hz=1500000
INT32U gi_udwPreSineZeroTimeOld;		// 上次市电过零CAP值,50Hz=1800000,60Hz=1500000
INT16U gi_uwPreSinePeriodCntNew;		// 市电周期值,50Hz=20000,60Hz=16667

extern INT16S gi_wLineCrossZero;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sPhaseLockInitial(void)
{
	
}

void	sPhaseLockControl(INT16S wPhaseLockInputR,INT16S wPhaseLockInputS,INT16S wPhaseLockInputT)
{ 
	// Positive Sequence Component Extration
	//Y(s)/X(s)=(-S+314)/(S+314)
//	if(uEepromCfg2.EepromStructCfg2.wEEOutputFreq == 5000)
//	{
		//Y(s)/X(s)=(-S+314)/(S+314)
		dwUr_PhasDely90 = (dwUr_PrePhasDely90*8059>>13) - wPhaseLockInputR + (dwUr_Pre*8323>>13);
//		dwUs_PhasDely90 = (dwUs_PrePhasDely90*8059>>13) - wPhaseLockInputS + (dwUs_Pre*8323>>13);
//		dwUt_PhasDely90 = (dwUt_PrePhasDely90*8059>>13) - wPhaseLockInputT + (dwUt_Pre*8323>>13);
//	}
//	else
//	{
		//Y(s)/X(s)=(-S+377)/(S+377)
//		dwUr_PhasDely90 = (dwUr_PrePhasDely90*8033>>13) - wPhaseLockInputR + (dwUr_Pre*8348>>13);
//		dwUs_PhasDely90 = (dwUs_PrePhasDely90*8033>>13) - wPhaseLockInputS + (dwUs_Pre*8348>>13);
//		dwUt_PhasDely90 = (dwUt_PrePhasDely90*8033>>13) - wPhaseLockInputT + (dwUt_Pre*8348>>13);
//	}
	
	dwUr_PrePhasDely90 = dwUr_PhasDely90;
//	dwUs_PrePhasDely90 = dwUs_PhasDely90;
//	dwUt_PrePhasDely90 = dwUt_PhasDely90;
	
	dwUr_Pre = wPhaseLockInputR;
//	dwUs_Pre = wPhaseLockInputS;
//	dwUt_Pre = wPhaseLockInputT;

//	dwUr_PosSeq = wDIVIDE3*(2*wPhaseLockInputR - (wPhaseLockInputS + wPhaseLockInputT) - (wSQRT3*(dwUs_PhasDely90 - dwUt_PhasDely90)>>10))>>11;
//	dwUt_PosSeq = wDIVIDE3*(2*wPhaseLockInputT - (wPhaseLockInputR + wPhaseLockInputS) - (wSQRT3*(dwUr_PhasDely90 - dwUs_PhasDely90)>>10))>>11;
//	dwUs_PosSeq = -(dwUr_PosSeq + dwUt_PosSeq);
	dwUr_PosSeq = ((INT32S)wDIVIDE3*(2*wPhaseLockInputR))>>11;
	dwUt_PosSeq = ((INT32S)wDIVIDE3*(-wPhaseLockInputR  - (wSQRT3*(dwUr_PhasDely90)>>10)))>>11;
	dwUs_PosSeq = -(dwUr_PosSeq + dwUt_PosSeq);
	
	// abc-AlfaBeta Frame Transformation
	// abc-AlfaBeta框架变换
	dwUalfa = dwUr_PosSeq;
	dwUbeta = (dwUr_PosSeq + 2*dwUs_PosSeq)*wI_SQRT3 >> 10;
	
	// AlfaBeta-dq Frame Transformation
	// AlfaBeta-dq帧变换
	wSinIndex = wTheta0;
	wCosIndex = wSinIndex + (gi_wSinePointMax >> 2);
	
	// Compute Sin(Theta) and Cos(Theta) Values 
	// 计算Sin（Theta）和Cos（Theta）值
	if (wCosIndex >= gi_wSinePointMax)
	{
		wCosIndex = wCosIndex - gi_wSinePointMax;
	}
	wSinTheta = pSinTab[wSinIndex];
	wCosTheta = pSinTab[wCosIndex];
	
	// Compute Uq 
	// 计算Uq Ud = UAlpha * cos + UBeta * sin ; Uq = -UAlpha * sin + UBeta * cos
	//dwUd = -dwUrlfa*wSinTheta + dwUseta*wCosTheta >>14; 
	dwUd = (dwUalfa*wCosTheta + dwUbeta*wSinTheta) >>14;
	dwUq = (-dwUalfa*wSinTheta + dwUbeta*wCosTheta)>>14;

	// Filter F(s)	D
	// 过滤器F(s) 低通滤波器
	dwUd_Filt = (dwUd_PreFilt*981 + dwUd*43) >>10;   
	dwUd_PreFilt = dwUd_Filt;
	// Filter F(s)	Q
	// 过滤器F(s) 低通滤波器
	dwUq_Filt = (dwUq_PreFilt*981 + dwUq*43) >>10;   
	dwUq_PreFilt = dwUq_Filt;
	
	// Compute Frequency Intrgral Control Output 
	// 计算频率积分控制输出
	dwFreqIntCtrl = dwFreqIntCtrl + dwUd_Filt*wKI_PLL + dwFreSatErr*wKAW_PLL;
	
	// Compute the Pre-Saturated Frequency Regulation Output with PI Control
	// 通过PI控制计算预饱和频率调节输出
	dwFreRegPreSat = (dwUd_Filt*wKP_PLL + dwFreqIntCtrl) >>10;   	//wFreqCtrl( Precision = 0.01Hz*2*3.14*16=1)
	
	// Limit the Frequency Regulation
	// 限制频率调节
	if (dwFreRegPreSat > 1206)				//1206=12Hz*2*pi*wSampAmpGain
	{
		dwFreReg = 1206;
	}
	else if (dwFreRegPreSat < -1206)
	{
		dwFreReg = -1206;
	}
	else
	{
		dwFreReg = dwFreRegPreSat;
	}
	
	// Compute the saturate error for Anti-Windup Use
	// 计算Anti-Windup使用的饱和误差
	dwFreSatErr = dwFreReg - dwFreRegPreSat;
	
	// Final Frequency Value with Feedforward Compensation 
	// 带前馈补偿的最终频率值
//	if(uEepromCfg2.EepromStructCfg2.wEEOutputFreq == 5000)
//	{
		//dwFreVal = dwFreReg + 314*wSampAmpGain;    		//wFreqSet=50Hz*2*pi*wSampAmpGain
		dwFreVal = dwFreReg + 3141;    		//wFreqSet=50Hz*2*pi*10
		// 31415926
		
//	}
//	else
//	{
//		dwFreVal = dwFreReg + 377*wSampAmpGain;    		//wFreqSet=60Hz*2*pi*wSampAmpGain
//	}
	
	// The Angle(Theta) EqUrls the Frequency Integral
	// 角度（Theta）等于频率积分
	dwThetaAmp = dwPreThetaAmp + dwFreVal;
	dwPreThetaAmp = dwThetaAmp;
	
	//dwThetaTemp = dwThetaAmp/wSampAmpGain; 				//Decrease wSampAmpGain
	
//	if(uEepromCfg2.EepromStructCfg2.wEEOutputFreq == 5000)
//	{
		//wTheta = dwThetaTemp*13 >> 12;				//13=0.003183099*4096(Q12)  0.003183099=Ts*(180/pi)*(384/360)
//	}
//	else
//	{
//		wTheta = dwThetaTemp*87 >> 15;				//87=0.002652582*32768(Q15)  0.002652582=Ts*(180/pi)*(324/360)
//	}
	wTheta = (INT16S)((dwThetaAmp * 21) >> 16);		//20.8=0.0003183099*65536(Q16)  0.0003183099=Ts*(180/pi)*(384/360)

//	dwPreThetaAmpTemp = dwPreThetaAmp / wTheta;		// 逆变周期值 for test 20250527
	
	if(wTheta >= gi_wSinePointMax)   
	{
		dwPllFre = (((dwPreThetaAmp * 100) / 20) / 3.1415926) / gi_wSinePointMax;
		wTheta = 0;
		dwPreThetaAmp = 0;
		
		if(g_uwLineWaveLockFlag)	// for test
		{ 
			//Check if new line period is noise. Yes, Do not care.
			//if(ECap1Regs.TSCTR < cPeriod70Hz || ECap1Regs.TSCTR > cPeriod35Hz)
			if(0)
			{
				// To recieve more interrupts from this PIE group, acknowledge this interrupt 
				ECap1Regs.ECCLR.bit.CEVT1 = 1;
				ECap1Regs.ECCLR.bit.INT = 1;
				ECap1Regs.ECCTL2.bit.REARM = 1;
				PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
			}
			else
			{
				gi_udwPreLineZeroTimeNew = ECap1Regs.TSCTR;				// 定时读取捕获的时间戳计数器器值即可计算得出市电频率
				gi_uwPreSinePeriodCntNew = (INT16U)((gi_udwPreLineZeroTimeNew - gi_udwPreSineZeroTimeOld) / cPLL_FREQ_DIV);	
				gi_udwPreSineZeroTimeOld = gi_udwPreLineZeroTimeNew;		// 上次市电过零CAP值

				sAdcLineIsr();
				gi_wLineCrossZero = true;	// for test,应该放在软件锁相环的过零里面，但锁相完成之后这里也相当于市电过零点
				OSISREventSend(cPrioGrid, eGridLineZero);			// 市电过零
			}
		}
	}
	
	wTheta0 = wTheta;    					//wTheta is not the real angle degree, but is the index
}

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetPllTheta(void)
{
	return wTheta;
}

INT16S	swGetInvSinPointBias(void)
{
	return g_wInvSinPointBias;
}


INT16S	swGetPreSinePeriodCntNew(void)
{
	return gi_uwPreSinePeriodCntNew;
}

INT16S	swGetdwUd(void)
{
	return dwUd;
}
INT16S	swGetdwUq(void)
{
	return dwUq;
}

INT16S	swGetdwUd_Filt(void)
{
	return dwUd_Filt;
}
INT16S	swGetdwUq_Filt(void)
{
	return dwUq_Filt;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/


