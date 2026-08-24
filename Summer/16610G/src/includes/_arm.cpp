#include "includes.hpp"

double scoringangle = 150;
double armkP = 1000;
double armkI = 0;
double armkD = 30;
double armAwr = 0;
double armexitrange = 1;
double armtimeout = 2500;

double armintegral = 0;
double armderivative = 0;
double armlasterror = 0;
bool armactive = false;
uint32_t armstart = 0;
double armtarget = 0;

double armPIDoutput() {
    double error = armtarget - armrotation.get_position()*4 % 360;

    double proportional = error;
    if (std::fabs(error) <= armAwr) {
        armintegral += error * 0.01;
    } else {
        armintegral = 0;
    }
    double rawderivative = (error - armlasterror) / 0.01;
    armderivative = (0.3 * rawderivative) + ((1 - 0.3) * armderivative);
    armlasterror = error;
    
    double output = (armkP * proportional) + (armkI * armintegral) + (armkD * armderivative);
    return std::clamp(output, -12000.0, 12000.0);
}

void armPIDupdate() {
    if (!armactive) return;

    bool timedout = pros::millis() - armstart >= armtimeout;
    bool exitrange = std::fabs(armtarget - armrotation.get_position()*4 % 360) <= armexitrange;

    if (timedout || exitrange) {
        armmotor.move_voltage(0);
        armactive = false;
        return;
    }

    armmotor.move_voltage(armPIDoutput());
}

void armPIDreset() {
    armintegral = 0;
    armderivative = 0;
    armlasterror = armtarget - armrotation.get_position()*4 % 360;
}

void armPIDtarget(double target) {
    armtarget = target;
    armPIDreset();
    armstart = pros::millis();
    armactive = true;
}