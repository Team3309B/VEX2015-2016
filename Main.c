#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftDrive,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightDrive,     sensorQuadEncoder)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightFrontDrive, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightBackDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftBackDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           shooterLeft,   tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           shooterRight,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           elevator1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           elevator2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          lift,          tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma systemFile

// Necessary File For Vex Competition
#include "Vex_Competition_Includes.c"

#include "DeclarationsAndDefines.h"

// Subsystems
#include "Drive.c"
#include "Intake.c"
#include "Shooter.c"
#include "Elevator.c"
#include "Lift.c"

#include "LCDTask.c"

#include "Auto.c"

#include "MiscFunctions.c"



// Ran when you turn ON Robot, I opt not to use this
void pre_auton() {

}

// Ran in Auto
task autonomous() {
	// Reset Encoders and then run the begin auto method found in AUTO.c
	resetEn();
	startauton();
	stopDrive();
}

//Ran in Teleop
task usercontrol() {
	// Start up the LCD
	LCDInit();
	startTask( runLCD );
	startTask( buttonTask );

	// Clear Encoders and possibly Gyro
	initSensors();
	resetEn();
	resetGyro();

	//Start the tasks that control each aspect of the robot
	startTask( driveTask );
	startBallTasks();

	while(true) {
		// Toggle for switching modes between climbing and shooting
		/*if ( isTapped(ButtonP8L) ) {
			shiftModes();
		}*/
	}
}
