/* 
 * File:   WeeklyTemperatureDefinitionSource.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 12:16 PM
 */

#include "WeeklyTemperatureDefinitionSource.h"

WeeklyTemperatureDefinitionSource::WeeklyTemperatureDefinitionSource() {
    weekDaysSources[MONDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[TUESDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[WEDNESDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[THURSDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[FRIDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[SATURDAY] = DailyTemperatureDefinitionSource();
    weekDaysSources[SUNDAY] = DailyTemperatureDefinitionSource();
}

float WeeklyTemperatureDefinitionSource::getMinTemperature() {
    return weekDaysSources[weekday()].getMinTemperature();
}

float WeeklyTemperatureDefinitionSource::getMaxTemperature() {
    return weekDaysSources[weekday()].getMaxTemperature();
}


