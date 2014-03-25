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

#define RUN_TIME    (1000l * 10)
#define STOP_TIME    (1000l * 60 * 10)

class ElectricHeaterUnit : public StateUnit {
public:
    ElectricHeaterUnit(Thermometer* tankThermometer, StateUnit* controlRelay, float temperature, unsigned long runTime = 0, unsigned long stopTime = 0);
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    Thermometer* tankThermometer;
    StateUnit* controlUnit;
    float temperature;

    unsigned long runTime;
    unsigned long stopTime;

    unsigned long startedTime;
    unsigned long stoppedTime;
    bool heating;
    
    bool shouldRun();
};

#endif	/* ELECTRICHEATERUNIT_H */

