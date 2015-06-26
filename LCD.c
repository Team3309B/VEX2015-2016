#include "LCD.h"
// Init LCD Screen
void LCDinit() {
	LCD.count = 0;
	LCD.line0 = "";
	LCD.line1 = "";
}
void setLine01(char* newLine0, char* newLine1) {
	LCD.line0 = newLine0;
	LCD.line1 = newLine1;
	displayLCDCenteredString(0, newLine0);
	displayLCDCenteredString(1, newLine1);
}

void setLine10(string newLine1, string newLine0) {
	LCD.line0 = newLine0;
	LCD.line1 = newLine1;
	displayLCDCenteredString(0, newLine0);
	displayLCDCenteredString(1, newLine1);
}

void setLine0(string newLine0) {
	LCD.line0 = newLine0;
	displayLCDCenteredString(0, newLine0);
}

void setLine1(string newLine1) {
	LCD.line1 = newLine1;
	displayLCDCenteredString(1, newLine1);
}

//Wait for Press--------------------------------------------------
void LCDwaitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(25);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void LCDwaitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(25);
}
//----------------------------------------------------------------

void animateFromBottom(char* newLine0, char* newLine1) {
	setLine01(LCD.line1, " ");
	wait1Msec(250);
	setLine01(" ", newLine0);
	wait1Msec(250);
	setLine01(newLine0, newLine1);
}

void animateFromTop(char* newLine0, char* newLine1) {
	setLine01(" ", LCD.line0);
	wait1Msec(250);
	setLine01(newLine1, " ");
	wait1Msec(250);
	setLine01(newLine0, newLine1);
}

void animateFromRight(char* newLine0, char* newLine1) {
	writeDebugStream("%4.4f", strlen(LCD.line0) );
	int starting0 = 7 - (strlen(LCD.line0)/2);
	int starting1 = 7 - (strlen(LCD.line1)/2);
	int greater = 0;

	if (starting0 > starting1) {
		greater = starting0;
	}else {
		greater = starting1;
	}
	for (int i = greater; i >= -greater; i--) {
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, i, LCD.line0);
		displayLCDString(1, i, LCD.line1);
		wait1Msec(50);
	}
	clearLCDLine(0);
	clearLCDLine(1);

	starting0 = 7 - (strlen(newLine0)/2);
	starting1 = 7 - (strlen(newLine1)/2);
	if (starting0 > starting1) {
		greater = starting0;
	}else {
		greater = starting1;
	}
	for (int i = 16; i >= 1; i--) {
		if (i >= starting0) {
			clearLCDLine(0);
			displayLCDString(0, i, newLine0);
		}
		if (i >= starting1) {
			clearLCDLine(1);
			displayLCDString(1, i, newLine1);
		}
		wait1Msec(50);
	}
	clearLCDLine(0);
	clearLCDLine(1);
	setLine01(newLine0, newLine1);
}

void animateFromLeft(char* newLine0, char* newLine1) {
	writeDebugStream("%4.4f", strlen(LCD.line0) );
	int starting0 = 7 - (strlen(LCD.line0)/2);
	int starting1 = 7 - (strlen(LCD.line1)/2);
	for (int i = 1; i <= 16; i++) {
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, starting0 + i, LCD.line0);
		displayLCDString(1, starting1 + i, LCD.line1);
		wait1Msec(50);
	}
	clearLCDLine(0);
	clearLCDLine(1);

	starting0 = 7 - (strlen(newLine0)/2);
	starting1 = 7 - (strlen(newLine1)/2);
	for (int i = 1; i <= 16; i++) {
		if (i <= starting0) {
			clearLCDLine(0);
			displayLCDString(0, i, newLine0);
		}
		if (i <= starting1) {
			clearLCDLine(1);
			displayLCDString(1, i, newLine1);
		}
		wait1Msec(50);
	}
	clearLCDLine(0);
	clearLCDLine(1);
	setLine01(newLine0, newLine1);
}
