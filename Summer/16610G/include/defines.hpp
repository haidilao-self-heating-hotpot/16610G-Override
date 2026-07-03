#ifndef DEFINES_HPP
#define DEFINES_HPP

#include "main.h"
#include "lemlib/api.hpp"
#include "autonomous_selector.hpp"
#include "sensor_loc.hpp"
#include "piston.hpp"
using namespace pros;

// Ports ----------------------------------------------------------------
#define intakeport 5
#define leftdrivehalfport -2
#define leftdrive1port -4
#define leftdrive2port -1
#define rightdrivehalfport 8
#define rightdrive1port 9
#define rightdrive2port 10
#define lift1port -3
#define lift2port 7

#define imuport 17
#define verticalport 11
// #define horizontalport 12
#define frontport 13
#define rightport 14
#define backport 15
#define leftport 16


#define clawclampport 'A'
#define clawswingport 'B'

// AutonSelector -----------------------------------------------------------------------------

inline AutonSelector autonSelect;

// Motor Definitions -------------------------------------------------------------------------

inline Motor rightdrivehalf(rightdrivehalfport, MotorGears::green);
inline Motor rightdrive1(rightdrive1port, MotorGears::blue);
inline Motor rightdrive2(rightdrive2port, MotorGears::blue);
inline MotorGroup rightdrive(
    {rightdrivehalfport, rightdrive1port, rightdrive2port}
);

inline Motor leftdrivehalf(leftdrivehalfport, MotorGears::green);
inline Motor leftdrive1(leftdrive1port, MotorGears::blue);
inline Motor leftdrive2(leftdrive2port, MotorGears::blue);
inline MotorGroup leftdrive(
    {leftdrivehalfport, leftdrive1port, leftdrive2port}
);

inline Motor lift1(lift1port, MotorGears::blue);
inline Motor lift2(lift2port, MotorGears::blue);
inline MotorGroup lift(
    {lift1port, lift2port}
);

inline Motor intake(intakeport, MotorGears::green);

// Pneumatics Definitions --------------------------------------------------------------------

inline pros::adi::Pneumatics clawclamp(clawclampport, false);
inline pros::adi::Pneumatics clawswing(clawswingport, false);

// Sensor Definitions ------------------------------------------------------------------------

inline Imu imu(imuport);
inline Rotation vertical(verticalport); inline lemlib::TrackingWheel verticalwheel(&vertical, lemlib::Omniwheel::NEW_2, 0);
// inline Rotation horizontal(horizontalport); inline lemlib::TrackingWheel horizontalwheel(&horizontal, lemlib::Omniwheel::NEW_2, 0);

inline Distance frontdist(frontport); inline dist_sensor front(&frontdist, lemlib::Pose(0, 1, 0));
inline Distance rightdist(rightport); inline dist_sensor right(&rightdist, lemlib::Pose(1, 0, 90));
inline Distance backdist(backport); inline dist_sensor back(&backdist, lemlib::Pose(0, -1, 180));
inline Distance leftdist(leftport); inline dist_sensor left(&leftdist, lemlib::Pose(-1, 0, 270));

// Drivetrain --------------------------------------------------------------------------------

inline lemlib::Drivetrain drivetrain(
    &leftdrive,
    &rightdrive,
    11.75,
    lemlib::Omniwheel::NEW_275,
    450,
    2
);

inline lemlib::ExpoDriveCurve throttle_curve(
    10,
    20,
    1.019
);

inline lemlib::ExpoDriveCurve steer_curve(
    3,
    10, 
    1.015
);

inline lemlib::ControllerSettings lateral_controller(
    10,  // Increase kP for more "push" at the end                                            
    0,   // Set kI to 0 unless you really need it
    3,   // kD                                            
    1,   // anti-windup
    0.5, // Reduce error range to 0.5 inches for better accuracy                                            
    100, 
    2,   // Large error range
    500, 
    127  // Set Slew to 127 for instant power
);

inline lemlib::ControllerSettings angular_controller(
    10,  // proportional gain (kP) 2, 3
    0,  // integral gain (kI)
    3, // derivative gain (kD) 12.05, 20
    3.8,  // anti windup (average error x 1.5)
    1,   // small error range, in degrees
    100, // small error range timeout, in milliseconds
    2,   // large error range, in degrees
    500, // large error range timeout, in milliseconds
    0    // maximum acceleration (slew) (never change this slew)
);

inline lemlib::OdomSensors sensors(
    &verticalwheel, // vertical tracking wheel 1, set to null
    nullptr,                  // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr,                  // horizontal tracking wheel 1
    nullptr,                  // horizontal tracking wheel 2, set to nullptr as we don't have a second one
    &imu                      // inertial sensor
);

inline lemlib::Chassis chassis(
    drivetrain,             
    lateral_controller,            
    angular_controller,            
    sensors,                
    &throttle_curve,                 
    &steer_curve
);

#endif