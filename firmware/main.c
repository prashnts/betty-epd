#include "main.h"
#include "bitmap.h"


void display_sequence() {
  Upload_Temperature_LUT();
  delay(1000);
  LOG_INFO("NYANNNN!");
  EPD_Display_Test_Bitmap(BMP_NYAN_R);
  delay(2000);
  EPD_Display_Test_Bitmap(BMP_WOOF);
  delay(1000);
  EPD_Display_Test_Bitmap(BMP_NYAN_L);
  delay(2000);
  EPD_Display_Test_Bitmap(BMP_FRENCH);
}


int main (void) {
  LOG_INFO("Setting up GPIOs and Initializing EPD");
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

  LOG_INFO("Initialized EPD");

  // Read Revision value
  EPD_Rev();
  // Read Status
  EPD_Status();
  EPD_TempSensor();

  display_sequence();

  return 0;
}