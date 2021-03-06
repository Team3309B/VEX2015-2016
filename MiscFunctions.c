#pragma systemFile





// ---Task Management ---
//Starts All Tasks that Pertain to Shooting
void startBallTasks() {
	startTask( intakeTask );
	startTask( elevatorTask );
	startTask( shooterTask);
}

void stopBallTasks() {
	stopTask( intakeTask );
	stopTask( elevatorTask );
	stopTask( shooterTask);
}

void shiftToLiftMode() {
	stopBallTasks();
	startTask( liftTask );
}

void shiftToBallMode() {
	stopTask( liftTask );
	startBallTasks();
}

void shiftModes() {
	if(	isBallMode ) {
		shiftToLiftMode();
	}else {
		shiftToBallMode();
	}
	isBallMode = !isBallMode;
}

// --- Sensor Management ---
// Reset All Encoders
void resetEn() {
	SensorValue[elevatorEncoder] = 0;
	nMotorEncoder[shooter1] = 0;
	SensorValue(rightDriveTrain) = 0;
	SensorValue(leftDriveTrain) = 0;
}

// Reset All Sensors
void resetSensors() {

}

// Recalibrate the Gyro, stop all tasks while doing so
void resetGyro() {

//stopAllTasks();
	SensorType[in1] = sensorNone;
	wait1Msec(1105);
	SensorType[in1] = sensorGyro;
	wait1Msec(2000);
	//startTask( driveTask );
	//startBallTasks();
}

void initSensors() {
	resetEn();
#ifdef INIT_GYRO_ON_STARTUP
	resetGyro();
#endif
}
