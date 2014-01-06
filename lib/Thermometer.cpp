/* 
 * File:   Thermometer.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 9:09 PM
 */

#include "Thermometer.h"

#define READ_COUNT      (10)

Thermometer::Thermometer(int sensorPin, ThermometerValueConverter* converter) :
sensorPin(sensorPin),
converter(converter) {
    pinMode(sensorPin, INPUT);
}

float Thermometer::getTemperature() {
    analogReference(converter->getAnalogReference());
    //read one value for "reseting" arduino input pin
    analogRead(sensorPin);
    delay(50);

    //read x times and make average
    float value = 0.0;
    for (int i = 0; i < READ_COUNT; i++) {
        value += analogRead(sensorPin);
        delay(20);
    }
    value /= (float) READ_COUNT;
    value = converter->convertValue(value);

    return value;
}


