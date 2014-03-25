/* 
 * File:   TemperatureController.cpp
 * Author: wladimiiir
 * 
 * Created on December 23, 2013, 9:35 PM
 */

#include "TemperatureController.h"
#include "TemperatureDefinitionSource.h"
#include <StandardCplusplus.h>
#include <vector>

TemperatureController::TemperatureController(
        Thermometer* thermometer,
        TemperatureDefinitionSource* temperatureDefinitionSource,
        StateUnit* heatingUnit,
        StateUnit* idleControlUnit
        ) :
thermometer(thermometer),
temperatureDefinitionSource(temperatureDefinitionSource),
heatingUnit(heatingUnit),
idleControlUnit(idleControlUnit),
heating(false) {
}

void TemperatureController::process() {
    float temperature = thermometer->getTemperature();

    if (heating && temperature >= temperatureDefinitionSource->getMaxTemperature()) {
        stopHeatingUnit();
        startIdleControlUnit();
    } else if (!heating && temperature <= temperatureDefinitionSource->getMinTemperature()) {
        stopIdleControlUnit();
        startHeatingUnit();
    } else if (heating) {
        processHeatingUnit(temperature);
    } else {
        processIdleControlUnit(temperature);
    }
}

void TemperatureController::startHeatingUnit() {
    heating = true;
    heatingUnit->start();
}

void TemperatureController::stopHeatingUnit() {
    heating = false;
    heatingUnit->stop();
}

float calculateState(float lowTemperature, float highTemperature, float temperature) {
    float state = (temperature - lowTemperature) / (highTemperature - lowTemperature) * 100;
    state = 100 - constrain(state, 0, 100);
    return state;
}

void TemperatureController::processHeatingUnit(float temperature) {
    float minTemperature;
    if (idleControlUnit != NULL) {
        minTemperature = (temperatureDefinitionSource->getMinTemperature() + temperatureDefinitionSource->getMaxTemperature()) / 2;
    } else {
        minTemperature = temperatureDefinitionSource->getMinTemperature();
    }

    heatingUnit->process(calculateState(minTemperature, temperatureDefinitionSource->getMaxTemperature(), temperature));
}

void TemperatureController::startIdleControlUnit() {
    if (idleControlUnit == NULL)
        return;
    idleControlUnit->start();
}

void TemperatureController::stopIdleControlUnit() {
    if (idleControlUnit == NULL)
        return;
    idleControlUnit->stop();
}

void TemperatureController::processIdleControlUnit(float temperature) {
    if (idleControlUnit == NULL)
        return;
//    if (temperature > temperatureDefinitionSource->getMaxTemperature()) {
//        idleControlUnit->stop();
//        return;
//    }
    idleControlUnit->process(calculateState(temperatureDefinitionSource->getMinTemperature(), temperatureDefinitionSource->getMaxTemperature(), temperature));
}