#include <Arduino.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <Ethernet.h>
#include <SPI.h>
#include "../lib/LM35Thermometer.h"
#include "../lib/D18B20Thermometer.h"
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
#include "../lib/TimeLCDInfo.h"
#include "../lib/TankTemperatureLDCInfo.h"
#include "../lib/FileLogger.h"
#include "../lib/TemperatureLogger.h"
#include "../lib/WebServer.h"

#define SD_CS_PIN                        4

#define ONE_WIRE_D18B20_SENSORS_PIN     43

#define FH_3VALVE_LOW_RELAY_PIN         22
#define FH_3VALVE_HIGH_RELAY_PIN        23
#define FH_PUMP_RELAY_PIN               24
#define ELECTRIC_HEATER_RELAY_PIN       25

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);
WebServer server(80);

DeviceAddress bedroomThermometerAddress = {0x28, 0x93, 0xC3, 0x55, 0x05, 0x00, 0x00, 0xF6};
DeviceAddress outsideThermometerAddress = {0x28, 0x46, 0x45, 0x38, 0x05, 0x00, 0x00, 0x83};
DeviceAddress tankTopThermometerAddress = {0x28, 0xD8, 0x75, 0x38, 0x05, 0x00, 0x00, 0xA5};
DeviceAddress tankMidThermometerAddress = {0x28, 0x0A, 0xE3, 0x55, 0x05, 0x00, 0x00, 0x29};
DeviceAddress tankBottomThermometerAddress = {0x28, 0x10, 0x93, 0x56, 0x05, 0x00, 0x00, 0x58};
DeviceAddress floorHeatingThermometerAddress = {0x28, 0xD5, 0x92, 0x55, 0x05, 0x00, 0x00, 0x69};

MultiSensorProvider oneWireSensorProvider(ONE_WIRE_D18B20_SENSORS_PIN);
D18B20Thermometer floorHeatingThermometer(&oneWireSensorProvider, &floorHeatingThermometerAddress);
D18B20Thermometer tankTopLevelThermometer(&oneWireSensorProvider, &tankTopThermometerAddress);
D18B20Thermometer tankMidLevelThermometer(&oneWireSensorProvider, &tankMidThermometerAddress);
D18B20Thermometer tankBottomLevelThermometer(&oneWireSensorProvider, &tankBottomThermometerAddress);
D18B20Thermometer outsideThermometer(&oneWireSensorProvider, &outsideThermometerAddress);
D18B20Thermometer bedroomThermometer(&oneWireSensorProvider, &bedroomThermometerAddress);

DailyRunStrategy electricHeaterRunner;
RelayUnit electricHeaterRelay(ELECTRIC_HEATER_RELAY_PIN);
RunnerUnit electricHeaterUnit(&electricHeaterRunner, &electricHeaterRelay);
ElectricHeaterUnit electricHeater(&tankTopLevelThermometer, &electricHeaterRelay, 44.0);

ThreeWayValveController floorHeatingValve(&floorHeatingThermometer, FH_3VALVE_LOW_RELAY_PIN, FH_3VALVE_HIGH_RELAY_PIN);

DailyTemperatureDefinitionSource floorHeatingTemperatureDefinitionSource;
FloorHeatingUnit floorHeatingUnit(
        new WaterTemperatureController(&floorHeatingValve, new SimpleTemperatureDefinitionSource(30, 34)),
        new RelayUnit(FH_PUMP_RELAY_PIN),
        NULL
        );
DailyTemperatureDefinitionSource roomTemperatureDefinitionSource;
DailyRunStrategy floorHeatingIdleRunner;
TemperatureController roomTempController(
        &bedroomThermometer,
        &roomTemperatureDefinitionSource,
        new StartStopUnit(&floorHeatingUnit, MINUTE(20), MINUTE(5)),
        new RunnerUnit(&floorHeatingIdleRunner, &floorHeatingUnit)
        );

LiquidCrystal lcd(48, 46, 30, 32, 34, 36);
LCDDisplay lcdDisplay(&lcd);

TemperatureLogger temperatureLogger(new FileLogger("temps.csv"), 60 * 1000l);

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
    //    roomTemperatureDefinitionSource.add(22, 0, 23, 59, 19.5, 20.0);
    //    roomTemperatureDefinitionSource.add(0, 0, 14, 0, 20.0, 20.5);
    //    roomTemperatureDefinitionSource.add(14, 0, 15, 0, 20.5, 21.0);
    //    roomTemperatureDefinitionSource.add(15, 0, 22, 0, 21.5, 22.0);

    roomTemperatureDefinitionSource.add(0, 0, 23, 59, 20.5, 21.0);

    //    roomTemperatureDefinitionSource.add(20, 0, 23, 59, 19.5, 21.0);
    //    roomTemperatureDefinitionSource.add(17, 0, 20, 0, 21.5, 22.0);
    //    roomTemperatureDefinitionSource.add(0, 0, 17, 0, 19.5, 21.0);

    //    floorHeatingTemperatureDefinitionSource.add(0, 0, 18, 00, 31, 34);
    floorHeatingTemperatureDefinitionSource.add(15, 0, 23, 59, 35, 36);
    floorHeatingTemperatureDefinitionSource.add(0, 0, 15, 0, 33, 36);
}

void setupLCDDisplay() {
    pinMode(53, OUTPUT);
    digitalWrite(53, HIGH);

    LCDSpecialCharacters::initSpecialCharacters(&lcd);
    lcd.begin(16, 2);
    lcd.write("Starting...");

    lcdDisplay.addLCDInfo(new TimeLCDInfo());
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Bedroom         ", &bedroomThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Floor heating   ", &floorHeatingThermometer));
    lcdDisplay.addLCDInfo(new TankTemperatureLDCInfo(&tankTopLevelThermometer, &tankMidLevelThermometer, &tankBottomLevelThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Outside         ", &outsideThermometer));
}

void setupLoggers() {
    temperatureLogger.registerThermometer(&bedroomThermometer);
    temperatureLogger.registerThermometer(&outsideThermometer);
    temperatureLogger.registerThermometer(&tankTopLevelThermometer);
    temperatureLogger.registerThermometer(&tankMidLevelThermometer);
    temperatureLogger.registerThermometer(&tankBottomLevelThermometer);
}

void setupSDCard() {
    if (!SD.begin(SD_CS_PIN)) {
        lcd.clear();
        lcd.write("SD card:");
        lcd.setCursor(0, 1);
        lcd.write("FAILED");
    } else {
        lcd.clear();
        lcd.write("SD card:");
        lcd.setCursor(0, 1);
        lcd.write("READY");
    }
    delay(500);
}


void setupWebServer() {
    Ethernet.begin(mac, ip);
    server.begin();
    
    server.registerThermometerReplace("outside", &outsideThermometer);
    server.registerThermometerReplace("bedroom", &bedroomThermometer);
    server.registerThermometerReplace("tankTop", &tankTopLevelThermometer);
    server.registerThermometerReplace("tankMiddle", &tankMidLevelThermometer);
    server.registerThermometerReplace("tankBottom", &tankBottomLevelThermometer);
    server.registerThermometerReplace("floorHeating", &floorHeatingThermometer);
    
    server.registerStateUnitReplace("floorHeatingState", &floorHeatingUnit);
    server.registerStateUnitReplace("electricHeaterState", &electricHeaterUnit);
    
    lcd.clear();
    lcd.write("Server on:");
    lcd.setCursor(0, 1);
    Ethernet.localIP().printTo(lcd);
    delay(500);
}

void setup() {
    Serial.begin(9600);
    analogReference(INTERNAL1V1);
    
    setTime(12, 43, 0, 9, 3, 2014);
    
    setupThreeWayValveControllers();
    setupRunTimeSources();
    setupTemperatureDefinitionSources();
    setupLCDDisplay();
    setupLoggers();
    setupSDCard();
    setupWebServer();
//    oneWireSensorProvider.printAddresses();
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
    Serial.print("Floor heating temperature: ");
    printTemperature(floorHeatingThermometer.getTemperature());
    Serial.print("Bedroom temperature: ");
    printTemperature(bedroomThermometer.getTemperature());
    Serial.print("Outside temperature: ");
    printTemperature(outsideThermometer.getTemperature());

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
    electricHeater.process(0);
}

unsigned long nextLCDRestart = 0;

void loop() {
    if (nextLCDRestart < millis()) {
        LCDSpecialCharacters::initSpecialCharacters(&lcd);
        lcd.begin(16, 2);
        nextLCDRestart = millis() + 10 * 1000l;
    }
    //        printDebugInfo();
    processModeB();
    lcdDisplay.refresh();
    temperatureLogger.process();
    server.process();
    delay(500);
}