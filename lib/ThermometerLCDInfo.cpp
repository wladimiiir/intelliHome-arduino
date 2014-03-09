/* 
 * File:   ThermometerLCDInfo.cpp
 * Author: Y12370
 * 
 * Created on Štvrtok, 2014, január 9, 12:34
 */

#include "ThermometerLCDInfo.h"

#define SHOW_TIME       (1500l)

ThermometerLCDInfo::ThermometerLCDInfo(String description, Thermometer* thermometer) :
description(description),
thermometer(thermometer) {
}

long ThermometerLCDInfo::showInLCD(LiquidCrystal* lcd) {
    lcd->clear();
    lcd->print(description);
    lcd->setCursor(0, 1);
    lcd->print(thermometer->getTemperature());
    lcd->print(" ");
    lcd->print((char) 223);
    lcd->print("C");
    
    return SHOW_TIME;
}


