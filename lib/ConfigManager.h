/* 
 * File:   SettingsManager.h
 * Author: Y12370
 *
 * Created on Piatok, 2014, marec 14, 14:24
 */

#ifndef SETTINGSMANAGER_H
#define	SETTINGSMANAGER_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <map>
#include "Configurator.h"

class ConfigManager {
public:
    ConfigManager();
    std::map<String, Configurator*> getConfigurators();
    void registerConfigurator(String key, Configurator* configurator);
    void setValue(String key, String value);
    String getValue(String key);
private:
    std::map<String, Configurator*> configurators;
};

#endif	/* SETTINGSMANAGER_H */

