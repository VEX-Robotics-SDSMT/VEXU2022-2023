#include "main.h"
#include "DiffDrive.h"
#include "botFunctions.h"
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
	//DiffDrive drive(leftDriveMotors, rightDriveMotors, intertialSensor);
	EncoderWheelSensorInterface encoderInterface(driveEncoder);
	DiffDrive drive(leftDriveMotors, rightDriveMotors, &encoderInterface, intertialSensor);
	drive.setDrivePIDVals(0.2, 0, 0);//0.2
	drive.setDrivePIDTol(50);
	drive.setTurnPIDVals(1.2, 0, 0);//1.2
	drive.setTurnPIDTol(2);
	drive.setMaxDriveSpeed(1); 
	drive.setMaxTurnSpeed(0.7);

	drive.setMaxDriveAccel(0.12);

	//ScreenLogger logger(LoggerSettings::verbose);
	//AimAssist aimAssist(vision, RED_GOAL_SIG_ID, &drive, shootDisk);
	//aimAssist.StartTask();
	//aimAssist.turnSpeed = 0.25;
	//aimAssist.leftOffset = 170;
	//aimAssist.turnTol = 0.2;

	//aimAssist.AimFire(10000);
	//drive.driveTiles(-500);


	if(skills) // Skills route
	{

		//Boo's Aggressive Route
		//start in same spot at angle
		//preloads of to the side

		//lift intake and drive forward to pick up three stack
		flywheelsGroup.move(87);
		rake.set_value(true);
		intake1.move(-114);
		intake2.move(-114);
		drive.driveTiles(-850);
		rake.set_value(false);
		drive.driveTiles(-50);
		pros::delay(1800);

		//back up and shoot 3
		drive.driveTiles(400);
		compress.set_value(true);
		pros::delay(200);
		compress.set_value(false);
		pros::delay(200);
		drive.turnDegreesAbsolute(136.5);

		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(200);

		flywheelsGroup.move(83);
		drive.turnDegreesAbsolute(-90);
		drive.setMaxDriveSpeed(0.75);
		drive.driveTiles(-2250);




		//turn and shoot
		compress.set_value(true);
		drive.turnDegreesAbsolute(168);
		compress.set_value(false);

		pros::delay(1600);
		shootDisk();
		pros::delay(2500);
		shootDisk();
		pros::delay(2500);
		shootDisk();

		//back to get roller
		flywheelsGroup.move(93);
		drive.turnDegreesAbsolute(89.75);
		drive.driveTiles(-3050,5000);
		drive.turnDegreesAbsolute(137);
		drive.driveTiles(-550, 1000);
		pros::delay(200);
		drive.driveTiles(-75, false);
		topRoller.move(-127);
		pros::delay(185);
		topRoller.brake();

		drive.driveTiles(250);
		drive.turnDegreesAbsolute(-133);
		rake.set_value(true);
		drive.driveTiles(-1150);
		rake.set_value(false);
		pros::delay(1500);
		drive.turnDegreesAbsolute(141.5);
		compress.set_value(true);
		pros::delay(250);
		compress.set_value(false);
		pros::delay(250);
		//pros::delay(1500);
		shootDisk();
		pros::delay(1500);
		shootDisk();

		//spin and do a little dance
		//or not
		flywheelsGroup.brake();
		intake1.brake();
		intake2.brake();

		drive.killPIDs();

		
		
	}
	else // Match auton route
	{
		//Boo's passive route
		//start in line with middle disk
		drive.setMaxDriveSpeed(0.5); 
		drive.setMaxTurnSpeed(0.5);
		drive.setMaxDriveAccel(0.15);
		
		//drive forward to grab one
		intake1.move(-100);
		intake2.move(-100);
		drive.driveTiles(-800);

		//turn and shoot 3
		flywheelsGroup.move(87); //87
		drive.turnDegreesAbsolute(190);
		compress.set_value(true);
		pros::delay(100);
		compress.set_value(false);

		pros::delay(1800);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(200);

		//pull forward to grab one on line
		drive.turnDegreesAbsolute(43);
		drive.driveTiles(-350);
		pros::delay(200);
		drive.driveTiles(500);

		//drive to line to pick other 2
		drive.turnDegreesAbsolute(-45);
		drive.driveTiles(-1500);
		drive.driveTiles(1000);

		//turn and shoot
		flywheelsGroup.move(86);
		compress.set_value(true);
		drive.turnDegreesAbsolute(195);
		compress.set_value(false);

		pros::delay(1500);
		shootDisk();
		pros::delay(2000);
		shootDisk();
		pros::delay(2000);
		shootDisk();

		//back to get roller
		drive.turnDegreesAbsolute(125);
		drive.driveTiles(-1500);
		drive.turnDegreesAbsolute(180);
		drive.driveTiles(-350, 1000);
		pros::delay(200);
		drive.driveTiles(-100, false);
		topRoller.move(-127);
		pros::delay(170);
		topRoller.brake();

		drive.driveTiles(500);
		//spin and do a little dance
		//or not
		flywheelsGroup.brake();
		intake1.brake();
		intake2.brake();

		drive.killPIDs();
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
	int flywheelPct = 62; //60
	flywheelsGroup.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	ScreenLogger logger(LoggerSettings::verbose);

	while(true)
	{	
		// ********************DRIVE********************
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
			flywheelPct = 70;
		}
		if(MasterController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			flywheelPct = 62;
		}

		flywheelLoopToggle(flywheelsGroup, flywheelPct);
		// *************************************************


		
		// ********************ROLLER********************
		//rollerLoop(topRoller, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X));
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			//swapRollerColor(Color::blue, 80);
			
			topRoller.move(100);
			pros::delay(100);
			topRoller.brake();
			
		}
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			//swapRollerColor(Color::red, 80);
			
			topRoller.move(-100);
			pros::delay(100);
			topRoller.brake();
			
		}
		// **********************************************



		// ********************INTAKE********************
		intakeLoopHold(intakeGroup, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
		// **********************************************



		// ********************ENDGAME********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			endgame.set_value(true);
		else
			endgame.set_value(false);
		// ***********************************************



		// ********************SHOOT********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_A))
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

		logger.Log(std::to_string(flywheelsGroup.getActualVelocity()), 3, LoggerSettings::verbose);
		compressLoopToggle(compress);
		pros::delay(10);
	}
}
