#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "MinesMotorGroup.h"

#define INERTIAL_SENSOR 20

#define TOP_ROLLER 1

#define L_FRONT 17
#define L_REAR 16
#define L_MID 14
#define R_FRONT 9
#define R_REAR 13
#define R_MID 8
#define STRING 13

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