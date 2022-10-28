#include "./../include/main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
void initVariables(int& side)
{
    master.clear();
    master.print(1, 1, "Y: Blue, A: Red");
    while(side == 0)
    {
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
        {
            master.clear();
            master.print(1, 1, "Blue auton selected");
            side = 1;
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        {
            master.clear();
            master.print(1, 1, "Red auton selected");
            side = 2;
        }
    }
}