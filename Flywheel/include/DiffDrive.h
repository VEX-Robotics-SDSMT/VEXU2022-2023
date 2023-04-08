#ifndef DIFF_DRIVE
#define DIFF_DRIVE

#include "MinesMotorGroup.h"
#include "PID.h"
#include "pros/imu.hpp"
#include <math.h>
#include "Logger.h"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.h"
#include <algorithm>
#include <cmath>
#include <limits.h>

namespace Mines {


class SensorInterface
{
    public:
        double Get();
        double Reset();
};


class DiffDrive
{
    //static nested classes
    class DriveInterface : public PIDInterface
    {
        DiffDrive* parent;

        public:
            DriveInterface(DiffDrive* pParent);

            double getPositionPID() override;
            void setVelocityPID(double value) override;
    };
    class TurnInterface : public PIDInterface
    {
        DiffDrive* parent;

        public:
            TurnInterface(DiffDrive* pParent);

            double getPositionPID() override;
            void setVelocityPID(double value) override;
    };

    //instance variables
    MinesMotorGroup leftMotors;
    MinesMotorGroup rightMotors;
    pros::Imu inertial;

    DriveInterface driveInterface;
    TurnInterface turnInterface;
    PID drivePID;
    PID turnPID;

    ScreenLogger logger;

    //configuration variables
    double MAX_SPEED;
    int GOAL_TIME = 500;
    double MAX_DRIVE_PERCENT = 1;
    double MAX_TURN_PERCENT = 1;
    double MAX_DRIVE_ACCEL = 1;
    double MAX_TURN_ACCEL = 1;
    
    bool ACTIVE = true;


    //updateable variables
    double turnVelocity = 0;
    double driveVelocity = 0;

    public:
        DiffDrive(MinesMotorGroup left, MinesMotorGroup right, pros::Imu Imu);
        DiffDrive(MinesMotorGroup left, MinesMotorGroup right, SensorInterface driveSensorInterface, pros::Imu Imu);

        double getDriveVelocity();
        double getTurnVelocity();

        void driveTiles(double target, bool waitForCompletion=true);
        void driveTiles(double target, int timeOut);
        void turnDegreesAbsolute(double target, bool waitForCompletion=true);
        void turnDegreesAbsolute(double target, int timeOut);

        //configuration functions
        void setBrakeMode(pros::motor_brake_mode_e mode);
        void setDrivePIDVals(double kp, double ki, double kd);
        void setTurnPIDVals(double kp, double ki, double kd);
        void setDrivePIDTol(double tolerance);
        void setTurnPIDTol(double tolerance);
        void setMaxDriveSpeed(double percent);
        void setMaxTurnSpeed(double percent);
        void setMaxDriveAccel(double value);
        void setMaxTurnAccel(double value);
        void setActive(bool active);

        void killPIDs();
        void StartPIDs();
        void SetPausedPID(bool paused);

        //these should only be called from the inside or when the PID is off
        void setTurnVelocity(double value);
        void setDriveVelocity(double value);

    private:
        double getDrivePosition();
        double getTurnPosition();
        void setMotorVelocities();

};

}

#endif

