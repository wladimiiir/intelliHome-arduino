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
}

void RelayUnit::start() {
    digitalWrite(controlPin, LOW);
}

void RelayUnit::stop() {
    digitalWrite(controlPin, HIGH);
}

void RelayUnit::process(float state) {
    //do nothing
}
