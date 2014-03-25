/* 
 * File:   Thermometer.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 9:09 PM
 */

#ifndef THERMOMETER_H
#define	THERMOMETER_H

#include <Arduino.h>

class Thermometer {
public:
    virtual float getTemperature() = 0;
};

#endif	/* THERMOMETER_H */

