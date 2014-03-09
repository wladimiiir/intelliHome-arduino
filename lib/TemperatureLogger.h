/* 
 * File:   TemperatureFileLogger.h
 * Author: wladimiiir
 *
 * Created on February 17, 2014, 9:34 PM
 */

#ifndef TEMPERATUREFILELOGGER_H
#define	TEMPERATUREFILELOGGER_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <Time.h>
#include <vector>

#include "Thermometer.h"
#include "Logger.h"
#include "AppHelper.h"

class TemperatureLogger {
public:
    TemperatureLogger(Logger* logger, unsigned long interval);
    void registerThermometer(Thermometer* thermometer);
    void process();
private:
    Logger* logger;
    unsigned long interval;
    std::vector<Thermometer*> thermometers;
    unsigned long nextLogTime;
};

#endif	/* TEMPERATUREFILELOGGER_H */

