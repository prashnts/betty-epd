#include "spi.h"

void spi_9b_init(void) {
  LOG_DEBUG("Initializing 9bit SPI")
  SCL_L;
  SDA_H;
  CSB_H;
  CSB1_H;
  BS_H;
  delayMicroseconds(200);
}

void spi_9b_send_9b(unsigned int dat) {
  if ((dat & DATA_MASK) == DATA_MASK) {
    LOG_DEBUG("Sending as Data");
    spi_9b_send(DCX_DATA, (unsigned char)dat);
  } else {
    LOG_DEBUG("Sending as Command");
    spi_9b_send(DCX_CMD, (unsigned char)dat);
  }
}

void spi_9b_send(unsigned int dcx, unsigned char dat) {
  unsigned char i;

  CSB_L;

  delayMicroseconds(20);
  if (dcx) {
    SDA_H; // 1 for DCX_DATA
  } else {
    SDA_L; // 0 for DCX_CMD
  }

  // Pulse Clock Line
  SCL_H;
  delayMicroseconds(20);
  SCL_L;
  delayMicroseconds(20);

  // Send data over SDA/MOSI Bus
  for (i = 0; i < 8; i++) {
    if (dat & 0x80) {
      SDA_H;
    } else {
      SDA_L;
    }
    delayMicroseconds(20);
    SCL_H;
    delayMicroseconds(20);
    SCL_L;
    dat = dat << 1;
  }

  // Pull SDA Low
  SDA_L;
  delayMicroseconds(20);
  CSB_H;
  delayMicroseconds(20);

  LOG_DEBUG("Send over SPI: %x", dat);
}

unsigned char spi_9b_get(void) {
  int i;
  unsigned char DATA_BUF = 0x00;

  CSB_L;
  delayMicroseconds(20);
  SDA_H; // 1 for data
  delayMicroseconds(20);
  SCL_H;
  delayMicroseconds(20);
  SCL_L;
  delayMicroseconds(20);
  pinMode(SDA, INPUT);
  delayMicroseconds(60);
  for (i = 0; i < 8; i++) {
    DATA_BUF = DATA_BUF << 1;
    SCL_H;
    if (SDA_IN)
      DATA_BUF |= 0x01;
    SCL_L;
    delayMicroseconds(20);
  }
  pinMode(SDA, OUTPUT);
  SDA_L;
  delayMicroseconds(20);
  CSB_H;
  delayMicroseconds(20);

  LOG_DEBUG("Received over SPI: %x", DATA_BUF);
  return DATA_BUF;
}
