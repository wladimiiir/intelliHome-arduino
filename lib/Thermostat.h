#ifndef _THERMOSTAT_H_
#define _THERMOSTAT_H_

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>

enum ControlType {
    HEATING, COOLING
};
enum State {
    RUNNING, STOPPED
};

typedef void (*ControlFunction)(State);

class Thermostat {
public:
    Thermostat(int sensorPin);
    float getCurrentTemperature();
    void setStartTemperature(float temp);
    void setStopTemperature(float temp);
    void setControlPin(int pin);
    void setUseAverageValueSystem(bool use);
    void setAverageValueCount(int count);
    void setControlFunction(ControlFunction func);
    void setControlType(ControlType controlType);
    void process();
private:
    State state;
    int sensorPin;
    float referenceV;
    int controlPin;
    float startTemp;
    float stopTemp;
    bool useAverageValueSystem;
    bool averageValueCount;
    std::vector<float> avsValues;
    ControlType controlType;
    long lastProcessTime;
    ControlFunction controlFunction;
    
    float applyAVS(float temperature);
    bool changeState(float temperature);
};

#endif
