/* 
 * File:   TimeLCDInfo.cpp
 * Author: wladimiiir
 * 
 * Created on January 14, 2014, 6:18 PM
 */

#include "TimeLCDInfo.h"

TimeLCDInfo::TimeLCDInfo() {
}

void TimeLCDInfo::showInLCD(LiquidCrystal* lcd) {
    lcd->clear();

    lcd->print(day());
    lcd->print(".");
    lcd->print(month());
    lcd->print(".");
    lcd->print(year());

    lcd->setCursor(0, 1);

    int digit = hour();
    if (digit < 10) {
        lcd->print("0");
    }
    lcd->print(digit);
    lcd->print(":");
    digit = minute();
    if (digit < 10) {
        lcd->print("0");
    }
    lcd->print(digit);
    lcd->print(":");
    digit = second();
    if (digit < 10) {
        lcd->print("0");
    }
    lcd->print(digit);

}
