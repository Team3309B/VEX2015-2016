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

// Controller 1 Buttons
ControllerButton Button8D;
ControllerButton Button8U;
ControllerButton Button8L;
ControllerButton Button8R;

ControllerButton Button7D;
ControllerButton Button7U;
ControllerButton Button7L;
ControllerButton Button7R;

ControllerButton Button5D;
ControllerButton Button5U;

ControllerButton Button6D;
ControllerButton Button6U;

// Controller 2 Buttons
ControllerButton ButtonP8D;
ControllerButton ButtonP8U;
ControllerButton ButtonP8L;
ControllerButton ButtonP8R;

ControllerButton ButtonP7D;
ControllerButton ButtonP7U;
ControllerButton ButtonP7L;
ControllerButton ButtonP7R;

ControllerButton ButtonP5D;
ControllerButton ButtonP5U;

ControllerButton ButtonP6D;
ControllerButton ButtonP6U;
#endif
