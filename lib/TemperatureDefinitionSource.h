/* 
 * File:   TemperatureDefinitionSource.h
 * Author: wladimiiir
 *
 * Created on December 29, 2013, 5:58 PM
 */

#ifndef TEMPERATUREDEFINITIONSOURCE_H
#define	TEMPERATUREDEFINITIONSOURCE_H

class TemperatureDefinitionSource {
public:
    virtual float getMinTemperature() = 0;
    virtual float getMaxTemperature() = 0;
};

#endif	/* TEMPERATUREDEFINITIONSOURCE_H */

