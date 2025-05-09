#pragma once
#include <Adafruit_GFX.h>
#include "Adafruit_ST7796S_kbv.h"
#include "SPI.h"
#include "gen.h"
#include "config.h"

Adafruit_ST7796S_kbv tft(TFT_CS, TFT_DC, TFT_RST);

#if defined(TIME)
    #include "screen_info.h"
    int bgHeightOffset = clockBarHeight;
#else
    int bgHeightOffset = 0;
#endif

void tft_render(int x, int y, int w, int h, uint8_t *buf)
{
    tft.drawRGBBitmap(x, y, (uint16_t*)buf, w, h);
}

void tft_init()
{
    SPI.setFrequency(4000000ul);

    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(0x0000);
    tft.setTextColor(0x07E0);
    gen.onRender(tft_render);
    screen_time_init();
}