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

namespace Mines {

class DiffDrive
{
    //static nested classes
    class DriveInterface : public PIDInterface
    {
        DiffDrive* parent;

        public:
            DriveInterface(DiffDrive* pParent);

            double getPositionActual() override;
            double getVelocityActual() override;
            void setVelocityPID(double value) override;
    };
    class TurnInterface : public PIDInterface
    {
        DiffDrive* parent;

        public:
            TurnInterface(DiffDrive* pParent);

            double getPositionActual() override;
            double getVelocityActual() override;
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
    
    bool ACTIVE = true;


    //updateable variables
    double turnVelocity = 0;
    double driveVelocity = 0;

    public:
        DiffDrive(MinesMotorGroup left, MinesMotorGroup right, pros::Imu Imu);

        void driveTiles(double target, bool waitForCompletion=true);
        void driveTiles(double target, int timeOut);
        void turnDegreesAbsolute(double target, bool waitForCompletion=true);
        void turnDegreesAbsolute(double target, int timeOut);

        //configuration functions
        void setBrakeMode(pros::motor_brake_mode_e mode);
        void setDrivePIDVals(double kp, double ki, double kd, double maxAccel);
        void setTurnPIDVals(double kp, double ki, double kd, double maxAccel);
        void setDrivePIDTol(double tolerance);
        void setTurnPIDTol(double tolerance);
        void setMaxDriveSpeed(double percent);
        void setMaxTurnSpeed(double percent);
        void setActive(bool active);

        void killPIDs();
        void StartPIDs();


    private:
        double getDrivePosition();
        double getDriveVelocity();
        void setDriveVelocity(double value);
        double getTurnPosition();
        double getTurnVelocity();
        void setTurnVelocity(double value);
        void setMotorVelocities();

};

}

#endif

