/* 
 * File:   StateUnit.h
 * Author: wladimiiir
 *
 * Created on December 23, 2013, 9:57 PM
 */

#ifndef STATEUNIT_H
#define	STATEUNIT_H

#include <Arduino.h>

class StateUnit {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void process(float state) = 0;
};

#endif	/* STATEUNIT_H */

