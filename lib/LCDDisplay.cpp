/* 
 * File:   LCDDisplay.cpp
 * Author: Y12370
 * 
 * Created on Štvrtok, 2014, január 9, 12:39
 */

#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal* lcd) :
lcd(lcd) {
    infoDelay = 3000;
    switchToIdleMode();
}

void LCDDisplay::addLCDInfo(LCDInfo* lcdInfo) {
    lcdInfos.push_back(lcdInfo);
}

void LCDDisplay::addLCDSetting(LCDSetting* lcdSetting) {
    lcdSettings.push_back(lcdSetting);
}

void LCDDisplay::switchToIdleMode() {
    nextInfoTime = 0;
    currentInfoIndex = 0;
    settingsMode = false;
}

void LCDDisplay::switchToSettingsMode() {
    if (lcdSettings.empty()) {
        lcd->clear();
        lcd->print("No settings");
        lcd->setCursor(0, 1);
        lcd->print("available.");
        nextInfoTime = millis() + infoDelay;
    } else {
        nextInfoTime = 0;
        settingDescription = true;
        settingsMode = true;
    }
}

void LCDDisplay::refresh() {
    if (settingsMode) {
        refreshSettingsMode();
    } else {
        refreshIdleMode();
    }
}

void LCDDisplay::refreshIdleMode() {
    if (lcdInfos.empty()) {
        return;
    }

    lcdInfos.at(currentInfoIndex)->showInLCD(lcd);
    if (millis() > nextInfoTime) {
        currentInfoIndex++;
        if (currentInfoIndex > lcdInfos.size() - 1) {
            currentInfoIndex = 0;
        }
        nextInfoTime = millis() + infoDelay;
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