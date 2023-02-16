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
	//Skills?
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
	drive.setDrivePIDVals(0.2, 0, 0);
	drive.setDrivePIDTol(5);
	drive.setTurnPIDVals(1.2, 0, 0);//1.2
	drive.setTurnPIDTol(1);
	drive.setMaxDriveSpeed(0.3);
	drive.setMaxTurnSpeed(0.7);
	
	if(skills) // Skills route
	{
		flywheelsGroup.move(102);  //107, 90
		drive.driveTiles(-100,false);
		topRoller.set_zero_position(0);
	
		pros::delay(600);
 	
		topRoller.move_absolute(-750,127); //move roller
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		drive.driveTiles(300, true); //turn and shoot two preloads
		drive.turnDegreesAbsolute(75.75); //72
		pros::delay(500);

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1100);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(300);

		flywheelsGroup.move(93);   //100, 60		
		drive.turnDegreesAbsolute(-130.5); //pick up three
		intake.move(-120);
		drive.setMaxDriveSpeed(0.20);
		drive.driveTiles(-2800);
		pros::delay(100);
		drive.turnDegreesAbsolute(110); //turn and shoot, 113

		pros::delay(500);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1100);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1100);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(500);


		drive.setMaxDriveSpeed(0.40);
		drive.turnDegreesAbsolute(-140);
		intake.move(-127);
		drive.driveTiles(-1100);

		flywheelsGroup.move(94);  // 95, 30
		drive.turnDegreesAbsolute(127); //pick up one 128
		pros::delay(700); //500
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(300); //shoot one
		
		
		drive.driveTiles(425); //-160
		drive.turnDegreesAbsolute(0);
		
		drive.setMaxDriveSpeed(0.25);
		drive.driveTiles(-2300);
		
		flywheelsGroup.move(92);  //112, 30
		drive.setMaxDriveSpeed(0.5);

		drive.turnDegreesAbsolute(77);
		drive.driveTiles(-250);
		

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(800);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1100);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(500);
		flywheelsGroup.move(110);

		drive.turnDegreesAbsolute(-42);

		drive.setMaxDriveSpeed(0.75);
		drive.driveTiles(1700);
		drive.turnDegreesAbsolute(90);
		drive.setMaxDriveSpeed(0.3);
		drive.driveTiles(-2850);
		drive.setMaxDriveSpeed(0.5);
		drive.driveTiles(-500, false);

		topRoller.set_zero_position(0);
	
		pros::delay(600);

 	
		topRoller.move_absolute(-950,127); 
		//drive.driveTiles(-400,false);
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		drive.driveTiles(500);
		drive.turnDegreesAbsolute(89.5);

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1000);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1200);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(300);

		drive.driveTiles(300);
		drive.turnDegreesAbsolute(55, 1000);
		launch.set_value(true);
	}
	else // Match auton route
	{
		drive.driveTiles(-100,false);
		topRoller.set_zero_position(0);
	
		pros::delay(600);
 	
		topRoller.move_absolute(-250,127); //move roller
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		flywheelsGroup.move(107);  //106

		drive.driveTiles(300, true); //turn and shoot two preloads
		drive.turnDegreesAbsolute(-15.25); //15
		pros::delay(2000);

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1500);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(300);
		
		drive.turnDegreesAbsolute(-130.5); //pick up three
		intake.move(-110);
		drive.setMaxDriveSpeed(0.15);
		drive.driveTiles(-2800);
		flywheelsGroup.move(102);   //100
		pros::delay(100);
		drive.turnDegreesAbsolute(-43.5); //turn and shoot

		pros::delay(1000);

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1900);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(2100);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(500);
		
		drive.turnDegreesAbsolute(-143);
		intake.move(-127);
		drive.driveTiles(-1100);

		flywheelsGroup.move(98);  // 95
		drive.turnDegreesAbsolute(-55); //pick up one
		pros::delay(700); //500
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(700);
		pros::delay(300); //shoot one
		
		
		drive.driveTiles(-160);
		drive.turnDegreesAbsolute(0);
		
		drive.setMaxDriveSpeed(0.25);
		drive.driveTiles(-2300);
		
		flywheelsGroup.move(113);  //112
		drive.setMaxDriveSpeed(0.5);

		drive.turnDegreesAbsolute(-42);
		

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1800);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(2000);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(500);
	}

	drive.killPIDs();
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
			flywheelPct = 85;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			flywheelPct = 80;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
		{
			flywheelPct = 72;
		}

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			driveLoop(leftDriveMotors, rightDriveMotors, .3*leftVelocity, .3*rightVelocity);
		}
		else
		{
			driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		}
		
		rollerLoop(topRoller, green, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_Y), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X));
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
