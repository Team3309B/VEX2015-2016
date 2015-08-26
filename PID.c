#include "PID.h"
#ifndef PID_SOURCE
#define PID_SOURCE
#pragma systemFile
void PIDInit(PID controller, float kP, float kD) {
	controller.kP = kP;
	controller.kI = 0;
	controller.kD = kD;
	controller.integral = 0;
	controller.kILimit = 50;
}

void PIDInit(PID controller, float kP, float kI, float kD) {
	controller.kP = kP;
	controller.kI = kI;
	controller.kD = kD;
	controller.integral = 0;
	controller.kILimit = 50;
}

float PIDRun(PID controller, float error) {

	// calculate the derivative
	float pidDerivative = error - controller.previousError;
	controller.previousError = error;

	if(controller.integral > controller.kILimit)
		controller.integral = controller.kILimit;

	if(controller.integral < -controller.kILimit)
		controller.integral = -controller.kILimit;

	//writeDebugStreamLine("KP: %4.4f KD: %4.4f", (controller.kP * error),(controller.kD * pidDerivative));
	return (float)((float)(controller.kP * error)  + (float)(controller.kI * controller.integral) + (float)(controller.kD * pidDerivative));
}

// Sets the limit for the integral constant
void PIDSetIntegralLimit(PID controller, float kILimit) {
	controller.kILimit = kILimit;
}

// Restes the integral value
void PIDResetIntegral(PID controller) {
	controller.integral = 0;
}
#endif
