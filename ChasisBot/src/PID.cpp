#include "PID.h"
#include "pros/rtos.hpp"

namespace Mines
{
    PID::PID(double (*positionFunction)())
    {
        position = positionFunction;
    }

    double PID::bindToMagnitude(double value)
    {
        if (value > MAX_POSITIVE_ACCELERATION)
        {
            return MAX_POSITIVE_ACCELERATION;
        }
        else if (value < MAX_NEGATIVE_ACCELERATION)
        {
            return MAX_NEGATIVE_ACCELERATION;
        }
        else
        {
            return value;
        }
    }

    void PID::update(double deltaT)
    {
        double currentPosition = position();
        double error = target - currentPosition;
        double positional = KP * error;
        double integral = KI * ( lastIntergral + (error * deltaT));
        double derivative = KD * ((error - lastError) / deltaT);
        double controlVariable = positional + integral + derivative;

        //setting loop variables
        lastError = error;
        lastIntergral = integral;

        //setting output variables
        acceleration = controlVariable - velocity;
        velocity = controlVariable;
    }

    void PID::updateTask()
    {
        std::uint32_t startTime = pros::millis();
        int deltaTime = 20;

        while(true)
        {
            update(deltaTime);
            pros::Task::delay_until(&startTime, deltaTime);
        }
    }

    void PID::StartTask(){
        pros::Task my_task([this] { 
            this->updateTask(); 
        } );
    }

    //----------------Getters/Setters-------------------
    void PID::resetTimers()
    {
        timeSinceTargetReached = 0;
        timeSinceTargetSet = 0;
    }

    void PID::SetPIDConst(double kp, double ki, double kd)
    {
        KP = kp;
        KI = ki;
        KD = kd;
    }

    void PID::SetMaxAcceleration(double maxPositive, double maxNegative)
    {
        MAX_NEGATIVE_ACCELERATION = maxNegative;
        MAX_POSITIVE_ACCELERATION = maxPositive;
    }

    void PID::SetMaxAcceleration(double maxAcceleration)
    {
        MAX_NEGATIVE_ACCELERATION = maxAcceleration;
        MAX_POSITIVE_ACCELERATION = maxAcceleration;
    }

    void PID::SetTolerance(double tolerance)
    {
        this->tolerance = tolerance;
    }

    void PID::SetTarget(double target)
    {
        resetTimers();
        this->target = target;
    }

    void PID::SetStopped(bool stopped)
    {
        this->stopped = stopped;
    }

    double PID::GetVelocity()
    {
        return velocity;
    }

    double PID::GetAcceleration()
    {
        return acceleration;
    }

    double PID::GetTimeSinceTargetReached()
    {
        return timeSinceTargetReached;
    }

    double PID::GetTimeSinceTargetSet()
    {
        return timeSinceTargetSet;
    }

    bool PID::GetStopped()
    {
        return stopped;
    }
}

