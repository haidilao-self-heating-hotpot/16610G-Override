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

float liftHeight = 0.0;
float front_distance = 0.0;
float back_distance = 0.0;
float left_distance = 0.0;
float right_distance = 0.0;
float heading = 0.0;

void leftAuton()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // set pose at stack of pins on left side of toggle
    chassis.setPose(-60, -14, 322);

    lift.move(+110);
    chassis.moveToPoint(-53, -24, 2000, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});

    chassis.arcade(-40, 0);
    delay(400);
    lift.move(-110);
    delay(900);
    clawclamp.set_value(false);
    delay(100);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    lift.move(0);

    chassis.cancelMotion();
    chassis.arcade(95, 0);
    delay(900);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    delay(500);

    chassis.arcade(-80, 0);
    delay(400);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    delay(500);

    chassis.arcade(80, 0);
    delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    // need to reset position
    // chassis.setPose(x, y, 270);

    chassis.arcade(-80, 0);
    delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
}

void rightAuton()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    // set pose at stack of pins on left side of toggle
    chassis.setPose(-14, -60, 142);

    lift.move(+110);
    chassis.moveToPoint(-20, -52, 2500, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});

    delay(400);
    lift.move(-110);
    delay(1000);
    clawclamp.set_value(false);
    delay(100);
    lift.move(0);

    chassis.cancelMotion();
    chassis.arcade(95, 0);
    delay(900);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    delay(500);

    chassis.arcade(-80, 0);
    delay(400);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    delay(500);

    chassis.arcade(80, 0);
    delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    chassis.arcade(-80, 0);
    delay(1000);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    // chassis.arcade(80, 0);
    // delay(500);
    // chassis.arcade(0, 0);

    // chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);

    // chassis.arcade(80, 0);
    // delay(1000);
    // chassis.arcade(-80, 0);
    // delay(800);
    // chassis.arcade(80, 0);
    // delay(1000);
}

void soloawp()
{
}

void skills()
{


    // setting ze starting position
    chassis.setPose(-60, -15, 305);
    clawclamp.set_value(true);

    // toggle ze toggle once using front pull toggle
    chassis.moveToPoint(-63, -12.5, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40}, false);
    chassis.moveToPoint(-57, -12.5, 1000, {.forwards = false, .maxSpeed = 110, .minSpeed = 40}, false);


    // move to back to goal + score 1st pin
    liftPID(9);
    while (liftactive)
    {
        pros::delay(10);
    }
    delay(1000);
    moveTo(-54, -17.5, 800, 500, false, 100, 100, false);

    // score pin as you rotate
    chassis.arcade(-40, 0);
    chassis.turnToHeading(270, 1500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, true);
    liftPID(7.5);
    while (liftactive)
    {
        pros::delay(10);
    }
    delay(1000);
    clawclamp.set_value(false);
    delay(200);
    chassis.cancelMotion();
    chassis.arcade(0, 0);


    // pick up new pin + score 2nd pin 
    armPIDtarget(90);
    while (armactive)
    {
        pros::delay(10);
    }
    liftPID(6.5);
    while (liftactive)
    {
        pros::delay(10);
    }
    delay(1000);
    chassis.moveToPoint(-60, -23.5, 500, {.forwards = true, .maxSpeed = 110, .minSpeed = 40}, false);
    clawclamp.set_value(true);

    // move back to score
    liftPID(15.5);
    while (liftactive)
    {
        pros::delay(10);
    }
    delay(1000);
    chassis.moveToPoint(-55.5, -23.5, 600, {.forwards = false, .maxSpeed = 110, .minSpeed = 40}, false);
    armPIDtarget(-90);
    while (armactive)
    {
        pros::delay(10);
    }
    liftPID(14.5);
    while (liftactive)
    {
        pros::delay(10);
    }
    clawclamp.set_value(false);
    delay(500);

    // swing to face 90 degrees while swinging arm
    liftPID(21.5);
    chassis.turnToHeading(180, 1500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);    
    armPIDtarget(90);
    chassis.arcade(-80, 0);
    delay(200);
    chassis.cancelMotion();
    chassis.arcade(0, 0);
    chassis.turnToHeading(90, 1500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, true);
    liftPID(6.7);
    while (liftactive)
    {
        pros::delay(10);
    }   
    delay(200);
    chassis.arcade(-80, 0);
    delay(200);
    chassis.cancelMotion();
    chassis.arcade(0, 0);


    // reset position
    chassis.turnToHeading(90, 1000, {.maxSpeed = 100, .minSpeed = 40}, false);
    right_distance = rightdist.get_distance() / 25.4;
    back_distance = backdist.get_distance() / 25.4;
    heading = imu.get_heading();
    chassis.setPose(back_distance - 62.5, back_distance - 62.5, heading);


    // grab top pin between red quadrants + score
    moveTo(-35, -23.5, 500, 100, true, 500, 1000, false);
    chassis.moveToPoint(-31, -23.5, 1000, {.forwards = true, .maxSpeed = 50, .minSpeed = 20}, false);
    

    // grab bottom pin between red quadrants + score
    moveTo(-47, -47, 500, 800, true, 500, 1000, false);
    chassis.moveToPoint(-47, -38.5, 1000, {.forwards = true, .maxSpeed = 50, .minSpeed = 20}, false);


    // move to matchloader
    moveTo(-58, -59, 500, 1500, true, 100, 100, true);
    delay(1000);
    armPIDtarget(90);
    while (armactive)
    {
        pros::delay(10);
    }
    liftPID(0);
    while (liftactive)
    {
        pros::delay(10);
    }
    clawclamp.set_value(false);
    delay(500);

    // grab pin
    moveTo(-63, -59, 500, 1000, true, 100, 80, false);
    delay(200);
    clawclamp.set_value(true);

    // loop to score pins + cups in red right alliance goal
    liftHeight = 8.5;
    for (int runNumber = 0; runNumber <= 6; runNumber++)
    {
        // move back
        chassis.moveToPoint(-58, -59, 700, {.forwards = false, .maxSpeed = 80, .minSpeed = 30}, false);

        // move to the goal
        moveTo(-31, -50, 1000, 2200, false, 50, 80, true);
        liftPID(liftHeight);
        delay(200);
        armPIDtarget(-90);
        while (armactive)
        {
            pros::delay(10);
        }

        // score pin
        chassis.arcade(-30, 0);
        liftPID(liftHeight - 0.8);
        while (liftactive)
        {
            pros::delay(10);
        }
        clawclamp.set_value(false);
        liftPID(liftHeight - 1);
        while (liftactive)
        {
            pros::delay(10);
        }

        // move down to align to matchloader, swing claw forward, and lower lift
        clawclamp.set_value(false);
        chassis.moveToPoint(-58, -59, 2000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, true);
        armPIDtarget(90);
        liftPID(0);
        while (liftactive)
        {
            pros::delay(10);
        }

        // go to matchloader and grab pin
        moveTo(-63, -59, 700, 1000, true, 100, 100, false);
        clawclamp.set_value(true);

        liftHeight += 7;

    }

    // reset lift height value
    liftHeight = 8.5;
    liftPID(0);

    // toggle red right alliance toggle
    chassis.turnToHeading(180, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, false);
    chassis.arcade(-40, 0);
    delay(200);
    moveTo(-8, -63, 800, 1400, true, 100, 100, false);  


    // park
    chassis.moveToPoint(-8, -26, 2000, {.forwards = false, .maxSpeed = 120, .minSpeed = 70}, false);

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