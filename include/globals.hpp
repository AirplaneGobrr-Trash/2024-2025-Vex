#pragma once
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"
#include "EZ-Template/api.hpp"

void lift_wait();
int getAngle();
void lift_task();

extern ez::Drive chassis;

extern pros::Controller masterController;

// Motors
extern pros::Motor intakeMotor;
extern pros::Motor twoBar;

// Sensors
extern pros::Rotation twoBarRot;
extern pros::Distance backDist;

// PID Stuff
extern ez::PID liftPID;
extern void lift_wait();
extern int getAngle();
extern void lift_task();

// 3 Wire
// Out
extern pros::adi::DigitalOut goalGrab;
extern pros::adi::DigitalOut ringGrab;
//In
extern pros::adi::DigitalIn autonButton;