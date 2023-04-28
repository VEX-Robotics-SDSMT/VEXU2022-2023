#include "../include/TaskBase.h"

using namespace Mines;

TaskBase::TaskBase()
{
    totalTime = pros::millis();
}

void TaskBase::taskTrampoline(void* arg)
{
    TaskBase* taskBasePtr = static_cast<TaskBase *>(arg);  
    taskBasePtr->updateTask();
}

void TaskBase::StartTask(std::string taskName){
    pros::Task my_task(taskTrampoline, this, taskName.c_str());
    taskPtr = &my_task;
}

void TaskBase::updateTask()
{
    while(!killed)
    {
        if(!paused)
        {
            update(deltaTime);
        } 
        pros::Task::delay_until(&totalTime, deltaTime);
    }

    taskPtr->join();
}

void TaskBase::KillTask()
{
    killed = true;
}

void TaskBase::SetTaskPaused(bool pause)
{
    paused = pause;
}

bool TaskBase::GetTaskPaused()
{
    return paused;
}



