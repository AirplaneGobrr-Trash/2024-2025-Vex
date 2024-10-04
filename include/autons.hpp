#pragma once

#include "EZ-Template/drive/drive.hpp"

extern ez::Drive chassis;
extern pros::adi::DigitalOut piston;
extern pros::Motor liftMotor;
extern pros::adi::DigitalOut goalGrab;
extern pros::Motor intakeMotor;
extern pros::adi::DigitalOut ringGrab;

namespace auton {
void default_constants();
void none();
void cali();

void skillsGood();
void skillsV2();

void neg(bool flipped);
void blue_neg();
void red_neg();

void pos_2(bool flipped);
void blue_pos();
void red_pos();
}  // namespace auton
