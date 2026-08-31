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

double armAngle() {
    double angle = std::fmod((armrotation.get_position() / 100.0) * 4.0, 360.0);
    return angle < 0 ? angle + 360.0 : angle;
}

double armAngleError(double target, double current) {
    return std::fmod(target - current + 180.0, 360.0) - 180.0;
}

double armPIDoutput() {
    double error = armAngleError(armtarget, armAngle());

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
    bool exitrange = std::fabs(armAngleError(armtarget, armAngle())) <= armexitrange;

    if (timedout || exitrange) {
        armmotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        armmotor.move_voltage(0);
        armactive = false;
        return;
    }

    armmotor.move_voltage(armPIDoutput());
}

void armPIDreset() {
    armintegral = 0;
    armderivative = 0;
    armlasterror = armAngleError(armtarget, armAngle());
}

void armPIDtarget(double target) {
    armtarget = target;
    armPIDreset();
    armstart = pros::millis();
    armactive = true;
}