#include "PID.h"
void PIDInit(struct PID controller, float kP, float kD) {
	controller.kP = kP;
	controller.kD = kD;
}

float PIDRun(struct PID controller, float error) {

	// calculate the derivative
	float pidDerivative = error - controller.previousError;
	controller.previousError = error;
	// calculate drive
	writeDebugStreamLine("KP: %4.4f KD: %4.4f", (controller.kP * error),(controller.kD * pidDerivative));
	return ((controller.kP * error)  + (controller.kD * pidDerivative));


}

int requestedGyroAngle;
struct PID gyroPID;
void 	PIDStartGyroTask(struct PID controller, int requested) {
	requestedGyroAngle = requested;
	startTask(gyro);
	gyroPID = controller;

}


task PIDGyroController() {
		int pidDrive = PIDRun(gyroPID, SensorValue[gyro] - requestedGyroAngle);
		motor[leftFront] = pidDrive;
		motor[leftBack] = pidDrive;
		motor[rightFront] = -pidDrive;
		motor[rightBack] = -pidDrive;
}

void 	PIDStopGyroTask(struct PID controller) {
	stopTask(gyro);
}
