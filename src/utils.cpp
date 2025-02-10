#include "utils.hpp"

#include <stdio.h>

#include <functional>
#include <iostream>
#include <optional>
#include <vector>

#include "a_red.hpp"
#include "autons.hpp"
#include "globals.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "screen.hpp"

// Creates an auton helper requires: name, r, g, b
AutonHelper::AutonHelper(const std::string& name, int r, int g, int b, int aType) : name(name), color{r, g, b}, aType(aType) {};

// Add an auton into the group
void AutonHelper::addAuton(const std::string& autonName, std::function<void()> func, const std::string& autonNameDesc) {
  autons.emplace_back(autonName, func);
  autonsDesc.emplace_back(autonName, autonNameDesc);
}

// Returns type of auton
int AutonHelper::getType() const {
  return aType;
}

// Get name of current auton group
std::string AutonHelper::getName() const {
  return name;
}

// Returns the count of autonomous routines
size_t AutonHelper::getCount() const {
  return autons.size();
}

// Get the RGB color for this Auton (used in screen.cpp)
std::tuple<int, int, int> AutonHelper::getRGB() const {
  return std::make_tuple(color.r, color.g, color.b);
}

// Get auton functions
std::vector<std::pair<std::string, std::function<void()>>> AutonHelper::getAutons() const {
  return autons;
}

// Get auton descriptions
std::vector<std::pair<std::string, std::string>> AutonHelper::getAutonsDesc() const {
  return autonsDesc;
}

// Runs a specific auton by its name
bool AutonHelper::runAuton(const std::string& autonName) const {
  for (const auto& [name, func] : autons) {
    if (name == autonName) {
      func();
      return true;
    }
  }
  return false;
}

// Returns the description of the auton requested
std::string AutonHelper::getAutonDesc(const std::string& autonName) const {
  for (const auto& [name, desc] : autonsDesc) {
    if (name == autonName) {
      return desc;
    }
  }
  return ":(";
}

// Stores created autons
std::vector<AutonHelper> autons;

// Creates autons
std::vector<AutonHelper> utils::createAutons() {
  // Create "Blue" Autons
  AutonHelper blue("Blue", 0, 0, 255, 1);
  blue.addAuton("neg", auton::blue::neg, "Neg\n5 - ring\n2 - tops");
  blue.addAuton("pos", auton::blue::pos, "Pos\n3 - ring\n2 - tops");
  

  // Create "Red" Autons
  AutonHelper red("Red", 255, 0, 0, 2);
  red.addAuton("neg", auton::red::neg, "Neg\n5 - ring\n2 - tops");
  red.addAuton("pos", auton::red::pos, "Pos\n3 - ring\n2 - tops");

  // Create "Skills" Autons
  AutonHelper skills("Skills", 204, 204, 0, 3);
  // skills.addAuton("SkillsV3", auton::skills::skillsv3, "Skills V3\nI hate (mondays) skills....");

  // Add the AutonHelpers to the autons
  autons = {blue, red, skills};
  return autons;
}

int target_speed = 0;

void raw_set_intake(int input) {
  intakeMotor.move_voltage(input * (12000.0 / 127.0));
}

void utils::set_intake(int input) {
  raw_set_intake(input);
  target_speed = input;
}

// 0 = Blue ring
// 1 = Red ring
void eject(int type) {
  printf("Ejecting %d", type);
  pros::delay(180);
  raw_set_intake(-10);
  pros::delay(300);
  raw_set_intake(target_speed);
  printf("Ejected %d", type);
}

void utils::intake_task() {
  const int wait_time = 30;
  const int outtake_time = 250;
  const int min_speed = 20;  // minimum speed to move the intake
  int jam_counter = 0;
  bool is_jammed = false;
  bool is_red = false;

  while (true) {
    pros::c::optical_rgb_s_t rgb_value = liftColor.get_rgb();
    liftColor.set_led_pwm(50);

    // Check if running auton
    if (true) { // isRunningAuton
      bool redCheck = false; // rgb_value.red > rgb_value.green && rgb_value.red > rgb_value.blue;
      bool blueCheck = false; // rgb_value.blue > rgb_value.red && rgb_value.blue > rgb_value.green;

      std::vector<uint16_t> auton = picker::getAuton();
      uint16_t autonColor = auton[0];

      switch (autonColor) {
        case 0: {
          // Blue auton
          if (redCheck) eject(1);
          break;
        }
        case 1: {
          // Red auton
          if (blueCheck) eject(0);
          break;
        }
      }
    }

    // Run intake full power in opposite direction for outtake_time ms when jammed, then
    // set intake back to normal
    if (is_jammed && isRunningAuton()) {
      raw_set_intake(-127 * ez::util::sgn(target_speed));
      jam_counter += ez::util::DELAY_TIME;
      if (jam_counter > outtake_time) {
        is_jammed = false;
        jam_counter = 0;
        raw_set_intake(target_speed);
      }
      // Detect a jam if velocity is 0 for wait_time ms
    } else if (abs(target_speed) >= min_speed && intakeMotor.get_actual_velocity() == 0) {
      jam_counter += ez::util::DELAY_TIME;
      if (jam_counter > wait_time) {
        jam_counter = 0;
        is_jammed = true;
      }
    }

    // Reset jam_counter when button is released
    if (target_speed <= min_speed) {
      jam_counter = 0;
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}

// Return the autons
std::vector<AutonHelper> utils::getAutons() {
  return autons;
}