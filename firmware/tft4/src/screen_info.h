#pragma once
#include <Arduino.h>
#include <GyverNTP.h>   
#include "tft.h"
#include "gen.h"
#include "macros.h"
#include "weather.h"

#if defined(TIME)
    int clockBarHeight = 80;
#else
    int clockBarHeight = 0;
#endif

static int timeX, timeY, lastMinute = -1;
static uint8_t textSize = 3;
bool need_update;

void screen_time_init(){
  #if defined(TIME)
  // --- Clock text positioning ---
  int charWidth = 6 * textSize;
  int charHeight = 8 * textSize;
  int textLength = 10;  // Format "HH:MM"
  int clockTextWidth = charWidth * textLength;

  timeX = (tft.width() - clockTextWidth) / 2;
  timeY = tft.height() - clockBarHeight + (clockBarHeight - charHeight) / 2;
  #endif
}

void trigger_update() {
  need_update = true;
}

void ntp_init()
{
  NTP.begin(TZ);
  NTP.setPeriod(300); // every 5 min

  Sprint(F("Waiting for NTP time sync: "));
  tft.setTextColor(0x07E0);
  tft.print(F("Waiting for NTP time sync: "));
  
  NTP.updateNow();
  
  String dt = NTP.dateToString();
  Sprintln(dt);

  NTP.onSecond([](){
    Datime dt = NTP;

    if (dt.minute != lastMinute) {
      lastMinute = dt.minute;
      need_update = true;
    }

    if (need_update) {
      need_update = false;
      
      tft.fillRect(0, tft.height() - clockBarHeight, tft.width(), clockBarHeight, 0x0000);
      tft.setCursor(timeX, timeY);
      tft.setTextColor(0xffff);
      tft.setTextSize(textSize);
      
      int tempRounded = get_curr_temp(dt.hour);
      char buf[16];
      snprintf(buf, sizeof(buf), "%02d:%02d %d", dt.hour, dt.minute, tempRounded);
      tft.print(buf);
      tft.print((char)247);  // Попробуй 247, 248, 223
      tft.print("C");
    }
  });

  gen.onRenderEnd(trigger_update);
}

void time_tick() {
  #if defined(TIME)
  tft.setTextSize(textSize);
  NTP.tick();
  #endif
}