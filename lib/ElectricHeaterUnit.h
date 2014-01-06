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
#include "RelayUnit.h"
#include "Thermometer.h"

#define RUN_TIME    (1000l * 60)
#define STOP_TIME    (1000l * 60 * 10)

class ElectricHeaterUnit : public StateUnit {
public:
    ElectricHeaterUnit(Thermometer* tankThermometer, RelayUnit* controlRelay, float temperature);
    void start();
    void stop();
    void process(float state);
private:
    Thermometer* tankThermometer;
    RelayUnit* controlRelay;
    float temperature;

    unsigned long startedTime;
    unsigned long stoppedTime;
    
    bool shouldRun();
};

#endif	/* ELECTRICHEATERUNIT_H */

