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


  printf("--> Init");
  EPD_Init();        // second Initial
  printf("--> Show White");
  EPD_Display_White();
  delay(1000);
  printf("--> Show Rect Black");
  EPD_Display_Partial_Black();
  delay(1000);
  printf("--> Show Black");
  EPD_Display_Black();
  delay(1000);
  printf("--> Show Rect White");
  EPD_Display_Partial_White();
  delay(1000);
  printf("--> Show White");
  EPD_Display_White();
  delay(1000);
}