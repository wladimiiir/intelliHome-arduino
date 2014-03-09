/* 
 * File:   WeeklyTemperatureDefinitionSource.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 12:16 PM
 */

#ifndef WEEKLYTEMPERATUREDEFINITIONSOURCE_H
#define	WEEKLYTEMPERATUREDEFINITIONSOURCE_H

#include "TemperatureDefinitionSource.h"
#include "DailyTemperatureDefinitionSource.h"
#include "Day.h"

class WeeklyTemperatureDefinitionSource : public TemperatureDefinitionSource {
public:
    WeeklyTemperatureDefinitionSource();
    void add(Day day, int fromHour, int fromMinute, int toHour, int toMinute, float minTemperature, float maxTemperature);
    float getMinTemperature();
    float getMaxTemperature();
private:
    DailyTemperatureDefinitionSource weekDaysSources[7];
};

#endif	/* WEEKLYTEMPERATUREDEFINITIONSOURCE_H */

