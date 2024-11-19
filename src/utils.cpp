#include "utils.hpp"
#include "autons.hpp"

#include <stdio.h>

#include <functional>
#include <iostream>
#include <optional>
#include <vector>

#include "main.h"

AutonHelper::AutonHelper(const std::string& name, int r, int g, int b)
    : name(name), color{r, g, b} {}

void AutonHelper::addAuton(const std::string& autonName, std::function<void()> func, const std::string& autonNameDesc) {
  autons.emplace_back(autonName, func);
  autonsDesc.emplace_back(autonName, autonNameDesc);
}

std::string AutonHelper::getName() const {
  return name;
}

void AutonHelper::listAutons() const {
  std::cout << "Autons for " << name << " (RGB: " << color.r << ", " << color.g << ", " << color.b << "):\n";
  for (const auto& [autonName, _] : autons) {
    std::cout << "  " << autonName << "\n";
  }
}

// Returns the count of autonomous routines
size_t AutonHelper::getCount() const {
  return autons.size();
}

std::tuple<int, int, int> AutonHelper::getRGB() const {
  return std::make_tuple(color.r, color.g, color.b);
}

std::vector<std::pair<std::string, std::function<void()>>> AutonHelper::getAutons() const {
  return autons;
}

std::vector<std::pair<std::string, std::string>> AutonHelper::getAutonsDesc() const {
  return autonsDesc;
}

// Runs a specific auton function by name
bool AutonHelper::runAuton(const std::string& autonName) const {
  for (const auto& [name, func] : autons) {
    if (name == autonName) {
      std::cout << "Running " << name << " for " << this->name << ":\n";
      func();
      return true;
    }
  }
  std::cerr << "Auton '" << autonName << "' not found for " << this->name << "!\n";
  return false;
}

std::string AutonHelper::getAutonDesc(const std::string& autonName) const {
  for (const auto& [name, desc] : autonsDesc) {
    if (name == autonName) {
      return desc;
    }
  }
  return ":(";
}

std::vector<AutonHelper> autons;

std::vector<AutonHelper> utils::createAutons() {
  AutonHelper blue("Blue", 0,0,255);
  blue.addAuton("pos", auton::blue::pos,"Pos\nx - ring\nx - tops");
  blue.addAuton("neg", auton::blue::neg,"Neg\nx - ring\nx - tops");
  blue.addAuton("neg_wp", auton::blue::neg_wp,"Neg (WP) Win Point\nx - ring\nx - tops");
  blue.addAuton("neg_elim", auton::blue::neg_elim,"Neg Elim\nx - ring\nx - tops");

  AutonHelper red("Red", 255,0,0);
  red.addAuton("pos", auton::red::pos,"Pos\nx - ring\nx - tops");
  red.addAuton("neg", auton::red::neg,"Neg\nx - ring\nx - tops");
  red.addAuton("neg_wp", auton::red::neg_wp,"Neg (WP) Win Point\nx - ring\nx - tops");
  red.addAuton("neg_elim", auton::red::neg_elim,"Neg Elim\nx - ring\nx - tops");

  AutonHelper skills("Skills", 204,204,0);
  skills.addAuton("SkillsV3", auton::skills::skillsv3,"Skills V3\nI hate (mondays) skills....");

  autons = {blue, red, skills};
  return autons;
}

std::vector<AutonHelper> utils::getAutons() {
  return autons;
}