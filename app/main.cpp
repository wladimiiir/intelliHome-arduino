#include <Arduino.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include "../lib/LM35Thermometer.h"
#include "../lib/D18B20Thermometer.h"
#include "../lib/Thermostat.h"
#include "../lib/ThreeWayValveController.h"
#include "../lib/DailyRunStrategy.h"
#include "../lib/DailyTemperatureDefinitionSource.h"
#include "../lib/SimpleTemperatureDefinitionSource.h"
#include "../lib/FloorHeatingUnit.h"
#include "../lib/WaterTemperatureController.h"
#include "../lib/TemperatureController.h"
#include "../lib/RunnerUnit.h"
#include "../lib/StartStopUnit.h"
#include "../lib/ElectricHeaterUnit.h"
#include "../lib/LCDDisplay.h"
#include "../lib/ThermometerLCDInfo.h"

#define FLOOR_HEATING_SENSOR_PIN                A0
#define TANK_MID_LEVEL_SENSOR_PIN               A1
#define TANK_FLOOR_HEATING_OUT_SENSOR_PIN       A2
#define BEDROOM_SENSOR_PIN                      40

#define ELECTRIC_HEATER_RELAY_PIN       31
#define FH_PUMP_RELAY_PIN               30
#define FH_3VALVE_LOW_RELAY_PIN         50
#define FH_3VALVE_HIGH_RELAY_PIN        51


LM35Thermometer tankFloorHeatingOutThermometer(TANK_FLOOR_HEATING_OUT_SENSOR_PIN);
LM35Thermometer tankMidLevelThermometer(TANK_MID_LEVEL_SENSOR_PIN);

DailyRunStrategy electricHeaterRunner;
RelayUnit electricHeaterRelay(ELECTRIC_HEATER_RELAY_PIN);
RunnerUnit electricHeaterUnit(&electricHeaterRunner, &electricHeaterRelay);
ElectricHeaterUnit electricHeater(&tankFloorHeatingOutThermometer, &electricHeaterRelay, 24.0);

LM35Thermometer floorHeatingThermometer(FLOOR_HEATING_SENSOR_PIN);
D18B20Thermometer bedroomRoomThermometer(BEDROOM_SENSOR_PIN);
ThreeWayValveController floorHeatingValve(&floorHeatingThermometer, FH_3VALVE_LOW_RELAY_PIN, FH_3VALVE_HIGH_RELAY_PIN);

DailyTemperatureDefinitionSource roomTemperatureDefinitionSource;
FloorHeatingUnit floorHeatingUnit(
        new WaterTemperatureController(&floorHeatingValve, new SimpleTemperatureDefinitionSource(25, 35)),
        new RelayUnit(FH_PUMP_RELAY_PIN),
        &electricHeater
        );
DailyRunStrategy floorHeatingIdleRunner;
TemperatureController roomTempController(
        &bedroomRoomThermometer,
        &roomTemperatureDefinitionSource,
        new StartStopUnit(&floorHeatingUnit, MINUTE(20), MINUTE(10)),
        new RunnerUnit(&floorHeatingIdleRunner, &floorHeatingUnit)
        );

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
LCDDisplay lcdDisplay(&lcd);

extern HardwareSerial Serial;

void setupThreeWayValveController(ThreeWayValveController* controller, float fromTemp, float toTemp) {
    controller->setFromTemperature(fromTemp);
    controller->setToTemperature(toTemp);
}

void setupThreeWayValveControllers() {
    setupThreeWayValveController(&floorHeatingValve, 30.0, 31.0);
}

void setupRunTimeSources() {
    for (int hour = 0; hour <= 23; hour++) {
        floorHeatingIdleRunner.addRunTime(hour, 0, 0, hour, 10, 0);
    }
}

void setupTemperatureDefinitionSources() {
    roomTemperatureDefinitionSource.add(21, 0, 23, 59, 19.5, 20.0);
    roomTemperatureDefinitionSource.add(0, 0, 6, 0, 19.0, 19.5);
    roomTemperatureDefinitionSource.add(6, 0, 15, 0, 20.0, 20.5);
    roomTemperatureDefinitionSource.add(15, 0, 17, 0, 21.5, 22.0);
    roomTemperatureDefinitionSource.add(17, 0, 21, 0, 21.0, 21.5);
}

void setupLCDDisplay() {
    lcd.begin(16, 2);
    lcd.print("Starting...");

    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Bedroom:        ", &bedroomRoomThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Floor heating:  ", &floorHeatingThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Tank FH out:    ", &tankFloorHeatingOutThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Tank mid level: ", &tankMidLevelThermometer));
}

void setup() {
    Serial.begin(9600);
    analogReference(INTERNAL1V1);
    setupThreeWayValveControllers();
    setupRunTimeSources();
    setupTemperatureDefinitionSources();
    setupLCDDisplay();
    setTime(18, 15, 00, 8, 1, 2014);
    //    floorHeatingController.reset(150);
}

void printDate() {
    Serial.print("Date: ");
    Serial.print(day());
    Serial.print(".");
    Serial.print(month());
    Serial.print(".");
    Serial.println(year());
}

void printTime() {
    Serial.print("Time: ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.println(second());
}

void printTemperature(float temp) {
    Serial.print(temp);
    Serial.print(" ");
    Serial.print((char) 176);
    Serial.println("C");
}

void printDebugInfo() {
    Serial.println("================================================");
    printDate();
    printTime();

    Serial.println();

    Serial.print("Tank mid level temperature: ");
    printTemperature(tankMidLevelThermometer.getTemperature());
    Serial.print("Tank floor heating out temperature: ");
    printTemperature(tankFloorHeatingOutThermometer.getTemperature());
    Serial.print("Floor heating temperature: ");
    printTemperature(floorHeatingThermometer.getTemperature());
    Serial.print("Bedroom temperature: ");
    printTemperature(bedroomRoomThermometer.getTemperature());

    Serial.println("================================================");
}

void processModeA() {
    electricHeaterUnit.process(100);

    //tank2Thermostat.process();
    if (floorHeatingIdleRunner.isRunning()) {
        digitalWrite(FH_PUMP_RELAY_PIN, LOW);
        floorHeatingValve.process();
    } else {
        digitalWrite(FH_PUMP_RELAY_PIN, HIGH);
    }
}

void processModeB() {
    roomTempController.process();
}

void loop() {
    //    printDebugInfo();
    processModeB();
    lcdDisplay.refresh();
    delay(500);
}