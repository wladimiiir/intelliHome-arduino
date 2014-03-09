/* 
 * File:   WebServer.h
 * Author: wladimiiir
 *
 * Created on March 7, 2014, 10:15 PM
 */

#ifndef WEBSERVER_H
#define	WEBSERVER_H

#include <Ethernet.h>
#include <SD.h>
#include <StandardCplusplus.h>
#include <map>

#include "AppHelper.h"
#include "Thermometer.h"
#include "StateUnit.h"

class WebServer {
public:
    WebServer(uint16_t port);
    void registerThermometerReplace(String pattern, Thermometer* thermometer);
    void registerStateUnitReplace(String pattern, StateUnit* stateUnit);
    void begin();
    void process();
private:
    EthernetServer* server;
    std::map<String, Thermometer*> thermometerReplaceMap;
    std::map<String, StateUnit*> stateUnitReplaceMap;
    
    bool checkAuthentication(EthernetClient client);
    void setXMLResponse(EthernetClient client);
};

#endif	/* WEBSERVER_H */

