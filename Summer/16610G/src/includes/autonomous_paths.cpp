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

int angminspeed = 20;
float angearlyexitrange = 1;

float latminspeed = 20;
float latearlyexitrange = 1;

double x_value = 0;
double y_value = 0;
double distance = 0;

void moveTo(double x, double y, int t1, int t2, bool b1, bool b2, int angmaxspeed, float latmaxspeed)
{
    chassis.turnToPoint(x, y, t1, {.forwards = b1, .maxSpeed = angmaxspeed, .minSpeed = angminspeed, .earlyExitRange = angearlyexitrange}, false);
    chassis.moveToPoint(x, y, t2, {.forwards = b2, .maxSpeed = latmaxspeed, .minSpeed = latminspeed, .earlyExitRange = latearlyexitrange}, false);
}

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
    // chassis.setPose(-19, -50, chassis.getPose().theta);

    // master.print(0, 0, "Pose: %f, %f, %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    // delay(10000);

    // chassis.moveToPoint(-17, -52, 1000, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1});

    // chassis.setPose(-11.5, -59, chassis.getPose().theta);

    // chassis.moveToPoint(-11.5, -55, 1000, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1});
    // delay(200);
    // chassis.moveToPoint(-11.5, -59, 1000, {.forwards = true, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1});

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
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    
    // --- STEP 1: INITIAL SETjPOSE ---
    // Set your starting position relative to the first yellow pin / wall setup
    chassis.setPose(-60, -14, 322);

    // Helper macro / inline lambda for scoring a pin to keep code clean
    auto scorePin = [](double x, double y, int timeout = 4000) {
        lift.move(80);
        chassis.moveToPoint(x, y, timeout, {.forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 1});
        delay(300);
        lift.move(-127);
        delay(500);
        clawclamp.set_value(false);
        delay(100);
        lift.move(0);
    };

    // --- STEP 2: SCORE YELLOW PIN 1 ---
    lift.move(+110);
    chassis.moveToPoint(-49.7, -25, 2500, {.forwards = false, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 1});
    delay(400);
    lift.move(-110);
    delay(1000);
    clawclamp.set_value(false);
    delay(100);
    lift.move(0);

    // toggle ze toggle
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
    delay(2200);
    chassis.cancelAllMotions();
    chassis.arcade(0, 0);
/* 
    // --- STEP 3: SCORE YELLOW PIN 2 ---
    // Back up / reposition towards Pin 2
    chassis.moveToPoint(-15, -40, 1500, {.forwards = true, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
    scorePin(-30, -35);

    // --- STEP 4: SCORE YELLOW PIN 3 ---
    // Reposition towards Pin 3
    chassis.moveToPoint(-20, -20, 1500, {.forwards = true, .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1});
    scorePin(-40, -15, 4000);

    // --- STEP 5: NAVIGATE TO TOGGLE & DOUBLE TOGGLE ---
    // Align in front of the toggle mechanism
    chassis.turnToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 90, .minSpeed = 30});
    chassis.moveToPoint(0, -55, 1200, {.forwards = true, .maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 1});

    // --- FIRST TOGGLE HIT ---
    chassis.arcade(127, 0); // Ram into toggle
    delay(500);
    chassis.cancelAllMotions();

    chassis.arcade(-127, 0); // Back off
    delay(700);
    chassis.cancelAllMotions();

    // --- SECOND TOGGLE HIT ---
    chassis.moveToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40, .earlyExitRange = 1});
    chassis.arcade(127, 0); // Ram second time
    delay(500);
    chassis.cancelAllMotions();

    chassis.arcade(-127, 0); // Back off clear of toggle
    delay(700);
    chassis.cancelAllMotions();

    // Stop chassis completely
    chassis.arcade(0, 0); */
}

void sawp()
{
}

void test()
{
    liftPID(7);
}

void toggles()
{
    chassis.setPose(0, -63, 0);
    chassis.moveToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40, .earlyExitRange = 1});
    chassis.arcade(-127, 0);
    delay(700);
    chassis.cancelMotion();
    

    chassis.moveToPoint(0, -55, 1000, {.forwards = true, .maxSpeed = 110, .minSpeed = 40, .earlyExitRange = 1});
    chassis.arcade(-127, 0);
    delay(700);
    chassis.cancelMotion();
}