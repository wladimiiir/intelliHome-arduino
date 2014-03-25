/* 
 * File:   SimpleTemperatureDefinitionSource.cpp
 * Author: wladimiiir
 * 
 * Created on December 29, 2013, 7:53 PM
 */

#include "SimpleTemperatureDefinitionSource.h"

SimpleTemperatureDefinitionSource::SimpleTemperatureDefinitionSource(float minTemperature, float maxTemperature) :
minTemperature(minTemperature),
maxTemperature(maxTemperature){
}

float SimpleTemperatureDefinitionSource::getMinTemperature() {
    return minTemperature;
}

float SimpleTemperatureDefinitionSource::getMaxTemperature() {
    return maxTemperature;
}

