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

ADIMechanism wingsMechanism(&wings, DIGITAL_L1, DIGITAL_L2);
ADIMechanism sideHangMechanism(&sideHang, DIGITAL_LEFT, DIGITAL_RIGHT);
ADIMechanism hangMechanism(&hang, DIGITAL_UP, DIGITAL_DOWN);

bool catapultToggle = false;
int catapultDirection = 0;
int catapultMaxVelo = 100;
void MechanismsTask(void *_)
{
    while (true)
    {
        wingsMechanism.poll();
        sideHangMechanism.poll();
        hangMechanism.poll();

        if (controller.get_digital(DIGITAL_A))
        {
            catapultToggle = true;
        }
        else if (controller.get_digital(DIGITAL_B))
        {
            catapultToggle = false;
        }

        if (controller.get_digital(DIGITAL_R1))
        {
            catapultDirection = 1;
        }
        else if (controller.get_digital(DIGITAL_R2))
        {
            catapultDirection = -1;
        }
        else
        {
            catapultDirection = 0;
        }

        if (catapultToggle)
        {
            catapultIntake.move_velocity(catapultMaxVelo);
        }
        else
        {
            if (catapultDirection != 0)
            {
                catapultIntake.move_velocity(catapultMaxVelo * catapultDirection);
            }
            else
            {
                catapultIntake.brake();
            }
        }

        pros::delay(20);
    }
}