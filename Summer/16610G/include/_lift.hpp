#ifndef LIFT_HPP
#define LIFT_HPP

extern double baseheight;
extern double basewinchdiameter;
extern double wpl;
extern double cablediameter;
extern double totalwraplayers;

extern double liftkP;
extern double liftkI;
extern double liftkD;
extern double gravity;
extern double liftAwr;
extern double liftexitrange;
extern double lifttimeout;

double currentHeight();

extern double integral;
extern double derivative;
extern double lasterror;
extern bool liftactive;
extern uint32_t liftstart;
extern double lifttarget;

double liftPIDoutput();

void liftPIDreset();

void liftPID(double target);

void liftPIDupdate();

void liftToHeight(double height);

#endif