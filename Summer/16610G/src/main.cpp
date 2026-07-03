#include "includes.hpp"
#include "autonomous_selector.hpp"

using namespace pros;

/// Callback for center button press (currently unused)
void on_center_button() {}

/// Robot initialization
/// Sets up chassis calibration, LCD, motors, and starts the periodic task
void initialize()
{
    // autonSelect.start();
    chassis.calibrate(); // Calibrate IMU and odometry

    autonSelect.setAutons(std::vector<autonomousRoute>{
        autonomousRoute{"red", "2 Toggles", "a", toggles},
    });
    autonSelect.setSkillsAuton(autonomousRoute{"red", "Skills", "Skills Auton", skills});
    autonSelect.start(); // Start autonomous selector task

    rightdrive.set_brake_mode_all(coast);
    leftdrive.set_brake_mode_all(coast);
    lift.set_brake_mode_all(hold);

}

/// Called when robot is disabled
void disabled() {}

/// Pre-competition initialization
void competition_initialize() {}

/// Autonomous routine - runs selected autonomous strategy
void autonomous()
{
    autonSelect.runAuton();  // Use autonomous selector
    // chassis.setPose(0, 0, 0);
    // chassis.moveToPoint(0, 24, 10000);
    // right();  // Alternative right side routine
    // soloAWP();  // Run solo AWP (Autonomous Win Point) strategy
    // right2();  // Alternative strategy
    // skills(); // Run skills routine
}

/// Main driver control loop
void opcontrol()
{
    while (true) {

        // Drivetrain
        int forward = LEFT_Y;
        int turning = RIGHT_X;
        chassis.arcade(forward, turning, 0.75);

        // Cascade Lift
        if (R2_HELD) 
        {
            lift.move(127);
        } 
        else if (R1_HELD) 
        {
            lift.move(-127);
        } 
        else 
        {
            lift.move(0);
        }

        // Intake
        if (L2_HELD) 
        {
            intake.move(127);
        } 
        else if (L1_HELD) 
        {
            intake.move(-127);
        }
        else 
        {
            intake.move(0);
        }

        // Claw
        if (DOWN_NEW_PRESS) 
        {
            clawclamp.toggle();
        }

        if (B_NEW_PRESS) 
        {
            clawswing.toggle();
        }

        pros::delay(10);
    }
}