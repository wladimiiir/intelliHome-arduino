/* 
 * File:   Thermometer.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 9:09 PM
 */

#ifndef THERMOMETER_H
#define	THERMOMETER_H

#include <Arduino.h>
#include "ThermometerValueConverter.h"

class Thermometer {
public:
    Thermometer(int sensorPin, ThermometerValueConverter* converter);
    float getTemperature();
private:
    int sensorPin;
    ThermometerValueConverter* converter;
};

#endif	/* THERMOMETER_H */

