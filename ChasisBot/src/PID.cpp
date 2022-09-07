#include "PID.h"

namespace Mines
{
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

    void PID::update(double deltaT, double currentPosition)
    {
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

    //----------------Getters/Setters-------------------
    void PID::resetTimers()
    {
        timeSinceTargetReached = 0;
        timeSinceTargetSet = 0;
    }

    void PID::setPIDConst(double kp, double ki, double kd)
    {
        KP = kp;
        KI = ki;
        KD = kd;
    }

    void PID::setMaxAcceleration(double maxPositive, double maxNegative)
    {
        MAX_NEGATIVE_ACCELERATION = maxNegative;
        MAX_POSITIVE_ACCELERATION = maxPositive;
    }

    void PID::setMaxAcceleration(double maxAcceleration)
    {
        MAX_NEGATIVE_ACCELERATION = maxAcceleration;
        MAX_POSITIVE_ACCELERATION = maxAcceleration;
    }

    void PID::setTolerance(double tolerance)
    {
        this->tolerance = tolerance;
    }

    void PID::setTarget(double target)
    {
        resetTimers();
        this->target = target;
    }

    void PID::setStopped(bool stopped)
    {
        this->stopped = stopped;
    }

    double PID::getVelocity()
    {
        return velocity;
    }

    double PID::getAcceleration()
    {
        return acceleration;
    }

    double PID::getTimeSinceTargetReached()
    {
        return timeSinceTargetReached;
    }

    double PID::getTimeSinceTargetSet()
    {
        return timeSinceTargetSet;
    }

    bool PID::getStopped()
    {
        return stopped;
    }
}

