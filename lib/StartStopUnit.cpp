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
stopTime(restTime),
stopped(false) {
    runningTime = 0;
    stoppedTime = 0;
}

void StartStopUnit::setMaxRunTime(long runTime) {
    maxRunTime = runTime;
}

void StartStopUnit::setStopTime(long restTime) {
    this->stopTime = restTime;
}

bool StartStopUnit::shouldStop() {
    return runningTime != 0 && millis() > runningTime + maxRunTime;
}

bool StartStopUnit::shouldStart() {
    return millis() > stoppedTime + stopTime;
}

void StartStopUnit::start() {
    unit->start();
    runningTime = millis();
    stopped = false;
}

void StartStopUnit::stop() {
    unit->stop();
    runningTime = 0;
    stopped = false;
}

void StartStopUnit::process(float state) {
    if (!stopped && shouldStop()) {
        stop();
        stoppedTime = millis();
        stopped = true;
    } else if (stopped && shouldStart()) {
        start();
        unit->process(state);
        stopped = false;
    } else if (!stopped) {
        unit->process(state);
    }
}

