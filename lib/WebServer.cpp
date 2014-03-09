/* 
 * File:   WebServer.cpp
 * Author: wladimiiir
 * 
 * Created on March 7, 2014, 10:15 PM
 */

#include <EthernetClient.h>

#include "WebServer.h"

WebServer::WebServer(uint16_t port) {
    this->server = new EthernetServer(port);
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

void WebServer::process() {
    EthernetClient client = server->available();
    if (!client) {
        return;
    }
    if (!checkAuthentication(client)) {
        return;
    }

    boolean currentLineIsBlank = true;
    String request = "";
    while (client.connected()) {
        if (client.available()) { // client data available to read
            char c = client.read(); // read 1 byte (character) from client
            // buffer first part of HTTP request in HTTP_req array (string)
            // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
            if (request.length() < 50) {
                request += c;
            }
            // last line of client request is blank and ends with \n
            // respond to client only after last line received
            if (c == '\n' && currentLineIsBlank) {
                // send a standard http response header
                client.println("HTTP/1.1 200 OK");
                // remainder of header follows below, depending on if
                // web page or XML page is requested
                // Ajax request - send XML file
                if (request.indexOf("arduino_inputs") != -1) {
                    // send rest of HTTP header
                    client.println("Content-Type: text/xml; charset=utf-8");
                    client.println("Connection: keep-alive");
                    client.println();
                    // send XML file containing input states
                    setXMLResponse(client);
                    client.println();
                } else { // web page request
                    // send rest of HTTP header
                    client.println("Content-Type: text/html");
                    client.println("Connection: keep-alive");
                    client.println();
                    // send web page
                    File webFile = SD.open("web/myhome.htm"); // open web page file
                    if (webFile) {
                        byte buf[256];
                        while (webFile.available()) {
                            int read = webFile.read(buf, 256);
                            client.write(buf, read);
                        }
                        webFile.close();
                    }
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
    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection
}

void WebServer::setXMLResponse(EthernetClient client) {
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


