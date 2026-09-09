#include "autonomous_paths.hpp"
#include "includes.hpp"

/* HEIGHTS OF PINS */
/* ADD 0.5 IN MORE FOR AUTONOMOUS */

// ALLIANCE GOALS //
// 1 PIN = 7.5 IN
// 2 PINS = 14.5 IN
// 3 PINS = 21.5 IN
// 4 PINS = 28.5 IN
// 5 PINS = 35.5 IN
// 6 PINS = 42.5 IN

// NEUTRAL GOALS //
// 1 PIN = 12 IN
// 2 PINS = 19 IN
// 3 PINS = 26 IN
// 4 PINS = 33 IN
// 5 PINS  = 40 IN

int angMinSpeed = 20;
float angEarlyExitRange = 1;

float latMinSpeed = 20;
float latEarlyExitRange = 1;

double x_value = 0;
double y_value = 0;
double distance = 0;

void moveTo(double x, double y, int t1, int t2, bool b1, bool b2, int angMaxSpeed, float latMaxSpeed, bool asyncValue)
{
    chassis.turnToPoint(x, y, t1, {.forwards = b1, .maxSpeed = angMaxSpeed, .minSpeed = angMinSpeed, .earlyExitRange = angEarlyExitRange}, asyncValue);
    chassis.moveToPoint(x, y, t2, {.forwards = b2, .maxSpeed = latMaxSpeed, .minSpeed = latMinSpeed, .earlyExitRange = latEarlyExitRange}, asyncValue);
}

float liftHeight = 0.0;

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

    // move to goal + score
    delay(1000);
    moveTo(-54, -17.5, 800, 500, false, false, 100, 100, false);

    // score pin as you rotate
    chassis.arcade(-40, 0);
    chassis.turnToHeading(270, 1500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, true);
    delay(1000);
    clawclamp.set_value(false);
    delay(200);
    chassis.cancelMotion();
    chassis.arcade(0, 0);

    // pick up new pin
    clawswing.set_value(true);
    delay(1000);
    chassis.moveToPoint(-60, -23.5, 500, {.forwards = true, .maxSpeed = 110, .minSpeed = 40}, false);
    clawclamp.set_value(true);

    // move back to score
    delay(1000);
    chassis.moveToPoint(-55.5, -23.5, 600, {.forwards = false, .maxSpeed = 110, .minSpeed = 40}, false);
    clawswing.set_value(false);
    chassis.turnToHeading(180, 1500, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40}, true);
    delay(1000);
    clawclamp.set_value(false);

    // score a pin in bottom quadrant from matchloader and push pin out of way
    chassis.moveToPoint(-50, -40, 1000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, false);
    intake.move(-127);
    chassis.moveToPoint(-45, -59, 1000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, false);
    
    // move to matchloader
    moveTo(-58, -59, 500, 1000, true, true, 100, 100, false);
    delay(1000);
    clawswing.set_value(true);
    clawclamp.set_value(true);
    delay(500);

    // grab pin
    moveTo(-63, -59, 500, 1000, true, true, 100, 80, true);
    delay(500);
    
    // loop to score pins + cups in red right alliance goal
    liftHeight = 8.5;
    for (int runNumber = 0; runNumber <= 6; runNumber++)
    {
        // move back
        chassis.moveToPoint(-58, -59, 700, {.forwards = false, .maxSpeed = 80, .minSpeed = 30}, false);

        // move to the goal
        moveTo(-31, -50, 1000, 2200, false, false, 50, 80, false);
        clawswing.set_value(false);

        // score pin
        chassis.arcade(-30, 0);
        clawclamp.set_value(false);

        clawswing.set_value(false);
        chassis.moveToPoint(-58, -59, 2000, {.forwards = true, .maxSpeed = 100, .minSpeed = 40}, true);

    }

}

void sawp()
{
}

void test()
{ 
}

void toggles()
{
    for (int i = 0; i < 2; i++)
    {

    chassis.arcade(120, 0);
    delay(1500);
    chassis.arcade(0, 0);
    chassis.cancelMotion();

    chassis.arcade(-100, 0);
    delay(800);
    chassis.arcade(0, 0);
    chassis.cancelMotion();

    }

    chassis.arcade(-100, 0);
    delay(800);
    chassis.arcade(0, 0);
    chassis.cancelMotion();
}