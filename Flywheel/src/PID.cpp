#include "PID.h"
#include "display/lv_misc/lv_task.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

using namespace std;

namespace Mines
{

    /** The constructor
    *
    * @param inputInterface The class that holds the input and output functions the PID uses to interact
    * with the outside world.
    * @param settings An enum that controls how much detail the logger prints to the screen.
    */
    PID::PID(PIDInterface *inputInterface, LoggerSettings settings) : logger(settings)
    {
        interface = inputInterface;
    }

    /** The main loop of the PID. Each time it's called it grabs data from the PIDInterface class,
     * runs the PID algorithm, and sets the result in PID::velocity and outputs it to PIDInterface.
    *
    * @param deltaT time(ms) since the last call
    */
    void PID::update(double deltaT)
    {
        double currentPosition = getPosition();
        logger.Log(("current position: " + std::to_string(currentPosition)).c_str(), 0, LoggerSettings::verbose);
        double error = target - currentPosition;
        logger.Log(("current error value: " + std::to_string(error)).c_str(), 1, LoggerSettings::verbose);

        double positional = KP * error;
        double integral = KI * ( lastIntergral + (error * deltaT));
        double derivative = KD * ((error - lastError) / deltaT);
        logger.Log(("positional: " + std::to_string(positional)).c_str(), 2, LoggerSettings::verbose);
        logger.Log(("integral: " + std::to_string(integral)).c_str(), 3, LoggerSettings::verbose);
        logger.Log(("derivative: " + std::to_string(derivative)).c_str(), 4, LoggerSettings::verbose);

        double controlVariable = positional + integral + derivative;
        logger.Log(("controlVariable: " + std::to_string(controlVariable)).c_str(), 6, LoggerSettings::verbose);


        //setting loop variables
        if (error != NAN)
        {
            logger.Log(("error: " + std::to_string(error)).c_str(), 8, LoggerSettings::verbose); 
            lastError = error;
        }
        else
        {
            logger.Log("ERROR: error is Nan", 8, LoggerSettings::error);
        }
        
        if (integral == NAN)
        {
            logger.Log("ERROR: integral is Nan", 9, LoggerSettings::error);
            lastIntergral = 0; 
        }

        //updating times
        timeSinceTargetSet += deltaT;
        if(fabs(target - currentPosition) < tolerance)
        {
            timeSinceTargetReached += deltaT;
        }

        //setting output variables
        setOutput(controlVariable);
    }

    /** Contains the update loop and runs it forever.
    *
    */
    void PID::updateTask()
    {
        std::uint32_t startTime = pros::millis();
        int deltaTime = 20;
        int count = 0;

        while(true)
        {
            count++;
            update(deltaTime);
            
            pros::Task::delay(deltaTime);
        }
    }

    /** Grabs the current position from the PIDInterface for internal use.
    */
    double PID::getPosition()
    {
        return interface->getPositionPID();
    }

    /** Outputs the recommended velocity value the PID finds
    */
    void PID::setOutput(double value)
    {
        velocity = value;
        interface->setVelocityPID(value);
    }

    /** The static "trampoline" function that exposes a call for multithreading
    */
    void PID::taskStarter(void* arg)
    {
        PID* pidPtr = static_cast<PID *>(arg);  
        pidPtr->updateTask();
    }

    /** Starts the mulitthreaded task
    */
    void PID::StartTask(){
        pros::Task my_task(taskStarter, this, "PID task");
    }

    //----------------Getters/Setters-------------------
    /** function to reset the timeout timers
    */
    void PID::resetTimers()
    {
        timeSinceTargetReached = 0;
        timeSinceTargetSet = 0;
    }

    /** Tunes the primary PID constants
    *
    * @param kp proportional - sets speed relative distance
    * from the target. Should do the majority of the heavy lifting.
    * @param ki integral - sets speed cumulatively based on kp. 
    * Used to deal with unexpected resitance.
    * @param kd derivative - sets speed based on inverse of last speed? 
    * Used to prevent overshoot.
    */
    void PID::SetPIDConst(double kp, double ki, double kd)
    {
        KP = kp;
        KI = ki;
        KD = kd;
    }

    /** Sets the acceptable margin of error before an operation is considered complete
    *
    * @param tolerance
    */
    void PID::SetTolerance(double tolerance)
    {
        this->tolerance = tolerance;
    }

    /** Sets the target position the PID is trying to reach
    *
    * @param target
    */
    void PID::SetTarget(double target)
    {
        resetTimers();
        this->target = target;
    }

    /** Sets whether the update loop outputs the results it finds
    *
    * @param stopped
    */
    void PID::SetStopped(bool stopped)
    {
        this->stopped = stopped;
    }

    /** Gets the recommended speed
    *
    */
    double PID::GetVelocity()
    {
        return velocity;
    }

    /** Gets how long the PID has been inside the tolerance window
    *
    */
    double PID::GetTimeSinceTargetReached()
    {
        return timeSinceTargetReached;
    }

    /** Gets how long it's been since a new target was set
    *
    */
    double PID::GetTimeSinceTargetSet()
    {
        return timeSinceTargetSet;
    }

    /** Gets whether the update loop is outputing
    */
    bool PID::GetStopped()
    {
        return stopped;
    }

    /** Gets the most recently set target
    */
    double PID::GetTarget()
    {
        return target;
    }
}

