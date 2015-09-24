void runShooterAt(int power) {
	motor[shooter1] = power;
	motor[shooter2] = power;
	motor[shooter3] = power;
	motor[shooter4] = power;
}



void checkAndFindSpeed() {
	if (vexRT[Btn7DXmtr2]){
		aimShooterSpeed = 485;
		//aimShooterSpeed = -.25;
		}else if( vexRT[Btn7LXmtr2] ){
		aimShooterSpeed = 495;
		//aimShooterSpeed = -.6; //.5600
		}else if( vexRT[Btn7RXmtr2]  ){
		aimShooterSpeed = 500;
		//aimShooterSpeed = -.75; //.7200
		}else if( vexRT[Btn7UXmtr2] ){
		//aimShooterSpeed = -.85;
		aimShooterSpeed = 530;
		//shoot();
		}else if( vexRT[Btn8UXmtr2] ) {
		//aimShooterSpeed = -2.5; // .8400
		aimShooterSpeed = 620;
		}else if (vexRT[Btn8DXmtr2]){
		aimShooterSpeed = 590;
		}else if(vexRT[Btn8LXmtr2]) {
		aimShooterSpeed = 600;
		}else if(vexRT[Btn8RXmtr2]) {
		aimShooterSpeed = 610;
		}else {
		aimShooterSpeed = 0;
	}
}

void shoot() {
	shooterSpeed += (float)PIDRun( shooterConstantPID, (float)aimShooterSpeed - (float)currentVelocity );
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
		if (currentVelocity < pastShooter - 100) {

		}
		char inFormat[32];
		sprintf(inFormat, "%3.3f,%3.3f,%3.3f,", currentVelocity, aimShooterSpeed, shooterSpeed);
		writeDebugStreamLine(inFormat);
		sendString(uartOne, inFormat);
		runShooterAt(shooterSpeed);
		}else {
		shooting = false;
		shooterSpeed = 0;
		runShooterAt(0);
	}
}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 0, 0);
	PIDInit(shooterConstantPID, .0152, .000001, .78);
	PIDSetIntegralLimit(shooterQuickPID, 127);
	bool timerStarted = false;
	//runShooterAt(127);
	//wait1Msec(5000);
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


		if ( abs(currentVelocity) < ( abs(aimShooterSpeed) + 15) && abs(currentVelocity) > ( abs(aimShooterSpeed) - 15 ) ) {
			if (timerStarted && time1[T3] > 500) {
				shooterIsReady = true;
				}else if(!timerStarted) {
				clearTimer(T3);
				timerStarted = true;
				}else {
			}
			}else {
			timerStarted = false;
			shooterIsReady = false;
		}
		pastShooter = curEn;
		previousShooterVelocity = currentVelocity;
		if (time1[T1] < shooterEquationDelayAmount) {
			wait1Msec(shooterEquationDelayAmount - time1[T1]);
		}
	}
}
