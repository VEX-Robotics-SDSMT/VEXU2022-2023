#include "../include/controllerUI.h"

int initAutonSide(pros::Controller Master)
{
    Master.print(0, 0, "A = Red, X = Blue");
	pros::lcd::initialize();
	while(true)
	{
		if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			return 1;
			pros::lcd::set_text(2, "A was pressed!");
		}
		else if(Master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			return 2;
			pros::lcd::set_text(2, "X was pressed!");
		}
        pros::delay(20);
	}
}