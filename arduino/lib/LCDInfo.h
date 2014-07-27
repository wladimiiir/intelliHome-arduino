/* 
 * File:   LCDInfo.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 12:28
 */

#ifndef LCDINFO_H
#define	LCDINFO_H

#include <Arduino.h>
#include <LCD.h>

class LCDInfo {
public:
    virtual long showInLCD(LCD* lcd) = 0;
};

#endif	/* LCDINFO_H */

