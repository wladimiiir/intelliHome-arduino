/* 
 * File:   UnitStateLogger.cpp
 * Author: wladimiiir
 * 
 * Created on March 9, 2014, 3:11 PM
 */

#include "UnitStateLogger.h"

UnitStateLogger::UnitStateLogger(Logger* logger, unsigned long interval) :
logger(logger),
interval(interval) {
    nextLogTime = 0;
}

void UnitStateLogger::registerStateUnit(StateUnit* stateUnit) {
    stateUnits.push_back(stateUnit);
}

void UnitStateLogger::process() {
    if (nextLogTime > millis())
        return;

    String logText = "";
    logText += AppHelper::getTimeString();
    logText += ";";
    for (std::vector<StateUnit*>::iterator stateUnit = stateUnits.begin(); stateUnit != stateUnits.end(); ++stateUnit) {
        switch((*stateUnit)->getState()) {
            case STARTED:
                logText += "STARTED;";
                break;
            case STOPPED:
                logText += "STOPPED;";
                break;
        }
    }
    logger->log("StateUnits", logText);

    nextLogTime = millis() + interval;
}

