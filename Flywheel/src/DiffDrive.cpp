#include "DiffDrive.h"

using namespace Mines;
using namespace std;


DiffDrive::DiffDrive(MinesMotorGroup left, MinesMotorGroup right, pros::IMU imu) : 
    leftMotors(left), rightMotors(right), inertial(imu),
    driveInterface(this), turnInterface(this), driveSensorInterface(DriveSensorInterface(left, right)),
    drivePID(&driveInterface, LoggerSettings::none), turnPID(&turnInterface, LoggerSettings::none),
    logger(LoggerSettings::none)
{
    MAX_SPEED = rightMotors.getMaxVelocity();

    logger.Log("status: constructor called", 10, LoggerSettings::verbose);

    driveSensorInterface.Reset();
    StartPIDs();
}

DiffDrive::DiffDrive(MinesMotorGroup left, MinesMotorGroup right, SensorInterface driveSensorInterface, pros::Imu imu):
    leftMotors(left), rightMotors(right), inertial(imu),
    driveInterface(this), turnInterface(this), driveSensorInterface(driveSensorInterface),
    drivePID(&driveInterface, LoggerSettings::none), turnPID(&turnInterface, LoggerSettings::none),
    logger(LoggerSettings::none)
{
    MAX_SPEED = rightMotors.getMaxVelocity();

    logger.Log("status: constructor called", 10, LoggerSettings::verbose);

    driveSensorInterface.Reset();
    StartPIDs();
}

double DiffDrive::getDriveVelocity()
{
    return (leftMotors.getActualVelocity() + rightMotors.getActualVelocity()) / 2;
}

double DiffDrive::getTurnVelocity()
{
    return inertial.get_gyro_rate().z; //might need to be a different call
}

void DiffDrive::driveTiles(double target, bool waitForCompletion)
{
    driveSensorInterface.Reset();

    drivePID.SetTarget(target);
    if(waitForCompletion)
    {
        while(drivePID.GetTimeSinceTargetReached() < GOAL_TIME)
        {
            pros::c::delay(20);
        }
    }
}

void DiffDrive::driveTiles(double target, int timeOut)
{
    driveSensorInterface.Reset();
    drivePID.SetTarget(target);

    while(drivePID.GetTimeSinceTargetReached() < GOAL_TIME && drivePID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    drivePID.SetTarget(getDrivePosition());
}

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

void DiffDrive::turnDegreesAbsolute(double target, int timeOut)
{
    turnPID.SetTarget(target);
    while(turnPID.GetTimeSinceTargetReached() < GOAL_TIME && turnPID.GetTimeSinceTargetSet() < timeOut)
    {
        pros::c::delay(20);
    }

    turnPID.SetTarget(getTurnPosition());
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

void DiffDrive::setMaxDriveAccel(double value)
{
    MAX_DRIVE_ACCEL = value;
}

void DiffDrive::setMaxTurnAccel(double value)
{
    MAX_TURN_ACCEL = value;
}

double DiffDrive::getDrivePosition()
{
    return driveSensorInterface.Get();
}

void DiffDrive::setDriveVelocity(double value)
{
    double adjustedDriveMaxAccel = MAX_DRIVE_ACCEL * MAX_SPEED;
    double dyanamicMax = fabs(getDriveVelocity()) + adjustedDriveMaxAccel;
    double clampedVal = std::clamp(value, -dyanamicMax, dyanamicMax);

    logger.Log("adj: " + std::to_string(adjustedDriveMaxAccel) +
    " dyn: " + std::to_string(dyanamicMax), 3, LoggerSettings::verbose);
    logger.Log("Target drive velocity: " + std::to_string(clampedVal), 4, LoggerSettings::verbose);

    driveVelocity = clampedVal;
    setMotorVelocities();
}

double DiffDrive::getTurnPosition()
{
    double current = inertial.get_heading();

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
    /*double adjustedTurnMaxAccel = MAX_TURN_ACCEL * MAX_SPEED;
    double dyanamicMax = fabs(getTurnVelocity()) + adjustedTurnMaxAccel;
    double clampedVal = std::clamp(value, -dyanamicMax, dyanamicMax);
    logger.Log("Target turn velocity: " + std::to_string(clampedVal), 2, LoggerSettings::verbose);

    turnVelocity = clampedVal;*/
    //std::cout << value << endl;
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

    if (ACTIVE)
    {
        leftMotors.moveVelocity(targetLeftSpeed * scaleFactor);
        rightMotors.moveVelocity(targetRightSpeed* scaleFactor);
    }
}

void DiffDrive::setActive(bool active)
{
    ACTIVE = active;

    if (active == true)
    {
        driveTiles(0, 50);
        turnDegreesAbsolute(inertial.get_heading(), 50);
    }
}

void DiffDrive::killPIDs()
{
    drivePID.KillTask();
    turnPID.KillTask();
    pros::delay(200);
}

void DiffDrive::StartPIDs()
{
    drivePID.StartTask();
    turnPID.StartTask();
}

void DiffDrive::SetPausedPID(bool paused)
{
    PIDPaused = paused;
    drivePID.SetTaskPaused(paused);
    turnPID.SetTaskPaused(paused);
}

bool DiffDrive::GetPausedPID()
{
    return PIDPaused; 
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

//base Sensor
double SensorInterface::Get()
{
    return 0;
}

void SensorInterface::Reset()
{

}


//Encoder Wheel Sensor
EncoderWheelSensorInterface::EncoderWheelSensorInterface(pros::ADIEncoder encoder) : encoder(encoder) {}

double EncoderWheelSensorInterface::Get()
{
    return encoder.get_value();
}

void EncoderWheelSensorInterface::Reset()
{
    encoder.reset();
}

//Motor Wheel Sensor
DiffDrive::DriveSensorInterface::DriveSensorInterface(MinesMotorGroup left, MinesMotorGroup right) : left(left), right(right) {}

double DiffDrive::DriveSensorInterface::Get()
{
    return (left.getPosition() + right.getPosition()) / 2;
}

void DiffDrive::DriveSensorInterface::Reset()
{
    left.tarePosition();
    right.tarePosition();
}


