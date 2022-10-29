#include "../include/botFunctions.h"
#include "../include/MinesMotorGroup.h"

bool intakeToggle = 0;

void toggleIntake()
{
    if(intakeToggle == 0)
    {
        intakeToggle = 1;
    }
    else
    {
        intakeToggle = 0;
    }
}

void intakeLoop(bool rev)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity(-1000);
    }
    else if(intakeToggle == 1)
    {
        intake.move_velocity(1000);
    }
    else
    {
        intake.brake();
    }
}

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity)
{
    leftMotorGroup.moveVelocity(leftVelocity);
    rightMotorGroup.moveVelocity(rightVelocity);
}

void catapultLoop(Mines::MinesMotorGroup catapultMotorGroup, double velocity, bool run)
{
    if(run)
	{
		catapultMotorGroup.moveVelocity(velocity);
	}
    else
	{
		catapultMotorGroup.brake();
	}
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