#include "../include/globals.h"
#include "pros/adi.hpp"

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);

pros::Imu intertialSensor(INERTIAL_SENSOR);
pros::ADIEncoder driveEncoder(ENCODER_TOP, ENCODER_BOTTOM, false);
pros::Vision vision(VISION);


pros::Motor frontRoller(FRONT_ROLLER, pros::E_MOTOR_GEARSET_18, false);
pros::Motor backRoller(BACK_ROLLER, pros::E_MOTOR_GEARSET_18, true);


pros::Motor intakeR(RIGHT_INTAKE, pros::E_MOTOR_GEARSET_18, true);
pros::Motor intakeL(LEFT_INTAKE, pros::E_MOTOR_GEARSET_18, false);

pros::Motor driveL1(LEFT1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveL2(LEFT2, pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveL3(LEFT3, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveL4(LEFT4, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveR1(RIGHT1, pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveR2(RIGHT2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor driveR3(RIGHT3, pros::E_MOTOR_GEARSET_18, false);
pros::Motor driveR4(RIGHT4, pros::E_MOTOR_GEARSET_18, false);

pros::Motor flyF(FRONT_FLY, pros::E_MOTOR_GEARSET_06, true);
pros::Motor flyB(BACK_FLY, pros::E_MOTOR_GEARSET_06, false);

pros::ADIDigitalOut intake(INTAKE);
pros::ADIDigitalOut shoot1(SINGLE);
pros::ADIDigitalOut shoot3(TRIPLE);
pros::ADIDigitalOut compress(COMPRESS);
pros::ADIDigitalOut endgame(ENDGAME);

std::vector<pros::Motor> leftDriveVector = {driveL1, driveL2, driveL3, driveL4};
std::vector<pros::Motor> rightDriveVector = {driveR1, driveR2, driveR3, driveR4};
std::vector<pros::Motor> flywheels = {flyF, flyB};
std::vector<pros::Motor> intakes = {intakeR, intakeL};
Mines::MinesMotorGroup leftDriveMotors(leftDriveVector);
Mines::MinesMotorGroup rightDriveMotors(rightDriveVector);
Mines::MinesMotorGroup flywheelsGroup(flywheels);
Mines::MinesMotorGroup intakeGroup(intakes);

double axisPercentBlue = 600.0 / 127;
double axisPercentGreen = 200.0 / 127;
double axisPercentRed = 100.0 / 127;
int blue = 600;
int green = 200;
int red = 100;

uint8_t RED_GOAL_SIG_ID = 1;
uint8_t BLUE_GOAL_SIG_ID = 2;

bool skills = false;