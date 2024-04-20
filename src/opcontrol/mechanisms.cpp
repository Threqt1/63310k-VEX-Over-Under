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

bool horizontalToggle = false;
bool verticalToggle = false;
bool driveMotorsHoldToggle = false;

void MechanismsTask(void *_)
{
    while (true)
    {
        intakeMechanism.poll();

        if (controller.get_digital_new_press(DIGITAL_RIGHT))
        {
            horizontalToggle = !horizontalToggle;
            horizontalWings.set_value(horizontalToggle);
        }

        if (controller.get_digital_new_press(DIGITAL_Y))
        {
            verticalToggle = !verticalToggle;
            verticalWings.set_value(verticalToggle);
        }

        if (controller.get_digital_new_press(DIGITAL_UP))
        {
            driveMotorsHoldToggle = !driveMotorsHoldToggle;
            if (driveMotorsHoldToggle)
            {
                leftSideMotors.set_brake_modes(MOTOR_BRAKE_HOLD);
                rightSideMotors.set_brake_modes(MOTOR_BRAKE_HOLD);
            }
            else
            {
                leftSideMotors.set_brake_modes(MOTOR_BRAKE_COAST);
                rightSideMotors.set_brake_modes(MOTOR_BRAKE_COAST);
            }
        }

        pros::delay(20);
    }
}