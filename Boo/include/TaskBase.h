#ifndef TASK_BASE
#define TASK_BASE

#include "pros/rtos.hpp"
#include <iostream>

namespace Mines
{

class TaskBase
{
    private:
        bool paused = false;
        bool killed = false;
        uint32_t totalTime;
        pros::Task *taskPtr;

        static void taskTrampoline(void* arg);
        void updateTask();

    protected:
        virtual void update(double deltaT) = 0;
        int deltaTime = 20;

    public:
        TaskBase();
        void StartTask(std::string taskName);
        void KillTask();
        void SetTaskPaused(bool pause);
        bool GetTaskPaused();

};

}

#endif