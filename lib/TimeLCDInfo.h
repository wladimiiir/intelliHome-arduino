/* 
 * File:   TimeLCDInfo.h
 * Author: wladimiiir
 *
 * Created on January 14, 2014, 6:18 PM
 */

#ifndef TIMELCDINFO_H
#define	TIMELCDINFO_H

#include <Arduino.h>
#include <Time.h>
#include "LCDInfo.h"

class TimeLCDInfo : public LCDInfo {
public:
    TimeLCDInfo();
    long showInLCD(LiquidCrystal* lcd);
};

#endif	/* TIMELCDINFO_H */

