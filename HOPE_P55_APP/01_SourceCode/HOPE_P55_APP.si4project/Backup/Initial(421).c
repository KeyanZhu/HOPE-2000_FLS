/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        F28P55X_DEMO
File Name:      Initial.c
Author:         xiaofeng
Date:           2024.07.11
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

void    sInitialDSP(void)
{
    // Step 1. Initialize System Control registers, PLL, WatchDog, Clocks to default state.
    sInitSysCtrl();

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
	//PieVectTable.EPWM2_INT = &isrDCDC;
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
    IER |= (M_INT1 | M_INT9);

    // Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Timer 0 Interrupt

	// Enable EPWM INTn in the PIE: Group 3 interrupt 1-7
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;		// EPWM1
	//PieCtrlRegs.PIEIER3.bit.INTx2 = 1;		// EPWM2
	//PieCtrlRegs.PIEIER3.bit.INTx3 = 1;		// EPWM3
	//PieCtrlRegs.PIEIER3.bit.INTx5 = 1;		// EPWM5
	//PieCtrlRegs.PIEIER3.bit.INTx6 = 1;		// EPWM6

	//Enable PIE group 4 interrupt 1,2 for eCAP1,eCAP2,eCAP3
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;		// eCAP1

	//Enable PIE group 8 interrupt 5,6 for SCIC
	//PieCtrlRegs.PIEIER8.bit.INTx5 = 1;		// 8.5 - SCIC Receive Interrupt
	//PieCtrlRegs.PIEIER8.bit.INTx6 = 1;		// 8.6 - SCIC Transmit Interrupt
	
	//Enable PIE group 9
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;      // 9.1 - SCIA Receive Interrupt
    PieCtrlRegs.PIEIER9.bit.INTx2 = 1;      // 9.2 - SCIA Transmit Interrupt
    //PieCtrlRegs.PIEIER9.bit.INTx3 = 1;      // 9.3 - SCIB Receive Interrupt
    //PieCtrlRegs.PIEIER9.bit.INTx4 = 1;      // 9.4 - SCIB Transmit Interrupt

    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    // Enable global Interrupts and higher priority real-time debug events:
    // EINT;   // Enable Global interrupt INTM
    // ERTM;   // Enable Global realtime interrupt DBGM
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
	Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;

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
void	sSetVREF(int module, int mode, int ref)
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
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = ~mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = ~mode;
    }
    else if(mode == ADC_EXTERNAL)
    {
        //
        // This configures reference mode for ADCA (external). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = ~0xF;
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = ~0xF;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;
    }
    else
    {
        //
        // This configures reference mode for ADCA (VDDA). Add other ADCs
        // to configure its reference mode
        //
        AnalogSubsysRegs.ANAREFPCTL.bit.REFPMUXSELA = mode;
        AnalogSubsysRegs.ANAREFNCTL.bit.REFNMUXSELA = mode;        
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
	(*Device_cal)();
	EDIS;

    // Setup VREF as internal
    sSetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

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

	// Power up the ADC and then delay for 1 ms
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

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
	EDIS;

	// Delay before converting ADC channels
	sDelay1ms(5); 

	EALLOW;
		
	//Sample mode
	//AdcaRegs.ADCSOCPRICTL.bit.ONESHOT = 1;// One-shot mode enabled

	// SOC  数模转换
	// 0001 0110 0011 0001	= 0X1631; 
	AdcaRegs.ADCSOC0CTL.bit.CHSEL= 0;		// SOC0 will convert ADCINA0
	AdcaRegs.ADCSOC1CTL.bit.CHSEL= 1;		// SOC1 will convert ADCINA1
	AdcaRegs.ADCSOC2CTL.bit.CHSEL= 2;		// SOC2 will convert ADCINA2
	AdcaRegs.ADCSOC3CTL.bit.CHSEL= 3;		// SOC3 will convert ADCINA3
	AdcaRegs.ADCSOC4CTL.bit.CHSEL= 4;		// SOC4 will convert ADCINA4
	AdcaRegs.ADCSOC5CTL.bit.CHSEL= 5;		// SOC5 will convert ADCINA5
	AdcaRegs.ADCSOC6CTL.bit.CHSEL= 6;		// SOC6 will convert ADCINA6
	AdcaRegs.ADCSOC7CTL.bit.CHSEL= 7;		// SOC7 will convert ADCINA7
	AdcaRegs.ADCSOC8CTL.bit.CHSEL= 8;		// SOC8 will convert ADCINA8
	AdcaRegs.ADCSOC9CTL.bit.CHSEL= 9;		// SOC9 will convert ADCINA9
	AdcaRegs.ADCSOC10CTL.bit.CHSEL= 10;		// SOC10 will convert ADCINA10
	AdcaRegs.ADCSOC11CTL.bit.CHSEL= 11;		// SOC11 will convert ADCINA11
	AdcaRegs.ADCSOC12CTL.bit.CHSEL= 12;		// SOC12 will convert ADCINA12
	AdcaRegs.ADCSOC13CTL.bit.CHSEL= 13;		// SOC13 will convert ADCINA13
	AdcaRegs.ADCSOC14CTL.bit.CHSEL= 14;		// SOC14 will convert ADCINA14
	AdcaRegs.ADCSOC15CTL.bit.CHSEL= 15;		// SOC15 will convert ADCINA15
	
	//Assuming a 100ns sample window is desired with a SYSCLK frequency of 150MHz, then the acquisition window
	//duration must be 100ns/6.667ns = 15 cycles. The ACQPS field must be set to 15 - 1 = 14.
	INT8U bTemp = 15;
	// SOCX will use bTemp+1 sampling duration of SYSCLK period.
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
	AdcaRegs.ADCSOC15CTL.bit.ACQPS 	= bTemp;

	// SOC Trigger Source Select
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
	AdcaRegs.ADCSOC15CTL.bit.TRIGSEL	= 0;
	
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
	// EPWM
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// GPIO0 = PWM1A
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;		// Disable pullup on
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// GPIO1 = PWM1B

	// LED4
	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;		// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO20 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;		// GPIO16 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;	// GPIO16 = GPIO
	// LED5
	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1; 	// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO21 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO21 = 1; 	// GPIO13 = output
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;	// GPIO13 = GPIO	

	// KEY1
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1; 	// Disable pullup on
	GpioDataRegs.GPACLEAR.bit.GPIO28 = 0;	// Load output latch to low
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0; 	// GPIO13 = input
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;	// GPIO13 = GPIO

	// KEY2

	// SCIA
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;		// Enable pullup on
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;	// Asynch input
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;	// GPIO28 = SCIA RXD
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;		// Enable pullup on
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;	// GPIO29 = SCIA TXD

	// ECAP
    InputXbarRegs.INPUT1SELECT = 48;      	// 使用 INPUT1--GPIO48 引脚，所有GPIO均支持ECAP
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 0;     // 配置为输入
    GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;     // 配置为上拉
    GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 3;   // GPIO配置为非同步模式

	// ADCA MUX CH
	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;	// ADC A9
	GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 1;			// 开启模拟功能
	
	AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;	// ADC A10
	GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 1;			// 开启模拟功能
	
	EDIS;
}

//---------------------------------------------------------------------------
//InitEV:
//---------------------------------------------------------------------------
//This function initializes the Evernt manager register

void sInitEPWM(void)
{
	// EPWM3 -- DCDC
	EALLOW;
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;  		// force low
	EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;  		// force low
	EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
	EDIS;
	
	EPwm1Regs.TBPRD = cDCDCPeriod; 					// Period = 5200 TBCLK counts
	EPwm1Regs.TBPHS.bit.TBPHS = 0; 					// Set Phase register to zero
	EPwm1Regs.TBCTR = 0x0000;       				// Clear counter
	EPwm1Regs.TBCTL.bit.CLKDIV = CHP_DIV1; 			// TBCLK = SYSCLKOUT / (HSPCLKDIV*CLKDIV)
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = CHP_DIV1;		// =120M/(1*1)
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// up-down mode
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; 		// Do not load the time-base counter (TBCTR) from the time-base phase register (TBPHS)
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;  		// loaded the TBPRD from shadow register when TBCTR is equal to zero
	
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  	// load CMPA from shadow register 
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  	// load CMPA on CTR=0
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.AQCTLA.all = 0x0555;					// EPWM1A always low,modify it when  control start
	EPwm1Regs.AQCTLB.all = 0x0555;					// EPWM1B always low
	EPwm1Regs.CMPA.bit.CMPA = 0xFFFF;
	EPwm1Regs.CMPB.all = 0xFFFF;

	//EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; 	// disable DB first,enable it  when control start
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 	// disable DB first,enable it  when control start
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active Hi complementary 
	EPwm1Regs.DBFED.all = 197;						// 197 ≈ 1.315us = (1.315/26.3*cDCDCPeriod)*2
	EPwm1Regs.DBRED.all = 197;
	
	
	EPwm1Regs.ETPS.bit.INTCNT = 0;
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;				// first envent trigger
	EPwm1Regs.ETSEL.bit.INTEN = cPWM3_INT_ENABLE;  	// enable PWM int 
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    	// Enable event time-base counter equal to period 
	EPwm1Regs.ETCLR.bit.INT = 1;    				// Clears the ETFLG[INT] flag bit

	EPwm1Regs.AQCTLA.all = 0;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;	
	EPwm1Regs.CMPA.bit.CMPA = cDCDCPeriod;
	
	EPwm1Regs.AQCTLB.all = 0;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.CBD = AQ_SET;	
	EPwm1Regs.CMPB.all = 0;
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
	sInitSysPll(XTAL_OSC, IMULT_30, REFDIV_2, ODIV_1, PLLCLK_BY_2, SYSCTL_DCC_BASE0);	// 20Mhz OSC
	//sInitSysPll(XTAL_OSC, IMULT_30, REFDIV_2, ODIV_1, PLLCLK_BY_1, SYSCTL_DCC_BASE0);	// 10Mhz OSC

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


