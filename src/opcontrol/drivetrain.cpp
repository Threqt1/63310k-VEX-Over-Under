#include "main.h"

void DrivetrainLoop(void *_)
{
    while (true)
    {
        drivetrain->arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX));

        pros::delay(20);
    }
}