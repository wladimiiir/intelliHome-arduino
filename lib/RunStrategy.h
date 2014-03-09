/* 
 * File:   Runner.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 12:05 PM
 */

#ifndef RUNSTRATEGY_H
#define	RUNSTRATEGY_H

#include <Arduino.h>

class RunStrategy {
public:
    virtual bool isRunning() = 0;
};


#endif	/* RUNSTRATEGY_H */

