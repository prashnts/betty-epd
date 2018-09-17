#include "delay.h"
#include "pin_rpi.h"
#include "ET011TT2.h"

#include "main.h"


void main (void) {

  pinMode(DC, OUTPUT);
  pinMode(BS, OUTPUT);
  pinMode(RSTN, OUTPUT);
  pinMode(CSB, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(CSB1, OUTPUT);
  pinMode(BUSY, INPUT);
        

  EPD_Init();        // second Initial
  EPD_Display_White();
  EPD_Display_Black();
  EPD_Display_White();
} 