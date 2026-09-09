#include "includes.hpp"

//pid constants

double liftkP = 4000;
double liftkI = 7;
double liftkD = 50;
double gravity = 2500;
double liftAwr = 2;
double liftexitrange = 0.25;
double lifttimeout = 2500; //millisecond

double currentHeight() 
{
    double x = winchrotation.get_position() / 36000.0;
    return 2.663*x + 5.224; // linear regression found by testing
}

static double liftintegral = 0;
static double liftderivative = 0;
static double liftlasterror = 0;


bool liftactive = false;
uint32_t liftstart = 0;
double lifttarget = 0;

double liftPIDoutput() 
{   
    double error = lifttarget - currentHeight();

    if (std::fabs(error) <= liftAwr) {
        liftintegral += error * 0.01;
    } else {
        liftintegral = 0;
    }
    double rawderivative = (error - liftlasterror) / 0.01;
    liftderivative = (0.3 * rawderivative) + (0.7 * liftderivative);
    liftlasterror = error;

    double output = (liftkP * error) + (liftkI * liftintegral) + (liftkD * liftderivative) + gravity;
    master.print(0,0,"%.3f", error);
    delay(50);
    // master.print(2,0,"%.3f", liftderivative);
    // delay(50);

    return std::clamp(output, -12000.0, 12000.0);
}

void liftPIDreset()
{
    liftintegral = 0;
    liftderivative = 0;
    liftlasterror = lifttarget - currentHeight();
}

void liftPIDtarget(double target) {
    lift.set_brake_mode_all(coast);
    lifttarget = target;
    liftPIDreset();
    liftstart = pros::millis();
    liftactive = true;
}

bool liftmanualheld = false;
double liftmanualvoltage = 12000;

void liftPIDupdate() {

    if (robotstate == 1) {
        master.print(1, 0, "Manual Control");

        bool manualUp   = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1); 
        bool manualDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

        if (manualUp || manualDown) {
            liftactive = false;
            liftmanualheld = true;
            lift.move_voltage(manualUp ? liftmanualvoltage : -liftmanualvoltage);
            return;
        }

        if (liftmanualheld) {
            liftmanualheld = false;
            liftPIDtarget(currentHeight());
        }
    }

    if (!liftactive) return;

    bool timedout = pros::millis() - liftstart >= lifttimeout;
    bool exitrange = std::fabs(lifttarget - currentHeight()) <= liftexitrange;

    if (timedout || exitrange) {
        lift.set_brake_mode_all(hold);
        lift.move_voltage(0);
        liftactive = false;
        return;
    }

    lift.move_voltage(liftPIDoutput());
}

//put liftPIDupdate in opcontrol