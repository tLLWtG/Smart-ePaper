#ifndef __WEATHER_H
#define __WEATHER_H

#include "SeP.h"

// 和风天气 APIKEY
#define myAPIKEY ""

struct Realtime_weather
{
    String updateTime, temp, text, windDir, windScale, humidity;
};

struct Forecast_weather
{
    String updateTime;
    String fxDate[3];
    String tempMax[3], tempMin[3];
    String textDay[3], textNight[3];
};

struct Air_data
{
    String updateTime, aqi, category;
};

Realtime_weather get_realtime_weather();
Forecast_weather get_forecast_weather();
Air_data get_air_data();

#endif
