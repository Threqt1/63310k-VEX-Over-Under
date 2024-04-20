#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once
extern Controller controller;
extern MotorGroup leftSideMotors;
extern MotorGroup rightSideMotors;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

extern MotorGroup intake;
extern ADIDigitalOut verticalWings;
extern ADIDigitalOut horizontalWings;