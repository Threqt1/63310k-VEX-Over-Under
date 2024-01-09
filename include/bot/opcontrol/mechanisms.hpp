#include "main.h"

#pragma once

class Mechanism
{
public:
    Mechanism(pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput);
    pros::controller_digital_e_t forwardInput;
    pros::controller_digital_e_t backwardInput;
};

class MotorMechanism : private Mechanism
{
public:
    MotorMechanism(Motor *motor, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput, int maxVoltage = 12000);
    void poll();

private:
    Motor *motor;
    int maxVoltage;
};

class MotorGroupMechanism : private Mechanism
{
public:
    MotorGroupMechanism(MotorGroup *motorGroup, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput, int maxVoltage = 12000);
    void poll();

private:
    MotorGroup *motorGroup;
    int maxVoltage;
};

class ADIMechanism : private Mechanism
{
public:
    ADIMechanism(ADIDigitalOut *adi, pros::controller_digital_e_t forwardInput, pros::controller_digital_e_t backwardInput);
    void poll();

private:
    ADIDigitalOut *adi;
};

void MechanismsTask(void *);