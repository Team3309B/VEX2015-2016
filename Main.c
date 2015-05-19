

// Necessary File For Vex Competition
#include "Vex_Competition_Includes.c"

#include "Drive.c"
#include "Intake.c"
#include "Shooter.c"
#include "Elevator.c"
#include "Lift.c"

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
	//Clear LCD and Reset Sensors, then begin teleop
	clearLCDLine(0);
	resetEn();
	resetGyro();

	//Start the tasks that control each aspect of the robot
	startTask( driveTask );
	startTask( intakeTask );
	startTask( elevatorTask );
	startTask( shooterTask);
	startTask( liftTask );

	while(true) {
		if (vexRT[Btn8L]) {
			shiftToLiftMode();
		}else if (vexRT[Btn8R]) {
			shiftToBallMode();
		}
	}

}
