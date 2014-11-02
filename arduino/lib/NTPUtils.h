/* 
 * File:   NTPUtils.h
 * Author: wladimiiir
 *
 * Created on October 22, 2014, 8:03 PM
 */

#ifndef NTPUTILS_H
#define	NTPUTILS_H

#include <Arduino.h>
#include <EthernetUdp.h>
#include <Time.h>

static const int NTP_PACKET_SIZE = 48;
static const int TIME_ZONE = 1;
static const IPAddress timeServer(132, 163, 4, 101);
static const unsigned int port = 8888;

class NTPUtils {
public:

    static time_t getNTPTime() {
        EthernetUDP udpClient;
        time_t ntpTime = 0;

        if (udpClient.begin(port)) {
            ntpTime = getNTPTime(udpClient);
            udpClient.stop();
        }

        return ntpTime;
    }
private:

    static time_t getNTPTime(EthernetUDP& udpClient) {
        byte packetBuffer[NTP_PACKET_SIZE];

        while (udpClient.parsePacket() > 0); // discard any previously received packets

        Serial.println("Transmit NTP Request");
        sendNTPpacket(timeServer, udpClient, packetBuffer);

        uint32_t beginWait = millis();
        while (millis() - beginWait < 1500) {
            int size = udpClient.parsePacket();
            if (size >= NTP_PACKET_SIZE) {
                Serial.println("Receive NTP Response");
                udpClient.read(packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
                unsigned long secsSince1900;
                // convert four bytes starting at location 40 to a long integer
                secsSince1900 = (unsigned long) packetBuffer[40] << 24;
                secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
                secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
                secsSince1900 |= (unsigned long) packetBuffer[43];
                return secsSince1900 - 2208988800UL + TIME_ZONE * SECS_PER_HOUR;
            }
        }
        Serial.println("No NTP Response :-(");
        return 0; // return 0 if unable to get the time
    }

    // send an NTP request to the time server at the given address
    static void sendNTPpacket(const IPAddress& address, EthernetUDP udpClient, byte packetBuffer[]) {
        // set all bytes in the buffer to 0
        memset(packetBuffer, 0, NTP_PACKET_SIZE);
        // Initialize values needed to form NTP request
        // (see URL above for details on the packets)
        packetBuffer[0] = 0b11100011; // LI, Version, Mode
        packetBuffer[1] = 0; // Stratum, or type of clock
        packetBuffer[2] = 6; // Polling Interval
        packetBuffer[3] = 0xEC; // Peer Clock Precision
        // 8 bytes of zero for Root Delay & Root Dispersion
        packetBuffer[12] = 49;
        packetBuffer[13] = 0x4E;
        packetBuffer[14] = 49;
        packetBuffer[15] = 52;
        // all NTP fields have been given values, now
        // you can send a packet requesting a timestamp:                 
        udpClient.beginPacket(address, 123); //NTP requests are to port 123
        udpClient.write(packetBuffer, NTP_PACKET_SIZE);
        udpClient.endPacket();
    }
};

#endif	/* NTPUTILS_H */

