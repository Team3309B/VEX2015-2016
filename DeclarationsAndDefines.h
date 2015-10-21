#include "PID.c"
#ifdef AT_COMPETITION

	#define UPDATECONTROLLER

	#define LOGENCODERS
	#define LOGDRIVEPID
	#define LOGSHOOTERPID

	#define INIT_GYRO_ON_STARTUP // Takes a three second gyro init period upon startup
#endif
bool isAuto = false;

// -- Misc Vars --
#define METERS_TO_CENTIMETERS(x) ()

// -- Task Management Vars ---
bool isBallMode = true; // Keeps track of which tasks are running

// --- Drive Vars ---
// Starting values set by LCD screen to be x and y at beginning of match
int startx = 0;
int starty = 0;
// Drive Equation Stuff
float xLeft = 0;
float yLeft = 0;
float xRight = 0;
float yRight = 0;
float pastLeft = 0;
float pastRight = 0;
float pastGyro = SensorValue[gyro];
#define driveEquationDelayAmount 150 //Amount delayed between each loop of drive equation
#define MAX_ANG_VEL 1.8 // Max Turning Speed
#define MAX_VEL .6 // Max Forward Velocity
#define wheelDeadband .02
#define throttleDeadband .02
PID gyroDrivePID;
PID driveLeftDrivePID;
PID driveRightDrivePID;
PID holdAnglePID;
PID holdEnPID;
float oldWheel = 0.0;

// --- Shooter Vars ---
float aimShooterSpeed = 0;
float shooterSpeed = 0;
float currentVelocity = 0;
float previousShooterVelocity = 0;
float pastShooter;
bool shooting = false;
bool shooterIsReady = false;
PID shooterQuickPID; // Gets there super quickly
PID shooterConstantPID; // Balances power to keep consistent speed
int ticksSinceShoot = 0;
#define TICKS_TO_USE_QUICK_SPEED_AFTER_SHOOTING 300
#define SHOOTER_OFFSET_AFTER_SHOOTING 20
#define shooterEquationDelayAmount 100

PID elevatorPID;
float pastElevatorVelocity = 0;
#define ELEVATOR_MAX_SPEED .95
typedef enum {
	ingateReadyToShoot = 0,
	notIngateReadyToShoot = 1,
	ingateNotReadyToShoot = 2,
	notIngateNotReadyToShoot = 3,
} ElevatorState;
ElevatorState curElevatorState = notIngateNotReadyToShoot;
float aimElevatorSpeed = 0;

// --- Auto Making Constants ---
// Starting Positions for match play (LCD uses them)
// Red
#define RED_OUTSIDE_X 100
#define RED_OUTSIDE_Y 100
#define RED_INSIDE_X 100
#define RED_INSIDE_Y 100
// Blue
#define BLUE_OUTSIDE_X 100
#define BLUE_OUTSIDE_Y 100
#define BLUE_INSIDE_X 100
#define BLUE_INSIDE_Y 100
