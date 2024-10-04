#include "main.h"

#include "autons.hpp"
#include "screen.hpp"
// OkapiLib?

ez::Drive chassis({-18, 19, -20}, {8, -9, 10}, 11, 2.75, 450);

pros::Controller masterController(CONTROLLER_MASTER);

pros::Motor liftMotor(2, pros::v5::MotorGear::green, pros::v5::MotorUnits::degrees);
pros::Motor intakeMotor(-4, pros::v5::MotorGear::green, pros::v5::MotorUnits::degrees);
pros::adi::DigitalOut goalGrab('H');
pros::adi::DigitalOut ringGrab('B');
pros::adi::DigitalIn autonButton('G');

bool grabbingRing = false;

void controlerButtons() {
  while (true) {
    if (pros::competition::is_autonomous()) { // Disable buttons if we are running auton
      pros::delay(100);
      continue;
    }

    if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)) {
      liftMotor.move(127);
      intakeMotor.move(127);
    } else if (masterController.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)) {
      liftMotor.move(-127);
      intakeMotor.move(-127);
    } else {
      liftMotor.brake();
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

void initialize2() {
  picker::render();

  while (true) {
    if (autonButton.get_new_press()) {
      picker::next();
    }
    picker::getAuton();
    pros::delay(100);
  }

  return;
  // pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(false);
  chassis.opcontrol_drive_activebrake_set(0);
  chassis.opcontrol_curve_default_set(1, 1);
  ringGrab.set_value(0);
  goalGrab.set_value(0);

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

  chassis.initialize();
  pros::screen::erase();
  pros::screen::set_pen(0x00B0E0E6);
  // pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 0, "Loading background?");
  // printf("Loading background");
  // // std::vector<std::vector<std::uint32_t>> pixelData = pic::background();
  // std::vector<std::vector<std::uint32_t>> pixelData = {{0x0020223f,0x0020233f,0x00202340,0x00212340,0x00212340,0x00212340,0x00212441,0x00212441,0x00212441,0x00212341,0x00222442,0x00222442,0x00222442,0x00222443,0x00222543,0x00222543,0x00222543,0x00232544,0x00232544,0x00232544,0x00232644,0x00242745,0x00232645,0x00232645,0x00232645,0x00242646,0x00242646,0x00242646,0x00242746,0x00242747,0x00242747,0x00242747,0x00242747,0x00242748,0x00252748,0x00252848,0x00252849,0x00252849,0x00252849,0x00252849,0x00262849,0x0026294a,0x0026284a,0x0026284a}};

  // pros::screen::print(pros::text_format_e_t::E_TEXT_MEDIUM_CENTER, 1, "Loaded background! S: %zu",pixelData.size());

  // // pros::screen::print(pros::TEXT_MEDIUM, 3, "Secon
  // ez::as::initialize();
  master.rumble(".");
}

void initialize() {
  initialize2();
}

void disabled() {}
void competition_initialize() {}

using AutonFunction = void(*)();
std::vector<std::vector<AutonFunction>> rAutons = {
  {auton::blue_pos, auton::blue_neg}, // 0 (0-1)
  {auton::red_pos, auton::red_neg}, // 1 (0-1)
  {auton::skillsV2} // 2 (0)
};

void autonomous() {
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);

  // ez::as::auton_selector.selected_auton_call();
  std::vector<uint16_t> auton = picker::getAuton();
  // rAutons[auton[0]][auton[1]]();

  if (auton.size() == 2 && auton[0] < rAutons.size() && auton[1] < rAutons[auton[0]].size()) {
    rAutons[auton[0]][auton[1]]();  // Call the function
  } else {
    std::cerr << "Invalid auton selection!" << std::endl;
  }
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