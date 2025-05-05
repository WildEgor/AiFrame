#pragma once
#include <Arduino.h>
#include "tft.h"
#include "gen.h"
#include <GyverNTP.h>    

static int w, h, timeX, timeY, lastMinute = -1;
static uint8_t textSize;
bool need_update;

void trigger_update() {
  need_update = true;
}

void ntpGetTime()
{
  NTP.begin(TZ);
  NTP.setPeriod(30);

  Serial.print(F("Waiting for NTP time sync: "));
  tft.setTextColor(TFT_GREEN);
  tft.print(F("Waiting for NTP time sync: "));

  NTP.updateNow();
  
  Datime dt = NTP;
  String dateToString = dt.dateToString();
  Serial.println(dateToString);
  tft.println(dateToString);

  NTP.onSecond([](){
    Datime dt = NTP;


    if (dt.minute != lastMinute) {
      lastMinute = dt.minute;
      need_update = true;
    }

    if (need_update) {
      need_update = false;
      
      if (tft_render){
        // print time with black background
        //tft.pushRect(timeX, timeY-textSize*8, textSize*6*5, textSize*8,(uint16_t*)screenContent, true);
        tft.fillRect(timeX-1, timeY-1, textSize*6*5, textSize*8,TFT_BLACK);
        tft.setCursor(timeX, timeY);
        tft.setTextColor(TFT_GREEN);
        tft.printf("%02d:%02d", dt.hour, dt.minute);
      } else {
        // print time with border
        tft.setCursor(timeX - 1, timeY - 1);
        tft.setTextColor(TFT_DARKGREY);
        tft.printf("%02d:%02d", dt.hour, dt.minute);
        tft.setCursor(timeX + 2, timeY + 2);
        tft.setTextColor(TFT_BLACK);
        tft.printf("%02d:%02d", dt.hour, dt.minute);
        tft.setCursor(timeX, timeY);
        tft.setTextColor(TFT_WHITE);
        tft.printf("%02d:%02d", dt.hour, dt.minute);
      }
    }
  });

  gen.onRenderEnd(trigger_update);
}

void time_tick() {
  #if defined(TIME)
  // ======== TIME ========
  tft.setTextSize(textSize);
  NTP.tick();
  // ======== TIME ======== 
  #endif
}