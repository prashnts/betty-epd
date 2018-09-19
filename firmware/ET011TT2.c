#include "ET011TT2.h"

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


void EPD_Init(void) {
  LOG_INFO("Initializing EPD")
  spi_9b_init();

  RSTN_L; // Reset
  delay(100);
  RSTN_H;
  delay(1000);

  // 240*240(pixel)/4(pixel per byte)
  byte_counter = 14400;

  EInk_Parameter_Initial();

  spi_9b_send_9b(POF);
  check_busy_low();
  LOG_INFO("Initialized EPD")
}

void EInk_Parameter_Initial() {
  LOG_INFO("Setting EPD Parameters")

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

  LOG_INFO("OTP Vcom=%x", VcomOTP);


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

void EPD_Rev() {
  LOG_INFO("Reading Chip Revision")
  unsigned char lut_v1, lut_v2;
  // Send to Register at 0x70
  spi_9b_send_9b(0b01110000);

  lut_v1 = spi_9b_get();
  lut_v2 = spi_9b_get();

  LOG_INFO("LUT Versions: v1=%x, v2=%x", lut_v1, lut_v2);
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

  // Upload_Temperature_LUT();

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
