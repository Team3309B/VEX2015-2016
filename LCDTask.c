#include "LCD.c"
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

typedef enum {
	MainMenu = 0,
	StartingPositionMenu = 1,
	AutoSelector = 2,
} LCDMenuType;
string textForMenu[] = {"Select Auto"};
string textForStartingPositionMenu[] = {"Red Inside", "Blue Inside", "Red Outside", "Blue Outside"};
string textForAutoSelector[] = {"The Norm", "Defense", "Do Nothing", "Make Your Own"};
void findCorrectMenu(LCDMenuType type) {
	string array[20];
	switch(type) {
	case MainMenu:
		array = textForMenu;
		break;
	case AutoSelector:
		array = textForAutoSelector;
	default:
		break;
	}
	LCDSetLine01(	array[LCD.count], "<     Enter    >" );
	LCDWaitForPress();
	if ( LCDIsLeftButtonPressed() ) {
		LCDWaitForRelease();
		if ( LCD.count == 0 ) {
			LCD.count = ARRAYSIZE(array);
		}else {
			LCD.count--;
		}
	}else if ( LCDIsRightButtonPressed() ) {
		LCDWaitForRelease();
		if ( LCD.count == ARRAYSIZE(array) ) {
				LCD.count = 0;
		}else {
			LCD.count++;
		}
	}
}

void 	LCDRunIntroScreen() {
	LCDAnimateFromBottom("WELCOME!", "TEAM 3309 LCD PROGRAM");
	wait1Msec(250);
	LCDAnimateFromBottom("MAIN MENU INCOMING" , ":)");
	wait1Msec(250);
}

void LCDRunAutoSelector() {
	while( !LCDIsCenterButtonPressed() )	{
			findCorrectMenu(StartingPositionMenu);
	}
	if ( strcmp(LCD.line0, "Red Inside") ) {

	}else if ( strcmp(LCD.line0, "Red Outside") ) {

	}else if ( strcmp(LCD.line0, "Blue Inside") ) {

	}else if ( strcmp(LCD.line0, "Blue Outside") ) {

	}
	LCDWaitForRelease();
	while( !LCDIsCenterButtonPressed() )	{
			findCorrectMenu(AutoSelector);
	}
	LCDWaitForRelease();
	// Respond to selection (use strcmp instead of count because order may change later in season)
	if ( strcmp(LCD.line0, "The Norm") ) {
		LCD.auto[0] = "M1";
		LCD.auto[1] = "R1";
		LCD.auto[2] = "B1";
	}else if ( strcmp(LCD.line0, "Defense") ) {

	}
}

void LCDRunMainMenu() {
	while( !LCDIsCenterButtonPressed() )	{
		findCorrectMenu(MainMenu);
	}
	LCDWaitForRelease();
	// Respond to selection (use strcmp instead of count because order may change later in season)
	if ( strcmp(LCD.line0, "Select Auto") ) {
		LCDRunAutoSelector();
	}else {
		LCDRunAutoSelector();
	}
}

task runLCD(){
	LCDRunIntroScreen();
	LCDRunMainMenu();
}
