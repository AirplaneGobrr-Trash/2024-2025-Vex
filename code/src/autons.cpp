#include "main.h"

// These are out of 127
const int DRIVE_SPEED = 120/2;
const int TURN_SPEED = 90/2;
const int SWING_SPEED = 90/2;

void auton::default_constants() {
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

void auton::blue_left_nm() {
  chassis.pid_drive_set(-28_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Grab goal

  piston.set_value(true);

  pros::delay(500);

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  // We should be lined up with the ring
  // Intake on

  liftMotor.move(127);

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back into the + box
  chassis.pid_drive_set(-1_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  liftMotor.brake();

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(4_in, DRIVE_SPEED);
  chassis.pid_wait();
}

void auton::blue_left_wp() {
  // Drive to goal
  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Grab goal

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  // Face stacked rings

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Face ring next to colored wall stake

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Grab rings

  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back away from AP line

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Face bottem ring

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  // Grab bottom ring

  chassis.pid_drive_set(48_in, DRIVE_SPEED);
  chassis.pid_wait();
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