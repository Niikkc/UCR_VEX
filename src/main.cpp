#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-4, 10, 15}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{-11, 12, -16}

  // IMU Port
  ,19

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,4.125

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    //Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Flywheel Autonomous\n\n", flyAuto),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  
  bool longShot = true;
  int longShotVelocity = 250;
  int closeShotVelocity = 130;
  bool flywheelToggle = false;
  bool loaderToggle = false;

  intake.brake();
  roller.brake();
  

  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    // == FLYWHEEL == \\

/*
error = target velocity - actual velocity
if (abs of error > 100) {
	go full speed
}
else if (abs of error < 100) {
	motor name = 127
}
else {
	go 30
}

*/
		

		

		
		if(master.get_digital(DIGITAL_LEFT)){   //180 120
			longShot = false;
		}
		if(master.get_digital(DIGITAL_RIGHT)){
			longShot = true;
		}

    if(master.get_digital(DIGITAL_UP)){													// If L1 is pressed, toggle the flywheel on
			flywheelToggle = !flywheelToggle;
			pros::delay(250);																// Delay used so bool doesn't toggle back and forth multiple times
		}

    int kP = 0.05;
    int longTargetVelocity = 300;
		int shortTargetVelocity = 180;
		int longError = longTargetVelocity - flywheel.get_actual_velocity();
		int shortError = shortTargetVelocity - flywheel.get_actual_velocity();

    int longPower = longError * kP;
    int shortPower = shortError * kP;

		if(flywheelToggle){
			if(longShot){
				if(abs(longError) > 100){
					flywheel.move(127);
				}else if(abs(longError) < 100){
					flywheel.move(80);
				}else{
					flywheel.move(30);
				}
			}else{
        if(master.get_digital(DIGITAL_L1)){
          flywheel.move(127);
        }else{
          if(abs(shortError) > 45){
            flywheel.move(127);
          }else if(abs(longError) < 45){
            //flywheel.move(50);
            flywheel = 127;
          }else{
            flywheel.move(20);
          }
        }
      }
		}else{
      flywheel.brake();
    }

    // if(flywheelToggle){
    //   if(longShot){
    //     flywheel.move(longPower);
    //   }else{
    //     flywheel.move(shortPower);
    //   }
    // }else{
    //   flywheel.brake();
    // }
		
		

		// if(flywheelToggle){
		// 	if(longShot){
		// 		flywheel.move_velocity(longShotVelocity);
		// 	}else{
		// 		flywheel.move_velocity(closeShotVelocity);
		// 	}
		// }else{
		// 	flywheel.brake();
		// }


    if(master.get_digital(DIGITAL_L1)){
			loaderToggle = !loaderToggle;
			pros::delay(300);
		}

		

		if(longShot){
			if((flywheel.get_actual_velocity() > longShotVelocity - 5) && (flywheel.get_actual_velocity() < longShotVelocity + 5) && loaderToggle){
        loader.move(127);
        pros::delay(100);
        loader.brake();
			}
		}else{
			if((flywheel.get_actual_velocity() > closeShotVelocity - 8) && (flywheel.get_actual_velocity() < closeShotVelocity + 8) && loaderToggle){
        loader.move(127);
        pros::delay(100);
        loader.brake();
			}
		}

    // TEMPORARY (DELETE LATER)
		if(master.get_digital(DIGITAL_L2)){
			loader.move(127);
		}else{
			loader.brake();
		}


    // == INTAKE == \\

		int intakeSpeed = 127;

		if(master.get_digital(DIGITAL_R1)){ 							// If r1 is pushed, intake.
			if(master.get_digital(DIGITAL_UP)){ 						// If up arrow is pushed at the same time, half speed intake
				intake.move(intakeSpeed/2);
			}else{
				intake.move(intakeSpeed);
				roller.move(intakeSpeed);
			}
		}else if(master.get_digital(DIGITAL_R2)){ 						// If L1 is pushed, outtake
			if(master.get_digital(DIGITAL_UP)){ 						// If up arrow is pushed at the same time, half speed outtake.
				intake.move(-intakeSpeed/2);
			}else{
				intake.move(-intakeSpeed);
				roller.move(-intakeSpeed);
			}
		}else{
			intake.brake(); 											// If nothing is pushed, intake should be stopped
			roller.brake();
		}


    // == EXPANSION == \\

		if(master.get_digital(DIGITAL_B)){
			expansion.move(-127);
		}else{
			expansion.move(15);
		}
    

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
