/* 
 * File:   ConfigurableTemperatureDefinitionSource.h
 * Author: Y12370
 *
 * Created on Piatok, 2014, marec 14, 15:12
 */

#ifndef CONFIGURABLETEMPERATUREDEFINITIONSOURCE_H
#define	CONFIGURABLETEMPERATUREDEFINITIONSOURCE_H

#include "TemperatureDefinitionSource.h"

#define AUTO_VALUE      (-1000.0)

class ConfigurableTemperatureDefinitionSource : public TemperatureDefinitionSource {
public:
    ConfigurableTemperatureDefinitionSource(TemperatureDefinitionSource* autoSource);
    float getMinTemperature();
    float getMaxTemperature();
    void setMinTemperature(float value);
    void setMaxTemperature(float value);
private:
    TemperatureDefinitionSource* autoSource;
    float minManual;
    float maxManual;
};

#endif	/* CONFIGURABLETEMPERATUREDEFINITIONSOURCE_H */

