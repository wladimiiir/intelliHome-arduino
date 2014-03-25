/* 
 * File:   WaterTemperatureController.h
 * Author: wladimiiir
 *
 * Created on December 27, 2013, 10:59 PM
 */

#ifndef WATERTEMPERATURECONTROLLER_H
#define	WATERTEMPERATURECONTROLLER_H

#include <Arduino.h>
#include "StateUnit.h"
#include "ThreeWayValveController.h"
#include "DailyTemperatureDefinitionSource.h"
#include "TemperatureDefinitionSource.h"


class WaterTemperatureController : public StateUnit {
public:
    WaterTemperatureController(ThreeWayValveController* threeWayValveController, TemperatureDefinitionSource* temperatureSource);
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    ThreeWayValveController* threeWayValveController;
    TemperatureDefinitionSource* temperatureDefinitionSource;
};

#endif	/* WATERTEMPERATURECONTROLLER_H */

