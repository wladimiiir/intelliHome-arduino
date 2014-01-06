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
}

void WaterTemperatureController::process(float state) {
    float minT = temperatureDefinitionSource->getMinTemperature();
    float maxT = temperatureDefinitionSource->getMaxTemperature();
    float toT = (state / 100.0) * (maxT - minT) + minT;
    float diffT = threeWayValveController->getToTemperature() - threeWayValveController->getFromTemperature();

    Serial.print("Setting temperature (");
    Serial.print(state);
    Serial.print(")");
    Serial.print(": ");
    Serial.print(toT - diffT);
    Serial.print("-");
    Serial.println(toT);
    threeWayValveController->setFromTemperature(toT - diffT);
    threeWayValveController->setToTemperature(toT);
    threeWayValveController->process();
}

