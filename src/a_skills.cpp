#include "a_skills.hpp"

#include "autons.hpp"
#include "globals.hpp"
#include "utils.hpp"

int S_DRIVE_SPEED = 115;
int S_TURN_SPEED = 90;
int S_SWING_SPEED = 90;

void skillsv4_1() {
  chassis.odom_xyt_set(-54_in, -7_in, 0_deg);

  chassis.pid_turn_set(295_deg, TURN_SPEED);
  chassis.pid_wait();

  liftPID.target_set(liftScore);

  chassis.pid_drive_set(2_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  lift_wait();

  chassis.pid_drive_set(-4_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(0);

  chassis.pid_turn_set(340_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-16, DRIVE_SPEED / 2);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(300);

  chassis.pid_drive_set(18_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(115, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(56_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(250, TURN_SPEED);
  chassis.pid_wait();

  // wall stake
  chassis.pid_drive_set(17_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(liftLoad);
  utils::antiJam(false);

  // face wall stake
  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(450);

  // score ring
  liftPID.target_set(liftScoreMain + 2000);
  utils::set_intake(0);
  utils::antiJam(true);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();

  lift_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(0);

  chassis.pid_turn_set(270, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(120);

  chassis.pid_drive_set(64_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(DRIVE_SPEED / 3);
  chassis.pid_wait();

  pros::delay(250);

  // chassis.pid_drive_set(-2_in, DRIVE_SPEED);
  // chassis.pid_wait();

  chassis.pid_turn_set(145, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  pros::delay(350);

  chassis.pid_turn_set(65, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(0);
  utils::set_intake(-60);
  pros::delay(100);

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  return;
}

void skillsv4_2() {
  // chassis.odom_xyt_set(-46_in, -54_in, 180_deg);

  chassis.pid_drive_set(-78_in, DRIVE_SPEED);
  chassis.pid_wait_until(-54);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait_until(-76);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  // other side

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(65, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(54_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(290, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to wall stake
  chassis.pid_drive_set(22_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(liftLoad);
  utils::antiJam(false);

  // face wall stake
  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  pros::delay(450);

  // score ring
  liftPID.target_set(liftScoreMain + 2000);
  utils::set_intake(0);
  utils::antiJam(true);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();

  lift_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  liftPID.target_set(0);

  chassis.pid_turn_set(270, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(120);

  chassis.pid_drive_set(64_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(DRIVE_SPEED / 3);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(25, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(6_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  pros::delay(400);

  chassis.pid_turn_set(120, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(-50);
  
  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(0);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait_quick_chain();
}

void skillsv4_3() {
  // chassis.odom_xyt_set(-47_in, 50_in, 90_deg);

  utils::set_intake(127);

  chassis.pid_drive_set(35_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  
  liftPID.target_set(liftLoad);
  utils::antiJam(false);

  chassis.pid_drive_set(44_in, DRIVE_SPEED);
  chassis.pid_wait();

  utils::set_intake(0);

  chassis.pid_turn_set(315, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-28_in, DRIVE_SPEED);
  chassis.pid_wait_until(-12_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/4);
  chassis.pid_wait_until(-24_in);
  goalGrab.set_value(1);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(100);

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  pros::delay(200);
  utils::set_intake(0);
  
  liftPID.target_set(liftScore);
  lift_wait();

  chassis.pid_drive_set(-9_in, DRIVE_SPEED);
  chassis.pid_wait();

  liftPID.target_set(0);
  utils::antiJam(true);

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  utils::set_intake(127);

  chassis.pid_drive_set(46_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(225, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // goto middle
  chassis.pid_drive_set(54_in, DRIVE_SPEED);
  chassis.pid_wait_until(12);
  utils::set_intake(0);

  // in ladder
  chassis.pid_wait_until(48);
  utils::set_intake(127);
  chassis.pid_wait_quick_chain();


  chassis.pid_drive_set(8_in, DRIVE_SPEED/2);
  chassis.pid_wait();
  
  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // leaving ladder

  chassis.pid_drive_set(62_in, DRIVE_SPEED);
  chassis.pid_wait_until(2);
  utils::set_intake(0);
  chassis.pid_wait_until(20);
  utils::set_intake(127);
  chassis.pid_wait();

  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(300, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  goalGrab.set_value(0);
  utils::set_intake(-50);

  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(15, TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(0);

  chassis.pid_drive_set(120_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(50, TURN_SPEED);
  chassis.pid_wait();

  liftPID.target_set(liftScore);

  chassis.pid_drive_set(-68_in, DRIVE_SPEED);
  chassis.pid_wait_until(-44);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait_quick_chain();
}

void auton::skills::skillsv4() {
  skillsv4_1();
  skillsv4_2();
  skillsv4_3();
}

void auton::skills::skillsv3() {
  S_DRIVE_SPEED = 90;
  utils::set_intake(127);
  pros::delay(1000);
  utils::set_intake(0);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED, false, true);
  chassis.pid_wait();

  // Turn to (-1200, -600) - goal
  chassis.pid_turn_set(90, S_TURN_SPEED);
  chassis.pid_wait();

  // Drive to (-1200, -600) - goal
  chassis.pid_drive_set(-22_in, S_DRIVE_SPEED, false, true);
  chassis.pid_wait_until(-4_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-16_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  // turn (-600, -600) - ring
  chassis.pid_turn_set(0, S_TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  // drive (-600, -600) - ring
  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-600, -1200) - ring
  chassis.pid_turn_set(-90, S_TURN_SPEED);
  chassis.pid_wait();

  // drive (-600, -1200) - ring
  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-1200, -1200) - ring
  chassis.pid_turn_set(-180, S_TURN_SPEED);
  chassis.pid_wait();

  // drive (-1200, -1200) - ring
  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // backup from (-1200, -1200) to (-1500, -1200)
  chassis.pid_drive_set(-16_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-1500, -1200) - ring
  chassis.pid_turn_set(-90, S_TURN_SPEED);
  chassis.pid_wait();

  // drive (-1500, -1200) - ring
  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // back up to put goal in coner
  chassis.pid_drive_set(-14_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  // face coner with goal
  chassis.pid_turn_set(-315, S_TURN_SPEED);
  chassis.pid_wait();

  // drive and drop goal
  chassis.pid_drive_set(-20_in, S_DRIVE_SPEED);
  chassis.pid_wait_until(-2);
  goalGrab.set_value(0);
  chassis.pid_wait();

  utils::set_intake(0);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-72_in, S_DRIVE_SPEED);
  chassis.pid_wait_until(-50_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-70_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  // turn
  chassis.pid_turn_set(0, S_TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(180, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-14_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_turn_set(315, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-16_in, S_DRIVE_SPEED);
  chassis.pid_wait_until(-2);
  goalGrab.set_value(0);
  chassis.pid_wait();

  utils::set_intake(0);

  pros::delay(500);

  chassis.pid_drive_set(6_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(360, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(46_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(315, S_TURN_SPEED);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_drive_set(40_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(350);

  utils::set_intake(0);

  chassis.pid_turn_set(136, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-36_in, S_DRIVE_SPEED);
  chassis.pid_wait_until(-20);
  chassis.pid_speed_max_set(20);
  chassis.pid_wait_until(-32);
  goalGrab.set_value(1);
  chassis.pid_wait();

  utils::set_intake(127);

  chassis.pid_turn_set(120, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(52_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-14_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, S_TURN_SPEED);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(225, S_TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  goalGrab.set_value(0);

  chassis.pid_drive_set(-8_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(8_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-16_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  utils::set_intake(0);

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(98, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-114_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(190, S_TURN_SPEED);
  chassis.pid_wait();
}