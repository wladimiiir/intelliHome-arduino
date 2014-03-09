/* 
 * File:   WaterTemperatureController.cpp
 * Author: wladimiiir
 * 
 * Created on December 27, 2013, 10:59 PM
 */

#include "WaterTemperatureController.h"
#include "ThreeWayValveController.h"

WaterTemperatureController::WaterTemperatureController(ThreeWayValveController* threeWayValveController, TemperatureDefinitionSource* temperatureSource) :
threeWayValveController(threeWayValveController),
temperatureDefinitionSource(temperatureSource) {
}

void WaterTemperatureController::start() {
}

void WaterTemperatureController::stop() {
    threeWayValveController->stop();
}

void WaterTemperatureController::process(float state) {
    float minT = temperatureDefinitionSource->getMinTemperature();
    float maxT = temperatureDefinitionSource->getMaxTemperature();
    float toT = (state / 100.0) * (maxT - minT) + minT;
    float diffT = threeWayValveController->getToTemperature() - threeWayValveController->getFromTemperature();

    threeWayValveController->setFromTemperature(toT - diffT);
    threeWayValveController->setToTemperature(toT);
    threeWayValveController->process();
}

State WaterTemperatureController::getState() {
    return STARTED;
}

