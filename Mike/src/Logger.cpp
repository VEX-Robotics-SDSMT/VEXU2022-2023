#include "Logger.h"


ScreenLogger::ScreenLogger(LoggerSettings setting)
{
    printSetting = setting;
}


void ScreenLogger::Log(std::string logLine, int row, LoggerSettings setting)
{
    if (setting <= printSetting)
    {
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, row, "                                                   ");
        pros::screen::print(pros::text_format_e_t::E_TEXT_SMALL, row, logLine.c_str());
    }
}


