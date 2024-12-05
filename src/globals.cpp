#include "globals.hpp"
#include "pros/distance.hpp"

// Drive setup
ez::Drive chassis({-16,17,-19}, {-13,14,15}, 20, 2.75, 450);

// Controller setup
pros::Controller masterController(CONTROLLER_MASTER);

// Motors
pros::Motor intakeMotor(4, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
pros::Motor twoBar(-6, pros::v5::MotorGear::red, pros::v5::MotorUnits::degrees);

// Sensors
pros::Rotation twoBarRot(1);
pros::Distance backDist(21);

// 3 Wire ports
pros::adi::DigitalOut goalGrab('A');
pros::adi::DigitalOut ringGrab('H');
pros::adi::DigitalIn autonButton('C');

// PID
ez::PID liftPID(0.45, 0, 0, 0, "Lift");

bool quitTask = false;
int resetValue = 35000;

void lift_wait() {
  while (liftPID.exit_condition({twoBar}, true) == ez::RUNNING) {
    if (quitTask) return;
    pros::delay(ez::util::DELAY_TIME);
  }
}

int getAngle(){
  int angle = twoBarRot.get_position();
  if (angle > resetValue) angle = 0;
  return angle;
}

void lift_task() {
  while (true) {
    // pros::delay(ez::util::DELAY_TIME);  
    int angle = getAngle();
    
    if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_B)) {
      if (angle > 1000) {
        twoBar.move(-127);
      }
      angle = getAngle();
      liftPID.target_set(angle);
      quitTask = true;
    } else {
      int wantSpeed = liftPID.compute(angle);
      twoBar.move(wantSpeed/1.2);
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}
