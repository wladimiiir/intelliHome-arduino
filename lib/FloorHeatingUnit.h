/* 
 * File:   FloorHeatingUnit.h
 * Author: wladimiiir
 *
 * Created on December 29, 2013, 5:01 PM
 */

#ifndef FLOORHEATINGUNIT_H
#define	FLOORHEATINGUNIT_H

#include "StateUnit.h"
#include "ThreeWayValveController.h"
#include "RelayUnit.h"
#include "WaterTemperatureController.h"


class FloorHeatingUnit : public StateUnit {
public:
    FloorHeatingUnit(WaterTemperatureController* waterTemperatureController, RelayUnit* pumpUnit, StateUnit* listener);
    void start();
    void stop();
    void process(float state);
    State getState();
private:
    WaterTemperatureController* waterTemperatureController;
    RelayUnit* pumpUnit;
    StateUnit* listener;
};

#endif	/* FLOORHEATINGUNIT_H */

