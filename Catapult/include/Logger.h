#ifndef LOGGER
#define LOGGER

#include "api.h"

enum LoggerSettings
{
    none = 0, //do not use this for logging, only for the constructor
    exception = 1,
    error = 2,
    warning = 3,
    verbose = 4,
};

class ScreenLogger
{
    LoggerSettings printSetting;

    public:
        ScreenLogger(LoggerSettings setting);

        void Log(const char logLine[], int row, LoggerSettings setting);
};


#endif