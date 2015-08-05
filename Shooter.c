void runShooterAt(int power) {
	motor[shooter1] = power;
	motor[shooter2] = power;
	motor[shooter3] = power;
	motor[shooter4] = power;
}

void checkAndFindSpeed() {
	if (vexRT[Btn7DXmtr2])
		aimShooterSpeed = 40;
	else if( vexRT[Btn7LXmtr2] )
		aimShooterSpeed = 60; //.5600
	else if( vexRT[Btn7RXmtr2]  )
		aimShooterSpeed = 80; //.7200
	else if( vexRT[Btn7UXmtr2]  )
		aimShooterSpeed = 100;
	else if( vexRT[Btn8UXmtr2] )
		aimShooterSpeed = 127; // .8400
	else
		aimShooterSpeed = 0;
}

void shoot() {
	float currentVelocity =  (nMotorEncoder[shooter1] - pastShooter)/shooterEquationDelayAmount;
	writeDebugStreamLine("EN: %d, past: %d, delay: %d", nMotorEncoder[shooter1], pastShooter, shooterEquationDelayAmount);
	writeDebugStreamLine("SHOOTER VELOCITY: %5.5f", (float)((float)nMotorEncoder[shooter1] - (float)pastShooter)/(float)shooterEquationDelayAmount);
	writeDebugStreamLine("SHOOTER ENCODER : %i", nMotorEncoder[shooter1] );
	if ( ticksSinceShoot < TICKS_TO_USE_QUICK_SPEED_AFTER_SHOOTING )
		shooterSpeed = shooterSpeed + PIDRun( shooterQuickPID, aimShooterSpeed - nMotorEncoder[shooter1] );
	else
		shooterSpeed = shooterSpeed + PIDRun( shooterConstantPID, aimShooterSpeed - nMotorEncoder[shooter1] );
	//runShooterAt(shooterSpeed);
	if( currentVelocity < previousShooterVelocity - SHOOTER_OFFSET_AFTER_SHOOTING) // if the current vel is less then the previous one minus a certain offset, then set to quick for x ticks
		ticksSinceShoot = 0;
	else
		ticksSinceShoot++;
	previousShooterVelocity = currentVelocity;
	pastShooter = nMotorEncoder[shooter1];
}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 1, 1);
	PIDInit(shooterConstantPID, .5, 0, .5);
	PIDSetIntegralLimit(shooterQuickPID, 1000);
	while(true) {
		/*if(vexRT[Btn8UXmtr2]){
			motor[shooter4] = 127;
			motor[shooter3] = 127;
			motor[shooter2] = 127;
			motor[shooter1] = 127;
		}else {
			runShooterAt(0);
		}*/
		checkAndFindSpeed();
		runShooterAt(aimShooterSpeed);
		shoot();
		delay(shooterEquationDelayAmount);
	}
}
