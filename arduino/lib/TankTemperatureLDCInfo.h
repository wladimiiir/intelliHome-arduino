/* 
 * File:   TankTemperatureLDCInfo.h
 * Author: wladimiiir
 *
 * Created on February 16, 2014, 12:23 AM
 */

#ifndef TANKTEMPERATURELDCINFO_H
#define	TANKTEMPERATURELDCINFO_H

#include <Arduino.h>
#include "Thermometer.h"
#include "LCDInfo.h"
#include "LCDSpecialCharacters.h"

enum TankPosition {
    TOP, MIDDLE, BOTTOM
};

class TankTemperatureLDCInfo : public LCDInfo {
public:
    TankTemperatureLDCInfo(Thermometer* top, Thermometer* middle, Thermometer* bottom);
    long showInLCD(LiquidCrystal* lcd);
private:
    Thermometer* top;
    Thermometer* middle;
    Thermometer* bottom;
    
    TankPosition currentPosition;
    unsigned long nextShowTime;
    
    void showTopTank(LiquidCrystal* lcd);
    void showMiddleTank(LiquidCrystal* lcd);
    void showBottomTank(LiquidCrystal* lcd);
};

#endif	/* TANKTEMPERATURELDCINFO_H */

