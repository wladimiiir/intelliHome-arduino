/* 
 * File:   LCDDisplay.cpp
 * Author: Y12370
 * 
 * Created on Štvrtok, 2014, január 9, 12:39
 */

#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LCD* lcd) :
lcd(lcd) {
    infoDelay = 1500;
    nextRefreshTime = 0;
    switchToIdleMode();
}

void LCDDisplay::addLCDInfo(LCDInfo* lcdInfo) {
    lcdInfos.push_back(lcdInfo);
}

void LCDDisplay::addLCDSetting(LCDSetting* lcdSetting) {
    lcdSettings.push_back(lcdSetting);
}

void LCDDisplay::switchToIdleMode() {
    lastInfoStart = 0;
    currentInfoIndex = 0;
    settingsMode = false;
}

void LCDDisplay::switchToSettingsMode() {
    if (lcdSettings.empty()) {
        lcd->clear();
        lcd->print("No settings");
        lcd->setCursor(0, 1);
        lcd->print("available.");
        lastInfoStart = 0;
    } else {
        lastInfoStart = 0;
        settingDescription = true;
        settingsMode = true;
    }
}

void LCDDisplay::refresh() {
    if (millis() < nextRefreshTime)
        return;

    if (settingsMode) {
        refreshSettingsMode();
    } else {
        refreshIdleMode();
    }

    nextRefreshTime = millis() + LCD_REFRESH_INTERVAL;
}

void LCDDisplay::refreshIdleMode() {
    if (lcdInfos.empty()) {
        return;
    }

    unsigned long showTime = lcdInfos.at(currentInfoIndex)->showInLCD(lcd);
    if (showTime == 0) {
        return;
    }
    if(lastInfoStart == 0) {
        lastInfoStart = millis();
    }

    if (millis() > lastInfoStart + showTime) {
        currentInfoIndex++;
        if (currentInfoIndex > lcdInfos.size() - 1) {
            currentInfoIndex = 0;
        }
        lastInfoStart = 0;
    }
}

void LCDDisplay::refreshSettingsMode() {
    LCDSetting* setting = getCurrentSetting();
    lcd->clear();
    if (settingDescription) {
        lcd->print(setting->getName());
    } else {
        lcd->print(setting->getValue());
    }
}

void LCDDisplay::nextSetting() {
    currentSettingIndex++;
    if (currentSettingIndex > lcdSettings.size() - 1) {
        currentSettingIndex = 0;
    }
}

void LCDDisplay::previousSetting() {
    if (currentSettingIndex == 0) {
        currentSettingIndex = lcdSettings.size() - 1;
    } else {
        currentSettingIndex--;
    }
}

void LCDDisplay::showSettingDescription() {
    settingDescription = true;
}

void LCDDisplay::showSettingValue() {
    settingDescription = false;
}

LCDSetting* LCDDisplay::getCurrentSetting() {
    return lcdSettings.empty() ? NULL : lcdSettings.at(currentSettingIndex);
}