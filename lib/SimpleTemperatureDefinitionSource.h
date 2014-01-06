/* 
 * File:   SimpleTemperatureDefinitionSource.h
 * Author: wladimiiir
 *
 * Created on December 29, 2013, 7:53 PM
 */

#ifndef SIMPLETEMPERATUREDEFINITIONSOURCE_H
#define	SIMPLETEMPERATUREDEFINITIONSOURCE_H

#include "TemperatureDefinitionSource.h"


class SimpleTemperatureDefinitionSource : public TemperatureDefinitionSource {
public:
    SimpleTemperatureDefinitionSource(float minTemperature, float maxTemperature);
    float getMinTemperature();
    float getMaxTemperature();
private:
    float minTemperature;
    float maxTemperature;
};

#endif	/* SIMPLETEMPERATUREDEFINITIONSOURCE_H */

