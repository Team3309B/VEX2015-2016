void setElevator(int power) {
	motor[elevator2] = power;
}



float goalElevatorVelocity = 0.8;
int timeIntervalElevator = 100;
float currentPIDValue = 0;
// Elevator and Hopper Mechanism
bool getSwitch() {
	if(SensorValue[elevatorTopLimitSwitch] && SensorValue[elevatorBotLimitSwitch]) {
		return false;
	}else if(!SensorValue[elevatorTopLimitSwitch] && !SensorValue[elevatorBotLimitSwitch]) {
		return false;
	}else if (SensorValue[elevatorTopLimitSwitch] || SensorValue[elevatorBotLimitSwitch]) {
		return true;
	}
	return false;
}

task elevatorTask() {
	PIDInit(elevatorPID, 10, 0, 0);
	wait1Msec(2000);
	while(true) {
		float currentElevatorVelocity = -( SensorValue[elevatorEncoder] - pastElevatorVelocity)/timeIntervalElevator;
		float error = (goalElevatorVelocity - currentElevatorVelocity);
		if (abs(vexRT[Ch3Xmtr2]) > 20) {
			setElevator(80);
		}else {
			setElevator(0);
		}
		/*
		if (shooting) {

			if (curElevatorState == ingateReadyToShoot) {
				setElevator(100);
				while(getSwitch()) {wait1Msec(100);}

				clearTimer(T2);
				wait1Msec(350);
				curElevatorState = notIngateNotReadyToShoot;
			}else if (curElevatorState == notIngateNotReadyToShoot) {
				setElevator(100);
				if(getSwitch()) {
					curElevatorState = ingateNotReadyToShoot;
				}else if(shooterIsReady) {
					curElevatorState = notIngateReadyToShoot;
				}
			}else if(curElevatorState == ingateNotReadyToShoot) {
				while (!shooterIsReady) {
					setElevator(0);
				}
				setElevator(100);
				curElevatorState = ingateReadyToShoot;
			}else if(curElevatorState == notIngateReadyToShoot) {
				setElevator(110);
				while(!getSwitch()) {
				}
				setElevator(-20);
				wait1Msec(150);
				curElevatorState = ingateReadyToShoot;
			}else {
				setElevator(0);
			}
			}else {
			setElevator(vexRT[Ch3Xmtr2]);
		}
		*/


		/*
		if (abs(vexRT[Ch3Xmtr2]) > 40) {
		currentPIDValue += PIDRun(elevatorPID, error);
		setElevator(currentPIDValue);
		}else {
		setElevator(0);
		}
		writeDebugStreamLine("ELevator Vel: %4.4f, %4.4f, %4.4f", currentElevatorVelocity, error, currentPIDValue);
		*/
		pastElevatorVelocity = SensorValue[elevatorEncoder];
		wait1Msec(timeIntervalElevator);
	}
}
