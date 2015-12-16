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

startTask(shooterAuto);
	aimShooterSpeed = 535;
	wait1Msec(4000);
	motor[intake] = 127;
	clearTimer(T2);
	int ballsShot = 0;
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			wait1Msec(1250);
			ballsShot++;
		}
		if(time1[T2] > 5000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}

	wait1Msec(4000);
	aimShooterSpeed = 0;
	motor[elevator2] = 0;
	/*
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
*/
}

void shootAndGo() {
	shootPreloadsFor(6000);
	runDriveAt(127);
	wait1Msec(3000);
	runDriveAt(0);
}

void shootAndGoAndShoot() {
	int angle =SensorValue[gyro];
	startTask(shooterAuto);
	aimShooterSpeed = 535;
	wait1Msec(4000);
	motor[intake] = 127;
	clearTimer(T2);
	int ballsShot = 0;
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			wait1Msec(1250);
			ballsShot++;
		}
		if(time1[T2] > 5000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}


	aimShooterSpeed = 0;
	runDriveAt(127);
	wait1Msec(1000);
	aimShooterSpeed = 358;
	wait1Msec(1500);
	runDriveAt(0);
	motor[elevator2] = 0;
	turnToAngle(angle);
	wait1Msec(4000);

}

void teamABlockAuto() {
	runDriveAt(127);
	wait1Msec(2000);
	runDriveAt(63);
	wait1Msec(1000);
	runDriveAt(0);
	wait1Msec(2750);
	runDriveAt(-127);
	wait1Msec(1500);
	runDriveAt(0);
}

void forwardAndShootBeforeCrossRight() {
	startTask(shooterAuto);
	aimShooterSpeed = 485; //aim
	moveForwardPID(170);
	wait1Msec(1000);
	turnToAngle(-380);
	wait1Msec(1000);
	moveForwardPID(1000);
	runDriveAt(0);
	wait1Msec(500);
	turnToAngle(-360);
	int ballsShot = 0;
	motor[intake] = 127;

	clearTimer(T2);
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			writeDebugStreamLine("EHHH");
			wait1Msec(850);
			ballsShot++;
		}
		if(time1[T2] > 4000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}
	wait1Msec(3000);
	motor[elevator2] = 0;
	motor[intake] = 0;
	aimShooterSpeed = 0;
	/*
	motor[elevator2] = 63;
	aimShooterSpeed = 350;
	runDriveAt(127);
	wait1Msec(2000);
	motor[elevator2] = 127;
	*/
}

void forwardAndShootBeforeCrossLeft() {
	startTask(shooterAuto);
	aimShooterSpeed = 485; //aim
	moveForwardPID(170);
	wait1Msec(1000);
	turnToAngle(380);
	wait1Msec(1000);
	moveForwardPID(1000);
	runDriveAt(0);
	wait1Msec(500);
	turnToAngle(360);
	int ballsShot = 0;
	motor[intake] = 127;

	clearTimer(T2);
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			writeDebugStreamLine("EHHH");
			wait1Msec(850);
			ballsShot++;
		}
		if(time1[T2] > 4000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}
	wait1Msec(3000);
	motor[elevator2] = 0;
	motor[intake] = 0;
	aimShooterSpeed = 0;
	/*
	motor[elevator2] = 63;
	aimShooterSpeed = 350;
	runDriveAt(127);
	wait1Msec(2000);
	motor[elevator2] = 127;
	*/
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
	startTask(shooterAuto);
	aimShooterSpeed =  438;
	wait1Msec(4000);
	setElevator(127);
	motor[intake] = 127;
}

void rightCrossAndPole() {
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
	moveForwardPID(1220, 35, 5000);
	motor[elevator2] = 127;
}

void leftCrossAndPole() {
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
	moveForwardPID(1220, 35, 5000);
	motor[elevator2] = 127;
}

void D986Auto() {
	motor[intake] = 127;
	setElevator(127);
	moveForwardPID(2000);
	setElevator(0);
	motor[intake] = 0;
}

void moveForwardAndShootBallsRight() {
	startTask(shooterAuto);
	aimShooterSpeed = 455;
	moveForwardPID(170);
	turnToAngle(-380);
	moveForwardPID(1600);
	turnToAngle(-325);
	int ballsShot = 0;
	motor[intake] = 127;

	clearTimer(T2);
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			writeDebugStreamLine("EHHH");
			wait1Msec(850);
			ballsShot++;
		}
		if(time1[T2] > 4000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}
	aimShooterSpeed = 0;
	turnToAngle(-1950);
	wait1Msec(500);
	moveForwardPID(800);
	turnToAngle(-1800);
	moveForwardPID(400, 30, 2000);

	wait1Msec(200);
	runDriveAt(-127);
	wait1Msec(750);
	turnToAngle(-300);
	runDriveAt(127);

	//turnToAngle(-1800);
	//moveForwardPID(1200);
}

void moveForwardAndShootBallsLeft() {
	startTask(shooterAuto);
	aimShooterSpeed = 455;
	moveForwardPID(170);
	turnToAngle(380);
	moveForwardPID(1600);
	turnToAngle(325);
	int ballsShot = 0;
	motor[intake] = 127;

	clearTimer(T2);
	while(ballsShot < 4) {
		if(currentAcceleration < -30) {
			motor[elevator2] = 0;
			writeDebugStreamLine("EHHH");
			wait1Msec(850);
			ballsShot++;
		}
		if(time1[T2] > 4000)
			ballsShot = 50;
		motor[elevator2] = 127;
	}
	aimShooterSpeed = 0;
	turnToAngle(1950);
	wait1Msec(500);
	moveForwardPID(800);
	turnToAngle(1800);
	moveForwardPID(400, 30, 2000);

	wait1Msec(200);
	runDriveAt(-127);
	wait1Msec(750);
	turnToAngle(300);
	runDriveAt(127);

	//turnToAngle(-1800);
	//moveForwardPID(1200);
}

void turnToOpponentGoalAndShot() {
	startTask(shooterAuto);
	aimShooterSpeed = 447;
	wait1Msec(4000);
	motor[elevator2] = 127;
	wait1Msec(2000);
	motor[intake] = 127;
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
		forwardAndShootBeforeCrossRight();
		break;
	case 2:
		forwardAndShootBeforeCrossLeft();
		break;
	case 3:
		moveForwardAndShootBallsRight();
		break;
	case 4:
		moveForwardAndShootBallsLeft();
		break;
	case 5:
		rightCrossAndPole();
		break;
	case 6:
		leftCrossAndPole();
		break;
	case 7:
		shootPreloadsFor(6000);
		break;
	case 8:
		shootAndGo();
		break;
	case 9:
		shootAndGoAndShoot();
		break;
	case 10:
		D986Auto();
		break;
	case 11:
		teamABlockAuto();
		break;
	case 12:
		turnToOpponentGoalAndShot();
		break;
	case 13:
		runDriveAt(127);
		wait1Msec(3000);
		runDriveAt(0);
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}
