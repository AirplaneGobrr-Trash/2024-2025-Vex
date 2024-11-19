#include "a_red.hpp"

#include "autons.hpp"
#include "globals.hpp"

int R_DRIVE_SPEED = 115;
int R_TURN_SPEED = 90;
int R_SWING_SPEED = 90;

void auton::red::pos() {
  bool flipped = true;

  chassis.pid_drive_set(-18, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 45);
  chassis.pid_wait();

  chassis.pid_drive_set(-18, R_DRIVE_SPEED / 1.5);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(26_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);
  goalGrab.set_value(0);
  intakeBreak();

  turn(flipped, 200);
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(1);

  pros::delay(1000);

  chassis.pid_drive_set(-21_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(0);

  turn(flipped, 265);
  chassis.pid_wait();

  chassis.pid_drive_set(48_in, R_DRIVE_SPEED / 2);
  chassis.pid_wait();

  ringGrab.set_value(1);
}

void auton::red::neg() {
  bool flipped = true;
  chassis.pid_drive_set(38_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  // grab ring
  chassis.pid_drive_set(10_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  // pros::delay(250);

  // pick up goal
  chassis.pid_drive_set(-20_in, R_DRIVE_SPEED / 1.5);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 90);
  chassis.pid_wait();

  // pros::delay(10000);

  chassis.pid_drive_set(28_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  // turn(flipped, 0);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(15_in, R_DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // // pros::delay(250);
  //
  // chassis.pid_drive_set(-18_in, R_DRIVE_SPEED);
  // chassis.pid_wait();
}

void auton::red::neg_wp() {
  bool flipped = true;
  chassis.pid_drive_set(38_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  // grab ring
  chassis.pid_drive_set(10_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  // pros::delay(250);

  // pick up goal
  chassis.pid_drive_set(-20_in, R_DRIVE_SPEED / 1.5);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 90);
  chassis.pid_wait();

  // pros::delay(10000);

  chassis.pid_drive_set(28_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  // turn(flipped, 0);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(15_in, R_DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // // pros::delay(250);
  //
  // chassis.pid_drive_set(-18_in, R_DRIVE_SPEED);
  // chassis.pid_wait();

  turn(flipped, 190);
  chassis.pid_wait();

  // go back and get rea
  chassis.pid_drive_set(34_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 270);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(52_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  // goalGrab.set_value(0);

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(8_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(13800);
  lift_wait();

  pros::delay(250);

  chassis.pid_drive_set(4_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-6_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(0);

  chassis.pid_drive_set(-6_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  lift_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  // chassis.pid_drive_set(40_in, R_DRIVE_SPEED);
  // chassis.pid_wait();

  // turn(flipped, 10);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(20_in, R_DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // ringGrab.set_value(1);
}

void auton::red::neg_elim() {
    bool flipped = true;
  chassis.pid_drive_set(38_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, R_DRIVE_SPEED/2);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 75);
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-18_in, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(18, R_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-6, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(30, R_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-6, R_DRIVE_SPEED);
  chassis.pid_wait();

  turn(false, -270);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(80, R_DRIVE_SPEED);
  chassis.pid_wait();
}