/* 
 * File:   TimerController.h
 * Author: Y12370
 *
 * Created on Piatok, 2013, december 13, 8:03
 */

#ifndef TIMERCONTROLLER_H
#define	TIMERCONTROLLER_H

#include <Time.h>
#include <StandardCplusplus.h>
#include <vector>

class RunTime {
public:
    RunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    bool isRunning();
private:
    int fromHour, fromMinute, fromSecond, toHour, toMinute, toSecond;
};

class DailyRunner {
public:
    DailyRunner();
    DailyRunner(int controlPin);
    void addRunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond);
    void clearRunTimes();
    bool isRunning();
    void process();
private:
    int controlPin;
    std::vector<RunTime> runTimes;
};


#endif	/* TIMERCONTROLLER_H */

