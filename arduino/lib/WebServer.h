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
#include "ConfigManager.h"
#include "FileLogger.h"

#define BUFFER_SIZE     32
#define DEBUG           false

class WebServer {
public:
    WebServer(uint16_t port);
    void setConfigManager(ConfigManager* manager);
    void registerThermometerReplace(String pattern, Thermometer* thermometer);
    void registerStateUnitReplace(String pattern, StateUnit* stateUnit);
    void begin();
    void process();
private:
    EthernetServer* server;
    ConfigManager* configManager;
    std::map<String, Thermometer*> thermometerReplaceMap;
    std::map<String, StateUnit*> stateUnitReplaceMap;
    Logger* logger;
    unsigned long coolerStartTime;
    
    void checkCooler();
    void startCooler();
    bool checkAuthentication(EthernetClient client);
    void setMainPage(EthernetClient client);
    void setStatsPage(EthernetClient client);
    void setConfigPage(EthernetClient client);
    void setConfigValues(EthernetClient client);
    void setConfig(EthernetClient client, String key, String value);
    void downloadStatsFile(EthernetClient client, String filename);
    void setInputsXML(EthernetClient client);
};

#endif	/* WEBSERVER_H */

