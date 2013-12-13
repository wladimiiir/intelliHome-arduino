/* 
 * File:   WeeklyRunner.h
 * Author: Y12370
 *
 * Created on Piatok, 2013, december 13, 10:23
 */

#ifndef WEEKLYRUNNER_H
#define	WEEKLYRUNNER_H

#include <Time.h>
#include "DailyRunner.h"

enum Day {
    MONDAY = 2, TUESDAY = 3, WEDNESDAY = 4, THURSDAY = 5, FRIDAY = 6, SATURDAY = 7, SUNDAY = 1
};

class WeeklyRunner {
public:
    WeeklyRunner(int controlPin);
    void addRunTime(Day day, int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    void cloneRunTimes(Day fromDay, Day toDay);
    bool isRunning();
    void process();
private:
    DailyRunner dailyRunners[7];
};

#endif	/* WEEKLYRUNNER_H */

