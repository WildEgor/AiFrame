#pragma once
#include "SPI.h"
#include "gen.h"

#ifdef TFT_eTFT
#include <TFT_eSPI.h>
#endif
#ifdef TFT_Adafruit
#include "Adafruit_ST7796S_kbv.h"
#endif

// TFT_eSPI tft = TFT_eSPI();
// void tft_render(int x, int y, int w, int h, uint8_t *buf)
// {
//     tft.pushImage(x, y, w, h,(uint16_t*)buf);
// }

Adafruit_ST7796S_kbv tft(TFT_CS, TFT_DC, TFT_RST);
void tft_render(int x, int y, int w, int h, uint8_t *buf)
{
    tft.drawRGBBitmap(x, y, (uint16_t*)buf, w, h);
}

#if defined(TIME)
    static int timeX1, timeY1;
    static uint8_t textSize1;
    #include "screen_time.h"
    uint16_t* screenContent;
#endif

void tft_init()
{
    SPI.setFrequency(4000000ul);

    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN);
    // tft.setSwapBytes(true);
    // tft.resetViewport();
    tft.setTextSize(1);

    gen.onRender(tft_render);

    #if defined(TIME)
        textSize1 = tft.width() / 7 / 6;
        timeX1 = (tft.width() - (textSize1 * 5 * 6)) / 3;
        timeY1 = tft.height() - (textSize1 * 8) - 10;
        // screenContent = NULL;
        // screenContent = (uint16_t*) malloc ((h * w)*2);
        // screenContent = (uint16_t*) malloc( textSize1*6*5 * textSize1*8 * 2 );
        // tft.readRect(timeX1-1, timeY1-1, textSize1*6*5, textSize1*8, screenContent);  
        // tft.fillRect(timeX-1, timeY-1, textSize*6*5, textSize*8,TFT_BLACK);
    #endif
}