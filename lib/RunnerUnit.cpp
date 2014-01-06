/* 
 * File:   RunnerUnit.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 12:03 PM
 */

#include "RunnerUnit.h"

RunnerUnit::RunnerUnit(RunStrategy* runner, StateUnit* runningUnit) :
runner(runner),
runningUnit(runningUnit) {
}

void RunnerUnit::start() {
    runningUnit->start();
}

void RunnerUnit::stop() {
    runningUnit->stop();
}

void RunnerUnit::process(float state) {
    if(runner->isRunning()) {
        runningUnit->start();
        runningUnit->process(state);
    } else {
        runningUnit->stop();
    }
}

