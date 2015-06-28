#include "Button.h"
// init button with its real vexRT value
void initButton( ControllerButton b, TVexJoysticks rt ) {
	b.button = rt;
	b.commandGiven = false;
	b.currentButtonState = Released;
	b.memoryValue = false;
}

// Will return true whenever button is pressed
int isPressed( ControllerButton b ) {
	return vexRT[b.button];
}

// Will return true if button is released
int isReleased( ControllerButton b ) {
	return !vexRT[b.button];
}

// Will return true once the button was released last time it was checked but is now pressed
int isTapped( ControllerButton b ) {
	if (b.currentButtonState == Pressed && !b.commandGiven ) {
			b.commandGiven = true;
			return true;
	}
	return false;
}

void update( ControllerButton b ) {
	if ( isPressed( b ) ) {
		b.currentButtonState = Pressed;
	}else if ( !isPressed( b ) ) {
		b.currentButtonState = Released;
		b.commandGiven = false;
	}
}

task buttonTask() {
	// Init P1 Buttons
	initButton( Button8D, Btn8D );

	// Update the status of each button... forever
	while (true) {
		update( Button8D );
	}
}
