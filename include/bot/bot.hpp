#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once
extern Controller controller;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

extern MotorGroup intake;
extern ADIDigitalOut wings;
extern ADIDigitalOut pto;
extern ADIDigitalOut hang;