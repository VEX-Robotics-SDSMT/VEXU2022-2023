#include "main.h"
#include "DiffDrive.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "globals.h"
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
	//pros::vision_signature_s_t RED_GOAL_SIG = vision.signature_from_utility(1, 4391, 7505, 5948, -1303, -147, -725, 1.6, 0);
	//vision.set_signature(RED_GOAL_SIG_ID, &RED_GOAL_SIG);
	//pros::vision_signature_s_t BLUE_GOAL_SIG = vision.signature_from_utility(2, -3073, -1323, -2198, 4405, 9923, 7164, 1.5, 0);
	//vision.set_signature(BLUE_GOAL_SIG_ID, &BLUE_GOAL_SIG);
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
	bool aggressive = true;


	//DiffDrive drive(leftDriveMotors, rightDriveMotors, intertialSensor);
	EncoderWheelSensorInterface encoderInterface(driveEncoder);
	DiffDrive drive(leftDriveMotors, rightDriveMotors, &encoderInterface, intertialSensor);
	drive.setDrivePIDVals(0.15, 0, 0);//0.2
	drive.setDrivePIDTol(25);
	drive.setTurnPIDVals(1.2, 0, 0);//1.2
	drive.setTurnPIDTol(1);
	drive.setMaxDriveSpeed(0.8); 
	drive.setMaxTurnSpeed(0.7);

	drive.setMaxDriveAccel(0.6);

	ScreenLogger logger(LoggerSettings::verbose);
	//AimAssist aimAssist(vision, RED_GOAL_SIG_ID, &drive, shootDisk);
	//aimAssist.StartTask();
	//aimAssist.turnSpeed = 0.25;
	//aimAssist.leftOffset = 170;
	//aimAssist.turnTol = 0.2;

	//aimAssist.AimFire(10000);
	//drive.driveTiles(-500);


	if (!aggressive)
	{
		//------Passive------
		//grab center disc
		/*compress.set_value(true);
		intakeGroup.move(-127);
		drive.driveTiles(150);
		pros::delay(500);
		drive.driveTiles(-200);
		intakeGroup.brake();

		//turn roller
		flywheelsGroup.move(87);
		drive.turnDegreesAbsolute(45);
		backRoller.move(127);
		drive.driveTiles(-350, 700);
		backRoller.brake();
		drive.driveTiles(250);

		//make first shot approach
		drive.turnDegreesAbsolute(125);
		drive.driveTiles(1700);
		drive.turnDegreesAbsolute(220);
		drive.driveTiles(-1250);

		//fire first stack
		drive.turnDegreesAbsolute(-166);
		shootDisk();
		pros::delay(2500);
		shootDisk();
		pros::delay(2500);
		shootDisk();

		//pick up second stack
		drive.setMaxDriveSpeed(0.4);
		drive.turnDegreesAbsolute(-100);
		intakeGroup.move(-127);
		intake.set_value(true);
		drive.driveTiles(1000, false);
		pros::delay(800);
		intake.set_value(false);
		pros::delay(3000);
		drive.setMaxDriveSpeed(0.8);

		//fire second stack
		flywheelsGroup.move(87);
		drive.driveTiles(-1000);
		drive.turnDegreesAbsolute(-170);
		shootDisk();
		pros::delay(2500);
		shootDisk();
		pros::delay(2500);
		shootDisk();*/
	}
	else
	{
		//Aggressive
		flywheelsGroup.move(94);
		compress.set_value(true);
		intake.set_value(true);
		intakeGroup.move(-127);

		drive.driveTiles(350);
		intake.set_value(false);
		pros::delay(2000);
		drive.driveTiles(-145);

		//turn and fire
		drive.turnDegreesAbsolute(-165);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		flywheelsGroup.move(94);

		//grab preloads and turn roller
		//drive.turnDegreesAbsolute(-165);
		intake.set_value(true);
		drive.driveTiles(375, 5000);
		intake.set_value(false);
		pros::delay(500);

		drive.driveTiles(400, 1500);
		frontRoller.move(-100);
		pros::delay(250);
		frontRoller.brake();

		drive.driveTiles(-275, 5000);
		drive.turnDegreesAbsolute(-40);
		drive.driveTiles(275, 5000);
		drive.driveTiles(-170);

		//shoot the second stack
		drive.turnDegreesAbsolute(-163);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		flywheelsGroup.move(91);

		//pick up the third stack
		drive.turnDegreesAbsolute(75);
		intake.set_value(true);	
		drive.driveTiles(920);
		intake.set_value(false);
		pros::delay(3000);

		//shoot last stack
		drive.turnDegreesAbsolute(-176);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();
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
	// Initialize the flywheel speed to 100% and brake type to coast
	int flywheelPct = 65;
	flywheelsGroup.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	bool lastVal = false;

	while(true)
	{	
		// ********************DRIVE********************
		// 2 stick arcade
		double leftAxisY = MasterController.get_analog(axisLeftY);
		double rightAxisX = MasterController.get_analog(axisRightX);
		double leftVelocity = leftAxisY + rightAxisX;
		double rightVelocity = leftAxisY - rightAxisX;

		// 1 stick arcade
		//double leftAxisY = MasterController.get_analog(axisLeftY);
		//double leftAxisX = MasterController.get_analog(axisLeftX);
		//double rightAxisX = MasterController.get_analog(axisRightX);
		//double aimVelocityLeft = (rightAxisX) * 0.06;
		//double aimVelocityRight = -rightAxisX * 0.06;
		//double leftVelocity = ((leftAxisY + leftAxisX + aimVelocityLeft));
		//double rightVelocity = ((leftAxisY - leftAxisX + aimVelocityRight));

		// Tank
		// double leftAxisY = MasterController.get_analog(axisLeftY);
	    // double rightAxisY = MasterController.get_analog(axisRightY);
		// double leftVelocity = ((leftAxisY) * axisPercentBlue);
		// double rightVelocity = ((-rightAxisY) * axisPercentBlue);

		// If the driver is holding B, drive at 30% speed to aim easier, otherwise drive using the values found anbove
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			driveLoop(leftDriveMotors, rightDriveMotors, .3*leftVelocity, .3*rightVelocity);
		}
		else
		{
			driveLoop(leftDriveMotors, rightDriveMotors, leftVelocity, rightVelocity);
		}
		//*********************************************



		// ********************FLYWHEELS********************
		// Flywheel toggle control
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
		{
			toggleFlywheels();
		}

		// Flywheel speed control
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
		{
			flywheelPct = 75;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			flywheelPct = 65;
		}

		flywheelLoopToggle(flywheelsGroup, flywheelPct);
		// *************************************************


		
		// ********************ROLLER********************
		//rollerLoop(topRoller, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X));
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			backRoller.move(100);
			pros::delay(100);
			backRoller.brake();
			frontRoller.move(-100);
			pros::delay(100);
			frontRoller.brake();
		}
		// **********************************************



		// ********************INTAKE********************
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{
			toggleIntake();
		}
		intakeLoopHold(intakeGroup, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
		// **********************************************



		//********************ENDGAME********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			endgame.set_value(true);
		else
			endgame.set_value(false);
		//***********************************************



		// ********************SHOOT********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			shoot1.set_value(true);
		}
		else if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			shoot3.set_value(true);
		}
		else
		{
			shoot1.set_value(false);
			shoot3.set_value(false);			
		}
		// *********************************************

		// ********************COMPRESS*****************
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
		{
			toggleCompress();
		}

		compressLoopToggle(compress);
	}
}
