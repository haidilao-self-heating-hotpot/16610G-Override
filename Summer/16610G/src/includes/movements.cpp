#include "includes.hpp"

void liftTaskFn(void* param) {
    uint32_t now = pros::millis();
    while (true) {
        liftPIDupdate();
        pros::Task::delay_until(&now, 10);
    }
}