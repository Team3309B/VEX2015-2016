#ifndef PID_HEADER
#define PID_HEADER

struct PID {
	float kP;
	float kD;
	float kI;
  float kILimit;
  float integral;
	float previousError;
};

void PIDInit(PID controller, float kP, float kI, float kD);
void PIDInit(PID controller, float kP, float kD);
float PIDRun(PID controller, float error);
void PIDSetIntegralLimit(PID controller, float kILimit);
void PIDResetIntegral(PID controller);


#endif
