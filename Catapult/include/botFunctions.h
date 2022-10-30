#ifndef BOTFUNCTIONS_H
#define BOTFUNCTIONS_H

#include "globals.h"
#include "MinesMotorGroup.h"

void toggleIntake();
void intakeLoop(bool rev);
void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity);
void catapultLoop(Mines::MinesMotorGroup catapultMotorGroup, double velocity, bool run);
void fire(Mines::MinesMotorGroup motorGroup);
void rollerLoop(pros::Motor roller, double velocity, bool run);

#endif