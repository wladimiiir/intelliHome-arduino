/* 
 * File:   TankTemperatureLDCInfo.cpp
 * Author: wladimiiir
 * 
 * Created on February 16, 2014, 12:23 AM
 */

#include "TankTemperatureLDCInfo.h"

#define SHOW_TIME       (2000l)

TankTemperatureLDCInfo::TankTemperatureLDCInfo(Thermometer* top, Thermometer* middle, Thermometer* bottom) :
top(top),
middle(middle),
bottom(bottom) {
    currentPosition = TOP;
    nextShowTime = 0;
}

long TankTemperatureLDCInfo::showInLCD(LCD* lcd) {
    if (nextShowTime == 0)
        nextShowTime = millis() + SHOW_TIME;
    
    switch (currentPosition) {
        case TOP:
            lcd->clear();
            showTopTank(lcd);
            lcd->setCursor(0, 1);
            showMiddleTank(lcd);
            if (nextShowTime < millis()) {
                currentPosition = MIDDLE;
                nextShowTime = 0;
            }
            return 0;
        case MIDDLE:
            lcd->clear();
            showMiddleTank(lcd);
            lcd->setCursor(0, 1);
            showBottomTank(lcd);
            if (nextShowTime < millis()) {
                currentPosition = TOP;
                nextShowTime = 0;
            }
            return SHOW_TIME;
        default:
            return SHOW_TIME;
    }
}

void showTankTemperature(LCD* lcd, const char* tankChar, float temperature) {
    lcd->write(tankChar);
    lcd->print(" ");
    lcd->print(temperature);
    lcd->print(" ");
    lcd->print((char) 223);
    lcd->print("C");
}

void TankTemperatureLDCInfo::showTopTank(LCD* lcd) {
    showTankTemperature(lcd, SPECIAL_CHAR_TANK_TOP, top->getTemperature());
}

void TankTemperatureLDCInfo::showMiddleTank(LCD* lcd) {
    showTankTemperature(lcd, SPECIAL_CHAR_TANK_MIDDLE, middle->getTemperature());
}

void TankTemperatureLDCInfo::showBottomTank(LCD* lcd) {
    showTankTemperature(lcd, SPECIAL_CHAR_TANK_BOTTOM, bottom->getTemperature());
}

