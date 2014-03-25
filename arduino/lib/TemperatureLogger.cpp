/* 
 * File:   TemperatureFileLogger.cpp
 * Author: wladimiiir
 * 
 * Created on February 17, 2014, 9:34 PM
 */

#include "TemperatureLogger.h"

TemperatureLogger::TemperatureLogger(Logger* logger, unsigned long interval) :
logger(logger),
interval(interval) {
    nextLogTime = 0;
}

void TemperatureLogger::registerThermometer(Thermometer* thermometer) {
    thermometers.push_back(thermometer);
}

void TemperatureLogger::process() {
    if (nextLogTime > millis())
        return;

    String logText = "";
    logText += AppHelper::getTimeString();
    logText += ";";
    for (std::vector<Thermometer*>::iterator thermometer = thermometers.begin(); thermometer != thermometers.end(); ++thermometer) {
        float temp = (*thermometer)->getTemperature();
        logText += AppHelper::toString(temp);
        logText += ";";
    }
    logger->log("Temperatures", logText);

    nextLogTime = millis() + interval;
}

