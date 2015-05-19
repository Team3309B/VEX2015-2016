

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
	setRigtDrive(x);
}

void stopDrive() {
	runDriveAt(0);
}

task driveTask() {

	while(true) {

	}
}
