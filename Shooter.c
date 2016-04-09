void runShooterAt(int power) {
	motor[shooter1] = power;
	motor[shooter2] = power;
	motor[shooter3] = power;
	motor[shooter4] = power;
}

int loops = 0;
bool pressed = false;
bool holdPower = false;
int curPower = 0;
int offset = 0;
void checkAndFindSpeed() {
	if (vexRT[Btn6UXmtr2] && !pressed) {
		if (aimShooterSpeed > 500) {
			offset +=2;
			}else {
			offset += 5;
		}
		pressed = true;
		}else if (vexRT[Btn6DXmtr2] && !pressed) {
		if (aimShooterSpeed > 500) {
			offset -= 2;
			}else {
			offset -= 5;
		}
		pressed = true;
		}else {
		pressed = false;
	}
	if (vexRT[Btn7DXmtr2]){
		aimShooterSpeed = 358; // Up Close
		//aimShooterSpeed = -.25;
		}else if( vexRT[Btn7LXmtr2] ){
		aimShooterSpeed = 368; // Up Close Robot
		//aimShooterSpeed = -.6; //.5600
		}else if( vexRT[Btn7RXmtr2] ){
		aimShooterSpeed = 448; // Cross
		//aimShooterSpeed = -.75; //.7200
		}else if( vexRT[Btn7UXmtr2] ){
		//aimShooterSpeed = -.85;
		aimShooterSpeed = 457; // Cross Robot
		//shoot();
		}else if( vexRT[Btn8DXmtr2]) {
		aimShooterSpeed = 540; // FULL COURT
		}else if( vexRT[Btn8UXmtr2]) {
		}else {
		aimShooterSpeed = 0;
		offset = 0;
		loops = 0;
	}
	loops++;
}

//float kV = .1;
//float kA = .1;

// Error Constant
float kP = 0.3;
// Max Velocity the flywheel can go
float maxVel = 600;
// Max acceleration the flywheel can achieve (disregard initial spinup when finding this number)
float maxAcc = 20;
// Constant which scales velocity
float kV = (1.0/1170.0);
// Constant which scales acceleration
float kA = (1.0/20.0);
// The Threshold in which the flywheel should have extra power because it is accelerating.
float ACCELERATION_THRESHOLD = 100;
// The flywheel will run at full if the current velocity is below this
float PERCENT_OF_MAX_TO_RUN_AT_FULL_POWER = (1/3);
// Max power that acceleration can contribute to spinup
float MAX_ACC_POWER = 40.0;

float getFeedForwardPower(float goalVel, float curVel) {

	// Don't send any power if the goal is 0
	if (goalVel == 0) {
		return 0;
	}

	// Run at full power if the flywheel is below a third of its max vel
	// This makes spinup faster
	if (curVel < PERCENT_OF_MAX_TO_RUN_AT_FULL_POWER * maxVel) {
		return 127.0;
	}

	// Find goal acceleration
	float goalAcc;
	// if curVel is less than the threshold, goalAcc is maxAcc
	// else if curVel is above the the threshold, goalAcc is -maxAcc
	// else require no acc
	if(curVel < goalVel - ACCELERATION_THRESHOLD) {
		goalAcc =  maxAcc;
	} else if(curVel > goalVel + ACCELERATION_THRESHOLD) {
		goalAcc = -maxAcc;
	} else {
		goalAcc = 0;
	}

	// Scale all of the values and translate them to power values
	float scaledErrorPower =  kP * (float)((float)(goalVel) - (float)curVel ); // error * kP
	float scaledVelPower = 127.0 * (kV * (float)((float)(goalVel))); // calculate scaled vel then translate to power values
	float scaledAccPower = MAX_ACC_POWER * (kA * (float)((float)(goalAcc))); // calculate scaled acc then translate to power values
	if (abs(scaledErrorPower) > abs(scaledVelPower)) { // if the robot is changing shots, only use the scaled velocity and acc, not the scaled error
		scaledErrorPower = 0;
	}
	// Add all three terms up
	float power = (float)scaledVelPower + + (float)scaledAccPower + (float)scaledErrorPower;
	// if the power value is negative (meaning the flywheel is trying to slow down) run the flywheel at 20
	if (power < 0) {
		power = 20;
	}
	writeDebugStreamLine( "Current Vel: %3.0f, Aim Vel: %3.0f, Power: %3.0f, Scaled Err Pow: %3.0f, Scaled Vel Pow: %3.0f, Scaled Acc Pow: %3.0f", currentVelocity, goalVel, power, scaledErrorPower, scaledVelPower , scaledAccPower);
	return power;
}

/*
float lastVel = 0;
float lastError = 0;
float aimBuildUp = 0;
float maxVel = 550;
float maxAcc = 50;
float kV = (1/maxVel)/2;
float kA = (1/30)/50;
float kVFull = (1/maxVel)/1.2;
float kAFull = (1/maxAcc)/40;
float aimVel;
float aimAcc;
void shoot() {
if(currentVelocity < aimShooterSpeed - 20) {
if (aimVel < aimShooterSpeed) {
aimAcc = maxAcc;
aimVel = currentVelocity + maxAcc;
}else {
aimAcc = maxAcc/4;
aimVel = aimShooterSpeed;
}
aimAcc = maxAcc;
}
else if(currentVelocity > aimShooterSpeed + 20){
if(aimVel > aimShooterSpeed) {
aimAcc = -maxAcc;
aimVel = currentVelocity - maxAcc;
}else {
aimVel =  aimShooterSpeed;
aimAcc = -maxAcc/4;
}
}
else
{
aimVel = aimShooterSpeed;
aimAcc = 0;
}

float temp = (float)PIDRun( shooterConstantPID, (float)(aimVel + offset) - (float)currentVelocity );
if( aimVel > 500) {
shooterSpeed = 127+ offset;

} else {
shooterSpeed = 127*(kV * aimVel)+ 127*(kA * aimAcc) + temp;
}
if(currentVelocity < aimShooterSpeed - 40 && shooterSpeed < (127*(aimShooterSpeed * kV) + 127*(kA * aimAcc)) - 10)
{
shooterSpeed = 127;
}
lastError = shooterSpeed;

if (shooterSpeed >127) {
shooterSpeed = 127;
}else if (shooterSpeed < -127) {
shooterSpeed = -127;
}
if(aimShooterSpeed != 0) {
shooting = true;
char inFormat[32];
sprintf(inFormat, "%3.0f,%3.0f,%3.0f,%3.0f,%3.0f,%3.0f", currentVelocity, aimVel + offset, shooterSpeed, 127*(aimVel * kV), 127*(aimAcc * kA), temp);
char percent[32];
//sprintf(percent, "Shoot");
sendString(uartOne, inFormat);
//sendString(uartOne, percent);
runShooterAt(shooterSpeed);
}else if (curPower != 0) {
runShooterAt(curPower + offset);
}else if(holdPower) {
runShooterAt(20);
}else{
shooting = false;
shooterSpeed = 0;
runShooterAt(0);
}
}
*/
task shooterTask() {
	PIDInit(shooterQuickPID, 1, 0, .5); // .03 0 .75
	PIDInit(shooterConstantPID, .6, .08, .03); // .01 .001 .4
	PIDSetIntegralLimit(shooterQuickPID, 127);
	bool timerStarted = false;
	//runShooterAt(127);
	//wait1Msec(5000);
	pastShooter = nMotorEncoder[shooter1];
	PIDResetIntegral(shooterConstantPID);
	while(true) {
		clearTimer(T1);
		// Negative to compensate for polarity
		float curEn = ((float)nMotorEncoder[shooter1]);

		currentVelocity = -((float)((float)curEn - (float)pastShooter)/((float)shooterEquationDelayAmount)) * 10.0 * 60.0; // gets in rpm
		currentAcceleration = currentVelocity - previousShooterVelocity;
		checkAndFindSpeed();
		runShooterAt(getFeedForwardPower(aimShooterSpeed, currentVelocity));
	//	shoot();

		/*if(vexRT[Btn7DXmtr2]) {
		runShooterAt(127);
		if(time1[T2] > 550) {
		shooterIsReady = true;
		}else {
		shooterIsReady = false;
		}
		shooting = true;
		}else {
		shooting = false;
		}*/


		if ( abs(currentVelocity) < ( abs(aimShooterSpeed) + 26) && abs(currentVelocity) > ( abs(aimShooterSpeed) - 26 ) ) {
			if (timerStarted && time1[T3] > 150) {
				bLCDBacklight = true;
				shooterIsReady = true;
				}else if(!timerStarted) {
				clearTimer(T3);
				timerStarted = true;
			}else {	}
			}else {
			timerStarted = false;
			bLCDBacklight = false;
			shooterIsReady = false;
		}
		pastShooter = curEn;
		previousShooterVelocity = currentVelocity;
		if (time1[T1] < shooterEquationDelayAmount) {
			wait1Msec(shooterEquationDelayAmount - time1[T1]);
		}
	}
}
