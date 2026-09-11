#ifndef AUTON_HPP
#define AUTON_HPP

#include "sensor_loc.hpp"

void moveTo(double x, double y, int t1, int t2, bool forward, int angMaxSpeed, float latMaxSpeed, bool asyncValue = false);

void leftAutonv1();

void leftAuton();

void rightAuton();

void soloawp();

void skills();

void test();

void toggles();


#endif