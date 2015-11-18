task shooterAuto() {
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
		shoot();
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

void shootAtCrossUpCloseShot() {
	aimShooterSpeed = 460; // Cross Shot
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

	aimShooterSpeed = 437;
	startTask(shooterAuto);

	runDriveAt(50);
	while (!shooterIsReady) {}
	setElevator(127);
}

void shootPreloadsFor(int time) {

	//aimShooterSpeed = 450; // Cross Shot
	//startTask(shooterAuto);
	runShooterAt(127);
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
//	stopTask(shooterAuto);
	//moveForwardPID(2700);
	runShooterAt(0);
	setElevator(0);
	stopDrive();

}

void shootAtCross() {
	aimShooterSpeed = 460; // Cross Shot
	startTask(shooterAuto);
	moveForwardPID(200); // Move Forward Some
	turnToAngle(1000); // Turn
	moveForwardPID(500);
	turnToAngle(450); // Turn to Goal
	setElevator(127);
	motor[intake] = 127;
}

void programmingSkills() {

	runShooterAt(127);
	wait1Msec(4000);
	setElevator(127);
	motor[intake] = 127;
}

void leftCrossAndPole() {
	startTask(shooterAuto);


	moveForwardPID(170);
	wait1Msec(100);
	turnToAngle(-420);

	wait1Msec(100);
	moveForwardPID(1220);
	aimShooterSpeed = 415;
	wait1Msec(400);
	turnToAngle(100);
	wait1Msec(400);
	moveForwardPID(700);
	wait1Msec(400);
	turnToAngle(-430);
	wait1Msec(401);
	moveForwardPID(520);

	//shoot
	motor[elevator2] = 100;

	motor[intake] = 127;
	wait1Msec(3000);
	motor[elevator2] = 127;

	//intaking
	//elevator
	aimShooterSpeed = 350;
	moveForwardPID(1220, 35);
	motor[elevator2] = 127;
}

void rightCrossAndPole() {
	startTask(shooterAuto);


	moveForwardPID(170);
	wait1Msec(100);
	turnToAngle(420);

	wait1Msec(100);
	moveForwardPID(1220);
	aimShooterSpeed = 415;
	wait1Msec(400);
	turnToAngle(-100);
	wait1Msec(400);
	moveForwardPID(700);
	wait1Msec(400);
	turnToAngle(	430);
	wait1Msec(401);
	moveForwardPID(520);

	//shoot
	motor[elevator2] = 100;

	motor[intake] = 127;
	wait1Msec(3000);
	motor[elevator2] = 127;

	//intaking
	//elevator
	aimShooterSpeed = 350;
	moveForwardPID(1220, 35);
	motor[elevator2] = 127;
}

void getSideStackRight() {

}

void getSideStackLeft() {

}

void D986Auto() {
	motor[intake] = 127;
	setElevator(127);
	moveForwardPID(2000);
	setElevator(0);
	motor[intake] = 0;
}

void startauton() {

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	//this switch case chooses the auto to run based off of the LCD Screen's choice
	//to see how count is choosen, reference LCDAuto.c
	switch(count){
	case 0:
		wait1Msec(15000);
		break;
	case 1:
		shootPreloadsFor(6000);
		break;
	case 2:
		rightCrossAndPole();
		break;
	case 3:
		leftCrossAndPole();
		break;
	case 4:
		getSideStackLeft()
		break;
	case 5:
		getSideStackRightt()
		break;
	case 6:
		D986Auto();
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}
