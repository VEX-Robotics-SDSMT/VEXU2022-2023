#include "./../include/MinesMotorGroup.h"
#include "pros/motors.hpp"
#include <vector>

using namespace Mines;

void MinesMotorGroup::Initialize(pros::Motor motors[], int numMotors)
{
    if (!initialized)
    {
        for(int i = 0; i < numMotors; i++)
        {
            motorVector.push_back(motors[i]);
        }

        initialized = true;
        size = motorVector.size();
    }
}

void MinesMotorGroup::Initialize(std::vector<pros::Motor> &motors)
{
    if (!initialized)
    {
        for(int i = 0; i < motors.size() ; i++)
        {
            motorVector.push_back(motors[i]);
        }

        initialized = true;
        size = motorVector.size();
    }
}


int MinesMotorGroup::move(const int voltage)
{
    for(int i = 0; i < motorVector.size(); i++)
    {
        motorVector[i].move(voltage);
    }
    return 0;
}




