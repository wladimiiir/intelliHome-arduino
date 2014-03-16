/* 
 * File:   ConfigurableStateUnit.cpp
 * Author: wladimiiir
 * 
 * Created on March 14, 2014, 8:48 PM
 */

#include "ConfigurableStateUnit.h"

ConfigurableStateUnit::ConfigurableStateUnit(StateUnit* autoStateUnit) :
autoStateUnit(autoStateUnit),
manual(false),
value("Auto") {
}

void ConfigurableStateUnit::start() {
    if (manual)
        return;
    autoStateUnit->start();
}

void ConfigurableStateUnit::stop() {
    if (manual)
        return;
    autoStateUnit->stop();
}

void ConfigurableStateUnit::process(float state) {
    if (manual)
        return;
    autoStateUnit->process(state);
}

State ConfigurableStateUnit::getState() {
    return autoStateUnit->getState();
}

String ConfigurableStateUnit::getValue() {
    return value;
}

void ConfigurableStateUnit::setValue(String value) {
    if (value.equals("Auto")) {
        manual = false;
        this->value = value;
    } else if (value.equals("On")) {
        autoStateUnit->start();
        manual = true;
        this->value = value;
    } else if (value.equals("Off")) {
        autoStateUnit->stop();
        manual = true;
        this->value = value;
    }
}
