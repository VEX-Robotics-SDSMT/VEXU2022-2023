#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include <string>
#include <iostream>

namespace Mines
{
    class PIDInterface
    {
        public:
            virtual double getPositionPID() = 0;
            virtual void setVelocityPID(double value) = 0;
    };


    class PID
    {        
        //Constants - technically changable, but if so, no often
        double KP = 0.005;
        double KI = 0;
        double KD = 0.0001;

        //Setpoints - goal variables of the algorithm
        double target = 0;
        double tolerance = 0.05;
        bool stopped = false;

        //Transients - change programatically every loop
        double lastError;
        double lastIntergral;
        
        //Output variables - the values kept track out for output only
        double timeSinceTargetReached;
        double timeSinceTargetSet;
        double velocity;

        //function pointer to the position function
        double (*position)();
        PIDInterface *interface;
        bool hasInterface;

        private:
            void resetTimers();
            void update(double deltaT);
            void updateTask();
            double getPosition();
            void setOutput(double value);

        public:
            PID(double (*positionFunction)());
            PID(PIDInterface *inputInterface);

            void StartTask();
            void SetPIDConst(double kp, double ki, double kd);
            void SetTolerance(double tolerance);
            void SetTarget(double target);
            void SetStopped(bool stopped);

            double GetVelocity();
            double GetTimeSinceTargetReached();
            double GetTimeSinceTargetSet();
            bool GetStopped();
    };
}

#endif