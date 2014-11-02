/* 
 * File:   CoolerController.cpp
 * Author: wladimiiir
 * 
 * Created on October 26, 2014, 2:46 PM
 */

#include "CoolerController.h"
#include "AppHelper.h"

CoolerController::CoolerController(
        Thermometer* thermometer,
        TemperatureDefinitionSource* temperatureDefinitionSource,
        StateUnit* coolerUnit
        ) :
thermometer(thermometer),
temperatureDefinitionSource(temperatureDefinitionSource),
coolerUnit(coolerUnit),
started(false) {
}

void CoolerController::process() {
    float temperature = thermometer->getTemperature();

    if (started && temperature < temperatureDefinitionSource->getMinTemperature()) {
        stopCoolerUnit();
    } else if (!started && temperature >= temperatureDefinitionSource->getMaxTemperature()) {
        startCoolerUnit();
    } else if (started) {
        processCoolerUnit(temperature);
    }
}

void CoolerController::startCoolerUnit() {
    coolerUnit->start();
    started = true;
}

void CoolerController::stopCoolerUnit() {
    coolerUnit->stop();
    started = false;
}

void CoolerController::processCoolerUnit(float temperature) {
    coolerUnit->process(AppHelper::calculateState(temperatureDefinitionSource->getMinTemperature(), temperatureDefinitionSource->getMaxTemperature(), temperature));
}




