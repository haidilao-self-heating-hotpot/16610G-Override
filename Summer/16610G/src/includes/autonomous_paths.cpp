#include "autonomous_paths.hpp"
#include "includes.hpp"

int angmaxspeed = 100;
int angminspeed = 40;
float angearlyexitrange = 1;

float latmaxspeed = 110;
float latminspeed = 40;
float latearlyexitrange = 1;

void moveTo(double x, double y, int t1, int t2, bool b1, bool b2)
{
    chassis.turnToPoint(x, y, t1, {.forwards = b1, .maxSpeed = angmaxspeed, .minSpeed = angminspeed, .earlyExitRange = angearlyexitrange});
    chassis.moveToPoint(x, y, t2, {.forwards = b2, .maxSpeed = latmaxspeed, .minSpeed = latminspeed, .earlyExitRange = latearlyexitrange});
}

void leftAuton() 
{

}

void rightAuton() 
{
    // set pose at stack of pins on left side of toggle
    chassis.setPose(-23.5, -62, 0);
    
    // move forward to alliance goal to score a pin
    intake.move(+20);
    moveTo(-23.5, -58, 700, 700, true, true);
    intake.move(+100);
    delay(300);
    intake.move(0);

    // go back to pick up pin
    moveTo(-23.5, -62, 700, 700, false, false);
    clawclamp.set_value(true);
    delay(200);

    // move to toggle to toggle
    moveTo(-13.5, -55.5, 700, 700, true, true);

    // move back to alliance goal to score pin
    moveTo(-15, -54, 700, 700, false, false);
    clawclamp.set_value(false);

    // move to opposite pins in quadrant to pick up pin
    moveTo(12.5, -55.5, 700, 700, true, true);
    moveTo(21, -59.5, 700, 700, false, false);
    chassis.turnToHeading(113, 700, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 1});
    moveTo(21, -62.5, 700, 700, false, false);
    clawclamp.set_value(true);

    // // move to opposite pins in quadrant to pick up pin
    // moveTo(-13.5, -58, 700, 700, true, true);
    // moveTo(13.5, -58, 700, 1200, true, true);
    // chassis.turnToHeading(0, 700, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 1});
    // moveTo(13.5, -62, 700, 700, false, false);

    // move back to move to neutral goal to score pin
    moveTo(-2, -42.5, 700, 1000, true, true);

    // move back to neutral goal to score pin
    moveTo(15.5, -42.5, 700, 1000, false, false);
    clawclamp.set_value(false);

    // move to pin and cup in your alliance quadrant to pick up pin and cup
    moveTo(-16, -28, 700, 1000, false, false);
    clawclamp.set_value(true);

    // move to alliance goal to score pin
    moveTo(-19, -37, 700, 1000, false, false);
    clawclamp.set_value(false);
    

    // chassis.setPose(0, -62.5, 0);
    // moveTo(0, -59, 700, 700, true, true);
    // moveTo(-23, -59, 700, 700, true, true);
    // moveTo(-23, -56.5, 1200, 1000, false, false);
    // lift.move(-100);
    // delay(300);
    // lift.move(0);
    // clawswing.set_value(true);
    // clawclamp.set_value(true);
}

void soloawp() {

}

void skills() {
    
}

void sawp()
{
    
}

void test()
{

}

void toggles() {
    chassis.setPose(0, -63, 0);
    chassis.moveToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40, .earlyExitRange = 1});
    chassis.arcade(-127, 0);
    delay(700);
    chassis.cancelAllMotions();

    chassis.moveToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40, .earlyExitRange = 1});
    chassis.arcade(-127, 0);
    delay(700);
    chassis.cancelAllMotions();
    
}