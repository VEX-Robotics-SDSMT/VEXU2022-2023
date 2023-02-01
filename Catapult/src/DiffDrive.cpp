#include "DiffDrive.h"
#include "MinesMotorGroup.h"
#include "globals.h"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.h"
#include <algorithm>
#include <cmath>

using namespace Mines;
using namespace std;


DiffDrive::DiffDrive(MinesMotorGroup left, MinesMotorGroup right, pros::IMU imu) : 
    leftMotors(left), rightMotors(right), intertial(imu),
    driveInterface(this), turnInterface(this),
    drivePID(&driveInterface, LoggerSettings::verbose), turnPID(&turnInterface, LoggerSettings::none),
    logger(LoggerSettings::verbose)
{
    MAX_SPEED = rightMotors.getMaxVelocity();

    logger.Log("status: constructor called", 10, LoggerSettings::verbose);
    drivePID.StartTask();
    logger.Log("status: drivePID started", 10, LoggerSettings::verbose);
    turnPID.StartTask();
    logger.Log("status: turnPID started", 10, LoggerSettings::verbose);

    leftMotors.tarePosition();
    rightMotors.tarePosition();
}

void DiffDrive::driveTiles(double target, bool waitForCompletion)
{
    drivePID.SetStopped(false);
    leftMotors.tarePosition();
    rightMotors.tarePosition();

    drivePID.SetTarget(target);
    if(waitForCompletion)
    {
        while(drivePID.GetTimeSinceTargetReached() < GOAL_TIME)
        {
            pros::c::delay(20);
        }
    }

    drivePID.SetStopped(true);
}

void DiffDrive::driveTiles(double target, int timeOut)
{
    drivePID.SetStopped(false);
    leftMotors.tarePosition();
    rightMotors.tarePosition();

    drivePID.SetTarget(target);

    while(drivePID.GetTimeSinceTargetReached() < GOAL_TIME && drivePID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    drivePID.SetTarget(getDrivePosition());
    drivePID.SetStopped(true);
}

void DiffDrive::turnDegreesAbsolute(double target, bool waitForCompletion)
{
    if(fabs(inertialSensor.get_rotation() - absoluteRot) > 0.01)
    {
        inertialSensor.set_rotation(absoluteRot);
    }
    absoluteRot = target;
    turnPID.SetStopped(false);
    turnPID.SetTarget(target);
    if(waitForCompletion)
    {
        while(turnPID.GetTimeSinceTargetReached() < GOAL_TIME)
        {
            pros::c::delay(20);
        }
    }
    turnPID.SetStopped(true);
}

void DiffDrive::turnDegreesAbsolute(double target, int timeOut)
{
    if(fabs(inertialSensor.get_rotation() - absoluteRot) > 0.01)
    {
        inertialSensor.set_rotation(absoluteRot);
    }
    absoluteRot = target;
    turnPID.SetStopped(false);
    turnPID.SetTarget(target);
    while(turnPID.GetTimeSinceTargetReached() < GOAL_TIME && turnPID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    turnPID.SetTarget(getTurnPosition());
    turnPID.SetStopped(true);
}

void DiffDrive::setBrakeMode(pros::motor_brake_mode_e mode)
{
    leftMotors.setBrakeMode(mode);
}

void DiffDrive::setDrivePIDVals(double kp, double ki, double kd)
{
    drivePID.SetPIDConst(kp, ki, kd);
}

void DiffDrive::setTurnPIDVals(double kp, double ki, double kd)
{
    turnPID.SetPIDConst(kp, ki, kd); 
}

void DiffDrive::setDrivePIDTol(double tolerance)
{
    drivePID.SetTolerance(tolerance);
}

void DiffDrive::setTurnPIDTol(double tolerance)
{
    turnPID.SetTolerance(tolerance);
}

void DiffDrive::setMaxDriveSpeed(double percent)
{
    MAX_DRIVE_PERCENT = percent;
}

void DiffDrive::setMaxTurnSpeed(double percent)
{
    MAX_TURN_PERCENT = percent;
}

double DiffDrive::getDrivePosition()
{
    return (leftMotors.getPosition() + rightMotors.getPosition()) / 2;
}

void DiffDrive::setDriveVelocity(double value)
{
    driveVelocity = value;
    setMotorVelocities();
}

double DiffDrive::getTurnPosition()
{
    double current = intertial.get_heading();

    double target = turnPID.GetTarget();

    if (current - target > 180)
    {
        return current - 360;
    }
    else if (target - current > 180)
    {
        return current + 360;
    }
    else
    {
        return current;
    }
}

void DiffDrive::setTurnVelocity(double value)
{
    turnVelocity = value;
    setMotorVelocities();
}

void DiffDrive::setMotorVelocities()
{
    double adjustedDriveMax = MAX_DRIVE_PERCENT * MAX_SPEED;
    double adjustedTurnMax = MAX_TURN_PERCENT * MAX_SPEED;
    double adjustedDriveVelocity = clamp(driveVelocity, -adjustedDriveMax, adjustedDriveMax);
    double adjustedTurnVelocity = clamp(turnVelocity, -adjustedTurnMax, adjustedTurnMax);

    double targetLeftSpeed = adjustedDriveVelocity + adjustedTurnVelocity;
    double targetRightSpeed = adjustedDriveVelocity - adjustedTurnVelocity;

    double scaleFactor = min(MAX_SPEED / max(fabs(targetLeftSpeed), fabs(targetRightSpeed)), 1.0);

    leftMotors.moveVelocity(targetLeftSpeed * scaleFactor);
    rightMotors.moveVelocity(targetRightSpeed* scaleFactor);
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


