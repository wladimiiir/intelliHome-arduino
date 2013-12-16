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
    if (hour() < fromHour)
        return false;
    if (hour() > toHour)
        return false;

    if (hour() == fromHour) {
        if (minute() < fromMinute)
            return false;
        if (minute() == fromMinute) {
            if (second() < fromSecond)
                return false;
        }
    }
    if (hour() == toHour) {
        if (minute() > toMinute)
            return false;
        if (minute() == toMinute) {
            if (second() >= toSecond)
                return false;
        }
    }
    
//    Serial.print("Running for: ");
//    Serial.print(fromHour);
//    Serial.print(":");
//    Serial.print(fromMinute);
//    Serial.print(":");
//    Serial.print(fromSecond);
//    Serial.print(" - ");
//    Serial.print(toHour);
//    Serial.print(":");
//    Serial.print(toMinute);
//    Serial.print(":");
//    Serial.println(toSecond);

    return true;
}

DailyRunner::DailyRunner(int controlPin) : controlPin(controlPin) {
    digitalWrite(controlPin, HIGH);
    pinMode(controlPin, OUTPUT);
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
    digitalWrite(controlPin, isRunning() ? LOW : HIGH);
}
