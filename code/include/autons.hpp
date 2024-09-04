#pragma once

#include "EZ-Template/drive/drive.hpp"

extern ez::Drive chassis;
extern pros::adi::DigitalOut piston;
extern pros::Motor liftMotor;

namespace auton {
void default_constants();
void none();
void cali();
void blue_left_nm();
void blue_left_wp();
}  // namespace auton
