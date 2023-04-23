#include "../include/globals.h"
#include "pros/adi.hpp"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu intertialSensor(INERTIAL_SENSOR);
pros::ADIEncoder driveEncoder(ENCODER_TOP, ENCODER_BOTTOM, false);
pros::Vision vision(VISION_SENSOR);
pros::Optical opticalSensor(COLOR_SENSOR);

pros::Motor topRoller(TOP_ROLLER, pros::E_MOTOR_GEARSET_18, false);

pros::Motor intake1(INTAKE1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor intake2(INTAKE2, pros::E_MOTOR_GEARSET_18, false);

pros::Motor leftFrontDrive(L_FRONT, pros::E_MOTOR_GEARSET_18, true);
pros::Motor leftRearDrive(L_REAR, pros::E_MOTOR_GEARSET_18, true);
pros::Motor leftMidDrive(L_MID, pros::E_MOTOR_GEARSET_18, true);
pros::Motor rightFrontDrive(R_FRONT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor rightRearDrive(R_REAR, pros::E_MOTOR_GEARSET_18, false);
pros::Motor rightMidDrive(R_MID, pros::E_MOTOR_GEARSET_18, false);

pros::Motor fly1(FLY1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor fly2(FLY2, pros::E_MOTOR_GEARSET_06, false);

pros::ADIDigitalOut endgame(LAUNCH);
pros::ADIDigitalOut rake(RAKES);
pros::ADIDigitalOut shoot1(PUSH);
pros::ADIDigitalOut shoot3(PUSH3);
pros::ADIDigitalOut compress(COMPRESSION);

std::vector<pros::Motor> leftDriveVector = {leftFrontDrive, leftRearDrive, leftMidDrive};
std::vector<pros::Motor> rightDriveVector = {rightFrontDrive, rightRearDrive, rightMidDrive};
std::vector<pros::Motor> flywheels = {fly1, fly2};
std::vector<pros::Motor> intakes = {intake1, intake2};
Mines::MinesMotorGroup leftDriveMotors(leftDriveVector);
Mines::MinesMotorGroup rightDriveMotors(rightDriveVector);
Mines::MinesMotorGroup flywheelsGroup(flywheels);
Mines::MinesMotorGroup intakeGroup(intakes);

double axisPercentBlue = 600.0 / 127;
double axisPercentGreen = 200.0 / 127;
double axisPercentRed = 100.0 / 127;
int blueGearbox = 600;
int greenGearbox = 200;
int redGearbox = 100;

uint8_t RED_GOAL_SIG_ID = 1;
uint8_t BLUE_GOAL_SIG_ID = 2;

int requiredColorLoops = 3;
const double ROLLER_TIMEOUT = 3000;

bool skills = false;