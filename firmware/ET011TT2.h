#ifndef __ET011TT2_H__
#define __ET011TT2_H__

#include <stdio.h>
#include <wiringPi.h>

#include "pin_rpi.h"
#include "spi.h"
#include "logger.h"


/**********************************
Constant set
**********************************/
#define DATA_MASK   0x0100
#define DCX_CMD     0x0000
#define DCX_DATA    0x0001

#define PSR         0x0000
#define PWR         0x0001
#define POF         0x0002
#define PFS         0x0003
#define PON         0x0004
#define BTST        0x0006
#define DRF         0x0012
#define DTM2        0x0013
#define DTMW        0x0014
#define LUT_KWVCOM  0x0020
#define LUT_KW      0x0022
#define LUT_FT      0x0026
#define LPRD        0x0030
#define TSE         0x0041
#define TSC         0x0040
#define CDI         0x0050
#define TRES        0x0061
#define GDS         0x0062
#define GBS         0x0063
#define GSS         0x0064
#define VDCS        0x0082
#define VBDS        0x0084
#define ROTP        0x00A2
#define LVSEL       0x00E4
#define DF          0x00DF

//============Address Setting==================
#define Initial_23_16          0x00
#define Initial_15_0           0x0000 // 1K
#define Temperature            0x000000
#define Temperature0_23_16     0x00
#define Temperature0_15_0      0x0400 // 1K
#define Temperature1_23_16     0x00
#define Temperature1_15_0      0x0800
#define Temperature2_23_16     0x00
#define Temperature2_15_0      0x0C00
#define Temperature3_23_16     0x00
#define Temperature3_15_0      0x1000
#define Temperature4_23_16     0x00
#define Temperature4_15_0      0x1400
#define Temperature5_23_16     0x00
#define Temperature5_15_0      0x1800
#define Temperature6_23_16     0x00
#define Temperature6_15_0      0x1C00
#define Temperature7_23_16     0x00
#define Temperature7_15_0      0x2000
#define Temperature8_23_16     0x00
#define Temperature8_15_0      0x2400
#define Temperature9_23_16     0x00
#define Temperature9_15_0      0x2800
#define Temperature10_23_16    0x00
#define Temperature10_15_0     0x2C00

#define Temperature_LUT_Counter   672
//===========================================

#endif


#ifdef __ET011TT2_C__
#define __ET011TT2_EXTERN__
#else
#define __ET011TT2_EXTERN__ extern
#endif

__ET011TT2_EXTERN__ void EPD_Init(void);
__ET011TT2_EXTERN__ void EPD_Load_LUT2(unsigned int LUT, unsigned char const *LUT_Value, unsigned int LUT_Counter);
__ET011TT2_EXTERN__ void spi_9b_send_9b(unsigned int dat);
__ET011TT2_EXTERN__ void spi_9b_send(unsigned int dcx,unsigned char dat);
__ET011TT2_EXTERN__ unsigned char spi_9b_get(void);
__ET011TT2_EXTERN__ void Upload_Temperature_LUT(void);
__ET011TT2_EXTERN__ void EPD_Display_White(void);
__ET011TT2_EXTERN__ void EPD_Display_Black(void);
__ET011TT2_EXTERN__ void EPD_Display_Partial_White(void);
__ET011TT2_EXTERN__ void EPD_Display_Partial_Black(void);
__ET011TT2_EXTERN__ void EInk_Parameter_Initial(void);
__ET011TT2_EXTERN__ void check_busy_high(void);// If BUSYN=0 then waiting
__ET011TT2_EXTERN__ void check_busy_low(void);// If BUSYN=1 then waiting
__ET011TT2_EXTERN__ unsigned char string_to_number(unsigned char Buf);

__ET011TT2_EXTERN__ unsigned int byte_counter;
__ET011TT2_EXTERN__ unsigned char dataBuff[5];
__ET011TT2_EXTERN__ unsigned char hun;
__ET011TT2_EXTERN__ unsigned char ten;
__ET011TT2_EXTERN__ unsigned char sim;
__ET011TT2_EXTERN__ unsigned int VcomOTP;
__ET011TT2_EXTERN__ unsigned int WF_MODE;
__ET011TT2_EXTERN__ unsigned char SPIdataBuff[1300];

#define  GU4_Mode 0x01
#define  GC4_Mode 0x00