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

#define PROCESS_INTERVAL        5000

unsigned long nextProcessTime = 0;
std::vector<float> averageValues;

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
running(false) {
    nextProcessTime = millis();
}

void writeAverageValue(float temperature) {
    averageValues.push_back(temperature);
}

float readAverageValue() {
    float value = 0;
    for (std::vector<float>::size_type index = 0; index < averageValues.size(); index++) {
        value += averageValues.at(index);
    }
    value /= averageValues.size();
    averageValues.clear();
    return value;
}

void TemperatureController::process() {
    float temperature = thermometer->getTemperature();

//    writeAverageValue(temperature);
    //if (millis() < nextProcessTime) {
      //  return;
    //}

//    temperature = readAverageValue();
    if (temperature > temperatureDefinitionSource->getMaxTemperature() && running) {
        stopHeatingUnit();
        startIdleControlUnit();
    } else if (temperature < temperatureDefinitionSource->getMinTemperature() && !running) {
        stopIdleControlUnit();
        startHeatingUnit();
    } else if (running) {
        processHeatingUnit(temperature);
    } else {
        processIdleControlUnit(temperature);
    }
    nextProcessTime = millis() + PROCESS_INTERVAL;
}

void TemperatureController::startHeatingUnit() {
    running = true;
    heatingUnit->start();
}

void TemperatureController::stopHeatingUnit() {
    running = false;
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
    idleControlUnit->process(calculateState(temperatureDefinitionSource->getMinTemperature(), temperatureDefinitionSource->getMaxTemperature(), temperature));
}