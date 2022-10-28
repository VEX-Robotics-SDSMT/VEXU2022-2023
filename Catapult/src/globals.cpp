#include "api.h"
#include "../include/globals.h"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu intertialSensor(INERTIAL_SENSOR);

pros::Motor topRoller(TOP_ROLLER, pros::E_MOTOR_GEARSET_36, false);

pros::Motor leftTopRearDrive(L_TOP_REAR, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftBotRearDrive(L_TOP_REAR, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftFrontDrive(L_FRONT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightTopRearDrive(R_TOP_REAR, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBotRearDrive(R_BOT_REAR, pros::E_MOTOR_GEARSET_06, true);
pros::Motor rightFrontDrive(R_FRONT, pros::E_MOTOR_GEARSET_06, false);

pros::Motor leftCatapult(R_CATAPULT, pros::E_MOTOR_GEARSET_36, false);
pros::Motor rightCatapult(L_CATAPULT, pros::E_MOTOR_GEARSET_36, false);

pros::Motor intake(INTAKE, pros::E_MOTOR_GEARSET_06, false);

std::vector<pros::Motor> leftDriveMotors = {leftTopRearDrive, leftBotRearDrive, leftFrontDrive};
std::vector<pros::Motor> rightDriveMotors = {rightTopRearDrive, rightBotRearDrive, rightFrontDrive};

std::vector<pros::Motor> catapultMotors {leftCatapult, rightCatapult};
