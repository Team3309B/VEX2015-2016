void runShooterAt(int power) {
	setMotor(shooter1, power);
	setMotor(shooter2, power);
	setMotor(shooter3, power);
	setMotor(shooter4, power);
}

void checkAndFindSpeed() {
	if (vexRT[Btn7DXmtr2]){
			aimShooterSpeed = .39;
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
			aimShooterSpeed = .92
	}else if (vexRT[Btn8DXmtr2]){
		aimShooterSpeed = .78;
	}else if(vexRT[Btn8LXmtr2]) {
		aimShooterSpeed = .86;
	}else if(vexRT[Btn8RXmtr2]) {
		aimShooterSpeed = 1;
	}else
		aimShooterSpeed = 0;
}

void shoot() {
	if(aimShooterSpeed != 0) {
		shooterSpeed = shooterSpeed + (float)PIDRun( shooterConstantPID, (float)aimShooterSpeed - (float)currentVelocity );
		writeDebugStreamLine("%4.4f, %4.4f, %4.4f", currentVelocity, aimShooterSpeed, shooterSpeed);
		runShooterAt(shooterSpeed);
	}else {
		runShooterAt(0);
	}
}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 1, 1);
	PIDInit(shooterConstantPID, .05, 0, 0);
	PIDSetIntegralLimit(shooterQuickPID, 1000);
	while(true) {
		currentVelocity = ((float)((float)nMotorEncoder[shooter1] - (float)pastShooter)/(float)shooterEquationDelayAmount) * 40.0;
		checkAndFindSpeed();
		//shoot();
		runShooterAt(aimShooterSpeed);
		previousShooterVelocity = currentVelocity;
		pastShooter = nMotorEncoder[shooter1];
		delay(shooterEquationDelayAmount);
	}
}
