#include "ThreeWayValveController.h"

#define REST_TIME               (10000l)   //ms
#define RELAY_RUN_TIME          (1000l) //ms

ThreeWayValveController::ThreeWayValveController(Thermostat thermometer, int lowerRelayPin, int higherRelayPin) :
thermometer(&thermometer),
lowerRelayPin(lowerRelayPin),
higherRelayPin(higherRelayPin),
fromTemperature(40),
toTemperature(45),
lastRelayRunTime(0){
    pinMode(lowerRelayPin, OUTPUT);
    pinMode(higherRelayPin, OUTPUT);
    digitalWrite(lowerRelayPin, LOW);
    digitalWrite(higherRelayPin, LOW);
}

void ThreeWayValveController::runRelay(int relayPin) {
    if(millis() < (lastRelayRunTime + REST_TIME)) {
        return;
    }
    
    //run relay for time specified
    digitalWrite(relayPin, HIGH);
    delay(RELAY_RUN_TIME);
    digitalWrite(relayPin, LOW);
    lastRelayRunTime = millis();
}

void ThreeWayValveController::process() {
    float currentTemp = thermometer->getCurrentTemperature();
    
    if(currentTemp < fromTemperature) {
        runRelay(higherRelayPin);
    } else if(currentTemp > toTemperature) {
        runRelay(lowerRelayPin);
    }
}

void ThreeWayValveController::setFromTemperature(float temp) {
    fromTemperature = temp;
}

void ThreeWayValveController::setToTemperature(float temp) {
    toTemperature = temp;
}
