/* 
 * File:   LM35Converter.cpp
 * Author: wladimiiir
 * 
 * Created on January 3, 2014, 9:15 PM
 */

#include "LM35Converter.h"

LM35Converter::LM35Converter() {
}

float LM35Converter::getAnalogReference() {
    return INTERNAL1V1;
}

float LM35Converter::convertValue(float analogValue) {
    return analogValue / 9.309091; //(10.0 / ((referenceV / 1024.0) * 1000.0)); //10mV per C / referenceV/1024
}
