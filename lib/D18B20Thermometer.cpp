/* 
 * File:   D18B20Thermometer.cpp
 * Author: wladimiiir
 * 
 * Created on January 7, 2014, 8:05 PM
 */

#include "D18B20Thermometer.h"

MultiSensorProvider::MultiSensorProvider(int multiSensorPin) {
    sensors = new DallasTemperature(new OneWire(multiSensorPin));
    sensors->begin();
    sensors->setWaitForConversion(false);
    nextReadingTime = 0;
}

void printAddress(DeviceAddress deviceAddress) {
    for (uint8_t i = 0; i < 8; i++) {
        // zero pad the address if necessary
        if(i > 0)
            Serial.print(", ");
        Serial.print("0x");
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
    Serial.println();
}

void MultiSensorProvider::printAddresses() {
    for (int index = 0; index < sensors->getDeviceCount(); index++) {
        DeviceAddress address;
        sensors->getAddress(address, index);
        printAddress(address);
    }
}

DeviceAddress* MultiSensorProvider::getAddress(int index) {
    DeviceAddress address;
    sensors->getAddress(address, index);
    return &address;
}

void MultiSensorProvider::initSensor(DeviceAddress* address, int resolution) {
    sensors->setResolution(*address, resolution);
    temperatures[address] = 0;
}

float MultiSensorProvider::getTemperature(DeviceAddress* sensorAddress) {
    if (millis() > nextReadingTime) {
        readTemperatures();
        nextReadingTime = millis() + WAIT_TIME;
    }

    return temperatures[sensorAddress];
}

void MultiSensorProvider::readTemperatures() {
    sensors->requestTemperatures();
    for (std::map<DeviceAddress*, float>::iterator it = temperatures.begin(); it != temperatures.end(); ++it) {
        DeviceAddress* address = (*it).first;
        temperatures[address] = sensors->getTempC(*address);
    }
}

D18B20Thermometer::D18B20Thermometer(int sensorPin) {
    provider = new MultiSensorProvider(sensorPin);
    address = provider->getAddress(0);
    provider->initSensor(address, 12);
}

D18B20Thermometer::D18B20Thermometer(MultiSensorProvider* provider, DeviceAddress* address) :
provider(provider),
address(address) {
    provider->initSensor(address, 12);
}

float D18B20Thermometer::getTemperature() {
    return provider->getTemperature(address);
}


