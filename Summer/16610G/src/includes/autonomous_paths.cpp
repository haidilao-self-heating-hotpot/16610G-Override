#include "autonomous_paths.hpp"
#include "includes.hpp"

/* EACH PIN ≈ 7 IN (MORE LIKE 6.7 BUT ITS OOKAY)*/
/* EACH CUP ≈ 7 IN (MORE LIKE 6.7 BUT ITS OOKAY) */
/* EACH CUP + PIN ≈ 10 IN */


/* HEIGHTS NEEDED TO SCORE PIN */
/* ADD 0.5 IN MORE FOR AUTONOMOUS */

// ALLIANCE GOALS //
// 1 PIN = 7.5 IN
// 2 PINS = 14.5 IN
// 3 PINS = 21.5 IN
// 4 PINS = 28.5 IN
// 5 PINS = 35.5 IN
// 6 PINS = 42.5 IN

// NEUTRAL GOALS //
// 1 PIN = 10 IN
// 2 PINS = 17 IN
// 3 PINS = 24 IN
// 4 PINS = 31 IN
// 5 PINS  = 38 IN



int angMinSpeed = 20;
float angEarlyExitRange = 1;

float latMinSpeed = 20;
float latEarlyExitRange = 1;

double x_value = 0;
double y_value = 0;
double distance = 0;

void moveTo(double x, double y, int t1, int t2, bool forward, int angMaxSpeed, float latMaxSpeed, bool asyncValue)
{
    chassis.turnToPoint(x, y, t1, {.forwards = forward, .maxSpeed = angMaxSpeed, .minSpeed = angMinSpeed, .earlyExitRange = angEarlyExitRange}, asyncValue);
    chassis.moveToPoint(x, y, t2, {.forwards = forward, .maxSpeed = latMaxSpeed, .minSpeed = latMinSpeed, .earlyExitRange = latEarlyExitRange}, asyncValue);
}

void liftMove(float liftHeight, float time)
{
    liftPIDtarget(liftHeight);
    for (int i = 0; i < time; i++)
    {
        pros::delay(100);
    }

}

float liftHeight = 0.0;
float front_distance = 0.0;
float back_distance = 0.0;
float left_distance = 0.0;
float right_distance = 0.0;
float heading = 0.0;

void leftAutonv1()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // set pose at stack of pins on left side of toggle
    //chassis.setPose(-60, 12.3, 318.6);

    // move to cup to place preload in 
    liftPIDtarget(11);
    pros::delay(500);
    chassis.moveToPoint(-61.5, 20, 500, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, true);
    pros::delay(300);
    claw.set_value(false);
    pros::delay(100);

    // move back a little and lower claw to grab 1st pin
    chassis.moveToPoint(-60.5, 13, 500, {.forwards = true, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, true);
    liftMove(6.5, 13);

    // move to 1st pin to grab it
    chassis.moveToPoint(61.5, 14, 500, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, false);
    claw.set_value(true);
    pros::delay(100);

    // // move back with slight curve to goal to score 1st pin
    // chassis.moveToPoint(-53, 8, 500, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1}, true);
    // pros::delay(200);
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    // chassis.turnToPoint(-50.5, 8, 1000, {.forwards = false, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    // chassis.moveToPoint(-50.5, 8, 500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1}, true);
    // liftMove(11, 10);
    // pros::delay(100);

    // // score 1st pin
    // liftPIDtarget(10);    
    // pros::delay(100);
    // claw.set_value(false);

    // // move out to go grab 2nd pin
    // chassis.moveToPoint(-53, 8, 500, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1}, true);
    // liftMove(6.5, 10);
    // chassis.turnToPoint(-61, 16, 1000, {.forwards = false, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);

    // // move to 2nd pin to grab it
    // chassis.moveToPoint(-61, 16, 500, {.forwards = false, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1}, false);
    // claw.set_value(true);
    // pros::delay(100);

    // // move back with slight curve to goal to score 2nd pin
    // liftPIDtarget(18);
    // chassis.moveToPoint(-53, 8, 500, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1}, true);
    // pros::delay(200);
    // chassis.turnToPoint(-50.5, 8, 1000, {.forwards = false, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    // chassis.moveToPoint(-50.5, 8, 700, {.forwards = false, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1}, true);

    // // score 2nd pin
    // liftPIDtarget(17);
    // pros::delay(100);
    // claw.set_value(false);
    // pros::delay(100);

    // // toggle ze toggle
    // chassis.moveToPoint(-65, 0, 1200, {.forwards = true, .maxSpeed = 100, .minSpeed = 30}, false);
    // liftPIDtarget(6.5);

    // // move to middle pin 
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // chassis.moveToPoint(-35, 0, 1300, {.forwards = false, .maxSpeed = 120, .minSpeed = 40}, false);
    // pros::delay(100);
    // chassis.moveToPoint(-32.5, 0, 800, {.forwards = false, .maxSpeed = 40, .minSpeed = 10}, false);
    // claw.set_value(true);

    // // score pin in middle
    // liftPIDtarget(22);
    // chassis.moveToPoint(0, 0, 1000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, false);
    // liftPIDtarget(21);
    // pros::delay(100);
    // claw.set_value(false);

    // // grab top pin in between two alliance quadrants
    // liftPIDtarget(0);
    // chassis.moveToPoint(-17, 0, 800, {.forwards = true, .maxSpeed = 100}, false);
    // // liftStopPiston.set_value(true);
    // liftPIDtarget(15);
    // chassis.turnToPoint(-19.5, -13.5, 1000, {.forwards = true, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    // if (liftactive)
    // {
    //     pros::pros::delay(300);
    // }
    // armPIDtarget(90);
    // chassis.moveToPoint(-19.5, -13.5, 1200, {.forwards = true, .maxSpeed = 120, .minSpeed = 50, .earlyExitRange = 1}, false);
    // if (armactive)
    // {
    //     pros::pros::delay(300);
    // }
    // liftPIDtarget(6.5);
    // chassis.moveToPoint(-21.5, -15.5, 800, {.forwards = true, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, false);
    // if (liftactive)
    // {
    //     pros::pros::delay(300);
    // }
    // claw.set_value(true);
    
    // // score pin
    // liftPIDtarget(15);
    // chassis.moveToPoint(-32, -34, 1000, {.forwards = false, .maxSpeed = 120, .minSpeed = 40}, false);
    // armPIDtarget(-90);
    // moveTo(-40.5, -29, 1000, 1000, false, 100, 120, false);
    // liftPIDtarget(6.5);
    // claw.set_value(false);

    // // turn to go to 5th pin
    // chassis.swingToHeading(180, DriveSide::LEFT, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    // liftPIDtarget(15);
    // chassis.turnToPoint(-47, -37, 500, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, false);
    // if (liftactive)
    // {
    //     pros::pros::delay(300);
    // }
    // armPIDtarget(90);
    // chassis.moveToPoint(-47, -37, 500, {.forwards = true, .maxSpeed = 100, .minSpeed = 20, .earlyExitRange = 1}, false);
    // if (armactive)
    // {
    //     pros::pros::delay(300);
    // }
    // liftPIDtarget(6.5);
    // if (liftactive)
    // {
    //     pros::pros::delay(600);
    // }
    // chassis.moveToPoint(-47, -39, 500, {.forwards = true, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1}, false);
    // claw.set_value(true);

    // // score pin
    // liftPIDtarget(15);
    // if (liftactive)
    // {
    //     pros::pros::delay(600);
    // }
    // armPIDtarget(-90);
    // if (armactive)
    // {
    //     pros::pros::delay(900);
    // }
    // liftPIDtarget(18);
    // chassis.moveToPoint(-32, -34, 1000, {.forwards = false, .maxSpeed = 120, .minSpeed = 40}, false);
    // liftPIDtarget(17);
    // pros::delay(100);
    // claw.set_value(false);


}

void leftAuton() {
    // start robot by aligning to tile (set pose is in initialize, drag to correct starting position)
    claw.extend();

    // toggle the toggle once using front pull toggle
    rightdrive.move(100);
    pros::delay(500);
    rightdrive.move(-127);
    pros::delay(300);
    rightdrive.move(0);

    // move to back to goal + score the 1st pin
    liftPIDtarget(9);
    chassis.turnToPoint(-53, -15, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 2.5}, false);
    pros::delay(500);
    chassis.tank(-50, -50);
    pros::delay(500);
    claw.retract();
    pros::delay(1000);

    // turn to route and move to 2nd pin
    chassis.moveToPoint(-56, -13, 500, {.forwards = true, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 1});
    liftPIDtarget(6);
    chassis.turnToHeading(270, 500, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 2.5});
    chassis.moveToPoint(-22, -13, 1000, {.forwards = false, .maxSpeed = 80});

    //grab 2nd pin
    chassis.turnToHeading(0, 500, {.maxSpeed = 80});
    chassis.moveToPoint(-20, -20, 1500, {.forwards = false, .maxSpeed = 80});
    claw.extend();
    liftPIDtarget(14.5);
    pros::delay(500);

    //score 2nd pin
    chassis.moveToPoint(-20, -26, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.turnToHeading(90, 500, {.maxSpeed = 100});
    chassis.moveToPoint(-38, -23, 1000, {.forwards = false, .maxSpeed = 100}, false);
    chassis.tank(-50, -50);
    delay(500);
    chassis.tank(0,0);
    claw.retract();

    // go to 3rd pin
    chassis.setPose(-38, -23, 90);
    chassis.moveToPoint(-30, -23, 1000, {.forwards = true, .maxSpeed = 100}, false);
    liftPIDtarget(6);
    chassis.turnToPoint(-46, -46, 500, {.forwards = false, .maxSpeed = 100});
    chassis.moveToPoint(-43.5, -41.5, 1000, {.forwards = false, .maxSpeed = 60}, false);
    claw.extend();
    liftPIDtarget(21.5);

    // score 3rd pin
    delay(500);
    chassis.moveToPoint(-46, 46, 1000, {.forwards = false, .maxSpeed = 60});
    chassis.turnToHeading(180, 500, {.maxSpeed = 80});
    chassis.moveToPoint(-52.5, -25, 1000, {.forwards = false, .maxSpeed = 80});
    claw.retract();
    delay(500);
    chassis.tank(0,0);
}

void rightAuton()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // set pose at stack of pins on left side of toggle
    chassis.setPose(-14, -60, 142);

    lift.move(+110);
    chassis.moveToPoint(-20, -52, 2500, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});

    pros::delay(400);
    lift.move(-110);
    pros::delay(1000);
    claw.set_value(false);
    pros::delay(100);
    lift.move(0);

    chassis.cancelMotion();
    chassis.arcade(95, 0);
    pros::delay(900);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    pros::delay(500);

    chassis.arcade(-80, 0);
    pros::delay(400);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    pros::delay(500);

    chassis.arcade(80, 0);
    pros::delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    chassis.arcade(-80, 0);
    pros::delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    // chassis.arcade(80, 0);
    // pros::delay(500);
    // chassis.arcade(0, 0);

    // chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);

    // chassis.arcade(80, 0);
    // pros::delay(1000);
    // chassis.arcade(-80, 0);
    // pros::delay(800);
    // chassis.arcade(80, 0);
    // pros::delay(1000);
}

void soloawp()
{
}

void skills()
{
    // start robot by aligning to tile (set pose is in initialize, drag to correct starting position)
    claw.extend();

    // toggle the toggle once using front pull toggle
    rightdrive.move(100);
    pros::delay(500);
    rightdrive.move(-127);
    pros::delay(300);
    rightdrive.move(0);

    // move to back to goal + score the 1st pin
    liftPIDtarget(9);
    chassis.turnToPoint(-53, -15, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 2.5}, false);
    pros::delay(500);
    chassis.tank(-50, -50);
    pros::delay(500);
    claw.retract();
    pros::delay(1000);

    // turn to route and move to 2nd pin
    chassis.moveToPoint(-56, -13, 500, {.forwards = true, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 1});
    liftPIDtarget(6);
    chassis.turnToHeading(270, 500, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 2.5});
    chassis.moveToPoint(-22, -13, 1000, {.forwards = false, .maxSpeed = 80});

    //grab 2nd pin
    chassis.turnToHeading(0, 500, {.maxSpeed = 80});
    chassis.moveToPoint(-20, -20, 1500, {.forwards = false, .maxSpeed = 80});
    claw.extend();
    liftPIDtarget(14.5);
    pros::delay(500);

    //score 2nd pin
    chassis.moveToPoint(-20, -26, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.turnToHeading(90, 500, {.maxSpeed = 100});
    chassis.moveToPoint(-38, -23, 1000, {.forwards = false, .maxSpeed = 100}, false);
    chassis.tank(-50, -50);
    delay(500);
    chassis.tank(0,0);
    claw.retract();

    // go to 3rd pin
    chassis.setPose(-38, -23, 90);
    chassis.moveToPoint(-30, -23, 1000, {.forwards = true, .maxSpeed = 100}, false);
    liftPIDtarget(6);
    chassis.turnToPoint(-46, -46, 500, {.forwards = false, .maxSpeed = 100});
    chassis.moveToPoint(-43.5, -41.5, 1000, {.forwards = false, .maxSpeed = 60}, false);
    claw.extend();
    liftPIDtarget(21.5);

    // score 3rd pin
    delay(500);
    chassis.moveToPoint(-46, 46, 1000, {.forwards = false, .maxSpeed = 60});
    chassis.turnToHeading(180, 500, {.maxSpeed = 80});
    chassis.moveToPoint(-52.5, -25, 1000, {.forwards = false, .maxSpeed = 80});
    claw.retract();
    delay(500);
    chassis.tank(0,0);

    //----completed

    // // move to matchloader
    // // moveTo(-58, -59, 500, 1500, true, 100, 100, true);
    // pros::delay(1000);
    // armPIDtarget(90);
    // while (armactive)
    // {
    //     pros::pros::delay(10);
    // }
    // liftPIDtarget(0);
    // while (liftactive)
    // {
    //     pros::pros::delay(10);
    // }
    // claw.set_value(false);
    // pros::delay(500);

    // // grab pin
    // // moveTo(-63, -59, 500, 1000, true, 100, 80, false);
    // pros::delay(200);
    // claw.set_value(true);

    // // loop to score pins + cups in red right alliance goal
    // // liftHeight = 8.5;
    // for (int runNumber = 0; runNumber <= 6; runNumber++)
    // {
    //     // move back
    //     chassis.moveToPoint(-58, -59, 700, {.forwards = false, .maxSpeed = 80, .minSpeed = 30}, false);

    //     // move to the goal
    //     // moveTo(-31, -50, 1000, 2200, false, 50, 80, true);
    //     liftPIDtarget(liftHeight);
    //     pros::delay(200);
    //     armPIDtarget(-90);
    //     while (armactive)
    //     {
    //         pros::pros::delay(10);
    //     }

    //     // score pin
    //     chassis.arcade(-30, 0);
    //     liftPIDtarget(liftHeight - 0.8);
    //     while (liftactive)
    //     {
    //         pros::pros::delay(10);
    //     }
    //     claw.set_value(false);
    //     liftPIDtarget(liftHeight - 1);
    //     while (liftactive)
    //     {
    //         pros::pros::delay(10);
    //     }

    //     // move down to align to matchloader, swing claw forward, and lower lift
    //     claw.set_value(false);
    //     chassis.moveToPoint(-58, -59, 2000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, true);
    //     armPIDtarget(90);
    //     liftPIDtarget(0);
    //     while (liftactive)
    //     {
    //         pros::pros::delay(10);
    //     }

    //     // go to matchloader and grab pin
    //     // moveTo(-63, -59, 700, 1000, true, 100, 100, false);
    //     claw.set_value(true);

    //     liftHeight += 7;

    // }

    // // reset lift height value
    // liftHeight = 8.5;
    // liftPIDtarget(0);

    // // toggle red right alliance toggle
    // chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    // chassis.arcade(-40, 0);
    // pros::delay(200);
    // // moveTo(-8, -63, 800, 1400, true, 100, 100, false);  

    // // park
    // chassis.moveToPoint(-8, -26, 2000, {.forwards = false, .maxSpeed = 120, .minSpeed = 70}, false);

}


void sawp()
{

}

void test()
{

}

void toggles()
{

}