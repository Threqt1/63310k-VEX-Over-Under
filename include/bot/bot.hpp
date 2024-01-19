#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once
extern Controller controller;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

extern MotorGroup catapult;
extern Motor intake;
extern ADIDigitalOut horizontalWings;
extern ADIDigitalOut verticalWings;
extern ADIDigitalOut hang;