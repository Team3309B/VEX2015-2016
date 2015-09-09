void setElevator(int power) {
	motor[elevator1] = power;
	motor[elevator2] = power;
}

// Elevator and Hopper Mechanism
task elevatorTask() {
	PIDInit(elevatorPID, 1, 0, 0);
	while(true) {
		float currentElevatorVelocity = (
		setElevatorSpeed(PIDCompute(elevatorPID, ));
	}
}
