/* 
 * File:   RestableUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 9:35 AM
 */

#include "StartStopUnit.h"

StartStopUnit::StartStopUnit(StateUnit* unit, long maxRunTime, long restTime) :
unit(unit),
maxRunTime(maxRunTime),
restTime(restTime),
restingDisabled(false),
resting(false) {
    startedTime = 0;
    stoppedTime = 0;
}

void StartStopUnit::setRestingDisabled(bool disabled) {
    restingDisabled = disabled;
}

bool StartStopUnit::shouldRest() {
    return startedTime != 0 && millis() > startedTime + maxRunTime;
}

bool StartStopUnit::shouldStart() {
    return millis() > stoppedTime + restTime;
}

void StartStopUnit::start() {
    unit->start();
    startedTime = millis();
    resting = false;
}

void StartStopUnit::stop() {
    unit->stop();
    startedTime = 0;
    resting = false;
}

void StartStopUnit::process(float state) {
    if (restingDisabled) {
        start();
        unit->process(state);
    } else if (!resting && shouldRest()) {
        stop();
        stoppedTime = millis();
        resting = true;
    } else if (resting && shouldStart()) {
        start();
        unit->process(state);
        resting = false;
    } else if (!resting) {
        unit->process(state);
    }
}

State StartStopUnit::getState() {
    return startedTime != 0 ? STARTED : STOPPED;
}

