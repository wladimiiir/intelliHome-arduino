/* 
 * File:   ThermometerLCDInfo.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 12:34
 */

#ifndef THERMOMETERLCDINFO_H
#define	THERMOMETERLCDINFO_H

#include "LCDInfo.h"
#include "Thermometer.h"



class ThermometerLCDInfo : public LCDInfo {
public:
    ThermometerLCDInfo(String description, Thermometer* thermometer);
    long showInLCD(LCD* lcd);
private:
    String description;
    Thermometer* thermometer;
};

#endif	/* THERMOMETERLCDINFO_H */

