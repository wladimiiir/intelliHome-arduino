/* 
 * File:   RestableUnit.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 9:35 AM
 */

#ifndef RESTABLEUNIT_H
#define	RESTABLEUNIT_H

#include <Arduino.h>
#include "StateUnit.h"

#define MINUTE(m) (m * 1000l * 60)

class StartStopUnit : public StateUnit {
public:
    StartStopUnit(StateUnit* unit, long maxRunTime, long stopTime);
    void setMaxRunTime(long runTime);
    void setStopTime(long restTime);
    bool isStopped();
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    StateUnit* unit;
    long maxRunTime;
    long stopTime;

    bool stopped;
    unsigned long runningTime;
    unsigned long stoppedTime;
    bool shouldStop();
    bool shouldStart();
};

#endif	/* RESTABLEUNIT_H */

