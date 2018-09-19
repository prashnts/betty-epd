#ifndef __SPI_3W__
#define __SPI_3W__

#include <stdio.h>
#include <wiringPi.h>

#include "ET011TT2.h"
#include "logger.h"

void spi_9b_init(void);
void spi_9b_send_9b(unsigned int dat);
void spi_9b_send(unsigned int dcx, unsigned char dat);
unsigned char spi_9b_get(void);

#endif
