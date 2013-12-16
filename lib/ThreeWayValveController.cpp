#include "ThreeWayValveController.h"

#define REST_TIME               (10000l)   //ms
#define RELAY_RUN_TIME          (2000l) //ms

ThreeWayValveController::ThreeWayValveController(Thermostat* thermometer, int lowerRelayPin, int higherRelayPin) :
thermometer(thermometer),
lowerRelayPin(lowerRelayPin),
higherRelayPin(higherRelayPin),
fromTemperature(40),
toTemperature(45),
lastRelayRunTime(0),
currentPosition(0) {
    digitalWrite(lowerRelayPin, HIGH);
    digitalWrite(higherRelayPin, HIGH);
    pinMode(lowerRelayPin, OUTPUT);
    pinMode(higherRelayPin, OUTPUT);
}

bool ThreeWayValveController::runRelay(int relayPin) {
    if (millis() < (lastRelayRunTime + REST_TIME)) {
        return false;
    }

    //run relay for time specified
    digitalWrite(relayPin, LOW);
    delay(RELAY_RUN_TIME);
    digitalWrite(relayPin, HIGH);
    lastRelayRunTime = millis();
    
    return true;
}

void ThreeWayValveController::process() {
    float currentTemp = thermometer->getCurrentTemperature();

    if (currentTemp < fromTemperature && currentPosition < 50) {
        if(runRelay(higherRelayPin))
                currentPosition++;
    } else if (currentTemp > toTemperature && currentPosition > -50) {
        if(runRelay(lowerRelayPin))
                currentPosition--;
    }
}

void ThreeWayValveController::reset(unsigned long cycleSeconds) {
    //move to the lowest position
    digitalWrite(lowerRelayPin, LOW);
    delay(cycleSeconds * 1000);
    digitalWrite(lowerRelayPin, HIGH);
    //move to the center position
    digitalWrite(higherRelayPin, LOW);
    delay(cycleSeconds * 1000 / 2);
    digitalWrite(higherRelayPin, HIGH);
    
    currentPosition = 0;
}

void ThreeWayValveController::setFromTemperature(float temp) {
    fromTemperature = temp;
}

void ThreeWayValveController::setToTemperature(float temp) {
    toTemperature = temp;
}
