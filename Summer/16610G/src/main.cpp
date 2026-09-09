#include "includes.hpp"
#include "autonomous_selector.hpp"

using namespace pros;

/// Callback for center button press (currently unused)
void on_center_button() {}

/// Robot initialization
/// Sets up chassis calibration, LCD, motors, and starts the periodic task
void initialize()
{
    chassis.calibrate(); // Calibrate IMU and odometry

    // autonomousRoute{"team colour (red/blue)", "name of auton", "description", functionName},
    // autonomousRoute{"red", "2 Toggles", "a", toggles},

    autonSelect.setAutons(std::vector<autonomousRoute>{
        autonomousRoute{"red", "2 Toggles", "a", toggles},
        autonomousRoute{"red", "LeftAuton", "LEFT Auton", leftAuton},
        autonomousRoute{"red", "RightAuton", "RIGHT Auton", rightAuton}});
    autonSelect.setSkillsAuton(autonomousRoute{"red", "Skills", "Skills Auton", skills});
    autonSelect.start(); // Start autonomous selector task
    
    robotstate = 0;
    rightdrive.set_brake_mode_all(coast);
    leftdrive.set_brake_mode_all(coast);
    lift.set_brake_mode_all(hold);
    armmotor.set_brake_mode_all(hold);

    claw.set_value(true);

    pros::Task movement(movementFn, nullptr, "Lift");
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

    uint32_t matchStart = pros::millis(); // for vibrate after 1 minute 30 seconds

    // for setting brake mode to coast
    rightdrive.set_brake_mode_all(coast);
    leftdrive.set_brake_mode_all(coast);

    // main loop
    while (true)
    {   

        /*Controls:
            L2 - Intake
            L1 - Outtake
            R2 - Lift Down
            R1 - Lift Up

            UP - Vacant
            LEFT - Vacant
            RIGHT - Side Toggle 1
            DOWN - Claw Close

            X - Arm Up
            Y - Side Toggle 2
            B - Claw Open
            A - Arm Down
        */

        if (pros::millis() - matchStart >= 90000) // 1 minute 30 seconds
        {
            matchStart = pros::millis();
            master.rumble("_");
        }
        pros::delay(10);

        if (LEFT_NEW_PRESS) {

        master.clear();

        // // angular awr
        // double tot = 0;
        // for (double i = 9.99; i <= 180; i += 10) {
        // 	double target = chassis.getPose().theta + i;
        // 	chassis.turnToHeading(target, 1500);
        // 	delay(2000);
        // 	tot += target - chassis.getPose().theta;
        // }

        // delay(500);
        // master.print(0, 0, "%.5f", tot);
        // lcd::print(6, 0, "%.5f", tot);
        // delay(3000);
        
        // int tar = 180;
        // chassis.turnToHeading(tar, 3000);
        // delay(2500);
        // master.print(0, 0, "%.3f", tar - chassis.getPose().theta);
        // delay(3000);

        // lateral awr
        // double tot = 0;
        // for (double i = 8; i <= 32; i += 8) {
        // 	double target = chassis.getPose().y + i;
        // 	chassis.moveToPoint(0, target, 4000);
        // 	delay(4050);
        // 	master.print(0, 0, "%f", target-chassis.getPose().y);
        // 	tot += target-chassis.getPose().y;
        // }
        // master.print(2, 0, "%.2f", tot);
        // delay(5000);

        double tar = 24;
        int time = 4000;
        chassis.moveToPoint(0, tar, time);
        delay(time+100);
        master.print(0, 0, "%.2f", tar-chassis.getPose().y);
        delay(100);
        master.print(2, 0, "%.2f", chassis.getPose().y);
        }

        // if (LEFT_NEW_PRESS) {
        //     armPIDtarget(0);
        // }
        // if (RIGHT_NEW_PRESS) {
        //     armPIDtarget(90);
        // }
    }
}
   