#include "Button.h"
#pragma systemFile // Pesky Warnings! I know what I am doing!
// Init button with its real vexRT value
void initButton( ControllerButton b, TVexJoysticks rt ) {
	b.button = rt;
	b.commandGiven = false;
	b.currentButtonState = Released;
	b.memoryValue = false;
}
// --- 'Is' Functions ---
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

// --- Update ---
// Updates the status of each button
void update( ControllerButton b ) {
	if ( isPressed( b ) ) {
		b.currentButtonState = Pressed;
	}else if ( !isPressed( b ) ) {
		b.currentButtonState = Released;
		b.commandGiven = false;
	}
}

// --- Task ---
// This task runs to update each button to ensure that the right state is returned
task buttonTask() {
	// Init P1 Buttons
	initButton( Button8D, Btn8D );
	initButton( Button8U, Btn8U );
	initButton( Button8L, Btn8L );
	initButton( Button8R, Btn8R );

	initButton( Button7D, Btn7D );
	initButton( Button7U, Btn7U );
	initButton( Button7L, Btn7L );
	initButton( Button7R, Btn7R );

	initButton( Button7D, Btn6D );
	initButton( Button7U, Btn6U );

	initButton( Button7D, Btn5D );
	initButton( Button7U, Btn5U );

	// Init Partner Buttons
	initButton( ButtonP8D, Btn8DXmtr2 );
	initButton( ButtonP8U, Btn8UXmtr2 );
	initButton( ButtonP8L, Btn8LXmtr2 );
	initButton( ButtonP8R, Btn8RXmtr2 );

	initButton( ButtonP7D, Btn7DXmtr2 );
	initButton( ButtonP7U, Btn7UXmtr2 );
	initButton( ButtonP7L, Btn7LXmtr2 );
	initButton( ButtonP7R, Btn7RXmtr2 );

	initButton( ButtonP7D, Btn6DXmtr2 );
	initButton( ButtonP7U, Btn6UXmtr2 );

	initButton( ButtonP7D, Btn5DXmtr2 );
	initButton( ButtonP7U, Btn5UXmtr2 );
	// Update the status of each button... forever
	while (true) {
		// Update P1 Buttons
		update( Button8U );
		update( Button8D );
		update( Button8L );
		update( Button8R );

		update( Button7U );
		update( Button7D );
		update( Button7L );
		update( Button7R );

		update( Button6U );
		update( Button6D );

		update( Button5U );
		update( Button5D );

		// Update Partner Buttons
		update( ButtonP8U );
		update( ButtonP8D );
		update( ButtonP8L );
		update( ButtonP8R );

		update( ButtonP7U );
		update( ButtonP7D );
		update( ButtonP7L );
		update( ButtonP7R );

		update( ButtonP6U );
		update( ButtonP6D );

		update( ButtonP5U );
		update( ButtonP5D );
	}
}
