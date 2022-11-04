#include "main.h"
#include "DiffDrive.h"
#include "globals.h"
#include "pros/rtos.h"

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
	intertialSensor.reset();
	//redBlue = initAutonSide(MasterController);
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
	// DiffDrive drive(leftDriveMotors, rightDriveMotors, intertialSensor);
	// drive.setDrivePIDVals(0.6, 0, 0);
	// drive.setDrivePIDTol(100);
	// drive.setTurnPIDVals(3, 0, 0);
	// drive.setTurnPIDTol(2);

	// // drive.driveTiles(3000);
	// // pros::lcd::set_text(7, "Drive succeeded");
	// // pros::delay(2000);

	// // drive.turnDegreesAbsolute(270);

	// // pros::lcd::set_text(7, "Turn succeeded");

	// drive.driveTiles(50);
	// topRoller.move_velocity(200);
	// pros::delay(1000);
	// topRoller.brake();
	// drive.driveTiles(-1500);
	// drive.turnDegreesAbsolute(90);
	// drive.driveTiles(1500);
	// topRoller.move_velocity(200);
	// pros::delay(1000);
	// drive.driveTiles(-500);

	while(true)
	{
		pros::delay(1000);
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

void opcontrol()
{	

	while(true)
	{
		double leftAxisY = MasterController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double rightAxisX = MasterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		double rightAxisY = MasterController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		double leftVelocity = (leftAxisY*axisPercentBlue);
		double rightVelocity = (rightAxisY*axisPercentBlue);
		//double leftVelocity = ((leftAxisY) * axisPercentBlue);
		//double rightVelocity = ((-rightAxisX + leftAxisY) * axisPercentBlue);

		driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		rollerLoop(topRoller, red, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X));

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			string.move_velocity(100);
		}
		else if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			string.move_velocity(-100);
		}
		else
		{
			string.brake();
		}
	}
}
