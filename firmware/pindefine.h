//==============================================
//            MSP430f550x pin define
//==============================================

#ifndef __PINDEFINE_H__
#define __PINDEFINE_H__

#include <msp430f5502.h>

/**********************************
MSP430f550x port define
**********************************/
//OUTPUT
//Pin define for DC 	    //Define your own MCU pin here.
#define DC_L    P5OUT&=0xFE
#define DC_H    P5OUT|=0x01
//Pin define for BS 	
#define BS_L    P6OUT&=0xFE
#define BS_H    P6OUT|=0x01
//Pin define for RSTN  
#define RSTN_L  P6OUT&=0xFD
#define RSTN_H  P6OUT|=0x02
//Pin define for CSB    
#define CSB_L  	P6OUT&=0xF7
#define CSB_H  	P6OUT|=0x08
//Pin define for SCL  	
#define SCL_L  	P4OUT&=0x7F
#define SCL_H  	P4OUT|=0x80
//Pin define for SDA 	
#define SDA_L 	P4OUT&=0xBF
#define SDA_H 	P4OUT|=0x40
//Pin define for CSB1_H  
#define CSB1_L  P5OUT&=0xFD
#define CSB1_H  P5OUT|=0x02
//Pin define for OTP_L 
#define OTP_L P1OUT&=0xFD
#define OTP_H P1OUT|=0x02

//========= Input ==========
//
//Pin define for SDA_IN  
#define SDA_IN  (P4IN&0x40)>>6
#define BUSYN 	P6IN_bit.P6IN2
#define OTP   P1IN_bit.P1IN1
#endif //#ifndef __PINDEFINE_H__


