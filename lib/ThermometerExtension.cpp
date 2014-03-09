/* 
 * File:   ThermometerExtension.cpp
 * Author: wladimiiir
 * 
 * Created on February 16, 2014, 8:10 PM
 */

#include "ThermometerExtension.h"

ThermometerExtension::ThermometerExtension(Thermometer* thermometer) :
thermometer(thermometer),
state(STALLED) {
    lastTemperature = 0;
    lastTemperatureChange = 0;
    temperatureCandidate = 0;
    stateCandidate = RISEN;
}

float ThermometerExtension::getTemperature() {
    float temperature = thermometer->getTemperature();
    if (lastTemperature != temperature)
        temperature = normalizeChange(temperature);
    return temperature;
}

float ThermometerExtension::normalizeChange(float newTemperature) {
    if (lastTemperatureChange == 0) {
        //after start
        lastTemperature = newTemperature;
        lastTemperatureChange = millis();
        return newTemperature;
    }

    if (newTemperature != temperatureCandidate) {
        temperatureCandidate = newTemperature;
        lastTemperatureChange = millis();
        updateState(lastTemperature, newTemperature);
    }
    if (millis() > (lastTemperatureChange + TEMPERATURE_CHANGE_TIME)) {
        lastTemperature = newTemperature;
        lastTemperatureChange = millis();
    }

    return lastTemperature;
}

void ThermometerExtension::updateState(float oldTemperature, float newTemperature) {
    switch (stateCandidate) {
        case RISEN:
            if (oldTemperature > newTemperature) {
                stateCandidate = STALLED;
            } else {
                state = RISEN;
            }
            break;
        case FALLEN:
            if (oldTemperature < newTemperature) {
                stateCandidate = STALLED;
            } else {
                state = FALLEN;
            }
            break;
        case STALLED:
            if (oldTemperature > newTemperature) {
                stateCandidate = FALLEN;
            } else {
                stateCandidate = RISEN;
            }
            state = STALLED;
            break;
    }
}

TemperatureState ThermometerExtension::getTemperatureState() {
    return state;
}
