#include <Weather/Weather.h>

sets::Timer wtmr;
Weather weather = Weather(MY_LAT, MY_LON);

// TODO
int8_t* getCurrTemp() {
    return weather.temp_min;
}

void init_wtmr()
{
    wtmr.setTime(0, 300);
    wtmr.startInterval();

    weather.get();
    int8_t* t = getCurrTemp();
    Serial.printf("%d", t);
}

void weather_tick() 
{
    #ifdef WEATHER
    weather.tick();
    
    if (wtmr.tick()) {
        weather.get();
        int8_t* t = getCurrTemp();
        Serial.printf("%d", t);
    }
    #endif
}

void weather_init() 
{
    #ifdef WEATHER
    init_wtmr();
    #endif
}