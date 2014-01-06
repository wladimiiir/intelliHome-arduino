/* 
 * File:   RunnerUnit.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 12:03 PM
 */

#ifndef RUNNERUNIT_H
#define	RUNNERUNIT_H

#include "StateUnit.h"
#include "RunStrategy.h"

class RunnerUnit : public StateUnit {
public:
    RunnerUnit(RunStrategy* runner, StateUnit* runningUnit);
    void start();
    void stop();
    void process(float state);
private:
    RunStrategy* runner;
    StateUnit* runningUnit;
};

#endif	/* RUNNERUNIT_H */

