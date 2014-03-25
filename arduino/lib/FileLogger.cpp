/* 
 * File:   FileLogger.cpp
 * Author: wladimiiir
 * 
 * Created on February 28, 2014, 6:17 PM
 */

#include "FileLogger.h"
#include "AppHelper.h"

FileLogger::FileLogger(String fileName)
: fileName(fileName) {
}

void FileLogger::log(String id, const String logText) {
    char dir[15];
    sprintf(dir, "stats/%02d_%02d_%02d", year() % 100, month(), day());
    dir[14] = '\0';
    String datedFileName = String(dir) + "/" + fileName;

    File dirFile = SD.open(dir);
    if (dirFile) {
        dirFile.close();
    } else {
        if (!SD.mkdir(dir)) {
            Serial.print("Cannot make directory: ");
            Serial.println(dir);
            return;
        }
    }
    File file = SD.open(datedFileName.c_str(), FILE_WRITE);

    if (file) {
        file.println(logText);
        file.close();
        delay(5); //give some time to process close
    } else {
        Serial.print("Cannot create file: ");
        Serial.println(datedFileName);
    }
}


