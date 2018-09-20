## Command line log of Demo run

```
pi@raspberrypi:~/epd-t2/firmware $ gcc -Wall -o main_rpi *.c -lwiringPi
pi@raspberrypi:~/epd-t2/firmware $ ./main_rpi
[INFO   ] | main.c          | main:20 | Setting up GPIOs and Initializing EPD
[INFO   ] | ET011TT2.c      | EPD_Init:33 | Initializing EPD
[DEBUG  ] | spi.c           | spi_9b_init:4 | Initializing 9bit SPI
[INFO   ] | ET011TT2.c      | EInk_Parameter_Initial:49 | Setting EPD Parameters
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 6
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 1
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 0
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 3
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 30
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 41
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 50
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 61
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 62
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: a2
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 0
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[INFO   ] | ET011TT2.c      | EInk_Parameter_Initial:114 | OTP Vcom=161b
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 82
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 84
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: e4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 63
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 64
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: df
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 2
[INFO   ] | ET011TT2.c      | EPD_Init:45 | Initialized EPD
[INFO   ] | main.c          | main:34 | Initialized EPD
[INFO   ] | ET011TT2.c      | EPD_Rev:139 | Reading Chip Revision
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 70
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: ff
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: a
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 0
[INFO   ] | ET011TT2.c      | EPD_Rev:150 | LUT Versions: v1=ff, v2=ff
[INFO   ] | ET011TT2.c      | EPD_Status:167 | Reading EPD Status
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 71
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 10
-> EPD I2C Error: 0
-> EPD I2C Busy:  16
-> EPD Data Flag: 0
-> EPD PON: 0
-> EPD POF: 0
-> EPD BUSYN: 0
[INFO   ] | ET011TT2.c      | EPD_TempSensor:154 | Reading EPD Temperature
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 40
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 0
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 18
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 0
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 18
[DEBUG  ] | spi.c           | spi_9b_get:90 | Received over SPI: 0
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 20
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 22
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 26
[INFO   ] | main.c          | display_sequence:8 | NYANNNN!
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 14
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 13
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 12
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 2
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 14
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 13
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 12
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 2
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 14
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 13
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 12
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 2
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 14
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 13
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 4
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 12
[DEBUG  ] | spi.c           | spi_9b_send_9b:14 | Sending as Data/CMD: 2
```
