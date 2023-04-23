#ifndef LOGGER
#define LOGGER

#include "globals.h"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.h"
#include <string>

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
    int starterRow = 0;

    public:
        ScreenLogger(LoggerSettings setting);
        ScreenLogger(LoggerSettings setting, int row);

        void Log(std::string logLine, int row, LoggerSettings setting);
};


#endif