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

    // autonomousRoute{"team colour (red/blue)", "name of auton", "description", functionName},
    // autonomousRoute{"red", "2 Toggles", "a", toggles},

    autonSelect.setAutons(std::vector<autonomousRoute>{
        autonomousRoute{"red", "2 Toggles", "a", toggles},
        autonomousRoute{"red", "LeftAuton", "LEFT Auton", leftAuton},
        autonomousRoute{"red", "RightAuton", "RIGHT Auton", rightAuton}});
    autonSelect.setSkillsAuton(autonomousRoute{"red", "Skills", "Skills Auton", skills});
    autonSelect.start(); // Start autonomous selector task

    rightdrive.set_brake_mode_all(hold);
    leftdrive.set_brake_mode_all(hold);
    lift.set_brake_mode_all(hold);

    matchloaderpiston.set_value(false);
    clawclamp.set_value(true);
    clawswing.set_value(true);
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
    // // reset pistons
    // matchloaderpiston.set_value(true);
    // clawclamp.set_value(false);
    // clawswing.set_value(false);

    // for vibrate after 1 minute 30 seconds
    int timer = 0;

    // for setting brake mode to coast
    rightdrive.set_brake_mode_all(coast);
    leftdrive.set_brake_mode_all(coast);
    bool clawClampState = false;
    bool matchloadingState = false;

    // main loop
    while (true)
    {

        // Drivetrain
        int forward = LEFT_Y;
        int turning = RIGHT_X;
        chassis.arcade(turning, -forward, /* true */ false, 0.5);

        // int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
        // int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
        // leftdrive.move(dir - turn);                      // Sets left motor voltage
        // rightdrive.move(dir + turn);

        // Cascade Lift
        if (R1_HELD)
        {
            lift.move(60);
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
        else if (L2_HELD)
        {
            intake.move(-127);
        }
        else
        {
            intake.move(0);
        }

        // Claw clamp piston, down is open b is closed
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

        // Match loader piston
        if (X_NEW_PRESS)
        {
            matchloadingState = !matchloadingState;
            matchloaderpiston.set_value(matchloadingState);
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