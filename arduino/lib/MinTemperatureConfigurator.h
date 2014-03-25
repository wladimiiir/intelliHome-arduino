/* 
 * File:   MinTemperatureConfigurator.h
 * Author: Y12370
 *
 * Created on Piatok, 2014, marec 14, 15:25
 */

#ifndef MINTEMPERATURECONFIGURATOR_H
#define	MINTEMPERATURECONFIGURATOR_H

#include "ConfigurableTemperatureDefinitionSource.h"
#include "Configurator.h"

class MinTemperatureConfigurator : public Configurator {
public:
    MinTemperatureConfigurator(ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource);
    void setValue(String value);
    String getValue();
private:
    ConfigurableTemperatureDefinitionSource* temperatureDefinitionSource;
};

#endif	/* MINTEMPERATURECONFIGURATOR_H */

