#include "LCD.h"
// Init LCD Screen
void LCDinit() {
	LCD.count = 0;
	LCD.line0 = "";
	LCD.line1 = "";
}
void setLine01(string newLine0, string newLine1) {

}

void setLine10(string newLine1, string newLine0) {

}

void setLine0(string newLine0) {

}

void setLine1(string newLine1) {

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

void animateFromBottom(string newLine0, string newLine1) {

}
