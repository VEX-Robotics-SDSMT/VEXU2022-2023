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

/** Contructor for the Differential Drive class
*
* @param left left side motor group
* @param right right side motor group
* @param imu inertial sensor
*/
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

/** Moves the robot forward or backward to the target using an acceleration curve
*
* @param target positive or negative distance to drive from the current location
* @param waitForCompletion decides if the call is blocking, defaults to true
*/
void DiffDrive::driveTiles(double target, bool waitForCompletion)
{
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
}

/** Moves the robot forward or backward to the target using an acceleration curve
*
* @param target positive or negative distance to drive from the current location
* @param timeout amount of time in ms that the robot should try to get to the target before it gives up
*/
void DiffDrive::driveTiles(double target, int timeOut)
{
    leftMotors.tarePosition();
    rightMotors.tarePosition();

    drivePID.SetTarget(target);

    while(drivePID.GetTimeSinceTargetReached() < GOAL_TIME && drivePID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    drivePID.SetTarget(getDrivePosition());
}

/** rotates the robot to the target using an acceleration curve
*
* @param target the direction in degrees (0-360) for the robot to rotate to
* @param waitForCompletion decides if the call is blocking, defaults to true
*/
void DiffDrive::turnDegreesAbsolute(double target, bool waitForCompletion)
{
    turnPID.SetTarget(target);
    if(waitForCompletion)
    {
        while(turnPID.GetTimeSinceTargetReached() < GOAL_TIME)
        {
            pros::c::delay(20);
        }
    }
}

/** rotates the robot to the target using an acceleration curve
*
* @param target the direction in degrees (0-360) for the robot to rotate to
* @param timeout amount of time in ms that the robot should try to get to the target before it gives up
*/
void DiffDrive::turnDegreesAbsolute(double target, int timeOut)
{
    turnPID.SetTarget(target);
    while(turnPID.GetTimeSinceTargetReached() < GOAL_TIME && turnPID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    turnPID.SetTarget(getTurnPosition());
}

/** sets the brakemode of all of the drive motors
 * 
 * @param mode
*/
void DiffDrive::setBrakeMode(pros::motor_brake_mode_e mode)
{
    leftMotors.setBrakeMode(mode);
}

/** sets the PID values for the drive PID
*
* @param kp proportional - sets speed relative distance
* from the target. Should do the majority of the heavy lifting.
* @param ki integral - sets speed cumulatively based on kp. 
* Used to deal with unexpected resitance.
* @param kd derivative - sets speed based on inverse of last speed? 
* Used to prevent overshoot.
*/
void DiffDrive::setDrivePIDVals(double kp, double ki, double kd)
{
    drivePID.SetPIDConst(kp, ki, kd);
}

/** sets the PID values for the turn PID
*
* @param kp proportional - sets speed relative distance
* from the target. Should do the majority of the heavy lifting.
* @param ki integral - sets speed cumulatively based on kp. 
* Used to deal with unexpected resitance.
* @param kd derivative - sets speed based on inverse of last speed? 
* Used to prevent overshoot.
*/
void DiffDrive::setTurnPIDVals(double kp, double ki, double kd)
{
    turnPID.SetPIDConst(kp, ki, kd); 
}

/** Sets the acceptable margin of error before the drive operation is considered complete
*
* @param tolerance
*/
void DiffDrive::setDrivePIDTol(double tolerance)
{
    drivePID.SetTolerance(tolerance);
}

/** Sets the acceptable margin of error before the turn operation is considered complete
*
* @param tolerance
*/
void DiffDrive::setTurnPIDTol(double tolerance)
{
    turnPID.SetTolerance(tolerance);
}

/** Sets the max motor speed for the drive operation
*
* @param percent percent of the maximum speed the motors are capable of, between 0 and 1
*/
void DiffDrive::setMaxDriveSpeed(double percent)
{
    MAX_DRIVE_PERCENT = percent;
}

/** Sets the max motor speed for the turn operation
*
* @param percent percent of the maximum speed the motors are capable of, between 0 and 1
*/
void DiffDrive::setMaxTurnSpeed(double percent)
{
    MAX_TURN_PERCENT = percent;
}

/** gets the average encoder position of the left and right side motors
*/
double DiffDrive::getDrivePosition()
{
    return (leftMotors.getPosition() + rightMotors.getPosition()) / 2;
}

/** Sets the ideal target speed of the drive 
*
* @param value
*/
void DiffDrive::setDriveVelocity(double value)
{
    driveVelocity = value;
    setMotorVelocities();
}


/** Gets the degrees the robot is facing from the inertial sensor
*/
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

/** Sets the target speed for the motors for a turn
*
* @param value
*/
void DiffDrive::setTurnVelocity(double value)
{
    turnVelocity = value;
    setMotorVelocities();
}

/** Sets the final speed for the motors based on the turn speed and drive speed command variables, and the 
 * max turn and drive speed config variables
*/
void DiffDrive::setMotorVelocities()
{
    double adjustedDriveMax = MAX_DRIVE_PERCENT * MAX_SPEED;
    double adjustedTurnMax = MAX_TURN_PERCENT * MAX_SPEED;
    double adjustedDriveVelocity = clamp(driveVelocity, -adjustedDriveMax, adjustedDriveMax);
    double adjustedTurnVelocity = clamp(turnVelocity, -adjustedTurnMax, adjustedTurnMax);

    double targetLeftSpeed = adjustedDriveVelocity + adjustedTurnVelocity;
    double targetRightSpeed = adjustedDriveVelocity - adjustedTurnVelocity;
    double scaleFactor = min(MAX_SPEED / max(fabs(targetLeftSpeed), fabs(targetRightSpeed)), 1.0);

    if (ACTIVE)
    {
        leftMotors.moveVelocity(targetLeftSpeed * scaleFactor);
        rightMotors.moveVelocity(targetRightSpeed* scaleFactor);
    }
}

/** Sets if the drivebase affects the motors
*
* @param active
*/
void DiffDrive::setActive(bool active)
{
    ACTIVE = active;

    if (active == true)
    {
        driveTiles(0, 50);
        turnDegreesAbsolute(intertialSensor.get_heading(), 50);
    }
}





//--------------------nested classes-----------------------

/** Drive interface constructor
*
* @param pParent the drivebase class that this interface calls to get sensor data and output motor speeds
*/
DiffDrive::DriveInterface::DriveInterface(DiffDrive* pParent)
{
    parent = pParent;
}

/** Gets the position of the drive, in this case, motor encoder values
*/
double DiffDrive::DriveInterface::getPositionPID()
{
    return parent->getDrivePosition();
}

/** Sets the recommended speed the PID found
*
* @param value
*/
void DiffDrive::DriveInterface::setVelocityPID(double value)
{
    parent->setDriveVelocity(value);
}

/** Turn interface constructor
*
* @param pParent the drivebase class that this interface calls to get sensor data and output motor speeds
*/
DiffDrive::TurnInterface::TurnInterface(DiffDrive* pParent)
{
    parent = pParent;
}

/** Gets the rotaion of the robot, in this case, inertial sensor heading values
*/
double DiffDrive::TurnInterface::getPositionPID()
{
    return parent->getTurnPosition();
}

/** Sets the recommended speed the PID found
*
* @param value
*/
void DiffDrive::TurnInterface::setVelocityPID(double value)
{
    parent->setTurnVelocity(value);
}


