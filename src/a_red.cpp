#include "a_red.hpp"

#include "autons.hpp"
#include "globals.hpp"
#include "utils.hpp"

void auton::red::pos() {
  chassis.odom_xyt_set(-54_in, -17_in, 0_deg);

  chassis.pid_turn_set(318, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(9_in, DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(liftScore+300);
  pros::delay(600);

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(0);

  chassis.pid_turn_set(287, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  pros::delay(150);

  chassis.pid_drive_set(-36_in, 127);
  chassis.pid_wait_until(-12_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait_until(-26_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);


  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-16_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face wall
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();

  // Goto wall
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face corner rings
  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to corner rings
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face rings
  chassis.pid_turn_set(228_deg, TURN_SPEED);
  chassis.pid_wait();

  // Grab ring!
  chassis.pid_drive_set(12_in, DRIVE_SPEED/1.4);
  chassis.pid_wait();

  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  liftPID.target_set(liftScoreMain+2000);

  chassis.pid_drive_set(44_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(8_in);
  utils::set_intake(0);
  chassis.pid_wait();
}

void auton::red::neg() {
  chassis.odom_xyt_set(-54_in, 17_in, 180_deg);

  chassis.pid_turn_set(-135, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(7_in, 120);
  chassis.pid_wait();

  liftPID.target_set(liftScore+300);
  pros::delay(600);

  chassis.pid_drive_set(-5_in, 120);
  chassis.pid_wait();

  liftPID.target_set(0);

  chassis.pid_turn_set(-107, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  pros::delay(150);

  chassis.pid_drive_set(-34_in, 127);
  chassis.pid_wait_until(-12_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait_until(-26_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  chassis.pid_turn_set(-315_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_odom_set({
      {{-11_in, 35_in}, ez::drive_directions::FWD, 120},
      {{-11_in, 40_in}, ez::drive_directions::FWD, 120},
      {{-11_in, 50_in}, ez::drive_directions::FWD, DRIVE_SPEED / 2},
      {{-16_in, 55_in}, ez::drive_directions::FWD, DRIVE_SPEED / 2},
  });
  chassis.pid_wait();

  chassis.pid_turn_set(-122_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(14_in, 120);
  chassis.pid_wait();

  chassis.pid_turn_set(-68_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(44_in, 127);
  chassis.pid_wait_until(24_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/2);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(70_in, DRIVE_SPEED);
  chassis.pid_wait_until(45_in);
  intakeLift.set_value(1);
  chassis.pid_speed_max_set(DRIVE_SPEED/1.5);
  chassis.pid_wait_quick_chain();

  // chassis.pid_turn_set(-220_deg, TURN_SPEED);
  // chassis.pid_wait_quick_chain();
// 
  // chassis.pid_drive_set(44_in, DRIVE_SPEED);
  // chassis.pid_wait_until(8);
  // liftPID.target_set(liftScoreMain+2400);
  // chassis.pid_wait_until(22);
  // utils::set_intake(-127);
  // chassis.pid_wait();

  utils::set_intake(0);
}