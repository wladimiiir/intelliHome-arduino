/* 
 * File:   IRRemoteController.h
 * Author: wladimiiir
 *
 * Created on July 25, 2014, 6:42 PM
 */

#ifndef IRREMOTECONTROLLER_H
#define	IRREMOTECONTROLLER_H

#include <Arduino.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>

class IRRemoteController {
public:
    IRRemoteController(int irRecvPin);
    void setLCD(LiquidCrystal_I2C* lcd);
    void process();
private:
    IRrecv* receiver;
    LiquidCrystal_I2C* lcd;
    
    bool lcdOn;
};

#endif	/* IRREMOTECONTROLLER_H */

