#include "WeeklyRunStrategy.h"

int controlPin;

WeeklyRunStrategy::WeeklyRunStrategy() {
    dailyStrategies[MONDAY] = DailyRunStrategy();
    dailyStrategies[TUESDAY] = DailyRunStrategy();
    dailyStrategies[WEDNESDAY] = DailyRunStrategy();
    dailyStrategies[THURSDAY] = DailyRunStrategy();
    dailyStrategies[FRIDAY] = DailyRunStrategy();
    dailyStrategies[SATURDAY] = DailyRunStrategy();
    dailyStrategies[SUNDAY] = DailyRunStrategy();
}

void WeeklyRunStrategy::addRunTime(Day day, int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond) {
    dailyStrategies[day].addRunTime(fromHour, fromMinute, fromSecond, toHour, toMinute, toSecond);
}

void WeeklyRunStrategy::cloneRunTimes(Day fromDay, Day toDay) {
    dailyStrategies[toDay] = dailyStrategies[fromDay];
}

bool WeeklyRunStrategy::isRunning() {
    return dailyStrategies[weekday()].isRunning();
}