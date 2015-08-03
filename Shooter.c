void checkAndFindSpeed() {
	if (vexRT[Btn7D])
		aimShooterSpeed = 40;
	else if( vexRT[Btn7U] )
		aimShooterSpeed = 60;
	else if( vexRT[Btn7L] )
		aimShooterSpeed = 80;
	else if( vexRT[Btn7R] )
		aimShooterSpeed = 100;
	else if( vexRT[Btn8U] )
		aimShooterSpeed = 127;
}

void shoot() {

}

task shooterTask() {
	PIDInit(shooterQuickPID, 1, 1, 1);
	PIDInit(shooterConstantPID, .5, .5, .5);
	PIDSetIntegralLimit(shooterQuickPID, 1000);
	while(true) {
		checkAndFindSpeed();
		shoot();
	}
}
