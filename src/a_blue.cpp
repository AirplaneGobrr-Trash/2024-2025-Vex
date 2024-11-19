#include "a_blue.hpp"

#include "autons.hpp"
#include "globals.hpp"

int B_DRIVE_SPEED = 115;
int B_TURN_SPEED = 90;
int B_SWING_SPEED = 90;

void auton::blue::pos() {
  bool flipped = false;

  chassis.pid_drive_set(-18, B_DRIVE_SPEED);
  chassis.pid_wait();

  auton::turn(flipped, 45);
  chassis.pid_wait();

  chassis.pid_drive_set(-18, B_DRIVE_SPEED / 2);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(26_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);
  goalGrab.set_value(0);
  intakeBreak();

  turn(flipped, 170);
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(1);

  pros::delay(1000);

  chassis.pid_drive_set(-24_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(0);

  turn(flipped, 250);
  chassis.pid_wait();

  chassis.pid_drive_set(42_in, B_DRIVE_SPEED / 2);
  chassis.pid_wait();

  ringGrab.set_value(1);
}

void auton::blue::neg() {
  bool flipped = false;
  chassis.pid_drive_set(38_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  // grab ring
  chassis.pid_drive_set(10_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  // pros::delay(250);

  // pick up goal
  chassis.pid_drive_set(-20_in, B_DRIVE_SPEED / 1.5);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 90);
  chassis.pid_wait();

  // pros::delay(10000);

  chassis.pid_drive_set(28_in, B_DRIVE_SPEED);
  chassis.pid_wait();
}

void auton::blue::neg_wp() {
  bool flipped = false;
  chassis.pid_drive_set(38_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  // grab ring
  chassis.pid_drive_set(10_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  // pros::delay(250);

  // pick up goal
  chassis.pid_drive_set(-20_in, B_DRIVE_SPEED / 1.5);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 90);
  chassis.pid_wait();

  // pros::delay(10000);

  chassis.pid_drive_set(28_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  // turn(flipped, 0);
  // chassis.pid_wait();
  //
  // chassis.pid_drive_set(15_in, B_DRIVE_SPEED);
  // chassis.pid_wait();
  //
  // // pros::delay(250);
  //
  // chassis.pid_drive_set(-18_in, B_DRIVE_SPEED);
  // chassis.pid_wait();

  turn(flipped, 190);
  chassis.pid_wait();

  // go back and get rea
  chassis.pid_drive_set(32_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 270);
  chassis.pid_wait();

  intakeBreak();

  // Middle rings push
  chassis.pid_drive_set(52_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-6_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  // goalGrab.set_value(0);

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-4_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(13800);
  // lift_wait();

  pros::delay(500);

  chassis.pid_drive_set(-2_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(0);

  chassis.pid_drive_set(-8_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  lift_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  // turn(flipped, -8);
  // chassis.pid_wait();

  // chassis.pid_drive_set(20_in, B_DRIVE_SPEED);
  // chassis.pid_wait_until(5_in);
  // ringGrab.set_value(1);
  // chassis.pid_wait();
}

void auton::blue::neg_elim() {
    bool flipped = false;

  chassis.pid_drive_set(38_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 35);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, B_DRIVE_SPEED/2);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 75);
  chassis.pid_wait();

  chassis.pid_drive_set(22_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  // 2ED RING turn
  turn(flipped, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(8_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-24_in, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(16, B_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-4, B_DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(32, B_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8, B_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(350);

  turn(flipped, 270);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(68, B_DRIVE_SPEED);
  chassis.pid_wait();
}