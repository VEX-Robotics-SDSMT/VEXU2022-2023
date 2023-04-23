#include "../include/botFunctions.h"

bool intakeToggle = false;
bool flywheelToggle = false;
bool compressToggle = false;

void toggleIntake()
{
    intakeToggle = !intakeToggle;
}

void toggleFlywheels()
{
    if(flywheelToggle == 0)
        flywheelToggle = 1;
    else
        flywheelToggle = 0;
}

void toggleCompress()
{
    if(compressToggle == 0)
        compressToggle = 1;
    else
        compressToggle = 0;
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

void intakeLoopHold(Mines::MinesMotorGroup intakeMotors, bool rev)
{
    if(intakeToggle)
        intakeMotors.moveVelocity(-200);
    else if(rev)
        intakeMotors.moveVelocity(200);
    else
        intakeMotors.brake();
}

void flywheelLoopToggle(Mines::MinesMotorGroup flywheels, int pct)
{
    if(flywheelToggle)
        flywheels.move(((0.01)* (pct) * 127));
    else
        flywheels.brake();
}

void compressLoopToggle(pros::ADIDigitalOut compress)
{
    if(compressToggle == 1)
        compress.set_value(true);
    else
        compress.set_value(false);
}

void shootDisk()
{
    shoot1.set_value(1);
    pros::delay(250);
    shoot1.set_value(0);
}