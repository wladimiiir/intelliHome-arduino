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
#define NORMALIZATION_TIME      (5000l)

enum TemperatureState {
    STALLED,
    FALLEN, 
    RISEN
};

class ThermometerExtension : public Thermometer {
public:
    ThermometerExtension(Thermometer* thermometer);
    float getTemperature();
    TemperatureState getTemperatureState();
private:
    Thermometer* thermometer;
    TemperatureState state;
    TemperatureState stateCandidate;
    float lastTemperature;
    float temperatureCandidate;
    unsigned long lastTemperatureChange;
    
    float normalizeChange(float temperature);
    void updateState(float oldTemperature, float newTemperature);
};

#endif	/* THERMOMETEREXTENSION_H */

