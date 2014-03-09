/* 
 * File:   LCDDisplay.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 12:39
 */

#ifndef LCDDISPLAY_H
#define	LCDDISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <vector>
#include "LCDInfo.h"
#include "LCDSetting.h"

#define LCD_REFRESH_INTERVAL    500l;

class LCDDisplay {
public:
    LCDDisplay(LiquidCrystal* lcd);
    void addLCDInfo(LCDInfo* lcdInfo);
    void addLCDSetting(LCDSetting* lcdSetting);
    void switchToIdleMode();
    void switchToSettingsMode();
    
    //settings mode functions
    void previousSetting();
    void nextSetting();
    void showSettingDescription();
    void showSettingValue();
    LCDSetting* getCurrentSetting();
    //
    
    void refresh();
private:
    LiquidCrystal* lcd;
    long infoDelay;
    std::vector<LCDInfo*> lcdInfos;
    std::vector<LCDSetting*> lcdSettings;
    
    bool settingsMode;
    bool settingDescription;
    unsigned long lastInfoStart;
    unsigned long nextRefreshTime;
    unsigned int currentInfoIndex;
    unsigned int currentSettingIndex;
    
    void refreshIdleMode();
    void refreshSettingsMode();
};

#endif	/* LCDDISPLAY_H */

