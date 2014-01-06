/* 
 * File:   LM35Converter.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 9:15 PM
 */

#ifndef LM35CONVERTER_H
#define	LM35CONVERTER_H

#include <Arduino.h>
#include "ThermometerValueConverter.h"


class LM35Converter : public ThermometerValueConverter {
public:
    LM35Converter();
    float getAnalogReference();
    float convertValue(float analogValue);
};

#endif	/* LM35CONVERTER_H */

