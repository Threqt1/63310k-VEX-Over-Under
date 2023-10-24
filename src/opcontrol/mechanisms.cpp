#include "main.h"

void MechanismsLoop(void *_)
{
    int catapultDirection = 0;
    int intakeDirection = 0;
    int hangDirection = 0;

    while (true)
    {
        if (catapultDirection != 0)
        {
            catapult.moveVelocity(100 * catapultDirection);
        }
        else
        {
            if (!catapult.isStopped())
                catapult.moveVelocity(0);
        }

        if (intakeDirection != 0)
        {
            intake.moveVelocity(600 * intakeDirection);
        }
        else
        {
            if (!intake.isStopped())
                intake.moveVelocity(0);
        }

        if (hangDirection != 0)
        {
            hang.moveVelocity(100 * hangDirection);
        }
        else
        {
            if (!hang.isStopped())
                hang.moveVelocity(0);
        }

        if (controller.getDigital(ControllerDigital::L1))
        {
            piston.set_value(true);
        }
        else if (controller.getDigital(ControllerDigital::L2))
        {
            piston.set_value(false);
        }

        if (controller.getDigital(ControllerDigital::R1))
        {
            intakeDirection = 1;
        }
        else if (controller.getDigital(ControllerDigital::R2))
        {
            intakeDirection = -1;
        }
        else
        {
            intakeDirection = 0;
        }

        if (controller.getDigital(ControllerDigital::X))
        {
            hangDirection = 1;
        }
        else if (controller.getDigital(ControllerDigital::Y))
        {
            hangDirection = -1;
        }
        else
        {
            hangDirection = 0;
        }

        if (controller.getDigital(ControllerDigital::A))
        {
            catapultDirection = 1;
        }
        else if (controller.getDigital(ControllerDigital::B))
        {
            catapultDirection = -1;
        }
        else
        {
            catapultDirection = 0;
        }

        pros::delay(20);
    }
}
