#include "ThreeWayValveController.h"

#define REST_TIME               (5000l)   //ms
#define RELAY_RUN_TIME          (2000l) //ms

ThreeWayValveController::ThreeWayValveController(Thermometer* thermometer, int lowerRelayPin, int higherRelayPin) :
thermometer(thermometer),
lowerRelayPin(lowerRelayPin),
higherRelayPin(higherRelayPin),
fromTemperature(40),
toTemperature(45),
lastRelayRunTime(0),
currentPosition(0),
runningUntil(0),
runningRelayPin(-1) {
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
    runningRelayPin = relayPin;
    runningUntil = millis() + RELAY_RUN_TIME;

    return true;
}

void ThreeWayValveController::process() {
    if (runningRelayPin != -1) {
        if (runningUntil < millis()) {
            digitalWrite(runningRelayPin, HIGH);
            runningRelayPin = -1;
            lastRelayRunTime = millis();
        }
        return;
    }

    float currentTemp = thermometer->getTemperature();

    if (currentTemp < fromTemperature && currentPosition < 150) {
        if (runRelay(higherRelayPin))
            currentPosition++;
    } else if (currentTemp > toTemperature && currentPosition > -150) {
        if (runRelay(lowerRelayPin))
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

float ThreeWayValveController::getFromTemperature() {
    return fromTemperature;
}

float ThreeWayValveController::getToTemperature() {
    return toTemperature;
}
