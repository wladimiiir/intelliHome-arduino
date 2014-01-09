/* 
 * File:   ThermometerLCDInfo.cpp
 * Author: Y12370
 * 
 * Created on Štvrtok, 2014, január 9, 12:34
 */

#include "ThermometerLCDInfo.h"

ThermometerLCDInfo::ThermometerLCDInfo(String description, Thermometer* thermometer) :
description(description),
thermometer(thermometer) {
}

void ThermometerLCDInfo::showInLCD(LiquidCrystal* lcd) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(description);
    lcd->setCursor(0, 1);
    lcd->print(thermometer->getTemperature());
}


