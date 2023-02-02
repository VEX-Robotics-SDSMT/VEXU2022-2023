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

bool skills = 0;
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
	drive.setDrivePIDVals(0.2, 0, 0);
	drive.setDrivePIDTol(5);
	drive.setTurnPIDVals(1.2, 0, 0);//1.2
	drive.setTurnPIDTol(1);
	drive.setMaxDriveSpeed(0.3);
	drive.setMaxTurnSpeed(0.7);

	// rightDriveMotors.moveVelocity(30);
	// leftDriveMotors.moveVelocity(-30);
	// pros::delay(1475); //second turn stack of three
	// rightDriveMotors.brake();
	// leftDriveMotors.brake();
	// pros::delay(500);
	// rightDriveMotors.moveVelocity(-30);
	// leftDriveMotors.moveVelocity(-30);
	// intake.move(-100); //pick up three
	// pros::delay(4700);
	// rightDriveMotors.brake();
	// leftDriveMotors.brake();
	// pros::delay(2500);
	// //intake.brake();
	// pros::delay(500);
	// leftDriveMotors.moveVelocity(40); //third turn
	// rightDriveMotors.moveVelocity(-40);
	// pros::delay(950);
	// leftDriveMotors.brake(); 
	// rightDriveMotors.brake();

	// flywheelsGroup.move(115);
	// pros::delay(3000);
	// for( int i = 0; i < 3; i++)
	// {
	// 	push.set_value(1);
	// 	pros::delay(100); //shoot three accross field
	// 	push.set_value(0);
	// 	pros::delay(2000);
	// }

	// intake.brake();
	// pros::delay(500);
	// leftDriveMotors.moveVelocity(-40);
	// rightDriveMotors.moveVelocity(40);
	// pros::delay(950); //turn back down the line

	// leftDriveMotors.moveVelocity(40);
	// rightDriveMotors.moveVelocity(40);
	// intake.move(120); //drive and pick up next three
	// pros::delay(6000); //**this value is not tuned**
	// leftDriveMotors.brake();
	// rightDriveMotors.brake();
	// pros::delay(2000);

	// leftDriveMotors.moveVelocity(40);
	// rightDriveMotors.moveVelocity(-40); //turn toward goal
	// pros::delay(1500); //**this value is not tuned**
	// rightDriveMotors.brake();
	// leftDriveMotors.brake();
	// intake.brake();

	// flywheelsGroup.move(115);
	// pros::delay(3000);
	// for( int i = 0; i < 3; i++)
	// {
	// 	push.set_value(1);
	// 	pros::delay(100); //shoot three accross field
	// 	push.set_value(0);
	// 	pros::delay(2000);
	// }
	// flywheelsGroup.brake(); //so far the end
	
	if(skills) // Skills route
	{
		//drive.driveTiles(1000); //Tuning PID

		//drive.driveTiles(100);
		// leftDriveMotors.moveVelocity(100);
		// rightDriveMotors.move(100);
		// pros::delay(1500);
		// //drive.turnDegreesAbsolute(90);
		// leftDriveMotors.moveVelocity(100);
		// rightDriveMotors.move(-100);

		drive.driveTiles(-100, false); //move backward to roller

 		topRoller.move(127); //move roller while applying pressure
		pros::delay(500);
		topRoller.brake();

		drive.driveTiles(300); //move forward IN LINE
		pros::delay(500);		
 
		drive.turnDegreesAbsolute(75); //RIGHT turn towards goal
		pros::delay(500);

		flywheelsGroup.move(105); //shoot preloads
		pros::delay(2800);
 		for( int i = 0; i < 2; i++)
		{
			push.set_value(1);
			pros::delay(100);
			push.set_value(0);
			pros::delay(1500);
		}

 		drive.turnDegreesAbsolute(138); //LEFT slight turn
		pros::delay(500);

		intake.move(-127);

		drive.driveTiles(-500); //move forward to corner disc
		pros::delay(500);		//pick up one along center

		drive.turnDegreesAbsolute(45); //LEFT slight turn
		pros::delay(500);
		drive.driveTiles(-900); //to corner along center
		pros::delay(500);
		intake.brake();

		drive.driveTiles(1600); //out of corner
		drive.turnDegreesAbsolute(90);
		drive.driveTiles(-1200); //back up to roller
		pros::delay(500);

		drive.driveTiles(-100, false);
		topRoller.move(127); //move roller while applying pressure
		pros::delay(500);
		topRoller.brake();
		drive.driveTiles(200); //pull forward slightly
		drive.turnDegreesAbsolute(85);

		flywheelsGroup.move(103); //shoot loads
		pros::delay(2500);
 		for( int i = 0; i < 2; i++)
		{
			push.set_value(1);
			pros::delay(100);
			push.set_value(0);
			pros::delay(1500);
		}
		flywheelsGroup.brake();

		drive.turnDegreesAbsolute(-45); //turn back down line
		intake.move(-127);
		drive.driveTiles(-3500); //drive and pick up three
		pros::delay(500);
		drive.turnDegreesAbsolute(-135); //turn toward far goal
		
		flywheelsGroup.move(103); //shoot loads
		pros::delay(2500);
 		for( int i = 0; i < 3; i++)
		{
			push.set_value(1);
			pros::delay(100);
			push.set_value(0);
			pros::delay(1500);
		}

		drive.turnDegreesAbsolute(-45); //turn back down line
		drive.driveTiles(-3000);
		pros::delay(500);
		drive.turnDegreesAbsolute(165); //turn toward goal

		flywheelsGroup.move(103); //shoot loads
		pros::delay(2500);
 		for( int i = 0; i < 3; i++)
		{
			push.set_value(1);
			pros::delay(100);
			push.set_value(0);
			pros::delay(1500);
		}

		flywheelsGroup.brake();

		drive.turnDegreesAbsolute(135);
		drive.driveTiles(-1500);
		launch.set_value(1);
		


		//up to this point, shoot 4 discs and both rollers
		//will need to speed up eventually
		//still tuning angles and shots
		//usually hits second of first two and last two

/*
		leftDriveMotors.moveVelocity(-50); //move forward to corner disc
		rightDriveMotors.moveVelocity(-50);
		pros::delay(1200);
		leftDriveMotors.brake();
		rightDriveMotors.brake();
		intake.brake();

		leftDriveMotors.moveVelocity(-50); //LEFT slight turn
		rightDriveMotors.moveVelocity(50);
		pros::delay(632);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		leftDriveMotors.moveVelocity(-30); //move backward to roller
		rightDriveMotors.moveVelocity(-30);
		pros::delay(1200);
 		topRoller.move(127); //move roller while applying pressure
		pros::delay(200);
		leftDriveMotors.brake();
		rightDriveMotors.brake();
		topRoller.brake();

		leftDriveMotors.moveVelocity(50); //move forward to corner disc
		rightDriveMotors.moveVelocity(50);
		pros::delay(1500);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		leftDriveMotors.moveVelocity(-50); //LEFT slight turn
		rightDriveMotors.moveVelocity(50);
		pros::delay(316);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		leftDriveMotors.moveVelocity(-50); //move forward to corner disc
		rightDriveMotors.moveVelocity(-50);
		pros::delay(700);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		pros::delay(17277);
		launch.set_value(1);
		pros::delay(1000);
		leftDriveMotors.moveVelocity(-50); //LEFT slight turn
		rightDriveMotors.moveVelocity(50);
		pros::delay(530);
		leftDriveMotors.brake();
		rightDriveMotors.brake();
		
		flywheelsGroup.move(113); //shoot preloads
		pros::delay(2500);
			push.set_value(1);
			pros::delay(100);
			push.set_value(0);
		flywheelsGroup.brake();
		//*/


		}
	else // Match auton route
	{
		

		drive.driveTiles(-100,false);
		topRoller.set_zero_position(0);
	
		pros::delay(600);
 	
		topRoller.move_absolute(800,127); //move roller
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		flywheelsGroup.move(106);

		drive.driveTiles(300, true); //turn and shoot two preloads
		drive.turnDegreesAbsolute(-14); //15
		pros::delay(1450);

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1500);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(400);

		
		drive.turnDegreesAbsolute(-130); //pick up three
		intake.move(-90);
		drive.setMaxDriveSpeed(0.20);
		drive.driveTiles(-2800);
		flywheelsGroup.move(99);
		pros::delay(200);
		drive.turnDegreesAbsolute(-43); //turn and shoot

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1800);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(1800);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(500);
		
		drive.turnDegreesAbsolute(-135);
		intake.move(-90);
		drive.driveTiles(-1100);

		flywheelsGroup.move(98);
		drive.turnDegreesAbsolute(-55); //pick up one
		pros::delay(700); //500
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(700);
		// push.set_value(1);
		// pros::delay(100);
		// push.set_value(0);
		// pros::delay(500);
		// push.set_value(1); //three just in case
		// pros::delay(100);
		// push.set_value(0);
		pros::delay(300); //shoot one

		drive.turnDegreesAbsolute(-7);
		drive.driveTiles(-210);
		pros::delay(200);
		drive.turnDegreesAbsolute(0);
		drive.setMaxDriveSpeed(0.25);
		drive.driveTiles(-500); //turn along low goal
		//pros::delay(200);
		drive.driveTiles(-1200);
		flywheelsGroup.move(114);
		drive.driveTiles(-700, 1500);

		drive.turnDegreesAbsolute(-40);
		

		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(2000);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);
		pros::delay(2000);
		push.set_value(1);
		pros::delay(100);
		push.set_value(0);

		//Match Auton seems fairly consistent hitting 4-6 out of 7
		//I don't believe any code could really fix this, maybe just setting
		//up consistently with full air tanks and battery




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

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			driveLoop(leftDriveMotors, rightDriveMotors, .3*leftVelocity, .3*rightVelocity);
		}
		else
		{
			driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		}
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
