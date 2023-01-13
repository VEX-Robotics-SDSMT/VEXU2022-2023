#include "../include/botFunctions.h"
#include "../include/MinesMotorGroup.h"

bool intakeToggle = 0;
bool flywheelToggle = 0;

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

void toggleFlywheels()
{
    if(flywheelToggle == 0)
    {
        flywheelToggle = 1;
    }
    else
    {
        flywheelToggle = 0;
    }
}

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

void intakeLoopToggle(bool rev, int pct)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity((100)*pct * INTAKE_MOTOR_GEARSET*-1);
    }
    else if(intakeToggle == 1)
    {
        intake.move_velocity((100)*pct * INTAKE_MOTOR_GEARSET);
    }
    else
    {
        intake.brake();
    }
}

void intakeLoopHold(bool run, bool rev, double pct)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity(-(100)*pct * INTAKE_MOTOR_GEARSET);
    }
    else if(run == 1)
    {
        intake.move_velocity((100)*pct * INTAKE_MOTOR_GEARSET);
    }
    else
    {
        intake.brake();
    }
}

void flywheelLoopToggle(Mines::MinesMotorGroup flywheels, int pct)
{
    if(flywheelToggle == 1)
    {
        flywheels.moveVelocity((100)*pct * FLYWHEELS_MOTOR_GEARSET);
    }
    else
    {
        flywheels.brake();
    }
}