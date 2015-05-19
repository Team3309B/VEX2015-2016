

struct PID {
	float kP;
	float kD;

	float previousError;
};

void PIDInit(struct PID controller, float kP, float kD);
float PIDRun(struct PID controller, float error);
void 	PIDStartGyroTask(struct PID controller, int requested);
void 	PIDStopGyroTask(struct PID controller);
