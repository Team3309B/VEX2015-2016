
PID rightPositionEncoder;
PID leftPositionEncoder;
PID turningPID;
void setLeftDrive(int x) {
	motor[leftDrive] = x;
	motor[leftDriveExtra] = x;
}

void setRightDrive(int x) {
	motor[rightDrive] = x;
	motor[rightDriveExtra] = x;
}

void runDriveAt(int x) {
	setLeftDrive(x);
	setRightDrive(x);
}

void stopDrive() {
	runDriveAt(0);
}

void moveForward(int encoders) {
	SensorValue[rightDriveTrain] = 0;
	SensorValue[leftDriveTrain] = 0;
	float encoderAvg = (abs(SensorValue[rightDriveTrain]) + abs(SensorValue[leftDriveTrain]) )/2;
	while ( abs(encoderAvg) < abs(encoders)) {
		encoderAvg = (abs(SensorValue[rightDriveTrain]) + abs(SensorValue[leftDriveTrain]) )/2;
		setRightDrive(127);
		setLeftDrive(127);
		writeDebugStreamLine("%4.4f", encoderAvg);
	}
	setRightDrive(0);
	setLeftDrive(0);
}

void moveForwardPID(int encoder) {
	SensorValue(rightDriveTrain) = 0;
	SensorValue(leftDriveTrain) = 0;
	PIDInit(leftPositionEncoder, .13, .001, 0.1);
	PIDInit(rightPositionEncoder, .13, .001, 0.1);
	PIDInit(turningPID, .08, .01);
	bool running = true;
	bool timerStarted = false;
	float rightSpeed = 0, leftSpeed = 0;
	float turnSpeed = 0;
	float aimGyro = SensorValue[gyro];
	while(running) {
		float currentEn = (abs(SensorValue(rightDriveTrain)) + abs(SensorValue(leftDriveTrain)))/2;
		leftSpeed = PIDRun(leftPositionEncoder, (encoder) - abs(SensorValue(leftDriveTrain)));
		rightSpeed = PIDRun(rightPositionEncoder, (encoder) -  abs(SensorValue(rightDriveTrain)));
		turnSpeed = PIDRun(turningPID, aimGyro - SensorValue[gyro]);
		setLeftDrive(leftSpeed + turnSpeed);
		setRightDrive(leftSpeed - turnSpeed);
		//writeDebugStreamLine("RIGHT: %4.4f, LEFHT: %4.4f", SensorValue(rightDriveTrain), SensorValue(leftDriveTrain));
		//writeDebugStreamLine("cur: %4.4f , pow: %4.4f aoim: %4.4f", currentEn, driveSpeed, encoder);
		if (abs(SensorValue(leftDriveTrain)) > encoder - 100 && abs(SensorValue(leftDriveTrain)) < encoder + 100 && !timerStarted) {
			clearTimer(T4);
			timerStarted = true;
		}else if (timerStarted) {

		}else {
			timerStarted = false;
		}
		if (timerStarted && time1[T4] > 100) {
				running = false;
		}
		wait1Msec(150);
	}
	writeDebugStreamLine("DONE");
}

void moveForwardPID(int encoder, int power) {
	SensorValue(rightDriveTrain) = 0;
	SensorValue(leftDriveTrain) = 0;
	PIDInit(leftPositionEncoder, .13, .001, 0.1);
	PIDInit(rightPositionEncoder, .13, .001, 0.1);
	PIDInit(turningPID, .1, .01);
	bool running = true;
	bool timerStarted = false;
	float rightSpeed = 0, leftSpeed = 0;
	float turnSpeed = 0;
	float aimGyro = SensorValue[gyro];
	while(running) {
		float currentEn = (abs(SensorValue(rightDriveTrain)) + abs(SensorValue(leftDriveTrain)))/2;
		leftSpeed = PIDRun(leftPositionEncoder, (encoder) - abs(SensorValue(leftDriveTrain)));
		rightSpeed = PIDRun(rightPositionEncoder, (encoder) -  abs(SensorValue(rightDriveTrain)));
		turnSpeed = PIDRun(turningPID, aimGyro - SensorValue[gyro]);
		setLeftDrive(power + turnSpeed);
		setRightDrive(power - turnSpeed);
		//writeDebugStreamLine("RIGHT: %4.4f, LEFHT: %4.4f", SensorValue(rightDriveTrain), SensorValue(leftDriveTrain));
		//writeDebugStreamLine("cur: %4.4f , pow: %4.4f aoim: %4.4f", currentEn, driveSpeed, encoder);
		if (abs(SensorValue(leftDriveTrain)) > encoder - 100 && abs(SensorValue(leftDriveTrain)) < encoder + 100 && !timerStarted) {
			clearTimer(T4);
			timerStarted = true;
		}else if (timerStarted) {

		}else {
			timerStarted = false;
		}
		if (timerStarted && time1[T4] > 100) {
				running = false;
		}
		wait1Msec(150);
	}
	writeDebugStreamLine("DONE");
}

PID gyroTurning;
void workToHoldAngle(int desAngle) {

	float term = PIDRun(gyroTurning, desAngle - SensorValue[gyro]);
		setRightDrive(term);
		setLeftDrive(-term);
}


void turnToAngle(int desAngle) {
		PIDInit(gyroTurning, .1, .01, .07);
	bool running = true;
	bool timerStarted = false;
	while(running) {
		workToHoldAngle(desAngle);
		if (SensorValue[gyro] > desAngle - 50 && SensorValue[gyro] < desAngle + 50 && !timerStarted) {
			clearTimer(T4);
			timerStarted = true;
		}else if (timerStarted) {

		}else {
			timerStarted = false;
		}
		if (timerStarted && time1[T4] > 100) {
				running = false;
		}
		wait1Msec(150);
	}
	writeDebugStreamLine("DONE");
}


float limit(float v, float limit) {
    return (abs(v) < limit) ? v : limit * (v < 0 ? -1 : 1);
 }
float pastLeftPower = 0;
float pastRightPower = 0;
float quickStopAccumulator = 0;
void chezyDrive(float throttle, float wheel, bool isQuickTurn) {
	//writeDebugStreamLine("%4.4f %4.4f", throttle , wheel);
    float wheelNonLinearity;

    //wheel = threshold(wheel, wheelDeadband);
    //throttle = threshold(throttle, throttleDeadband);

    float negInertia = wheel - oldWheel;
    oldWheel = wheel;
		//writeDebugStreamLine("negInertia %4.4f", negInertia);
    wheelNonLinearity = 0.6;
    // Apply a sin function that's scaled to make it feel better.
    wheel = sin(PI / 2.0 * wheelNonLinearity * wheel)
              / sin(PI / 2.0 * wheelNonLinearity);
    wheel = sin(PI / 2.0 * wheelNonLinearity * wheel)
              / sin(PI / 2.0 * wheelNonLinearity);
    wheel = sin(PI / 2.0 * wheelNonLinearity * wheel)
              / sin(PI / 2.0 * wheelNonLinearity);
   // writeDebugStreamLine("newWheel (after sin) %4.4f", wheel);

    float leftPwm, rightPwm, overPower;
    float sensitivity;

    float angularPower;
    float linearPower;

    // Negative inertia!
    float negInertiaAccumulator = 0.0;
    float negInertiaScalar;

      if (wheel * negInertia > 0.0) {
        negInertiaScalar = 1.5;
      } else {
        if (abs(wheel) > 0.65) {
          negInertiaScalar = 5.0;
        } else {
          negInertiaScalar = 3.0;
        }
      }
      sensitivity = .9;

    float negInertiaPower = negInertia * negInertiaScalar;
    negInertiaAccumulator += negInertiaPower;
	//	writeDebugStreamLine("negAccumulatotr %4.4f", negInertiaAccumulator);
    wheel = wheel + negInertiaAccumulator;
    if (negInertiaAccumulator > 1.0) {
      negInertiaAccumulator -= 1.0;
    } else if (negInertiaAccumulator < -1.0) {
      negInertiaAccumulator += 1.0;
    } else {
      negInertiaAccumulator = 0.0;
    }
    linearPower = throttle;

    // Quickturn!
    if (isQuickTurn) {
      if (abs(linearPower) < 0.2) {
        float alpha = 0.2;
        quickStopAccumulator = (1.0 - alpha) * quickStopAccumulator + alpha
                * limit(wheel, 1.0) * 5.0;
      }
      overPower = 1.0;
      sensitivity = 1.0;
      angularPower = wheel;
    } else {
      overPower = 0.0;
      angularPower = abs(throttle) * (wheel * 1.1) * sensitivity - quickStopAccumulator;
      if (abs(throttle) < .1) {
      	angularPower = wheel;
    	}
      if (quickStopAccumulator > 1.0) {
        quickStopAccumulator -= 1.0;
      } else if (quickStopAccumulator < -1.0) {
        quickStopAccumulator += 1.0;
      } else {
        quickStopAccumulator = 0.0;
      }
    }
		//float CONSTANT = 20;
    rightPwm = leftPwm = linearPower;
    leftPwm += angularPower;
    rightPwm -= angularPower;


		pastRightPower = rightPwm;
		pastLeftPower = leftPwm;
    if (leftPwm > 1.0) {
      rightPwm -= overPower * (leftPwm - 1.0);
      leftPwm = 1.0;
    } else if (rightPwm > 1.0) {
      leftPwm -= overPower * (rightPwm - 1.0);
      rightPwm = 1.0;
    } else if (leftPwm < -1.0) {
      rightPwm += overPower * (-1.0 - leftPwm);
      leftPwm = -1.0;
    } else if (rightPwm < -1.0) {
      leftPwm += overPower * (-1.0 - rightPwm);
      rightPwm = -1.0;
    }
	setLeftDrive((leftPwm * 127.0));
	setRightDrive((rightPwm * 127.0));
	//motor[rightDriveExtra] = (rightPwm * 127.0);
	//motor[leftDriveExtra] =  (leftPwm * 127.0);
}

void lameDrive() {
	float leftSpeed = threshold(vexRT[Ch3], 25) + threshold(vexRT[Ch1], 25);
	float rightSpeed = threshold(vexRT[Ch3], 25) - threshold(vexRT[Ch1], 25);
	// Find current velocities
	float leftDriveVelocity = (float)(((float)-SensorValue[leftDriveTrain] - pastLeft) / driveEquationDelayAmount);
	float rightDriveVelocity = (float)(((float)-SensorValue[rightDriveTrain] - pastRight) / driveEquationDelayAmount);
	float gyroAngularVelocity = (float)(((float)SensorValue[gyro] - pastGyro) / driveEquationDelayAmount);
	//writeDebugStreamLine(" DRIVE: rightVel: %4.4f leftVel: %4.4f ang: %4.4f", rightDriveVelocity, leftDriveVelocity, gyroAngularVelocity);
	//writeDebugStreamLine(" GYRO: %4.4f",SensorValue[gyro]);
	//writeDebugStreamLine("LEFT: %d RIGHT: %d", leftSpeed, rightSpeed);
	setRightDrive(rightSpeed);
	setLeftDrive(leftSpeed);
		// Store past position so next time, the loop can find velocities
	pastRight = (float)-SensorValue[rightDriveTrain];
	pastLeft = (float)-SensorValue[leftDriveTrain];
	pastGyro = (float)SensorValue[gyro];
}

task driveTask() {
	PIDInit(gyroDrivePID, .19, .09);
	PIDInit(driveRightDrivePID, .41,.1);
	PIDInit(driveLeftDrivePID, .41, .1);
	PIDInit(holdAnglePID, .2, .095);
	PIDInit(holdEnPID, .8, 0);
	PIDInit(gyroTurning, .2, .095);
	bool isFirstTimePressed = true;
	int lockedAngle = 0;
	while(true) {

			float toSend = ((float)vexRT[Ch3])/127;
			float toSendTurn = ((float)vexRT[Ch1])/127;
			chezyDrive((float)(toSend), (float)(toSendTurn), vexRT[Btn5U]);
			isFirstTimePressed = true;
			//lameDrive();
			//driveHalo( threshold(vexRT[Ch3], 10), threshold(vexRT[Ch1], 10) );
		//wait1Msec(driveEquationDelayAmount);
	}
}
