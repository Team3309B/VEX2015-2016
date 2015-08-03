

void setLeftDrive(int x) {
	motor[leftFrontDrive] = x;
	motor[leftBackDrive] = x;
}

void setRightDrive(int x) {
	motor[rightFrontDrive] = x;
	motor[rightBackDrive] = x;
}

void runDriveAt(int x) {
	setLeftDrive(x);
	setRightDrive(x);
}

void stopDrive() {
	runDriveAt(0);
}

// Skim off some to smooth drive equation
float skim(float v) {
	float skimGain = .25;	// gain determines how much to skim off the top
	if (v > 1.0) {
		return -((v - 1.0) * skimGain);
		} else if (v < -1.0) {
		return -((v + 1.0) * skimGain);
	}
	return 0;
}

void driveHalo ( int throttle, int turn ) {

	// Find current velocities
	float leftDriveVelocity = (float)(((float)-SensorValue[leftDrive] - pastLeft) / driveEquationDelayAmount);
	float rightDriveVelocity = (float)(((float)SensorValue[rightDrive] - pastRight) / driveEquationDelayAmount);
	float gyroAngularVelocity = (float)(((float)-SensorValue[gyro] - pastGyro) / driveEquationDelayAmount);

	// Track x and y coordinates
	x += sin((SensorValue[gyro]/10) * (PI/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);
	y += cos((SensorValue[gyro]/10) * (PI/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);

	// Store past position so next time, the loop can find velocities
	pastRight = (float)SensorValue[rightDrive];
	pastLeft = (float)-SensorValue[leftDrive];
	pastGyro = (float)-SensorValue[gyro];

	// Find target by multiplying joystick percentage by 127
	float targetAngularVelocity = (float)((float) turn/127) * MAX_ANG_VEL;
	float targetDriveVelocity = (float)((float) throttle /127) * MAX_VEL;

	// Find PID Value of the velocities and turns
	float angVelocityPWM = PIDRun(gyroDrivePID, targetAngularVelocity - gyroAngularVelocity);
	float leftVelocityPWM = PIDRun(driveLeftDrivePID, targetDriveVelocity - leftDriveVelocity);
	float rightVelocityPWM = PIDRun(driveRightDrivePID, targetDriveVelocity - rightDriveVelocity);

	// Get overall vel from new velocities added to old ones
	float angVel = angVelocityPWM + skim(angVelocityPWM);
	float leftVel = leftVelocityPWM + skim(leftVelocityPWM);
	float rightVel = rightVelocityPWM + skim(rightVelocityPWM);

	// Set power to motors
	motor[leftFrontDrive]  = 127*(leftVel + angVel); // (y + x)/2
	motor[rightFrontDrive] = 127*(rightVel - angVel);
	motor[leftBackDrive]  = 127*(leftVel + angVel);  // (y + x)/2
	motor[rightBackDrive] = 127*(rightVel - angVel);

	delay(driveEquationDelayAmount);
}

task driveTask() {
	PIDInit(gyroDrivePID, .02, 00);
	PIDInit(driveRightDrivePID, .11, 0);
	PIDInit(driveLeftDrivePID, .11, 0);
	while(true) {
		driveHalo( vexRT[Ch3], vexRT[Ch1] );
	}
}
