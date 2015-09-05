float getRightDriveEncoderInches() {
	return ((float)nMotorEncoder[rightDrive]/360.0) * 4.0; // Rotations times 4 inches
}

float getLeftDriveEncoderInches() {
	return ((float)nMotorEncoder[leftDrive]/360.0) * 4.0; // Rotations times 4 inches
}

float getRightDriveEncoderMeters() {
	return ((float)nMotorEncoder[rightDrive]/360.0) * 0.1016; // Rotations times .1016 meters
}

float getLeftDriveEncoderMeters() {
	return ((float)nMotorEncoder[leftDrive]/360.0) * 0.1016; // Rotations times .1016 meters
}

float getRightDriveEncoderCentimeters() {
	return ((float)nMotorEncoder[rightDrive]/360.0) * 10.16; // Rotations times 10.16 centimeters
}

float getLeftDriveEncoderCentimeters() {
	return ((float)nMotorEncoder[leftDrive]/360.0) * 10.16; // Rotations times 10.16 centimeters
}

float getRightDriveEncoderRotations() {
	return ((float)nMotorEncoder[rightDrive]/360.0); //360 counts per rotations
}

float getLeftDriveEncoderRotations() {
	return ((float)nMotorEncoder[leftDrive]/360.0); //360 counts per rotations
}
