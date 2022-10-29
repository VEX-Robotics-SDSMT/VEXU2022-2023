#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "MinesMotorGroup.h"

#define INERTIAL_SENSOR 20

#define TOP_ROLLER 1

#define L_TOP_FRONT 2
#define L_TOP_REAR 10
#define L_BOT 11
#define R_TOP_FRONT 5
#define R_TOP_REAR 6
#define R_BOT 12
#define STRING 16

extern pros::Controller MasterController;

extern pros::Imu intertialSensor;

extern pros::Motor topRoller;

extern pros::Motor leftTopFrontDrive;
extern pros::Motor leftTopRearDrive;
extern pros::Motor leftBotDrive;
extern pros::Motor rightTopFrontDrive;
extern pros::Motor rightTopRearDrive;
extern pros::Motor rightBot;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;
extern Mines::MinesMotorGroup leftDriveMotors;
extern Mines::MinesMotorGroup rightDriveMotors;


extern pros::Motor string;

extern double axisPercentBlue;
extern double axisPercentGreen;
extern double axisPercentRed;
extern int blue;
extern int green;
extern int red;

#endif