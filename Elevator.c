void setElevator(int power) {
	motor[elevator1] = power;
	motor[elevator2] = power;
}

// Elevator and Hopper Mechanism
task elevatorTask()
{

	while(true) {
		setElevator(vexRT[Ch3Xmtr2] );
	}


}
