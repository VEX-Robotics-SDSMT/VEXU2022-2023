#include "../include/botFunctions.h"

bool intakeToggle = 0;

void toggleIntake()
{
    if(intakeToggle == 0)
    {
        intakeToggle = 1;
    }
    else
    {
        intakeToggle = 0;
    }
}

void intakeLoopToggle(bool rev, int pct)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity((100)*pct * INTAKE_MOTOR_GEARSET*-1);
    }
    else if(intakeToggle == 1)
    {
        intake.move_velocity((100)*pct * INTAKE_MOTOR_GEARSET);
    }
    else
    {
        intake.brake();
    }
}

void intakeLoopHold(bool run, bool rev, double pct)
{
    if(rev == 1)
    {
        intakeToggle = 0;
        intake.move_velocity(-(10000)*pct * INTAKE_MOTOR_GEARSET);
    }
    else if(run == 1)
    {
        intake.move_velocity((10000)*pct * INTAKE_MOTOR_GEARSET);
    }
    else
    {
        intake.brake();
    }
}

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity)
{
    leftMotorGroup.move(leftVelocity);
    rightMotorGroup.move(rightVelocity);
}

void catapultLoop(Mines::MinesMotorGroup catapultMotorGroup, int pct)
{
    catapultMotorGroup.moveVelocity(R_CATAPULT_MOTOR_GEARSET * (pct*0.01));
}

void fire(Mines::MinesMotorGroup catapultMotorGroup)
{
    catapultMotorGroup.tarePosition();
    while(catapultMotorGroup.getPosition() < 100)
    {
        catapultMotorGroup.moveVelocity(30);
    }
    catapultMotorGroup.brake();
}

void loadAndFire(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch)
{
    bool loaded = 0;

    if(limitSwitch.get_value() == 1)
    {
        while(limitSwitch.get_value() == 1)
        {
            catapultMotorGroup.moveVelocity(10);
        }
        loaded = 0;
    }
    else
    {
        while(limitSwitch.get_value() == 0)
        {
            catapultMotorGroup.moveVelocity(10);
        }
        catapultMotorGroup.brake();
        loaded = 1;
    }
    
}

void rollerLoop(pros::Motor roller, pros::Motor rollerFront, double velocity, bool run, bool rev)
{
    if(run)
    {
        roller.move_velocity(velocity);
        rollerFront.move_velocity(velocity);
    }
    else if(rev)
    {
        roller.move_velocity(velocity);
    }
    else
    {
        roller.brake();
        rollerFront.brake();
    }
}

void catInit(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch, pros::ADIDigitalOut shield)
{
    shield.set_value(1);
		pros::delay(200);
		while(!limitSwitch.get_new_press())
		{
			catapultMotorGroup.move(127);
		}
		catapultMotorGroup.brake();
		shield.set_value(0);
}

void catFire(Mines::MinesMotorGroup catapultMotorGroup, pros::ADIDigitalIn limitSwitch, pros::ADIDigitalOut shield)
{
    shield.set_value(1);
		 pros::delay(250);
		 while(limitSwitch.get_value() == 1)
		 {
		 	catapultMotorGroup.move(127);
		 }
		 pros::delay(200);
		 while(limitSwitch.get_value() == 0)
		 {
		 	catapultMotorGroup.move(127);
		 }
		catapultMotorGroup.brake();
		shield.set_value(0);
		pros::delay(200);
}



Color getColor(pros::c::optical_rgb_s_t color)
{
    if (fabs(color.blue - color.red) < 0.3)
    {
        return Color::purple;
    }
    else if (color.blue > color.red)
    {
        return Color::blue;
    }
    else
    {
        return Color::red;
    }
}

void swapRollerColor(Color targetColor, double voltage)
{
    opticalSensor.set_led_pwm(100);
    int loopCount = 0;
    int timeout = pros::millis() + ROLLER_TIMEOUT;

    pros::delay(5);

    while (loopCount < requiredColorLoops && timeout > pros::millis() )
    {
        pros::c::optical_rgb_s_t readColor = opticalSensor.get_rgb();
        colorLogger.Log(("Red: " + std::to_string(readColor.red) + 
            "  Green: " + std::to_string(readColor.green) + 
            "  Blue: " + std::to_string(readColor.blue)).c_str(), 7, LoggerSettings::verbose);

        Color colorEnum = getColor(readColor);
        

        if(colorEnum == targetColor || colorEnum == Color::purple)
        {
            loopCount = 0;
            topRollerFront.move(voltage);
            colorLogger.Log("Color target aquired", 8, LoggerSettings::verbose);
        }
        else
        {
            loopCount++;
            topRollerFront.brake();
            colorLogger.Log("Color searching", 8, LoggerSettings::verbose);
        }

        pros::delay(20);
    }

    topRollerFront.brake();
    
    opticalSensor.set_led_pwm(0);
}