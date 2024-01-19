#include "main.h"

void DrivetrainTask(void *_)
{
    while (true)
    {
        // get joystick positions
        int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = -controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (abs(forward) < 5)
            forward = 0;
        if (abs(turn) < 5)
            turn = 0;
        // move the chassis with arcade drive
        chassis.arcade(forward, turn);

        pros::delay(10);
    }
}