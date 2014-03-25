/* 
 * File:   LM35Thermometer.cpp
 * Author: wladimiiir
 * 
 * Created on January 7, 2014, 8:01 PM
 */

#include "LM35Thermometer.h"

#define READ_COUNT      (10)

LM35Thermometer::LM35Thermometer(int sensorPin) :
sensorPin(sensorPin) {
    pinMode(sensorPin, INPUT);
}

float LM35Thermometer::getTemperature() {
    analogReference(INTERNAL1V1);
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

    //convert V to °C
    value = value / (10.0 / (1.1 * 1000 / 1024.0)); //10mV per C / referenceV/1024

    return value;
}


