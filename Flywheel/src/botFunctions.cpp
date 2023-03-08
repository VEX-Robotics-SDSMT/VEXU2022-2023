#include "../include/botFunctions.h"

bool intakeToggle = 0;
bool flywheelToggle = 0;

void toggleIntake()
{
    if(intakeToggle == 0)
        intakeToggle = 1;
    else
        intakeToggle = 0;
}

void toggleFlywheels()
{
    if(flywheelToggle == 0)
        flywheelToggle = 1;
    else
        flywheelToggle = 0;
}

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity)
{
    leftMotorGroup.move(leftVelocity);
    rightMotorGroup.move(rightVelocity);
}

void rollerLoop(pros::Motor roller, int pct, bool run)
{
    if(run)
        roller.move_velocity(ROLLER_MOTOR_GEARSET*(pct/100));
    else
        roller.brake();
}

void intakeLoopHold(Mines::MinesMotorGroup intakeMotors, int pct, bool run, bool rev)
{
    if(rev == 1)
        intakeMotors.moveVelocity(-(100)*pct * INTAKE_MOTOR_GEARSET);
    else if(run == 1)
        intakeMotors.moveVelocity((100)*pct * INTAKE_MOTOR_GEARSET);
    else
        intakeMotors.brake();
}

void flywheelLoopToggle(Mines::MinesMotorGroup flywheels, int pct)
{
    if(flywheelToggle == 1)
        flywheels.move(((0.01)* (pct) * 127));
    else
        flywheels.brake();
}