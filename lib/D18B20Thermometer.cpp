/* 
 * File:   D18B20Thermometer.cpp
 * Author: wladimiiir
 * 
 * Created on January 7, 2014, 8:05 PM
 */

#include "D18B20Thermometer.h"

D18B20Thermometer::D18B20Thermometer(int sensorPin) {
    sensor = new DallasTemperature(new OneWire(sensorPin));
    sensor->begin();
    DeviceAddress address;
    sensor->getAddress(address, 0);
    sensor->setResolution(address, 12);
//    sensor->setWaitForConversion(false);
}

float D18B20Thermometer::getTemperature() {
    sensor->requestTemperaturesByIndex(0);
    return sensor->getTempCByIndex(0);
}


