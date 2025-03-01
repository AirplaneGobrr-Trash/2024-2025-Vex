#pragma once
#include "EZ-Template/tracking_wheel.hpp"
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"
#include "EZ-Template/api.hpp"

void lift_wait();
int getAngle();
void lift_task();

extern ez::Drive chassis;
extern ez::tracking_wheel vert_tracker;

extern pros::Controller masterController;

// Motors
extern pros::Motor intakeMotor;
extern pros::Motor twoBar;

// Sensors
extern pros::Rotation twoBarRot;
extern pros::Distance backDist;
extern pros::Optical liftColor;

// PID Stuff
extern ez::PID liftPID;
extern void lift_wait();
extern int getAngle();
extern void lift_task();

// 3 Wire
// Out
extern pros::adi::DigitalOut goalGrab;
extern pros::adi::DigitalOut ringGrab;
extern pros::adi::DigitalOut intakeLift;
//In
extern pros::adi::DigitalIn autonButton;

// Load rings into the two bar
inline int liftLoad = 5000;
// Ring loaded just above the og load pos, nice for having a ring loaded but the intake be able to load on goals still
inline int liftRingBypass = 7300;

// Score ring onto colored wall stake
inline int liftScoreMain = 15500;
// Score ring onto wall stake
inline int liftScore = 21000;