/* 
 * File:   TemperatureDefinitionSource.cpp
 * Author: wladimiiir
 * 
 * Created on December 29, 2013, 5:14 PM
 */
#include "DailyTemperatureDefinitionSource.h"

TemperatureDefinition::TemperatureDefinition(int fromHour, int fromMinute, int toHour, int toMinute, float minTemperature, float maxTemperature) :
fromHour(fromHour),
fromMinute(fromMinute),
toHour(toHour),
toMinute(toMinute),
minTemperature(minTemperature),
maxTemperature(maxTemperature) {
}

float TemperatureDefinition::getMinTemperature() {
    return minTemperature;
}

float TemperatureDefinition::getMaxTemperature() {
    return maxTemperature;
}

bool TemperatureDefinition::isInTime() {
    if (hour() < fromHour)
        return false;
    if (hour() > toHour)
        return false;

    if (hour() == fromHour) {
        if (minute() < fromMinute)
            return false;
        if (minute() >= toMinute)
            return false;
    }

    return true;
}

DailyTemperatureDefinitionSource::DailyTemperatureDefinitionSource() {
}

void DailyTemperatureDefinitionSource::add(int fromHour, int fromMinute, int toHour, int toMinute, float minTemperature, float maxTemperature) {
    definitions.push_back(TemperatureDefinition(fromHour, fromMinute, toHour, toMinute, minTemperature, maxTemperature));
}

float DailyTemperatureDefinitionSource::getMinTemperature() {
    for (std::vector<TemperatureDefinition>::iterator definition = definitions.begin(); definition != definitions.end(); ++definition) {
        if (definition->isInTime()) {
            return definition->getMinTemperature();
        }
    }
    
    return 0.0;
}

float DailyTemperatureDefinitionSource::getMaxTemperature() {
    for (std::vector<TemperatureDefinition>::iterator definition = definitions.begin(); definition != definitions.end(); ++definition) {
        if (definition->isInTime()) {
            return definition->getMaxTemperature();
        }
    }
    
    return 0.0;
}