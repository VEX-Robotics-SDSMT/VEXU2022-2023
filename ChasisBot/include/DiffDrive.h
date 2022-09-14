#ifndef _FOUR_WHEEL_DRIVE
#define _FOUR_WHEEL_DRIVE

#define ONE_SEC_IN_MS 1000.0

#include <vector>
#include <sstream>
#include <fstream>
#include "api.h"

class FourWheelDrive
{
    pros::Motor_Group *rightMotors;
    MinesMotorGroup *leftMotors;
    vex::inertial *inertialSensor;
    vex::controller *master;

    //calibration values
    std::stringstream fileStream;
    //these values are observed from the routine in the past
    //they will work if the file input fails, but not as well
    double maxSpeed = 128;
    double midSpeed = 69;
    double minSpeed = 10;
    double speedBias = 1;

    double LRBiasHigh = 1;
    double LRBiasLow = 1;
    double LRBiasHighBack = 1;
    double LRBiasLowBack = 1;
    double maxAccelerationForward = 3;
    double maxAccelerationBackward = 3;

    const double ROTATION_MUL = 845;
    const int STOP_AMOUNT = 100;
    const int LOOP_DELAY = 20;
    const rotationUnits ROT_UNIT = rotationUnits::deg;
    const velocityUnits VEL_UNIT = velocityUnits::dps;
    const brakeType BRAKE_MODE = brakeType::brake;

public:
    FourWheelDrive(MinesMotorGroup&, MinesMotorGroup&,
        vex::inertial & , vex::controller &);

    void readCalibration();
    void writeCalibration();
    void calibrateAll();
    void calibrateMinSpeed();
    void calibrateMaxSpeed();
    void calibrateMaxAcceleration();
    void calibrateDrift();
    void calibrateDriftLoop(double testSpeed, double &bias);
    void waitForUser(std::string message);
    void showOff();

    void accelerate(double speed);
    void setMotorsRelative(MinesMotorGroup *motors, double distance, double speed);
    void setMotorsRelative(double distance, double speed);
    void setBrakes(vex::brakeType mode);
    double getSpeed(MinesMotorGroup *);
    double getAllSpeed();
    double getAllPosition();
    double getPosition(MinesMotorGroup * motors);

    void drive(MinesMotorGroup *leftWheelMotorVector,
        MinesMotorGroup *rightWheelMotorVector, int distance);
    void driveTilesPID(float numTiles, float desiredSpeed= 75);
    void turnDegreesAbsolutePID(float targetDegrees, float desiredSpeed = -1);
    void turnDegreesPID(float numDegrees, float desiredSpeed= 55);



private:
    void rawSetMotors(double speed, double bias = 1);
    void setMotors(MinesMotorGroup *motors, double speed);
    void setMotors(double speed);
    void setZeroPosition(MinesMotorGroup * motors);
    void setZeroPosition();

    bool panic();

    float degreeBoundingHelper(float inDegrees);
    float degreesToRadians(float radians);
    float radiansToDegrees(float degrees);
    float bindToMagnitude(float value, float MAX_MAGNITUDE);
    void setAllBrakeMode(MinesMotorGroup *motors, vex::brakeType mode);
    void setAllBrakeMode(vex::brakeType mode);


    void checkGyro();
    void correctGyroCalibration(float accel, float jerk);
    void addStream(std::stringstream &gyroStream, float speed);

};


#endif

