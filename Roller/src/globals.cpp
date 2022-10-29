#include "api.h"
#include "../include/globals.h"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu intertialSensor(INERTIAL_SENSOR);

pros::Motor topRoller(TOP_ROLLER, pros::E_MOTOR_GEARSET_36, false);

pros::Motor leftTopFrontDrive(L_TOP_FRONT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftTopRearDrive(L_TOP_REAR, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBotDrive(L_BOT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightTopFrontDrive(R_TOP_FRONT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightTopRearDrive(R_TOP_REAR, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBotDrive(R_BOT, pros::E_MOTOR_GEARSET_06, true);

std::vector<pros::Motor> leftDriveVector = {leftTopFrontDrive, leftTopRearDrive, leftBotDrive};
std::vector<pros::Motor> rightDriveVector = {rightTopFrontDrive, rightTopRearDrive, rightBotDrive};


int testCounter = 0;