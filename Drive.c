

void setLeftDrive(int x) {
	motor[LeftFrontDrive] = x;
	motor[LeftBackDrive] = x;
}

void setRightDrive(int x) {
	motor[RightFrontDrive] = x;
	motor[RightBackDrive] = x;
}

void runDriveAt(int x) {
	setLeftDrive(x);
	setRightDrive(x);
}

void stopDrive() {
	runDriveAt(0);
}

void driveHalo ( int throttle, int turn ) {

	// Find current velocities
	leftDriveVelocity = (float)(((float)-SensorValue[leftDrive] - pastLeft) / delayAmount); // Divide by "delayAmount" so that if you change the update loop frequency, your velocities don't change
	rightDriveVelocity = (float)(((float)SensorValue[rightDrive] - pastRight) / delayAmount);
	gyroAngularVelocity = (float)(((float)-SensorValue[gyro] - pastGyro) / delayAmount);

	// Track x and y coordinates
	x += sin((SensorValue[gyro]/10) * (pi/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);
	y += cos((SensorValue[gyro]/10) * (pi/180)) * ((((float)-SensorValue[leftDrive] - pastLeft) + ((float)SensorValue[rightDrive] - pastRight))/2);

	// Store past position so next time, the loop can find velocities
	pastRight = (float)SensorValue[rightDrive];
	pastLeft = (float)-SensorValue[leftDrive];
	pastGyro = (float)-SensorValue[gyro];

	// Find target by multiplying joystick percentage by 127
	float targetAngularVelocity = (float)((float) turn/127) * MAX_ANG_VEL;
	float targetDriveVelocity = (float)((float) throtte /127) * MAX_VEL;

	// Find PID Value of the velocities and turns
	angVelocityPWM = PIDRun(gyroDrivePID, targetAngularVelocity - gyroAngularVelocity);
	leftVelocityPWM = PIDRun(driveLeftDrivePID, targetDriveVelocity - leftDriveVelocity);
	rightVelocityPWM = PIDRun(driveRightDrivePID, targetDriveVelocity - rightDriveVelocity);

	// Get overall vel from new velocities added to old ones
	float angVel = angVelocityPWM + skim(angVelocityPWM);
	float leftVel = leftVelocityPWM + skim(leftVelocityPWM);
	float rightVel = rightVelocityPWM + skim(rightVelocityPWM);

	// Set power to motors
	motor[leftFront]  = 127*(leftVel + angVel); // (y + x)/2
	motor[rightFront] = 127*(rightVel - angVel);
	motor[leftBack]  = 127*(leftVel + angVel);  // (y + x)/2
	motor[rightBack] = 127*(rightVel - angVel);
}

task driveTask() {
	while(true) {
		driveHalo( vexRT[Ch3], vexRT[Ch1] );
	}
}
