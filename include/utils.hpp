#pragma once
#include "main.h"


class AutonHelper {
 public:
  // Constructor
  AutonHelper(const std::string& name, int r, int g, int b, int aType);

  // Adds an autonomous function
  void addAuton(const std::string& autonName, std::function<void()> func, const std::string& autonNameDesc);

  int getType() const;

  // Prints all autonomous routines
  void listAutons() const;

  // Returns the count of autonomous routines
  size_t getCount() const;

  // Runs a specific autonomous routine by name
  bool runAuton(const std::string& autonName) const;

  std::string getAutonDesc(const std::string& autonName) const;

  std::tuple<int, int, int> getRGB() const;

  std::string getName() const;

  std::vector<std::pair<std::string, std::function<void()>>> getAutons() const;
  std::vector<std::pair<std::string, std::string>> getAutonsDesc() const;

 private:
  // Nested struct for RGB color
  struct Color {
    int r, g, b;
  };

  std::string name;                                                   // Name of the auton (e.g., "Blue", "Red", "Skills")
  int aType;
  Color color;                                                        // RGB color associated with this auton
  std::vector<std::pair<std::string, std::function<void()>>> autons;  // Auton names and functions
  std::vector<std::pair<std::string, std::string>> autonsDesc;        // Auton names and desc
};


namespace utils {
std::vector<AutonHelper> createAutons();
std::vector<AutonHelper> getAutons();

void set_intake(int speed);
void intake_task();
}
