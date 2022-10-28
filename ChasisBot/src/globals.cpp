#include "globals.h"

pros::Motor rightFrontDrive(12);
pros::Motor rightMidDrive(20);
pros::Motor rightBackDrive(20);
pros::Motor leftFrontDrive(11);
pros::Motor leftMidDrive(20);
pros::Motor leftBackDrive(20);


pros::IMU inertial(20);

pros::Controller MasterController (pros::E_CONTROLLER_MASTER);
