#include "main.h"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once

extern Controller controller;
extern std::shared_ptr<ChassisController> chassis;
extern std::shared_ptr<SkidSteerModel> drivetrain;
extern MotorGroup lift;