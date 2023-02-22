#include "api.h"
#include "../include/globals.h"

//loggers
ScreenLogger colorLogger(LoggerSettings::verbose);

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu inertialSensor(INERTIAL_SENSOR);
pros::Optical opticalSensor(COLOR_SENSOR);

pros::Motor topRoller(TOP_ROLLER, RED_GEARSET, true);
pros::Motor topRollerFrontLeft(TOP_ROLLER_FRONT_L, RED_GEARSET, false);
pros::Motor topRollerFrontRoght(TOP_ROLLER_FRONT_R, RED_GEARSET, true);


pros::Motor leftTopRearDrive(L_TOP_REAR, BLUE_GEARSET, false);
pros::Motor leftBotRearDrive(L_TOP_REAR, BLUE_GEARSET, false);
pros::Motor leftFrontDrive(L_FRONT, BLUE_GEARSET, false);
pros::Motor rightTopRearDrive(R_TOP_REAR, BLUE_GEARSET, true);
pros::Motor rightBotRearDrive(R_BOT_REAR, BLUE_GEARSET, false);
pros::Motor rightFrontDrive(R_FRONT, BLUE_GEARSET, true);

pros::Motor leftCatapult(R_CATAPULT, RED_GEARSET, false);
pros::Motor rightCatapult(L_CATAPULT, RED_GEARSET, true);

pros::Motor intake(INTAKE, BLUE_GEARSET, true);
pros::Motor intake2(INTAKE2, BLUE_GEARSET, false);

pros::ADIDigitalIn limitSwitch (LIMIT_SWITCH);
pros::ADIDigitalIn limitSwitchMid (LIMIT_SWITCH_MID);
pros::ADIDigitalOut shield (SHIELD);
pros::ADIDigitalOut endgame (ENDGAME);

std::vector<pros::Motor> leftDriveVector = {leftTopRearDrive, leftBotRearDrive, leftFrontDrive};
std::vector<pros::Motor> rightDriveVector = {rightTopRearDrive, rightBotRearDrive, rightFrontDrive};

std::vector<pros::Motor> catapultVector = {leftCatapult, rightCatapult};
std::vector<pros::Motor> topRollerFrontVector = {topRollerFrontLeft, topRollerFrontRoght};

Mines::MinesMotorGroup leftDriveMotors(leftDriveVector);
Mines::MinesMotorGroup rightDriveMotors(rightDriveVector);
Mines::MinesMotorGroup catapultMotors(catapultVector);
Mines::MinesMotorGroup topRollerFront(topRollerFrontVector);

Mines::DiffDrive drive(leftDriveMotors, rightDriveMotors, inertialSensor);

double axisPercentBlue = 600.0 / 127;
double axisPercentGreen = 200.0 / 127;
double axisPercentRed = 100.0 / 127;

int redGearing = 100;
int greenGearing = 200;
int blueGearing = 600;
int requiredColorLoops = 50;
const double ROLLER_TIMEOUT = 1500;
