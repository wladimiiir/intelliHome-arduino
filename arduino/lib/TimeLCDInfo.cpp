/* 
 * File:   TimeLCDInfo.cpp
 * Author: wladimiiir
 * 
 * Created on January 14, 2014, 6:18 PM
 */

#include "TimeLCDInfo.h"
#include "AppHelper.h"

#define SHOW_TIME       (2000l)

TimeLCDInfo::TimeLCDInfo() {
}

long TimeLCDInfo::showInLCD(LCD* lcd) {
    lcd->clear();

    lcd->print(AppHelper::getDateString());
    lcd->setCursor(0, 1);
    lcd->print(AppHelper::getTimeString());

    return SHOW_TIME;
}
