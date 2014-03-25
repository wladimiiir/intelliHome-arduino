/* 
 * File:   MinTemperatureConfigurator.cpp
 * Author: Y12370
 * 
 * Created on Piatok, 2014, marec 14, 15:25
 */

#include <Arduino.h>
#include "MinTemperatureConfigurator.h"
#include "AppHelper.h"

MinTemperatureConfigurator::MinTemperatureConfigurator(ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource) :
temperatureDefinitionSource(temperatureDefinitionSource) {
}

String MinTemperatureConfigurator::getValue() {
    float value = temperatureDefinitionSource->getMinTemperature();
    return AppHelper::toString(value);
}

void MinTemperatureConfigurator::setValue(String value) {
    if (value.equalsIgnoreCase("auto")) {
        temperatureDefinitionSource->setMinTemperature(AUTO_VALUE);
        return;
    }
    if (!AppHelper::checkFloatValue(value))
        return;

    temperatureDefinitionSource->setMinTemperature(atof(value.c_str()));
}


