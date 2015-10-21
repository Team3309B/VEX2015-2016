void setElevator(int power) {
	motor[elevator2] = power;
}

void setElevatorVelocity(int velocity) {
	aimElevatorSpeed = velocity;
}

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
	PIDInit(elevatorPID, 20, .05, 0);
  aimElevatorSpeed = 0;
	while(true) {
		float currentElevatorVelocity = -( SensorValue[elevatorEncoder] - pastElevatorVelocity)/timeIntervalElevator;
		if(isAuto) {
				//aimElevatorSpeed = (float)ELEVATOR_MAX_SPEED * (float)((float)vexRT[Ch3Xmtr2]/127);
				float error = (aimElevatorSpeed - currentElevatorVelocity);
				currentPIDValue += PIDRun(elevatorPID, error);
				if (currentPIDValue > 127) {
					currentPIDValue = 127;
					}	else if (currentPIDValue < -127) {
					currentPIDValue = -127;
				}
				char inFormat[32];
				sprintf(inFormat, "%3.3f,%3.3f,%3.3f", currentElevatorVelocity, aimElevatorSpeed, currentPIDValue);
				writeDebugStreamLine(inFormat);
				sendString(uartOne, inFormat);
				pastElevatorVelocity = SensorValue[elevatorEncoder];
				setElevator(currentPIDValue);
				writeDebugStreamLine("%4.4f, %4.4f, %4.4f", aimElevatorSpeed, error, currentPIDValue);
		} else {
		if (abs(vexRT[Ch3Xmtr2]) > 20) {
				setElevator(vexRT[Ch3Xmtr2]);
		}else {
			setElevator(0);
		}
	}


		wait1Msec(timeIntervalElevator);
	}
}
