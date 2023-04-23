#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "MinesMotorGroup.h"

#define INERTIAL_SENSOR 15
#define RADIO 2
#define VISION 10

#define LEFT1 16
#define LEFT2 19
#define LEFT3 17
#define LEFT4 18

#define RIGHT1 14
#define RIGHT2 13
#define RIGHT3 12
#define RIGHT4 1

#define FRONT_FLY 3
#define BACK_FLY 5

#define RIGHT_INTAKE 6
#define LEFT_INTAKE 7

#define FRONT_ROLLER 9
#define BACK_ROLLER 2

#define COMPRESS 4
#define INTAKE 5
#define SINGLE 6
#define TRIPLE 7
#define ENCODER_TOP 1
#define ENCODER_BOTTOM 2
#define ENDGAME 3

#define ROLLER_MOTOR_GEARSET 600
#define INTAKE_MOTOR_GEARSET 600

extern pros::Controller MasterController;

extern pros::Imu intertialSensor;
extern pros::ADIEncoder driveEncoder;
extern pros::Vision vision;

extern pros::Motor frontRoller;
extern pros::Motor backRoller;
extern pros::Motor intakeR;
extern pros::Motor intakeL;

extern pros::Motor driveL1;
extern pros::Motor driveL2;
extern pros::Motor driveL3;
extern pros::Motor driveL4;
extern pros::Motor driveR1;
extern pros::Motor driveR2;
extern pros::Motor driveR3;
extern pros::Motor driveR4;

extern pros::Motor flyF;
extern pros::Motor flyB;

extern pros::ADIDigitalOut shoot1;
extern pros::ADIDigitalOut shoot3;
extern pros::ADIDigitalOut compress;
extern pros::ADIDigitalOut intake;
extern pros::ADIDigitalOut endgame;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;
extern Mines::MinesMotorGroup leftDriveMotors;
extern Mines::MinesMotorGroup rightDriveMotors;
extern Mines::MinesMotorGroup flywheelsGroup;
extern Mines::MinesMotorGroup intakeGroup;

extern double axisPercentBlue;
extern double axisPercentGreen;
extern double axisPercentRed;
extern int blue;
extern int green;
extern int red;

extern bool skills;

extern uint8_t RED_GOAL_SIG_ID;
extern uint8_t BLUE_GOAL_SIG_ID;

#define buttonUp pros::E_CONTROLLER_DIGITAL_UP
#define buttonDown pros::E_CONTROLLER_DIGITAL_DOWN
#define buttonLeft pros::E_CONTROLLER_DIGITAL_LEFT
#define buttonRight pros::E_CONTROLLER_DIGITAL_RIGHT
#define buttonX pros::E_CONTROLLER_DIGITAL_X
#define buttonY pros::E_CONTROLLER_DIGITAL_Y
#define buttonA pros::E_CONTROLLER_DIGITAL_A
#define buttonB pros::E_CONTROLLER_DIGITAL_B
#define buttonL1 pros::E_CONTROLLER_DIGITAL_L1
#define buttonL2 pros::E_CONTROLLER_DIGITAL_L2
#define buttonR1 pros::E_CONTROLLER_DIGITAL_R1
#define buttonR2 pros::E_CONTROLLER_DIGITAL_R2
#define axisLeftY pros::E_CONTROLLER_ANALOG_LEFT_Y
#define axisLeftX pros::E_CONTROLLER_ANALOG_LEFT_X
#define axisRightY pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define axisRightX pros::E_CONTROLLER_ANALOG_RIGHT_X

#endif