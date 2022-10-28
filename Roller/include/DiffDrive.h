#ifndef DIFF_DRIVE
#define DIFF_DRIVE

#include "MinesMotorGroup.h"
#include "PID.h"

namespace Mines {

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

    //instance variables and functions
    MinesMotorGroup leftMotors;
    MinesMotorGroup rightMotors;
    DriveInterface driveInterface;
    TurnInterface turnInterface;
    PID drivePID;
    PID turnPID;

    public:
        DiffDrive(MinesMotorGroup left, MinesMotorGroup right);

        void driveTiles(double target, bool waitForCompletion=true);
        void turnDegreesAbsolute(double target, bool waitForCompletion);
        void turnDegreesRelative(double target, bool waitForCompletion);
        void setBrakeMode(pros::motor_brake_mode_e mode);

    private:
        double getDrivePosition();
        void setDriveVelocity(double value);
        double getTurnPosition();
        void setTurnVelocity(double value);

};

}

#endif

