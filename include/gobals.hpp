#pragma once
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"
#include "EZ-Template/api.hpp"

extern ez::Drive chassis;

extern pros::Controller masterController;

// Motors
extern pros::Motor intakeMotor;
extern pros::Motor twoBar;

// Other
extern pros::Rotation twoBarRot;
extern ez::PID liftPID;

// 3 Wire
// Out
extern pros::adi::DigitalOut goalGrab;
extern pros::adi::DigitalOut ringGrab;
//In
extern pros::adi::DigitalIn autonButton;