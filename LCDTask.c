#include "LCD.c"
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

typedef enum {
	MainMenu = 0,
	StartingPositionMenu = 1,
	AutoSelector = 2,
	MakeYourOwnAutoPosition = 3,
	MakeYourOwnAutoShootingLocation = 4,
} LCDMenuType;
string textForMenu[] = {"Select Auto"};
string textForStartingPositionMenu[] = {"Red Inside", "Blue Inside", "Red Outside", "Blue Outside"};
string textForAutoSelector[] = {"The Norm", "Defense", "Do Nothing", "Make Your Own"};
string textForMakeYourOwnAutoPosition[] = {"R1", "R2", "R3", "M1", "M2", "B1", "B2", "B3", "Done"};
string textForMakeYourOwnAutoShooting[] = {"Default", "Center", "Goal"};
bool goLeftNextTime = false;
void findCorrectMenu(LCDMenuType type) {
	string array[20];
	switch(type) {
	case MainMenu:
		array = textForMenu;
		break;
	case AutoSelector:
		array = textForAutoSelector;
		break;
	case MakeYourOwnAutoPosition:
		array = textForMakeYourOwnAutoPosition;
		break;
	case MakeYourOwnAutoShootingLocation:
		array = textForMakeYourOwnAutoShooting;
		break;
	default:
		break;
	}
	if (goLeftNextTime) {
		LCDAnimateFromRight(0, 		array[LCD.count], "<     Enter    >" );
	}else {
		LCDAnimateFromLeft(0, 		array[LCD.count], "<     Enter    >" );
	}
	LCDWaitForPress();
	if ( LCDIsLeftButtonPressed() ) {
		goLeftNextTime = true;
		LCDWaitForRelease();
		if ( LCD.count == 0 ) {
			LCD.count = ARRAYSIZE(array);
		}else {
			LCD.count--;
		}
	}else if ( LCDIsRightButtonPressed() ) {
		goLeftNextTime = false;
		LCDWaitForRelease();
		if ( LCD.count == ARRAYSIZE(array) ) {
				LCD.count = 0;
		}else {
			LCD.count++;
		}
	}
}



void LCDRunMakeYourOwnAutoMenu() {
	bool running = true;
	while ( running ) {
		LCDAnimateFromBottom("Choose A Position", "<     Enter    >" );
		while( !LCDIsCenterButtonPressed() )	{
				findCorrectMenu(MakeYourOwnAutoPosition);
		}
		LCDWaitForRelease();
		if ( strcmp( LCD.line0, "Done" ) ) {
			running = false;
		}else {
			LCDAnimateFromBottom( "Where to shoot from?", "<     Enter    >"  );
			LCDAddAuto( LCD.line0 );
			while( !LCDIsCenterButtonPressed() )	{
				findCorrectMenu(MakeYourOwnAutoShootingLocation);
			}
			LCDWaitForRelease();
			if ( strcmp(LCD.line0, "Done") ) {
				running = false;
			}	else {
				LCDAddAuto( LCD.line0 );
			}
		}
	}
	LCDAnimateFromBottom( "I HOPE AUTO MAKES IT!", "GOOD LUCK!");
}

void LCDRunAutoSelector() {
	while( !LCDIsCenterButtonPressed() )	{
			findCorrectMenu(StartingPositionMenu);
	}
	// Set the starting Position for Drive depending on what starting position was selected
	if ( strcmp(LCD.line0, "Red Inside") ) {
		startx = RED_INSIDE_X;
		starty = RED_INSIDE_Y;
	}else if ( strcmp(LCD.line0, "Red Outside") ) {
		startx = RED_OUTSIDE_X;
		starty = RED_OUTSIDE_Y;
	}else if ( strcmp(LCD.line0, "Blue Inside") ) {
		startx = BLUE_INSIDE_X;
		starty = BLUE_INSIDE_Y;
	}else if ( strcmp(LCD.line0, "Blue Outside") ) {
		startx = BLUE_OUTSIDE_X;
		starty = BLUE_OUTSIDE_Y;
	}
	LCDWaitForRelease();
	while( !LCDIsCenterButtonPressed() )	{
			findCorrectMenu(AutoSelector);
	}
	LCDWaitForRelease();
	// Respond to selection (use strcmp instead of count because order may change later in season)
	if ( strcmp(LCD.line0, "The Norm") ) {
		LCDAddAuto( "M1" );
		LCDAddAuto( "R1" );
		LCDAddAuto( "B1" );
	}else if ( strcmp(LCD.line0, "Defense") ) {
		LCDAddAuto( "Defense" );
	}else if ( strcmp(LCD.line0, "Make Your Own") ) {
		LCDRunMakeYourOwnAutoMenu();
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

void 	LCDRunIntroScreen() {
	LCDAnimateFromBottom("WELCOME!", "TEAM 3309 LCD PROGRAM");
	wait1Msec(250);
	LCDAnimateFromBottom("MAIN MENU INCOMING" , ":)");
	wait1Msec(250);
}

task runLCD(){
	LCDRunIntroScreen();
	LCDRunMainMenu();
}
