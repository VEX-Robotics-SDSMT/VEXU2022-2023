#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "api.h"
#include "./DiffDrive.h"
#include "./MinesMotorGroup.h"
#include "./Logger.h"

#define INERTIAL_SENSOR 17
#define COLOR_SENSOR 7

#define TOP_ROLLER 12
#define TOP_ROLLER_FRONT_L 21
#define TOP_ROLLER_FRONT_R 3
#define ROLLER_MOTOR_GEARSET redGearing

#define L_TOP_REAR 19
#define L_TOP_REAR_MOTOR_GEARSET blueGearing
#define L_BOT_REAR 16
#define L_BOT_REAR_MOTOR_GEARSET blueGearing
#define L_FRONT 20
#define L_FRONT_MOTOR_GEARSET blueGearing
#define R_TOP_REAR 5
#define R_TOP_REAR_MOTOR_GEARSET blueGearing
#define R_BOT_REAR 6
#define R_BOT_REAR_MOTOR_GEARSET blueGearing
#define R_FRONT 8
#define R_FRONT_MOTOR_GEARSET blueGearing

#define L_CATAPULT 14
#define L_CATAPULT_MOTOR_GEARSET redGearing
#define R_CATAPULT 1
#define R_CATAPULT_MOTOR_GEARSET redGearing


#define INTAKE 15
#define INTAKE2 16
#define INTAKE_MOTOR_GEARSET blueGearing

#define LIMIT_SWITCH 2
#define LIMIT_SWITCH_MID 3 
#define SHIELD 8
#define ENDGAME 1
#define WALL 4 //currently do not have wall

enum Color { red, blue, purple };

//loggers
extern ScreenLogger colorLogger;

extern pros::Controller MasterController;

extern pros::Imu inertialSensor;
extern pros::Optical opticalSensor;

//sensor that doesn't exist
extern pros::Vision visionSensor;
//-----------

extern pros::Motor topRoller;
extern pros::Motor topRollerFrontR;
extern pros::Motor topRollerFrontL;

extern pros::Motor leftTopRearDrive;
extern pros::Motor leftBotRearDrive;
extern pros::Motor leftFrontDrive;
extern pros::Motor rightTopRearDrive;
extern pros::Motor rightBotRearDrive;
extern pros::Motor rightFrontDrive;

extern pros::Motor leftCatapult;
extern pros::Motor rightCatapult;

extern pros::Motor intake;
extern pros::Motor intake2;

extern pros::ADIDigitalIn limitSwitch;
extern pros::ADIDigitalIn limitSwitchMid;
extern pros::ADIDigitalOut shield;
extern pros::ADIDigitalOut endgame;
extern pros::ADIDigitalOut wall;

extern std::vector<pros::Motor> leftDriveVector;
extern std::vector<pros::Motor> rightDriveVector;

extern std::vector<pros::Motor> catapultVector;

extern Mines::MinesMotorGroup leftDriveMotors;
extern Mines::MinesMotorGroup rightDriveMotors;
extern Mines::MinesMotorGroup catapultMotors;
extern Mines::MinesMotorGroup topRollerFront;

extern Mines::DiffDrive drive;

extern double axisPercentBlue;
extern double axisPercentGreen;
extern double axisPercentRed;

extern int redGearing;
extern int greenGearing;
extern int blueGearing;
extern double absoluteRot;
extern int requiredColorLoops;
extern const double ROLLER_TIMEOUT;

#define RED_GEARSET pros::E_MOTOR_GEARSET_36
#define GREEN_GEARSET pros::E_MOTOR_GEARSET_18
#define BLUE_GEARSET pros::E_MOTOR_GEARSET_06

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
#define axisleftX pros::E_CONTROLLER_ANALOG_LEFT_X
#define axisRightY pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define axisRightX pros::E_CONTROLLER_ANALOG_RIGHT_X

#endif