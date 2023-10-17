#include "main.h"

int liftSpeed = 70;

void MechanismsLoop(void *_)
{
    int liftDirection = 0;

    while (true)
    {
        lift.moveVelocity(liftSpeed * liftDirection);

        if (controller.getDigital(ControllerDigital::L1))
        {
            liftDirection = 1;
        }
        else if (controller.getDigital(ControllerDigital::L2))
        {
            liftDirection = -5;
        }
        else if (controller.getDigital(ControllerDigital::B))
        {
            liftDirection = 0;
        }

        if (controller.getDigital(ControllerDigital::R2))
        {
            piston.set_value(true);
        }
        else if (controller.getDigital(ControllerDigital::R1))
        {
            piston.set_value(false);
        }

        pros::delay(20);
    }
}
