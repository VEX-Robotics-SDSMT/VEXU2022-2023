#ifndef BOTFUNCTIONS_H
#define BOTFUNCTIONS_H

#include "globals.h"
#include "MinesMotorGroup.h"

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity);
void rollerLoop(pros::Motor roller, double velocity, bool run);

#endif