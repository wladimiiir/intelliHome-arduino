/* 
 * File:   AppHelper.h
 * Author: wladimiiir
 *
 * Created on February 28, 2014, 6:36 PM
 */

#ifndef APPHELPER_H
#define	APPHELPER_H

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
};

#endif	/* APPHELPER_H */

