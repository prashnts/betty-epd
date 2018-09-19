#include "main.h"

void display_sequence() {
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


void main (void) {
  LOG_INFO("Setting up GPIOs and Initializing EPD")
  wiringPiSetup();

  pinMode(DC, OUTPUT);
  pinMode(BS, OUTPUT);
  pinMode(RSTN, OUTPUT);
  pinMode(CSB, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(CSB1, OUTPUT);
  pinMode(BUSY, INPUT);

  EPD_Init();

  LOG_INFO("Initialized EPD")

  // Read Revision value
  EPD_Rev();
}