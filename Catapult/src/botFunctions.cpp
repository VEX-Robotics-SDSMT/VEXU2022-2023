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

void intakeLoop(bool run, bool rev)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity(-1000);
    }
    else if(run == 1)
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

void catapultLoop(Mines::MinesMotorGroup catapultMotorGroup, double velocity, bool run, bool rev)
{
    if(run)
	{
		catapultMotorGroup.moveVelocity(velocity);
	}
    else if(rev)
    {
        catapultMotorGroup.moveVelocity(-velocity);
    }
    else
	{
		catapultMotorGroup.brake();
	}
}

void fire(Mines::MinesMotorGroup catapultMotorGroup)
{
    catapultMotorGroup.tarePosition();
    while(catapultMotorGroup.getPosition() < 100)
    {
        catapultMotorGroup.moveVelocity(30);
    }
    catapultMotorGroup.brake();
}

void rollerLoop(pros::Motor roller, double velocity, bool run, bool rev)
{
    if(run)
    {
        roller.move_velocity(velocity);
    }
    else if(rev)
    {
        roller.move_velocity(velocity);
    }
    else
    {
        roller.brake();
    }
}