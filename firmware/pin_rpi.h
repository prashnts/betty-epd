//==============================================
//==============================================

#ifndef __PINDEFINE_H__
#define __PINDEFINE_H__

#include <wiringPi.h>

/*
#define DC      8     // BCM 2 - Pin 3
#define BS      9     // BCM 3 - Pin 5
#define RSTN    7     // BCM 4 - Pin 7
#define CSB     0     // BCM 17 - Pin 11
#define SCL     2     // BCM 27 - Pin 13
#define SDA     3     // BCM 22 - Pin 15
#define CSB1    12    // BCM 10 - Pin 19
#define BUSY    14   // BCM 11 - Pin 23
#define OTP_IN     30   // BCM 0 - Pin 27
*/

#define SDA      8     // BCM 2 - Pin 3
#define SCL      9     // BCM 3 - Pin 5
#define CSB    7     // BCM 4 - Pin 7
#define RSTN     0     // BCM 17 - Pin 11
#define DC     2     // BCM 27 - Pin 13
#define BUSY     3     // BCM 22 - Pin 15
#define BS    12    // BCM 10 - Pin 19
#define CSB1    14   // BCM 11 - Pin 23
#define OTP_IN     30   // BCM 0 - Pin 27

//OUTPUT
//Pin define for DC
#define DC_L    digitalWrite(DC, 0)
#define DC_H    digitalWrite(DC, 1)
//Pin define for BS 	
#define BS_L    digitalWrite(BS, 0)
#define BS_H    digitalWrite(BS, 1)
//Pin define for RSTN  
#define RSTN_L  digitalWrite(RSTN, 0)
#define RSTN_H  digitalWrite(RSTN, 1)
//Pin define for CSB    
#define CSB_L  	digitalWrite(CSB, 0)
#define CSB_H  	digitalWrite(CSB, 1)
//Pin define for SCL  	
#define SCL_L  	digitalWrite(SCL, 0)
#define SCL_H  	digitalWrite(SCL, 1)
//Pin define for SDA 	
#define SDA_L 	digitalWrite(SDA, 0)
#define SDA_H 	digitalWrite(SDA, 1)
//Pin define for CSB1_H  
#define CSB1_L  digitalWrite(CSB1, 0)
#define CSB1_H  digitalWrite(CSB1, 1)
//Pin define for OTP_L 
#define OTP_L   digitalWrite(OTP_IN, 0)
#define OTP_H   digitalWrite(OTP_IN, 1)

//========= Input ==========
//
//Pin define for SDA_IN  
#define SDA_IN  digitalRead(SDA)
#define BUSYN 	digitalRead(BUSY)
#define OTP     digitalRead(OTP_IN)
#endif //#ifndef __PINDEFINE_H__

