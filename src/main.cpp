#include "main.h"

#include "autons.hpp"
#include "screen.hpp"
#include "utils.hpp"
// OkapiLib?

#include "gobals.hpp"

using AutonFunction = void(*)();
std::vector<std::vector<AutonFunction>> rAutons = {
  { auton::blue_pos2, auton::blue_neg, auton::blue_elim }, // 0 (0-1) - Blue
  { auton::red_pos, auton::red_neg, auton::red_elim }, // 1 (0-1) - Red
  { auton::skills3 } // 2 (0) - Skills
};

std::vector<std::vector<std::string>> rAutonsNames = {
  {"blue_pos", "blue_neg", "blue_elim"}, // 0 (0-1) - Blue
  {"red_pos", "red_neg", "red_elim"}, // 1 (0-1) - Red
  {"skills_3"} // 2 (0) - Skills
};

bool grabbingRing = false;
int twoBarSpeed = 90;
bool runningAuton = false;
bool quitTask = false;

void lift_wait() {
  while (liftPID.exit_condition({twoBar}, true) == ez::RUNNING) {
    if (quitTask) return;
    pros::delay(ez::util::DELAY_TIME);
  }
}

int resetValue = 35000;
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
      twoBar.move(wantSpeed);
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}

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
      // utils::cataGotoAngle(2500, twoBarSpeed, false, twoBarRot, twoBar, 10);
      liftPID.target_set(2700);
      lift_wait();
      // master.rumble("-");
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)) {
      // utils::cataGotoAngle(12500, twoBarSpeed/1.4, false, twoBarRot, twoBar, 10);
      liftPID.target_set(13500);
      lift_wait();
      // master.rumble("-");
    }

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
    master.print(0,0,"%s %u %u..", rAutonsNames[auton[0]][auton[1]], auton[0], auton[1]);
    pros::delay(100);
  }
}


void initialize() {
  picker::render();
  pros::Task::create(autonSelc);

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

  chassis.opcontrol_curve_sd_initialize();
  chassis.drive_imu_calibrate(false);
  chassis.drive_sensor_reset();
  
  master.rumble("-");
}

void disabled() {
  runningAuton = false;
}

void competition_initialize() {}

void autonomous() {
  runningAuton = true;
  twoBar.brake();
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
  pros::Task::create(lift_task);

  std::vector<uint16_t> auton = picker::getAuton();
  rAutons[auton[0]][auton[1]]();
}

void opcontrol() {
  runningAuton = false;
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  twoBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Task::create(controllerButtons);
  pros::Task::create(controllerButtons2);
  pros::Task::create(lift_task);

  chassis.pid_tuner_print_brain_set(true);

  while (true) {
    // Check if we are connected to a field, if we aren't then we enable the option to change the PID
    if (!pros::competition::is_connected()) {
      if (master.get_digital_new_press(DIGITAL_X)) chassis.pid_tuner_toggle();
      chassis.pid_tuner_iterate();

      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        runningAuton = true;
        autonomous();
        // auton::skills3();
        runningAuton = false;
        chassis.drive_brake_set(MOTOR_BRAKE_COAST);
      }
    }

    chassis.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(ez::util::DELAY_TIME);  // Don't change
  }
}