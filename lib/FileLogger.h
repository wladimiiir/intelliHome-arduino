/* 
 * File:   FileLogger.h
 * Author: wladimiiir
 *
 * Created on February 28, 2014, 6:17 PM
 */

#ifndef FILELOGGER_H
#define	FILELOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <Time.h>
#include "Logger.h"

class FileLogger : public Logger {
public:
    FileLogger(String fileName);
    void log(String id, const String logText);
private:
    String fileName;
};

#endif	/* FILELOGGER_H */

