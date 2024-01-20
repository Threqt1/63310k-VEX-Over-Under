#include "main.h"

Mechanism::Mechanism(pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput) : forwardInput(forwardInput), backwardInput(backwardInput){};
MotorMechanism::MotorMechanism(Motor *motor, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput, int maxVoltage) : motor(motor), maxVoltage(maxVoltage), Mechanism(forwardInput, backwardInput){};
MotorGroupMechanism::MotorGroupMechanism(MotorGroup *motorGroup, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput, int maxVoltage) : motorGroup(motorGroup), maxVoltage(maxVoltage), Mechanism(forwardInput, backwardInput){};
ADIMechanism::ADIMechanism(ADIDigitalOut *adi, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput) : adi(adi), Mechanism(forwardInput, backwardInput){};

void MotorMechanism::poll()
{
    if (controller.get_digital(this->forwardInput))
    {
        this->motor->move_voltage(this->maxVoltage);
    }
    else if (controller.get_digital(this->backwardInput))
    {
        this->motor->move_voltage(-this->maxVoltage);
    }
    else
    {
        this->motor->brake();
    }
}

void MotorGroupMechanism::poll()
{
    if (controller.get_digital(this->forwardInput))
    {
        this->motorGroup->move_voltage(this->maxVoltage);
    }
    else if (controller.get_digital(this->backwardInput))
    {
        this->motorGroup->move_voltage(-this->maxVoltage);
    }
    else
    {
        this->motorGroup->brake();
    }
}

void ADIMechanism::poll()
{
    if (controller.get_digital(this->forwardInput))
    {
        this->adi->set_value(true);
    }
    else if (controller.get_digital(this->backwardInput))
    {
        this->adi->set_value(false);
    }
}

MotorMechanism intakeMechanism(&intake, DIGITAL_R1, DIGITAL_R2);
ADIMechanism horizontalWingsMechanism(&horizontalWings, DIGITAL_L1, DIGITAL_L2);
ADIMechanism verticalWingsMechanism(&verticalWings, DIGITAL_L1, DIGITAL_L2);
ADIMechanism hangMechanism(&hang, DIGITAL_UP, DIGITAL_DOWN);

bool wingsToggle = true;

bool catapultToggle = false;

int catapultDirection = 0;
int catapultMaxVoltage = -12000;
void MechanismsTask(void *_)
{
    while (true)
    {
        intakeMechanism.poll();
        hangMechanism.poll();

        if (controller.get_digital(DIGITAL_RIGHT))
        {
            wingsToggle = !wingsToggle;
        }

        if (wingsToggle)
        {
            horizontalWingsMechanism.poll();
        }
        else
        {
            verticalWingsMechanism.poll();
        }

        if (controller.get_digital(DIGITAL_A))
        {
            catapultToggle = true;
        }

        if (controller.get_digital(DIGITAL_B))
        {
            catapultToggle = false;
        }

        if (controller.get_digital(DIGITAL_X))
        {
            catapultToggle = false;
            catapultDirection = 1;
        }
        else if (controller.get_digital(DIGITAL_Y))
        {
            catapultToggle = false;
            catapultDirection = -1;
        }
        else
        {
            catapultDirection = 0;
        }

        if (catapultToggle)
        {
            catapult.move_voltage(catapultMaxVoltage);
        }
        else
        {
            if (catapultDirection != 0)
            {
                catapult.move_voltage(catapultMaxVoltage * catapultDirection);
            }
            else
            {
                catapult.brake();
            }
        }

        pros::delay(20);
    }
}