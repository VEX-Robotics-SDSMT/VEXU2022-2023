#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include <string>
#include <iostream>
#include "api.h"
#include <math.h>
#include "Logger.h"
#include "TaskBase.h"

namespace Mines
{
    class PIDInterface
    {
        public:
            virtual double getPositionPID() = 0;
            virtual void setVelocityPID(double value) = 0;
    };


    class PID : public TaskBase
    {        
        //Logger
        ScreenLogger logger;

        //Constants - technically changable, but if so, no often
        double KP = 0.005;
        double KI = 0;
        double KD = 0.0001;

        //Setpoints - goal variables of the algorithm
        double target = 0;
        double tolerance = 0.05;

        //Transients - change programatically every loop
        double lastError = 0;
        double lastIntergral = 0;
        
        //Output variables - the values kept track out for output only
        double timeSinceTargetReached;
        double timeSinceTargetSet;
        double velocity;

        private:
            void resetTimers();
            void update(double deltaT);
            double getPosition();
            void setOutput(double value);

        public:
            PIDInterface *interface;

            PID(double (*positionFunction)());
            PID(PIDInterface *inputInterface, LoggerSettings settings);
            
            void SetPIDConst(double kp, double ki, double kd);
            void SetTolerance(double tolerance);
            void SetTarget(double target);

            double GetVelocity();
            double GetTimeSinceTargetReached();
            double GetTimeSinceTargetSet();
            double GetTarget();
    };
}

#endif