#include "../include/botFunctions.h"
#include "../include/MinesMotorGroup.h"

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity)
{
    leftMotorGroup.moveVelocity(leftVelocity);
    rightMotorGroup.moveVelocity(rightVelocity);
}

void rollerLoop(pros::Motor roller, double velocity, bool run)
{
    if(run)
    {
        roller.move_velocity(velocity);
    }
    else
    {
        roller.brake();
    }
}