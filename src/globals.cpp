#include "globals.hpp"

#include "pros/distance.hpp"
#include "pros/optical.hpp"


// Drive setup
ez::Drive chassis({-11, 12, -14}, {16, -17, 18}, 20, 3.25, 480);
ez::tracking_wheel vert_tracker(-10, 2.175, 1.0);  // This tracking wheel is perpendicular to the drive wheels

// Controller setup
pros::Controller masterController(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor intakeMotor(9, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
pros::Motor twoBar(-5, pros::v5::MotorGear::red, pros::v5::MotorUnits::degrees);

// Sensors
pros::Rotation twoBarRot(1);
pros::Distance backDist(21);
pros::Optical liftColor(2);

// 3 Wire ports
pros::adi::DigitalOut goalGrab('A');
pros::adi::DigitalOut intakeLift('B');
pros::adi::DigitalOut ringGrab('C'); 
pros::adi::DigitalIn autonButton('H');

// PID
ez::PID liftPID(5, 0, 20, 0, "Lift");

bool quitTask = false;
int resetValue = 35000;

void lift_wait() {
  while (liftPID.exit_condition({twoBar}, true) == ez::RUNNING) {
    if (quitTask) return;
    pros::delay(ez::util::DELAY_TIME);
  }
}

int getAngle() {
  int angle = twoBarRot.get_position();
  if (angle > resetValue) angle = 0;
  return angle;
}

void lift_task() {
  while (true) {
    // pros::delay(ez::util::DELAY_TIME);
    int angle = getAngle();

    if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_B)) {
      if (angle > 2000) {
        twoBar.move(-100);
      }
      angle = getAngle();
      liftPID.target_set(angle);
      quitTask = true;
    } else if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_X)) {
      if (angle < 25000) {
        twoBar.move(100);
      }
      angle = getAngle();
      liftPID.target_set(angle);
      quitTask = true;
    } else {
      int wantSpeed = liftPID.compute(angle);
      twoBar.move(wantSpeed / 1.2);
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}
