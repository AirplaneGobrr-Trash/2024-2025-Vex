#include "utils.hpp"
#include "autons.hpp"

#include <stdio.h>

#include <functional>
#include <iostream>
#include <optional>
#include <vector>

#include "main.h"

// Creates an auton helper requires: name, r, g, b
AutonHelper::AutonHelper(const std::string& name, int r, int g, int b): name(name), color{r, g, b} {}

// Add an auton into the group
void AutonHelper::addAuton(const std::string& autonName, std::function<void()> func, const std::string& autonNameDesc) {
  autons.emplace_back(autonName, func);
  autonsDesc.emplace_back(autonName, autonNameDesc);
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
  AutonHelper blue("Blue", 0,0,255);
  blue.addAuton("pos", auton::blue::pos,"Pos\nx - ring\nx - tops");
  blue.addAuton("neg", auton::blue::neg,"Neg\nx - ring\nx - tops");
  blue.addAuton("neg_wp", auton::blue::neg_wp,"Neg (WP) Win Point\nx - ring\nx - tops");
  blue.addAuton("neg_elim", auton::blue::neg_elim,"Neg Elim\nx - ring\nx - tops");

  // Create "Red" Autons
  AutonHelper red("Red", 255,0,0);
  red.addAuton("pos", auton::red::pos,"Pos\nx - ring\nx - tops");
  red.addAuton("neg", auton::red::neg,"Neg\nx - ring\nx - tops");
  red.addAuton("neg_wp", auton::red::neg_wp,"Neg (WP) Win Point\nx - ring\nx - tops");
  red.addAuton("neg_elim", auton::red::neg_elim,"Neg Elim\nx - ring\nx - tops");

  // Create "Skills" Autons
  AutonHelper skills("Skills", 204,204,0);
  skills.addAuton("SkillsV3", auton::skills::skillsv3,"Skills V3\nI hate (mondays) skills....");

  // Add the AutonHelpers to the autons 
  autons = {blue, red, skills};
  return autons;
}

// Return the autons
std::vector<AutonHelper> utils::getAutons() {
  return autons;
}