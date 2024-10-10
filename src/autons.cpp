#include "main.h"

// These are out of 127
int DRIVE_SPEED = 80;
int TURN_SPEED = 90/2;
int SWING_SPEED = 90/2;

void auton::default_constants() {
  master.clear();
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
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


void turn(bool flipped, int degrees){
  if (flipped) degrees = degrees * -1;
  chassis.pid_turn_set(degrees, TURN_SPEED);
  chassis.pid_wait();
}

void intakeSpin(int voltage) {
  intakeMotor.move(voltage);
  // liftMotor.move(voltage);
}

void intakeBreak() {
  intakeMotor.brake();
  // liftMotor.brake();
}

void skills(bool flip) {
  DRIVE_SPEED = 115;
  // Turn to (-600, -600)
  // chassis.pid_turn_set(0, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 0);

  // Drive to (-600, -600)
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (0, -1500)
  // chassis.pid_turn_set(55, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 55);

  // Drive to (0, -1500)
  chassis.pid_drive_set(38_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-600, -1200) & (-1200, -1200)
  // chassis.pid_turn_set(190, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 190);

  // Drive to (-600, -1200) & (-1200, -1200)
  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(DRIVE_SPEED/3);
  chassis.pid_wait();

  // Turn to (-1500, -1200)
  // chassis.pid_turn_set(185, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 185);

  // Drive to (-1500, -1200)
  chassis.pid_drive_set(20_in, DRIVE_SPEED/4);
  chassis.pid_wait();

  // Goal: (-1200, -1500)
  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1200, -1500)
  // chassis.pid_turn_set(130, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 130);

  // Drive to (-1200, -1500)
  chassis.pid_drive_set(16_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back up cus we have a "full" goal (hopefully)
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Face coner
  // chassis.pid_turn_set(325, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, 325);

  // Drop goal
  chassis.pid_drive_set(-26_in, DRIVE_SPEED);
  chassis.pid_wait_until(-12_in);
  goalGrab.set_value(0);
  intakeSpin(-127);
  chassis.pid_wait();

  intakeBreak();

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();

  // chassis.pid_turn_set(90, TURN_SPEED);
  // chassis.pid_wait();
  turn(flip, -90);
}

void auton::skillsV2() {
  intakeSpin(127);
  pros::delay(1000);
  intakeBreak();

  chassis.pid_drive_set(13_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  // Grab goal
  chassis.pid_drive_set(-23_in, DRIVE_SPEED);
  chassis.pid_wait_until(-14_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  goalGrab.set_value(1);
  pros::delay(100);

  intakeSpin(127);

  skills(false);

  chassis.pid_drive_set(-76_in, DRIVE_SPEED); // 78
  chassis.pid_wait_until(-58_in);
  chassis.pid_speed_max_set(25);
  chassis.pid_wait_until(-70_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  intakeSpin(127);
  skills(true);

  pros::delay(1000);
  intakeBreak();
}

// https://api.vex.com/vr/home/playgrounds/v5rc_high_stakes/gps_coordinates.html
void auton::skillsGood() {
  intakeSpin(127);
  pros::delay(1000);
  intakeBreak();

  chassis.pid_drive_set(13_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-90, TURN_SPEED);
  chassis.pid_wait();

  // Grab goal
  chassis.pid_drive_set(-23_in, DRIVE_SPEED);
  chassis.pid_wait_until(-12_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  goalGrab.set_value(1);
  pros::delay(100);

  intakeSpin(127);

  // Turn to (-600, -600)
  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-600, -1200)
  chassis.pid_turn_set(90, TURN_SPEED/1.1);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1200, -1200) & (-1500, -1200)
  chassis.pid_turn_set(180, TURN_SPEED/1.1);
  chassis.pid_wait();

  // Hit wall
  master.print(0,0, "Hit wall???");
  chassis.pid_drive_set(50_in, DRIVE_SPEED/2.2);
  chassis.pid_wait();

  chassis.pid_turn_set(120, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to (-1200, -1500) & (0, -1500)
  chassis.pid_turn_set(5, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(53_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-5, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-58_in, DRIVE_SPEED);
  chassis.pid_wait_until(-50_in);
  goalGrab.set_value(0);
  intakeBreak();
  chassis.pid_wait();

  pros::delay(500);

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(90.5, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-92_in, DRIVE_SPEED);
  chassis.pid_wait_until(-85);
  chassis.pid_speed_max_set(15);
  chassis.pid_wait();

  goalGrab.set_value(1);

  intakeSpin(127);

  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-55, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(50_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-190, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(24_in, DRIVE_SPEED/1.5);
  chassis.pid_wait();

  chassis.pid_turn_set(-180, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(56_in, DRIVE_SPEED/2.2);
  chassis.pid_wait();
  // idk
}

void auton::neg(bool flipped) {
  chassis.pid_drive_set(-36, DRIVE_SPEED);
  chassis.pid_wait_until(-25_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-35_in);
  goalGrab.set_value(1);
  chassis.pid_wait();

  // chassis.pid_turn_set(-60, TURN_SPEED);
  turn(flipped, -60);
  // chassis.pid_wait();

  intakeSpin(127);

  chassis.pid_drive_set(30_in, DRIVE_SPEED);
  chassis.pid_wait();

  //chassis.pid_turn_set(-144, TURN_SPEED);
  turn(flipped, -150);
  // chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait();

  // chassis.pid_turn_set(-180, TURN_SPEED);
  turn(flipped, -175);
  // chassis.pid_wait();

  chassis.pid_drive_set(9_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  // chassis.pid_turn_set(-220, TURN_SPEED);
  turn(flipped, -220);
  // chassis.pid_wait();

  chassis.pid_drive_set(22_in, DRIVE_SPEED/2);
  chassis.pid_wait_until(12_in);
  chassis.pid_speed_max_set(15);
  chassis.pid_wait();

  // chassis.pid_turn_set(-210, TURN_SPEED);
  turn(flipped, -210);
  // chassis.pid_wait();

  intakeBreak();
  if (!flipped) ringGrab.set_value(1);

  turn(flipped, -210);
}

void auton::pos_2(bool flipped) {
  chassis.pid_drive_set(-20_in, DRIVE_SPEED);
  chassis.pid_wait();

  turn(flipped, 45);

  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10);
  goalGrab.set_value(1);
  chassis.pid_wait();


  pros::delay(100);
  intakeSpin(127);

  pros::delay(1000);

  goalGrab.set_value(0);
  pros::delay(500);
  intakeBreak();

  turn(flipped, 90);
  intakeSpin(120);

  chassis.pid_drive_set(23_in, DRIVE_SPEED);
  chassis.pid_wait();
  intakeBreak();


  turn(flipped, 0);

  chassis.pid_drive_set(-17_in, DRIVE_SPEED);
  chassis.pid_wait_until(-7_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  goalGrab.set_value(1);
  pros::delay(500);

  chassis.pid_drive_set(23_in, DRIVE_SPEED);
  chassis.pid_wait();
  intakeSpin(127);

  turn(flipped, -132);

  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(5);
  chassis.pid_wait();
}

void auton::blue_neg(){
  auton::neg(false);
}

void auton::red_neg(){
  auton::neg(true);
}

void auton::blue_pos() {
  auton::pos_2(false);
}

void auton::red_pos() {
  auton::pos_2(true);
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