#include <Arduino.h>
#include <Time.h>
#include <LiquidCrystal_I2C.h>
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include "../lib/LM35Thermometer.h"
#include "../lib/D18B20Thermometer.h"
#include "../lib/ThreeWayValveController.h"
#include "../lib/DailyRunStrategy.h"
#include "../lib/WeeklyRunStrategy.h"
#include "../lib/DailyTemperatureDefinitionSource.h"
#include "../lib/SimpleTemperatureDefinitionSource.h"
#include "../lib/ConfigurableTemperatureDefinitionSource.h"
#include "../lib/ConfigurableStateUnit.h"
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
#include "../lib/UnitStateLogger.h"
#include "../lib/WebServer.h"
#include "../lib/ConfigManager.h"
#include "../lib/MinTemperatureConfigurator.h"
#include "../lib/MaxTemperatureConfigurator.h"

#define SD_CS_PIN                        4

#define ONE_WIRE_D18B20_SENSORS_PIN     38

#define ELECTRIC_HEATER_RELAY_PIN       2
#define FH_3VALVE_LOW_RELAY_PIN         3
#define FH_3VALVE_HIGH_RELAY_PIN        5
#define FH_PUMP_RELAY_PIN               6

#define IR_REMOTE_PIN                   12

//web components
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);
WebServer server(776);
ConfigManager configManager;

//thermometer addresses
DeviceAddress bedroomThermometerAddress = {0x28, 0x93, 0xC3, 0x55, 0x05, 0x00, 0x00, 0xF6};
DeviceAddress kitchenThermometerAddress = {0x28, 0xA2, 0x8C, 0x55, 0x05, 0x00, 0x00, 0xAA};
DeviceAddress outsideThermometerAddress = {0x28, 0x46, 0x45, 0x38, 0x05, 0x00, 0x00, 0x83};
DeviceAddress tankTopThermometerAddress = {0x28, 0xD8, 0x75, 0x38, 0x05, 0x00, 0x00, 0xA5};
DeviceAddress tankMidThermometerAddress = {0x28, 0x0A, 0xE3, 0x55, 0x05, 0x00, 0x00, 0x29};
DeviceAddress tankBottomThermometerAddress = {0x28, 0x10, 0x93, 0x56, 0x05, 0x00, 0x00, 0x58};
DeviceAddress floorHeatingThermometerAddress = {0x28, 0xD5, 0x92, 0x55, 0x05, 0x00, 0x00, 0x69};
DeviceAddress fireplaceExchangerThermometerAddress = {0x28, 0x53, 0x60, 0x30, 0x05, 0x00, 0x00, 0x05};

//thermometers
MultiSensorProvider oneWireSensorProvider(ONE_WIRE_D18B20_SENSORS_PIN);
D18B20Thermometer floorHeatingThermometer(&oneWireSensorProvider, &floorHeatingThermometerAddress);
D18B20Thermometer tankTopLevelThermometer(&oneWireSensorProvider, &tankTopThermometerAddress);
D18B20Thermometer tankMidLevelThermometer(&oneWireSensorProvider, &tankMidThermometerAddress);
D18B20Thermometer tankBottomLevelThermometer(&oneWireSensorProvider, &tankBottomThermometerAddress);
D18B20Thermometer outsideThermometer(&oneWireSensorProvider, &outsideThermometerAddress);
D18B20Thermometer bedroomThermometer(&oneWireSensorProvider, &bedroomThermometerAddress);
D18B20Thermometer kitchenThermometer(&oneWireSensorProvider, &kitchenThermometerAddress);
D18B20Thermometer fireplaceExchangerThermometer(&oneWireSensorProvider, &fireplaceExchangerThermometerAddress);

//electric heater
WeeklyRunStrategy electricHeaterRunner;
RelayUnit electricHeaterRelay(ELECTRIC_HEATER_RELAY_PIN);
ConfigurableStateUnit electricHeaterUnit(&electricHeaterRelay);
ElectricHeaterUnit electricHeater(&tankTopLevelThermometer, &electricHeaterUnit, 41.0);
RunnerUnit electricHeaterRunnerUnit(&electricHeaterRunner, &electricHeater);

//floor heating components
ThreeWayValveController floorHeatingValve(&floorHeatingThermometer, FH_3VALVE_LOW_RELAY_PIN, FH_3VALVE_HIGH_RELAY_PIN);
DailyTemperatureDefinitionSource autoFloorHeatingTemperatureDefinitionSource;
ConfigurableTemperatureDefinitionSource floorHeatingTemperatureDefinitionSource(&autoFloorHeatingTemperatureDefinitionSource);
FloorHeatingUnit floorHeatingUnit(
        new WaterTemperatureController(&floorHeatingValve, &floorHeatingTemperatureDefinitionSource),
        new RelayUnit(FH_PUMP_RELAY_PIN),
        new ElectricHeaterUnit(&tankMidLevelThermometer, &electricHeaterUnit, 35.0, 1000l * 10, 1000l * 60 * 10)
        );
DailyTemperatureDefinitionSource autoBedroomTemperatureDefinitionSource;
ConfigurableTemperatureDefinitionSource bedroomTemperatureDefinitionSource(&autoBedroomTemperatureDefinitionSource);
//ConfigurableTemperatureDefinitionSource bedroomTemperatureDefinitionSource(new SimpleTemperatureDefinitionSource(20.5, 21.0));
DailyRunStrategy floorHeatingIdleRunner;

//main temperature controller
TemperatureController roomTempController(
        &bedroomThermometer,
        &bedroomTemperatureDefinitionSource,
        new StartStopUnit(&floorHeatingUnit, MINUTE(20), MINUTE(5)),
        NULL
        //        new RunnerUnit(&floorHeatingIdleRunner, &floorHeatingUnit)
        );

//lcd
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LCDDisplay lcdDisplay(&lcd);

//loggers
TemperatureLogger temperatureLogger(new FileLogger("temps.csv"), 60 * 1000l);
UnitStateLogger unitStateLogger(new FileLogger("units.csv"), 60 * 1000l);

extern HardwareSerial Serial;

/* Setup functions */
void setupThreeWayValveController(ThreeWayValveController* controller, float fromTemp, float toTemp) {
    controller->setFromTemperature(fromTemp);
    controller->setToTemperature(toTemp);
}

void setupThreeWayValveControllers() {
    setupThreeWayValveController(&floorHeatingValve, 34.0, 35.0);
}

void setupRunTimeSources() {
    for (int hour = 15; hour <= 23; hour++) {
        floorHeatingIdleRunner.addRunTime(hour, 0, 0, hour, 10, 0);
    }
//    electricHeaterRunner.addRunTime(MONDAY, 18, 0, 0, 19, 0, 0);
//    electricHeaterRunner.addRunTime(WEDNESDAY, 18, 0, 0, 19, 0, 0);
//    electricHeaterRunner.addRunTime(SATURDAY, 16, 0, 0, 18, 0, 0);
}

void setupTemperatureDefinitionSources() {
    //    roomTemperatureDefinitionSource.add(22, 0, 23, 59, 19.5, 20.0);
    //    roomTemperatureDefinitionSource.add(0, 0, 14, 0, 20.0, 20.5);
    //    roomTemperatureDefinitionSource.add(14, 0, 15, 0, 20.5, 21.0);
    //    roomTemperatureDefinitionSource.add(15, 0, 22, 0, 21.5, 22.0);

    autoBedroomTemperatureDefinitionSource.add(0, 0, 4, 59, 19.5, 20.5);
    autoBedroomTemperatureDefinitionSource.add(5, 0, 18, 59, 21.7, 22.0);
    autoBedroomTemperatureDefinitionSource.add(19, 0, 23, 59, 20.0, 21.0);
    //    autoBedroomTemperatureDefinitionSource.add(21, 0, 23, 59, 19.5, 20.0);

    //    roomTemperatureDefinitionSource.add(20, 0, 23, 59, 19.5, 21.0);
    //    roomTemperatureDefinitionSource.add(17, 0, 20, 0, 21.5, 22.0);
    //    roomTemperatureDefinitionSource.add(0, 0, 17, 0, 19.5, 21.0);

    //    floorHeatingTemperatureDefinitionSource.add(0, 0, 18, 00, 31, 34);
    autoFloorHeatingTemperatureDefinitionSource.add(15, 0, 23, 59, 35, 36);
    autoFloorHeatingTemperatureDefinitionSource.add(0, 0, 15, 0, 33, 36);
}

void setupLCDDisplay() {
    Serial.println("Initializing LCD...");

    LCDSpecialCharacters::initSpecialCharacters(&lcd);
    lcd.begin(16, 2);
    lcd.write("Starting...");

    for (int i = 0; i < 3; i++) {
        lcd.backlight();
        delay(250);
        lcd.noBacklight();
        delay(250);
    }
    //    lcd.backlight(); // finish with backlight on  

    lcdDisplay.addLCDInfo(new TimeLCDInfo());
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Bedroom         ", &bedroomThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Kitchen         ", &kitchenThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Fireplace       ", &fireplaceExchangerThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Floor heating   ", &floorHeatingThermometer));
    lcdDisplay.addLCDInfo(new TankTemperatureLDCInfo(&tankTopLevelThermometer, &tankMidLevelThermometer, &tankBottomLevelThermometer));
    lcdDisplay.addLCDInfo(new ThermometerLCDInfo("Outside         ", &outsideThermometer));
}

void setupLoggers() {
    temperatureLogger.registerThermometer(&bedroomThermometer);
    temperatureLogger.registerThermometer(&kitchenThermometer);
    temperatureLogger.registerThermometer(&outsideThermometer);
    temperatureLogger.registerThermometer(&floorHeatingThermometer);
    temperatureLogger.registerThermometer(&tankTopLevelThermometer);
    temperatureLogger.registerThermometer(&tankMidLevelThermometer);
    temperatureLogger.registerThermometer(&tankBottomLevelThermometer);
    temperatureLogger.registerThermometer(&fireplaceExchangerThermometer);

    unitStateLogger.registerStateUnit(&floorHeatingUnit);
    unitStateLogger.registerStateUnit(&electricHeaterUnit);
}

void setupSDCard() {
    pinMode(53, OUTPUT); //SS pin
    //        digitalWrite(53, HIGH);

    if (!SD.begin(SD_CS_PIN)) {
        //lcd.clear();
        //lcd.write("SD card:");
        //lcd.setCursor(0, 1);
        //lcd.write("FAILED");
    } else {
        //lcd.clear();
        //lcd.write("SD card:");
        //lcd.setCursor(0, 1);
        //lcd.write("READY");
    }

    delay(500);
}

void setupWebServer() {
    Ethernet.begin(mac, ip);
    server.begin();

    server.setConfigManager(&configManager);

    server.registerThermometerReplace("outside", &outsideThermometer);
    server.registerThermometerReplace("bedroom", &bedroomThermometer);
    server.registerThermometerReplace("kitchen", &kitchenThermometer);
    server.registerThermometerReplace("tankTop", &tankTopLevelThermometer);
    server.registerThermometerReplace("tankMiddle", &tankMidLevelThermometer);
    server.registerThermometerReplace("tankBottom", &tankBottomLevelThermometer);
    server.registerThermometerReplace("floorHeating", &floorHeatingThermometer);
    server.registerThermometerReplace("fireplaceExchanger", &fireplaceExchangerThermometer);

    server.registerStateUnitReplace("floorHeatingState", &floorHeatingUnit);
    server.registerStateUnitReplace("electricHeaterState", &electricHeaterUnit);

    //lcd.clear();
    //lcd.write("Server on:");
    //lcd.setCursor(0, 1);
    //Ethernet.localIP().printTo(lcd);
    delay(1000);
}

void setupConfigManager() {
    configManager.registerConfigurator("bedroomMinTemp", new MinTemperatureConfigurator(&bedroomTemperatureDefinitionSource));
    configManager.registerConfigurator("bedroomMaxTemp", new MaxTemperatureConfigurator(&bedroomTemperatureDefinitionSource));
    configManager.registerConfigurator("floorHeatingMinTemp", new MinTemperatureConfigurator(&floorHeatingTemperatureDefinitionSource));
    configManager.registerConfigurator("floorHeatingMaxTemp", new MaxTemperatureConfigurator(&floorHeatingTemperatureDefinitionSource));
    configManager.registerConfigurator("electricHeater", &electricHeaterUnit);
    configManager.registerConfigurator("floorHeating", &roomTempController);
}

void setupTime() {
    bool externalSet = false;
    if (externalSet) {
        tmElements_t time;
        time.Day = 15;
        time.Month = 10;
        time.Year = 2014 - 1970;

        time.Hour = 19;
        time.Minute = 14;
        time.Second = 0;
        RTC.write(time);
    }
    setTime(RTC.get());
}

/* Main setup function */
void setup() {
    Serial.begin(9600);
    analogReference(INTERNAL1V1);

    //setupLCDDisplay();
    setupTime();
    setupThreeWayValveControllers();
    setupRunTimeSources();
    setupTemperatureDefinitionSources();
    setupLoggers();
    setupSDCard();
    setupConfigManager();
    setupWebServer();
    oneWireSensorProvider.printAddresses();

    pinMode(31, OUTPUT);
    digitalWrite(31, HIGH);
}

/* Main heating process function */
void processHeating() {
    electricHeaterRunnerUnit.process(100);
    State state = electricHeaterRunnerUnit.getState();

    roomTempController.process();

    //check if electric heater should not be running by its runner
    if (state == STARTED && electricHeaterUnit.getState() == STOPPED) {
        electricHeaterUnit.start();
    }
}

/* Failsafe functions */
unsigned long nextLCDRestart = 0;

void processFailsafeActions() {
    //failsafe LCD
    if (nextLCDRestart < millis()) {
        LCDSpecialCharacters::initSpecialCharacters(&lcd);
        lcd.begin(16, 2);
        lcd.noBacklight();
        nextLCDRestart = millis() + 60 * 1000l;
    }
}

/* Main loop function */
void loop() {
    //processFailsafeActions();
    processHeating();
    //lcdDisplay.refresh();
    temperatureLogger.process();
    unitStateLogger.process();
    server.process();
    delay(500);
}