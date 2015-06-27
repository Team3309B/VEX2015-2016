#ifndef BUTTON_HEADER
#define BUTTON_HEADER

typedef enum{
	Released = 0,
	Pressed = 1,
}ButtonState;

struct ControllerButton {
	TVexJoysticks button;
	ButtonState currentButtonState;
};

int isPressed( ControllerButton b );
int isTapped( ControllerButton b );
int isReleased( ControllerButton b );
#endif
