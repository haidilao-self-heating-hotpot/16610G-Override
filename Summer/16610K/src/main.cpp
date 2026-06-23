#include "globals.hpp"          //contains motor definitions, other libraries, and global variables new
#include "AutonSelector.hpp"    // contains how to select a specific path
#include "Autonomous_Paths.hpp" // Contains the different autonomous paths
#include "movements.cpp" // Contains all movements
 
// creates autonSelector object
AutonSelector autonSelector;

void on_center_button() {

}

void initialize() {
    pros::lcd::initialize();
    pros::screen::erase();
    pros::delay(1000);
    /*
    Sets up the autons and passes in the all the routes as a vector (similar to an array)
    Each autonomousRoute contains the team color, name, description, and the acutal path
    */

    autonSelector.setAutons(std::vector<autonomousRoute>{
        // autonomousRoute{"color", "name", "description", path from Autonomous_Paths.hpp},
    });
    autonSelector.setSkillsAuton(autonomousRoute{"red", "Skills", "Skills Auton", autonomous});

    // Starts the auton selector screen (NOT the actual auton yet)
    autonSelector.start();

    // Put standard initialization code below here
    // chassis.calibrate();
    imu.reset();
    pros::delay(1000);
    
    // Code to set how bright the light of the color sensor is
    // color_sensor.set_led_pwm(100);
}

void disabled() {

}

void competition_initialize() {

}

void autonomous() {
    teamColor = autonSelector.isRedTeam() ? "red" : "blue";

    // Code to run during the autonomous period
    autonSelector.runAuton();
}

void systems_check() {
    
}

void opcontrol()
{
    uint32_t macroTimer = 0;

    while (true)
    {   
        pros::delay(50);
    }
}