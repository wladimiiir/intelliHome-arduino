/* 
 * File:   LCDInfoMode.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 15:46
 */

#ifndef LCDINFOMODE_H
#define	LCDINFOMODE_H

#include "LCDMode.h"

class LCDInfoMode : public LCDMode {
public:
    LCDInfoMode();
    void increase();
    void decrease();
    void confirm();
    void back();
    void refresh(LiquidCrystal* lcd);

};

#endif	/* LCDINFOMODE_H */

