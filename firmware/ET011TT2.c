#define __ET011TT2_C__

#include "pin_rpi.h"
#include "ET011TT2.h"
#include "delay.h"

//==============================================================================
// Check Busy
//==============================================================================
void check_busy_high(void) // If BUSYN=0 then waiting
{
  while (!(BUSYN))
    ;
}

void check_busy_low(void) // If BUSYN=1 then waiting
{
  while (BUSYN)
    ;
}
//==============================================================================
// EPD initial
//==============================================================================
void spi_9b_init(void) {
  SCL_L;
  SDA_H;
  CSB_H;
  CSB1_H;
  BS_H;
  delay(10); // 5+(1+1)*6+3 = 20 us
}

void EPD_Init(void) {
  spi_9b_init();
  RSTN_L; // Reset
  delay(100);
  RSTN_H;
  delay(1000);

  byte_counter = 14400; // 240*240(pixel)/4(pixel per byte)

  EInk_Parameter_Initial();

  spi_9b_send_9b(POF);
  check_busy_low();
}

void EInk_Parameter_Initial() {

  spi_9b_send_9b(BTST);
  spi_9b_send(1, 0x17);
  spi_9b_send(1, 0x97);
  spi_9b_send(1, 0x20);

  spi_9b_send_9b(PWR);
  spi_9b_send(1, 0x03);
  spi_9b_send(1, 0x03);
  spi_9b_send(1, 0x2B);
  spi_9b_send(1, 0x2B);
  spi_9b_send(1, 0x00);

  spi_9b_send_9b(PON);
  check_busy_high();

  spi_9b_send_9b(PSR);
  spi_9b_send(1, 0x0B);
  spi_9b_send(1, 0x06); // Change 0x86 to 0x06

  spi_9b_send_9b(PFS);
  spi_9b_send(1, 0x00);

  spi_9b_send_9b(LPRD); // PLL 50=0x25 25=0x4f 100=0x13
  spi_9b_send(1, 0x25);

  spi_9b_send_9b(TSE);
  spi_9b_send(1, 0x00);

  spi_9b_send_9b(CDI);
  spi_9b_send(1, 0xE1);
  spi_9b_send(1, 0x20);
  spi_9b_send(1, 0x10);

  spi_9b_send_9b(TRES);
  spi_9b_send(1, 0xEF);
  spi_9b_send(1, 0x00);
  spi_9b_send(1, 0xEF);

  spi_9b_send_9b(GDS);
  spi_9b_send(1, 0xA9);
  spi_9b_send(1, 0xA9);
  spi_9b_send(1, 0xEB);
  spi_9b_send(1, 0xEB);
  spi_9b_send(1, 0x02);

  ///////////Read VCOM from OTP
  spi_9b_send_9b(PON);
  check_busy_high();
  spi_9b_send_9b(ROTP);
  spi_9b_get();
  spi_9b_get();
  for (int i = 0; i < 20; i++) {
    spi_9b_get();
  }
  for (int i = 0; i < 5; i++) {
    dataBuff[i] = spi_9b_get();
  }
  hun = string_to_number(dataBuff[1]);
  ten = string_to_number(dataBuff[3]);
  sim = string_to_number(dataBuff[4]);
  VcomOTP = (hun * 100 + ten * 10 + sim) / 5 - 2;
  //////////////////////////////////

  spi_9b_send_9b(VDCS);
  spi_9b_send(1, VcomOTP);

  spi_9b_send_9b(VBDS);
  spi_9b_send(1, VcomOTP);

  spi_9b_send_9b(LVSEL);
  spi_9b_send(1, 0x02);

  spi_9b_send_9b(GBS);
  spi_9b_send(1, 0x01);
  spi_9b_send(1, 0x01);

  spi_9b_send_9b(GSS);
  spi_9b_send(1, 0x02);
  spi_9b_send(1, 0x02);

  spi_9b_send_9b(DF); // For REGAL
  spi_9b_send(1, 0x1F);
}
//==============================================================================
// Waveform Loading
//==============================================================================

void EPD_Load_LUT2(unsigned int LUT, unsigned char const *LUT_Value,
                   unsigned int LUT_Counter) {
  unsigned int i;
  spi_9b_send_9b(LUT);
  for (i = 0; i < LUT_Counter; i++) {
    spi_9b_send(1, *LUT_Value);
    LUT_Value++;
  }
}

void Upload_Temperature_LUT(void) {

  unsigned long TemperatureAddress;
  unsigned long i = 0;
  unsigned char TemperatureAddress_23_16;
  unsigned int TemperatureAddress_15_0;

  int Temp = 0;

  spi_9b_send_9b(TSC);
  check_busy_high();
  Temp = (int)spi_9b_get();
  spi_9b_get();

  if (Temp < 3)
    i = 0;
  else if (Temp < 7)
    i = 1;
  else if (Temp < 10)
    i = 2;
  else if (Temp < 13)
    i = 3;
  else if (Temp < 17)
    i = 4;
  else if (Temp < 20)
    i = 5;
  else if (Temp < 23)
    i = 6;
  else if (Temp < 27)
    i = 7;
  else if (Temp < 31)
    i = 8;
  else if (Temp < 35)
    i = 9;
  else if (Temp <= 40)
    i = 10;
  else if (Temp <= 45)
    i = 11;
  else if (Temp <= 50)
    i = 12;
  else
    i = 0;

  if (WF_MODE == GC4_Mode)
    TemperatureAddress = Temperature + i * 0x02A0;
  else if (WF_MODE == GU4_Mode) {
    i = i + 13;
    TemperatureAddress = Temperature + i * 0x02A0;
  } else {
    i = i + 26;
    TemperatureAddress = Temperature + i * 0x02A0;
  }

  //====================Set your own flash
  //setting=====================================================
  TemperatureAddress_15_0 = (unsigned int)TemperatureAddress;
  TemperatureAddress_23_16 = (unsigned char)(TemperatureAddress >> 16);
  ReadData(TemperatureAddress_23_16, TemperatureAddress_15_0, SPIdataBuff,
           Temperature_LUT_Counter); // Load waveform from flash to SRAM
                                     // (SPIdataBuff).
  //===================================================================================================

  // Load waveform data from SRAM
  EPD_Load_LUT2(LUT_KWVCOM, &SPIdataBuff[0], 32);
  EPD_Load_LUT2(LUT_KW, &SPIdataBuff[32], 512);
  EPD_Load_LUT2(LUT_FT, &SPIdataBuff[544], 128);
}
//==============================================================================
// EPD Display
//==============================================================================
void EPD_Display_White(void) {
  unsigned long i;

  // Upload_Temperature_LUT();

  spi_9b_send_9b(DTMW);
  spi_9b_send(1, 0x00); // X  update window x_start
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x00);
  spi_9b_send(1, 0xEF); // W  update window width = 240 (0x00EF)
  spi_9b_send(1, 0x00); // L  update window width = 240 (0x00EF)
  spi_9b_send(1, 0xEF);

  spi_9b_send_9b(DTM2);
  for (i = 0; i < byte_counter; i++) {
    spi_9b_send(1, 0xFF);
  }

  spi_9b_send_9b(PON);
  check_busy_high();

  spi_9b_send_9b(DRF);
  spi_9b_send(1, 0x00);
  spi_9b_send(
      1, 0x00); // X  update window x_start //this should follow DTMW setting
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x00);
  spi_9b_send(1, 0xEF); // W  update window width = 240 (0x00EF)
  spi_9b_send(1, 0x00); // L  update window width = 240 (0x00EF)
  spi_9b_send(1, 0xEF);

  check_busy_high();

  spi_9b_send_9b(POF);
  check_busy_low();
}

void EPD_Display_Black(void) {
  unsigned long i;

  // Upload_Temperature_LUT();

  spi_9b_send_9b(DTMW);
  spi_9b_send(1, 0x00); // X  update window x_start
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x00);
  spi_9b_send(1, 0xEF); // W  update window width = 240 (0x00EF)
  spi_9b_send(1, 0x00); // L  update window width = 240 (0x00EF)
  spi_9b_send(1, 0xEF);

  spi_9b_send_9b(DTM2);
  for (i = 0; i <= byte_counter; i++) {
    spi_9b_send(1, 0x00);
  }

  spi_9b_send_9b(PON);
  check_busy_high();

  spi_9b_send_9b(DRF);
  spi_9b_send(1, 0x00);
  spi_9b_send(
      1, 0x00); // X  update window x_start //this should follow DTMW setting
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x00);
  spi_9b_send(1, 0xEF); // W  update window width = 240 (0x00EF)
  spi_9b_send(1, 0x00); // L  update window width = 240 (0x00EF)
  spi_9b_send(1, 0xEF);

  check_busy_high();

  spi_9b_send_9b(POF);
  check_busy_low();
}

void EPD_Display_Partial_White(void) {
  unsigned long i;

  // Upload_Temperature_LUT();

  spi_9b_send_9b(DTMW);
  spi_9b_send(1, 0x14); // X  update window x_start
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x14);
  spi_9b_send(1, 0x64); // W  update window width = 40 (0x0027)
  spi_9b_send(1, 0x00); // L  update window width = 40 (0x0027)
  spi_9b_send(1, 0x64);

  spi_9b_send_9b(DTM2);
  for (i = 0; i < byte_counter; i++) {
    spi_9b_send(1, 0xFF);
  }

  spi_9b_send_9b(PON);
  check_busy_high();

  spi_9b_send_9b(DRF);
  spi_9b_send(1, 0x00);
  spi_9b_send(
      1, 0x14); // X  update window x_start //this should follow DTMW setting
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x14);
  spi_9b_send(1, 0x27); // W  update window width = 40 (0x0027)
  spi_9b_send(1, 0x00); // L  update window width = 40 (0x0027)
  spi_9b_send(1, 0x27);

  check_busy_high();

  spi_9b_send_9b(POF);
  check_busy_low();
}

void EPD_Display_Partial_Black(void) {
  unsigned long i;

  Upload_Temperature_LUT();

  spi_9b_send_9b(DTMW);
  spi_9b_send(1, 0x14); // X  update window x_start
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x14);
  spi_9b_send(1, 0x64); // W  update window width = 40 (0x0027)
  spi_9b_send(1, 0x00); // L  update window width = 40 (0x0027)
  spi_9b_send(1, 0x64);

  spi_9b_send_9b(DTM2);
  for (i = 0; i <= byte_counter; i++) {
    spi_9b_send(1, 0x00);
  }

  spi_9b_send_9b(PON);
  check_busy_high();

  spi_9b_send_9b(DRF);
  spi_9b_send(1, 0x00);
  spi_9b_send(
      1, 0x14); // X  update window x_start //this should follow DTMW setting
  spi_9b_send(1, 0x00); // Y  update window y_start
  spi_9b_send(1, 0x14);
  spi_9b_send(1, 0x27); // W  update window width = 40 (0x0027)
  spi_9b_send(1, 0x00); // L  update window width = 40 (0x0027)
  spi_9b_send(1, 0x27);

  check_busy_high();

  spi_9b_send_9b(POF);
  check_busy_low();
}
//==============================================================================
// SPI Transmission Protocol
//==============================================================================
void spi_9b_send_9b(unsigned int dat) {
  if ((dat & DATA_MASK) == DATA_MASK)
    spi_9b_send(DCX_DATA, (unsigned char)dat);
  else
    spi_9b_send(DCX_CMD, (unsigned char)dat);
}

void spi_9b_send(unsigned int dcx, unsigned char dat) {
  unsigned char i;

  CSB_L;

  delay(1);
  if (dcx)
    SDA_H; // 1 for DCX_DATA
  else
    SDA_L; // 0 for DCX_CMD
  SCL_H;
  delay(1);
  SCL_L;
  delay(1);
  for (i = 0; i < 8; i++) {
    if (dat & 0x80) {
      SDA_H;
    } else {
      SDA_L;
    }
    delay(1);
    SCL_H;
    delay(1);
    SCL_L;
    dat = dat << 1;
  }
  SDA_L;
  delay(1);

  CSB_H;

  delay(1);
}

unsigned char spi_9b_get(void) {
  int i;
  unsigned char DATA_BUF = 0x00;

  CSB_L;

  delay(1);
  SDA_H; // 1 for data
  delay(1);
  SCL_H;
  delay(1);
  SCL_L;
  delay(1);
  pinMode(SDA, INPUT);
  delay(3);
  for (i = 0; i < 8; i++) {
    DATA_BUF = DATA_BUF << 1;
    SCL_H;
    if (SDA_IN)
      DATA_BUF |= 0x01;
    SCL_L;
    delay(1);
  }
  pinMode(SDA, OUTPUT);
  SDA_L;

  delay(1);

  CSB_H;

  delay(1);
  return DATA_BUF;
}
//==============================================================================
// Data type transfer
//============================================================================================
unsigned char string_to_number(unsigned char Buf) {
  if ((Buf > 47) && (Buf < 58)) // ASCII(Decimal) 48 ~ 57 = 0 ~ 9
  {
    return Buf - 48;
  } else {
    return 0xFF;
  }
}
//===========================================================================================
