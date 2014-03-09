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
#include <StandardCplusplus.h>
#include <map>
#include "Thermometer.h"

#define WAIT_TIME       (750l)

class MultiSensorProvider {
public:
    MultiSensorProvider(int multiSensorPin);
    DeviceAddress* getAddress(int index);
    void initSensor(DeviceAddress* address, int resolution);
    float getTemperature(DeviceAddress* sensorAddress);
    void printAddresses();
private:
    DallasTemperature* sensors;
    std::map<DeviceAddress*, float> temperatures;
    
    unsigned long nextReadingTime;
    void readTemperatures();
};

class D18B20Thermometer : public Thermometer {
public:
    D18B20Thermometer(int sensorPin);
    D18B20Thermometer(MultiSensorProvider* provider, DeviceAddress* address);
    float getTemperature();
private:
    MultiSensorProvider* provider;
    DeviceAddress* address;
};

#endif	/* D18B20THERMOMETER_H */

