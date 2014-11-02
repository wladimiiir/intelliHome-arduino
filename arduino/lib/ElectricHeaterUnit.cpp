/* 
 * File:   ElectricHeaterUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 4, 2014, 8:51 PM
 */

#include "ElectricHeaterUnit.h"

ElectricHeaterUnit::ElectricHeaterUnit(Thermometer* thermometer, StateUnit* controlUnit, TemperatureDefinitionSource* temperatureDefinition) :
thermometer(thermometer),
controlUnit(controlUnit),
temperatureDefinition(temperatureDefinition) {
}

bool ElectricHeaterUnit::shouldRun() {
    if (getState() == STOPPED
            && thermometer->getTemperature() < temperatureDefinition->getMaxTemperature()) {
        return true;
    }
    if (getState() == STARTED
            && thermometer->getTemperature() < temperatureDefinition->getMaxTemperature() + 1) {
        return true;
    }
    return false;
}

void ElectricHeaterUnit::start() {
    controlUnit->start();
}

void ElectricHeaterUnit::stop() {
    controlUnit->stop();
}

void ElectricHeaterUnit::process(float state) {
    if (shouldRun()) {
        controlUnit->start();
    } else {
        controlUnit->stop();
    }
}

State ElectricHeaterUnit::getState() {
    return controlUnit->getState();
}