void setElevator(int power) {
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
ElevatorState curElevatorState = notIngateNotReadyToShoot;
task elevatorTask() {
	PIDInit(elevatorPID, 10, 0, 0);
	wait1Msec(2000);
	while(true) {
		float currentElevatorVelocity = -( SensorValue[elevatorEncoder] - pastElevatorVelocity)/timeIntervalElevator;
		float error = (goalElevatorVelocity - currentElevatorVelocity);
		if (shooting) {

			if (curElevatorState == ingateReadyToShoot) {
				setElevator(127);
				while(SensorValue[elevatorTopLimitSwitch] == 1) {}
				clearTimer(T2);
				curElevatorState = notIngateNotReadyToShoot;
			}else if (curElevatorState == notIngateNotReadyToShoot) {
				setElevator(127);
				if(SensorValue[elevatorTopLimitSwitch] == 1) {
					setElevator(-20);
					wait1Msec(100);
					curElevatorState = ingateNotReadyToShoot;
				}else if(shooterIsReady) {
					curElevatorState = notIngateReadyToShoot;
				}
			}else if(curElevatorState == ingateNotReadyToShoot) {
				while (!shooterIsReady) {
					setElevator(-5);
				}
				setElevator(110);
				curElevatorState = ingateReadyToShoot;
			}else if(curElevatorState == notIngateReadyToShoot) {
				setElevator(110);
				while(!SensorValue[elevatorTopLimitSwitch]) {
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
