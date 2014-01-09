/* 
 * File:   ElectricHeaterUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 4, 2014, 8:51 PM
 */

#include "ElectricHeaterUnit.h"
#include "RelayUnit.h"

ElectricHeaterUnit::ElectricHeaterUnit(Thermometer* tankThermometer, RelayUnit* controlRelay, float temperature) :
tankThermometer(tankThermometer),
controlRelay(controlRelay),
temperature(temperature) {
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

    if (startedTime == 0 && millis() - stoppedTime > STOP_TIME) {
        startedTime = millis();
        stoppedTime = 0;
        return true;
    }

    if (stoppedTime == 0 && millis() - startedTime > RUN_TIME) {
        startedTime = 0;
        stoppedTime = millis();
        heating = false;
        return false;
    }

    return startedTime != 0;
}

void ElectricHeaterUnit::start() {
    controlRelay->start();
    startedTime = millis();
    stoppedTime = 0;
}

void ElectricHeaterUnit::stop() {
    controlRelay->stop();
    startedTime = 0;
    stoppedTime = 0;
    heating = false;
}

void ElectricHeaterUnit::process(float state) {
    if (shouldRun()) {
        controlRelay->start();
    } else {
        controlRelay->stop();
    }
}