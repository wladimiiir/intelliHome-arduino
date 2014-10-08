/* 
 * File:   ConfigurableStateUnit.h
 * Author: wladimiiir
 *
 * Created on March 14, 2014, 8:48 PM
 */

#ifndef CONFIGURABLESTATEUNIT_H
#define	CONFIGURABLESTATEUNIT_H

#include "StateUnit.h"
#include "Configurator.h"

class ConfigurableStateUnit : public StateUnit, public Configurator {
public:
    ConfigurableStateUnit(StateUnit* autoStateUnit);
    void start();
    void stop();
    void process(float state);
    State getState();
    String getValue();
    void setValue(String value);
private:
    StateUnit* autoStateUnit;
    bool manualProcessing;
    String previousValue;
    String value;
    unsigned long changeTime;
};

#endif	/* CONFIGURABLESTATEUNIT_H */

