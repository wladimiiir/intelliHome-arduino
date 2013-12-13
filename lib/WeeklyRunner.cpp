#include "WeeklyRunner.h"

WeeklyRunner::WeeklyRunner(int controlPin) {
    dailyRunners[MONDAY] = DailyRunner(controlPin);
    dailyRunners[TUESDAY] = DailyRunner(controlPin);
    dailyRunners[WEDNESDAY] = DailyRunner(controlPin);
    dailyRunners[THURSDAY] = DailyRunner(controlPin);
    dailyRunners[FRIDAY] = DailyRunner(controlPin);
    dailyRunners[SATURDAY] = DailyRunner(controlPin);
    dailyRunners[SUNDAY] = DailyRunner(controlPin);
}

void WeeklyRunner::addRunTime(Day day, int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond) {
    dailyRunners[day].addRunTime(fromHour, fromMinute, fromSecond, toHour, toMinute, toSecond);
}

void WeeklyRunner::cloneRunTimes(Day fromDay, Day toDay) {
    dailyRunners[toDay] = dailyRunners[fromDay];
}

bool WeeklyRunner::isRunning() {
    return dailyRunners[weekday()].isRunning();
}

void WeeklyRunner::process() {
    dailyRunners[weekday()].process();
}
