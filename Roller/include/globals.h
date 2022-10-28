#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"

#define INERTIAL_SENSOR 20

#define TOP_ROLLER 11

#define L_TOP_FRONT 2
#define L_BOT_FRONT 11
#define L_REAR 10
#define R_TOP_FRONT 5
#define R_BOT_FRONT 12
#define R_REAR 6

#define L_CATAPULT 14
#define R_CATAPULT 1

extern pros::Controller MasterController;

extern pros::Imu intertialSensor;

extern pros::Motor topRoller;

extern pros::Motor leftTopFrontDrive;
extern pros::Motor leftBotFrontDrive;
extern pros::Motor leftRearDrive;
extern pros::Motor rightTopFrontDrive;
extern pros::Motor rightBotFrontDrive;
extern pros::Motor rightRearDrive;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;

#endif