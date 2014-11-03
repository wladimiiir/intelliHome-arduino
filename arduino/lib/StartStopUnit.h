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

#define SECOND(s) (s * 1000l)
#define MINUTE(m) (m * 1000l * 60)

class StartStopUnit : public StateUnit {
public:
    StartStopUnit(StateUnit* unit, long maxRunTime, long stopTime);
    void setRestingDisabled(bool disabled);
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    StateUnit* unit;
    long maxRunTime;
    long restTime;
    bool restingDisabled;

    bool resting;
    unsigned long startedTime;
    unsigned long stoppedTime;
    bool shouldRest();
    bool shouldStart();
};

#endif	/* RESTABLEUNIT_H */

