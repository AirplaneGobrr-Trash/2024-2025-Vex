#include "main.h"

#include "autons.hpp"
#include "screen.hpp"
#include "utils.hpp"
#include "globals.hpp"

bool grabbingRing = false;
int twoBarSpeed = 90;
bool runningAuton = false;

bool noCode = false;

std::chrono::high_resolution_clock::time_point start;
std::chrono::high_resolution_clock::time_point endTime;

std::vector<AutonHelper> m_autons;

bool isRunningAuton() {
  return pros::competition::is_autonomous() || runningAuton;
}

void controllerButtons2() {
  while (true) {
    if (isRunningAuton()) { // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_UP)) {
      liftPID.target_set(2400);
      lift_wait();
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)) {
      liftPID.target_set(14000);
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
    if (isRunningAuton()) { // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)) {
      intakeMotor.move(127);
    } else if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)) {
      intakeMotor.move(-127);
    } else {
      intakeMotor.brake();
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

void autonSelc(){
  while (true) {
    if (isRunningAuton()) { // Disable buttons if we are running auton
      pros::delay(500);
      continue;
    } 
    if (autonButton.get_new_press() || master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_Y)) {
      picker::next();
    }
    std::vector<uint16_t> auton = picker::getAuton();
    uint16_t autonColor = auton[0];
    uint16_t autonType = auton[1];

    master.print(0,0,"%s %s %u %u %u %u....", m_autons[autonColor].getName(), m_autons[autonColor].getAutons()[autonType].first, autonColor, autonType, backDist.get(), backDist.get()-1610);
    pros::delay(10);
  }
}

void autonTimer() {
  while (true) {
    if (isRunningAuton()) endTime = std::chrono::high_resolution_clock::now();
    auto duration = endTime - start;
    auto seconds = std::chrono::duration<double>(duration).count();
    int whole_seconds = static_cast<int>(seconds);
    int milliseconds = static_cast<int>((seconds - whole_seconds) * 1000);

    master.print(0, 0, "%u %u", backDist.get(), (backDist.get()-1615)/25.4);
    pros::delay(100);
  }
}

void noCodeCheck() {
  if (autonButton.get_value() == 1) noCode = true;
  if (autonButton.get_new_press()) noCode = true;
}

void initialize() {
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

  chassis.drive_imu_calibrate(false);
  chassis.drive_sensor_reset();
  
  master.rumble("-");
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
  pros::task_t t = pros::Task::create(autonTimer);

  std::vector<uint16_t> auton = picker::getAuton();
  uint16_t autonColor = auton[0];
  uint16_t autonType = auton[1];

  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  m_autons[autonColor].getAutons()[autonType].second();
}

void opcontrol() {
  runningAuton = false;
  if (noCode) return;
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  twoBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Task::create(controllerButtons);
  pros::Task::create(controllerButtons2);
  pros::Task::create(lift_task);

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