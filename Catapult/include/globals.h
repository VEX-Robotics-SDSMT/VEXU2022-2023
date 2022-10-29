#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"

#define INERTIAL_SENSOR 17

#define TOP_ROLLER 11

#define L_TOP_REAR 19
#define L_BOT_REAR 16
#define L_FRONT 20
#define R_TOP_REAR 5
#define R_BOT_REAR 6
#define R_FRONT 8

#define L_CATAPULT 14
#define R_CATAPULT 1

#define INTAKE 15

extern pros::Controller MasterController;

extern pros::Imu intertialSensor;

extern pros::Motor topRoller;

extern pros::Motor leftTopRearDrive;
extern pros::Motor leftBotRearDrive;
extern pros::Motor leftFrontDrive;
extern pros::Motor rightTopRearDrive;
extern pros::Motor rightBotRearDrive;
extern pros::Motor rightFrontDrive;

extern pros::Motor leftCatapult;
extern pros::Motor rightCatapult;

extern pros::Motor intake;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;

extern std::vector<pros::Motor> catapultVector;

extern double axisPercentBlue;
extern double axisPercentGreen;
extern double axisPercentRed;
extern int blue;
extern int green;
extern int red;

#endif