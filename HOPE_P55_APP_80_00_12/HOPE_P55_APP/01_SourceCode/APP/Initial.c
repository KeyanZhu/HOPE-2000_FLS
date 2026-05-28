/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#include "Main.h"

/****************************************************************************
Constant definition
*****************************************************************************/
// Configure the period for each timer
#define cPWM1_TIMER_TBPRD   2600
#define cPWM2_TIMER_TBPRD   0x1FFF
#define cPWM3_TIMER_TBPRD   49999
#define cPWM4_TIMER_TBPRD   0x1FFF
#define cPWM5_TIMER_TBPRD   49999
#define cPWM6_TIMER_TBPRD   0x1FFF

// 1 = enabled,  0 = disabled
#define cPWM1_INT_ENABLE  1
#define cPWM2_INT_ENABLE  1
#define cPWM3_INT_ENABLE  1
#define cPWM4_INT_ENABLE  1
#define cPWM5_INT_ENABLE  1
#define cPWM6_INT_ENABLE  1

const struct PIE_VECT_TABLE PieVectTableInit = 
{
	PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    PIE_RESERVED_ISR,		   // Reserved
    
    TIMER1_ISR,                // CPU Timer 1 Interrupt
    TIMER2_ISR,                // CPU Timer 2 Interrupt
    DATALOG_ISR,               // Datalogging Interrupt
    RTOS_ISR,                  // RTOS Interrupt from ERAD
    EMU_ISR,                   // Emulation Interrupt
    NMI_ISR,                   // Non-Maskable Interrupt
    ILLEGAL_ISR,               // Illegal Operation Trap
    USER1_ISR,                 // User Defined Trap 1
    USER2_ISR,                 // User Defined Trap 2
    USER3_ISR,                 // User Defined Trap 3
    USER4_ISR,                 // User Defined Trap 4
    USER5_ISR,                 // User Defined Trap 5
    USER6_ISR,                 // User Defined Trap 6
    USER7_ISR,                 // User Defined Trap 7
    USER8_ISR,                 // User Defined Trap 8
    USER9_ISR,                 // User Defined Trap 9
    USER10_ISR,                // User Defined Trap 10
    USER11_ISR,                // User Defined Trap 11
    USER12_ISR,                // User Defined Trap 12
    
    ADCA1_ISR,                 // 1.1 - ADCA Interrupt 1
    ADCB1_ISR,                 // 1.2 - ADCB Interrupt 1
    ADCC1_ISR,                 // 1.3 - ADCC Interrupt 1
    XINT1_ISR,                 // 1.4 - XINT1 Interrupt
    XINT2_ISR,                 // 1.5 - XINT2 Interrupt
    SYS_ERR_ISR,               // 1.6 - SYS_ERR Interrupt
    TIMER0_ISR,                // 1.7 - Timer 0 Interrupt
    WAKE_ISR,                  // 1.8 - Standby and Halt Wakeup Interrupt
    
    EPWM1_TZ_ISR,              // 2.1 - ePWM1 Trip Zone Interrupt
    EPWM2_TZ_ISR,              // 2.2 - ePWM2 Trip Zone Interrupt
    EPWM3_TZ_ISR,              // 2.3 - ePWM3 Trip Zone Interrupt
    EPWM4_TZ_ISR,              // 2.4 - ePWM4 Trip Zone Interrupt
    EPWM5_TZ_ISR,              // 2.5 - ePWM5 Trip Zone Interrupt
    EPWM6_TZ_ISR,              // 2.6 - ePWM6 Trip Zone Interrupt
    EPWM7_TZ_ISR,              // 2.7 - ePWM7 Trip Zone Interrupt
    EPWM8_TZ_ISR,              // 2.8 - ePWM8 Trip Zone Interrupt
    
    EPWM1_ISR,                 // 3.1 - ePWM1 Interrupt
    EPWM2_ISR,                 // 3.2 - ePWM2 Interrupt
    EPWM3_ISR,                 // 3.3 - ePWM3 Interrupt
    EPWM4_ISR,                 // 3.4 - ePWM4 Interrupt
    EPWM5_ISR,                 // 3.5 - ePWM5 Interrupt
    EPWM6_ISR,                 // 3.6 - ePWM6 Interrupt
    EPWM7_ISR,                 // 3.7 - ePWM7 Interrupt
    EPWM8_ISR,                 // 3.8 - ePWM8 Interrupt
    
    ECAP1_ISR,                 // 4.1 - eCAP1 Interrupt
    ECAP2_ISR,                 // 4.2 - eCAP2 Interrupt
    PIE_RESERVED_ISR,          // 4.3 - Reserved
    PIE_RESERVED_ISR,          // 4.4 - Reserved
    PIE_RESERVED_ISR,          // 4.5 - Reserved
    PIE_RESERVED_ISR,          // 4.6 - Reserved
    PIE_RESERVED_ISR,          // 4.7 - Reserved
    PIE_RESERVED_ISR,          // 4.8 - Reserved
    
    EQEP1_ISR,                 // 5.1 - eQEP1 Interrupt
    EQEP2_ISR,                 // 5.2 - eQEP2 Interrupt
    EQEP3_ISR,                 // 5.3 - eQEP3 Interrupt
    PIE_RESERVED_ISR,          // 5.4 - Reserved
    CLB1_ISR,                  // 5.5 - CLB1 (Reconfigurable Logic) Interrupt
    CLB2_ISR,                  // 5.6 - CLB2 (Reconfigurable Logic) Interrupt
    PIE_RESERVED_ISR,          // 5.7 - Reserved
    PIE_RESERVED_ISR,          // 5.8 - Reserved
    
    SPIA_RX_ISR,               // 6.1 - SPIA Receive Interrupt
    SPIA_TX_ISR,               // 6.2 - SPIA Transmit Interrupt
    SPIB_RX_ISR,               // 6.3 - SPIB Receive Interrupt
    SPIB_TX_ISR,               // 6.4 - SPIB Transmit Interrupt
    PIE_RESERVED_ISR,          // 6.5 - Reserved
    PIE_RESERVED_ISR,          // 6.6 - Reserved
    DCC0_ISR,                  // 6.7 - DCC0 Interrupt
    DCC1_ISR,                  // 6.8 - DCC1 Interrupt
    
    DMA_CH1_ISR,               // 7.1 - DMA Channel 1 Interrupt
    DMA_CH2_ISR,               // 7.2 - DMA Channel 2 Interrupt
    DMA_CH3_ISR,               // 7.3 - DMA Channel 3 Interrupt
    DMA_CH4_ISR,               // 7.4 - DMA Channel 4 Interrupt
    DMA_CH5_ISR,               // 7.5 - DMA Channel 5 Interrupt
    DMA_CH6_ISR,               // 7.6 - DMA Channel 6 Interrupt
    PMBUSA_ISR,                // 7.7 - PMBUSA Interrupt
    PIE_RESERVED_ISR,          // 7.8 - Reserved
    
    I2CA_ISR,                  // 8.1 - I2CA Interrupt 1
    I2CA_FIFO_ISR,             // 8.2 - I2CA Interrupt 2
    I2CB_ISR,                  // 8.3 - I2CB Interrupt 1
    I2CB_FIFO_ISR,             // 8.4 - I2CB Interrupt 2
    SCIC_RX_ISR,               // 8.5 - SCIC Receive Interrupt
    SCIC_TX_ISR,               // 8.6 - SCIC Transmit Interrupt
    PIE_RESERVED_ISR,          // 8.7 - Reserved
    PIE_RESERVED_ISR,          // 8.8 - Reserved
    
    SCIA_RX_ISR,               // 9.1 - SCIA Receive Interrupt
    SCIA_TX_ISR,               // 9.2 - SCIA Transmit Interrupt
    SCIB_RX_ISR,               // 9.3 - SCIB Receive Interrupt
    SCIB_TX_ISR,               // 9.4 - SCIB Transmit Interrupt
    PIE_RESERVED_ISR,          // 9.5 - Reserved
    PIE_RESERVED_ISR,          // 9.6 - Reserved
    MCANA_0_ISR,               // 9.7 - MCANSSA0
    MCANA_1_ISR,               // 9.8 - MCANSSA1
    
    ADCA_EVT_ISR,              // 10.1 - ADCA Event Interrupt
    ADCA2_ISR,                 // 10.2 - ADCA Interrupt 2
    ADCA3_ISR,                 // 10.3 - ADCA Interrupt 3
    ADCA4_ISR,                 // 10.4 - ADCA Interrupt 4
    ADCB_EVT_ISR,              // 10.5 - ADCB Event Interrupt
    ADCB2_ISR,                 // 10.6 - ADCB Interrupt 2
    ADCB3_ISR,                 // 10.7 - ADCB Interrupt 3
    ADCB4_ISR,                 // 10.8 - ADCB Interrupt 4
    
    CLA1_1_ISR,                // 11.1 - CLA1 Interrupt 1
    CLA1_2_ISR,                // 11.2 - CLA1 Interrupt 2
    CLA1_3_ISR,                // 11.3 - CLA1 Interrupt 3
    CLA1_4_ISR,                // 11.4 - CLA1 Interrupt 4
    CLA1_5_ISR,                // 11.5 - CLA1 Interrupt 5
    CLA1_6_ISR,                // 11.6 - CLA1 Interrupt 6
    CLA1_7_ISR,                // 11.7 - CLA1 Interrupt 7
    CLA1_8_ISR,                // 11.8 - CLA1 Interrupt 8
    
    XINT3_ISR,                 // 12.1 - XINT3 Interrupt
    XINT4_ISR,                 // 12.2 - XINT4 Interrupt
    XINT5_ISR,                 // 12.3 - XINT5 Interrupt
    PIE_RESERVED_ISR,          // 12.4 - Reserved
    FLSS_ISR,                  // 12.5 - Interrupt from flash sub-system
    VCU_ISR,                   // 12.6 - VCU Interrupt (VCRC)
    MCANA_ECC_ISR,             // 12.7 - MCANSSA_ECC_CORR_PLS
    MCANA_WAKE_ISR,            // 12.8 - MCANSSA_WAKE_AND_TS_PLS
    
    ADCD1_ISR,                 // 1.9 - ADCD Interrupt 1
    ADCE1_ISR,                 // 1.10 - ADCE Interrupt 1
    PIE_RESERVED_ISR,          // 1.11 - Reserved
    PIE_RESERVED_ISR,          // 1.12 - Reserved
    PIE_RESERVED_ISR,          // 1.13 - Reserved
    PIE_RESERVED_ISR,          // 1.14 - Reserved
    PIE_RESERVED_ISR,          // 1.15 - Reserved
    PIE_RESERVED_ISR,          // 1.16 - Reserved

    EPWM9_TZ_ISR,              // 2.9 - ePWM9 Trip Zone Interrupt
    EPWM10_TZ_ISR,             // 2.10 - ePWM9 Trip Zone Interrupt
    EPWM11_TZ_ISR,             // 2.11 - ePWM10 Trip Zone Interrupt
    EPWM12_TZ_ISR,             // 2.12 - ePWM10 Trip Zone Interrupt
    PIE_RESERVED_ISR,          // 2.13 - Reserved
    PIE_RESERVED_ISR,          // 2.14 - Reserved
    PIE_RESERVED_ISR,          // 2.15 - Reserved
    PIE_RESERVED_ISR,          // 2.16 - Reserved

    EPWM9_ISR,                 // 3.9 - ePWM9 Interrupt
    EPWM10_ISR,                // 3.10 - ePWM9 Interrupt
    EPWM11_ISR,                // 3.11 - ePWM10 Interrupt
    EPWM12_ISR,                // 3.12 - ePWM10 Interrupt
    PIE_RESERVED_ISR,          // 3.13 - Reserved
    PIE_RESERVED_ISR,          // 3.14 - Reserved
    PIE_RESERVED_ISR,          // 3.15 - Reserved
    PIE_RESERVED_ISR,          // 3.16 - Reserved

    PIE_RESERVED_ISR,          // 4.9 - Reserved
    PIE_RESERVED_ISR,          // 4.10 - Reserved
    PIE_RESERVED_ISR,          // 4.11 - Reserved
    PIE_RESERVED_ISR,          // 4.12 - Reserved
    PIE_RESERVED_ISR,          // 4.13 - Reserved
    PIE_RESERVED_ISR,          // 4.14 - Reserved
    PIE_RESERVED_ISR,          // 4.15 - Reserved
    PIE_RESERVED_ISR,          // 4.16 - Reserved
    
    PIE_RESERVED_ISR,          // 5.9 - Reserved
    PIE_RESERVED_ISR,          // 5.10 - Reserved
    PIE_RESERVED_ISR,          // 5.11 - Reserved
    PIE_RESERVED_ISR,          // 5.12 - Reserved
    PIE_RESERVED_ISR,          // 5.13 - Reserved
    PIE_RESERVED_ISR,          // 5.14 - Reserved
    PIE_RESERVED_ISR,          // 5.15 - Reserved
    PIE_RESERVED_ISR,          // 5.16 - Reserved
    
    PIE_RESERVED_ISR,          // 6.9 - Reserved
    PIE_RESERVED_ISR,          // 6.10 - Reserved
    PIE_RESERVED_ISR,          // 6.11 - Reserved
    PIE_RESERVED_ISR,          // 6.12 - Reserved
    PIE_RESERVED_ISR,          // 6.13 - Reserved
    PIE_RESERVED_ISR,          // 6.14 - Reserved
    PIE_RESERVED_ISR,          // 6.15 - Reserved
    PIE_RESERVED_ISR,          // 6.16 - Reserved
    
    PIE_RESERVED_ISR,          // 7.9 - Reserved
    PIE_RESERVED_ISR,          // 7.10 - Reserved
    FSITXA1_ISR,               // 7.11 - FSITXA_INT1 Interrupt
    FSITXA2_ISR,               // 7.12 - FSITXA_INT2 Interrupt
    FSIRXA1_ISR,               // 7.13 - FSIRXA_INT1 Interrupt
    FSIRXA2_ISR,               // 7.14 - FSIRXA_INT2 Interrupt
    PIE_RESERVED_ISR,          // 7.9 - Reserved
    PIE_RESERVED_ISR,          // 7.8 - Reserved
    
    LINA_0_ISR,                // 8.9 - LINA Interrupt0
    LINA_1_ISR,                // 8.10 - LINA Interrupt1
    PIE_RESERVED_ISR,          // 8.11 - Reserved
    PIE_RESERVED_ISR,          // 8.12 - Reserved
    PIE_RESERVED_ISR,          // 8.13 - Reserved
    PIE_RESERVED_ISR,          // 8.14 - Reserved
    PIE_RESERVED_ISR,          // 8.15 - Reserved
    PIE_RESERVED_ISR,          // 8.16 - Reserved
    
    MCANB_0_ISR,               // 9.9 - MCANSSB0
    MCANB_1_ISR,               // 9.10 - MCANSSB1
    MCANB_ECC_ISR,             // 9.11 - MCANSSB_ECC_CORR_PLS
    MCANB_WAKE_ISR,            // 9.12 - MCANSSB_WAKE_AND_TS_PLS
    PIE_RESERVED_ISR,          // 9.13 - Reserved
    PIE_RESERVED_ISR,          // 9.14 - Reserved
    USBA_ISR,                  // 9.15 - USBA Interrupt
    PIE_RESERVED_ISR,          // 8.16 - Reserved
    
    ADCC_EVT_ISR,              // 10.9 - ADCC Event Interrupt
    ADCC2_ISR,                 // 10.10 - ADCC Interrupt 2
    ADCC3_ISR,                 // 10.11 - ADCC Interrupt 3
    ADCC4_ISR,                 // 10.12 - ADCC Interrupt 4
    ADCD_EVT_ISR,              // 10.13 - ADCD Event Interrupt
    ADCD2_ISR,                 // 10.14 - ADCD Interrupt 2
    ADCD3_ISR,                 // 10.15 - ADCD Interrupt 3
    ADCD4_ISR,                 // 10.16 - ADCD Interrupt 4
    
    ADCE_EVT_ISR,              // 11.9 - ADCE Event Interrupt
    ADCE2_ISR,                 // 11.10 - ADCE Interrupt 2
    ADCE3_ISR,                 // 11.11 - ADCE Interrupt 3
    ADCE4_ISR,                 // 11.12 - ADCE Interrupt 4
    PIE_RESERVED_ISR,          // 11.13 - Reserved
    PIE_RESERVED_ISR,          // 11.14 - Reserved
    PIE_RESERVED_ISR,          // 11.15 - Reserved
    PIE_RESERVED_ISR,          // 11.16 - Reserved
    
    PIE_RESERVED_ISR,          // 12.9 - Reserved
    PIE_RESERVED_ISR,          // 12.10 - Reserved
    PIE_RESERVED_ISR,          // 12.11 - Reserved
    PIE_RESERVED_ISR,          // 12.12 - Reserved
    AES_SINTREQUEST_ISR,       // 12.13 - AES Interrupt
    PIE_RESERVED_ISR,          // 12.14 - Reserved
    PIE_RESERVED_ISR,          // 12.15 - Reserved
    PIE_RESERVED_ISR,          // 12.16 - Reserved
};
	
#pragma CODE_SECTION(sInitFlash, ".TI.ramfunc");

struct CPUTIMER_VARS CpuTimer0;

void    sInitSysPll(Uint16 clock_source, Uint16 imult, Uint32 refdiv, Uint32 odiv,Uint16 divsel, Uint32 dccbase);
void	sMemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);
void    sConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period);
void	sInitPieVectTable(void);
void	sInitPieCtrl(void);
void    sInitCpuTimers(void);
void    sInitSysCtrl(void);
void	sInitFlash(void);
void	sInitAdc(void);
void	sInitGpio(void);
void	sInitSCI(void);
void	sInitSCIQuery(void);
void	sInitEPWM(void);
void	sInitECAP(void);
void    sInitTAP(void);
void    sInitialDSP(void)
{
    // Step 1. Initialize System Control registers, PLL, WatchDog, Clocks to default state.
    sInitSysCtrl();
//禁止DSP进入TI的SCAN测试模式
	sInitTAP();
    // Disable and clear all CPU interrupts.
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

	// Initialize PIE and clear PIE registers.
	sInitPieCtrl();

    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
    sInitPieVectTable();
	
	//=======================Run in Flash=======================
	sMemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	sInitFlash();
	
	// Step 2. Initialize EPWM registers for the specific application, ECAP register	
	sInitEPWM();

	sInitECAP();

	// Step 3. Initialize AD registers	
	sInitAdc();

	// Step 4. Select GPIO for the device or for the specific application:
	sInitGpio();

	// Step 5. Initialize SCI registers
	sInitSCI();				// 中断方式
	//sInitSCIQuery();		// 查询方式
	
	// Step 6. Initialize CAN registers


	// Step 7. Initialize SPI registers 


    sInitCpuTimers();    					// For this example, only initialize the Cpu Timers
    sConfigCpuTimer(&CpuTimer0, 150, 500);	// 150MHz,0.5ms
    CpuTimer0Regs.TCR.all = 0x4001;			// Use write-only instruction to set TSS bit = 0

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.USER12_INT = &OSCtxSw;
    PieVectTable.TIMER0_INT = &isrOSTimeBase;

	//PieVectTable.ADCA1_INT = &isrADCA;
	
	PieVectTable.EPWM1_INT = &isrINV;
	PieVectTable.EPWM2_INT = &isrDCDC;
	//PieVectTable.EPWM3_INT = &isrEPWM3;
	//PieVectTable.EPWM6_INT = &isrFAN;

	PieVectTable.ECAP1_INT = &isrLineZero;
	
	PieVectTable.SCIA_RX_INT = &isrSCIAReceive;
	PieVectTable.SCIA_TX_INT = &isrSCIATransmit;
	PieVectTable.SCIB_RX_INT = &isrSCIBReceive;
	PieVectTable.SCIB_TX_INT = &isrSCIBTransmit;
	PieVectTable.SCIC_RX_INT = &isrSCICReceive;
	PieVectTable.SCIC_TX_INT = &isrSCICTransmit;

    EDIS;    // This is needed to disable write to EALLOW protected registers

    // If IER has been adjusted, Please check whether the OSTaskStkInit's IER is the same
    IER |= (M_INT1 | M_INT3 | M_INT9);

    // Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Timer 0 Interrupt

	// Enable EPWM INTn in the PIE: Group 3 interrupt 1-7
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;		// EPWM1
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;		// EPWM2
	//PieCtrlRegs.PIEIER3.bit.INTx3 = 1;		// EPWM3
	//PieCtrlRegs.PIEIER3.bit.INTx5 = 1;		// EPWM5
	//PieCtrlRegs.PIEIER3.bit.INTx6 = 1;		// EPWM6

	//Enable PIE group 4 interrupt 1,2 for eCAP1,eCAP2,eCAP3
	//PieCtrlRegs.PIEIER4.bit.INTx1 = 1;		// eCAP1

	//Enable PIE group 8 interrupt 5,6 for SCIC
	//PieCtrlRegs.PIEIER8.bit.INTx5 = 1;		// 8.5 - SCIC Receive Interrupt
	//PieCtrlRegs.PIEIER8.bit.INTx6 = 1;		// 8.6 - SCIC Transmit Interrupt
	
	//Enable PIE group 9
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;      // 9.1 - SCIA Receive Interrupt
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;      // 9.2 - SCIA Transmit Interrupt
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;      // 9.3 - SCIB Receive Interrupt
    PieCtrlRegs.PIEIER9.bit.INTx4 = 1;      // 9.4 - SCIB Transmit Interrupt

    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    // Enable global Interrupts and higher priority real-time debug events:
    // EINT;   // Enable Global interrupt INTM
    // ERTM;   // Enable Global realtime interrupt DBGM
}

void	sInitComIsr(void)
{
	//Enable PIE group 9
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// 9.1 - SCIA Receive Interrupt
	PieCtrlRegs.PIEIER9.bit.INTx2 = 1;		// 9.2 - SCIA Transmit Interrupt
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;		// 9.3 - SCIB Receive Interrupt
	PieCtrlRegs.PIEIER9.bit.INTx4 = 1;		// 9.4 - SCIB Transmit Interrupt
}
INT32U	udwTapRegsValue = 0;
void	sInitTAP(void)
{
	if(DevCfgRegs.TAP_CONTROL.all == false)
	{
		// 必须一次写入32位,高16的0xA5A5是密钥,低16的0x0001是禁止SCAN标志
		EALLOW;
		DevCfgRegs.TAP_CONTROL.all = 0xA5A50001;
		EDIS;
	}
	udwTapRegsValue = DevCfgRegs.TAP_CONTROL.all;
}


void	sInitFlash(void)
{
	EALLOW;
	
	// Disable Cache and prefetch mechanism before changing wait states
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 0;
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;

	// Set waitstates according to frequency
	//	   *CAUTION*
	// Minimum waitstates required for the flash operating at a given CPU rate
	// must be characterized by TI. Refer to the datasheet for the latest
	// information.
	Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;//0x3;//0x2;

	// Enable Cache and prefetch mechanism to improve performance of code
	// executed from Flash.
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 1;
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;

	// At reset, ECC is enabled. If it is disabled by application software and
	// if application again wants to enable ECC.
	Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

	EDIS;

	// Force a pipeline flush to ensure that the write to the last register
	// configured occurs before returning.
	__asm(" RPT #7 || NOP");
}

// SetVREF - Set Vref mode. Function to select reference mode and offset trim.
// Offset trim for Internal VREF 3.3 is unique.  All other modes use the same
// offset trim. Also note that when the mode parameter is ADC_EXTERNAL, the
// ref parameter has no effect.
//
// In this device, the bandgaps are common for all the ADC instances,
// hence common Vref configuration needs to be done for all the ADCs. This
// API configures same Vref configuration for all the supported ADCs in the
// device.
//void	sSetVREF(int module, int mode, int ref)
void 	sSetVREF(int module, int mode, int ref)
{
    Uint16 *offset;  // pointer to offset trim location in OTP

    //
    // Set up pointer to offset trim in OTP for ADCA.
    //
    offset = (Uint16 *)((Uint32)0x72064U);

    EALLOW;

    //
    // Get offset trim from OTP and write it to the register for ADCA.
    //
    AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCB.
    //
    offset = (Uint16 *)((Uint32)0x72066U);

    //
    // Get offset trim from OTP and write it to the register for ADCB.
    //
    AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCC.
    //
    offset = (Uint16 *)((Uint32)0x72068U);

    //
    // Get offset trim from OTP and write it to the register for ADCC.
    //
    AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCD.
    //
    offset = (Uint16 *)((Uint32)0x7206AU);

    //
    // Get offset trim from OTP and write it to the register for ADCD.
    //
    AdcdRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Set up pointer to offset trim in OTP for ADCE.
    //
    offset = (Uint16 *)((Uint32)0x7206CU);

    //
    // Get offset trim from OTP and write it to the register for ADCE.
    //
    AdceRegs.ADCOFFTRIM.bit.OFFTRIM = (*offset) & 0xFFFU;

    //
    // Configure the reference mode for all ADCs.
    //
    if(mode == ADC_INTERNAL)
    {
        //
        // This Configures reference mode for ADCA (internal). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;
    }
    else if(mode == ADC_EXTERNAL)
    {
        //
        // This configures reference mode for ADCA (external). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;
    }
    else
    {
        //
        // This configures reference mode for ADCA (VDDA). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELB = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELB = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELC = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELC = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELD = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELD = mode;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELE = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELE = mode;        
    }


    //
    // Configure the reference voltage for all ADCs (3.3V or 2.5V).
    //
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFA1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFB1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFC1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFD1P65SEL = ref;
    AnalogSubsysRegs.ANAREFPCTL.bit.ANAREFE1P65SEL = ref;

    EDIS;
}


//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
void	sInitAdc(void)
{
	// *IMPORTANT*
	// The Device_cal function, which copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	EALLOW;
	CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
	(*Device_cal)();
	EDIS;

    // Setup VREF as internal
    sSetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
	sSetVREF(ADC_ADCB, ADC_INTERNAL, ADC_VREF3P3);
	sSetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);

	// To powerup the ADC the ADCENCLK bit should be set first to enable
	// clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
	// Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

	// Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the F2806x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.
	EALLOW;

	//Set pulse positions to late
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
	AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
	AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

	// Power up the ADC and then delay for 1 ms
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
	AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
	AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

	EDIS;

	// Delay before converting ADC channels, Delay >= 5ms
	sDelay1ms(5);	

	// ADC Clock Prescaler
	EALLOW;
/*  0000 ADCCLK = Input Clock / 1.0
	0001 Invalid
	0010 ADCCLK = Input Clock / 2.0
	0011 ADCCLK = Input Clock / 2.5
	0100 ADCCLK = Input Clock / 3.0
	0101 ADCCLK = Input Clock / 3.5
	0110 ADCCLK = Input Clock / 4.0
	0111 ADCCLK = Input Clock / 4.5
	1000 ADCCLK = Input Clock / 5.0
	1001 ADCCLK = Input Clock / 5.5
	1010 ADCCLK = Input Clock / 6.0
	1011 ADCCLK = Input Clock / 6.5
	1100 ADCCLK = Input Clock / 7.0
	1101 ADCCLK = Input Clock / 7.5
	1110 ADCCLK = Input Clock / 8.0
	1111 ADCCLK = Input Clock / 8.5  */	
	//ADC clock = CPU clock / 4  = 37.5Mhz
	AdcaRegs.ADCCTL2.bit.PRESCALE = 0X06;
	AdcbRegs.ADCCTL2.bit.PRESCALE = 0X06;	
	AdccRegs.ADCCTL2.bit.PRESCALE = 0X06;	

	EDIS;

	// Delay before converting ADC channels
	sDelay1ms(5); 

	EALLOW;
		
	//Sample mode
	//AdcaRegs.ADCSOCPRICTL.bit.ONESHOT = 1;// One-shot mode enabled

	// ADCA SOC  数模转换
	// 0111 1111 1111 1111	= 0X7FFF; 
	AdcaRegs.ADCSOC0CTL.bit.CHSEL= 0;		// SOC0 will convert ADCINA0
	AdcaRegs.ADCSOC1CTL.bit.CHSEL= 2;		// SOC1 will convert ADCINA2
	AdcaRegs.ADCSOC2CTL.bit.CHSEL= 3;		// SOC2 will convert ADCINA3
	AdcaRegs.ADCSOC3CTL.bit.CHSEL= 4;		// SOC3 will convert ADCINA4
	AdcaRegs.ADCSOC4CTL.bit.CHSEL= 5;		// SOC4 will convert ADCINA5
	AdcaRegs.ADCSOC5CTL.bit.CHSEL= 6;		// SOC5 will convert ADCINA6
	AdcaRegs.ADCSOC6CTL.bit.CHSEL= 9;		// SOC6 will convert ADCINA9
	AdcaRegs.ADCSOC7CTL.bit.CHSEL= 11;		// SOC7 will convert ADCINA11
	AdcaRegs.ADCSOC8CTL.bit.CHSEL= 12;		// SOC8 will convert ADCINA12
	AdcaRegs.ADCSOC9CTL.bit.CHSEL= 14;		// SOC9 will convert ADCINA14
	AdcaRegs.ADCSOC10CTL.bit.CHSEL= 15;		// SOC10 will convert ADCINA15
	AdcaRegs.ADCSOC11CTL.bit.CHSEL= 16;		// SOC11 will convert ADCINA16
	AdcaRegs.ADCSOC12CTL.bit.CHSEL= 18;		// SOC12 will convert ADCINA18
	AdcaRegs.ADCSOC13CTL.bit.CHSEL= 28;		// SOC13 will convert ADCINA28
	AdcaRegs.ADCSOC14CTL.bit.CHSEL= 26;		// SOC14 will convert ADCINA14
//	AdcaRegs.ADCSOC15CTL.bit.CHSEL= 1;		// SOC15 will convert ADCINA15
	
	// ADCB SOC  数模转换
	// 0000 0011 1111 1111	= 0X01FF; 
	AdcbRegs.ADCSOC0CTL.bit.CHSEL= 7;		// SOC0 will convert ADCINA7
	AdcbRegs.ADCSOC1CTL.bit.CHSEL= 30;		// SOC1 will convert ADCINA30
	AdcbRegs.ADCSOC2CTL.bit.CHSEL= 0;		// SOC2 will convert ADCINA0
	AdcbRegs.ADCSOC3CTL.bit.CHSEL= 1;		// SOC3 will convert ADCINA1
	AdcbRegs.ADCSOC4CTL.bit.CHSEL= 4;		// SOC4 will convert ADCINA4
	AdcbRegs.ADCSOC5CTL.bit.CHSEL= 27;		// SOC5 will convert ADCINA27
	AdcbRegs.ADCSOC6CTL.bit.CHSEL= 5;		// SOC6 will convert ADCINA5
	AdcbRegs.ADCSOC7CTL.bit.CHSEL= 11;		// SOC7 will convert ADCINA11
	AdcbRegs.ADCSOC8CTL.bit.CHSEL= 26;		// SOC8 will convert ADCINA26
	AdcbRegs.ADCSOC9CTL.bit.CHSEL= 18;		// SOC9 will convert ADCINA9
//	AdcbRegs.ADCSOC10CTL.bit.CHSEL= 10;		// SOC10 will convert ADCINA10
//	AdcbRegs.ADCSOC11CTL.bit.CHSEL= 11;		// SOC11 will convert ADCINA11
//	AdcbRegs.ADCSOC12CTL.bit.CHSEL= 12;		// SOC12 will convert ADCINA12
//	AdcbRegs.ADCSOC13CTL.bit.CHSEL= 13;		// SOC13 will convert ADCINA13
//	AdcbRegs.ADCSOC14CTL.bit.CHSEL= 14;		// SOC14 will convert ADCINA14
//	AdcbRegs.ADCSOC15CTL.bit.CHSEL= 15;		// SOC15 will convert ADCINA15

	// ADCC SOC  数模转换
	// 0000 0000 0000 0001	= 0X0001; 
	AdccRegs.ADCSOC0CTL.bit.CHSEL= 27;		// SOC0 will convert ADCINA27
//	AdcbRegs.ADCSOC1CTL.bit.CHSEL= 1;		// SOC1 will convert ADCINA1
//	AdcbRegs.ADCSOC2CTL.bit.CHSEL= 2;		// SOC2 will convert ADCINA2
//	AdcbRegs.ADCSOC3CTL.bit.CHSEL= 3;		// SOC3 will convert ADCINA3
//	AdcbRegs.ADCSOC4CTL.bit.CHSEL= 4;		// SOC4 will convert ADCINA4
//	AdcbRegs.ADCSOC5CTL.bit.CHSEL= 5;		// SOC5 will convert ADCINA5
//	AdcbRegs.ADCSOC6CTL.bit.CHSEL= 6;		// SOC6 will convert ADCINA6
//	AdcbRegs.ADCSOC7CTL.bit.CHSEL= 7;		// SOC7 will convert ADCINA7
//	AdcbRegs.ADCSOC8CTL.bit.CHSEL= 8;		// SOC8 will convert ADCINA8
//	AdcbRegs.ADCSOC9CTL.bit.CHSEL= 9;		// SOC9 will convert ADCINA9
//	AdcbRegs.ADCSOC10CTL.bit.CHSEL= 10; 	// SOC10 will convert ADCINA10
//	AdcbRegs.ADCSOC11CTL.bit.CHSEL= 11; 	// SOC11 will convert ADCINA11
//	AdcbRegs.ADCSOC12CTL.bit.CHSEL= 12; 	// SOC12 will convert ADCINA12
//	AdcbRegs.ADCSOC13CTL.bit.CHSEL= 13; 	// SOC13 will convert ADCINA13
//	AdcbRegs.ADCSOC14CTL.bit.CHSEL= 14; 	// SOC14 will convert ADCINA14
//	AdcbRegs.ADCSOC15CTL.bit.CHSEL= 15; 	// SOC15 will convert ADCINA15

	
	//Assuming a 100ns sample window is desired with a SYSCLK frequency of 150MHz, then the acquisition window
	//duration must be 100ns/6.667ns = 15 cycles. The ACQPS field must be set to 15 - 1 = 14.
	INT8U bTemp = 15;
	// SOCX will use bTemp+1 sampling duration of SYSCLK period.
	// ADCA
	AdcaRegs.ADCSOC0CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC1CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC2CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC3CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC4CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC5CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC6CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC7CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC8CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC9CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC10CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC11CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC12CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC13CTL.bit.ACQPS 	= bTemp;
	AdcaRegs.ADCSOC14CTL.bit.ACQPS 	= bTemp;
//	AdcaRegs.ADCSOC15CTL.bit.ACQPS 	= bTemp;
	// ADCB
	AdcbRegs.ADCSOC0CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC1CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC2CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC3CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC4CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC5CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC6CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC7CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC8CTL.bit.ACQPS 	= bTemp;
	AdcbRegs.ADCSOC9CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC10CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC11CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC12CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC13CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC14CTL.bit.ACQPS 	= bTemp;
//	AdcbRegs.ADCSOC15CTL.bit.ACQPS 	= bTemp;
	// ADCC
	AdccRegs.ADCSOC0CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC1CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC2CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC3CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC4CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC5CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC6CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC7CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC8CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC9CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC10CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC11CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC12CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC13CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC14CTL.bit.ACQPS	= bTemp;
//	AdccRegs.ADCSOC15CTL.bit.ACQPS	= bTemp;


	// SOC Trigger Source Select
	// ADCA
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL 	= 0;	// ADC sampling is forcibly triggered by software.													
	AdcaRegs.ADCSOC1CTL.bit.TRIGSEL 	= 0;	// It is currently triggered in the EPWM1 interrupt service function.
	AdcaRegs.ADCSOC2CTL.bit.TRIGSEL 	= 0;	// for test 20240625
	AdcaRegs.ADCSOC3CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC4CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC5CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC6CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC7CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC8CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC9CTL.bit.TRIGSEL 	= 0;
	AdcaRegs.ADCSOC10CTL.bit.TRIGSEL	= 0;
	AdcaRegs.ADCSOC11CTL.bit.TRIGSEL	= 0;
	AdcaRegs.ADCSOC12CTL.bit.TRIGSEL	= 0;
	AdcaRegs.ADCSOC13CTL.bit.TRIGSEL	= 0;
	AdcaRegs.ADCSOC14CTL.bit.TRIGSEL	= 0;
//	AdcaRegs.ADCSOC15CTL.bit.TRIGSEL	= 0;
	// ADCB
	AdcbRegs.ADCSOC0CTL.bit.TRIGSEL 	= 0;	// ADC sampling is forcibly triggered by software.													
	AdcbRegs.ADCSOC1CTL.bit.TRIGSEL 	= 0;	// It is currently triggered in the EPWM1 interrupt service function.
	AdcbRegs.ADCSOC2CTL.bit.TRIGSEL 	= 0;	// for test 20240625
	AdcbRegs.ADCSOC3CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC4CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC5CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC6CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC7CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC8CTL.bit.TRIGSEL 	= 0;
	AdcbRegs.ADCSOC9CTL.bit.TRIGSEL 	= 0;
//	AdcbRegs.ADCSOC10CTL.bit.TRIGSEL	= 0;
//	AdcbRegs.ADCSOC11CTL.bit.TRIGSEL	= 0;
//	AdcbRegs.ADCSOC12CTL.bit.TRIGSEL	= 0;
//	AdcbRegs.ADCSOC13CTL.bit.TRIGSEL	= 0;
//	AdcbRegs.ADCSOC14CTL.bit.TRIGSEL	= 0;
//	AdcbRegs.ADCSOC15CTL.bit.TRIGSEL	= 0;
	// ADCC
	AdccRegs.ADCSOC0CTL.bit.TRIGSEL 	= 0;	// ADC sampling is forcibly triggered by software.													
//	AdccRegs.ADCSOC1CTL.bit.TRIGSEL 	= 0;	// It is currently triggered in the EPWM1 interrupt service function.
//	AdccRegs.ADCSOC2CTL.bit.TRIGSEL 	= 0;	// for test 20240625
//	AdccRegs.ADCSOC3CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC4CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC5CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC6CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC7CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC8CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC9CTL.bit.TRIGSEL 	= 0;
//	AdccRegs.ADCSOC10CTL.bit.TRIGSEL	= 0;
//	AdccRegs.ADCSOC11CTL.bit.TRIGSEL	= 0;
//	AdccRegs.ADCSOC12CTL.bit.TRIGSEL	= 0;
//	AdccRegs.ADCSOC13CTL.bit.TRIGSEL	= 0;
//	AdccRegs.ADCSOC14CTL.bit.TRIGSEL	= 0;
//	AdccRegs.ADCSOC15CTL.bit.TRIGSEL	= 0;

/*	// The corresponding register needs to be enabled when the
	// EPWM2 trigger is turned on (or triggered in other ways).
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; 	// End of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   	// Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 	// Make sure INT1 flag is cleared 	

	EPwm2Regs.ETSEL.bit.SOCAEN = 1;    		// Enable SOCA
    EPwm2Regs.TBCTL.bit.CTRMODE = 0;   */ 	// Unfreeze, and enter up count mode

	EDIS;
}

// InitGpio - Sets all pins to be muxed to GPIO in input mode.
// Also resets CPU control to CPU1 and disables open drain
// and polarity inversion and sets the qualification to synchronous.
// Also unlocks all GPIOs. Only one CPU should call this function.
void sUnlockAllGpio(void)
{
    volatile Uint32 *gpioBaseAddr;
    Uint16 regOffset;

    //
    // Disable pin locks
    //
    EALLOW;
    GpioCtrlRegs.GPALOCK.all = 0x00000000;
    GpioCtrlRegs.GPBLOCK.all = 0x00000000;
    GpioCtrlRegs.GPCLOCK.all = 0x00000000;
    GpioCtrlRegs.GPGLOCK.all = 0x00000000;
    GpioCtrlRegs.GPHLOCK.all = 0x00000000;

    //
    // Fill all registers with zeros. Writing to each register separately
    // for three GPIO modules would make this function *very* long.
    // Fortunately, we'd be writing them all with zeros anyway,
    // so this saves a lot of space.
    //
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs;
    for (regOffset = 0; regOffset < sizeof(GpioCtrlRegs)/2; regOffset++)
    {
        //
        // Must avoid enabling pull-ups on all pins. GPyPUD is offset
        // 0x0C in each register group of 0x40 words. Since this is a
        // 32-bit pointer, the addresses must be divided by 2.
        //
        // Also, to avoid changing pin muxing of the emulator pins to regular
        // GPIOs, skip GPBMUX1 (0x46) and GPBGMUX1 (0x60).
        //
        if ((regOffset % (0x40/2) != (0x0C/2)) && (regOffset != (0x46/2)) &&
            (regOffset != (0x60/2)))
        {
            gpioBaseAddr[regOffset] = 0x00000000;
        }
    }

    gpioBaseAddr = (Uint32 *)&GpioDataRegs;
    for (regOffset = 0; regOffset < sizeof(GpioDataRegs)/2; regOffset++)
    {
        gpioBaseAddr[regOffset] = 0x00000000;
    }

    EDIS;

}

void sInitGpio(void)
{
	// Unlock all GPIO.
    sUnlockAllGpio();
	
	EALLOW;

	// ADCA MUX CH
	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;	// ADC A2
	GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 1;			// 开启模拟功能
	
	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;	// ADC A3
	GpioCtrlRegs.GPHAMSEL.bit.GPIO242 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO228 = 1;	// ADC A6
	GpioCtrlRegs.GPHAMSEL.bit.GPIO228 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;	// ADC A9
	GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;	// ADC A10
	GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO236 = 1;	// ADC 
	GpioCtrlRegs.GPHAMSEL.bit.GPIO236 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLG.bit.GPIO215 = 1;	// ADC 
	GpioCtrlRegs.GPGAMSEL.bit.GPIO215 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLG.bit.GPIO214 = 1;	// ADC 
	GpioCtrlRegs.GPGAMSEL.bit.GPIO214 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLG.bit.GPIO213 = 1;	// ADC 
	GpioCtrlRegs.GPGAMSEL.bit.GPIO213 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO21 = 1;		// ADC  
	GpioCtrlRegs.GPAAMSEL.bit.GPIO21 = 1;			// 开启模拟功能

	AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO28 = 1;		// ADC 
	GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 1;			// 开启模拟功能


	// EPWM1	INVL
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// GPIO0 = PWM1A
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// GPIO1 = PWM1B

	// EPWM2	INVU
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// GPIO2 = PWM2A
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// GPIO3 = PWM2B

	// EPWM3	推挽
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;		// GPIO4 = PWM3A
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;		// GPIO5 = PWM3B

	// EPWM4	LLC
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;		// GPIO6 = PWM4A
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;		// GPIO7 = PWM4B

	// EPWM5	PV
	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;		// GPIO8 = PWM5A
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;		// GPIO9 = PWM5B

	// EPWM6	FAN
	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;	// GPIO10 = PWM6A

	// RLY
	// RLY -- OP.RLY
	GpioCtrlRegs.GPCPUD.bit.GPIO67 = 1;		// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO67 = 1;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO67 = 1;		// GPIO67 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;	// GPIO67 = GPIO
	// RLY -- OP.RLY1	预留
	GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;		// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;		// GPIO30 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;	// GPIO30 = GPIO
	// RLY -- GRID.RLY1
	GpioCtrlRegs.GPBPUD.bit.GPIO59 = 1;		// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;		// GPIO59 = output
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;	// GPIO59 = GPIO
	// RLY -- GRID.RLY2	// 预留
	GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;		// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// GPIO34 = output
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// GPIO34 = GPIO
	
	// HW OVER
	// PV.OVP		PV过流信号
	GpioCtrlRegs.GPCPUD.bit.GPIO79 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO79 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO79 = 0; 	// GPIO79 = input
	GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0;	// GPIO79 = GPIO
	// BAT.OVP		电池过压信号
	GpioCtrlRegs.GPCPUD.bit.GPIO78 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO78 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO78 = 0; 	// GPIO78 = input
	GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0;	// GPIO78 = GPIO
	// BUS.OVP		BUS过压信号
	GpioCtrlRegs.GPCPUD.bit.GPIO77 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO77 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO77 = 0; 	// GPIO77 = input
	GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0;	// GPIO77 = GPIO

	// 风扇堵转信号
	// FAN CLK1
	GpioCtrlRegs.GPBPUD.bit.GPIO44 = 0;	  	// Disable pullup on GPIO34
	GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;  	// Load output latch to high
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;	  	// GPIO44 = input
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;   	// GPIO44 = GPIO
	// FAN CLK1
	GpioCtrlRegs.GPBPUD.bit.GPIO45 = 0;	  	// Disable pullup on GPIO34
	GpioDataRegs.GPBCLEAR.bit.GPIO45 = 1;  	// Load output latch to high
	GpioCtrlRegs.GPBDIR.bit.GPIO45 = 0;	  	// GPIO45 = input
	GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;   	// GPIO45 = GPIO

	// 电池软起
	// STAR.EN	电池软起使能
	GpioCtrlRegs.GPCPUD.bit.GPIO74 = 1;		// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO74 = 1;		// GPIO74 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;	// GPIO74 = GPIO
	// SR.DRV	电池充放MOS开关使能
	GpioCtrlRegs.GPCPUD.bit.GPIO73 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1; 	// GPIO73 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;	// GPIO73 = GPIO


	// KEY.SNESE	 主开关键
	GpioCtrlRegs.GPCPUD.bit.GPIO72 = 1;		// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO72 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO72 = 0;		// GPIO72 = input
	GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;	// GPIO72 = GPIO

	// KEY2.SNESE	 预留按键
	GpioCtrlRegs.GPCPUD.bit.GPIO70 = 1;		// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO70 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO70 = 0;		// GPIO70 = input
	GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;	// GPIO70 = GPIO

	// PV.FUSE		PV保险丝熔断使能
	GpioCtrlRegs.GPCPUD.bit.GPIO71 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO71 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO71 = 1; 	// GPIO71 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0;	// GPIO71 = GPIO

	// PV.LOAD.EN	PV弱光吸收电路使能信号
	GpioCtrlRegs.GPBPUD.bit.GPIO58 = 1; 	// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO58 = 0;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1; 	// GPIO58 = output
	GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;	// GPIO58 = GPIO

	// SPS.EN		BOOST辅助电源使能信号
	GpioCtrlRegs.GPBPUD.bit.GPIO57 = 1; 	// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO57 = 0;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1; 	// GPIO57 = output
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;	// GPIO57 = GPIO

	// KEY.SPS(ONOFF)		关机信号/SYS辅源
	GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0; 	// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO56 = 0;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO56 = 1; 	// GPIO56 = output
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;	// GPIO56 = GPIO

	// EEPROM
	// EEPROM EEP.SDA
	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0; 	// Enable pullup on 	  
	GpioDataRegs.GPASET.bit.GPIO24 = 1; 	// Load output latch to High
	GpioCtrlRegs.GPADIR.bit.GPIO24 = 1; 	// GPIO24 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;	// GPIO24 = I/O
	// EEPROM EEP.SCL
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0; 	// Enable pullup on 	  
	GpioDataRegs.GPBSET.bit.GPIO32 = 1; 	// Load output latch to High
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; 	// GPIO32 = output
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;	// GPIO32 = I/O


	// LCD
	// LCD.BL
	GpioCtrlRegs.GPCPUD.bit.GPIO69 = 0; 	// Enable pullup on GPIO17		// 使能上拉
	GpioDataRegs.GPCSET.bit.GPIO69 = 1; 	// Load output latch to high
	GpioCtrlRegs.GPCDIR.bit.GPIO69 = 1; 	// GPIO69 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 0;	// GPIO69 = GPIO
	//LCD.CS
	GpioCtrlRegs.GPCPUD.bit.GPIO68 = 0; 	// Disable pullup on GPIO25  
	GpioDataRegs.GPCSET.bit.GPIO68 = 1; 	// Load output latch to high
	GpioCtrlRegs.GPCDIR.bit.GPIO68 = 1; 	// GPIO68 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;	// GPIO68 = GPIO
	//LCD.CLK
	GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0; 	// Disable pullup on GPIO27 	
	GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 1; 	// GPIO27 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;	// GPIO27 = GPIO
	//LCD.SDA
	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0; 	// Disable pullup on GPIO26
	GpioDataRegs.GPACLEAR.bit.GPIO26 = 1;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO26 = 1; 	// GPIO26 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;	// GPIO26 = GPIO
	// LCD.EN
	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1; 	// Enable pullup on GPIO17		// 使能上拉
	GpioDataRegs.GPASET.bit.GPIO25 = 0; 	// Load output latch to high
	GpioCtrlRegs.GPADIR.bit.GPIO25 = 1; 	// GPIO25 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;	// GPIO25 = GPIO

	// WIFI.EN		WIFI使能信号
	GpioCtrlRegs.GPCPUD.bit.GPIO65 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO65 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO65 = 1; 	// GPIO65 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0;	// GPIO65 = GPIO

	// AUX.EN		AC辅助电源使能信号
	GpioCtrlRegs.GPCPUD.bit.GPIO66 = 1; 	// Disable pullup on
	GpioDataRegs.GPCCLEAR.bit.GPIO66 = 0;	// Load output latch to low
	GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1; 	// GPIO66 = output
	GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;	// GPIO66 = GPIO

	//PV防反
	GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1; 	// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO42 = 0;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1; 	// GPIO42 = output
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;	// GPIO42 = GPIO


	// LED1
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1; 	// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO11 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1; 	// GPIO11 = output
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;	// GPIO11 = GPIO
	// LED2
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1; 	// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO12 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1; 	// GPIO12 = output
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;	// GPIO12 = GPIO
	// LED3
	GpioCtrlRegs.GPBPUD.bit.GPIO46 = 1;		// Disable pullup on
	GpioDataRegs.GPBCLEAR.bit.GPIO46 = 0;	// Load output latch to low
	GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1;		// GPIO46 = output
	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;	// GPIO46 = GPIO
	// LED4
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1; 	// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO29 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 1; 	// GPIO29 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;	// GPIO29 = GPIO	

	// BEEP
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;		// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO16 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;		// GPIO16 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;	// GPIO16 = GPIO

//	// SCIA		WIFI通讯
//	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;		// Enable pullup on
//	GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 3;	// Asynch input
//	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 6;	// GPIO63 = SCIA RXD
//	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;		// Enable pullup on
//	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 6;	// GPIO62 = SCIA TXD

	// SCIA		WIFI通讯
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;		// Enable pullup on
	GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 3;	// Asynch input
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 2;	// GPIO63 = SCIA RXD
	GpioCtrlRegs.GPBGMUX2.bit.GPIO63 = 1;	// GPIO63 = SCIA RXD
	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;		// Enable pullup on
	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 2;	// GPIO62 = SCIA TXD
	GpioCtrlRegs.GPBGMUX2.bit.GPIO62 = 1;	// GPIO62 = SCIA TXD
	// SCIB		调试串口
	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;		// Enable pullup on
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;	// Asynch input
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;	// GPIO23 = SCIB RXD
	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;		// Enable pullup on
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;	// GPIO22 = SCIB TXD

	// CAN配置
	// CAN
//	GPIO_setPinConfig(GPIO_35_MCANB_RX);
//  GPIO_setPinConfig(GPIO_37_MCANB_TX);

	EDIS;
}

//---------------------------------------------------------------------------
//InitEV:
//---------------------------------------------------------------------------
//This function initializes the Evernt manager register
void	sInitInvEPWM(void)
{
	// PWM1A/1B for Inverter
	EALLOW;
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;  		// force low
	EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;  		// force low
	EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm1Regs.TBPRD = cPWMCntlPeriod50Hz; 			// Period = 5200 TBCLK counts
	EPwm1Regs.TBPHS.bit.TBPHS = 0; 					// Set Phase register to zero
	EPwm1Regs.TBCTR = 0x0000;       				// Clear counter
	EPwm1Regs.TBCTL.bit.CLKDIV = CHP_DIV1; 			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down mode
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;  		// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;    	// load the TBPRD immediately  preriod interrupt couldn't take palce?
	EPwm1Regs.TBCTL.bit.SWFSYNC = 0;				// 137/157里面，写0是无效，写1是强制同步	TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal
	
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  	// load CMPA from shadow register 
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load CMPA on CTR=0
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm1Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm1Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm1Regs.CMPB.all = 0xFFFF;

	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 		// disable DB first,enable it  when control start	// 配置逆变运行模式时再使能死区
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary 
	EPwm1Regs.DBFED.all = 144;						// =1.2usus	// 144 = (192/2*52/3125) = 1.2us   = (1.2/52*cPWMCntlPeriod50Hz)*2
	EPwm1Regs.DBRED.all = 144;						// =1.2usus
	
	
	EPwm1Regs.ETPS.bit.INTCNT = 0;
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;				// first envent trigger
	EPwm1Regs.ETSEL.bit.INTEN = cPWM1_INT_ENABLE;	// enable PWM int 
	//EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    	// Enable event time-base counter equal to period 
	//EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm1Regs.ETCLR.bit.INT = 1;    				// Clears the ETFLG[INT] flag bit

//	EPwm1Regs.AQCTLA.all = 0;
//	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
//	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
//	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;
	EPwm1Regs.ETPS.bit.SOCACNT = ET_1ST;
	EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;

	// Trigger event when DCAH is high
	// DCAH高时触发事件
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE,EPWM_TZ_DC_OUTPUT_A1,EPWM_TZ_EVENT_DCXH_HIGH);
	
	//
	// Configure DCAH to use TRIP4 as an input
	// 配置DCAH以使用TRIP4作为输入
	EPWM_enableDigitalCompareTripCombinationInput(EPWM1_BASE,EPWM_DC_COMBINATIONAL_TRIPIN7,EPWM_DC_TYPE_DCAH);
//	EPWM_enableDigitalCompareTripCombinationInput(EPWM1_BASE,EPWM_DC_COMBINATIONAL_TRIPIN7,EPWM_DC_TYPE_DCAH);//

	//
	// Enable DCA as OST
	// 启用DCA作为OST
	EPWM_enableTripZoneSignals(EPWM1_BASE, EPWM_TZ_SIGNAL_DCAEVT1);
	EPWM_enableTripZoneSignals(EPWM1_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

	//
	// Configure the DCB path to be unfiltered and asynchronous
	// 将DCB路径配置为未过滤的异步路径
	EPWM_setDigitalCompareEventSource(EPWM1_BASE,EPWM_DC_MODULE_A,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
//	EPWM_setDigitalCompareEventSource(EPWM1_BASE,EPWM_DC_MODULE_B,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);//

	//
	// Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
	// 使用ePWM X-BAR配置TRIP4为CTRIP1H
	XBAR_setEPWMMuxConfig(XBAR_TRIP7, XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L);
	XBAR_enableEPWMMux(XBAR_TRIP7, XBAR_MUX00);

	//
	// Clear trip flags
	// 清除标志
	EPWM_clearTripZoneFlag(EPWM1_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST);


	// PWM2A/2B for Inverter
	EALLOW;
	EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;  		// force low
	EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;  		// force low
	EPwm2Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm2Regs.TBPRD = cPWMCntlPeriod50Hz; 			// Period = 5200 TBCLK counts
	EPwm2Regs.TBPHS.bit.TBPHS = 0; 					// Set Phase register to zero
	EPwm2Regs.TBCTR = 0x0000;       				// Clear counter
	EPwm2Regs.TBCTL.bit.CLKDIV = CHP_DIV1; 			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// = 120M/(1*1)
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down mode
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;  		// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;    	// load the TBPRD immediately  preriod interrupt couldn't take palce?
	EPwm2Regs.TBCTL.bit.SWFSYNC = 0;				// TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal
	
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  	// load CMPA from shadow register 
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  	// load CMPA on CTR=0
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm2Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm2Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm2Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm2Regs.CMPB.all = 0xFFFF;

	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 		// disable DB first,enable it  when control start	// 配置逆变运行模式时再使能死区
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi complementary 
	EPwm2Regs.DBFED.all = 144;//192;// =1.5us
	EPwm2Regs.DBRED.all = 144;//192;// =1.5us
	
	EPwm2Regs.ETPS.bit.INTCNT = 0;
	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;				// first envent trigger
	EPwm2Regs.ETSEL.bit.INTEN = cPWM2_INT_ENABLE;  	// enable PWM int 
	//EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    	// Enable event time-base counter equal to period 
	//EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm2Regs.ETCLR.bit.INT = 1;    				// Clears the ETFLG[INT] flag bit

//	EPwm2Regs.AQCTLA.all = 0;
//	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
//	EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
//	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
//
	EPwm2Regs.ETSEL.bit.SOCAEN = 1;
	EPwm2Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;
	EPwm2Regs.ETPS.bit.SOCACNT = ET_1ST;
	EPwm2Regs.ETPS.bit.SOCAPRD = ET_1ST;

	
	// Trigger event when DCAH is high
	// DCAH高时触发事件
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM2_BASE,EPWM_TZ_DC_OUTPUT_A1,EPWM_TZ_EVENT_DCXH_HIGH);
	
	//
	// Configure DCAH to use TRIP4 as an input
	// 配置DCAH以使用TRIP4作为输入
	EPWM_enableDigitalCompareTripCombinationInput(EPWM2_BASE,EPWM_DC_COMBINATIONAL_TRIPIN7,EPWM_DC_TYPE_DCAH);
//	EPWM_enableDigitalCompareTripCombinationInput(EPWM2_BASE,EPWM_DC_COMBINATIONAL_TRIPIN7,EPWM_DC_TYPE_DCAH);//

	//
	// Enable DCA as OST
	// 启用DCA作为OST
	EPWM_enableTripZoneSignals(EPWM2_BASE, EPWM_TZ_SIGNAL_DCAEVT1);
	EPWM_enableTripZoneSignals(EPWM2_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

	//
	// Configure the DCB path to be unfiltered and asynchronous
	// 将DCB路径配置为未过滤的异步路径
	EPWM_setDigitalCompareEventSource(EPWM2_BASE,EPWM_DC_MODULE_A,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
//	EPWM_setDigitalCompareEventSource(EPWM2_BASE,EPWM_DC_MODULE_B,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);//

	//
	// Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
	// 使用ePWM X-BAR配置TRIP4为CTRIP1H
	XBAR_setEPWMMuxConfig(XBAR_TRIP7, XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L);
	XBAR_enableEPWMMux(XBAR_TRIP7, XBAR_MUX00);

	//
	// Clear trip flags
	// 清除标志
	EPWM_clearTripZoneFlag(EPWM2_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST);

}



void	sInitDcDcEPWM(void)
{
	// EPWM3 -- DCDC L
	EALLOW;
	EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// force low
	EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// force low

	//00：时基计数器上的负载等于零
	//01：时基计数器上的负载等于周期
	//10：时基计数器上的负载等于零或计数器等于周期
	//11：立即加载（活动寄存器由程序直接访问CPU，而不是从影子寄存器加载)。
	EPwm3Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm3Regs.TBPRD = cDCDCPeriod;					// Period = 1200 TBCLK counts
	EPwm3Regs.TBPHS.bit.TBPHS = 0;					// Set Phase register to zero
	EPwm3Regs.TBCTR = 0x0000;						// Clear counter
	EPwm3Regs.TBCTL.bit.CLKDIV = CHP_DIV1;			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// up-down mode
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;			// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// load the TBPRD immediately  preriod interrupt couldn't take palce?
//	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal	// F2800137里面已经去掉了这个位
	EPwm3Regs.TBCTL.bit.SWFSYNC = 0;				// 137/157里面，写0是无效，写1是强制同步	TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal
//	  EPwm3Regs.TBCTL.bit.PHSDIR = TB_UP;			// Count Up on sync (=240 deg)，同步信号来临时，向上计数
	
	EPwm3Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1; 		// ePWM3 SYNCO is generated on CTR=0	
	
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 	// load CMPA from shadow register 
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load CMPA on CTR=0
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm3Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm3Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm3Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm3Regs.CMPB.all = 0xFFFF;

	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;		// disable DB first,enable it  when control start
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi complementary 
	EPwm3Regs.DBFED.all = 50;						// 3% = 1200*2/100*4   0.8us
	EPwm3Regs.DBRED.all = 50;						// 3% = 1200*2/100*4   0.8us
	
	EPwm3Regs.ETPS.bit.INTCNT = 0;
	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST; 			// first envent trigger
	EPwm3Regs.ETSEL.bit.INTEN = cPWM3_INT_ENABLE;	// enable PWM int 
	//EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Enable event time-base counter equal to period 
	//EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm3Regs.ETCLR.bit.INT = 1;					// Clears the ETFLG[INT] flag bit

	EPwm3Regs.AQCTLA.all = 0;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
	EPwm3Regs.CMPA.bit.CMPA = cDCDCPeriod;
	
	EPwm3Regs.AQCTLB.all = 0;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;	
	EPwm3Regs.CMPB.all = 0;

/*
	// Trigger event when DCAH is high
	// DCAH高时触发事件
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM3_BASE,EPWM_TZ_DC_OUTPUT_A1,EPWM_TZ_EVENT_DCXH_HIGH);
		
	//
	// Configure DCAH to use TRIP4 as an input
	// 配置DCAH以使用TRIP4作为输入
	EPWM_enableDigitalCompareTripCombinationInput(EPWM3_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCAH);
//	EPWM_enableDigitalCompareTripCombinationInput(EPWM3_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCAH);//

	//
	// Enable DCA as OST
	// 启用DCA作为OST
	EPWM_enableTripZoneSignals(EPWM3_BASE, EPWM_TZ_SIGNAL_DCAEVT1);
	EPWM_enableTripZoneSignals(EPWM3_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

	//
	// Configure the DCB path to be unfiltered and asynchronous
	// 将DCB路径配置为未过滤的异步路径
		EPWM_setDigitalCompareEventSource(EPWM3_BASE,EPWM_DC_MODULE_A,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
	//	EPWM_setDigitalCompareEventSource(EPWM3_BASE,EPWM_DC_MODULE_B,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);//

	//
	// Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
	// 使用ePWM X-BAR配置TRIP4为CTRIP1H
	XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L);
	XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX02);
	//
		// Clear trip flags
	// 清除标志
	EPWM_clearTripZoneFlag(EPWM3_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST);

*/


	// EPWM4 -- DCDC H
	EALLOW;
	EPwm4Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			//force low
	EPwm4Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			//force low

	//00：时基计数器上的负载等于零
	//01：时基计数器上的负载等于周期
	//10：时基计数器上的负载等于零或计数器等于周期
	//11：立即加载（活动寄存器由程序直接访问CPU，而不是从影子寄存器加载)。
	EPwm4Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm4Regs.TBPRD = cDCDCPeriod;					// Period = 1200 TBCLK counts
	EPwm4Regs.TBPHS.bit.TBPHS = 0;					// Set Phase register to zero	//移项CNT
	EPwm4Regs.TBCTR = 0x0000;						// Clear counter	与 TBPHS一样
	EPwm4Regs.TBCTL.bit.CLKDIV = CHP_DIV1;			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// up-down mode
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;			// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;			// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// load the TBPRD immediately  preriod interrupt couldn't take palce?
	EPwm4Regs.TBCTL.bit.SWFSYNC = 0;				// TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal
	
	EPwm4Regs.TBCTL2.bit.PRDLDSYNC = 2; 			// 15:14 PRD Shadow to Active Load on SYNC Event
	EPwm4Regs.EPWMSYNCINSEL.bit.SEL = 3;			//	base PWM3 
	
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 	// load CMPA from shadow register 
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load CMPA on CTR=0
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm4Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm4Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm4Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm4Regs.CMPB.all = 0xFFFF;

	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;		// disable DB first,enable it  when control start
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi complementary 
	EPwm4Regs.DBFED.all = 0;						// 3% = 1200*2/100*4   0.8us 
	EPwm4Regs.DBRED.all = 0;						// 3% = 1200*2/100*4   0.8us 
	
	EPwm4Regs.ETPS.bit.INTCNT = 0;
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST; 			// first envent trigger
	EPwm4Regs.ETSEL.bit.INTEN = cPWM5_INT_ENABLE;	// enable PWM int 
	//EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Enable event time-base counter equal to period 
	//EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm4Regs.ETCLR.bit.INT = 1;					// Clears the ETFLG[INT] flag bit

	EPwm4Regs.AQCTLA.all = 0;
	EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
	EPwm4Regs.CMPA.bit.CMPA = cDCDCPeriod;
	
	EPwm4Regs.AQCTLB.all = 0;
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm4Regs.AQCTLB.bit.CBD = AQ_SET;	
	EPwm4Regs.CMPB.all = 0;

	/*
	// Trigger event when DCAH is high
	// DCAH高时触发事件
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM4_BASE,EPWM_TZ_DC_OUTPUT_A1,EPWM_TZ_EVENT_DCXH_HIGH);
	
	//
	// Configure DCAH to use TRIP4 as an input
	// 配置DCAH以使用TRIP4作为输入
	EPWM_enableDigitalCompareTripCombinationInput(EPWM4_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCAH);
//	EPWM_enableDigitalCompareTripCombinationInput(EPWM4_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCAH);//

	//
	// Enable DCA as OST
	// 启用DCA作为OST
	EPWM_enableTripZoneSignals(EPWM4_BASE, EPWM_TZ_SIGNAL_DCAEVT1);
	EPWM_enableTripZoneSignals(EPWM4_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

	//
	// Configure the DCB path to be unfiltered and asynchronous
	// 将DCB路径配置为未过滤的异步路径
	EPWM_setDigitalCompareEventSource(EPWM4_BASE,EPWM_DC_MODULE_A,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);
//	EPWM_setDigitalCompareEventSource(EPWM4_BASE,EPWM_DC_MODULE_B,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);//

	//
	// Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
	// 使用ePWM X-BAR配置TRIP4为CTRIP1H
	XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L);
	XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX02);
	//
	// Clear trip flags
	// 清除标志
	EPWM_clearTripZoneFlag(EPWM4_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST);
*/

}


void	sInitPvEPWM(void)
{
	// EPWM5 -- BUCK
	EALLOW;
	EPwm5Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// force low
	EPwm5Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// force low

	//00：时基计数器上的负载等于零
	//01：时基计数器上的负载等于周期
	//10：时基计数器上的负载等于零或计数器等于周期
	//11：立即加载（活动寄存器由程序直接访问CPU，而不是从影子寄存器加载)。
	EPwm5Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm5Regs.TBPRD = cBuckPeriod;					// Period = 1200 TBCLK counts
	EPwm5Regs.TBPHS.bit.TBPHS = 0;					// Set Phase register to zero
	EPwm5Regs.TBCTR = 0x0000;						// Clear counter
	EPwm5Regs.TBCTL.bit.CLKDIV = CHP_DIV1;			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// up-down mode
	EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;			// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm5Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// load the TBPRD immediately  preriod interrupt couldn't take palce?
//	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal	// F2800137里面已经去掉了这个位
	EPwm5Regs.TBCTL.bit.SWFSYNC = 0;				// 137/157里面，写0是无效，写1是强制同步	TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal
//	  EPwm5Regs.TBCTL.bit.PHSDIR = TB_UP;			// Count Up on sync (=240 deg)，同步信号来临时，向上计数
	
	EPwm5Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1; 		// ePWM3 SYNCO is generated on CTR=0	
	
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 	// load CMPA from shadow register 
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load CMPA on CTR=0
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm5Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm5Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm5Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm5Regs.CMPB.all = 0xFFFF;

	EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;		// disable DB first,enable it  when control start
	EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi complementary 
	EPwm5Regs.DBFED.all = 50;						// 3% = 1200*2/100*4   0.8us
	EPwm5Regs.DBRED.all = 50;						// 3% = 1200*2/100*4   0.8us
	
	EPwm5Regs.ETPS.bit.INTCNT = 0;
	EPwm5Regs.ETPS.bit.INTPRD = ET_1ST; 			// first envent trigger
	EPwm5Regs.ETSEL.bit.INTEN = cPWM3_INT_ENABLE;	// enable PWM int 
	//EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Enable event time-base counter equal to period 
	//EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm5Regs.ETCLR.bit.INT = 1;					// Clears the ETFLG[INT] flag bit

	EPwm5Regs.AQCTLA.all = 0;
	EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
	EPwm5Regs.CMPA.bit.CMPA = cBuckPeriod;
	
	EPwm5Regs.AQCTLB.all = 0;
	EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm5Regs.AQCTLB.bit.CBD = AQ_SET;	
	EPwm5Regs.CMPB.all = 0;

    // Configure ePWM5A and ePWM5B to output high on TZB TRIP // 将 ePWM5配置为在 TZA 和 TZB 保险丝断开时输出低电平。
    EPWM_setTripZoneAction(EPWM5_BASE, EPWM_TZ_ACTION_EVENT_TZA,EPWM_TZ_ACTION_LOW);
	EPWM_setTripZoneAction(EPWM5_BASE, EPWM_TZ_ACTION_EVENT_TZB,EPWM_TZ_ACTION_LOW);

    // Trigger event when DCBH is high
    // 当 DCAH 为高电平时触发事件
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM5_BASE,EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DCXH_HIGH);
	//EPWM_setTripZoneDigitalCompareEventCondition(EPWM5_BASE,EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);

    // Configure DCAH to use TRIP4 as an input 将 DCAH 设定为使用 TRIP4 作为输入。
    EPWM_enableDigitalCompareTripCombinationInput(EPWM5_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCAH);
	//EPWM_enableDigitalCompareTripCombinationInput(EPWM5_BASE,EPWM_DC_COMBINATIONAL_TRIPIN4,EPWM_DC_TYPE_DCBH);

    // Enable DCA as OST
    EPWM_enableTripZoneSignals(EPWM5_BASE, EPWM_TZ_SIGNAL_DCAEVT1);

    // Configure the DCB path to be unfiltered and asynchronous 将 DCB 路径设置为不进行过滤且非同步的状态。
    EPWM_setDigitalCompareEventSource(EPWM5_BASE,EPWM_DC_MODULE_A,EPWM_DC_EVENT_1,EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

	// Configure TRIP4 to be CTRIP1H using the ePWM X-BAR // 使用 ePWM X-BAR 将 TRIP4 配置为 CTRIP1H
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX06_CMPSS4_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX06);

    EPWM_clearTripZoneFlag(EPWM5_BASE, EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST);
}

void	sInitFanEPWM(void)
{
	// EPWM6A -- FAN
	EALLOW;
	EPwm6Regs.TZCTL.bit.TZA = TZ_FORCE_LO;			// force low
//	EPwm6Regs.TZCTL.bit.TZB = TZ_FORCE_LO;			// force low
//	EPwm6Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm6Regs.TBPRD = cFanPeriod;					// Period = 3000 TBCLK counts
	EPwm6Regs.TBPHS.bit.TBPHS = 0;					// Set Phase register to zero
	EPwm6Regs.TBCTR = 0x0000;						// Clear counter
	EPwm6Regs.TBCTL.bit.CLKDIV = CHP_DIV1;			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// up-down mode
	EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;			// loaded the TBPRD from shadow register when TBCTR is equal to zero
	//EPwm6Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE; 	// load the TBPRD immediately  preriod interrupt couldn't take palce?
//	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Disable EPWMxSYNCO signal	// F2800137里面已经去掉了这个位
	
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 	// load CMPA from shadow register 
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load CMPA on CTR=0
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm6Regs.AQCTLA.all = 0x0555;					// EPWM5A always low,modify it when  control start
//	EPwm6Regs.AQCTLB.all = 0x0555;					// EPWM5B always low
	EPwm6Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm6Regs.CMPB.all = 0xFFFF;

	EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;		// disable DB first,enable it  when control start	// 这里不会重新启用死区
	EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;		// Active Hi complementary 
	EPwm6Regs.DBFED.all = 450;//270;
	EPwm6Regs.DBRED.all = 450;//270;
	
	EPwm6Regs.ETPS.bit.INTCNT = 0;
	EPwm6Regs.ETPS.bit.INTPRD = ET_1ST; 			// first envent trigger
	EPwm6Regs.ETSEL.bit.INTEN = cPWM5_INT_ENABLE;	// enable PWM int 
	//EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; 	// Enable event time-base counter equal to zero.
	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// Enable event time-base counter equal to period 
	//EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;		// timebase counter equal to period
	EPwm6Regs.ETCLR.bit.INT = 1;					// Clears the ETFLG[INT] flag bit

	EPwm6Regs.AQCTLA.all = 0;
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR; 
	EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;	
	EPwm6Regs.CMPA.bit.CMPA = cFanPeriod;
//	EPwm6Regs.AQCTLA.all = 0;		// for test 20241122
//	EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;
//	EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
//	EPwm6Regs.CMPA.bit.CMPA = cFanPeriod;
	
	EPwm6Regs.AQCTLB.all = 0;
	EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm6Regs.AQCTLB.bit.CBD = AQ_SET;	
	EPwm6Regs.CMPB.all = 0;
}

void	sInitCMPSS1_INV(void)
{
    //
    // Select the value for CMP1HPMXSEL.
    // 选择CMP1HPMXSEL的值。
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_1,0U);
    //
    // Select the value for CMP1LPMXSEL.
    // 选择CMP1LPMXSEL的值。
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPHPMUX_SELECT_1,0U);
    //
    // Sets the configuration for the high comparator.
    // 设置高比较器的配置。
    CMPSS_configHighComparator(CMPSS1_INV_BASE,(CMPSS_INSRC_DAC));// | CMPSS_INV_INVERTED
    //
    // Sets the configuration for the low comparator.
    // 设置低比较器的配置。
    CMPSS_configLowComparator(CMPSS1_INV_BASE,(CMPSS_INSRC_DAC | CMPSS_INV_INVERTED)); 
    //
    // Sets the configuration for the internal comparator DACs.
    // 设置内部比较器dac的配置。
    CMPSS_configDACHigh(CMPSS1_INV_BASE,(CMPSS_DACVAL_PWMSYNC | CMPSS_DACSRC_SHDW));
    CMPSS_configDACLow(CMPSS1_INV_BASE, CMPSS_DACSRC_SHDW);
    //
    // Sets the value of the internal DAC of the high comparator.
    // 设置高比较器的内部DAC的值。
    CMPSS_setDACValueHigh(CMPSS1_INV_BASE,3000U);//9A~10A
    //
    // Sets the value of the internal DAC of the low comparator.
    // 设置低比较器的内部DAC的值。
    CMPSS_setDACValueLow(CMPSS1_INV_BASE,1147U);
    //
    //  Configures the digital filter of the high comparator.
    // 配置高比较器的数字滤波器。
    CMPSS_configFilterHigh(CMPSS1_INV_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    // 配置低比较器的数字滤波器。
    CMPSS_configFilterLow(CMPSS1_INV_BASE, 0U, 1U, 1U);
    //
    // Sets the output signal configuration for the high comparator.
    // 设置高比较器的输出信号配置。
    CMPSS_configOutputsHigh(CMPSS1_INV_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the output signal configuration for the low comparator.
    // 设置低比较器的输出信号配置。
    CMPSS_configOutputsLow(CMPSS1_INV_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the comparator hysteresis settings.
    // 设置比较器滞后设置。
    CMPSS_setHysteresis(CMPSS1_INV_BASE,0U);
    //
    // Configures the comparator subsystem's high ramp generator.
    // 配置比较器子系统的高斜坡发生器。
    CMPSS_configRampHigh(CMPSS1_INV_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the comparator subsystem's low ramp generator.
    // 配置比较器子系统的低斜坡生成器。
    CMPSS_configRampLow(CMPSS1_INV_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用HIGH比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCHigh(CMPSS1_INV_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用LOW比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCLow(CMPSS1_INV_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    // 设置ePWM模块在复位时保持跳闸的下电信号。
    CMPSS_configBlanking(CMPSS1_INV_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    // 在复位时禁用ePWM消隐信号。
    CMPSS_disableBlanking(CMPSS1_INV_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    // 配置数字滤波器锁存器是否通过PWMSYNC复位
    CMPSS_configLatchOnPWMSYNC(CMPSS1_INV_BASE,false,false);
    //
    // Enables the CMPSS module.
    // 启用CMPSS模块。
    CMPSS_enableModule(CMPSS1_INV_BASE);
    //
    // Delay for CMPSS DAC to power up.
    // CMPSS DAC上电延迟。
//    DEVICE_DELAY_US(500);
}
void	sInitCMPSS2_LLC(void)
{
    //
    // Select the value for CMP1HPMXSEL.
    // 选择CMP1HPMXSEL的值。
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_2,1U);
    //
    // Select the value for CMP1LPMXSEL.
    // 选择CMP1LPMXSEL的值。
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPHPMUX_SELECT_2,1U);
    //
    // Sets the configuration for the high comparator.
    // 设置高比较器的配置。
    CMPSS_configHighComparator(CMPSS2_LLC_BASE,(CMPSS_INSRC_DAC));// | CMPSS_INV_INVERTED
    //
    // Sets the configuration for the low comparator.
    // 设置低比较器的配置。
    CMPSS_configLowComparator(CMPSS2_LLC_BASE,(CMPSS_INSRC_DAC)); 
    //
    // Sets the configuration for the internal comparator DACs.
    // 设置内部比较器dac的配置。
    CMPSS_configDACHigh(CMPSS2_LLC_BASE,(CMPSS_DACVAL_PWMSYNC | CMPSS_DACSRC_SHDW));
    CMPSS_configDACLow(CMPSS2_LLC_BASE, CMPSS_DACSRC_SHDW);
    //
    // Sets the value of the internal DAC of the high comparator.
    // 设置高比较器的内部DAC的值。
    CMPSS_setDACValueHigh(CMPSS2_LLC_BASE,4096U);
    //
    // Sets the value of the internal DAC of the low comparator.
    // 设置低比较器的内部DAC的值。
    CMPSS_setDACValueLow(CMPSS2_LLC_BASE,0U);
    //
    //  Configures the digital filter of the high comparator.
    // 配置高比较器的数字滤波器。
    CMPSS_configFilterHigh(CMPSS2_LLC_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    // 配置低比较器的数字滤波器。
    CMPSS_configFilterLow(CMPSS2_LLC_BASE, 0U, 1U, 1U);
    //
    // Sets the output signal configuration for the high comparator.
    // 设置高比较器的输出信号配置。
    CMPSS_configOutputsHigh(CMPSS2_LLC_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the output signal configuration for the low comparator.
    // 设置低比较器的输出信号配置。
    CMPSS_configOutputsLow(CMPSS2_LLC_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the comparator hysteresis settings.
    // 设置比较器滞后设置。
    CMPSS_setHysteresis(CMPSS2_LLC_BASE,0U);
    //
    // Configures the comparator subsystem's high ramp generator.
    // 配置比较器子系统的高斜坡发生器。
    CMPSS_configRampHigh(CMPSS2_LLC_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the comparator subsystem's low ramp generator.
    // 配置比较器子系统的低斜坡生成器。
    CMPSS_configRampLow(CMPSS2_LLC_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用HIGH比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCHigh(CMPSS2_LLC_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用LOW比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCLow(CMPSS2_LLC_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    // 设置ePWM模块在复位时保持跳闸的下电信号。
    CMPSS_configBlanking(CMPSS2_LLC_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    // 在复位时禁用ePWM消隐信号。
    CMPSS_disableBlanking(CMPSS2_LLC_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    // 配置数字滤波器锁存器是否通过PWMSYNC复位
    CMPSS_configLatchOnPWMSYNC(CMPSS2_LLC_BASE,false,false);
    //
    // Enables the CMPSS module.
    // 启用CMPSS模块。
    CMPSS_enableModule(CMPSS2_LLC_BASE);
    //
    // Delay for CMPSS DAC to power up.
    // CMPSS DAC上电延迟。
//    DEVICE_DELAY_US(500);
}

void	sInitCMPSS4_PV(void)
{
    //
    // Select the value for CMP1HPMXSEL.
    // 选择CMP1HPMXSEL的值。
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_4,1U);
    //
    // Select the value for CMP1LPMXSEL.
    // 选择CMP1LPMXSEL的值。
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPHPMUX_SELECT_4,1U);
    //
    // Sets the configuration for the high comparator.
    // 设置高比较器的配置。
    CMPSS_configHighComparator(CMPSS_PVCURR_BASE,(CMPSS_INSRC_DAC));// | CMPSS_INV_INVERTED
    //
    // Sets the configuration for the low comparator.
    // 设置低比较器的配置。
    CMPSS_configLowComparator(CMPSS_PVCURR_BASE,(CMPSS_INSRC_DAC));// | CMPSS_INV_INVERTED
    //
    // Sets the configuration for the internal comparator DACs.
    // 设置内部比较器dac的配置。
    CMPSS_configDACHigh(CMPSS_PVCURR_BASE,(CMPSS_DACVAL_PWMSYNC | CMPSS_DACSRC_SHDW));
    CMPSS_configDACLow(CMPSS_PVCURR_BASE, CMPSS_DACSRC_SHDW);
    //
    // Sets the value of the internal DAC of the high comparator.
    // 设置高比较器的内部DAC的值。
    CMPSS_setDACValueHigh(CMPSS_PVCURR_BASE,3072U);	// 3072U
    //
    // Sets the value of the internal DAC of the low comparator.
    // 设置低比较器的内部DAC的值。
    CMPSS_setDACValueLow(CMPSS_PVCURR_BASE,0U);	// 1024U
    //
    //  Configures the digital filter of the high comparator.
    // 配置高比较器的数字滤波器。
    CMPSS_configFilterHigh(CMPSS_PVCURR_BASE, 0U, 1U, 1U);
    //
    // Configures the digital filter of the low comparator.
    // 配置低比较器的数字滤波器。
    CMPSS_configFilterLow(CMPSS_PVCURR_BASE, 0U, 1U, 1U);
    //
    // Sets the output signal configuration for the high comparator.
    // 设置高比较器的输出信号配置。
    CMPSS_configOutputsHigh(CMPSS_PVCURR_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the output signal configuration for the low comparator.
    // 设置低比较器的输出信号配置。
    CMPSS_configOutputsLow(CMPSS_PVCURR_BASE,(CMPSS_TRIPOUT_ASYNC_COMP | CMPSS_TRIP_ASYNC_COMP));
    //
    // Sets the comparator hysteresis settings.
    // 设置比较器滞后设置。
    CMPSS_setHysteresis(CMPSS_PVCURR_BASE,0U);
    //
    // Configures the comparator subsystem's high ramp generator.
    // 配置比较器子系统的高斜坡发生器。
    CMPSS_configRampHigh(CMPSS_PVCURR_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Configures the comparator subsystem's low ramp generator.
    // 配置比较器子系统的低斜坡生成器。
    CMPSS_configRampLow(CMPSS_PVCURR_BASE, CMPSS_RAMP_DIR_DOWN, 0U,0U,0U,1U,true);
    //
    // Disables reset of HIGH comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用HIGH比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCHigh(CMPSS_PVCURR_BASE);
    //
    // Disables reset of LOW comparator digital filter output latch on PWMSYNC
    // 在PWMSYNC上禁用LOW比较器数字滤波器输出锁存器复位
    CMPSS_disableLatchResetOnPWMSYNCLow(CMPSS_PVCURR_BASE);
    //
    // Sets the ePWM module blanking signal that holds trip in reset.
    // 设置ePWM模块在复位时保持跳闸的下电信号。
    CMPSS_configBlanking(CMPSS_PVCURR_BASE,1U);
    //
    // Disables an ePWM blanking signal from holding trip in reset.
    // 在复位时禁用ePWM消隐信号。
    CMPSS_disableBlanking(CMPSS_PVCURR_BASE);
    //
    // Configures whether or not the digital filter latches are reset by PWMSYNC
    // 配置数字滤波器锁存器是否通过PWMSYNC复位
    CMPSS_configLatchOnPWMSYNC(CMPSS_PVCURR_BASE,false,false);
    //
    // Enables the CMPSS module.
    // 启用CMPSS模块。
    CMPSS_enableModule(CMPSS_PVCURR_BASE);
    //
    // Delay for CMPSS DAC to power up.
    // CMPSS DAC上电延迟。
//    DEVICE_DELAY_US(500);
}
INT16S gi_uwPWM1_TZ_ResetCnt = 0;
INT16S gi_uwPWM1_TZ_Cnt = 0;
void sInitTZCount(void)
{
	if(EPwm1Regs.TZFLG.bit.DCAEVT2)
	{
		EALLOW; 
		EPwm1Regs.TZCLR.bit.DCAEVT2 = 1;
		EPwm1Regs.TZCLR.bit.CBC = 1;
		EPwm1Regs.TZCBCCLR.bit.DCBEVT2 = 1;
		EDIS;
		gi_uwPWM1_TZ_ResetCnt = 0;
		if(++gi_uwPWM1_TZ_Cnt > 30)
		{
			gi_uwPWM1_TZ_Cnt = 0;
//			mDisALLPWMOut();
			mDisINVPWMOut();
			sSetPV1CtrlSts(cPVWait);
			T_FAULT_DATA.bits.bInvSoftOC = true;
			sSetFaultCode(cInvCurrOver);
		}
	}
//	else if(gi_uwPWM1_TZ_Cnt > 0)
//	{
//		if(++gi_uwPWM1_TZ_ResetCnt > 10)
//		{
//			gi_uwPWM1_TZ_ResetCnt = 0;
//			gi_uwPWM1_TZ_Cnt--;
//		}
//	}

}

void sInitEPWM(void)
{
	EALLOW;    
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;			// Stop all the TB clocks
	EDIS;

	sInitInvEPWM();		// 逆变桥臂PWM初始化
	sInitDcDcEPWM();	// 推挽/LLC桥臂PWM初始化
	sInitPvEPWM();		// PV 同步buck发波初始化
	sInitFanEPWM();		// 风扇驱动

	
	sInitCMPSS1_INV();	// INV比较器
//	sInitCMPSS2_LLC();  //LLC比较器
	sInitCMPSS4_PV();	// PV电流比较器
	sInitTZCount();
	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;			// Start all the timers synced
	EDIS;




//	// EPWM3 -- DCDC
//	EALLOW;
//	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;  		// force low
//	EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;  		// force low
//	EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
//	EDIS;
//	
//	EPwm1Regs.TBPRD = cDCDCPeriod; 					// Period = 5200 TBCLK counts
//	EPwm1Regs.TBPHS.bit.TBPHS = 0; 					// Set Phase register to zero
//	EPwm1Regs.TBCTR = 0x0000;       				// Clear counter
//	EPwm1Regs.TBCTL.bit.CLKDIV = CHP_DIV1; 			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
//	EPwm1Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
//	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down mode
//	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
//	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;  		// loaded the TBPRD from shadow register when TBCTR is equal to zero
//	
//	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  	// load CMPA from shadow register 
//	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  	// load CMPA on CTR=0
//	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
//	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
//	EPwm1Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
//	EPwm1Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
//	EPwm1Regs.CMPA.bit.CMPA = 0xFFFF;
//	EPwm1Regs.CMPB.all = 0xFFFF;
//
//	//EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 	// disable DB first,enable it  when control start
//	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 	// disable DB first,enable it  when control start
//	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary 
//	EPwm1Regs.DBFED.all = 197;						// 197 ≈ 1.315us = (1.315/26.3*cDCDCPeriod)*2
//	EPwm1Regs.DBRED.all = 197;
//	
//	
//	EPwm1Regs.ETPS.bit.INTCNT = 0;
//	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;				// first envent trigger
//	EPwm1Regs.ETSEL.bit.INTEN = cPWM3_INT_ENABLE;  	// enable PWM int 
//	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    	// Enable event time-base counter equal to period 
//	EPwm1Regs.ETCLR.bit.INT = 1;    				// Clears the ETFLG[INT] flag bit
//
//	EPwm1Regs.AQCTLA.all = 0;
//	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
//	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
//	EPwm1Regs.CMPA.bit.CMPA = cDCDCPeriod;
//	
//	EPwm1Regs.AQCTLB.all = 0;
//	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
//	EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;	
//	EPwm1Regs.CMPB.all = 0;
}

void sInitECAP(void)	  					//eCAP以SYSCLK为时基
{
	// ECAP1
	ECap1Regs.ECEINT.all = 0x0000;			// Disable all capture interrupts				
	ECap1Regs.ECCLR.all = 0xFFFF;			// Clear all CAP interrupt flags    			
	ECap1Regs.ECCTL1.bit.CAPLDEN = 0;		// Disable CAP register loads  					
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;		// Make sure the counter is stopped				
	ECap1Regs.ECCTL2.bit.CAP_APWM = 0;		// eCAP mode									
	ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;	// one-shot mode								
	ECap1Regs.ECCTL2.bit.SYNCO_SEL = 3;		// disable sync out signal						
	ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;		// disable synv in option						
	ECap1Regs.ECCTL2.bit.STOP_WRAP = 0;		// Stop after Capture Event 1 in one-shot mode	
	ECap1Regs.ECCTL1.bit.CAP1POL = 1;		// Falling edge									
	ECap1Regs.ECCTL1.bit.CTRRST1 = 0;		// do not reset counter         				
	ECap1Regs.ECCTL1.bit.PRESCALE = 0;		// div = /1
	
	ECap1Regs.ECCTL2.bit.REARM = 1;			// arm one-shot									
	ECap1Regs.ECCTL1.bit.CAPLDEN = 1;		// Enable CAP1-CAP4 register loads				
	ECap1Regs.ECEINT.bit.CEVT1 = 1;			// 1 events = interrupt
	
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;		// Start Counter

	ECap1Regs.ECCTL0.bit.INPUTSEL = 0;		// ECap1 captures pins corresponding to INTPUT1		
}

void sInitSCI(void)
{
	// @LSPCLK = 37.5 MHz (150 MHz SYSCLK) LSPCLK = SYSCLKOUT / 4,BRR = LSPCLK / (Baud * 8) - 1;
	// SCIA at 9600   baud,	HBAUD = 0x01 and LBAUD = 0xE7.

// SCIA
	
	SciaRegs.SCICCR.all = 0x07;			// One stop bit, no parity, 8-bit character length
	SciaRegs.SCICTL1.all = 0x03;		// Enable transmit and receive
	
    SciaRegs.SCIHBAUD.all = 0x0001;		// Set Baud	@9600	// @150M / 4	
    SciaRegs.SCILBAUD.all = 0x00E7; 
	
	SciaRegs.SCICTL2.all = 0x03;		// Enable Receive interrupt and transmit interrupt
	SciaRegs.SCICTL1.all = 0x23;   		// Relinquish SCI from Reset

// SCIB
	ScibRegs.SCICCR.all = 0x07;			// One stop bit, no parity, 8-bit character length
	ScibRegs.SCICTL1.all = 0x03;		// Enable transmit and receive

    ScibRegs.SCIHBAUD.all = 0x0001;		// Set Baud	@9600	// @150M / 4
    ScibRegs.SCILBAUD.all = 0x00E7; 
	
	ScibRegs.SCICTL2.all = 0x0003;		// Enable Receive interrupt and transmit interrupt
	ScibRegs.SCICTL1.all = 0x0023;    	// Relinquish SCI from Reset

// SCIC
	ScicRegs.SCICCR.all = 0x07;			// One stop bit, no parity, 8-bit character length
	ScicRegs.SCICTL1.all = 0x03;		// Enable transmit and receive

    ScicRegs.SCIHBAUD.all = 0x0001;		// Set Baud	@9600	// @150M / 4
    ScicRegs.SCILBAUD.all = 0x00E7; 
	
	ScicRegs.SCICTL2.all = 0x0003;		// Enable Receive interrupt and transmit interrupt
	ScicRegs.SCICTL1.all = 0x0023;		// Relinquish SCI from Reset
}

void sInitSCIQuery(void) 
{
	// @LSPCLK = 37.5 MHz (150 MHz SYSCLK) LSPCLK = SYSCLKOUT / 4,BRR = LSPCLK / (Baud * 8) - 1;
	// SCIA at 9600   baud,	HBAUD = 0x01 and LBAUD = 0xE7.

	// SCIA
	SciaRegs.SCIFFTX.all = 0xE040;		// Init SCIA FIFO
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;

    SciaRegs.SCICCR.all = 0x0007;		// One stop bit, no parity, 8-bit character length
    SciaRegs.SCICTL1.all = 0x0003;		// enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
   
    SciaRegs.SCIHBAUD.all = 0x0001;		// SCIA at 9600 baud
    SciaRegs.SCILBAUD.all = 0x00E7;
	
	SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL1.all = 0x0023;		// Relinquish SCI from Reset

	// SCIB
	ScibRegs.SCIFFTX.all = 0xE040;		// Init SCIB FIFO
    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFCT.all = 0x0;

    ScibRegs.SCICCR.all = 0x0007;		// One stop bit, no parity, 8-bit character length
    ScibRegs.SCICTL1.all = 0x0003;		// enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
   
    ScibRegs.SCIHBAUD.all = 0x0001;		// SCIB at 9600 baud
    ScibRegs.SCILBAUD.all = 0x00E7;
	
	ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL1.all = 0x0023;		// Relinquish SCI from Reset
    
    // SCIC
	ScicRegs.SCIFFTX.all = 0xE040;		// Init SCIC FIFO
    ScicRegs.SCIFFRX.all = 0x2044;
    ScicRegs.SCIFFCT.all = 0x0;

    ScicRegs.SCICCR.all = 0x0007;		// One stop bit, no parity, 8-bit character length
    ScicRegs.SCICTL1.all = 0x0003;		// enable TX, RX, internal SCICLK,Disable RX ERR, SLEEP, TXWAKE
    ScicRegs.SCICTL2.bit.TXINTENA = 1;
    ScicRegs.SCICTL2.bit.RXBKINTENA = 1;
   
    ScicRegs.SCIHBAUD.all = 0x0001;		// SCIC at 9600 baud
    ScicRegs.SCILBAUD.all = 0x00E7;
	
	ScicRegs.SCICTL2.all = 0x0003;
    ScicRegs.SCICTL1.all = 0x0023;		// Relinquish SCI from Reset 
}


void    sInitSysCtrl(void)
{   
    volatile Uint16 temp;

	// ============= Disable the watchdog ===============
    // Grab the clock config first so we don't clobber it
    EALLOW;
    temp = WdRegs.WDCR.all & 0x0007;
    WdRegs.WDCR.all = 0x0068 | temp;
    EDIS;

	// ======== Disable and clear all CPU interrupts =======
    DINT;                   // Global Disable all Interrupts
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // Clear all CPU interrupt flags

    // ============== This function initializes the PLL registers =================
   
/*	clock_source：	时钟源
	imult：			SYSPLL整数乘法器
	refdiv：			参考时钟分频器
	odiv：			输出时钟分频器
	divsel：			PLL SYSCLK 分频选择
	dccbase：	
*/
	// 内部振荡器，INT_OSC2是10Mhz的内置振荡器，INT_OSC1是10Mhz的内置振荡器，但INT_OSC1一般作为看门狗或备用时钟
    //sInitSysPll(INT_OSC2, IMULT_30, REFDIV_2, ODIV_1, PLLCLK_BY_1, SYSCTL_DCC_BASE0);
	
	// 外部晶振 SYSCLK@150M, 20MHZ * 30 / 2 / 1 / 2
	//sInitSysPll(XTAL_OSC, IMULT_30, REFDIV_2, ODIV_1, PLLCLK_BY_2, SYSCTL_DCC_BASE0);	// 20Mhz OSC
	sInitSysPll(XTAL_OSC, IMULT_30, REFDIV_2, ODIV_1, PLLCLK_BY_1, SYSCTL_DCC_BASE0);	// 10Mhz OSC

	// ==========以下函数调用指针校准ADC基准电压、DAC失调和内部振荡器===============
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the InitSysCtrl function since during debug time resets, the boot code
    // will not be executed and the gel script will reinitialize all the
    // registers and the calibrated values will be lost.
    Device_cal();

    // ====================== Turn on all peripherals ============================
    // InitPeripheralClocks - Initializes the clocks for the peripherals.
	// Note: In order to reduce power consumption, turn off the clocks to any
	// peripheral that is not specified for your part-number or is not used in the
	// application
	EALLOW;
	
	// LOSPCP prescale register settings, normally it will be set to default values(0x2)
	/*	000, LSPCLK = / 1
		001, LSPCLK = / 2
		010, LSPCLK = / 4 	(default on reset, Project configuration)
		011, LSPCLK = / 6
		100, LSPCLK = / 8	
		101, LSPCLK = / 10
		110, LSPCLK = / 12
		111, LSPCLK = / 14	*/
	ClkCfgRegs.LOSPCP.all = 0x0002; 		// SYSCLKOUT / 4 (SCI,SPI) CLK = 37.5Mhz
	
	CpuSysRegs.PCLKCR0.bit.CLA1 = 1;
	CpuSysRegs.PCLKCR0.bit.DMA = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
	CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
	CpuSysRegs.PCLKCR0.bit.HRCAL = 1;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	CpuSysRegs.PCLKCR0.bit.ERAD = 1;

	CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM9 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM11 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM12 = 1;


	CpuSysRegs.PCLKCR3.bit.ECAP1 = 1;
	CpuSysRegs.PCLKCR3.bit.ECAP2 = 1;

	CpuSysRegs.PCLKCR4.bit.EQEP1 = 1;
	CpuSysRegs.PCLKCR4.bit.EQEP2 = 1;
	CpuSysRegs.PCLKCR4.bit.EQEP3 = 1;

	CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
	CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
	CpuSysRegs.PCLKCR7.bit.SCI_C = 1;

	CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
	CpuSysRegs.PCLKCR8.bit.SPI_B = 1;

	CpuSysRegs.PCLKCR9.bit.I2C_A = 1;
	CpuSysRegs.PCLKCR9.bit.I2C_B = 1;

	CpuSysRegs.PCLKCR10.bit.MCAN_A = 1;
	CpuSysRegs.PCLKCR10.bit.MCAN_B = 1;

	CpuSysRegs.PCLKCR11.bit.USB_A = 1;

	CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_D = 1;
	CpuSysRegs.PCLKCR13.bit.ADC_E = 1;

	CpuSysRegs.PCLKCR14.bit.CMPSS1 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS2 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS3 = 1;
	CpuSysRegs.PCLKCR14.bit.CMPSS4 = 1;

	CpuSysRegs.PCLKCR15.bit.PGA1 = 1;
	CpuSysRegs.PCLKCR15.bit.PGA2 = 1;
	CpuSysRegs.PCLKCR15.bit.PGA3 = 1;

	CpuSysRegs.PCLKCR16.bit.DAC_A = 1;

	CpuSysRegs.PCLKCR17.bit.CLB1 = 1;
	CpuSysRegs.PCLKCR17.bit.CLB2 = 1;

	CpuSysRegs.PCLKCR18.bit.FSITX_A = 1;
	CpuSysRegs.PCLKCR18.bit.FSIRX_A = 1;

	CpuSysRegs.PCLKCR19.bit.LIN_A = 1;

	CpuSysRegs.PCLKCR20.bit.PMBUS_A = 1;

	CpuSysRegs.PCLKCR21.bit.DCC0 = 1;
	CpuSysRegs.PCLKCR21.bit.DCC1 = 1;

	CpuSysRegs.PCLKCR26.bit.AESA = 1;
	CpuSysRegs.PCLKCR27.bit.EPG1 = 1;

	EDIS;

}

// SysIntOsc1Sel - This function switches to Internal Oscillator 1.
void    SysIntOsc1Sel(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2;     // Clk Src = INTOSC1
    EDIS;
}

// SysIntOsc2Sel - This function switches to Internal oscillator 2.
void    SysIntOsc2Sel(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0;     // Clk Src = INTOSC2
    EDIS;
}

// PollX1Counter - Clear the X1CNT counter and then wait for it to saturate four times.
static void PollX1Counter(void)
{
    Uint16 loopCount = 0;

    // Delay for 1 ms while the XTAL powers up
    // 2000 loops, 5 cycles per loop + 9 cycles overhead = 10009 cycles
    //F28x_usDelay(2000);
    sDelay1ms(3);

    // Clear and saturate X1CNT 4 times to guarantee operation
    do
    {
        // Keep clearing the counter until it is no longer saturated
        while(ClkCfgRegs.X1CNT.all > 0x1FF)
        {
            ClkCfgRegs.X1CNT.bit.CLR = 1;
            ClkCfgRegs.X1CNT.bit.CLR = 0;
        }

        // Wait for the X1 clock to saturate
        while(ClkCfgRegs.X1CNT.all != 0x7FFU)
        {
            ;
        }

        // Increment the counter
        loopCount++;
    }while(loopCount < 4);
}

// SysXtalOscSel - This function switches to External CRYSTAL oscillator.
void    SysXtalOscSel(void)
{
    EALLOW;
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;     // Turn on XTALOSC
    ClkCfgRegs.XTALCR.bit.SE = 0;         // Select crystal mode
    EDIS;

    // Wait for the X1 clock to saturate
    PollX1Counter();

    // Select XTAL as the oscillator source
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    EDIS;

    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    while(ClkCfgRegs.MCDCR.bit.MCLKSTS != 0)
    {
        EALLOW;
        ClkCfgRegs.MCDCR.bit.MCLKCLR = 1;
        EDIS;

        // Wait for the X1 clock to saturate
        PollX1Counter();

        // Select XTAL as the oscillator source
        EALLOW;
        ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
        EDIS;
    }
}

// SysXtalOscSESel - This function switches to external oscillator in
// single-ended mode and turns off all other clock sources to minimize power
// consumption. This option may not be available on all device packages
void    SysXtalOscSESel (void)
{
    EALLOW;
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;     // Turn on XTALOSC
    ClkCfgRegs.XTALCR.bit.SE = 1;         // Select single-ended mode
    EDIS;

    // Wait for the X1 clock to saturate
    PollX1Counter();

    // Select XTALOSC as the oscillator source
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    EDIS;

    // If missing clock detected, there is something wrong with the oscillator module.
    if(ClkCfgRegs.MCDCR.bit.MCLKSTS != 0)
    {
        ESTOP0;
    }
}

// ComputeCntSeedValid - Compute Counter seed values based on the frequency ratio of output
// clock vs reference clock & tolerance expected for the desired DCC
void    sComputeCntrSeedValue(Uint32 base, float fclk1_0ratio, Uint32 tolerance)
{
    Uint32 window, dccCounterSeed0, dccValidSeed0, dccCounterSeed1, total_error;
    volatile struct DCC_REGS *DccRegs;

    if(fclk1_0ratio >= 1U)
    {
        // Setting Counter0 & Valid Seed Value with expected tolerance
        // Total error is 12
        window = (12U * 100U) / tolerance;
        dccCounterSeed0 = window - 12U;
        dccValidSeed0 = 24U;
    }
    else
    {
        total_error = (((Uint32)2U / fclk1_0ratio) + (Uint32)10U);

        window = ((total_error * 100U)/ tolerance);

        // Setting Counter0 & Valid Seed Value with expected tolerance
        dccCounterSeed0 = window - total_error;
        dccValidSeed0 = (Uint32)2U * total_error;
    }

    // Multiplying Counter-0 window with PLL Integer Multiplier
    dccCounterSeed1 = window * fclk1_0ratio;

    // Assigning DCC for PLL validation
    if(base == SYSCTL_DCC_BASE0)
        DccRegs = &Dcc0Regs;
    else
        ESTOP0; // Invalid DCC selected

    // Configure COUNTER-0, COUNTER-1 & Valid Window
    DccRegs->DCCCNTSEED0.bit.COUNTSEED0 = dccCounterSeed0; // Loaded Counter0 Value
    DccRegs->DCCVALIDSEED0.bit.VALIDSEED = dccValidSeed0;  // Loaded Valid Value
    DccRegs->DCCCNTSEED1.bit.COUNTSEED1 = dccCounterSeed1; // Loaded Counter1 Value
}

bool    sIsPLLValid(Uint32 base, Uint16 oscSource, Uint16 pllclk, Uint16 imult,
           Uint16 odiv, Uint16 refdiv)
{
    float fclk1_0ratio;
    volatile struct DCC_REGS *DccRegs;

    EALLOW;

    // Assigning DCC for PLL validation
    // Enable Peripheral Clock Domain PCLKCR21 for DCC
    if(base == SYSCTL_DCC_BASE0)
    {
            DccRegs = &Dcc0Regs;
            CpuSysRegs.PCLKCR21.bit.DCC0 = 1;
    }
    else
        ESTOP0; // Invalid DCC selected

    // Clear Error & Done Flag
    DccRegs->DCCSTATUS.bit.ERR = 1;
    DccRegs->DCCSTATUS.bit.DONE = 1;

    // Disable DCC
    DccRegs->DCCGCTRL.bit.DCCENA = 0x5;

    // Disable Error Signal
    DccRegs->DCCGCTRL.bit.ERRENA = 0x5;

    // Disable Done Signal
    DccRegs->DCCGCTRL.bit.DONEENA = 0x5;

    // Configure Clock Source1 to PLL
    // Clk Src1 Key 0xA to enable clock source selection
    switch(pllclk)
    {
        case INT_PLL_SYSPLL:
            DccRegs->DCCCLKSRC1.all = 0xA000;   // Clk Src1 = SYSPLL
            break;

        default:                                // Code shouldn't reach here
            break;
    }

    // Configure Clock Source0 to whatever is set as a reference
    // clock source for PLL
    // Clk Src0 Key 0xA to enable clock source selection
    switch(oscSource)
    {
        case INT_OSC1:
            DccRegs->DCCCLKSRC0.all = 0xA001;   // Clk Src0 = INTOSC1
            break;

        case INT_OSC2:
            DccRegs->DCCCLKSRC0.all = 0xA002;   // Clk Src0 = INTOSC2
            break;

        case XTAL_OSC:
        case XTAL_OSC_SE:
            DccRegs->DCCCLKSRC0.all = 0xA000;   // Clk Src0 = XTAL
            break;

        default:                                // Code shouldn't reach here
            break;
    }

    // Calculating frequency ratio of output clock(f1) vs reference clock(f0)
    fclk1_0ratio = (float)imult / ((odiv + 1U) * (refdiv + 1));

    // Computing and configuring Counter0 , Counter1 & Valid Seed Values
    // with +/-1% tolerance for the desired DCC
    sComputeCntrSeedValue(base, fclk1_0ratio, DCC_COUNTER0_TOLERANCE);

    // Enable Single Shot Mode
    DccRegs->DCCGCTRL.bit.SINGLESHOT = 0xA;

    // Enable DCC to start counting
    DccRegs->DCCGCTRL.bit.DCCENA = 0xA;
    EDIS;

    // Wait until Error or Done Flag is generated
    while((DccRegs->DCCSTATUS.all & 3) == 0)
    {
    }

    // Returns true if DCC completes without error
    return((DccRegs->DCCSTATUS.all & 3) == 2);
}

// InitPll - This function initializes the PLL registers.
// Note: This function uses the DCC to check that the PLLRAWCLK is running at
// the expected rate. The desirable DCC can be provided as a parameter.
/*
	clock_source：时钟源
	imult：SYSPLL整数乘法器
	refdiv：参考时钟分频器
	odiv：输出时钟分频器
	divsel：PLL SYSCLK 分频选择
	dccbase：
*/
void    sInitSysPll(Uint16 clock_source, Uint16 imult, Uint32 refdiv, Uint32 odiv,
                 Uint16 divsel, Uint32 dccbase)
{
    Uint32 timeout,temp_syspllmult, pllLockStatus;
    bool status;

    if(((clock_source & 0x3) == ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL) &&
       (((clock_source & 0x4) >> 2) == ClkCfgRegs.XTALCR.bit.SE)        &&
       (imult  == ClkCfgRegs.SYSPLLMULT.bit.IMULT)           &&
       (refdiv  == ClkCfgRegs.SYSPLLMULT.bit.REFDIV)         &&
       (odiv == ClkCfgRegs.SYSPLLMULT.bit.ODIV)              &&
       (divsel == ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV))
    {
        // Everything is set as required, so just return
        return;
    }

    EALLOW;

    // First modify the PLL multipliers if the multipliers need an update or PLL needs to be powered on / enabled
    if((imult != ClkCfgRegs.SYSPLLMULT.bit.IMULT) ||
       (refdiv != ClkCfgRegs.SYSPLLMULT.bit.REFDIV)||
       (odiv != ClkCfgRegs.SYSPLLMULT.bit.ODIV) ||
       (1U != ClkCfgRegs.SYSPLLCTL1.bit.PLLEN))
    {
        // Bypass PLL and set dividers to / 1
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
		

        // Delay of at least 120 OSCCLK cycles required post PLL bypass
        asm(" RPT #120 || NOP");

        // Evaluate PLL multipliers and dividers
        temp_syspllmult = ((refdiv << 24U) | (odiv << 16U)| imult);
		//temp_syspllmult = ((0 << 24U) | (3 << 16U)| 48);
		
        // Turnoff the PLL
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
        EDIS;

        // Delay of at least 66 OSCCLK cycles
        asm(" RPT #66 || NOP");
		

        if(((clock_source & 0x3) != ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL) ||
          (((clock_source & 0x4) >> 2) != ClkCfgRegs.XTALCR.bit.SE))
        {
            switch (clock_source)
            {
                case INT_OSC1:
                    SysIntOsc1Sel();					
                    break;

                case INT_OSC2:
                    SysIntOsc2Sel();					
                    break;

                case XTAL_OSC:
                    SysXtalOscSel();
                    break;

                case XTAL_OSC_SE:
                    SysXtalOscSESel();
                    break;
            }
        }

        // Delay of at least 60 OSCCLK cycles
        asm(" RPT #60 || NOP");

        EALLOW;

        // Set dividers to /1 to ensure the fastest PLL configuration
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;

        // Program PLL multipliers
        ClkCfgRegs.SYSPLLMULT.all = temp_syspllmult;
		//ClkCfgRegs.SYSPLLMULT.bit.IMULT = imult;		// for test
		//ClkCfgRegs.SYSPLLMULT.bit.ODIV = odiv;		// for test

        // Enable SYSPLL
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;

        // Lock time is 1024 OSCCLK * (REFDIV+1)
        timeout = (1024U * (refdiv + 1U));
        pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;

        // Wait for the SYSPLL lock
        while((pllLockStatus != 1) && (timeout != 0U))
        {
            pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;
            timeout--;
        }

        EDIS;

        // Check PLL Frequency using DCC
        status = sIsPLLValid(dccbase, clock_source, INT_PLL_SYSPLL, imult, odiv , refdiv);
    }
    else
    {
        // Re-Lock of PLL not needed since the multipliers are not updated
        status = true;
    }

    if(status)
    {
        EALLOW;

        // Set divider to produce slower output frequency to limit current increase
        if(divsel != PLLCLK_BY_126)
        {
            ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel + 1;
        }
        else
        {
            ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
        }

        // Enable PLLSYSCLK is fed from system PLL clock
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;

        // Small 100 cycle delay
        asm(" RPT #100 || NOP");

        // Set the divider to user value
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
        EDIS;
    }
    else
        ESTOP0; // If the frequency is out of range, stop here.
}

// InitPieVectTable - This function initializes the PIE vector table to a known state and must be executed after boot time.                   
void	sInitPieVectTable(void)
{
    Uint16 i;
    Uint32 *Source = (void *) &PieVectTableInit;
    Uint32 *Dest = (void *) &PieVectTable;

    // Do not write over first 3 32-bit locations (these locations are
    // initialized by Boot ROM with boot variables)
    Source = Source + 3;
    Dest = Dest + 3;

    EALLOW;
    for(i = 0; i < 221; i++)
    {
    	*Dest++ = *Source++;
    }
    EDIS;

    // Enable the PIE Vector Table
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
}

// InitPieCtrl - This function initializes the PIE control registers to a known state.
void	sInitPieCtrl(void)
{
    // Disable Interrupts at the CPU level:
    DINT;
	
    // Disable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    // Clear all PIEIER registers:
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

    // Clear all PIEIFR registers:
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}

void	sMemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

// InitCpuTimers - This function initializes all three CPU timers to a known state.
void    sInitCpuTimers(void)
{
    // CPU Timer 0
    // Initialize address pointers to respective timer registers
    CpuTimer0.RegsAddr = &CpuTimer0Regs;

    // Initialize timer period to maximum
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;

    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;

    // Make sure timer is stopped
    CpuTimer0Regs.TCR.bit.TSS = 1;

    // Reload all counter register with period value
    CpuTimer0Regs.TCR.bit.TRB = 1;

    // Reset interrupt counters
    //CpuTimer0.InterruptCount = 0;

/*
    // CPU Timer 1 and 2
    // Initialize address pointers to respective timer registers
    CpuTimer1.RegsAddr = &CpuTimer1Regs;
    CpuTimer2.RegsAddr = &CpuTimer2Regs;

    // Initialize timer period to maximum
    CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;

    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    CpuTimer1Regs.TPR.all  = 0;
    CpuTimer1Regs.TPRH.all = 0;
    CpuTimer2Regs.TPR.all  = 0;
    CpuTimer2Regs.TPRH.all = 0;

    // Make sure timers are stopped
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;

    // Reload all counter register with period value
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer2Regs.TCR.bit.TRB = 1;

    // Reset interrupt counters
    CpuTimer1.InterruptCount = 0;
    CpuTimer2.InterruptCount = 0;
*/
}

/************************************************************************************************
ConfigCpuTimer - This function initializes the selected timer to the period specified by the
"Freq" and "Period" parameters. The "Freq" is entered as "MHz" and the "Period" in "uSeconds". 
The timer is held in the stopped state after configuration.
*************************************************************************************************/
void    sConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
    Uint32 PeriodInClocks;

    // Initialize timer period
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    PeriodInClocks = (long) (Freq * Period);
    Timer->RegsAddr->PRD.all = PeriodInClocks - 1;    // Counter decrements PRD+1 times each period

    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;

    // Initialize timer control register
    Timer->RegsAddr->TCR.bit.TSS = 1;   			 // 1 = Stop timer, 0 = Start/Restart Timer
    Timer->RegsAddr->TCR.bit.TRB = 1;   			 // 1 = reload timer
    Timer->RegsAddr->TCR.bit.SOFT = 0;
    Timer->RegsAddr->TCR.bit.FREE = 0;  			 // Timer Free Run Disabled
    Timer->RegsAddr->TCR.bit.TIE = 1;   			 // 0 = Disable 1 = Enable Timer Interrupt

    // Reset interrupt counter
    Timer->InterruptCount = 0;
}

void    sDelay4us(void)
{
    INT8U   xxx;

    for(xxx = 0; xxx< 60; xxx++)    		// 实测120MHz时100＝5us,如果用于IIC则对应100kHz频率
    {
        asm(" NOP ");
    }
}

void    sDelay1ms(INT8U ms)
{
    INT8U   yyy;
    INT16U  xxx;

    for(yyy = 0; yyy < ms; yyy++)
    {
        for(xxx = 0; xxx < 12000; xxx++)    // 实测120MHz时20000＝1ms
        {
            asm(" NOP ");
        }
    }
}
INT16S	swGetuwPWM1_TZ_Cnt(void)
{
	return gi_uwPWM1_TZ_Cnt;
}


