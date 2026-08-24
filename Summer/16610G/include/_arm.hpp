#ifndef ARM_HPP
#define ARM_HPP
#include "includes.hpp"

extern double scoringangle;
extern double armkP;
extern double armkI;
extern double armkD;
extern double armAwr;
extern double armexitrange;
extern double armtimeout;

extern double armintegral;
extern double armderivative;
extern double armlasterror;
extern bool armactive;
extern uint32_t armstart;
extern double armtarget;

double armPIDoutput();

void armPIDupdate();

void armPIDreset();

void armPIDtarget(double target);

#endif