#include "main.h"

#include "autons.hpp"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "screen.hpp"
#include "utils.hpp"


bool grabbingRing = false;
int twoBarSpeed = 90;
bool runningAuton = false;
bool isIntakeUp = false;
bool isRunningIntake = false;

bool noCode = false;

std::chrono::high_resolution_clock::time_point start;
std::chrono::high_resolution_clock::time_point endTime;

std::vector<AutonHelper> m_autons;

// Checks if we are running an auton
bool isRunningAuton() {
  return runningAuton;
  //pros::competition::is_autonomous() || runningAuton;
}

void controllerButtons2() {
  while (true) {
    if (isRunningAuton()) {  // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_UP)) {
      liftPID.target_set(liftLoad);
      lift_wait();
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_Y)) {
      liftPID.target_set(liftRingBypass);
      lift_wait();
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)) {
      liftPID.target_set(liftScoreMain);
      lift_wait();
    }

    pros::delay(100);

    // if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_B)) {
    //
    //   // utils::cataGotoAngle(12500, twoBarSpeed/1.4, false, twoBarRot, twoBar, 10);
    //   liftPID.target_set(100);
    //   lift_wait();
    //   // master.rumble("-");
    // }
  }
}

void controllerButtons() {
  while (true) {
    if (isRunningAuton()) {  // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)) {
      // intakeMotor.move(127);
      utils::set_intake(127);
      isRunningIntake = true;
    } else if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)) {
      // intakeMotor.move(-127);
      utils::set_intake(-127);
      isRunningIntake = true;
    } else if (
      isRunningIntake &&
      !masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2) &&
      !masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)
      ) {
      isRunningIntake = false;
      utils::set_intake(0);
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)) {
      goalGrab.set_value(1);
    } else if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2)) {
      goalGrab.set_value(0);
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_LEFT)) {
      ringGrab.set_value(1);
    } else if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_DOWN)) {
      ringGrab.set_value(0);
    }

    pros::delay(100);
  }
}

void autonSelc() {
  while (true) {
    if (isRunningAuton()) {  // Disable buttons if we are running auton
      pros::delay(500);
      continue;
    }
    if (autonButton.get_new_press() || master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_A)) {
      picker::next();
    }
    std::vector<uint16_t> auton = picker::getAuton();
    uint16_t autonColor = auton[0];
    uint16_t autonType = auton[1];

    std::chrono::duration<double> duration = endTime - start;
    double seconds = duration.count();

    master.print(0, 0, "%s %s %u %u %.2f....", m_autons[autonColor].getName(), m_autons[autonColor].getAutons()[autonType].first, autonColor, autonType, seconds);
    pros::delay(10);
  }
}

void autonTimer() {
  while (true) {
    if (isRunningAuton()) endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = endTime - start;
    double seconds = duration.count();

    master.print(0, 0, "%.2f", seconds);
    pros::delay(100);
  }
}

void noCodeCheck() {
  if (autonButton.get_value() == 1) noCode = true;
  if (autonButton.get_new_press()) noCode = true;
}

void initialize() {
  noCodeCheck();
  master.rumble(".");
  m_autons = utils::createAutons();
  picker::render();
  pros::Task::create(autonSelc);

  if (noCode) return;

  ringGrab.set_value(0);
  goalGrab.set_value(0);

  twoBarRot.reset_position();

  liftPID.constants_set(0.03, 0, 0.04);
  liftPID.exit_condition_set(80, 2, 250, 10, 500, 500);
  twoBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  chassis.opcontrol_curve_buttons_toggle(false);
  chassis.opcontrol_drive_activebrake_set(0);
  chassis.opcontrol_curve_default_set(1, 1);

  auton::default_constants();

  // Look at your horizontal tracking wheel and decide if it's in front of the midline of your robot or behind it
  //  - change `back` to `front` if the tracking wheel is in front of the midline
  chassis.odom_tracker_right_set(&vert_tracker);

  chassis.drive_imu_calibrate(false);
  chassis.drive_sensor_reset();

  master.rumble(chassis.drive_imu_calibrated() ? "-" : "-----");
}

void disabled() {
  runningAuton = false;
}

void competition_initialize() {}

void autonomous() {
  if (noCode) return;
  runningAuton = true;
  twoBar.brake();
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
  pros::Task::create(lift_task);
  pros::Task::create(utils::intake_task);
  pros::task_t t = pros::Task::create(autonTimer);

  std::vector<uint16_t> auton = picker::getAuton();
  uint16_t autonColor = auton[0];
  uint16_t autonType = auton[1];

  // pros::delay(2000);

  start = std::chrono::high_resolution_clock::now();
  m_autons[autonColor].getAutons()[autonType].second();
  runningAuton = false;
  // auton::blue::neg();
}

void opcontrol() {
  runningAuton = false;
  if (noCode) return;
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  twoBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Task::create(controllerButtons);
  pros::Task::create(controllerButtons2);

  pros::Task::create(lift_task);
  pros::Task::create(utils::intake_task);

  intakeLift.set_value(0);

  while (true) {
    // Check if we are connected to a field
    if (!pros::competition::is_connected()) {
      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        runningAuton = true;
        autonomous();
        runningAuton = false;
        chassis.drive_brake_set(MOTOR_BRAKE_COAST);
      }
    }

    chassis.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(ez::util::DELAY_TIME);  // Don't change
  }
}