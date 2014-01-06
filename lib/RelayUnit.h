/* 
 * File:   RelayUnit.h
 * Author: wladimiiir
 *
 * Created on December 23, 2013, 10:03 PM
 */

#ifndef RELAYUNIT_H
#define	RELAYUNIT_H

#include <Arduino.h>
#include "StateUnit.h"

class RelayUnit : public StateUnit {
public:
    RelayUnit(int controlPin);
    void start();
    void stop();
    void process(float state);
private:
    int controlPin;
};

#endif	/* RELAYUNIT_H */

