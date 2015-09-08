#define driveRadiusInches 4 //R
#define wheelBaseInches 10 // L
float x = 0;
float y = 0;
float heading = 0;

void kragerNewXYT() {

}

void unicycleXYT() {
	float rightVel = (nMotorEncoder[RightDrive]);
	float leftVel = (nMotorEncoder[LeftDrive]);
	float deltaHeading = (driveRadiusInches/wheelBaseInches) * (rightVel - leftVel);
	heading += deltaHeading;
	float translationalVelocity = (((driveRadiusInches/2.0) * (rightVel + leftVel))); // may have to do something with time here
	float angularVelocity = (deltaHeading); // may have to do something with time here
	float deltaX = translationalVelocity * cos(heading);
	float deltaY = translationalVelocity * sin(heading);
	x += deltaX;
	y += deltaY;
	nMotorEncoder[RightDrive] = 0;
	nMotorEncoder[LeftDrive ] = 0;
	wait1Msec(delayAmount);
}
