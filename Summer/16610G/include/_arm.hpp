#ifndef ARM_HPP
#define ARM_HPP
#include "includes.hpp"

// tuning constants (defined in arm.cpp)
extern double armkP;
extern double armkI;
extern double armkD;
extern double armAwr;
extern double armexitrange;
extern double armtimeout;
extern double armmanualvoltage;

// runtime state (defined in arm.cpp)
extern bool armactive;
extern uint32_t armstart;
extern double armtarget;

// public API
double armgetangle();
void armPIDtarget(double target);
void armPIDupdate();

#endif