#include "gobals.hpp"

// Drive setup
ez::Drive chassis({16,-17,-18}, {-12,13,14}, 20, 2.75, 450);

// Controller setup
pros::Controller masterController(CONTROLLER_MASTER);

// Motors
pros::Motor intakeMotor(4, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
pros::Motor twoBar(-6, pros::v5::MotorGear::red, pros::v5::MotorUnits::degrees);

// Rations
pros::Rotation twoBarRot(1);

// 3 Wire ports
pros::adi::DigitalOut goalGrab('A');
pros::adi::DigitalOut ringGrab('H');
pros::adi::DigitalIn autonButton('C');

// PID
ez::PID liftPID(0.45, 0, 0, 0, "Lift");