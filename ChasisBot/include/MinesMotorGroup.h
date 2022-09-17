#ifndef MINES_MOTOR_GROUP
#define MINES_MOTOR_GROUP

#include <vector>
#include "api.h"
#include "pros/motors.hpp"

namespace Mines {


class MinesMotorGroup
{
    const int NOT_INITIALIZED_CODE = -2;

    //variables
    std::vector<pros::Motor> motorVector;
    bool initialized = false;
    int size;

    //public functions
    public:
    void Initialize(std::vector<pros::Motor> &motors);
    void Initialize(pros::Motor motors[], int numMotors);

    int move(const int voltage);

    //private functions
    private:

};

}

#endif
