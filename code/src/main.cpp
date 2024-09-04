#include "main.h"

#include "autons.hpp"
// OkapiLib?

ez::Drive chassis({-18, 19, -20}, {8, -9, 10}, 11, 2.75, 450);

pros::Controller masterController(CONTROLLER_MASTER);


pros::Motor liftMotor(2, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
pros::adi::DigitalOut piston('H');

void controlerButtons() {
  while (true) {
    if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)) {
      liftMotor.move(127);
    } else if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)) {
      liftMotor.move(-127);
    } else {
      liftMotor.brake();
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)) {
      piston.set_value(1);
    } else if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2)) {
      piston.set_value(0);
    }
    pros::delay(100);
  }
}

void initialize() {
  // pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(false);
  chassis.opcontrol_drive_activebrake_set(0);
  chassis.opcontrol_curve_default_set(1, 1);

  auton::default_constants();
  ez::as::auton_selector.autons_add({
    Auton("None", auton::none),
    Auton("Cali", auton::cali),
    Auton("Blue Left NM", auton::blue_left_nm),
    Auton("Blue Left WP", auton::blue_left_wp)
  });

  ez::as::page_up();
  ez::as::page_down();

  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

void disabled() {}
void competition_initialize() {}

void autonomous() {
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  ez::as::auton_selector.selected_auton_call();
}

void opcontrol() {
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  pros::Task::create(controlerButtons);

  chassis.pid_tuner_print_brain_set(true);

  while (true) {
    // Check if we are connected to a field, if we aren't then we enable the option to change the PID
    if (!pros::competition::is_connected()) {
      if (master.get_digital_new_press(DIGITAL_X)) chassis.pid_tuner_toggle();
      chassis.pid_tuner_iterate();

      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        autonomous();
        // chassis.drive_brake_set(MOTOR_BRAKE_COAST);
      }
    }

    chassis.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(ez::util::DELAY_TIME);  // Don't change
  }
}