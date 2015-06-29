#include "LCD.h" // Header File, import this anywhere you wish to use LCD functions
#pragma systemFile // Remove unreferenced function warnings

// --- Init LCD Screen ---
void LCDInit() {
	LCD.count = 0;
	LCD.line0 = "";
	LCD.line1 = "";
	LCD.auto[0] = "None";
	LCD.auto[1] = "None";
	LCD.auto[2] = "None";
	LCD.auto[3] = "None";
	LCD.auto[4] = "None";
}
// --- LCD Button Functions ---
bool LCDIsLeftButtonPressed() {
	if (nLCDButtons == leftBtnVEX) {
		return true;
	}
	return false;
}

bool LCDIsRightButtonPressed() {
	if (nLCDButtons == rightBtnVEX) {
		return true;
	}
	return false;
}

bool LCDIsCenterButtonPressed() {
	if (nLCDButtons == centerBtnVEX) {
		return true;
	}
	return false;
}

// --- Clearing Functions ---
// Clears the top line
void LCDClear0() {
	clearLCDLine(0);
	LCD.line0 = "";
}

// Clears the bottom line
void LCDClear1() {
	clearLCDLine(1);
	LCD.line1 = "";
}

// Clears both lines
void LCDClear() {
	LCDClear0();
	LCDClear1();
}

// --- Setting Functions ---
// Set 1st param to top line and 2nd param to bottom line
void LCDSetLine01(char* newLine0, char* newLine1) {
	LCD.line0 = newLine0;
	LCD.line1 = newLine1;
	displayLCDCenteredString(0, newLine0);
	displayLCDCenteredString(1, newLine1);
}

// Set 1st param to bottom line and 2nd param to top line
void LCDSetLine10(char*  newLine1, char*  newLine0) {
	LCD.line0 = newLine0;
	LCD.line1 = newLine1;
	displayLCDCenteredString(0, newLine0);
	displayLCDCenteredString(1, newLine1);
}

// Set top line
void LCDSetLine0(char*  newLine0) {
	LCD.line0 = newLine0;
	displayLCDCenteredString(0, newLine0);
}

// Set bottom line
void LCDSetLine1(char*  newLine1) {
	LCD.line1 = newLine1;
	displayLCDCenteredString(1, newLine1);
}

// --- Waiting Functions ---
// Will pause whatever task until any button/buttons is/are pressed
void LCDWaitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(25);
}

// Will pause whatever task until no buttons are being pressed
void LCDWaitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(25);
}

// --- Animation Functions --
// The old texts goes off the top and the new text comes in from the bottom
void LCDAnimateFromBottom(char* newLine0, char* newLine1) {
	LCDSetLine01(LCD.line1, " ");
	wait1Msec(250);
	LCDSetLine01(" ", newLine0);
	wait1Msec(250);
	LCDSetLine01(newLine0, newLine1);
}

// The old texts goes off the buttom and the new text comes in from the top
void LCDAnimateFromTop(char* newLine0, char* newLine1) {
	LCDSetLine01(" ", LCD.line0);
	wait1Msec(250);
	LCDSetLine01(newLine1, " ");
	wait1Msec(250);
	LCDSetLine01(newLine0, newLine1);
}

// Sends the old text to the left and brings the new text on from the right
void LCDAnimateFromRight(char* newLine0, char* newLine1) {
	int starting0 = 7 - (strlen(LCD.line0)/2);
	int starting1 = 7 - (strlen(LCD.line1)/2);
	int greater = 0;
	if (starting0 > starting1) {
		greater = starting0;
	}else {
		greater = starting1;
	}
	// Animate the old text from middle to left
	for (int i = greater; i >= -greater; i--) {
		LCDClear();
		displayLCDString(0, i, LCD.line0);
		displayLCDString(1, i, LCD.line1);
		wait1Msec(50);
	}
	LCDClear();
	starting0 = 7 - (strlen(newLine0)/2);
	starting1 = 7 - (strlen(newLine1)/2);
	// Animate the new text from right to middle
	for (int i = 16; i >= 1; i--) {
		if (i >= starting0) {
			LCDClear0();
			LCDSetLine0(newLine0);
		}
		if (i >= starting1) {
			LCDClear1();
			LCDSetLine1(newLine1);
		}
		wait1Msec(50);
	}
	LCDClear();
	LCDSetLine01(newLine0, newLine1);
}

// Sends the old text to the right and brings the new text on from the left
void LCDAnimateFromLeft(char* newLine0, char* newLine1) {
	int starting0 = 7 - (strlen(LCD.line0)/2);
	int starting1 = 7 - (strlen(LCD.line1)/2);
	// Animate the old text from middle to right
	for (int i = 1; i <= 16; i++) {
		LCDClear();
		displayLCDString(0, starting0 + i, LCD.line0);
		displayLCDString(1, starting1 + i, LCD.line1);
		wait1Msec(50);
	}
	LCDClear();
	starting0 = 7 - (strlen(newLine0)/2);
	starting1 = 7 - (strlen(newLine1)/2);
	// Animate the new text from left to middle
	for (int i = 1; i <= 16; i++) {
		if (i <= starting0) {
			LCDClear0();
			displayLCDString(0, i, newLine0);
		}
		if (i <= starting1) {
			LCDClear1();
			displayLCDString(1, i, newLine1);
		}
		wait1Msec(50);
	}
	LCDClear();
	LCDSetLine01(newLine0, newLine1);
}
