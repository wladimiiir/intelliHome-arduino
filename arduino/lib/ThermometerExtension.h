/* 
 * File:   ThermometerExtension.h
 * Author: wladimiiir
 *
 * Created on February 16, 2014, 8:10 PM
 */

#ifndef THERMOMETEREXTENSION_H
#define	THERMOMETEREXTENSION_H

#include <Arduino.h>
#include "Thermometer.h"

#define TEMPERATURE_CHANGE_TIME (3000l)

enum Tendency {
    RESTING,
    DECREASING, 
    INCREASING
};

class ThermometerExtension : public Thermometer {
public:
    ThermometerExtension(Thermometer* thermometer);
    float getTemperature();
    Tendency getTendency();
private:
    Thermometer* thermometer;
    Tendency tendency;
    Tendency tendencyCandidate;
    float lastTemperature;
    float temperatureCandidate;
    unsigned long lastTemperatureChange;
    
    float normalizeChange(float temperature);
    void updateTendency(float oldTemperature, float newTemperature);
};

#endif	/* THERMOMETEREXTENSION_H */

