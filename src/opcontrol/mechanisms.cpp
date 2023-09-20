#include "main.h"

void MechanismsLoop(void *_)
{
    bool liftStopped = false;

    while (true)
    {
        if (controller.getDigital(ControllerDigital::A))
        {
            liftStopped = false;
            lift.moveVoltage(10000);
        }
        else if (!liftStopped)
        {
            liftStopped = true;
            lift.moveVoltage(0);
        }

        pros::delay(20);
    }
}