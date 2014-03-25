/* 
 * File:   TimerController.h
 * Author: Y12370
 *
 * Created on Piatok, 2013, december 13, 8:03
 */

#ifndef DAILYRUNSTRATEGY_H
#define	DAILYRUNSTRATEGY_H

#include <Arduino.h>
#include <Time.h>
#include <StandardCplusplus.h>
#include <vector>
#include "RunStrategy.h"
#include "StateUnit.h"

class RunTime {
public:
    RunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    bool isRunning();
private:
    int fromHour, fromMinute, fromSecond, toHour, toMinute, toSecond;
};

class DailyRunStrategy : public RunStrategy {
public:
    DailyRunStrategy();
    void addRunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    void clearRunTimes();
    bool isRunning();
private:
    std::vector<RunTime> runTimes;
};


#endif	/* DAILYRUNSTRATEGY_H */

