#ifndef MINES_MOTOR_GROUP
#define MINES_MOTOR_GROUP

#include <vector>
#include "api.h"
#include "pros/motors.hpp"
#include "Logger.h"

namespace Mines {


class MinesMotorGroup
{
    const int NOT_INITIALIZED_CODE = -2;
    const std::string NAME = "[MotorGroup]";

    //variables
    std::vector<pros::Motor> motorVector;
    ScreenLogger logger;
    bool initialized = false;
    int size;

    //public functions
    public:
        MinesMotorGroup(std::vector<pros::Motor> &motors, LoggerSettings loggerSettings = LoggerSettings::none);
        MinesMotorGroup(pros::Motor motors[], int numMotors, LoggerSettings loggerSettings = LoggerSettings::none);

        int move(const int voltage);
        int moveVelocity(const int velocity);
        int brake();
        int tarePosition();
        int setBrakeMode(pros::motor_brake_mode_e mode);
        double getActualVelocity();
        double getMaxVelocity();
        double getPosition();


    //private functions
    private:

};

}

#endif
