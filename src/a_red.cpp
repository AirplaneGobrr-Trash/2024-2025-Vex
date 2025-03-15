#include "a_red.hpp"

#include "autons.hpp"
#include "globals.hpp"
#include "utils.hpp"

void auton::red::solo() {
  
}

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
  chassis.pid_drive_set(26_in, DRIVE_SPEED);
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

  chassis.pid_drive_set(46_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(8_in);
  utils::set_intake(0);
  chassis.pid_wait();
}

void auton::red::neg(){
  chassis.odom_xyt_set(-51_in, 9.5_in, 240_deg);

  liftPID.target_set(liftScore + 300);

  chassis.pid_odom_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_quick();

  pros::delay(600);

  chassis.pid_odom_set(-38_in, DRIVE_SPEED);
  chassis.pid_wait_until(-6_in);
  liftPID.target_set(0);
  chassis.pid_wait_until(-34_in);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_odom_set({
    {{-5.2_in, 38_in}, fwd, DRIVE_SPEED/2}, // grab ring 1
    {{-5.2_in, 64_in}, fwd, DRIVE_SPEED/2}, // grab ring 2
    {{-7_in, 40_in}, rev, DRIVE_SPEED}, // Go back
    {{-7.5_in, 35_in}, rev, DRIVE_SPEED}, // Go back
    {{-12_in, 30_in}, rev, DRIVE_SPEED}, // go back more
  }, true);
  chassis.pid_wait_quick();

  chassis.pid_odom_set({
    {{-27_in, 51.5_in}, fwd, DRIVE_SPEED}, // grab ring 3
    {{-20_in, 35_in}, rev, DRIVE_SPEED}, // go back
    //{{-45_in, 35_in}, fwd, 127}, // goto wall
    {{-64_in, 69_in}, fwd, 127}, // grab ring 4
    {{-43_in, 35_in}, rev, DRIVE_SPEED}, // backup terry!
  }, true);
  chassis.pid_wait_until_index_started(5);
  
  intakeLift.set_value(1);
  chassis.pid_wait_quick();
  
  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick();

  chassis.pid_odom_set({
    {{-42_in, 0_in}, fwd, DRIVE_SPEED}, // goto ring 5
  },
  true);
  chassis.pid_wait_quick();

  chassis.pid_turn_set({-25.5, 3}, fwd, DRIVE_SPEED);
  chassis.pid_wait_quick();

  pros::delay(250);
  intakeLift.set_value(0);

  chassis.pid_odom_set(14_in, DRIVE_SPEED);
  chassis.pid_wait_quick();

  utils::set_intake(0);
  ringGrab.set_value(1);
}

void neg2g() {
  chassis.odom_xyt_set(-54_in, 17_in, 180_deg);

  chassis.pid_turn_set(-138, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(8_in, 120);
  chassis.pid_wait();

  liftPID.target_set(liftScore+300);
  pros::delay(600);

  chassis.pid_drive_set(-8_in, 120);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(0);

  chassis.pid_turn_set(-100, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(150);

  chassis.pid_drive_set(-30_in, 127);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait_until(-26_in);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-315_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, 0, SWING_SPEED, 22);
  chassis.pid_wait();

  chassis.pid_drive_set(14_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::e_swing::RIGHT_SWING, -300, SWING_SPEED, 45);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-60, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(56_in, DRIVE_SPEED/2);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-220, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(liftScoreMain+500);

  chassis.pid_drive_set(36_in, DRIVE_SPEED);
  chassis.pid_wait();
}

void auton::red::pos_rush() {
  chassis.odom_xyt_set(-52_in, -59_in, 90_deg);

  utils::set_intake(70);

  chassis.pid_odom_set({
  {{-24_in, -47_in}, fwd, 127},
  {{-14_in, -45_in}, fwd, 127}
  }, true);

  chassis.pid_wait_until_index(1);
  ringGrab.set_value(1);
  utils::set_intake(0);
  chassis.pid_wait();

  chassis.pid_odom_set(-16_in, 127);
  chassis.pid_wait_quick_chain();

  ringGrab.set_value(0);
  pros::delay(200);

  chassis.pid_turn_set(-85, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-16_in, 127);
  chassis.pid_wait_until(-12);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(8_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-8_in, 127);
  chassis.pid_wait_until(-4);
  utils::set_intake(-60);
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(0);

  chassis.pid_turn_set(-160, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-36_in, 127);
  chassis.pid_wait_until(-26);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-105, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_odom_set(40_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-175, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(24_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-140, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set(10_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_odom_set(-8_in, 127);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-310, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(0);

  liftPID.target_set(liftScoreMain+1500);

  chassis.pid_odom_set(48_in, 127, true);
  chassis.pid_wait();
}