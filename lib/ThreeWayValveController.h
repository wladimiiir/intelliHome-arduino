/* 
 * File:   ThreeWayValveControl.h
 * Author: Y12370
 *
 * Created on Utorok, 2013, december 10, 11:55
 */

#ifndef THREEWAYVALVECONTROL_H
#define	THREEWAYVALVECONTROL_H

#include <Arduino.h>

#include "Thermostat.h"

class ThreeWayValveController {
public:
    ThreeWayValveController(Thermostat thermometer, int lowerRelayPin, int higherRelayPin);
    void setFromTemperature(float temp);
    void setToTemperature(float temp);
    void process();
private:
    Thermostat thermometer;
    int lowerRelayPin;
    int higherRelayPin;
    float fromTemperature;
    float toTemperature;
    //
    long lastRelayRunTime;
    
    void runRelay(int relayPin);
};

#endif	/* THREEWAYVALVECONTROL_H */

