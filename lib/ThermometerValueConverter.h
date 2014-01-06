/* 
 * File:   ThermometerValueConverter.h
 * Author: wladimiiir
 *
 * Created on January 3, 2014, 9:11 PM
 */

#ifndef THERMOMETERVALUECONVERTER_H
#define	THERMOMETERVALUECONVERTER_H

class ThermometerValueConverter {
public:
    virtual float getAnalogReference() = 0;
    virtual float convertValue(float analogValue) = 0;
};


#endif	/* THERMOMETERVALUECONVERTER_H */

