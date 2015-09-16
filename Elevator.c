void setElevator(int power) {
	motor[elevator1] = power;
	motor[elevator2] = power;
}

typedef enum {
	ingateReadyToShoot = 0,
	notIngateReadyToShoot = 1,
	ingateNotReadyToShoot = 2,
	notIngateNotReadyToShoot = 3,
} ElevatorState;

float goalElevatorVelocity = 0.8;
int timeIntervalElevator = 100;
float currentPIDValue = 0;
// Elevator and Hopper Mechanism
ElevatorState curElevatorState = ingateReadyToShoot;
task elevatorTask() {
	PIDInit(elevatorPID, 10, 0, 0);
	wait1Msec(2000);
	while(true) {
		float currentElevatorVelocity = -( SensorValue[elevatorEncoder] - pastElevatorVelocity)/timeIntervalElevator;
		float error = (goalElevatorVelocity - currentElevatorVelocity);
		if (curElevatorState == ingateReadyToShoot) {
			setElevator(127);
			while(SensorValue[elevatorTopLimitSwitch] == 1) {}
			clearTimer(T2);
			curElevatorState = notIngateNotReadyToShoot;
		}else if (curElevatorState == notIngateNotReadyToShoot) {
			setElevator(127);
			if(SensorValue[elevatorTopLimitSwitch] == 1) {
					curElevatorState = ingateNotReadyToShoot;
			}
		}else if(curElevatorState == ingateNotReadyToShoot) {
			setElevator(-127);
			wait1Msec(100);
			while (!shooterIsReady) {
				setElevator(0);
			}
			setElevator(110);
			curElevatorState = ingateReadyToShoot;
		}else if(curElevatorState == notIngateReadyToShoot) {
			setElevator(110);
			while(!SensorValue[elevatorTopLimitSwitch]) {
			}
			setElevator(127);
			wait1Msec(2000);
			curElevatorState = ingateNotReadyToShoot;
		}else {
			setElevator(0);
		}
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
