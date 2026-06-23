#ifndef GLOBALS_HPP
#define GLOBALS_HPP
using namespace pros;

#include "main.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "sensor_loc.cpp"
#include "pros/optical.hpp"
#include "lemlib/api.hpp" //lemlibs

// Ports
    #define LEFT_WHEELS_BACK_PORT -11
    #define LEFT_WHEELS_FRONT_PORT -12
    #define LEFT_WHEELS_TOP_PORT -13
    #define RIGHT_WHEELS_TOP_PORT +18
    #define RIGHT_WHEELS_FRONT_PORT +19
    #define RIGHT_WHEELS_BACK_PORT +20 
    #define PistonPort 'A';

// Defines
    inline std::string autonomousPath = "none"; // Default autonomous path
    inline std::string teamColor = "none";      // Default team color

// Constants
    constexpr double PI = 3.141592;

// Controller
    inline pros::Controller master(pros::E_CONTROLLER_MASTER);
    inline pros::Controller slave(pros::E_CONTROLLER_PARTNER);

    namespace buttons
    {
        constexpr auto R1 = pros::E_CONTROLLER_DIGITAL_R1;
        constexpr auto R2 = pros::E_CONTROLLER_DIGITAL_R2;
        constexpr auto L1 = pros::E_CONTROLLER_DIGITAL_L1;
        constexpr auto L2 = pros::E_CONTROLLER_DIGITAL_L2;
        constexpr auto A = pros::E_CONTROLLER_DIGITAL_A;
        constexpr auto B = pros::E_CONTROLLER_DIGITAL_B;
        constexpr auto Y = pros::E_CONTROLLER_DIGITAL_Y;
        constexpr auto X = pros::E_CONTROLLER_DIGITAL_X;
        constexpr auto UP = pros::E_CONTROLLER_DIGITAL_UP;
        constexpr auto DOWN = pros::E_CONTROLLER_DIGITAL_DOWN;
        constexpr auto LEFT = pros::E_CONTROLLER_DIGITAL_LEFT;
        constexpr auto RIGHT = pros::E_CONTROLLER_DIGITAL_RIGHT;
    }

// Motor Brake Method
    const pros::motor_brake_mode_e_t brake = pros::E_MOTOR_BRAKE_BRAKE;
    const pros::motor_brake_mode_e_t coast = pros::E_MOTOR_BRAKE_COAST;
    const pros::motor_brake_mode_e_t hold = pros::E_MOTOR_BRAKE_HOLD;

// Motors and MotorGroups
    // Motor motor(motor_port);

// Pneumatics - Define Pneumatics like this
    //pros::adi::Pneumatics horizontal_tracking_lift_piston(PistonPort, true);

// System Booleans - Define Booleans
    // bool boolean = false;

// Sensors - Define Sensors
    Imu imu(15); // IMU
    Rotation vertical_tracking_sensor(6); lemlib::TrackingWheel vertical_tracking_wheel(&vertical_tracking_sensor, lemlib::Omniwheel::NEW_2, 0); // Vertical Odom
    Rotation horizontal_tracking_sensor(5); lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_tracking_sensor, lemlib::Omniwheel::NEW_2, 2.0); // Horizontal Odom

    // Distance front_distance_sensor(FRONT_DISTANCE_SENSOR_PORT); inline dist_sensor front(&front_distance_sensor, lemlib::Pose(4.25, 4.75, 0));
    // Distance left_distance_sensor(LEFT_DISTANCE_SENSOR_PORT); inline dist_sensor left(&left_distance_sensor, lemlib::Pose(-5.1, -1, 270));
    // Distance back_distance_sensor(BACK_DISTANCE_SENSOR_PORT); inline dist_sensor back(&back_distance_sensor, lemlib::Pose(4.25, -5.45, 180));
    // Distance right_distance_sensor(RIGHT_DISTANCE_SENSOR_PORT); inline dist_sensor right(&right_distance_sensor, lemlib::Pose(5.1, -0.25, 90));

    // Optical color_sensor(COLOR_SORT_SENSOR_PORT);

// Lemlib Classes Definitions - Define Autonomous Classes

    // Drivetrain
    // lemlib::Drivetrain drivetrain(&left_wheels,               // left motor group
    //                             &right_wheels,              // right motor group
    //                             12,                         // 12 inch track width
    //                             lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
    //                             450,                        // drivetrain rpm is 360
    //                             2                           // horizontal drift is 2 (for now)
    // );

    // Drivetrain Controller Settings - Throttle
    lemlib::ExpoDriveCurve throttle_curve(10,   // joystick deadband out of 127
                                        20,   // minimum output where drivetrain will move out of 127
                                        1.019 // expo curve gain
    );

    // Drivetrain Controller Settings - Curve
    lemlib::ExpoDriveCurve steer_curve(3,   // joystick deadband out of 127
                                    10,  // minimum output where drivetrain will move out of 127
                                    1.015 // expo curve gain
    );

    // PID - Lateral
    lemlib::ControllerSettings lateral_controller(10,  // Increase kP for more "push" at the end
                                                0.35,   // Set kI to 0 unless you really need it
                                                70,   // kD
                                                1.5,   // anti-windup
                                                0.5, // Reduce error range to 0.5 inches for better accuracy
                                                100, 
                                                2,   // Large error range
                                                500, 
                                                127  // Set Slew to 127 for instant power
    );

    // PID - Angular
    lemlib::ControllerSettings angular_controller(2.5,  // proportional gain (kP) 2, 3
                                                0.5,  // integral gain (kI)
                                                17.75, // derivative gain (kD) 12.05, 20
                                                3.8,  // anti windup (average error x 1.5)
                                                // error range =  turn, every time you turn increase from 10-180
                                                1,   // small error range, in degrees
                                                100, // small error range timeout, in milliseconds
                                                2,   // large error range, in degrees
                                                500, // large error range timeout, in milliseconds
                                                0    // maximum acceleration (slew) (never change this slew)
    );

    // Odometry
    lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                                nullptr,                  // vertical tracking wheel 2, set to nullptr as we are using IMEs
                                &horizontal_tracking_wheel,                  // horizontal tracking wheel 1
                                nullptr,                  // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                                &imu                      // inertial sensor
    );

    // // Chassis
    // lemlib::Chassis chassis(drivetrain,
    //                         lateral_controller,
    //                         angular_controller,
    //                         sensors,
    //                         &throttle_curve,
    //                         &steer_curve);

#endif