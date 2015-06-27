#include "Button.h"
// Will return true whenever button is pressed
int isPressed( ControllerButton b ) {
	return vexRT[b.button];
}

// Will return true once the button was released last time it was checked but is now pressed
int isTapped( ControllerButton b ) {
	return true;
}

// Will return true once the button was pressed last time it was check but is now released
int isReleased( ControllerButton b ) {
	return true;
}
