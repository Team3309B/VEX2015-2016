

void setLeftDrive(int x) {
	motor[leftDrive] = x;
	motor[leftDriveExtra] = x;
}

void setRightDrive(int x) {
	motor[rightDrive] = x;
	motor[rightDriveExtra] = x;
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

float angVel = 0;
float leftVel = 0;
float rightVel = 0;
void driveHalo ( int throttle, int turn ) {

	// Find current velocities
	float leftDriveVelocity = (float)(((float)-SensorValue[leftDriveTrain] - pastLeft) / driveEquationDelayAmount);
	float rightDriveVelocity = (float)(((float)SensorValue[rightDriveTrain] - pastRight) / driveEquationDelayAmount);
	float gyroAngularVelocity = (float)(((float)-SensorValue[gyro] - pastGyro) / driveEquationDelayAmount);
	writeDebugStreamLine(" DRIVE: rightVel: %4.4f leftVel: %4.4f ang: %4.4f", rightDriveVelocity, leftDriveVelocity, gyroAngularVelocity);

	xRight += sin((SensorValue[gyro]/10) * (PI/180)) * ((float)SensorValue[rightDriveTrain] - pastRight);
	// Track x and y coordinates
	float x = sin((SensorValue[gyro]/10) * (PI/180)) * ((((float)-SensorValue[leftDriveTrain] - pastLeft) + ((float)SensorValue[rightDriveTrain] - pastRight))/2);
	float y = cos((SensorValue[gyro]/10) * (PI/180)) * ((((float)-SensorValue[leftDriveTrain] - pastLeft) + ((float)SensorValue[rightDriveTrain] - pastRight))/2);

	// Store past position so next time, the loop can find velocities
	pastRight = (float)SensorValue[rightDriveTrain];
	pastLeft = (float)-SensorValue[leftDriveTrain];
	pastGyro = (float)-SensorValue[gyro];

	// Find target by multiplying joystick percentage by 127
	float targetAngularVelocity = (float)((float) turn/127) * MAX_ANG_VEL;
	float targetDriveVelocity = (float)((float) throttle /127) * MAX_VEL;

	writeDebugStreamLine(" AIM: ang: %4.4f for: %4.4f", targetAngularVelocity, targetDriveVelocity);

	// Find PID Value of the velocities and turns
	float angVelocityPWM = PIDRun(gyroDrivePID, targetAngularVelocity - gyroAngularVelocity);
	float leftVelocityPWM = PIDRun(driveLeftDrivePID, targetDriveVelocity - leftDriveVelocity);
	float rightVelocityPWM = PIDRun(driveRightDrivePID, targetDriveVelocity - rightDriveVelocity);

	// Get overall vel from new velocities added to old ones
	angVel += skim(angVelocityPWM);// + skim(angVelocityPWM);
	leftVel += skim(leftVelocityPWM);// + skim(leftVelocityPWM);
	rightVel += skim(rightVelocityPWM);// + skim(rightVelocityPWM);

	writeDebugStreamLine("SET VEL: Left: %4.4f Right: %4.4f ", (leftVel + angVel), (rightVel - angVel));
	writeDebugStreamLine(" ");
	// Set power to motors
	motor[leftDrive]  = 127*(leftVel + angVel); // (y + x)/2
	motor[rightDrive] = 127*(rightVel - angVel);
}

void lameDrive() {
	float leftSpeed = vexRT[Ch3] + vexRT[Ch1];
	float rightSpeed = vexRT[Ch3] - vexRT[Ch1];
	//writeDebugStreamLine("LEFT: %d RIGHT: %d", leftSpeed, rightSpeed);
	setRightDrive(rightSpeed);
	setLeftDrive(leftSpeed);
}

task driveTask() {
	PIDInit(gyroDrivePID, .5, 00);
	PIDInit(driveRightDrivePID, 1, 0);
	PIDInit(driveLeftDrivePID, 1, 0);
	while(true) {
		//lameDrive();
		driveHalo( threshold(vexRT[Ch3], 20), threshold(vexRT[Ch1], 20) );
		wait1Msec(driveEquationDelayAmount);
	}
}
