#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once

extern Controller controller;
extern std::shared_ptr<OdomChassisController> chassis;
extern std::shared_ptr<SkidSteerModel> drivetrain;
extern Motor intake;
extern MotorGroup hang;
// extern Motor hold;
extern MotorGroup catapult;
extern pros::ADIDigitalOut pistonA;
extern pros::ADIDigitalOut pistonB;