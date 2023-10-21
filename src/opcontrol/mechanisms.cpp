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

        if (controller.getDigital(ControllerDigital::A))
        {
            piston.set_value(true);
        }
        else if (controller.getDigital(ControllerDigital::B))
        {
            piston.set_value(false);
        }

        if (controller.getDigital(ControllerDigital::R1))
        {
            arm.moveVoltage(9000);
        }
        else if (controller.getDigital(ControllerDigital::R2))
        {
            arm.moveVoltage(-9000);
        }
        else
        {
            arm.moveVoltage(0);
        }

        pros::delay(20);
    }
}
