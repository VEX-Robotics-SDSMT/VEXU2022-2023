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

bool skills = 1;
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
	drive.setDrivePIDVals(2.46725, 0, 0.135);
	drive.setDrivePIDTol(10);
	drive.setTurnPIDVals(0.01, 0, 0);
	drive.setTurnPIDTol(2);

	drive.driveTiles(1, true);
	//drive.driveTiles(1000);
	drive.turnDegreesAbsolute(720);
	
	if(skills) // Skills route
	{
		drive.driveTiles(2000); //Tuning PID

		//drive.driveTiles(100);
		//drive.turnDegreesAbsolute(90);

		//bot moving forward is intake
		//shooting is back of bot

		/*

		drive.driveTiles(0.07); //small back
		topRoller.move(127); //roller
		pros::delay(100); 
		topRoller.brake(); //roller stop      //STEP 1
		drive.turnDegreesAbsolute(-90); //turn
		flywheelsGroup.move(127); //shoot preloads
		pros::delay(1500);
		for( int i = 0; i < 3; i++)
		{
			push.set_value(1);
			push.set_value(0);
			pros::delay(500);
		}
		flywheelsGroup.brake(); //flywheel stop //STEP 2

		/*
		intake.move(127);
		pros::delay(1000);
		drive.turnDegreesAbsolute(-135); //turn
		drive.driveTiles(0.3); //pick up 1 disc
		pros::delay(1000);
		drive.turnDegreesAbsolute(315); //turn down the line
		drive.driveTiles(0.7); //pick up other disc
		pros::delay(1000);
		intake.brake(); //stop intake
		drive.driveTiles(-1);
		drive.turnDegreesAbsolute(-90); //turn toward roller
		drive.driveTiles(1.5); //drive to roller
		roller.move(127); //roller on
		pros::delay(100);
		roller.brake(); //roller brake   //STEP 3
		drive.driveTiles(0.1);
		drive.turnDegreesAbsolute(-95);
		flywheels.move(127); //flywheel on
		pros::delay(1500);
		for(int i = 0;, i < 3; i++)
		{
			push.set_value(1);
			push.set_value(0);
			pros::delay(500);
		}
		flywheels.brake(); //stop flywheel     //STEP 4
		drive.turnDegreesAbsolute(-135);
		intake.move(127);
		pros::delay(1000);
		drive.driveTiles(3);
		pros::delay(1000);
		intake.brake();
		drive.turnDegreesAbsolute(255);
		pros::delay(1000);
		flywheels.move(127);
		pros::delay(1500);
		for(int i = 0; i < 3; i++)
		{
			push.set_value(1);
			push.set_value(0);
			pros::delay(500);
		}
		flywheels.brake();    //STEP 5
		drive.turnDegreesAbsolute(135);
		drive.driveTiles(4);

		//endgame launch      //STEP 6
		//*/


		//small back
		//roller
		//turn
		//shoot preloads goal 1
		//pick up two along diagnol
		//move to roller
		//roller
		//turn toward goal 2
		//shoot goal 2
		//turn and pick up three
		//turn and shoot goal 2
		
	}
	else // Match auton route
	{
		// small move back
		//roller
		//small move forward
		//aim
		//shoot
		//turn
		//drive w/ intakes
		// pick up 3
		// turn
		//shoot
		//turn
		//drive w/ intakes
		//pick up 3
		// turn
		//shoot
	}

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
