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
	DiffDrive drive(leftDriveMotors, rightDriveMotors, intertialSensor);
	drive.setDrivePIDVals(15, 0, 0);
	drive.setDrivePIDTol(0);
	drive.setTurnPIDVals(0.01, 0, 0);
	drive.setTurnPIDTol(2);

	drive.driveTiles(1000);
	//drive.driveTiles(1500);

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


	//Attention! do not remove, bot will crash
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
	int flywheelPct = 100;

	while(true)
	{		
		// 2 stick arcade
		// double leftAxisY = MasterController.get_analog(axisLeftY);
		// double rightAxisX = MasterController.get_analog(axisRightX);
		// double leftVelocity = ((rightAxisX + leftAxisY) * axisPercentBlue);
		// double rightVelocity = ((rightAxisX - leftAxisY) * axisPercentBlue);

		// 1 stick arcade
		double leftAxisY = MasterController.get_analog(axisLeftY);
		double leftAxisX = MasterController.get_analog(axisLeftX);
		double rightAxisX = MasterController.get_analog(axisRightX);
		double aimVelocityLeft = (rightAxisX) * 0.06;
		double aimVelocityRight = -rightAxisX * 0.06;
		double leftVelocity = ((leftAxisY + leftAxisX + aimVelocityLeft));
		double rightVelocity = ((leftAxisY - leftAxisX + aimVelocityRight));

		// Tank
		// double leftAxisY = MasterController.get_analog(axisLeftY);
	    // double rightAxisY = MasterController.get_analog(axisRightY);
		// double leftVelocity = ((leftAxisY) * axisPercentBlue);
		// double rightVelocity = ((-rightAxisY) * axisPercentBlue);

		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
		{
			toggleFlywheels();
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{
			toggleIntake();
		}

		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			flywheelPct = 100;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			flywheelPct = 75;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			flywheelPct = 50;
		}

		driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		rollerLoop(topRoller, green, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_Y));
		//intakeLoopToggle(MasterController.get_digital(buttonR2), 1);
		flywheelsGroup.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
		intakeLoopHold(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2), 100);
		flywheelLoopToggle(flywheelsGroup, flywheelPct);

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			launch.set_value(true);
		}
		else
		{
			launch.set_value(false);
		}

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			push.set_value(true);
		}
		else
		{
			push.set_value(false);
		}
	}
}
