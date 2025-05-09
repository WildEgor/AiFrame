#pragma once
#include <Weather.h>
#include "config.h"

Weather weather;

int get_curr_temp(int hour) {
    #ifdef WEATHER
    float currT = weather.temps[hour];
    return round(currT);
    #endif
    return 0;
}

void weather_tick() 
{
    #ifdef WEATHER
    weather.tick();
    #endif
}

void weather_init() 
{
    #ifdef WEATHER
    weather.setCoordinates(MY_LAT, MY_LON);
    weather.get();
    #endif
}