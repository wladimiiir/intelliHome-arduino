/* 
 * File:   RunnerUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 12:03 PM
 */

#include "RunnerUnit.h"

RunnerUnit::RunnerUnit(RunStrategy* runner, StateUnit* runningUnit) :
runner(runner),
runningUnit(runningUnit),
running(false) {
}

void RunnerUnit::start() {
    if (running)
        return;

    runningUnit->start();
    running = true;
}

void RunnerUnit::stop() {
    if (!running)
        return;

    runningUnit->stop();
    running = false;
}

void RunnerUnit::process(float state) {
    if (runner->isRunning()) {
        start();
        runningUnit->process(state);
    } else {
        stop();
    }
}

State RunnerUnit::getState() {
    return runningUnit->getState();
}


