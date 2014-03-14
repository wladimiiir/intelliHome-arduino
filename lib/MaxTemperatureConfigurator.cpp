/* 
 * File:   MaxTemperatureConfigurator.cpp
 * Author: Y12370
 * 
 * Created on Piatok, 2014, marec 14, 15:38
 */

#include "MaxTemperatureConfigurator.h"
#include "AppHelper.h"

MaxTemperatureConfigurator::MaxTemperatureConfigurator(ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource) :
temperatureDefinitionSource(temperatureDefinitionSource) {
}

String MaxTemperatureConfigurator::getValue() {
    float value = temperatureDefinitionSource->getMaxTemperature();
    return AppHelper::toString(value);
}

void MaxTemperatureConfigurator::setValue(String value) {
    if (!AppHelper::checkFloatValue(value))
        return;

    temperatureDefinitionSource->setMaxTemperature(atof(value.c_str()));
}


