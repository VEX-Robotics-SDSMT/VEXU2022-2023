#include "main.h"
#include "DiffDrive.h"
#include "globals.h"

//globals

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

using namespace Mines;

int redBlue = 0;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() 
{
	redBlue = initAutonSide(MasterController);
	//set up PIDs
	//testPID = Mines::PID();	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() 
{
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
	if(redBlue == 1) // red
	{

	}
	else if (redBlue == 2) // blue
	{

	}

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

MinesMotorGroup leftDriveMotors(leftDriveVector);
MinesMotorGroup rightDriveMotors(rightDriveVector);

void opcontrol()
{	
	//ATTENTION REMOVE:

	DiffDrive drive(leftDriveMotors, rightDriveMotors);

	drive.driveTiles(2);

	pros::lcd::set_text(2, "Drive succeeded");

	while(true)
	{
		pros::delay(1000);
	}


	double lefty = MasterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double rightx = MasterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); 
		leftDriveMotors.moveVelocity(((rightx+lefty) * 600 / 127));
		rightDriveMotors.moveVelocity(((rightx-lefty) * 600 / 127));

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			topRoller.move(127);
		}
		else
		{
			topRoller.brake();
		};
	

	//pid.SetTarget(-120);
	

	//DO NOT REMOVE: Main should not exit while there are subtasks going on - it will crash the robot
	while(true)
	{
		pros::c::delay(1000);
	}


	

	//DO NOT REMOVE: Main should not exit while there are subtasks going on - it will crash the robot
	while(true)
	{
		pros::c::delay(1000);
	}
}
