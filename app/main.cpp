#include <Arduino.h>
#include <thermostat.h>

std::vector<Thermostat> thermostats;

extern HardwareSerial Serial;

void setup() { 
    initThermostats();
}

void initThermostats() {
    //krb
    thermostats.push_back(createThermostat(A0, 10, 55, 40, ControlType.COOLING));
    //podlahovka
    //TODO: add function to control if there is need to cool
    thermostats.push_back(createThermostat(A1, 11, 45, 35, ControlType.COOLING));
}

Thermostat createThermostat(int sensorPin, int controlPin, float startTemp, float stopTemp, ControlType controlType) {
    Thermostat thermostat(sensorPin);
    thermostat.setControlPin(controlPin);
    thermostat.setStartTemperature(startTemp);
    thermostat.setStopTemperature(stopTemp);
    thermostat.setControlType(controlType);
    return thermostat;
}

void loop() {

}