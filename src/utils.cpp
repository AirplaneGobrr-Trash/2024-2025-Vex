#include "utils.hpp"
#include <stdio.h>

#include "main.h"

bool utils::cataGotoAngle(int angle, int speed, bool stopAtWeridAngle, pros::Rotation rot, pros::Motor motor, int timeout = 5) {
  int cataAngle = rot.get_angle();
  int resetValue = 35000;
  if (cataAngle > resetValue)
    cataAngle = 0;  // When the roto is at 35500 we are at the top.
  bool notThere = true;

  if (speed > 0) {
    if (angle < cataAngle)
      return false;
  } else if (speed < 0) {
    if (angle > cataAngle)
      return false;
  }

  while (notThere) {
    // Override
    if (master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_X)) {
      motor.brake();
      notThere = false;
      return true;
    }

    int cataAngle = rot.get_angle();
    // printf("AngleGoto: %ld \n", cataAngle);
    if (cataAngle > resetValue) {
      cataAngle = 0;
    }

    if (speed > 0) {  // Positive speed
      if (cataAngle < angle) {
        motor.move(speed);
      } else {
        motor.brake();
        notThere = false;
        return true;
      }
    } else if (speed < 0) {  // Negative speed

      if (cataAngle > angle) {
        motor.move(speed);
      } else {
        motor.brake();
        notThere = false;
        return true;
      }
    }
    pros::delay(ez::util::DELAY_TIME);
  }
  return true;
}