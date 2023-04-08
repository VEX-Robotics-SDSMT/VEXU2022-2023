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
	pros::vision_signature_s_t RED_GOAL_SIG = vision.signature_from_utility(1, 4391, 7505, 5948, -1303, -147, -725, 1.6, 0);
	vision.set_signature(RED_GOAL_SIG_ID, &RED_GOAL_SIG);
	pros::vision_signature_s_t BLUE_GOAL_SIG = vision.signature_from_utility(2, -3073, -1323, -2198, 4405, 9923, 7164, 1.5, 0);
	vision.set_signature(BLUE_GOAL_SIG_ID, &BLUE_GOAL_SIG);
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
	drive.setDrivePIDVals(0.2, 0, 0);//0.2
	drive.setDrivePIDTol(5);
	drive.setTurnPIDVals(1.2, 0, 0);//1.2
	drive.setTurnPIDTol(1);
	drive.setMaxDriveSpeed(1); 
	drive.setMaxTurnSpeed(0.7);

	drive.setMaxDriveAccel(0.12);

	ScreenLogger logger(LoggerSettings::verbose);
	AimAssist aimAssist(vision, RED_GOAL_SIG_ID, drive, shootDisk);
	aimAssist.StartTask();

	while(true)
	{
		Mines::Target target = aimAssist.GetTarget();
		logger.Log("rotation: " + std::to_string(target.rotation), 0, LoggerSettings::verbose);
		logger.Log("distance: " + std::to_string(target.distance), 1, LoggerSettings::verbose);
		logger.Log("certainty: " + std::to_string(target.certainty), 2, LoggerSettings::verbose);
		std::cout << "box: " << target.rotation << " " << target.distance << " " << target.certainty << std::endl;
		//std::cout << strerror(errno) << std::endl;
		pros::delay(500);
	}

	if(skills) // Skills route
	{
		// Start spinning up the flywheel and drive into the roller
		flywheelsGroup.move(84);  //82, 90
		drive.driveTiles(-100,false);
		topRoller.set_zero_position(0);
	
		pros::delay(600);
 	
		// Move the roller
		topRoller.move_absolute(-750,127); //move roller
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		// Drive forward to avoid hitting the wall, then turn towards the high goal
		drive.driveTiles(300, true); //turn and shoot two preloads
		drive.turnDegreesAbsolute(72); //72
		pros::delay(500);

		//Fire preloads
        shootDisk();
		pros::delay(1100);
        shootDisk();
		pros::delay(300);

		// Slow down flywheels for next shot and move forward picking up the stack of 3 discs, then turn towards the goal
		flywheelsGroup.move(76);   //82, 60		
		drive.turnDegreesAbsolute(-130); //pick up three
		intake1.move(-118);
		intake2.move(-118);
		drive.setMaxDriveSpeed(0.20);
		drive.driveTiles(-2800);
		pros::delay(100);
		drive.turnDegreesAbsolute(102); //turn and shoot, 113

		//Fire first stack
		pros::delay(500);
        shootDisk();
		pros::delay(1100);
        shootDisk();
		pros::delay(1100);
        shootDisk();
		pros::delay(500);

		// Turn and pick up the single disc (first disc in line of 3)
		drive.setMaxDriveSpeed(0.40);
		drive.turnDegreesAbsolute(-140);
		intake1.move(-118);
		intake2.move(-118);
		drive.driveTiles(-1375);

		//fire single disc
		flywheelsGroup.move(71);  // 80, 30
		drive.turnDegreesAbsolute(127); //pick up one 128
		pros::delay(700); //500
        shootDisk();
		pros::delay(300); //shoot one


		//turn towards line of 3 on the low goal
		drive.turnDegreesAbsolute(0);
		
		//Slow down and drive towards the line of 3, intaking them
		drive.setMaxDriveSpeed(0.25);
		drive.driveTiles(-2300);
		
		//Speed up the flywheels and turn towards the goal
		flywheelsGroup.move(74);  //75, 30
		drive.setMaxDriveSpeed(0.5);

		drive.turnDegreesAbsolute(76);
		//drive.driveTiles(-250);
		
		//Fire line of discs
        shootDisk();
		pros::delay(800);
        shootDisk();
		pros::delay(1100);
        shootDisk();
		pros::delay(500);
		flywheelsGroup.move(89);//105


		// Back up and turn towards a position that is in line with the 2nd stack of 3 discs and the 2nd roller, then drive to that point
		drive.driveTiles(-250);
		drive.turnDegreesAbsolute(-42);
		drive.setMaxDriveSpeed(0.75);
		drive.driveTiles(950);

		// Drive forward, picking up discs and then driving into the roller and scoring it
		drive.turnDegreesAbsolute(90);
		drive.setMaxDriveSpeed(0.20);
		drive.driveTiles(-3000);
		drive.setMaxDriveSpeed(0.5);
		drive.driveTiles(-600, false);

		topRoller.set_zero_position(0);
	
		pros::delay(600);

 	
		topRoller.move_absolute(-950,127); 
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();


		//Turn towards the goal and shoot the 2nd stack of 3 discs
		drive.driveTiles(800);
		drive.turnDegreesAbsolute(84);

        shootDisk();
		pros::delay(1000);
        shootDisk();
		pros::delay(1200);
        shootDisk();
		pros::delay(300);

		// Fire endgame, then turn so that each wheel is touching its own tile
		drive.driveTiles(800);
		drive.turnDegreesAbsolute(45, 1000);
		drive.driveTiles(-1200);
		endgame.set_value(true);
		drive.turnDegreesAbsolute(0);
	}
	else // Match auton route
	{
		//Boo's passive route
		//start on edge of tile with flywheel facing our goal
		drive.setMaxDriveSpeed(0.55); 
		drive.setMaxTurnSpeed(0.5);
		drive.setMaxDriveAccel(0.1);
		//drive toward roller and prep flywheels
		drive.driveTiles(-1200);
		flywheelsGroup.move(85);
		pros::delay(700);

		//turn, backup and spin roller
		drive.turnDegreesAbsolute(90);
		pros::delay(700);
		drive.driveTiles(-500);
		pros::delay(700);
		drive.driveTiles(-150, false);
		topRoller.move(127);
		pros::delay(300);
		topRoller.brake();

		//move forward, turn and shoot preloads
		drive.driveTiles(300);
		drive.turnDegreesAbsolute(85);
		
        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(300);

		//drive and pick up three in a line
		drive.setMaxDriveSpeed(0.3);
		drive.setMaxDriveAccel(0.05);
		intake1.move(-127);
		intake2.move(-127);
		drive.turnDegreesAbsolute(-138);
		drive.driveTiles(-3575);
		pros::delay(500);

		//backup, turn and shoot 3
		drive.driveTiles(100);
		drive.turnDegreesAbsolute(119);
		flywheelsGroup.move(82);
		
        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(300);

		//backup to line of three
		drive.turnDegreesAbsolute(-90);
		pros::delay(700);
		drive.driveTiles(2375);
		pros::delay(700);

		//turn along edge and pick up three
		drive.turnDegreesAbsolute(-120);
		drive.driveTiles(-900);
		pros::delay(500);
		drive.turnDegreesAbsolute(-90);
		drive.driveTiles(-1700);
		pros::delay(500);

		//turn and shoot 3
		drive.turnDegreesAbsolute(125);
		flywheelsGroup.move(90);
        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(300);
		
		flywheelsGroup.brake();
		intake1.brake();
		intake2.brake();
//*/





		//*****************************************************************/
		/* //previous auton route, could use for Mike
		// Start spinning up flywheels and get the first roller
		drive.driveTiles(-100,false);
		topRoller.set_zero_position(0);
	
		pros::delay(600);
 	
		topRoller.move_absolute(-250,127); 
		pros::delay(100);
		leftDriveMotors.brake();
		rightDriveMotors.brake();

		flywheelsGroup.move(96);  

		// Shoot preloads
		drive.driveTiles(300, true); 
		drive.turnDegreesAbsolute(-15, false);
		pros::delay(2000);

        shootDisk();
		pros::delay(1800);
        shootDisk();
		pros::delay(300);

		// Turn towards first stack of 3, then move forward and intake them
		drive.turnDegreesAbsolute(-130.5); 
		intake1.move(-127);
		intake2.move(-127);
		drive.setMaxDriveSpeed(0.15);
		drive.driveTiles(-2800);
		flywheelsGroup.move(91);
		pros::delay(100);

		// Turn towards goal, shoot first stack of 3
		drive.turnDegreesAbsolute(-42.5); 

		pros::delay(1000);

        shootDisk();
		pros::delay(1900);
        shootDisk();
		pros::delay(2100);
        shootDisk();
		pros::delay(500);

		// Turn towards single disc (First disc in line of 3) and intake it
		drive.turnDegreesAbsolute(-143);
		intake1.move(-127);
		intake2.move(-127);
		drive.driveTiles(-1100);

		// Shoot the single disc
		flywheelsGroup.move(88);  
		drive.turnDegreesAbsolute(-55.5); 
		pros::delay(700); 
        shootDisk();
		pros::delay(700);
		pros::delay(300); 
		
		// Turn towards line of 3 discs on the low goal
		drive.driveTiles(-180); //180
		drive.turnDegreesAbsolute(0);
		
		// Slow down and intake the 3 discs on the low goal
		drive.setMaxDriveSpeed(0.25);
		drive.driveTiles(-2300);
		
		// Speed up the flywheels and turn towards the high goal
		flywheelsGroup.move(105);  //103
		drive.setMaxDriveSpeed(0.5);
		drive.turnDegreesAbsolute(-43);
		
		// Shoot the 3 discs that were on the low goal
        shootDisk();
		pros::delay(1600);
        shootDisk();
		pros::delay(1600);
        shootDisk();
		pros::delay(500);
		//*/
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
	int flywheelPct = 100;
	flywheelsGroup.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

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

		flywheelLoopToggle(flywheelsGroup, flywheelPct);
		// *************************************************


		
		// ********************ROLLER********************
		rollerLoop(topRoller, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
		// **********************************************



		// ********************INTAKE********************
		intakeLoopHold(intakeGroup, 100, MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1), MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
		// **********************************************



		// ********************ENDGAME********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
			endgame.set_value(true);
		else
			endgame.set_value(false);
		// ***********************************************



		// ********************SHOOT********************
		if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			shoot1.set_value(true);
		}
		else if(MasterController.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			shoot1.set_value(true);
			shoot3.set_value(true);
		}
		else
		{
			shoot1.set_value(false);
			shoot3.set_value(false);			
		}
		// *********************************************
	}
}
