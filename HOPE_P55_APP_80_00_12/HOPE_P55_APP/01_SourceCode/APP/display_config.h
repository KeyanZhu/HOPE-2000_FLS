/*================================================================================================*
 *FileName:  Display_config.h																																					*
 *																																																*
 *================================================================================================*/
#ifndef			__DISPLAY_CONFIG_H__
#define			__DISPLAY_CONFIG_H__

//configation for display device 
#define         CF_LCD		


//============================================================================
// configuration for LCD
//============================================================================
#ifdef     CF_LCD

//the size of view buffer
#define VRAMSIZE				255

//display status              
#define     DISPLAY_ON      1
#define     DISPLAY_OFF     0
//configuration for single display or double display
//#define CF_DOUBLEDISPLAY                    //defined: double display.   no diefine :single display

//configuration for single display or double display
#define CF_SEGMENT7                         //defined: support 7 segments.  no diefin: No support
  
//configuration for single display or double display
//#define CF_SEGMENT9                         //defined: support 9 segments.  no diefin: No support      
        
//configuration for single display or double display
//#define CF_SEGMENT16                      //defined: support 16 segments.  no diefin: No support                 

//total of every type figure
#define     FIG_7SEG_TOTAL      8       //max support 10
#define     FIG_9SEG_TOTAL      0       //max support 2
#define     FIG_13SEG_TOTAL     13      //max support 2

#define     FIG_16SEG_TOTAL     0       //max support 2
#endif      //CF_LCD
                                               
#endif          //__DISPLAY_CONFIG_H__

