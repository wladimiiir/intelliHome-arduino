/* 
 * File:   LCDSpecialCharacters.h
 * Author: wladimiiir
 *
 * Created on February 16, 2014, 11:05 AM
 */

#ifndef LCDSPECIALCHARACTERS_H
#define	LCDSPECIALCHARACTERS_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define SPECIAL_CHAR_TANK_TOP        (0)
#define SPECIAL_CHAR_TANK_MIDDLE     (1)
#define SPECIAL_CHAR_TANK_BOTTOM     (2)

class LCDSpecialCharacters {
public:

    static void initSpecialCharacters(LiquidCrystal* lcd) {
        lcd->createChar(SPECIAL_CHAR_TANK_TOP, topTankChar);
        lcd->createChar(SPECIAL_CHAR_TANK_MIDDLE, middleTankChar);
        lcd->createChar(SPECIAL_CHAR_TANK_BOTTOM, bottomTankChar);
    }
private:
    static uint8_t topTankChar[8];
    static uint8_t middleTankChar[8];
    static uint8_t bottomTankChar[8];
};

#endif	/* LCDSPECIALCHARACTERS_H */

