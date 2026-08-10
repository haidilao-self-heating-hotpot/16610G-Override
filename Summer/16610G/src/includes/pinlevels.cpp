#include "includes.hpp"

// winch constants

double baseheight = 7;
double winchdiameter = 0.75;
double wpl = 6;
double cablediameter = 0.0625;

// pid constants

double liftkP = 1000;
double liftkI = 0;
double liftkD = 200;
double gravity = 0;
double liftAwr = 0;
double liftexitrange = 0.25;
double lifttimeout = 2500; // millisecond

double currentHeight()
{
    double winchrotations = lift.get_position() / 360.0;
    double winchheight = 0;
    for (int i = 0; i < winchrotations; i++)
    {
        winchheight += M_PI * (winchdiameter + (2 * cablediameter * std::floor(i / wpl)));
    }
    winchheight += (winchrotations - std::floor(winchrotations)) * M_PI * (winchdiameter + (2 * cablediameter * std::floor(winchrotations / wpl)));
    return baseheight + winchheight;
}

double integral = 0;
double derivative = 0;
double lasterror = 0;
bool liftactive = false;
uint32_t liftstart = 0;
double lifttarget = 0;

double liftPIDoutput()
{
    double error = lifttarget - currentHeight();

    double proportional = error;
    if (std::fabs(error) <= liftAwr)
    {
        integral += error * 0.01;
    }
    else
    {
        integral = 0;
    }
    double rawderivative = (error - lasterror) / 0.01;
    derivative = (0.3 * rawderivative) + ((1 - 0.3) * derivative);
    lasterror = error;

    double output = (liftkP * proportional) + (liftkI * integral) + (liftkD * derivative) + gravity;
    return std::clamp(output, -12000.0, 12000.0);
}

void liftPIDreset()
{
    integral = 0;
    derivative = 0;
    lasterror = lifttarget - currentHeight();
}

void liftPID(double target)
{
    lifttarget = target;
    liftPIDreset();
    liftstart = pros::millis();
    liftactive = true;
}

void liftPIDupdate()
{
    if (!liftactive)
        return;

    bool timedout = pros::millis() - liftstart >= lifttimeout;
    bool exitrange = std::fabs(lifttarget - currentHeight()) <= liftexitrange;

    if (timedout || exitrange)
    {
        lift.move_voltage(0);
        liftactive = false;
        return;
    }

    lift.move_voltage(liftPIDoutput());
}

// put liftPIDupdate in opcontrol