/* 
 * File:   ThermometerExtension.cpp
 * Author: wladimiiir
 * 
 * Created on February 16, 2014, 8:10 PM
 */

#include "ThermometerExtension.h"

ThermometerExtension::ThermometerExtension(Thermometer* thermometer) :
thermometer(thermometer),
tendency(RESTING) {
    lastTemperature = 0;
    lastTemperatureChange = 0;
    temperatureCandidate = 0;
    tendencyCandidate = RESTING;
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
    } else if (millis() > (lastTemperatureChange + TEMPERATURE_CHANGE_TIME)) {
        updateTendency(lastTemperature, newTemperature);
        lastTemperature = newTemperature;
        lastTemperatureChange = millis();
    }

    return lastTemperature;
}

void ThermometerExtension::updateTendency(float oldTemperature, float newTemperature) {
    switch (tendencyCandidate) {
        case INCREASING:
            if (newTemperature < oldTemperature) {
                tendencyCandidate = RESTING;
            } else {
                tendency = INCREASING;
            }
            break;
        case DECREASING:
            if (newTemperature > oldTemperature) {
                tendencyCandidate = RESTING;
            } else {
                tendency = DECREASING;
            }
            break;
        case RESTING:
            if (newTemperature < oldTemperature) {
                tendencyCandidate = DECREASING;
            } else {
                tendencyCandidate = INCREASING;
            }
            tendency = RESTING;
            break;
    }
}

Tendency ThermometerExtension::getTendency() {
    return tendency;
}
