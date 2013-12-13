#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <Time.h>
#include "../lib/Thermostat.h"
#include "../lib/ThreeWayValveController.h"
#include "../lib/DailyRunner.h"

#define FLOOR_HEATING_SENSOR_PIN        A0
#define TANK_1_SENSOR_PIN               A1
#define TANK_2_SENSOR_PIN               A2

#define ELECTRIC_HEATER_RELAY_PIN       30
#define FH_PUMP_RELAY_PIN               31
#define FH_3VALVE_LOW_RELAY_PIN         50
#define FH_3VALVE_HIGH_RELAY_PIN        51

//Thermostat tank1Thermostat(TANK_1_SENSOR_PIN);
Thermostat tank2Thermostat(TANK_2_SENSOR_PIN);

DailyRunner electricHeaterRunner(ELECTRIC_HEATER_RELAY_PIN);

DailyRunner floorHeatingRunner(FH_PUMP_RELAY_PIN);
Thermostat floorHeatingThermostat(FLOOR_HEATING_SENSOR_PIN);
ThreeWayValveController floorHeatingController(floorHeatingThermostat, FH_3VALVE_LOW_RELAY_PIN, FH_3VALVE_HIGH_RELAY_PIN);

extern HardwareSerial Serial;

void setupThermostat(Thermostat thermostat, int controlPin, float startTemp, float stopTemp, ControlType controlType) {
    thermostat.setControlPin(controlPin);
    thermostat.setStartTemperature(startTemp);
    thermostat.setStopTemperature(stopTemp);
    thermostat.setControlType(controlType);
}

void setupThreeWayValveController(ThreeWayValveController controller, float fromTemp, float toTemp) {
    controller.setFromTemperature(fromTemp);
    controller.setToTemperature(toTemp);
}

void setupThermostats() {
    setupThermostat(tank2Thermostat, -1, 25, 35, COOLING);
}

void setupThreeWayValveControllers() {
    setupThreeWayValveController(floorHeatingController, 40, 45);
}

void setupDailyControllers() {
    //weekends
    electricHeaterRunner.addRunTime(3, 0, 0, 6, 0, 0);
    for (int hour = 0; hour <= 6; hour++) {
        floorHeatingRunner.addRunTime(hour, 0, 0, hour, 20, 0);
    }
    for (int hour = 7; hour <= 23; hour++) {
        floorHeatingRunner.addRunTime(hour, 0, 0, hour, 45, 0);
    }
}

void printDebugInfo() {
    Serial.println("================================================");
    Serial.print("Date: "); Serial.print(day()); Serial.print("."); Serial.print(month()); Serial.print("."); Serial.println(year());
    Serial.print("Time: "); Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());
    Serial.println();
    Serial.print("Tank 2 temperature: "); Serial.print(tank2Thermostat.getCurrentTemperature()); Serial.println(" °C");
    Serial.print("Floor heating temperature: "); Serial.print(floorHeatingThermostat.getCurrentTemperature()); Serial.println(" °C");
    Serial.println("================================================");
}

void setup() {
    Serial.begin(9600);
    setupThermostats();
    setupThreeWayValveControllers();
    setTime(18, 0, 0, 13, 0, 2013);
}

void loop() {
//    printDebugInfo();
    electricHeaterRunner.process();
    
    tank2Thermostat.process();
    if(!floorHeatingRunner.isRunning())
        digitalWrite(FH_PUMP_RELAY_PIN, LOW);
    floorHeatingController.process();
    delay(1000);
}
