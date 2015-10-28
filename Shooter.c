void runShooterAt(int power) {
	motor[shooter1] = power;
	motor[shooter2] = power;
	motor[shooter3] = power;
	motor[shooter4] = power;
}

int loops =0;
bool pressed = false;
bool holdPower = false;
int curPower = 0;
int offset = 0;
void checkAndFindSpeed() {
	if (vexRT[Btn6UXmtr2] &&!pressed) {
		offset += 5;
		pressed = true;
	}else if (vexRT[Btn6DXmtr2] && !pressed) {
		offset -= 5;
		pressed = true;
	}else {
		pressed = false;
	}
	if (vexRT[Btn7DXmtr2]){
		aimShooterSpeed = 335; // Up Close
		//aimShooterSpeed = -.25;
		}else if( vexRT[Btn7LXmtr2] ){
		aimShooterSpeed = 409; // Up Close Robot
		//aimShooterSpeed = -.6; //.5600
		}else if( vexRT[Btn7RXmtr2] ){
		aimShooterSpeed = 440; // Cross
		//aimShooterSpeed = -.75; //.7200
		}else if( vexRT[Btn7UXmtr2] ){
		//aimShooterSpeed = -.85;
		aimShooterSpeed = 465; // Cross Robot
		//shoot();
		}else if( vexRT[Btn8DXmtr2]) {
			aimShooterSpeed = 520; // FULL COURT
		}else if( vexRT[Btn8UXmtr2]) {
		}else {
			aimShooterSpeed = 0;
			offset = 0;
			loops = 0;
		}
		loops++;
}

void shoot() {
	//if (currentVelocity > aimShooterSpeed - 75) {
	shooterSpeed += (float)PIDRun( shooterConstantPID, (float)(aimShooterSpeed + offset) - (float)currentVelocity );
	//}else {
	//shooterSpeed += (float)PIDRun( shooterConstantPID, (float)(aimShooterSpeed + offset) - (float)currentVelocity );
	//}

	if (shooterSpeed >127) {
		shooterSpeed = 127;
	}else if (shooterSpeed < -127) {
		shooterSpeed = -127;
	}
	/*if(currentVelocity < (aimShooterSpeed - 90) ) {
	runShooterAt(90);
	char inFormat[32];
	sprintf(inFormat, "%3.3f,%3.3f,%3.3f,", currentVelocity, aimShooterSpeed, 127);
	writeDebugStreamLine(inFormat);
	sendString(uartOne, inFormat);
	return;
	}*/
	if(aimShooterSpeed != 0) {
		shooting = true;
		char inFormat[32];
		sprintf(inFormat, "%3.3f,%3.3f,%3.3f,%3.3f, %3.3f", currentVelocity, aimShooterSpeed + offset, shooterSpeed, curElevatorState, motor[elevator2]);
		writeDebugStreamLine(inFormat);
		sendString(uartOne, inFormat);
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

task shooterTask() {
	PIDInit(shooterQuickPID, .04, 0, 1);
	PIDInit(shooterConstantPID, .03, 0, .4); // .152, .000099 .78; .06, .000099, .81
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
