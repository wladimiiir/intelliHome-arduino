/* 
 * File:   WebServer.cpp
 * Author: wladimiiir
 * 
 * Created on March 7, 2014, 10:15 PM
 */

#include <EthernetClient.h>
#include <Wire.h>

#include "WebServer.h"

WebServer::WebServer(uint16_t port) {
    this->server = new EthernetServer(port);
    this->logger = new FileLogger("webserv.txt");
    this->coolerStartTime = 0;
}

void WebServer::setConfigManager(ConfigManager* manager) {
    this->configManager = manager;
}

void WebServer::registerThermometerReplace(String pattern, Thermometer* thermometer) {
    thermometerReplaceMap[pattern] = thermometer;
}

void WebServer::registerStateUnitReplace(String pattern, StateUnit* stateUnit) {
    stateUnitReplaceMap[pattern] = stateUnit;
}

void WebServer::begin() {
    server->begin();
}

bool WebServer::checkAuthentication(EthernetClient client) {
    //TODO:
    return true;
}

void WebServer::checkCooler() {
    if (coolerStartTime == 0)
        return;

    if (millis() - coolerStartTime > 60 * 1000l) {
        digitalWrite(31, LOW);
        coolerStartTime = 0;
    }
}

void WebServer::startCooler() {
    if (coolerStartTime == 0) {
        digitalWrite(31, HIGH);
    }
    coolerStartTime = millis();
}

void WebServer::process() {
    EthernetClient client = server->available();

    //    checkCooler();
    if (!client) {
        return;
    }
    //    startCooler();
    if (!checkAuthentication(client)) {
        return;
    }

    bool currentLineIsBlank = true;
    bool logged = false;
    String request = "";
    while (client.connected()) {
        if (!logged) {
            if (DEBUG)
                logger->log("web", AppHelper::getTimeString() + ": client has connected.");
            logged = true;
        }
        if (client.available()) { // client data available to read
            char c = client.read(); // read 1 byte (character) from client
            // buffer first part of HTTP request in HTTP_req array (string)
            // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
            if (request.length() < 100) {
                request += c;
            }
            // last line of client request is blank and ends with \n
            // respond to client only after last line received
            if (c == '\n' && currentLineIsBlank) {
                // send a standard http response header
                client.println("HTTP/1.1 200 OK");
                if (DEBUG)
                    logger->log("web", "Got request: " + request);
                // remainder of header follows below, depending on if
                // web page or XML page is requested
                // Ajax request - send XML file
                if (request.indexOf("arduino_inputs") != -1) {
                    // send XML file containing input states
                    setInputsXML(client);
                } else if (request.indexOf("GET /stats ") != -1) {
                    setStatsPage(client);
                } else if (request.indexOf("downloadFile?") != -1) {
                    int fileNameStartIndex = request.indexOf("downloadFile?") + 13;
                    downloadStatsFile(client, request.substring(fileNameStartIndex, request.indexOf(' ', fileNameStartIndex)));
                } else if (request.indexOf("GET /config ") != -1) {
                    setConfigPage(client);
                } else if (request.indexOf("arduino_config_values") != -1) {
                    setConfigValues(client);
                } else if (request.indexOf("set_config?") != -1) {
                    int configStartIndex = request.indexOf("set_config?") + 11;
                    String keyValue = request.substring(configStartIndex, request.indexOf(' ', configStartIndex));
                    setConfig(client, keyValue.substring(0, keyValue.indexOf('=')), keyValue.substring(keyValue.indexOf('=') + 1));
                } else { // web page request
                    setMainPage(client);
                }
                //clearing buffer, just in case
                while (client.available() > 0) {
                    client.read();
                }
                break;
            }
            // every line of text received from the client ends with \r\n
            if (c == '\n') {
                // last character on line of received text
                // starting new line with next character read
                currentLineIsBlank = true;
            } else if (c != '\r') {
                // a text character was received from client
                currentLineIsBlank = false;
            }
        } // end if (client.available())
    } // end while (client.connected())
    delay(10); // give the web browser time to receive the data
    if (DEBUG)
        logger->log("web", AppHelper::getTimeString() + ": client has disconnected.");
    client.stop(); // close the connection
    while (client.status() != 0) {
        delay(10);
    }
}

void WebServer::setMainPage(EthernetClient client) {
    client.println("Content-Type: text/html");
    client.println("Connection: keep-alive");
    client.println();
    // send web page
    File webFile = SD.open("web/myhome.htm"); // open web page file
    if (webFile) {
        byte buf[BUFFER_SIZE];
        while (webFile.available()) {
            int read = webFile.read(buf, BUFFER_SIZE);
            if (client.connected())
                client.write(buf, read);
        }
        webFile.close();
    }
}

void addFileEntries(EthernetClient client, String dirPrefix, File dir) {
    File file;
    while (file = dir.openNextFile()) {
        if (file.isDirectory()) {
            addFileEntries(client, dirPrefix + file.name() + "/", file);
        } else {
            client.print("<a href=\"downloadFile?");
            client.print(dirPrefix + file.name());
            client.print("\">");
            client.print(dirPrefix + file.name());
            client.print("</a><br/>");
        }
        file.close();
    }
}

void WebServer::setStatsPage(EthernetClient client) {
    client.println("Content-Type: text/html");
    client.println("Connection: keep-alive");
    client.println();
    client.print("<html>");
    client.print("<head>");
    client.print("</head>");
    client.print("<body>");
    File statsDir = SD.open("stats");
    if (statsDir) {
        if (statsDir.isDirectory())
            addFileEntries(client, "", statsDir);

        statsDir.close();
    }
    client.print("</body>");
    client.print("</html>");
}

void WebServer::setConfigPage(EthernetClient client) {
    if (configManager == NULL) {
        client.println("HTTP/1.1 404 Not found");
        return;
    }

    client.println("Content-Type: text/html");
    client.println("Connection: keep-alive");
    client.println();

    // send web page
    File webFile = SD.open("web/config.htm"); // open config page file
    if (webFile) {
        byte buf[BUFFER_SIZE];
        while (webFile.available()) {
            int read = webFile.read(buf, BUFFER_SIZE);
            if (client.connected())
                client.write(buf, read);
        }
        webFile.close();
    }
}

void WebServer::setConfigValues(EthernetClient client) {
    client.println("Content-Type: text/xml; charset=utf-8");
    client.println("Connection: keep-alive");
    client.println();

    client.print("<?xml version = \"1.0\"?>");
    client.print("<values>");

    if (configManager == NULL) {
        client.print("</values>");
        return;
    }

    std::map<String, Configurator*> configurators = configManager->getConfigurators();
    for (std::map<String, Configurator*>::iterator it = configurators.begin(); it != configurators.end(); ++it) {
        client.print("<");
        client.print((*it).first);
        client.print(">");
        client.print((*it).second->getValue());
        client.print("</");
        client.print((*it).first);
        client.print(">");
    }

    client.print("</values>");
}

void WebServer::setConfig(EthernetClient client, String key, String value) {
    client.println("Content-Type: text/html");
    client.println();
    client.print("<html>");
    client.print("<head>");
    client.print("</head>");
    client.print("<body>");

    if (configManager != NULL) {
        configManager->setValue(key, value);
        client.print("OK");
    } else {
        client.print("No place to set.");
    }

    client.print("</body>");
    client.print("</html>");
}

String getMimeType(String fileName) {
    if (fileName.endsWith(".CSV")) {
        return "text/csv";
    } else {
        return "text/plain";
    }
}

void WebServer::downloadStatsFile(EthernetClient client, String fileName) {
    File statsFile = SD.open(String("stats/" + fileName).c_str());
    if (statsFile) {
        client.println("Content-Type: " + getMimeType(fileName));
        client.print("Content-Disposition: inline; filename=\"");
        client.print(fileName);
        client.println("\"");
        client.println("Connection: keep-alive");
        client.println();
        byte buf[BUFFER_SIZE];
        while (statsFile.available()) {
            int read = statsFile.read(buf, BUFFER_SIZE);
            if (client.connected())
                client.write(buf, read);
        }
        statsFile.close();
    } else {
        client.println("Content-Type: text/html");
        client.println("Connection: keep-alive");
        client.println();
        client.print("<html>");
        client.print("<head>");
        client.print("</head>");
        client.print("<body>");
        client.print("Cannot find file.");
        client.print("</body>");
        client.print("</html>");
    }
}

void WebServer::setInputsXML(EthernetClient client) {
    client.println("Content-Type: text/xml; charset=utf-8");
    client.println("Connection: keep-alive");
    client.println();

    client.print("<?xml version = \"1.0\"?>");
    client.print("<inputs>");

    client.print("<currentTime>");
    client.print(AppHelper::getDateString());
    client.print(" ");
    client.print(AppHelper::getTimeString());
    client.print("</currentTime>");
    for (std::map<String, Thermometer*>::iterator it = thermometerReplaceMap.begin(); it != thermometerReplaceMap.end(); ++it) {
        client.print("<");
        client.print((*it).first);
        client.print(">");
        client.print((*it).second->getTemperature());
        client.print(" °C");
        client.print("</");
        client.print((*it).first);
        client.print(">");
    }
    for (std::map<String, StateUnit*>::iterator it = stateUnitReplaceMap.begin(); it != stateUnitReplaceMap.end(); ++it) {
        client.print("<");
        client.print((*it).first);
        client.print(">");
        client.print((*it).second->getState() == STARTED ? "RUNNING" : "STOPPED");
        client.print("</");
        client.print((*it).first);
        client.print(">");
    }
    client.print("</inputs>");
}


