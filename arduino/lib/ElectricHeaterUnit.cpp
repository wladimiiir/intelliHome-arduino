/* 
 * File:   ElectricHeaterUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 4, 2014, 8:51 PM
 */

#include "ElectricHeaterUnit.h"
#include "RelayUnit.h"

ElectricHeaterUnit::ElectricHeaterUnit(Thermometer* tankThermometer, StateUnit* controlUnit, float temperature, unsigned long runTime, unsigned long stopTime) :
tankThermometer(tankThermometer),
controlUnit(controlUnit),
temperature(temperature),
runTime(runTime),
stopTime(stopTime) {
    startedTime = 0;
    stoppedTime = 0;
    heating = false;
}

bool ElectricHeaterUnit::shouldRun() {
    if (tankThermometer->getTemperature() < temperature) {
        heating = true;
        return true;
    }
    if (heating && tankThermometer->getTemperature() < temperature + 1) {
        return true;
    }

    if (stopTime != 0 && startedTime == 0 && millis() - stoppedTime >= stopTime) {
        startedTime = millis();
        stoppedTime = 0;
        heating = false;
        return true;
    }

    if (runTime != 0 && stoppedTime == 0 && millis() - startedTime >= runTime) {
        startedTime = 0;
        stoppedTime = millis();
        heating = false;
        return false;
    }

    return startedTime != 0;
}

void ElectricHeaterUnit::start() {
    controlUnit->start();
    startedTime = millis();
    stoppedTime = 0;
}

void ElectricHeaterUnit::stop() {
    controlUnit->stop();
    startedTime = 0;
    stoppedTime = 0;
    heating = false;
}

void ElectricHeaterUnit::process(float state) {
    if (shouldRun()) {
        controlUnit->start();
    } else {
        controlUnit->stop();
    }
}

State ElectricHeaterUnit::getState() {
    return startedTime == 0 ? STOPPED : STARTED;
}