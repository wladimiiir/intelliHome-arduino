/* 
 * File:   TemperatureDefinitionSource.h
 * Author: wladimiiir
 *
 * Created on December 29, 2013, 5:14 PM
 */

#ifndef DAILYTEMPERATUREDEFINITIONSOURCE_H
#define	DAILYTEMPERATUREDEFINITIONSOURCE_H

#include <Arduino.h>
#include <Time.h>
#include <StandardCplusplus.h>
#include <vector>

#include "TemperatureDefinitionSource.h"

class TemperatureDefinition {
public:
    TemperatureDefinition(int fromHour, int fromMinute, int toHour, int toMinute, float minTemperature, float maxTemperature);
    bool isInTime();
    float getMinTemperature();
    float getMaxTemperature();
private:
    int fromHour, fromMinute, toHour, toMinute;
    float minTemperature, maxTemperature;
};

class DailyTemperatureDefinitionSource : public TemperatureDefinitionSource {
public:
    DailyTemperatureDefinitionSource();
    void add(int fromHour, int fromMinute, int toHour, int toMinute, float minTemperature, float maxTemperature);
    float getMinTemperature();
    float getMaxTemperature();
private:
    std::vector<TemperatureDefinition> definitions;
};

#endif	/* DAILYTEMPERATUREDEFINITIONSOURCE_H */

