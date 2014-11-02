/* 
 * File:   CoolerController.h
 * Author: wladimiiir
 *
 * Created on October 26, 2014, 2:46 PM
 */

#ifndef COOLERCONTROLLER_H
#define	COOLERCONTROLLER_H

#include "StateUnit.h"
#include "TemperatureDefinitionSource.h"
#include "Thermometer.h"


class CoolerController {
public:
    CoolerController(Thermometer* thermometer, TemperatureDefinitionSource* temperatureDefinitionSource, StateUnit* coolerUnit);
    void process();
private:
    Thermometer* thermometer;
    TemperatureDefinitionSource* temperatureDefinitionSource;
    StateUnit* coolerUnit;
    bool started;
    void startCoolerUnit();
    void stopCoolerUnit();
    void processCoolerUnit(float temperature);
};

#endif	/* COOLERCONTROLLER_H */

