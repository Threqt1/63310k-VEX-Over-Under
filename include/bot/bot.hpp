#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once

extern Controller controller;
extern std::shared_ptr<OdomChassisController> chassis;
extern std::shared_ptr<SkidSteerModel> drivetrain;
extern MotorGroup lift;
extern Motor arm;
extern pros::ADIDigitalOut piston;
extern IntegratedEncoder leftEncoder;
extern IntegratedEncoder rightEncoder;