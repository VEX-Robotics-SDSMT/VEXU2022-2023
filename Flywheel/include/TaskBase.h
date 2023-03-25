#ifndef TASK_BASE
#define TASK_BASE

#include "pros/rtos.hpp"

namespace Mines
{

class TaskBase
{
    private:
        bool paused = false;
        bool killed = false;
        uint32_t totalTime;
        int deltaTime = 20;
        pros::Task *taskPtr;

        static void taskTrampoline(void* arg);
        void updateTask();

    protected:
        virtual void update() = 0;

    public:
        TaskBase();
        void StartTask();
        void KillTask();
        void SetTaskPaused(bool pause);

};

}

#endif