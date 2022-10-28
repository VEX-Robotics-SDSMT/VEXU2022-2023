#include "main.h"

//globals

pros::Motor test_mtr(20);
int calls = 0;




/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

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


MotPID::MotPID()
{

}

double MotPID::getPositionPID()
{
	double pos = test_mtr.get_position();
	pros::lcd::print(4, "get_position|calls: %d, pos: %f", calls, pos);
	calls++;
	return pos;
}

void MotPID::setVelocityPID(double value)
{
	pros::lcd::print(5, "get_position velocity: %f", value);
	test_mtr.move_velocity(value);
}


void opcontrol() {	
	// pros::Controller master(pros::E_CONTROLLER_MASTER);
	// test_mtr.tare_position();
	// MotPID in;
	// Mines::PID pid(&in);
	// pid.SetPIDConst(0.1, 0.001, 0);
	// pid.StartTask();

	// int loopCount = 0;

	// pid.SetTarget(5000);

	// while(loopCount < 20)
	// {
	// 	pros::lcd::print(6, "main loop: %d", loopCount);
	// 	loopCount++;
	// 	pros::c::delay(100);
	// }

	// pid.SetTarget(-120);
	

	//DO NOT REMOVE: Main should not exit while there are subtasks going on - it will crash the robot
	while(true)
	{
		pros::c::delay(1000);
	}
}
