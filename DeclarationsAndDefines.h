#include "Button.c"
#ifdef AT_COMPETITION

	#define UPDATECONTROLLER

	#define LOGENCODERS
	#define LOGDRIVEPID
	#define LOGSHOOTERPID

	#define INIT_GYRO_ON_STARTUP // Takes a three second gyro init period upon startup
#endif

// -- Task Management Vars ---
bool isBallMode = true; // Keeps track of which tasks are running

// --- Drive Vars ---
// Starting values set by LCD screen to be x and y at beginning of match
int startx = 0;
int starty = 0;
int x = 0;
int y = 0;

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
