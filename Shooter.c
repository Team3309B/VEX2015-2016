void runShooterAt(int power) {
	motor[shooter1] = power;
	motor[shooter2] = power;
	motor[shooter3] = power;
	motor[shooter4] = power;
}

void sendString ( TUARTs uart, char* hello ) {
	for(int i = 0; i < 32; i++) {
		sendChar(uart, hello[i]);
	}
	sendChar(uart, '\r');
	sendChar(uart, '\n');
}

void checkAndFindSpeed() {
	if (vexRT[Btn7DXmtr2]){
			aimShooterSpeed = 540;
		//aimShooterSpeed = -.25;
	}else if( vexRT[Btn7LXmtr2] ){
			aimShooterSpeed = .47;
		//aimShooterSpeed = -.6; //.5600
	}else if( vexRT[Btn7RXmtr2]  ){
			aimShooterSpeed = .70;
		//aimShooterSpeed = -.75; //.7200
	}else if( vexRT[Btn7UXmtr2] ){
		//aimShooterSpeed = -.85;
		aimShooterSpeed = .59;
		//shoot();
	}else if( vexRT[Btn8UXmtr2] ) {
		//aimShooterSpeed = -2.5; // .8400
			aimShooterSpeed = .92;
	}else if (vexRT[Btn8DXmtr2]){
		aimShooterSpeed = .78;
	}else if(vexRT[Btn8LXmtr2]) {
		aimShooterSpeed = .86;
	}else if(vexRT[Btn8RXmtr2]) {
		aimShooterSpeed = 1;
	}else {
		aimShooterSpeed = 0;
	}
}

void shoot() {

	if(aimShooterSpeed != 0) {
		shooterSpeed += (float)PIDRun( shooterConstantPID, (float)aimShooterSpeed - (float)currentVelocity );
		char inFormat[32];
		sprintf(inFormat, "%3.3f,%3.3f,%3.3f,", currentVelocity, aimShooterSpeed, shooterSpeed);
		writeDebugStreamLine(inFormat);
		sendString(uartOne, inFormat);
		runShooterAt(shooterSpeed);
	}else {
		shooterSpeed = 0;
		runShooterAt(0);
	}
}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 0, 0);
	PIDInit(shooterConstantPID, .011, .001, .045);
	PIDSetIntegralLimit(shooterQuickPID, 127);
	while(true) {
		clearTimer(T1);
		// Negative to compensate for polarity
		float curEn = ((float)nMotorEncoder[shooter1]);
		currentVelocity = -((float)((float)curEn - (float)pastShooter)/((float)shooterEquationDelayAmount)) * 10.0 * 60.0; // gets in rpm
		checkAndFindSpeed();
		shoot();
		pastShooter = curEn;
		wait1Msec(shooterEquationDelayAmount - time1[T1]);
	}
}
