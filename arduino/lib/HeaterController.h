/* 
 * 
 * File:   TemperatureController.h
 * Author: wladimiiir
 *
 * Created on December 23, 2013, 9:35 PM
 */

#ifndef TEMPERATURECONTROLLER_H
#define	TEMPERATURECONTROLLER_H

#include <Arduino.h>
#include "Thermometer.h"
#include "StateUnit.h"
#include "TemperatureDefinitionSource.h"
#include "Configurator.h"

class HeaterController : public Configurator {
public:
    HeaterController(Thermometer* thermometer, TemperatureDefinitionSource* temperatureDefinitionSource, StateUnit* heatingUnit, StateUnit* idleControlUnit);
    void process();
    void setValue(String value);
    String getValue();
private:
    Thermometer* thermometer;
    TemperatureDefinitionSource* temperatureDefinitionSource;
    StateUnit* heatingUnit;
    StateUnit* idleControlUnit;
    bool heating;
    bool manualProcessing;
    unsigned long changeTime;
    String previousValue;
    String value;
    void startHeatingUnit();
    void stopHeatingUnit();
    void processHeatingUnit(float temperature);
    void startIdleControlUnit();
    void stopIdleControlUnit();
    void processIdleControlUnit(float temperature);
};

#endif	/* TEMPERATURECONTROLLER_H */

