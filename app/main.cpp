#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include "../lib/Thermostat.h"
#include "../lib/ThreeWayValveController.h"

std::vector<Thermostat> thermostats;
Thermostat *threeWayValveControllerThermostat = NULL;
std::vector<ThreeWayValveController> threeWayValveControllers;

extern HardwareSerial Serial;

Thermostat createThermostat(int sensorPin, int controlPin, float startTemp, float stopTemp, ControlType controlType) {
    Thermostat thermostat(sensorPin);
    thermostat.setControlPin(controlPin);
    thermostat.setStartTemperature(startTemp);
    thermostat.setStopTemperature(stopTemp);
    thermostat.setControlType(controlType);
    return thermostat;
}

void setupThermostats() {
    //krb
    thermostats.push_back(createThermostat(A0, 10, 55, 40, COOLING));
    //podlahovka
    //TODO: add function to control if there is need to cool
    thermostats.push_back(createThermostat(A1, 11, 45, 35, COOLING));
    threeWayValveControllerThermostat = thermostats.end();
}

ThreeWayValveController createThreeWayValveController(Thermostat thermometer, int lowerRelayPin, int higherRelayPin, float fromTemp, float toTemp) {
    ThreeWayValveController controller(thermometer, lowerRelayPin, higherRelayPin);
    controller.setFromTemperature(fromTemp);
    controller.setToTemperature(toTemp);
    return controller;
}

void setupThreeWayValveControllers() {
    threeWayValveControllers.push_back(createThreeWayValveController(*threeWayValveControllerThermostat, 20, 21, 40, 45));
}

void setup() {
    setupThermostats();
    setupThreeWayValveControllers();
}

void loop() {
    for (std::vector<Thermostat>::iterator it = thermostats.begin(); it != thermostats.end(); ++it) {
        it->process();
    }
    for (std::vector<ThreeWayValveController>::iterator it = threeWayValveControllers.begin(); it != threeWayValveControllers.end(); ++it) {
        it->process();
    }
}