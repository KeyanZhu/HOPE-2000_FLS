/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#define		__PV_CONTROL_C__

/********************************************************************************
* Include head files															*
********************************************************************************/
#include	"Main.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#pragma CODE_SECTION(sPV1Control,".TI.ramfunc");


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
INT16U	g_uwPV1CtrlSts = 0;

INT16S	g_wPVPwmPeriod = cPWM_DUTY_LIMIT_UP;
INT16U 	g_uwPv1DCDCCtrlSts = cDCDCWait;

INT16S	g_wLoop1Cnt = 0;			// 控制器执行延迟次数
INT32S	g_dwPv1BatVoltSum = 0;		// PV1控BUS电压累加和
INT32S	g_dwPv1VoltSum = 0;			// PV1控PV电压累加和
INT16S	g_wPv1BatVoltAvg = 0;		// PV1控BUS电压滤波值
INT16S	g_wPvVoltAvg = 0;			// PV1控PV电压滤波值
INT16S	g_wBatVoltErr1 = 0;
INT16S	g_wPv1VoltErr = 0;
INT16S	g_wPv1BatVoltErr = 0;
INT16S	g_wPPv1VoltErr = 0;

// Ctrl V
INT16S	g_wBatVKp1 = 30000;//4000;
INT16S	g_wBatVKi1 = 20;//2;
INT32S	g_dwBat_P = 0;
INT32S	g_dwBat_I = 0;
INT32S	g_dwBatVmo1 = 0;
INT16S	g_wPv1VKp = 30000;//4000;
INT16S	g_wPv1VKi = 20;//2;
INT32S	g_dwPv1_P = 0;
INT32S	g_dwPDCDCImo1 = 0;			// PV1电压环输出结果/电流环给定

// Ctrl I
INT16S	g_wPDCDCIErr1 = 0;
INT16S	g_wDCDCIKp1 = 120;//100;
INT16S	g_wDCDCIKi1 = 5;
INT32S	g_dwCurr1_P = 0;
INT32S 	g_dwCurr1_I = 0;
INT32S	g_dwCurr1Vmo = 0;			// PV1电流环输出
INT16S	g_wPv1PWM;					// PWM占空比

INT16S	g_wPvChgStatus = cPVDCM;					// PV充电状态

INT16S	g_wPvChgPWMDie = 40;					// 死区补偿


INT32S 	uwPvBatChgLimit = 50;		// PV充电控制器电流限制 5A
INT16S 	uwSciPvBatChgLimit  = 50;	// 调试寄存器写入的PV充电目标电流 5A
INT16S 	uwUserPvBatChgLimit = 50;	// 用户设置的充电电流(读EEPROM) 5A

INT16S 	g_wPvVoltRef = 4500;		// PV电压参考 45V
INT16S 	g_wPvChgBatVoltRef;			// PV充电电池电压参考 20V

extern INT16U	uwPvChgBatCurrRef;

INT16U	g_wPv1PWMA = 0;
INT16U	g_wPv1PWMB = 0;
INT16U	g_wPv1PWMupLimit = 0;
INT16U	g_wPv1PWMupLimit2 = 1200;

/********************************************************************************
* Internal routine prototypes													*
********************************************************************************/


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
void	sPvParaInit(void)
{

}

void	sClrPv1CtrlPara(void)
{
	g_dwPv1BatVoltSum = 0;
	g_dwPv1VoltSum = 0;
	g_wLoop1Cnt = 0;
	g_dwBat_I = 0;
	g_dwCurr1_I = 0;
	g_dwBatVmo1 = 0;
	g_dwCurr1Vmo = 0;
	g_wPv1PWM = 0;
	g_dwPDCDCImo1 = 0;
	uwPvBatChgLimit = 0;
//	g_wPvChgBatVoltRef = uwGetPvChgBatVoltRef();	// for test
}

void	sPV1Control(void)
{
	g_dwPv1BatVoltSum += swGetAdcBatVoltReal();
	g_dwPv1VoltSum += swGetAdcPv1VoltReal();

	// Load任务里面做MPPT点追踪
	// 如果是双通道并联的时候,用同一路做基准
	g_wPvVoltRef = suwGetMpptVoltRef();	// MPPT扰动给出的PV外环参考电压

//	if(suwGetSysPvChgEn() == true)
//	{
		if(uwPvBatChgLimit < uwPvChgBatCurrRef)
		{
			uwPvBatChgLimit++;
		}
		else
		{
			uwPvBatChgLimit = uwPvChgBatCurrRef;
		}
//	}
//	else
//	{
//		uwPvBatChgLimit = cMpptBatCurr02A;				// Reserve 2A to avoid detect error
//	}
	if(swGetWorkMode() == cToBatteryMode)				// 逆变软起时，充电电流限制到5A,防止触发电池过压
	{
		Uplimit(uwPvBatChgLimit,cMpptBatCurr05A);
	}

	
	if(++g_wLoop1Cnt >= 8)								// 电压外环8个中断周期运行一次
	{
		g_wLoop1Cnt = 0;
		g_wPv1BatVoltAvg = g_dwPv1BatVoltSum >> 3;
		g_wPvVoltAvg = g_dwPv1VoltSum >> 3;
		g_dwPv1BatVoltSum = 0;
		g_dwPv1VoltSum = 0;

		g_wBatVoltErr1 = (INT16S)g_wPvChgBatVoltRef - g_wPv1BatVoltAvg;	// BAT电压实际值与目标值的误差
		g_wPv1VoltErr = g_wPvVoltAvg - g_wPvVoltRef;	// PV1电压实际值与目标值的误差

		if(g_uwPv1DCDCCtrlSts == cDCDCSoft)				// 控制器软起(不做这个状态)
		{
			g_wPv1BatVoltErr = g_wBatVoltErr1;
			g_wPPv1VoltErr = g_wPv1VoltErr;
			if(g_wPv1BatVoltErr < 0)
			{
				g_uwPv1DCDCCtrlSts = cDCDCWork;
			}
			else
			{
			
				g_wPv1BatVoltErr = 1;
			}
		}
		else
		{
			g_wPv1BatVoltErr = g_wBatVoltErr1;			// Work模式的时候误差值直接更新给控制器
			g_wPPv1VoltErr = g_wPv1VoltErr;
		}

//		if(g_wBatVoltErr1 <= 0) // Bat voltage loop PI controler (电池满，调稳电池电压)
		if(1)	// for test 调试用，不去运行PV扰动控制环路
		{
			sSetPvMpptPause(true);	// 稳压模式时，不运行MPPT扰动
			
			if(g_wPv1BatVoltErr > 500)	// 5V
			{
				g_wPv1BatVoltErr = 500;
			}
			else if(g_wPv1BatVoltErr < -500)
			{
				g_wPv1BatVoltErr = -500;
			}

			g_dwBat_P = ((INT32S)g_wPv1BatVoltErr * g_wBatVKp1) >> 8;			// 电池电压外环KP
			g_dwBat_I =  g_dwBat_I + ((INT32S)g_wPv1BatVoltErr * g_wBatVKi1);	// 电池电压外环KI
			if(g_dwBat_I > (uwPvBatChgLimit << 8))								// 电池电压外环积分限幅
			{
				g_dwBat_I = (uwPvBatChgLimit << 8);
			}
			else if(g_dwBat_I < 0)
			{
				g_dwBat_I = 0;
			}
			g_dwBatVmo1 = g_dwBat_P + (g_dwBat_I >> 8);							// 电池电压外环输出
		}
		else	// PV voltage loop PI controler	(电池未满，调PV电压追踪最大功率点)
		{
			sSetPvMpptPause(false);	// PV追踪模式时，运行MPPT扰动
			
			if(g_wPPv1VoltErr > 1000)	// 10V
			{
				g_wPPv1VoltErr = 1000;
			}
			else if(g_wPPv1VoltErr < -1000)
			{
				g_wPPv1VoltErr = -1000;
			}

			g_dwPv1_P = ((INT32S)g_wPPv1VoltErr * g_wPv1VKp) >> 8;				// PV电压外环KP
			g_dwBat_I =  g_dwBat_I + ((INT32S)g_wPPv1VoltErr * g_wPv1VKi);		// PV电压外环KI
			if(g_dwBat_I > (uwPvBatChgLimit << 8))								// PV电压外环积分限幅
			{
				g_dwBat_I = (uwPvBatChgLimit << 8);
			}
			else if(g_dwBat_I < 0)
			{
				g_dwBat_I = 0;
			}
			g_dwBatVmo1 = g_dwPv1_P + (g_dwBat_I >> 8);							// PV电压外环输出
		}

		if(g_dwBatVmo1 > uwPvBatChgLimit)										// 用户设置的最大充电电流
		{
			g_dwBatVmo1 = uwPvBatChgLimit;
		}
		else if(g_dwBatVmo1 < 0)
		{
			g_dwBatVmo1 = 0;
		}
		
		g_dwPDCDCImo1 = g_dwBatVmo1;											// 电压外环输出(电流内环给定)
		if(g_dwPDCDCImo1 > cMaxPVBatChgCurr)									// 系统最大允许PV最大的充电电流
		{
			g_dwPDCDCImo1 = cMaxPVBatChgCurr;
		}
		else if(g_dwPDCDCImo1 < 0)
		{
			g_dwPDCDCImo1 = 0;
		}
	}
			
	// 电流内环，每个中断周期运行一次
	// BUCK Curr loop PI controler										// 电池电流内环
	g_wPDCDCIErr1 = g_dwPDCDCImo1 - swGetAdcPvInCurrReal();				// PV负端电流
	if(g_wPDCDCIErr1 > 3000)											// 环路单次调节误差步进限制5A
	{
		g_wPDCDCIErr1 = 3000;
	}
	if(g_wPDCDCIErr1 < -3000)
	{
		g_wPDCDCIErr1 = -3000;
	}

	g_dwCurr1_P = ((INT32S)g_wPDCDCIErr1 * g_wDCDCIKp1) >> 12;			// 电流环KP
	g_dwCurr1_I = g_dwCurr1_I + ((INT32S)g_wPDCDCIErr1 * g_wDCDCIKi1);	// 电流环KI
	if(g_dwCurr1_I > 67108864)											// 积分限幅,67108864 = (16384 << 12)
	{
		g_dwCurr1_I = 67108864;
	}
	else if(g_dwCurr1_I < 0)											// 2457600  = (600 << 12)
	{
		g_dwCurr1_I = 0;
	}
	g_dwCurr1Vmo = g_dwCurr1_P + (g_dwCurr1_I >> 12);					// 电流环输出
	if(g_dwCurr1Vmo > 16384)											// 电流环输出限幅
	{
		g_dwCurr1Vmo = 16384;
	}
	else if(g_dwCurr1Vmo < 0)
	{
		g_dwCurr1Vmo = 0;
	}

	// 还原占空比，更新PWM寄存器值
	g_wPv1PWM = (INT16S)(((INT32S)g_wPVPwmPeriod * g_dwCurr1Vmo) >> 14);// max 1140 0.95
	if(g_wPv1PWM > (cBuckPeriod >> 1))	// 限制了占空比不能超过百分之五十，可能是个风险点，特别是PV低压时
	{
		g_wPv1PWM = (cBuckPeriod >> 1);
	}
	else if(g_wPv1PWM < 0)
	{
		g_wPv1PWM = 0;
	}

	// 在电池端电压冲高到一定值时，直接把积分和占空比清零，不靠环路自己调下来，靠环路目前动态不够
	if(g_wPv1BatVoltAvg > (g_wPvChgBatVoltRef + 20))		//0.2V
	{
		g_dwBat_I = 0;
		g_wPv1PWM = 0;
	}

	// PV充电状态识别
	if(swGetPv1BatCurrNew() >= cMpptBatCurr20A)	// 考虑增加计数滤波
	{
		g_wPvChgStatus = cPVCCM;
	}
	else
	{
		g_wPvChgStatus = cPVDCM;
	}

	if(g_wPv1PWM <= cBuckPeriod)
	{
		if(g_wPvChgStatus == cPVDCM)	// DCM
		{
			if(g_wPv1PWM > (cBuckPeriod >> 1))	// 不要让占空比超过百分之五十
			{
				g_wPv1PWM = (cBuckPeriod >> 1);
			}
		
			g_wPv1PWMA = cBuckPeriod - g_wPv1PWM;
			g_wPv1PWMB = g_wPv1PWM;

			//下管占空比限制 = Ton * (Uin - Uo) / Uo
			g_wPv1PWMupLimit = (INT32S)g_wPv1PWM * (swGetAdcPv1VoltReal() - swGetAdcBatVoltReal()) \
									/ swGetAdcPv1VoltReal();	// 注意一下采样值是否属于同一个数量级
			if(g_wPv1PWMB > g_wPv1PWMupLimit)
			{
				g_wPv1PWMB = g_wPv1PWMupLimit;
			}
			if(g_wPv1PWMB > (g_wPv1PWM - 30))
			{
				g_wPv1PWMB = (g_wPv1PWM - 30);
			}
		}
		else	// CCM
		{
			g_wPv1PWMA = cBuckPeriod - g_wPv1PWM;
			g_wPv1PWMB = cBuckPeriod - g_wPv1PWM;

			g_wPv1PWMupLimit = cBuckPeriod - g_wPv1PWM - g_wPvChgPWMDie;
			if(g_wPv1PWMB > g_wPv1PWMupLimit)
			{
				g_wPv1PWMB = g_wPv1PWMupLimit;
			}
			if(g_wPv1PWMB > g_wPv1PWMupLimit2)
			{
				g_wPv1PWMB = g_wPv1PWMupLimit2;
			}
		}
		// 发波
		mPV1BuckPWMA = g_wPv1PWMA;
		mPV1BuckPWMB = g_wPv1PWMB;
	}
}


void	sPV1OpenControl(void)
{
	if(g_wPv1PWM <= cBuckPeriod)
	{
//		if(g_wPv1PWM > (cBuckPeriod >> 1))	// 不要让占空比超过百分之五十
//		{
//			g_wPv1PWM = (cBuckPeriod >> 1);
//		}
	
		g_wPv1PWMA = cBuckPeriod - g_wPv1PWM;
		g_wPv1PWMB = cBuckPeriod - g_wPv1PWM;//g_wPv1PWM;

		//下管占空比限制 = Ton * (Uin - Uo) / Uo
//		g_wPv1PWMupLimit = g_wPv1PWM * (1200 - 330) / 1200;		// for test
//		g_wPv1PWMupLimit = g_wPv1PWM * (swGetAdcPv1VoltReal() - swGetAdcBatVoltReal()) / swGetAdcPv1VoltReal();	// 注意一下采样值是否属于同一个数量级
		g_wPv1PWMupLimit = cBuckPeriod - g_wPv1PWM - 40;
		if(g_wPv1PWMB > g_wPv1PWMupLimit)
		{
			g_wPv1PWMB = g_wPv1PWMupLimit;
		}
//		if(g_wPv1PWMB > g_wPv1PWMupLimit2)
//		{
//			g_wPv1PWMB = g_wPv1PWMupLimit2;
//		}

		// 发波
		mPV1BuckPWMA = g_wPv1PWMA;
		mPV1BuckPWMB = g_wPv1PWMB;

//		mPV1BuckPWMA = cBuckPeriod - g_wPv1PWM;	// 占空比由调试寄存器写入
//		mPV1BuckPWMB = cBuckPeriod - g_wPv1PWM;	// 占空比由调试寄存器写入
	}
}



/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INT16U	suwGetPV1CtrlSts(void)
{
	return g_uwPV1CtrlSts;
}

INT16U	suwGetPV1PWM(void)
{
	return g_wPv1PWM;
}

INT16U	suwGetPvChgBatVoltRef(void)				// PV充电电池电压参考
{
	return g_wPvChgBatVoltRef;
}

INT16U	suwGetPvBatChgLimit(void)				// PV控制器充电电流参考
{
	return uwPvBatChgLimit;
}

INT16U	suwGetSciPvBatChgLimit(void) 	  		// 调试寄存器写入的PV充电目标电流
{
	return uwSciPvBatChgLimit;
}

INT16U	suwGetUserPvBatChgLimit(void) 	  		// 用户设置的充电电流
{
	return uwUserPvBatChgLimit;
}

INT16U	suwGetPvVoltRef(void) 	  				// PV电压参考 80V
{
	return g_wPvVoltRef;
}

INT16U	suwGetBatVKp1(void)
{
	return g_wBatVKp1;
}

INT16U	suwGetBatVKi1(void)
{
	return g_wBatVKi1;
}

INT16U	suwGetPv1VKp(void)
{
	return g_wPv1VKp;
}

INT16U	suwGetPv1VKi(void)
{
	return g_wPv1VKi;
}

INT16U	suwGetDCDCIKp1(void)
{
	return g_wDCDCIKp1;
}

INT16U	suwGetDCDCIKi1(void)
{
	return g_wDCDCIKi1;
}

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
void	sSetPV1CtrlStsIsr(INT16U uwPV1CtrlSts)
{
	if(uwPV1CtrlSts == cDCDCWait)
	{
		sClrPv1CtrlPara();
//		hoPVRLYOff;
	}
	else if(uwPV1CtrlSts == cDCDCWork)
	{
//		hoPVRLYOn;
	}
	g_uwPV1CtrlSts = uwPV1CtrlSts;
}

void	sSetPV1CtrlSts(INT16U uwPV1CtrlSts)				// 控制器状态设置
{
	OS_ENTER_CRITICAL();
	sSetPV1CtrlStsIsr(uwPV1CtrlSts);
	OS_EXIT_CRITICAL();
}

void	sSetPv1PWM(INT16U uwTemp)						// PV BUCK 实际发波占空比
{
	OS_ENTER_CRITICAL();
	g_wPv1PWM = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetPvChgBatVoltRef(INT16U uwTemp)				// PV充电电池电压参考
{
	OS_ENTER_CRITICAL();
	g_wPvChgBatVoltRef = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetSciPvBatChgLimit(INT16U uwTemp)				// 调试寄存器写入的PV充电目标电流
{
	OS_ENTER_CRITICAL();
	uwSciPvBatChgLimit = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetUserPvBatChgLimit(INT16U uwTemp)			// 用户设置的充电电流
{
	OS_ENTER_CRITICAL();
	uwUserPvBatChgLimit = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetPvVoltRef(INT16U uwTemp)					// PV电压参考 80V
{
	OS_ENTER_CRITICAL();
	g_wPvVoltRef = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetBatVKp1(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wBatVKp1 = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetBatVKi1(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wBatVKi1 = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetPv1VKp(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wPv1VKp = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetPv1VKi(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wPv1VKi = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetDCDCIKp1(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wDCDCIKp1 = uwTemp;
	OS_EXIT_CRITICAL();
}

void	sSetDCDCIKi1(INT16U uwTemp)
{
	OS_ENTER_CRITICAL();
	g_wDCDCIKi1 = uwTemp;
	OS_EXIT_CRITICAL();
}



