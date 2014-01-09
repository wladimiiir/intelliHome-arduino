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

class LCDDisplay {
public:
    LCDDisplay(LiquidCrystal* lcd);
    void addLCDInfo(LCDInfo* lcdInfo);
    void refresh();
private:
    LiquidCrystal* lcd;
    long infoDelay;
    std::vector<LCDInfo*> lcdInfos;
    
    unsigned long nextInfoTime;
    unsigned int currentInfoIndex;
};

#endif	/* LCDDISPLAY_H */

