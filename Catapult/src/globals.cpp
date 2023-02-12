#include "api.h"
#include "../include/globals.h"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu inertialSensor(INERTIAL_SENSOR);
pros::Optical opticalSensor(COLOR_SENSOR);

pros::Motor topRoller(TOP_ROLLER, RED_GEARSET, true);
pros::Motor topRollerFront(TOP_ROLLER_FRONT, RED_GEARSET, false);


pros::Motor leftTopRearDrive(L_TOP_REAR, BLUE_GEARSET, false);
pros::Motor leftBotRearDrive(L_TOP_REAR, BLUE_GEARSET, false);
pros::Motor leftFrontDrive(L_FRONT, BLUE_GEARSET, false);
pros::Motor rightTopRearDrive(R_TOP_REAR, BLUE_GEARSET, true);
pros::Motor rightBotRearDrive(R_BOT_REAR, BLUE_GEARSET, false);
pros::Motor rightFrontDrive(R_FRONT, BLUE_GEARSET, true);

pros::Motor leftCatapult(R_CATAPULT, RED_GEARSET, false);
pros::Motor rightCatapult(L_CATAPULT, RED_GEARSET, true);

pros::Motor intake(INTAKE, BLUE_GEARSET, true);

pros::ADIDigitalIn limitSwitch (LIMIT_SWITCH);
pros::ADIDigitalOut shield (SHIELD);
pros::ADIDigitalOut endgame (ENDGAME);
pros::ADIDigitalOut wall(WALL);

std::vector<pros::Motor> leftDriveVector = {leftTopRearDrive, leftBotRearDrive, leftFrontDrive};
std::vector<pros::Motor> rightDriveVector = {rightTopRearDrive, rightBotRearDrive, rightFrontDrive};

std::vector<pros::Motor> catapultVector = {leftCatapult, rightCatapult};

Mines::MinesMotorGroup leftDriveMotors(leftDriveVector);
Mines::MinesMotorGroup rightDriveMotors(rightDriveVector);
Mines::MinesMotorGroup catapultMotors(catapultVector);

Mines::DiffDrive drive(leftDriveMotors, rightDriveMotors, inertialSensor);

double axisPercentBlue = 600.0 / 127;
double axisPercentGreen = 200.0 / 127;
double axisPercentRed = 100.0 / 127;
int blueMotorGearset = 600;
int greenMotorGearset = 200;
int redMotorGearset = 100;
int requiredColorLoops = 15;