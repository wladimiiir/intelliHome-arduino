/* 
 * File:   TemperatureController.cpp
 * Author: wladimiiir
 * 
 * Created on December 23, 2013, 9:35 PM
 */

#include "HeaterController.h"
#include "TemperatureDefinitionSource.h"
#include "AppHelper.h"
#include <StandardCplusplus.h>
#include <vector>

HeaterController::HeaterController(
        Thermometer* thermometer,
        TemperatureDefinitionSource* temperatureDefinitionSource,
        StateUnit* heatingUnit,
        StateUnit* idleControlUnit
        ) :
thermometer(thermometer),
temperatureDefinitionSource(temperatureDefinitionSource),
heatingUnit(heatingUnit),
idleControlUnit(idleControlUnit),
heating(false),
manualProcessing(false),
changeTime(0),
previousValue("Auto"),
value("Auto") {
}

void HeaterController::process() {
    float temperature = thermometer->getTemperature();

    if (manualProcessing) {
        if (changeTime != 0 && millis() >= changeTime) {
            setValue(previousValue);
        }
        if (heating) {
            processHeatingUnit(temperature);
        }
        return;
    }

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

void HeaterController::setValue(String value) {
    this->previousValue = this->value;
    int separatorIndex = value.indexOf(';');
    unsigned long forSeconds = separatorIndex > 0 ? atol(value.substring(separatorIndex + 1).c_str()) : 0;
    value = separatorIndex > 0 ? value.substring(0, separatorIndex) : value;
    if (value.equals("Auto")) {
        manualProcessing = false;
        this->value = value;
    } else if (value.equals("On")) {
        startHeatingUnit();
        manualProcessing = true;
        this->value = value;
    } else if (value.equals("Off")) {
        stopHeatingUnit();
        manualProcessing = true;
        this->value = value;
    }
    changeTime = forSeconds == 0 ? 0 : (millis() + forSeconds * 1000);
}

String HeaterController::getValue() {
    return value;
}

void HeaterController::startHeatingUnit() {
    heating = true;
    heatingUnit->start();
}

void HeaterController::stopHeatingUnit() {
    heating = false;
    heatingUnit->stop();
}

void HeaterController::processHeatingUnit(float temperature) {
    float minTemperature;
    if (idleControlUnit != NULL) {
        minTemperature = (temperatureDefinitionSource->getMinTemperature() + temperatureDefinitionSource->getMaxTemperature()) / 2;
    } else {
        minTemperature = temperatureDefinitionSource->getMinTemperature();
    }

    heatingUnit->process(manualProcessing ? 100 : AppHelper::calculateState(minTemperature, temperatureDefinitionSource->getMaxTemperature(), temperature));
}

void HeaterController::startIdleControlUnit() {
    if (idleControlUnit == NULL)
        return;
    idleControlUnit->start();
}

void HeaterController::stopIdleControlUnit() {
    if (idleControlUnit == NULL)
        return;
    idleControlUnit->stop();
}

void HeaterController::processIdleControlUnit(float temperature) {
    if (idleControlUnit == NULL)
        return;
    //    if (temperature > temperatureDefinitionSource->getMaxTemperature()) {
    //        idleControlUnit->stop();
    //        return;
    //    }
    idleControlUnit->process(AppHelper::calculateState(temperatureDefinitionSource->getMinTemperature(), temperatureDefinitionSource->getMaxTemperature(), temperature));
}