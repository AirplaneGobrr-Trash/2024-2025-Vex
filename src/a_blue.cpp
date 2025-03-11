#include "a_blue.hpp"

#include "autons.hpp"
#include "globals.hpp"
#include "pros/device.hpp"
#include "pros/rtos.hpp"
#include "utils.hpp"

void auton::blue::solo() {
  chassis.odom_xyt_set(52_in, 10_in, 125_deg);

  liftPID.target_set(liftScore + 300);

  chassis.pid_odom_set(6_in, DRIVE_SPEED);
  chassis.pid_wait();

  // lift_wait();

  chassis.pid_odom_set(-34_in, DRIVE_SPEED);
  chassis.pid_wait_until(-28);
  goalGrab.set_value(1);
  chassis.pid_wait_quick();

  liftPID.target_set(0);

  chassis.pid_turn_set(320, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_odom_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_quick();

  chassis.pid_odom_set(-22_in, DRIVE_SPEED);
  chassis.pid_wait_quick();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(22_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-26_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(140, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(110);

  intakeLift.set_value(1);

  chassis.pid_odom_set(26_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  chassis.pid_turn_set(190, TURN_SPEED);
  chassis.pid_wait();

  intakeLift.set_value(0);
  goalGrab.set_value(0);
  utils::set_intake(0);

  chassis.pid_odom_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(47, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-36_in, DRIVE_SPEED);
  chassis.pid_wait_until(-28);
  goalGrab.set_value(1);
  chassis.pid_wait_quick();

  utils::set_intake(127);
  
  chassis.pid_turn_set(190, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(26_in, 127);
  chassis.pid_wait();

  chassis.pid_turn_set(-15, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-28_in, 127);
  chassis.pid_wait();

  liftPID.target_set(liftScoreMain);
}

void auton::blue::pos() {
  DRIVE_SPEED = 127;
  chassis.odom_xyt_set(54_in, 17_in, 0_deg);

  // Drive to wall stake
  chassis.pid_turn_set(-318, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Score wall ring
  liftPID.target_set(liftScore + 300);
  pros::delay(600);

  chassis.pid_drive_set(-3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(0);

  chassis.pid_turn_set(-285, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  pros::delay(150);

  // Grab goal
  chassis.pid_drive_set(-32_in, 127);
  chassis.pid_wait_until(-8_in);
  chassis.pid_speed_max_set(DRIVE_SPEED / 3);
  chassis.pid_wait_until(-26_in);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  // Grab ring
  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-16_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face wall
  chassis.pid_turn_set(-270_deg, TURN_SPEED);
  chassis.pid_wait();

  // Goto wall
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face corner rings
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to corner rings
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Face rings
  chassis.pid_turn_set(-228_deg, TURN_SPEED);
  chassis.pid_wait();

  // Grab ring!
  chassis.pid_drive_set(12_in, DRIVE_SPEED / 1.4);
  chassis.pid_wait();

  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  liftPID.target_set(liftScoreMain + 2000);

  chassis.pid_drive_set(44_in, DRIVE_SPEED / 2);
  chassis.pid_wait_until(8_in);
  utils::set_intake(0);
  chassis.pid_wait();
}

void auton::blue::neg() {
  chassis.odom_xyt_set(54_in, 17_in, 180_deg);

  chassis.pid_turn_set(138, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(8_in, 120);
  chassis.pid_wait();

  liftPID.target_set(liftScore + 300);
  pros::delay(600);

  chassis.pid_drive_set(-8_in, 120);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(0);

  chassis.pid_turn_set(100, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(150);

  chassis.pid_drive_set(-30_in, 127);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED / 3);
  chassis.pid_wait_until(-26_in);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(315_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_swing_set(ez::e_swing::LEFT_SWING, 0, SWING_SPEED, 21);
  chassis.pid_wait();

  chassis.pid_drive_set(14_in, DRIVE_SPEED / 2);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::e_swing::LEFT_SWING, 300, SWING_SPEED, 45);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(60, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(52_in, DRIVE_SPEED / 2);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(220, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(liftScoreMain + 500);

  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait();
}

void auton::blue::neg2() {
  // Start
  chassis.odom_xyt_set(54_in, 17_in, 90_deg);

  chassis.pid_odom_set({{{18_in, 27_in, 115_deg}, ez::drive_directions::REV, DRIVE_SPEED / 2}});
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(1);
  pros::delay(50);

  chassis.pid_turn_set(330_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_odom_set({
      {{14_in, 35_in}, ez::drive_directions::FWD, DRIVE_SPEED},
      {{14_in, 40_in}, ez::drive_directions::FWD, DRIVE_SPEED},
      {{17_in, 50_in}, ez::drive_directions::FWD, DRIVE_SPEED / 2},
      {{20_in, 55_in}, ez::drive_directions::FWD, DRIVE_SPEED / 2},
  });
  chassis.pid_wait();

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait_until(2_in);
  utils::set_intake(-35);
  chassis.pid_wait_until(6_in);
  utils::set_intake(127);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_turn_set(190, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(140, DRIVE_SPEED);
  chassis.pid_wait();

  intakeLift.set_value(1);

  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  goalGrab.set_value(0);
  liftPID.target_set(4000);
  chassis.pid_speed_max_set(DRIVE_SPEED / 2.6);
  chassis.pid_wait();
  intakeLift.set_value(0);

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(1500);
  utils::set_intake(0);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait_until(8_in);
  liftPID.target_set(21000);
  chassis.pid_wait();

  lift_wait();

  chassis.pid_drive_set(-26_in, DRIVE_SPEED / 1.4);
  chassis.pid_wait();
}

void auton::blue::pos_rush() {
  chassis.odom_xyt_set(52_in, -36_in, 270_deg);

  utils::set_intake(127);

  chassis.pid_odom_set({
  {{24_in, -47_in}, fwd, 127},
  {{15_in, -50_in}, fwd, 127}
  }, true);

  chassis.pid_wait_until_index(1);
  ringGrab.set_value(1);
  utils::set_intake(0);
  chassis.pid_wait();

  chassis.pid_odom_set(-16_in, 127);
  chassis.pid_wait_quick_chain();

  ringGrab.set_value(0);
  pros::delay(200);

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-14_in, 127);
  chassis.pid_wait_until(-12);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(6_in, 127);
  chassis.pid_wait_quick_chain();

  utils::set_intake(-60);

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-16_in, 127);
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(0);

  chassis.pid_turn_set(155, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-32_in, 127);
  chassis.pid_wait_until(-26);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(105, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_odom_set(42_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(175, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(40_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set(-8_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(310, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(0);

  liftPID.target_set(liftScoreMain+1000);

  chassis.pid_odom_set(48_in, 127);
  chassis.pid_wait();
}