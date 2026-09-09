#include "includes.hpp"

double armkP = 750;
double armkI = 0;
double armkD = 10;
double armAwr = 0;
double armgravity = 250;
double armexitrange = 1;
double armtimeout = 2500;

static double armintegral = 0;
static double armderivative = 0;
static double armlasterror = 0;


bool armactive = false;
uint32_t armstart = 0;
double armtarget = 0;

double armgetangle() {
    armmotor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    return std::fmod(armmotor.get_position() / 5, 360.0);
}

// shortest-path error from the current angle to armtarget, wrapped into (-180, 180]
double armgeterror() {
    double error = std::fmod(armtarget - armgetangle() + 180.0, 360.0) - 180.0;
    if (error < -180.0) error += 360.0;
    return error;
}

double armPIDoutput() {
    double error = armgeterror();

    if (std::fabs(error) <= armAwr) {
        armintegral += error * 0.01;
    } else {
        armintegral = 0;
    }

    double rawderivative = (error - armlasterror) / 0.01;
    armderivative = (0.3 * rawderivative) + (0.7 * armderivative);
    armlasterror = error;

    double output = (armkP * error) + (armkI * armintegral) + (armkD * armderivative) + (armgravity * std::cos(armgetangle() * M_PI / 180));
    return std::clamp(output, -12000.0, 12000.0);
}

void armPIDreset() {
    armintegral = 0;
    armderivative = 0;
    armlasterror = armgeterror();
}

void armPIDtarget(double target) {
    armmotor.set_brake_mode_all(coast);
    armtarget = target;
    armPIDreset();
    armstart = pros::millis();
    armactive = true;
}

bool armmanualheld = false;
double armmanualvoltage = 4000;

void armPIDupdate() {

    if (robotstate == 1) {
        master.print(1, 0, "Manual Control");
        bool armmanualUp   = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
        bool armmanualDown = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);

        if (armmanualUp || armmanualDown) {
            armactive = false;
            armmanualheld = true;
            armmotor.move_voltage(armmanualUp ? armmanualvoltage : -armmanualvoltage);
            return;
        }

        if (armmanualheld) {
            armmanualheld = false;
            armPIDtarget(armgetangle());
        }
    }

    if (!armactive) return;

    bool timedout  = pros::millis() - armstart >= armtimeout;
    bool exitrange = std::fabs(armgeterror()) <= armexitrange;

    if (timedout || exitrange) {
        armmotor.set_brake_mode_all(hold);
        armmotor.move_voltage(0);
        armactive = false;
        return;
    }

    armmotor.move_voltage(armPIDoutput());
}