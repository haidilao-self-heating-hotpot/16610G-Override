#include "includes.hpp"

void movementFn(void* param) {
    uint32_t now = pros::millis();
    while (true) {

        int timer = millis();
        int togglestart1 = 0;
        int togglestart2 = 0;

        /* Robot Scoring State 
            1 - Manual
            2 - Shared Goals
            3 - Alliance Goals
        */

        if (UP_NEW_PRESS) {
            robotstate = (robotstate % 3) + 1;
        }

        //Manual Mode

        if (robotstate == 1) {
            master.print(1, 0, "Manual Control");
        }

        //Shared Goals Mode
        if (robotstate == 2) {
            master.print(1, 0, "Shared Goals");
            
            if (R1_NEW_PRESS || R2_NEW_PRESS) {
                level += 1;
                liftPIDtarget(3.25 + 7 * level);
                armPIDtarget(0);
            }
            if (claw.is_extended() && LEFT_Y > 70) {
                level = 0;
                liftPIDtarget(6);
            }
        }

        if (robotstate == 3) {
            master.print(1, 0, "Alliance Goals");

            if (R1_NEW_PRESS || R2_NEW_PRESS) {
                level += 1;
                liftPIDtarget(3.25 + 7 * level);
                armPIDtarget(0);
            }
            if (claw.is_extended() && LEFT_Y > 70) {
                level = 0;
                liftPIDtarget(6);
            }
        }

        //Lift and Arm
        liftPIDupdate();
        armPIDupdate();

        //Drivetrain
        int forward = LEFT_Y;
        int turning = RIGHT_X;
        chassis.arcade(forward, turning, 0.54);

        //Intake Mode
        if (L2_NEW_PRESS) {
            liftPIDtarget(15);
            armPIDtarget(55);
        }

        //Intake
        if (L2_HELD) {
            intake.move(127);
        } else if (L1_HELD) {
            intake.move(-127);
        } else {
            intake.move(0);
        }

        //Side Toggle
        if (Y_NEW_PRESS) {
            sidetoggle1.extend();
            togglestart1 = timer;
        }

        if (timer - togglestart1 > 50) {
            sidetoggle1.retract();
        }

        if (RIGHT_NEW_PRESS) {
            sidetoggle2.extend();
            togglestart2 = timer;
        }

        if (timer - togglestart2 > 50) {
            sidetoggle2.retract();
        }

        //Claw
        if (DOWN_NEW_PRESS) {
            claw.extend();
        }

        if (B_NEW_PRESS) {
            claw.retract();
        }

        //Wedges

        pros::Task::delay_until(&now, 10);
    }
}

