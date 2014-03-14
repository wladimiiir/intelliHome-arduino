/* 
 * File:   ConfigurableTemperatureDefinitionSource.cpp
 * Author: Y12370
 * 
 * Created on Piatok, 2014, marec 14, 15:12
 */

#include "ConfigurableTemperatureDefinitionSource.h"

ConfigurableTemperatureDefinitionSource::ConfigurableTemperatureDefinitionSource(TemperatureDefinitionSource* autoSource) :
autoSource(autoSource),
minManual(AUTO_VALUE),
maxManual(AUTO_VALUE) {
}

float ConfigurableTemperatureDefinitionSource::getMaxTemperature() {
    if(maxManual == AUTO_VALUE) {
        return autoSource->getMaxTemperature();
    } else {
        return maxManual;
    }
}

float ConfigurableTemperatureDefinitionSource::getMinTemperature() {
    if(minManual == AUTO_VALUE) {
        return autoSource->getMinTemperature();
    } else {
        return minManual;
    }
}

void ConfigurableTemperatureDefinitionSource::setMaxTemperature(float value) {
    maxManual = value;
}

void ConfigurableTemperatureDefinitionSource::setMinTemperature(float value) {
    minManual = value;
}

