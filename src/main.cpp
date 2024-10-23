#include "main.h"

#include "autons.hpp"
#include "screen.hpp"
#include "utils.hpp"
// OkapiLib?

#include "gobals.hpp"

using AutonFunction = void(*)();
std::vector<std::vector<AutonFunction>> rAutons = {
  {auton::blue_pos, auton::blue_neg}, // 0 (0-1) - Blue
  {auton::red_pos, auton::red_neg}, // 1 (0-1) - Red
  {auton::skillsV2} // 2 (0) - Skills
};

std::vector<std::vector<std::string>> rAutonsNames = {
  {"blue_pos", "blue_neg"}, // 0 (0-1) - Blue
  {"red_pos", "red_neg"}, // 1 (0-1) - Red
  {"skillsV2"} // 2 (0) - Skills
};

bool grabbingRing = false;
int twoBarSpeed = 90;
bool runningAuton = false;

void lift_wait() {
  while (liftPID.exit_condition({twoBar}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}

void lift_task() {
  int resetValue = 35000;
  while (true) {
    // pros::delay(ez::util::DELAY_TIME);  
    int angle = twoBarRot.get_position();
    if (angle > resetValue) angle = 0;
    int wantSpeed = liftPID.compute(angle);
    twoBar.move(wantSpeed);
    pros::delay(ez::util::DELAY_TIME);
  }
}

void controllerButtons2() {
  while (true) {
    if (pros::competition::is_autonomous() || runningAuton) { // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_UP)) {
      // utils::cataGotoAngle(2500, twoBarSpeed, false, twoBarRot, twoBar, 10);
      liftPID.target_set(2900);
      lift_wait();
      master.rumble("-");
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)) {
      // utils::cataGotoAngle(12500, twoBarSpeed/1.4, false, twoBarRot, twoBar, 10);
      liftPID.target_set(13500);
      lift_wait();
      master.rumble("-");
    }

    if (masterController.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_B)) {
      // utils::cataGotoAngle(12500, twoBarSpeed/1.4, false, twoBarRot, twoBar, 10);
      liftPID.target_set(1000);
      lift_wait();
      master.rumble("-");
    }
  }
}

void controllerButtons() {
  while (true) {
    if (pros::competition::is_autonomous() || runningAuton) { // Disable buttons if we are running auton
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
    if (pros::competition::is_autonomous() || runningAuton) { // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    } 
    if (autonButton.get_new_press()) {
      picker::next();
    }
    std::vector<uint16_t> auton = picker::getAuton();
    master.print(0,0,"%s %u %u", rAutonsNames[auton[0]][auton[1]], auton[0], auton[1]);
    pros::delay(100);
  }
}

void initialize2() {
  picker::render();

  // return;
  // pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(false);
  chassis.opcontrol_drive_activebrake_set(0);
  chassis.opcontrol_curve_default_set(1, 1);
  ringGrab.set_value(0);
  goalGrab.set_value(0);
  twoBarRot.reset_position();

  auton::default_constants();

  // clang-format off
  // ez::as::auton_selector.autons_add({
  //   // Auton("None", auton::none),
  //   // Auton("Cali", auton::cali),
  //   Auton("Skills", auton::skillsV2),
  //   Auton("Blue Pos", auton::blue_pos),
  //   Auton("Red Pos", auton::red_pos),
  //   Auton("Red Neg", auton::red_neg),
  //   Auton("Blue Neg", auton::blue_neg),
  // });
  // clang-format on

  // ez::as::limit_switch_lcd_initialize(&autonButton);
  // ez::as::page_up();
  // ez::as::page_down();

  // chassis.initialize(false);
  chassis.opcontrol_curve_sd_initialize();
  chassis.drive_imu_calibrate(false);
  chassis.drive_sensor_reset();
  // pros::screen::erase();
  // pros::screen::set_pen(0x00B0E0E6);
  // pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 0, "Loading background?");
  // printf("Loading background");
  // // std::vector<std::vector<std::uint32_t>> pixelData = pic::background();
  // std::vector<std::vector<std::uint32_t>> pixelData = {{0x0020223f,0x0020233f,0x00202340,0x00212340,0x00212340,0x00212340,0x00212441,0x00212441,0x00212441,0x00212341,0x00222442,0x00222442,0x00222442,0x00222443,0x00222543,0x00222543,0x00222543,0x00232544,0x00232544,0x00232544,0x00232644,0x00242745,0x00232645,0x00232645,0x00232645,0x00242646,0x00242646,0x00242646,0x00242746,0x00242747,0x00242747,0x00242747,0x00242747,0x00242748,0x00252748,0x00252848,0x00252849,0x00252849,0x00252849,0x00252849,0x00262849,0x0026294a,0x0026284a,0x0026284a}};

  // pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 1, "Loaded background! S: %zu",pixelData.size());

  // // pros::screen::print(pros::TEXT_MEDIUM, 3, "Secon
  // ez::as::initialize();
  master.rumble("-");
  pros::Task::create(autonSelc);
}

void initialize() {
  liftPID.constants_set(0.03, 0, 0.04);
  liftPID.exit_condition_set(80, 2, 250, 10, 500, 500);
  twoBar.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  initialize2();
}

void disabled() {
  runningAuton = false;
}
void competition_initialize() {}

void autonomous() {
  twoBar.brake();
  runningAuton = true;
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  // ez::as::auton_selector.selected_auton_call();
  std::vector<uint16_t> auton = picker::getAuton();
  rAutons[auton[0]][auton[1]]();
  return;

  printf("%u\n", (unsigned int)auton[0]);
  printf("%u\n", (unsigned int)auton[1]);

  if (auton.size() == 2 && auton[0] < rAutons.size() && auton[1] < rAutons[auton[0]].size()) {
    rAutons[auton[0]][auton[1]]();  // Call the function
  } else {
    std::cerr << "Invalid auton selection!" << std::endl;
  }
  runningAuton = false;
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
        autonomous();
        chassis.drive_brake_set(MOTOR_BRAKE_COAST);
      }
    }

    chassis.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(ez::util::DELAY_TIME);  // Don't change
  }
}