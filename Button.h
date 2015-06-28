#ifndef BUTTON_HEADER
#define BUTTON_HEADER

typedef enum{
	Released = 0,
	Pressed = 1,
}ButtonState;

struct ControllerButton {
	TVexJoysticks button; // Which button on remote
	ButtonState currentButtonState; // Released or Pressed
	bool commandGiven; // Ensures that isTapped can only return true once per tap
	bool memoryValue; // Used for toggles with one button
};
void initButton( ControllerButton b, TVexJoysticks rt );
int isPressed( ControllerButton b );
int isTapped( ControllerButton b );
int isReleased( ControllerButton b );

ControllerButton Button8D ;
#endif
