/*================================================================================================*
 *FileName:  vram_map.h																																					*
 *Description: 		
 *   There are two display modes if display device is LCD, One is bit mode,another is figure mode.
 * In bit mode, the display cell is a segment. In figure mode,the display cell include N(N=7,9,16)
 * segments.																																														*
 *================================================================================================*/
       

#ifndef			__VRAMMAP_H__
#define			__VRAMMAP_H__


//amy #include  "def_data_type.h"                                                
#include "display_driver.h" 

//definition for display direction
#define cDIR_HORIZONTAL             0
#define cDIR_VERTICAL               1


//========================================================================
// definition for character index
//========================================================================
enum CHAR_INDEX
{
    char0 = 0,       
    char1,       
    char2,       
    char3,       
    char4,       
    char5,       
    char6,       
    char7,       
    char8,       
    char9,       
    charA,       
    charB,       
    charC,       
    charD,       
    charE,       
    charF,       
    charG,       
    charH,       
    charI,       
    charJ,       
    charK,       
    charL,       
    charM,       
    charN,       
    charO,       
    charP,       
    charQ,           
    charR,       
    charS,       
    charT,       
    charU,       
    charV,       
    charW,       
    charX,       
    charY,       
    charZ,       
    cCharSpace,  
    cCharLength  
};
//========================================================================
// definition for character code (13 segments)
//========================================================================
#define cSeg7CodeA      0x77
#define cSeg7CodeB      0x7C
#define cSeg7CodeC      0x39
#define cSeg7CodeD      0x5E
#define cSeg7CodeE      0x79
#define cSeg7CodeF      0x71
#define cSeg7CodeG      0x3D
#define cSeg7CodeH      0x76
#define cSeg7CodeI      0x30
#define cSeg7CodeJ      0x1E
#define cSeg7CodeK      0x70
#define cSeg7CodeL      0x38
#define cSeg7CodeM      0x54//0x4F
#define cSeg7CodeN      0x37//0x54
#define cSeg7CodeO      0x3F//0x5C
#define cSeg7CodeP      0x73
#define cSeg7CodeQ      0x67
#define cSeg7CodeR      0x70//0x5F
#define cSeg7CodeS      0x6D
#define cSeg7CodeT      0x78
#define cSeg7CodeU      0x3E
#define cSeg7CodeV      0x62
#define cSeg7CodeW      0x1C//0x49
#define cSeg7CodeX      0x64
#define cSeg7CodeY      0x6E//0x46
#define cSeg7CodeZ      0x5B//0x49
//========================================================================
//definition for character code  table
//INT16U  a:1;  //0
//INT16U  b:1;  //1
//INT16U  c:1;  //2
//INT16U  d:1;  //3
//INT16U  e:1;  //4
//INT16U  f:1;  //5
//INT16U  g:1;  //6	
//INT16U  i:1;  //7
//INT16U  j:1;  //8
//INT16U  k:1;  //9
//INT16U  l:1;  //10
//INT16U  m:1;  //11
//INT16U  h:1;  //12
#define cSeg13Code0      0x1EBF	// 0001 1110 1011 1111
#define cSeg13Code1      0x0606	// 0000 0110 0000 0110
#define cSeg13Code2      0x0BDB	// 0000 1011 1101 1011
#define cSeg13Code3      0x0FCF	// 0000 1111 1100 1111
#define cSeg13Code4      0x07E6	// 0000 0111 1110 0110
#define cSeg13Code5      0x0BED	// 0000 1011 1110 1101
#define cSeg13Code6      0x1BFD	// 0001 1011 1111 1101
#define cSeg13Code7      0x0607	// 0000 0110 0000 0111
#define cSeg13Code8      0x1FFF	// 0001 1111 1111 1111
#define cSeg13Code9      0x0FEF	// 0000 1111 1110 1111
#define cSeg13CodeSpace  0x0000

const INT16U Seg13CodeTab[cCharLength]=
{
	// 数字可以正常使用
    cSeg13Code0,cSeg13Code1,cSeg13Code2,cSeg13Code3,cSeg13Code4,cSeg13Code5,cSeg13Code6,cSeg13Code7,cSeg13Code8,cSeg13Code9,

	// 字母还没有按照13段数码管取模，显示会有异常
    cSeg7CodeA,cSeg7CodeB,cSeg7CodeC,cSeg7CodeD,cSeg7CodeE,cSeg7CodeF,cSeg7CodeG,cSeg7CodeH,cSeg7CodeI,cSeg7CodeJ,
    cSeg7CodeK,cSeg7CodeL,cSeg7CodeM,cSeg7CodeN,cSeg7CodeO,cSeg7CodeP,cSeg7CodeQ,cSeg7CodeR,cSeg7CodeS,cSeg7CodeT,
    cSeg7CodeU,cSeg7CodeV,cSeg7CodeW,cSeg7CodeX,cSeg7CodeY,cSeg7CodeZ,cSeg13CodeSpace
};


//============================================================================
// definition for LCD display bit(BIT mode)
//============================================================================
enum LCD_BIT
{
	//SEG1
	cBIT_S21,
	cBIT_13SEG9_F,
	cBIT_13SEG9_H,
	cBIT_13SEG9_I,
	cBIT_13SEG9_G,
	cBIT_13SEG9_E,
	cBIT_13SEG9_M,
	cBIT_13SEG9_D,

	//SEG2
	cBIT_S20,
	cBIT_S19,
	cBIT_13SEG9_A,
	cBIT_13SEG9_B,
	cBIT_13SEG9_J,
	cBIT_13SEG9_K,
	cBIT_13SEG9_L,
	cBIT_13SEG9_C,

	//SEG3
	cBIT_S18,
	cBIT_13SEG10_F,
	cBIT_13SEG10_H,
	cBIT_13SEG10_I,
	cBIT_13SEG10_G,
	cBIT_13SEG10_E,
	cBIT_13SEG10_M,
	cBIT_13SEG10_D,

	//SEG4
	cBIT_S16,
	cBIT_S17,
	cBIT_13SEG10_A,
	cBIT_13SEG10_B,
	cBIT_13SEG10_J,
	cBIT_13SEG10_K,
	cBIT_13SEG10_L,
	cBIT_13SEG10_C,

	//SEG5
	cBIT_S15,
	cBIT_13SEG11_F,
	cBIT_13SEG11_H,
	cBIT_13SEG11_I,
	cBIT_13SEG11_G,
	cBIT_13SEG11_E,
	cBIT_13SEG11_M,
	cBIT_13SEG11_D,

	//SEG6
	cBIT_S11,
	cBIT_S14,
	cBIT_13SEG11_A,
	cBIT_13SEG11_B,
	cBIT_13SEG11_J,
	cBIT_13SEG11_K,
	cBIT_13SEG11_L,
	cBIT_13SEG11_C,

	//SEG7
	cReserved0,
	cBIT_13SEG5_F,
	cBIT_13SEG5_H,
	cBIT_13SEG5_I,
	cBIT_13SEG5_G,
	cBIT_13SEG5_E,
	cBIT_13SEG5_M,
	cBIT_13SEG5_D,

	//SEG8
	cReserved2,
	cBIT_S5,
	cBIT_13SEG5_A,
	cBIT_13SEG5_B,
	cBIT_13SEG5_J,
	cBIT_13SEG5_K,
	cBIT_13SEG5_L,
	cBIT_13SEG5_C,

	//SEG9
	cReserved3,
	cBIT_13SEG6_F,
	cBIT_13SEG6_H,
	cBIT_13SEG6_I,
	cBIT_13SEG6_G,
	cBIT_13SEG6_E,
	cBIT_13SEG6_M,
	cBIT_13SEG6_D,

	//SEG10
	cBIT_S7,
	cBIT_13SEG6_A,
	cBIT_13SEG6_B,
	cBIT_13SEG6_J,
	cBIT_13SEG6_K,
	cBIT_13SEG6_L,
	cBIT_13SEG6_C,
	cBIT_S27,

	//SEG11
	cReserved4,
	cBIT_13SEG7_F,
	cBIT_13SEG7_H,
	cBIT_13SEG7_I,
	cBIT_13SEG7_G,
	cBIT_13SEG7_E,
	cBIT_13SEG7_M,
	cBIT_13SEG7_D,

	//SEG12
	cBIT_S6,
	cBIT_13SEG7_A,
	cBIT_13SEG7_B,
	cBIT_13SEG7_J,
	cBIT_13SEG7_K,
	cBIT_13SEG7_L,
	cBIT_13SEG7_C,
	cBIT_S10,

	//SEG13
	cReserved5,
	cBIT_13SEG8_F,
	cBIT_13SEG8_H,
	cBIT_13SEG8_I,
	cBIT_13SEG8_G,
	cBIT_13SEG8_E,
	cBIT_13SEG8_M,
	cBIT_13SEG8_D,

	//SEG14
	cBIT_S8,
	cBIT_13SEG8_A,
	cBIT_13SEG8_B,
	cBIT_13SEG8_J,
	cBIT_13SEG8_K,
	cBIT_13SEG8_L,
	cBIT_13SEG8_C,
	cBIT_S9,
/*
	//SEG15
	cReserved6,
	cReserved7,
	cReserved8,
	cReserved9,
	cReserved10,
	cReserved11,
	cReserved12,
	cReserved13,

	//SEG16
	cReserved14,
	cReserved15,
	cReserved16,
	cReserved17,
	cReserved18,
	cReserved19,
	cReserved20,
	cReserved21,

	//SEG17
	cReserved22,
	cReserved23,
	cReserved24,
	cReserved25,
	cReserved26,
	cReserved27,
	cReserved28,
	cReserved29,

	//SEG18
	cReserved30,
	cReserved31,
	cReserved32,
	cReserved33,
	cReserved34,
	cReserved35,
	cReserved36,
	cReserved37,

	//SEG19
	cReserved38,
	cReserved39,
	cReserved40,
	cReserved41,
	cReserved42,
	cReserved43,
	cReserved44,
	cReserved45,

	//SEG20
	cReserved46,
	cReserved47,
	cReserved48,
	cReserved49,
	cReserved50,
	cReserved51,
	cReserved52,
	cReserved53,

	//SEG21
	cReserved54,
	cReserved55,
	cReserved56,
	cReserved57,
	cReserved58,
	cReserved59,
	cReserved60,
	cReserved61,

	//SEG22
	cReserved62,
	cReserved63,
	cReserved64,
	cReserved65,
	cReserved66,
	cReserved67,
	cReserved68,
	cReserved69,

	//SEG23
	cReserved70,
	cReserved71,
	cReserved72,
	cReserved73,
	cReserved74,
	cReserved75,
	cReserved76,
	cReserved77,

	//SEG24
	cReserved78,
	cReserved79,
	cReserved80,
	cReserved81,
	cReserved82,
	cReserved83,
	cReserved84,
	cReserved85,

	//SEG25
	cReserved86,
	cReserved87,
	cReserved88,
	cReserved89,
	cReserved90,
	cReserved91,
	cReserved92,
	cReserved93,

	//SEG26
	cReserved94,
	cReserved95,
	cReserved96,
	cReserved97,
	cReserved98,
	cReserved99,
	cReserved100,
	cReserved101,

	//SEG27
	cReserved102,
	cReserved103,
	cReserved104,
	cReserved105,
	cReserved106,
	cReserved107,
	cReserved108,
	cReserved109,

	//SEG28
	cReserved110,
	cReserved111,
	cReserved112,
	cReserved113,
	cReserved114,
	cReserved115,
	cReserved116,
	cReserved117,

	//SEG29
	cReserved118,
	cReserved119,
	cReserved120,
	cReserved121,
	cReserved122,
	cReserved123,
	cReserved124,
	cReserved125,

	//SEG30
	cReserved126,
	cReserved127,
	cReserved128,
	cReserved129,
	cReserved130,
	cReserved131,
	cReserved132,
	cReserved133,
*/
	//SEG31
	cBIT_S12,
	cBIT_S4,
	cBIT_13SEG13_C,
	cBIT_13SEG13_L,
	cBIT_13SEG13_K,
	cBIT_13SEG13_J,
	cBIT_13SEG13_B,
	cBIT_13SEG13_A,

	//SEG32
	cBIT_S13,
	cBIT_13SEG13_D,
	cBIT_13SEG13_M,
	cBIT_13SEG13_E,
	cBIT_13SEG13_G,
	cBIT_13SEG13_I,
	cBIT_13SEG13_H,
	cBIT_13SEG13_F,

	//SEG33
	cReserved134,
	cBIT_14BC,		// SOC显示的 1
	cBIT_13SEG12_C,
	cBIT_13SEG12_L,
	cBIT_13SEG12_K,
	cBIT_13SEG12_J,
	cBIT_13SEG12_B,
	cBIT_13SEG12_A,

	//SEG34
	cReserved135,
	cBIT_13SEG12_D,
	cBIT_13SEG12_M,
	cBIT_13SEG12_E,
	cBIT_13SEG12_G,
	cBIT_13SEG12_I,
	cBIT_13SEG12_H,
	cBIT_13SEG12_F,

	//SEG35
	cBIT_S3,
	cBIT_13SEG4_C,
	cBIT_13SEG4_L,
	cBIT_13SEG4_K,
	cBIT_13SEG4_J,
	cBIT_13SEG4_B,
	cBIT_13SEG4_A,
	cBIT_S2,

	//SEG36
	cBIT_S22,
	cBIT_13SEG4_D,
	cBIT_13SEG4_M,
	cBIT_13SEG4_E,
	cBIT_13SEG4_G,
	cBIT_13SEG4_I,
	cBIT_13SEG4_H,
	cBIT_13SEG4_F,

	//SEG37
	cBIT_S23,
	cBIT_13SEG3_C,
	cBIT_13SEG3_L,
	cBIT_13SEG3_K,
	cBIT_13SEG3_J,
	cBIT_13SEG3_B,
	cBIT_13SEG3_A,
	cBIT_S1,

	//SEG38
	cReserved136,
	cBIT_13SEG3_D,
	cBIT_13SEG3_M,
	cBIT_13SEG3_E,
	cBIT_13SEG3_G,
	cBIT_13SEG3_I,
	cBIT_13SEG3_H,
	cBIT_13SEG3_F,

	//SEG39
	cReserved137,
	cBIT_13SEG2_C,
	cBIT_13SEG2_L,
	cBIT_13SEG2_K,
	cBIT_13SEG2_J,
	cBIT_13SEG2_B,
	cBIT_13SEG2_A,
	cReserved138,

	//SEG40
	cReserved139,
	cBIT_13SEG2_D,
	cBIT_13SEG2_M,
	cBIT_13SEG2_E,
	cBIT_13SEG2_G,
	cBIT_13SEG2_I,
	cBIT_13SEG2_H,
	cBIT_13SEG2_F,

	//SEG41
	cReserved140,
	cBIT_13SEG1_C,
	cBIT_13SEG1_L,
	cBIT_13SEG1_K,
	cBIT_13SEG1_J,
	cBIT_13SEG1_B,
	cBIT_13SEG1_A,
	cReserved141,

	//SEG42
	cReserved142,
	cBIT_13SEG1_D,
	cBIT_13SEG1_M,
	cBIT_13SEG1_E,
	cBIT_13SEG1_G,
	cBIT_13SEG1_I,
	cBIT_13SEG1_H,
	cBIT_13SEG1_F
};

//============================================================================
// definition for LCD display cell(figure mode)
//============================================================================
//Figure type
#define     cFIG_TYPE_13        13

//start address in FigureSEG_TAB array
#define     FIG_7SEG_POS        0


//definition index for figure
enum SEG13_INDEX
{
    FIG1_13SEG = 0,
    FIG2_13SEG,
    FIG3_13SEG,
    FIG4_13SEG,
    FIG5_13SEG,
    FIG6_13SEG,
    FIG7_13SEG, 
    FIG8_13SEG,     
    FIG9_13SEG,  
    FIG10_13SEG,
    FIG11_13SEG, 
    FIG12_13SEG, 
    FIG13_13SEG
};

//Figure SEG table
const INT8U Figure13SEG_TAB[FIG_13SEG_TOTAL * 13] =
{
	cBIT_13SEG1_A,cBIT_13SEG1_B,cBIT_13SEG1_C,cBIT_13SEG1_D,cBIT_13SEG1_E,cBIT_13SEG1_F,cBIT_13SEG1_G,cBIT_13SEG1_I,cBIT_13SEG1_J,cBIT_13SEG1_K,cBIT_13SEG1_L,cBIT_13SEG1_M,cBIT_13SEG1_H,
	cBIT_13SEG2_A,cBIT_13SEG2_B,cBIT_13SEG2_C,cBIT_13SEG2_D,cBIT_13SEG2_E,cBIT_13SEG2_F,cBIT_13SEG2_G,cBIT_13SEG2_I,cBIT_13SEG2_J,cBIT_13SEG2_K,cBIT_13SEG2_L,cBIT_13SEG2_M,cBIT_13SEG2_H,
	cBIT_13SEG3_A,cBIT_13SEG3_B,cBIT_13SEG3_C,cBIT_13SEG3_D,cBIT_13SEG3_E,cBIT_13SEG3_F,cBIT_13SEG3_G,cBIT_13SEG3_I,cBIT_13SEG3_J,cBIT_13SEG3_K,cBIT_13SEG3_L,cBIT_13SEG3_M,cBIT_13SEG3_H,
	cBIT_13SEG4_A,cBIT_13SEG4_B,cBIT_13SEG4_C,cBIT_13SEG4_D,cBIT_13SEG4_E,cBIT_13SEG4_F,cBIT_13SEG4_G,cBIT_13SEG4_I,cBIT_13SEG4_J,cBIT_13SEG4_K,cBIT_13SEG4_L,cBIT_13SEG4_M,cBIT_13SEG4_H,
	cBIT_13SEG5_A,cBIT_13SEG5_B,cBIT_13SEG5_C,cBIT_13SEG5_D,cBIT_13SEG5_E,cBIT_13SEG5_F,cBIT_13SEG5_G,cBIT_13SEG5_I,cBIT_13SEG5_J,cBIT_13SEG5_K,cBIT_13SEG5_L,cBIT_13SEG5_M,cBIT_13SEG5_H,
	cBIT_13SEG6_A,cBIT_13SEG6_B,cBIT_13SEG6_C,cBIT_13SEG6_D,cBIT_13SEG6_E,cBIT_13SEG6_F,cBIT_13SEG6_G,cBIT_13SEG6_I,cBIT_13SEG6_J,cBIT_13SEG6_K,cBIT_13SEG6_L,cBIT_13SEG6_M,cBIT_13SEG6_H,
	cBIT_13SEG7_A,cBIT_13SEG7_B,cBIT_13SEG7_C,cBIT_13SEG7_D,cBIT_13SEG7_E,cBIT_13SEG7_F,cBIT_13SEG7_G,cBIT_13SEG7_I,cBIT_13SEG7_J,cBIT_13SEG7_K,cBIT_13SEG7_L,cBIT_13SEG7_M,cBIT_13SEG7_H,
	cBIT_13SEG8_A,cBIT_13SEG8_B,cBIT_13SEG8_C,cBIT_13SEG8_D,cBIT_13SEG8_E,cBIT_13SEG8_F,cBIT_13SEG8_G,cBIT_13SEG8_I,cBIT_13SEG8_J,cBIT_13SEG8_K,cBIT_13SEG8_L,cBIT_13SEG8_M,cBIT_13SEG8_H,
	cBIT_13SEG9_A,cBIT_13SEG9_B,cBIT_13SEG9_C,cBIT_13SEG9_D,cBIT_13SEG9_E,cBIT_13SEG9_F,cBIT_13SEG9_G,cBIT_13SEG9_I,cBIT_13SEG9_J,cBIT_13SEG9_K,cBIT_13SEG9_L,cBIT_13SEG9_M,cBIT_13SEG9_H,
	cBIT_13SEG10_A,cBIT_13SEG10_B,cBIT_13SEG10_C,cBIT_13SEG10_D,cBIT_13SEG10_E,cBIT_13SEG10_F,cBIT_13SEG10_G,cBIT_13SEG10_I,cBIT_13SEG10_J,cBIT_13SEG10_K,cBIT_13SEG10_L,cBIT_13SEG10_M,cBIT_13SEG10_H,
	cBIT_13SEG11_A,cBIT_13SEG11_B,cBIT_13SEG11_C,cBIT_13SEG11_D,cBIT_13SEG11_E,cBIT_13SEG11_F,cBIT_13SEG11_G,cBIT_13SEG11_I,cBIT_13SEG11_J,cBIT_13SEG11_K,cBIT_13SEG11_L,cBIT_13SEG11_M,cBIT_13SEG11_H,
	cBIT_13SEG12_A,cBIT_13SEG12_B,cBIT_13SEG12_C,cBIT_13SEG12_D,cBIT_13SEG12_E,cBIT_13SEG12_F,cBIT_13SEG12_G,cBIT_13SEG12_I,cBIT_13SEG12_J,cBIT_13SEG12_K,cBIT_13SEG12_L,cBIT_13SEG12_M,cBIT_13SEG12_H,
	cBIT_13SEG13_A,cBIT_13SEG13_B,cBIT_13SEG13_C,cBIT_13SEG13_D,cBIT_13SEG13_E,cBIT_13SEG13_F,cBIT_13SEG13_G,cBIT_13SEG13_I,cBIT_13SEG13_J,cBIT_13SEG13_K,cBIT_13SEG13_L,cBIT_13SEG13_M,cBIT_13SEG13_H
};  

const INT8U SOC_TAB[10] =
{
	cBIT_S21,cBIT_S20,cBIT_S19,cBIT_S18,cBIT_S17,cBIT_S16,cBIT_S15,cBIT_S14,cBIT_S13,cBIT_S12
}; 

//==================================================================================================
//definiton for figure struct
//==================================================================================================
typedef union
{
    INT16U  bByte;
    struct
    {       
       INT16U  a:1;  //0
       INT16U  b:1;  //1
       INT16U  c:1;  //2
       INT16U  d:1;  //3
       INT16U  e:1;  //4
       INT16U  f:1;  //5
       INT16U  g:1;  //6                                        
       INT16U  i:1;  //7
	   INT16U  j:1;  //8
       INT16U  k:1;  //9
       INT16U  l:1;  //10
       INT16U  m:1;  //11
       INT16U  h:1;  //12
    }Seg;
}Seg13_Field;   
//==================================================================================================
//definiton for display macro
//==================================================================================================



#endif			//__VRAMMAP_H__
