/* 
 * File:   LCDMode.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 15:43
 */

#ifndef LCDMODE_H
#define	LCDMODE_H

#include <LiquidCrystal.h>

class LCDMode {
public:
    virtual void increase() = 0;
    virtual void decrease() = 0;
    virtual void confirm() = 0;
    virtual void back() = 0;
    virtual void refresh(LiquidCrystal* lcd) = 0;
};


#endif	/* LCDMODE_H */

