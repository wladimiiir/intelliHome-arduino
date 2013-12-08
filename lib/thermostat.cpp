#include "thermostat.h"

#define READ_COUNT      (10)
#define AVS_TIME_LIMIT  (5) //in seconds

Thermostat::Thermostat(int sensorPin) :
state(STOPPED),
sensorPin(sensorPin),
controlPin(-1),
startTemp(25),
stopTemp(30),
useAverageValueSystem(true),
averageValueCount(5),
controlType(HEATING),
lastProcessTime(0) {
#ifdef INTERNAL1V1
    referenceV = INTERNAL1V1;
#else
    referenceV = DEFAULT;
#endif
}

float Thermostat::getCurrentTemperature() {
    //read one value for "reseting" arduino input pin
    analogRead(sensorPin);
    delay(20);

    //read x times and make average
    float value = 0;
    for (int i = 0; i < READ_COUNT; i++) {
        value += analogRead(sensorPin);
        delay(20);
    }
    value /= READ_COUNT;

    return value;
}

void Thermostat::setUseAverageValueSystem(bool use) {
    this->useAverageValueSystem = use;
}

void Thermostat::setStartTemperature(float temp) {
    this->startTemp = temp;
}

void Thermostat::setStopTemperature(float temp) {
    this->stopTemp = temp;
}

void Thermostat::setControlPin(int pin) {
    this->controlPin = pin;
}

void Thermostat::setControlFunction(ControlFunction func) {
    this->controlFunction = func;
}

void Thermostat::setControlType(ControlType controlType) {
    this->controlType = controlType;
}

void Thermostat::process() {
    float temperature = getCurrentTemperature();

    if (useAverageValueSystem)
        temperature = applyAVS(temperature);

    lastProcessTime = millis();

    bool changed = changeState(temperature);
    if (changed) {
        if (controlPin != -1)
            digitalWrite(controlPin, state == RUNNING);
        if (controlFunction != NULL)
            controlFunction(state);
    }

}

bool Thermostat::changeState(float temperature) {
    switch (state) {
        case STOPPED:
            if ((controlType == COOLING && temperature >= startTemp)
                    || (controlType == HEATING && temperature <= startTemp)) {
                state = RUNNING;
                return true;
            }
            break;
        case RUNNING:
            if ((controlType == COOLING && temperature <= stopTemp)
                    || (controlType == HEATING && temperature >= stopTemp)) {
                state = STOPPED;
                return true;
            }
    }
    return false;
}

float Thermostat::applyAVS(float temperature) {
    long time = millis();
    if (time - lastProcessTime > AVS_TIME_LIMIT * 1000)
        return temperature;

    //removing the last one
    if (!avsValues.empty())
        avsValues.pop_back();

    avsValues.insert(0, temperature);

    temperature = 0;
    for (int index = 0; index < avsValues.size(); index++) {
        temperature += avsValues.at(index);
    }
    temperature /= avsValues.size();

    return temperature;
}
