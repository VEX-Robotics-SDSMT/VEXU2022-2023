#include "api.h"
#include "../include/globals.h"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu intertialSensor(INERTIAL_SENSOR);

pros::Motor topRoller(TOP_ROLLER, pros::E_MOTOR_GEARSET_36, false);

pros::Motor leftTopFrontDrive(L_TOP_FRONT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBotFrontDrive(L_BOT_FRONT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftRearDrive(L_REAR, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightTopFrontDrive(R_TOP_FRONT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightBotFrontDrive(R_BOT_FRONT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightRearDrive(R_REAR, pros::E_MOTOR_GEARSET_06, true);

std::vector<pros::Motor> leftDriveVector = {leftTopFrontDrive, leftBotFrontDrive, leftRearDrive};
std::vector<pros::Motor> rightDriveVector = {rightTopFrontDrive, rightBotFrontDrive, rightRearDrive};