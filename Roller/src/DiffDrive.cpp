#include "DiffDrive.h"
#include "MinesMotorGroup.h"
#include "pros/motors.hpp"

using namespace Mines;


DiffDrive::DiffDrive(MinesMotorGroup left, MinesMotorGroup right) : 
    leftMotors(left), rightMotors(right),
    driveInterface(this), turnInterface(this),
    drivePID(&driveInterface), turnPID(&turnInterface)
{

}

void DiffDrive::driveTiles(double target, bool waitForCompletion)
{

}

void DiffDrive::turnDegreesAbsolute(double target, bool waitForCompletion)
{

}

void DiffDrive::turnDegreesRelative(double target, bool waitForCompletion)
{

}

void DiffDrive::setBrakeMode()
{

}

double DiffDrive::getDrivePosition()
{

}

void DiffDrive::setDriveVelocity(double value)
{

}

double DiffDrive::getTurnPosition()
{

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

