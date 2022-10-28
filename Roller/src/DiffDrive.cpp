#include "DiffDrive.h"
#include "MinesMotorGroup.h"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.h"

using namespace Mines;


DiffDrive::DiffDrive(MinesMotorGroup left, MinesMotorGroup right) : 
    leftMotors(left), rightMotors(right),
    driveInterface(this), turnInterface(this),
    drivePID(&driveInterface), turnPID(&turnInterface)
{
    drivePID.SetPIDConst(1, 0, 0);

    drivePID.StartTask();
    turnPID.StartTask();
}

void DiffDrive::driveTiles(double target, bool waitForCompletion)
{
    drivePID.SetTarget(target);
    if(waitForCompletion)
    {
        while(drivePID.GetTimeSinceTargetReached() < 1)
        {
            pros::c::delay(20);
        }
    }
}

void DiffDrive::turnDegreesAbsolute(double target, bool waitForCompletion)
{

}

void DiffDrive::turnDegreesRelative(double target, bool waitForCompletion)
{

}

void DiffDrive::setBrakeMode(pros::motor_brake_mode_e mode)
{
    leftMotors.setBrakeMode(mode);
}

double DiffDrive::getDrivePosition()
{
    return (leftMotors.getPosition() + rightMotors.getPosition()) / 2;
}

void DiffDrive::setDriveVelocity(double value)
{
    pros::lcd::print(3, "velocity: %f", value);
    leftMotors.moveVelocity(value);
    rightMotors.moveVelocity(value);
}

double DiffDrive::getTurnPosition()
{
    return 0;
}

void DiffDrive::setTurnVelocity(double value)
{

}





//--------------------nested classes-----------------------


DiffDrive::DriveInterface::DriveInterface(DiffDrive* pParent)
{
    parent = pParent;
}

double DiffDrive::DriveInterface::getPositionPID()
{
    return parent->getDrivePosition();
}

void DiffDrive::DriveInterface::setVelocityPID(double value)
{
    parent->setDriveVelocity(value);
}

DiffDrive::TurnInterface::TurnInterface(DiffDrive* pParent)
{
    parent = pParent;
}

double DiffDrive::TurnInterface::getPositionPID()
{
    return parent->getTurnPosition();
}

void DiffDrive::TurnInterface::setVelocityPID(double value)
{
    parent->setTurnVelocity(value);
}

