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
        autonomousRoute{"red", "LeftAutonOnePin", "LEFT Auton One Pin", leftAuton},
        autonomousRoute{"red", "RightAutonOnePin", "RIGHT Auton One Pin", rightAuton}});
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
    autonSelect.runAuton(); // Use autonomous selector
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
    // for vibrate after 1 minute 30 seconds
    int timer = 0;
    bool clawClampState = false;
    while (true)
    {

        // Drivetrain
        int forward = LEFT_Y;
        int turning = RIGHT_X;
        chassis.arcade(forward, turning, 0.75);

        // Cascade Lift
        if (R1_HELD)
        {
            lift.move(127);
        }
        else if (R2_HELD)
        {
            lift.move(-127);
        }
        else
        {
            lift.move(0);
        }

        // Intake
        if (L1_HELD)
        {
            intake.move(127);
        }
        else if (LEFT_HELD)
        {
            intake.move(40);
        }
        else if (L2_HELD)
        {
            intake.move(-127);
        }
        else
        {
            intake.move(0);
        }

        // Claw, down is open b is closed yay
        if (DOWN_NEW_PRESS && !clawClampState)
        {
            clawclamp.set_value(true);
            clawClampState = true;
        }

        if (B_NEW_PRESS && clawClampState)
        {
            clawclamp.set_value(false);
            clawClampState = false;
        }

        if (A_NEW_PRESS)
        {
            clawswing.toggle();
        }

        timer += 1;
        if (timer == 9000) // 1 minute 30 seconds at 10ms intervals
        {
            // Vibrate the controller
            timer = 0;
            master.rumble("_");
        }
        pros::delay(10);
    }
}