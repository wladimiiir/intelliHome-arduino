/* 
 * File:   ElectricHeaterUnit.h
 * Author: wladimiiir
 *
 * Created on January 4, 2014, 8:51 PM
 */

#ifndef ELECTRICHEATERUNIT_H
#define	ELECTRICHEATERUNIT_H

#include <Arduino.h>
#include "StateUnit.h"
#include "Thermometer.h"
#include "TemperatureDefinitionSource.h"

#define RUN_TIME    (1000l * 10)
#define STOP_TIME    (1000l * 60 * 10)

class ElectricHeaterUnit : public StateUnit {
public:
    ElectricHeaterUnit(Thermometer* thermometer, StateUnit* controlRelay, TemperatureDefinitionSource* temperatureDefinition);
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    Thermometer* thermometer;
    StateUnit* controlUnit;
    TemperatureDefinitionSource* temperatureDefinition;

    bool shouldHeat();
};

#endif	/* ELECTRICHEATERUNIT_H */

