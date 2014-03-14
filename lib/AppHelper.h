/* 
 * File:   AppHelper.h
 * Author: wladimiiir
 *
 * Created on February 28, 2014, 6:36 PM
 */

#ifndef APPHELPER_H
#define	APPHELPER_H

#include <Arduino.h>
#include <Time.h>

class AppHelper {
public:
    static const String getDateString() {
        String date = "";

        date += day();
        date += ".";
        date += month();
        date += ".";
        date += year();

        return date;
    }

    static const String getTimeString() {
        String time = "";

        int digit = hour();
        if (digit < 10) {
            time += "0";
        }
        time += digit;
        time += ":";
        digit = minute();
        if (digit < 10) {
            time += "0";
        }
        time += digit;
        time += ":";
        digit = second();
        if (digit < 10) {
            time += "0";
        }
        time += digit;

        return time;
    }

    static const String toString(float value) {
        String strValue = "";
        if (value < 0) {
            strValue += "-";
            value = -value;
        }
        strValue += (int) value;
        strValue += ".";
        strValue += (int) ((value - (int) value) * 100);
        return strValue;
    }

    static bool checkFloatValue(String value) {
        bool hasSeparator = false;
        for (unsigned int index = 0; index < value.length(); index++) {
            char c = value.charAt(index);
            if (c == '.') {
                if (hasSeparator)
                    return false;
                else
                    hasSeparator = true;
            } else if (c < '0' || c > '9') {
                return false;
            }
        }
        return value.length() > 0 && value.charAt(value.length() - 1) != '.';
    }
};

#endif	/* APPHELPER_H */

