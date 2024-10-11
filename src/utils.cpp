#include "main.h"
#include "utils.hpp"
#include <stdio.h>

bool utils::cataGotoAngle(int angle, int speed, bool stopAtWeridAngle, pros::Rotation rot, pros::Motor motor, int timeout = 5) {
    int cataAngle = rot.get_angle();
    int resetValue = 35000;
    if (cataAngle > resetValue) cataAngle = 0; // When the roto is at 35500 we are at the top.
    if (angle < cataAngle) return false; // Unable to get to that angle as we have already gone past it.
    bool notThere = true;

    std::time_t start = std::time(nullptr);
    while (notThere) {
        std::time_t end = std::time(nullptr);
        if (end - start > timeout) {
            // This will cancel the function if the angle is not meet within X seconds
            // No it doesn't work.
            motor.brake();
            notThere = false;
            return true;
        }

        int cataAngle = rot.get_angle();
        // printf("AngleGoto: %ld \n", cataAngle);
        if (cataAngle > resetValue) {
            cataAngle = 0;
        }

        if (stopAtWeridAngle) {
            if (cataAngle < 2000) { // I don't remeber what this does but whatever it is I can assure you this is needded
                motor.brake();
                notThere = false;
                return true;
            }
        }

        if (cataAngle < angle) { // 5400
            motor.move(speed);
        }

        if (angle < cataAngle) {
            motor.brake();
            notThere = false;
            return true;
        }
        pros::delay(ez::util::DELAY_TIME);
    }
    return true;
}