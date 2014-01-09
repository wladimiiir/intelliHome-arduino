/* 
 * File:   D18B20Thermometer.h
 * Author: wladimiiir
 *
 * Created on January 7, 2014, 8:05 PM
 */

#ifndef D18B20THERMOMETER_H
#define	D18B20THERMOMETER_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Thermometer.h"

#define WAIT_TIME       (750l)

class D18B20Thermometer : public Thermometer {
public:
    D18B20Thermometer(int sensorPin);
    float getTemperature();
private:
    DallasTemperature* sensor;
    float currentTemperature;
    unsigned long nextReadingTime;
};

#endif	/* D18B20THERMOMETER_H */

