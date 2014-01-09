/* 
 * File:   LCDDisplay.cpp
 * Author: Y12370
 * 
 * Created on Štvrtok, 2014, január 9, 12:39
 */

#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal* lcd) :
lcd(lcd) {
    infoDelay = 5000;
    nextInfoTime = 0;
    currentInfoIndex = 0;
}

void LCDDisplay::addLCDInfo(LCDInfo* lcdInfo) {
    lcdInfos.push_back(lcdInfo);
}

void LCDDisplay::refresh() {
    if (millis() < nextInfoTime || lcdInfos.empty()) {
        return;
    }

    lcdInfos.at(currentInfoIndex)->showInLCD(lcd);
    
    currentInfoIndex++;
    if (currentInfoIndex > lcdInfos.size() - 1) {
        currentInfoIndex = 0;
    }
    nextInfoTime = millis() + infoDelay;
}


