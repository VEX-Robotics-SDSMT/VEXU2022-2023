#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include <string>
#include <iostream>

namespace Mines
{

    class PID
    {        
        //Constants - technically changable, but if so, no often
        double KP = 0.005;
        double KI = 0;
        double KD = 0.0001;
        double MAX_NEGATIVE_ACCELERATION = 1;
        double MAX_POSITIVE_ACCELERATION = 1;

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
        double acceleration;

        //function pointer to the position function
        double (*position)();

        private:
            double bindToMagnitude(double value);
            void resetTimers();
            void update(double deltaT);
            void updateTask();

        public:
            PID(double (*positionFunction)());

            void StartTask();
            void SetPIDConst(double kp, double ki, double kd);
            void SetMaxAcceleration(double maxPositive, double maxNegative);
            void SetMaxAcceleration(double maxAcceleration);
            void SetTolerance(double tolerance);
            void SetTarget(double target);
            void SetStopped(bool stopped);


            double GetVelocity();
            double GetAcceleration();
            double GetTimeSinceTargetReached();
            double GetTimeSinceTargetSet();
            bool GetStopped();
    };
}




#endif