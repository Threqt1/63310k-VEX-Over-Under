#include "main.h"

#include "autonomous/odometry.hpp"
#include "autonomous/pid_movements.hpp"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once

extern Controller controller;
extern std::shared_ptr<ChassisController> chassis;
extern std::shared_ptr<SkidSteerModel> drivetrain;
extern MotorGroup lift;
extern pros::ADIDigitalOut piston;
extern pros::Imu inertial;
extern okapi::IntegratedEncoder leftEncoder;
extern okapi::IntegratedEncoder rightEncoder;
