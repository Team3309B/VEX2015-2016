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
/*
float TBHSpeed = 0;
float error = 0;
float lastError = 0;
float  TBHSpeed_at_zero = 0;
float TBHSpeed_approx = 40;
float firstCross = 1;*/
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
		//writeDebugStreamLine(inFormat);
		sendString(uartOne, inFormat);
		//sendString(uartOne, percent);

	runShooterAt(shooterSpeed);
	//runShooterAt(127);
		/*
		// -=----TBH =====---
		// calculate error in velocity
    // target is desired velocity
    // current is measured velocity
    error = aimShooterSpeed - currentVelocity;

    // Use Kp as gain
    TBHSpeed =  TBHSpeed + (error * .0008);

    // Clip - we are only going forwards
    if( TBHSpeed > 127 )
          TBHSpeed = 127;
    if( TBHSpeed < 0 )
          TBHSpeed = 0;

    // Check for zero crossing
    if( sgn(error) != sgn(lastError) ) {
        // First zero crossing after a new set velocity command
        if( firstCross ) {
            // Set drive to the open loop approximation
            TBHSpeed = TBHSpeed_approx;
            firstCross = 0;
        }
        else {
            TBHSpeed = 0.5 * ( TBHSpeed + TBHSpeed_at_zero );
          }

        // Save this drive value in the "tbh" variable
        TBHSpeed_at_zero = TBHSpeed;
    }
		runShooterAt(TBHSpeed);
    // Save last error
    lastError = error;
    */

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
		shoot();

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
