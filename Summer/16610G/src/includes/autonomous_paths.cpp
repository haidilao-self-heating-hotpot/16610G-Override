#include "autonomous_paths.hpp"
#include "includes.hpp"

int angmaxspeed = 100;
int angminspeed = 40;
float angearlyexitrange = 1;

float latmaxspeed = 100;
float latminspeed = 40;
float latearlyexitrange = 1;

void moveTo(double x, double y, int t1, int t2, bool b1, bool b2)
{
    chassis.turnToPoint(x, y, t1, {.forwards = b1, .maxSpeed = angmaxspeed, .minSpeed = angminspeed, .earlyExitRange = angearlyexitrange});
    chassis.moveToPoint(x, y, t2, {.forwards = b2, .maxSpeed = latmaxspeed, .minSpeed = latminspeed, .earlyExitRange = latearlyexitrange});
}

void primary() {

}

void mirror() {

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
    chassis.arcade(-127, 0);
    delay(500);
    chassis.cancelAllMotions();

    chassis.moveToPoint(0, -45, 1000, {.forwards = true, .maxSpeed = latmaxspeed, .minSpeed = latminspeed});
    moveTo(45, 0, 600, 2000, true, true);
    moveTo(70, 0, 600, 1000, true, false);
    chassis.arcade(-127, 0);
    chassis.cancelAllMotions();
}