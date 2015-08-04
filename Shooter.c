void runShooterAt(int power) {
	motor[shooterLeft] = power;
	motor[shooterRight] = power;
}

void checkAndFindSpeed() {
	if (isPressed(Button7D))
		aimShooterSpeed = 40;
	else if( isPressed(Button7U) )
		aimShooterSpeed = 60;
	else if( isPressed(Button7L) )
		aimShooterSpeed = 80;
	else if( isPressed(Button7R) )
		aimShooterSpeed = 100;
	else if( isPressed(Button7U) )
		aimShooterSpeed = 127;
}

void shoot() {
	float currentVelocity =  (nMotorEncoder[shooterRight] - pastShooter)/shooterEquationDelayAmount ;
	if ( ticksSinceShoot < TICKS_TO_USE_QUICK_SPEED_AFTER_SHOOTING )
		shooterSpeed = shooterSpeed + PIDRun( shooterQuickPID, aimShooterSpeed - nMotorEncoder[shooterRight] );
	else
		shooterSpeed = shooterSpeed + PIDRun( shooterConstantPID, aimShooterSpeed - nMotorEncoder[shooterRight] );
	runShooterAt(shooterSpeed);
	if( currentVelocity < previousShooterVelocity - SHOOTER_OFFSET_AFTER_SHOOTING) // if the current vel is less then the previous one minus a certain offset, then set to quick for x ticks
		ticksSinceShoot = 0;
	else
		ticksSinceShoot++;

	previousShooterVelocity = currentVelocity;
	pastShooter = nMotorEncoder[shooterRight];
}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 1, 1);
	PIDInit(shooterConstantPID, .5, 0, .5);
	PIDSetIntegralLimit(shooterQuickPID, 1000);
	while(true) {
		checkAndFindSpeed();
		shoot();
		delay(shooterEquationDelayAmount);
	}
}
