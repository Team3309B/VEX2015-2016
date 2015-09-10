void setElevator(int power) {
	motor[elevator1] = power;
	motor[elevator2] = power;
}

float goalElevatorVelocity = 0.8;
int timeIntervalElevator = 100;
float currentPIDValue = 0;
// Elevator and Hopper Mechanism
task elevatorTask() {
	PIDInit(elevatorPID, 10, 0, 0);
	while(true) {
			float currentElevatorVelocity = -( SensorValue[elevatorEncoder] - pastElevatorVelocity)/timeIntervalElevator;
			float error = (goalElevatorVelocity - currentElevatorVelocity);
		if (abs(vexRT[Ch3Xmtr2]) > 40) {
			currentPIDValue += PIDRun(elevatorPID, error);
			setElevator(currentPIDValue);
		}else {
			setElevator(0);
		}
		writeDebugStreamLine("ELevator Vel: %4.4f, %4.4f, %4.4f", currentElevatorVelocity, error, currentPIDValue);
		pastElevatorVelocity = SensorValue[elevatorEncoder];
		//setElevator(80);
		wait1Msec(timeIntervalElevator);
	}
}
