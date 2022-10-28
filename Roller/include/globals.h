#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"

#define INERTIAL_SENSOR 17

#define TOP_ROLLER 11

#define L_TOP_FRONT 2
#define L_BOT_FRONT 10
#define L_REAR 11
#define R_TOP_FRONT 5
#define R_BOT_FRONT 12
#define R_REAR 6

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

extern std::vector<pros::Motor> leftDriveMotors;
extern std::vector<pros::Motor> rightDriveMotors;

extern std::vector<pros::Motor> catapultMotors;

#endif