#include "a_skills.hpp"

#include "autons.hpp"
#include "globals.hpp"

int S_DRIVE_SPEED = 115;
int S_TURN_SPEED = 90;
int S_SWING_SPEED = 90;

void auton::skills::skillsv3() {
  S_DRIVE_SPEED = 90;
  intakeSpin(127);
  pros::delay(1000);
  intakeBreak();

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

  intakeSpin(127);

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

  intakeBreak();

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

  intakeSpin(127);

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

  intakeBreak();

  pros::delay(500);

  chassis.pid_drive_set(6_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(360, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(46_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(315, S_TURN_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(40_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(350);

  intakeBreak();

  chassis.pid_turn_set(136, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-36_in, S_DRIVE_SPEED);
  chassis.pid_wait_until(-20);
  chassis.pid_speed_max_set(20);
  chassis.pid_wait_until(-32);
  goalGrab.set_value(1);
  chassis.pid_wait();

  intakeSpin(127);

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

  intakeBreak();

  chassis.pid_drive_set(12_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(98, S_TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-114_in, S_DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(190, S_TURN_SPEED);
  chassis.pid_wait();
}