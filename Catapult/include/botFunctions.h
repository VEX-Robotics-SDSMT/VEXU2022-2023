#ifndef BOTFUNCTIONS_H
#define BOTFUNCTIONS_H

#include "globals.h"
#include "MinesMotorGroup.h"
#include "pros/adi.hpp"

void toggleIntake();
void intakeLoopHold(bool run, bool rev, double pct);
void intakeLoopToggle(bool rev, int pct);
void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity);
void catapultLoop(Mines::MinesMotorGroup catapultMotorGroup, int pct);
void rollerLoop(pros::Motor roller, pros::Motor rollerFront, double velocity, bool run, bool rev);
void fire(Mines::MinesMotorGroup motorGroup);
void loadAndFire(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch);
void catInit(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch, pros::ADIDigitalOut shield);
void catFire(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch, pros::ADIDigitalOut shield);

#endif