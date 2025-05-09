#pragma once
// common 
#define F_VERSION "1.1"
#define DISP_WIDTH 320
#define DISP_HEIGHT 480
#define DISP_SCALE 2    // 1, 2, 4, 8
#define TIME
#define NTP_SERVER "pool.ntp.org"
#define TZ 3
#define ENABLE_OTA false
#define TFT_eTFT false
#define TFT_Adafruit true
#define WEATHER
#define MY_LAT 55.645609
#define MY_LON 37.391890
// tft
#define ST7796_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 480
#define TFT_CS   D3     
#define TFT_RST  D0  
#define TFT_DC   D8 
// #define TFT_MOSI PIN_D7
// #define TFT_SCK PIN_D5
// #define TFT_MISO -1 
#define LOAD_GLCD   
#define LOAD_FONT2  
#define LOAD_FONT4  
#define LOAD_FONT6 
#define LOAD_FONT7  
#define LOAD_FONT8  
#define LOAD_GFXFF  
#define SMOOTH_FONT
#define SPI_FREQUENCY  40000000
#define SPI_TOUCH_FREQUENCY  2500000
#define SUPPORT_TRANSACTIONS
// system
#define SERIAL_PRINTING
#define ESP_SERIAL_BAUD 115200