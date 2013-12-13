#include <Arduino.h>

#include "DailyRunner.h"

RunTime::RunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond) :
fromHour(fromHour),
fromMinute(fromMinute),
fromSecond(fromSecond),
toHour(toHour),
toMinute(toMinute),
toSecond(toSecond) {
}

bool RunTime::isRunning() {
    return hour() > fromHour && hour() < toHour
            && minute() > fromMinute && minute() < toMinute
            && second() > fromSecond && second() <toSecond;
}

DailyRunner::DailyRunner(int controlPin) : controlPin(controlPin) {
    pinMode(controlPin, OUTPUT);
    digitalWrite(controlPin, LOW);
}

void DailyRunner::addRunTime(int fromHour, int fromMinute, int fromSecond, int toHour, int toMinute, int toSecond) {
    runTimes.push_back(RunTime(fromHour, fromMinute, fromSecond, toHour, toMinute, toSecond));
}

void DailyRunner::clearRunTimes() {
    runTimes.clear();
}

bool DailyRunner::isRunning() {
    for (std::vector<RunTime>::iterator runTime = runTimes.begin(); runTime != runTimes.end(); ++runTime) {
        if (runTime->isRunning()) {
            return true;
        }
    }
    return false;
}

void DailyRunner::process() {
    digitalWrite(controlPin, isRunning() ? HIGH : LOW);
}
