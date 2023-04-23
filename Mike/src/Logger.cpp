#include "Logger.h"


ScreenLogger::ScreenLogger(LoggerSettings setting)
{
    printSetting = setting;
}

ScreenLogger::ScreenLogger(LoggerSettings setting, int row)
{
    printSetting = setting;
    starterRow = row;
}


void ScreenLogger::Log(std::string logLine, int row, LoggerSettings setting)
{
    if (setting <= printSetting)
    {
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, row + starterRow, "                                                   ");
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, row + starterRow, logLine.c_str());
        std::cout << logLine << std::endl;
    }
}


