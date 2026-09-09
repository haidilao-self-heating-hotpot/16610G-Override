#ifndef LIFT_HPP
#define LIFT_HPP

// winch geometry constants (defined in lift.cpp)
extern double baseheight;
extern double winchdiameter;
extern double wpl;
extern double cablediameter;

// tuning constants (defined in lift.cpp)
extern double liftkP;
extern double liftkI;
extern double liftkD;
extern double gravity;
extern double liftAwr;
extern double liftexitrange;
extern double lifttimeout;
extern double liftmanualvoltage;

// runtime state (defined in lift.cpp)
extern bool liftactive;
extern uint32_t liftstart;
extern double lifttarget;

// public API
double currentHeight();
void liftPIDtarget(double target);
void liftPIDupdate();

#endif