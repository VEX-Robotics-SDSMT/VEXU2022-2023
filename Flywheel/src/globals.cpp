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

pros::Motor string(STRING, pros::E_MOTOR_GEARSET_36, true);

std::vector<pros::Motor> leftDriveVector = {leftTopFrontDrive, leftTopRearDrive, leftBotDrive};
std::vector<pros::Motor> rightDriveVector = {rightTopFrontDrive, rightTopRearDrive, rightBotDrive};
Mines::MinesMotorGroup leftDriveMotors(leftDriveVector);
Mines::MinesMotorGroup rightDriveMotors(rightDriveVector);

double axisPercentBlue = 600.0 / 127;
double axisPercentGreen = 200.0 / 127;
double axisPercentRed = 100.0 / 127;
int blue = 600;
int green = 200;
int red = 100;
