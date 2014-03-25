/* 
 * File:   WeeklyRunner.h
 * Author: Y12370
 *
 * Created on Piatok, 2013, december 13, 10:23
 */

#ifndef WEEKLYRUNSTRATEGY_H
#define	WEEKLYRUNSTRATEGY_H

#include <Time.h>
#include "DailyRunStrategy.h"
#include "Day.h"

class WeeklyRunStrategy : public RunStrategy {
public:
    WeeklyRunStrategy();
    void addRunTime(Day day, int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    void cloneRunTimes(Day fromDay, Day toDay);
    bool isRunning();
private:
    DailyRunStrategy dailyStrategies[8];
};

#endif	/* WEEKLYRUNSTRATEGY_H */

