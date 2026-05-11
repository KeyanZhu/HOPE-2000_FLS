/********************************************************************************
Right Reserve:  Guangzhou Felicity Solar Technology Co., Ltd
Project:        HOPE
File Name:      Main.h
Author:         HOPE Team
Date:           2025.11.10
Description:    None
********************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

/********************************************************************************
* Include head files                                                            *
********************************************************************************/
#include 	<string.h>
#include 	<stdint.h>
#include 	<stdbool.h>

#include 	"kernel.h"

#include 	"Library.h"

#include 	"f28P55x_device.h"
#include 	"f28P55x_examples.h"

#include 	"pin_map.h"
#include 	"hw_gpio.h"
#include 	"hw_memmap.h"
#include 	"hw_types.h"
#include 	"hw_sysctl.h"
#include 	"driverlib.h"
//#include    "asysctl.h"


#include 	"Initial.h"
#include 	"interrupt.h"
#include 	"Initial.h"

#include 	"SupervisorJob.h"
#include 	"InvLoadOPJob.h"
#include 	"GridJob.h"
#include 	"BusBatProtJob.h"
#include 	"ParallelJob.h"
#include 	"InterfaceJob.h"
#include 	"DisplayJob.h"
#include 	"IdleJob.h"

#include	"Module.h"

#include 	"sci_driver.h"
#include	"rly_driver.h"
#include	"eeprom_driver.h"
#include	"Soc.h"
#include	"SoxProcess.h"

#include 	"SciRoute.h"
#include	"Oscillograph.h"
#include 	"AdcProcess.h"
#include 	"AdjProcess.h"
#include 	"ModBusProcess.h"
#include 	"InverterProcess.h"
#include	"EepromProcess.h"
#include	"FanProcess.h"  

#include 	"INVControl.h"
#include 	"INVControlNew.h"

#include	"DCDCControl.h"
#include	"PVControl.h"
#include	"PhaseLock.h"
#include	"PvMppt.h"

#include	"FaultAlarm.h"
#include	"DeratingProcess.h"

#include    "SciPassthrough.h"

//#include	"FlashTech_F280015x_C28x.h"
//#include	"flash_programming_f280015x.h"


/***************************设备信息********************************/
// 逆变器机型
#define cCtrlHOPE1000					1			// HOPE1000
#define cCtrlHOPE2000					2			// HOPE1000

// DSP软件大版本
#define cCtrlV80					80			// 建立工程，功能调试
#define cCtrlV100					100			// 
#define cCtrlV101					101			// 
#define cCtrlV102					102			// 
#define cCtrlV103					103			// 
#define cCtrlV104					104			// 
#define cCtrlV105					105			//  
#define cDspCtrlVersion				cCtrlV80	// 当前编译版本

// DSP软件子版本
#define cCtrlV00					0	// 工程建立，基本配置
#define cCtrlV01					1	// 功能移植
#define cCtrlV02					2	// 解决烧录之后程序跑飞的问题(更新驱动库)
										// 解决烧录后软件直接关辅源的问题(信号写反)
#define cCtrlV03					3	// 解决ADCB外设采样数据不更新的问题，解决B0采样口数据跟随B5采样口变化的问题
#define cCtrlV04					4	// 备份一版本
#define cCtrlV05					5	// 增加库函数文件的包含
										// PV控制改控负端，给定计算同步修改
										// 增加INV比较器触发TZ，增加PV比较器触发TZ
										// 优化部分EEPRON参数写入
										// 驱动辅源，电池充放电MOS开关都在待机时自动开启
										// PV弱光信号在待机时默认不开启
										// 优化MPPT策略，在稳电池电压时，MPPT不启动，PV模式时启动MPPT
#define cCtrlV06					6	// TEST
#define cCtrlV07					7	// 同步朱工代码
#define cCtrlV08					8	// 现版本代码梳理和初步补充
#define cCtrlV09					9	// 增加SOC代码，LED逻辑，同步朱工程序
#define cCtrlV10					10	//
#define cCtrlV11					11	// 内部eeprom、modbus协议全部换掉
										// 协议新增SOC部分内容
										// 优化SOC算法存在问题
										
#define cCtrlV12					12	// 优化SOC算法在32(32位)单片机和DSP(16位)之间计算存在的临时计算结果存储导致SOC积分和自动校准异常问题
										// 优化EEPROM设置项在通讯上写错位
										// 增加单体电芯电压和温度的最大值计算
										// 增加电池过压告警(按3.6V单体算总压)，可能会存在单体达到了但不触发的问题
										// 实时数据显示增加电芯最大最小温度和最大最小单体电芯电压
#define cCtrlV13					13
#define cCtrlV14					14
#define cCtrlV15					15



#define cDspTempVersion				cCtrlV11	// 当前编译版本

// IAP版本	// 不定义,直接读取标识地址自动获取


// CT方向
#define cFirdirect					0 			// 正接	
#define cReverse					1 			// 反接			// 量产版本确认全是反接CT
#define cCTdirection				cReverse	// CT当前方向

// 设备类型
#define MACHINE_TYPE_HOPE             0x0065		// 设备大类 HOPE			// 0x0058 = 88
#define MACHINE_SUB_TYPE_HOPE1000     0x0101  		// 设备子类 HOPE1000		// 0x0102 = 258
#define MACHINE_SUB_TYPE_HOPE2000     0x0200  		// 设备子类 HOPE2000		// 0x0102 = 258


#define MACHINE_HW_VERSION          1000  		// for test
#define MACHINE_SW_VERSION          201 		// for test
//#define MODBUS_PROT_VERSION         200 		// 0-199原对外协议,200优化后对外协议
//#define CAN_PROT_VERSION            200 		// 0-199原CAN并机协议,200优化后并机协议
//#define MACHINE_DBG_VERSION         0   		// 量产时复位为0  // for test
//#define LED_SOC_HW_VERSION          0   		// 0=SOC中存在红灯,1=取消SOC中的红灯
/*******************************************************************/

// CMD内存分配信息
// For TMS320F2800157PN
// Total RAM   =  18kWords( 36kBytes)
// RAM M0      = 0x00000000 - 0x000003FF = 0x00400  1kWords(  2kBytes)
// RAM M1      = 0x00000400 - 0x000007FF = 0x00400  1kWords(  2kBytes)
// RAM LS0     = 0x00008000 - 0x00009FFF = 0x02000  8kWords( 16kBytes)
// RAM LS1     = 0x0000A000 - 0x0000BFFF = 0x02000  8kWords( 16kBytes)
// Total FLASH = 128kWords(256kBytes,2kBytes/Page,total=128Pages)
// FLASH BOOT  = 0x00080000 - 0x00081FFF = 0x02000  8kWords( 16kBytes)
// FLASH BEGIN = 0x00082000 - 0x00082001 = 0x00002  2 Words(  4 Bytes)
// FLASH FLAG1 = 0x00082002 - 0x00082002 = 0x00001  1 Word (  2 Bytes)('F5'=0x4635)
// FLASH FLAG2 = 0x00082003 - 0x00082003 = 0x00001  1 Word (  2 Bytes)('PN'=0x504E)
// FLASH RSVD1 = 0x00082004 - 0x0008200F = 0x0000B 12 Word ( 24 Bytes)
// FLASH FINV  = 0x00082010 - 0x00099FFF = 0x17FF0 96kWords(192kBytes - 32Bytes)
// FLASH RSVD2 = 0x0009A000 - 0x0009FFEF = 0x05FF0 24kWords( 48kBytes - 32Bytes)
// FLASH VALID = 0x0009FFF0 - 0x0009FFFF = 0x00010 16 Words( 32 Bytes) /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

#define CMD_IAP_ADDR_START		0x080000
#define CMD_IAP_ADDR_BV			0x080003
#define CMD_IAP_ADDR_HV			0x080005

/********************************************************************************
* Macros                                                                        *
********************************************************************************/
#define RAM_ADDR_START          0x20000000
#define RAM_ADDR_END            0x2000BFFF
#define RAM_SIZE_MAX            (RAM_ADDR_END-RAM_ADDR_START+1)
#define FLASH_ADDR_START        0x08000000
#define FLASH_ADDR_END          0x0803FFFF
#define FLASH_SIZE_MAX          (FLASH_ADDR_END-FLASH_ADDR_START+1)

#define FLASH_IAP_ADDR_START    0x08000000
#define FLASH_IAP_ADDR_END      0x08003FFF
#define FLASH_APP_ADDR_START    0x08004000
#define FLASH_APP_ADDR_END      0x08033FFF
#define FLASH_FLG_ADDR_START    0x08004130  // don't modify
#define FLASH_FLG_ADDR_END      0x08004133  // don't modify
#define FLASH_EEP1_ADDR_START   0x0803A000
#define FLASH_EEP1_ADDR_END     0x0803BFFF
#define FLASH_EEP2_ADDR_START   0x0803C000
#define FLASH_EEP2_ADDR_END     0x0803DFFF
#define FLASH_EEP3_ADDR_START   0x0803E000
#define FLASH_EEP3_ADDR_END     0x0803FFFF

#define FLASH_IAP_INFO_ADDR     0x08000C00
#define FLASH_IAP_NAME_ADDR     0x08000C60
#define FLASH_IAP_VER_ADDR      0x08000C68
#define FLASH_IAP_TIME_ADDR     0x08000C70
#define FLASH_IAP_ENCRYPT_ADDR  0x08000C90
#define FLASH_IAP_ROLLCODE_ADDR 0x08000C98
#define FLASH_APP_RANDOM1_ADDR  0x08012000
#define FLASH_APP_RANDOM2_ADDR  0x08012400
#define FLASH_APP_TIME_ADDR     0x08012800
#define FLASH_IAP_FLG_ADDR      FLASH_FLG_ADDR_START

#define DSP_FLASH_APP_RANDOM1_ADDR  0x00082000

#if(FLASH_IAP_ADDR_START & 0x7FF)
#error ERROR: FLASH_IAP_ADDR_START must be a multiple of 2048 bytes!
#endif

#if(FLASH_APP_ADDR_START & 0x7FF)
#error ERROR: FLASH_APP_ADDR_START must be a multiple of 2048 bytes!
#endif

#if(FLASH_EEP1_ADDR_START & 0x7FF)
#error ERROR: FLASH_EEP1_ADDR_START must be a multiple of 2048 bytes!
#endif

#if(FLASH_EEP2_ADDR_START & 0x7FF)
#error ERROR: FLASH_EEP2_ADDR_START must be a multiple of 2048 bytes!
#endif

#if(FLASH_EEP3_ADDR_START & 0x7FF)
#error ERROR: FLASH_EEP3_ADDR_START must be a multiple of 2048 bytes!
#endif

#if((FLASH_IAP_INFO_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_INFO_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_INFO_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_IAP_NAME_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_NAME_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_NAME_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_IAP_VER_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_VER_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_VER_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_IAP_TIME_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_TIME_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_TIME_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_IAP_ENCRYPT_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_ENCRYPT_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_ENCRYPT_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_IAP_ROLLCODE_ADDR < FLASH_IAP_ADDR_START) || (FLASH_IAP_ROLLCODE_ADDR > FLASH_IAP_ADDR_END))
#error ERROR: FLASH_IAP_ROLLCODE_ADDR Must be in range of FLASH_IAP_ADDR_START to FLASH_IAP_ADDR_END!
#endif

#if((FLASH_APP_RANDOM1_ADDR <= FLASH_FLG_ADDR_END) || (FLASH_APP_RANDOM1_ADDR > FLASH_APP_ADDR_END))
#error ERROR: FLASH_APP_RANDOM1_ADDR Must be in range of FLASH_APP_ADDR_START to FLASH_APP_ADDR_END!
#endif

#if((FLASH_APP_RANDOM2_ADDR <= FLASH_FLG_ADDR_END) || (FLASH_APP_RANDOM2_ADDR > FLASH_APP_ADDR_END))
#error ERROR: FLASH_APP_RANDOM2_ADDR Must be in range of FLASH_APP_ADDR_START to FLASH_APP_ADDR_END!
#endif

#if((FLASH_APP_TIME_ADDR <= FLASH_FLG_ADDR_END) || (FLASH_APP_TIME_ADDR > FLASH_APP_ADDR_END))
#error ERROR: FLASH_APP_TIME_ADDR Must be in range of FLASH_APP_ADDR_START to FLASH_APP_ADDR_END!
#endif

#if((FLASH_IAP_FLG_ADDR < FLASH_FLG_ADDR_START) || (FLASH_IAP_FLG_ADDR > FLASH_FLG_ADDR_END))
#error ERROR: FLASH_IAP_FLG_ADDR Must be in range of FLASH_FLG_ADDR_START to FLASH_FLG_ADDR_END!
#endif


// Task priority define
#define cPrioSuper                      0
#define cPrioInvLoadOP                  1
#define cPrioGrid                       2
#define cPrioBusBatProt                 3
#define cPrioParallel                   4
#define cPrioInterface                  5
#define cPrioDisplay                    6
#define cPrioIdle                       7
#define cPrioTaskEnd                    8

// Task stack size define	// num max = OS_MAX_STK_SIZE - 100，预留100个字的空间内不使用
#define cMaxSuperJobTaskSize            500
#define cMaxInvLoadOPJobTaskSize        700
#define cMaxGridJobTaskSize             500
#define cMaxBusBatProtJobTaskSize       500
#define cMaxParallelJobTaskSize         500
#define cMaxInterfaceJobTaskSize        500
#define cMaxDisplayJobTaskSize          500
#define cMaxIdleJobTaskSize             200

// Task timer define
#define cTimer1ms                       2
#define cTimer2ms                       4
#define cTimer5ms                       10
#define cTimer8ms                       16
#define cTimer10ms                      20
#define cTimer20ms                      40
#define cTimer50ms                      100
#define cTimer100ms                     200

// SUPERVISOR_JOB task event define
#define eSuperTimer                     0
//#define eSuperInitialOK               1
#define eSuperFault                     2
#define eSuperLineLoss                  3
#define eSuperToShutdown                4
//#define eSuperGFCIOver                4
#define eSuperToStandby                 5
#define eSuperToBat                     6
#define eSuperToLine                    7
#define eSuperOPRlyOn                   8
#define eSuperOPRlyOff                  9
#define eSuperToBypass                  10
#define eSuperToChg                     11
//#define eSuperUserSelect              12
//#define eSuperUserSelect2             13
//#define eSuperUserSelect3             14
#define eSuperSelectPoint               15


// INVLOADOP task event define
#define eInvLoadOPTimer                 0
#define eInvLoadOPInvZero               1
#define eInvLoadOPSinZero               2
#define eInvLoadOPOutputZero            3

// GRID task event define
#define eGridTimer                      0
#define eGridLineZero                   1
#define eGridSLineZero                  2
#define eGridTLineZero                  3
#define eSYNZero                        4

// BUSBATPROT task event define
#define eGeneralTimer                   0

// PARALLEL task event define
#define eParallelTimer                  0
#define eParallelCANParsing             1
#define eParaToLineMode                 2
#define eParaToBatMode                  3
#define eParaToStandbyMode              4
#define eParaToFaultMode                5
#define eParaToBypassMode               6
#define eParaToShutDownMode             7
#define eParaOPRlyOn                    8
#define eParaOPRlyOff                   9
#define eParaBusSoftOn                  10
#define eParaToMasterRelease            11
#define eParaSYNLineLoss                12
#define eParaDataSet                    13
#define eParaSelectPoint                15

// INTERFACE task event define
#define eInterfaceTimer                 0
#define eEepromTimer                    eInterfaceTimer
#define eI2CEEpromUserSave              1
#define eI2CEEpromUser2Save             2
#define eI2CEEpromUser3Save             3
#define eI2CEEpromFacSave               4
#define eI2CEEpromFac2Save              5
#define eMCUDSPDataParsing              6
#define eEepromSaveCounter              7
#define eEepromSaveKeyNum               8
#define eEepromWaitTime                 9
#define eEepromSaveSetDate              10
#define eTTLParsing                     11
#define e485Parsing                     12
#define e232Parsing                     13

// DISPLAY task event define
#define eDisplayTimer                   0

// IDLE task event define
#define eIdleTimer                      0

//
#define cChargeUtilityFrist             0
#define cChargeSolarFrist               1
#define cChargeSolarAndUtilityFrist     2
#define cChargeSolarOnly                3

#define cOutputUtilityFrist             0
#define cOutputSolarFrist               1
#define cOutputSolarBatUtility          2

#define cSelfConsupmMode                0
//#define cBatBackupMode2                   1
#define cBatBackupMode                  1

// Bat volt define
#define cBatVoltReal0V1     10
#define cBatVoltReal0V2     20
#define cBatVoltReal0V25    25
#define cBatVoltReal0V3     30
#define cBatVoltReal0V4     40
#define cBatVoltReal0V5     50
#define cBatVoltReal1V      100
#define cBatVoltReal1V3     130
#define cBatVoltReal2V      200
#define cBatVoltReal2V12    212
#define cBatVoltReal2V50    250
#define cBatVoltReal2V63    263
#define cBatVoltReal2V7     270
#define cBatVoltReal2V75    275
#define cBatVoltReal2V8     280
#define cBatVoltReal2V87    287
#define cBatVoltReal3V      300
#define cBatVoltReal3V2     320
#define cBatVoltReal3V25    325
#define cBatVoltReal3V3     330
#define cBatVoltReal3V37    337
#define cBatVoltReal3V4     340
#define cBatVoltReal3V55    355
#define cBatVoltReal3V6     360
#define cBatVoltReal3V65    365
#define cBatVoltReal3V75    375
#define cBatVoltReal4V      400
#define cBatVoltReal5V3     530
#define cBatVoltReal5V6     560
#define cBatVoltReal6V4     640
#define cBatVoltReal8V      800
#define cBatVoltReal8V5     850
#define cBatVoltReal9V6     960
#define cBatVoltReal10V     1000
#define cBatVoltReal10V1    1010
#define cBatVoltReal10V2    1020
#define cBatVoltReal10V5    1050
#define cBatVoltReal10V6    1060
#define cBatVoltReal10V7    1070
#define cBatVoltReal11V     1100
#define cBatVoltReal11V2    1120
#define cBatVoltReal11V5    1150
#define cBatVoltReal12V     1200
#define cBatVoltReal12V1    1210
#define cBatVoltReal12V2    1220
#define cBatVoltReal12V3    1230
#define cBatVoltReal12V5    1250
#define cBatVoltReal13V     1300
#define cBatVoltReal13V5    1350
#define cBatVoltReal13V6    1360
#define cBatVoltReal14V     1400
#define cBatVoltReal14V1    1410
#define cBatVoltReal14V4    1440
#define cBatVoltReal14V6    1460
#define cBatVoltReal15V     1500
#define cBatVoltReal15V5    1550
#define cBatVoltReal16V     1600
#define cBatVoltReal16V4    1640
#define cBatVoltReal20V     2000
#define cBatVoltReal32V     3200
#define cBatVoltReal34V     3400
#define cBatVoltReal35V     3500
#define cBatVoltReal40V     4000
#define cBatVoltReal42V     4200
#define cBatVoltReal44V     4400
#define cBatVoltReal46V     4600
#define cBatVoltReal48V     4800
#define cBatVoltReal54V     5400
#define cBatVoltReal58V     5800
#define cBatVoltReal60V     6000
#define cBatVoltReal62V     6200
#define cBatVoltReal64V     6400

// Bus volt define
#define cBusVoltReal1V          10
#define cBusVoltReal5V          50
#define cBusVoltReal10V         100
#define cBusVoltReal20V         200
#define cBusVoltReal30V         300
#define cBusVoltReal40V         400
#define cBusVoltReal50V         500
#define cBusVoltReal80V         800
#define cBusVoltReal100V        1000
#define cBusVoltReal150V        1500
#define cBusVoltReal190V        1900
#define cBusVoltReal200V        2000
#define cBusVoltReal240V        2400
#define cBusVoltReal250V        2500
#define cBusVoltReal280V        2800
#define cBusVoltReal285V        2850
#define cBusVoltReal290V        2900
#define cBusVoltReal300V        3000
#define cBusVoltReal340V        3400
#define cBusVoltReal350V        3500
#define cBusVoltReal360V        3600
#define cBusVoltReal370V        3600
#define cBusVoltReal380V        3800
#define cBusVoltReal400V        4000
#define cBusVoltReal420V        4200
#define cBusVoltReal430V        4300
#define cBusVoltReal440V        4400
#define cBusVoltReal450V        4500
#define cBusVoltReal460V        4600
#define cBusVoltReal465V        4650
#define cBusVoltReal470V        4700
#define cBusVoltReal475V        4750
#define cBusVoltReal480V        4800
#define cBusVoltReal485V        4850
#define cBusVoltReal490V        4900
#define cBusVoltReal500V        5000
#define cBusVoltReal510V        5100
#define cBusVoltReal520V        5200
#define cBusVoltReal550V        5500
#define cBusVoltReal560V        5600
#define cBusVoltReal570V        5700
#define cBusVoltReal580V        5800
#define cBusVoltReal600V        6000

// Ac Inv volt define
#define cAcVoltReal10V      100
#define cAcVoltReal20V      200
#define cAcVoltReal30V      300
#define cAcVoltReal50V      500
#define cAcVoltReal60V      600
#define cAcVoltReal65V      650
#define cAcVoltReal80V      800
#define cAcVoltReal90V      900
#define cAcVoltReal95V      950
#define cAcVoltReal100V     1000
#define cAcVoltReal110V     1100
#define cAcVoltReal115V     1150
#define cAcVoltReal120V     1200
#define cAcVoltReal127V     1270
#define cAcVoltReal135V     1350
#define cAcVoltReal140V     1400
#define cAcVoltReal150V     1500
#define cAcVoltReal170V     1700
#define cAcVoltReal190V     1900
#define cAcVoltReal220V     2200
#define cAcVoltReal230V     2300
#define cAcVoltReal240V     2400
#define cAcVoltReal253V     2530
#define cAcVoltReal270V     2700
#define cAcVoltReal287V5    2875
#define cAcVoltReal280V     2800
#define cAcVoltReal290V     2900
#define cAcVoltReal300V     3000
#define cAcVoltReal305V     3050

// Line volt define
#define cLineVolt305V       3050
#define cLineVolt300V       3000
#define cLineVolt290V       2900
#define cLineVolt280V       2800
#define cLineVolt275V       2750
#define cLineVolt270V       2700
#define cLineVolt264V       2650
#define cLineVolt264V       2640
#define cLineVolt255V       2550
#define cLineVolt254V       2540
#define cLineVolt240V       2400
#define cLineVolt210V       2100
#define cLineVolt253V       2530
#define cLineVolt200V       1900
#define cLineVolt190V       1900
#define cLineVolt180V       1800
#define cLineVolt176V       1760
#define cLineVolt170V       1700
#define cLineVolt160V       1600
#define cLineVolt150V       1500
#define cLineVolt140V       1400
#define cLineVolt135V       1350
#define cLineVolt100V       1000
#define cLineVolt95V        950
#define cLineVolt90V        900
#define cLineVolt85V        850
#define cLineVolt80V        800
#define cLineVolt70V        700
#define cLineVolt65V        650
#define cLineVolt60V        600

// Line freq define
#define cLineFreq65Hz       6500
#define cLineFreq63Hz       6300
#define cLineFreq60Hz       6000
#define cLineFreq55Hz       5500
#define cLineFreq54Hz       5400
#define cLineFreq53Hz       5300
#define cLineFreq52Hz       5200
#define cLineFreq51Hz       5100
#define cLineFreq50Hz2      5020
#define cLineFreq50Hz1      5010
#define cLineFreq50Hz       5000
#define cLineFreq49Hz9      4990
#define cLineFreq49Hz8      4980
#define cLineFreq48Hz5      4850
#define cLineFreq47Hz5      4750
#define cLineFreq45Hz       4500
#define cLineFreq42Hz       4200
#define cLineFreq40Hz       4000

// DCDC curr define
#define cDCDC5A            	500
#define cDCDC10A            1000
#define cDCDC15A            1500
#define cDCDC16A            1600
#define cDCDC20A            2000
#define cDCDC30A            3000
#define cDCDC35A            3500

// Inv curr define
#define cInv01A             100
#define cInv02A             200
#define cInv05A             500
#define cInv08A             800
#define cInv10A             1000
#define cInv12A             1200
#define cInv15A             1500
#define cInv16A             1600
#define cInv18A             1800
#define cInv20A             2000
#define cInv25A             2500
#define cInv30A             3000
#define cInv35A             3500
#define cInv40A             4000
#define cInv45A             4500
#define cInv60A             6000

// Op curr define
#define cOp5A               500
#define cOp7A5              750
#define cOp8A              	800
#define cOp8A75             875
#define cOp9A50             950
#define cOp10A              1000
#define cOp11A              1100
#define cOp12A              1200
#define cOp14A              1400
#define cOp15A              1500
#define cOp22A              2200
#define cOp24A              2400
#define cOp30A              3000

#define cDelay20ms          200
#define cDelay15ms          150
#define cDelay10ms          100
#define cDelay8ms           80
#define cDelay7ms           70
#define cDelay6ms           60
#define cDelay5ms           50
#define cDelay2ms           20
#define cDelay1ms           10


#define cCPU_FREQ           150000000
#define cPLL_FREQ_DIV       150
#define cPeriodMax          cCPU_FREQ/cPLL_FREQ_DIV
#define cPeriod35Hz         ((cPeriodMax+18)/35)
#define cPeriod38Hz         ((cPeriodMax+19)/38)
#define cPeriod50Hz         ((cPeriodMax+25)/50)
#define cPeriod60Hz         ((cPeriodMax+30)/60)
#define cPeriod67Hz         ((cPeriodMax+34)/67)
#define cPeriod70Hz         ((cPeriodMax+35)/70)   

#define cFreq50hzConst		0
#define cFreq60hzConst		1

#define cFBWait				0
#define cFBInvOpenLoop		1
#define cFBInvCtrlVolt		2
#define cFBInvCtrlBus		3


#define cSFTRlyDelayTime            50
#define cInvRlyDelayTime            50
#define cBatSwitchLineSCRDelayTime  0
#define cSFTRlySCRDelayTime         2
#define cOPRlySCRDelayTime          2
#define cBatSwitchLineDelayTime     80
#define cGRIDRlyDelayTime           0
#define cOPRlyDelayTime             50

#define cTransformerRatio64	         640		// 推挽变比 0.1
//#define cTransformerRatio360         360		// 推挽变比 0.1
//#define cTransformerRatio330         330		// 推挽变比 0.1
//#define cTransformerRatio180         180		// 推挽变比 0.1
//#define cTransformerRatio165         165		// 推挽变比 0.1
//#define cTransformerRatio155         155		// 推挽变比 0.1
//#define cTransformerRatio      	   	 330		// 推挽变比 0.1

#define cBatSerialPcs               1			// IVDM3224 = 2
#define cInt_DCDCCurrPrtPnt         cDCDC20A
#define cMaxInvFeedCntlCurr         100    		// 22.62A(3200W*1.414/200V=15A*1.414=22.62A)	// 0.01A
#define cMaxInvFeedCntlCurr1        71//20//226    		// 22.6A(3200W*1.414/200V=15A*1.414=22.6A)		// 0.1A

#define cMaxACInputCurr             500    		// RLY=
#define cMaxACInputPower            1000    	// 市电最大功率 230V*30A=6900W
#define cMaxPVBatChgCurr            230			// 控输入电流，HOPE2000是20A额定
#define cDCDCCntlCurrntLimit        3200		// 1600    // 15*100 15A
#define cBatDischgCurrMax           160    		// 160A
#define cLiBatActChgCurr            5	      	// 5A
#define cInvWattMax                 1000		// 1000W
#define cInvVAMax					1000		// 1000W

#define PhaseR          0
#define PhaseS          1
#define PhaseT          2

#define cDCDCChgDischgDis           0x00
#define cDCDCChgEnable              0x01
#define cDCDCDischgEnable           0x02

//电池类型
#define cBatType_AGM						0
#define cBatType_FLD						1
#define cBatType_USER						2
#define cBatType_LIB						3
#define cBatType_MAX						3

//电池模式 0:电池相关的使用SOC，1:使用电压，2:无电池
#define cBatMode_SOC						0
#define cBatMode_Volt						1
#define cBatMode_NULL						2
#define cBatMode_MAX						2

#define cChargeEnable						0x0080	//充电允许
#define cDischargeEnable					0x0040	//放电允许

// 温度降额、电压降额的宏定义放这里	// 0.1°
#define cHsTemp01C					10
#define cHsTemp10C					100
#define cHsTemp15C					150
#define cHsTemp50C					500
#define cHsTemp55C					550
#define cHsTemp60C					600
#define cHsTemp65C					650
#define cHsTemp66C					660
#define cHsTemp70C					700
#define cHsTemp72C					720
#define cHsTemp75C					750
#define cHsTemp77C					770
#define cHsTemp78C					780
#define cHsTemp79C					790
#define cHsTemp80C					800
#define cHsTemp82C					820
#define cHsTemp83C					830
#define cHsTemp84C					840
#define cHsTemp85C					850
#define cHsTemp86C					860
#define cHsTemp87C					870
#define cHsTemp89C					890
#define cHsTemp90C					900
#define cHsTemp91C					910
#define cHsTemp94C					940
#define cHsTemp95C					950
#define cHsTemp99C					990
#define cHsTemp114C					1140
#define cHsTemp119C					1190
#define cHsTemp124C					1240
#define cHsTemp129C					1290


#define cBatVoltStartDerat			cBatVoltReal5V6		// 0.1V
#define cBatVoltEndDerat			cBatVoltReal5V3		// 0.1V

#define cOPWattPercent40			40
#define cOPWattPercent50			50

#define cMpptBatCurr0A				0
#define cMpptBatCurr01A				10
#define cMpptBatCurr02A				20
#define cMpptBatCurr05A				50
#define cMpptBatCurr06A				60
#define cMpptBatCurr10A				100
#define cMpptBatCurr15A				150
#define cMpptBatCurr16A				160
#define cMpptBatCurr20A				200
#define cMpptBatCurr30A				300
#define cMpptBatCurr35A				350
#define cMpptBatCurr40A				400
#define cMpptBatCurr50A				500
#define cMpptBatCurr60A				600
#define cMpptBatCurr65A				650
#define cMpptBatCurr70A				700
#define cMpptBatCurr100A			1000
#define cMpptBatCurr150A			1500
#define cMpptBatCurrMax				cMpptBatCurr100A

#define cMpptPVCurr10A				100
#define cMpptPVCurr20A				200
#define cMpptPVCurr22A				220
#define cMpptPVCurr23A				230
#define cMpptPVCurr35A				350
#define cMpptPVCurrMax				cMpptPVCurr23A

#define cMpptPvVolt10V				1000
#define cMpptPvVolt11V				1100
#define cMpptPvVolt12V				1200
#define cMpptPvVolt20V				2000
#define cMpptPvVolt30V				3000
#define cMpptPvVolt40V				4000
#define cMpptPvVolt50V				5000
#define cMpptPvVolt55V				5500
#define cMpptPvVolt60V				6000
#define cMpptPvVolt90V				9000
#define cMpptPvVolt95V				9500
#define cMpptPvVolt105V				10500
#define cMpptPvVolt145V				14500
#define cMpptPvVoltMax				cMpptPvVolt55V



//for test 没删掉的原因是有别的地方调用了，暂时懒得改
#define cDsgPriorityLINE			0		// 市电 --> (PV + BAT)				
#define cDsgPriorityPV				1		// (PV + BAT) --> 市电   PV不在则切市电
#define cDsgPriorityBAT				2		// (PV + BAT) --> 市电   BAT不在则切市电

// 逆变器新工作模式(能量调度)
#define cInvWorkUSB					0
#define cInvWorkSUB					1
#define cInvWorkSBU					2

// 逆变器并网能量方向
#define cInvFeedWorkAuto			0		// 并网充放电自动计算(default)
#define cInvFeedWorkOnlyChg			1		// 仅充电，充电功率手动下发
#define cInvFeedWorkOnlyDsg			2		// 仅放电，放电功率手动下发

#define cInvWorSUBGridDirChg		0		// SUB模式下，市电方向充电
#define cInvWorSUBGridDirDsg		1		// SUB模式下，市电方向放电

#define cAPL						0
#define cUPS						1
#define cGEN						2

// 充电状态
#define		cChgModeNO					0
#define 	cChgModeCC					1
#define 	cChgModeCV					2
#define 	cChgModeFloat				3
#define 	cChgModeEQ					4	// Equalize	

// 离网转市电时间
#define cBatToLIneTimeSwitch0S		0
#define cBatToLIneTimeSwitch1S		1
#define cBatToLIneTimeSwitch5S		5
#define cBatToLIneTimeSwitch10S		10
#define cBatToLIneTimeSwitch60S		60
#define cBatToLIneTimeSwitchMin		cBatToLIneTimeSwitch0S
#define cBatToLIneTimeSwitchMax		cBatToLIneTimeSwitch60S

#define cLineVoltStartDerat			cLineVolt176V		// 0.1V
#define cLineVoltEndDerat			cLineVolt90V		// 0.1V

/********************************************************************************
* Routines' implementations                                                     *
********************************************************************************/
extern void sOSTimerStop(void);
extern void sOSTimerStart(void);

/********************************************************************************
* Output interface Routines                                                     *
********************************************************************************/


/********************************************************************************
* Input interface Routines                                                      *
********************************************************************************/


#endif  // __MAIN_H__

