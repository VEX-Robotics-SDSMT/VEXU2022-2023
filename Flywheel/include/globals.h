#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "MinesMotorGroup.h"

#define INERTIAL_SENSOR 10
#define VISION_SENSOR 1

#define TOP_ROLLER 11

#define L_FRONT 17
#define L_REAR 16
#define L_MID 14
#define R_FRONT 9
#define R_REAR 13
#define R_MID 8
#define STRING 13
#define FLY1 21
#define FLY2 20
#define INTAKE1 2
#define INTAKE2 19
#define LAUNCH 8
#define PUSH 7
#define PUSH3 6

#define INTAKE_MOTOR_GEARSET red
#define FLYWHEELS_MOTOR_GEARSET blue
#define ROLLER_MOTOR_GEARSET green

extern pros::Controller MasterController;

extern pros::Imu intertialSensor;
extern pros::Vision vision;

extern pros::Motor topRoller;
extern pros::Motor intake1;
extern pros::Motor intake2;

extern pros::Motor leftTopFrontDrive;
extern pros::Motor leftTopRearDrive;
extern pros::Motor leftBotDrive;
extern pros::Motor rightTopFrontDrive;
extern pros::Motor rightTopRearDrive;
extern pros::Motor rightBot;

extern pros::ADIDigitalOut endgame;
extern pros::ADIDigitalOut shoot1;
extern pros::ADIDigitalOut shoot3;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;
extern Mines::MinesMotorGroup leftDriveMotors;
extern Mines::MinesMotorGroup rightDriveMotors;
extern Mines::MinesMotorGroup flywheelsGroup;
extern Mines::MinesMotorGroup intakeGroup;



extern pros::Motor string;

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