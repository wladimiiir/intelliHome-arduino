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

void FileLogger::log(String id, String logText) {
    char dir[14];
    sprintf(dir, "stats/%02d_%02d_%02d", year() % 100, month(), day());
    String datedFileName =  String(dir) + "/" + fileName;
    
    SD.mkdir(dir);
    File file = SD.open(datedFileName.c_str(), FILE_WRITE);

    if (file) {
        file.println(logText);
        file.close();
    } else {
        Serial.print("Cannot create file: ");
        Serial.print(datedFileName);
    }
}


