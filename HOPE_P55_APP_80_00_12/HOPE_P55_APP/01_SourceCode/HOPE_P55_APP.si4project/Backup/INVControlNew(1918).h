/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __INV_CONTROLNEW_H__
#define __INV_CONTROLNEW_H__

/********************************************************************************
* Include head files															*
********************************************************************************/
//#include		"OS_CPU.h"

/********************************************************************************
* Macros 																		*
********************************************************************************/
#ifdef  __INV_CONTROLNEW_C__
#define INV_CONTROLNEW
#else
#define INV_CONTROLNEW  extern
#endif


/********************************************************************************
* Routines' implementations														*
********************************************************************************/
INV_CONTROLNEW	void	sInvVoltLoopCtrlInit(void);				// 离网逆变外环初始化
INV_CONTROLNEW	void	sInvVoltRmsLoopCtrl(void);				// 离网有效值外环
INV_CONTROLNEW	void	sInvVoltRealLoopCtrl(void);				// 离网瞬时逆变电压环	
INV_CONTROLNEW	void 	sInvCurrRealLoopCtrl(void);				// 离网瞬时电流内环

INV_CONTROLNEW	void	sGridBusLoopCtrl(void);					// 并网BUS电压外环
INV_CONTROLNEW	void	sGridPowerLoopCtrl(void);				// 并网功率外环			for test 未验证但预期存在设计问题
INV_CONTROLNEW	void	sGridFBLoopCtrl(void);					// 并网电流内环			for test 未验证但预期存在设计问题

INV_CONTROLNEW	void	sFBINVController2Init(void);			// 并网电流内环初始化函数
INV_CONTROLNEW	void	sFBINVController2(void);				// 并网电流内环

INV_CONTROLNEW	void	sFBBUSController2Init(void);			// 并网BUS电压外环初始化函数
INV_CONTROLNEW	void	sFBBUSController2(void);				// 并网BUS电压外环
INV_CONTROLNEW	void	sFBINVControl50hzParaInit(void);
INV_CONTROLNEW	void	sFBINVControl60hzParaInit(void);

/********************************************************************************
* Output interface Routines														*
********************************************************************************/
INV_CONTROLNEW INT16S	swGetInvChgCurrLimit(void);				// 并网最大买电电流
INV_CONTROLNEW INT16S	swGetInvFeedCurrLimit(void);			// 并网最大卖电电流
INV_CONTROLNEW INT16S	swGetInvFeedBusVoltRef(void);	 		// 并网BUS参考电压
INV_CONTROLNEW INT16S	swGetFBRFBVm_P(void);					// 并网控制器电压外环输出

INV_CONTROLNEW INT16S 	swGetfPDCDCImo(void);

/********************************************************************************
* Input interface Routines														*
********************************************************************************/
INV_CONTROLNEW void		sSetInvChgCurrLimit(INT16S wValue);				// 并网最大买电电流
INV_CONTROLNEW void		sSetInvFeedCurrLimit(INT16S wValue);			// 并网最大卖电电流
INV_CONTROLNEW void		sSetInvFeedBusVoltRef(INT16S wValue);			// 并网BUS参考电压


#endif	// __INV_CONTROL_H__

