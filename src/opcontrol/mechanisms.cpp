#include "main.h"

void MechanismsLoop(void *_)
{
    bool liftStopped = false;

    while (true)
    {
        if (controller.getDigital(ControllerDigital::L1))
        {
            liftStopped = false;
            lift.moveVoltage(10000);
        }
        else if (controller.getDigital(ControllerDigital::L2))
        {
            liftStopped = false;
            lift.moveVoltage(-10000);
        }
        else if (!liftStopped)
        {
            liftStopped = true;
            lift.moveVoltage(0);
        }

        pros::delay(20);
    }
}