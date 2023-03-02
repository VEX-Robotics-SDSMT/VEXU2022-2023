#include "./../include/MinesMotorGroup.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include <vector>

using namespace Mines;

MinesMotorGroup::MinesMotorGroup(pros::Motor motors[], int numMotors, LoggerSettings loggerSettings) :
logger(loggerSettings)
{
    if (!initialized)
    {
        for(int i = 0; i < numMotors; i++)
        {
            motorVector.push_back(motors[i]);
        }

        initialized = true;
        size = motorVector.size();
        logger.Log( (NAME + " Initialized").c_str(), 0, LoggerSettings::verbose);
    }
    else
    {
        logger.Log((NAME + " Trying to initialize again").c_str(), 0, LoggerSettings::warning);
    }
}

MinesMotorGroup::MinesMotorGroup(std::vector<pros::Motor> &motors, LoggerSettings loggerSettings) :
logger(loggerSettings)
{
    if (!initialized)
    {
        for(int i = 0; i < motors.size() ; i++)
        {
            motorVector.push_back(motors[i]);
        }

        initialized = true;
        size = motorVector.size();
        logger.Log((NAME + " Initialized").c_str(), 0, LoggerSettings::verbose);
    }
    else
    {
        logger.Log((NAME + " Trying to initialize again").c_str(), 0, LoggerSettings::warning);
    }
}


int MinesMotorGroup::move(const int voltage)
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].move(voltage);
    }
    logger.Log((NAME + " Setting voltage: " + std::to_string(voltage)).c_str(), 1, LoggerSettings::verbose);
    return 0;
}

int MinesMotorGroup::moveVelocity(const int velocity)
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].move_velocity(velocity);
    }
    logger.Log((NAME + " Setting velocity: " + std::to_string(velocity)).c_str(), 1, LoggerSettings::verbose);
    return 0;
}

int MinesMotorGroup::brake()
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].brake();
    }
    logger.Log((NAME + " Braking").c_str(), 1, LoggerSettings::verbose);
    return 0;
}

int MinesMotorGroup::tarePosition()
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].tare_position();
    }
    return 0;
}

int MinesMotorGroup::setBrakeMode(pros::motor_brake_mode_e mode)
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].set_brake_mode(mode);
    }
    return 0;
}

double MinesMotorGroup::getActualVelocity()
{
    double average = 0;
    int motorCount = 0;
    for(int i = 0; i < motorVector.size(); i++)
    {
        double vel = motorVector[i].get_actual_velocity();
        if (vel != NAN && vel != infinity() && vel != -infinity())
        {
            average += vel;
            motorCount++;
        }
        else
        {
            logger.Log((NAME + " Motor " + std::to_string(i) + " is reporting invalid values").c_str(), 4, LoggerSettings::error);
        } 
    }
    double reportedVelocity = average / motorCount;
    logger.Log((NAME + " Actual velocity: " + std::to_string(reportedVelocity)).c_str(), 2, LoggerSettings::verbose);
    return reportedVelocity;
}

double MinesMotorGroup::getPosition()
{
    double average = 0;
    int motorCount = 0;
    for(int i = 0; i < motorVector.size(); i++)
    {
        double pos = motorVector[i].get_position();
        if (pos != NAN && pos != infinity() && pos != -infinity())
        {
            average += pos;
            motorCount++;
        }   
        else
        {
            logger.Log((NAME + " Motor " + std::to_string(i) + " is reporting invalid values").c_str(), 4, LoggerSettings::error);
        } 
    }
    double reportedPosition = average /motorCount;
    logger.Log((NAME + " Actual velocity: " + std::to_string(reportedPosition)).c_str(), 3, LoggerSettings::verbose);
    return reportedPosition;
}

double MinesMotorGroup::getMaxVelocity()
{
    if(motorVector[0].get_gearing()== pros::E_MOTOR_GEARSET_36)
    {
        return 100;
    }
    if(motorVector[0].get_gearing() == pros::E_MOTOR_GEARSET_18)
    {
        return 200;
    }
    if(motorVector[0].get_gearing() == pros::E_MOTOR_GEARSET_06)
    {
        return 600;
    }
    return 0;
}
