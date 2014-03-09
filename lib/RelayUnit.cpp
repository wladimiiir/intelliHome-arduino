/* 
 * File:   RelayUnit.cpp
 * Author: wladimiiir
 * 
 * Created on December 23, 2013, 10:03 PM
 */

#include "RelayUnit.h"

RelayUnit::RelayUnit(int controlPin) :
controlPin(controlPin) {
    digitalWrite(controlPin, HIGH);
    pinMode(controlPin, OUTPUT);
    currentState = STOPPED;
}

void RelayUnit::start() {
    if (currentState == STOPPED) {
        digitalWrite(controlPin, LOW);
        currentState = STARTED;
    }
}

void RelayUnit::stop() {
    if (currentState == STARTED) {
        digitalWrite(controlPin, HIGH);
        currentState = STOPPED;
    }
}

void RelayUnit::process(float state) {
    //do nothing
}

State RelayUnit::getState() {
    return currentState;
}