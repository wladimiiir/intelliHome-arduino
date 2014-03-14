/* 
 * File:   Configurator.h
 * Author: Y12370
 *
 * Created on Piatok, 2014, marec 14, 14:27
 */

#ifndef CONFIGURATOR_H
#define	CONFIGURATOR_H

class Configurator {
public:
    virtual void setValue(String value) = 0;
    virtual String getValue() = 0;
};

#endif	/* CONFIGURATOR_H */

