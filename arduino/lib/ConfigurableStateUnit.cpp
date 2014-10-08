/* 
 * File:   ConfigurableStateUnit.cpp
 * Author: wladimiiir
 * 
 * Created on March 14, 2014, 8:48 PM
 */

#include "ConfigurableStateUnit.h"

ConfigurableStateUnit::ConfigurableStateUnit(StateUnit* autoStateUnit) :
autoStateUnit(autoStateUnit),
manualProcessing(false),
previousValue("Auto"),
value("Auto"),
changeTime(0) {
}

void ConfigurableStateUnit::start() {
    if (manualProcessing)
        return;
    autoStateUnit->start();
}

void ConfigurableStateUnit::stop() {
    if (manualProcessing)
        return;
    autoStateUnit->stop();
}

void ConfigurableStateUnit::process(float state) {
    if (manualProcessing) {
        if (changeTime != 0 && changeTime >= millis()) {
            setValue(previousValue);
        }
        return;
    }
    autoStateUnit->process(state);
}

State ConfigurableStateUnit::getState() {
    return autoStateUnit->getState();
}

String ConfigurableStateUnit::getValue() {
    return value;
}

void ConfigurableStateUnit::setValue(String value) {
    this->previousValue = this->value;
    int separatorIndex = value.indexOf(';');
    unsigned long forSeconds = separatorIndex > 0 ? atol(value.substring(separatorIndex + 1).c_str()) : 0;
    value = separatorIndex > 0 ? value.substring(0, separatorIndex) : value;
    if (value.equals("Auto")) {
        manualProcessing = false;
        this->value = value;
    } else if (value.equals("On")) {
        autoStateUnit->start();
        manualProcessing = true;
        this->value = value;
    } else if (value.equals("Off")) {
        autoStateUnit->stop();
        manualProcessing = true;
        this->value = value;
    }
    changeTime = forSeconds == 0 ? 0 : (millis() + forSeconds * 1000);
}
