#include "main.h"
#include "autons.hpp"

#include "globals.hpp"
#include "utils.hpp"
#include "a_blue.hpp"
#include "a_red.hpp"
#include "a_skills.hpp"

// These are out of 127
int DRIVE_SPEED = 115;
int TURN_SPEED = 90;
int SWING_SPEED = 90;

void auton::default_constants() {
  master.clear();
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 200_ms, 200_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

void auton::none() {
  return;
}


// This should go in a box, a 6" by 6" box
void auton::cali() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(360_deg, TURN_SPEED);
  chassis.pid_wait();
}

void auton::turn(bool flipped, int degrees) {
  if (flipped) degrees = degrees * -1;
  chassis.pid_turn_set(degrees, TURN_SPEED);
}

void auton::swing(bool flipped, int degrees, int speed) {
  if (flipped) {
    chassis.pid_swing_set(ez::RIGHT_SWING, degrees * -1, SWING_SPEED, speed);
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING, degrees, SWING_SPEED, speed);
  }
}

void auton::intakeSpin(int voltage) {
  intakeMotor.move(voltage);
}

void auton::intakeBreak() {
  intakeMotor.brake();
}