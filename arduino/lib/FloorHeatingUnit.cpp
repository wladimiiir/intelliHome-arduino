/* 
 * File:   FloorHeatingUnit.cpp
 * Author: wladimiiir
 * 
 * Created on December 29, 2013, 5:01 PM
 */

#include "FloorHeatingUnit.h"
#include "WaterTemperatureController.h"

FloorHeatingUnit::FloorHeatingUnit(WaterTemperatureController* waterTemperatureController, RelayUnit* pumpUnit, StateUnit* listener) :
waterTemperatureController(waterTemperatureController),
pumpUnit(pumpUnit),
listener(listener) {
}

void FloorHeatingUnit::start() {
    waterTemperatureController->start();
    pumpUnit->start();
    if(listener != NULL)
        listener->start();
}

void FloorHeatingUnit::stop() {
    waterTemperatureController->stop();
    pumpUnit->stop();
    if(listener != NULL)
        listener->stop();
}

void FloorHeatingUnit::process(float state) {
    waterTemperatureController->process(state);
    pumpUnit->process(state);
    if(listener != NULL)
        listener->process(state);
}

State FloorHeatingUnit::getState() {
    return pumpUnit->getState();
}
