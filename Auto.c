float shooterSpeedAuto = 0;
float aimShooterSpeedAuto = 610;
task shooterAuto() {
	PIDInit(shooterConstantPID, .06, .000099,.81); // .152, .000099 .78
	bool timerStarted = false;
	while(true) {
		float curEn = (float) nMotorEncoder[shooter1];
		currentVelocity = -((float)((float)curEn - (float)pastShooter)/((float)shooterEquationDelayAmount)) * 10.0 * 60.0;
		shooterSpeedAuto += PIDRun(shooterConstantPID, aimShooterSpeedAuto - currentVelocity);
		runShooterAt(shooterSpeedAuto);
		pastShooter = curEn;

		if ( abs(currentVelocity) < ( abs(aimShooterSpeedAuto) + 26) && abs(currentVelocity) > ( abs(aimShooterSpeedAuto) - 26 ) ) {
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
		wait1Msec(shooterEquationDelayAmount);
	}
}

void shootAtCrossUpCloseShot() {
	aimShooterSpeedAuto = 460; // Cross Shot
	startTask(shooterAuto);
	moveForwardPID(500); // Move Forward Some
	turnToAngle(450); // Turn
	moveForwardPID(500);
	turnToAngle(-450);
	moveForwardPID(500);
	turnToAngle(450);
	setElevator(127);
	motor[intake] = 127;

	wait1Msec(3000);
	stopTask(shooterAuto);
	moveForwardPID(3000);

	aimShooterSpeedAuto = 437;
	startTask(shooterAuto);

	runDriveAt(50);
	while (!shooterIsReady) {}
	setElevator(127);
}

void shootPreloadsFor(int time) {

	aimShooterSpeedAuto = 450; // Cross Shot
	startTask(shooterAuto);
	clearTimer(T1);
	wait1Msec(3500);
	setElevator(127);// shoot first ball
	wait1Msec(750);
	setElevator(-20);
	wait1Msec(1000);
	setElevator(127); // shooter second ball
	wait1Msec(1000);
	motor[intake] = 127;
	setElevator(127);
	wait1Msec(3000);
	//setElevator(0);
	//motor[intake] = 0;
	stopTask(shooterAuto);
	//moveForwardPID(2700);
	stopDrive();

}

void shootAtCross() {
	aimShooterSpeedAuto = 460; // Cross Shot
	startTask(shooterAuto);
	moveForwardPID(200); // Move Forward Some
	turnToAngle(1000); // Turn
	moveForwardPID(500);
	turnToAngle(450); // Turn to Goal
	setElevator(127);
	motor[intake] = 127;
}

void programmingSkills() {

	aimShooterSpeedAuto = 440;
	startTask(shooterAuto);
	wait1Msec(4000);
	setElevator(127);
	motor[intake] = 127;
}

void D986Auto() {
	motor[intake] = 127;
	setElevator(127);
	moveForwardPID(2000);
	setElevator(0);
	motor[intake] = 0;
}
void startauton()
{
	//moveForwardPID(1500);
	//shootAtCrossUpCloseShot();
	shootPreloadsFor(6000);
	//programmingSkills();
	//D986Auto();
	// shootAtCross();
}
