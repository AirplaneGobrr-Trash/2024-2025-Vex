#ifndef AUTONS_HPP
#define AUTONS_HPP

#pragma once
#include "utils.hpp"

#include <vector>
#include "a_blue.hpp"
#include "a_red.hpp"
#include "a_skills.hpp"

// These are out of 127
inline int DRIVE_SPEED = 115;
inline int TURN_SPEED = 90;
inline int SWING_SPEED = 90;

namespace auton {
void default_constants();
void none();
void cali();

void intakeBreak();
void turn(bool flipped, int degrees);
void swing(bool flipped, int degrees, int speed);
}  // namespace auton

#endif // AUTONS_HPP