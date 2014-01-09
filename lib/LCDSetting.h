/* 
 * File:   LCDSetting.h
 * Author: Y12370
 *
 * Created on Štvrtok, 2014, január 9, 15:12
 */

#ifndef LCDSETTING_H
#define	LCDSETTING_H

class LCDSetting {
public:
    virtual String getName() = 0;
    virtual String getValue() = 0;
    virtual void increaseValue() = 0;
    virtual void decreaseValue() = 0;
};

#endif	/* LCDSETTING_H */

