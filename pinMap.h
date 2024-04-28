

#pragma once

#define CAN_RX 8
#define CAN_TX 18

#define USER_INPUT_A1 17
#define USER_INPUT_A2 9

#define USER_INPUT_D1 48
#define USER_INPUT_D2 47

#define R24 5
#define R25 4
#define R26 2
#define R27 1

#define LED_1 21
#define LED_2 14

/*

TFT eSPI Library settings. May beed to be setup in userconfig file of library.

*/

/*

#define GC9A01_DRIVER

#define TFT_HEIGHT 240 // GC9A01 240 x 240

//#define TFT_MISO 21
#define TFT_MOSI 11
#define TFT_SCLK 12
#define TFT_DC 13
#define TFT_CS   10  // Chip select control pin/#define TFT_DC    13  // Data Command control pin
//#define TFT_RST   36  // Reset pin (could connect to RST pin)
#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
#define TFT_BL   6  // LED back-light

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY  20000000
 #define SPI_FREQUENCY  27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  55000000 // STM32 SPI1 only (SPI2 maximum is 27MHz)
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000


*/