float getRightDriveEncoder() {
	return SensorValue(rightDriveTrain);
}

float getLeftDriveEncoder() {
	return SensorValue(leftDriveTrain);
}

float getRightDriveEncoderInches() {
	return (getRightDriveEncoder()/360.0) * 4.0; // Rotations times 4 inches
}

float getLeftDriveEncoderInches() {
	return (getLeftDriveEncoder()/360.0) * 4.0; // Rotations times 4 inches
}

float getRightDriveEncoderMeters() {
	return (getRightDriveEncoder()/360.0) * 0.1016; // Rotations times .1016 meters
}

float getLeftDriveEncoderMeters() {
	return (getLeftDriveEncoder()/360.0) * 0.1016; // Rotations times .1016 meters
}

float getRightDriveEncoderCentimeters() {
	return (getRightDriveEncoder()/360.0) * 10.16; // Rotations times 10.16 centimeters
}

float getLeftDriveEncoderCentimeters() {
	return (getLeftDriveEncoder()/360.0) * 10.16; // Rotations times 10.16 centimeters
}

float getRightDriveEncoderRotations() {
	return (getRightDriveEncoder()/360.0); //360 counts per rotations
}

float getLeftDriveEncoderRotations() {
	return (getLeftDriveEncoder()/360.0); //360 counts per rotations
}
