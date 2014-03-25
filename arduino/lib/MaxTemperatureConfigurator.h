/* 
 * File:   MaxTemperatureConfigurator.h
 * Author: Y12370
 *
 * Created on Piatok, 2014, marec 14, 15:38
 */

#ifndef MAXTEMPERATURECONFIGURATOR_H
#define	MAXTEMPERATURECONFIGURATOR_H

#include <Arduino.h>
#include "Configurator.h"
#include "ConfigurableTemperatureDefinitionSource.h"

class MaxTemperatureConfigurator : public Configurator {
public:
    MaxTemperatureConfigurator(ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource);
    void setValue(String value);
    String getValue();
private:
    ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource;
};


#endif	/* MAXTEMPERATURECONFIGURATOR_H */

