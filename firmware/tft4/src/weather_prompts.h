#pragma once
#include <Arduino.h>
#include <GyverNTP.h>
#include "mString.h"
#include "weather.h"
#include "macros.h"

// consts
#define MORNING_START 5
#define MORNING_END 11
#define DAY_START 11
#define DAY_END 17
#define EVENING_START 17
#define EVENING_END 22
#define NIGHT_START 22
#define NIGHT_END 5
#define COLD_TEMP 5 // below 5 degrees
#define COOL_TEMP 15 // 5-15 degrees
#define WARM_TEMP 25 // 15-25 degrees
#define HOT_TEMP 30 // above 30 degrees

enum TimeOfDay {
    MORNING,
    DAY,
    EVENING,
    NIGHT
};

enum Season {
    WINTER,
    SPRING,
    SUMMER,
    AUTUMN
};

TimeOfDay get_time_of_day() {
    uint8_t hour = NTP.hour();
    if (hour >= MORNING_START && hour < MORNING_END) return MORNING;
    if (hour >= DAY_START && hour < DAY_END) return DAY;
    if (hour >= EVENING_START && hour < EVENING_END) return EVENING;
    return NIGHT;
}

Season get_season() {
    uint8_t month = NTP.month();

    if (month >= 3 && month <= 5) return SPRING; // March, April, May
    if (month >= 6 && month <= 8) return SUMMER; // June, July, August
    if (month >= 9 && month <= 11) return AUTUMN; // September, October, November

    return WINTER;
}

Text get_weather_prompt() {
    TimeOfDay tod = get_time_of_day();
    Season season = get_season();
    int temp = get_curr_temp(NTP.hour());
    
    mString<50> buffer;

    switch (tod) {
        case MORNING: buffer.add("peaceful morning scene, "); break;
        case DAY: buffer.add("daylight scene, "); break;
        case EVENING: buffer.add("beautiful sunset scene, "); break;
        case NIGHT: buffer.add("starry night scene, "); break;
    }

    switch (season) {
        case WINTER:
            buffer.add("winter landscape, ");
            temp < COLD_TEMP ? buffer.add("frosty, snowy, ") : buffer.add("cold weather, ");
            break;
        case SPRING:
            buffer.add("spring landscape, ");
            temp < COOL_TEMP ? buffer.add("early spring, ") : buffer.add("blooming flowers, ");
            break;
        case SUMMER:
            buffer.add("summer landscape, ");
            if (temp > HOT_TEMP) buffer.add("hot summer day, ");
            else if (temp > WARM_TEMP) buffer.add("warm summer day, ");
            else buffer.add("pleasant summer day, ");
            break;
        case AUTUMN:
            buffer.add("autumn landscape, ");
            temp < COOL_TEMP ? buffer.add("late autumn, ") : buffer.add("fall colors, ");
            break;
    }

    switch (tod) {
        case MORNING:
            temp < COOL_TEMP ? buffer.add("morning mist, ") : buffer.add("morning light, ");
            break;
        case DAY:
            temp > WARM_TEMP ? buffer.add("bright sunshine, ") : buffer.add("clear sky, ");
            break;
        case EVENING:
            buffer.add("golden hour, ");
            break;
        case NIGHT:
            temp < COOL_TEMP ? buffer.add("cold night sky, ") : buffer.add("warm night sky, ");
            break;
    }

    buffer.add("digital art, beautiful, detailed, high quality");

    return Text(buffer);
}