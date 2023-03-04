#include "main.h"
#include "botFunctions.h"
#include "globals.h"
#include "pros/misc.h"
#include "pros/motors.h"

using namespace Mines;


//globals

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

bool skills = true;
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
	endgame.set_value(0);
	wall.set_value(0);

	drive.setDrivePIDVals(0.90, 0, 0); //0.95
	drive.setDrivePIDTol(5);
	drive.setTurnPIDVals(2.98, 0, 0);//1.2
	drive.setTurnPIDTol(0.75);
	drive.setMaxDriveSpeed(0.5);
	drive.setMaxTurnSpeed(0.75);
	//redBlue = initAutonSide(MasterController);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() 
{
	drive.killPIDs();
}

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
 * with the default priority and stack size	 whenever the robot is enabled via
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
	double startTime = pros::millis();

	catapultMotors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	leftDriveMotors.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	rightDriveMotors.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

	drive.StartPIDs();

	if(skills)
	{
		catInit(catapultMotors, limitSwitch, shield);
		//drive.setActive(true);

		drive.driveTiles(550);	

		drive.turnDegreesAbsolute(90);

		intake.move(1270);
		intake2.move(1270);
		drive.driveTiles(1500);

		drive.driveTiles(-200);

		drive.turnDegreesAbsolute(0);				

		intake.brake();
		intake2.brake();

		drive.driveTiles(-1200, 1500);
		pros::delay(750);
		topRoller.move(127);
		pros::delay(320); //150
		topRoller.brake();

		drive.driveTiles(200); //1000
		drive.turnDegreesAbsolute(45);
		drive.driveTiles(700);
		drive.turnDegreesAbsolute(90);

		drive.driveTiles(1000, 1500);
		pros::delay(750);
		topRollerFrontR.move(127);
		pros::delay(190); //150
		topRollerFrontR.brake();
		drive.driveTiles(-900);

		drive.turnDegreesAbsolute(-180);
		drive.driveTiles(-3000);
		// drive.turnDegreesAbsolute(-190);
		drive.setActive(0);
		catFire(catapultMotors, limitSwitch, shield);

		for(int i = 0; i < 3; i++)
		{
			drive.setActive(1);
			drive.driveTiles(400);
			drive.setActive(0);
			leftDriveMotors.moveVelocity(-100);
			rightDriveMotors.moveVelocity(100);
			pros::delay(1150);
			while(limitSwitchMid.get_value() != 1)
			{
				catapultMotors.move(127);
			}
			catapultMotors.brake();
			shield.set_value(0);

			drive.setActive(1);
			drive.setMaxDriveSpeed(0.3);
			drive.driveTiles(750, 1000);
			drive.setMaxDriveSpeed(0.5);
			drive.setActive(0);

			inertialSensor.reset();
			while(inertialSensor.is_calibrating())
			{
				pros::delay(100);
			}
			pros::delay(1000);

			drive.setActive(1);
			drive.driveTiles(-900);
			drive.turnDegreesAbsolute(90);
			drive.driveTiles(-400);

			catFire(catapultMotors, limitSwitch, shield);
		}
		


	}
	else
	{
		catInit(catapultMotors, limitSwitch, shield);

		drive.driveTiles(500);
		drive.turnDegreesAbsolute(90, 1500);
		drive.driveTiles(1050);
		drive.turnDegreesAbsolute(0, 1500);
		drive.driveTiles(-525, 1500);
		pros::delay(500);
		topRoller.move(127);
		pros::delay(120); //150
		topRoller.brake();
		pros::delay(50); 

		drive.driveTiles(350);
		drive.turnDegreesAbsolute(-45, 2000);
		drive.driveTiles(850);
		drive.turnDegreesAbsolute(200, 1500);
		drive.driveTiles(100); //175
		catFire(catapultMotors, limitSwitch, shield);

		inertialSensor.reset();
		while (inertialSensor.is_calibrating())
		{
			pros::delay(20);
		}

		drive.driveTiles(275); //275 // PID is fine to here, retune or possible switch to encoder-based
		drive.turnDegreesAbsolute(117, 2000);
		drive.setActive(true);
		intake.move(127);
		drive.driveTiles(1350);
		pros::delay(1000);
		drive.setActive(false);
		leftDriveMotors.move(-100);
		rightDriveMotors.move(100);
		pros::delay(600);
		drive.setActive(true);

		drive.driveTiles(500);
		catFire(catapultMotors, limitSwitch, shield);
		intake.brake();

		/*drive.setActive(false);
		leftDriveMotors.move(-100);
		rightDriveMotors.move(100);
		pros::delay(300);
		drive.setActive(true);

		drive.driveTiles(550);

		drive.setActive(false);
		leftDriveMotors.move(100);
		rightDriveMotors.move(-100);
		pros::delay(600);
		drive.setActive(true);

		drive.driveTiles(750, 2000);
		drive.driveTiles(-750);

		drive.setActive(false);
		leftDriveMotors.move(-100);
		rightDriveMotors.move(100);
		pros::delay(425);
		drive.setActive(true);

		pros::delay(500);
		drive.driveTiles(300);
		//catFire(catapultMotors, limitSwitch, shield);

		intake.brake();		*/

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


// MotPID::MotPID()
// {

// }

// double MotPID::getPositionPID()
// {
// 	double pos = test_mtr.get_position();
// 	pros::lcd::print(4, "get_position|calls: %d, pos: %f", calls, pos);
// 	calls++;
// 	return pos;
// }

// void MotPID::setVelocityPID(double value)
// {
// 	pros::lcd::print(5, "get_position velocity: %f", value);
// 	test_mtr.move_velocity(value);
// }


void opcontrol()
{
	bool catapultGoal = 1;
	bool catapultMid = 0;

	MinesMotorGroup leftDriveMotors(leftDriveVector);
	MinesMotorGroup rightDriveMotors(rightDriveVector);
	MinesMotorGroup catapultMotors(catapultVector);

	leftDriveMotors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	rightDriveMotors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	catapultMotors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	shield.set_value(1);
	pros::delay(500);

	while(true)
	{
		// ***** DRIVE *****
		// 2 stick arcade
		double leftAxisY = MasterController.get_analog(axisLeftY);
		double rightAxisX = MasterController.get_analog(axisRightX);
		double leftVelocity = ((leftAxisY + rightAxisX));
		double rightVelocity = ((leftAxisY - rightAxisX));

		// Tank
		// double leftAxisY = MasterController.get_analog(axisLeftY);
	    // double rightAxisY = MasterController.get_analog(axisRightY);
		// double leftVelocity = ((leftAxisY) * axisPercentBlue);
		// double rightVelocity = ((-rightAxisY) * axisPercentBlue);

		driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		// ***** END DRIVE *****



		// ***** INTAKE *****
		if(MasterController.get_digital_new_press(buttonR1))
		{
			toggleIntake();
		}

		intakeLoopToggle(MasterController.get_digital(buttonR2), true);
		//intakeLoopHold(MasterController.get_digital(R1), MasterController.get_digital(R2));
		// ***** END INTAKE *****



		// ***** CATAPULT *****
		if(MasterController.get_digital_new_press(buttonL2))
		{
			if(catapultGoal == 0)
			{
				shield.set_value(1);
				pros::delay(750);
				catapultGoal = 1;
			}

			else
			{
				shield.set_value(1);
				pros::delay(750);
				catapultGoal = 0;
			}
		}

		if(MasterController.get_digital_new_press(buttonX))
		{
				while(limitSwitch.get_value() != 1)
				{
					catapultLoop(catapultMotors, 100);
				}
				shield.set_value(0);
		}

		if(limitSwitchMid.get_value() != catapultGoal)
		{
			catapultLoop(catapultMotors, 100);
		}
		else
		{
			if(catapultGoal == 1)
			{
			    shield.set_value(0);
			}
			catapultMotors.brake();
		}
		// **** END CATAPULT *****

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			endgame.set_value(true);
		}
		else
		{
			endgame.set_value(false);
		}

		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			wall.set_value(true);
		}
		else
		{
			wall.set_value(false);
		}

		// ***** ROLLER *****
		rollerLoop(topRoller, topRollerFrontL, topRollerFrontR, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_B));
		// ***** END ROLLER *****





		// ***** TEST *****
		if (MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
		{
			swapRollerColor(Color::red, 70);
		}

		if (MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
		{
			swapRollerColor(Color::blue, 70);
		}
	}
}
