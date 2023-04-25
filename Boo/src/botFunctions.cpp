#include "../include/botFunctions.h"

bool intakeToggle = 0;
bool flywheelToggle = 0;
bool compressToggle = 0;

void toggleIntake()
{
    if(intakeToggle == 0)
        intakeToggle = 1;
    else
        intakeToggle = 0;
}

void toggleFlywheels()
{
    if(flywheelToggle == 0)
        flywheelToggle = 1;
    else
        flywheelToggle = 0;
}

void toggleCompress()
{
    if(compressToggle == 0)
        compressToggle = 1;
    else
        compressToggle = 0;
}

void driveLoop(Mines::MinesMotorGroup leftMotorGroup, Mines::MinesMotorGroup rightMotorGroup, double leftVelocity, double rightVelocity)
{
    leftMotorGroup.move(leftVelocity);
    rightMotorGroup.move(rightVelocity);
}

void rollerLoop(pros::Motor roller, int pct, bool run)
{
    if(run)
        roller.move_velocity(ROLLER_MOTOR_GEARSET*(pct/100));
    else
        roller.brake();
}

void intakeLoopHold(Mines::MinesMotorGroup intakeMotors, int pct, bool run, bool rev)
{
    if(rev == 1)
        intakeMotors.moveVelocity(-(100)*pct * INTAKE_MOTOR_GEARSET);
    else if(run == 1)
        intakeMotors.moveVelocity((100)*pct * INTAKE_MOTOR_GEARSET);
    else
        intakeMotors.brake();
}

void flywheelLoopToggle(Mines::MinesMotorGroup flywheels, int pct)
{
    if(flywheelToggle == 1)
    {
        flywheels.move(((0.01)* (pct) * 127));
       // std::cout << "FLYWHEEL MOVE" << std::endl;
    }

    else
    {
        flywheels.brake();
        //std::cout << "FLYWHEEL BREAK" << std::endl;
    }
}

void compressLoopToggle(pros::ADIDigitalOut compress)
{
    if(compressToggle == 1)
        compress.set_value(true);
    else
        compress.set_value(false);
}

void shootDisk()
{
    shoot1.set_value(1);
    pros::delay(250);
    shoot1.set_value(0);
}

void shoot3Disk()
{
    shoot3.set_value(1);
    pros::delay(250);
    shoot3.set_value(0);
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
    double rollerSpeed;

    //check if currently purple
    while (getColor(opticalSensor.get_rgb()) == Color::purple && timeout > pros::millis() )
    {
        topRoller.move(voltage);
        std::cout << "Started purple, checking" << std::endl;
    }

    //roll until purple
    while (loopCount < requiredColorLoops && timeout > pros::millis() )
    {
        Color foundColor = getColor(opticalSensor.get_rgb());

        if(foundColor != Color::purple)
        {
            //reset the filter, move the roller and log
            loopCount = 0;
            if (getColor(opticalSensor.get_rgb()) == targetColor)
            {
                topRoller.move(-voltage);
                std::cout << "found target" << std::endl;
            }
            else
            {
                topRoller.move(voltage);
                std::cout << "found non-target" << std::endl;
            }
        }
        else
        {
            //if we see the right color, stop moving the roller and start filtering
            loopCount++;
            topRoller.brake();
            std::cout << "Found Purple" << std::endl;
        }

        std::cout << pros::millis() << std::endl;
        pros::delay(10);
    }

    //stop the roller and turn off the light
    topRoller.brake();
    opticalSensor.set_led_pwm(0);
}

