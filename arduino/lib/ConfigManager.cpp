/* 
 * File:   SettingsManager.cpp
 * Author: Y12370
 * 
 * Created on Piatok, 2014, marec 14, 14:24
 */

#include "ConfigManager.h"

ConfigManager::ConfigManager() {
}

std::map<String, Configurator*> ConfigManager::getConfigurators() {
    return configurators;
}

void ConfigManager::registerConfigurator(String key, Configurator* configurator) {
    configurators[key] = configurator;
}

String ConfigManager::getValue(String key) {
    Configurator* configurator = configurators[key];
    if (configurator == NULL)
        return "NA";
    return configurator->getValue();
}

void ConfigManager::setValue(String key, String value) {
    Configurator* configurator = configurators[key];
    if (configurator == NULL)
        return;

    configurator->setValue(value);
}


