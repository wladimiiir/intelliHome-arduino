/* 
 * File:   ThreeWayValveControl.h
 * Author: Y12370
 *
 * Created on Utorok, 2013, december 10, 11:55
 */

#ifndef THREEWAYVALVECONTROL_H
#define	THREEWAYVALVECONTROL_H

#include <Arduino.h>

#include "Thermometer.h"

class ThreeWayValveController {
public:
    ThreeWayValveController(Thermometer* thermometer, int lowerRelayPin, int higherRelayPin);
    float getFromTemperature();
    float getToTemperature();
    void setFromTemperature(float temp);
    void setToTemperature(float temp);
    void reset(unsigned long cycleSeconds);
    void process();
    void stop();
private:
    Thermometer* thermometer;
    int lowerRelayPin;
    int higherRelayPin;
    float fromTemperature;
    float toTemperature;
    //
    unsigned long nextRelayRunTime;
    int currentPosition;
    unsigned long runningUntil;
    int runningRelayPin;
    
    void runRelay(int relayPin);
};

#endif	/* THREEWAYVALVECONTROL_H */

