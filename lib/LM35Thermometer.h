/* 
 * File:   LM35Thermometer.h
 * Author: wladimiiir
 *
 * Created on January 7, 2014, 8:01 PM
 */

#ifndef LM35THERMOMETER_H
#define	LM35THERMOMETER_H

#include <Arduino.h>
#include "Thermometer.h"


class LM35Thermometer : public Thermometer {
public:
    LM35Thermometer(int sensorPin);
    float getTemperature();
private:
    int sensorPin;
};

#endif	/* LM35THERMOMETER_H */

