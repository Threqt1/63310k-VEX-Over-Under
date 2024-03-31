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

MotorGroupMechanism intakeMechanism(&intake, DIGITAL_R1, DIGITAL_R2);
ADIMechanism wingsMechanism(&wings, DIGITAL_L1, DIGITAL_L2);
ADIMechanism ptoMechanism(&pto, DIGITAL_A, DIGITAL_B);
ADIMechanism hangMechanism(&hang, DIGITAL_UP, DIGITAL_DOWN);

void MechanismsTask(void *_)
{
    while (true)
    {
        intakeMechanism.poll();
        wingsMechanism.poll();
        ptoMechanism.poll();
        hangMechanism.poll();

        pros::delay(20);
    }
}