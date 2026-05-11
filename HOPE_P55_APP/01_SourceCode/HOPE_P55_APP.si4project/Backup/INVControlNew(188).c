/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__INV_CONTROLNEW_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sInvVoltRealLoopCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sInvCurrRealLoopCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sGridBusLoopCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sGridFBLoopCtrl,".TI.ramfunc");
#pragma CODE_SECTION(sFBBUSController2,".TI.ramfunc");
#pragma CODE_SECTION(sFBINVController2,".TI.ramfunc");



/********************************************************************************
* Constants																		*
********************************************************************************/


/********************************************************************************
* External variables															*
********************************************************************************/
extern INT16S* pSinTab;
extern INT16S* pCosTab;
extern INT16S g_wRSinPointer;

INT32S	wCtrlLoopOutPwm = 0;
extern 	INT16S g_wKpwm;
extern 	INT16S g_wPwmPeriod;
extern 	INT16S g_wInvPWM;
extern INT16S g_wR_PWMDirectionPre;


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
INT16S	g_wInvVoltRmsLoopRef = 2300;	// 有效值环路参考
INT16S	g_wInvVoltRmsLoopErr = 0;		// 有效值环路误差
INT16S	g_wInvVoltRmsLoopKP = 2;		// 有效值环路KP	// 还需要调整
INT16S	g_wInvVoltRmsLoopKI = 1;		// 有效值环路KI	// 还需要调整
INT32S	g_wInvVoltRmsLoopRmsI = 0;		// 有效值环路积分累积
INT16S	g_wInvVoltRmsLoopOUT = 0;		// 有效值环路输出

											// 在控制器调不到REF的时候可以尝试增加前馈补偿占空比，让环路调节小一点
INT16U	g_uwInvVoltFeedWard = 25;			// 电压前馈, 10是不放大也不缩小，25是放大2.5倍
INT16S	g_wLoadCurrFeedWard = 0;			// 电流前馈
INT16S	g_wLoadCurrFeedWardKP = 0;			// 电流前馈补偿系数
INT16S	g_wInvVoltRealKP = 200;				// 电压外环KP	// 还需要调整
INT16S	g_wInvVoltRealLoopRef = 0;			// 瞬时电压外环电压参考计算
INT16S	g_wInvVoltRealLoopSoftRef = 0;		// 瞬时电压外环电压软起参考
INT16U	g_uwInvVoltRealLoopSoftFlag = 1;	// 瞬时电压外环电压软起参考标志
INT16S	g_wInvVoltRealLoopCtrlRef = 0;		// 瞬时电压外环电压参考实际值
INT16S	g_wInvVoltRealLoopErr = 0;			// 实际值与参考值的误差
INT16S	g_wInvVoltRealOut = 0;				// 瞬时电压外环输出结果


INT16S	g_wInvCurrRealRef = 0;		// 电流内环参考
INT16S	g_wInvCurrRealErr = 0;		// 电流误差
INT16S	g_wInvCurrRealKp = 3;		// 电流KP系数	// 还需要调整
INT16S	g_wInvCurrRealOut = 0;		// 控制器输出
INT16S	g_wInvCtrlLoopOut = 0;		// 整个控制环路输出

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sInvVoltLoopCtrlInit(void)
{
	g_wInvVoltRmsLoopRef = 2300;	// 有效值环路参考
	g_wInvVoltRmsLoopErr = 0;		// 有效值环路误差
//	g_wInvVoltRmsLoopKP = 2;		// 有效值环路KP	// 还需要调整
//	g_wInvVoltRmsLoopKI = 1;		// 有效值环路KI	// 还需要调整
	g_wInvVoltRmsLoopRmsI = 0;		// 有效值环路积分累积
	g_wInvVoltRmsLoopOUT = 0;		// 有效值环路输出

										// 在控制器调不到REF的时候可以尝试增加前馈补偿占空比，让环路调节小一点
	g_uwInvVoltFeedWard = 25;			// 电压前馈, 10是不放大也不缩小，25是放大2.5倍
	g_wLoadCurrFeedWard = 0;			// 电流前馈
	g_wLoadCurrFeedWardKP = 0;			// 电流前馈补偿系数
//	g_wInvVoltRealKP = 200;				// 电压外环KP	// 还需要调整
	g_wInvVoltRealLoopRef = 0;			// 瞬时电压外环电压参考计算
	g_wInvVoltRealLoopSoftRef = 0;		// 瞬时电压外环电压软起参考
	g_uwInvVoltRealLoopSoftFlag = 1;	// 瞬时电压外环电压软起参考标志
	g_wInvVoltRealLoopCtrlRef = 0;		// 瞬时电压外环电压参考实际值
	g_wInvVoltRealLoopErr = 0;			// 实际值与参考值的误差
	g_wInvVoltRealOut = 0;				// 瞬时电压外环输出结果


	g_wInvCurrRealRef = 0;		// 电流内环参考
	g_wInvCurrRealErr = 0;		// 电流误差
//	g_wInvCurrRealKp = 3;		// 电流KP系数	// 还需要调整
	g_wInvCurrRealOut = 0;		// 控制器输出
	g_wInvCtrlLoopOut = 0;		// 整个控制环路输出
}


void	sInvVoltRmsLoopCtrl(void)	// 离网电压有效值外环	20ms任务运行
{
	g_wInvVoltRmsLoopRef = uwGetInvRMSCtrlVolt();
	
	if(suwGetFBInvCtrlSts() == cFBInvCtrlVolt)
	{
		// 计算实际误差
	    g_wInvVoltRmsLoopErr = g_wInvVoltRmsLoopRef - swGetRInvVoltNew();
		if(g_wInvVoltRmsLoopErr > 200)	// 20V
		{
			g_wInvVoltRmsLoopErr = 200;
		}
		else if(g_wInvVoltRmsLoopErr < -200)
		{
			g_wInvVoltRmsLoopErr = -200;
		}

		// PI调节
	    g_wInvVoltRmsLoopOUT = g_wInvVoltRmsLoopRmsI + g_wInvVoltRmsLoopErr * g_wInvVoltRmsLoopKP;
		if(g_wInvVoltRmsLoopOUT > 2800) // 输出限幅 280V
		{
			g_wInvVoltRmsLoopOUT = 2800;
		}
		else if(g_wInvVoltRmsLoopOUT < -2800)
		{
			g_wInvVoltRmsLoopOUT = -2800;
		}
	    g_wInvVoltRmsLoopRmsI += g_wInvVoltRmsLoopErr * g_wInvVoltRmsLoopKI;
		if(g_wInvVoltRmsLoopRmsI > 2800) // 积分限幅 280V
		{
			g_wInvVoltRmsLoopRmsI = 2800;
		}
		else if(g_wInvVoltRmsLoopRmsI < -2800)
		{
			g_wInvVoltRmsLoopRmsI = -2800;
		}
	}
}


void	sInvVoltRealLoopCtrl(void)	// 离网瞬时电压外环，中断运行
{
	// 电流前馈
    g_wLoadCurrFeedWard = swGetRInvCurrNew() * g_wLoadCurrFeedWardKP / 10;	

	// 计算瞬时逆变电压参考(RMS --> DC --> SIN)
	g_wInvVoltRealLoopRef = (INT16S)(((INT32S)(g_wInvVoltRmsLoopRef * g_uwInvVoltFeedWard / 10 + g_wInvVoltRmsLoopOUT + g_wLoadCurrFeedWard) * 181 >> 7) * pSinTab[g_wRSinPointer] >> 14);

	// 逆变电压软起(控制器内部软起)
	if(abs(g_wInvVoltRealLoopSoftRef - g_wInvVoltRealLoopRef) <= 141)	// 软起完成 141 = 10V
	{
		g_wInvVoltRealLoopSoftRef = g_wInvVoltRealLoopRef;
		g_uwInvVoltRealLoopSoftFlag = 0;
	}
	else if(g_wInvVoltRealLoopSoftRef < g_wInvVoltRealLoopRef)			// 实际值比参考值小
	{
		g_wInvVoltRealLoopSoftRef += 1;
	}
	else if(g_wInvVoltRealLoopSoftRef > g_wInvVoltRealLoopRef)			// 实际值比参考值大
	{
		g_wInvVoltRealLoopSoftRef -= 1;
	}

	// 控制器参考选择
	if(g_uwInvVoltRealLoopSoftFlag)										// == true 软起未完成，使用软起值
	{
		g_wInvVoltRealLoopCtrlRef = g_wInvVoltRealLoopSoftRef;			//切换或软起时继承逆变电容上的残余电压
	}
	else
	{
		g_wInvVoltRealLoopCtrlRef = g_wInvVoltRealLoopRef;				//稳态运行
	}

	// 参考与实际值的误差 考虑叠加一个重复控制器或者直流分量补偿
    g_wInvVoltRealLoopErr = g_wInvVoltRealLoopCtrlRef - swGetAdcInvVoltReal();	// 实测效果不理想的话可以考虑把重复控制加进来
	if(g_wInvVoltRealLoopErr > 278)		// = 3200/230*0.2*100	// 需要×sin？，这里没有做
	{
		g_wInvVoltRealLoopErr = 278;
	}
	else if(g_wInvVoltRealLoopErr < -278)
	{
		g_wInvVoltRealLoopErr = -278;
	}

	// 电压外环 KP /输出限幅
    g_wInvVoltRealOut = g_wInvVoltRealLoopErr * g_wInvVoltRealKP;
	if(g_wInvVoltRealOut > 1391)		// = 3200/230*100
	{
		g_wInvVoltRealOut = 1391;
	}
	else if(g_wInvVoltRealOut < -1391)
	{
		g_wInvVoltRealOut = -1391;
	}
}


void 	sInvCurrRealLoopCtrl(void)		// 离网瞬时电流内环，中断运行
{
    g_wInvCurrRealRef = g_wInvVoltRealOut;								// 电流内环参考 = 电压外环输出
    g_wInvCurrRealErr = g_wInvCurrRealRef - swGetAdcInvCurrReal();		// 与实际误差
    g_wInvCurrRealOut = g_wInvCurrRealErr * g_wInvCurrRealKp;			// KP计算
	if(g_wInvCurrRealOut > 690)	// = 230*0.3	// 需要×sin？，这里没有做
	{
		g_wInvCurrRealOut = 690;
	}
	else if(g_wInvCurrRealOut < -690)
	{
		g_wInvCurrRealOut = -690;
	}

    //调制波 = 电压基准前馈 + 控制器补偿
	g_wInvCtrlLoopOut = g_wInvCurrRealOut + g_wInvVoltRealLoopCtrlRef;

	// 占空比计算     	离网，用调制比还原占空比  3250 × 1000 >> 12 = 793
	wCtrlLoopOutPwm = (INT16S)(((INT32S)g_wInvCtrlLoopOut * g_wKpwm) >> 12);

//以下是管子发波部分(考虑一下做成函数形式)
	// 限制占空比不超过最大值-1
	if(wCtrlLoopOutPwm > (g_wPwmPeriod - 1))
	{
		wCtrlLoopOutPwm = g_wPwmPeriod - 1;
	}
	if(wCtrlLoopOutPwm < -(g_wPwmPeriod -1))
	{
		wCtrlLoopOutPwm = -(g_wPwmPeriod -1);
	}

	// 正负半周发波
	if(wCtrlLoopOutPwm > 0 || (g_wR_PWMDirectionPre == 0 && wCtrlLoopOutPwm == 0))    
	{
		g_wInvPWM = wCtrlLoopOutPwm;// + 75;
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
		g_wInvPWM = -wCtrlLoopOutPwm;
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

//////////////////////////////////////////////////////////////////////////////////并网
// for test
INT16S g_wInvBusVoltRefTest = 4200;		// 并网控制器BUS电压参考
INT16S g_wRFBVm_P;						// BUS电压外环输出
INT16S gi_wInvChgCurrLimit = -5;		// -5是补偿;	// 并网最大买电电流 市电给电池充电
INT16S gi_wInvFeedCurrLimit = 5;		// 5是补偿;	// 并网最大卖电电流 电池向市电馈电
INT16S gi_wBatChgInvLimit = 0;			// 并网充放电电流限制值,动态调整,负数卖电,正数买电	// IVDM不适用，拓扑不一样
INT16S gi_wInvFeedCurrLimitTemp = 20;
INT16S g_wInvBusVoltRef = 3600;			// BUS电压参考

INT16S g_wInvFeedBusVoltRef = 4608;//4140;		// 并网BUS电压参考 414V = 23V × 18变比

INT16S	g_wGridBusLoopOUT = 0;			// 并网BUS环路输出
void	sGridBusLoopCtrl(void)			// 并网BUS电压外环，中断运行
{
	// 先用swFBVoltLoopCntl这个控制器
	g_wRFBVm_P = swFBVoltLoopCntl(swGetAdcBusVoltReal(),g_wInvFeedBusVoltRef,gi_wBatChgInvLimit,gi_wInvChgCurrLimit,gi_wInvFeedCurrLimitTemp,PhaseR);
	g_wGridBusLoopOUT = g_wRFBVm_P;
	if(g_wGridBusLoopOUT > 300)	// 输出限幅 30A
	{
		g_wGridBusLoopOUT = 300;
	}
	else if(g_wGridBusLoopOUT < -500)
	{
		g_wGridBusLoopOUT = 300;
	}
	sSetOscTestData1(g_wGridBusLoopOUT);
}


INT16S	g_wGridPowerLoopDB = 0;			// 并网功率反馈值
INT16S	g_wGridPowerLoopRef = 500;		// 并网功率环路参考
INT16S	g_wGridPowerLoopErr = 0;		// 并网功率环路误差
F32		fGridPowerLoopOUT = 0;		// 并网功率环路输出
F32		fGridPowerLoopKP = 0.5;			// 并网功率环路KP	// 还需要调整
F32		fGridPowerLoopKI = 0.00123;			// 并网功率环路KI	// 还需要调整
F32		fGridPowerLoopI = 0;			// 并网功率环路积分累积
INT16S	g_wInvWattTemp = 0;
void	sGridPowerLoopCtrl(void) // 并网功率外环，1ms运行，20ms应该也可以，但总觉得风险太大，有波动调节不及时，可以改成锁相环算DQ，功率
{
	// 计算实际误差
    g_wGridPowerLoopDB = g_wInvWattTemp;//swGetRInvWattNew();	// 20ms值
    g_wGridPowerLoopErr = g_wGridPowerLoopRef - g_wGridPowerLoopDB;
	if(g_wGridPowerLoopErr > 20)	// 20W
	{
		g_wGridPowerLoopErr = 20;
	}
	else if(g_wGridPowerLoopErr < -20)
	{
		g_wGridPowerLoopErr = 20;
	}

	// PI调节
	fGridPowerLoopOUT = fGridPowerLoopI + g_wGridPowerLoopErr * fGridPowerLoopKP;
	if(fGridPowerLoopOUT > 50)	// 输出限幅 5A
	{
		fGridPowerLoopOUT = 50;
	}
	else if(fGridPowerLoopOUT < -50)
	{
		fGridPowerLoopOUT = 50;
	}
	if(fGridPowerLoopOUT > g_wGridBusLoopOUT)
	{
		fGridPowerLoopOUT = g_wGridBusLoopOUT;
	}
	else if(fGridPowerLoopOUT < -g_wGridBusLoopOUT)
	{
		fGridPowerLoopOUT = -g_wGridBusLoopOUT;
	}
	fGridPowerLoopI += g_wGridPowerLoopErr * fGridPowerLoopKI;
	if(fGridPowerLoopI > 50)		// 积分限幅 5A
	{
		fGridPowerLoopI = 50;
	}
	else if(fGridPowerLoopI < -50)
	{
		fGridPowerLoopI = 50;
	}
}

INT16S	g_wGridLoopIdRef = 0;		// 并网电流环路电流的直流电流参考值
INT16S	g_wGridCurrLoopRef = 0;		// 并网电流环路电流的正弦电流参考值
INT16S	g_wGridCurrLoopErr = 0;		// 并网电流环路电流的误差值
INT16S	g_wGridCurrLoopKP = 1;		// 并网电流环路电流的KP
INT16S	g_wGridCurrLoopOUT = 0;		// 并网电流环路电流的输出
INT16S	g_wGridFBLoopOUT = 0;		// 整个并网环路的输出
void	sGridFBLoopCtrl(void)	// 并网电流内环，中断运行
{
	// 电流参考 RMS CURR --> DC CURR
	g_wGridLoopIdRef = (INT16S)((INT32S)(fGridPowerLoopOUT + g_wGridPowerLoopRef) * 181 >> 7);	

	// 电流变成sin参考 DC CURR -- AC CURR
	g_wGridCurrLoopRef = (INT16S)((INT32S)g_wGridLoopIdRef * pSinTab[g_wRSinPointer] >> 14);		// 还没有加前馈	
	//g_wGridCurrLoopRef += (INT16S)(((INT32S)pCosTab[g_wRSinPointerTemp] * 1) >> 14);	// 1 : g_wRFixCapaReactivePower，这里暂时不做

	// P控制
	g_wGridCurrLoopErr = g_wGridCurrLoopRef - swGetAdcInvCurrReal();			// 误差值	// 是不是要把实际电流取反？
	g_wGridCurrLoopOUT = g_wGridCurrLoopErr * g_wGridCurrLoopKP;				// KP计算
	if(g_wGridCurrLoopOUT > 751)	// 需要×sin?，这里没有做
	{
		g_wGridCurrLoopOUT = 751;
	}
	else if(g_wGridCurrLoopOUT < -751)
	{
		g_wGridCurrLoopOUT = -751;
	}

	//调制波 = 电网电压前馈 + 控制器补偿
	g_wGridFBLoopOUT = g_wGridCurrLoopOUT + swGetAdcGridVoltReal();

	// 占空比计算
//	wCtrlLoopOutPwm = (INT16S)(((INT32S)g_wInvCtrlLoopOut * g_wKpwm) >> 12);		// 离网，用调制比还原占空比  3250 × 1000 >> 12 = 793
	wCtrlLoopOutPwm = (INT16S)(((INT32S)g_wGridFBLoopOUT * g_wPwmPeriod) >> 14);	// 并网，用周期值还原占空比  3250 × 3125 >> 14 = 619

/*	
//以下是管子发波部分(考虑一下做成函数形式)
	// 限制占空比不超过最大值-1
	if(wCtrlLoopOutPwm > (g_wPwmPeriod - 1))
	{
		wCtrlLoopOutPwm = g_wPwmPeriod - 1;
	}
	if(wCtrlLoopOutPwm < -(g_wPwmPeriod -1))
	{
		wCtrlLoopOutPwm = -(g_wPwmPeriod -1);
	}

	// 正负半周发波
	if(wCtrlLoopOutPwm > 0 || (g_wR_PWMDirectionPre == 0 && wCtrlLoopOutPwm == 0))	  
	{
		g_wInvPWM = wCtrlLoopOutPwm;// + 75;
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
		g_wInvPWM = -wCtrlLoopOutPwm;
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
*/
}

//////////////////////////////////////////////////////////////////////////////////并网 BUS电压外环 PI
INT16S	g_wLoopCnt = 0;
INT32S	g_dwPBusVoltSum = 0;
INT16S	g_wPBusVoltAvg = 0;
F32	g_wPBusVoltErr = 0;
F32	g_wBusVoltErr = 0;

F32	fBus_P = 0;
F32	fBus_I = 0;
F32	fBusVmo = 0;				// BUS PI控制器输出
F32	fDCDCBusKpFast = 1.5;		// 快速调节的KP系数(在BUS超Ref太大的时候用)
F32	fDCDCBusKiFast = 0.015;		// 快速调节的KI系数(在BUS超Ref太大的时候用)
F32	fDCDCBusKpSlow = 0.05;		// 初始的KP系数
F32	fDCDCBusKiSlow = 0.0005;	// 初始的KI系数
F32	fBUSVKp = 0.05;				// KP系数
F32	fBUSVKi = 0.0005;			// KI系数
F32	fPDCDCImo = 0;				// BUS电压外环输出
void	sFBBUSController2Init(void)	// 并网BUS电压外环初始化函数
{
	g_wLoopCnt = 0;
	g_dwPBusVoltSum = 0;	// BUS电压累加和
	g_wPBusVoltAvg = 0;
	g_wPBusVoltErr = 0;
	g_wBusVoltErr = 0;

	fBus_P = 0;
	fBus_I = 0;
	fBusVmo = 0;
	fPDCDCImo = 0;
}

void	sFBBUSController2(void)// 并网BUS电压外环
{
	g_dwPBusVoltSum += swGetAdcBusVoltReal();
	
	if(++g_wLoopCnt >= 8)
	{
		// BUS电压均值滤波后的值
		g_wLoopCnt = 0;
		g_wPBusVoltAvg = g_dwPBusVoltSum >> 3;
		g_dwPBusVoltSum = 0;

		// 误差值
		g_wPBusVoltErr = g_wInvFeedBusVoltRef - g_wPBusVoltAvg;
		g_wBusVoltErr = g_wPBusVoltErr;
		if(g_wBusVoltErr > cBusVoltReal80V)			// 20V
		{
			g_wBusVoltErr = cBusVoltReal80V;
		}
		else if(g_wBusVoltErr < -cBusVoltReal80V)
		{
			g_wBusVoltErr = -cBusVoltReal80V;
		}
		
		// Bus voltage loop PI controler
		fBus_P = g_wBusVoltErr * fBUSVKp;									// 计算KP参数
		fBus_I += g_wBusVoltErr * fBUSVKi;									// 计算KI参数
		UpDownLimit(fBus_I,gi_wInvChgCurrLimit,-gi_wInvFeedCurrLimit);		// KI限幅
		fBusVmo = fBus_P + fBus_I;											// PI环路输出
		UpDownLimit(fBusVmo,gi_wInvChgCurrLimit,-gi_wInvFeedCurrLimit);		// PI输出限幅(实际控制电流最大值)

		fPDCDCImo = fBusVmo;												// 外环输出，限制在系统额定最大充放电电流
//		if(g_wInvFeedBusVoltRef > 5300)		// for test BatVolt * 18 
//		{
//			fPDCDCImo -= 100;
//		}
//		UpDownLimit(fPDCDCImo,uwGetInvFreeCntlCurrMax()/10,-uwGetInvFreeCntlCurrMax()/10);	// 0.1A
		UpDownLimit(fPDCDCImo,cMaxInvFeedCntlCurr1,-cMaxInvFeedCntlCurr1);	// 0.1A
//		UpDownLimit(fPDCDCImo,cMaxInvFeedCntlCurr,-cMaxInvFeedCntlCurr);	// 0.01A
	}

}


//////////////////////////////////////////////////////////////////////////////////并网 逆变电流内环 PR
F32 fDisChgCurrSamp = 0;		// 电流采样值
F32 fDisChgCurrRef = 0;			// 内环参考
F32 fDisChgPwm = 0;

// PR1 基波
F32 fDisChgCurrLoopErr0 = 0;
F32 fDisChgCurrLoopErr1 = 0;
F32 fDisChgCurrLoopErr2 = 0;
F32 fDisChgCurrLoopOut0 = 0;	// PR输出
F32 fDisChgCurrLoopOut1 = 0;
F32 fDisChgCurrLoopOut2 = 0;
// 50hz Kp=2.5, Kr=280, Wc=2×3.14×5=31.4, Wo=2×3.14×50=314	Ts=19.2k
F32	fKcd1 = 1.9965f;
F32	fKcd2 = 0.9967f;
F32	fKcn0 = 2.9571f;
F32	fKcn1 = 4.9912f;
F32	fKcn2 = 2.0347f;

// PR2 三次谐波
F32 fDisChgCurrLoop2Err0 = 0;
F32 fDisChgCurrLoop2Err1 = 0;
F32 fDisChgCurrLoop2Err2 = 0;
F32 fDisChgCurrLoop2Out0 = 0;	// PR输出
F32 fDisChgCurrLoop2Out1 = 0;
F32 fDisChgCurrLoop2Out2 = 0;

// 150hz Kp=2.5, Kr=280, Wc=2×3.14×5=31.4, Wo=2×3.14×150=942	Ts=19.2k
//F32	fKc2d1 = 1.9943f;
//F32	fKc2d2 = 0.9967f;
//F32	fKc2n0 = 2.9569f;
//F32	fKc2n1 = 4.9858f;
//F32	fKc2n2 = 2.0349f;

// 150hz Kp=2.5, Kr=280, Wc=2×3.14×1=6.28, Wo=2×3.14×150=942	Ts=19.2k
F32	fKc2d1 = 1.9969f;
F32	fKc2d2 = 0.9993f;
F32	fKc2n0 = 2.5915f;
F32	fKc2n1 = 4.9924f;
F32	fKc2n2 = 2.4069f;

// 市电电压前馈系数
F32	g_uwGridVoltFeedWard = 0.1;//0.2;

// 孤岛
extern INT16S gi_wIslandDetectStep;		// 并网控制器用
extern INT16S gi_wSinePointMax;
extern INT16S gi_wSinePointThreeSix;

extern INT16S g_wRSinPointerwThetaTemp;
extern INT16S g_wRFixCapaReactivePower;

INT16S	g_wRSinPointerTemp2 = 0;

void	sFBINVController2Init(void)
{
	fDisChgCurrSamp = 0;
	fDisChgCurrLoopErr0 = 0;
	fDisChgCurrLoopErr1 = 0;
	fDisChgCurrLoopErr2 = 0;
	fDisChgCurrLoopOut0 = 0;
	fDisChgCurrLoopOut1 = 0;
	fDisChgCurrLoopOut2 = 0;
	fDisChgCurrRef = 0;			// 内环参考
	fDisChgPwm = 0;

	fDisChgCurrLoop2Err0 = 0;
	fDisChgCurrLoop2Err1 = 0;
	fDisChgCurrLoop2Err2 = 0;
	fDisChgCurrLoop2Out0 = 0;
	fDisChgCurrLoop2Out1 = 0;
	fDisChgCurrLoop2Out2 = 0;
}

void	sFBINVControl50hzParaInit(void)
{
	// 50hz Kp=2.5, Kr=280, Wc=2×3.14×5=31.4, Wo=2×3.14×50=314	Ts=19.2k
//	fKcd1 = 1.9965f;	// 1 旧款机器
//	fKcd2 = 0.9967f;
//	fKcn0 = 2.9571f;
//	fKcn1 = 4.9912f;
//	fKcn2 = 2.0347f;

	// fKcd1 = 1.9965f;	// 2 上周验证有效
	// fKcd2 = 0.9967f;
	// fKcn0 = 3.9796f;
	// fKcn1 = 5.9894f;
	// fKcn2 = 2.0106f;

//	fKcd1 = 1.9965f;	// 3 使用2的参数降级使用，可以正常并网
//	fKcd2 = 0.9967f;
//	fKcn0 = 3.3163f;
//	fKcn1 = 4.9912f;
//	fKcn2 = 1.6755f;

// 50hz Kp=4, Kr=800, Wc=2×3.14×5=31.4, Wo=2×3.14×50=314	Ts=19.2k
	fKcd1 = 1.9965f;	// 2 上周验证有效
	fKcd2 = 0.9967f;
	fKcn0 = 5.3061f;
	fKcn1 = 7.9859f;
	fKcn2 = 2.6808f;

	// 150hz Kp=2.5, Kr=280, Wc=2×3.14×1=6.28, Wo=2×3.14×150=942	Ts=19.2k
	fKc2d1 = 1.9969f;
	fKc2d2 = 0.9993f;
	fKc2n0 = 2.5915f;
	fKc2n1 = 4.9924f;
	fKc2n2 = 2.4069f;

	// 150hz Kp=4, Kr=800, Wc=2×3.14×1=6.28, Wo=2×3.14×150=942	Ts=19.2k
//	fKc2d1 = 1.9969f;
//	fKc2d2 = 0.9993f;
//	fKc2n0 = 4.2614f;
//	fKc2n1 = 7.9878f;
//	fKc2n2 = 3.7356f;
}

void	sFBINVControl60hzParaInit(void)
{
	// 60hz Kp=2.5, Kr=280, Wc=2×3.14×5=31.4, Wo=2×3.14×60=376.8	Ts=19.2k
	fKcd1 = 1.9964f;
	fKcd2 = 0.9967f;
	fKcn0 = 2.9571f;
	fKcn1 = 4.9909f;
	fKcn2 = 2.0347f;

	// 180hz Kp=2.5, Kr=280, Wc=2×3.14×1=6.28, Wo=2×3.14×180=1,130.4	Ts=19.2k
	fKc2d1 = 1.9959f;
	fKc2d2 = 0.9993f;
	fKc2n0 = 2.5915f;
	fKc2n1 = 4.9897f;
	fKc2n2 = 2.4069f;
}

void	sFBINVController2(void)
{
	//if(gi_wIslandDetectStep)
	if(0)	// 孤岛不生效
	{
		if(g_wRSinPointerwThetaTemp < gi_wSinePointThreeSix)
		{
			g_wRSinPointerTemp2 = (INT16S)((INT32S)g_wRSinPointerwThetaTemp * (gi_wIslandDetectStep + 50) / 50);
			if(g_wRSinPointerTemp2 > gi_wSinePointThreeSix)
			{
				g_wRSinPointerTemp2 = gi_wSinePointThreeSix;
			}
		}
		else
		{
			g_wRSinPointerTemp2 = (INT16S)(((INT32S)g_wRSinPointerwThetaTemp - gi_wSinePointThreeSix) * \
									(gi_wIslandDetectStep + 50) / 50) + gi_wSinePointThreeSix;
			if(g_wRSinPointerTemp2 > (gi_wSinePointMax - 1))
			{
				g_wRSinPointerTemp2 = (gi_wSinePointMax - 1);
			}
		}	
	}
	else
	{
		g_wRSinPointerTemp2 = g_wRSinPointerwThetaTemp;				// 市电相位
	}

	fDisChgCurrSamp = (F32)(-swGetAdcInvCurrReal()/10);		// 实际采样数据  		// 0.1A 采样改成了0.01A 改成0.01后并网失败，初始电流太大
	
	//fDisChgCurrRef = (F32)((INT16S)((INT32S)g_wGridBusLoopOUT * pSinTab[g_wRSinPointerTemp2] >> 14));		// 电流正弦参考(BUS外环1)
	fDisChgCurrRef = (F32)((INT16S)((INT32S)fPDCDCImo * pSinTab[g_wRSinPointerTemp2] >> 14));				// 电流正弦参考(BUS外环2)
	//fDisChgCurrRef += (INT16S)(((INT32S)pCosTab[g_wRSinPointerTemp2] * g_wRFixCapaReactivePower) >> 14);	// 无功补偿
	sSetOscTestData1(fPDCDCImo);
	sSetOscTestData2(fDisChgCurrSamp);
	sSetOscTestData3(fDisChgCurrRef);

	// PR1 基波控制
	fDisChgCurrLoopErr2 = fDisChgCurrLoopErr1;
	fDisChgCurrLoopErr1 = fDisChgCurrLoopErr0;
	fDisChgCurrLoopOut2 = fDisChgCurrLoopOut1;
	fDisChgCurrLoopOut1 = fDisChgCurrLoopOut0;
	fDisChgCurrLoopErr0 = fDisChgCurrRef - fDisChgCurrSamp;	// 内环输入，参考与实际误差，需要加  限幅 = 3200W / 220.0V * 1.414 * 100 ≈ 2057
	sSetOscTestData4(fDisChgCurrLoopErr0);

	fDisChgCurrLoopOut0 = fDisChgCurrLoopOut1*fKcd1 - fDisChgCurrLoopOut2*fKcd2\
						+ fDisChgCurrLoopErr0*fKcn0 - fDisChgCurrLoopErr1*fKcn1\
						+ fDisChgCurrLoopErr2*fKcn2;
	UpDownLimit(fDisChgCurrLoopOut0,3850.0,-3850.0);
	sSetOscTestData5(fDisChgCurrLoopOut0);

	// PR2 3次谐波抑制
//	fDisChgCurrLoop2Err2 = fDisChgCurrLoop2Err1;
//	fDisChgCurrLoop2Err1 = fDisChgCurrLoop2Err0;
//	fDisChgCurrLoop2Out2 = fDisChgCurrLoop2Out1;
//	fDisChgCurrLoop2Out1 = fDisChgCurrLoop2Out0;
//	fDisChgCurrLoop2Err0 = fDisChgCurrRef - fDisChgCurrSamp;
//	fDisChgCurrLoop2Out0 = fDisChgCurrLoop2Out1*fKc2d1 - fDisChgCurrLoop2Out2*fKc2d2\
//							+ fDisChgCurrLoop2Err0*fKc2n0 - fDisChgCurrLoop2Err1*fKc2n1\
//							+ fDisChgCurrLoop2Err2*fKc2n2;
//	UpDownLimit(fDisChgCurrLoop2Out0,3100.0,-3100.0);

	// 占空比
//	fDisChgPwm = fDisChgCurrLoopOut0 + fDisChgCurrLoop2Out0 * g_uwGridVoltFeedWard; //\
				+ swGetAdcInvVoltReal() * g_uwGridVoltFeedWard;	// 叠加市电电压前馈系数

	fDisChgPwm = fDisChgCurrLoopOut0 + swGetAdcInvVoltReal() * g_uwGridVoltFeedWard;
	
	UpDownLimit(fDisChgPwm,3850.0,-3850.0);
	sSetOscTestData6(fDisChgPwm);
		
	if(fDisChgPwm < 0 || (g_wR_PWMDirectionPre == 0 && fDisChgPwm == 0))    
	{
		g_wInvPWM = (-fDisChgPwm);
		if(g_wInvPWM > (g_wPwmPeriod - 10))
		{
			g_wInvPWM = (g_wPwmPeriod - 10);
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
		{	//NU LOW, ND HIGH
			mEnForceNULow();			
		}
	}
	else
	{
		g_wInvPWM = fDisChgPwm;		
		if(g_wInvPWM > (g_wPwmPeriod - 10))
		{
			g_wInvPWM = (g_wPwmPeriod - 10);
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
		{	//NU HIGH, ND LOW
			mEnForceNUHigh();
		}
	}
	sSetOscTestData7(g_wInvPWM);
}


/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16S	swGetInvChgCurrLimit(void)				// 并网最大买电电流
{
	return gi_wInvChgCurrLimit;
}

INT16S	swGetInvFeedCurrLimit(void)				// 并网最大卖电电流
{
	return gi_wInvFeedCurrLimit;
}

INT16S	swGetInvFeedBusVoltRef(void)			// 并网BUS参考
{
	return g_wInvFeedBusVoltRef;
}

INT16S	swGetFBRFBVm_P(void)					// 并网控制器电压外环输出
{
	return g_wRFBVm_P;
}

INT16S swGetfPDCDCImo(void)
{
	return (INT16S)fPDCDCImo;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetInvChgCurrLimit(INT16S wValue)				// 并网最大买电电流
{
	gi_wInvChgCurrLimit = wValue;
}

void	sSetInvFeedCurrLimit(INT16S wValue)				// 并网最大卖电电流
{
	gi_wInvFeedCurrLimit = wValue;
}

void	sSetInvFeedBusVoltRef(INT16S wValue)			// 并网BUS参考
{
	g_wInvFeedBusVoltRef = wValue;
}



