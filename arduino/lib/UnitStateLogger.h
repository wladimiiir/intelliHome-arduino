/* 
 * File:   UnitStateLogger.h
 * Author: wladimiiir
 *
 * Created on March 9, 2014, 3:11 PM
 */

#ifndef UNITSTATELOGGER_H
#define	UNITSTATELOGGER_H

#include "StateUnit.h"
#include "AppHelper.h"
#include "Logger.h"
#include <StandardCplusplus.h>
#include <vector>

class UnitStateLogger {
public:
    UnitStateLogger(Logger* logger, unsigned long interval);
    void registerStateUnit(StateUnit* stateUnit);
    void process();
private:
    Logger* logger;
    unsigned long interval;
    std::vector<StateUnit*> stateUnits;
    unsigned long nextLogTime;
};

#endif	/* UNITSTATELOGGER_H */

