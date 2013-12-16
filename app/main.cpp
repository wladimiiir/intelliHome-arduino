#include <Arduino.h>
#include <Time.h>
#include "../lib/Thermostat.h"
#include "../lib/ThreeWayValveController.h"
#include "../lib/DailyRunner.h"

#define FLOOR_HEATING_SENSOR_PIN        A0
#define TANK_1_SENSOR_PIN               A1
#define TANK_2_SENSOR_PIN               A2

#define ELECTRIC_HEATER_RELAY_PIN       31
#define FH_PUMP_RELAY_PIN               30
#define FH_3VALVE_LOW_RELAY_PIN         50
#define FH_3VALVE_HIGH_RELAY_PIN        51

//Thermostat tank1Thermostat(TANK_1_SENSOR_PIN);
Thermostat tank2Thermostat(TANK_2_SENSOR_PIN);

DailyRunner electricHeaterRunner(ELECTRIC_HEATER_RELAY_PIN);

DailyRunner floorHeatingRunner(FH_PUMP_RELAY_PIN);
Thermostat floorHeatingThermostat(FLOOR_HEATING_SENSOR_PIN);
ThreeWayValveController floorHeatingController(&floorHeatingThermostat, FH_3VALVE_LOW_RELAY_PIN, FH_3VALVE_HIGH_RELAY_PIN);

extern HardwareSerial Serial;

void setupThermostat(Thermostat* thermostat, int controlPin, float startTemp, float stopTemp, ControlType controlType) {
    thermostat->setControlPin(controlPin);
    thermostat->setStartTemperature(startTemp);
    thermostat->setStopTemperature(stopTemp);
    thermostat->setControlType(controlType);
}

void setupThreeWayValveController(ThreeWayValveController* controller, float fromTemp, float toTemp) {
    controller->setFromTemperature(fromTemp);
    controller->setToTemperature(toTemp);
}

void setupThermostats() {
//    setupThermostat(&tank2Thermostat, -1, 25, 35, COOLING);
}

void setupThreeWayValveControllers() {
    setupThreeWayValveController(&floorHeatingController, 30.0, 31.0);
}

void setupDailyControllers() {
    //weekends
    electricHeaterRunner.addRunTime(8, 0, 0, 10, 0, 0);
    electricHeaterRunner.addRunTime(12, 0, 0, 14, 0, 0);
    electricHeaterRunner.addRunTime(16, 0, 0, 18, 0, 0);
    electricHeaterRunner.addRunTime(20, 0, 0, 22, 0, 0);
    
    for (int hour = 0; hour <= 6; hour++) {
        floorHeatingRunner.addRunTime(hour, 0, 0, hour, 15, 0);
    }
    for (int hour = 7; hour <= 16; hour++) {
        floorHeatingRunner.addRunTime(hour, 0, 0, hour, 20, 0);
    }
    for (int hour = 17; hour <= 23; hour++) {
        floorHeatingRunner.addRunTime(hour, 0, 0, hour, 20, 0);
        floorHeatingRunner.addRunTime(hour, 40, 0, hour, 59, 0);
    }
}

void printDebugInfo() {
    Serial.println("================================================");
    Serial.print("Date: "); Serial.print(day()); Serial.print("."); Serial.print(month()); Serial.print("."); Serial.println(year());
    Serial.print("Time: "); Serial.print(hour()); Serial.print(":"); Serial.print(minute()); Serial.print(":"); Serial.println(second());
    Serial.println();
    //Serial.print("Tank 2 temperature: "); Serial.print(tank2Thermostat.getCurrentTemperature()); Serial.print(" "); Serial.print((char) 176); Serial.println("C");
    Serial.print("Floor heating temperature: "); Serial.print(floorHeatingThermostat.getCurrentTemperature()); Serial.print(" "); Serial.print((char) 176); Serial.println("C");
    Serial.println("================================================");
}

void setup() {
    Serial.begin(9600);
    setupThermostats();
    setupThreeWayValveControllers();
    setupDailyControllers();
    setTime(10, 42, 00, 16, 12, 2013);
//    floorHeatingController.reset(150);
}

void loop() {
    printDebugInfo();
    electricHeaterRunner.process();

    //tank2Thermostat.process();
    if (floorHeatingRunner.isRunning()) {
        digitalWrite(FH_PUMP_RELAY_PIN, LOW);
        floorHeatingController.process();
    } else {
        digitalWrite(FH_PUMP_RELAY_PIN, HIGH);
    }
    delay(1000);
}
