#include "main.h"

void MechanismsLoop(void *_)
{
    bool liftStopped = false;

    while (true)
    {
        if (controller.getDigital(ControllerDigital::L1))
        {
            liftStopped = false;
            lift.moveVoltage(7500);
        }
        else if (controller.getDigital(ControllerDigital::L2))
        {
            liftStopped = false;
            lift.moveVoltage(-7500);
        }
        else if (!liftStopped)
        {
            liftStopped = true;
            lift.moveVoltage(0);
        }

        if (controller.getDigital(ControllerDigital::R2)) {
              piston.set_value(true);
        } else if (controller.getDigital(ControllerDigital::R1)) {
            piston.set_value(false);
        }

        pros::delay(20);
    }
}