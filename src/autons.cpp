#include "main.h"
#include "gobals.hpp"

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

void auton::none() {}

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

void turn(bool flipped, int degrees) {
  if (flipped) degrees = degrees * -1;
  chassis.pid_turn_set(degrees, TURN_SPEED);
}

void swing(bool flipped, int degrees, int speed) {
  if (flipped) {
    chassis.pid_swing_set(ez::RIGHT_SWING, degrees * -1, SWING_SPEED, speed);
  } else {
    chassis.pid_swing_set(ez::LEFT_SWING, degrees, SWING_SPEED, speed);
  }
}

void intakeSpin(int voltage) {
  intakeMotor.move(voltage);
  // liftMotor.move(voltage);
}

void intakeBreak() {
  intakeMotor.brake();
  // liftMotor.brake();
}

void auton::skills3() {
  DRIVE_SPEED = 90;
  intakeSpin(127);
  pros::delay(1000);
  intakeBreak();

  chassis.pid_drive_set(12_in, DRIVE_SPEED, false, true);
  chassis.pid_wait();

  // Turn to (-1200, -600) - goal
  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  // Drive to (-1200, -600) - goal
  chassis.pid_drive_set(-22_in, DRIVE_SPEED, false, true);
  chassis.pid_wait_until(-4_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-16_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  // turn (-600, -600) - ring
  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  // drive (-600, -600) - ring
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-600, -1200) - ring
  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  // drive (-600, -1200) - ring
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-1200, -1200) - ring
  chassis.pid_turn_set(-180, TURN_SPEED);
  chassis.pid_wait();

  // drive (-1200, -1200) - ring
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);
  
  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  // backup from (-1200, -1200) to (-1500, -1200)
  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  // turn (-1500, -1200) - ring
  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  // drive (-1500, -1200) - ring
  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  // back up to put goal in coner
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  // face coner with goal
  chassis.pid_turn_set(-315, TURN_SPEED);
  chassis.pid_wait();

  // drive and drop goal
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_until(-2);
  goalGrab.set_value(0);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-88, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-76_in, DRIVE_SPEED);
  chassis.pid_wait_until(-50_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-70_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  // turn 
  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  
  pros::delay(500);

  chassis.pid_turn_set(315, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait_until(-2);
  goalGrab.set_value(0);
  chassis.pid_wait();

  intakeBreak();

  pros::delay(500);

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(360, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(44_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(315, TURN_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(38_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(350);

  intakeBreak();

  chassis.pid_turn_set(136, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-34_in, DRIVE_SPEED);
  chassis.pid_wait_until(-20);
  chassis.pid_speed_max_set(20);
  chassis.pid_wait_until(-32);
  goalGrab.set_value(1);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_turn_set(120, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(48_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90, TURN_SPEED);

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(225, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  goalGrab.set_value(0);

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeBreak();
}

void removed(){
   return;

  // Turn to (-600, -1200) - ring
  chassis.pid_turn_set(-45, TURN_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  // Drive to (-600, -1200) - ring
  chassis.pid_drive_set(36_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (0, -1500)
  chassis.pid_turn_set(-30, TURN_SPEED);
  chassis.pid_wait();

  pros::delay(500); // this bot can't pick up any rings.

  // Drive to (0, -1500)
  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back up from (0, -1500) to (-600, -600)
  chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-600, -600)
  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();

  // Drive to (-600, -600)
  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1200, -1200)
  chassis.pid_turn_set(230, TURN_SPEED);
  chassis.pid_wait();

  // Drive to (-1200, -1200)
  chassis.pid_drive_set(36_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1500, -1200)
  chassis.pid_turn_set(180, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  
  // Back up from (-1500, -1200) to (-1200, -1500)
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1200, -1500)
  chassis.pid_turn_set(270, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Line up to put goal in coner
  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to coner
  chassis.pid_turn_set(45, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  goalGrab.set_value(0);
  intakeSpin(-30);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();
}

void e(){
    return;

  chassis.pid_turn_set(135, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();
  
  goalGrab.set_value(0);
  pros::delay(100);

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();
}

void auton::blue_pos2() {
  bool flipped = false;

  chassis.pid_drive_set(-18, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 45);
  chassis.pid_wait();

  chassis.pid_drive_set(-18, DRIVE_SPEED/2);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();
  
  intakeSpin(127);

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);
  goalGrab.set_value(0);
  intakeBreak();  

  turn(flipped, 170);
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(1);

  pros::delay(1000);

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(0);

  turn(flipped, 245);
  chassis.pid_wait();

  chassis.pid_drive_set(40_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  return;
  chassis.pid_drive_set(-32_in, 200);
  chassis.pid_wait_quick_chain();

  turn(flipped, 40);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-10_in, DRIVE_SPEED/3);
  chassis.pid_wait();

  goalGrab.set_value(1);

  pros::delay(200);

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, -40);
  chassis.pid_wait();

  pros::delay(1200);
  intakeSpin(-30);
  goalGrab.set_value(0);

  pros::delay(200);

  intakeSpin(127);

  // Grabs middle ring?
  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(100);
  intakeBreak();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-18_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  goalGrab.set_value(1);
  intakeSpin(127);

  pros::delay(500);

  turn(flipped, 180);
  chassis.pid_wait();

  pros::delay(500);

  goalGrab.set_value(0);

  chassis.pid_drive_set(14_in, DRIVE_SPEED/2.5);
  chassis.pid_wait();

  intakeBreak();
}

void auton::blue_neg() {
  bool flipped = false;

  chassis.pid_drive_set(38_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 35);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 75);
  chassis.pid_wait();

  chassis.pid_drive_set(22_in, DRIVE_SPEED);
  chassis.pid_wait();

  // 2ED RING turn
  turn(flipped, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-4, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(32, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 295);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(46, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  return;
  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 42);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  goalGrab.set_value(1);

  pros::delay(350);

  turn(flipped, 225);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 235);
  chassis.pid_wait();
  
  pros::delay(2000);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 320);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 130);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  turn(flipped, 140);
  chassis.pid_wait();
}

void auton::red_neg() {
  bool flipped = true;
  chassis.pid_drive_set(38_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  // grab ring
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  pros::delay(250);

  // pick up goal
  chassis.pid_drive_set(-20_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 70);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(2_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(16, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-2, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(37, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 300);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(50, DRIVE_SPEED/2);
  chassis.pid_wait();
  

  return;
  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped,35);
  chassis.pid_wait();

  chassis.pid_drive_set(-18_in, DRIVE_SPEED/1.5);
  chassis.pid_wait_until(-14_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 220);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 235);
  chassis.pid_wait();
  
  pros::delay(2000);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 320);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 130);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  turn(flipped, 140);
  chassis.pid_wait();

  intakeBreak();
}

void auton::red_pos() {
  bool flipped = true;

  chassis.pid_drive_set(-18, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 45);
  chassis.pid_wait();

  chassis.pid_drive_set(-18, DRIVE_SPEED/1.5);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();
  
  intakeSpin(127);

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(1000);
  goalGrab.set_value(0);
  intakeBreak();  

  turn(flipped, 200);
  chassis.pid_wait();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(1);

  pros::delay(1000);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  ringGrab.set_value(0);

  turn(flipped, 265);
  chassis.pid_wait();

  chassis.pid_drive_set(48_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  return;
  chassis.pid_drive_set(-31_in, 200);
  chassis.pid_wait_quick_chain();

  turn(flipped, 40);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  goalGrab.set_value(1);

  pros::delay(200);

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, -45);
  chassis.pid_wait();

  pros::delay(1200);
  intakeSpin(-30);
  goalGrab.set_value(0);

  pros::delay(200);

  intakeSpin(127);

  // grab mid ring
  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(100);
  intakeBreak();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(-18_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  goalGrab.set_value(1);
  intakeSpin(127);

  pros::delay(500);

  turn(flipped, 180);
  chassis.pid_wait();

  pros::delay(500);

  goalGrab.set_value(0);

  chassis.pid_drive_set(14_in, DRIVE_SPEED/2.5);
  chassis.pid_wait();

  intakeBreak();

}

void auton::blue_elim() {
  bool flipped = false;
  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 42);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  goalGrab.set_value(1);

  pros::delay(350);

  turn(flipped, 225);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 235);
  chassis.pid_wait();
  
  pros::delay(2000);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 320);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, -120);
  chassis.pid_wait_quick_chain();

  intakeBreak();

  chassis.pid_drive_set(-58_in, DRIVE_SPEED);
  chassis.pid_wait();
  return;

  chassis.pid_drive_set(20_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  turn(flipped, 140);
  chassis.pid_wait();
}

void auton::red_elim() {
  bool flipped = true;
  chassis.pid_drive_set(38_in, DRIVE_SPEED);
  chassis.pid_wait();

  intakeSpin(127);

  turn(flipped, 25);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 55);
  chassis.pid_wait();
  intakeBreak();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(-2);
  chassis.pid_wait_until(-18_in);
  goalGrab.set_value(1);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, 75);
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 40);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(250);

  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 90);
  chassis.pid_wait();

  chassis.pid_drive_set(20, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-6, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 180);
  chassis.pid_wait();

  chassis.pid_drive_set(30, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-6, DRIVE_SPEED);
  chassis.pid_wait();

  turn(false, -270);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(80, DRIVE_SPEED);
  chassis.pid_wait();

  return;
  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped,35);
  chassis.pid_wait();

  chassis.pid_drive_set(-18_in, DRIVE_SPEED/1.5);
  chassis.pid_wait_until(-14_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  turn(flipped, 220);
  chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 235);
  chassis.pid_wait();
  
  pros::delay(2000);

  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(300);

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 320);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 130);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED/2);
  chassis.pid_wait();

  ringGrab.set_value(1);

  turn(flipped, 140);
  chassis.pid_wait();

  intakeBreak();
}
///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}